#include "Events.hpp"
#include "Console.hpp"
#include "Items.hpp"
#include "Instances.hpp"
#include "../Includes.hpp"
#include "Fun.hpp"
#include "DevConsole.hpp"
#include "Notify.hpp"
#include "../../Modules/Mods/GameEventHook.hpp"
#include "../../Modules/Mods/BallPrediction.hpp"
#include "../../Modules/Mods/TAS.hpp"
#include "../../Modules/Mods/CustomTextureStudio.hpp"
#include "../../Modules/Mods/CustomBoostMeter.hpp"
#include <cmath>
#include <algorithm>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <deque>
#include <cctype>
#include <atomic>
#include <cstdio>
#include "../../Extensions/Extensions/Colors.hpp"
#include <Windows.h>
#include <shellapi.h>
#include <shlobj.h>
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"

void ApplyPingSpoof();
void ResetPing();
void UpdateRealPing();

static inline int clampi(int v, int lo, int hi) {
	return (v < lo) ? lo : (v > hi) ? hi : v;
}

static inline uint8_t EncodePingByteFromMilliseconds(int pingMs)
{
	const int clampedPing = clampi(pingMs, 0, 1000);
	if (clampedPing <= 0)
		return 0;

	const double encoded = (255.0 * static_cast<double>(clampedPing)) / 1000.0;
	return static_cast<uint8_t>(clampi((std::max)(1, static_cast<int>(std::lround(encoded))), 0, 255));
}

static inline int DecodePingMillisecondsFromByte(uint8_t pingByte)
{
	if (pingByte == 0)
		return 0;

	return clampi(static_cast<int>(std::ceil((1000.0 * static_cast<double>(pingByte)) / 255.0)), 0, 1000);
}

static inline float StableExactPingSecondsForByte(uint8_t pingByte)
{
    if (pingByte == 0) return 0.0f;
                                                                              
                                                                           
                                                                 
    return static_cast<float>((static_cast<double>(pingByte) - 0.5) / 255.0);
}

static bool SafeProbePointer(void* ptr);

                                                                              
                                                                              
                                                                                
                                                                              
                                                                              
                                                                   
static std::atomic<uint32_t> g_ResetFnPlayerController{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnGameEvent{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnGameEventNotify{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnFreeplayCommands{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnGameEditorRound{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnGameEditorPlayer{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingEditor{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingGfx{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnFreeplayMutator{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTutorialPlayer{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingGfxShot{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingEditorBalls{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingFxBall{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTrainingGoalie{ UINT32_MAX };
                                                                    
static std::atomic<uint32_t> g_ResetFnSoccarResetGame{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnSoccarResetBalls{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnSoccarResetBall{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTutorialFreeplayResetBalls{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTutorialFreeplayResetGameEvent{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTutorialResetBalls{ UINT32_MAX };
static std::atomic<uint32_t> g_ResetFnTutorialResetGameEvent{ UINT32_MAX };
static std::atomic<ULONGLONG> g_TrainingResetQuarantineUntil{ 0 };
static std::atomic<uint32_t> g_TrainingResetGlobalDepth{ 0 };
                                                                              
                                                                                
                                                                                 
static std::atomic<uint32_t> g_RenderGameplayReaders{ 0 };
static thread_local uint32_t g_TrainingResetDepth = 0;

static bool IsTrainingResetFunctionIndex(uint32_t index)
{
    if (index == UINT32_MAX)
        return false;

    return index == g_ResetFnPlayerController.load(std::memory_order_acquire) ||
        index == g_ResetFnGameEvent.load(std::memory_order_acquire) ||
        index == g_ResetFnGameEventNotify.load(std::memory_order_acquire) ||
        index == g_ResetFnFreeplayCommands.load(std::memory_order_acquire) ||
        index == g_ResetFnGameEditorRound.load(std::memory_order_acquire) ||
        index == g_ResetFnGameEditorPlayer.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingEditor.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingGfx.load(std::memory_order_acquire) ||
        index == g_ResetFnFreeplayMutator.load(std::memory_order_acquire) ||
        index == g_ResetFnTutorialPlayer.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingGfxShot.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingEditorBalls.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingFxBall.load(std::memory_order_acquire) ||
        index == g_ResetFnTrainingGoalie.load(std::memory_order_acquire) ||
        index == g_ResetFnSoccarResetGame.load(std::memory_order_acquire) ||
        index == g_ResetFnSoccarResetBalls.load(std::memory_order_acquire) ||
        index == g_ResetFnSoccarResetBall.load(std::memory_order_acquire) ||
        index == g_ResetFnTutorialFreeplayResetBalls.load(std::memory_order_acquire) ||
        index == g_ResetFnTutorialFreeplayResetGameEvent.load(std::memory_order_acquire) ||
        index == g_ResetFnTutorialResetBalls.load(std::memory_order_acquire) ||
        index == g_ResetFnTutorialResetGameEvent.load(std::memory_order_acquire);
}

static bool IsTrainingResetQuarantineActive()
{
    const ULONGLONG until = g_TrainingResetQuarantineUntil.load(std::memory_order_acquire);
    return until != 0 && GetTickCount64() < until;
}

                                                                               
                                                                           
struct WheelSyncParams
{
	float offY[2] = { 0.0f, 0.0f };
	float offZ[2] = { 0.0f, 0.0f };
	float roll[2] = { 0.0f, 0.0f };
};

static std::string EncodeCustomTitlePayload(const std::string& text, int color, int glow)
{
	static const char hex[] = "0123456789ABCDEF";
	std::string encoded;
	encoded.reserve(text.size() * 2);
	for (unsigned char c : text)
	{
		encoded.push_back(hex[c >> 4]);
		encoded.push_back(hex[c & 15]);
	}
	char header[32]{};
	sprintf_s(header, sizeof(header), "KMCT1_%06X_%06X_", color & 0xFFFFFF, glow & 0xFFFFFF);
	return std::string(header) + encoded;
}

static bool DecodeCustomTitlePayload(const std::string& rawPayload, std::string& text, int& color, int& glow)
{
	                                                                          
	                                                      
	const size_t pipe = rawPayload.find('|');
	const std::string payload = (pipe == std::string::npos) ? rawPayload : rawPayload.substr(0, pipe);
	if (payload.size() < 21 || payload.compare(0, 6, "KMCT1_") != 0 || payload[12] != '_' || payload[19] != '_')
		return false;
	auto nibble = [](char c) -> int {
		if (c >= '0' && c <= '9') return c - '0';
		if (c >= 'A' && c <= 'F') return c - 'A' + 10;
		if (c >= 'a' && c <= 'f') return c - 'a' + 10;
		return -1;
	};
	auto parseColor = [&](size_t offset, int& value) {
		value = 0;
		for (size_t i = 0; i < 6; ++i) {
			const int n = nibble(payload[offset + i]);
			if (n < 0) return false;
			value = (value << 4) | n;
		}
		return true;
	};
	if (!parseColor(6, color) || !parseColor(13, glow) || ((payload.size() - 20) & 1) != 0)
		return false;
	text.clear();
	text.reserve((payload.size() - 20) / 2);
	for (size_t i = 20; i < payload.size(); i += 2)
	{
		const int hi = nibble(payload[i]);
		const int lo = nibble(payload[i + 1]);
		if (hi < 0 || lo < 0) return false;
		text.push_back(static_cast<char>((hi << 4) | lo));
	}
	return !text.empty();
}

                                                                              
                                                                             
                                                                            
static std::string EncodeWheelPayload(const WheelSyncParams& w)
{
	auto q = [](float v) -> uint16_t {
		float c = v;
		if (c < -120.0f) c = -120.0f;
		if (c > 120.0f) c = 120.0f;
		int iv = static_cast<int>(std::lround(c * 256.0f));
		if (iv < -32768) iv = -32768;
		if (iv > 32767) iv = 32767;
		return static_cast<uint16_t>(static_cast<int16_t>(iv));
	};
	char buf[48]{};
	sprintf_s(buf, sizeof(buf), "KMCW1_%04X%04X%04X%04X%04X%04X",
		q(w.offY[0]), q(w.offY[1]), q(w.offZ[0]), q(w.offZ[1]), q(w.roll[0]), q(w.roll[1]));
	return std::string(buf);
}

static bool DecodeWheelPayload(const std::string& raw, WheelSyncParams& out)
{
	const size_t p = raw.find("KMCW1_");
	if (p == std::string::npos)
		return false;
	const size_t start = p + 6;
	if (raw.size() < start + 24)
		return false;
	auto nibble = [](char c) -> int {
		if (c >= '0' && c <= '9') return c - '0';
		if (c >= 'A' && c <= 'F') return c - 'A' + 10;
		if (c >= 'a' && c <= 'f') return c - 'a' + 10;
		return -1;
	};
	float vals[6];
	for (int f = 0; f < 6; ++f)
	{
		int word = 0;
		for (int i = 0; i < 4; ++i)
		{
			const int n = nibble(raw[start + f * 4 + i]);
			if (n < 0) return false;
			word = (word << 4) | n;
		}
		vals[f] = static_cast<float>(static_cast<int16_t>(word)) / 256.0f;
	}
	out.offY[0] = vals[0]; out.offY[1] = vals[1];
	out.offZ[0] = vals[2]; out.offZ[1] = vals[3];
	out.roll[0] = vals[4]; out.roll[1] = vals[5];
	return true;
}

                                                                             
                                                                             
                                                                              
                                                                              
static void ApplyWheelParamsToMesh(UCarMeshComponent_TA* carMesh, const WheelSyncParams& w)
{
	if (!carMesh || carMesh->WheelControls.size() == 0)
		return;
	const int wheelCount = carMesh->WheelControls.size();
	for (int i = 0; i < wheelCount; ++i)
	{
		USkelControlSingleBone* bone = carMesh->WheelControls[i].SteerControl;
		if (!bone)
			bone = carMesh->WheelControls[i].TranslationControl;
		if (!bone)
			continue;

		const bool isFront = (i < wheelCount / 2);
		const int side = isFront ? 0 : 1;
		const int rollUnits = static_cast<int>(w.roll[side] * (65536.0f / 360.0f));

		const bool isLeft = (i % 2 == 0);
		const float ySign = isLeft ? -1.0f : 1.0f;
		const int sidedRoll = isLeft ? rollUnits : -rollUnits;

		if (bone->ControlStrength < 1.0f)
			bone->ControlStrength = 1.0f;

		                                    
		bone->BoneRotationSpace = EBoneControlSpace::BCS_ComponentSpace;
		bone->bApplyRotation = 1;
		bone->BoneRotation.Roll = sidedRoll;

		                                                                          
		bone->BoneTranslationSpace = EBoneControlSpace::BCS_ComponentSpace;
		bone->bApplyTranslation = 1;
		bone->bAddTranslation = 1;
		bone->BoneTranslation = FVector{ 0.f, ySign * w.offY[side], w.offZ[side] };
	}
}

                                                                               
                                                                               
                                                                         
                                                                               
std::string EventsComponent::BuildCustomSyncPayload()
{
	std::string payload;
	if (setcustomtitle && !titletext.empty())
		payload = EncodeCustomTitlePayload(titletext, titlecolor, titleglowcolor);
	if (wheelOffsetActive)
	{
		WheelSyncParams w;
		w.offY[0] = wheelOffsetY[0]; w.offY[1] = wheelOffsetY[1];
		w.offZ[0] = wheelOffsetZ[0]; w.offZ[1] = wheelOffsetZ[1];
		w.roll[0] = wheelRoll[0];    w.roll[1] = wheelRoll[1];
		const std::string wheelPart = EncodeWheelPayload(w);
		payload = payload.empty() ? wheelPart : (payload + "|" + wheelPart);
	}
	return payload;
}

struct CachedTitlePayload {
    std::string text;
    int color = 0;
    int glow = 0;
    uint64_t tickReceived = 0;
};
static std::unordered_map<APRI_TA*, CachedTitlePayload> g_RemoteTitleCache;

static void CacheRemoteTitle(APRI_TA* pri, const std::string& rawTitle)
{
    if (!pri) return;
    std::string decoded;
    int color = 0, glow = 0;
    if (DecodeCustomTitlePayload(rawTitle, decoded, color, glow))
    {
        auto& entry = g_RemoteTitleCache[pri];
        entry.text = decoded;
        entry.color = color;
        entry.glow = glow;
        entry.tickReceived = GetTickCount64();
    }
    else
    {
        g_RemoteTitleCache.erase(pri);
    }
}

static bool GetCachedRemoteTitle(APRI_TA* pri, std::string& text, int& color, int& glow)
{
    if (!pri) return false;
    auto it = g_RemoteTitleCache.find(pri);
    if (it == g_RemoteTitleCache.end()) return false;
    text = it->second.text;
    color = it->second.color;
    glow = it->second.glow;
    return true;
}

static bool CanSyncCustomTitles()
{
	if (Events.CanUseLocalServerFeatures())
		return true;
	try
	{
		return SafeProbePointer(GameEventHookModule::CurrentGameEvent) && GameEventHookModule::CurrentGameEvent->IsPlayingLan();
	}
	catch (...)
	{
		return false;
	}
}

static void ApplyCustomTitleRow(UGFxDataStore_X* dataStore, UGFxData_PRI_TA* row, const std::string& text, int color, int glow)
{
	if (!SafeProbePointer(dataStore) || !SafeProbePointer(row) || text.empty()) return;
	std::wstring wideTitle(text.begin(), text.end());
	FString title(wideTitle.c_str());
	FName table = L"PlayerInfo";
	dataStore->SetStringValue(table, row->RowIndex, L"XPTitle", title);
	FASValue titleColor = dataStore->GetValue(table, row->RowIndex, L"TitleColor");
	titleColor.Type = EASType::AS_UInt;
	titleColor.I = color;
	dataStore->SetASValue(table, row->RowIndex, L"TitleColor", titleColor);
	FASValue glowColor = dataStore->GetValue(table, row->RowIndex, L"TitleGlowColor");
	glowColor.Type = EASType::AS_UInt;
	glowColor.I = glow;
	dataStore->SetASValue(table, row->RowIndex, L"TitleGlowColor", glowColor);
}

#define LOG(...) Console.Write(__VA_ARGS__)

template<typename T>
bool validUObject(T* obj) {
	return obj != nullptr;
}
static bool TryReadMemoryRaw(uintptr_t address, void* result, size_t size) {
	__try {
		memcpy(result, reinterpret_cast<const void*>(address), size);
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

                                                                                 
                                                                             
static bool SafeProbePointer(void* ptr)
{
	uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
	if (addr < 0x10000 || (addr & 0x7) != 0)
		return false;
	__try {
		volatile uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(addr);
		if (vtable < 0x10000 || (vtable & 0x7) != 0)
			return false;
		volatile uintptr_t vtFirst = *reinterpret_cast<volatile uintptr_t*>(vtable);
		(void)vtFirst;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
	return true;
}

static bool SafeGetObjectInternalIndex(UObject* object, uint32_t* outIndex)
{
	if (!object || !outIndex)
		return false;

	__try {
		const int32_t index = object->ObjectInternalInteger;
		if (index < 0)
			return false;
		*outIndex = static_cast<uint32_t>(index);
		return true;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

static bool SafeObjectStillRegistered(UObject* object, uint32_t expectedIndex)
{
	if (!SafeProbePointer(object))
		return false;

	__try {
		TArray<UObject*>* objects = UObject::GObjObjects();
		if (!objects || expectedIndex >= static_cast<uint32_t>(objects->size()))
			return false;
		return objects->at(static_cast<int32_t>(expectedIndex)) == object;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

template<typename T>
static bool SafeIsObjectOfClass(T* obj, UClass* expectedClass)
{
	if (!SafeProbePointer(obj) || !expectedClass)
		return false;
	__try {
		return obj->IsA(expectedClass);
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return false;
	}
}

static APawn* SEH_GetPawn(APlayerController* pc)
{
	__try {
		return pc ? pc->Pawn : nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

static UCarMeshComponent_TA* SEH_GetCarMesh(ACar_TA* car)
{
	__try {
		return car ? car->CarMesh : nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

static APRI_TA* SEH_GetCarPRI(ACar_TA* car)
{
	__try {
		return car ? static_cast<APRI_TA*>(car->PlayerReplicationInfo) : nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

static UCarMeshComponent_TA* SEH_GetPreviewCarMesh(ACarPreviewActor_TA* previewActor)
{
	__try {
		return previewActor ? previewActor->CarMesh : nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

static UCarPreviewSet_TA* SEH_GetPreviewSet(UGFxData_Garage_TA* garage)
{
	__try {
		return garage ? garage->CarPreviewSet : nullptr;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

static int SEH_GetPreviewActorCount(UCarPreviewSet_TA* previewSet)
{
	__try {
		return previewSet ? static_cast<int>(previewSet->CarPreviewActors.size()) : 0;
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return 0;
	}
}

static ACarPreviewActor_TA* SEH_GetPreviewActor(UCarPreviewSet_TA* previewSet, int index)
{
	__try {
		if (!previewSet || index < 0 || index >= static_cast<int>(previewSet->CarPreviewActors.size()))
			return nullptr;
		return previewSet->CarPreviewActors[index];
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return nullptr;
	}
}

template<typename T>
bool TryReadMemory(uintptr_t address, T* result) {
	return TryReadMemoryRaw(address, result, sizeof(T));
}

template <typename T>
T SafeRead(uintptr_t address) {
	T result = T{};
	TryReadMemory(address, &result);
	return result;
}

namespace
{
	constexpr int kHudColorRefreshMs = 250;
	constexpr int kStadiumColorRefreshMs = 500;
	constexpr int kDynamicRainbowRefreshMs = 75;
	constexpr int kUnderglowRainbowRefreshMs = 150;
	constexpr int kDynamicStaticRefreshMs = 500;
	constexpr int kBoostColorRainbowRefreshMs = 150;
	constexpr int kBoostColorStaticRefreshMs = 1000;
	constexpr float kColorEpsilon = 0.0001f;

	float ClampColorChannel(float value)
	{
		return std::clamp(value, 0.0f, 1.0f);
	}

	                                                                         
	                                                                        
	                                                                            
	                                                                           
	std::vector<UCarMeshComponent_TA*> GetLocalCarMeshes()
	{
		std::vector<UCarMeshComponent_TA*> out;

		try {
			APlayerController* pc = Instances.IAPlayerController();
			if (SafeProbePointer(pc)) {
				APawn* pawn = SEH_GetPawn(pc);
				if (SafeIsObjectOfClass(pawn, ACar_TA::StaticClass())) {
					ACar_TA* car = static_cast<ACar_TA*>(pawn);
					if (UCarMeshComponent_TA* carMesh = SEH_GetCarMesh(car); SafeProbePointer(carMesh))
						out.push_back(carMesh);
				}
			}
		} catch (...) {}

		try {
			UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
			if (SafeProbePointer(garage)) {
				if (UCarPreviewSet_TA* previewSet = SEH_GetPreviewSet(garage); SafeProbePointer(previewSet)) {
					const int previewCount = SEH_GetPreviewActorCount(previewSet);
					for (int i = 0; i < previewCount; ++i) {
						ACarPreviewActor_TA* pa = SEH_GetPreviewActor(previewSet, i);
						if (!SafeProbePointer(pa))
							continue;
						if (UCarMeshComponent_TA* carMesh = SEH_GetPreviewCarMesh(pa); SafeProbePointer(carMesh))
							out.push_back(carMesh);
					}
				}
			}
		} catch (...) {}

		return out;
	}

	bool HasColorChanged(const float* current, const float* previous, size_t count = 4)
	{
		if (!current || !previous)
			return false;

		for (size_t i = 0; i < count; ++i)
		{
			if ((std::fabs)(current[i] - previous[i]) > kColorEpsilon)
				return true;
		}

		return false;
	}

	FLinearColor MakeUnrealLinearColor(const float* rgba)
	{
		return FLinearColor
		{
			ClampColorChannel(rgba[0]),
			ClampColorChannel(rgba[1]),
			ClampColorChannel(rgba[2]),
			ClampColorChannel(rgba[3])
		};
	}

	LinearColor MakeColorValue(const float* rgba)
	{
		return LinearColor
		{
			ClampColorChannel(rgba[0]),
			ClampColorChannel(rgba[1]),
			ClampColorChannel(rgba[2]),
			ClampColorChannel(rgba[3])
		};
	}

	void GetActiveColor(const float* base, bool rainbow, float* out)
	{
		if (!out)
			return;

		if (rainbow)
		{
			LinearColor rainbowColor = GRainbowColor::GetLinear();
			out[0] = rainbowColor.R;
			out[1] = rainbowColor.G;
			out[2] = rainbowColor.B;
			out[3] = 1.0f;
			return;
		}

		out[0] = ClampColorChannel(base[0]);
		out[1] = ClampColorChannel(base[1]);
		out[2] = ClampColorChannel(base[2]);
		out[3] = ClampColorChannel(base[3]);
	}

	std::string ToLowerCopy(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
			return static_cast<char>(std::tolower(ch));
		});
		return value;
	}

	bool ContainsInsensitive(const std::string& haystack, const std::string& needle)
	{
		if (haystack.empty() || needle.empty())
			return false;

		return ToLowerCopy(haystack).find(ToLowerCopy(needle)) != std::string::npos;
	}

	bool IsWheelMaterialName(const std::string& name)
	{
		return ContainsInsensitive(name, "wheel") ||
			ContainsInsensitive(name, "rim") ||
			ContainsInsensitive(name, "tire");
	}

	                                                                            
	                                                                        
	                                                                       
	                                             
	static void SEH_SetMICLinearColor(UMaterialInstanceConstant* mic, const FName* param, const FLinearColor* color)
	{
		__try {
			mic->SetLinearColorParameter(*param, *color);
		} __except (EXCEPTION_EXECUTE_HANDLER) {}
	}

	void SetMaterialColorParameters(UMaterialInstanceConstant* mic, const FLinearColor& color, std::initializer_list<const wchar_t*> parameterNames)
	{
		                                                                         
		                                                                        
		                                                                  
		if (!SafeProbePointer(mic))
			return;

		for (const wchar_t* parameterName : parameterNames)
		{
			FName param(parameterName);
			SEH_SetMICLinearColor(mic, &param, &color);
		}
	}

	bool CanUpdateHudTeamInfo(UGFxDataStore_X* dataStore)
	{
		if (!dataStore)
			return false;

		try
		{
			return dataStore->GetRowCount(FName(L"TeamInfo")) >= 2;
		}
		catch (...)
		{
			return false;
		}
	}

	                                                                                
	                                                                         
	                                                                              
	                                                                     
	static bool SEH_DataStoreSetColorValue(UGFxDataStore_X* dataStore, FName* table, FName* column, int row, FASValue* value)
	{
		__try
		{
			dataStore->SetASValue(*table, row, *column, *value);
			dataStore->SetDirty(*table, row, *column);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}
		return true;
	}

	void ApplyHudTeamColor(UGFxDataStore_X* dataStore, int row, const float* rgba)
	{
		if (!dataStore || row < 0 || !rgba)
			return;
		if (!SafeProbePointer(dataStore))
			return;

		uint32_t colorDecimal = Colors::LinearToDecimal(MakeColorValue(rgba));
		FName teamInfoTable = FName(L"TeamInfo");
		FName teamColorColumn = FName(L"TeamColor");
		FASValue value{};
		value.Type = EASType::AS_UInt;
		value.I = static_cast<int32_t>(colorDecimal);
		SEH_DataStoreSetColorValue(dataStore, &teamInfoTable, &teamColorColumn, row, &value);
	}

	static AGameEvent_TA* SEH_GetGameEvent(AGFxHUD_TA* hud)
	{
		__try
		{
			return hud->GetGameEvent();
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return nullptr;
		}
	}

	static int SEH_GetTeamsCount(AGameEvent_Soccar_TA* soccarEvent)
	{
		__try
		{
			return (int)soccarEvent->Teams.size();
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return 0;
		}
	}

	static ATeam_TA* SEH_GetTeam(AGameEvent_Soccar_TA* soccarEvent, int idx)
	{
		__try
		{
			return soccarEvent->Teams[idx];
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return nullptr;
		}
	}

	bool TryGetSoccarTeams(AGFxHUD_TA* hud, ATeam_TA*& blueTeam, ATeam_TA*& orangeTeam)
	{
		blueTeam = nullptr;
		orangeTeam = nullptr;

		if (!hud)
			return false;

		AGameEvent_TA* gameEvent = SEH_GetGameEvent(hud);
		if (!gameEvent)
			return false;

		if (!gameEvent->IsA<AGameEvent_Soccar_TA>())
			return false;

		AGameEvent_Soccar_TA* soccarEvent = static_cast<AGameEvent_Soccar_TA*>(gameEvent);
		if (!soccarEvent || SEH_GetTeamsCount(soccarEvent) < 2)
			return false;

		blueTeam = SEH_GetTeam(soccarEvent, 0);
		orangeTeam = SEH_GetTeam(soccarEvent, 1);
		return blueTeam != nullptr && orangeTeam != nullptr;
	}

	                                                                                
	                                                                               
	                                                
	static bool SEH_CallUpdateShaderColors(ATeam_TA* team, int teamIndex, TArray<FLinearColor>* colors)
	{
		__try
		{
			team->UpdateGameShaderParamColors(teamIndex, *colors);
		}
		__except (EXCEPTION_EXECUTE_HANDLER)
		{
			return false;
		}
		return true;
	}

	void ApplyStadiumTeamColor(ATeam_TA* team, int teamIndex, const float* rgba)
	{
		if (!team || !rgba)
			return;
		if (!SafeProbePointer(team))
			return;

		FLinearColor color = MakeUnrealLinearColor(rgba);
		TArray<FLinearColor> colorList;
		colorList.push_back(color);
		SEH_CallUpdateShaderColors(team, teamIndex, &colorList);
	}
}

PreEvent::PreEvent() : PE_Caller(nullptr), PE_Function(nullptr), PE_Params(nullptr), PE_Detour(true) {}

PreEvent::PreEvent(class UObject* caller, class UFunction* function, void* params) : PE_Caller(caller), PE_Function(function), PE_Params(params), PE_Detour(true) {}

PreEvent::~PreEvent() {}

class UObject* PreEvent::Caller() const
{
	return PE_Caller;
}

template <typename T> T* PreEvent::GetCaller() const
{
	if (PE_Caller)
	{
		return static_cast<T*>(PE_Caller);
	}

	return nullptr;
}

class UFunction* PreEvent::Function() const
{
	return PE_Function;
}

void* PreEvent::Params() const
{
	return PE_Params;
}

bool PreEvent::ShouldDetour() const
{
	if (PE_Function && EventsComponent::IsEventBlacklisted(PE_Function->ObjectInternalInteger))
	{
		return false;
	}

	return PE_Detour;
}

void PreEvent::SetDetour(bool bDetour)
{
	PE_Detour = bDetour;
}

PreEvent PreEvent::operator=(const PreEvent& other)
{
	PE_Caller = other.PE_Caller;
	PE_Function = other.PE_Function;
	PE_Params = other.PE_Params;
	PE_Detour = other.PE_Detour;
	return *this;
}

PostEvent::PostEvent() : PE_Result(nullptr) {}

PostEvent::PostEvent(class UObject* caller, class UFunction* function, void* params, void* result) : PreEvent(caller, function, params), PE_Result(result) {}

PostEvent::~PostEvent() {}

void* PostEvent::Result() const
{
	return PE_Result;
}

template <typename T> T* PostEvent::GetResult() const
{
	if (PE_Result)
	{
		return reinterpret_cast<T*>(PE_Result);
	}

	return nullptr;
}

PostEvent PostEvent::operator=(const PostEvent& other)
{
	PE_Caller = other.PE_Caller;
	PE_Function = other.PE_Function;
	PE_Params = other.PE_Params;
	PE_Detour = other.PE_Detour;
	PE_Result = other.PE_Result;
	return *this;
}

namespace Hooks
{


	void ExecuteFunctions(PreEvent& event)
	{
		                                                                      
		                                                                    
		                                          
		std::vector<std::function<void()>> functions;
		{
			std::lock_guard<std::mutex> lock(MainComponent::GameFunctionsMutex);
			functions.swap(MainComponent::GameFunctions);
		}

		for (std::function<void()>& Func : functions) {
			if (Func) {
				Func();
			}

		}

	}

	void HUDPostRender(PreEvent& event)
	{
		if (event.Caller())
		{
			AHUD* hud = event.GetCaller<AHUD>();
			if (!hud) return;
			Instances.SetHUD(hud);
			if (hud->Canvas)
				Instances.SetCanvas(hud->Canvas);
			HandleCustomFeatures();
		}
	}

	void HUDPostRenderPost(const PostEvent& event)
	{
		Manager.OnTick();


	}

	void MenuSequencerTick(PreEvent& event)
	{
		if (Events.setcustomtitle)
		{
			if (!Events.dataStore)
				Events.dataStore = Instances.GetInstanceOf<UGFxDataStore_X>();

			if (SafeProbePointer(Events.dataStore))
			{

				wchar_t* p = new wchar_t[Events.titletext.size() + 1];
				for (std::string::size_type i = 0; i < Events.titletext.size(); ++i)
					p[i] = Events.titletext[i];

				p[Events.titletext.size()] = '\0';
				FString fstitletext = FString(p);

				FName t = FName(L"PlayerTitlesPlayerTitles");
				FASValue count = Events.dataStore->GetValue(FName(L"PlayerTitles"), NULL, FName(L"SelectedTitle"));
				Events.dataStore->SetStringValue(t, count.I, FName(L"Text"), fstitletext);
				FASValue fasColor = Events.dataStore->GetValue(t, count.I, FName(L"Color"));
				fasColor.Type = EASType::AS_UInt;
				fasColor.I = Events.titlecolor;
				FASValue fasGlowColor = Events.dataStore->GetValue(t, count.I, FName(L"GlowColor"));
				fasGlowColor.Type = EASType::AS_UInt;
				fasGlowColor.I = Events.titleglowcolor;
				Events.dataStore->SetASValue(t, count.I, FName(L"Color"), fasColor);
				Events.dataStore->SetASValue(t, count.I, FName(L"GlowColor"), fasGlowColor);

				delete[] p;
			}
		}

		if (!Events.dataStore)
			Events.dataStore = Instances.GetInstanceOf<UGFxDataStore_X>();
		if (SafeProbePointer(Events.dataStore)) {
			FCustomTitleData customtitle = Events.hardcodedcustomtags[Events.playerid];
			if (customtitle.titletext != "") {
				if (customtitle.playerid == Events.playerid && Events.setcustomtitle == false && Events.dopaidcustomtitle == true) {
					FName t = FName(L"PlayerTitlesPlayerTitles");
					FASValue count = Events.dataStore->GetValue(FName(L"PlayerTitles"), NULL, FName(L"SelectedTitle"));


					std::wstring wideTitle(customtitle.titletext.begin(), customtitle.titletext.end());
					FString fTitle = FString(wideTitle.c_str());
					Events.dataStore->SetStringValue(t, count.I, FName(L"Text"), fTitle);

					FASValue fasColor = Events.dataStore->GetValue(t, count.I, FName(L"Color"));
					fasColor.Type = EASType::AS_UInt;

					fasColor.I = std::stoi(customtitle.titlecolor, 0, 16);
					FASValue fasGlowColor = Events.dataStore->GetValue(t, count.I, FName(L"GlowColor"));
					fasGlowColor.Type = EASType::AS_UInt;
					fasGlowColor.I = std::stoi(customtitle.titleglow, 0, 16);
					Events.dataStore->SetASValue(t, count.I, FName(L"Color"), fasColor);
					Events.dataStore->SetASValue(t, count.I, FName(L"GlowColor"), fasGlowColor);
				}
			}
		}
	}

	void HandleCustomFeatures()
	{
		GRainbowColor::OnTick();
		if (Events.setOnlineStatus && Events.forceStatusUpdate)
		{
			Events.forceStatusUpdate = false;

			try {

				auto onlinePlayerFriends = Instances.GetInstanceOf<UOnlinePlayerFriends_X>();
				if (onlinePlayerFriends) {

					std::wstring wideStatus(Events.customStatus.begin(), Events.customStatus.end());
					FString presenceString(wideStatus.c_str());
					FString gameDataString(L"");

					onlinePlayerFriends->SetPlatformRichPresence(0, presenceString, gameDataString);

					try {
						onlinePlayerFriends->SetEpicRichPresence(0, presenceString, gameDataString);
					}
					catch (...) {

					}

					Console.Write("[OnlineStatus] Status updated to: " + Events.customStatus);
				}
			}
			catch (...) {
				Console.Write("[OnlineStatus] Error setting rich presence");
			}
		}



		try {
			(void)Instances.IAPlayerController();
		}
		catch (...) {

		}

		const auto now = std::chrono::steady_clock::now();
		static auto lastWheelColorApply = now - std::chrono::milliseconds(kDynamicStaticRefreshMs);
		static auto lastTrimColorApply = now - std::chrono::milliseconds(kDynamicStaticRefreshMs);
		static auto lastBoostColorApply = now - std::chrono::milliseconds(kBoostColorStaticRefreshMs);

		if (Events.alphaBoostColorEnabled)
		{
			const int refreshMs = Events.alphaBoostColorRainbow ? kBoostColorRainbowRefreshMs : kBoostColorStaticRefreshMs;
			const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastBoostColorApply).count();
			if (elapsed >= refreshMs)
			{
				Events.ApplyAlphaBoostColor();
				lastBoostColorApply = now;
			}
		}

		if (Events.wheelColorEnabled)
		{
			const int refreshMs = Events.wheelColorRainbow ? kDynamicRainbowRefreshMs : kDynamicStaticRefreshMs;
			const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastWheelColorApply).count();
			if (elapsed >= refreshMs)
			{
				Events.ApplyWheelColor();
				lastWheelColorApply = now;
			}
		}


		if (Items.custompainttrim)
		{
			const int refreshMs = Items.custompainttrimrgb ? kDynamicRainbowRefreshMs : kDynamicStaticRefreshMs;
			const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTrimColorApply).count();
			if (elapsed >= refreshMs)
			{
				GameEventHookModule::UpdateBodyColor();
				lastTrimColorApply = now;
			}
		}

		                                                                    
		                                                                              
		static auto lastUnderglowApply = now - std::chrono::milliseconds(kDynamicStaticRefreshMs);
		if (Items.customunderglow || !Items.hasresetunderglow)
		{
			const int refreshMs = Items.customunderglowrgb ? kUnderglowRainbowRefreshMs : kDynamicStaticRefreshMs;
			const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUnderglowApply).count();
			if (elapsed >= refreshMs)
			{
				GameEventHookModule::UpdateUnderglowColor();
				lastUnderglowApply = now;
			}
		}

		                                                                    
		                                                                
		static auto lastPlateApply = now - std::chrono::milliseconds(kDynamicStaticRefreshMs);
		if (Items.plateFrontEnabled || Items.plateRearEnabled ||
			Items.plateFrontDirty || Items.plateRearDirty)
		{
			const auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastPlateApply).count();
			if (elapsed >= kDynamicStaticRefreshMs)
			{
				GameEventHookModule::UpdateLicensePlates();
				lastPlateApply = now;
			}
		}

		if (Events.setblackcar == true) {
			Events.setblackcar = false;
			Console.Write("[BlackCar] Apply black car triggered - starting execution");

			try {

				if (!Events.saveData) {
					Events.saveData = Instances.GetSaveData();
					Console.Write("[BlackCar] Retrieved saveData from Instances");
				}

				if (!Events.saveData) {
					Console.Write("[BlackCar] SaveData not available, skipping black car application");
					return;
				}

				FUniqueNetId netId = Instances.GetUniqueID();
				auto profile = Events.saveData->GetProfileForPlayer(netId);
				if (!profile || !profile->LoadoutSave) {
					Console.Write("[BlackCar] Profile or LoadoutSave not available");
					return;
				}

				ULoadoutSet_TA* loadoutset = profile->LoadoutSave->EquippedLoadoutSet;

				if (loadoutset)
				{
					ULoadout_TA* l0 = loadoutset->Loadouts[0];
					ULoadout_TA* l1 = loadoutset->Loadouts[1];

					if (l0)
					{
						FLoadoutData myloadout = l0->GetData();
						myloadout.TeamPaint.bSet = true;
						myloadout.TeamPaint.CustomColorID = 0;
						myloadout.TeamPaint.CustomFinishID = 0;
						myloadout.TeamPaint.Team = 2;
						myloadout.TeamPaint.TeamColorID = 90;
						myloadout.TeamPaint.TeamFinishID = 90;
						myloadout.TeamIndex = 0;
						l0->SetData(myloadout);
					}
					if (l1)
					{
						FLoadoutData myloadout = l1->GetData();
						myloadout.TeamPaint.bSet = true;
						myloadout.TeamPaint.CustomColorID = 0;
						myloadout.TeamPaint.CustomFinishID = 0;
						myloadout.TeamPaint.Team = 2;
						myloadout.TeamPaint.TeamColorID = 90;
						myloadout.TeamPaint.TeamFinishID = 90;
						myloadout.TeamIndex = 0;
						l1->SetData(myloadout);
					}
					Console.Write("[BlackCar] Black car paint applied successfully");
				}
			}
			catch (...) {
				Console.Write("[BlackCar] Error applying black car paint");
			}
		}
		if (Events.premium_garage_active) {
    try {
		{
            UGFxData_Garage_TA* garageGFX = Instances.GetInstanceOf<UGFxData_Garage_TA>();
            if (garageGFX) {
                UCarPreviewSet_TA* previewSet = garageGFX->CarPreviewSet;
                if (previewSet) {
                    ACarPreviewActor_TA* previewactor = previewSet->GetPlayerCarPreviewActor(Instances.IULocalPlayer());
                    if (!previewactor && previewSet->CarPreviewActors.size() > 0) {
                        previewactor = previewSet->CarPreviewActors[0];
                    }
                    if (previewactor) {
                        UPremiumGaragePreviewSet_TA* premGarage = Instances.GetInstanceOf<UPremiumGaragePreviewSet_TA>();
                        if (premGarage) {
                            if (ATurnTableActor_TA* tt = premGarage->GetTurntable()) {
                                previewactor->SetTurntableActor(tt, previewactor->Rotation);
                            }
                            FVector location = previewactor->Location;
                            location.Z = location.Z + 45.0f;
                            previewactor->SetLocation(location);
                            int index = 0;
                            for (ACarPreviewActor_TA* pa : previewSet->CarPreviewActors) {
                                index++;
                                if (index == 1 && pa == previewactor) {
                                    index = 0;
                                    continue;
                                }
                                if (pa && pa != previewactor) {
                                    location.X = location.X - 333.33f;
                                    pa->SetLocation(location);
                                }
                            }
                            if (ACamera_X* camera = Instances.GetInstanceOf<ACamera_X>()) {
                                FVector oldlocation = camera->Location;
                                camera->Move(oldlocation);
                            }
                        }
                    }
                }
            }
        }
    } catch (...) {}
    Events.premium_garage_active = false;
}


		if (Events.offblackcar == true) {
			Events.offblackcar = false;
			Console.Write("[BlackCar] Remove black car triggered - starting execution");

			try {

				if (!Events.saveData) {
					Events.saveData = Instances.GetSaveData();
					Console.Write("[BlackCar] Retrieved saveData from Instances");
				}

				if (!Events.saveData) {
					Console.Write("[BlackCar] SaveData not available, skipping black car removal");
					return;
				}

				FUniqueNetId netId = Instances.GetUniqueID();
				auto profile = Events.saveData->GetProfileForPlayer(netId);
				if (!profile || !profile->LoadoutSave) {
					Console.Write("[BlackCar] Profile or LoadoutSave not available");
					return;
				}

				ULoadoutSet_TA* loadoutset = profile->LoadoutSave->EquippedLoadoutSet;

				if (loadoutset)
				{
					ULoadout_TA* l0 = loadoutset->Loadouts[0];
					ULoadout_TA* l1 = loadoutset->Loadouts[1];

					if (l0)
					{
						FLoadoutData myloadout = l0->GetData();
						myloadout.TeamPaint.bSet = true;
						myloadout.TeamPaint.CustomColorID = 0;
						myloadout.TeamPaint.CustomFinishID = 0;
						myloadout.TeamPaint.Team = 0;
						myloadout.TeamPaint.TeamColorID = 90;
						myloadout.TeamPaint.TeamFinishID = 90;
						myloadout.TeamIndex = 0;
						l0->SetData(myloadout);
					}
					if (l1)
					{
						FLoadoutData myloadout = l1->GetData();
						myloadout.TeamPaint.bSet = true;
						myloadout.TeamPaint.CustomColorID = 0;
						myloadout.TeamPaint.CustomFinishID = 0;
						myloadout.TeamPaint.Team = 1;
						myloadout.TeamPaint.TeamColorID = 90;
						myloadout.TeamPaint.TeamFinishID = 90;
						myloadout.TeamIndex = 0;
						l1->SetData(myloadout);
					}
					Console.Write("[BlackCar] Black car paint removed successfully");
				}
			}
			catch (...) {
				Console.Write("[BlackCar] Error removing black car paint");
			}
		}

		try {

			if (Events.wheelSizeState == 1) {
				std::vector<UProductAsset_Wheel_TA*> Wheels = Instances.GetAllInstancesOf<UProductAsset_Wheel_TA>();

				for (UProductAsset_Wheel_TA* wheel : Wheels) {
					if (wheel) {

						wheel->MeshWidth = (int)(15 * Events.wheelWidth);
						wheel->MeshRadius = (int)(16 * Events.wheelHeight);
					}
				}


				UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
				if (garage) {
					if (garage->PreviewTeam == 0) {
						garage->SetPreviewTeam(1);
						garage->SetPreviewTeam(0);
					}
					else {
						garage->SetPreviewTeam(0);
						garage->SetPreviewTeam(1);
					}
				}




				Console.Write("[WHEEL SIZE] Applied custom wheel size - Width: " + std::to_string(Events.wheelWidth) + ", Height: " + std::to_string(Events.wheelHeight));
				Events.wheelSizeState = 2;
			}

			if (Events.wheelSizeState == 3) {
				std::vector<UProductAsset_Wheel_TA*> Wheels = Instances.GetAllInstancesOf<UProductAsset_Wheel_TA>();

				for (UProductAsset_Wheel_TA* wheel : Wheels) {
					if (wheel) {

						wheel->MeshWidth = 15;
						wheel->MeshRadius = 16;
					}
				}


				UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
				if (garage) {
					if (garage->PreviewTeam == 0) {
						garage->SetPreviewTeam(1);
						garage->SetPreviewTeam(0);
					}
					else {
						garage->SetPreviewTeam(0);
						garage->SetPreviewTeam(1);
					}
				}

				Console.Write("[WHEEL SIZE] Restored normal wheel size");
				Events.wheelSizeState = 0;
			}

			                                                          
			if (Events.wheelOffsetState == 1) {
				Events.wheelOffsetActive = true;
				Events.wheelOffsetState = 2;
				Console.Write("[WHEEL OFFSET] Live offsets enabled");
			}

			if (Events.wheelOffsetState == 3) {
				                                                                    
				                                                                 
				std::vector<UCarMeshComponent_TA*> carMeshes = GetLocalCarMeshes();
				for (UCarMeshComponent_TA* carMesh : carMeshes) {
					if (!carMesh || carMesh->WheelControls.size() == 0) continue;
					for (int i = 0; i < carMesh->WheelControls.size(); ++i) {
						USkelControlSingleBone* steer = carMesh->WheelControls[i].SteerControl;
						if (steer) { steer->BoneRotation.Roll = 0; steer->BoneTranslation = FVector{0.f,0.f,0.f}; }
						USkelControlSingleBone* trans = carMesh->WheelControls[i].TranslationControl;
						if (trans) { trans->BoneRotation.Roll = 0; trans->BoneTranslation = FVector{0.f,0.f,0.f}; }
					}
				}
				Events.wheelOffsetActive = false;
				Events.wheelOffsetState = 0;
				Console.Write("[WHEEL OFFSET] Reset wheel offsets");
			}

			                                                                      
			                                                                  
			                                                               
			if (Events.wheelOffsetActive) {
				WheelSyncParams lw;
				lw.offY[0] = Events.wheelOffsetY[0]; lw.offY[1] = Events.wheelOffsetY[1];
				lw.offZ[0] = Events.wheelOffsetZ[0]; lw.offZ[1] = Events.wheelOffsetZ[1];
				lw.roll[0] = Events.wheelRoll[0];    lw.roll[1] = Events.wheelRoll[1];
				for (UCarMeshComponent_TA* carMesh : GetLocalCarMeshes())
					ApplyWheelParamsToMesh(carMesh, lw);
			}

			                                                                    
			                                                                   
			                                                                    
			                                                                     
			                                                                      
			{
				AGameEvent_Soccar_TA* wge = GameEventHookModule::CurrentGameEvent;
				if (SafeProbePointer(wge)) {
					APawn* localPawn = SEH_GetPawn(Instances.IAPlayerController());
					TArray<ACar_TA*> cars = wge->Cars;
					for (int ci = 0; ci < cars.size(); ++ci) {
						ACar_TA* car = cars[ci];
						if (!SafeProbePointer(car) || car == localPawn)
							continue;
						APRI_TA* rpri = SEH_GetCarPRI(car);
						if (!SafeIsObjectOfClass(rpri, APRI_TA::StaticClass()))
							continue;
						WheelSyncParams rw;
						if (!DecodeWheelPayload(rpri->Title.ToString(), rw))
							continue;
						if (UCarMeshComponent_TA* rmesh = SEH_GetCarMesh(car); SafeProbePointer(rmesh))
							ApplyWheelParamsToMesh(rmesh, rw);
					}
				}
			}
		}
		catch (...) {

			Console.Write("[WHEEL SIZE] Error in wheel size modification - disabled for safety");
			Events.wheelSizeState = 0;
		}
	}

	void PlayerControllerTick(PreEvent& event)
	{
		if (event.Caller())
		{
			APlayerController* pc = event.GetCaller<APlayerController>();
			Instances.SetPlayerController(pc);

			if (Events.enablePingSpoof)
			{
				if (GameEventHookModule::IsInGame)
				{
					ApplyPingSpoof();
				}
				else
				{
					ResetPing();
				}
			}
			else
			{
				ResetPing();
			}
			UpdateRealPing();
			
			if (Events.CanUseLocalServerFeatures() && pc && pc->WorldInfo) {
				if (Events.timeDilation != 1.0f) {
					pc->WorldInfo->TimeDilation = Events.timeDilation;
				}
				if (Events.worldGravityZ != -650.0f) {
					pc->WorldInfo->WorldGravityZ = Events.worldGravityZ;
				}
			}

			                                                                               
			{
				AGameEvent_Soccar_TA* wge = GameEventHookModule::CurrentGameEvent;
				if (SafeProbePointer(wge)) {
					TArray<ACar_TA*> cars = wge->Cars;
					for (int ci = 0; ci < cars.size(); ++ci) {
						ACar_TA* car = cars[ci];
						if (!SafeProbePointer(car))
							continue;
						APRI_TA* rpri = SEH_GetCarPRI(car);
						if (!SafeIsObjectOfClass(rpri, APRI_TA::StaticClass()))
							continue;
						
						                                            
						std::string title = rpri->Title.ToString();
						float scale = 1.0f;
						
						                                                                   
						size_t scalePos = title.find("KINGMOD_SCALE:");
						if (scalePos != std::string::npos) {
							try {
								size_t scaleEnd = title.find(";", scalePos);
								if (scaleEnd == std::string::npos) scaleEnd = title.length();
								std::string scaleStr = title.substr(scalePos + 14, scaleEnd - scalePos - 14);
								scale = std::stof(scaleStr);
							} catch (...) {
								scale = 1.0f;
							}
						}
						
						                                 
						if (scale != 1.0f) {
							car->DrawScale = scale;
						}
					}
				}
			}

			                                                 
			if (Events.needtoclearfriends) {
				Events.needtoclearfriends = false;
				try {
					UGFxData_Friends_TA* friends = Instances.GetInstanceOf<UGFxData_Friends_TA>();
					if (friends) {
						for (auto pending : friends->Pending) {
							friends->DeclineEpicFriendInvite(pending.PersonaId);
						}
						Console.Write("[Social] Declined all pending friend invites");
					}
				} catch (...) {
				}
			}

			                                  
		}
	}
}

bool EventsComponent::CanUseLocalServerFeatures() const
{
	try
	{
		APlayerController* pc = Instances.IAPlayerController();
		if (!SafeProbePointer(pc) || !SafeProbePointer(pc->WorldInfo))
			return false;
		const ENetMode mode = pc->WorldInfo->NetMode;
		return mode == ENetMode::NM_Standalone || mode == ENetMode::NM_ListenServer;
	}
	catch (...)
	{
		return false;
	}
}

namespace CustomTitleWheel {

	static std::deque<std::wstring> g_customTitleStrings;
	static int g_customTitleSlot = -1;

	void SpawnCustomTitle(const char* Text) {
		auto* playerTitles = Instances.GetInstanceOf<UGFxData_PlayerTitles_TA>();
		auto* titleConfig = Instances.GetInstanceOf<UTitleConfig_X>();

		if (!titleConfig || !playerTitles) {
			return;
		}

		std::string textStr(Text ? Text : "");
		if (textStr.empty()) {
			Console.Warning("[CustomTitle] Ignored empty title text");
			return;
		}

		int titleCount = titleConfig->Titles.size();
		if (titleCount <= 0) {
			Console.Error("[CustomTitle] Title config has no entries to use");
			return;
		}

		if (g_customTitleSlot < 0) {
			g_customTitleSlot = (titleCount > 1) ? 1 : 0;
		} else {
			g_customTitleSlot++;
			if (g_customTitleSlot >= titleCount) {
				g_customTitleSlot = (titleCount > 1) ? 1 : 0;
			}
		}
		int slot = g_customTitleSlot;

		FName slotId = titleConfig->Titles[slot].Id;
		if (!slotId.IsValid()) {
			Console.Error("[CustomTitle] Selected title slot has no valid Id");
			return;
		}
		std::string slotIdStr = slotId.ToString();
		std::wstring slotIdName(slotIdStr.begin(), slotIdStr.end());

		g_customTitleStrings.emplace_back(textStr.begin(), textStr.end());
		const std::wstring& stored = g_customTitleStrings.back();

		titleConfig->Titles[slot].Text = FString(stored.c_str());
		titleConfig->Titles[slot].Color = UObject::IntToColor(Events.titlecolor);
		titleConfig->Titles[slot].GlowColor = UObject::IntToColor(Events.titleglowcolor);

		playerTitles->UpdatePlayerTitles();

		FOnlineProductData productData = { 3036, Items.GeneratePIID(3036), 0, {}, 0, Items.GetTimestampLong() };
		productData.Attributes.push_back({ FName(L"TitleId"), FString(slotIdName.c_str()) });

		if (Items.SpawnProductData(productData, "", true)) {
			Console.Write(std::format("Spawned custom title '{}' into slot {} (Id: {})",
				textStr, slot, slotId.ToString()));
		}
		else {
			Console.Error("Failed to spawn custom title product");
			g_customTitleStrings.pop_back();
		}
	}

    bool Enabled() {
        return Events.setcustomtitle;
    }

    bool AllowWheelAdd() {
        return true;
    }
}

namespace Hooks {
	void GameViewPortKeyPress(const PostEvent& event)
	{
		                                                                       
		                                                                           
		                                                                        
		                                                                           
		                                                                          
		                                             
		(void)event;
	}

	void GFxDataMainMenuAdded(PreEvent& event)
	{
		GameState.MainMenuAdded();

	}


}

void ApplyPingSpoof()
{
    if (!Events.enablePingSpoof) return;

    APlayerController* pc = Instances.IAPlayerController();
    if (!pc) return;

    APRI_TA* PRI = (APRI_TA*)pc->PlayerReplicationInfo;
    if (!PRI) return;

    if (!Events.pingSpoofApplied) {
        Events.realPingByte = PRI->Ping;
        Events.realExactPingValue = PRI->ExactPing;
        Events.realPing = DecodePingMillisecondsFromByte(PRI->Ping);
    }

    const int pingToSet = clampi(Events.customPingValue, 0, 1000);
    const uint8_t bytePing = EncodePingByteFromMilliseconds(pingToSet);
    const float exactPingSeconds = StableExactPingSecondsForByte(bytePing);
    PRI->Ping = bytePing;
    PRI->ExactPing = exactPingSeconds;
    Events.pingSpoofApplied = true;
}

void ResetPing()
{
    if (!Events.pingSpoofApplied) return;

    APlayerController* pc = Instances.IAPlayerController();
    if (!pc) return;

    APRI_TA* PRI = (APRI_TA*)pc->PlayerReplicationInfo;
    if (!PRI) return;

    PRI->Ping = Events.realPingByte;
    PRI->ExactPing = Events.realExactPingValue;

    Events.realPing = 0;
    Events.realPingByte = 0;
    Events.realExactPingValue = 0.0f;
    Events.pingSpoofApplied = false;
}

void UpdateRealPing()
{
    if (Events.enablePingSpoof) return;
    if (Events.pingSpoofApplied) return;

    APlayerController* pc = Instances.IAPlayerController();
    if (!pc) return;

    APRI_TA* PRI = (APRI_TA*)pc->PlayerReplicationInfo;
    if (!PRI) return;

    Events.realPingByte = PRI->Ping;
    Events.realExactPingValue = PRI->ExactPing;
    Events.realPing = DecodePingMillisecondsFromByte(PRI->Ping);
}

EventsComponent::EventsComponent() : Component("Events", "Manages function hooks and process event.") { OnCreate(); }

EventsComponent::~EventsComponent() { OnDestroy(); }

void EventsComponent::OnCreate()
{
	Detoured = false;
	ProcessEvent = nullptr;


	saveData = nullptr;

	RefreshCameraPresets();
}

void EventsComponent::OnDestroy()
{
	DetachDetour();
}

bool EventsComponent::IsDetoured()
{
	return (Detoured && ProcessEvent);
}

bool EventsComponent::AttachDetour(const ProcessEventType& detourFunction)
{
	if (IsDetoured())
		return true;

	if (!detourFunction)
	{
		Console.Error("[Events Component] ProcessEvent target was null; hook was not installed.");
		return false;
	}

	ProcessEvent = detourFunction;
	LONG result = DetourTransactionBegin();
	if (result == NO_ERROR)
		result = DetourUpdateThread(GetCurrentThread());
	if (result == NO_ERROR)
		result = DetourAttach(&reinterpret_cast<PVOID&>(ProcessEvent), reinterpret_cast<PVOID>(ProcessEventDetour));
	if (result == NO_ERROR)
		result = DetourTransactionCommit();
	else
		DetourTransactionAbort();

	if (result != NO_ERROR)
	{
		ProcessEvent = nullptr;
		Console.Error("[Events Component] Failed to attach ProcessEvent detour (error " + std::to_string(result) + ").");
		return false;
	}

	Detoured = true;
	return true;
}

void EventsComponent::DetachDetour()
{
	if (IsDetoured())
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&reinterpret_cast<PVOID&>(ProcessEvent), reinterpret_cast<PVOID>(ProcessEventDetour));
		DetourTransactionCommit();
		Detoured = false;
		ProcessEvent = nullptr;
	}
}

                                                                              
                                                                                
                                                                                
                                                                                 
                                                                        
namespace
{
	std::atomic<bool>            g_FuncLogEnabled{ false };                                 
	std::atomic<bool>            g_FuncLogStream { false };                                                  
	std::atomic<bool>            g_FuncLogClear  { false };                               
	char                         g_FuncLogFilter[128] = "";                                          
	std::unordered_set<uint32_t> g_FuncLogSeen;                                
	uint32_t                     g_FuncLogLast = 0;                                              

	void KingModLogFunctionCall(class UFunction* function)
	{
		                                                                        
		                                                                      
		                                                                     
		if (g_FuncLogClear.exchange(false, std::memory_order_relaxed))
		{
			g_FuncLogSeen.clear();
			g_FuncLogLast = 0;
		}

		const uint32_t idx = static_cast<uint32_t>(function->ObjectInternalInteger);
		if (g_FuncLogStream.load(std::memory_order_relaxed))
		{
			                                                                   
			                                                                    
			if (idx == g_FuncLogLast)
				return;
			g_FuncLogLast = idx;
		}
		else
		{
			                                                                    
			                                                                  
			if (!g_FuncLogSeen.insert(idx).second)
				return;
		}

		std::string name = function->GetFullName();
		if (g_FuncLogFilter[0] != '\0')
		{
			std::string low = name;
			std::transform(low.begin(), low.end(), low.begin(),
				[](unsigned char c) { return static_cast<char>(std::tolower(c)); });
			if (low.find(g_FuncLogFilter) == std::string::npos)
				return;
		}
		KingConsole::Push("[FuncLog] " + name, KingConsole::LogLevel::Debug);
	}
}

void EventsComponent::SetFunctionLog(bool enabled, bool streamMode, const std::string& filter)
{
	                                                                              
	                                                                       
	std::string low = filter;
	std::transform(low.begin(), low.end(), low.begin(),
		[](unsigned char c) { return static_cast<char>(std::tolower(c)); });
	snprintf(g_FuncLogFilter, sizeof(g_FuncLogFilter), "%s", low.c_str());
	g_FuncLogStream.store(streamMode, std::memory_order_relaxed);
	g_FuncLogClear.store(true, std::memory_order_relaxed);                                    
	g_FuncLogEnabled.store(enabled, std::memory_order_release);
}

void EventsComponent::ClearFunctionLogSeen()
{
	g_FuncLogClear.store(true, std::memory_order_relaxed);
}

bool EventsComponent::IsFunctionLogEnabled()
{
	return g_FuncLogEnabled.load(std::memory_order_acquire);
}

bool EventsComponent::IsTrainingResetQuarantined()
{
	return g_TrainingResetGlobalDepth.load(std::memory_order_acquire) != 0 ||
		IsTrainingResetQuarantineActive();
}

bool EventsComponent::TryEnterRenderGameplayRead()
{
	                                                                         
	                                                                         
	                                                                          
	if (IsTrainingResetQuarantined())
		return false;

	g_RenderGameplayReaders.fetch_add(1, std::memory_order_acq_rel);
	if (IsTrainingResetQuarantined())
	{
		g_RenderGameplayReaders.fetch_sub(1, std::memory_order_acq_rel);
		return false;
	}
	return true;
}

void EventsComponent::LeaveRenderGameplayRead()
{
	g_RenderGameplayReaders.fetch_sub(1, std::memory_order_acq_rel);
}

void EventsComponent::ProcessEventDetour(class UObject* caller, class UFunction* function, void* params, void* result)
{
	if (!ProcessEvent || !function || !caller)
		return;

	extern std::atomic<bool> g_DllUnloading;
	if (g_DllUnloading.load())
	{
		ProcessEvent(caller, function, params, result);
		return;
	}

	                                                                            
	                                                                             
	                                                                           
	                                                                          
	                                                                             
	if (g_TrainingResetDepth != 0 ||
		g_TrainingResetGlobalDepth.load(std::memory_order_acquire) != 0 ||
		IsTrainingResetQuarantineActive())
	{
		ProcessEvent(caller, function, params, result);
		return;
	}

	uint32_t functionIndex = 0;
	if (!SafeGetObjectInternalIndex(function, &functionIndex))
	{
		ProcessEvent(caller, function, params, result);
		return;
	}

	if (IsTrainingResetFunctionIndex(functionIndex))
	{
		                                                                         
		                                                                            
		                                                                              
		++g_TrainingResetDepth;
		g_TrainingResetGlobalDepth.fetch_add(1, std::memory_order_acq_rel);

		                                                                      
		                                                                           
		                                                                          
		                                                                         
		const ULONGLONG drainDeadline = GetTickCount64() + 150;
		while (g_RenderGameplayReaders.load(std::memory_order_acquire) != 0 &&
			GetTickCount64() < drainDeadline)
		{
			Sleep(1);
		}

		                                                                    
		                                                                       
		                                                                   
		CustomTextureStudioModule::PrepareForGameplayReset();

		                                                                            
		                                                                             
		                                                                           
		                            
		KingTAS::PrepareForTrainingReset();

		ProcessEvent(caller, function, params, result);

		                                                                           
		                                                                        
		g_TrainingResetQuarantineUntil.store(GetTickCount64() + 900, std::memory_order_release);
		CustomTextureStudioModule::NotifyGameplayReset();
		g_TrainingResetGlobalDepth.fetch_sub(1, std::memory_order_acq_rel);
		--g_TrainingResetDepth;

		                                                                         
		                                                                            
		                                                                           
		                                                                             
		                                                                  
		GameEventHookModule::CurrentBall.IsValid = false;
		GameEventHookModule::players.Valid = false;
		BallPrediction::ForceRefresh();
		KingTAS::NotifyTrainingReset();
		return;
	}

	try
	{
		if (g_FuncLogEnabled.load(std::memory_order_acquire))
			KingModLogFunctionCall(function);

		         
		                                                                        
		                                                                          
		                                                                           
		                                                     
		std::vector<std::function<void(PreEvent&)>> preCallbacks;
		std::vector<std::function<void(const PostEvent&)>> postCallbacks;

		{
			auto it = PreHookedEvents.find(functionIndex);
			if (it != PreHookedEvents.end())
				preCallbacks = it->second;
		}

		{
			auto it = PostHookedEvents.find(functionIndex);
			if (it != PostHookedEvents.end())
				postCallbacks = it->second;
		}

		PreEvent event(caller, function, params);

		for (const auto& callback : preCallbacks)
		{
			if (callback)
				callback(event);
		}

		if (event.ShouldDetour())
			ProcessEvent(caller, function, params, result);

		                                                                        
		if (postCallbacks.empty())
			return;

		                                                                    
		                                                                        
		                                                                     
		PostEvent postEvent(caller, function, params, result);

		for (const auto& callback : postCallbacks)
		{
			if (callback)
				callback(postEvent);
		}
	}
	catch (...)
	{
		Console.Error("ProcessEventDetour unknown exception");
	}
}

bool EventsComponent::IsEventBlacklisted(uint32_t functionInteger)
{
	return (std::find(BlacklistedEvents.begin(), BlacklistedEvents.end(), functionInteger) != BlacklistedEvents.end());
}

void EventsComponent::BlacklistEvent(const std::string& function)
{
	UFunction* foundFunction = Instances.FindStaticFunction(function);

	if (foundFunction)
	{
		if (!IsEventBlacklisted(foundFunction->ObjectInternalInteger))
		{
			BlacklistedEvents.emplace_back(foundFunction->ObjectInternalInteger);
			std::sort(BlacklistedEvents.begin(), BlacklistedEvents.end());
		}
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to blacklist function \"" + function + "\"!");
	}
}

void EventsComponent::WhitelistEvent(const std::string& functionName)
{
	UFunction* foundFunction = Instances.FindStaticFunction(functionName);

	if (foundFunction)
	{
		std::vector<uint32_t>::iterator blackIt = std::find(BlacklistedEvents.begin(), BlacklistedEvents.end(), foundFunction->ObjectInternalInteger);

		if (blackIt != BlacklistedEvents.end())
		{
			BlacklistedEvents.erase(blackIt);
			std::sort(BlacklistedEvents.begin(), BlacklistedEvents.end());
		}
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to whitelist function \"" + functionName + "\"!");
	}
}

void EventsComponent::HookEventPre(const std::string& functionName, std::function<void(PreEvent&)> preHook)
{
	UFunction* foundFunction = Instances.FindStaticFunction(functionName);

	if (foundFunction)
	{
		HookEventPre(foundFunction->ObjectInternalInteger, preHook);
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to hook function \"" + functionName + "\"!");
	}
}

void EventsComponent::HookEventPre(uint32_t functionIndex, std::function<void(PreEvent&)> preHook)
{
	UObject* foundFunction = UObject::GObjObjects()->at(functionIndex);

	if (foundFunction && foundFunction->IsA(UFunction::StaticClass()))
	{
		if (PreHookedEvents.find(functionIndex) != PreHookedEvents.end())
		{
			PreHookedEvents[functionIndex].push_back(preHook);
		}
		else
		{
			PreHookedEvents[functionIndex] = std::vector<std::function<void(PreEvent&)>>{ preHook };
		}
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to hook function at index \"" + std::to_string(functionIndex) + "\"!");
	}
}

void EventsComponent::HookEventPost(const std::string& functionName, std::function<void(const PostEvent&)> postHook)
{
	UFunction* foundFunction = Instances.FindStaticFunction(functionName);

	if (foundFunction)
	{
		HookEventPost(foundFunction->ObjectInternalInteger, postHook);
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to hook function \"" + functionName + "\"!");
	}
}

void EventsComponent::HookEventPost(uint32_t functionIndex, std::function<void(const PostEvent&)> postHook)
{
	UObject* foundFunction = UObject::GObjObjects()->at(functionIndex);

	if (foundFunction && foundFunction->IsA(UFunction::StaticClass()))
	{
		if (PostHookedEvents.find(functionIndex) != PostHookedEvents.end())
		{
			PostHookedEvents[functionIndex].push_back(postHook);
		}
		else
		{
			PostHookedEvents[functionIndex] = std::vector<std::function<void(const PostEvent&)>>{ postHook };
		}
	}
	else
	{
		Console.Warning(GetNameFormatted() + "Warning: Failed to hook function at index \"" + std::to_string(functionIndex) + "\"!");
	}
}

void EventsComponent::Initialize()
{

	Sleep(500);


	Console.Write("[KingMod] Starting initialization with delay...");

	auto resolveResetFunction = [](const char* name, std::atomic<uint32_t>& slot)
	{
		UFunction* fn = Instances.FindStaticFunction(name);
		uint32_t index = UINT32_MAX;
		if (fn && SafeGetObjectInternalIndex(fn, &index))
			slot.store(index, std::memory_order_release);
	};

	resolveResetFunction("Function TAGame.PlayerController_TA.PlayerResetTraining", g_ResetFnPlayerController);
	resolveResetFunction("Function TAGame.GameEvent_TA.PlayerResetTraining", g_ResetFnGameEvent);
	resolveResetFunction("Function TAGame.GameEvent_TA.EventPlayerResetTraining", g_ResetFnGameEventNotify);
	resolveResetFunction("Function TAGame.FreeplayCommands_TA.ResetTraining", g_ResetFnFreeplayCommands);
	resolveResetFunction("Function TAGame.GameEvent_GameEditor_TA.ResetRound", g_ResetFnGameEditorRound);
	resolveResetFunction("Function TAGame.GameEvent_GameEditor_TA.HandlePlayerResetTraining", g_ResetFnGameEditorPlayer);
	resolveResetFunction("Function TAGame.GameEvent_TrainingEditor_TA.EventResetTrainingRound", g_ResetFnTrainingEditor);
	resolveResetFunction("Function TAGame.GFxData_Training_TA.HandleResetRound", g_ResetFnTrainingGfx);
	resolveResetFunction("Function TAGame.Mutator_Freeplay_TA.HandlePlayerResetTraining", g_ResetFnFreeplayMutator);
	resolveResetFunction("Function TAGame.GameEvent_Tutorial_TA.HandlePlayerResetTraining", g_ResetFnTutorialPlayer);
	resolveResetFunction("Function TAGame.GFxData_Training_TA.OnShotReset", g_ResetFnTrainingGfxShot);
	resolveResetFunction("Function TAGame.GameEvent_TrainingEditor_TA.ResetBalls", g_ResetFnTrainingEditorBalls);
	resolveResetFunction("Function TAGame.FXActor_TrainingEditor_TA.HandleBallReset", g_ResetFnTrainingFxBall);
	resolveResetFunction("Function TAGame.GameEvent_Training_Goalie_TA.ResetGameEvent", g_ResetFnTrainingGoalie);
	resolveResetFunction("Function TAGame.GameEvent_Soccar_TA.ResetGame", g_ResetFnSoccarResetGame);
	resolveResetFunction("Function TAGame.GameEvent_Soccar_TA.ResetBalls", g_ResetFnSoccarResetBalls);
	resolveResetFunction("Function TAGame.GameEvent_Soccar_TA.ResetBall", g_ResetFnSoccarResetBall);
	resolveResetFunction("Function TAGame.GameEvent_Tutorial_FreePlay_TA.ResetBalls", g_ResetFnTutorialFreeplayResetBalls);
	resolveResetFunction("Function TAGame.GameEvent_Tutorial_FreePlay_TA.ResetGameEvent", g_ResetFnTutorialFreeplayResetGameEvent);
	resolveResetFunction("Function TAGame.GameEvent_Tutorial_TA.ResetBalls", g_ResetFnTutorialResetBalls);
	resolveResetFunction("Function TAGame.GameEvent_Tutorial_TA.ResetGameEvent", g_ResetFnTutorialResetGameEvent);

	LoadHUDStadiumColors();

	HookEventPre("Function Engine.HUD.PostRender", Hooks::HUDPostRender);
	HookEventPost("Function Engine.HUD.PostRender", Hooks::HUDPostRenderPost);

	HookEventPre("Function Engine.Interaction.Tick", &Hooks::ExecuteFunctions);
	HookEventPre("Function Engine.Interaction.Tick", [](PreEvent& event) {
		Fun::HandleModalEvents();
		});

	HookEventPre("Function TAGame.PlayerController_TA.PlayerTick", &Hooks::PlayerControllerTick);
	HookEventPost("Function TAGame.GameViewportClient_TA.HandleKeyPress", &Hooks::GameViewPortKeyPress);
	HookEventPre("Function TAGame.MenuSequencer_TA.Tick", &Hooks::MenuSequencerTick);

	                                                                            
	                                                                             
	                                                                             
	                                                                            
	                                                                              
	                                                                            
	                                                                          
	                                                                            
	                    
	HookEventPre("Function ProjectX.OnlinePlayerFriends_X.EventEpicFriendInviteAccepted", [](PreEvent& event) {
		auto* p = event.GetParams<UOnlinePlayerFriends_X_execEventEpicFriendInviteAccepted_Params>();
		std::string who = p ? p->AcceptingPlayerName.ToString() : std::string();
		if (who.empty()) who = "A player";
		Notify::Toast("Friend Request Accepted", who + " accepted your friend request!", Notify::Style::Success, 6.0f);
		KingConsole::Push("[Social] " + who + " accepted your friend request", KingConsole::LogLevel::Success);
	});

	HookEventPre("Function ProjectX.OnlinePlayerFriends_X.EventEpicFriendInviteRemoved", [](PreEvent& event) {
		auto* p = event.GetParams<UOnlinePlayerFriends_X_execEventEpicFriendInviteRemoved_Params>();
		std::string id;
		if (p) { std::stringstream ss; ss << p->PlayerToRemove.Uid; id = ss.str(); }
		Notify::Toast("Friend Invite Declined", "Your friend request was declined or withdrawn.", Notify::Style::Warning, 6.0f);
		KingConsole::Push("[Social] Friend invite no longer pending (declined/withdrawn)" + (id.empty() ? std::string() : " uid=" + id), KingConsole::LogLevel::Warning);
	});

	HookEventPre("Function ProjectX.OnlinePlayerFriends_X.EventEpicFriendInviteFailed", [](PreEvent& event) {
		Notify::Toast("Friend Invite Failed", "Your friend request could not be sent.", Notify::Style::Error, 6.0f);
		KingConsole::Push("[Social] Friend invite failed to send", KingConsole::LogLevel::Error);
	});

	HookEventPre("Function ProjectX.OnlineGameParty_X.EventAddPartyMember", [](PreEvent& event) {
		Notify::Toast("Party", "A player joined your party.", Notify::Style::Success, 5.0f);
		KingConsole::Push("[Social] A player joined your party", KingConsole::LogLevel::Success);
	});

	HookEventPre("Function ProjectX.OnlineGameParty_X.EventRemovePartyMember", [](PreEvent& event) {
		Notify::Toast("Party", "A player left your party.", Notify::Style::Warning, 5.0f);
		KingConsole::Push("[Social] A player left your party", KingConsole::LogLevel::Warning);
	});

	HookEventPre("Function ProjectX.OnlineGameParty_X.OnPartyInviteAccepted", [](PreEvent& event) {
		Notify::Toast("Party Invite Accepted", "Someone accepted your party invite.", Notify::Style::Success, 5.0f);
		KingConsole::Push("[Social] Party invite accepted", KingConsole::LogLevel::Success);
	});


	HookEventPre("Function TAGame.PRI_TA.ReplicatedEvent", [&](PreEvent& event) {

		UOnline_X* online_x = Instances.GetInstanceOf<UOnline_X>();
		if (online_x && online_x->IsInMainMenu())
		{

			return;
		}


		ULocalPlayer* lp = Instances.IULocalPlayer();
		if (!lp || !validUObject(lp->Actor))
		{
			return;
		}

		APlayerControllerBase_TA* pc = static_cast<APlayerControllerBase_TA*>(lp->Actor);
		if (!pc || !SafeProbePointer(pc) || !pc->PlayerReplicationInfo ||
			!SafeProbePointer(pc->PlayerReplicationInfo))
		{
			return;
		}

		APRI_TA* callerPRI = event.GetCaller<APRI_TA>();
		if (callerPRI && SafeProbePointer(callerPRI))
		{
			auto steamid = callerPRI->UniqueId.Uid;

			std::stringstream streamid;
			streamid << steamid;

			APRI_TA_eventReplicatedEvent_Params* replicatedEventParms = event.GetParams<APRI_TA_eventReplicatedEvent_Params>();
			if (!replicatedEventParms) return;
			std::string Event = replicatedEventParms->VarName.ToString();


			if (Event == "Title")
			{
				if (callerPRI)
				{
					                                                          
					                                                        
					                                                    

					if (callerPRI->Title == L"None")
					{
						event.SetDetour(false);
					}
				}
			}

			if (Event == "ClientLoadouts")
			{
				if (callerPRI != pc->PlayerReplicationInfo)
					return;

				LOG("ClientLoadouts replication detected");


				ULocalPlayer* lp = Instances.IULocalPlayer();
				if (!lp || !validUObject(lp->Actor) || !lp->Actor->IsA<APlayerControllerBase_TA>())
				{
					LOG("LocalPlayer invalid");
					return;
				}

				auto* pc = static_cast<APlayerControllerBase_TA*>(lp->Actor);
				UProfile_TA* profile = pc->GetProfile();
				if (!validUObject(profile))
				{
					LOG("Profile invalid");
					return;
				}

				UProfileLoadoutSave_TA* loadoutSave = profile->LoadoutSave;
				if (!validUObject(loadoutSave))
				{
					LOG("LoadoutSave invalid");
					return;
				}

				ULoadoutSet_TA* loadoutSet = loadoutSave->EquippedLoadoutSet;
				if (!SafeProbePointer(loadoutSet))
				{
					LOG("EquippedLoadoutSet invalid");
					return;
				}

				ULoadout_TA* localLoadout0 = loadoutSet->Loadouts[0];
				ULoadout_TA* localLoadout1 = loadoutSet->Loadouts[1];
				if (!SafeProbePointer(localLoadout0) || !SafeProbePointer(localLoadout1))
				{
					LOG("Local loadout entries invalid");
					return;
				}

				TArray<int32_t>& equippedProducts0 = localLoadout0->Products;
				TArray<int32_t>& equippedProducts1 = localLoadout1->Products;

				LOG("Local Loadout0 count: " + std::to_string(equippedProducts0.size()));
				LOG("Local Loadout1 count: " + std::to_string(equippedProducts1.size()));

				APRI_TA* myPRI = reinterpret_cast<APRI_TA*>(pc->PlayerReplicationInfo);
				if (!SafeProbePointer(myPRI))
				{
					LOG("My PRI invalid");
					return;
				}

				auto& target0 = myPRI->ClientLoadouts.Loadouts[0].Products;
				auto& target1 = myPRI->ClientLoadouts.Loadouts[1].Products;


				int size0_target = (int)target0.size();
				int size0_equipped = (int)equippedProducts0.size();
				int min0 = (size0_target < size0_equipped) ? size0_target : size0_equipped;
				for (int i = 0; i < min0; i++)
					target0[i] = equippedProducts0[i];


				int size1_target = (int)target1.size();
				int size1_equipped = (int)equippedProducts1.size();
				int min1 = (size1_target < size1_equipped) ? size1_target : size1_equipped;
				for (int i = 0; i < min1; i++)
					target1[i] = equippedProducts1[i];

				LOG("Injected items into my PRI only");

			}
		}
		});

	                                                                            
	                                                                           
	                                                                  
	HookEventPost("Function TAGame.PRI_TA.ReplicatedEvent", [](const PostEvent& event) {
		try
		{
			APRI_TA* callerPRI = event.GetCaller<APRI_TA>();
			auto* params = static_cast<APRI_TA_eventReplicatedEvent_Params*>(event.Params());
			ULocalPlayer* localPlayer = Instances.IULocalPlayer();
			if (!callerPRI || !params || !localPlayer || !localPlayer->Actor ||
				localPlayer->Actor->PlayerReplicationInfo != callerPRI)
				return;

			const std::string replicatedName = params->VarName.ToString();
			if (replicatedName == "ClientLoadouts")
				Items.RequestEquippedCosmeticOverrideReapply();
			else if (replicatedName == "PlayerName" &&
				(GameEventHookModule::UsernameChangerEnabled || GameEventHookModule::UsernameInvisible))
				GameEventHookModule::ApplyUsernameChange();
		}
		catch (...) {}
		});

	                                                                            
	                                                                          
	                                                                        
	                                                                           
	HookEventPost("Function TAGame.GFxData_LocalPlayer_TA.HandleOnlineNameChanged", [](const PostEvent&) {
		if (GameEventHookModule::UsernameChangerEnabled || GameEventHookModule::UsernameInvisible)
			GameEventHookModule::ApplyUsernameChange();
		});

	                                                                         
	                                                                      
	HookEventPost("Function TAGame.GFxData_Garage_TA.HandlePreviewActorsChanged", [](const PostEvent& event) {
		Items.RefreshEquippedCosmeticLobbyPreview();
		});
	HookEventPost("Function TAGame.GFxData_Garage_TA.SetPreviewTeam", [](const PostEvent& event) {
		Items.RefreshEquippedCosmeticLobbyPreview();
		});


		HookEventPre("Function TAGame.GFxData_MainMenu_TA.MainMenuAdded", &Hooks::GFxDataMainMenuAdded);
		HookEventPost("Function TAGame.GFxData_MainMenu_TA.MainMenuAdded", [](const PostEvent& event) {
			try {
				Items.RefreshEquippedCosmeticLobbyPreview();
				std::string MOTD =
					"<font size='16' color='#FFFFFF'><b>King</b></font>"
					"<font size='16' color='#FF2B2B'><b>Mod</b></font>"
					"<font size='12' color='#CCCCCC'>  KingMod is free and open source. "
                    "If you paid anyone for this mod, you were scammed. </font>"
                    "<font size='12' color='#FF2B2B'>Signed, rlsdk</font>";

				UBlogConfig_X* blogConfig = Instances.GetInstanceOf<UBlogConfig_X>();
				if (blogConfig) {
					blogConfig->Entries.clear();
					blogConfig->MotD = Format::ToFString(MOTD);
				}
				else {
					UGFxData_Community_TA* communityData = Instances.GetInstanceOf<UGFxData_Community_TA>();
					if (communityData) {
						communityData->MotD = Format::ToFString(MOTD);
					}
				}
			}
			catch (...) {

			}
			});


	HookEventPost("Function TAGame.GameEvent_TA.EventMatchStarted", [](const PostEvent& event) {
		Items.RequestEquippedCosmeticOverrideReapply();
		Console.Write("[OnlineMatch] Match started - applying local cosmetics when the car is ready");
	});

	HookEventPost("Function TAGame.GameEvent_Soccar_TA.InitGame", [](const PostEvent& event) {
		Items.RequestEquippedCosmeticOverrideReapply();
		Console.Write("[OnlineMatch] Game initialized - local cosmetics queued");
	});


	HookEventPost("Function TAGame.GFxHUD_TA.Tick", [](const PostEvent& event) {
		AGFxHUD_TA* hud = event.GetCaller<AGFxHUD_TA>();
		if (!hud)
			return;

		if (!Events.dataStore)
			Events.dataStore = Instances.GetInstanceOf<UGFxDataStore_X>();

		FUniqueNetId NetID = Instances.GetUniqueID();
		UGFxData_PRI_TA* localplayerpri = hud->GetPRIDataFromID(NetID);

		try {
			if (Events.hudColorChangerEnabled && Events.dataStore) {
				auto now = std::chrono::steady_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - Events.lastHudColorUpdate).count();

				                                                                      
				bool shouldUpdate = Events.hudColorRainbow ||
					HasColorChanged(Events.hudColorBlue, Events.lastHudColorBlue) ||
					HasColorChanged(Events.hudColorOrange, Events.lastHudColorOrange);

				if (shouldUpdate || elapsed >= kHudColorRefreshMs) {
					                                                          
					float activeBlueColor[4];
					float activeOrangeColor[4];
					GetActiveColor(Events.hudColorBlue, Events.hudColorRainbow, activeBlueColor);
					GetActiveColor(Events.hudColorOrange, Events.hudColorRainbow, activeOrangeColor);

					if (Events.hudColorBlueTeam)
						ApplyHudTeamColor(Events.dataStore, 0, activeBlueColor);

					if (Events.hudColorOrangeTeam)
						ApplyHudTeamColor(Events.dataStore, 1, activeOrangeColor);

					Events.lastHudColorUpdate = now;
					memcpy(Events.lastHudColorBlue, activeBlueColor, sizeof(activeBlueColor));
					memcpy(Events.lastHudColorOrange, activeOrangeColor, sizeof(activeOrangeColor));
				}
			}

			if (Events.stadiumColorChangerEnabled) {
				auto now = std::chrono::steady_clock::now();
				auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - Events.lastStadiumColorUpdate).count();

				                                                                      
				bool shouldUpdate = Events.stadiumColorRainbow ||
					HasColorChanged(Events.stadiumColorBlue, Events.lastStadiumColorBlue) ||
					HasColorChanged(Events.stadiumColorOrange, Events.lastStadiumColorOrange);

				if (shouldUpdate || elapsed >= kStadiumColorRefreshMs) {
					ATeam_TA* blueTeam = nullptr;
					ATeam_TA* orangeTeam = nullptr;
					if (TryGetSoccarTeams(hud, blueTeam, orangeTeam)) {
						                                                          
						float activeBlueColor[4];
						float activeOrangeColor[4];
						GetActiveColor(Events.stadiumColorBlue, Events.stadiumColorRainbow, activeBlueColor);
						GetActiveColor(Events.stadiumColorOrange, Events.stadiumColorRainbow, activeOrangeColor);

						if (Events.stadiumColorBlueTeam)
							ApplyStadiumTeamColor(blueTeam, 0, activeBlueColor);

						if (Events.stadiumColorOrangeTeam)
							ApplyStadiumTeamColor(orangeTeam, 1, activeOrangeColor);

						Events.lastStadiumColorUpdate = now;
						memcpy(Events.lastStadiumColorBlue, activeBlueColor, sizeof(activeBlueColor));
						memcpy(Events.lastStadiumColorOrange, activeOrangeColor, sizeof(activeOrangeColor));
					}
				}
			}
		} catch (...) {}

		if (Events.setcustomtitle && !Events.titletext.empty() && Events.dataStore && localplayerpri) {
			ApplyCustomTitleRow(Events.dataStore, localplayerpri, Events.titletext, Events.titlecolor, Events.titleglowcolor);
			std::wstring wideTitle(Events.titletext.begin(), Events.titletext.end());
			FString fstitletext = FString(wideTitle.c_str());
			FName playerTitlesTable = FName(L"PlayerTitlesPlayerTitles");
			FASValue count = Events.dataStore->GetValue(FName(L"PlayerTitles"), NULL, FName(L"SelectedTitle"));
			Events.dataStore->SetStringValue(playerTitlesTable, count.I, L"Text", fstitletext);

			FASValue titleColor = Events.dataStore->GetValue(playerTitlesTable, count.I, L"Color");
			titleColor.Type = EASType::AS_UInt;
			titleColor.I = Events.titlecolor;
			Events.dataStore->SetASValue(playerTitlesTable, count.I, L"Color", titleColor);

			FASValue glowColor = Events.dataStore->GetValue(playerTitlesTable, count.I, L"GlowColor");
			glowColor.Type = EASType::AS_UInt;
			glowColor.I = Events.titleglowcolor;
			Events.dataStore->SetASValue(playerTitlesTable, count.I, L"GlowColor", glowColor);
		}

		                                                                
		                                                                 
		                   
	});

	Console.Write("[OnlineMatch] ALL online match integration functions REMOVED for stability");
	Console.Write("[OnlineMatch] PRI ReplicatedEvent hook enabled - TITLES ONLY");
	Console.Write("[OnlineMatch] Only title visibility system active");

	Console.Write(GetNameFormatted() + std::to_string(PreHookedEvents.size()) + " Pre-Hook(s) Initialized!");
	Console.Write(GetNameFormatted() + std::to_string(PostHookedEvents.size()) + " Post-Hook(s) Initialized!");
	Console.Write(GetNameFormatted() + std::to_string(BlacklistedEvents.size()) + " Backlisted Event(s) Initialized!");
}


void EventsComponent::OpenTexturesFolder()
{
	std::string dirPath = "KingMod\\Textures";
	if (!std::filesystem::exists(dirPath)) {
		std::filesystem::create_directories(dirPath);
	}


	ShellExecuteA(NULL, "open", dirPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
}

void EventsComponent::ReloadMainMenu()
{
	UOnlineGameDedicatedServer_TA* srver = Instances.GetInstanceOf<UOnlineGameDedicatedServer_TA>();
	if (srver) {
		srver->GoToMap(L"Menu_Main_P");
		Console.Write("[KingMod] Reloaded Main Menu");
	} else {
		Console.Error("[KingMod] Failed to find dedicated server instance to reload map");
	}
}

void EventsComponent::ApplyRocketPassSettings(int tier, float xpMultiplier, bool premium)
{
	try
	{
		rocketPassTier = tier;
		rocketPassXPMultiplier = xpMultiplier;
		rocketPassPremium = premium;

		Console.Write("[RocketPass] Applying settings - Tier: " + std::to_string(tier) +
			", XP Mult: " + std::to_string(xpMultiplier) +
			", Premium: " + std::string(premium ? "true" : "false"));

		URocketPass_TA* rocketPass = Instances.GetInstanceOf<URocketPass_TA>();
		if (!rocketPass)
		{
			Console.Write("[RocketPass] ERROR: RocketPass_TA instance is null!");
			return;
		}


		FRocketPassInfo rpInfo;
		rpInfo.TierLevel = tier;
		rpInfo.XPMultiplier = xpMultiplier;
		rpInfo.bOwnsPremium = premium ? 1 : 0;


		try
		{
			rocketPass->SetRocketPassInfo(rpInfo);
			Console.Write("[RocketPass] SetRocketPassInfo called successfully");
		}
		catch (...)
		{
			Console.Write("[RocketPass] WARN: SetRocketPassInfo call failed");
		}



		try
		{
			int tempTier = (tier == 1) ? 2 : tier - 1;
			rocketPass->TierLevel = tempTier;
			rocketPass->TierLevel = tier;
			rocketPass->XPMultiplier = xpMultiplier;
			rocketPass->bOwnsPremium = premium ? 1 : 0;
		}
		catch (...) { }


		try
		{
			FUniqueNetId playerID;
			if (ULocalPlayer* lp = Instances.IULocalPlayer()) {
				playerID = lp->eventGetUniqueNetId();
			}

		}
		catch (...) { }

		Console.Write("[RocketPass] Completed attempt to apply settings.");
	}
	catch (...)
	{
		Console.Write("[RocketPass] Unknown error applying Rocket Pass settings!");
	}
}

void EventsComponent::ApplyAlphaBoostColor()
{
	try
	{
		if (!alphaBoostColorEnabled)
			return;


		auto productDB = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (!productDB) return;

		auto boostProd = productDB->GetProduct(32);
		if (!boostProd) return;

		auto boostAsset = boostProd->LoadAsset();
		if (!boostAsset) return;

		auto boostAssetBoost = (UProductAsset_Boost_TA*)boostAsset;
		if (!boostAssetBoost || !boostAssetBoost->FXActor) return;

		auto fxb = (AFXActor_Boost_TA*)boostAssetBoost->FXActor;

		float activeColor[4];
		GetActiveColor(alphaBoostColor, alphaBoostColorRainbow, activeColor);
		activeColor[3] = ClampColorChannel(alphaBoostColor[3]);
		const FLinearColor color = MakeUnrealLinearColor(activeColor);


		auto boostLensFlare = FName(L"BoostLensFlare");
		auto lensFlare = (ULensFlareComponent*)fxb->GetComponentByName(ULensFlareComponent::StaticClass(), boostLensFlare);
		if (lensFlare) {
			lensFlare->SourceColor.R = color.R;
			lensFlare->SourceColor.G = color.G;
			lensFlare->SourceColor.B = color.B;
		}


		fxb->CarBoostGlowColor.R = color.R;
		fxb->CarBoostGlowColor.G = color.G;
		fxb->CarBoostGlowColor.B = color.B;


		FName drivingParticle = FName(L"DrivingParticle");
		FName boostParticle = FName(L"BoostParticle");
		auto drive_psc = (UParticleSystemComponent*)fxb->GetComponentByName(UParticleSystemComponent::StaticClass(), drivingParticle);
		auto boost_psc = (UParticleSystemComponent*)fxb->GetComponentByName(UParticleSystemComponent::StaticClass(), boostParticle);


		if (boost_psc && boost_psc->Template) {
			for (auto em : boost_psc->Template->Emitters) {
				if (!em) continue;
				for (auto lodlevel : em->LODLevels) {
					if (!lodlevel) continue;
					for (auto mod : lodlevel->Modules) {
						if (!mod) continue;
						if (mod->IsA<UParticleModuleColor>()) {
							UParticleModuleColor* umc = (UParticleModuleColor*)mod;
							if (umc->StartColor.Distribution && umc->StartColor.Distribution->IsA<UDistributionVectorParticleParameter>()) {
								UDistributionVectorParticleParameter* udvpp = (UDistributionVectorParticleParameter*)umc->StartColor.Distribution;
								udvpp->Constant.X = color.R;
								udvpp->Constant.Y = color.G;
								udvpp->Constant.Z = color.B;
							}
						}
					}
				}
			}
		}


		if (drive_psc && drive_psc->Template) {
			for (auto em : drive_psc->Template->Emitters) {
				if (!em) continue;
				for (auto lodlevel : em->LODLevels) {
					if (!lodlevel) continue;
					for (auto mod : lodlevel->Modules) {
						if (!mod) continue;
						if (mod->IsA<UParticleModuleColor>()) {
							UParticleModuleColor* umc = (UParticleModuleColor*)mod;
							if (!umc->StartColor.Distribution) continue;
							if (umc->StartColor.Distribution->IsA<UDistributionVectorParticleParameter>()) {
								UDistributionVectorParticleParameter* udvpp = (UDistributionVectorParticleParameter*)umc->StartColor.Distribution;
								udvpp->Constant.X = color.R;
								udvpp->Constant.Y = color.G;
								udvpp->Constant.Z = color.B;
							}
						}
					}
				}
			}
		}

		
	}
	catch (...)
	{
		
	}
}

void EventsComponent::ApplyWheelColor()
{
	try
	{
		if (!wheelColorEnabled)
			return;

		const auto now = std::chrono::steady_clock::now();
		static auto lastWheelCacheBuild = now - std::chrono::milliseconds(10000);

		const int cacheRefreshMs = wheelColorRainbow ? 2000 : 5000;
		const auto cacheAgeMs = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastWheelCacheBuild).count();
		const bool shouldRebuildCache = Hooks::cachedWheelMICs.empty() || cacheAgeMs >= cacheRefreshMs;

		if (shouldRebuildCache)
		{
			Hooks::cachedWheelMICs.clear();
			std::unordered_set<UMaterialInstanceConstant*> uniqueWheelMICs;

			auto addWheelMIC = [&](UMaterialInstanceConstant* mic)
			{
				if (!mic)
					return;

				if (uniqueWheelMICs.insert(mic).second)
				{
					Hooks::cachedWheelMICs.push_back(mic);
				}
			};

			auto collectWheelMaterials = [&](const std::string& search, bool filterByName)
			{
				auto found = Instances.FindAllObjects<UMaterialInstanceConstant>(search);
				for (auto* mic : found)
				{
					if (!mic)
						continue;

					if (!filterByName || IsWheelMaterialName(mic->GetName()))
					{
						addWheelMIC(mic);
					}
				}
			};

			auto collectWheelAssetPackage = [&](UProductAsset_Wheel_TA* wheelAsset)
			{
				if (!wheelAsset)
					return;

				auto wheelPackage = wheelAsset->GetPackageObj();
				if (!wheelPackage)
					return;

				collectWheelMaterials(wheelPackage->GetName() + ".", true);
			};

			for (auto* wheelAsset : Instances.GetAllInstancesOf<UProductAsset_Wheel_TA>())
			{
				collectWheelAssetPackage(wheelAsset);
			}

			if (auto carPreviewActor = Instances.FindObject<ACarPreviewActor_TA>("_p.TheWorld.PersistentLevel.CarPreviewActor_TA"))
			{
				auto* cmc = carPreviewActor->CarMesh;
				if (cmc && cmc->WheelAsset)
				{
					collectWheelAssetPackage(cmc->WheelAsset);
				}
			}

			if (Hooks::cachedWheelMICs.empty())
			{
				for (const std::string& keyword : { "Wheel", "wheel", "WHEEL", "Rim", "rim", "RIM", "Tire", "tire", "TIRE" })
				{
					collectWheelMaterials(keyword, true);
				}
			}

			if (Hooks::cachedWheelMICs.empty())
			{
				Console.Write("[WheelColor] No wheel MICs found to recolor");
				return;
			}

			lastWheelCacheBuild = now;
		}

		float activeColor[4];
		GetActiveColor(wheelColor, wheelColorRainbow, activeColor);
		const FLinearColor wheelColorLinear = MakeUnrealLinearColor(activeColor);

		size_t paintedCount = 0;
		for (auto* mic : Hooks::cachedWheelMICs)
		{
			if (!mic)
				continue;

			if (ContainsInsensitive(mic->GetName(), "_painted"))
			{
				paintedCount++;
			}

			SetMaterialColorParameters(mic, wheelColorLinear, {
				L"AccentColor",
				L"CustomColor",
				L"PaintColor",
				L"TeamColor",
				L"PrimaryColor",
				L"SecondaryColor",
				L"TrimColor",
				L"Color"
			});
		}

	
	}
	catch (...)
	{
		Console.Write("[WheelColor] Error applying wheel color");
	}
}

                                                               
                                                               
                                                                              
                                                               

static fs::path WheelConfigDir()
{
	char pathBuffer[MAX_PATH];
	GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
	fs::path exePath(pathBuffer);
	return exePath.parent_path() / "KingMod" / "WheelConfigs";
}

                                                                              
static std::string SanitizeConfigName(const std::string& name)
{
	std::string out;
	for (char c : name)
	{
		if (std::isalnum(static_cast<unsigned char>(c)) || c == '_' || c == '-' || c == ' ')
			out.push_back(c);
	}
	return out;
}

bool EventsComponent::SaveWheelConfig(const std::string& name)
{
	try
	{
		std::string safe = SanitizeConfigName(name);
		if (safe.empty())
			return false;

		fs::path dir = WheelConfigDir();
		fs::create_directories(dir);
		fs::path file = dir / (safe + ".json");

		nlohmann::json j;
		j["offset_y_front"] = wheelOffsetY[0];
		j["offset_y_rear"]  = wheelOffsetY[1];
		j["offset_z_front"] = wheelOffsetZ[0];
		j["offset_z_rear"]  = wheelOffsetZ[1];
		j["roll_front"]     = wheelRoll[0];
		j["roll_rear"]      = wheelRoll[1];

		std::ofstream out(file);
		if (!out.is_open())
			return false;
		out << j.dump(4);
		out.close();
		Console.Write("[WheelConfig] Saved '" + safe + "'");
		return true;
	}
	catch (...)
	{
		Console.Warning("[WheelConfig] Failed to save config");
		return false;
	}
}

bool EventsComponent::LoadWheelConfig(const std::string& name)
{
	try
	{
		std::string safe = SanitizeConfigName(name);
		if (safe.empty())
			return false;

		fs::path file = WheelConfigDir() / (safe + ".json");
		if (!fs::exists(file))
			return false;

		std::ifstream in(file);
		if (!in.is_open())
			return false;
		nlohmann::json j;
		in >> j;
		in.close();

		wheelOffsetY[0] = j.value("offset_y_front", wheelOffsetY[0]);
		wheelOffsetY[1] = j.value("offset_y_rear",  wheelOffsetY[1]);
		wheelOffsetZ[0] = j.value("offset_z_front", wheelOffsetZ[0]);
		wheelOffsetZ[1] = j.value("offset_z_rear",  wheelOffsetZ[1]);
		wheelRoll[0]    = j.value("roll_front",     wheelRoll[0]);
		wheelRoll[1]    = j.value("roll_rear",      wheelRoll[1]);
		Console.Write("[WheelConfig] Loaded '" + safe + "'");
		return true;
	}
	catch (...)
	{
		Console.Warning("[WheelConfig] Failed to load config");
		return false;
	}
}

std::vector<std::string> EventsComponent::ListWheelConfigs()
{
	std::vector<std::string> names;
	try
	{
		fs::path dir = WheelConfigDir();
		if (!fs::exists(dir))
			return names;
		for (const auto& entry : fs::directory_iterator(dir))
		{
			if (entry.is_regular_file() && entry.path().extension() == ".json")
				names.push_back(entry.path().stem().string());
		}
	}
	catch (...) {}
	return names;
}

void EventsComponent::SaveHUDStadiumColors()
{
	try
	{
		char pathBuffer[MAX_PATH];
		GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
		fs::path exePath(pathBuffer);
		fs::path configPath = exePath.parent_path() / "KingMod" / "stadium_colors.json";

		fs::create_directories(configPath.parent_path());

		nlohmann::json j;

		j["hud"]["enabled"] = hudColorChangerEnabled;
		j["hud"]["rainbow"] = hudColorRainbow;
		j["hud"]["blueTeam"] = hudColorBlueTeam;
		j["hud"]["orangeTeam"] = hudColorOrangeTeam;
		j["hud"]["blueColor"] = {hudColorBlue[0], hudColorBlue[1], hudColorBlue[2], hudColorBlue[3]};
		j["hud"]["orangeColor"] = {hudColorOrange[0], hudColorOrange[1], hudColorOrange[2], hudColorOrange[3]};

		j["stadium"]["enabled"] = stadiumColorChangerEnabled;
		j["stadium"]["rainbow"] = stadiumColorRainbow;
		j["stadium"]["blueTeam"] = stadiumColorBlueTeam;
		j["stadium"]["orangeTeam"] = stadiumColorOrangeTeam;
		j["stadium"]["blueColor"] = {stadiumColorBlue[0], stadiumColorBlue[1], stadiumColorBlue[2], stadiumColorBlue[3]};
		j["stadium"]["orangeColor"] = {stadiumColorOrange[0], stadiumColorOrange[1], stadiumColorOrange[2], stadiumColorOrange[3]};

		std::ofstream file(configPath);
		if (file.is_open())
		{
			file << j.dump(4);
			file.close();
		}
	}
	catch (const std::exception& e)
	{
		Console.Warning("[SaveStadiumColors] Error: " + std::string(e.what()));
	}
	catch (...)
	{
		Console.Warning("[SaveStadiumColors] Unknown error");
	}
}

void EventsComponent::LoadHUDStadiumColors()
{
	try
	{
		char pathBuffer[MAX_PATH];
		GetModuleFileNameA(NULL, pathBuffer, MAX_PATH);
		fs::path exePath(pathBuffer);
		fs::path configPath = exePath.parent_path() / "KingMod" / "stadium_colors.json";

		if (!fs::exists(configPath))
			return;

		std::ifstream file(configPath);
		if (!file.is_open())
			return;

		nlohmann::json j;
		try
		{
			file >> j;
		}
		catch (const nlohmann::json::exception&)
		{
			return;
		}

		if (j.contains("hud"))
		{
			auto& hud = j["hud"];
			if (hud.contains("enabled")) hudColorChangerEnabled = hud["enabled"].get<bool>();
			if (hud.contains("rainbow")) hudColorRainbow = hud["rainbow"].get<bool>();
			if (hud.contains("blueTeam")) hudColorBlueTeam = hud["blueTeam"].get<bool>();
			if (hud.contains("orangeTeam")) hudColorOrangeTeam = hud["orangeTeam"].get<bool>();
			if (hud.contains("blueColor") && hud["blueColor"].is_array() && hud["blueColor"].size() >= 4)
			{
				hudColorBlue[0] = hud["blueColor"][0].get<float>();
				hudColorBlue[1] = hud["blueColor"][1].get<float>();
				hudColorBlue[2] = hud["blueColor"][2].get<float>();
				hudColorBlue[3] = hud["blueColor"][3].get<float>();
			}
			if (hud.contains("orangeColor") && hud["orangeColor"].is_array() && hud["orangeColor"].size() >= 4)
			{
				hudColorOrange[0] = hud["orangeColor"][0].get<float>();
				hudColorOrange[1] = hud["orangeColor"][1].get<float>();
				hudColorOrange[2] = hud["orangeColor"][2].get<float>();
				hudColorOrange[3] = hud["orangeColor"][3].get<float>();
			}
		}

		if (j.contains("stadium"))
		{
			auto& stadium = j["stadium"];
			if (stadium.contains("enabled")) stadiumColorChangerEnabled = stadium["enabled"].get<bool>();
			if (stadium.contains("rainbow")) stadiumColorRainbow = stadium["rainbow"].get<bool>();
			if (stadium.contains("blueTeam")) stadiumColorBlueTeam = stadium["blueTeam"].get<bool>();
			if (stadium.contains("orangeTeam")) stadiumColorOrangeTeam = stadium["orangeTeam"].get<bool>();
			if (stadium.contains("blueColor") && stadium["blueColor"].is_array() && stadium["blueColor"].size() >= 4)
			{
				stadiumColorBlue[0] = stadium["blueColor"][0].get<float>();
				stadiumColorBlue[1] = stadium["blueColor"][1].get<float>();
				stadiumColorBlue[2] = stadium["blueColor"][2].get<float>();
				stadiumColorBlue[3] = stadium["blueColor"][3].get<float>();
			}
			if (stadium.contains("orangeColor") && stadium["orangeColor"].is_array() && stadium["orangeColor"].size() >= 4)
			{
				stadiumColorOrange[0] = stadium["orangeColor"][0].get<float>();
				stadiumColorOrange[1] = stadium["orangeColor"][1].get<float>();
				stadiumColorOrange[2] = stadium["orangeColor"][2].get<float>();
				stadiumColorOrange[3] = stadium["orangeColor"][3].get<float>();
			}
		}
	}
	catch (const std::exception& e)
	{
		Console.Warning("[LoadStadiumColors] Error: " + std::string(e.what()));
	}
	catch (...)
	{
		Console.Warning("[LoadStadiumColors] Unknown error");
	}
}

std::string GetCameraPresetsDirectory()
{
    char exePath[MAX_PATH] = {};
    std::string presetsDir;
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
        presetsDir = (fs::path(exePath).parent_path() / "KingMod" / "camera_presets").string();
    else
        presetsDir = (fs::current_path() / "KingMod" / "camera_presets").string();
    std::filesystem::create_directories(presetsDir);
    return presetsDir;
}

std::string GetCameraPresetsFilePath()
{
    return GetCameraPresetsDirectory() + "\\presets.json";
}

void EventsComponent::SaveCameraPreset(const std::string& name)
{
    if (name.empty()) return;

    std::string filePath = GetCameraPresetsFilePath();
    nlohmann::json j;

    std::ifstream inFile(filePath);
    if (inFile.is_open())
    {
        try { inFile >> j; } catch (...) {}
        inFile.close();
    }

    if (!j.is_object()) j = nlohmann::json::object();
    if (!j.contains("presets") || !j["presets"].is_object()) j["presets"] = nlohmann::json::object();

    nlohmann::json preset;
    preset["distance"] = cameraDistance;
    preset["height"] = cameraHeight;
    preset["angle"] = cameraAngle;
    preset["stiffness"] = cameraStiffness;
    preset["swivel_speed"] = cameraSwivelSpeed;
    preset["transition_speed"] = cameraTransitionSpeed;

    j["presets"][name] = preset;

    std::ofstream outFile(filePath);
    if (outFile.is_open())
    {
        outFile << j.dump(4);
        outFile.close();
    }

    RefreshCameraPresets();
}

void EventsComponent::LoadCameraPreset(const std::string& name)
{
    if (name.empty()) return;

    std::string filePath = GetCameraPresetsFilePath();
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    nlohmann::json j;
    try { inFile >> j; } catch (...) { inFile.close(); return; }
    inFile.close();

    if (!j.contains("presets") || !j["presets"].is_object()) return;
    if (!j["presets"].contains(name)) return;

    auto& preset = j["presets"][name];
    if (preset.contains("distance")) cameraDistance = preset["distance"].get<float>();
    else if (preset.contains("fov")) cameraDistance = preset["fov"].get<float>();
    if (preset.contains("height")) cameraHeight = preset["height"].get<float>();
    if (preset.contains("angle")) cameraAngle = preset["angle"].get<float>();
    if (preset.contains("stiffness")) cameraStiffness = preset["stiffness"].get<float>();
    if (preset.contains("swivel_speed")) cameraSwivelSpeed = preset["swivel_speed"].get<float>();
    if (preset.contains("transition_speed")) cameraTransitionSpeed = preset["transition_speed"].get<float>();

    enableCameraSettings = true;

    strncpy_s(presetName, name.c_str(), sizeof(presetName) - 1);
    presetName[sizeof(presetName) - 1] = '\0';

    Main.Execute([this]() {
        try {
            std::vector<ACameraSettingsActor_TA*> actors = Instances.GetAllInstancesOf<ACameraSettingsActor_TA>();
            for (ACameraSettingsActor_TA* actor : actors)
            {
                if (!actor) continue;
                FProfileCameraSettings settings = actor->ProfileSettings;
                settings.Distance = cameraDistance;
                settings.Height = cameraHeight;
                settings.Pitch = cameraAngle;
                settings.Stiffness = cameraStiffness;
                settings.SwivelSpeed = cameraSwivelSpeed;
                settings.TransitionSpeed = cameraTransitionSpeed;
                actor->SetProfileSettings(settings);
                actor->ServerSetCameraSettings(settings);
            }
        }
        catch (...) {
            Console.Error("[CameraPresets] Failed to apply camera settings");
        }
    });
}

void EventsComponent::DeleteCameraPreset(const std::string& name)
{
    if (name.empty()) return;

    std::string filePath = GetCameraPresetsFilePath();
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    nlohmann::json j;
    try { inFile >> j; } catch (...) { inFile.close(); return; }
    inFile.close();

    if (j.contains("presets") && j["presets"].is_object() && j["presets"].contains(name))
    {
        j["presets"].erase(name);
        std::ofstream outFile(filePath);
        if (outFile.is_open())
        {
            outFile << j.dump(4);
            outFile.close();
        }
    }

    RefreshCameraPresets();
}

void EventsComponent::RefreshCameraPresets()
{
    cameraPresets.clear();

    std::string filePath = GetCameraPresetsFilePath();
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) return;

    nlohmann::json j;
    try { inFile >> j; } catch (...) { inFile.close(); return; }
    inFile.close();

    if (j.contains("presets") && j["presets"].is_object())
    {
        for (auto& [key, value] : j["presets"].items())
        {
            cameraPresets.push_back(key);
        }
    }
}

void EventsComponent::ApplyCameraSettings()
{
    if (!enableCameraSettings) return;

    float d = cameraDistance;
    float h = cameraHeight;
    float p = cameraAngle;
    float s = cameraStiffness;

    Main.Execute([d, h, p, s]() {
        try {
            std::vector<ACameraSettingsActor_TA*> actors = Instances.GetAllInstancesOf<ACameraSettingsActor_TA>();
            for (ACameraSettingsActor_TA* actor : actors)
            {
                if (!actor) continue;
                FProfileCameraSettings settings = actor->ProfileSettings;
                settings.Distance = d;
                settings.Height = h;
                settings.Pitch = p;
                settings.Stiffness = s;
                actor->SetProfileSettings(settings);
                actor->ServerSetCameraSettings(settings);
            }
        }
        catch (...) {}
    });
}

class EventsComponent Events{};
