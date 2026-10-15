#pragma once
#include "../Component.hpp"
#include <vector>
#include <unordered_map>

class UMaterialInstanceConstant;
class ACarPreviewActor_TA;
struct FVector;
class ACarPreviewActor_TA;
struct FVector;
class ACar_TA;
class UOnlineGame_X;
class UOnlinePlayer_X;
class UGFxData_LocalPlayer_TA;

class PreEvent
{
protected:
	class UObject* PE_Caller;
	class UFunction* PE_Function;
	void* PE_Params;
	bool PE_Detour;

public:
	PreEvent();
	PreEvent(class UObject* caller, class UFunction* function, void* params);
	~PreEvent();

public:
	class UObject* Caller() const;
	template <typename T> T* GetCaller() const;
	class UFunction* Function() const;
	void* Params() const;
	template <typename T> T* GetParams() const;
	bool ShouldDetour() const;
	void SetDetour(bool bDetour);

public:
	PreEvent operator=(const PreEvent& other);
};

                                                                                 
template <typename T> T* PreEvent::GetParams() const
{
	if (PE_Params)
	{
		return reinterpret_cast<T*>(PE_Params);
	}
	return nullptr;
}

class PostEvent : public PreEvent
{
private:
	void* PE_Result;

public:
	PostEvent();
	PostEvent(class UObject* caller, class UFunction* function, void* params, void* result);
	~PostEvent();

public:
	void* Result() const;
	template <typename T> T* GetResult() const;

public:
	PostEvent operator=(const PostEvent& other);
};

namespace Hooks
{
	void HUDPostRender(PreEvent& event);
	void HUDPostRenderPost(const PostEvent& event);
	void MenuSequencerTick(PreEvent& event);
	void HandleCustomFeatures();
	void RenderBallPrediction(class UCanvas* canvas);
	void GameViewPortPostRender(PreEvent& event);
	void GFxDataMainMenuAdded(PreEvent& event);
	void PlayerControllerTick(PreEvent& event);
	void GameViewPortKeyPress(const PostEvent& event);


	inline std::vector<UMaterialInstanceConstant*> cachedBodyMICs;
	inline std::vector<UMaterialInstanceConstant*> cachedBoostMICs;
	inline std::vector<UMaterialInstanceConstant*> cachedWheelMICs;
}

typedef void(*ProcessEventType)(class UObject*, class UFunction*, void*, void*);

struct FCustomTitleData {
	std::string playerid = "";
	std::string titletext = "";
	std::string titlecolor = "";
	std::string titleglow = "";
};

class EventsComponent : public Component
{
private:
	static inline bool Detoured;
	static inline ProcessEventType ProcessEvent;
	static inline std::map<uint32_t, std::vector<std::function<void(PreEvent&)>>> PreHookedEvents;
	static inline std::map<uint32_t, std::vector<std::function<void(const PostEvent&)>>> PostHookedEvents;
	static inline std::vector<uint32_t> BlacklistedEvents;

public:

	bool setblackcar = false;
	bool offblackcar = false;


	bool custompainttrim = false;
	bool custompainttrimrgb = false;
	float customtrimcolors[3] = { 1.0f, 1.0f, 1.0f };
	bool hasresetpainttrim = true;
	USaveData_TA* saveData = nullptr;


	bool setcustomtitle = false;
	std::string titletext = "";
	int titlecolor = 0xFFFFFF;
	int titleglowcolor = 0x000000;
	bool dopaidcustomtitle = false;
	std::string playerid = "";
	std::map<std::string, FCustomTitleData> hardcodedcustomtags;

	UGFxDataStore_X* dataStore = nullptr;
	UGFxData_LocalPlayer_TA* gfxlocalplayer = nullptr;
	UOnlineGame_X* onlineGame = nullptr;
	UOnlinePlayer_X* onlinePlayer = nullptr;


	int inviswheels = 0;
	int wheelSizeState = 0;
	float wheelWidth = 1.0f;
	float wheelHeight = 1.0f;

	                                                                            
	                                                                            
	                                                                         
	                                                                
	float wheelOffsetY[2] = { 0.0f, 0.0f };
	float wheelOffsetZ[2] = { 0.0f, 0.0f };
	float wheelRoll[2]    = { 0.0f, 0.0f };
	int wheelOffsetState = 0;
	bool wheelOffsetActive = false;
	                                                                        
	                                                                      
	                                               
	int wheelTarget = 0;
	                                 
	char wheelConfigName[128] = "";
	bool SaveWheelConfig(const std::string& name);
	bool LoadWheelConfig(const std::string& name);
	std::vector<std::string> ListWheelConfigs();

	                                                                        
	                                                                        
	                                                                        
	                                          
	std::string BuildCustomSyncPayload();


	bool enablePingSpoof = false;
	int realPing = 0;
	uint8_t realPingByte = 0;
	float realExactPingValue = 0.0f;
	int customPingValue = 4;
	bool pingSpoofApplied = false;


	bool premium_garage_active = false;
	UOnline_X* online_x = nullptr;
    std::unordered_map<ACarPreviewActor_TA*, FVector> PremiumGarageOriginalPositions;

public:

	bool setOnlineStatus = false;
	std::string customStatus = "KingMod The Best!";
	bool forceStatusUpdate = false;


public:
	EventsComponent();
	~EventsComponent() override;

public:
	void OnCreate() override;
	void OnDestroy() override;

public:
	static bool IsDetoured();
	                                                                      
	static bool AttachDetour(const ProcessEventType& detourFunction);
	static void DetachDetour();
	static void ProcessEventDetour(class UObject* caller, class UFunction* function, void* params, void* result);
	static bool IsEventBlacklisted(uint32_t functionIndex);

	                                                                        
	                                                                           
	                                                                  
	static void SetFunctionLog(bool enabled, bool streamMode, const std::string& filter);
	static void ClearFunctionLogSeen();
	static bool IsFunctionLogEnabled();

	                                                                              
	                                                                             
	                                                         
	static bool IsTrainingResetQuarantined();
	                                                                   
	static bool TryEnterRenderGameplayRead();
	static void LeaveRenderGameplayRead();

public:
	void BlacklistEvent(const std::string& functionName);
	void WhitelistEvent(const std::string& functionName);
	void HookEventPre(const std::string& functionName, std::function<void(PreEvent&)> preHook);
	void HookEventPre(uint32_t functionIndex, std::function<void(PreEvent&)> preHook);
	void HookEventPost(const std::string& functionName, std::function<void(const PostEvent&)> postHook);
	void HookEventPost(uint32_t functionIndex, std::function<void(const PostEvent&)> postHook);
	void Initialize();
	int GetColorID(float* color);
	bool CanUseLocalServerFeatures() const;

	bool enableFovChanger = false;
	float fov = 110.0f;


	bool enableCameraSettings = false;
	float cameraDistance = 270.0f;
	float cameraHeight = 110.0f;
	float cameraAngle = -3.0f;
	float cameraStiffness = 0.5f;
	float cameraSwivelSpeed = 2.5f;
	float cameraTransitionSpeed = 1.0f;


	char presetName[128] = "default";
	std::vector<std::string> cameraPresets;
	void SaveCameraPreset(const std::string& name);
	void LoadCameraPreset(const std::string& name);
	void DeleteCameraPreset(const std::string& name);
	void RefreshCameraPresets();
	void ApplyCameraSettings();


	int rocketPassTier = 1;
	float rocketPassXPMultiplier = 1.0f;
	bool rocketPassPremium = false;
	void ApplyRocketPassSettings(int tier, float xpMultiplier, bool premium);


	bool alphaBoostColorEnabled = false;
	bool alphaBoostColorRainbow = false;
	float alphaBoostColor[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	void ApplyAlphaBoostColor();


	bool wheelColorEnabled = false;
	bool wheelColorRainbow = false;
	float wheelColor[4] = {1.0f, 0.0f, 1.0f, 1.0f};
	void ApplyWheelColor();


	bool hudColorChangerEnabled = false;
	bool hudColorRainbow = false;
	bool hudColorBlueTeam = true;
	bool hudColorOrangeTeam = true;
	float hudColorBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	float hudColorOrange[4] = {1.0f, 0.5f, 0.0f, 1.0f};

	std::chrono::steady_clock::time_point lastHudColorUpdate;
	float lastHudColorBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	float lastHudColorOrange[4] = {1.0f, 0.5f, 0.0f, 1.0f};

	bool stadiumColorChangerEnabled = false;
	bool stadiumColorRainbow = false;
	bool stadiumColorBlueTeam = true;
	bool stadiumColorOrangeTeam = true;
	float stadiumColorBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	float stadiumColorOrange[4] = {1.0f, 0.5f, 0.0f, 1.0f};

	std::chrono::steady_clock::time_point lastStadiumColorUpdate;
	float lastStadiumColorBlue[4] = {0.0f, 0.0f, 1.0f, 1.0f};
	float lastStadiumColorOrange[4] = {1.0f, 0.5f, 0.0f, 1.0f};


	void SaveHUDStadiumColors();
	void LoadHUDStadiumColors();


	bool customavatar = false;
	std::string avatarTexturePath = "KingMod\\Textures\\Avatar.png";
	std::vector<std::string> availableTextures;
	int selectedTextureIndex = 0;
	bool refreshTextures = false;
	UTexture* customAvatarTexture = nullptr;
	UPlayerAvatar_TA* playerAvatar = nullptr;
	UVanitySetManager_TA* vanityManager = nullptr;

	void RefreshTextureList();
	void OpenTexturesFolder();
	void ReloadMainMenu();
	void ReloadCarBodyModel();

	                        
	bool enableCarPosition = false;
	float carPositionX = 0.0f;
	float carPositionY = 0.0f;
	float carPositionZ = 0.0f;
	float carRotationPitch = 0.0f;
	float carRotationYaw = 0.0f;

	bool enableWorldSettings = false;
	float timeDilation = 1.0f;
	float worldGravityZ = -650.0f;

	bool enableCarScale = false;
	float carScale = 1.0f;

	bool showMouseCrosshair = false;

	                               
	std::vector<int> spawnedItemIDs;
	void AddSpawnedItem(int productID);

 	                    
 	bool needtoclearfriends = false;
};

extern class EventsComponent Events;
