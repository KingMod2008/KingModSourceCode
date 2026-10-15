#include "CustomBoostMeter.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../Components/Components/Main.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#pragma warning(disable: 4996)

                                                               
                          
  
                                                                 
                                                                   
                                                                    
                                                                    
                                       
  
                                                       
                            
                                                             
                                                            
                                                                       
                                                                         
                                                      
                                                               

bool                                              CustomBoostMeterModule::IsEnabled        = false;
bool                                              CustomBoostMeterModule::IsInGame         = false;
fs::path                                          CustomBoostMeterModule::MeterFolder;
std::unordered_map<std::string, BoostMeterSkin>   CustomBoostMeterModule::SavedSkins;
std::string                                       CustomBoostMeterModule::SelectedSkinName;
bool                                              CustomBoostMeterModule::PendingApply     = false;

CustomBoostMeterModule::CustomBoostMeterModule()
    : Module("CustomBoostMeter", "HUD boost-meter texture replacement", States::STATES_All) {}
CustomBoostMeterModule::~CustomBoostMeterModule() {}
void CustomBoostMeterModule::OnCreate()  {}
void CustomBoostMeterModule::OnDestroy() {}

CustomBoostMeterModule CustomBoostMeter;

                                                                        
                                                                                  
                                                                                 
                                                                       
                                                                         
                                           
                                         
                                                                           
static std::unordered_map<std::string, std::string> g_LayerTargets = {
                  
    { "Background",      "GFX_Hud.BoostMeter_Background" },
    { "Fill",            "GFX_Hud.BoostMeter_Fill" },
    { "Tint",            "GFX_Hud.BoostMeter_FillTintablePortion" },
    { "Glow",            "GFX_Hud.BoostMeter_Glow" },
                                                              
    { "TimerBackground", "GFX_HudMatchInfo.MatchTimer_Background" },
    { "TimerCaption",    "GFX_HudMatchInfo.MatchTimer_CaptionBackground" },
    { "TimerBorder",     "GFX_HudMatchInfo.MatchTimer_SafeZoneBorder" },
};

std::string CustomBoostMeterModule::TargetForLayer(const std::string& layerName)
{
    auto it = g_LayerTargets.find(layerName);
    return it != g_LayerTargets.end() ? it->second : layerName;
}

                                                               
                    
                                                               

struct BoostMeterOverride
{
    UTexture* target;                                           
    UTexture* source;                                                            
    FPointer  originalResource;                                          
};

static std::vector<BoostMeterOverride> g_Overrides;

                                                                            
                                                                            
                                                              
static bool g_WantActive = false;

                                                                           
                                                                           
                                                                  
static ULONGLONG g_LastMeterReassertTick = 0;
static constexpr ULONGLONG kMeterReassertIntervalMs = 100;

                                                               
                                                                         
                                                               

static bool MeterGetFileBytes(const fs::path& filePath, std::vector<uint8_t>& outBytes)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) return false;
    std::streamsize size = file.tellg();
    if (size <= 0) return false;
    file.seekg(0, std::ios::beg);
    outBytes.resize(static_cast<size_t>(size));
    return static_cast<bool>(file.read(reinterpret_cast<char*>(outBytes.data()), size));
}

                                                                              
                                                   
static bool SafeSwapResourceInner(UTexture* target, const FPointer* srcResource, FPointer* outOriginal)
{
    if (!target || !srcResource || !outOriginal) return false;
    __try
    {
        if (target->Resource.Dummy != 0 && srcResource->Dummy != 0)
        {
            *outOriginal = target->Resource;
            target->Resource = *srcResource;
            return true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

static bool SafeRestoreResourceInner(UTexture* target, const FPointer* originalResource)
{
    if (!target || !originalResource) return false;
    __try
    {
        target->Resource = *originalResource;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

                                                                       
                                                                          
static void UnsafeAssignObjectFullName(UObject* object, std::string* outName)
{
    *outName = object->GetFullName();
}

static bool SafeGetObjectFullNameInner(UObject* object, std::string* outName)
{
    if (!object || !outName) return false;
    __try
    {
        UnsafeAssignObjectFullName(object, outName);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

static void RememberOverride(UTexture* target, UTexture* source, const FPointer& original)
{
    for (const BoostMeterOverride& e : g_Overrides)
        if (e.target == target) return;                              
    g_Overrides.push_back(BoostMeterOverride{ target, source, original });
}

                                                                        
static bool SafeResourceEquals(UTexture* target, const FPointer* other, bool* outEqual)
{
    if (!target || !other || !outEqual) return false;
    __try
    {
        *outEqual = (target->Resource.Dummy == other->Dummy);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

                                                                              
static bool SafeReassertResource(UTexture* target, const FPointer* srcResource)
{
    if (!target || !srcResource) return false;
    __try
    {
        if (target->Resource.Dummy != 0 && srcResource->Dummy != 0)
        {
            target->Resource = *srcResource;
            return true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

                                                                 
static bool SafeGetTextureSize(UTexture2D* tex, int* outX, int* outY)
{
    if (!tex || !outX || !outY) return false;
    __try
    {
        *outX = tex->SizeX;
        *outY = tex->SizeY;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { }
    return false;
}

                                                                               
                                                                               
                                                                      
                                                                                
                                                                                 
static bool SafeIsLiveObject(void* obj)
{
    uintptr_t addr = reinterpret_cast<uintptr_t>(obj);
    if (addr < 0x10000 || (addr & 0x7) != 0)
        return false;
    __try
    {
        uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(addr);
        if (vtable < 0x10000 || (vtable & 0x7) != 0) return false;
        volatile uintptr_t vtFirst = *reinterpret_cast<volatile uintptr_t*>(vtable);
        (void)vtFirst;
        uintptr_t klass = *reinterpret_cast<volatile uintptr_t*>(addr + 0x50);
        if (klass < 0x10000 || (klass & 0x7) != 0) return false;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

                                                               
             
                                                               

bool BoostMeterSkin::loadTextures()
{
    bool anyLoaded = false;
    for (BoostMeterLayer& layer : layers)
    {
        if (layer.texture) { anyLoaded = true; continue; }
        if (layer.imgFile.empty() || !fs::exists(layer.imgFile)) continue;

        std::vector<uint8_t> bytes;
        if (!MeterGetFileBytes(layer.imgFile, bytes)) continue;

        UTexture2DDynamic* tex = Instances.CreateInstance<UTexture2DDynamic>();
        if (!tex) continue;

        tex->CompressionFullDynamicRange = true;
        tex->CompressionSettings         = ETextureCompressionSettings::TC_NormalmapUncompressed;
        tex->Init(256, 256, EPixelFormat::PF_A8R8G8B8, false);

        struct RawTArray { uint8_t* data; int32_t size; int32_t cap; };
        RawTArray raw{ bytes.data(), static_cast<int32_t>(bytes.size()), static_cast<int32_t>(bytes.size()) };
        TArray<uint8_t>& sdkBytes = *reinterpret_cast<TArray<uint8_t>*>(&raw);

        std::string ext = layer.imgFile.extension().string();
        for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

        if (ext == ".png")
            tex->UpdateMipFromPNG(0, sdkBytes);
        else if (ext == ".jpg" || ext == ".jpeg")
            tex->UpdateMipFromJPEG(0, sdkBytes);
        else { Instances.MarkForDestory(tex); continue; }

        Instances.MarkInvincible(tex);
        layer.texture = tex;
        anyLoaded = true;
    }
    bLoaded = anyLoaded;
    return anyLoaded;
}

void BoostMeterSkin::clearLoadedTextures()
{
    for (BoostMeterLayer& layer : layers)
    {
        if (!layer.texture) continue;
        Instances.MarkForDestory(layer.texture);
        layer.texture = nullptr;
    }
    bLoaded = false;
}

                                                               
                                                                   
                                                               

namespace
{
    size_t jsSkipWS(const std::string& s, size_t p)
    {
        while (p < s.size() && (s[p] == ' ' || s[p] == '\t' || s[p] == '\r' || s[p] == '\n')) p++;
        return p;
    }

    std::string jsParseStr(const std::string& s, size_t& p)
    {
        if (p >= s.size() || s[p] != '"') return {};
        p++;
        std::string out;
        while (p < s.size() && s[p] != '"')
        {
            if (s[p] == '\\' && p + 1 < s.size())
            {
                p++;
                switch (s[p])
                {
                case 'n': out += '\n'; break;
                case 't': out += '\t'; break;
                case 'r': out += '\r'; break;
                default:  out += s[p]; break;
                }
            }
            else out += s[p];
            p++;
        }
        if (p < s.size()) p++;                 
        return out;
    }

                                                           
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
    parseMeterSkinFile(const std::string& json)
    {
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> result;
        size_t p = jsSkipWS(json, 0);
        if (p >= json.size() || json[p] != '{') return result;
        p++;

        while (p < json.size())
        {
            p = jsSkipWS(json, p);
            if (p >= json.size() || json[p] == '}') break;
            if (json[p] != '"') { p++; continue; }

            std::string skinName = jsParseStr(json, p);
            p = jsSkipWS(json, p);
            if (p < json.size() && json[p] == ':') p++;
            p = jsSkipWS(json, p);
            if (p >= json.size() || json[p] != '{') break;
            p++;                      

            std::unordered_map<std::string, std::string> layers;
            while (p < json.size())
            {
                p = jsSkipWS(json, p);
                if (p >= json.size() || json[p] == '}') { if (p < json.size()) p++; break; }
                if (json[p] != '"') { p++; continue; }

                std::string layerName = jsParseStr(json, p);
                p = jsSkipWS(json, p);
                if (p < json.size() && json[p] == ':') p++;
                p = jsSkipWS(json, p);
                if (p < json.size() && json[p] == '"')
                    layers[layerName] = jsParseStr(json, p);
                p = jsSkipWS(json, p);
                if (p < json.size() && json[p] == ',') p++;
            }

            if (!layers.empty()) result[skinName] = std::move(layers);

            p = jsSkipWS(json, p);
            if (p < json.size() && json[p] == ',') p++;
        }
        return result;
    }

}

                                                               
                        
                                                               

void CustomBoostMeterModule::Initialize()
{
    wchar_t exePath[MAX_PATH] = {};
    if (GetModuleFileNameW(nullptr, exePath, MAX_PATH) > 0)
        MeterFolder = fs::path(exePath).parent_path() / "KingMod" / "Texture" / "BoostMeter";
    else
        MeterFolder = fs::current_path() / "KingMod" / "Texture" / "BoostMeter";

    std::error_code ec;
    fs::create_directories(MeterFolder, ec);

    Console.Write("[CustomBoostMeter] Using folder: " + MeterFolder.string());
    SearchForSkins();
    Hook();
}

void CustomBoostMeterModule::SearchForSkins()
{
    for (auto& [name, skin] : SavedSkins)
        skin.clearLoadedTextures();
    SavedSkins.clear();

    if (!fs::exists(MeterFolder)) return;

    try
    {
        for (const auto& entry : fs::recursive_directory_iterator(MeterFolder))
        {
            if (!entry.is_regular_file()) continue;
            std::string ext = entry.path().extension().string();
            for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
            if (ext != ".json") continue;

            std::ifstream f(entry.path());
            if (!f.is_open()) continue;
            std::string text((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
            f.close();

            auto parsed = parseMeterSkinFile(text);
            for (auto& [skinName, layerMap] : parsed)
            {
                BoostMeterSkin skin;
                skin.name     = skinName;
                skin.jsonFile = entry.path();
                for (const auto& [layerName, relPath] : layerMap)
                {
                    if (relPath.empty()) continue;
                    fs::path full = fs::weakly_canonical(entry.path().parent_path() / relPath);
                    skin.layers.push_back(BoostMeterLayer{ layerName, full, nullptr });
                }
                if (!skin.layers.empty())
                    SavedSkins[skinName] = std::move(skin);
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        Console.Error("[CustomBoostMeter] Filesystem error while scanning: " + std::string(e.what()));
    }

    Console.Write("[CustomBoostMeter] Found " + std::to_string(SavedSkins.size()) + " skin(s).");

    if (SelectedSkinName.empty() && !SavedSkins.empty())
        SelectedSkinName = SavedSkins.begin()->first;
}

                                                               
                   
                                                               

void CustomBoostMeterModule::RestoreMeter()
{
    g_WantActive = false;
    g_LastMeterReassertTick = 0;
    size_t restored = 0;
    for (const BoostMeterOverride& e : g_Overrides)
        if (e.target && SafeIsLiveObject(e.target) && SafeRestoreResourceInner(e.target, &e.originalResource))
            ++restored;
    if (!g_Overrides.empty())
        Console.Write("[CustomBoostMeter] Restored " + std::to_string(restored) + " texture(s)");
    g_Overrides.clear();
}

                                                                             
                                                                               
                                                                               
                                                                
void CustomBoostMeterModule::ReassertOverrides()
{
    if (!g_WantActive) return;

    const ULONGLONG now = GetTickCount64();
    if (g_LastMeterReassertTick != 0 &&
        now - g_LastMeterReassertTick < kMeterReassertIntervalMs)
    {
        return;
    }
    g_LastMeterReassertTick = now;

    for (const BoostMeterOverride& e : g_Overrides)
    {
        if (!e.target || !e.source) continue;
                                                                             
                                                                                
                                                                                 
        if (!SafeIsLiveObject(e.target) || !SafeIsLiveObject(e.source)) continue;
        bool equal = true;
        if (!SafeResourceEquals(e.target, &e.source->Resource, &equal)) continue;
        if (!equal)
            SafeReassertResource(e.target, &e.source->Resource);
    }
}

void CustomBoostMeterModule::ApplySelectedSkin()
{
    if (!IsEnabled) return;
    if (!IsInGame) { PendingApply = true; return; }

    auto it = SavedSkins.find(SelectedSkinName);
    if (it == SavedSkins.end()) { Console.Error("[CustomBoostMeter] No skin selected"); return; }

    BoostMeterSkin& skin = it->second;
    if (!skin.bLoaded && !skin.loadTextures())
    {
        Console.Error("[CustomBoostMeter] Failed to load skin textures: " + SelectedSkinName);
        return;
    }

                                                                           
    RestoreMeter();
    g_WantActive = true;
    g_LastMeterReassertTick = 0;

    int applied = 0;
    for (const BoostMeterLayer& layer : skin.layers)
    {
        if (!layer.texture) continue;
        UTexture* src = static_cast<UTexture*>(static_cast<UObject*>(layer.texture));
        if (!src) continue;

        const std::string target = TargetForLayer(layer.layerName);
        if (target.empty()) continue;

                                                                                  
                                                                                 
                                                                             
        for (UTexture* gameTex : Instances.FindAllObjects<UTexture>(target))
        {
            if (!gameTex || gameTex == src) continue;

            std::string fullName;
            if (!SafeGetObjectFullNameInner(static_cast<UObject*>(gameTex), &fullName)) continue;
            const size_t pos = fullName.rfind(target);
            const bool endsAtTarget = (pos != std::string::npos) && (pos + target.size() == fullName.size());
            if (!endsAtTarget) continue;

            FPointer original{};
            if (SafeSwapResourceInner(gameTex, &src->Resource, &original))
            {
                RememberOverride(gameTex, src, original);
                ++applied;
            }
        }
    }

    Console.Write("[CustomBoostMeter] Applied skin '" + SelectedSkinName + "' ("
                  + std::to_string(applied) + " texture swap(s))");
    if (applied == 0)
        Console.Error("[CustomBoostMeter] 0 textures matched. Use 'Dump Texture Names' to find the real names, then edit layer targets.");
}

void CustomBoostMeterModule::ArmForNextTick() { PendingApply = true; }

                                                               
                                                                     
                                                                          
                                                               

void CustomBoostMeterModule::DumpTextureNames()
{
    Main.Execute([]()
    {
        std::vector<std::string> lines;
        try
        {
            for (UTexture2D* tex : Instances.GetAllInstancesOf<UTexture2D>())
            {
                if (!tex) continue;
                std::string name;
                if (!SafeGetObjectFullNameInner(static_cast<UObject*>(tex), &name)) continue;
                if (name.find("Default__") != std::string::npos) continue;

                int sx = 0, sy = 0;
                SafeGetTextureSize(tex, &sx, &sy);

                                                                                     
                if (sx > 0 && sx <= 512 && sy > 0 && sy <= 512)
                {
                    std::ostringstream oss;
                    oss << sx << "x" << sy << "  " << name;
                    lines.push_back(oss.str());
                }
            }
        }
        catch (...) {}

        fs::path outPath = MeterFolder / "texture_dump.txt";
        std::ofstream f(outPath);
        if (f.is_open())
        {
            f << "# Small UTexture2D objects (<=512^2). Find the boost meter here,\n";
            f << "# then set its name fragment as the layer target.\n";
            f << "# total: " << lines.size() << "\n\n";
            for (const std::string& l : lines) f << l << "\n";
            f.close();
            Console.Success("[CustomBoostMeter] Dumped " + std::to_string(lines.size())
                            + " textures to " + outPath.string());
            Main.SpawnNotification("KingMod", "Boost meter: dumped " + std::to_string(lines.size()) + " textures", 4);
        }
        else
        {
            Console.Error("[CustomBoostMeter] Failed to write dump file");
        }
    });
}

                                                               
         
                                                               

void CustomBoostMeterModule::OnGameEventStart(PreEvent& event)
{
    try
    {
        if (event.Caller() && event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
        {
            IsInGame = true;
            if (IsEnabled && !SelectedSkinName.empty())
                ArmForNextTick();                                        
        }
    }
    catch (...) { Console.Error("[CustomBoostMeter] Exception in OnGameEventStart"); }
}

void CustomBoostMeterModule::OnGameEventDestroyed(PreEvent&)
{
    RestoreMeter();
    IsInGame     = false;
    PendingApply = false;
}

void CustomBoostMeterModule::Hook()
{
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay",        OnGameEventStart);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed",            OnGameEventDestroyed);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Active.BeginState",    OnGameEventStart);
    Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Countdown.BeginState", OnGameEventStart);

    Events.HookEventPost("Function TAGame.PlayerController_TA.PlayerTick",
        [](const PostEvent&)
        {
            if (PendingApply && IsInGame)
            {
                PendingApply = false;
                Main.Execute([]() { ApplySelectedSkin(); });
            }
            else if (g_WantActive && IsInGame)
            {
                                                                                  
                ReassertOverrides();
            }
        });
}
