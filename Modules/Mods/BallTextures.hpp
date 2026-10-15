#pragma once
#include "../Module.hpp"
#include "../../Components/Includes.hpp"
#include <filesystem>
#include <unordered_map>
#include <vector>

namespace fs = std::filesystem;

struct BallTexData
{
	fs::path           imgPath;
	UTexture2DDynamic* texture = nullptr;
};

struct BallSkinData
{
	std::string                                  name;
	fs::path                                     jsonFile;
	std::unordered_map<std::string, BallTexData> paramTextures;                            
	bool                                         bTexturesLoaded = false;

	bool loadTextures();
	void clearLoadedTextures();
};

class BallTexturesModule : public Module
{
public:
	BallTexturesModule();
	~BallTexturesModule() override;

	void OnCreate();
	void OnDestroy();

	static void Initialize();
	static void Hook();

	        
	static void OnGameEventStart(PreEvent& event);
	static void OnGameEventDestroyed(PreEvent& event);
	static void OnBallFadeInPost(const PostEvent& event);
	static void OnReplaceBotPost(const PostEvent& event);
	static void OnTick();                                         

	                      
	static void                        ApplySelectedSkinToAllBalls();
	static void                        ApplySkinToBall(ABall_TA* ball, const BallSkinData& skin);
	static void                        ApplySkinToBallArchetype(ABall_TA* arch, const BallSkinData& skin);
	static void                        ApplySkinToBallDissolveMIC(const BallSkinData& skin);
	static UMaterialInstanceConstant*  GetBallDissolveMIC();

	                  
	static void          SearchForBallSkins();
	static BallSkinData* GetSelectedSkin();

	                        
	static bool               GetFileBytes(const fs::path& filePath, std::vector<uint8_t>& outBytes);
	static UTexture2DDynamic* ImgPathToTexture(const fs::path& imgPath, bool markInvincible = true);

	                                                                           
	                                                              
	static void RestoreDefaultTextures();

public:
	static bool                                          IsEnabled;
	static bool                                          IsInGame;
	static AGameEvent_Soccar_TA*                         CurrentGameEvent;
	static fs::path                                      BallTexturesFolder;
	static std::unordered_map<std::string, BallSkinData> SavedTextureData;
	static std::string                                   SelectedSkinName;
};

extern class BallTexturesModule BallTextures;
