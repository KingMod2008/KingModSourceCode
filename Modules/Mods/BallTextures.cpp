#include "BallTextures.hpp"
#include "../../Components/Components/Instances.hpp"
#include "../../Components/Components/Console.hpp"
#include "../../Components/Components/Main.hpp"
#include "../../Modules/Mods/GameEventHook.hpp"
#include <chrono>
#pragma warning(disable: 4996)

                                                               
                                                       
                                                               

                            
bool                                          BallTexturesModule::IsEnabled         = true;
bool                                          BallTexturesModule::IsInGame          = false;
AGameEvent_Soccar_TA*                         BallTexturesModule::CurrentGameEvent  = nullptr;
fs::path                                      BallTexturesModule::BallTexturesFolder;
std::unordered_map<std::string, BallSkinData> BallTexturesModule::SavedTextureData;
std::string                                   BallTexturesModule::SelectedSkinName;

                 
static std::chrono::steady_clock::time_point  s_lastCacheClear;
static bool                                   s_hooksRegistered = false;

                       
static void OnGameEventChanged();
static void ClearTextureCache();
static bool ShouldSkipApplication();

                                                               
                                                            
  
     
                   
                       
                   
                                    
                                    
                                   
         
       
     
                                                               
namespace
{
	static size_t skipWS(const std::string& s, size_t p)
	{
		while (p < s.size() && (s[p] == ' ' || s[p] == '\t' || s[p] == '\r' || s[p] == '\n'))
			p++;
		return p;
	}

	                                                             
	static std::string parseStr(const std::string& s, size_t& p)
	{
		if (p >= s.size() || s[p] != '"')
			return {};
		p++;
		std::string out;
		while (p < s.size() && s[p] != '"')
		{
			if (s[p] == '\\' && p + 1 < s.size())
			{
				p++;
				switch (s[p])
				{
				case '"':  out += '"';  break;
				case '\\': out += '\\'; break;
				case '/':  out += '/';  break;
				case 'n':  out += '\n'; break;
				case 't':  out += '\t'; break;
				case 'r':  out += '\r'; break;
				default:   out += s[p]; break;
				}
			}
			else
			{
				out += s[p];
			}
			p++;
		}
		if (p < s.size())
			p++;                    
		return out;
	}

	                                                                        
	static void skipValue(const std::string& s, size_t& p);

	static void skipObject(const std::string& s, size_t& p)
	{
		                
		p++;
		int depth = 1;
		while (p < s.size() && depth > 0)
		{
			p = skipWS(s, p);
			if (s[p] == '"')
			{
				parseStr(s, p);            
				p = skipWS(s, p);
				if (p < s.size() && s[p] == ':')
					p++;
				p = skipWS(s, p);
				skipValue(s, p);
				p = skipWS(s, p);
				if (p < s.size() && s[p] == ',')
					p++;
			}
			else if (s[p] == '}')
			{
				p++;
				depth--;
			}
			else
			{
				p++;
			}
		}
	}

	static void skipValue(const std::string& s, size_t& p)
	{
		p = skipWS(s, p);
		if (p >= s.size())
			return;
		if (s[p] == '"')
		{
			parseStr(s, p);
		}
		else if (s[p] == '{')
		{
			skipObject(s, p);
		}
		else if (s[p] == '[')
		{
			p++;
			int depth = 1;
			while (p < s.size() && depth > 0)
			{
				if (s[p] == '[')      depth++;
				else if (s[p] == ']') depth--;
				else if (s[p] == '"') parseStr(s, p);
				if (depth > 0)        p++;
			}
			if (p < s.size())
				p++;            
		}
		else
		{
			                       
			while (p < s.size() && s[p] != ',' && s[p] != '}' && s[p] != ']' && s[p] != '\n')
				p++;
		}
	}

	                                                              
	                     
	static std::unordered_map<std::string, std::string> parseStringMap(const std::string& s, size_t& p)
	{
		std::unordered_map<std::string, std::string> result;
		if (p >= s.size() || s[p] != '{')
			return result;
		p++;
		while (p < s.size())
		{
			p = skipWS(s, p);
			if (p >= s.size() || s[p] == '}')
			{
				if (p < s.size())
					p++;
				break;
			}
			if (s[p] != '"')
			{
				p++;
				continue;
			}
			std::string key = parseStr(s, p);
			p               = skipWS(s, p);
			if (p < s.size() && s[p] == ':')
				p++;
			p = skipWS(s, p);

			if (p < s.size() && s[p] == '"')
			{
				result[key] = parseStr(s, p);
			}
			else
			{
				skipValue(s, p);
			}

			p = skipWS(s, p);
			if (p < s.size() && s[p] == ',')
				p++;
		}
		return result;
	}

	                                 
	                                                                    
	static std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
	parseSkinFile(const std::string& json)
	{
		std::unordered_map<std::string, std::unordered_map<std::string, std::string>> result;
		size_t p = skipWS(json, 0);
		if (p >= json.size() || json[p] != '{')
			return result;
		p++;                          

		while (p < json.size())
		{
			p = skipWS(json, p);
			if (p >= json.size() || json[p] == '}')
				break;
			if (json[p] != '"')
			{
				p++;
				continue;
			}

			std::string skinName = parseStr(json, p);
			p                   = skipWS(json, p);
			if (p < json.size() && json[p] == ':')
				p++;
			p = skipWS(json, p);

			if (p >= json.size() || json[p] != '{')
			{
				skipValue(json, p);
				p = skipWS(json, p);
				if (p < json.size() && json[p] == ',')
					p++;
				continue;
			}

			                             
			p++;                     
			std::unordered_map<std::string, std::string> params;

			while (p < json.size())
			{
				p = skipWS(json, p);
				if (p >= json.size() || json[p] == '}')
				{
					if (p < json.size())
						p++;
					break;
				}
				if (json[p] != '"')
				{
					p++;
					continue;
				}

				std::string key = parseStr(json, p);
				p               = skipWS(json, p);
				if (p < json.size() && json[p] == ':')
					p++;
				p = skipWS(json, p);

				if (key == "Params" && p < json.size() && json[p] == '{')
				{
					params = parseStringMap(json, p);
				}
				else
				{
					skipValue(json, p);
				}

				p = skipWS(json, p);
				if (p < json.size() && json[p] == ',')
					p++;
			}

			if (!params.empty())
				result[skinName] = params;

			p = skipWS(json, p);
			if (p < json.size() && json[p] == ',')
				p++;
		}

		return result;
	}
}                       

                                                               
                      
                                                               

BallTexturesModule::BallTexturesModule() : Module("BallTextures", "Custom ball texture swapping", States::STATES_All)
{
	s_lastCacheClear = std::chrono::steady_clock::now();
	OnCreate();
}

BallTexturesModule::~BallTexturesModule()
{
	OnDestroy();
}

void BallTexturesModule::OnCreate() {}

void BallTexturesModule::OnDestroy()
{
	for (auto& [name, skin] : SavedTextureData)
		skin.clearLoadedTextures();
	SavedTextureData.clear();
}

void BallTexturesModule::Initialize()
{
	                                                      
	wchar_t exePath[MAX_PATH] = {};
	if (GetModuleFileNameW(nullptr, exePath, MAX_PATH))
	{
		fs::path basePath = fs::path(exePath).parent_path();
		BallTexturesFolder = basePath / "KingMod" / "Texture" / "Ball";
	}
	else
	{
		BallTexturesFolder = fs::current_path() / "KingMod" / "Texture" / "Ball";
	}

	if (!fs::exists(BallTexturesFolder))
	{
		std::error_code ec;
		if (fs::create_directories(BallTexturesFolder, ec))
			Console.Write("[BallTextures] Created BallTextures folder: " + BallTexturesFolder.string());
		else
			Console.Error("[BallTextures] Failed to create BallTextures folder: " + ec.message());
	}

	Console.Write("[BallTextures] Using folder: " + BallTexturesFolder.string());

	Hook();
	SearchForBallSkins();

	Console.Write("[BallTextures] Initialized.");
}

void BallTexturesModule::Hook()
{
	Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay",          &OnGameEventStart);
	Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Active.BeginState",      &OnGameEventStart);
	Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Countdown.BeginState",   &OnGameEventStart);
	Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed",              &OnGameEventDestroyed);
	Events.HookEventPost("Function TAGame.FXActor_Ball_TA.StartBallFadeIn",           &OnBallFadeInPost);
	Events.HookEventPost("Function TAGame.GFxHUD_TA.HandleReplaceBot",                &OnReplaceBotPost);
	
	                                                  
	Events.HookEventPost("Function TAGame.PlayerController_TA.PlayerTick",          [](const PostEvent&) { BallTextures.OnTick(); });
}

                                                               
         
                                                               

void BallTexturesModule::OnGameEventStart(PreEvent& event)
{
	try
	{
		if (event.Caller() && event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
		{
			AGameEvent_Soccar_TA* gameEvent = static_cast<AGameEvent_Soccar_TA*>(event.Caller());
			
			                                                       
			bool isReplay = (gameEvent->WorldInfo && gameEvent->WorldInfo->Game && 
				gameEvent->WorldInfo->Game->IsA(AGameInfo_Replay_TA::StaticClass()));
			
			if (isReplay)
			{
				Console.Write("[BallTextures] Replay mode detected - skipping texture application");
				                                                                               
				IsInGame = true;
				return;
			}
			
			CurrentGameEvent = gameEvent;
			IsInGame = true;
			Console.Write("[BallTextures] GameEvent acquired: " + std::string(event.Function()->GetName()));
			
			                                                                    
			if (!SelectedSkinName.empty())
			{
				Main.Execute([]() { ApplySelectedSkinToAllBalls(); });
			}
		}
	}
	catch (...) { Console.Error("[BallTextures] Exception in OnGameEventStart"); }
}

void BallTexturesModule::OnGameEventDestroyed(PreEvent& event)
{
	try
	{
		                                                                                
		if (event.Caller() && event.Caller() == CurrentGameEvent)
		{
			Console.Write("[BallTextures] Current game event destroyed, clearing state");
			CurrentGameEvent = nullptr;
			IsInGame = false;
		}
		else if (event.Caller() && event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
		{
			                                                                
			Console.Write("[BallTextures] Other game event destroyed (likely replay)");
		}
	}
	catch (...) { Console.Error("[BallTextures] Exception in OnGameEventDestroyed"); }
}

void BallTexturesModule::OnBallFadeInPost(const PostEvent& event)
{
	try
	{
		if (!event.Caller())
			return;

		if (!event.Caller() || !event.Caller()->IsA(AFXActor_Ball_TA::StaticClass()))
			return;
		AFXActor_Ball_TA* fxActor = static_cast<AFXActor_Ball_TA*>(event.Caller());

		ABall_TA* ball = fxActor->Ball;
		if (!ball)
			return;

		BallSkinData* skin = GetSelectedSkin();
		if (!skin)
			return;

		                                             
		ABall_TA* arch = nullptr;
		if (ball->ObjectArchetype && ball->ObjectArchetype->IsA(ABall_TA::StaticClass()))
			arch = static_cast<ABall_TA*>(ball->ObjectArchetype);

		ApplySkinToBall(ball, *skin);
		if (arch)
			ApplySkinToBallArchetype(arch, *skin);
		ApplySkinToBallDissolveMIC(*skin);
	}
	catch (...) { Console.Error("[BallTextures] Exception in OnBallFadeInPost"); }
}

void BallTexturesModule::OnReplaceBotPost(const PostEvent& event)
{
	try
	{
		Main.Execute([]() { ApplySelectedSkinToAllBalls(); });
	}
	catch (...) { Console.Error("[BallTextures] Exception in OnReplaceBotPost"); }
}

                                                               
                       
                                                               

void BallTexturesModule::ApplySelectedSkinToAllBalls()
{
	if (ShouldSkipApplication())
		return;

	BallSkinData* skin = GetSelectedSkin();
	if (!skin)
		return;

	ApplySkinToBallDissolveMIC(*skin);

	if (!CurrentGameEvent)
	{
		CurrentGameEvent = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();
	}

	if (!CurrentGameEvent)
	{
		Console.Error("[BallTextures] No valid GameEvent_Soccar_TA found");
		return;
	}

	Console.Write("[BallTextures] Applying skin to " + std::to_string(CurrentGameEvent->GameBalls.size()) + " ball(s)");

	for (ABall_TA* ball : CurrentGameEvent->GameBalls)
		ApplySkinToBall(ball, *skin);

	if (CurrentGameEvent->BallArchetype)
		ApplySkinToBallArchetype(CurrentGameEvent->BallArchetype, *skin);
}

static void ApplyParamsToMIC(UMaterialInstanceConstant* mic, const BallSkinData& skin, const std::string& context)
{
	if (!mic)
		return;

	for (const auto& [paramName, texData] : skin.paramTextures)
	{
		if (!texData.texture)
			continue;

		FName param{ std::wstring(paramName.begin(), paramName.end()).c_str() };

		mic->SetTextureParameterValue(param, texData.texture);
	}
}

void BallTexturesModule::ApplySkinToBall(ABall_TA* ball, const BallSkinData& skin)
{
	if (!ball)
		return;

	UStaticMeshComponent* mesh = ball->StaticMesh;
	if (!mesh)
		return;

	UMaterialInstanceConstant* mic = nullptr;
	if (mesh->Materials.empty())
		mic = mesh->ConditionalCreateMIC(0);
	else if (auto* existingMI = mesh->GetMaterial(0))
	{
		if (existingMI->IsA<UMaterialInstanceConstant>())
			mic = static_cast<UMaterialInstanceConstant*>(existingMI);
	}

	ApplyParamsToMIC(mic, skin, "ball mesh MIC");
}

void BallTexturesModule::ApplySkinToBallArchetype(ABall_TA* arch, const BallSkinData& skin)
{
	if (!arch)
		return;

	UStaticMeshComponent* mesh = arch->StaticMesh;
	if (!mesh)
		return;

	UMaterialInstanceConstant* mic = nullptr;
	if (mesh->Materials.empty())
		mic = mesh->ConditionalCreateMIC(0);
	else if (auto* existingMI = mesh->GetMaterial(0))
	{
		if (existingMI->IsA<UMaterialInstanceConstant>())
			mic = static_cast<UMaterialInstanceConstant*>(existingMI);
	}

	ApplyParamsToMIC(mic, skin, "ball archetype MIC");
}

void BallTexturesModule::ApplySkinToBallDissolveMIC(const BallSkinData& skin)
{
	UMaterialInstanceConstant* dissolveMIC = GetBallDissolveMIC();
	if (!dissolveMIC)
	{
		Console.Error("[BallTextures] Could not find BallDissolve MIC");
		return;
	}
	ApplyParamsToMIC(dissolveMIC, skin, "ball dissolve MIC");
}

UMaterialInstanceConstant* BallTexturesModule::GetBallDissolveMIC()
{
	constexpr int32_t ITER_OFFSET = 10;
	for (int32_t i = static_cast<int32_t>(UObject::GObjObjects()->size()) - ITER_OFFSET; i > 0; --i)
	{
		UObject* obj = UObject::GObjObjects()->at(i);
		if (!obj || !obj->IsA<UMaterialInstanceConstant>())
			continue;

		if (obj->GetName().find("BallDissolve_Soccar") != 0)
			continue;

		return static_cast<UMaterialInstanceConstant*>(obj);
	}
	return nullptr;
}

                                                               
                                  
                                                               

void BallTexturesModule::SearchForBallSkins()
{
	                 
	for (auto& [name, skin] : SavedTextureData)
		skin.clearLoadedTextures();
	SavedTextureData.clear();

	if (!fs::exists(BallTexturesFolder))
	{
		Console.Error("[BallTextures] BallTextures folder does not exist: " + BallTexturesFolder.string());
		return;
	}

	                                                           
	std::vector<fs::path> pngFiles;
	try
	{
		for (const auto& entry : fs::directory_iterator(BallTexturesFolder))
		{
			if (!entry.is_regular_file())
				continue;

			std::string ext = entry.path().extension().string();
			for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
			if (ext == ".png" || ext == ".jpg" || ext == ".jpeg")
			{
				pngFiles.push_back(entry.path());
			}
		}
	}
	catch (...) {}

	                                      
	for (const auto& pngPath : pngFiles)
	{
		std::string skinName = pngPath.stem().string();
		BallSkinData skin;
		skin.name = skinName;
		skin.jsonFile = BallTexturesFolder / (skinName + ".json");
		skin.paramTextures.emplace("Diffuse", BallTexData{ pngPath, nullptr });
		SavedTextureData["Auto: " + skinName] = std::move(skin);

		                                              
		if (!fs::exists(skin.jsonFile))
		{
			std::ofstream f(skin.jsonFile);
			if (f.is_open())
			{
				f << "{ \"" << skinName << "\": { \"Params\": { \"Diffuse\": \"" << pngPath.filename().string() << "\" } } }";
				f.close();
			}
		}
	}

	                                                         
	try
	{
		for (const auto& entry : fs::recursive_directory_iterator(BallTexturesFolder))
		{
			if (!entry.is_regular_file())
				continue;

			std::string ext = entry.path().extension().string();
			for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
			if (ext != ".json")
				continue;

			                                                 
			std::string stem = entry.path().stem().string();
			bool isAutoGenerated = false;
			for (const auto& png : pngFiles)
			{
				if (png.stem().string() == stem)
				{
					isAutoGenerated = true;
					break;
				}
			}
			if (isAutoGenerated)
				continue;

			            
			std::ifstream f(entry.path());
			if (!f.is_open())
				continue;
			std::string jsonText((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
			f.close();

			auto parsed = parseSkinFile(jsonText);
			if (parsed.empty())
				continue;

			std::error_code ec;
			fs::path        relPath = fs::relative(entry.path(), BallTexturesFolder, ec);
			if (ec)
				continue;

			for (auto& [skinName, params] : parsed)
			{
				BallSkinData skin;
				skin.name     = skinName;
				skin.jsonFile = entry.path();

				for (const auto& [paramName, relImgPath] : params)
				{
					if (relImgPath.empty())
						continue;

					fs::path fullImgPath = entry.path().parent_path() / relImgPath;
					fullImgPath          = fs::weakly_canonical(fullImgPath);

					skin.paramTextures.emplace(paramName, BallTexData{ fullImgPath, nullptr });
				}

				if (skin.paramTextures.empty())
					continue;

				std::string key = relPath.string() + " - " + skinName;
				SavedTextureData[key] = std::move(skin);
			}
		}
	}
	catch (const fs::filesystem_error& e)
	{
		Console.Error("[BallTextures] Filesystem error while scanning: " + std::string(e.what()));
	}

	Console.Write("[BallTextures] Found " + std::to_string(SavedTextureData.size()) + " ball skin(s).");

	                                          
	if (SelectedSkinName.empty() && !SavedTextureData.empty())
		SelectedSkinName = SavedTextureData.begin()->first;
}

BallSkinData* BallTexturesModule::GetSelectedSkin()
{
	auto it = SavedTextureData.find(SelectedSkinName);
	if (it == SavedTextureData.end())
		return nullptr;

	BallSkinData& skin = it->second;
	if (!skin.bTexturesLoaded)
	{
		if (!skin.loadTextures())
		{
			Console.Error("[BallTextures] Failed to load textures for skin: " + SelectedSkinName);
			return nullptr;
		}
	}

	return &skin;
}

                                                               
                           
                                                               

bool BallTexturesModule::GetFileBytes(const fs::path& filePath, std::vector<uint8_t>& outBytes)
{
	std::ifstream file(filePath, std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		Console.Error("[BallTextures] Failed to open file: " + filePath.string());
		return false;
	}

	std::streamsize size = file.tellg();
	if (size <= 0)
	{
		Console.Error("[BallTextures] File is empty: " + filePath.string());
		return false;
	}

	file.seekg(0, std::ios::beg);
	outBytes.resize(static_cast<size_t>(size));
	if (!file.read(reinterpret_cast<char*>(outBytes.data()), size))
	{
		Console.Error("[BallTextures] Failed to read file: " + filePath.string());
		return false;
	}

	Console.Write("[BallTextures] Loaded " + std::to_string(size) + " bytes from " + filePath.filename().string());
	return true;
}

UTexture2DDynamic* BallTexturesModule::ImgPathToTexture(const fs::path& imgPath, bool doMarkInvincible)
{
	if (!fs::exists(imgPath))
	{
		Console.Error("[BallTextures] Image does not exist: " + imgPath.string());
		return nullptr;
	}

	std::vector<uint8_t> bytes;
	if (!GetFileBytes(imgPath, bytes))
		return nullptr;

	UTexture2DDynamic* tex = Instances.CreateInstance<UTexture2DDynamic>();
	if (!tex)
	{
		Console.Error("[BallTextures] Failed to create UTexture2DDynamic instance");
		return nullptr;
	}

	tex->CompressionFullDynamicRange = true;
	tex->CompressionSettings         = ETextureCompressionSettings::TC_NormalmapUncompressed;
	tex->Init(50, 50, EPixelFormat::PF_A8R8G8B8, false);

	                                                                                      
	                                                                                        
	                                                                         
	struct RawTArray { uint8_t* data; int32_t size; int32_t cap; };
	RawTArray raw{ bytes.data(), static_cast<int32_t>(bytes.size()), static_cast<int32_t>(bytes.size()) };
	TArray<uint8_t>& sdkBytes = *reinterpret_cast<TArray<uint8_t>*>(&raw);

	std::string ext = imgPath.extension().string();
	for (auto& c : ext) c = static_cast<char>(tolower(static_cast<unsigned char>(c)));

	if (ext == ".png")
	{
		tex->UpdateMipFromPNG(0, sdkBytes);
	}
	else if (ext == ".jpg" || ext == ".jpeg")
	{
		tex->UpdateMipFromJPEG(0, sdkBytes);
	}
	else
	{
		Console.Error("[BallTextures] Unsupported image format: " + ext + "  (use .png or .jpg)");
		Instances.MarkForDestory(tex);
		return nullptr;
	}

	if (doMarkInvincible)
		Instances.MarkInvincible(tex);

	Console.Write("[BallTextures] Texture created from: " + imgPath.filename().string());
	return tex;
}

                                                               
                        
                                                               

bool BallSkinData::loadTextures()
{
	for (auto& [paramName, texData] : paramTextures)
	{
		if (texData.texture)
			continue;

		UTexture2DDynamic* created = BallTexturesModule::ImgPathToTexture(texData.imgPath);
		if (!created)
			return false;

		texData.texture = created;
	}

	bTexturesLoaded = true;
	return true;
}

void BallSkinData::clearLoadedTextures()
{
	for (auto& [paramName, texData] : paramTextures)
	{
		if (!texData.texture)
			continue;

		Instances.MarkForDestory(texData.texture);
		texData.texture = nullptr;
	}
	bTexturesLoaded = false;
}

                                                               
                     
                                                               

void BallTexturesModule::RestoreDefaultTextures()
{
    Main.Execute([]()
    {
        if (!CurrentGameEvent)
            CurrentGameEvent = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();

        auto clearBallMIC = [](ABall_TA* ball)
        {
            if (!ball || !ball->StaticMesh || ball->StaticMesh->Materials.empty())
                return;

            UMaterialInterface* mi = ball->StaticMesh->GetMaterial(0);
            if (mi && mi->IsA<UMaterialInstanceConstant>())
                static_cast<UMaterialInstanceConstant*>(mi)->ClearParameterValues();
        };

        if (CurrentGameEvent)
        {
            for (ABall_TA* ball : CurrentGameEvent->GameBalls)
                clearBallMIC(ball);
            clearBallMIC(CurrentGameEvent->BallArchetype);
        }

        if (UMaterialInstanceConstant* dissolve = GetBallDissolveMIC())
            dissolve->ClearParameterValues();

        for (auto& [name, skin] : SavedTextureData)
            skin.clearLoadedTextures();
    });
}

                                                               
                    
                                                               

static void ClearTextureCache()
{
	auto now = std::chrono::steady_clock::now();
	if (std::chrono::duration_cast<std::chrono::minutes>(now - s_lastCacheClear).count() >= 5)
	{
		for (auto& [name, skin] : BallTexturesModule::SavedTextureData)
		{
			skin.clearLoadedTextures();
		}
		s_lastCacheClear = now;
		Console.Write("[BallTextures] Cache cleared (5min interval)");
	}
}

static bool ShouldSkipApplication()
{
	if (!BallTexturesModule::IsEnabled)
		return true;

	if (!BallTexturesModule::CurrentGameEvent)
		BallTexturesModule::CurrentGameEvent = GameEventHookModule::CurrentGameEvent;

	if (!BallTexturesModule::CurrentGameEvent)
		BallTexturesModule::CurrentGameEvent = Instances.GetInstanceOf<AGameEvent_Soccar_TA>();

	                                       
	if (!BallTexturesModule::CurrentGameEvent)
		return true;
	
	                           
	if (BallTexturesModule::SelectedSkinName.empty())
		return true;
	
	return false;
}

                                        
void BallTexturesModule::OnTick()
{
	ClearTextureCache();
}

BallTexturesModule BallTextures;
