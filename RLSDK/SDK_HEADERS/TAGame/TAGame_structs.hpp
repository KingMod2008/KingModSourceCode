/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: TAGame\TAGame_structs.hpp
# ========================================================================================= #
# Credits: rlsdk (KingMod)
# Links: www.github.com/KingMod2008
#############################################################################################
*/
#pragma once

#ifdef _MSC_VER
#pragma pack(push, 0x8)
#endif

/*
# ========================================================================================= #
# Structs
# ========================================================================================= #
*/

// ScriptStruct TAGame.ConsecutiveMatchTracker_TA.MatchData
// 0x004C
struct FMatchData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            ConsecutiveMatchesPlayed;                      // 0x0048 (0x0004) [0x0000000000000000]               

	bool operator==(const FMatchData& other) const { return memcmp(this, &other, sizeof(FMatchData)) == 0; }
	bool operator!=(const FMatchData& other) const { return !(*this == other); }
	bool operator<(const FMatchData& other) const { return memcmp(this, &other, sizeof(FMatchData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MutatorInfo
// 0x0028
struct FMutatorInfo
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Category;                                      // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	struct FColor                                      ColorOverride;                                 // 0x0020 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            SortPriority;                                  // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FMutatorInfo& other) const { return memcmp(this, &other, sizeof(FMutatorInfo)) == 0; }
	bool operator!=(const FMutatorInfo& other) const { return !(*this == other); }
	bool operator<(const FMutatorInfo& other) const { return memcmp(this, &other, sizeof(FMutatorInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VoiceRoomCredentials
// 0x0030
struct FVoiceRoomCredentials
{
	class FString                                      RoomId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      BaseUrl;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Token;                                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVoiceRoomCredentials& other) const { return memcmp(this, &other, sizeof(FVoiceRoomCredentials)) == 0; }
	bool operator!=(const FVoiceRoomCredentials& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomCredentials& other) const { return memcmp(this, &other, sizeof(FVoiceRoomCredentials)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerVoiceRoomCredentials
// 0x0048 (0x0030 - 0x0078)
struct FPlayerVoiceRoomCredentials : FVoiceRoomCredentials
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0030 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerVoiceRoomCredentials& other) const { return memcmp(this, &other, sizeof(FPlayerVoiceRoomCredentials)) == 0; }
	bool operator!=(const FPlayerVoiceRoomCredentials& other) const { return !(*this == other); }
	bool operator<(const FPlayerVoiceRoomCredentials& other) const { return memcmp(this, &other, sizeof(FPlayerVoiceRoomCredentials)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ActivePlayerVoice
// 0x0011
struct FActivePlayerVoice
{
	uint64_t                                           StartTimestamp;                                // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0008 (0x0008) [0x0000000000000000]               
	EActiveVoiceLocation                               Location;                                      // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FActivePlayerVoice& other) const { return memcmp(this, &other, sizeof(FActivePlayerVoice)) == 0; }
	bool operator!=(const FActivePlayerVoice& other) const { return !(*this == other); }
	bool operator<(const FActivePlayerVoice& other) const { return memcmp(this, &other, sizeof(FActivePlayerVoice)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VoiceRoomErrorMetric
// 0x0010
struct FVoiceRoomErrorMetric
{
	class FName                                        ErrorName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           TimeStamp;                                     // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FVoiceRoomErrorMetric& other) const { return memcmp(this, &other, sizeof(FVoiceRoomErrorMetric)) == 0; }
	bool operator!=(const FVoiceRoomErrorMetric& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomErrorMetric& other) const { return memcmp(this, &other, sizeof(FVoiceRoomErrorMetric)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VoiceRoomPlayerActivity
// 0x0020
struct FVoiceRoomPlayerActivity
{
	class TArray<struct FActivePlayerVoice>            ActiveVoiceSummary;                            // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FVoiceRoomErrorMetric>         Errors;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVoiceRoomPlayerActivity& other) const { return memcmp(this, &other, sizeof(FVoiceRoomPlayerActivity)) == 0; }
	bool operator!=(const FVoiceRoomPlayerActivity& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomPlayerActivity& other) const { return memcmp(this, &other, sizeof(FVoiceRoomPlayerActivity)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VoiceRoomDetails
// 0x0028
struct FVoiceRoomDetails
{
	class FString                                      RoomName;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EVoiceRoomType                                     RoomType;                                      // 0x0010 (0x0001) [0x0000000000000000]               
	uint64_t                                           CreatedTimestamp;                              // 0x0018 (0x0008) [0x0000000000000000]               
	uint64_t                                           DestroyedTimestamp;                            // 0x0020 (0x0008) [0x0000000000000000]               

	bool operator==(const FVoiceRoomDetails& other) const { return memcmp(this, &other, sizeof(FVoiceRoomDetails)) == 0; }
	bool operator!=(const FVoiceRoomDetails& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomDetails& other) const { return memcmp(this, &other, sizeof(FVoiceRoomDetails)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerMessageInfo
// 0x0020
struct FPlayerMessageInfo
{
	class FString                                      SenderId;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayName;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerMessageInfo& other) const { return memcmp(this, &other, sizeof(FPlayerMessageInfo)) == 0; }
	bool operator!=(const FPlayerMessageInfo& other) const { return !(*this == other); }
	bool operator<(const FPlayerMessageInfo& other) const { return memcmp(this, &other, sizeof(FPlayerMessageInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SavedTrainingData
// 0x0028
struct FSavedTrainingData
{
	class FString                                      TrainingType;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Difficulty;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Score;                                         // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalRounds;                                   // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FSavedTrainingData& other) const { return memcmp(this, &other, sizeof(FSavedTrainingData)) == 0; }
	bool operator!=(const FSavedTrainingData& other) const { return !(*this == other); }
	bool operator<(const FSavedTrainingData& other) const { return memcmp(this, &other, sizeof(FSavedTrainingData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VehicleInputs
// 0x0024
struct FVehicleInputs
{
	float                                              Throttle;                                      // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Steer;                                         // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Pitch;                                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Yaw;                                           // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Roll;                                          // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DodgeForward;                                  // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DodgeRight;                                    // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bHandbrake : 1;                                // 0x001C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bJump : 1;                                     // 0x001C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bActivateBoost : 1;                            // 0x001C (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bHoldingBoost : 1;                             // 0x001C (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           bJumped : 1;                                   // 0x001C (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bGrab : 1;                                     // 0x001C (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bButtonMash : 1;                               // 0x001C (0x0004) [0x0000000000000000] [0x100000040] 
	uint32_t                                           bAirRoll : 1;                                  // 0x0020 (0x0004) [0x0001000000000000] [0x100000001] 

	bool operator==(const FVehicleInputs& other) const { return memcmp(this, &other, sizeof(FVehicleInputs)) == 0; }
	bool operator!=(const FVehicleInputs& other) const { return !(*this == other); }
	bool operator<(const FVehicleInputs& other) const { return memcmp(this, &other, sizeof(FVehicleInputs)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OwnedStatTitleEntry
// 0x0020
struct FOwnedStatTitleEntry
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000000000000]               
	int32_t                                            StatId;                                        // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            StatValue;                                     // 0x0014 (0x0004) [0x0000000000000000]               
	class FName                                        TitleId;                                       // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FOwnedStatTitleEntry& other) const { return memcmp(this, &other, sizeof(FOwnedStatTitleEntry)) == 0; }
	bool operator!=(const FOwnedStatTitleEntry& other) const { return !(*this == other); }
	bool operator<(const FOwnedStatTitleEntry& other) const { return memcmp(this, &other, sizeof(FOwnedStatTitleEntry)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RandomWeight
// 0x0010
struct FRandomWeight
{
	class UObject*                                     Obj;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Weight;                                        // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              OrigWeight;                                    // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FRandomWeight& other) const { return memcmp(this, &other, sizeof(FRandomWeight)) == 0; }
	bool operator!=(const FRandomWeight& other) const { return !(*this == other); }
	bool operator<(const FRandomWeight& other) const { return memcmp(this, &other, sizeof(FRandomWeight)) < 0; }
};

// ScriptStruct TAGame._Types_TA.AssetLoadResult
// 0x0020
struct FAssetLoadResult
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        AssetName;                                     // 0x0004 (0x0008) [0x0000000000000000]               
	class UProductAsset_TA*                            Asset;                                         // 0x0010 (0x0008) [0x0000000000000000]               
	class UProductThumbnailAsset_TA*                   ThumbnailAsset;                                // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FAssetLoadResult& other) const { return memcmp(this, &other, sizeof(FAssetLoadResult)) == 0; }
	bool operator!=(const FAssetLoadResult& other) const { return !(*this == other); }
	bool operator<(const FAssetLoadResult& other) const { return memcmp(this, &other, sizeof(FAssetLoadResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductThumbnailResult
// 0x0018
struct FProductThumbnailResult
{
	class UProductAsset_TA*                            Asset;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0008 (0x0008) [0x0000000000000000]               
	class UProductThumbnail_TA*                        Thumbnail;                                     // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FProductThumbnailResult& other) const { return memcmp(this, &other, sizeof(FProductThumbnailResult)) == 0; }
	bool operator!=(const FProductThumbnailResult& other) const { return !(*this == other); }
	bool operator<(const FProductThumbnailResult& other) const { return memcmp(this, &other, sizeof(FProductThumbnailResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MapImageLoadResult
// 0x0010
struct FMapImageLoadResult
{
	class UTexture2D*                                  Image;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        MapName;                                       // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FMapImageLoadResult& other) const { return memcmp(this, &other, sizeof(FMapImageLoadResult)) == 0; }
	bool operator!=(const FMapImageLoadResult& other) const { return !(*this == other); }
	bool operator<(const FMapImageLoadResult& other) const { return memcmp(this, &other, sizeof(FMapImageLoadResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ClientLoadoutData
// 0x0010
struct FClientLoadoutData
{
	class TArray<int32_t>                              Products;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FClientLoadoutData& other) const { return memcmp(this, &other, sizeof(FClientLoadoutData)) == 0; }
	bool operator!=(const FClientLoadoutData& other) const { return !(*this == other); }
	bool operator<(const FClientLoadoutData& other) const { return memcmp(this, &other, sizeof(FClientLoadoutData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutTeamColor
// 0x0008
struct FLoadoutTeamColor
{
	uint8_t                                            Team;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            TeamColorID;                                   // 0x0001 (0x0001) [0x0000000000000000]               
	uint8_t                                            CustomColorID;                                 // 0x0002 (0x0001) [0x0000000000000000]               
	uint32_t                                           bSet : 1;                                      // 0x0004 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FLoadoutTeamColor& other) const { return memcmp(this, &other, sizeof(FLoadoutTeamColor)) == 0; }
	bool operator!=(const FLoadoutTeamColor& other) const { return !(*this == other); }
	bool operator<(const FLoadoutTeamColor& other) const { return memcmp(this, &other, sizeof(FLoadoutTeamColor)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutTeamPaint
// 0x0008 (0x0008 - 0x0010)
struct FLoadoutTeamPaint : FLoadoutTeamColor
{
	int32_t                                            TeamFinishID;                                  // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            CustomFinishID;                                // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FLoadoutTeamPaint& other) const { return memcmp(this, &other, sizeof(FLoadoutTeamPaint)) == 0; }
	bool operator!=(const FLoadoutTeamPaint& other) const { return !(*this == other); }
	bool operator<(const FLoadoutTeamPaint& other) const { return memcmp(this, &other, sizeof(FLoadoutTeamPaint)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutData
// 0x0030 (0x0010 - 0x0040)
struct FLoadoutData : FClientLoadoutData
{
	struct FLoadoutTeamPaint                           TeamPaint;                                     // 0x0010 (0x0010) [0x0000000000000000]               
	class FName                                        Title;                                         // 0x0020 (0x0008) [0x0000000000000000]               
	int32_t                                            TeamIndex;                                     // 0x0028 (0x0004) [0x0000000000000000]               
	class TArray<struct FProductInstanceID>            OnlineProducts;                                // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLoadoutData& other) const { return memcmp(this, &other, sizeof(FLoadoutData)) == 0; }
	bool operator!=(const FLoadoutData& other) const { return !(*this == other); }
	bool operator<(const FLoadoutData& other) const { return memcmp(this, &other, sizeof(FLoadoutData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ClientLoadoutOnlineProduct
// 0x0010
struct FClientLoadoutOnlineProduct
{
	class TArray<class UProductAttribute_TA*>          Attributes;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FClientLoadoutOnlineProduct& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineProduct)) == 0; }
	bool operator!=(const FClientLoadoutOnlineProduct& other) const { return !(*this == other); }
	bool operator<(const FClientLoadoutOnlineProduct& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineProduct)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ClientLoadoutOnlineData
// 0x0010
struct FClientLoadoutOnlineData
{
	class TArray<struct FClientLoadoutOnlineProduct>   Products;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FClientLoadoutOnlineData& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineData)) == 0; }
	bool operator!=(const FClientLoadoutOnlineData& other) const { return !(*this == other); }
	bool operator<(const FClientLoadoutOnlineData& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.InputRate
// 0x0008
struct FInputRate
{
	float                                              RiseRate;                                      // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FallRate;                                      // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInputRate& other) const { return memcmp(this, &other, sizeof(FInputRate)) == 0; }
	bool operator!=(const FInputRate& other) const { return !(*this == other); }
	bool operator<(const FInputRate& other) const { return memcmp(this, &other, sizeof(FInputRate)) < 0; }
};

// ScriptStruct TAGame._Types_TA.TurningCircle
// 0x0010
struct FTurningCircle
{
	struct FVector                                     Center;                                        // 0x0000 (0x000C) [0x0000000000000000]               
	float                                              Radius;                                        // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FTurningCircle& other) const { return memcmp(this, &other, sizeof(FTurningCircle)) == 0; }
	bool operator!=(const FTurningCircle& other) const { return !(*this == other); }
	bool operator<(const FTurningCircle& other) const { return memcmp(this, &other, sizeof(FTurningCircle)) < 0; }
};

// ScriptStruct TAGame._Types_TA.GFxTeamColor
// 0x0010
struct FGFxTeamColor
{
	struct FColor                                      Value;                                         // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            ColorID;                                       // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            X;                                             // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Y;                                             // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxTeamColor& other) const { return memcmp(this, &other, sizeof(FGFxTeamColor)) == 0; }
	bool operator!=(const FGFxTeamColor& other) const { return !(*this == other); }
	bool operator<(const FGFxTeamColor& other) const { return memcmp(this, &other, sizeof(FGFxTeamColor)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MapGroup
// 0x0010
struct FMapGroup
{
	class TArray<class UMapData_TA*>                   Maps;                                          // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMapGroup& other) const { return memcmp(this, &other, sizeof(FMapGroup)) == 0; }
	bool operator!=(const FMapGroup& other) const { return !(*this == other); }
	bool operator<(const FMapGroup& other) const { return memcmp(this, &other, sizeof(FMapGroup)) < 0; }
};

// ScriptStruct TAGame._Types_TA.StatValue
// 0x0014
struct FStatValue
{
	class FName                                        Id;                                            // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Values[3];                                     // 0x0008 (0x000C) [0x0000000000000000]               

	bool operator==(const FStatValue& other) const { return memcmp(this, &other, sizeof(FStatValue)) == 0; }
	bool operator!=(const FStatValue& other) const { return !(*this == other); }
	bool operator<(const FStatValue& other) const { return memcmp(this, &other, sizeof(FStatValue)) < 0; }
};

// ScriptStruct TAGame._Types_TA.VoiceRoomTokenRequest
// 0x0020
struct FVoiceRoomTokenRequest
{
	class FString                                      RoomId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  PlayerIds;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVoiceRoomTokenRequest& other) const { return memcmp(this, &other, sizeof(FVoiceRoomTokenRequest)) == 0; }
	bool operator!=(const FVoiceRoomTokenRequest& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomTokenRequest& other) const { return memcmp(this, &other, sizeof(FVoiceRoomTokenRequest)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerIdArray
// 0x0010
struct FPlayerIdArray
{
	class TArray<struct FUniqueNetId>                  Players;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerIdArray& other) const { return memcmp(this, &other, sizeof(FPlayerIdArray)) == 0; }
	bool operator!=(const FPlayerIdArray& other) const { return !(*this == other); }
	bool operator<(const FPlayerIdArray& other) const { return memcmp(this, &other, sizeof(FPlayerIdArray)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductWithSettings
// 0x0018
struct FProductWithSettings
{
	class UProductAsset_TA*                            Product;                                       // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UProductPaint_TA*                            Paint;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UDataAsset_ESportsTeam_TA*                   ESportsTeam;                                   // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FProductWithSettings& other) const { return memcmp(this, &other, sizeof(FProductWithSettings)) == 0; }
	bool operator!=(const FProductWithSettings& other) const { return !(*this == other); }
	bool operator<(const FProductWithSettings& other) const { return memcmp(this, &other, sizeof(FProductWithSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductTradeInFilter
// 0x0050
struct FProductTradeInFilter
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              SeriesIDs;                                     // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bBlueprint : 1;                                // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<EProductQuality>                      Qualities;                                     // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        TradeInQualities;                              // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FProductTradeInFilter& other) const { return memcmp(this, &other, sizeof(FProductTradeInFilter)) == 0; }
	bool operator!=(const FProductTradeInFilter& other) const { return !(*this == other); }
	bool operator<(const FProductTradeInFilter& other) const { return memcmp(this, &other, sizeof(FProductTradeInFilter)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ColorOverride
// 0x0014
struct FColorOverride
{
	uint32_t                                           bOverride : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FLinearColor                                Color;                                         // 0x0004 (0x0010) [0x0000000000000000]               

	bool operator==(const FColorOverride& other) const { return memcmp(this, &other, sizeof(FColorOverride)) == 0; }
	bool operator!=(const FColorOverride& other) const { return !(*this == other); }
	bool operator<(const FColorOverride& other) const { return memcmp(this, &other, sizeof(FColorOverride)) < 0; }
};

// ScriptStruct TAGame._Types_TA.TeamColor
// 0x0020
struct FTeamColor
{
	struct FLinearColor                                FontColor;                                     // 0x0000 (0x0010) [0x0000000000000000]               
	class TArray<struct FLinearColor>                  Colors;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTeamColor& other) const { return memcmp(this, &other, sizeof(FTeamColor)) == 0; }
	bool operator!=(const FTeamColor& other) const { return !(*this == other); }
	bool operator<(const FTeamColor& other) const { return memcmp(this, &other, sizeof(FTeamColor)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MapSkillSettings
// 0x000C
struct FMapSkillSettings
{
	class FName                                        MapName;                                       // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              MinimumSkill;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMapSkillSettings& other) const { return memcmp(this, &other, sizeof(FMapSkillSettings)) == 0; }
	bool operator!=(const FMapSkillSettings& other) const { return !(*this == other); }
	bool operator<(const FMapSkillSettings& other) const { return memcmp(this, &other, sizeof(FMapSkillSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MaterialTextureParam
// 0x0010
struct FMaterialTextureParam
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UTexture*                                    Value;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMaterialTextureParam& other) const { return memcmp(this, &other, sizeof(FMaterialTextureParam)) == 0; }
	bool operator!=(const FMaterialTextureParam& other) const { return !(*this == other); }
	bool operator<(const FMaterialTextureParam& other) const { return memcmp(this, &other, sizeof(FMaterialTextureParam)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MaterialVectorParam
// 0x0018
struct FMaterialVectorParam
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                Value;                                         // 0x0008 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMaterialVectorParam& other) const { return memcmp(this, &other, sizeof(FMaterialVectorParam)) == 0; }
	bool operator!=(const FMaterialVectorParam& other) const { return !(*this == other); }
	bool operator<(const FMaterialVectorParam& other) const { return memcmp(this, &other, sizeof(FMaterialVectorParam)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MaterialScalarParam
// 0x000C
struct FMaterialScalarParam
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              Value;                                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMaterialScalarParam& other) const { return memcmp(this, &other, sizeof(FMaterialScalarParam)) == 0; }
	bool operator!=(const FMaterialScalarParam& other) const { return !(*this == other); }
	bool operator<(const FMaterialScalarParam& other) const { return memcmp(this, &other, sizeof(FMaterialScalarParam)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MaterialParams
// 0x0030
struct FMaterialParams
{
	class TArray<struct FMaterialTextureParam>         TextureParameters;                             // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FMaterialVectorParam>          VectorParameters;                              // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FMaterialScalarParam>          ScalarParameters;                              // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMaterialParams& other) const { return memcmp(this, &other, sizeof(FMaterialParams)) == 0; }
	bool operator!=(const FMaterialParams& other) const { return !(*this == other); }
	bool operator<(const FMaterialParams& other) const { return memcmp(this, &other, sizeof(FMaterialParams)) < 0; }
};

// ScriptStruct TAGame._Types_TA.AssociativeMaterialParams
// 0x0038
struct FAssociativeMaterialParams
{
	class UMaterialInterface*                          Material;                                      // 0x0000 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	struct FMaterialParams                             Params;                                        // 0x0008 (0x0030) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FAssociativeMaterialParams& other) const { return memcmp(this, &other, sizeof(FAssociativeMaterialParams)) == 0; }
	bool operator!=(const FAssociativeMaterialParams& other) const { return !(*this == other); }
	bool operator<(const FAssociativeMaterialParams& other) const { return memcmp(this, &other, sizeof(FAssociativeMaterialParams)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SkinBodySettings
// 0x0048
struct FSkinBodySettings
{
	class UProductAssetReferenceBody_TA*               Body;                                          // 0x0000 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	struct FMaterialParams                             Parameters;                                    // 0x0008 (0x0030) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FAssociativeMaterialParams>    AdditionalBodyParameters;                      // 0x0038 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)

	bool operator==(const FSkinBodySettings& other) const { return memcmp(this, &other, sizeof(FSkinBodySettings)) == 0; }
	bool operator!=(const FSkinBodySettings& other) const { return !(*this == other); }
	bool operator<(const FSkinBodySettings& other) const { return memcmp(this, &other, sizeof(FSkinBodySettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.UniqueNetIdGroup4
// 0x0120
struct FUniqueNetIdGroup4
{
	struct FUniqueNetId                                PlayerIds[4];                                  // 0x0000 (0x0120) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUniqueNetIdGroup4& other) const { return memcmp(this, &other, sizeof(FUniqueNetIdGroup4)) == 0; }
	bool operator!=(const FUniqueNetIdGroup4& other) const { return !(*this == other); }
	bool operator<(const FUniqueNetIdGroup4& other) const { return memcmp(this, &other, sizeof(FUniqueNetIdGroup4)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineProductAttribute
// 0x0018
struct FOnlineProductAttribute
{
	class FName                                        Key;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Value;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineProductAttribute& other) const { return memcmp(this, &other, sizeof(FOnlineProductAttribute)) == 0; }
	bool operator!=(const FOnlineProductAttribute& other) const { return !(*this == other); }
	bool operator<(const FOnlineProductAttribute& other) const { return memcmp(this, &other, sizeof(FOnlineProductAttribute)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineProductData
// 0x0040
struct FOnlineProductData
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000000000000000]               
	int32_t                                            SeriesID;                                      // 0x0018 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductAttribute>       Attributes;                                    // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TradeHold;                                     // 0x0030 (0x0004) [0x0000000000000000]               
	uint64_t                                           AddedTimestamp;                                // 0x0038 (0x0008) [0x0000000000000000]               

	bool operator==(const FOnlineProductData& other) const { return memcmp(this, &other, sizeof(FOnlineProductData)) == 0; }
	bool operator!=(const FOnlineProductData& other) const { return !(*this == other); }
	bool operator<(const FOnlineProductData& other) const { return memcmp(this, &other, sizeof(FOnlineProductData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.CurrencyProductData
// 0x0010
struct U_Types_TA_FCurrencyProductData
{
	class UProduct_TA*                                 Product;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const U_Types_TA_FCurrencyProductData& other) const { return memcmp(this, &other, sizeof(U_Types_TA_FCurrencyProductData)) == 0; }
	bool operator!=(const U_Types_TA_FCurrencyProductData& other) const { return !(*this == other); }
	bool operator<(const U_Types_TA_FCurrencyProductData& other) const { return memcmp(this, &other, sizeof(U_Types_TA_FCurrencyProductData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.Currency
// 0x0060
struct FCurrency
{
	ECurrency                                          Type;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000000000000]               
	uint32_t                                           bCanBeTraded : 1;                              // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsRocketPassDrop : 1;                         // 0x000C (0x0004) [0x0000000000000000] [0x00000002] 
	int32_t                                            TradeHold;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	struct U_Types_TA_FCurrencyProductData             ProductData;                                   // 0x0018 (0x0010) [0x0000000000000000]               
	int32_t                                            CurrencyID;                                    // 0x0028 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Id;                                            // 0x002C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Amount;                                        // 0x0030 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    LargeImage;                                    // 0x0038 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    SmallImage;                                    // 0x0040 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      LocalizedName;                                 // 0x0048 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint64_t                                           UpdatedTimestamp;                              // 0x0058 (0x0008) [0x0000000000000000]               

	bool operator==(const FCurrency& other) const { return memcmp(this, &other, sizeof(FCurrency)) == 0; }
	bool operator!=(const FCurrency& other) const { return !(*this == other); }
	bool operator<(const FCurrency& other) const { return memcmp(this, &other, sizeof(FCurrency)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineXPModifier
// 0x0038
struct FOnlineXPModifier
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	float                                              Modifier;                                      // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	EOnlineXPModifierType                              ModifierType;                                  // 0x000C (0x0001) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Value;                                         // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      LocalizedText;                                 // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bPremium : 1;                                  // 0x0028 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bPenalty : 1;                                  // 0x0028 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bPromo : 1;                                    // 0x0028 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	int32_t                                            Remaining;                                     // 0x002C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Count;                                         // 0x0030 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            MaxCount;                                      // 0x0034 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FOnlineXPModifier& other) const { return memcmp(this, &other, sizeof(FOnlineXPModifier)) == 0; }
	bool operator!=(const FOnlineXPModifier& other) const { return !(*this == other); }
	bool operator<(const FOnlineXPModifier& other) const { return memcmp(this, &other, sizeof(FOnlineXPModifier)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineXPReward
// 0x0040
struct FOnlineXPReward
{
	class FName                                        RewardName;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Total;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            Base;                                          // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            BaseLevel;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            Level;                                         // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            CapAdjustment;                                 // 0x0018 (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              LevelThresholds;                               // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineXPModifier>             RewardModifiers;                               // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineXPReward& other) const { return memcmp(this, &other, sizeof(FOnlineXPReward)) == 0; }
	bool operator!=(const FOnlineXPReward& other) const { return !(*this == other); }
	bool operator<(const FOnlineXPReward& other) const { return memcmp(this, &other, sizeof(FOnlineXPReward)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineProductDrop
// 0x0078
struct FOnlineProductDrop
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurrency>                     CurrencyData;                                  // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineXPReward>               RewardDrops;                                   // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineProductDrop& other) const { return memcmp(this, &other, sizeof(FOnlineProductDrop)) == 0; }
	bool operator!=(const FOnlineProductDrop& other) const { return !(*this == other); }
	bool operator<(const FOnlineProductDrop& other) const { return memcmp(this, &other, sizeof(FOnlineProductDrop)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ChallengeRequirementProgress
// 0x0008
struct FChallengeRequirementProgress
{
	int32_t                                            ProgressCount;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ProgressChange;                                // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FChallengeRequirementProgress& other) const { return memcmp(this, &other, sizeof(FChallengeRequirementProgress)) == 0; }
	bool operator!=(const FChallengeRequirementProgress& other) const { return !(*this == other); }
	bool operator<(const FChallengeRequirementProgress& other) const { return memcmp(this, &other, sizeof(FChallengeRequirementProgress)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ChallengeProgress
// 0x0028
struct FChallengeProgress
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bIsHidden : 1;                                 // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            CompleteCount;                                 // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bNotifyCompleted : 1;                          // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bNotifyAvailable : 1;                          // 0x000C (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bNotifyNewInfo : 1;                            // 0x000C (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bRewardsAvailable : 1;                         // 0x000C (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bComplete : 1;                                 // 0x000C (0x0004) [0x0000000000000000] [0x00000010] 
	uint64_t                                           ProgressResetTimeUTC;                          // 0x0010 (0x0008) [0x0000000000000000]               
	class TArray<struct FChallengeRequirementProgress> RequirementProgress;                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FChallengeProgress& other) const { return memcmp(this, &other, sizeof(FChallengeProgress)) == 0; }
	bool operator!=(const FChallengeProgress& other) const { return !(*this == other); }
	bool operator<(const FChallengeProgress& other) const { return memcmp(this, &other, sizeof(FChallengeProgress)) < 0; }
};

// ScriptStruct TAGame._Types_TA.XPRewardData
// 0x000C
struct FXPRewardData
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	float                                              Amount;                                        // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FXPRewardData& other) const { return memcmp(this, &other, sizeof(FXPRewardData)) == 0; }
	bool operator!=(const FXPRewardData& other) const { return !(*this == other); }
	bool operator<(const FXPRewardData& other) const { return memcmp(this, &other, sizeof(FXPRewardData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.GarageSlotCost
// 0x0008
struct FGarageSlotCost
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Amount;                                        // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGarageSlotCost& other) const { return memcmp(this, &other, sizeof(FGarageSlotCost)) == 0; }
	bool operator!=(const FGarageSlotCost& other) const { return !(*this == other); }
	bool operator<(const FGarageSlotCost& other) const { return memcmp(this, &other, sizeof(FGarageSlotCost)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductDrop
// 0x0024
struct FProductDrop
{
	struct FProductHashID                              GroupId;                                       // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	struct FProductInstanceID                          DropID;                                        // 0x0008 (0x0010) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           DropTime;                                      // 0x0018 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bCanEquipNow : 1;                              // 0x0020 (0x0004) [0x0000000040000000] [0x100000001] (CPF_DataBinding)

	bool operator==(const FProductDrop& other) const { return memcmp(this, &other, sizeof(FProductDrop)) == 0; }
	bool operator!=(const FProductDrop& other) const { return !(*this == other); }
	bool operator<(const FProductDrop& other) const { return memcmp(this, &other, sizeof(FProductDrop)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RPCIntroCar
// 0x0038
struct FRPCIntroCar
{
	int32_t                                            TemplateIndex;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      TemplateName;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TemplateDescription;                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              ProductsList;                                  // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRPCIntroCar& other) const { return memcmp(this, &other, sizeof(FRPCIntroCar)) == 0; }
	bool operator!=(const FRPCIntroCar& other) const { return !(*this == other); }
	bool operator<(const FRPCIntroCar& other) const { return memcmp(this, &other, sizeof(FRPCIntroCar)) < 0; }
};

// ScriptStruct TAGame._Types_TA.IntroCarInfo
// 0x0028
struct FIntroCarInfo
{
	int32_t                                            TemplateIndex;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FString                                      TemplateName;                                  // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      TemplateDescription;                           // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FIntroCarInfo& other) const { return memcmp(this, &other, sizeof(FIntroCarInfo)) == 0; }
	bool operator!=(const FIntroCarInfo& other) const { return !(*this == other); }
	bool operator<(const FIntroCarInfo& other) const { return memcmp(this, &other, sizeof(FIntroCarInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.EditorIntroCar
// 0x0038
struct FEditorIntroCar
{
	struct FIntroCarInfo                               Info;                                          // 0x0000 (0x0028) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<class UProduct_TA*>                   ProductList;                                   // 0x0028 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FEditorIntroCar& other) const { return memcmp(this, &other, sizeof(FEditorIntroCar)) == 0; }
	bool operator!=(const FEditorIntroCar& other) const { return !(*this == other); }
	bool operator<(const FEditorIntroCar& other) const { return memcmp(this, &other, sizeof(FEditorIntroCar)) < 0; }
};

// ScriptStruct TAGame._Types_TA.AppliedBreakoutDamage
// 0x0018
struct FAppliedBreakoutDamage
{
	uint8_t                                            Id;                                            // 0x0000 (0x0001) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	int32_t                                            DamageIndex;                                   // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalDamage;                                   // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FAppliedBreakoutDamage& other) const { return memcmp(this, &other, sizeof(FAppliedBreakoutDamage)) == 0; }
	bool operator!=(const FAppliedBreakoutDamage& other) const { return !(*this == other); }
	bool operator<(const FAppliedBreakoutDamage& other) const { return memcmp(this, &other, sizeof(FAppliedBreakoutDamage)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PaintAttributeParameter
// 0x0010
struct FPaintAttributeParameter
{
	EPaintColorVariant                                 PaintVariant;                                  // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class FName                                        ParameterName;                                 // 0x0004 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnabled : 1;                                  // 0x000C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bGammaCorrect : 1;                             // 0x000C (0x0004) [0x0000000000000001] [0x100000002] (CPF_Edit)

	bool operator==(const FPaintAttributeParameter& other) const { return memcmp(this, &other, sizeof(FPaintAttributeParameter)) == 0; }
	bool operator!=(const FPaintAttributeParameter& other) const { return !(*this == other); }
	bool operator<(const FPaintAttributeParameter& other) const { return memcmp(this, &other, sizeof(FPaintAttributeParameter)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductLevelData
// 0x0010
struct FProductLevelData
{
	int32_t                                            Level;                                         // 0x0000 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	int32_t                                            SoftCurrency;                                  // 0x0004 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	int32_t                                            HardCurrency;                                  // 0x0008 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	float                                              UnlockWeight;                                  // 0x000C (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)

	bool operator==(const FProductLevelData& other) const { return memcmp(this, &other, sizeof(FProductLevelData)) == 0; }
	bool operator!=(const FProductLevelData& other) const { return !(*this == other); }
	bool operator<(const FProductLevelData& other) const { return memcmp(this, &other, sizeof(FProductLevelData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.BallPredictionInfo
// 0x003C
struct FBallPredictionInfo
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              ArchTopTime;                                   // 0x0004 (0x0004) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     ArchTop;                                       // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     ArchTopVelocity;                               // 0x002C (0x000C) [0x0000000000000000]               
	uint32_t                                           bHitWall : 1;                                  // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bHitGround : 1;                                // 0x0038 (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FBallPredictionInfo& other) const { return memcmp(this, &other, sizeof(FBallPredictionInfo)) == 0; }
	bool operator!=(const FBallPredictionInfo& other) const { return !(*this == other); }
	bool operator<(const FBallPredictionInfo& other) const { return memcmp(this, &other, sizeof(FBallPredictionInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerPrivateMatchData
// 0x0050
struct FPlayerPrivateMatchData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              GameSecondsPlayed;                             // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            GameScore;                                     // 0x004C (0x0004) [0x0000000000000000]               

	bool operator==(const FPlayerPrivateMatchData& other) const { return memcmp(this, &other, sizeof(FPlayerPrivateMatchData)) == 0; }
	bool operator!=(const FPlayerPrivateMatchData& other) const { return !(*this == other); }
	bool operator<(const FPlayerPrivateMatchData& other) const { return memcmp(this, &other, sizeof(FPlayerPrivateMatchData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.StatData
// 0x000C
struct FStatData
{
	class FName                                        EventName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FStatData& other) const { return memcmp(this, &other, sizeof(FStatData)) == 0; }
	bool operator!=(const FStatData& other) const { return !(*this == other); }
	bool operator<(const FStatData& other) const { return memcmp(this, &other, sizeof(FStatData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.QuickChatGroup
// 0x0014
struct FQuickChatGroup
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Count;                                         // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FQuickChatGroup& other) const { return memcmp(this, &other, sizeof(FQuickChatGroup)) == 0; }
	bool operator!=(const FQuickChatGroup& other) const { return !(*this == other); }
	bool operator<(const FQuickChatGroup& other) const { return memcmp(this, &other, sizeof(FQuickChatGroup)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlinePlayerMatchData
// 0x0131
struct FOnlinePlayerMatchData
{
	class APRI_TA*                                     PRI;                                           // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	struct FUniqueNetId                                PlayerID;                                      // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              GameSecondsPlayed;                             // 0x0050 (0x0004) [0x0000000000000000]               
	int32_t                                            GameScore;                                     // 0x0054 (0x0004) [0x0000000000000000]               
	int32_t                                            MatchGoals;                                    // 0x0058 (0x0004) [0x0000000000000000]               
	int32_t                                            MatchAssists;                                  // 0x005C (0x0004) [0x0000000000000000]               
	int32_t                                            MatchSaves;                                    // 0x0060 (0x0004) [0x0000000000000000]               
	int32_t                                            MatchShots;                                    // 0x0064 (0x0004) [0x0000000000000000]               
	int32_t                                            XPGained;                                      // 0x0068 (0x0004) [0x0001000000000000]               
	class TArray<struct FOnlineProductData>            Loadout;                                       // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineProductData>            StatTitles;                                    // 0x0080 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCompletedMatch : 1;                           // 0x0090 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bForfeit : 1;                                  // 0x0090 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bMvp : 1;                                      // 0x0090 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bWinner : 1;                                   // 0x0090 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bLeaver : 1;                                   // 0x0090 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bInParty : 1;                                  // 0x0090 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bJoinedInProgress : 1;                         // 0x0090 (0x0004) [0x0000000000000000] [0x00000040] 
	int32_t                                            ConsecutiveMatchesPlayed;                      // 0x0094 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                PartyLeader;                                   // 0x0098 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  PartyMembers;                                  // 0x00E0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            DistanceDrivenMeters;                          // 0x00F0 (0x0004) [0x0000000000000000]               
	uint32_t                                           bPartyLeaderValid : 1;                         // 0x00F4 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            TeamIndex;                                     // 0x00F8 (0x0004) [0x0000000000000000]               
	class TArray<struct FStatData>                     Stats;                                         // 0x0100 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FLoadoutData>                  TeamLoadouts;                                  // 0x0110 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FQuickChatGroup>               QuickChat;                                     // 0x0120 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EInfectedType                                      InfectedByType;                                // 0x0130 (0x0001) [0x0001000000000000]               

	bool operator==(const FOnlinePlayerMatchData& other) const { return memcmp(this, &other, sizeof(FOnlinePlayerMatchData)) == 0; }
	bool operator!=(const FOnlinePlayerMatchData& other) const { return !(*this == other); }
	bool operator<(const FOnlinePlayerMatchData& other) const { return memcmp(this, &other, sizeof(FOnlinePlayerMatchData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.StatDataFloat
// 0x000C
struct FStatDataFloat
{
	class FName                                        EventName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Count;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FStatDataFloat& other) const { return memcmp(this, &other, sizeof(FStatDataFloat)) == 0; }
	bool operator!=(const FStatDataFloat& other) const { return !(*this == other); }
	bool operator<(const FStatDataFloat& other) const { return memcmp(this, &other, sizeof(FStatDataFloat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ActorHistory
// 0x0020
struct FActorHistory
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	EHistory                                           Type;                                          // 0x0008 (0x0001) [0x0000000000000000]               
	class FString                                      SerializedHistory;                             // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FActorHistory& other) const { return memcmp(this, &other, sizeof(FActorHistory)) == 0; }
	bool operator!=(const FActorHistory& other) const { return !(*this == other); }
	bool operator<(const FActorHistory& other) const { return memcmp(this, &other, sizeof(FActorHistory)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SortedProductData
// 0x0034
struct FSortedProductData
{
	struct FProductInstanceID                          Id;                                            // 0x0000 (0x0010) [0x0000000000000000]               
	struct FProductHashID                              HashID;                                        // 0x0010 (0x0004) [0x0000000000000000]               
	class UProduct_TA*                                 Product;                                       // 0x0018 (0x0008) [0x0000000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0020 (0x0008) [0x0000000000000000]               
	int32_t                                            BlueprintSortWeight;                           // 0x0028 (0x0004) [0x0000000000000000]               
	int32_t                                            Quantity;                                      // 0x002C (0x0004) [0x0000000000000000]               
	uint32_t                                           bUnlocked : 1;                                 // 0x0030 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsFavorited : 1;                              // 0x0030 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bCurrency : 1;                                 // 0x0030 (0x0004) [0x0000000000000000] [0x100000004] 

	bool operator==(const FSortedProductData& other) const { return memcmp(this, &other, sizeof(FSortedProductData)) == 0; }
	bool operator!=(const FSortedProductData& other) const { return !(*this == other); }
	bool operator<(const FSortedProductData& other) const { return memcmp(this, &other, sizeof(FSortedProductData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.EditorRoundData
// 0x0018
struct FEditorRoundData
{
	float                                              TimeLimit;                                     // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<class FString>                        SerializedArchetypes;                          // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FEditorRoundData& other) const { return memcmp(this, &other, sizeof(FEditorRoundData)) == 0; }
	bool operator!=(const FEditorRoundData& other) const { return !(*this == other); }
	bool operator<(const FEditorRoundData& other) const { return memcmp(this, &other, sizeof(FEditorRoundData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadObjectResult
// 0x0021
struct FLoadObjectResult
{
	class FString                                      FilePath;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UObject*                                     ObjectData;                                    // 0x0010 (0x0008) [0x0000000000000000]               
	class UError*                                      Error;                                         // 0x0018 (0x0008) [0x0000000000000000]               
	EBasicLoadResult                                   Code;                                          // 0x0020 (0x0001) [0x0000000000000000]               

	bool operator==(const FLoadObjectResult& other) const { return memcmp(this, &other, sizeof(FLoadObjectResult)) == 0; }
	bool operator!=(const FLoadObjectResult& other) const { return !(*this == other); }
	bool operator<(const FLoadObjectResult& other) const { return memcmp(this, &other, sizeof(FLoadObjectResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SaveObjectResult
// 0x0011
struct FSaveObjectResult
{
	class UObject*                                     ObjectData;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	class UError*                                      Error;                                         // 0x0008 (0x0008) [0x0000000000000000]               
	ESaveGameResult                                    Code;                                          // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FSaveObjectResult& other) const { return memcmp(this, &other, sizeof(FSaveObjectResult)) == 0; }
	bool operator!=(const FSaveObjectResult& other) const { return !(*this == other); }
	bool operator<(const FSaveObjectResult& other) const { return memcmp(this, &other, sizeof(FSaveObjectResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.WeldingInfo
// 0x0024
struct FWeldingInfo
{
	class ARBActor_TA*                                 RBActor;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     Offset;                                        // 0x0008 (0x000C) [0x0000000000000000]               
	float                                              Mass;                                          // 0x0014 (0x0004) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0018 (0x000C) [0x0000000000000000]               

	bool operator==(const FWeldingInfo& other) const { return memcmp(this, &other, sizeof(FWeldingInfo)) == 0; }
	bool operator!=(const FWeldingInfo& other) const { return !(*this == other); }
	bool operator<(const FWeldingInfo& other) const { return memcmp(this, &other, sizeof(FWeldingInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ChatBanInfo
// 0x000C
struct FChatBanInfo
{
	uint64_t                                           Expiration;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	uint32_t                                           bPermanentlyBanned : 1;                        // 0x0008 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FChatBanInfo& other) const { return memcmp(this, &other, sizeof(FChatBanInfo)) == 0; }
	bool operator!=(const FChatBanInfo& other) const { return !(*this == other); }
	bool operator<(const FChatBanInfo& other) const { return memcmp(this, &other, sizeof(FChatBanInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerChatMessage
// 0x0068
struct FPlayerChatMessage
{
	float                                              MessageTimeStamp;                              // 0x0000 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                PlayerID;                                      // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	EChatChannel                                       ChatChannel;                                   // 0x0050 (0x0001) [0x0000000000000000]               
	int32_t                                            Team;                                          // 0x0054 (0x0004) [0x0000000000000000]               
	class FString                                      Message;                                       // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerChatMessage& other) const { return memcmp(this, &other, sizeof(FPlayerChatMessage)) == 0; }
	bool operator!=(const FPlayerChatMessage& other) const { return !(*this == other); }
	bool operator<(const FPlayerChatMessage& other) const { return memcmp(this, &other, sizeof(FPlayerChatMessage)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ReportedPlayerInfo
// 0x00A4
struct FReportedPlayerInfo
{
	struct FUniqueNetId                                Reporter;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                Offender;                                      // 0x0048 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              ReasonIDs;                                     // 0x0090 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              ReportTimeStamp;                               // 0x00A0 (0x0004) [0x0000000000000000]               

	bool operator==(const FReportedPlayerInfo& other) const { return memcmp(this, &other, sizeof(FReportedPlayerInfo)) == 0; }
	bool operator!=(const FReportedPlayerInfo& other) const { return !(*this == other); }
	bool operator<(const FReportedPlayerInfo& other) const { return memcmp(this, &other, sizeof(FReportedPlayerInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerStatus
// 0x0068
struct FPlayerStatus
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Statuses;                                      // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EPlayerStatusType>                    ConvertedStatuses;                             // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerStatus& other) const { return memcmp(this, &other, sizeof(FPlayerStatus)) == 0; }
	bool operator!=(const FPlayerStatus& other) const { return !(*this == other); }
	bool operator<(const FPlayerStatus& other) const { return memcmp(this, &other, sizeof(FPlayerStatus)) < 0; }
};

// ScriptStruct TAGame._Types_TA.BoostOptionData
// 0x0010
struct FBoostOptionData
{
	class FString                                      LocalizedName;                                 // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FBoostOptionData& other) const { return memcmp(this, &other, sizeof(FBoostOptionData)) == 0; }
	bool operator!=(const FBoostOptionData& other) const { return !(*this == other); }
	bool operator<(const FBoostOptionData& other) const { return memcmp(this, &other, sizeof(FBoostOptionData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.GoalResetOptionData
// 0x0020
struct FGoalResetOptionData
{
	class FString                                      LocalizedName;                                 // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      LocalizedDescription;                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGoalResetOptionData& other) const { return memcmp(this, &other, sizeof(FGoalResetOptionData)) == 0; }
	bool operator!=(const FGoalResetOptionData& other) const { return !(*this == other); }
	bool operator<(const FGoalResetOptionData& other) const { return memcmp(this, &other, sizeof(FGoalResetOptionData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.GameModeData
// 0x0020
struct FGameModeData
{
	int32_t                                            GameMode;                                      // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      LocalizedName;                                 // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            SortIdx;                                       // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bFreeForAll : 1;                               // 0x001C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bBotsDisabled : 1;                             // 0x001C (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bAllMutatorsDisallowed : 1;                    // 0x001C (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)

	bool operator==(const FGameModeData& other) const { return memcmp(this, &other, sizeof(FGameModeData)) == 0; }
	bool operator!=(const FGameModeData& other) const { return !(*this == other); }
	bool operator<(const FGameModeData& other) const { return memcmp(this, &other, sizeof(FGameModeData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SimilarLogoGroup
// 0x0010
struct FSimilarLogoGroup
{
	class TArray<class UProductAsset_Logo_TA*>         SimilarLogoColorAssets;                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FSimilarLogoGroup& other) const { return memcmp(this, &other, sizeof(FSimilarLogoGroup)) == 0; }
	bool operator!=(const FSimilarLogoGroup& other) const { return !(*this == other); }
	bool operator<(const FSimilarLogoGroup& other) const { return memcmp(this, &other, sizeof(FSimilarLogoGroup)) < 0; }
};

// ScriptStruct TAGame._Types_TA.UIProductSlotData
// 0x0018
struct FUIProductSlotData
{
	class UProductSlot_TA*                             Slot;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UTexture2D*                                  Texture;                                       // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UAkSoundCue*                                 Sound;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FUIProductSlotData& other) const { return memcmp(this, &other, sizeof(FUIProductSlotData)) == 0; }
	bool operator!=(const FUIProductSlotData& other) const { return !(*this == other); }
	bool operator<(const FUIProductSlotData& other) const { return memcmp(this, &other, sizeof(FUIProductSlotData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SimpleSpringSettings
// 0x0050
struct FSimpleSpringSettings
{
	struct FVector                                     Strength;                                      // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Damping;                                       // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     MaxDisplacement;                               // 0x0018 (0x000C) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bUseMinDisplacement : 1;                       // 0x0024 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FVector                                     MinDisplacement;                               // 0x0028 (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              Mass;                                          // 0x0034 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     MassOffset;                                    // 0x0038 (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxSpeed;                                      // 0x0044 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bDebug : 1;                                    // 0x0048 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              DrawDebugOffset;                               // 0x004C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSimpleSpringSettings& other) const { return memcmp(this, &other, sizeof(FSimpleSpringSettings)) == 0; }
	bool operator!=(const FSimpleSpringSettings& other) const { return !(*this == other); }
	bool operator<(const FSimpleSpringSettings& other) const { return memcmp(this, &other, sizeof(FSimpleSpringSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.WheelContactData
// 0x0050
struct FWheelContactData
{
	uint32_t                                           bHasContact : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bHasContactWithWorldGeometry : 1;              // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	float                                              HasContactChangeTime;                          // 0x0004 (0x0004) [0x0000000000000000]               
	class AActor*                                      Actor;                                         // 0x0008 (0x0008) [0x0000000000000000]               
	class UPrimitiveComponent*                         Component;                                     // 0x0010 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     Location;                                      // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     Normal;                                        // 0x0024 (0x000C) [0x0000000000000000]               
	struct FVector                                     LatDirection;                                  // 0x0030 (0x000C) [0x0000000000000000]               
	struct FVector                                     LongDirection;                                 // 0x003C (0x000C) [0x0000000000000000]               
	class UPhysicalMaterialProperty_TA*                PhysMatProp;                                   // 0x0048 (0x0008) [0x0000000000000000]               

	bool operator==(const FWheelContactData& other) const { return memcmp(this, &other, sizeof(FWheelContactData)) == 0; }
	bool operator!=(const FWheelContactData& other) const { return !(*this == other); }
	bool operator<(const FWheelContactData& other) const { return memcmp(this, &other, sizeof(FWheelContactData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.WheelAttachment
// 0x0030
struct FWheelAttachment
{
	class UPrimitiveComponent*                         Component;                                     // 0x0000 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class TArray<class UAttachmentBehavior_TA*>        Behaviors;                                     // 0x0008 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)
	class FName                                        Socket;                                        // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UMaterialInterface*>            PaintableMaterials;                            // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FWheelAttachment& other) const { return memcmp(this, &other, sizeof(FWheelAttachment)) == 0; }
	bool operator!=(const FWheelAttachment& other) const { return !(*this == other); }
	bool operator<(const FWheelAttachment& other) const { return memcmp(this, &other, sizeof(FWheelAttachment)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductAttachment
// 0x0070
struct FProductAttachment
{
	class UStaticMesh*                                 StaticMesh;                                    // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USkeletalMesh*                               SkeletalMesh;                                  // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UParticleSystem*                             ParticleSystem;                                // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInterface*                          Material;                                      // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              Scale;                                         // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Translation;                                   // 0x0024 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FRotator                                    Rotation;                                      // 0x0030 (0x000C) [0x0000000000000001] (CPF_Edit)    
	EProductAttachmentSocket                           Socket;                                        // 0x003C (0x0001) [0x0000000000000001] (CPF_Edit)    
	class UAntennaComponent_TA*                        Antenna;                                       // 0x0040 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class TArray<class UAttachmentBehavior_TA*>        Behaviors;                                     // 0x0048 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)
	class UProductAttribute_InheritCarSetting_TA*      InheritCarAttribute;                           // 0x0058 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	class UPrimitiveComponent*                         Component;                                     // 0x0060 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class AFXActor_X*                                  FXActor;                                       // 0x0068 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FProductAttachment& other) const { return memcmp(this, &other, sizeof(FProductAttachment)) == 0; }
	bool operator!=(const FProductAttachment& other) const { return !(*this == other); }
	bool operator<(const FProductAttachment& other) const { return memcmp(this, &other, sizeof(FProductAttachment)) < 0; }
};

// ScriptStruct TAGame._Types_TA.AccumulatedRigidBodyCollision
// 0x0080
struct FAccumulatedRigidBodyCollision
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class UPrimitiveComponent*                         Component;                                     // 0x0008 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class UPhysicalMaterial*                           PhysMat;                                       // 0x0010 (0x0008) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     OtherVelocity;                                 // 0x0024 (0x000C) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0030 (0x000C) [0x0000000000000000]               
	struct FVector                                     Normal;                                        // 0x003C (0x000C) [0x0000000000000000]               
	struct FVector                                     NormalForce;                                   // 0x0048 (0x000C) [0x0000000000000000]               
	struct FVector                                     FrictionForce;                                 // 0x0054 (0x000C) [0x0000000000000000]               
	struct FVector                                     NormalVelocity;                                // 0x0060 (0x000C) [0x0000000000000000]               
	struct FVector                                     FrictionVelocity;                              // 0x006C (0x000C) [0x0000000000000000]               
	int32_t                                            NumCollisions;                                 // 0x0078 (0x0004) [0x0000000000000000]               
	int32_t                                            NumContacts;                                   // 0x007C (0x0004) [0x0000000000000000]               

	bool operator==(const FAccumulatedRigidBodyCollision& other) const { return memcmp(this, &other, sizeof(FAccumulatedRigidBodyCollision)) == 0; }
	bool operator!=(const FAccumulatedRigidBodyCollision& other) const { return !(*this == other); }
	bool operator<(const FAccumulatedRigidBodyCollision& other) const { return memcmp(this, &other, sizeof(FAccumulatedRigidBodyCollision)) < 0; }
};

// ScriptStruct TAGame._Types_TA.TAPlayerStat
// 0x000C
struct FTAPlayerStat
{
	class UStatEvent_TA*                               StatEvent;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FTAPlayerStat& other) const { return memcmp(this, &other, sizeof(FTAPlayerStat)) == 0; }
	bool operator!=(const FTAPlayerStat& other) const { return !(*this == other); }
	bool operator<(const FTAPlayerStat& other) const { return memcmp(this, &other, sizeof(FTAPlayerStat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.BallHitInfo
// 0x010C
struct FBallHitInfo
{
	class APRI_TA*                                     PRI;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class APRI_TA*                                     AttackerPRI;                                   // 0x0008 (0x0008) [0x0000000000000000]               
	class FName                                        CarName;                                       // 0x0010 (0x0008) [0x0000000000000000]               
	int32_t                                            TeamNum;                                       // 0x0018 (0x0004) [0x0000000000000000]               
	struct FReplicatedRBState                          PreHitCarPhysics;                              // 0x0020 (0x0040) [0x0000000000000000]               
	struct FReplicatedRBState                          PreHitBallPhysics;                             // 0x0060 (0x0040) [0x0000000000000000]               
	struct FReplicatedRBState                          PostHitBallPhysics;                            // 0x00A0 (0x0040) [0x0000000000000000]               
	float                                              Distance;                                      // 0x00E0 (0x0004) [0x0000000000000000]               
	float                                              Time;                                          // 0x00E4 (0x0004) [0x0000000000000000]               
	struct FVector                                     HitLocation;                                   // 0x00E8 (0x000C) [0x0000000000000000]               
	struct FVector                                     HitNormal;                                     // 0x00F4 (0x000C) [0x0000000000000000]               
	uint32_t                                           bDodging : 1;                                  // 0x0100 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bWheelsTouching : 1;                           // 0x0100 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bWorldTouching : 1;                            // 0x0100 (0x0004) [0x0000000000000000] [0x00000004] 
	EBallHitType                                       HitType;                                       // 0x0104 (0x0001) [0x0000000000000000]               
	int32_t                                            HitID;                                         // 0x0108 (0x0004) [0x0000000000000000]               

	bool operator==(const FBallHitInfo& other) const { return memcmp(this, &other, sizeof(FBallHitInfo)) == 0; }
	bool operator!=(const FBallHitInfo& other) const { return !(*this == other); }
	bool operator<(const FBallHitInfo& other) const { return memcmp(this, &other, sizeof(FBallHitInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MessageValue
// 0x002C
struct FMessageValue
{
	class FString                                      StringValue;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            IntValue;                                      // 0x0010 (0x0004) [0x0000000000000000]               
	class UObject*                                     ObjectValue;                                   // 0x0018 (0x0008) [0x0000000000000000]               
	class FName                                        NameValue;                                     // 0x0020 (0x0008) [0x0000000000000000]               
	int32_t                                            ValueType;                                     // 0x0028 (0x0004) [0x0000000000000000]               

	bool operator==(const FMessageValue& other) const { return memcmp(this, &other, sizeof(FMessageValue)) == 0; }
	bool operator!=(const FMessageValue& other) const { return !(*this == other); }
	bool operator<(const FMessageValue& other) const { return memcmp(this, &other, sizeof(FMessageValue)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MessagePacket
// 0x0018
struct FMessagePacket
{
	class UMessage_TA*                                 Message;                                       // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FMessageValue>                 Values;                                        // 0x0008 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FMessagePacket& other) const { return memcmp(this, &other, sizeof(FMessagePacket)) == 0; }
	bool operator!=(const FMessagePacket& other) const { return !(*this == other); }
	bool operator<(const FMessagePacket& other) const { return memcmp(this, &other, sizeof(FMessagePacket)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ClientFrameData
// 0x002C
struct FClientFrameData
{
	struct FVehicleInputs                              VehicleInput;                                  // 0x0000 (0x0024) [0x0000000000000000]               
	int32_t                                            frame;                                         // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              TimeStamp;                                     // 0x0028 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientFrameData& other) const { return memcmp(this, &other, sizeof(FClientFrameData)) == 0; }
	bool operator!=(const FClientFrameData& other) const { return !(*this == other); }
	bool operator<(const FClientFrameData& other) const { return memcmp(this, &other, sizeof(FClientFrameData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ClientOnlineProductStat
// 0x0014
struct FClientOnlineProductStat
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000000000000]               
	int32_t                                            Value;                                         // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientOnlineProductStat& other) const { return memcmp(this, &other, sizeof(FClientOnlineProductStat)) == 0; }
	bool operator!=(const FClientOnlineProductStat& other) const { return !(*this == other); }
	bool operator<(const FClientOnlineProductStat& other) const { return memcmp(this, &other, sizeof(FClientOnlineProductStat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineProductStat
// 0x001C
struct FOnlineProductStat
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000000000000]               
	class UProductStat_TA*                             ProductStat;                                   // 0x0010 (0x0008) [0x0000000000000000]               
	int32_t                                            StatId;                                        // 0x0018 (0x0004) [0x0001000000000000]               

	bool operator==(const FOnlineProductStat& other) const { return memcmp(this, &other, sizeof(FOnlineProductStat)) == 0; }
	bool operator!=(const FOnlineProductStat& other) const { return !(*this == other); }
	bool operator<(const FOnlineProductStat& other) const { return memcmp(this, &other, sizeof(FOnlineProductStat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductAttributesArray
// 0x0010
struct FProductAttributesArray
{
	class TArray<class UProductAttribute_TA*>          Attributes;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FProductAttributesArray& other) const { return memcmp(this, &other, sizeof(FProductAttributesArray)) == 0; }
	bool operator!=(const FProductAttributesArray& other) const { return !(*this == other); }
	bool operator<(const FProductAttributesArray& other) const { return memcmp(this, &other, sizeof(FProductAttributesArray)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutAttributesArray
// 0x0010
struct FLoadoutAttributesArray
{
	class TArray<struct FProductAttributesArray>       Products;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLoadoutAttributesArray& other) const { return memcmp(this, &other, sizeof(FLoadoutAttributesArray)) == 0; }
	bool operator!=(const FLoadoutAttributesArray& other) const { return !(*this == other); }
	bool operator<(const FLoadoutAttributesArray& other) const { return memcmp(this, &other, sizeof(FLoadoutAttributesArray)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutProductData
// 0x0028
struct FLoadoutProductData
{
	int32_t                                            SlotIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ProductID;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000000000000000]               
	class TArray<class UProductAttribute_TA*>          Attributes;                                    // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLoadoutProductData& other) const { return memcmp(this, &other, sizeof(FLoadoutProductData)) == 0; }
	bool operator!=(const FLoadoutProductData& other) const { return !(*this == other); }
	bool operator<(const FLoadoutProductData& other) const { return memcmp(this, &other, sizeof(FLoadoutProductData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ServerSetLoadoutTeam
// 0x0020
struct FServerSetLoadoutTeam
{
	class TArray<struct FLoadoutProductData>           Products;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLoadoutTeamPaint                           TeamPaint;                                     // 0x0010 (0x0010) [0x0000000000000000]               

	bool operator==(const FServerSetLoadoutTeam& other) const { return memcmp(this, &other, sizeof(FServerSetLoadoutTeam)) == 0; }
	bool operator!=(const FServerSetLoadoutTeam& other) const { return !(*this == other); }
	bool operator<(const FServerSetLoadoutTeam& other) const { return memcmp(this, &other, sizeof(FServerSetLoadoutTeam)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ServerSetLoadoutParams
// 0x0058
struct FServerSetLoadoutParams
{
	class FName                                        Title;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	struct FServerSetLoadoutTeam                       Loadouts[2];                                   // 0x0008 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FLoadoutProductData>           DataProducts;                                  // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FServerSetLoadoutParams& other) const { return memcmp(this, &other, sizeof(FServerSetLoadoutParams)) == 0; }
	bool operator!=(const FServerSetLoadoutParams& other) const { return !(*this == other); }
	bool operator<(const FServerSetLoadoutParams& other) const { return memcmp(this, &other, sizeof(FServerSetLoadoutParams)) < 0; }
};

// ScriptStruct TAGame._Types_TA.LoadoutAssetNames
// 0x0010
struct FLoadoutAssetNames
{
	class TArray<class FString>                        Assets;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLoadoutAssetNames& other) const { return memcmp(this, &other, sizeof(FLoadoutAssetNames)) == 0; }
	bool operator!=(const FLoadoutAssetNames& other) const { return !(*this == other); }
	bool operator<(const FLoadoutAssetNames& other) const { return memcmp(this, &other, sizeof(FLoadoutAssetNames)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RandomRange
// 0x0008
struct FRandomRange
{
	float                                              Min;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Max;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRandomRange& other) const { return memcmp(this, &other, sizeof(FRandomRange)) == 0; }
	bool operator!=(const FRandomRange& other) const { return !(*this == other); }
	bool operator<(const FRandomRange& other) const { return memcmp(this, &other, sizeof(FRandomRange)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SchematicResourceData
// 0x0014
struct FSchematicResourceData
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Resources;                                     // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FSchematicResourceData& other) const { return memcmp(this, &other, sizeof(FSchematicResourceData)) == 0; }
	bool operator!=(const FSchematicResourceData& other) const { return !(*this == other); }
	bool operator<(const FSchematicResourceData& other) const { return memcmp(this, &other, sizeof(FSchematicResourceData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProfileProduct
// 0x0020
struct FProfileProduct
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000000000000]               
	class TArray<class UProductAttribute_TA*>          Attributes;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FProfileProduct& other) const { return memcmp(this, &other, sizeof(FProfileProduct)) == 0; }
	bool operator!=(const FProfileProduct& other) const { return !(*this == other); }
	bool operator<(const FProfileProduct& other) const { return memcmp(this, &other, sizeof(FProfileProduct)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductFilter
// 0x0170
struct FProductFilter
{
	class TArray<class UOnlineProduct_TA*>             OnlineProducts;                                // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UProduct_TA*>                   Products;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FProductHashID>                ArchivedProducts;                              // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FProductHashID>                FavoritedProducts;                             // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Label;                                         // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              Slots;                                         // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UProductSlot_TA*>               ProhibitedSlots;                               // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EProductQuality>                      ExclusiveQualities;                            // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EProductQuality>                      ProhibitedQualities;                           // 0x0080 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EUnlockMethod>                        UnlockMethods;                                 // 0x0090 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EProductTradeRestriction>             TradeRestrictions;                             // 0x00A0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              TradeHoldRestrictions;                         // 0x00B0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UClass*>                        ExclusiveAttributes;                           // 0x00C0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UClass*>                        ProhibitedAttributes;                          // 0x00D0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EProductFilterSortType                             SortType;                                      // 0x00E0 (0x0001) [0x0000000000000000]               
	class TArray<int32_t>                              SeriesIDs;                                     // 0x00E8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FProductHashID                              PackHashID;                                    // 0x00F8 (0x0004) [0x0000000000000000]               
	uint32_t                                           bExcludePacks : 1;                             // 0x00FC (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bOnlyXEItems : 1;                              // 0x00FC (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bIgnoreEquipped : 1;                           // 0x00FC (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bIgnoreLicensedCars : 1;                       // 0x00FC (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bStackProducts : 1;                            // 0x00FC (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bAllowEquippedArchivedProducts : 1;            // 0x00FC (0x0004) [0x0000000000000000] [0x00000020] 
	class TArray<int32_t>                              Loadout;                                       // 0x0100 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FProductHashID>                EquippedHashIDs;                               // 0x0110 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint8_t                                            LogLevel;                                      // 0x0120 (0x0001) [0x0000000000000000]               
	EArchiveProductFilter                              ArchivedProductFilter;                         // 0x0121 (0x0001) [0x0000000000000000]               
	EFavoritedProductFilter                            FavoritedProductFilter;                        // 0x0122 (0x0001) [0x0000000000000000]               
	class TArray<EBlueprintType>                       ProhibitedBlueprints;                          // 0x0128 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EProductFilterSortType>               ProhibitedSortTypes;                           // 0x0138 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UClass*>                        ProhibitedAttributeSortTypes;                  // 0x0148 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              PaintIDs;                                      // 0x0158 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	EDuplicatesFilterType                              DuplicatesFilterType;                          // 0x0168 (0x0001) [0x0000000000000000]               
	uint32_t                                           bAllowQualityPreFiltering : 1;                 // 0x016C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bSkipOfflineProducts : 1;                      // 0x016C (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FProductFilter& other) const { return memcmp(this, &other, sizeof(FProductFilter)) == 0; }
	bool operator!=(const FProductFilter& other) const { return !(*this == other); }
	bool operator<(const FProductFilter& other) const { return memcmp(this, &other, sizeof(FProductFilter)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ThumbnailComponent
// 0x0058
struct FThumbnailComponent
{
	class UActorComponent*                             Component;                                     // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	uint8_t                                            UnknownData00[0x8];                              // 0x0008 (0x0008) MISSED OFFSET
	struct FMatrix                                     BaseTransform;                                 // 0x0010 (0x0040) [0x0000000000000000]               
	class FName                                        Tag;                                           // 0x0050 (0x0008) [0x0000000000000000]               
	uint8_t                                            MinStructAlignment[0x8];                         // 0x0058 (0x0008) ADDED PADDING

	bool operator==(const FThumbnailComponent& other) const { return memcmp(this, &other, sizeof(FThumbnailComponent)) == 0; }
	bool operator!=(const FThumbnailComponent& other) const { return !(*this == other); }
	bool operator<(const FThumbnailComponent& other) const { return memcmp(this, &other, sizeof(FThumbnailComponent)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassPlayerRewards
// 0x0008
struct FRocketPassPlayerRewards
{
	int32_t                                            BaseTierRewards;                               // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ProTierRewards;                                // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FRocketPassPlayerRewards& other) const { return memcmp(this, &other, sizeof(FRocketPassPlayerRewards)) == 0; }
	bool operator!=(const FRocketPassPlayerRewards& other) const { return !(*this == other); }
	bool operator<(const FRocketPassPlayerRewards& other) const { return memcmp(this, &other, sizeof(FRocketPassPlayerRewards)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassTierBonusRange
// 0x000C
struct FRocketPassTierBonusRange
{
	int32_t                                            Start;                                         // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            End;                                           // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Bonus;                                         // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FRocketPassTierBonusRange& other) const { return memcmp(this, &other, sizeof(FRocketPassTierBonusRange)) == 0; }
	bool operator!=(const FRocketPassTierBonusRange& other) const { return !(*this == other); }
	bool operator<(const FRocketPassTierBonusRange& other) const { return memcmp(this, &other, sizeof(FRocketPassTierBonusRange)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassUnlock
// 0x0038
struct FRocketPassUnlock
{
	int32_t                                            Tier;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineXPReward>               RewardDrops;                                   // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurrency>                     CurrencyDrops;                                 // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRocketPassUnlock& other) const { return memcmp(this, &other, sizeof(FRocketPassUnlock)) == 0; }
	bool operator!=(const FRocketPassUnlock& other) const { return !(*this == other); }
	bool operator<(const FRocketPassUnlock& other) const { return memcmp(this, &other, sizeof(FRocketPassUnlock)) < 0; }
};

// ScriptStruct TAGame._Types_TA.TierUnlockRequirements
// 0x0008
struct FTierUnlockRequirements
{
	int32_t                                            Tier;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Requirement;                                   // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FTierUnlockRequirements& other) const { return memcmp(this, &other, sizeof(FTierUnlockRequirements)) == 0; }
	bool operator!=(const FTierUnlockRequirements& other) const { return !(*this == other); }
	bool operator<(const FTierUnlockRequirements& other) const { return memcmp(this, &other, sizeof(FTierUnlockRequirements)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineProductTimestampedData
// 0x0010 (0x0040 - 0x0050)
struct FOnlineProductTimestampedData : FOnlineProductData
{
	uint64_t                                           UpdatedTimestamp;                              // 0x0040 (0x0008) [0x0000000000000000]               
	uint64_t                                           DeletedTimestamp;                              // 0x0048 (0x0008) [0x0000000000000000]               

	bool operator==(const FOnlineProductTimestampedData& other) const { return memcmp(this, &other, sizeof(FOnlineProductTimestampedData)) == 0; }
	bool operator!=(const FOnlineProductTimestampedData& other) const { return !(*this == other); }
	bool operator<(const FOnlineProductTimestampedData& other) const { return memcmp(this, &other, sizeof(FOnlineProductTimestampedData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ItemSetsData
// 0x0030
struct FItemSetsData
{
	class TArray<struct FOnlineProductTimestampedData> Instances;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Id;                                            // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              StartTime;                                     // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              EndTime;                                       // 0x0028 (0x0004) [0x0000000000000000]               
	uint32_t                                           HideNotification : 1;                          // 0x002C (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FItemSetsData& other) const { return memcmp(this, &other, sizeof(FItemSetsData)) == 0; }
	bool operator!=(const FItemSetsData& other) const { return !(*this == other); }
	bool operator<(const FItemSetsData& other) const { return memcmp(this, &other, sizeof(FItemSetsData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassRewardData
// 0x0048
struct FRocketPassRewardData
{
	int32_t                                            Tier;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	ERocketPassTierType                                UnlockType;                                    // 0x0004 (0x0001) [0x0000000000000000]               
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FItemSetsData>                 ItemSets;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FXPRewardData>                 XPRewards;                                     // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurrency>                     CurrencyDrops;                                 // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRocketPassRewardData& other) const { return memcmp(this, &other, sizeof(FRocketPassRewardData)) == 0; }
	bool operator!=(const FRocketPassRewardData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassRewardData& other) const { return memcmp(this, &other, sizeof(FRocketPassRewardData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassExtendedRewardData
// 0x0010 (0x0048 - 0x0058)
struct FRocketPassExtendedRewardData : FRocketPassRewardData
{
	uint32_t                                           bPremiumTier : 1;                              // 0x0048 (0x0004) [0x0000000000000000] [0x00000001] 
	ERocketPassTierLockState                           LockState;                                     // 0x004C (0x0001) [0x0000000000000000]               
	int32_t                                            LevelRequirement;                              // 0x0050 (0x0004) [0x0000000000000000]               
	int32_t                                            ClaimRequirement;                              // 0x0054 (0x0004) [0x0000000000000000]               

	bool operator==(const FRocketPassExtendedRewardData& other) const { return memcmp(this, &other, sizeof(FRocketPassExtendedRewardData)) == 0; }
	bool operator!=(const FRocketPassExtendedRewardData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassExtendedRewardData& other) const { return memcmp(this, &other, sizeof(FRocketPassExtendedRewardData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassPage
// 0x004C
struct FRocketPassPage
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            RocketPassID;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Page;                                          // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            StartLevel;                                    // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            EndLevel;                                      // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            LevelRequiredToUnlock;                         // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            ClaimsRequiredToUnlock;                        // 0x0018 (0x0004) [0x0000000000000000]               
	class TArray<struct FTierUnlockRequirements>       TierClaimRequirements;                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bProTier : 1;                                  // 0x0030 (0x0004) [0x0000000000002000] [0x00000001] (CPF_Transient)
	class TArray<struct FRocketPassExtendedRewardData> Rewards;                                       // 0x0038 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	int32_t                                            NumClaimedRewards;                             // 0x0048 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FRocketPassPage& other) const { return memcmp(this, &other, sizeof(FRocketPassPage)) == 0; }
	bool operator!=(const FRocketPassPage& other) const { return !(*this == other); }
	bool operator<(const FRocketPassPage& other) const { return memcmp(this, &other, sizeof(FRocketPassPage)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassClaimData
// 0x0028
struct FRocketPassClaimData
{
	int32_t                                            Tier;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurrency>                     CurrencyDrops;                                 // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRocketPassClaimData& other) const { return memcmp(this, &other, sizeof(FRocketPassClaimData)) == 0; }
	bool operator!=(const FRocketPassClaimData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassClaimData& other) const { return memcmp(this, &other, sizeof(FRocketPassClaimData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.MTXOnlineProductData
// 0x0044
struct FMTXOnlineProductData
{
	struct FOnlineProductData                          Item;                                          // 0x0000 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           IsOwned : 1;                                   // 0x0040 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FMTXOnlineProductData& other) const { return memcmp(this, &other, sizeof(FMTXOnlineProductData)) == 0; }
	bool operator!=(const FMTXOnlineProductData& other) const { return !(*this == other); }
	bool operator<(const FMTXOnlineProductData& other) const { return memcmp(this, &other, sizeof(FMTXOnlineProductData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassInfo
// 0x000C
struct FRocketPassInfo
{
	int32_t                                            TierLevel;                                     // 0x0000 (0x0004) [0x0000000000002000] (CPF_Transient)
	uint32_t                                           bOwnsPremium : 1;                              // 0x0004 (0x0004) [0x0000000000002000] [0x00000001] (CPF_Transient)
	float                                              XPMultiplier;                                  // 0x0008 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FRocketPassInfo& other) const { return memcmp(this, &other, sizeof(FRocketPassInfo)) == 0; }
	bool operator!=(const FRocketPassInfo& other) const { return !(*this == other); }
	bool operator<(const FRocketPassInfo& other) const { return memcmp(this, &other, sizeof(FRocketPassInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassBundleInfo
// 0x0038
struct FRocketPassBundleInfo
{
	int32_t                                            PurchasableID;                                 // 0x0000 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            KeyCost;                                       // 0x0004 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            OriginalKeyCost;                               // 0x0008 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            OriginalCurrencyCost;                          // 0x000C (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            CurrencyID;                                    // 0x0010 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            CurrencyCost;                                  // 0x0014 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            Tiers;                                         // 0x0018 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            Savings;                                       // 0x001C (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	class UTexture*                                    Image;                                         // 0x0020 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      ImageURL;                                      // 0x0028 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FRocketPassBundleInfo& other) const { return memcmp(this, &other, sizeof(FRocketPassBundleInfo)) == 0; }
	bool operator!=(const FRocketPassBundleInfo& other) const { return !(*this == other); }
	bool operator<(const FRocketPassBundleInfo& other) const { return memcmp(this, &other, sizeof(FRocketPassBundleInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassStore
// 0x0020
struct FRocketPassStore
{
	class TArray<struct FRocketPassBundleInfo>         Tiers;                                         // 0x0000 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FRocketPassBundleInfo>         Bundles;                                       // 0x0010 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FRocketPassStore& other) const { return memcmp(this, &other, sizeof(FRocketPassStore)) == 0; }
	bool operator!=(const FRocketPassStore& other) const { return !(*this == other); }
	bool operator<(const FRocketPassStore& other) const { return memcmp(this, &other, sizeof(FRocketPassStore)) < 0; }
};

// ScriptStruct TAGame._Types_TA.RocketPassPurchasable
// 0x0008
struct FRocketPassPurchasable
{
	int32_t                                            PurchasableID;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FRocketPassPurchasable& other) const { return memcmp(this, &other, sizeof(FRocketPassPurchasable)) == 0; }
	bool operator!=(const FRocketPassPurchasable& other) const { return !(*this == other); }
	bool operator<(const FRocketPassPurchasable& other) const { return memcmp(this, &other, sizeof(FRocketPassPurchasable)) < 0; }
};

// ScriptStruct TAGame._Types_TA.OnlineReward
// 0x0028
struct FOnlineReward
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineXPReward>               RewardDrops;                                   // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineReward& other) const { return memcmp(this, &other, sizeof(FOnlineReward)) == 0; }
	bool operator!=(const FOnlineReward& other) const { return !(*this == other); }
	bool operator<(const FOnlineReward& other) const { return memcmp(this, &other, sizeof(FOnlineReward)) < 0; }
};

// ScriptStruct TAGame._Types_TA.CertifiedStatData
// 0x0058
struct FCertifiedStatData
{
	class TArray<int32_t>                              Thresholds;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      StatName;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Label;                                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           StartTime;                                     // 0x0040 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTime;                                       // 0x0048 (0x0008) [0x0000000000000000]               
	int32_t                                            StatId;                                        // 0x0050 (0x0004) [0x0000000000000000]               
	uint32_t                                           IsTitleStat : 1;                               // 0x0054 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FCertifiedStatData& other) const { return memcmp(this, &other, sizeof(FCertifiedStatData)) == 0; }
	bool operator!=(const FCertifiedStatData& other) const { return !(*this == other); }
	bool operator<(const FCertifiedStatData& other) const { return memcmp(this, &other, sizeof(FCertifiedStatData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.TradeSkipValidation
// 0x0000
struct FTradeSkipValidation
{

	bool operator==(const FTradeSkipValidation& other) const { return memcmp(this, &other, sizeof(FTradeSkipValidation)) == 0; }
	bool operator!=(const FTradeSkipValidation& other) const { return !(*this == other); }
	bool operator<(const FTradeSkipValidation& other) const { return memcmp(this, &other, sizeof(FTradeSkipValidation)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SeasonMatch
// 0x001C
struct FSeasonMatch
{
	int32_t                                            Week;                                          // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Team0;                                         // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Team1;                                         // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Score0;                                        // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Score1;                                        // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Winner;                                        // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bBye : 1;                                      // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FSeasonMatch& other) const { return memcmp(this, &other, sizeof(FSeasonMatch)) == 0; }
	bool operator!=(const FSeasonMatch& other) const { return !(*this == other); }
	bool operator<(const FSeasonMatch& other) const { return memcmp(this, &other, sizeof(FSeasonMatch)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SeasonTeam
// 0x001C
struct FSeasonTeam
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FName                                        LogoAsset;                                     // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            EliminationWeek;                               // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FSeasonTeam& other) const { return memcmp(this, &other, sizeof(FSeasonTeam)) == 0; }
	bool operator!=(const FSeasonTeam& other) const { return !(*this == other); }
	bool operator<(const FSeasonTeam& other) const { return memcmp(this, &other, sizeof(FSeasonTeam)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SeasonPlayerStat
// 0x001C
struct FSeasonPlayerStat
{
	int32_t                                            PlayerIndex;                                   // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      StatName;                                      // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            StatValue;                                     // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FSeasonPlayerStat& other) const { return memcmp(this, &other, sizeof(FSeasonPlayerStat)) == 0; }
	bool operator!=(const FSeasonPlayerStat& other) const { return !(*this == other); }
	bool operator<(const FSeasonPlayerStat& other) const { return memcmp(this, &other, sizeof(FSeasonPlayerStat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SeasonPlayer
// 0x002C
struct FSeasonPlayer
{
	int32_t                                            Team;                                          // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Name;                                          // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Id;                                            // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bBot : 1;                                      // 0x0028 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FSeasonPlayer& other) const { return memcmp(this, &other, sizeof(FSeasonPlayer)) == 0; }
	bool operator!=(const FSeasonPlayer& other) const { return !(*this == other); }
	bool operator<(const FSeasonPlayer& other) const { return memcmp(this, &other, sizeof(FSeasonPlayer)) < 0; }
};

// ScriptStruct TAGame._Types_TA.SeasonTeamRank
// 0x001C
struct FSeasonTeamRank
{
	int32_t                                            Team;                                          // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Wins;                                          // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Losses;                                        // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PointsFor;                                     // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PointsAgainst;                                 // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PointsDifferential;                            // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            EliminationWeek;                               // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FSeasonTeamRank& other) const { return memcmp(this, &other, sizeof(FSeasonTeamRank)) == 0; }
	bool operator!=(const FSeasonTeamRank& other) const { return !(*this == other); }
	bool operator<(const FSeasonTeamRank& other) const { return memcmp(this, &other, sizeof(FSeasonTeamRank)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ReplayHeaderLoadResult
// 0x0010
struct FReplayHeaderLoadResult
{
	class UReplay_TA*                                  Header;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class UError*                                      Error;                                         // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FReplayHeaderLoadResult& other) const { return memcmp(this, &other, sizeof(FReplayHeaderLoadResult)) == 0; }
	bool operator!=(const FReplayHeaderLoadResult& other) const { return !(*this == other); }
	bool operator<(const FReplayHeaderLoadResult& other) const { return memcmp(this, &other, sizeof(FReplayHeaderLoadResult)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProfileAutoCamSettings
// 0x0028
struct FProfileAutoCamSettings
{
	float                                              FOV;                                           // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Height;                                        // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              Distance;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              MoveSpeed;                                     // 0x000C (0x0004) [0x0000000000000000]               
	float                                              MoveSpeedZ;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              RotateSpeed;                                   // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              AerialDistance;                                // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              FocusBlendSpeed;                               // 0x001C (0x0004) [0x0000000000000000]               
	float                                              AerialPrediction;                              // 0x0020 (0x0004) [0x0000000000000000]               
	uint32_t                                           bUseReplayCamera : 1;                          // 0x0024 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bFocusOnGoals : 1;                             // 0x0024 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FProfileAutoCamSettings& other) const { return memcmp(this, &other, sizeof(FProfileAutoCamSettings)) == 0; }
	bool operator!=(const FProfileAutoCamSettings& other) const { return !(*this == other); }
	bool operator<(const FProfileAutoCamSettings& other) const { return memcmp(this, &other, sizeof(FProfileAutoCamSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProfileCameraInputSettings
// 0x0014
struct FProfileCameraInputSettings
{
	uint32_t                                           bInvertSwivelPitch : 1;                        // 0x0000 (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bUnconstrainRotation : 1;                      // 0x0000 (0x0004) [0x0001000000000000] [0x00000002] 
	float                                              CameraAccelRate;                               // 0x0004 (0x0004) [0x0001000000000000]               
	float                                              CameraDecelRate;                               // 0x0008 (0x0004) [0x0001000000000000]               
	uint32_t                                           bFreeLookSmoothing : 1;                        // 0x000C (0x0004) [0x0001000000000000] [0x00000001] 
	float                                              FreeLookSpeed;                                 // 0x0010 (0x0004) [0x0001000000000000]               

	bool operator==(const FProfileCameraInputSettings& other) const { return memcmp(this, &other, sizeof(FProfileCameraInputSettings)) == 0; }
	bool operator!=(const FProfileCameraInputSettings& other) const { return !(*this == other); }
	bool operator<(const FProfileCameraInputSettings& other) const { return memcmp(this, &other, sizeof(FProfileCameraInputSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProfileCameraSettings
// 0x002C
struct FProfileCameraSettings
{
	float                                              FOV;                                           // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Height;                                        // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              Pitch;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              Distance;                                      // 0x000C (0x0004) [0x0000000000000000]               
	float                                              Stiffness;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              SwivelSpeed;                                   // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              TransitionSpeed;                               // 0x0018 (0x0004) [0x0000000000000000]               
	uint32_t                                           bUnconstrainRotation : 1;                      // 0x001C (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bFreeLookSmoothing : 1;                        // 0x001C (0x0004) [0x0001000000000000] [0x00000002] 
	float                                              CameraAccelRate;                               // 0x0020 (0x0004) [0x0001000000000000]               
	float                                              CameraDecelRate;                               // 0x0024 (0x0004) [0x0001000000000000]               
	float                                              FreeLookSpeed;                                 // 0x0028 (0x0004) [0x0001000000000000]               

	bool operator==(const FProfileCameraSettings& other) const { return memcmp(this, &other, sizeof(FProfileCameraSettings)) == 0; }
	bool operator!=(const FProfileCameraSettings& other) const { return !(*this == other); }
	bool operator<(const FProfileCameraSettings& other) const { return memcmp(this, &other, sizeof(FProfileCameraSettings)) < 0; }
};

// ScriptStruct TAGame._Types_TA.StatEventScore
// 0x000C
struct FStatEventScore
{
	class UStatEvent_TA*                               StatEvent;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Score;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FStatEventScore& other) const { return memcmp(this, &other, sizeof(FStatEventScore)) == 0; }
	bool operator!=(const FStatEventScore& other) const { return !(*this == other); }
	bool operator<(const FStatEventScore& other) const { return memcmp(this, &other, sizeof(FStatEventScore)) < 0; }
};

// ScriptStruct TAGame._Types_TA.XPInfo
// 0x0020
struct FXPInfo
{
	int32_t                                            TotalXP;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            XpLevel;                                       // 0x0004 (0x0004) [0x0000000000000000]               
	class FString                                      XPTitle;                                       // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            XPProgressInCurrentLevel;                      // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            XPRequiredForNextLevel;                        // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FXPInfo& other) const { return memcmp(this, &other, sizeof(FXPInfo)) == 0; }
	bool operator!=(const FXPInfo& other) const { return !(*this == other); }
	bool operator<(const FXPInfo& other) const { return memcmp(this, &other, sizeof(FXPInfo)) < 0; }
};

// ScriptStruct TAGame._Types_TA.ProductStat
// 0x0008
struct FProductStat
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Value;                                         // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FProductStat& other) const { return memcmp(this, &other, sizeof(FProductStat)) == 0; }
	bool operator!=(const FProductStat& other) const { return !(*this == other); }
	bool operator<(const FProductStat& other) const { return memcmp(this, &other, sizeof(FProductStat)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PrespawnData
// 0x001C
struct FPrespawnData
{
	uint32_t                                           bPrespawnSet : 1;                              // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0010 (0x000C) [0x0000000000000000]               

	bool operator==(const FPrespawnData& other) const { return memcmp(this, &other, sizeof(FPrespawnData)) == 0; }
	bool operator!=(const FPrespawnData& other) const { return !(*this == other); }
	bool operator<(const FPrespawnData& other) const { return memcmp(this, &other, sizeof(FPrespawnData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemolishInvulnerability
// 0x0018
struct FDemolishInvulnerability
{
	class UObject*                                     ObjectSource;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<EDemolishSource>                      DemolishSources;                               // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDemolishInvulnerability& other) const { return memcmp(this, &other, sizeof(FDemolishInvulnerability)) == 0; }
	bool operator!=(const FDemolishInvulnerability& other) const { return !(*this == other); }
	bool operator<(const FDemolishInvulnerability& other) const { return memcmp(this, &other, sizeof(FDemolishInvulnerability)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemolishData
// 0x0028
struct FDemolishData
{
	class ARBActor_TA*                                 Attacker;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class ACar_TA*                                     Victim;                                        // 0x0008 (0x0008) [0x0000000000000000]               
	struct FVector                                     AttackerVelocity;                              // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     VictimVelocity;                                // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FDemolishData& other) const { return memcmp(this, &other, sizeof(FDemolishData)) == 0; }
	bool operator!=(const FDemolishData& other) const { return !(*this == other); }
	bool operator<(const FDemolishData& other) const { return memcmp(this, &other, sizeof(FDemolishData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemolishDataGoalExplosion
// 0x0008 (0x0028 - 0x0030)
struct FDemolishDataGoalExplosion : FDemolishData
{
	class APRI_TA*                                     GoalExplosionOwner;                            // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FDemolishDataGoalExplosion& other) const { return memcmp(this, &other, sizeof(FDemolishDataGoalExplosion)) == 0; }
	bool operator!=(const FDemolishDataGoalExplosion& other) const { return !(*this == other); }
	bool operator<(const FDemolishDataGoalExplosion& other) const { return memcmp(this, &other, sizeof(FDemolishDataGoalExplosion)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemolishDataExtended
// 0x0014 (0x0030 - 0x0044)
struct FDemolishDataExtended : FDemolishDataGoalExplosion
{
	class APRI_TA*                                     AttackerPRI;                                   // 0x0030 (0x0008) [0x0000000000000000]               
	class AFXActor_X*                                  SelfDemoFX;                                    // 0x0038 (0x0008) [0x0000000000000000]               
	uint32_t                                           bSelfDemolish : 1;                             // 0x0040 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FDemolishDataExtended& other) const { return memcmp(this, &other, sizeof(FDemolishDataExtended)) == 0; }
	bool operator!=(const FDemolishDataExtended& other) const { return !(*this == other); }
	bool operator<(const FDemolishDataExtended& other) const { return memcmp(this, &other, sizeof(FDemolishDataExtended)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemolishData2
// 0x0008 (0x0028 - 0x0030)
struct FDemolishData2 : FDemolishData
{
	class AFXActor_X*                                  CustomDemoFX;                                  // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FDemolishData2& other) const { return memcmp(this, &other, sizeof(FDemolishData2)) == 0; }
	bool operator!=(const FDemolishData2& other) const { return !(*this == other); }
	bool operator<(const FDemolishData2& other) const { return memcmp(this, &other, sizeof(FDemolishData2)) < 0; }
};

// ScriptStruct TAGame._Types_TA.UISavedKeyValue
// 0x0018
struct FUISavedKeyValue
{
	class FName                                        Key;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Value;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUISavedKeyValue& other) const { return memcmp(this, &other, sizeof(FUISavedKeyValue)) == 0; }
	bool operator!=(const FUISavedKeyValue& other) const { return !(*this == other); }
	bool operator<(const FUISavedKeyValue& other) const { return memcmp(this, &other, sizeof(FUISavedKeyValue)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlaylistMapPrefs
// 0x000C (0x0020 - 0x002C)
struct FPlaylistMapPrefs : FMapPrefs
{
	class FName                                        Playlist;                                      // 0x0020 (0x0008) [0x0000000000000000]               
	uint32_t                                           bOverrideGlobal : 1;                           // 0x0028 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FPlaylistMapPrefs& other) const { return memcmp(this, &other, sizeof(FPlaylistMapPrefs)) == 0; }
	bool operator!=(const FPlaylistMapPrefs& other) const { return !(*this == other); }
	bool operator<(const FPlaylistMapPrefs& other) const { return memcmp(this, &other, sizeof(FPlaylistMapPrefs)) < 0; }
};

// ScriptStruct TAGame._Types_TA.NetBucketMetrics
// 0x0014
struct FNetBucketMetrics
{
	int32_t                                            MinPossibleValue;                              // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              TotalSeconds;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              AvgRecordedValue;                              // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              MaxRecordedValue;                              // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FNetBucketMetrics& other) const { return memcmp(this, &other, sizeof(FNetBucketMetrics)) == 0; }
	bool operator!=(const FNetBucketMetrics& other) const { return !(*this == other); }
	bool operator<(const FNetBucketMetrics& other) const { return memcmp(this, &other, sizeof(FNetBucketMetrics)) < 0; }
};

// ScriptStruct TAGame._Types_TA.FPSBucketMetrics
// 0x0020
struct FFPSBucketMetrics
{
	int32_t                                            FPS;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            FrameCount;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              PercentTime;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              AverageGameThreadTime;                         // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              AverageRenderThreadTime;                       // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              AverageGPUFrameTime;                           // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              UndockedAverageResolutionIndex;                // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DockedAverageResolutionIndex;                  // 0x001C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFPSBucketMetrics& other) const { return memcmp(this, &other, sizeof(FFPSBucketMetrics)) == 0; }
	bool operator!=(const FFPSBucketMetrics& other) const { return !(*this == other); }
	bool operator<(const FFPSBucketMetrics& other) const { return memcmp(this, &other, sizeof(FFPSBucketMetrics)) < 0; }
};

// ScriptStruct TAGame._Types_TA.BodyToEngineAudioPair
// 0x0010
struct FBodyToEngineAudioPair
{
	class UProduct_TA*                                 Body;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class UProduct_TA*                                 EngineAudio;                                   // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FBodyToEngineAudioPair& other) const { return memcmp(this, &other, sizeof(FBodyToEngineAudioPair)) == 0; }
	bool operator!=(const FBodyToEngineAudioPair& other) const { return !(*this == other); }
	bool operator<(const FBodyToEngineAudioPair& other) const { return memcmp(this, &other, sizeof(FBodyToEngineAudioPair)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PartyUpMergeError
// 0x0098
struct FPartyUpMergeError
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                LeaderID;                                      // 0x0048 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class UError*                                      Error;                                         // 0x0090 (0x0008) [0x0000000000000000]               

	bool operator==(const FPartyUpMergeError& other) const { return memcmp(this, &other, sizeof(FPartyUpMergeError)) == 0; }
	bool operator!=(const FPartyUpMergeError& other) const { return !(*this == other); }
	bool operator<(const FPartyUpMergeError& other) const { return memcmp(this, &other, sizeof(FPartyUpMergeError)) < 0; }
};

// ScriptStruct TAGame._Types_TA.AutoFlipData
// 0x0008
struct FAutoFlipData
{
	float                                              Torque;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Force;                                         // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAutoFlipData& other) const { return memcmp(this, &other, sizeof(FAutoFlipData)) == 0; }
	bool operator!=(const FAutoFlipData& other) const { return !(*this == other); }
	bool operator<(const FAutoFlipData& other) const { return memcmp(this, &other, sizeof(FAutoFlipData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.StickyForceData
// 0x0008
struct FStickyForceData
{
	float                                              Ground;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Wall;                                          // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FStickyForceData& other) const { return memcmp(this, &other, sizeof(FStickyForceData)) == 0; }
	bool operator!=(const FStickyForceData& other) const { return !(*this == other); }
	bool operator<(const FStickyForceData& other) const { return memcmp(this, &other, sizeof(FStickyForceData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.WaveParams
// 0x0008
struct FWaveParams
{
	float                                              Frequency;                                     // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Amplitude;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWaveParams& other) const { return memcmp(this, &other, sizeof(FWaveParams)) == 0; }
	bool operator!=(const FWaveParams& other) const { return !(*this == other); }
	bool operator<(const FWaveParams& other) const { return memcmp(this, &other, sizeof(FWaveParams)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PersonaDataId
// 0x0058
struct FPersonaDataId
{
	struct FUniqueNetId                                PersonaId;                                     // 0x0000 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      EpicPUID;                                      // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPersonaDataId& other) const { return memcmp(this, &other, sizeof(FPersonaDataId)) == 0; }
	bool operator!=(const FPersonaDataId& other) const { return !(*this == other); }
	bool operator<(const FPersonaDataId& other) const { return memcmp(this, &other, sizeof(FPersonaDataId)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PaintWithOverride
// 0x0018
struct FPaintWithOverride
{
	class UProductPaint_TA*                            PaintToOverride;                               // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UProductOverride_TA*>           Overrides;                                     // 0x0008 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)

	bool operator==(const FPaintWithOverride& other) const { return memcmp(this, &other, sizeof(FPaintWithOverride)) == 0; }
	bool operator!=(const FPaintWithOverride& other) const { return !(*this == other); }
	bool operator<(const FPaintWithOverride& other) const { return memcmp(this, &other, sizeof(FPaintWithOverride)) < 0; }
};

// ScriptStruct TAGame._Types_TA.DemoSpawnSelectionData
// 0x002C
struct FDemoSpawnSelectionData
{
	EDemoSpawnPreference                               SpawnPreference;                               // 0x0000 (0x0001) [0x0000000000000000]               
	EDemoSelectionState                                SelectionState;                                // 0x0001 (0x0001) [0x0000000000000000]               
	int32_t                                            PercentageTimeLeft;                            // 0x0004 (0x0004) [0x0000000000000000]               
	class AActor*                                      SpawnActor;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            SpawnIndex;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	struct FVector                                     SpawnLocation;                                 // 0x0014 (0x000C) [0x0000000000000000]               
	struct FRotator                                    SpawnRotation;                                 // 0x0020 (0x000C) [0x0000000000000000]               

	bool operator==(const FDemoSpawnSelectionData& other) const { return memcmp(this, &other, sizeof(FDemoSpawnSelectionData)) == 0; }
	bool operator!=(const FDemoSpawnSelectionData& other) const { return !(*this == other); }
	bool operator<(const FDemoSpawnSelectionData& other) const { return memcmp(this, &other, sizeof(FDemoSpawnSelectionData)) < 0; }
};

// ScriptStruct TAGame._Types_TA.PlayerActorIDPair
// 0x0050
struct FPlayerActorIDPair
{
	int32_t                                            ActorID;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                PlayerID;                                      // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerActorIDPair& other) const { return memcmp(this, &other, sizeof(FPlayerActorIDPair)) == 0; }
	bool operator!=(const FPlayerActorIDPair& other) const { return !(*this == other); }
	bool operator<(const FPlayerActorIDPair& other) const { return memcmp(this, &other, sizeof(FPlayerActorIDPair)) < 0; }
};

// ScriptStruct TAGame.GFxData_Mutators_TA.CustomGameSetting
// 0x0070
struct FCustomGameSetting
{
	class FString                                      MutatorCategoryName;                           // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      MutatorCategoryDesc;                           // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      SettingsName;                                  // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            SettingIndex;                                  // 0x0030 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            DefaultIndex;                                  // 0x0034 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FName                                        InternalName;                                  // 0x0038 (0x0008) [0x0000000000000000]               
	int32_t                                            MutatorGroupID;                                // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            GameSettingCategoryIndex;                      // 0x0044 (0x0004) [0x0000000000000000]               
	class TArray<class FName>                          SettingNameExplicit;                           // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bPresetLocked : 1;                             // 0x0058 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	int32_t                                            RowID;                                         // 0x005C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<class FString>                        PreviouslyBlockedCategories;                   // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCustomGameSetting& other) const { return memcmp(this, &other, sizeof(FCustomGameSetting)) == 0; }
	bool operator!=(const FCustomGameSetting& other) const { return !(*this == other); }
	bool operator<(const FCustomGameSetting& other) const { return memcmp(this, &other, sizeof(FCustomGameSetting)) < 0; }
};

// ScriptStruct TAGame.GFxData_Mutators_TA.ModeMapPair
// 0x000C
struct FModeMapPair
{
	int32_t                                            GameMode;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        MapName;                                       // 0x0004 (0x0008) [0x0000000000000000]               

	bool operator==(const FModeMapPair& other) const { return memcmp(this, &other, sizeof(FModeMapPair)) == 0; }
	bool operator!=(const FModeMapPair& other) const { return !(*this == other); }
	bool operator<(const FModeMapPair& other) const { return memcmp(this, &other, sizeof(FModeMapPair)) < 0; }
};

// ScriptStruct TAGame.GFxData_Mutators_TA.OnlineFreeplayOption
// 0x0048
struct FOnlineFreeplayOption
{
	int32_t                                            OptionIndex;                                   // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      LocalizationGroup;                             // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LocalizationPackage;                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LocalizationName;                              // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LocalizationDescription;                       // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineFreeplayOption& other) const { return memcmp(this, &other, sizeof(FOnlineFreeplayOption)) == 0; }
	bool operator!=(const FOnlineFreeplayOption& other) const { return !(*this == other); }
	bool operator<(const FOnlineFreeplayOption& other) const { return memcmp(this, &other, sizeof(FOnlineFreeplayOption)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ItemShopNotificationData
// 0x0048
struct FItemShopNotificationData
{
	int32_t                                            ShopNotificationID;                            // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ShopItemCostID;                                // 0x0004 (0x0004) [0x0000000000000000]               
	uint64_t                                           StartTime;                                     // 0x0008 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTime;                                       // 0x0010 (0x0008) [0x0000000000000000]               
	class FString                                      ImageURL;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Title;                                         // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineProductData>            DeliverableProducts;                           // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FItemShopNotificationData& other) const { return memcmp(this, &other, sizeof(FItemShopNotificationData)) == 0; }
	bool operator!=(const FItemShopNotificationData& other) const { return !(*this == other); }
	bool operator<(const FItemShopNotificationData& other) const { return memcmp(this, &other, sizeof(FItemShopNotificationData)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopCurrencyInfo
// 0x0008
struct FShopCurrencyInfo
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Amount;                                        // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FShopCurrencyInfo& other) const { return memcmp(this, &other, sizeof(FShopCurrencyInfo)) == 0; }
	bool operator!=(const FShopCurrencyInfo& other) const { return !(*this == other); }
	bool operator<(const FShopCurrencyInfo& other) const { return memcmp(this, &other, sizeof(FShopCurrencyInfo)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.DestructionProductValue
// 0x0020
struct FDestructionProductValue
{
	struct FProductInstanceID                          ProductInstanceID;                             // 0x0000 (0x0010) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FShopCurrencyInfo>             Value;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FDestructionProductValue& other) const { return memcmp(this, &other, sizeof(FDestructionProductValue)) == 0; }
	bool operator!=(const FDestructionProductValue& other) const { return !(*this == other); }
	bool operator<(const FDestructionProductValue& other) const { return memcmp(this, &other, sizeof(FDestructionProductValue)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopData
// 0x0058
struct FShopData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Name;                                          // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Title;                                         // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Type;                                          // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           StartDate;                                     // 0x0038 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndDate;                                       // 0x0040 (0x0008) [0x0000000000000000]               
	class FString                                      LogoURL;                                       // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopData& other) const { return memcmp(this, &other, sizeof(FShopData)) == 0; }
	bool operator!=(const FShopData& other) const { return !(*this == other); }
	bool operator<(const FShopData& other) const { return memcmp(this, &other, sizeof(FShopData)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopDeliverable
// 0x0060
struct FShopDeliverable
{
	int32_t                                            Count;                                         // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	struct FProductInstanceID                          Id;                                            // 0x0008 (0x0010) [0x0000000040000000] (CPF_DataBinding)
	struct FProductHashID                              HashID;                                        // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           IsOwned : 1;                                   // 0x001C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bOwnedUntradeable : 1;                         // 0x001C (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bIsInjectedProduct : 1;                        // 0x001C (0x0004) [0x0000000000000000] [0x00000004] 
	struct FOnlineProductData                          Product;                                       // 0x0020 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopDeliverable& other) const { return memcmp(this, &other, sizeof(FShopDeliverable)) == 0; }
	bool operator!=(const FShopDeliverable& other) const { return !(*this == other); }
	bool operator<(const FShopDeliverable& other) const { return memcmp(this, &other, sizeof(FShopDeliverable)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopPrice
// 0x0008
struct FShopPrice
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Amount;                                        // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FShopPrice& other) const { return memcmp(this, &other, sizeof(FShopPrice)) == 0; }
	bool operator!=(const FShopPrice& other) const { return !(*this == other); }
	bool operator<(const FShopPrice& other) const { return memcmp(this, &other, sizeof(FShopPrice)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopDiscount
// 0x0030
struct FShopDiscount
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            ShopItemCostID;                                // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           StartDate;                                     // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           EndDate;                                       // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FShopPrice>                    Price;                                         // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Quantity;                                      // 0x0028 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           IsProrated : 1;                                // 0x002C (0x0004) [0x0000000040000000] [0x100000001] (CPF_DataBinding)

	bool operator==(const FShopDiscount& other) const { return memcmp(this, &other, sizeof(FShopDiscount)) == 0; }
	bool operator!=(const FShopDiscount& other) const { return !(*this == other); }
	bool operator<(const FShopDiscount& other) const { return memcmp(this, &other, sizeof(FShopDiscount)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopCost
// 0x0069
struct FShopCost
{
	int32_t                                            ShopItemCostID;                                // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FShopPrice>                    Price;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	struct FShopDiscount                               Discount;                                      // 0x0018 (0x0030) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint64_t                                           StartDate;                                     // 0x0048 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           EndDate;                                       // 0x0050 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FShopDiscount>                 BulkDiscounts;                                 // 0x0058 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	EItemDisplayType                                   DisplayTypeID;                                 // 0x0068 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FShopCost& other) const { return memcmp(this, &other, sizeof(FShopCost)) == 0; }
	bool operator!=(const FShopCost& other) const { return !(*this == other); }
	bool operator<(const FShopCost& other) const { return memcmp(this, &other, sizeof(FShopCost)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.OnlineShopAttribute
// 0x0018
struct FOnlineShopAttribute
{
	class FName                                        Key;                                           // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Value;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FOnlineShopAttribute& other) const { return memcmp(this, &other, sizeof(FOnlineShopAttribute)) == 0; }
	bool operator!=(const FOnlineShopAttribute& other) const { return !(*this == other); }
	bool operator<(const FOnlineShopAttribute& other) const { return memcmp(this, &other, sizeof(FOnlineShopAttribute)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopItem
// 0x00E8
struct FShopItem
{
	int32_t                                            ShopItemID;                                    // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           Purchasable : 1;                               // 0x0004 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	int32_t                                            PurchasedQuantity;                             // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            MaxQuantityPerPlayer;                          // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           StartDate;                                     // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           EndDate;                                       // 0x0018 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FShopDeliverable>              DeliverableProducts;                           // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<struct FShopCurrencyInfo>             DeliverableCurrencies;                         // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<struct FShopCost>                     Costs;                                         // 0x0040 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<class FString>                        FeaturedCollections;                           // 0x0050 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<int32_t>                              ShopItemLocations;                             // 0x0060 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Title;                                         // 0x0070 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0080 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      disclaimer;                                    // 0x0090 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<struct FOnlineShopAttribute>          Attributes;                                    // 0x00A0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ImageURL;                                      // 0x00B0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    ItemTexture;                                   // 0x00C0 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bOwnsAllUntradeableProducts : 1;               // 0x00C8 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bOwnsAllDeliverables : 1;                      // 0x00C8 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bIsProrated : 1;                               // 0x00C8 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	int32_t                                            BuyingProductCount;                            // 0x00CC (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            NonInjectedBuyingProductCount;                 // 0x00D0 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<int32_t>                              IgnoreOfflineProductIDs;                       // 0x00D8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopItem& other) const { return memcmp(this, &other, sizeof(FShopItem)) == 0; }
	bool operator!=(const FShopItem& other) const { return !(*this == other); }
	bool operator<(const FShopItem& other) const { return memcmp(this, &other, sizeof(FShopItem)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopCatalogue
// 0x0018
struct FShopCatalogue
{
	int32_t                                            ShopID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FShopItem>                     ShopItems;                                     // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopCatalogue& other) const { return memcmp(this, &other, sizeof(FShopCatalogue)) == 0; }
	bool operator!=(const FShopCatalogue& other) const { return !(*this == other); }
	bool operator<(const FShopCatalogue& other) const { return memcmp(this, &other, sizeof(FShopCatalogue)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.CurrencyProductData
// 0x0010
struct U_ShopTypes_TA_FCurrencyProductData
{
	class UProduct_TA*                                 Product;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const U_ShopTypes_TA_FCurrencyProductData& other) const { return memcmp(this, &other, sizeof(U_ShopTypes_TA_FCurrencyProductData)) == 0; }
	bool operator!=(const U_ShopTypes_TA_FCurrencyProductData& other) const { return !(*this == other); }
	bool operator<(const U_ShopTypes_TA_FCurrencyProductData& other) const { return memcmp(this, &other, sizeof(U_ShopTypes_TA_FCurrencyProductData)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopCurrency
// 0x0058
struct FShopCurrency
{
	ECurrency                                          Type;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	int32_t                                            Id;                                            // 0x0004 (0x0004) [0x0000000000000000]               
	class UTexture*                                    SmallImage;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	class UTexture*                                    LargeImage;                                    // 0x0010 (0x0008) [0x0000000000000000]               
	int32_t                                            Amount;                                        // 0x0018 (0x0004) [0x0000000000000000]               
	class FString                                      Name;                                          // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LocalizedName;                                 // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCanBeTraded : 1;                              // 0x0040 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            TradeHold;                                     // 0x0044 (0x0004) [0x0000000000000000]               
	struct U_ShopTypes_TA_FCurrencyProductData         ProductData;                                   // 0x0048 (0x0010) [0x0000000000000000]               

	bool operator==(const FShopCurrency& other) const { return memcmp(this, &other, sizeof(FShopCurrency)) == 0; }
	bool operator!=(const FShopCurrency& other) const { return !(*this == other); }
	bool operator<(const FShopCurrency& other) const { return memcmp(this, &other, sizeof(FShopCurrency)) < 0; }
};

// ScriptStruct TAGame._ShopTypes_TA.ShopCurrencyData
// 0x0008
struct FShopCurrencyData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Amount;                                        // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FShopCurrencyData& other) const { return memcmp(this, &other, sizeof(FShopCurrencyData)) == 0; }
	bool operator!=(const FShopCurrencyData& other) const { return !(*this == other); }
	bool operator<(const FShopCurrencyData& other) const { return memcmp(this, &other, sizeof(FShopCurrencyData)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourPlayer
// 0x0060
struct FTourPlayer
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PlayerName;                                    // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UTexture*                                    Avatar;                                        // 0x0058 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FTourPlayer& other) const { return memcmp(this, &other, sizeof(FTourPlayer)) == 0; }
	bool operator!=(const FTourPlayer& other) const { return !(*this == other); }
	bool operator<(const FTourPlayer& other) const { return memcmp(this, &other, sizeof(FTourPlayer)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourReward
// 0x0014
struct FTourReward
{
	class TArray<struct FOnlineProductData>            Rewards;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Placement;                                     // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FTourReward& other) const { return memcmp(this, &other, sizeof(FTourReward)) == 0; }
	bool operator!=(const FTourReward& other) const { return !(*this == other); }
	bool operator<(const FTourReward& other) const { return memcmp(this, &other, sizeof(FTourReward)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourTeam
// 0x0044
struct FTourTeam
{
	uint64_t                                           TeamID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	struct FCustomMatchTeamSettings                    Settings;                                      // 0x0008 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourPlayer>                   Players;                                       // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           Seed;                                          // 0x0038 (0x0008) [0x0000000000000000]               
	int32_t                                            Difficulty;                                    // 0x0040 (0x0004) [0x0000000000000000]               

	bool operator==(const FTourTeam& other) const { return memcmp(this, &other, sizeof(FTourTeam)) == 0; }
	bool operator!=(const FTourTeam& other) const { return !(*this == other); }
	bool operator<(const FTourTeam& other) const { return memcmp(this, &other, sizeof(FTourTeam)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourMatchGame
// 0x0018
struct FTourMatchGame
{
	int32_t                                            GameTimeSeconds;                               // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bOverTime : 1;                                 // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bAborted : 1;                                  // 0x0004 (0x0004) [0x0000000000000000] [0x00000002] 
	uint64_t                                           Winner;                                        // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            Scores[2];                                     // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FTourMatchGame& other) const { return memcmp(this, &other, sizeof(FTourMatchGame)) == 0; }
	bool operator!=(const FTourMatchGame& other) const { return !(*this == other); }
	bool operator<(const FTourMatchGame& other) const { return memcmp(this, &other, sizeof(FTourMatchGame)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourPlayerStats
// 0x0060
struct FTourPlayerStats
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TeamNum;                                       // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            Score;                                         // 0x004C (0x0004) [0x0000000000000000]               
	int32_t                                            Saves;                                         // 0x0050 (0x0004) [0x0000000000000000]               
	int32_t                                            Shots;                                         // 0x0054 (0x0004) [0x0000000000000000]               
	int32_t                                            Goals;                                         // 0x0058 (0x0004) [0x0000000000000000]               
	int32_t                                            Assists;                                       // 0x005C (0x0004) [0x0000000000000000]               

	bool operator==(const FTourPlayerStats& other) const { return memcmp(this, &other, sizeof(FTourPlayerStats)) == 0; }
	bool operator!=(const FTourPlayerStats& other) const { return !(*this == other); }
	bool operator<(const FTourPlayerStats& other) const { return memcmp(this, &other, sizeof(FTourPlayerStats)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourMatch
// 0x0030
struct FTourMatch
{
	int32_t                                            MatchID;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	uint64_t                                           Teams[2];                                      // 0x0008 (0x0010) [0x0000000000000000]               
	uint64_t                                           Winner;                                        // 0x0018 (0x0008) [0x0000000000000000]               
	class TArray<struct FTourMatchGame>                Games;                                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourMatch& other) const { return memcmp(this, &other, sizeof(FTourMatch)) == 0; }
	bool operator!=(const FTourMatch& other) const { return !(*this == other); }
	bool operator<(const FTourMatch& other) const { return memcmp(this, &other, sizeof(FTourMatch)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.IntPair
// 0x0008
struct FIntPair
{
	int32_t                                            A;                                             // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            B;                                             // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FIntPair& other) const { return memcmp(this, &other, sizeof(FIntPair)) == 0; }
	bool operator!=(const FIntPair& other) const { return !(*this == other); }
	bool operator<(const FIntPair& other) const { return memcmp(this, &other, sizeof(FIntPair)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.QWORDPair
// 0x0010
struct FQWORDPair
{
	uint64_t                                           A;                                             // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           B;                                             // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FQWORDPair& other) const { return memcmp(this, &other, sizeof(FQWORDPair)) == 0; }
	bool operator!=(const FQWORDPair& other) const { return !(*this == other); }
	bool operator<(const FQWORDPair& other) const { return memcmp(this, &other, sizeof(FQWORDPair)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourMatchNode
// 0x002C
struct FTourMatchNode
{
	int32_t                                            MatchID;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Round;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Order;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	struct FQWORDPair                                  Teams;                                         // 0x0010 (0x0010) [0x0000000000000000]               
	int32_t                                            NextMatchID;                                   // 0x0020 (0x0004) [0x0000000000000000]               
	struct FIntPair                                    PrevMatch;                                     // 0x0024 (0x0008) [0x0000000000000000]               

	bool operator==(const FTourMatchNode& other) const { return memcmp(this, &other, sizeof(FTourMatchNode)) == 0; }
	bool operator!=(const FTourMatchNode& other) const { return !(*this == other); }
	bool operator<(const FTourMatchNode& other) const { return memcmp(this, &other, sizeof(FTourMatchNode)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourPlacementInfo
// 0x0070
struct FTourPlacementInfo
{
	int32_t                                            Placement;                                     // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Name;                                          // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Value;                                         // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           TeamID;                                        // 0x0020 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	struct FUniqueNetId                                PlayerID;                                      // 0x0028 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FTourPlacementInfo& other) const { return memcmp(this, &other, sizeof(FTourPlacementInfo)) == 0; }
	bool operator!=(const FTourPlacementInfo& other) const { return !(*this == other); }
	bool operator<(const FTourPlacementInfo& other) const { return memcmp(this, &other, sizeof(FTourPlacementInfo)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourLeaderboard
// 0x0040
struct FTourLeaderboard
{
	class TArray<struct FTourPlacementInfo>            TeamGoals;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourPlacementInfo>            PlayerGoals;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourPlacementInfo>            PlayerAssists;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourPlacementInfo>            PlayerSaves;                                   // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourLeaderboard& other) const { return memcmp(this, &other, sizeof(FTourLeaderboard)) == 0; }
	bool operator!=(const FTourLeaderboard& other) const { return !(*this == other); }
	bool operator<(const FTourLeaderboard& other) const { return memcmp(this, &other, sizeof(FTourLeaderboard)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourMatchPlayerStats
// 0x0064
struct FTourMatchPlayerStats
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	struct FUniqueNetId                                Id;                                            // 0x0008 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Score;                                         // 0x0050 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Goals;                                         // 0x0054 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Assists;                                       // 0x0058 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Saves;                                         // 0x005C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Shots;                                         // 0x0060 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTourMatchPlayerStats& other) const { return memcmp(this, &other, sizeof(FTourMatchPlayerStats)) == 0; }
	bool operator!=(const FTourMatchPlayerStats& other) const { return !(*this == other); }
	bool operator<(const FTourMatchPlayerStats& other) const { return memcmp(this, &other, sizeof(FTourMatchPlayerStats)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourMatchTeamDetails
// 0x0028
struct FTourMatchTeamDetails
{
	uint64_t                                           TeamID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<int32_t>                              GoalsPerGame;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourMatchPlayerStats>         CumulativePlayerStats;                         // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourMatchTeamDetails& other) const { return memcmp(this, &other, sizeof(FTourMatchTeamDetails)) == 0; }
	bool operator!=(const FTourMatchTeamDetails& other) const { return !(*this == other); }
	bool operator<(const FTourMatchTeamDetails& other) const { return memcmp(this, &other, sizeof(FTourMatchTeamDetails)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourBracket
// 0x0078
struct FTourBracket
{
	uint64_t                                           TournamentID;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FTourTeam>                     Teams;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourMatch>                    Matches;                                       // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FTourLeaderboard                            Leaderboard;                                   // 0x0028 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FShopCurrencyInfo>             CurrentPayouts;                                // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourBracket& other) const { return memcmp(this, &other, sizeof(FTourBracket)) == 0; }
	bool operator!=(const FTourBracket& other) const { return !(*this == other); }
	bool operator<(const FTourBracket& other) const { return memcmp(this, &other, sizeof(FTourBracket)) < 0; }
};

// ScriptStruct TAGame.CameraState_PodiumSpotlight_TA.CachedPodiumCar
// 0x0018
struct FCachedPodiumCar
{
	class ACar_TA*                                     Car;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	uint32_t                                           bHasPostMatchCelebration : 1;                  // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FCachedPodiumCar& other) const { return memcmp(this, &other, sizeof(FCachedPodiumCar)) == 0; }
	bool operator!=(const FCachedPodiumCar& other) const { return !(*this == other); }
	bool operator<(const FCachedPodiumCar& other) const { return memcmp(this, &other, sizeof(FCachedPodiumCar)) < 0; }
};

// ScriptStruct TAGame.Car_KnockOut_TA.PendingHit
// 0x001C
struct FPendingHit
{
	class ACar_KnockOut_TA*                            Attacker;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     HitDirection;                                  // 0x0008 (0x000C) [0x0000000000000000]               
	float                                              HitSpeed;                                      // 0x0014 (0x0004) [0x0000000000000000]               
	uint32_t                                           bHeavyAttack : 1;                              // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FPendingHit& other) const { return memcmp(this, &other, sizeof(FPendingHit)) == 0; }
	bool operator!=(const FPendingHit& other) const { return !(*this == other); }
	bool operator<(const FPendingHit& other) const { return memcmp(this, &other, sizeof(FPendingHit)) < 0; }
};

// ScriptStruct TAGame.CarMeshComponent_TA.WheelSkelControlSet
// 0x0020
struct FWheelSkelControlSet
{
	class UWheel_TA*                                   Wheel;                                         // 0x0000 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class USkelControlSingleBone*                      TranslationControl;                            // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USkelControlSingleBone*                      SteerControl;                                  // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USkelControlSingleBone*                      RollControl;                                   // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWheelSkelControlSet& other) const { return memcmp(this, &other, sizeof(FWheelSkelControlSet)) == 0; }
	bool operator!=(const FWheelSkelControlSet& other) const { return !(*this == other); }
	bool operator<(const FWheelSkelControlSet& other) const { return memcmp(this, &other, sizeof(FWheelSkelControlSet)) < 0; }
};

// ScriptStruct TAGame.CodeRedeemer_TA.PendingCodeRedemption
// 0x0018
struct FPendingCodeRedemption
{
	class UOnlinePlayer_TA*                            OnlinePlayer;                                  // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	class FString                                      Code;                                          // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPendingCodeRedemption& other) const { return memcmp(this, &other, sizeof(FPendingCodeRedemption)) == 0; }
	bool operator!=(const FPendingCodeRedemption& other) const { return !(*this == other); }
	bool operator<(const FPendingCodeRedemption& other) const { return memcmp(this, &other, sizeof(FPendingCodeRedemption)) < 0; }
};

// ScriptStruct TAGame.CrumbTrails_TA.CrumbTrailData
// 0x0058
struct FCrumbTrailData
{
	class FName                                        CrumbTrailId;                                  // 0x0000 (0x0008) [0x0001000000000000]               
	class TArray<class FName>                          CrumbNames;                                    // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FName                                        MenuTreeTrailEnd;                              // 0x0018 (0x0008) [0x0001000000000000]               
	class TArray<class UTriggerClump_TA*>              ActivationTriggers;                            // 0x0020 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class TArray<class UTriggerClump_TA*>              CompletionOverride;                            // 0x0030 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCompleteOnlyWhenActive : 1;                   // 0x0040 (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bRepeatable : 1;                               // 0x0040 (0x0004) [0x0001000000000000] [0x00000002] 
	uint32_t                                           bManualStart : 1;                              // 0x0040 (0x0004) [0x0001000000000000] [0x00000004] 
	class UTriggerCondition_TA*                        ActivationCondition;                           // 0x0048 (0x0008) [0x0001000000002000] (CPF_Transient)
	class UTriggerCondition_TA*                        CompletionCondition;                           // 0x0050 (0x0008) [0x0001000000002000] (CPF_Transient)

	bool operator==(const FCrumbTrailData& other) const { return memcmp(this, &other, sizeof(FCrumbTrailData)) == 0; }
	bool operator!=(const FCrumbTrailData& other) const { return !(*this == other); }
	bool operator<(const FCrumbTrailData& other) const { return memcmp(this, &other, sizeof(FCrumbTrailData)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceManager_TA.VoiceRoomToken
// 0x0068
struct FVoiceRoomToken
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      ClientBaseUrl;                                 // 0x0048 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Token;                                         // 0x0058 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVoiceRoomToken& other) const { return memcmp(this, &other, sizeof(FVoiceRoomToken)) == 0; }
	bool operator!=(const FVoiceRoomToken& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomToken& other) const { return memcmp(this, &other, sizeof(FVoiceRoomToken)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceManager_TA.MappedRoomMember
// 0x0058
struct FMappedRoomMember
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      EpicAccountId;                                 // 0x0048 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMappedRoomMember& other) const { return memcmp(this, &other, sizeof(FMappedRoomMember)) == 0; }
	bool operator!=(const FMappedRoomMember& other) const { return !(*this == other); }
	bool operator<(const FMappedRoomMember& other) const { return memcmp(this, &other, sizeof(FMappedRoomMember)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceManager_TA.VoiceRoom
// 0x0031
struct FVoiceRoom
{
	class FString                                      RoomName;                                      // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class TArray<struct FVoiceRoomToken>               Tokens;                                        // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMappedRoomMember>             Members;                                       // 0x0020 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	EVoiceRoomType                                     RoomType;                                      // 0x0030 (0x0001) [0x0001000000000000]               

	bool operator==(const FVoiceRoom& other) const { return memcmp(this, &other, sizeof(FVoiceRoom)) == 0; }
	bool operator!=(const FVoiceRoom& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoom& other) const { return memcmp(this, &other, sizeof(FVoiceRoom)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceSettingsSave_TA.PlatformAudioDevices
// 0x0021
struct FPlatformAudioDevices
{
	class FString                                      InputDeviceId;                                 // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      OutputDeviceId;                                // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	EOnlinePlatform                                    Platform;                                      // 0x0020 (0x0001) [0x0001000000000000]               

	bool operator==(const FPlatformAudioDevices& other) const { return memcmp(this, &other, sizeof(FPlatformAudioDevices)) == 0; }
	bool operator!=(const FPlatformAudioDevices& other) const { return !(*this == other); }
	bool operator<(const FPlatformAudioDevices& other) const { return memcmp(this, &other, sizeof(FPlatformAudioDevices)) < 0; }
};

// ScriptStruct TAGame.EpicAccountSave_TA.EpicConvertFriendsSaveData
// 0x0014
struct FEpicConvertFriendsSaveData
{
	EOnlinePlatform                                    Platform;                                      // 0x0000 (0x0001) [0x0000000000000000]               
	uint64_t                                           LastPromptTime;                                // 0x0008 (0x0008) [0x0000000000000000]               
	uint32_t                                           bConvertPlatformFriends : 1;                   // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bPromptedForConversion : 1;                    // 0x0010 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FEpicConvertFriendsSaveData& other) const { return memcmp(this, &other, sizeof(FEpicConvertFriendsSaveData)) == 0; }
	bool operator!=(const FEpicConvertFriendsSaveData& other) const { return !(*this == other); }
	bool operator<(const FEpicConvertFriendsSaveData& other) const { return memcmp(this, &other, sizeof(FEpicConvertFriendsSaveData)) < 0; }
};

// ScriptStruct TAGame.FirstTimeExperienceManager_TA.FTEGroup
// 0x0048
struct FFTEGroup
{
	class FName                                        GroupName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      RequirementInfo;                               // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UTriggerClump_TA*>              TriggerClumps;                                 // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCanBeDoneAgain : 1;                           // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 
	EFTELegacyGroupType                                GroupUserType;                                 // 0x002C (0x0001) [0x0000000000000000]               
	int32_t                                            GroupVersion;                                  // 0x0030 (0x0004) [0x0000000000000000]               
	class TArray<class FName>                          Checkpoints;                                   // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFTEGroup& other) const { return memcmp(this, &other, sizeof(FFTEGroup)) == 0; }
	bool operator!=(const FFTEGroup& other) const { return !(*this == other); }
	bool operator<(const FFTEGroup& other) const { return memcmp(this, &other, sizeof(FFTEGroup)) < 0; }
};

// ScriptStruct TAGame.FirstTimeExperienceSave_TA.CompletedFTEInfo
// 0x0024
struct FCompletedFTEInfo
{
	class FName                                        GroupName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	uint32_t                                           bHasCompletedGroup : 1;                        // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<class FName>                          CompletedCheckpoints;                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            GroupVersion;                                  // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FCompletedFTEInfo& other) const { return memcmp(this, &other, sizeof(FCompletedFTEInfo)) == 0; }
	bool operator!=(const FCompletedFTEInfo& other) const { return !(*this == other); }
	bool operator<(const FCompletedFTEInfo& other) const { return memcmp(this, &other, sizeof(FCompletedFTEInfo)) < 0; }
};

// ScriptStruct TAGame.FirstTimeExperienceManager_TA.FTELevelData
// 0x0048
struct FFTELevelData
{
	class FString                                      LevelId;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UClass*                                      SequenceClass;                                 // 0x0010 (0x0008) [0x0000000000000000]               
	class FString                                      MapName;                                       // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      MatchType;                                     // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        AddedInfo;                                     // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFTELevelData& other) const { return memcmp(this, &other, sizeof(FFTELevelData)) == 0; }
	bool operator!=(const FFTELevelData& other) const { return !(*this == other); }
	bool operator<(const FFTELevelData& other) const { return memcmp(this, &other, sizeof(FFTELevelData)) < 0; }
};

// ScriptStruct TAGame.FirstTimeExperienceManager_TA.FTEChallengeInfo
// 0x0010
struct FFTEChallengeInfo
{
	class FName                                        GroupName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        CheckpointName;                                // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FFTEChallengeInfo& other) const { return memcmp(this, &other, sizeof(FFTEChallengeInfo)) == 0; }
	bool operator!=(const FFTEChallengeInfo& other) const { return !(*this == other); }
	bool operator<(const FFTEChallengeInfo& other) const { return memcmp(this, &other, sizeof(FFTEChallengeInfo)) < 0; }
};

// ScriptStruct TAGame.FXActor_SafeZone_Knockout_TA.SafeZoneInfo
// 0x0010
struct FSafeZoneInfo
{
	int32_t                                            Size;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            StartTime;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ReturnToZoneTime;                              // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendSpeed;                                    // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSafeZoneInfo& other) const { return memcmp(this, &other, sizeof(FSafeZoneInfo)) == 0; }
	bool operator!=(const FSafeZoneInfo& other) const { return !(*this == other); }
	bool operator<(const FSafeZoneInfo& other) const { return memcmp(this, &other, sizeof(FSafeZoneInfo)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Team_TA.PlayerLeavingData
// 0x0010
struct FPlayerLeavingData
{
	class AController*                                 Player;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class ATeam_TA*                                    Team;                                          // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FPlayerLeavingData& other) const { return memcmp(this, &other, sizeof(FPlayerLeavingData)) == 0; }
	bool operator!=(const FPlayerLeavingData& other) const { return !(*this == other); }
	bool operator<(const FPlayerLeavingData& other) const { return memcmp(this, &other, sizeof(FPlayerLeavingData)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Soccar_TA.ClubMemberCount
// 0x0010
struct FClubMemberCount
{
	int32_t                                            Count;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	uint64_t                                           ClubID;                                        // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FClubMemberCount& other) const { return memcmp(this, &other, sizeof(FClubMemberCount)) == 0; }
	bool operator!=(const FClubMemberCount& other) const { return !(*this == other); }
	bool operator<(const FClubMemberCount& other) const { return memcmp(this, &other, sizeof(FClubMemberCount)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Soccar_TA.PendingClubStatRecord
// 0x0010
struct FPendingClubStatRecord
{
	int32_t                                            TeamIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	uint64_t                                           ClubID;                                        // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FPendingClubStatRecord& other) const { return memcmp(this, &other, sizeof(FPendingClubStatRecord)) == 0; }
	bool operator!=(const FPendingClubStatRecord& other) const { return !(*this == other); }
	bool operator<(const FPendingClubStatRecord& other) const { return memcmp(this, &other, sizeof(FPendingClubStatRecord)) < 0; }
};

// ScriptStruct TAGame.MatchSeries_TA.SeriesTeam
// 0x0014
struct FSeriesTeam
{
	class TArray<struct FUniqueNetId>                  Players;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            GamesWon;                                      // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FSeriesTeam& other) const { return memcmp(this, &other, sizeof(FSeriesTeam)) == 0; }
	bool operator!=(const FSeriesTeam& other) const { return !(*this == other); }
	bool operator<(const FSeriesTeam& other) const { return memcmp(this, &other, sizeof(FSeriesTeam)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Soccar_TA.MemberTitleStat
// 0x0020
struct FMemberTitleStat
{
	class UStatCategory_TA*                            Category;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class UStatTitle_TA*                               Title;                                         // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            PointsEarned;                                  // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            StatCount;                                     // 0x0014 (0x0004) [0x0000000000000000]               
	class APRI_TA*                                     MemberPRI;                                     // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FMemberTitleStat& other) const { return memcmp(this, &other, sizeof(FMemberTitleStat)) == 0; }
	bool operator!=(const FMemberTitleStat& other) const { return !(*this == other); }
	bool operator<(const FMemberTitleStat& other) const { return memcmp(this, &other, sizeof(FMemberTitleStat)) < 0; }
};

// ScriptStruct TAGame.ThistleConfig_TA.ThistleData
// 0x003C
struct FThistleData
{
	class FString                                      TeamName;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLinearColor                                TeamColor;                                     // 0x0010 (0x0010) [0x0000000000000000]               
	struct FLinearColor                                TeamColorSecondary;                            // 0x0020 (0x0010) [0x0000000000000000]               
	int32_t                                            CosmeticID;                                    // 0x0030 (0x0004) [0x0000000000000000]               
	class FName                                        TitleId;                                       // 0x0034 (0x0008) [0x0000000000000000]               

	bool operator==(const FThistleData& other) const { return memcmp(this, &other, sizeof(FThistleData)) == 0; }
	bool operator!=(const FThistleData& other) const { return !(*this == other); }
	bool operator<(const FThistleData& other) const { return memcmp(this, &other, sizeof(FThistleData)) < 0; }
};

// ScriptStruct TAGame.OnlineGameReservations_TA.ReservationLoadout
// 0x0058
struct FReservationLoadout
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              ProductIDs;                                    // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FReservationLoadout& other) const { return memcmp(this, &other, sizeof(FReservationLoadout)) == 0; }
	bool operator!=(const FReservationLoadout& other) const { return !(*this == other); }
	bool operator<(const FReservationLoadout& other) const { return memcmp(this, &other, sizeof(FReservationLoadout)) < 0; }
};

// ScriptStruct TAGame.FpsBucketRecorder_TA.FpsBucketData
// 0x0024
struct FFpsBucketData
{
	int32_t                                            FPS;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              TotalTime;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              GameThreadTime;                                // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              RenderThreadTime;                              // 0x000C (0x0004) [0x0000000000000000]               
	float                                              GPUFrameTime;                                  // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              AvgFPS;                                        // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            DockedResolutionIndexSum;                      // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            UndockedResolutionIndexSum;                    // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FFpsBucketData& other) const { return memcmp(this, &other, sizeof(FFpsBucketData)) == 0; }
	bool operator!=(const FFpsBucketData& other) const { return !(*this == other); }
	bool operator<(const FFpsBucketData& other) const { return memcmp(this, &other, sizeof(FFpsBucketData)) < 0; }
};

// ScriptStruct TAGame.GameEvent_TrainingEditor_TA.CachedLocationModifier
// 0x0020
struct FCachedLocationModifier
{
	class UClass*                                      ActorClass;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     ActorLocation;                                 // 0x0008 (0x000C) [0x0000000000000000]               
	struct FRotator                                    ActorRotation;                                 // 0x0014 (0x000C) [0x0000000000000000]               

	bool operator==(const FCachedLocationModifier& other) const { return memcmp(this, &other, sizeof(FCachedLocationModifier)) == 0; }
	bool operator!=(const FCachedLocationModifier& other) const { return !(*this == other); }
	bool operator<(const FCachedLocationModifier& other) const { return memcmp(this, &other, sizeof(FCachedLocationModifier)) < 0; }
};

// ScriptStruct TAGame.GameInfo_TA.GameEventData
// 0x001C
struct FGameEventData
{
	class AGameEvent_TA*                               Archetype;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FString                                      LaunchOption;                                  // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	uint32_t                                           bDestroyCurrentGame : 1;                       // 0x0018 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bAddAllPlayers : 1;                            // 0x0018 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)

	bool operator==(const FGameEventData& other) const { return memcmp(this, &other, sizeof(FGameEventData)) == 0; }
	bool operator!=(const FGameEventData& other) const { return !(*this == other); }
	bool operator<(const FGameEventData& other) const { return memcmp(this, &other, sizeof(FGameEventData)) < 0; }
};

// ScriptStruct TAGame.GameInfo_TA.PostMatchCelebrationData
// 0x0024
struct FPostMatchCelebrationData
{
	class FName                                        CelebrationName;                               // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        MVPAnim;                                       // 0x0008 (0x0008) [0x0000000000000000]               
	class TArray<class FName>                          RegularAnims;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            CelebrationPlayerCount;                        // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FPostMatchCelebrationData& other) const { return memcmp(this, &other, sizeof(FPostMatchCelebrationData)) == 0; }
	bool operator!=(const FPostMatchCelebrationData& other) const { return !(*this == other); }
	bool operator<(const FPostMatchCelebrationData& other) const { return memcmp(this, &other, sizeof(FPostMatchCelebrationData)) < 0; }
};

// ScriptStruct TAGame.GameObserver_TA.BallData
// 0x001C
struct FBallData
{
	class ABall_TA*                                    Ball;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Altitude;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              AerialSkill;                                   // 0x000C (0x0004) [0x0000000000000000]               
	class AVehicle_TA*                                 LastHitBy;                                     // 0x0010 (0x0008) [0x0000000000000000]               
	float                                              LastHitTime;                                   // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FBallData& other) const { return memcmp(this, &other, sizeof(FBallData)) == 0; }
	bool operator!=(const FBallData& other) const { return !(*this == other); }
	bool operator<(const FBallData& other) const { return memcmp(this, &other, sizeof(FBallData)) < 0; }
};

// ScriptStruct TAGame.GameObserver_TA.CarGoalData
// 0x000C
struct FCarGoalData
{
	float                                              Distance;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Dot;                                           // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              DotBetweenBall;                                // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FCarGoalData& other) const { return memcmp(this, &other, sizeof(FCarGoalData)) == 0; }
	bool operator!=(const FCarGoalData& other) const { return !(*this == other); }
	bool operator<(const FCarGoalData& other) const { return memcmp(this, &other, sizeof(FCarGoalData)) < 0; }
};

// ScriptStruct TAGame.GameObserver_TA.CarData
// 0x0058
struct FCarData
{
	class AVehicle_TA*                                 Car;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Dot;                                           // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              DistToBall;                                    // 0x000C (0x0004) [0x0000000000000000]               
	float                                              SpeedTowardsBall;                              // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              TimeToBall;                                    // 0x0014 (0x0004) [0x0000000000000000]               
	struct FCarGoalData                                OffensiveGoal;                                 // 0x0018 (0x000C) [0x0000000000000000]               
	struct FCarGoalData                                DefensiveGoal;                                 // 0x0024 (0x000C) [0x0000000000000000]               
	class FString                                      LastEvent;                                     // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              BallHitProbability;                            // 0x0040 (0x0004) [0x0000000000000000]               
	float                                              Offense;                                       // 0x0044 (0x0004) [0x0000000000000000]               
	float                                              Defense;                                       // 0x0048 (0x0004) [0x0000000000000000]               
	float                                              Aerial;                                        // 0x004C (0x0004) [0x0000000000000000]               
	float                                              PredictedDistToBall;                           // 0x0050 (0x0004) [0x0000000000000000]               
	float                                              TimeInAir;                                     // 0x0054 (0x0004) [0x0000000000000000]               

	bool operator==(const FCarData& other) const { return memcmp(this, &other, sizeof(FCarData)) == 0; }
	bool operator!=(const FCarData& other) const { return !(*this == other); }
	bool operator<(const FCarData& other) const { return memcmp(this, &other, sizeof(FCarData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Chat_TA.GFxChatMessage
// 0x0094
struct FGFxChatMessage
{
	int32_t                                            Team;                                          // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PlayerName;                                    // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Message;                                       // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	EChatChannel                                       ChatChannel;                                   // 0x0028 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bLocalPlayer : 1;                              // 0x002C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bTransient : 1;                                // 0x002C (0x0004) [0x0000000000000000] [0x00000002] 
	struct FUniqueNetId                                SenderId;                                      // 0x0030 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bPreset : 1;                                   // 0x0078 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	EChatMessageType                                   MessageType;                                   // 0x007C (0x0001) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      TimeStamp;                                     // 0x0080 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	struct FColor                                      TeamColor;                                     // 0x0090 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxChatMessage& other) const { return memcmp(this, &other, sizeof(FGFxChatMessage)) == 0; }
	bool operator!=(const FGFxChatMessage& other) const { return !(*this == other); }
	bool operator<(const FGFxChatMessage& other) const { return memcmp(this, &other, sizeof(FGFxChatMessage)) < 0; }
};

// ScriptStruct TAGame.GFxData_Chat_TA.ChatPresetGroupOverride
// 0x0020
struct FChatPresetGroupOverride
{
	int32_t                                            GroupIndex;                                    // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FString                                      GroupName;                                     // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            MessageIDOffset;                               // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bTeam : 1;                                     // 0x001C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)

	bool operator==(const FChatPresetGroupOverride& other) const { return memcmp(this, &other, sizeof(FChatPresetGroupOverride)) == 0; }
	bool operator!=(const FChatPresetGroupOverride& other) const { return !(*this == other); }
	bool operator<(const FChatPresetGroupOverride& other) const { return memcmp(this, &other, sizeof(FChatPresetGroupOverride)) < 0; }
};

// ScriptStruct TAGame.GFxData_Chat_TA.ChatPresetMessageGroup
// 0x0018
struct FChatPresetMessageGroup
{
	uint32_t                                           bTeam : 1;                                     // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FChatPresetMessageGroup& other) const { return memcmp(this, &other, sizeof(FChatPresetMessageGroup)) == 0; }
	bool operator!=(const FChatPresetMessageGroup& other) const { return !(*this == other); }
	bool operator<(const FChatPresetMessageGroup& other) const { return memcmp(this, &other, sizeof(FChatPresetMessageGroup)) < 0; }
};

// ScriptStruct TAGame.GFxData_Chat_TA.ChatPresetMessage
// 0x0020
struct FChatPresetMessage
{
	int32_t                                            GroupIndex;                                    // 0x0000 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	class FName                                        Id;                                            // 0x0004 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bTeam : 1;                                     // 0x000C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FChatPresetMessage& other) const { return memcmp(this, &other, sizeof(FChatPresetMessage)) == 0; }
	bool operator!=(const FChatPresetMessage& other) const { return !(*this == other); }
	bool operator<(const FChatPresetMessage& other) const { return memcmp(this, &other, sizeof(FChatPresetMessage)) < 0; }
};

// ScriptStruct TAGame.GFxData_Chat_TA.ChatChannelHistory
// 0x0018
struct FChatChannelHistory
{
	EChatChannel                                       ChatChannel;                                   // 0x0000 (0x0001) [0x0000000000000000]               
	class TArray<struct FGFxChatMessage>               Messages;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FChatChannelHistory& other) const { return memcmp(this, &other, sizeof(FChatChannelHistory)) == 0; }
	bool operator!=(const FChatChannelHistory& other) const { return !(*this == other); }
	bool operator<(const FChatChannelHistory& other) const { return memcmp(this, &other, sizeof(FChatChannelHistory)) < 0; }
};

// ScriptStruct TAGame.GFxData_EOSVoiceRoom_TA.NotificationCooldown
// 0x0018
struct FNotificationCooldown
{
	class FString                                      EpicAccountId;                                 // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint64_t                                           NotificationTime;                              // 0x0010 (0x0008) [0x0001000000000000]               

	bool operator==(const FNotificationCooldown& other) const { return memcmp(this, &other, sizeof(FNotificationCooldown)) == 0; }
	bool operator!=(const FNotificationCooldown& other) const { return !(*this == other); }
	bool operator<(const FNotificationCooldown& other) const { return memcmp(this, &other, sizeof(FNotificationCooldown)) < 0; }
};

// ScriptStruct TAGame.GFxData_ErrorModals_TA.PendingError
// 0x0028
struct FPendingError
{
	class UError*                                      Error;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	class UClass*                                      ModalClass;                                    // 0x0020 (0x0008) [0x0000000000000000]               

	bool operator==(const FPendingError& other) const { return memcmp(this, &other, sizeof(FPendingError)) == 0; }
	bool operator!=(const FPendingError& other) const { return !(*this == other); }
	bool operator<(const FPendingError& other) const { return memcmp(this, &other, sizeof(FPendingError)) < 0; }
};

// ScriptStruct TAGame.GFxData_MenuTree_TA.MenuTreeNodeData
// 0x0020
struct FMenuTreeNodeData
{
	class FName                                        NodeID;                                        // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      TableName;                                     // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UMenuTreeNode_TA*                            Node;                                          // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FMenuTreeNodeData& other) const { return memcmp(this, &other, sizeof(FMenuTreeNodeData)) == 0; }
	bool operator!=(const FMenuTreeNodeData& other) const { return !(*this == other); }
	bool operator<(const FMenuTreeNodeData& other) const { return memcmp(this, &other, sizeof(FMenuTreeNodeData)) < 0; }
};

// ScriptStruct TAGame.PlayMenuSave_TA.MenuTreeFocusMap
// 0x0010
struct FMenuTreeFocusMap
{
	class FName                                        ParentNodeID;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        ChildNodeID;                                   // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FMenuTreeFocusMap& other) const { return memcmp(this, &other, sizeof(FMenuTreeFocusMap)) == 0; }
	bool operator!=(const FMenuTreeFocusMap& other) const { return !(*this == other); }
	bool operator<(const FMenuTreeFocusMap& other) const { return memcmp(this, &other, sizeof(FMenuTreeFocusMap)) < 0; }
};

// ScriptStruct TAGame.GFxData_MusicPlayer_TA.GFxMusicPlaylist
// 0x0030
struct FGFxMusicPlaylist
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    Icon;                                          // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0018 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	class FName                                        PlaylistName;                                  // 0x001C (0x0008) [0x0000000000000000]               
	class UMusicPlaylist_TA*                           Playlist;                                      // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxMusicPlaylist& other) const { return memcmp(this, &other, sizeof(FGFxMusicPlaylist)) == 0; }
	bool operator!=(const FGFxMusicPlaylist& other) const { return !(*this == other); }
	bool operator<(const FGFxMusicPlaylist& other) const { return memcmp(this, &other, sizeof(FGFxMusicPlaylist)) < 0; }
};

// ScriptStruct TAGame.GFxData_NotificationManager_TA.GFXNotificationInfo
// 0x0020
struct FGFXNotificationInfo
{
	int32_t                                            NotificationID;                                // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      TableName;                                     // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UNotification_TA*                            Notification;                                  // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFXNotificationInfo& other) const { return memcmp(this, &other, sizeof(FGFXNotificationInfo)) == 0; }
	bool operator!=(const FGFXNotificationInfo& other) const { return !(*this == other); }
	bool operator<(const FGFXNotificationInfo& other) const { return memcmp(this, &other, sizeof(FGFXNotificationInfo)) < 0; }
};

// ScriptStruct TAGame.GFxData_PartyInvite_TA.InviteDatabind
// 0x0058
struct FInviteDatabind
{
	struct FUniqueLobbyId                              LobbyId;                                       // 0x0000 (0x0010) [0x0000000000000000]               
	struct FUniqueNetId                                FromUser;                                      // 0x0010 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FInviteDatabind& other) const { return memcmp(this, &other, sizeof(FInviteDatabind)) == 0; }
	bool operator!=(const FInviteDatabind& other) const { return !(*this == other); }
	bool operator<(const FInviteDatabind& other) const { return memcmp(this, &other, sizeof(FInviteDatabind)) < 0; }
};

// ScriptStruct TAGame.GFxData_PartyInvite_TA.InviteTarget
// 0x0060
struct FInviteTarget
{
	struct FUniqueNetId                                ToPlayer;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             InviteHandler;                                 // 0x0048 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FInviteTarget& other) const { return memcmp(this, &other, sizeof(FInviteTarget)) == 0; }
	bool operator!=(const FInviteTarget& other) const { return !(*this == other); }
	bool operator<(const FInviteTarget& other) const { return memcmp(this, &other, sizeof(FInviteTarget)) < 0; }
};

// ScriptStruct TAGame.ProductHash_TA.ProductHashSource
// 0x0020
struct FProductHashSource
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FProductHashSource& other) const { return memcmp(this, &other, sizeof(FProductHashSource)) == 0; }
	bool operator!=(const FProductHashSource& other) const { return !(*this == other); }
	bool operator<(const FProductHashSource& other) const { return memcmp(this, &other, sizeof(FProductHashSource)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductSlot
// 0x0040
struct FFilterProductSlot
{
	class FName                                        SlotName;                                      // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      PluralLabel;                                   // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    Icon;                                          // 0x0028 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0030 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bHasNewItems : 1;                              // 0x0030 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	int32_t                                            SlotIndex;                                     // 0x0034 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PreviewQuantity;                               // 0x0038 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bHidden : 1;                                   // 0x003C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FFilterProductSlot& other) const { return memcmp(this, &other, sizeof(FFilterProductSlot)) == 0; }
	bool operator!=(const FFilterProductSlot& other) const { return !(*this == other); }
	bool operator<(const FFilterProductSlot& other) const { return memcmp(this, &other, sizeof(FFilterProductSlot)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductQuality
// 0x001C
struct FFilterProductQuality
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0010 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	EProductQuality                                    Quality;                                       // 0x0014 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PreviewQuantity;                               // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FFilterProductQuality& other) const { return memcmp(this, &other, sizeof(FFilterProductQuality)) == 0; }
	bool operator!=(const FFilterProductQuality& other) const { return !(*this == other); }
	bool operator<(const FFilterProductQuality& other) const { return memcmp(this, &other, sizeof(FFilterProductQuality)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductAttribute
// 0x0028
struct FFilterProductAttribute
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0010 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	class UClass*                                      AttributeClass;                                // 0x0018 (0x0008) [0x0000000000000000]               
	int32_t                                            PreviewQuantity;                               // 0x0020 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bHidden : 1;                                   // 0x0024 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FFilterProductAttribute& other) const { return memcmp(this, &other, sizeof(FFilterProductAttribute)) == 0; }
	bool operator!=(const FFilterProductAttribute& other) const { return !(*this == other); }
	bool operator<(const FFilterProductAttribute& other) const { return memcmp(this, &other, sizeof(FFilterProductAttribute)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductExtraAttributeEntry
// 0x0010
struct FFilterProductExtraAttributeEntry
{
	class UClass*                                      OriginalAttributeClass;                        // 0x0000 (0x0008) [0x0000000000000000]               
	class UClass*                                      ExtraAttributeClass;                           // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FFilterProductExtraAttributeEntry& other) const { return memcmp(this, &other, sizeof(FFilterProductExtraAttributeEntry)) == 0; }
	bool operator!=(const FFilterProductExtraAttributeEntry& other) const { return !(*this == other); }
	bool operator<(const FFilterProductExtraAttributeEntry& other) const { return memcmp(this, &other, sizeof(FFilterProductExtraAttributeEntry)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductSeries
// 0x0018
struct FFilterProductSeries
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0010 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	int32_t                                            SeriesID;                                      // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FFilterProductSeries& other) const { return memcmp(this, &other, sizeof(FFilterProductSeries)) == 0; }
	bool operator!=(const FFilterProductSeries& other) const { return !(*this == other); }
	bool operator<(const FFilterProductSeries& other) const { return memcmp(this, &other, sizeof(FFilterProductSeries)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductPaint
// 0x001C
struct FFilterProductPaint
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0010 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	int32_t                                            PaintID;                                       // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            PreviewQuantity;                               // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FFilterProductPaint& other) const { return memcmp(this, &other, sizeof(FFilterProductPaint)) == 0; }
	bool operator!=(const FFilterProductPaint& other) const { return !(*this == other); }
	bool operator<(const FFilterProductPaint& other) const { return memcmp(this, &other, sizeof(FFilterProductPaint)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductFilter_TA.FilterProductSorting
// 0x0011
struct FFilterProductSorting
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	EProductFilterSortType                             SortType;                                      // 0x0010 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FFilterProductSorting& other) const { return memcmp(this, &other, sizeof(FFilterProductSorting)) == 0; }
	bool operator!=(const FFilterProductSorting& other) const { return !(*this == other); }
	bool operator<(const FFilterProductSorting& other) const { return memcmp(this, &other, sizeof(FFilterProductSorting)) < 0; }
};

// ScriptStruct TAGame.GFxData_ProductTradeIn_TA.TradeIn
// 0x0004
struct FTradeIn
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTradeIn& other) const { return memcmp(this, &other, sizeof(FTradeIn)) == 0; }
	bool operator!=(const FTradeIn& other) const { return !(*this == other); }
	bool operator<(const FTradeIn& other) const { return memcmp(this, &other, sizeof(FTradeIn)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourServerSettings
// 0x00E4
struct FTourServerSettings
{
	uint64_t                                           TournamentID;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            MatchID;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	class FString                                      GameTags;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMatchTieBreaker                                   TieBreaker;                                    // 0x0020 (0x0001) [0x0000000000000000]               
	uint8_t                                            GameMode;                                      // 0x0021 (0x0001) [0x0000000000000000]               
	class TArray<class FName>                          DisabledMaps;                                  // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        MapSetName;                                    // 0x0038 (0x0008) [0x0000000000000000]               
	int32_t                                            SeriesLength;                                  // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            TeamSize;                                      // 0x0044 (0x0004) [0x0000000000000000]               
	class TArray<struct FTourTeam>                     Teams;                                         // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint64_t>                             BotTeams;                                      // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourMatchGame>                Games;                                         // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  SpectatorPlayerIDs;                            // 0x0078 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                CreatorPlayerID;                               // 0x0088 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint8_t                                            MinPlayersPerTeam;                             // 0x00D0 (0x0001) [0x0000000000000000]               
	uint64_t                                           MatchExpireTimestamp;                          // 0x00D8 (0x0008) [0x0000000000000000]               
	int32_t                                            MinPlayersMetWaitTimeSeconds;                  // 0x00E0 (0x0004) [0x0000000000000000]               

	bool operator==(const FTourServerSettings& other) const { return memcmp(this, &other, sizeof(FTourServerSettings)) == 0; }
	bool operator!=(const FTourServerSettings& other) const { return !(*this == other); }
	bool operator<(const FTourServerSettings& other) const { return memcmp(this, &other, sizeof(FTourServerSettings)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourPrivateCredentials
// 0x0020
struct FTourPrivateCredentials
{
	class FString                                      Title;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Password;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourPrivateCredentials& other) const { return memcmp(this, &other, sizeof(FTourPrivateCredentials)) == 0; }
	bool operator!=(const FTourPrivateCredentials& other) const { return !(*this == other); }
	bool operator<(const FTourPrivateCredentials& other) const { return memcmp(this, &other, sizeof(FTourPrivateCredentials)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourCreateSettings
// 0x0038
struct FTourCreateSettings
{
	class UTourSettings_TA*                            Settings;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	struct FTourPrivateCredentials                     PrivateSettings;                               // 0x0008 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTourReward>                   Rewards;                                       // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTourCreateSettings& other) const { return memcmp(this, &other, sizeof(FTourCreateSettings)) == 0; }
	bool operator!=(const FTourCreateSettings& other) const { return !(*this == other); }
	bool operator<(const FTourCreateSettings& other) const { return memcmp(this, &other, sizeof(FTourCreateSettings)) < 0; }
};

// ScriptStruct TAGame.InMapDragonManager_TA.DragonEntry
// 0x0030
struct FDragonEntry
{
	class UAnimStateComponent_TA*                      AnimState;                                     // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	int32_t                                            TeamIndex;                                     // 0x0008 (0x0004) [0x0000000000000000]               
	class UAnimNodeAimOffset*                          AimOffsetNode;                                 // 0x0010 (0x0008) [0x0000000000000000]               
	struct FRotator                                    DesiredAim;                                    // 0x0018 (0x000C) [0x0000000000002000] (CPF_Transient)
	struct FRotator                                    CurrentAim;                                    // 0x0024 (0x000C) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FDragonEntry& other) const { return memcmp(this, &other, sizeof(FDragonEntry)) == 0; }
	bool operator!=(const FDragonEntry& other) const { return !(*this == other); }
	bool operator<(const FDragonEntry& other) const { return memcmp(this, &other, sizeof(FDragonEntry)) < 0; }
};

// ScriptStruct TAGame.MapsConfig_TA.OnlineMapData
// 0x0010
struct FOnlineMapData
{
	class UMapData_TA*                                 Map;                                           // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              Frequency;                                     // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bInRotation : 1;                               // 0x000C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)

	bool operator==(const FOnlineMapData& other) const { return memcmp(this, &other, sizeof(FOnlineMapData)) == 0; }
	bool operator!=(const FOnlineMapData& other) const { return !(*this == other); }
	bool operator<(const FOnlineMapData& other) const { return memcmp(this, &other, sizeof(FOnlineMapData)) < 0; }
};

// ScriptStruct TAGame.MapsConfig_TA.OnlineMapSet
// 0x0020
struct FOnlineMapSet
{
	class FName                                        SetName;                                       // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FOnlineMapData>                Maps;                                          // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class UMapSet_TA*                                  MapSet;                                        // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FOnlineMapSet& other) const { return memcmp(this, &other, sizeof(FOnlineMapSet)) == 0; }
	bool operator!=(const FOnlineMapSet& other) const { return !(*this == other); }
	bool operator<(const FOnlineMapSet& other) const { return memcmp(this, &other, sizeof(FOnlineMapSet)) < 0; }
};

// ScriptStruct TAGame.MapsConfig_TA.MapSetMapData
// 0x0028
struct FMapSetMapData
{
	class UMapSet_TA*                                  MapSet;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<class UMapData_TA*>                   MapsToAdd;                                     // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UMapData_TA*>                   MapsToRemove;                                  // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMapSetMapData& other) const { return memcmp(this, &other, sizeof(FMapSetMapData)) == 0; }
	bool operator!=(const FMapSetMapData& other) const { return !(*this == other); }
	bool operator<(const FMapSetMapData& other) const { return memcmp(this, &other, sizeof(FMapSetMapData)) < 0; }
};

// ScriptStruct TAGame.RPC_GetActivePlaylists_TA.ActivePlaylistInfo
// 0x0030
struct FActivePlaylistInfo
{
	class FName                                        NodeID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Playlist;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	EActivePlaylistType                                Type;                                          // 0x000C (0x0001) [0x0000000000000000]               
	uint64_t                                           StartTime;                                     // 0x0010 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTime;                                       // 0x0018 (0x0008) [0x0000000000000000]               
	struct FRankedDisparitySettings                    DisparitySettings;                             // 0x0020 (0x000C) [0x0000000000000000]               
	uint32_t                                           bCompetitive : 1;                              // 0x002C (0x0004) [0x0000000000002000] [0x00000001] (CPF_Transient)

	bool operator==(const FActivePlaylistInfo& other) const { return memcmp(this, &other, sizeof(FActivePlaylistInfo)) == 0; }
	bool operator!=(const FActivePlaylistInfo& other) const { return !(*this == other); }
	bool operator<(const FActivePlaylistInfo& other) const { return memcmp(this, &other, sizeof(FActivePlaylistInfo)) < 0; }
};

// ScriptStruct TAGame.RPC_GetActivePlaylists_TA.RankedUnlockCondition
// 0x0020
struct FRankedUnlockCondition
{
	class FString                                      Criteria;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              Value;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRankedUnlockCondition& other) const { return memcmp(this, &other, sizeof(FRankedUnlockCondition)) == 0; }
	bool operator!=(const FRankedUnlockCondition& other) const { return !(*this == other); }
	bool operator<(const FRankedUnlockCondition& other) const { return memcmp(this, &other, sizeof(FRankedUnlockCondition)) < 0; }
};

// ScriptStruct TAGame.MTXGarageUtils_TA.PriceInfo
// 0x0034
struct FPriceInfo
{
	int32_t                                            CatalogID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Title;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsExactPack : 1;                              // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            Price;                                         // 0x001C (0x0004) [0x0000000000000000]               
	class FString                                      PurchasePrice;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            VCAmount;                                      // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FPriceInfo& other) const { return memcmp(this, &other, sizeof(FPriceInfo)) == 0; }
	bool operator!=(const FPriceInfo& other) const { return !(*this == other); }
	bool operator<(const FPriceInfo& other) const { return memcmp(this, &other, sizeof(FPriceInfo)) < 0; }
};

// ScriptStruct TAGame.MTXGarageUtils_TA.MTXProduct
// 0x000C
struct FMTXProduct
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FProductHashID                              HashID;                                        // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bIsOwned : 1;                                  // 0x0008 (0x0004) [0x0000000040000000] [0x100000001] (CPF_DataBinding)

	bool operator==(const FMTXProduct& other) const { return memcmp(this, &other, sizeof(FMTXProduct)) == 0; }
	bool operator!=(const FMTXProduct& other) const { return !(*this == other); }
	bool operator<(const FMTXProduct& other) const { return memcmp(this, &other, sizeof(FMTXProduct)) < 0; }
};

// ScriptStruct TAGame.MTXGarageUtils_TA.MTXPurchaseInfo
// 0x00E0
struct FMTXPurchaseInfo
{
	int32_t                                            CatalogID;                                     // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Title;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      PriceDescription;                              // 0x0028 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      TabTitle;                                      // 0x0038 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    Image;                                         // 0x0048 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PurchasePrice;                                 // 0x0050 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      OriginalPrice;                                 // 0x0060 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            DiscountPercentage;                            // 0x0070 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FMTXProduct>                   Products;                                      // 0x0078 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class TArray<struct FMTXProduct>                   InjectedProducts;                              // 0x0088 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      BundleCurrencies;                              // 0x0098 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bCanBePlayerTraded : 1;                        // 0x00A8 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bIsOwned : 1;                                  // 0x00A8 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bIsExactPack : 1;                              // 0x00A8 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	int32_t                                            BonusVCPercentage;                             // 0x00AC (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bDualLev : 1;                                  // 0x00B0 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	int32_t                                            Price;                                         // 0x00B4 (0x0004) [0x0000000000000000]               
	int32_t                                            VCAmount;                                      // 0x00B8 (0x0004) [0x0000000000000000]               
	uint32_t                                           bIsPriceUpdated : 1;                           // 0x00BC (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      ImageURL;                                      // 0x00C0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PlatformProductID;                             // 0x00D0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMTXPurchaseInfo& other) const { return memcmp(this, &other, sizeof(FMTXPurchaseInfo)) == 0; }
	bool operator!=(const FMTXPurchaseInfo& other) const { return !(*this == other); }
	bool operator<(const FMTXPurchaseInfo& other) const { return memcmp(this, &other, sizeof(FMTXPurchaseInfo)) < 0; }
};

// ScriptStruct TAGame.PhysicsMetrics_TA.ResimMetricData
// 0x0024
struct FResimMetricData
{
	class FName                                        GameStateName;                                 // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            NumCorrectionEvents;                           // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalNumResimFrames;                           // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            MinNumResimFramesPerEvent;                     // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxNumResimFramesPerEvent;                     // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              AverageNumResimFramesPerEvent;                 // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              AverageCorrectionEventsPerSecond;              // 0x001C (0x0004) [0x0000000000000000]               
	float                                              AverageResimFramesPerSecond;                   // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FResimMetricData& other) const { return memcmp(this, &other, sizeof(FResimMetricData)) == 0; }
	bool operator!=(const FResimMetricData& other) const { return !(*this == other); }
	bool operator<(const FResimMetricData& other) const { return memcmp(this, &other, sizeof(FResimMetricData)) < 0; }
};

// ScriptStruct TAGame.PlatformMetrics_TA.PlatformMetricData
// 0x000C
struct FPlatformMetricData
{
	uint64_t                                           Marker;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Type;                                          // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPlatformMetricData& other) const { return memcmp(this, &other, sizeof(FPlatformMetricData)) == 0; }
	bool operator!=(const FPlatformMetricData& other) const { return !(*this == other); }
	bool operator<(const FPlatformMetricData& other) const { return memcmp(this, &other, sizeof(FPlatformMetricData)) < 0; }
};

// ScriptStruct TAGame.PlatformMetrics_TA.PlatformMetric
// 0x0018
struct FPlatformMetric
{
	class APlayerController_TA*                        PC;                                            // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FPlatformMetricData>           MetricData;                                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlatformMetric& other) const { return memcmp(this, &other, sizeof(FPlatformMetric)) == 0; }
	bool operator!=(const FPlatformMetric& other) const { return !(*this == other); }
	bool operator<(const FPlatformMetric& other) const { return memcmp(this, &other, sizeof(FPlatformMetric)) < 0; }
};

// ScriptStruct TAGame.SaveData_TA.OptionsValue
// 0x0018
struct FOptionsValue
{
	class FName                                        Id;                                            // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Value;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOptionsValue& other) const { return memcmp(this, &other, sizeof(FOptionsValue)) == 0; }
	bool operator!=(const FOptionsValue& other) const { return !(*this == other); }
	bool operator<(const FOptionsValue& other) const { return memcmp(this, &other, sizeof(FOptionsValue)) < 0; }
};

// ScriptStruct TAGame.SaveData_TA.PlaylistSkillData
// 0x000C
struct FPlaylistSkillData
{
	int32_t                                            Playlist;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Tier;                                          // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            MatchesPlayed;                                 // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPlaylistSkillData& other) const { return memcmp(this, &other, sizeof(FPlaylistSkillData)) == 0; }
	bool operator!=(const FPlaylistSkillData& other) const { return !(*this == other); }
	bool operator<(const FPlaylistSkillData& other) const { return memcmp(this, &other, sizeof(FPlaylistSkillData)) < 0; }
};

// ScriptStruct TAGame.PrivacyPolicySave_TA.LegalTextVersion
// 0x0008
struct FLegalTextVersion
{
	int32_t                                            TextHash;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Version;                                       // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FLegalTextVersion& other) const { return memcmp(this, &other, sizeof(FLegalTextVersion)) == 0; }
	bool operator!=(const FLegalTextVersion& other) const { return !(*this == other); }
	bool operator<(const FLegalTextVersion& other) const { return memcmp(this, &other, sizeof(FLegalTextVersion)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Skin_TA.ParameterInformation
// 0x0038
struct FParameterInformation
{
	class UProductAsset_PaintFinish_TA*                PaintFinishToApply;                            // 0x0000 (0x0008) [0x0000000800000001] (CPF_Edit | CPF_EditorOnly)
	class TArray<struct FTextureParameterValue>        TextureParameterValues;                        // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FScalarParameterValue>         ScalarParameterValues;                         // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FVectorParameterValue>         VectorParameterValues;                         // 0x0028 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FParameterInformation& other) const { return memcmp(this, &other, sizeof(FParameterInformation)) == 0; }
	bool operator!=(const FParameterInformation& other) const { return !(*this == other); }
	bool operator<(const FParameterInformation& other) const { return memcmp(this, &other, sizeof(FParameterInformation)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Skin_TA.BodyChassisOverride
// 0x0010
struct FBodyChassisOverride
{
	class UProductAssetReferenceBody_TA*               Body;                                          // 0x0000 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	class UProductOverride_SpecificMaterials_TA*       MaterialOverride;                              // 0x0008 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FBodyChassisOverride& other) const { return memcmp(this, &other, sizeof(FBodyChassisOverride)) == 0; }
	bool operator!=(const FBodyChassisOverride& other) const { return !(*this == other); }
	bool operator<(const FBodyChassisOverride& other) const { return memcmp(this, &other, sizeof(FBodyChassisOverride)) < 0; }
};

// ScriptStruct TAGame.ProductOverride_ParticleSystemColorParameter_TA.PaintColorParameterOverride
// 0x0028
struct FPaintColorParameterOverride
{
	class FName                                        PaintParameterName;                            // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EPaintColorVariant                                 PaintType;                                     // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class UProductPaint_TA*                            Paint;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                CustomColor;                                   // 0x0018 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPaintColorParameterOverride& other) const { return memcmp(this, &other, sizeof(FPaintColorParameterOverride)) == 0; }
	bool operator!=(const FPaintColorParameterOverride& other) const { return !(*this == other); }
	bool operator<(const FPaintColorParameterOverride& other) const { return memcmp(this, &other, sizeof(FPaintColorParameterOverride)) < 0; }
};

// ScriptStruct TAGame.RecentPlayers_TA.PlayerGameID
// 0x0058
struct FPlayerGameID
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GameID;                                        // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerGameID& other) const { return memcmp(this, &other, sizeof(FPlayerGameID)) == 0; }
	bool operator!=(const FPlayerGameID& other) const { return !(*this == other); }
	bool operator<(const FPlayerGameID& other) const { return memcmp(this, &other, sizeof(FPlayerGameID)) < 0; }
};

// ScriptStruct TAGame.RecentPlayers_TA.PlayerLoadoutData
// 0x00C8
struct FPlayerLoadoutData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FOnlineProductData                          BannerData;                                    // 0x0048 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FOnlineProductData                          AvatarBorderData;                              // 0x0088 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerLoadoutData& other) const { return memcmp(this, &other, sizeof(FPlayerLoadoutData)) == 0; }
	bool operator!=(const FPlayerLoadoutData& other) const { return !(*this == other); }
	bool operator<(const FPlayerLoadoutData& other) const { return memcmp(this, &other, sizeof(FPlayerLoadoutData)) < 0; }
};

// ScriptStruct TAGame.RocketPassNotificationsManager_TA.RocketPassNotificationData
// 0x0034
struct FRocketPassNotificationData
{
	class FString                                      Title;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Body;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	ERocketPassNotificationType                        RPNotificationType;                            // 0x0020 (0x0001) [0x0000000000000000]               
	ERocketPassNotificationRewardType                  RewardType;                                    // 0x0021 (0x0001) [0x0000000000000000]               
	int32_t                                            TierLevel;                                     // 0x0024 (0x0004) [0x0000000000000000]               
	class UOnlineProduct_TA*                           Reward;                                        // 0x0028 (0x0008) [0x0000000000000000]               
	float                                              CreatedTime;                                   // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FRocketPassNotificationData& other) const { return memcmp(this, &other, sizeof(FRocketPassNotificationData)) == 0; }
	bool operator!=(const FRocketPassNotificationData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassNotificationData& other) const { return memcmp(this, &other, sizeof(FRocketPassNotificationData)) < 0; }
};

// ScriptStruct TAGame.FXActor_Car_TA.WheelFX
// 0x0034
struct FWheelFX
{
	class UParticleSystemComponent*                    PSC;                                           // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     Velocity;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	uint32_t                                           bHasContact : 1;                               // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 
	class AFXActor_X*                                  SupersonicFXActor;                             // 0x0018 (0x0008) [0x0000000000000000]               
	class FName                                        BoneName;                                      // 0x0020 (0x0008) [0x0000000000000000]               
	struct FVector                                     BoneOffset;                                    // 0x0028 (0x000C) [0x0000000000000000]               

	bool operator==(const FWheelFX& other) const { return memcmp(this, &other, sizeof(FWheelFX)) == 0; }
	bool operator!=(const FWheelFX& other) const { return !(*this == other); }
	bool operator<(const FWheelFX& other) const { return memcmp(this, &other, sizeof(FWheelFX)) < 0; }
};

// ScriptStruct TAGame.SFXConfig_TA.SoundEventSetting
// 0x0020
struct FSoundEventSetting
{
	class FName                                        SoundName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           StartTime;                                     // 0x0008 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTime;                                       // 0x0010 (0x0008) [0x0000000000000000]               
	float                                              Frequency;                                     // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              MinValue;                                      // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FSoundEventSetting& other) const { return memcmp(this, &other, sizeof(FSoundEventSetting)) == 0; }
	bool operator!=(const FSoundEventSetting& other) const { return !(*this == other); }
	bool operator<(const FSoundEventSetting& other) const { return memcmp(this, &other, sizeof(FSoundEventSetting)) < 0; }
};

// ScriptStruct TAGame.ShopAdsConfig_TA.ShopAdData
// 0x0068
struct FShopAdData
{
	class FString                                      IdleImageURL;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      HoverImageURL;                                 // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ClickImageURL;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UTexture*                                    IdleImage;                                     // 0x0030 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    HoverImage;                                    // 0x0038 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    ClickImage;                                    // 0x0040 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bOpenURLInCoherent : 1;                        // 0x0048 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	class FName                                        Section;                                       // 0x004C (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Link;                                          // 0x0058 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FShopAdData& other) const { return memcmp(this, &other, sizeof(FShopAdData)) == 0; }
	bool operator!=(const FShopAdData& other) const { return !(*this == other); }
	bool operator<(const FShopAdData& other) const { return memcmp(this, &other, sizeof(FShopAdData)) < 0; }
};

// ScriptStruct TAGame.ShopCatalogueCacheSave_TA.ShopItemCacheItem
// 0x0018
struct FShopItemCacheItem
{
	int32_t                                            ShopItemID;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FProductHashID>                ProductHashIDs;                                // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopItemCacheItem& other) const { return memcmp(this, &other, sizeof(FShopItemCacheItem)) == 0; }
	bool operator!=(const FShopItemCacheItem& other) const { return !(*this == other); }
	bool operator<(const FShopItemCacheItem& other) const { return memcmp(this, &other, sizeof(FShopItemCacheItem)) < 0; }
};

// ScriptStruct TAGame.ShopNotificationsManager_TA.ReadyItemShopNotification
// 0x0038
struct FReadyItemShopNotification
{
	int32_t                                            ShopNotificationID;                            // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Title;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Body;                                          // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UTexture*                                    Icon;                                          // 0x0028 (0x0008) [0x0000000000000000]               
	uint64_t                                           ExpirationTime;                                // 0x0030 (0x0008) [0x0000000000000000]               

	bool operator==(const FReadyItemShopNotification& other) const { return memcmp(this, &other, sizeof(FReadyItemShopNotification)) == 0; }
	bool operator!=(const FReadyItemShopNotification& other) const { return !(*this == other); }
	bool operator<(const FReadyItemShopNotification& other) const { return memcmp(this, &other, sizeof(FReadyItemShopNotification)) < 0; }
};

// ScriptStruct TAGame.ServerStartVoteEvent_TA.PartyInfo
// 0x0060
struct FPartyInfo
{
	struct FUniqueNetId                                LeaderID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  FollowerIds;                                   // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class AActor*                                      VoterOwner;                                    // 0x0058 (0x0008) [0x0000000000000000]               

	bool operator==(const FPartyInfo& other) const { return memcmp(this, &other, sizeof(FPartyInfo)) == 0; }
	bool operator!=(const FPartyInfo& other) const { return !(*this == other); }
	bool operator<(const FPartyInfo& other) const { return memcmp(this, &other, sizeof(FPartyInfo)) < 0; }
};

// ScriptStruct TAGame.TextModerationManager_TA.PendingValidatedMessage
// 0x0010
struct FPendingValidatedMessage
{
	class USignedMessageObject_X*                      MessageObject;                                 // 0x0000 (0x0008) [0x0001000000000000]               
	int32_t                                            ServerTimeStamp;                               // 0x0008 (0x0004) [0x0001000000000000]               
	int32_t                                            RequestID;                                     // 0x000C (0x0004) [0x0001000000000000]               

	bool operator==(const FPendingValidatedMessage& other) const { return memcmp(this, &other, sizeof(FPendingValidatedMessage)) == 0; }
	bool operator!=(const FPendingValidatedMessage& other) const { return !(*this == other); }
	bool operator<(const FPendingValidatedMessage& other) const { return memcmp(this, &other, sizeof(FPendingValidatedMessage)) < 0; }
};

// ScriptStruct TAGame.TextModerationManager_TA.PendingSignedMessage
// 0x0024
struct FPendingSignedMessage
{
	class USignedMessageObject_X*                      MessageObject;                                 // 0x0000 (0x0008) [0x0001000000000000]               
	struct FScriptDelegate                             FinishedCallback;                              // 0x0008 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            RequestID;                                     // 0x0020 (0x0004) [0x0001000000000000]               

	bool operator==(const FPendingSignedMessage& other) const { return memcmp(this, &other, sizeof(FPendingSignedMessage)) == 0; }
	bool operator!=(const FPendingSignedMessage& other) const { return !(*this == other); }
	bool operator<(const FPendingSignedMessage& other) const { return memcmp(this, &other, sizeof(FPendingSignedMessage)) < 0; }
};

// ScriptStruct TAGame.TextModerationManager_TA.PendingKeyGenMessage
// 0x0078
struct FPendingKeyGenMessage
{
	class FString                                      Message;                                       // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                SenderId;                                      // 0x0010 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	EChatChannel                                       ChatChannel;                                   // 0x0058 (0x0001) [0x0001000000000000]               
	struct FScriptDelegate                             FinishedCallback;                              // 0x0060 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPendingKeyGenMessage& other) const { return memcmp(this, &other, sizeof(FPendingKeyGenMessage)) == 0; }
	bool operator!=(const FPendingKeyGenMessage& other) const { return !(*this == other); }
	bool operator<(const FPendingKeyGenMessage& other) const { return memcmp(this, &other, sizeof(FPendingKeyGenMessage)) < 0; }
};

// ScriptStruct TAGame.TextModerationManager_TA.UserPublicKey
// 0x0030
struct FUserPublicKey
{
	class FString                                      EpicAccountId;                                 // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      PublicKey;                                     // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      PublicKeyJWT;                                  // 0x0020 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUserPublicKey& other) const { return memcmp(this, &other, sizeof(FUserPublicKey)) == 0; }
	bool operator!=(const FUserPublicKey& other) const { return !(*this == other); }
	bool operator<(const FUserPublicKey& other) const { return memcmp(this, &other, sizeof(FUserPublicKey)) < 0; }
};

// ScriptStruct TAGame.TextModerationManager_TA.KeyRegistrationContent
// 0x0020
struct FKeyRegistrationContent
{
	class FString                                      algorithm;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Key;                                           // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FKeyRegistrationContent& other) const { return memcmp(this, &other, sizeof(FKeyRegistrationContent)) == 0; }
	bool operator!=(const FKeyRegistrationContent& other) const { return !(*this == other); }
	bool operator<(const FKeyRegistrationContent& other) const { return memcmp(this, &other, sizeof(FKeyRegistrationContent)) < 0; }
};

// ScriptStruct TAGame.TourBracketCache_TA.BracketResult
// 0x00B8
struct FBracketResult
{
	uint64_t                                           TourID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	struct FTourBracket                                Bracket;                                       // 0x0008 (0x0078) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              RetrieveTime;                                  // 0x0080 (0x0004) [0x0000000000002000] (CPF_Transient)
	struct FScriptDelegate                             BracketChangedCallback;                        // 0x0088 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             ErrorCallback;                                 // 0x00A0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FBracketResult& other) const { return memcmp(this, &other, sizeof(FBracketResult)) == 0; }
	bool operator!=(const FBracketResult& other) const { return !(*this == other); }
	bool operator<(const FBracketResult& other) const { return memcmp(this, &other, sizeof(FBracketResult)) < 0; }
};

// ScriptStruct TAGame.TourBracketCache_TA.BracketRequest
// 0x0028
struct FBracketRequest
{
	uint64_t                                           TourID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class UAsyncTask*                                  Task;                                          // 0x0008 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0010 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FBracketRequest& other) const { return memcmp(this, &other, sizeof(FBracketRequest)) == 0; }
	bool operator!=(const FBracketRequest& other) const { return !(*this == other); }
	bool operator<(const FBracketRequest& other) const { return memcmp(this, &other, sizeof(FBracketRequest)) < 0; }
};

// ScriptStruct TAGame.RPC_TourUpdateGame_TA.TeamUpdateInfo
// 0x000C
struct FTeamUpdateInfo
{
	uint64_t                                           TeamID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Difficulty;                                    // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FTeamUpdateInfo& other) const { return memcmp(this, &other, sizeof(FTeamUpdateInfo)) == 0; }
	bool operator!=(const FTeamUpdateInfo& other) const { return !(*this == other); }
	bool operator<(const FTeamUpdateInfo& other) const { return memcmp(this, &other, sizeof(FTeamUpdateInfo)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourSearchSettings
// 0x005C
struct FTourSearchSettings
{
	class FString                                      Text;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            RankMin;                                       // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            RankMax;                                       // 0x0014 (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              GameModes;                                     // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Regions;                                       // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TeamSize;                                      // 0x0038 (0x0004) [0x0000000000000000]               
	int32_t                                            BracketSize;                                   // 0x003C (0x0004) [0x0000000000000000]               
	uint32_t                                           bEnableCrossplay : 1;                          // 0x0040 (0x0004) [0x0000000000000000] [0x00000001] 
	uint64_t                                           StartTime;                                     // 0x0048 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTime;                                       // 0x0050 (0x0008) [0x0000000000000000]               
	uint32_t                                           bShowFull : 1;                                 // 0x0058 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bShowIneligibleRank : 1;                       // 0x0058 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FTourSearchSettings& other) const { return memcmp(this, &other, sizeof(FTourSearchSettings)) == 0; }
	bool operator!=(const FTourSearchSettings& other) const { return !(*this == other); }
	bool operator<(const FTourSearchSettings& other) const { return memcmp(this, &other, sizeof(FTourSearchSettings)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.GFxTournamentReward
// 0x0018
struct FGFxTournamentReward
{
	int32_t                                            Placement;                                     // 0x0000 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)

	bool operator==(const FGFxTournamentReward& other) const { return memcmp(this, &other, sizeof(FGFxTournamentReward)) == 0; }
	bool operator!=(const FGFxTournamentReward& other) const { return !(*this == other); }
	bool operator<(const FGFxTournamentReward& other) const { return memcmp(this, &other, sizeof(FGFxTournamentReward)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TournamentResult
// 0x0010
struct FTournamentResult
{
	int32_t                                            Difficulty;                                    // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Placement;                                     // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Score;                                         // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            ResultStanding;                                // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTournamentResult& other) const { return memcmp(this, &other, sizeof(FTournamentResult)) == 0; }
	bool operator!=(const FTournamentResult& other) const { return !(*this == other); }
	bool operator<(const FTournamentResult& other) const { return memcmp(this, &other, sizeof(FTournamentResult)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TourResult
// 0x0010
struct FTourResult
{
	uint64_t                                           TournamentID;                                  // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Difficulty;                                    // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Placement;                                     // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTourResult& other) const { return memcmp(this, &other, sizeof(FTourResult)) == 0; }
	bool operator!=(const FTourResult& other) const { return !(*this == other); }
	bool operator<(const FTourResult& other) const { return memcmp(this, &other, sizeof(FTourResult)) < 0; }
};

// ScriptStruct TAGame.TourStatus_TA.TourStatus
// 0x0028
struct FTourStatus
{
	uint64_t                                           Id;                                            // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	ETourStatus                                        Status;                                        // 0x0008 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           PlayerTeamID;                                  // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      TeamName;                                      // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FTourStatus& other) const { return memcmp(this, &other, sizeof(FTourStatus)) == 0; }
	bool operator!=(const FTourStatus& other) const { return !(*this == other); }
	bool operator<(const FTourStatus& other) const { return memcmp(this, &other, sizeof(FTourStatus)) < 0; }
};

// ScriptStruct TAGame._UserBugReportTypes_TA.UserBugReportCategory
// 0x0028
struct FUserBugReportCategory
{
	class FName                                        Id;                                            // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        ParentId;                                      // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EUserBugReportCategoryType                         Type;                                          // 0x0010 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class FString                                      Label;                                         // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FUserBugReportCategory& other) const { return memcmp(this, &other, sizeof(FUserBugReportCategory)) == 0; }
	bool operator!=(const FUserBugReportCategory& other) const { return !(*this == other); }
	bool operator<(const FUserBugReportCategory& other) const { return memcmp(this, &other, sizeof(FUserBugReportCategory)) < 0; }
};

// ScriptStruct TAGame.UserSettingObserverEventCache_TA.SettingEvent
// 0x0060
struct FSettingEvent
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	class FName                                        Id;                                            // 0x0048 (0x0008) [0x0001000000000000]               
	class FString                                      Value;                                         // 0x0050 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSettingEvent& other) const { return memcmp(this, &other, sizeof(FSettingEvent)) == 0; }
	bool operator!=(const FSettingEvent& other) const { return !(*this == other); }
	bool operator<(const FSettingEvent& other) const { return memcmp(this, &other, sizeof(FSettingEvent)) < 0; }
};

// ScriptStruct TAGame.VanityQuery_TA.VanityQueryRequest
// 0x0044
struct FVanityQueryRequest
{
	class UGFxShell_X*                                 Shell;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	EVanityType                                        VanityType;                                    // 0x0008 (0x0001) [0x0000000000000000]               
	class TArray<struct FUniqueNetId>                  PlayerIds;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             VanityCallback;                                // 0x0020 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            NumIdsToQuery;                                 // 0x0038 (0x0004) [0x0000000000000000]               
	int32_t                                            NumQueriesCompleted;                           // 0x003C (0x0004) [0x0000000000000000]               
	uint32_t                                           bForced : 1;                                   // 0x0040 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FVanityQueryRequest& other) const { return memcmp(this, &other, sizeof(FVanityQueryRequest)) == 0; }
	bool operator!=(const FVanityQueryRequest& other) const { return !(*this == other); }
	bool operator<(const FVanityQueryRequest& other) const { return memcmp(this, &other, sizeof(FVanityQueryRequest)) < 0; }
};

// ScriptStruct TAGame.ViralItemConfig_TA.ViralSeriesGroup
// 0x0018
struct FViralSeriesGroup
{
	EInfectedType                                      InfectedType;                                  // 0x0000 (0x0001) [0x0001000000000000]               
	class TArray<int32_t>                              SeriesIDs;                                     // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FViralSeriesGroup& other) const { return memcmp(this, &other, sizeof(FViralSeriesGroup)) == 0; }
	bool operator!=(const FViralSeriesGroup& other) const { return !(*this == other); }
	bool operator<(const FViralSeriesGroup& other) const { return memcmp(this, &other, sizeof(FViralSeriesGroup)) < 0; }
};

// ScriptStruct TAGame.VoteActor_TA.Voter
// 0x0009
struct FVoter
{
	class APRI_TA*                                     PRI;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	EVoteStatus                                        Status;                                        // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FVoter& other) const { return memcmp(this, &other, sizeof(FVoter)) == 0; }
	bool operator!=(const FVoter& other) const { return !(*this == other); }
	bool operator<(const FVoter& other) const { return memcmp(this, &other, sizeof(FVoter)) < 0; }
};

// ScriptStruct TAGame._AITypes_TA.BTDynamicLinkData
// 0x0010
struct FBTDynamicLinkData
{
	class FName                                        LinkName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UBTNode*                                     Node;                                          // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBTDynamicLinkData& other) const { return memcmp(this, &other, sizeof(FBTDynamicLinkData)) == 0; }
	bool operator!=(const FBTDynamicLinkData& other) const { return !(*this == other); }
	bool operator<(const FBTDynamicLinkData& other) const { return memcmp(this, &other, sizeof(FBTDynamicLinkData)) < 0; }
};

// ScriptStruct TAGame._AITypes_TA.AIProxyData
// 0x0048
struct FAIProxyData
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     Gravity;                                       // 0x0018 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0024 (0x000C) [0x0000000000000000]               
	float                                              Radius;                                        // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              Bounce;                                        // 0x0034 (0x0004) [0x0000000000000000]               
	class AActor*                                      Actor;                                         // 0x0038 (0x0008) [0x0000000000000000]               
	class AVehicle_TA*                                 Vehicle;                                       // 0x0040 (0x0008) [0x0000000000000000]               

	bool operator==(const FAIProxyData& other) const { return memcmp(this, &other, sizeof(FAIProxyData)) == 0; }
	bool operator!=(const FAIProxyData& other) const { return !(*this == other); }
	bool operator<(const FAIProxyData& other) const { return memcmp(this, &other, sizeof(FAIProxyData)) < 0; }
};

// ScriptStruct TAGame._AITypes_TA.AICachedGoalInfo
// 0x0014
struct FAICachedGoalInfo
{
	class UGoal_TA*                                    Goal;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     FieldSize;                                     // 0x0008 (0x000C) [0x0000000000000000]               

	bool operator==(const FAICachedGoalInfo& other) const { return memcmp(this, &other, sizeof(FAICachedGoalInfo)) == 0; }
	bool operator!=(const FAICachedGoalInfo& other) const { return !(*this == other); }
	bool operator<(const FAICachedGoalInfo& other) const { return memcmp(this, &other, sizeof(FAICachedGoalInfo)) < 0; }
};

// ScriptStruct TAGame._CrowdTypes_TA.CrowdExcitementSound
// 0x000C
struct FCrowdExcitementSound
{
	class UAkSoundCue*                                 Sound;                                         // 0x0000 (0x0008) [0x0001000000000001] (CPF_Edit)    
	float                                              Value;                                         // 0x0008 (0x0004) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FCrowdExcitementSound& other) const { return memcmp(this, &other, sizeof(FCrowdExcitementSound)) == 0; }
	bool operator!=(const FCrowdExcitementSound& other) const { return !(*this == other); }
	bool operator<(const FCrowdExcitementSound& other) const { return memcmp(this, &other, sizeof(FCrowdExcitementSound)) < 0; }
};

// ScriptStruct TAGame._CrowdTypes_TA.CrowdExcitementSounds
// 0x0028
struct FCrowdExcitementSounds
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0001000000000001] (CPF_Edit)    
	float                                              Cooldown;                                      // 0x0008 (0x0004) [0x0001000000000001] (CPF_Edit)    
	class TArray<struct FCrowdExcitementSound>         Sounds;                                        // 0x0010 (0x0010) [0x0001000000400001] (CPF_Edit | CPF_NeedCtorLink)
	ECrowdValueType                                    CompareType;                                   // 0x0020 (0x0001) [0x0001000000000001] (CPF_Edit)    
	float                                              LastPlayed;                                    // 0x0024 (0x0004) [0x0001000000002000] (CPF_Transient)

	bool operator==(const FCrowdExcitementSounds& other) const { return memcmp(this, &other, sizeof(FCrowdExcitementSounds)) == 0; }
	bool operator!=(const FCrowdExcitementSounds& other) const { return !(*this == other); }
	bool operator<(const FCrowdExcitementSounds& other) const { return memcmp(this, &other, sizeof(FCrowdExcitementSounds)) < 0; }
};

// ScriptStruct TAGame._CrowdTypes_TA.CrowdDefense
// 0x000C
struct FCrowdDefense
{
	float                                              DefenseZoneTime;                               // 0x0000 (0x0004) [0x0001000000000001] (CPF_Edit)    
	float                                              DefenseZoneDistance;                           // 0x0004 (0x0004) [0x0001000000000001] (CPF_Edit)    
	float                                              ReplayDelay;                                   // 0x0008 (0x0004) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FCrowdDefense& other) const { return memcmp(this, &other, sizeof(FCrowdDefense)) == 0; }
	bool operator!=(const FCrowdDefense& other) const { return !(*this == other); }
	bool operator<(const FCrowdDefense& other) const { return memcmp(this, &other, sizeof(FCrowdDefense)) < 0; }
};

// ScriptStruct TAGame._CrowdTypes_TA.CrowdScoreState
// 0x0010
struct FCrowdScoreState
{
	int32_t                                            MaxIncreaseScoreSeparation;                    // 0x0000 (0x0004) [0x0001000000000001] (CPF_Edit)    
	int32_t                                            MaxDecreaseScoreSeparation;                    // 0x0004 (0x0004) [0x0001000000000001] (CPF_Edit)    
	class FName                                        StateName;                                     // 0x0008 (0x0008) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FCrowdScoreState& other) const { return memcmp(this, &other, sizeof(FCrowdScoreState)) == 0; }
	bool operator!=(const FCrowdScoreState& other) const { return !(*this == other); }
	bool operator<(const FCrowdScoreState& other) const { return memcmp(this, &other, sizeof(FCrowdScoreState)) < 0; }
};

// ScriptStruct TAGame._CrowdTypes_TA.CrowdValueState
// 0x000C
struct FCrowdValueState
{
	float                                              Value;                                         // 0x0000 (0x0004) [0x0001000000000001] (CPF_Edit)    
	class FName                                        StateName;                                     // 0x0004 (0x0008) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FCrowdValueState& other) const { return memcmp(this, &other, sizeof(FCrowdValueState)) == 0; }
	bool operator!=(const FCrowdValueState& other) const { return !(*this == other); }
	bool operator<(const FCrowdValueState& other) const { return memcmp(this, &other, sizeof(FCrowdValueState)) < 0; }
};

// ScriptStruct TAGame._FreeplayCommandsTypes_TA.FreeplayCommandsMetricsData
// 0x0054
struct FFreeplayCommandsMetricsData
{
	struct FVector                                     BallLocation;                                  // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     BallVelocity;                                  // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocation;                                   // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarVelocity;                                   // 0x0024 (0x000C) [0x0000000000000000]               
	struct FRotatorRadians                             CarRotation;                                   // 0x0030 (0x000C) [0x0000000000000000]               
	class FString                                      MapName;                                       // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCarOnGround : 1;                              // 0x0050 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FFreeplayCommandsMetricsData& other) const { return memcmp(this, &other, sizeof(FFreeplayCommandsMetricsData)) == 0; }
	bool operator!=(const FFreeplayCommandsMetricsData& other) const { return !(*this == other); }
	bool operator<(const FFreeplayCommandsMetricsData& other) const { return memcmp(this, &other, sizeof(FFreeplayCommandsMetricsData)) < 0; }
};

// ScriptStruct TAGame._FreeplayCommandsTypes_TA.FreeplayCommandEvent
// 0x0070
struct FFreeplayCommandEvent
{
	uint64_t                                           ActivationTimestamp;                           // 0x0000 (0x0008) [0x0000000000000000]               
	EFreeplayCommand                                   ActivatedCommand;                              // 0x0008 (0x0001) [0x0000000000000000]               
	struct FFreeplayCommandsMetricsData                PreActivationData;                             // 0x0010 (0x0058) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        CommandExecutionError;                         // 0x0068 (0x0008) [0x0000000000000000]               

	bool operator==(const FFreeplayCommandEvent& other) const { return memcmp(this, &other, sizeof(FFreeplayCommandEvent)) == 0; }
	bool operator!=(const FFreeplayCommandEvent& other) const { return !(*this == other); }
	bool operator<(const FFreeplayCommandEvent& other) const { return memcmp(this, &other, sizeof(FFreeplayCommandEvent)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.TournamentEndData
// 0x0070
struct FTournamentEndData
{
	uint64_t                                           CycleID;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            WeekIndex;                                     // 0x0008 (0x0004) [0x0000000000000000]               
	class TArray<struct FTournamentResult>             OldWeeklyResults;                              // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FTournamentResult                           Result;                                        // 0x0020 (0x0010) [0x0000000000000000]               
	class TArray<struct FShopCurrencyInfo>             CurrencyRewards;                               // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FShopCurrencyInfo>             OldWeeklyCurrencies;                           // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FShopCurrencyInfo>             WeeklyCurrencies;                              // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FShopCurrencyInfo>             FinalCurrencies;                               // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTournamentEndData& other) const { return memcmp(this, &other, sizeof(FTournamentEndData)) == 0; }
	bool operator!=(const FTournamentEndData& other) const { return !(*this == other); }
	bool operator<(const FTournamentEndData& other) const { return memcmp(this, &other, sizeof(FTournamentEndData)) < 0; }
};

// ScriptStruct TAGame._TourTypes_TA.FaceItReservationMatchInfo
// 0x000C
struct FFaceItReservationMatchInfo
{
	int32_t                                            PartnerID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ServerId;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	uint32_t                                           bIsCrossPlatform : 1;                          // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FFaceItReservationMatchInfo& other) const { return memcmp(this, &other, sizeof(FFaceItReservationMatchInfo)) == 0; }
	bool operator!=(const FFaceItReservationMatchInfo& other) const { return !(*this == other); }
	bool operator<(const FFaceItReservationMatchInfo& other) const { return memcmp(this, &other, sizeof(FFaceItReservationMatchInfo)) < 0; }
};

// ScriptStruct TAGame._TrainingTypes_TA.TrainingRoundProgress
// 0x0005
struct FTrainingRoundProgress
{
	int32_t                                            RoundNumber;                                   // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	ETrainingRoundAttempt                              Status;                                        // 0x0004 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTrainingRoundProgress& other) const { return memcmp(this, &other, sizeof(FTrainingRoundProgress)) == 0; }
	bool operator!=(const FTrainingRoundProgress& other) const { return !(*this == other); }
	bool operator<(const FTrainingRoundProgress& other) const { return memcmp(this, &other, sizeof(FTrainingRoundProgress)) < 0; }
};

// ScriptStruct TAGame.PRI_TA.ClientLoadoutDatas
// 0x0020
struct FClientLoadoutDatas
{
	struct FClientLoadoutData                          Loadouts[2];                                   // 0x0000 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FClientLoadoutDatas& other) const { return memcmp(this, &other, sizeof(FClientLoadoutDatas)) == 0; }
	bool operator!=(const FClientLoadoutDatas& other) const { return !(*this == other); }
	bool operator<(const FClientLoadoutDatas& other) const { return memcmp(this, &other, sizeof(FClientLoadoutDatas)) < 0; }
};

// ScriptStruct TAGame.PRI_TA.SkillTierData
// 0x0010
struct FSkillTierData
{
	uint8_t                                            Tier;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            PlacementMatchesPlayed;                        // 0x0001 (0x0001) [0x0000000000000000]               
	float                                              MMR;                                           // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              PrevMMR;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bReplicated : 1;                               // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FSkillTierData& other) const { return memcmp(this, &other, sizeof(FSkillTierData)) == 0; }
	bool operator!=(const FSkillTierData& other) const { return !(*this == other); }
	bool operator<(const FSkillTierData& other) const { return memcmp(this, &other, sizeof(FSkillTierData)) < 0; }
};

// ScriptStruct TAGame.ActorChannelMonitor_TA.OverflowedProperties
// 0x0018
struct FOverflowedProperties
{
	class AActor*                                      OverflowedActor;                               // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<class FString>                        PropertyNames;                                 // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOverflowedProperties& other) const { return memcmp(this, &other, sizeof(FOverflowedProperties)) == 0; }
	bool operator!=(const FOverflowedProperties& other) const { return !(*this == other); }
	bool operator<(const FOverflowedProperties& other) const { return memcmp(this, &other, sizeof(FOverflowedProperties)) < 0; }
};

// ScriptStruct TAGame.ActorChannelMonitor_TA.ActorOverflowEvent
// 0x0058
struct FActorOverflowEvent
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOverflowedProperties>         OverflowedActors;                              // 0x0048 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FActorOverflowEvent& other) const { return memcmp(this, &other, sizeof(FActorOverflowEvent)) == 0; }
	bool operator!=(const FActorOverflowEvent& other) const { return !(*this == other); }
	bool operator<(const FActorOverflowEvent& other) const { return memcmp(this, &other, sizeof(FActorOverflowEvent)) < 0; }
};

// ScriptStruct TAGame.AdManager_TA.CachedAdImageData
// 0x0020
struct FCachedAdImageData
{
	class FString                                      ImageURL;                                      // 0x0000 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	uint64_t                                           CacheEndTime;                                  // 0x0010 (0x0008) [0x0000000000002000] (CPF_Transient)
	class UTexture2DDynamic*                           ImageTexture;                                  // 0x0018 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FCachedAdImageData& other) const { return memcmp(this, &other, sizeof(FCachedAdImageData)) == 0; }
	bool operator!=(const FCachedAdImageData& other) const { return !(*this == other); }
	bool operator<(const FCachedAdImageData& other) const { return memcmp(this, &other, sizeof(FCachedAdImageData)) < 0; }
};

// ScriptStruct TAGame.AdManager_TA.BillboardData
// 0x0014
struct FBillboardData
{
	class FString                                      MaterialName;                                  // 0x0000 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	int32_t                                            ZoneID;                                        // 0x0010 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FBillboardData& other) const { return memcmp(this, &other, sizeof(FBillboardData)) == 0; }
	bool operator!=(const FBillboardData& other) const { return !(*this == other); }
	bool operator<(const FBillboardData& other) const { return memcmp(this, &other, sizeof(FBillboardData)) < 0; }
};

// ScriptStruct TAGame.AdManager_TA.BillboardUpdateRequestData
// 0x0020
struct FBillboardUpdateRequestData
{
	int32_t                                            ZoneID;                                        // 0x0000 (0x0004) [0x0000000000002000] (CPF_Transient)
	int32_t                                            MaterialIndex;                                 // 0x0004 (0x0004) [0x0000000000002000] (CPF_Transient)
	class FString                                      MaterialName;                                  // 0x0008 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class UStaticMeshComponent*                        Mesh;                                          // 0x0018 (0x0008) [0x0000000004082008] (CPF_ExportObject | CPF_Transient | CPF_Component | CPF_EditInline)

	bool operator==(const FBillboardUpdateRequestData& other) const { return memcmp(this, &other, sizeof(FBillboardUpdateRequestData)) == 0; }
	bool operator!=(const FBillboardUpdateRequestData& other) const { return !(*this == other); }
	bool operator<(const FBillboardUpdateRequestData& other) const { return memcmp(this, &other, sizeof(FBillboardUpdateRequestData)) < 0; }
};

// ScriptStruct TAGame.RPC_AdsGet_TA.AdInfo
// 0x0020
struct FAdInfo
{
	class FString                                      URL;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            ZoneID;                                        // 0x0010 (0x0004) [0x0000000000000000]               
	uint64_t                                           UTCEndTime;                                    // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FAdInfo& other) const { return memcmp(this, &other, sizeof(FAdInfo)) == 0; }
	bool operator!=(const FAdInfo& other) const { return !(*this == other); }
	bool operator<(const FAdInfo& other) const { return memcmp(this, &other, sizeof(FAdInfo)) < 0; }
};

// ScriptStruct TAGame.AdManagerConfig_TA.MapAds
// 0x0020
struct FMapAds
{
	class FString                                      MapName;                                       // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FAdInfo>                       Ads;                                           // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMapAds& other) const { return memcmp(this, &other, sizeof(FMapAds)) == 0; }
	bool operator!=(const FMapAds& other) const { return !(*this == other); }
	bool operator<(const FMapAds& other) const { return memcmp(this, &other, sizeof(FMapAds)) < 0; }
};

// ScriptStruct TAGame.BTLockCollection.TimedLock
// 0x0010
struct FTimedLock
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              ReleaseTime;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bLockedOneFrame : 1;                           // 0x000C (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FTimedLock& other) const { return memcmp(this, &other, sizeof(FTimedLock)) == 0; }
	bool operator!=(const FTimedLock& other) const { return !(*this == other); }
	bool operator<(const FTimedLock& other) const { return memcmp(this, &other, sizeof(FTimedLock)) < 0; }
};

// ScriptStruct TAGame.AIController_TA.CachedProxyData
// 0x005C
struct FCachedProxyData
{
	class UBTProxyType*                                Type;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Index;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	struct FAIProxyData                                Data;                                          // 0x0010 (0x0048) [0x0000000000000000]               
	float                                              CacheTime;                                     // 0x0058 (0x0004) [0x0000000000000000]               

	bool operator==(const FCachedProxyData& other) const { return memcmp(this, &other, sizeof(FCachedProxyData)) == 0; }
	bool operator!=(const FCachedProxyData& other) const { return !(*this == other); }
	bool operator<(const FCachedProxyData& other) const { return memcmp(this, &other, sizeof(FCachedProxyData)) < 0; }
};

// ScriptStruct TAGame.AIController_TA.CachedTargetData
// 0x005C
struct FCachedTargetData
{
	class UBTTarget*                                   Target;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Index;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	struct FAIProxyData                                Data;                                          // 0x0010 (0x0048) [0x0000000000000000]               
	float                                              CacheTime;                                     // 0x0058 (0x0004) [0x0000000000000000]               

	bool operator==(const FCachedTargetData& other) const { return memcmp(this, &other, sizeof(FCachedTargetData)) == 0; }
	bool operator!=(const FCachedTargetData& other) const { return !(*this == other); }
	bool operator<(const FCachedTargetData& other) const { return memcmp(this, &other, sizeof(FCachedTargetData)) < 0; }
};

// ScriptStruct TAGame.AIController_TA.SkillRange
// 0x000C
struct FSkillRange
{
	float                                              Easy;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Hard;                                          // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Value;                                         // 0x0008 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FSkillRange& other) const { return memcmp(this, &other, sizeof(FSkillRange)) == 0; }
	bool operator!=(const FSkillRange& other) const { return !(*this == other); }
	bool operator<(const FSkillRange& other) const { return memcmp(this, &other, sizeof(FSkillRange)) < 0; }
};

// ScriptStruct TAGame.AIController_TA.CachedObstaclePoly
// 0x0020
struct FCachedObstaclePoly
{
	struct FPointer                                    Poly;                                          // 0x0000 (0x0008) [0x0000000000001000] (CPF_Native)  
	uint8_t                                            UnknownData00[0x8];                              // 0x0008 (0x0008) MISSED OFFSET
	struct FPlane                                      Plane;                                         // 0x0010 (0x0010) [0x0000000000000000]               

	bool operator==(const FCachedObstaclePoly& other) const { return memcmp(this, &other, sizeof(FCachedObstaclePoly)) == 0; }
	bool operator!=(const FCachedObstaclePoly& other) const { return !(*this == other); }
	bool operator<(const FCachedObstaclePoly& other) const { return memcmp(this, &other, sizeof(FCachedObstaclePoly)) < 0; }
};

// ScriptStruct TAGame.AIController_TA.CachedObstaclesData
// 0x0028
struct FCachedObstaclesData
{
	struct FVector                                     CarLocation;                                   // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarNavMeshLocation;                            // 0x000C (0x000C) [0x0000000000000000]               
	class TArray<struct FCachedObstaclePoly>           Polys;                                         // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCachedObstaclesData& other) const { return memcmp(this, &other, sizeof(FCachedObstaclesData)) == 0; }
	bool operator!=(const FCachedObstaclesData& other) const { return !(*this == other); }
	bool operator<(const FCachedObstaclesData& other) const { return memcmp(this, &other, sizeof(FCachedObstaclesData)) < 0; }
};

// ScriptStruct TAGame.AIManager_TA.CachedNavMeshLocation
// 0x0020
struct FCachedNavMeshLocation
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     NavMeshLocation;                               // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     OldActorLocation;                              // 0x0014 (0x000C) [0x0000000000000000]               

	bool operator==(const FCachedNavMeshLocation& other) const { return memcmp(this, &other, sizeof(FCachedNavMeshLocation)) == 0; }
	bool operator!=(const FCachedNavMeshLocation& other) const { return !(*this == other); }
	bool operator<(const FCachedNavMeshLocation& other) const { return memcmp(this, &other, sizeof(FCachedNavMeshLocation)) < 0; }
};

// ScriptStruct TAGame.ExplosionHitHandler_TA.ExplosionPaintInfo
// 0x0018
struct FExplosionPaintInfo
{
	class UProductAsset_TA*                            Asset;                                         // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	class UProductAttribute_PaintSettings_TA*          PaintSettings;                                 // 0x0008 (0x0008) [0x0000000000002000] (CPF_Transient)
	class UProductPaint_TA*                            Paint;                                         // 0x0010 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FExplosionPaintInfo& other) const { return memcmp(this, &other, sizeof(FExplosionPaintInfo)) == 0; }
	bool operator!=(const FExplosionPaintInfo& other) const { return !(*this == other); }
	bool operator<(const FExplosionPaintInfo& other) const { return memcmp(this, &other, sizeof(FExplosionPaintInfo)) < 0; }
};

// ScriptStruct TAGame.PRI_TA.ClientLoadoutOnlineDatas
// 0x0024
struct FClientLoadoutOnlineDatas
{
	struct FClientLoadoutOnlineData                    Loadouts[2];                                   // 0x0000 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bLoadoutSet : 1;                               // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDeprecated : 1;                               // 0x0020 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FClientLoadoutOnlineDatas& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineDatas)) == 0; }
	bool operator!=(const FClientLoadoutOnlineDatas& other) const { return !(*this == other); }
	bool operator<(const FClientLoadoutOnlineDatas& other) const { return memcmp(this, &other, sizeof(FClientLoadoutOnlineDatas)) < 0; }
};

// ScriptStruct TAGame.ArenaReflectionsManager_TA.SlapbackActorSetup
// 0x0018
struct FSlapbackActorSetup
{
	class FName                                        Bus;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	EPinnedAxisType                                    Axis;                                          // 0x0008 (0x0001) [0x0000000000000000]               
	struct FVector                                     FieldLocation;                                 // 0x000C (0x000C) [0x0000000000000000]               

	bool operator==(const FSlapbackActorSetup& other) const { return memcmp(this, &other, sizeof(FSlapbackActorSetup)) == 0; }
	bool operator!=(const FSlapbackActorSetup& other) const { return !(*this == other); }
	bool operator<(const FSlapbackActorSetup& other) const { return memcmp(this, &other, sizeof(FSlapbackActorSetup)) < 0; }
};

// ScriptStruct TAGame.ArenaSoundSettings_TA.ArenaStatSound
// 0x0010
struct FArenaStatSound
{
	class UStatEvent_TA*                               StatEvent;                                     // 0x0000 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	class UAkSoundCue*                                 Sound;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FArenaStatSound& other) const { return memcmp(this, &other, sizeof(FArenaStatSound)) == 0; }
	bool operator!=(const FArenaStatSound& other) const { return !(*this == other); }
	bool operator<(const FArenaStatSound& other) const { return memcmp(this, &other, sizeof(FArenaStatSound)) < 0; }
};

// ScriptStruct TAGame.StatFactory_TA.StatEventCollection
// 0x0290
struct FStatEventCollection
{
	class UStatEvent_TA*                               Win;                                           // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Loss;                                          // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               TimePlayed;                                    // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Shot;                                          // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Assist;                                        // 0x0020 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Center;                                        // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Clear;                                         // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PoolShot;                                      // 0x0038 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Goal;                                          // 0x0040 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               AerialGoal;                                    // 0x0048 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BicycleGoal;                                   // 0x0050 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BulletGoal;                                    // 0x0058 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BackwardsGoal;                                 // 0x0060 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               LongGoal;                                      // 0x0068 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               OvertimeGoal;                                  // 0x0070 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               TurtleGoal;                                    // 0x0078 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               AerialHit;                                     // 0x0080 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BicycleHit;                                    // 0x0088 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BulletHit;                                     // 0x0090 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               JuggleHit;                                     // 0x0098 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FirstTouch;                                    // 0x00A0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BallHit;                                       // 0x00A8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Save;                                          // 0x00B0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               EpicSave;                                      // 0x00B8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FreezeSave;                                    // 0x00C0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               HatTrick;                                      // 0x00C8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Savior;                                        // 0x00D0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Playmaker;                                     // 0x00D8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               MVP;                                           // 0x00E0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FastestGoal;                                   // 0x00E8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               SlowestGoal;                                   // 0x00F0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FurthestGoal;                                  // 0x00F8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               OwnGoal;                                       // 0x0100 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               MostBallTouches;                               // 0x0108 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FewestBallTouches;                             // 0x0110 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               MostBoostPickups;                              // 0x0118 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FewestBoostPickups;                            // 0x0120 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BoostPickups;                                  // 0x0128 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               CarTouches;                                    // 0x0130 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Demolition;                                    // 0x0138 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Demolish;                                      // 0x0140 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Demolished;                                    // 0x0148 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BallDemolitionScore;                           // 0x0150 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               CarDemolitionScore;                            // 0x0158 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               DemolitionSave;                                // 0x0160 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               DemolitionRespawn;                             // 0x0168 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               LowFive;                                       // 0x0170 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               HighFive;                                      // 0x0178 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PossessionPoint;                               // 0x0180 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PossessionSteal;                               // 0x0188 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PossessionDenial;                              // 0x0190 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PossessionClear;                               // 0x0198 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               ComebackWin;                                   // 0x01A0 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               SmallBoostsCollected;                          // 0x01A8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BigBoostsCollected;                            // 0x01B0 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BoostUsed;                                     // 0x01B8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               Dodges;                                        // 0x01C0 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               DistanceDrivenMeters;                          // 0x01C8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               SupersonicDistanceDrivenMeters;                // 0x01D0 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               DistanceFlown;                                 // 0x01D8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               CrossbarHits;                                  // 0x01E0 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               DoubleGrapple;                                 // 0x01E8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               MaxDodgeStreak;                                // 0x01F0 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PowerUpsUsed;                                  // 0x01F8 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               InfectedPlayersDefeated;                       // 0x0200 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               PlayersInfected;                               // 0x0208 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               KeepUpPoint;                                   // 0x0210 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               KeepUpPossession;                              // 0x0218 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               KeepUpDenial;                                  // 0x0220 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               KeepUpClear;                                   // 0x0228 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               FlipReset;                                     // 0x0230 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               AerialFlipReset;                               // 0x0238 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BellyFlipReset;                                // 0x0240 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               AerialBellyFlipReset;                          // 0x0248 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               MaxFlipResetStreak;                            // 0x0250 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               EqualizerGoal;                                 // 0x0258 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               AerialEqualizerGoal;                           // 0x0260 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BladeTargetGrabSwap;                           // 0x0268 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BladeRedirect;                                 // 0x0270 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BladeCooldown;                                 // 0x0278 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BladeCooldownHit;                              // 0x0280 (0x0008) [0x0001000000000001] (CPF_Edit)    
	class UStatEvent_TA*                               BladeCooldownSave;                             // 0x0288 (0x0008) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FStatEventCollection& other) const { return memcmp(this, &other, sizeof(FStatEventCollection)) == 0; }
	bool operator!=(const FStatEventCollection& other) const { return !(*this == other); }
	bool operator<(const FStatEventCollection& other) const { return memcmp(this, &other, sizeof(FStatEventCollection)) < 0; }
};

// ScriptStruct TAGame.AssetAttribute_ChangeProductDrawScale_TA.ProductSlotNewDrawScale
// 0x0010
struct FProductSlotNewDrawScale
{
	float                                              DrawScaleToApply;                              // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UProductSlot_TA*                             ProductSlotToApplyTo;                          // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FProductSlotNewDrawScale& other) const { return memcmp(this, &other, sizeof(FProductSlotNewDrawScale)) == 0; }
	bool operator!=(const FProductSlotNewDrawScale& other) const { return !(*this == other); }
	bool operator<(const FProductSlotNewDrawScale& other) const { return memcmp(this, &other, sizeof(FProductSlotNewDrawScale)) < 0; }
};

// ScriptStruct TAGame.AssetAttribute_GoalCountChanging_TA.GoalCountAndAsset
// 0x0010
struct FGoalCountAndAsset
{
	int32_t                                            GoalToChangeOn;                                // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UObject*                                     ObjectToChangeTo;                              // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FGoalCountAndAsset& other) const { return memcmp(this, &other, sizeof(FGoalCountAndAsset)) == 0; }
	bool operator!=(const FGoalCountAndAsset& other) const { return !(*this == other); }
	bool operator<(const FGoalCountAndAsset& other) const { return memcmp(this, &other, sizeof(FGoalCountAndAsset)) < 0; }
};

// ScriptStruct TAGame.AssetAttribute_SoundOverrides_TA.FXAttachmentSoundOverride
// 0x0010
struct FFXAttachmentSoundOverride
{
	class FName                                        FXName;                                        // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UAkSoundCue*                                 SoundCue;                                      // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFXAttachmentSoundOverride& other) const { return memcmp(this, &other, sizeof(FFXAttachmentSoundOverride)) == 0; }
	bool operator!=(const FFXAttachmentSoundOverride& other) const { return !(*this == other); }
	bool operator<(const FFXAttachmentSoundOverride& other) const { return memcmp(this, &other, sizeof(FFXAttachmentSoundOverride)) < 0; }
};

// ScriptStruct TAGame.AssetAttribute_TeamEdition_TA.TeamEditionOverrides
// 0x0028
struct FTeamEditionOverrides
{
	class UDataAsset_ESportsTeam_TA*                   ESportsTeam;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UProductOverride_TA*>           Overrides;                                     // 0x0008 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)
	class TArray<struct FPaintWithOverride>            PaintOverrides;                                // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FTeamEditionOverrides& other) const { return memcmp(this, &other, sizeof(FTeamEditionOverrides)) == 0; }
	bool operator!=(const FTeamEditionOverrides& other) const { return !(*this == other); }
	bool operator<(const FTeamEditionOverrides& other) const { return memcmp(this, &other, sizeof(FTeamEditionOverrides)) < 0; }
};

// ScriptStruct TAGame.AudioPriorityComponent_TA.PriorityCandidate
// 0x0020
struct FPriorityCandidate
{
	class AVehicle_TA*                                 Candidate;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Priority;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	class TArray<class FString>                        BonusReasons;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPriorityCandidate& other) const { return memcmp(this, &other, sizeof(FPriorityCandidate)) == 0; }
	bool operator!=(const FPriorityCandidate& other) const { return !(*this == other); }
	bool operator<(const FPriorityCandidate& other) const { return memcmp(this, &other, sizeof(FPriorityCandidate)) < 0; }
};

// ScriptStruct TAGame.AutoTour_TA.ScheduledTournament
// 0x0038
struct FScheduledTournament
{
	uint64_t                                           Time;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           ScheduleID;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	class FString                                      Description;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bUpdateSkill : 1;                              // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<class UTourSettings_TA*>              Tournaments;                                   // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FScheduledTournament& other) const { return memcmp(this, &other, sizeof(FScheduledTournament)) == 0; }
	bool operator!=(const FScheduledTournament& other) const { return !(*this == other); }
	bool operator<(const FScheduledTournament& other) const { return memcmp(this, &other, sizeof(FScheduledTournament)) < 0; }
};

// ScriptStruct TAGame.AutoTour_TA.TournamentWeek
// 0x0010
struct FTournamentWeek
{
	class TArray<struct FTournamentResult>             Results;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTournamentWeek& other) const { return memcmp(this, &other, sizeof(FTournamentWeek)) == 0; }
	bool operator!=(const FTournamentWeek& other) const { return !(*this == other); }
	bool operator<(const FTournamentWeek& other) const { return memcmp(this, &other, sizeof(FTournamentWeek)) < 0; }
};

// ScriptStruct TAGame.AutoTourConfig_TA.ScheduleRegion
// 0x0020
struct FScheduleRegion
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FScheduleRegion& other) const { return memcmp(this, &other, sizeof(FScheduleRegion)) == 0; }
	bool operator!=(const FScheduleRegion& other) const { return !(*this == other); }
	bool operator<(const FScheduleRegion& other) const { return memcmp(this, &other, sizeof(FScheduleRegion)) < 0; }
};

// ScriptStruct TAGame.RBActor_TA.WorldContactData
// 0x0028
struct FWorldContactData
{
	uint32_t                                           bHasContact : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     Normal;                                        // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FWorldContactData& other) const { return memcmp(this, &other, sizeof(FWorldContactData)) == 0; }
	bool operator!=(const FWorldContactData& other) const { return !(*this == other); }
	bool operator<(const FWorldContactData& other) const { return memcmp(this, &other, sizeof(FWorldContactData)) < 0; }
};

// ScriptStruct TAGame.RBActor_TA.NetworkSyncSettingsData
// 0x0020
struct FNetworkSyncSettingsData
{
	float                                              LocationFixRate;                               // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              AngularFixRate;                                // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MinDeltaLocation;                              // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WeldedLerpRate;                                // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MinDeltaRotation;                              // 0x0010 (0x0004) [0x0000000000000003] (CPF_Edit | CPF_Const)
	float                                              MinDeltaLinearVelocity;                        // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ForceReplicationDelay;                         // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bDebug : 1;                                    // 0x001C (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FNetworkSyncSettingsData& other) const { return memcmp(this, &other, sizeof(FNetworkSyncSettingsData)) == 0; }
	bool operator!=(const FNetworkSyncSettingsData& other) const { return !(*this == other); }
	bool operator<(const FNetworkSyncSettingsData& other) const { return memcmp(this, &other, sizeof(FNetworkSyncSettingsData)) < 0; }
};

// ScriptStruct TAGame.RBActor_TA.TimeOfImpactData
// 0x004C
struct FTimeOfImpactData
{
	float                                              Fraction;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     OtherLocation;                                 // 0x001C (0x000C) [0x0000000000000000]               
	struct FRotator                                    OtherRotation;                                 // 0x0028 (0x000C) [0x0000000000000000]               
	struct FVector                                     ImpactLocation;                                // 0x0034 (0x000C) [0x0000000000000000]               
	struct FVector                                     ImpactNormal;                                  // 0x0040 (0x000C) [0x0000000000000000]               

	bool operator==(const FTimeOfImpactData& other) const { return memcmp(this, &other, sizeof(FTimeOfImpactData)) == 0; }
	bool operator!=(const FTimeOfImpactData& other) const { return !(*this == other); }
	bool operator<(const FTimeOfImpactData& other) const { return memcmp(this, &other, sizeof(FTimeOfImpactData)) < 0; }
};

// ScriptStruct TAGame.PitchTekDrawingComponent_TA.PitchTekCarBodyContactData
// 0x0010
struct FPitchTekCarBodyContactData
{
	uint32_t                                           bHasContact : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               

	bool operator==(const FPitchTekCarBodyContactData& other) const { return memcmp(this, &other, sizeof(FPitchTekCarBodyContactData)) == 0; }
	bool operator!=(const FPitchTekCarBodyContactData& other) const { return !(*this == other); }
	bool operator<(const FPitchTekCarBodyContactData& other) const { return memcmp(this, &other, sizeof(FPitchTekCarBodyContactData)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.PredictedPosition
// 0x0018
struct FPredictedPosition
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x000C (0x000C) [0x0000000000000000]               

	bool operator==(const FPredictedPosition& other) const { return memcmp(this, &other, sizeof(FPredictedPosition)) == 0; }
	bool operator!=(const FPredictedPosition& other) const { return !(*this == other); }
	bool operator<(const FPredictedPosition& other) const { return memcmp(this, &other, sizeof(FPredictedPosition)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.ExplosionData
// 0x0014
struct FExplosionData
{
	class UGoal_TA*                                    Goal;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               

	bool operator==(const FExplosionData& other) const { return memcmp(this, &other, sizeof(FExplosionData)) == 0; }
	bool operator!=(const FExplosionData& other) const { return !(*this == other); }
	bool operator<(const FExplosionData& other) const { return memcmp(this, &other, sizeof(FExplosionData)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.ExplosionDataExtended
// 0x0020
struct FExplosionDataExtended
{
	class UGoal_TA*                                    Goal;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	class APRI_TA*                                     Scorer;                                        // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FExplosionDataExtended& other) const { return memcmp(this, &other, sizeof(FExplosionDataExtended)) == 0; }
	bool operator!=(const FExplosionDataExtended& other) const { return !(*this == other); }
	bool operator<(const FExplosionDataExtended& other) const { return memcmp(this, &other, sizeof(FExplosionDataExtended)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.ExplosionDataReactive
// 0x0005
struct FExplosionDataReactive
{
	uint32_t                                           bPodiumExplosion : 1;                          // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint8_t                                            ScorerGoalNumber;                              // 0x0004 (0x0001) [0x0000000000000000]               

	bool operator==(const FExplosionDataReactive& other) const { return memcmp(this, &other, sizeof(FExplosionDataReactive)) == 0; }
	bool operator!=(const FExplosionDataReactive& other) const { return !(*this == other); }
	bool operator<(const FExplosionDataReactive& other) const { return memcmp(this, &other, sizeof(FExplosionDataReactive)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.GoalPenetrationData
// 0x0024
struct FGoalPenetrationData
{
	class UGoal_TA*                                    Goal;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     PlaneLocation;                                 // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     PlaneNormal;                                   // 0x0014 (0x000C) [0x0000000000000000]               
	float                                              PenetrationDistance;                           // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FGoalPenetrationData& other) const { return memcmp(this, &other, sizeof(FGoalPenetrationData)) == 0; }
	bool operator!=(const FGoalPenetrationData& other) const { return !(*this == other); }
	bool operator<(const FGoalPenetrationData& other) const { return memcmp(this, &other, sizeof(FGoalPenetrationData)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.CarBallInteractionSettings
// 0x0034
struct FCarBallInteractionSettings
{
	uint32_t                                           bSkipScriptForces : 1;                         // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FInterpCurveFloat                           PushFactorCurve;                               // 0x0008 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	float                                              PushZScale;                                    // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              PushForwardScale;                              // 0x0024 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxRelativeSpeed;                              // 0x0028 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Restitution;                                   // 0x002C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Friction;                                      // 0x0030 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCarBallInteractionSettings& other) const { return memcmp(this, &other, sizeof(FCarBallInteractionSettings)) == 0; }
	bool operator!=(const FCarBallInteractionSettings& other) const { return !(*this == other); }
	bool operator<(const FCarBallInteractionSettings& other) const { return memcmp(this, &other, sizeof(FCarBallInteractionSettings)) < 0; }
};

// ScriptStruct TAGame.Ball_TA.BallExtraData
// 0x0008
struct FBallExtraData
{
	int32_t                                            DamageIndex;                                   // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              TargetSpeed;                                   // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FBallExtraData& other) const { return memcmp(this, &other, sizeof(FBallExtraData)) == 0; }
	bool operator!=(const FBallExtraData& other) const { return !(*this == other); }
	bool operator<(const FBallExtraData& other) const { return memcmp(this, &other, sizeof(FBallExtraData)) < 0; }
};

// ScriptStruct TAGame.Ball_Breakout_TA.BreakoutDamage
// 0x0008
struct FBreakoutDamage
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Damage;                                        // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FBreakoutDamage& other) const { return memcmp(this, &other, sizeof(FBreakoutDamage)) == 0; }
	bool operator!=(const FBreakoutDamage& other) const { return !(*this == other); }
	bool operator<(const FBreakoutDamage& other) const { return memcmp(this, &other, sizeof(FBreakoutDamage)) < 0; }
};

// ScriptStruct TAGame.BallTrajectoryComponent_TA.TrajectorySetup
// 0x0014
struct FTrajectorySetup
{
	float                                              TotalSimulateTime;                             // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bAlwaysEnabled : 1;                            // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bUpdatePathEveryFrame : 1;                     // 0x0004 (0x0004) [0x0000000000000000] [0x00000002] 
	int32_t                                            TotalPoints;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxStepsPerFrame;                              // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            QuickTrajectorySteps;                          // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FTrajectorySetup& other) const { return memcmp(this, &other, sizeof(FTrajectorySetup)) == 0; }
	bool operator!=(const FTrajectorySetup& other) const { return !(*this == other); }
	bool operator<(const FTrajectorySetup& other) const { return memcmp(this, &other, sizeof(FTrajectorySetup)) < 0; }
};

// ScriptStruct TAGame.BallTrajectoryComponent_Beam_TA.TrajectoryFX
// 0x0008
struct FTrajectoryFX
{
	class UParticleSystemComponent*                    Particle;                                      // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FTrajectoryFX& other) const { return memcmp(this, &other, sizeof(FTrajectoryFX)) == 0; }
	bool operator!=(const FTrajectoryFX& other) const { return !(*this == other); }
	bool operator<(const FTrajectoryFX& other) const { return memcmp(this, &other, sizeof(FTrajectoryFX)) < 0; }
};

// ScriptStruct TAGame.BallTrajectoryComponent_Mesh_TA.MeshInfo
// 0x0038
struct FMeshInfo
{
	class UStaticMeshComponent*                        Meshes;                                        // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0014 (0x000C) [0x0000000000000000]               
	int32_t                                            PointIndex;                                    // 0x0020 (0x0004) [0x0000000000000000]               
	struct FVector                                     MoveDirection;                                 // 0x0024 (0x000C) [0x0000000000000000]               
	float                                              DistanceAlongPath;                             // 0x0030 (0x0004) [0x0000000000000000]               
	uint32_t                                           bCrossedZero : 1;                              // 0x0034 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FMeshInfo& other) const { return memcmp(this, &other, sizeof(FMeshInfo)) == 0; }
	bool operator!=(const FMeshInfo& other) const { return !(*this == other); }
	bool operator<(const FMeshInfo& other) const { return memcmp(this, &other, sizeof(FMeshInfo)) < 0; }
};

// ScriptStruct TAGame.BallTrajectoryComponent_Spline_TA.TrajectorySplineFX
// 0x0008
struct FTrajectorySplineFX
{
	class ASplineLoftActorMovable*                     Spline;                                        // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FTrajectorySplineFX& other) const { return memcmp(this, &other, sizeof(FTrajectorySplineFX)) == 0; }
	bool operator!=(const FTrajectorySplineFX& other) const { return !(*this == other); }
	bool operator<(const FTrajectorySplineFX& other) const { return memcmp(this, &other, sizeof(FTrajectorySplineFX)) < 0; }
};

// ScriptStruct TAGame.BeamTraceComponent_TA.BeamTraceProps
// 0x0020
struct FBeamTraceProps
{
	float                                              NextTraceTime;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     LastWorldLocation;                             // 0x0004 (0x000C) [0x0000000000000000]               
	uint32_t                                           LastWorldHit : 1;                              // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 
	class UParticleSystemComponent*                    PSC;                                           // 0x0018 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FBeamTraceProps& other) const { return memcmp(this, &other, sizeof(FBeamTraceProps)) == 0; }
	bool operator!=(const FBeamTraceProps& other) const { return !(*this == other); }
	bool operator<(const FBeamTraceProps& other) const { return memcmp(this, &other, sizeof(FBeamTraceProps)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.AnimatedMaterialParam
// 0x0008
struct FAnimatedMaterialParam
{
	class FName                                        ParamName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAnimatedMaterialParam& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParam)) == 0; }
	bool operator!=(const FAnimatedMaterialParam& other) const { return !(*this == other); }
	bool operator<(const FAnimatedMaterialParam& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParam)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.AnimatedMaterialParamFloat
// 0x0008 (0x0008 - 0x0010)
struct FAnimatedMaterialParamFloat : FAnimatedMaterialParam
{
	class UDistributionFloat*                          Value;                                         // 0x0008 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FAnimatedMaterialParamFloat& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamFloat)) == 0; }
	bool operator!=(const FAnimatedMaterialParamFloat& other) const { return !(*this == other); }
	bool operator<(const FAnimatedMaterialParamFloat& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamFloat)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.AnimatedMaterialParamVector
// 0x0008 (0x0008 - 0x0010)
struct FAnimatedMaterialParamVector : FAnimatedMaterialParam
{
	class UDistributionVector*                         Value;                                         // 0x0008 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FAnimatedMaterialParamVector& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamVector)) == 0; }
	bool operator!=(const FAnimatedMaterialParamVector& other) const { return !(*this == other); }
	bool operator<(const FAnimatedMaterialParamVector& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamVector)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.BoostMeshOverride
// 0x0020
struct FBoostMeshOverride
{
	class UActorComponent*                             Mesh;                                          // 0x0000 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class AFXActor_X*                                  CarType;                                       // 0x0008 (0x0008) [0x0000000800000001] (CPF_Edit | CPF_EditorOnly)
	class FString                                      CarTypePath;                                   // 0x0010 (0x0010) [0x0000000000420001] (CPF_Edit | CPF_EditConst | CPF_NeedCtorLink)

	bool operator==(const FBoostMeshOverride& other) const { return memcmp(this, &other, sizeof(FBoostMeshOverride)) == 0; }
	bool operator!=(const FBoostMeshOverride& other) const { return !(*this == other); }
	bool operator<(const FBoostMeshOverride& other) const { return memcmp(this, &other, sizeof(FBoostMeshOverride)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.AnimatedMaterialParamColor
// 0x0008 (0x0010 - 0x0018)
struct FAnimatedMaterialParamColor : FAnimatedMaterialParamVector
{
	class UDistributionFloat*                          AlphaValue;                                    // 0x0010 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FAnimatedMaterialParamColor& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamColor)) == 0; }
	bool operator!=(const FAnimatedMaterialParamColor& other) const { return !(*this == other); }
	bool operator<(const FAnimatedMaterialParamColor& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialParamColor)) < 0; }
};

// ScriptStruct TAGame.BoostMesh_TA.AnimatedMaterialMesh
// 0x0064
struct FAnimatedMaterialMesh
{
	class FName                                        MeshAttachmentName;                            // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInterface*                          Material;                                      // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MaterialIndex;                                 // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FBoostMeshOverride>            MeshOverrides;                                 // 0x0018 (0x0010) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	class TArray<struct FAnimatedMaterialParamFloat>   FloatParams;                                   // 0x0028 (0x0010) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	class TArray<struct FAnimatedMaterialParamVector>  VectorParams;                                  // 0x0038 (0x0010) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	class TArray<struct FAnimatedMaterialParamColor>   ColorParams;                                   // 0x0048 (0x0010) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	class UActorComponent*                             Mesh;                                          // 0x0058 (0x0008) [0x0000000004082008] (CPF_ExportObject | CPF_Transient | CPF_Component | CPF_EditInline)
	float                                              ElapsedTime;                                   // 0x0060 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FAnimatedMaterialMesh& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialMesh)) == 0; }
	bool operator!=(const FAnimatedMaterialMesh& other) const { return !(*this == other); }
	bool operator<(const FAnimatedMaterialMesh& other) const { return memcmp(this, &other, sizeof(FAnimatedMaterialMesh)) < 0; }
};

// ScriptStruct TAGame.BreakOutActor_Platform_TA.BreakoutDamageState
// 0x0020
struct FBreakoutDamageState
{
	uint8_t                                            State;                                         // 0x0000 (0x0001) [0x0000000000000000]               
	class APRI_TA*                                     Causer;                                        // 0x0008 (0x0008) [0x0000000000000000]               
	struct FVector                                     DamageLocation;                                // 0x0010 (0x000C) [0x0000000000000000]               
	uint32_t                                           bDirectDamage : 1;                             // 0x001C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bImmediate : 1;                                // 0x001C (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FBreakoutDamageState& other) const { return memcmp(this, &other, sizeof(FBreakoutDamageState)) == 0; }
	bool operator!=(const FBreakoutDamageState& other) const { return !(*this == other); }
	bool operator<(const FBreakoutDamageState& other) const { return memcmp(this, &other, sizeof(FBreakoutDamageState)) < 0; }
};

// ScriptStruct TAGame.BTComponent.BTStatusLog
// 0x0028
struct FBTStatusLog
{
	class UBTNode*                                     Node;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Depth;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	EBTStatus                                          Status;                                        // 0x000C (0x0001) [0x0000000000000000]               
	class FString                                      Message;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bSetMessage : 1;                               // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bCondition : 1;                                // 0x0020 (0x0004) [0x0000000000000000] [0x00000002] 
	float                                              LastEvalTime;                                  // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FBTStatusLog& other) const { return memcmp(this, &other, sizeof(FBTStatusLog)) == 0; }
	bool operator!=(const FBTStatusLog& other) const { return !(*this == other); }
	bool operator<(const FBTStatusLog& other) const { return memcmp(this, &other, sizeof(FBTStatusLog)) < 0; }
};

// ScriptStruct TAGame.Camera_TA.ProfileSliderLimits
// 0x000C
struct FProfileSliderLimits
{
	float                                              Min;                                           // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Max;                                           // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              interval;                                      // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FProfileSliderLimits& other) const { return memcmp(this, &other, sizeof(FProfileSliderLimits)) == 0; }
	bool operator!=(const FProfileSliderLimits& other) const { return !(*this == other); }
	bool operator<(const FProfileSliderLimits& other) const { return memcmp(this, &other, sizeof(FProfileSliderLimits)) < 0; }
};

// ScriptStruct TAGame.Camera_TA.SwivelExtent
// 0x000C
struct FSwivelExtent
{
	int32_t                                            PitchMin;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            PitchMax;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            YawMax;                                        // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FSwivelExtent& other) const { return memcmp(this, &other, sizeof(FSwivelExtent)) == 0; }
	bool operator!=(const FSwivelExtent& other) const { return !(*this == other); }
	bool operator<(const FSwivelExtent& other) const { return memcmp(this, &other, sizeof(FSwivelExtent)) < 0; }
};

// ScriptStruct TAGame.CameraState_Car_TA.InterpVector
// 0x0028
struct FInterpVector
{
	float                                              Rate;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxDistance;                                   // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	uint32_t                                           bInitialized : 1;                              // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              Rate_Old;                                      // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Velocity;                                      // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FInterpVector& other) const { return memcmp(this, &other, sizeof(FInterpVector)) == 0; }
	bool operator!=(const FInterpVector& other) const { return !(*this == other); }
	bool operator<(const FInterpVector& other) const { return memcmp(this, &other, sizeof(FInterpVector)) < 0; }
};

// ScriptStruct TAGame.TargetFinder_TA.PlaneSelectData
// 0x0010
struct FPlaneSelectData
{
	float                                              YExtent;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              ZExtent;                                       // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              MaxDegreeAngle;                                // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              MaxDistance;                                   // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FPlaneSelectData& other) const { return memcmp(this, &other, sizeof(FPlaneSelectData)) == 0; }
	bool operator!=(const FPlaneSelectData& other) const { return !(*this == other); }
	bool operator<(const FPlaneSelectData& other) const { return memcmp(this, &other, sizeof(FPlaneSelectData)) < 0; }
};

// ScriptStruct TAGame.TargetFinder_TA.AngleSelectData
// 0x0008
struct FAngleSelectData
{
	float                                              MaxDegreeAngle;                                // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              MaxDistance;                                   // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FAngleSelectData& other) const { return memcmp(this, &other, sizeof(FAngleSelectData)) == 0; }
	bool operator!=(const FAngleSelectData& other) const { return !(*this == other); }
	bool operator<(const FAngleSelectData& other) const { return memcmp(this, &other, sizeof(FAngleSelectData)) < 0; }
};

// ScriptStruct TAGame.CameraState_CarPreview_TA.TargetCacheEntry
// 0x0020
struct FTargetCacheEntry
{
	class FName                                        TargetName;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0014 (0x000C) [0x0000000000000000]               

	bool operator==(const FTargetCacheEntry& other) const { return memcmp(this, &other, sizeof(FTargetCacheEntry)) == 0; }
	bool operator!=(const FTargetCacheEntry& other) const { return !(*this == other); }
	bool operator<(const FTargetCacheEntry& other) const { return memcmp(this, &other, sizeof(FTargetCacheEntry)) < 0; }
};

// ScriptStruct TAGame.GameObserver_TA.GoalData
// 0x0048
struct FGoalData
{
	class UGoal_TA*                                    Goal;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FVector                                     GoalFront;                                     // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     GoalForward;                                   // 0x0014 (0x000C) [0x0000000000000000]               
	float                                              DotToBall;                                     // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              DistToBall;                                    // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              BallSpeedTowardsGoal;                          // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              DotToBallVelocity;                             // 0x002C (0x0004) [0x0000000000000000]               
	float                                              RawScorability;                                // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              Scorability;                                   // 0x0034 (0x0004) [0x0000000000000000]               
	float                                              Defense;                                       // 0x0038 (0x0004) [0x0000000000000000]               
	int32_t                                            NumDefensiveCars;                              // 0x003C (0x0004) [0x0000000000000000]               
	float                                              Offense;                                       // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            NumOffensiveCars;                              // 0x0044 (0x0004) [0x0000000000000000]               

	bool operator==(const FGoalData& other) const { return memcmp(this, &other, sizeof(FGoalData)) == 0; }
	bool operator!=(const FGoalData& other) const { return !(*this == other); }
	bool operator<(const FGoalData& other) const { return memcmp(this, &other, sizeof(FGoalData)) < 0; }
};

// ScriptStruct TAGame.CameraState_Lobby_TA.CameraSettings
// 0x0008
struct FCameraSettings
{
	float                                              XOffsetDistance;                               // 0x0000 (0x0004) [0x0001000000000000]               
	float                                              CameraOffsetPitch;                             // 0x0004 (0x0004) [0x0001000000000000]               

	bool operator==(const FCameraSettings& other) const { return memcmp(this, &other, sizeof(FCameraSettings)) == 0; }
	bool operator!=(const FCameraSettings& other) const { return !(*this == other); }
	bool operator<(const FCameraSettings& other) const { return memcmp(this, &other, sizeof(FCameraSettings)) < 0; }
};

// ScriptStruct TAGame.CameraStateSelector_Priority_TA.StateParams
// 0x0009
struct FStateParams
{
	class UCameraState_X*                              State;                                         // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EStatePriority                                     Priority;                                      // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FStateParams& other) const { return memcmp(this, &other, sizeof(FStateParams)) == 0; }
	bool operator!=(const FStateParams& other) const { return !(*this == other); }
	bool operator<(const FStateParams& other) const { return memcmp(this, &other, sizeof(FStateParams)) < 0; }
};

// ScriptStruct TAGame.CameraTrack_TA.CameraTrackRotationPoint
// 0x0010
struct FCameraTrackRotationPoint
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0004 (0x000C) [0x0000000000000000]               

	bool operator==(const FCameraTrackRotationPoint& other) const { return memcmp(this, &other, sizeof(FCameraTrackRotationPoint)) == 0; }
	bool operator!=(const FCameraTrackRotationPoint& other) const { return !(*this == other); }
	bool operator<(const FCameraTrackRotationPoint& other) const { return memcmp(this, &other, sizeof(FCameraTrackRotationPoint)) < 0; }
};

// ScriptStruct TAGame.Vehicle_TA.CarInteractionData
// 0x000C
struct FCarInteractionData
{
	class AVehicle_TA*                                 LastHitCar;                                    // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	float                                              LastHitTime;                                   // 0x0008 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FCarInteractionData& other) const { return memcmp(this, &other, sizeof(FCarInteractionData)) == 0; }
	bool operator!=(const FCarInteractionData& other) const { return !(*this == other); }
	bool operator<(const FCarInteractionData& other) const { return memcmp(this, &other, sizeof(FCarInteractionData)) < 0; }
};

// ScriptStruct TAGame.CarMeshComponentBase_TA.InheritedObjects
// 0x0018
struct FInheritedObjects
{
	class UProductAsset_TA*                            Asset;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class UObject*                                     ObjectToEdit;                                  // 0x0008 (0x0008) [0x0000000000000000]               
	class UProductAttribute_InheritCarSetting_TA*      InheritSetting;                                // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FInheritedObjects& other) const { return memcmp(this, &other, sizeof(FInheritedObjects)) == 0; }
	bool operator!=(const FInheritedObjects& other) const { return !(*this == other); }
	bool operator<(const FInheritedObjects& other) const { return memcmp(this, &other, sizeof(FInheritedObjects)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Body_TA.VehicleWheelSettings
// 0x0008
struct FVehicleWheelSettings
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVehicleWheelSettings& other) const { return memcmp(this, &other, sizeof(FVehicleWheelSettings)) == 0; }
	bool operator!=(const FVehicleWheelSettings& other) const { return !(*this == other); }
	bool operator<(const FVehicleWheelSettings& other) const { return memcmp(this, &other, sizeof(FVehicleWheelSettings)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Body_TA.VehicleAxleSettings
// 0x0028
struct FVehicleAxleSettings
{
	float                                              WheelMeshRadius;                               // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WheelWidth;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WheelMeshOffsetSide;                           // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVehicleWheelSettings                       LeftWheel;                                     // 0x000C (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVehicleWheelSettings                       RightWheel;                                    // 0x0014 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              WheelRadius;                                   // 0x001C (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              WheelOffsetForward;                            // 0x0020 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              WheelOffsetSide;                               // 0x0024 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)

	bool operator==(const FVehicleAxleSettings& other) const { return memcmp(this, &other, sizeof(FVehicleAxleSettings)) == 0; }
	bool operator!=(const FVehicleAxleSettings& other) const { return !(*this == other); }
	bool operator<(const FVehicleAxleSettings& other) const { return memcmp(this, &other, sizeof(FVehicleAxleSettings)) < 0; }
};

// ScriptStruct TAGame.ProductAttribute_PaintSettings_TA.PaintMaterialGroup
// 0x0010
struct FPaintMaterialGroup
{
	class TArray<class UMaterialInterface*>            Materials;                                     // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPaintMaterialGroup& other) const { return memcmp(this, &other, sizeof(FPaintMaterialGroup)) == 0; }
	bool operator!=(const FPaintMaterialGroup& other) const { return !(*this == other); }
	bool operator<(const FPaintMaterialGroup& other) const { return memcmp(this, &other, sizeof(FPaintMaterialGroup)) < 0; }
};

// ScriptStruct TAGame.EngineAudioComponent_TA.CarStateData
// 0x0010
struct FCarStateData
{
	float                                              Throttle;                                      // 0x0000 (0x0004) [0x0000000000002000] (CPF_Transient)
	float                                              WheelSpeed;                                    // 0x0004 (0x0004) [0x0000000000002000] (CPF_Transient)
	float                                              EngineRPM;                                     // 0x0008 (0x0004) [0x0000000000002000] (CPF_Transient)
	float                                              EngineLoad;                                    // 0x000C (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FCarStateData& other) const { return memcmp(this, &other, sizeof(FCarStateData)) == 0; }
	bool operator!=(const FCarStateData& other) const { return !(*this == other); }
	bool operator<(const FCarStateData& other) const { return memcmp(this, &other, sizeof(FCarStateData)) < 0; }
};

// ScriptStruct TAGame.EngineAudioComponent_TA.EngineAudioNativeState
// 0x0038
struct FEngineAudioNativeState
{
	class UEngineAudioComponent_TA*                    Component;                                     // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class UEngineAudioProfile_TA*                      Profile;                                       // 0x0008 (0x0008) [0x0000000000000000]               
	class AVehicle_TA*                                 Car;                                           // 0x0010 (0x0008) [0x0000000000000000]               
	struct FCarStateData                               OldCarState;                                   // 0x0018 (0x0010) [0x0000000000000000]               
	struct FCarStateData                               CarState;                                      // 0x0028 (0x0010) [0x0000000000000000]               

	bool operator==(const FEngineAudioNativeState& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState)) == 0; }
	bool operator!=(const FEngineAudioNativeState& other) const { return !(*this == other); }
	bool operator<(const FEngineAudioNativeState& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState)) < 0; }
};

// ScriptStruct TAGame.EngineAudioComponent_TA.EngineAudioNativeState_Clutched
// 0x0004 (0x0038 - 0x003C)
struct FEngineAudioNativeState_Clutched : FEngineAudioNativeState
{
	uint32_t                                           bUsingRevLimiter : 1;                          // 0x0038 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FEngineAudioNativeState_Clutched& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_Clutched)) == 0; }
	bool operator!=(const FEngineAudioNativeState_Clutched& other) const { return !(*this == other); }
	bool operator<(const FEngineAudioNativeState_Clutched& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_Clutched)) < 0; }
};

// ScriptStruct TAGame.EngineAudioComponent_TA.EngineAudioNativeState_OnGround
// 0x0010 (0x0038 - 0x0048)
struct FEngineAudioNativeState_OnGround : FEngineAudioNativeState
{
	float                                              GearSwitchTimeRemaining;                       // 0x0038 (0x0004) [0x0000000000000000]               
	float                                              RPMShiftUp;                                    // 0x003C (0x0004) [0x0000000000000000]               
	float                                              RPMShiftDown;                                  // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            Gear;                                          // 0x0044 (0x0004) [0x0000000000000000]               

	bool operator==(const FEngineAudioNativeState_OnGround& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_OnGround)) == 0; }
	bool operator!=(const FEngineAudioNativeState_OnGround& other) const { return !(*this == other); }
	bool operator<(const FEngineAudioNativeState_OnGround& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_OnGround)) < 0; }
};

// ScriptStruct TAGame.EngineAudioComponent_TA.EngineAudioNativeState_InAir
// 0x0008 (0x003C - 0x0044)
struct FEngineAudioNativeState_InAir : FEngineAudioNativeState_Clutched
{
	float                                              TimeInAir;                                     // 0x0040 (0x0004) [0x0000000000000000]               

	bool operator==(const FEngineAudioNativeState_InAir& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_InAir)) == 0; }
	bool operator!=(const FEngineAudioNativeState_InAir& other) const { return !(*this == other); }
	bool operator<(const FEngineAudioNativeState_InAir& other) const { return memcmp(this, &other, sizeof(FEngineAudioNativeState_InAir)) < 0; }
};

// ScriptStruct TAGame.HandlingPreset_TA.VehicleAxleData
// 0x0014
struct FVehicleAxleData
{
	float                                              WheelRadius;                                   // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WheelWidth;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     LocalRestPosition;                             // 0x0008 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVehicleAxleData& other) const { return memcmp(this, &other, sizeof(FVehicleAxleData)) == 0; }
	bool operator!=(const FVehicleAxleData& other) const { return !(*this == other); }
	bool operator<(const FVehicleAxleData& other) const { return memcmp(this, &other, sizeof(FVehicleAxleData)) < 0; }
};

// ScriptStruct TAGame.ViralItemFXComponent_TA.ViralFXData
// 0x0018
struct FViralFXData
{
	class AFXActor_TA*                                 FXArchetype;                                   // 0x0000 (0x0008) [0x0001000000000001] (CPF_Edit)    
	float                                              Brightness;                                    // 0x0008 (0x0004) [0x0001000000000001] (CPF_Edit)    
	float                                              GoldTint;                                      // 0x000C (0x0004) [0x0001000000000001] (CPF_Edit)    
	class UAkSoundCue*                                 SFX;                                           // 0x0010 (0x0008) [0x0001000000000001] (CPF_Edit)    

	bool operator==(const FViralFXData& other) const { return memcmp(this, &other, sizeof(FViralFXData)) == 0; }
	bool operator!=(const FViralFXData& other) const { return !(*this == other); }
	bool operator<(const FViralFXData& other) const { return memcmp(this, &other, sizeof(FViralFXData)) < 0; }
};

// ScriptStruct TAGame.Car_KnockOut_TA.ImpulseData
// 0x0008
struct FImpulseData
{
	int32_t                                            CompressedRotation;                            // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              ImpulseSpeed;                                  // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FImpulseData& other) const { return memcmp(this, &other, sizeof(FImpulseData)) == 0; }
	bool operator!=(const FImpulseData& other) const { return !(*this == other); }
	bool operator<(const FImpulseData& other) const { return memcmp(this, &other, sizeof(FImpulseData)) < 0; }
};

// ScriptStruct TAGame.Team_TA.ReplicatedLogoData
// 0x0008
struct FReplicatedLogoData
{
	int32_t                                            LogoID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bSwapColors : 1;                               // 0x0004 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FReplicatedLogoData& other) const { return memcmp(this, &other, sizeof(FReplicatedLogoData)) == 0; }
	bool operator!=(const FReplicatedLogoData& other) const { return !(*this == other); }
	bool operator<(const FReplicatedLogoData& other) const { return memcmp(this, &other, sizeof(FReplicatedLogoData)) < 0; }
};

// ScriptStruct TAGame.CarColorSet_TA.DebugColor
// 0x0014
struct FDebugColor
{
	struct FLinearColor                                Color;                                         // 0x0000 (0x0010) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bPreview : 1;                                  // 0x0010 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FDebugColor& other) const { return memcmp(this, &other, sizeof(FDebugColor)) == 0; }
	bool operator!=(const FDebugColor& other) const { return !(*this == other); }
	bool operator<(const FDebugColor& other) const { return memcmp(this, &other, sizeof(FDebugColor)) < 0; }
};

// ScriptStruct TAGame.CarComponent_Boost_TA.ReplicatedBoostData
// 0x0004
struct FReplicatedBoostData
{
	uint8_t                                            GrantCount;                                    // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            BoostAmount;                                   // 0x0001 (0x0001) [0x0000000000000000]               
	uint8_t                                            Unused1;                                       // 0x0002 (0x0001) [0x0000000000000000]               
	uint8_t                                            Unused2;                                       // 0x0003 (0x0001) [0x0000000000000000]               

	bool operator==(const FReplicatedBoostData& other) const { return memcmp(this, &other, sizeof(FReplicatedBoostData)) == 0; }
	bool operator!=(const FReplicatedBoostData& other) const { return !(*this == other); }
	bool operator<(const FReplicatedBoostData& other) const { return memcmp(this, &other, sizeof(FReplicatedBoostData)) < 0; }
};

// ScriptStruct TAGame.CarPreviewAnim_TA.PreviewAnimKeyframe
// 0x0038
struct FPreviewAnimKeyframe
{
	struct FRotator                                    Rotation;                                      // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Translation;                                   // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FViewTargetTransitionParams                 BlendParams;                                   // 0x0018 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     BouncyChassisForce;                            // 0x0028 (0x000C) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bAddRotation : 1;                              // 0x0034 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bAddTranslation : 1;                           // 0x0034 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)

	bool operator==(const FPreviewAnimKeyframe& other) const { return memcmp(this, &other, sizeof(FPreviewAnimKeyframe)) == 0; }
	bool operator!=(const FPreviewAnimKeyframe& other) const { return !(*this == other); }
	bool operator<(const FPreviewAnimKeyframe& other) const { return memcmp(this, &other, sizeof(FPreviewAnimKeyframe)) < 0; }
};

// ScriptStruct TAGame.CinematicIntroSequence_TA.PressedAxis
// 0x0010
struct FPressedAxis
{
	class FName                                        Key;                                           // 0x0000 (0x0008) [0x0001000000000000]               
	EAxisSign                                          AxisSign;                                      // 0x0008 (0x0001) [0x0001000000000000]               
	float                                              PressTime;                                     // 0x000C (0x0004) [0x0001000000000000]               

	bool operator==(const FPressedAxis& other) const { return memcmp(this, &other, sizeof(FPressedAxis)) == 0; }
	bool operator!=(const FPressedAxis& other) const { return !(*this == other); }
	bool operator<(const FPressedAxis& other) const { return memcmp(this, &other, sizeof(FPressedAxis)) < 0; }
};

// ScriptStruct TAGame.CountryConfig_TA.CountryInfo
// 0x0020
struct FCountryInfo
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Code;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCountryInfo& other) const { return memcmp(this, &other, sizeof(FCountryInfo)) == 0; }
	bool operator!=(const FCountryInfo& other) const { return !(*this == other); }
	bool operator<(const FCountryInfo& other) const { return memcmp(this, &other, sizeof(FCountryInfo)) < 0; }
};

// ScriptStruct TAGame.CrowdActor_TA.CrowdNoiseModifierInstance
// 0x0008
struct FCrowdNoiseModifierInstance
{
	float                                              Value;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Duration;                                      // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FCrowdNoiseModifierInstance& other) const { return memcmp(this, &other, sizeof(FCrowdNoiseModifierInstance)) == 0; }
	bool operator!=(const FCrowdNoiseModifierInstance& other) const { return !(*this == other); }
	bool operator<(const FCrowdNoiseModifierInstance& other) const { return memcmp(this, &other, sizeof(FCrowdNoiseModifierInstance)) < 0; }
};

// ScriptStruct TAGame.CrowdActorSettings_TA.StatCrowdNoise
// 0x0010
struct FStatCrowdNoise
{
	class UStatEvent_TA*                               StatEvent;                                     // 0x0000 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	class UCrowdNoiseModifier_TA*                      Noise;                                         // 0x0008 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FStatCrowdNoise& other) const { return memcmp(this, &other, sizeof(FStatCrowdNoise)) == 0; }
	bool operator!=(const FStatCrowdNoise& other) const { return !(*this == other); }
	bool operator<(const FStatCrowdNoise& other) const { return memcmp(this, &other, sizeof(FStatCrowdNoise)) < 0; }
};

// ScriptStruct TAGame.CrowdActorSettings_TA.BallHitCrowdNoise
// 0x0010
struct FBallHitCrowdNoise
{
	float                                              RelativeSpeed;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UCrowdNoiseModifier_TA*                      Noise;                                         // 0x0008 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FBallHitCrowdNoise& other) const { return memcmp(this, &other, sizeof(FBallHitCrowdNoise)) == 0; }
	bool operator!=(const FBallHitCrowdNoise& other) const { return !(*this == other); }
	bool operator<(const FBallHitCrowdNoise& other) const { return memcmp(this, &other, sizeof(FBallHitCrowdNoise)) < 0; }
};

// ScriptStruct TAGame.CrowdActorSettings_TA.CrowdDefenseSettings
// 0x0014
struct FCrowdDefenseSettings
{
	float                                              DefenseZoneTime;                               // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DefenseZoneDistance;                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UAkSoundCue*                                 Sound;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              ReplayDelay;                                   // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCrowdDefenseSettings& other) const { return memcmp(this, &other, sizeof(FCrowdDefenseSettings)) == 0; }
	bool operator!=(const FCrowdDefenseSettings& other) const { return !(*this == other); }
	bool operator<(const FCrowdDefenseSettings& other) const { return memcmp(this, &other, sizeof(FCrowdDefenseSettings)) < 0; }
};

// ScriptStruct TAGame.CrumbTrailRedefinition_TA.CrumbRedefinedInfo
// 0x0060
struct FCrumbRedefinedInfo
{
	ECrumbRedefinitionType                             RedefinedType;                                 // 0x0000 (0x0001) [0x0001000000000000]               
	ECrumbAction                                       RedefinedAction;                               // 0x0001 (0x0001) [0x0001000000000000]               
	struct FCrumbTrailData                             CrumbData;                                     // 0x0008 (0x0058) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCrumbRedefinedInfo& other) const { return memcmp(this, &other, sizeof(FCrumbRedefinedInfo)) == 0; }
	bool operator!=(const FCrumbRedefinedInfo& other) const { return !(*this == other); }
	bool operator<(const FCrumbRedefinedInfo& other) const { return memcmp(this, &other, sizeof(FCrumbRedefinedInfo)) < 0; }
};

// ScriptStruct TAGame.CurrencyProductSet_TA.CurrencyProduct
// 0x000C
struct FCurrencyProduct
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            CurrencyID;                                    // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Quantity;                                      // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FCurrencyProduct& other) const { return memcmp(this, &other, sizeof(FCurrencyProduct)) == 0; }
	bool operator!=(const FCurrencyProduct& other) const { return !(*this == other); }
	bool operator<(const FCurrencyProduct& other) const { return memcmp(this, &other, sizeof(FCurrencyProduct)) < 0; }
};

// ScriptStruct TAGame.DebugHelpMenu_TA.DebugHelpItem
// 0x0030
struct FDebugHelpItem
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Command;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDebugHelpItem& other) const { return memcmp(this, &other, sizeof(FDebugHelpItem)) == 0; }
	bool operator!=(const FDebugHelpItem& other) const { return !(*this == other); }
	bool operator<(const FDebugHelpItem& other) const { return memcmp(this, &other, sizeof(FDebugHelpItem)) < 0; }
};

// ScriptStruct TAGame.DebugHelpMenu_TA.DebugCategory
// 0x0020
struct FDebugCategory
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FDebugHelpItem>                Items;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDebugCategory& other) const { return memcmp(this, &other, sizeof(FDebugCategory)) == 0; }
	bool operator!=(const FDebugCategory& other) const { return !(*this == other); }
	bool operator<(const FDebugCategory& other) const { return memcmp(this, &other, sizeof(FDebugCategory)) < 0; }
};

// ScriptStruct TAGame.EngagementEventsConfig_TA.EngagementEventData
// 0x0040
struct FEngagementEventData
{
	class FString                                      Description;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EEngagementEventType>                 EventTypes;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           EpochStartTime;                                // 0x0020 (0x0008) [0x0000000000000000]               
	uint64_t                                           EpochEndTime;                                  // 0x0028 (0x0008) [0x0000000000000000]               
	uint32_t                                           bEndingSoon : 1;                               // 0x0030 (0x0004) [0x0000000000002000] [0x00000001] (CPF_Transient)
	uint32_t                                           bLiveNow : 1;                                  // 0x0030 (0x0004) [0x0000000000002000] [0x00000002] (CPF_Transient)
	uint64_t                                           EpochSoonEndTime;                              // 0x0038 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FEngagementEventData& other) const { return memcmp(this, &other, sizeof(FEngagementEventData)) == 0; }
	bool operator!=(const FEngagementEventData& other) const { return !(*this == other); }
	bool operator<(const FEngagementEventData& other) const { return memcmp(this, &other, sizeof(FEngagementEventData)) < 0; }
};

// ScriptStruct TAGame.EngagementEventsConfig_TA.EngagementEventStatus
// 0x0030
struct FEngagementEventStatus
{
	uint32_t                                           bEventActive : 1;                              // 0x0000 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bEventEndingSoon : 1;                          // 0x0000 (0x0004) [0x0000000040002000] [0x00000002] (CPF_Transient | CPF_DataBinding)
	uint64_t                                           EpochTimeStart;                                // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           EpochTimeEnd;                                  // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint64_t                                           EpochTimeRemaining;                            // 0x0018 (0x0008) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	uint32_t                                           bStartNotificationShown : 1;                   // 0x0020 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint64_t                                           EpochTimeStartForNotificationShown;            // 0x0028 (0x0008) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FEngagementEventStatus& other) const { return memcmp(this, &other, sizeof(FEngagementEventStatus)) == 0; }
	bool operator!=(const FEngagementEventStatus& other) const { return !(*this == other); }
	bool operator<(const FEngagementEventStatus& other) const { return memcmp(this, &other, sizeof(FEngagementEventStatus)) < 0; }
};

// ScriptStruct TAGame.EngineAudioProfile_TA.AudioMinMax
// 0x0008
struct FAudioMinMax
{
	float                                              Min;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              RandRange;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAudioMinMax& other) const { return memcmp(this, &other, sizeof(FAudioMinMax)) == 0; }
	bool operator!=(const FAudioMinMax& other) const { return !(*this == other); }
	bool operator<(const FAudioMinMax& other) const { return memcmp(this, &other, sizeof(FAudioMinMax)) < 0; }
};

// ScriptStruct TAGame.EngineAudioProfile_TA.AudioGear
// 0x0010
struct FAudioGear
{
	struct FAudioMinMax                                RPMShiftDownRange;                             // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FAudioMinMax                                RPMShiftUpRange;                               // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAudioGear& other) const { return memcmp(this, &other, sizeof(FAudioGear)) == 0; }
	bool operator!=(const FAudioGear& other) const { return !(*this == other); }
	bool operator<(const FAudioGear& other) const { return memcmp(this, &other, sizeof(FAudioGear)) < 0; }
};

// ScriptStruct TAGame.EOSShopPurchaseEvent_X.EOSShopPurchaseEventProduct
// 0x0014
struct FEOSShopPurchaseEventProduct
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	EProductQuality                                    Quality;                                       // 0x0004 (0x0001) [0x0000000000000000]               
	int32_t                                            PaintID;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            CertifiedStatID;                               // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            SpecialEditionID;                              // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FEOSShopPurchaseEventProduct& other) const { return memcmp(this, &other, sizeof(FEOSShopPurchaseEventProduct)) == 0; }
	bool operator!=(const FEOSShopPurchaseEventProduct& other) const { return !(*this == other); }
	bool operator<(const FEOSShopPurchaseEventProduct& other) const { return memcmp(this, &other, sizeof(FEOSShopPurchaseEventProduct)) < 0; }
};

// ScriptStruct TAGame.OnlineSaveRecord_TA.OnlineSaveObject
// 0x0028
struct FOnlineSaveObject
{
	class FString                                      Path;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Data;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UObject*                                     DataObj;                                       // 0x0020 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FOnlineSaveObject& other) const { return memcmp(this, &other, sizeof(FOnlineSaveObject)) == 0; }
	bool operator!=(const FOnlineSaveObject& other) const { return !(*this == other); }
	bool operator<(const FOnlineSaveObject& other) const { return memcmp(this, &other, sizeof(FOnlineSaveObject)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SRemediation
// 0x0018
struct FK3SRemediation
{
	ERemediationMethod                                 remediationMethod;                             // 0x0000 (0x0001) [0x0000000000000000]               
	class FString                                      remediationUrl;                                // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SRemediation& other) const { return memcmp(this, &other, sizeof(FK3SRemediation)) == 0; }
	bool operator!=(const FK3SRemediation& other) const { return !(*this == other); }
	bool operator<(const FK3SRemediation& other) const { return memcmp(this, &other, sizeof(FK3SRemediation)) < 0; }
};

// ScriptStruct TAGame.EOSPermissions_TA.PolicyDecisionAggregation
// 0x0030
struct FPolicyDecisionAggregation
{
	uint32_t                                           bDecisionPresent : 1;                          // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDecisionDenied : 1;                           // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	class FString                                      DenyReason;                                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FK3SRemediation                             PrimaryRemediation;                            // 0x0018 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPolicyDecisionAggregation& other) const { return memcmp(this, &other, sizeof(FPolicyDecisionAggregation)) == 0; }
	bool operator!=(const FPolicyDecisionAggregation& other) const { return !(*this == other); }
	bool operator<(const FPolicyDecisionAggregation& other) const { return memcmp(this, &other, sizeof(FPolicyDecisionAggregation)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3STranslation
// 0x0030
struct FK3STranslation
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      UserNotice;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ParentNotice;                                  // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3STranslation& other) const { return memcmp(this, &other, sizeof(FK3STranslation)) == 0; }
	bool operator!=(const FK3STranslation& other) const { return !(*this == other); }
	bool operator<(const FK3STranslation& other) const { return memcmp(this, &other, sizeof(FK3STranslation)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3STranslations
// 0x0030
struct FK3STranslations
{
	struct FK3STranslation                             en;                                            // 0x0000 (0x0030) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3STranslations& other) const { return memcmp(this, &other, sizeof(FK3STranslations)) == 0; }
	bool operator!=(const FK3STranslations& other) const { return !(*this == other); }
	bool operator<(const FK3STranslations& other) const { return memcmp(this, &other, sizeof(FK3STranslations)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SOptions
// 0x0040
struct FK3SOptions
{
	struct FK3STranslations                            Translations;                                  // 0x0000 (0x0030) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SOptions& other) const { return memcmp(this, &other, sizeof(FK3SOptions)) == 0; }
	bool operator!=(const FK3SOptions& other) const { return !(*this == other); }
	bool operator<(const FK3SOptions& other) const { return memcmp(this, &other, sizeof(FK3SOptions)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SAgeBracket
// 0x0050
struct FK3SAgeBracket
{
	class FString                                      ConsentTypeRequired;                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ConsentTypeUnderParentalControl;               // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DefaultValue;                                  // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DefaultParentLimit;                            // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      EnforcedLimit;                                 // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SAgeBracket& other) const { return memcmp(this, &other, sizeof(FK3SAgeBracket)) == 0; }
	bool operator!=(const FK3SAgeBracket& other) const { return !(*this == other); }
	bool operator<(const FK3SAgeBracket& other) const { return memcmp(this, &other, sizeof(FK3SAgeBracket)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SDefinition
// 0x0174
struct FK3SDefinition
{
	class TArray<struct FK3SOptions>                   Options;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FK3STranslations                            Translations;                                  // 0x0010 (0x0030) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FK3SAgeBracket                              AgeBracket;                                    // 0x0040 (0x0050) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FK3SAgeBracket                              PreviousAgeBracket;                            // 0x0090 (0x0050) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      OrgId;                                         // 0x00E0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ProductID;                                     // 0x00F0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Namespace;                                     // 0x0100 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SettingName;                                   // 0x0110 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ValueType;                                     // 0x0120 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      NumericValueFormat;                            // 0x0130 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AllowProductOverrides;                         // 0x0140 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      RestrictiveOrder;                              // 0x0150 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            NumberOfDecimals;                              // 0x0160 (0x0004) [0x0000000000000000]               
	int32_t                                            Min;                                           // 0x0164 (0x0004) [0x0000000000000000]               
	int32_t                                            Max;                                           // 0x0168 (0x0004) [0x0000000000000000]               
	int32_t                                            IncrementOrDecrementBy;                        // 0x016C (0x0004) [0x0000000000000000]               
	uint32_t                                           InheritFromOrg : 1;                            // 0x0170 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           UserHidden : 1;                                // 0x0170 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           UserReadOnly : 1;                              // 0x0170 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           Required : 1;                                  // 0x0170 (0x0004) [0x0000000000000000] [0x00000008] 

	bool operator==(const FK3SDefinition& other) const { return memcmp(this, &other, sizeof(FK3SDefinition)) == 0; }
	bool operator!=(const FK3SDefinition& other) const { return !(*this == other); }
	bool operator<(const FK3SDefinition& other) const { return memcmp(this, &other, sizeof(FK3SDefinition)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SSetting
// 0x01EC
struct FK3SSetting
{
	struct FK3SDefinition                              Definition;                                    // 0x0000 (0x0178) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           PreferredValueUpdatedAt;                       // 0x0178 (0x0008) [0x0000000000000000]               
	uint64_t                                           LastGraduatedAt;                               // 0x0180 (0x0008) [0x0000000000000000]               
	class FString                                      Namespace;                                     // 0x0188 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SettingName;                                   // 0x0198 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PreferredValue;                                // 0x01A8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ParentLimit;                                   // 0x01B8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      EffectiveValue;                                // 0x01C8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      EffectiveSource;                               // 0x01D8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           ParentLimitFromOrgLevel : 1;                   // 0x01E8 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           PreferredValueFromOrgLevel : 1;                // 0x01E8 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           IsOrgLevel : 1;                                // 0x01E8 (0x0004) [0x0000000000000000] [0x00000004] 

	bool operator==(const FK3SSetting& other) const { return memcmp(this, &other, sizeof(FK3SSetting)) == 0; }
	bool operator!=(const FK3SSetting& other) const { return !(*this == other); }
	bool operator<(const FK3SSetting& other) const { return memcmp(this, &other, sizeof(FK3SSetting)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SResponse
// 0x0010
struct FK3SResponse
{
	class TArray<struct FK3SSetting>                   Settings;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SResponse& other) const { return memcmp(this, &other, sizeof(FK3SResponse)) == 0; }
	bool operator!=(const FK3SResponse& other) const { return !(*this == other); }
	bool operator<(const FK3SResponse& other) const { return memcmp(this, &other, sizeof(FK3SResponse)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SFirstTimeDefaults
// 0x0070
struct FK3SFirstTimeDefaults
{
	class FString                                      AgeGateDefaultVoice;                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AgeGateDefaultText;                            // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AgeGateDefaultTrade;                           // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ItemShopNotificationsDefaultEnabled;           // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AgeGateDefaultVoiceReporting;                  // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AgeGateDefaultTextReporting;                   // 0x0050 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      AgeGateDefaultFilterMatureLanguage;            // 0x0060 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SFirstTimeDefaults& other) const { return memcmp(this, &other, sizeof(FK3SFirstTimeDefaults)) == 0; }
	bool operator!=(const FK3SFirstTimeDefaults& other) const { return !(*this == other); }
	bool operator<(const FK3SFirstTimeDefaults& other) const { return memcmp(this, &other, sizeof(FK3SFirstTimeDefaults)) < 0; }
};

// ScriptStruct TAGame.EOSUserPermissions_TA.EOSPermissionsResult
// 0x0064
struct FEOSPermissionsResult
{
	uint32_t                                           Disabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           AllowedToAcquire : 1;                          // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           AllowedToMakePurchases : 1;                    // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           CanSeeMatureLanguage : 1;                      // 0x0000 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           CanAcceptFriendRequest : 1;                    // 0x0000 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           CanRecieveInGameItems : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           CanSeeThirdPartyNames : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000040] 
	uint32_t                                           CanDisplayMyUserName : 1;                      // 0x0000 (0x0004) [0x0000000000000000] [0x00000080] 
	uint32_t                                           CanSeeOtherPlayersNames : 1;                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000100] 
	uint32_t                                           CanUseVoiceChat : 1;                           // 0x0000 (0x0004) [0x0000000000000000] [0x00000200] 
	uint32_t                                           CanVoiceChatWithUnknowns : 1;                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000400] 
	uint32_t                                           CanUseHousepartyCasting : 1;                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000800] 
	class FString                                      PlaytimeReportingFrequency;                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           PurchaseReportingEnabled : 1;                  // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           CanUseTextChat : 1;                            // 0x0018 (0x0004) [0x0000000000000000] [0x00000002] 
	class FString                                      UgcViewing;                                    // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      UgcSharing;                                    // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      VoiceChat;                                     // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TextChat;                                      // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           RequirePinToAddFriend : 1;                     // 0x0060 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FEOSPermissionsResult& other) const { return memcmp(this, &other, sizeof(FEOSPermissionsResult)) == 0; }
	bool operator!=(const FEOSPermissionsResult& other) const { return !(*this == other); }
	bool operator<(const FEOSPermissionsResult& other) const { return memcmp(this, &other, sizeof(FEOSPermissionsResult)) < 0; }
};

// ScriptStruct TAGame.EOSUserPermissions_TA.EOSPermissionsResponse
// 0x0138
struct FEOSPermissionsResponse
{
	struct FEOSPermissionsResult                       Result;                                        // 0x0000 (0x0068) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FEOSPermissionsResult                       NamespaceSetting;                              // 0x0068 (0x0068) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FEOSPermissionsResult                       UserSetting;                                   // 0x00D0 (0x0068) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FEOSPermissionsResponse& other) const { return memcmp(this, &other, sizeof(FEOSPermissionsResponse)) == 0; }
	bool operator!=(const FEOSPermissionsResponse& other) const { return !(*this == other); }
	bool operator<(const FEOSPermissionsResponse& other) const { return memcmp(this, &other, sizeof(FEOSPermissionsResponse)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceManager_TA.PendingRoomJoin
// 0x0018
struct FPendingRoomJoin
{
	class UOnlinePlayer_X*                             OnlinePlayer;                                  // 0x0000 (0x0008) [0x0001000000002000] (CPF_Transient)
	class FString                                      RoomName;                                      // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPendingRoomJoin& other) const { return memcmp(this, &other, sizeof(FPendingRoomJoin)) == 0; }
	bool operator!=(const FPendingRoomJoin& other) const { return !(*this == other); }
	bool operator<(const FPendingRoomJoin& other) const { return memcmp(this, &other, sizeof(FPendingRoomJoin)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceManager_TA.VoiceRecordingBufferData
// 0x0011
struct FVoiceRecordingBufferData
{
	uint64_t                                           RecordStartTime;                               // 0x0000 (0x0008) [0x0001000000000000]               
	uint64_t                                           RecordEndTime;                                 // 0x0008 (0x0008) [0x0001000000000000]               
	EVoiceRoomType                                     RoomType;                                      // 0x0010 (0x0001) [0x0001000000000000]               

	bool operator==(const FVoiceRecordingBufferData& other) const { return memcmp(this, &other, sizeof(FVoiceRecordingBufferData)) == 0; }
	bool operator!=(const FVoiceRecordingBufferData& other) const { return !(*this == other); }
	bool operator<(const FVoiceRecordingBufferData& other) const { return memcmp(this, &other, sizeof(FVoiceRecordingBufferData)) < 0; }
};

// ScriptStruct TAGame.EOSVoiceMetrics_TA.UserVoiceSettings
// 0x0020
struct FUserVoiceSettings
{
	EChatFilter                                        VoiceChatFilter;                               // 0x0000 (0x0001) [0x0001000000000000]               
	EVoiceInputMode                                    VoiceInputMode;                                // 0x0001 (0x0001) [0x0001000000000000]               
	uint32_t                                           bMainMenuNotifications : 1;                    // 0x0004 (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bMatchNotifications : 1;                       // 0x0004 (0x0004) [0x0001000000000000] [0x00000002] 
	uint32_t                                           bTextNotifications : 1;                        // 0x0004 (0x0004) [0x0001000000000000] [0x00000004] 
	float                                              OutputVolume;                                  // 0x0008 (0x0004) [0x0001000000000000]               
	EVoiceRoomType                                     PreferredRoomType;                             // 0x000C (0x0001) [0x0001000000000000]               
	class TArray<class FString>                        MutedPlayers;                                  // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUserVoiceSettings& other) const { return memcmp(this, &other, sizeof(FUserVoiceSettings)) == 0; }
	bool operator!=(const FUserVoiceSettings& other) const { return !(*this == other); }
	bool operator<(const FUserVoiceSettings& other) const { return memcmp(this, &other, sizeof(FUserVoiceSettings)) < 0; }
};

// ScriptStruct TAGame.ESportConfig_TA.ESportEventData
// 0x00D4
struct FESportEventData
{
	class FString                                      Image;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Title;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      URL;                                           // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      UTCStartTime;                                  // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      UTCEndTime;                                    // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bStartingSoon : 1;                             // 0x0060 (0x0004) [0x0000000040002000] [0x00000001] (CPF_Transient | CPF_DataBinding)
	uint32_t                                           bLiveNow : 1;                                  // 0x0060 (0x0004) [0x0000000040002000] [0x00000002] (CPF_Transient | CPF_DataBinding)
	class UTexture*                                    ImageTexture;                                  // 0x0068 (0x0008) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            ImageTextureSizeX;                             // 0x0070 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	int32_t                                            ImageTextureSizeY;                             // 0x0074 (0x0004) [0x0000000040002000] (CPF_Transient | CPF_DataBinding)
	class FString                                      StartTime;                                     // 0x0078 (0x0010) [0x0000000040402000] (CPF_Transient | CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      EndTime;                                       // 0x0088 (0x0010) [0x0000000040402000] (CPF_Transient | CPF_NeedCtorLink | CPF_DataBinding)
	uint64_t                                           EpochSoonStartTime;                            // 0x0098 (0x0008) [0x0000000000002000] (CPF_Transient)
	uint64_t                                           EpochStartTime;                                // 0x00A0 (0x0008) [0x0000000000002000] (CPF_Transient)
	uint64_t                                           EpochEndTime;                                  // 0x00A8 (0x0008) [0x0000000000002000] (CPF_Transient)
	class FString                                      ButtonTitle;                                   // 0x00B0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ButtonDescription;                             // 0x00C0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bShowLiveNow : 1;                              // 0x00D0 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bCanNavigateToEventURL : 1;                    // 0x00D0 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bWorldCup : 1;                                 // 0x00D0 (0x0004) [0x0001000040000000] [0x00000004] (CPF_DataBinding)

	bool operator==(const FESportEventData& other) const { return memcmp(this, &other, sizeof(FESportEventData)) == 0; }
	bool operator!=(const FESportEventData& other) const { return !(*this == other); }
	bool operator<(const FESportEventData& other) const { return memcmp(this, &other, sizeof(FESportEventData)) < 0; }
};

// ScriptStruct TAGame.EulaSave_TA.EulaVersion
// 0x0004
struct FEulaVersion
{
	int32_t                                            TextHash;                                      // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FEulaVersion& other) const { return memcmp(this, &other, sizeof(FEulaVersion)) == 0; }
	bool operator!=(const FEulaVersion& other) const { return !(*this == other); }
	bool operator<(const FEulaVersion& other) const { return memcmp(this, &other, sizeof(FEulaVersion)) < 0; }
};

// ScriptStruct TAGame.FaceIt_TA.FaceItMatchInfo
// 0x0080
struct FFaceItMatchInfo
{
	int32_t                                            MatchID;                                       // 0x0000 (0x0004) [0x0001000000000000]               
	int32_t                                            ServerId;                                      // 0x0004 (0x0004) [0x0001000000000000]               
	class FString                                      TeamNameA;                                     // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      TeamNameB;                                     // 0x0018 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsSpectator : 1;                              // 0x0028 (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bIsCrossPlatform : 1;                          // 0x0028 (0x0004) [0x0001000000000000] [0x00000002] 
	int32_t                                            TeamSize;                                      // 0x002C (0x0004) [0x0001000000000000]               
	int32_t                                            PartnerID;                                     // 0x0030 (0x0004) [0x0001000000000000]               
	struct FUniqueNetId                                PlayerID;                                      // 0x0038 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFaceItMatchInfo& other) const { return memcmp(this, &other, sizeof(FFaceItMatchInfo)) == 0; }
	bool operator!=(const FFaceItMatchInfo& other) const { return !(*this == other); }
	bool operator<(const FFaceItMatchInfo& other) const { return memcmp(this, &other, sizeof(FFaceItMatchInfo)) < 0; }
};

// ScriptStruct TAGame.FaceItConfig_TA.PartnerMapping
// 0x0018
struct FPartnerMapping
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0001000000000000]               
	class FString                                      Name;                                          // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPartnerMapping& other) const { return memcmp(this, &other, sizeof(FPartnerMapping)) == 0; }
	bool operator!=(const FPartnerMapping& other) const { return !(*this == other); }
	bool operator<(const FPartnerMapping& other) const { return memcmp(this, &other, sizeof(FPartnerMapping)) < 0; }
};

// ScriptStruct TAGame.FirstTimeExperienceRedefinition_TA.RedefinedInfo
// 0x0040
struct FRedefinedInfo
{
	EFTERedefinitionAction                             RedefinedAction;                               // 0x0000 (0x0001) [0x0000000000000000]               
	EFTERedefinitionType                               RedefinedType;                                 // 0x0001 (0x0001) [0x0000000000000000]               
	class FName                                        GroupName;                                     // 0x0004 (0x0008) [0x0000000000000000]               
	class TArray<class FName>                          CheckpointNames;                               // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UTriggerClump_TA*>              TriggerClumps;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        NameValue;                                     // 0x0030 (0x0008) [0x0000000000000000]               
	int32_t                                            IntValue;                                      // 0x0038 (0x0004) [0x0000000000000000]               
	uint32_t                                           bValue : 1;                                    // 0x003C (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FRedefinedInfo& other) const { return memcmp(this, &other, sizeof(FRedefinedInfo)) == 0; }
	bool operator!=(const FRedefinedInfo& other) const { return !(*this == other); }
	bool operator<(const FRedefinedInfo& other) const { return memcmp(this, &other, sizeof(FRedefinedInfo)) < 0; }
};

// ScriptStruct TAGame.FlockActor_TA.FlockAgent
// 0x0038
struct FFlockAgent
{
	uint32_t                                           bWaitingForOtherAgents : 1;                    // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              DistanceAlongSpline;                           // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              Scale;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	struct FVector                                     Position;                                      // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     NormalizedSplineOffset;                        // 0x0024 (0x000C) [0x0000000000000000]               
	class ASplineActor*                                CurrentSplineActor;                            // 0x0030 (0x0008) [0x0000000000000000]               

	bool operator==(const FFlockAgent& other) const { return memcmp(this, &other, sizeof(FFlockAgent)) == 0; }
	bool operator!=(const FFlockAgent& other) const { return !(*this == other); }
	bool operator<(const FFlockAgent& other) const { return memcmp(this, &other, sizeof(FFlockAgent)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommands_TA.ActivateFreeplayCommandOutParams
// 0x0060
struct FActivateFreeplayCommandOutParams
{
	struct FFreeplayCommandsMetricsData                PreActivationData;                             // 0x0000 (0x0058) [0x0000000000400000] (CPF_NeedCtorLink)
	class UError*                                      ExecutionError;                                // 0x0058 (0x0008) [0x0000000000000000]               

	bool operator==(const FActivateFreeplayCommandOutParams& other) const { return memcmp(this, &other, sizeof(FActivateFreeplayCommandOutParams)) == 0; }
	bool operator!=(const FActivateFreeplayCommandOutParams& other) const { return !(*this == other); }
	bool operator<(const FActivateFreeplayCommandOutParams& other) const { return memcmp(this, &other, sizeof(FActivateFreeplayCommandOutParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.ModifyRBStateInParams
// 0x0064
struct FModifyRBStateInParams
{
	struct FReplicatedRBState                          InRBState;                                     // 0x0000 (0x0040) [0x0000000000000000]               
	struct FVector                                     NewLocation;                                   // 0x0040 (0x000C) [0x0000000000000000]               
	struct FVector                                     NewLinearVelocity;                             // 0x004C (0x000C) [0x0000000000000000]               
	struct FVector                                     NewAngularVelocity;                            // 0x0058 (0x000C) [0x0000000000000000]               

	bool operator==(const FModifyRBStateInParams& other) const { return memcmp(this, &other, sizeof(FModifyRBStateInParams)) == 0; }
	bool operator!=(const FModifyRBStateInParams& other) const { return !(*this == other); }
	bool operator<(const FModifyRBStateInParams& other) const { return memcmp(this, &other, sizeof(FModifyRBStateInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateVerticalLaunchSpeedInParams
// 0x0010
struct FCalculateVerticalLaunchSpeedInParams
{
	float                                              TargetHeight;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              StartHeight;                                   // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              FlightTime;                                    // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              Gravity;                                       // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FCalculateVerticalLaunchSpeedInParams& other) const { return memcmp(this, &other, sizeof(FCalculateVerticalLaunchSpeedInParams)) == 0; }
	bool operator!=(const FCalculateVerticalLaunchSpeedInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateVerticalLaunchSpeedInParams& other) const { return memcmp(this, &other, sizeof(FCalculateVerticalLaunchSpeedInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateBallInFrontLocationInParams
// 0x002C
struct FCalculateBallInFrontLocationInParams
{
	float                                              BallRadius;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              BallInFrontDistance;                           // 0x0004 (0x0004) [0x0000000000000000]               
	struct FRotator                                    CarRotation;                                   // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocalCollisionExtent;                       // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocation;                                   // 0x0020 (0x000C) [0x0000000000000000]               

	bool operator==(const FCalculateBallInFrontLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallInFrontLocationInParams)) == 0; }
	bool operator!=(const FCalculateBallInFrontLocationInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateBallInFrontLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallInFrontLocationInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateBallOnCarLocationInParams
// 0x0048
struct FCalculateBallOnCarLocationInParams
{
	struct FRotator                                    CarRotation;                                   // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocation;                                   // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     CarAcceleration;                               // 0x0018 (0x000C) [0x0000000000000000]               
	float                                              CarSpeedPerc;                                  // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              CarTurnPerc;                                   // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              BaseForwardOffset;                             // 0x002C (0x0004) [0x0000000000000000]               
	float                                              BaseUpOffset;                                  // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              ForwardOffsetFromTurn;                         // 0x0034 (0x0004) [0x0000000000000000]               
	float                                              AccelerationEffectMultiplier;                  // 0x0038 (0x0004) [0x0000000000000000]               
	float                                              MaxRightOffset;                                // 0x003C (0x0004) [0x0000000000000000]               
	float                                              SlowRightOffsetPerc;                           // 0x0040 (0x0004) [0x0000000000000000]               
	float                                              MinUpOffsetPerc;                               // 0x0044 (0x0004) [0x0000000000000000]               

	bool operator==(const FCalculateBallOnCarLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallOnCarLocationInParams)) == 0; }
	bool operator!=(const FCalculateBallOnCarLocationInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateBallOnCarLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallOnCarLocationInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateBallOnCarInAirLocationInParams
// 0x0030
struct FCalculateBallOnCarInAirLocationInParams
{
	float                                              BallRadius;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              BallOnCarDistance;                             // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              CarLocalCollisionZ;                            // 0x0008 (0x0004) [0x0000000000000000]               
	struct FRotator                                    CarRotation;                                   // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocation;                                   // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarCurrentLinearVelocity;                      // 0x0024 (0x000C) [0x0000000000000000]               

	bool operator==(const FCalculateBallOnCarInAirLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallOnCarInAirLocationInParams)) == 0; }
	bool operator!=(const FCalculateBallOnCarInAirLocationInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateBallOnCarInAirLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateBallOnCarInAirLocationInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateLaunchVectorInParams
// 0x0024
struct FCalculateLaunchVectorInParams
{
	struct FVector                                     StartLocation;                                 // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     TargetLocation;                                // 0x000C (0x000C) [0x0000000000000000]               
	float                                              Gravity;                                       // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              HorizontalSpeed;                               // 0x001C (0x0004) [0x0000000000000000]               
	float                                              MaxVerticalLaunchSpeedRatio;                   // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FCalculateLaunchVectorInParams& other) const { return memcmp(this, &other, sizeof(FCalculateLaunchVectorInParams)) == 0; }
	bool operator!=(const FCalculateLaunchVectorInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateLaunchVectorInParams& other) const { return memcmp(this, &other, sizeof(FCalculateLaunchVectorInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateRedirectPassLocationInParams
// 0x004C
struct FCalculateRedirectPassLocationInParams
{
	struct FVector                                     BallStartLocation;                             // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarStartLocation;                              // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     CarStartVelocity;                              // 0x0018 (0x000C) [0x0000000000000000]               
	struct FVector                                     BestGoalLocation;                              // 0x0024 (0x000C) [0x0000000000000000]               
	float                                              VelocityWeight;                                // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              VelocityZWeight;                               // 0x0034 (0x0004) [0x0000000000000000]               
	float                                              GoalWeight;                                    // 0x0038 (0x0004) [0x0000000000000000]               
	float                                              BallHorizontalSpeed;                           // 0x003C (0x0004) [0x0000000000000000]               
	float                                              MaxGoalLeading;                                // 0x0040 (0x0004) [0x0000000000000000]               
	float                                              AdditionalTargetHeight;                        // 0x0044 (0x0004) [0x0000000000000000]               
	int32_t                                            Iterations;                                    // 0x0048 (0x0004) [0x0000000000000000]               

	bool operator==(const FCalculateRedirectPassLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateRedirectPassLocationInParams)) == 0; }
	bool operator!=(const FCalculateRedirectPassLocationInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateRedirectPassLocationInParams& other) const { return memcmp(this, &other, sizeof(FCalculateRedirectPassLocationInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateRedirectHorizontalLaunchSpeedInParams
// 0x002C
struct FCalculateRedirectHorizontalLaunchSpeedInParams
{
	struct FVector                                     BallLocation;                                  // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     CarLocation;                                   // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     CarVelocity;                                   // 0x0018 (0x000C) [0x0000000000000000]               
	float                                              MaxHorizontalLaunchSpeed;                      // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              SpeedDropoffMaxRange;                          // 0x0028 (0x0004) [0x0000000000000000]               

	bool operator==(const FCalculateRedirectHorizontalLaunchSpeedInParams& other) const { return memcmp(this, &other, sizeof(FCalculateRedirectHorizontalLaunchSpeedInParams)) == 0; }
	bool operator!=(const FCalculateRedirectHorizontalLaunchSpeedInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateRedirectHorizontalLaunchSpeedInParams& other) const { return memcmp(this, &other, sizeof(FCalculateRedirectHorizontalLaunchSpeedInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateShotOnGoalSpeedHoopsInParams
// 0x001C
struct FCalculateShotOnGoalSpeedHoopsInParams
{
	float                                              MaxLaunchSpeed;                                // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              DropoffRange;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              MinSpeedReductionAngle;                        // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              AboveNetSpeedReduction;                        // 0x000C (0x0004) [0x0000000000000000]               
	struct FVector                                     BallProximityToRim;                            // 0x0010 (0x000C) [0x0000000000000000]               

	bool operator==(const FCalculateShotOnGoalSpeedHoopsInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalSpeedHoopsInParams)) == 0; }
	bool operator!=(const FCalculateShotOnGoalSpeedHoopsInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateShotOnGoalSpeedHoopsInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalSpeedHoopsInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateShotOnGoalLocationHoopsInParams
// 0x0034
struct FCalculateShotOnGoalLocationHoopsInParams
{
	float                                              SurfaceHeight;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              GoalRadius;                                    // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              WidthPosition;                                 // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              LengthPosition;                                // 0x000C (0x0004) [0x0000000000000000]               
	struct FVector                                     BackboardDirection;                            // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     BackboardLocation;                             // 0x001C (0x000C) [0x0000000000000000]               
	struct FVector                                     GoalCenter;                                    // 0x0028 (0x000C) [0x0000000000000000]               

	bool operator==(const FCalculateShotOnGoalLocationHoopsInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalLocationHoopsInParams)) == 0; }
	bool operator!=(const FCalculateShotOnGoalLocationHoopsInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateShotOnGoalLocationHoopsInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalLocationHoopsInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.CalculateShotOnGoalLocationStandardInParams
// 0x002C
struct FCalculateShotOnGoalLocationStandardInParams
{
	float                                              BallRadius;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              HorizontalGoalPosition;                        // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              VerticalGoalPosition;                          // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              GoalVolumeHalfWidth;                           // 0x000C (0x0004) [0x0000000000000000]               
	float                                              GoalVolumeHalfHeight;                          // 0x0010 (0x0004) [0x0000000000000000]               
	struct FVector                                     GoalWorldFrontCenter;                          // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     GoalForward;                                   // 0x0020 (0x000C) [0x0000000000000000]               

	bool operator==(const FCalculateShotOnGoalLocationStandardInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalLocationStandardInParams)) == 0; }
	bool operator!=(const FCalculateShotOnGoalLocationStandardInParams& other) const { return !(*this == other); }
	bool operator<(const FCalculateShotOnGoalLocationStandardInParams& other) const { return memcmp(this, &other, sizeof(FCalculateShotOnGoalLocationStandardInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplayCommandsStatics_TA.GetTargetLocationFromFlightTimeInParams
// 0x0024
struct FGetTargetLocationFromFlightTimeInParams
{
	struct FVector                                     TargetStartLocation;                           // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     TargetVelocity;                                // 0x000C (0x000C) [0x0000000000000000]               
	float                                              FlightTime;                                    // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              VelocityWeight;                                // 0x001C (0x0004) [0x0000000000000000]               
	float                                              VelocityZWeight;                               // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FGetTargetLocationFromFlightTimeInParams& other) const { return memcmp(this, &other, sizeof(FGetTargetLocationFromFlightTimeInParams)) == 0; }
	bool operator!=(const FGetTargetLocationFromFlightTimeInParams& other) const { return !(*this == other); }
	bool operator<(const FGetTargetLocationFromFlightTimeInParams& other) const { return memcmp(this, &other, sizeof(FGetTargetLocationFromFlightTimeInParams)) < 0; }
};

// ScriptStruct TAGame.FreeplaySessionManager_TA.FreeplaySettings
// 0x0002
struct FFreeplaySettings
{
	EGoalResetType                                     GoalResetValue;                                // 0x0000 (0x0001) [0x0000000000002000] (CPF_Transient)
	EBoostFillType                                     BoostFillValue;                                // 0x0001 (0x0001) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FFreeplaySettings& other) const { return memcmp(this, &other, sizeof(FFreeplaySettings)) == 0; }
	bool operator!=(const FFreeplaySettings& other) const { return !(*this == other); }
	bool operator<(const FFreeplaySettings& other) const { return memcmp(this, &other, sizeof(FFreeplaySettings)) < 0; }
};

// ScriptStruct TAGame.FriendsListBuilder_TA.PersonaUpdateData
// 0x0119
struct FPersonaUpdateData
{
	struct FOnlineFriend                               FriendData;                                    // 0x0000 (0x0118) [0x0000000000400000] (CPF_NeedCtorLink)
	EPersonaInfoOrigin                                 Origin;                                        // 0x0118 (0x0001) [0x0000000000000000]               

	bool operator==(const FPersonaUpdateData& other) const { return memcmp(this, &other, sizeof(FPersonaUpdateData)) == 0; }
	bool operator!=(const FPersonaUpdateData& other) const { return !(*this == other); }
	bool operator<(const FPersonaUpdateData& other) const { return memcmp(this, &other, sizeof(FPersonaUpdateData)) < 0; }
};

// ScriptStruct TAGame.FriendsListUtils_TA.FriendInfoCounts
// 0x0010
struct FFriendInfoCounts
{
	int32_t                                            OnlinePlatform;                                // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            InGamePlatform;                                // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            OnlineEpic;                                    // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            InGameEpic;                                    // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FFriendInfoCounts& other) const { return memcmp(this, &other, sizeof(FFriendInfoCounts)) == 0; }
	bool operator!=(const FFriendInfoCounts& other) const { return !(*this == other); }
	bool operator<(const FFriendInfoCounts& other) const { return memcmp(this, &other, sizeof(FFriendInfoCounts)) < 0; }
};

// ScriptStruct TAGame.FXActor_Boost_TA.ParticleBodyParameterSet
// 0x0018
struct FParticleBodyParameterSet
{
	class FName                                        AttachmentName;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FParticleSysParam>             Parameters;                                    // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FParticleBodyParameterSet& other) const { return memcmp(this, &other, sizeof(FParticleBodyParameterSet)) == 0; }
	bool operator!=(const FParticleBodyParameterSet& other) const { return !(*this == other); }
	bool operator<(const FParticleBodyParameterSet& other) const { return memcmp(this, &other, sizeof(FParticleBodyParameterSet)) < 0; }
};

// ScriptStruct TAGame.FXActor_Boost_TA.ParticleParameterSet
// 0x0020
struct FParticleParameterSet
{
	class TArray<struct FParticleSysParam>             Parameters;                                    // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FParticleSysParam>             DrivingParameters;                             // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FParticleParameterSet& other) const { return memcmp(this, &other, sizeof(FParticleParameterSet)) == 0; }
	bool operator!=(const FParticleParameterSet& other) const { return !(*this == other); }
	bool operator<(const FParticleParameterSet& other) const { return memcmp(this, &other, sizeof(FParticleParameterSet)) < 0; }
};

// ScriptStruct TAGame.FXActor_Boost_TA.BoostMeshMaterialOverride
// 0x0018
struct FBoostMeshMaterialOverride
{
	class UMaterialInterface*                          Material;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<int32_t>                              Index;                                         // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FBoostMeshMaterialOverride& other) const { return memcmp(this, &other, sizeof(FBoostMeshMaterialOverride)) == 0; }
	bool operator!=(const FBoostMeshMaterialOverride& other) const { return !(*this == other); }
	bool operator<(const FBoostMeshMaterialOverride& other) const { return memcmp(this, &other, sizeof(FBoostMeshMaterialOverride)) < 0; }
};

// ScriptStruct TAGame.FXActor_Boost_TA.PreviewParticleOverride
// 0x0010
struct FPreviewParticleOverride
{
	class UParticleSystem*                             Template;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        FXAttachmentName;                              // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPreviewParticleOverride& other) const { return memcmp(this, &other, sizeof(FPreviewParticleOverride)) == 0; }
	bool operator!=(const FPreviewParticleOverride& other) const { return !(*this == other); }
	bool operator<(const FPreviewParticleOverride& other) const { return memcmp(this, &other, sizeof(FPreviewParticleOverride)) < 0; }
};

// ScriptStruct TAGame.FXActor_BreakoutPlatform_TA.PlatformParam
// 0x0020
struct FPlatformParam
{
	class FName                                        ParamName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveFloat                           ValueOverTime;                                 // 0x0008 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPlatformParam& other) const { return memcmp(this, &other, sizeof(FPlatformParam)) == 0; }
	bool operator!=(const FPlatformParam& other) const { return !(*this == other); }
	bool operator<(const FPlatformParam& other) const { return memcmp(this, &other, sizeof(FPlatformParam)) < 0; }
};

// ScriptStruct TAGame.FXActor_Car_TA.CarMovementState
// 0x0004
struct FCarMovementState
{
	float                                              DesiredBoostGlow;                              // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FCarMovementState& other) const { return memcmp(this, &other, sizeof(FCarMovementState)) == 0; }
	bool operator!=(const FCarMovementState& other) const { return !(*this == other); }
	bool operator<(const FCarMovementState& other) const { return memcmp(this, &other, sizeof(FCarMovementState)) < 0; }
};

// ScriptStruct TAGame.ProductDatabase_TA.TemporaryProduct
// 0x0018
struct FTemporaryProduct
{
	class FString                                      AssetPath;                                     // 0x0000 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class FName                                        SlotName;                                      // 0x0010 (0x0008) [0x0000000000004000] (CPF_Config)  

	bool operator==(const FTemporaryProduct& other) const { return memcmp(this, &other, sizeof(FTemporaryProduct)) == 0; }
	bool operator!=(const FTemporaryProduct& other) const { return !(*this == other); }
	bool operator<(const FTemporaryProduct& other) const { return memcmp(this, &other, sizeof(FTemporaryProduct)) < 0; }
};

// ScriptStruct TAGame.ProductDatabase_TA.GarageFolderData
// 0x0060
struct FGarageFolderData
{
	class TArray<int32_t>                              FolderIDs;                                     // 0x0000 (0x0010) [0x0000000000001000] (CPF_Native)  
	struct FMap_Mirror                                 ProductIDToFolderID;                           // 0x0010 (0x0050) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FGarageFolderData& other) const { return memcmp(this, &other, sizeof(FGarageFolderData)) == 0; }
	bool operator!=(const FGarageFolderData& other) const { return !(*this == other); }
	bool operator<(const FGarageFolderData& other) const { return memcmp(this, &other, sizeof(FGarageFolderData)) < 0; }
};

// ScriptStruct TAGame.XPManager_TA.TitleInfo
// 0x000C
struct FTitleInfo
{
	class FName                                        Title;                                         // 0x0000 (0x0008) [0x0000000000000003] (CPF_Edit | CPF_Const)
	int32_t                                            TitleCap;                                      // 0x0008 (0x0004) [0x0000000000000003] (CPF_Edit | CPF_Const)

	bool operator==(const FTitleInfo& other) const { return memcmp(this, &other, sizeof(FTitleInfo)) == 0; }
	bool operator!=(const FTitleInfo& other) const { return !(*this == other); }
	bool operator<(const FTitleInfo& other) const { return memcmp(this, &other, sizeof(FTitleInfo)) < 0; }
};

// ScriptStruct TAGame.Team_TA.TemporarySpawnSpot
// 0x0028
struct FTemporarySpawnSpot
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0018 (0x000C) [0x0000000000000000]               
	float                                              Time;                                          // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FTemporarySpawnSpot& other) const { return memcmp(this, &other, sizeof(FTemporarySpawnSpot)) == 0; }
	bool operator!=(const FTemporarySpawnSpot& other) const { return !(*this == other); }
	bool operator<(const FTemporarySpawnSpot& other) const { return memcmp(this, &other, sizeof(FTemporarySpawnSpot)) < 0; }
};

// ScriptStruct TAGame.GlobalLookupTexture_TA.IntVector
// 0x0008
struct FIntVector
{
	int32_t                                            X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FIntVector& other) const { return memcmp(this, &other, sizeof(FIntVector)) == 0; }
	bool operator!=(const FIntVector& other) const { return !(*this == other); }
	bool operator<(const FIntVector& other) const { return memcmp(this, &other, sizeof(FIntVector)) < 0; }
};

// ScriptStruct TAGame.MapInfo_TA.WorldColorData
// 0x0040
struct FWorldColorData
{
	struct FLinearColor                                EnvironmentA;                                  // 0x0000 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                EnvironmentB;                                  // 0x0010 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                SunLight;                                      // 0x0020 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                WorldLight;                                    // 0x0030 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWorldColorData& other) const { return memcmp(this, &other, sizeof(FWorldColorData)) == 0; }
	bool operator!=(const FWorldColorData& other) const { return !(*this == other); }
	bool operator<(const FWorldColorData& other) const { return memcmp(this, &other, sizeof(FWorldColorData)) < 0; }
};

// ScriptStruct TAGame.GameEditor_Ring_TA.ActorTouchRecordData
// 0x0014
struct FActorTouchRecordData
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     TouchDirection;                                // 0x0008 (0x000C) [0x0000000000000000]               

	bool operator==(const FActorTouchRecordData& other) const { return memcmp(this, &other, sizeof(FActorTouchRecordData)) == 0; }
	bool operator!=(const FActorTouchRecordData& other) const { return !(*this == other); }
	bool operator<(const FActorTouchRecordData& other) const { return memcmp(this, &other, sizeof(FActorTouchRecordData)) < 0; }
};

// ScriptStruct TAGame.RPC_GetWorldCupPlayerCountries_TA.PlayerRepresentingTeamData
// 0x0058
struct FPlayerRepresentingTeamData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Country;                                       // 0x0048 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerRepresentingTeamData& other) const { return memcmp(this, &other, sizeof(FPlayerRepresentingTeamData)) == 0; }
	bool operator!=(const FPlayerRepresentingTeamData& other) const { return !(*this == other); }
	bool operator<(const FPlayerRepresentingTeamData& other) const { return memcmp(this, &other, sizeof(FPlayerRepresentingTeamData)) < 0; }
};

// ScriptStruct TAGame.WorldCupConfig_TA.WorldCupData
// 0x0034
struct FWorldCupData
{
	class FString                                      TeamCodeName;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLinearColor                                TeamColor;                                     // 0x0010 (0x0010) [0x0000000000000000]               
	struct FLinearColor                                TeamColorSecondary;                            // 0x0020 (0x0010) [0x0000000000000000]               
	int32_t                                            CosmeticID;                                    // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FWorldCupData& other) const { return memcmp(this, &other, sizeof(FWorldCupData)) == 0; }
	bool operator!=(const FWorldCupData& other) const { return !(*this == other); }
	bool operator<(const FWorldCupData& other) const { return memcmp(this, &other, sizeof(FWorldCupData)) < 0; }
};

// ScriptStruct TAGame.GameEvent_GameEditor_TA.SpawnArchetypeData
// 0x000C
struct FSpawnArchetypeData
{
	class AActor*                                      Archetype;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            MaxSpawnCount;                                 // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FSpawnArchetypeData& other) const { return memcmp(this, &other, sizeof(FSpawnArchetypeData)) == 0; }
	bool operator!=(const FSpawnArchetypeData& other) const { return !(*this == other); }
	bool operator<(const FSpawnArchetypeData& other) const { return memcmp(this, &other, sizeof(FSpawnArchetypeData)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Tutorial_TA.CarSpawnData
// 0x0020
struct FCarSpawnData
{
	class AController*                                 Controller;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0014 (0x000C) [0x0000000000000000]               

	bool operator==(const FCarSpawnData& other) const { return memcmp(this, &other, sizeof(FCarSpawnData)) == 0; }
	bool operator!=(const FCarSpawnData& other) const { return !(*this == other); }
	bool operator<(const FCarSpawnData& other) const { return memcmp(this, &other, sizeof(FCarSpawnData)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Tutorial_TA.FieldSpawnInfo
// 0x003C
struct FFieldSpawnInfo
{
	struct FVector                                     ExtentLoc;                                     // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     Extent;                                        // 0x000C (0x000C) [0x0000000000000000]               
	float                                              Speed;                                         // 0x0018 (0x0004) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x001C (0x000C) [0x0000000000000000]               
	ERotationType                                      RotationType;                                  // 0x0028 (0x0001) [0x0000000000000000]               
	struct FVector                                     MaxFieldExtentScale;                           // 0x002C (0x000C) [0x0000000000000000]               
	uint32_t                                           bSpawnCannon : 1;                              // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDrawDebug : 1;                                // 0x0038 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FFieldSpawnInfo& other) const { return memcmp(this, &other, sizeof(FFieldSpawnInfo)) == 0; }
	bool operator!=(const FFieldSpawnInfo& other) const { return !(*this == other); }
	bool operator<(const FFieldSpawnInfo& other) const { return memcmp(this, &other, sizeof(FFieldSpawnInfo)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Tutorial_TA.FieldSpawnInfoPair
// 0x0078
struct FFieldSpawnInfoPair
{
	struct FFieldSpawnInfo                             PlayerSpawn;                                   // 0x0000 (0x003C) [0x0000000000000000]               
	struct FFieldSpawnInfo                             BallSpawn;                                     // 0x003C (0x003C) [0x0000000000000000]               

	bool operator==(const FFieldSpawnInfoPair& other) const { return memcmp(this, &other, sizeof(FFieldSpawnInfoPair)) == 0; }
	bool operator!=(const FFieldSpawnInfoPair& other) const { return !(*this == other); }
	bool operator<(const FFieldSpawnInfoPair& other) const { return memcmp(this, &other, sizeof(FFieldSpawnInfoPair)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Tutorial_TA.FieldSetupWave
// 0x0014
struct FFieldSetupWave
{
	class TArray<struct FFieldSpawnInfoPair>           SpawnList;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            MaxWaveLoops;                                  // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FFieldSetupWave& other) const { return memcmp(this, &other, sizeof(FFieldSetupWave)) == 0; }
	bool operator!=(const FFieldSetupWave& other) const { return !(*this == other); }
	bool operator<(const FFieldSetupWave& other) const { return memcmp(this, &other, sizeof(FFieldSetupWave)) < 0; }
};

// ScriptStruct TAGame.GameEvent_Tutorial_TA.DifficultyInfo
// 0x0028
struct FDifficultyInfo
{
	class TArray<struct FFieldSetupWave>               FieldSetupList;                                // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TotalGameEventRounds;                          // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalGameEventRoundsToWin;                     // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              ResetCheckTime;                                // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              ResetCheckTimeAfterBallTouch;                  // 0x001C (0x0004) [0x0000000000000000]               
	float                                              MinBallVelocityForDestroy;                     // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              BallStartTime;                                 // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FDifficultyInfo& other) const { return memcmp(this, &other, sizeof(FDifficultyInfo)) == 0; }
	bool operator!=(const FDifficultyInfo& other) const { return !(*this == other); }
	bool operator<(const FDifficultyInfo& other) const { return memcmp(this, &other, sizeof(FDifficultyInfo)) < 0; }
};

// ScriptStruct TAGame.GameEvent_TrainingEditor_TA.CachedSpeedModifier
// 0x000C
struct FCachedSpeedModifier
{
	class UClass*                                      ActorClass;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              SpeedModifier;                                 // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FCachedSpeedModifier& other) const { return memcmp(this, &other, sizeof(FCachedSpeedModifier)) == 0; }
	bool operator!=(const FCachedSpeedModifier& other) const { return !(*this == other); }
	bool operator<(const FCachedSpeedModifier& other) const { return memcmp(this, &other, sizeof(FCachedSpeedModifier)) < 0; }
};

// ScriptStruct TAGame.MaxActorsGroup_TA.MaxActorCallback
// 0x0030
struct FMaxActorCallback
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FScriptDelegate>               EnabledDelegates;                              // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               DisabledDelegates;                             // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bEnabled : 1;                                  // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              Distance;                                      // 0x002C (0x0004) [0x0000000000000000]               

	bool operator==(const FMaxActorCallback& other) const { return memcmp(this, &other, sizeof(FMaxActorCallback)) == 0; }
	bool operator!=(const FMaxActorCallback& other) const { return !(*this == other); }
	bool operator<(const FMaxActorCallback& other) const { return memcmp(this, &other, sizeof(FMaxActorCallback)) < 0; }
};

// ScriptStruct TAGame.GFxData_BlueprintGarage_TA.BlueprintPreviewProduct
// 0x0020
struct FBlueprintPreviewProduct
{
	int32_t                                            BlueprintProductID;                            // 0x0000 (0x0004) [0x0001000000000000]               
	struct FProductHashID                              BlueprintHashID;                               // 0x0004 (0x0004) [0x0001000000000000]               
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0008 (0x0008) [0x0001000000000000]               
	class TArray<struct FProductHashID>                PossibleHashIDsForThisProduct;                 // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FBlueprintPreviewProduct& other) const { return memcmp(this, &other, sizeof(FBlueprintPreviewProduct)) == 0; }
	bool operator!=(const FBlueprintPreviewProduct& other) const { return !(*this == other); }
	bool operator<(const FBlueprintPreviewProduct& other) const { return memcmp(this, &other, sizeof(FBlueprintPreviewProduct)) < 0; }
};

// ScriptStruct TAGame.GFxData_CarRumble_TA.RumblePickupData
// 0x0030
struct FRumblePickupData
{
	class UTexture2D*                                  ActiveIcon;                                    // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture2D*                                  InactiveIcon;                                  // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PickupName;                                    // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            CooldownSeconds;                               // 0x0020 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class ASpecialPickup_TA*                           Item;                                          // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FRumblePickupData& other) const { return memcmp(this, &other, sizeof(FRumblePickupData)) == 0; }
	bool operator!=(const FRumblePickupData& other) const { return !(*this == other); }
	bool operator<(const FRumblePickupData& other) const { return memcmp(this, &other, sizeof(FRumblePickupData)) < 0; }
};

// ScriptStruct TAGame.RumblePickups_TA.PickupInfo_TA
// 0x001C
struct FPickupInfo_TA
{
	class ASpecialPickup_TA*                           AvailablePickups[3];                           // 0x0000 (0x0018) [0x0000000000000000]               
	uint32_t                                           bItemsArePreview : 1;                          // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FPickupInfo_TA& other) const { return memcmp(this, &other, sizeof(FPickupInfo_TA)) == 0; }
	bool operator!=(const FPickupInfo_TA& other) const { return !(*this == other); }
	bool operator<(const FPickupInfo_TA& other) const { return memcmp(this, &other, sizeof(FPickupInfo_TA)) < 0; }
};

// ScriptStruct TAGame.GFxData_Clubs_TA.GFxSeasonBadgesData
// 0x0007
struct FGFxSeasonBadgesData
{
	int32_t                                            Season;                                        // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	EClubBadge                                         AssistBadgeSeasonTier;                         // 0x0004 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	EClubBadge                                         GoalBadgeSeasonTier;                           // 0x0005 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	EClubBadge                                         SaveBadgeSeasonTier;                           // 0x0006 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxSeasonBadgesData& other) const { return memcmp(this, &other, sizeof(FGFxSeasonBadgesData)) == 0; }
	bool operator!=(const FGFxSeasonBadgesData& other) const { return !(*this == other); }
	bool operator<(const FGFxSeasonBadgesData& other) const { return memcmp(this, &other, sizeof(FGFxSeasonBadgesData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Clubs_TA.GFxClubSeasonStatMilestoneData
// 0x0008
struct FGFxClubSeasonStatMilestoneData
{
	int32_t                                            MilestoneStatValue;                            // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            MilestoneSize;                                 // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxClubSeasonStatMilestoneData& other) const { return memcmp(this, &other, sizeof(FGFxClubSeasonStatMilestoneData)) == 0; }
	bool operator!=(const FGFxClubSeasonStatMilestoneData& other) const { return !(*this == other); }
	bool operator<(const FGFxClubSeasonStatMilestoneData& other) const { return memcmp(this, &other, sizeof(FGFxClubSeasonStatMilestoneData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Clubs_TA.GFxClubSeasonMilestoneData
// 0x0028
struct FGFxClubSeasonMilestoneData
{
	class FString                                      TitleText;                                     // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	struct FColor                                      TitleColor;                                    // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	struct FColor                                      TitleGlowColor;                                // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class TArray<struct FGFxClubSeasonStatMilestoneData> Stats;                                         // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxClubSeasonMilestoneData& other) const { return memcmp(this, &other, sizeof(FGFxClubSeasonMilestoneData)) == 0; }
	bool operator!=(const FGFxClubSeasonMilestoneData& other) const { return !(*this == other); }
	bool operator<(const FGFxClubSeasonMilestoneData& other) const { return memcmp(this, &other, sizeof(FGFxClubSeasonMilestoneData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Clubs_TA.GFxClubStatData
// 0x0030
struct FGFxClubStatData
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      DisplayValue;                                  // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxClubStatData& other) const { return memcmp(this, &other, sizeof(FGFxClubStatData)) == 0; }
	bool operator!=(const FGFxClubStatData& other) const { return !(*this == other); }
	bool operator<(const FGFxClubStatData& other) const { return memcmp(this, &other, sizeof(FGFxClubStatData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Clubs_TA.GFxClubActionData
// 0x0018
struct FGFxClubActionData
{
	class FString                                      LocalizedName;                                 // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	EClubMemberAction                                  ClubAction;                                    // 0x0010 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Priority;                                      // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FGFxClubActionData& other) const { return memcmp(this, &other, sizeof(FGFxClubActionData)) == 0; }
	bool operator!=(const FGFxClubActionData& other) const { return !(*this == other); }
	bool operator<(const FGFxClubActionData& other) const { return memcmp(this, &other, sizeof(FGFxClubActionData)) < 0; }
};

// ScriptStruct TAGame.GFxData_ClubServerBrowser_TA.GFxClubServer
// 0x0018
struct FGFxClubServer
{
	class UClubServerResult_X*                         Server;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      ServerName;                                    // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxClubServer& other) const { return memcmp(this, &other, sizeof(FGFxClubServer)) == 0; }
	bool operator!=(const FGFxClubServer& other) const { return !(*this == other); }
	bool operator<(const FGFxClubServer& other) const { return memcmp(this, &other, sizeof(FGFxClubServer)) < 0; }
};

// ScriptStruct TAGame.GFxData_ContainerDrops_TA.ContainerInfo
// 0x0018
struct FContainerInfo
{
	int32_t                                            SeriesID;                                      // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            ProductID;                                     // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PossibleContents;                              // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FContainerInfo& other) const { return memcmp(this, &other, sizeof(FContainerInfo)) == 0; }
	bool operator!=(const FContainerInfo& other) const { return !(*this == other); }
	bool operator<(const FContainerInfo& other) const { return memcmp(this, &other, sizeof(FContainerInfo)) < 0; }
};

// ScriptStruct TAGame.RPC_MicroTransactions_GetContainerDropTable_TA.RPCContainerDropTable
// 0x0018
struct FRPCContainerDropTable
{
	int32_t                                            SeriesID;                                      // 0x0000 (0x0004) [0x0000000000002000] (CPF_Transient)
	int32_t                                            ProductID;                                     // 0x0004 (0x0004) [0x0000000000002000] (CPF_Transient)
	class TArray<struct FOnlineProductData>            Drops;                                         // 0x0008 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FRPCContainerDropTable& other) const { return memcmp(this, &other, sizeof(FRPCContainerDropTable)) == 0; }
	bool operator!=(const FRPCContainerDropTable& other) const { return !(*this == other); }
	bool operator<(const FRPCContainerDropTable& other) const { return memcmp(this, &other, sizeof(FRPCContainerDropTable)) < 0; }
};

// ScriptStruct TAGame.GFxData_Controls_TA.LocalizedBindingCategory
// 0x0028
struct FLocalizedBindingCategory
{
	class FName                                        Category;                                      // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FLocalizedBindingCategory& other) const { return memcmp(this, &other, sizeof(FLocalizedBindingCategory)) == 0; }
	bool operator!=(const FLocalizedBindingCategory& other) const { return !(*this == other); }
	bool operator<(const FLocalizedBindingCategory& other) const { return memcmp(this, &other, sizeof(FLocalizedBindingCategory)) < 0; }
};

// ScriptStruct TAGame.GFxData_Controls_TA.LocalizedAction
// 0x0024 (0x0038 - 0x005C)
struct FLocalizedAction : FBindingAction
{
	class FString                                      Label;                                         // 0x0038 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0048 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bRebindable : 1;                               // 0x0058 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FLocalizedAction& other) const { return memcmp(this, &other, sizeof(FLocalizedAction)) == 0; }
	bool operator!=(const FLocalizedAction& other) const { return !(*this == other); }
	bool operator<(const FLocalizedAction& other) const { return memcmp(this, &other, sizeof(FLocalizedAction)) < 0; }
};

// ScriptStruct TAGame.GFxData_Controls_TA.UIPlayerBinding
// 0x0024 (0x002C - 0x0050)
struct FUIPlayerBinding : FPlayerBinding
{
	class FString                                      UIKey;                                         // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      UIAxisKey;                                     // 0x0040 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FUIPlayerBinding& other) const { return memcmp(this, &other, sizeof(FUIPlayerBinding)) == 0; }
	bool operator!=(const FUIPlayerBinding& other) const { return !(*this == other); }
	bool operator<(const FUIPlayerBinding& other) const { return memcmp(this, &other, sizeof(FUIPlayerBinding)) < 0; }
};

// ScriptStruct TAGame.GFxData_Credits_TA.LocalizedNameData
// 0x0020
struct FLocalizedNameData
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Position;                                      // 0x0010 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FLocalizedNameData& other) const { return memcmp(this, &other, sizeof(FLocalizedNameData)) == 0; }
	bool operator!=(const FLocalizedNameData& other) const { return !(*this == other); }
	bool operator<(const FLocalizedNameData& other) const { return memcmp(this, &other, sizeof(FLocalizedNameData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Credits_TA.LocalizedDepartmentData
// 0x0020
struct FLocalizedDepartmentData
{
	class FString                                      DepartmentTitle;                               // 0x0000 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class TArray<struct FLocalizedNameData>            Names;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLocalizedDepartmentData& other) const { return memcmp(this, &other, sizeof(FLocalizedDepartmentData)) == 0; }
	bool operator!=(const FLocalizedDepartmentData& other) const { return !(*this == other); }
	bool operator<(const FLocalizedDepartmentData& other) const { return memcmp(this, &other, sizeof(FLocalizedDepartmentData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Credits_TA.LocalizedPostCreditData
// 0x0020
struct FLocalizedPostCreditData
{
	class TArray<class FString>                        Lines;                                         // 0x0000 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class TArray<EOnlinePlatform>                      Platforms;                                     // 0x0010 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)

	bool operator==(const FLocalizedPostCreditData& other) const { return memcmp(this, &other, sizeof(FLocalizedPostCreditData)) == 0; }
	bool operator!=(const FLocalizedPostCreditData& other) const { return !(*this == other); }
	bool operator<(const FLocalizedPostCreditData& other) const { return memcmp(this, &other, sizeof(FLocalizedPostCreditData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Credits_TA.DepartmentData
// 0x0030
struct FDepartmentData
{
	class FString                                      DepartmentTitle;                               // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Position;                                      // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FDepartmentData& other) const { return memcmp(this, &other, sizeof(FDepartmentData)) == 0; }
	bool operator!=(const FDepartmentData& other) const { return !(*this == other); }
	bool operator<(const FDepartmentData& other) const { return memcmp(this, &other, sizeof(FDepartmentData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Credits_TA.PostCreditData
// 0x0040
struct FPostCreditData
{
	class FString                                      Line0;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Line1;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Line2;                                         // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Line3;                                         // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FPostCreditData& other) const { return memcmp(this, &other, sizeof(FPostCreditData)) == 0; }
	bool operator!=(const FPostCreditData& other) const { return !(*this == other); }
	bool operator<(const FPostCreditData& other) const { return memcmp(this, &other, sizeof(FPostCreditData)) < 0; }
};

// ScriptStruct TAGame.GFxData_CrumbTrails_TA.CrumbTrailName
// 0x0008
struct FCrumbTrailName
{
	class FName                                        CrumbName;                                     // 0x0000 (0x0008) [0x0001000040000000] (CPF_DataBinding)

	bool operator==(const FCrumbTrailName& other) const { return memcmp(this, &other, sizeof(FCrumbTrailName)) == 0; }
	bool operator!=(const FCrumbTrailName& other) const { return !(*this == other); }
	bool operator<(const FCrumbTrailName& other) const { return memcmp(this, &other, sizeof(FCrumbTrailName)) < 0; }
};

// ScriptStruct TAGame.GFxData_CustomTeams_TA.GFxCustomTeamSettings
// 0x0018
struct FGFxCustomTeamSettings
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            TeamColorID;                                   // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            CustomColorID;                                 // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxCustomTeamSettings& other) const { return memcmp(this, &other, sizeof(FGFxCustomTeamSettings)) == 0; }
	bool operator!=(const FGFxCustomTeamSettings& other) const { return !(*this == other); }
	bool operator<(const FGFxCustomTeamSettings& other) const { return memcmp(this, &other, sizeof(FGFxCustomTeamSettings)) < 0; }
};

// ScriptStruct TAGame.GFxData_DLC_TA.GFxDLCData
// 0x0060
struct FGFxDLCData
{
	class FString                                      PackName;                                      // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FName                                        Id;                                            // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            ProductID;                                     // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      SubItems;                                      // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Price;                                         // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      DiscountPrice;                                 // 0x0040 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            DiscountPercentage;                            // 0x0050 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            LabelSlotIndex;                                // 0x0054 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bUnlocked : 1;                                 // 0x0058 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bIsNew : 1;                                    // 0x0058 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	int32_t                                            PurchaseTime;                                  // 0x005C (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FGFxDLCData& other) const { return memcmp(this, &other, sizeof(FGFxDLCData)) == 0; }
	bool operator!=(const FGFxDLCData& other) const { return !(*this == other); }
	bool operator<(const FGFxDLCData& other) const { return memcmp(this, &other, sizeof(FGFxDLCData)) < 0; }
};

// ScriptStruct TAGame.GFxData_EngagementEventsConfig_TA.NotificationStatus
// 0x0010
struct FNotificationStatus
{
	class TArray<uint32_t>                             bShow;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNotificationStatus& other) const { return memcmp(this, &other, sizeof(FNotificationStatus)) == 0; }
	bool operator!=(const FNotificationStatus& other) const { return !(*this == other); }
	bool operator<(const FNotificationStatus& other) const { return memcmp(this, &other, sizeof(FNotificationStatus)) < 0; }
};

// ScriptStruct TAGame.NotificationSave_TA.EngagementEventNotificationData
// 0x0010
struct FEngagementEventNotificationData
{
	uint32_t                                           bStartNotificationShown : 1;                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint64_t                                           EpochTimeStartForNotificationShown;            // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FEngagementEventNotificationData& other) const { return memcmp(this, &other, sizeof(FEngagementEventNotificationData)) == 0; }
	bool operator!=(const FEngagementEventNotificationData& other) const { return !(*this == other); }
	bool operator<(const FEngagementEventNotificationData& other) const { return memcmp(this, &other, sizeof(FEngagementEventNotificationData)) < 0; }
};

// ScriptStruct TAGame.GFxData_FreeToPlayRewards_TA.CompensationItem
// 0x0004
struct FCompensationItem
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FCompensationItem& other) const { return memcmp(this, &other, sizeof(FCompensationItem)) == 0; }
	bool operator!=(const FCompensationItem& other) const { return !(*this == other); }
	bool operator<(const FCompensationItem& other) const { return memcmp(this, &other, sizeof(FCompensationItem)) < 0; }
};

// ScriptStruct TAGame.GFxData_Garage_TA.GarageTeam
// 0x0020
struct FGarageTeam
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            TeamColorID;                                   // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            CustomColorID;                                 // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	struct FProductHashID                              TeamFinishHashID;                              // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	struct FProductHashID                              CustomFinishHashID;                            // 0x001C (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGarageTeam& other) const { return memcmp(this, &other, sizeof(FGarageTeam)) == 0; }
	bool operator!=(const FGarageTeam& other) const { return !(*this == other); }
	bool operator<(const FGarageTeam& other) const { return memcmp(this, &other, sizeof(FGarageTeam)) < 0; }
};

// ScriptStruct TAGame.LeaderboardsConfig_TA.LeaderboardRequestInfo
// 0x0030
struct FLeaderboardRequestInfo
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      RequestName;                                   // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ImageName;                                     // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FLeaderboardRequestInfo& other) const { return memcmp(this, &other, sizeof(FLeaderboardRequestInfo)) == 0; }
	bool operator!=(const FLeaderboardRequestInfo& other) const { return !(*this == other); }
	bool operator<(const FLeaderboardRequestInfo& other) const { return memcmp(this, &other, sizeof(FLeaderboardRequestInfo)) < 0; }
};

// ScriptStruct TAGame.GFxData_LoadoutSets_TA.GFxLoadoutSet
// 0x0018
struct FGFxLoadoutSet
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Index;                                         // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bEquipped : 1;                                 // 0x0014 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxLoadoutSet& other) const { return memcmp(this, &other, sizeof(FGFxLoadoutSet)) == 0; }
	bool operator!=(const FGFxLoadoutSet& other) const { return !(*this == other); }
	bool operator<(const FGFxLoadoutSet& other) const { return memcmp(this, &other, sizeof(FGFxLoadoutSet)) < 0; }
};

// ScriptStruct TAGame.GFxData_Map_TA.GFxMapData
// 0x0034
struct FGFxMapData
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      FriendlyName;                                  // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture2D*                                  Thumbnail;                                     // 0x0018 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture2D*                                  LargeImage;                                    // 0x0020 (0x0008) [0x0000000000000000]               
	class UMapData_TA*                                 Data;                                          // 0x0028 (0x0008) [0x0000000000000000]               
	int32_t                                            GameMode;                                      // 0x0030 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxMapData& other) const { return memcmp(this, &other, sizeof(FGFxMapData)) == 0; }
	bool operator!=(const FGFxMapData& other) const { return !(*this == other); }
	bool operator<(const FGFxMapData& other) const { return memcmp(this, &other, sizeof(FGFxMapData)) < 0; }
};

// ScriptStruct TAGame.GFxData_MapPrefs_TA.GFxPlaylistType
// 0x0018
struct FGFxPlaylistType
{
	class FName                                        PlaylistTypeID;                                // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxPlaylistType& other) const { return memcmp(this, &other, sizeof(FGFxPlaylistType)) == 0; }
	bool operator!=(const FGFxPlaylistType& other) const { return !(*this == other); }
	bool operator<(const FGFxPlaylistType& other) const { return memcmp(this, &other, sizeof(FGFxPlaylistType)) < 0; }
};

// ScriptStruct TAGame.GFxData_MapPrefs_TA.GFxMapType
// 0x0020
struct FGFxMapType
{
	class FName                                        MapTypeID;                                     // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UMapSet_TA*                                  MapSet;                                        // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxMapType& other) const { return memcmp(this, &other, sizeof(FGFxMapType)) == 0; }
	bool operator!=(const FGFxMapType& other) const { return !(*this == other); }
	bool operator<(const FGFxMapType& other) const { return memcmp(this, &other, sizeof(FGFxMapType)) < 0; }
};

// ScriptStruct TAGame.GFxData_MapPrefs_TA.GFxMapPlaylist
// 0x002C
struct FGFxMapPlaylist
{
	class FName                                        PlaylistId;                                    // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FName                                        PlaylistTypeID;                                // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            LikesRemaining;                                // 0x0020 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            DislikesRemaining;                             // 0x0024 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bOverrideGlobal : 1;                           // 0x0028 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxMapPlaylist& other) const { return memcmp(this, &other, sizeof(FGFxMapPlaylist)) == 0; }
	bool operator!=(const FGFxMapPlaylist& other) const { return !(*this == other); }
	bool operator<(const FGFxMapPlaylist& other) const { return memcmp(this, &other, sizeof(FGFxMapPlaylist)) < 0; }
};

// ScriptStruct TAGame.GFxData_MapPrefs_TA.GFxMapPreference
// 0x0031
struct FGFxMapPreference
{
	class FName                                        MapID;                                         // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FName                                        MapTypeID;                                     // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FName                                        PlaylistId;                                    // 0x0010 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture2D*                                  Thumbnail;                                     // 0x0028 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	EMapPrefType                                       Preference;                                    // 0x0030 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxMapPreference& other) const { return memcmp(this, &other, sizeof(FGFxMapPreference)) == 0; }
	bool operator!=(const FGFxMapPreference& other) const { return !(*this == other); }
	bool operator<(const FGFxMapPreference& other) const { return memcmp(this, &other, sizeof(FGFxMapPreference)) < 0; }
};

// ScriptStruct TAGame.GFxData_MapSelection_TA.GFxMapSelectionData
// 0x000C
struct FGFxMapSelectionData
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0008 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxMapSelectionData& other) const { return memcmp(this, &other, sizeof(FGFxMapSelectionData)) == 0; }
	bool operator!=(const FGFxMapSelectionData& other) const { return !(*this == other); }
	bool operator<(const FGFxMapSelectionData& other) const { return memcmp(this, &other, sizeof(FGFxMapSelectionData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Regions_TA.GFxRegion
// 0x0024
struct FGFxRegion
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0020 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxRegion& other) const { return memcmp(this, &other, sizeof(FGFxRegion)) == 0; }
	bool operator!=(const FGFxRegion& other) const { return !(*this == other); }
	bool operator<(const FGFxRegion& other) const { return memcmp(this, &other, sizeof(FGFxRegion)) < 0; }
};

// ScriptStruct TAGame.GFxData_Matchmaking_TA.MessageUpdate
// 0x0018
struct FMessageUpdate
{
	int32_t                                            DelayFromStart;                                // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FString                                      MessageKey;                                    // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMessageUpdate& other) const { return memcmp(this, &other, sizeof(FMessageUpdate)) == 0; }
	bool operator!=(const FMessageUpdate& other) const { return !(*this == other); }
	bool operator<(const FMessageUpdate& other) const { return memcmp(this, &other, sizeof(FMessageUpdate)) < 0; }
};

// ScriptStruct TAGame.GFxData_MenuSequence_TA.MenuSequencePair
// 0x0010
struct FMenuSequencePair
{
	class FName                                        MenuSequence;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        MenuID;                                        // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FMenuSequencePair& other) const { return memcmp(this, &other, sizeof(FMenuSequencePair)) == 0; }
	bool operator!=(const FMenuSequencePair& other) const { return !(*this == other); }
	bool operator<(const FMenuSequencePair& other) const { return memcmp(this, &other, sizeof(FMenuSequencePair)) < 0; }
};

// ScriptStruct TAGame.GFxData_MiniScoreboard_TA.ScoreIndex
// 0x0064
struct FScoreIndex
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Place;                                         // 0x0048 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Score;                                         // 0x004C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PlayerName;                                    // 0x0050 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bOwningPlayer : 1;                             // 0x0060 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FScoreIndex& other) const { return memcmp(this, &other, sizeof(FScoreIndex)) == 0; }
	bool operator!=(const FScoreIndex& other) const { return !(*this == other); }
	bool operator<(const FScoreIndex& other) const { return memcmp(this, &other, sizeof(FScoreIndex)) < 0; }
};

// ScriptStruct TAGame.MTXGarageUtils_TA.CartInfo
// 0x0008
struct FCartInfo
{
	int32_t                                            CatalogID;                                     // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Count;                                         // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FCartInfo& other) const { return memcmp(this, &other, sizeof(FCartInfo)) == 0; }
	bool operator!=(const FCartInfo& other) const { return !(*this == other); }
	bool operator<(const FCartInfo& other) const { return memcmp(this, &other, sizeof(FCartInfo)) < 0; }
};

// ScriptStruct TAGame.RPC_MicroTransactions_GetCatalog_TA.MTCatalogInfo
// 0x00B8
struct FMTCatalogInfo
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Title;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ImageURL;                                      // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TabTitle;                                      // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PriceDescription;                              // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMTXOnlineProductData>         Items;                                         // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              IgnoreOfflineProductIDs;                       // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurrency>                     Currencies;                                    // 0x0078 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PlatformProductID;                             // 0x0088 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Category;                                      // 0x0098 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Price;                                         // 0x00A8 (0x0004) [0x0000000000000000]               
	int32_t                                            OriginalPrice;                                 // 0x00AC (0x0004) [0x0000000000000000]               
	int32_t                                            DiscountPercentage;                            // 0x00B0 (0x0004) [0x0000000000000000]               
	uint32_t                                           bIsOwned : 1;                                  // 0x00B4 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FMTCatalogInfo& other) const { return memcmp(this, &other, sizeof(FMTCatalogInfo)) == 0; }
	bool operator!=(const FMTCatalogInfo& other) const { return !(*this == other); }
	bool operator<(const FMTCatalogInfo& other) const { return memcmp(this, &other, sizeof(FMTCatalogInfo)) < 0; }
};

// ScriptStruct TAGame.RPC_MicroTransactions_StartPurchase_TA.MTCartItem
// 0x0008
struct FMTCartItem
{
	int32_t                                            CatalogID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FMTCartItem& other) const { return memcmp(this, &other, sizeof(FMTCartItem)) == 0; }
	bool operator!=(const FMTCartItem& other) const { return !(*this == other); }
	bool operator<(const FMTCartItem& other) const { return memcmp(this, &other, sizeof(FMTCartItem)) < 0; }
};

// ScriptStruct TAGame.GFxData_Shops_TA.ShopsMapEntry
// 0x0010
struct FShopsMapEntry
{
	int32_t                                            ShopIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class UGFxData_ShopCatalogue_TA*                   Catalogue;                                     // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FShopsMapEntry& other) const { return memcmp(this, &other, sizeof(FShopsMapEntry)) == 0; }
	bool operator!=(const FShopsMapEntry& other) const { return !(*this == other); }
	bool operator<(const FShopsMapEntry& other) const { return memcmp(this, &other, sizeof(FShopsMapEntry)) < 0; }
};

// ScriptStruct TAGame.MusicTheme_TA.PlaylistTrack
// 0x0010
struct FPlaylistTrack
{
	class UAkSoundCue*                                 Track;                                         // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UTexture*                                    Icon;                                          // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPlaylistTrack& other) const { return memcmp(this, &other, sizeof(FPlaylistTrack)) == 0; }
	bool operator!=(const FPlaylistTrack& other) const { return !(*this == other); }
	bool operator<(const FPlaylistTrack& other) const { return memcmp(this, &other, sizeof(FPlaylistTrack)) < 0; }
};

// ScriptStruct TAGame.MusicTheme_TA.PlaylistTitleTrack
// 0x0004 (0x0010 - 0x0014)
struct FPlaylistTitleTrack : FPlaylistTrack
{
	float                                              StartupLogoDisplayDurationMS;                  // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPlaylistTitleTrack& other) const { return memcmp(this, &other, sizeof(FPlaylistTitleTrack)) == 0; }
	bool operator!=(const FPlaylistTitleTrack& other) const { return !(*this == other); }
	bool operator<(const FPlaylistTitleTrack& other) const { return memcmp(this, &other, sizeof(FPlaylistTitleTrack)) < 0; }
};

// ScriptStruct TAGame.MusicPlayerSave_TA.PlaylistState
// 0x000C
struct FPlaylistState
{
	class FName                                        Playlist;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	uint32_t                                           bEnabled : 1;                                  // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FPlaylistState& other) const { return memcmp(this, &other, sizeof(FPlaylistState)) == 0; }
	bool operator!=(const FPlaylistState& other) const { return !(*this == other); }
	bool operator<(const FPlaylistState& other) const { return memcmp(this, &other, sizeof(FPlaylistState)) < 0; }
};

// ScriptStruct TAGame.GFxData_OnlineMatchStatus_TA.MatchmakingMessage
// 0x0011
struct FMatchmakingMessage
{
	class FString                                      Message;                                       // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	ESearchMessageType                                 MessageType;                                   // 0x0010 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FMatchmakingMessage& other) const { return memcmp(this, &other, sizeof(FMatchmakingMessage)) == 0; }
	bool operator!=(const FMatchmakingMessage& other) const { return !(*this == other); }
	bool operator<(const FMatchmakingMessage& other) const { return memcmp(this, &other, sizeof(FMatchmakingMessage)) < 0; }
};

// ScriptStruct TAGame.GFxData_Party_TA.GFxPartyMember
// 0x0084
struct FGFxPartyMember
{
	struct FUniqueNetId                                PersonaId;                                     // 0x0000 (0x0048) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      PlayerName;                                    // 0x0048 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ProfileId;                                     // 0x0058 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    PlayerAvatarTexture;                           // 0x0068 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            XpLevel;                                       // 0x0070 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bCompletedChallenges : 1;                      // 0x0074 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bLegacyPlayer : 1;                             // 0x0074 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bGuestAccount : 1;                             // 0x0074 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint64_t                                           ClubID;                                        // 0x0078 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bSplitScreen : 1;                              // 0x0080 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           bLocalSplitScreen : 1;                         // 0x0080 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           bHasProfile : 1;                               // 0x0080 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint32_t                                           bPartyLeader : 1;                              // 0x0080 (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           bIsPlayerInMatch : 1;                          // 0x0080 (0x0004) [0x0000000040000000] [0x00000010] (CPF_DataBinding)

	bool operator==(const FGFxPartyMember& other) const { return memcmp(this, &other, sizeof(FGFxPartyMember)) == 0; }
	bool operator!=(const FGFxPartyMember& other) const { return !(*this == other); }
	bool operator<(const FGFxPartyMember& other) const { return memcmp(this, &other, sizeof(FGFxPartyMember)) < 0; }
};

// ScriptStruct TAGame.GFxData_PlayerAvatarBorderPreview_TA.GFxPlayerAvatarBorderRef
// 0x0010
struct FGFxPlayerAvatarBorderRef
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class UGFxData_PlayerAvatarBorder_TA*              PlayerAvatarBorder;                            // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxPlayerAvatarBorderRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerAvatarBorderRef)) == 0; }
	bool operator!=(const FGFxPlayerAvatarBorderRef& other) const { return !(*this == other); }
	bool operator<(const FGFxPlayerAvatarBorderRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerAvatarBorderRef)) < 0; }
};

// ScriptStruct TAGame.GFxData_PlayerAvatarPreview_TA.GFxPlayerAvatarRef
// 0x0010
struct FGFxPlayerAvatarRef
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class UGFxData_PlayerAvatar_TA*                    PlayerAvatar;                                  // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxPlayerAvatarRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerAvatarRef)) == 0; }
	bool operator!=(const FGFxPlayerAvatarRef& other) const { return !(*this == other); }
	bool operator<(const FGFxPlayerAvatarRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerAvatarRef)) < 0; }
};

// ScriptStruct TAGame.GFxData_PlayerBanners_TA.GFxPlayerBannerRef
// 0x0010
struct FGFxPlayerBannerRef
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class UGFxData_PlayerBanner_TA*                    PlayerBanner;                                  // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxPlayerBannerRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerBannerRef)) == 0; }
	bool operator!=(const FGFxPlayerBannerRef& other) const { return !(*this == other); }
	bool operator<(const FGFxPlayerBannerRef& other) const { return memcmp(this, &other, sizeof(FGFxPlayerBannerRef)) < 0; }
};

// ScriptStruct TAGame.PRI_TA.ScoreboardStat
// 0x000C
struct FScoreboardStat
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Value;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FScoreboardStat& other) const { return memcmp(this, &other, sizeof(FScoreboardStat)) == 0; }
	bool operator!=(const FScoreboardStat& other) const { return !(*this == other); }
	bool operator<(const FScoreboardStat& other) const { return memcmp(this, &other, sizeof(FScoreboardStat)) < 0; }
};

// ScriptStruct TAGame.PRI_TA.StatCooldown
// 0x000C
struct FStatCooldown
{
	class UStatEvent_TA*                               Stat;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              UnlockWorldTime;                               // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FStatCooldown& other) const { return memcmp(this, &other, sizeof(FStatCooldown)) == 0; }
	bool operator!=(const FStatCooldown& other) const { return !(*this == other); }
	bool operator<(const FStatCooldown& other) const { return memcmp(this, &other, sizeof(FStatCooldown)) < 0; }
};

// ScriptStruct TAGame.GFxData_Products_TA.ProductStatInfo
// 0x0040
struct FProductStatInfo
{
	class FString                                      ProductStatLabel;                              // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ProductStatDescription;                        // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ProductStatValue;                              // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      CertifiedStatLabel;                            // 0x0030 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FProductStatInfo& other) const { return memcmp(this, &other, sizeof(FProductStatInfo)) == 0; }
	bool operator!=(const FProductStatInfo& other) const { return !(*this == other); }
	bool operator<(const FProductStatInfo& other) const { return memcmp(this, &other, sizeof(FProductStatInfo)) < 0; }
};

// ScriptStruct TAGame.GFxData_QuickChatBindings_TA.LocalizedQuickChat
// 0x0021
struct FLocalizedQuickChat
{
	class FString                                      MessageId;                                     // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Message;                                       // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	EQuickChatState                                    QuickChatState;                                // 0x0020 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FLocalizedQuickChat& other) const { return memcmp(this, &other, sizeof(FLocalizedQuickChat)) == 0; }
	bool operator!=(const FLocalizedQuickChat& other) const { return !(*this == other); }
	bool operator<(const FLocalizedQuickChat& other) const { return memcmp(this, &other, sizeof(FLocalizedQuickChat)) < 0; }
};

// ScriptStruct TAGame.GFxData_QuickChatBindings_TA.LocalizedQuickChatBinding
// 0x0038
struct FLocalizedQuickChatBinding
{
	class FString                                      MessageId;                                     // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Message;                                       // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            Group;                                         // 0x0020 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Action;                                        // 0x0028 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FLocalizedQuickChatBinding& other) const { return memcmp(this, &other, sizeof(FLocalizedQuickChatBinding)) == 0; }
	bool operator!=(const FLocalizedQuickChatBinding& other) const { return !(*this == other); }
	bool operator<(const FLocalizedQuickChatBinding& other) const { return memcmp(this, &other, sizeof(FLocalizedQuickChatBinding)) < 0; }
};

// ScriptStruct TAGame.Replay_Soccar_TA.ReplayPlayerStats
// 0x0084
struct FReplayPlayerStats
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Name;                                          // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlinePlatform                                    Platform;                                      // 0x0058 (0x0001) [0x0000000000000000]               
	uint64_t                                           OnlineID;                                      // 0x0060 (0x0008) [0x0000000000000000]               
	int32_t                                            Team;                                          // 0x0068 (0x0004) [0x0000000000000000]               
	int32_t                                            Score;                                         // 0x006C (0x0004) [0x0000000000000000]               
	int32_t                                            Goals;                                         // 0x0070 (0x0004) [0x0000000000000000]               
	int32_t                                            Assists;                                       // 0x0074 (0x0004) [0x0000000000000000]               
	int32_t                                            Saves;                                         // 0x0078 (0x0004) [0x0000000000000000]               
	int32_t                                            Shots;                                         // 0x007C (0x0004) [0x0000000000000000]               
	uint32_t                                           bBot : 1;                                      // 0x0080 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FReplayPlayerStats& other) const { return memcmp(this, &other, sizeof(FReplayPlayerStats)) == 0; }
	bool operator!=(const FReplayPlayerStats& other) const { return !(*this == other); }
	bool operator<(const FReplayPlayerStats& other) const { return memcmp(this, &other, sizeof(FReplayPlayerStats)) < 0; }
};

// ScriptStruct TAGame.GFxData_ReplayViewer_TA.LocalizedCameraMode
// 0x0030
struct FLocalizedCameraMode
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	uint32_t                                           bDisabled : 1;                                 // 0x0008 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Description;                                   // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FLocalizedCameraMode& other) const { return memcmp(this, &other, sizeof(FLocalizedCameraMode)) == 0; }
	bool operator!=(const FLocalizedCameraMode& other) const { return !(*this == other); }
	bool operator<(const FLocalizedCameraMode& other) const { return memcmp(this, &other, sizeof(FLocalizedCameraMode)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.TimelineKeyframe
// 0x000C
struct FTimelineKeyframe
{
	class FName                                        Type;                                          // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            frame;                                         // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTimelineKeyframe& other) const { return memcmp(this, &other, sizeof(FTimelineKeyframe)) == 0; }
	bool operator!=(const FTimelineKeyframe& other) const { return !(*this == other); }
	bool operator<(const FTimelineKeyframe& other) const { return memcmp(this, &other, sizeof(FTimelineKeyframe)) < 0; }
};

// ScriptStruct TAGame.RewardDrop_TA.GFxLevelThreshold
// 0x0004
struct FGFxLevelThreshold
{
	int32_t                                            TotalXP;                                       // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxLevelThreshold& other) const { return memcmp(this, &other, sizeof(FGFxLevelThreshold)) == 0; }
	bool operator!=(const FGFxLevelThreshold& other) const { return !(*this == other); }
	bool operator<(const FGFxLevelThreshold& other) const { return memcmp(this, &other, sizeof(FGFxLevelThreshold)) < 0; }
};

// ScriptStruct TAGame.GFxData_RocketPass_TA.RocketPassReward
// 0x0014
struct FRocketPassReward
{
	int32_t                                            CurrencyID;                                    // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	float                                              Amount;                                        // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Tier;                                          // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FRocketPassReward& other) const { return memcmp(this, &other, sizeof(FRocketPassReward)) == 0; }
	bool operator!=(const FRocketPassReward& other) const { return !(*this == other); }
	bool operator<(const FRocketPassReward& other) const { return memcmp(this, &other, sizeof(FRocketPassReward)) < 0; }
};

// ScriptStruct TAGame.GFxData_RocketPass_TA.RocketPassProduct
// 0x0009
struct FRocketPassProduct
{
	struct FProductHashID                              HashID;                                        // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Tier;                                          // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	ERocketPassTierType                                UnlockType;                                    // 0x0008 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FRocketPassProduct& other) const { return memcmp(this, &other, sizeof(FRocketPassProduct)) == 0; }
	bool operator!=(const FRocketPassProduct& other) const { return !(*this == other); }
	bool operator<(const FRocketPassProduct& other) const { return memcmp(this, &other, sizeof(FRocketPassProduct)) < 0; }
};

// ScriptStruct TAGame.GFxData_RocketPass_TA.RocketPassXPReward
// 0x0000 (0x0014 - 0x0014)
struct FRocketPassXPReward : FRocketPassReward
{

	bool operator==(const FRocketPassXPReward& other) const { return memcmp(this, &other, sizeof(FRocketPassXPReward)) == 0; }
	bool operator!=(const FRocketPassXPReward& other) const { return !(*this == other); }
	bool operator<(const FRocketPassXPReward& other) const { return memcmp(this, &other, sizeof(FRocketPassXPReward)) < 0; }
};

// ScriptStruct TAGame.GFxData_RocketPass_TA.RocketPassCurrencyReward
// 0x0000 (0x0014 - 0x0014)
struct FRocketPassCurrencyReward : FRocketPassReward
{

	bool operator==(const FRocketPassCurrencyReward& other) const { return memcmp(this, &other, sizeof(FRocketPassCurrencyReward)) == 0; }
	bool operator!=(const FRocketPassCurrencyReward& other) const { return !(*this == other); }
	bool operator<(const FRocketPassCurrencyReward& other) const { return memcmp(this, &other, sizeof(FRocketPassCurrencyReward)) < 0; }
};

// ScriptStruct TAGame.GFxData_Season_TA.SeasonWeek
// 0x0004
struct FSeasonWeek
{
	uint32_t                                           bWinner : 1;                                   // 0x0000 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FSeasonWeek& other) const { return memcmp(this, &other, sizeof(FSeasonWeek)) == 0; }
	bool operator!=(const FSeasonWeek& other) const { return !(*this == other); }
	bool operator<(const FSeasonWeek& other) const { return memcmp(this, &other, sizeof(FSeasonWeek)) < 0; }
};

// ScriptStruct TAGame.ProductTemplate_TA.ProductReplacement2
// 0x0018
struct FProductReplacement2
{
	class TArray<EConsoleType>                         Platforms;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UProduct_TA*                                 Replacement;                                   // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FProductReplacement2& other) const { return memcmp(this, &other, sizeof(FProductReplacement2)) == 0; }
	bool operator!=(const FProductReplacement2& other) const { return !(*this == other); }
	bool operator<(const FProductReplacement2& other) const { return memcmp(this, &other, sizeof(FProductReplacement2)) < 0; }
};

// ScriptStruct TAGame.GFxData_SeasonMode_TA.GFxLogoData
// 0x002C
struct FGFxLogoData
{
	class FName                                        AssetName;                                     // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    Logo;                                          // 0x0008 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            TeamColor;                                     // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            CustomColor;                                   // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      DefaultTeamName;                               // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bIsBotTeam : 1;                                // 0x0028 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxLogoData& other) const { return memcmp(this, &other, sizeof(FGFxLogoData)) == 0; }
	bool operator!=(const FGFxLogoData& other) const { return !(*this == other); }
	bool operator<(const FGFxLogoData& other) const { return memcmp(this, &other, sizeof(FGFxLogoData)) < 0; }
};

// ScriptStruct TAGame.GFxData_SeasonMode_TA.GFxBotData
// 0x0020
struct FGFxBotData
{
	class FString                                      PlayerName;                                    // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Id;                                            // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxBotData& other) const { return memcmp(this, &other, sizeof(FGFxBotData)) == 0; }
	bool operator!=(const FGFxBotData& other) const { return !(*this == other); }
	bool operator<(const FGFxBotData& other) const { return memcmp(this, &other, sizeof(FGFxBotData)) < 0; }
};

// ScriptStruct TAGame.GFxData_Settings_TA.BindingPreset
// 0x0018
struct FBindingPreset
{
	class FName                                        PresetName;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      DisplayName;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FBindingPreset& other) const { return memcmp(this, &other, sizeof(FBindingPreset)) == 0; }
	bool operator!=(const FBindingPreset& other) const { return !(*this == other); }
	bool operator<(const FBindingPreset& other) const { return memcmp(this, &other, sizeof(FBindingPreset)) < 0; }
};

// ScriptStruct TAGame.LoadedMtxCatalog_TA.LoadedMtxCatalog
// 0x0019
struct FLoadedMtxCatalog
{
	int32_t                                            CatalogID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMTXCatalogCategory                                Category;                                      // 0x0018 (0x0001) [0x0000000000000000]               

	bool operator==(const FLoadedMtxCatalog& other) const { return memcmp(this, &other, sizeof(FLoadedMtxCatalog)) == 0; }
	bool operator!=(const FLoadedMtxCatalog& other) const { return !(*this == other); }
	bool operator<(const FLoadedMtxCatalog& other) const { return memcmp(this, &other, sizeof(FLoadedMtxCatalog)) < 0; }
};

// ScriptStruct TAGame.ShopTabs_TA.ShopTab
// 0x0018
struct FShopTab
{
	EShopTabType                                       Type;                                          // 0x0000 (0x0001) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Index;                                         // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FShopTab& other) const { return memcmp(this, &other, sizeof(FShopTab)) == 0; }
	bool operator!=(const FShopTab& other) const { return !(*this == other); }
	bool operator<(const FShopTab& other) const { return memcmp(this, &other, sizeof(FShopTab)) < 0; }
};

// ScriptStruct TAGame.GFxData_Stats_TA.GFxStatData
// 0x0050
struct FGFxStatData
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      DisplayValue;                                  // 0x0020 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    Texture;                                       // 0x0030 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Description;                                   // 0x0038 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class UClass*                                      DisplayProductStatClass;                       // 0x0048 (0x0008) [0x0000000000000000]               

	bool operator==(const FGFxStatData& other) const { return memcmp(this, &other, sizeof(FGFxStatData)) == 0; }
	bool operator!=(const FGFxStatData& other) const { return !(*this == other); }
	bool operator<(const FGFxStatData& other) const { return memcmp(this, &other, sizeof(FGFxStatData)) < 0; }
};

// ScriptStruct TAGame.GFxData_TextChatChannel_TA.CachedChatMessage
// 0x0104
struct FCachedChatMessage
{
	struct FGFxChatMessage                             ChatMessage;                                   // 0x0000 (0x0098) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FSignedMessagePacket                        MessagePacket;                                 // 0x0098 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FPlayerMessageInfo                          PlayerInfo;                                    // 0x00E0 (0x0020) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            InternalId;                                    // 0x0100 (0x0004) [0x0001000000000000]               

	bool operator==(const FCachedChatMessage& other) const { return memcmp(this, &other, sizeof(FCachedChatMessage)) == 0; }
	bool operator!=(const FCachedChatMessage& other) const { return !(*this == other); }
	bool operator<(const FCachedChatMessage& other) const { return memcmp(this, &other, sizeof(FCachedChatMessage)) < 0; }
};

// ScriptStruct TAGame.GFxData_TourBracketMatchTeamDetails_TA.TeamGameStats
// 0x0004
struct FTeamGameStats
{
	int32_t                                            Goals;                                         // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTeamGameStats& other) const { return memcmp(this, &other, sizeof(FTeamGameStats)) == 0; }
	bool operator!=(const FTeamGameStats& other) const { return !(*this == other); }
	bool operator<(const FTeamGameStats& other) const { return memcmp(this, &other, sizeof(FTeamGameStats)) < 0; }
};

// ScriptStruct TAGame.GFxData_TourPlatforms_TA.GFxTourPlatformGroup
// 0x0024
struct FGFxTourPlatformGroup
{
	class TArray<EOnlinePlatform>                      Platforms;                                     // 0x0000 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bSelected : 1;                                 // 0x0020 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)

	bool operator==(const FGFxTourPlatformGroup& other) const { return memcmp(this, &other, sizeof(FGFxTourPlatformGroup)) == 0; }
	bool operator!=(const FGFxTourPlatformGroup& other) const { return !(*this == other); }
	bool operator<(const FGFxTourPlatformGroup& other) const { return memcmp(this, &other, sizeof(FGFxTourPlatformGroup)) < 0; }
};

// ScriptStruct TAGame.GFxData_TourSubscriptions_TA.SubscriptionInfo
// 0x0008
struct FSubscriptionInfo
{
	uint64_t                                           Id;                                            // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FSubscriptionInfo& other) const { return memcmp(this, &other, sizeof(FSubscriptionInfo)) == 0; }
	bool operator!=(const FSubscriptionInfo& other) const { return !(*this == other); }
	bool operator<(const FSubscriptionInfo& other) const { return memcmp(this, &other, sizeof(FSubscriptionInfo)) < 0; }
};

// ScriptStruct TAGame.TradeInConfig_TA.TradeInProductCount
// 0x0008
struct FTradeInProductCount
{
	EProductQuality                                    Quality;                                       // 0x0000 (0x0001) [0x0001000000000000]               
	int32_t                                            ProductCount;                                  // 0x0004 (0x0004) [0x0001000000000000]               

	bool operator==(const FTradeInProductCount& other) const { return memcmp(this, &other, sizeof(FTradeInProductCount)) == 0; }
	bool operator!=(const FTradeInProductCount& other) const { return !(*this == other); }
	bool operator<(const FTradeInProductCount& other) const { return memcmp(this, &other, sizeof(FTradeInProductCount)) < 0; }
};

// ScriptStruct TAGame.GFxData_Training_TA.UseAction
// 0x0020
struct FUseAction
{
	class FString                                      ActionName;                                    // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      LocalizedActionName;                           // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FUseAction& other) const { return memcmp(this, &other, sizeof(FUseAction)) == 0; }
	bool operator!=(const FUseAction& other) const { return !(*this == other); }
	bool operator<(const FUseAction& other) const { return memcmp(this, &other, sizeof(FUseAction)) < 0; }
};

// ScriptStruct TAGame.TrainingEditorMetrics_TA.TrainingNavigationEvent
// 0x0024
struct FTrainingNavigationEvent
{
	uint64_t                                           TimeStamp;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	ETrainingNavigationCommand                         CommandUsed;                                   // 0x0008 (0x0001) [0x0000000000000000]               
	int32_t                                            PrevPlaylistIndex;                             // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            NewPlaylistIndex;                              // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            PrevRoundNum;                                  // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            NewRoundNum;                                   // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            PrevShotAttempt;                               // 0x001C (0x0004) [0x0000000000000000]               
	uint32_t                                           bShuffle : 1;                                  // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FTrainingNavigationEvent& other) const { return memcmp(this, &other, sizeof(FTrainingNavigationEvent)) == 0; }
	bool operator!=(const FTrainingNavigationEvent& other) const { return !(*this == other); }
	bool operator<(const FTrainingNavigationEvent& other) const { return memcmp(this, &other, sizeof(FTrainingNavigationEvent)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeBrowser_TA.FavoritedFileMetaData
// 0x0028
struct FFavoritedFileMetaData
{
	class FString                                      Code;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           UpdatedAt;                                     // 0x0010 (0x0008) [0x0000000000000000]               
	class FString                                      Filename;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFavoritedFileMetaData& other) const { return memcmp(this, &other, sizeof(FFavoritedFileMetaData)) == 0; }
	bool operator!=(const FFavoritedFileMetaData& other) const { return !(*this == other); }
	bool operator<(const FFavoritedFileMetaData& other) const { return memcmp(this, &other, sizeof(FFavoritedFileMetaData)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeBrowser_TA.CachedDownloadedFile
// 0x0020
struct FCachedDownloadedFile
{
	class FString                                      Filename;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Code;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCachedDownloadedFile& other) const { return memcmp(this, &other, sizeof(FCachedDownloadedFile)) == 0; }
	bool operator!=(const FCachedDownloadedFile& other) const { return !(*this == other); }
	bool operator<(const FCachedDownloadedFile& other) const { return memcmp(this, &other, sizeof(FCachedDownloadedFile)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeBrowser_TA.SearchCacheData
// 0x0018
struct FSearchCacheData
{
	float                                              TimeoutTime;                                   // 0x0000 (0x0004) [0x0000000000002000] (CPF_Transient)
	class TArray<class UTrainingEditorData_TA*>        TrainingModes;                                 // 0x0008 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FSearchCacheData& other) const { return memcmp(this, &other, sizeof(FSearchCacheData)) == 0; }
	bool operator!=(const FSearchCacheData& other) const { return !(*this == other); }
	bool operator<(const FSearchCacheData& other) const { return memcmp(this, &other, sizeof(FSearchCacheData)) < 0; }
};

// ScriptStruct TAGame.RPC_TrainingEditor_ListPlayerTrainingDataTimestamp_TA.CodeTimePair
// 0x0018
struct FCodeTimePair
{
	class FString                                      Code;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           UpdatedAt;                                     // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FCodeTimePair& other) const { return memcmp(this, &other, sizeof(FCodeTimePair)) == 0; }
	bool operator!=(const FCodeTimePair& other) const { return !(*this == other); }
	bool operator<(const FCodeTimePair& other) const { return memcmp(this, &other, sizeof(FCodeTimePair)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeConstants_TA.TrainingModeDifficulty
// 0x0001
struct FTrainingModeDifficulty
{
	EDifficulty                                        Difficulty;                                    // 0x0000 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTrainingModeDifficulty& other) const { return memcmp(this, &other, sizeof(FTrainingModeDifficulty)) == 0; }
	bool operator!=(const FTrainingModeDifficulty& other) const { return !(*this == other); }
	bool operator<(const FTrainingModeDifficulty& other) const { return memcmp(this, &other, sizeof(FTrainingModeDifficulty)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeConstants_TA.TrainingModeType
// 0x0001
struct FTrainingModeType
{
	ETrainingType                                      Type;                                          // 0x0000 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTrainingModeType& other) const { return memcmp(this, &other, sizeof(FTrainingModeType)) == 0; }
	bool operator!=(const FTrainingModeType& other) const { return !(*this == other); }
	bool operator<(const FTrainingModeType& other) const { return memcmp(this, &other, sizeof(FTrainingModeType)) < 0; }
};

// ScriptStruct TAGame.GFxData_TrainingModeConstants_TA.TrainingModeTag
// 0x0001
struct FTrainingModeTag
{
	ETrainingTag                                       Tag;                                           // 0x0000 (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FTrainingModeTag& other) const { return memcmp(this, &other, sizeof(FTrainingModeTag)) == 0; }
	bool operator!=(const FTrainingModeTag& other) const { return !(*this == other); }
	bool operator<(const FTrainingModeTag& other) const { return memcmp(this, &other, sizeof(FTrainingModeTag)) < 0; }
};

// ScriptStruct TAGame.GFxData_UserBugReport_TA.GFxUserBugReportCategory
// 0x0020
struct FGFxUserBugReportCategory
{
	class FName                                        Id;                                            // 0x0000 (0x0008) [0x0001000040000000] (CPF_DataBinding)
	EUserBugReportCategoryType                         Type;                                          // 0x0008 (0x0001) [0x0001000040000000] (CPF_DataBinding)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0001000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxUserBugReportCategory& other) const { return memcmp(this, &other, sizeof(FGFxUserBugReportCategory)) == 0; }
	bool operator!=(const FGFxUserBugReportCategory& other) const { return !(*this == other); }
	bool operator<(const FGFxUserBugReportCategory& other) const { return memcmp(this, &other, sizeof(FGFxUserBugReportCategory)) < 0; }
};

// ScriptStruct TAGame.GFxEngine_TA.SoundStateItem
// 0x0011
struct FSoundStateItem
{
	class FName                                        StateName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class UGFxShell_X*                                 Shell;                                         // 0x0008 (0x0008) [0x0000000000000000]               
	ESoundStatePriority                                Priority;                                      // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FSoundStateItem& other) const { return memcmp(this, &other, sizeof(FSoundStateItem)) == 0; }
	bool operator!=(const FSoundStateItem& other) const { return !(*this == other); }
	bool operator<(const FSoundStateItem& other) const { return memcmp(this, &other, sizeof(FSoundStateItem)) < 0; }
};

// ScriptStruct TAGame.HUDBase_TA.ChatMessage
// 0x0090
struct FChatMessage
{
	class APlayerReplicationInfo*                      PRI;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class ATeam_TA*                                    Team;                                          // 0x0008 (0x0008) [0x0000000000000000]               
	class FString                                      PlayerName;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Message;                                       // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EChatChannel                                       ChatChannel;                                   // 0x0030 (0x0001) [0x0000000000000000]               
	uint32_t                                           bPreset : 1;                                   // 0x0034 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FUniqueNetId                                Recipient;                                     // 0x0038 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TimeStamp;                                     // 0x0080 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FChatMessage& other) const { return memcmp(this, &other, sizeof(FChatMessage)) == 0; }
	bool operator!=(const FChatMessage& other) const { return !(*this == other); }
	bool operator<(const FChatMessage& other) const { return memcmp(this, &other, sizeof(FChatMessage)) < 0; }
};

// ScriptStruct TAGame.GFxHUD_TA.ScreenLocation
// 0x0010
struct FScreenLocation
{
	struct FVector                                     ScreenPos;                                     // 0x0000 (0x000C) [0x0000000000000000]               
	uint32_t                                           bOffScreen : 1;                                // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FScreenLocation& other) const { return memcmp(this, &other, sizeof(FScreenLocation)) == 0; }
	bool operator!=(const FScreenLocation& other) const { return !(*this == other); }
	bool operator<(const FScreenLocation& other) const { return memcmp(this, &other, sizeof(FScreenLocation)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.ReplayActorChannel
// 0x0040
struct FReplayActorChannel
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class UClass*                                      ActorClass;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	class FName                                        actorName;                                     // 0x0010 (0x0008) [0x0000000000000000]               
	class TArray<uint8_t>                              Recent;                                        // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              StillDirty;                                    // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              CloseTime;                                     // 0x0038 (0x0004) [0x0000000000000000]               
	uint32_t                                           bNetInitial : 1;                               // 0x003C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bPlaybackPersistent : 1;                       // 0x003C (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FReplayActorChannel& other) const { return memcmp(this, &other, sizeof(FReplayActorChannel)) == 0; }
	bool operator!=(const FReplayActorChannel& other) const { return !(*this == other); }
	bool operator<(const FReplayActorChannel& other) const { return memcmp(this, &other, sizeof(FReplayActorChannel)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.ReplayLogItem
// 0x0028
struct FReplayLogItem
{
	int32_t                                            frame;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      PlayerName;                                    // 0x0008 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Text;                                          // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FReplayLogItem& other) const { return memcmp(this, &other, sizeof(FReplayLogItem)) == 0; }
	bool operator!=(const FReplayLogItem& other) const { return !(*this == other); }
	bool operator<(const FReplayLogItem& other) const { return memcmp(this, &other, sizeof(FReplayLogItem)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.ReplayKeyframe
// 0x000C
struct FReplayKeyframe
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            frame;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Position;                                      // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FReplayKeyframe& other) const { return memcmp(this, &other, sizeof(FReplayKeyframe)) == 0; }
	bool operator!=(const FReplayKeyframe& other) const { return !(*this == other); }
	bool operator<(const FReplayKeyframe& other) const { return memcmp(this, &other, sizeof(FReplayKeyframe)) < 0; }
};

// ScriptStruct TAGame.ReplayDirector_TA.ReplayScoreData
// 0x0019
struct FReplayScoreData
{
	class APRI_TA*                                     ScoredBy;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class APRI_TA*                                     AssistedBy;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	float                                              Speed;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              Time;                                          // 0x0014 (0x0004) [0x0000000000000000]               
	uint8_t                                            ScoreTeam;                                     // 0x0018 (0x0001) [0x0000000000000000]               

	bool operator==(const FReplayScoreData& other) const { return memcmp(this, &other, sizeof(FReplayScoreData)) == 0; }
	bool operator!=(const FReplayScoreData& other) const { return !(*this == other); }
	bool operator<(const FReplayScoreData& other) const { return memcmp(this, &other, sizeof(FReplayScoreData)) < 0; }
};

// ScriptStruct TAGame.ImpactEffectsComponent_TA.CollisionEffectData
// 0x0058
struct FCollisionEffectData
{
	class UPhysicalMaterial*                           PhysMat;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	class UPhysicalMaterialProperty_TA*                PhysMatProp;                                   // 0x0008 (0x0008) [0x0000000000000000]               
	struct FEffectsMapping                             ImpactEffects;                                 // 0x0010 (0x0010) [0x0000000000000000]               
	struct FVector                                     HitLocation;                                   // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     HitNormal;                                     // 0x002C (0x000C) [0x0000000000000000]               
	struct FVector                                     Momentum;                                      // 0x0038 (0x000C) [0x0000000000000000]               
	float                                              ImpactMomentum;                                // 0x0044 (0x0004) [0x0000000000000000]               
	float                                              SlideMomentum;                                 // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            PhysicsFrame;                                  // 0x004C (0x0004) [0x0000000000000000]               
	class AActor*                                      HitActor;                                      // 0x0050 (0x0008) [0x0000000000000000]               

	bool operator==(const FCollisionEffectData& other) const { return memcmp(this, &other, sizeof(FCollisionEffectData)) == 0; }
	bool operator!=(const FCollisionEffectData& other) const { return !(*this == other); }
	bool operator<(const FCollisionEffectData& other) const { return memcmp(this, &other, sizeof(FCollisionEffectData)) < 0; }
};

// ScriptStruct TAGame.InMapScoreboard_TA.ScoreboardMaterialOverride
// 0x0038
struct FScoreboardMaterialOverride
{
	class UMaterialInstanceConstant*                   MaterialInstance;                              // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MaterialIndex;                                 // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveFloat                           MICValueOverrideCurve;                         // 0x0010 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FName                                        ParamToOverride;                               // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInstanceConstant*                   MIC;                                           // 0x0030 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FScoreboardMaterialOverride& other) const { return memcmp(this, &other, sizeof(FScoreboardMaterialOverride)) == 0; }
	bool operator!=(const FScoreboardMaterialOverride& other) const { return !(*this == other); }
	bool operator<(const FScoreboardMaterialOverride& other) const { return memcmp(this, &other, sizeof(FScoreboardMaterialOverride)) < 0; }
};

// ScriptStruct TAGame.PhysicsConfig_TA.SimTimeScaleSettings
// 0x0004
struct FSimTimeScaleSettings
{
	float                                              FixedAdjustSimTimeRate;                        // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FSimTimeScaleSettings& other) const { return memcmp(this, &other, sizeof(FSimTimeScaleSettings)) == 0; }
	bool operator!=(const FSimTimeScaleSettings& other) const { return !(*this == other); }
	bool operator<(const FSimTimeScaleSettings& other) const { return memcmp(this, &other, sizeof(FSimTimeScaleSettings)) < 0; }
};

// ScriptStruct TAGame.NetworkInputBuffer_TA.ClientPacketData
// 0x0030
struct FClientPacketData
{
	float                                              TimeStamp;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     CameraLoc;                                     // 0x0004 (0x000C) [0x0000000000000000]               
	struct FRotator                                    CameraRot;                                     // 0x0010 (0x000C) [0x0000000000000000]               
	class TArray<struct FClientFrameData>              Frames;                                        // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FClientPacketData& other) const { return memcmp(this, &other, sizeof(FClientPacketData)) == 0; }
	bool operator!=(const FClientPacketData& other) const { return !(*this == other); }
	bool operator<(const FClientPacketData& other) const { return memcmp(this, &other, sizeof(FClientPacketData)) < 0; }
};

// ScriptStruct TAGame.NetworkInputBuffer_TA.InputBufferStats
// 0x0005
struct FInputBufferStats
{
	uint8_t                                            OverBufferFrames;                              // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            UnderBufferFrames;                             // 0x0001 (0x0001) [0x0000000000000000]               
	uint8_t                                            InputBufferLow;                                // 0x0002 (0x0001) [0x0000000000000000]               
	uint8_t                                            InputBufferHigh;                               // 0x0003 (0x0001) [0x0000000000000000]               
	uint8_t                                            InputBufferTarget;                             // 0x0004 (0x0001) [0x0000000000000000]               

	bool operator==(const FInputBufferStats& other) const { return memcmp(this, &other, sizeof(FInputBufferStats)) == 0; }
	bool operator!=(const FInputBufferStats& other) const { return !(*this == other); }
	bool operator<(const FInputBufferStats& other) const { return memcmp(this, &other, sizeof(FInputBufferStats)) < 0; }
};

// ScriptStruct TAGame.JiggleHitHandler_TA.JiggleCarData
// 0x0025
struct FJiggleCarData
{
	class AVehicle_TA*                                 HitVehicle;                                    // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	struct FVector                                     JiggleAxis;                                    // 0x0008 (0x000C) [0x0000000000002000] (CPF_Transient)
	struct FVector                                     JiggleStartLocation;                           // 0x0014 (0x000C) [0x0000000000002000] (CPF_Transient)
	float                                              JiggleStartTime;                               // 0x0020 (0x0004) [0x0000000000002000] (CPF_Transient)
	EPhysics                                           OriginalPhysics;                               // 0x0024 (0x0001) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FJiggleCarData& other) const { return memcmp(this, &other, sizeof(FJiggleCarData)) == 0; }
	bool operator!=(const FJiggleCarData& other) const { return !(*this == other); }
	bool operator<(const FJiggleCarData& other) const { return memcmp(this, &other, sizeof(FJiggleCarData)) < 0; }
};

// ScriptStruct TAGame.K3SUserPermissions_TA.K3SMeta
// 0x0020
struct FK3SMeta
{
	class FString                                      RequestID;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TimeStamp;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FK3SMeta& other) const { return memcmp(this, &other, sizeof(FK3SMeta)) == 0; }
	bool operator!=(const FK3SMeta& other) const { return !(*this == other); }
	bool operator<(const FK3SMeta& other) const { return memcmp(this, &other, sizeof(FK3SMeta)) < 0; }
};

// ScriptStruct TAGame.ListenServer_TA.LoadingPlayer
// 0x0050
struct FLoadingPlayer
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            NumPlayers;                                    // 0x0048 (0x0004) [0x0000000000000000]               
	float                                              TimeoutTime;                                   // 0x004C (0x0004) [0x0000000000000000]               

	bool operator==(const FLoadingPlayer& other) const { return memcmp(this, &other, sizeof(FLoadingPlayer)) == 0; }
	bool operator!=(const FLoadingPlayer& other) const { return !(*this == other); }
	bool operator<(const FLoadingPlayer& other) const { return memcmp(this, &other, sizeof(FLoadingPlayer)) < 0; }
};

// ScriptStruct TAGame.LoadoutSequencer_TA.SequenceData
// 0x0010
struct FSequenceData
{
	class UProductSlot_TA*                             Slot;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              AnimDelay;                                     // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bAssetLoaded : 1;                              // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FSequenceData& other) const { return memcmp(this, &other, sizeof(FSequenceData)) == 0; }
	bool operator!=(const FSequenceData& other) const { return !(*this == other); }
	bool operator<(const FSequenceData& other) const { return memcmp(this, &other, sizeof(FSequenceData)) < 0; }
};

// ScriptStruct TAGame.MapDataLoader_TA.MapSelectorPair
// 0x0010
struct FMapSelectorPair
{
	class UMapSet_TA*                                  MapSet;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class UMapSelector_TA*                             Selector;                                      // 0x0008 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FMapSelectorPair& other) const { return memcmp(this, &other, sizeof(FMapSelectorPair)) == 0; }
	bool operator!=(const FMapSelectorPair& other) const { return !(*this == other); }
	bool operator<(const FMapSelectorPair& other) const { return memcmp(this, &other, sizeof(FMapSelectorPair)) < 0; }
};

// ScriptStruct TAGame.MapDataLoader_TA.MapImageLoadRequest
// 0x0038
struct FMapImageLoadRequest
{
	class UMapData_TA*                                 MapData;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        PackageName;                                   // 0x0008 (0x0008) [0x0000000000000000]               
	class FString                                      AssetPath;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             Callback;                                      // 0x0020 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMapImageLoadRequest& other) const { return memcmp(this, &other, sizeof(FMapImageLoadRequest)) == 0; }
	bool operator!=(const FMapImageLoadRequest& other) const { return !(*this == other); }
	bool operator<(const FMapImageLoadRequest& other) const { return memcmp(this, &other, sizeof(FMapImageLoadRequest)) < 0; }
};

// ScriptStruct TAGame.MapPrefsMetrics_TA.MapPrefsMetric
// 0x0028
struct FMapPrefsMetric
{
	int32_t                                            Playlist;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<class FName>                          Likes;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FName>                          Dislikes;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMapPrefsMetric& other) const { return memcmp(this, &other, sizeof(FMapPrefsMetric)) == 0; }
	bool operator!=(const FMapPrefsMetric& other) const { return !(*this == other); }
	bool operator<(const FMapPrefsMetric& other) const { return memcmp(this, &other, sizeof(FMapPrefsMetric)) < 0; }
};

// ScriptStruct TAGame.MatchCompleteMetrics_TA.MatchCompleteHistory
// 0x0024
struct FMatchCompleteHistory
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  Players;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              MatchCompleteTime;                             // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FMatchCompleteHistory& other) const { return memcmp(this, &other, sizeof(FMatchCompleteHistory)) == 0; }
	bool operator!=(const FMatchCompleteHistory& other) const { return !(*this == other); }
	bool operator<(const FMatchCompleteHistory& other) const { return memcmp(this, &other, sizeof(FMatchCompleteHistory)) < 0; }
};

// ScriptStruct TAGame.MatchHistoryMetrics_TA.MatchPreviewData
// 0x001C
struct FMatchPreviewData
{
	int32_t                                            Index;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      MatchGUID;                                     // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TimesPreviewed;                                // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FMatchPreviewData& other) const { return memcmp(this, &other, sizeof(FMatchPreviewData)) == 0; }
	bool operator!=(const FMatchPreviewData& other) const { return !(*this == other); }
	bool operator<(const FMatchPreviewData& other) const { return memcmp(this, &other, sizeof(FMatchPreviewData)) < 0; }
};

// ScriptStruct TAGame.MatchHistoryMetrics_TA.MatchHistoryChangeTabEvent
// 0x0030
struct FMatchHistoryChangeTabEvent
{
	EMatchHistoryUI                                    CurrentTab;                                    // 0x0000 (0x0001) [0x0000000000000000]               
	EMatchHistoryUI                                    NewTab;                                        // 0x0001 (0x0001) [0x0000000000000000]               
	uint64_t                                           StartTimestamp;                                // 0x0008 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0010 (0x0008) [0x0000000000000000]               
	EMatchHistoryNavigableButton                       NavigableButtonID;                             // 0x0018 (0x0001) [0x0000000000000000]               
	class TArray<struct FMatchPreviewData>             MatchPreviews;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMatchHistoryChangeTabEvent& other) const { return memcmp(this, &other, sizeof(FMatchHistoryChangeTabEvent)) == 0; }
	bool operator!=(const FMatchHistoryChangeTabEvent& other) const { return !(*this == other); }
	bool operator<(const FMatchHistoryChangeTabEvent& other) const { return memcmp(this, &other, sizeof(FMatchHistoryChangeTabEvent)) < 0; }
};

// ScriptStruct TAGame.MenuTreeNode_TA.NodePlatformAvailability
// 0x0018
struct FNodePlatformAvailability
{
	uint32_t                                           bPlatformIncludeList : 1;                      // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	class TArray<EOnlinePlatform>                      Platforms;                                     // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FNodePlatformAvailability& other) const { return memcmp(this, &other, sizeof(FNodePlatformAvailability)) == 0; }
	bool operator!=(const FNodePlatformAvailability& other) const { return !(*this == other); }
	bool operator<(const FNodePlatformAvailability& other) const { return memcmp(this, &other, sizeof(FNodePlatformAvailability)) < 0; }
};

// ScriptStruct TAGame.MenuTreePlaylistQueue_TA.ActivePlaylistQueueInfo
// 0x0010
struct FActivePlaylistQueueInfo
{
	int32_t                                            PlaylistDataIndex;                             // 0x0000 (0x0004) [0x0000000000000000]               
	uint64_t                                           StartTime;                                     // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FActivePlaylistQueueInfo& other) const { return memcmp(this, &other, sizeof(FActivePlaylistQueueInfo)) == 0; }
	bool operator!=(const FActivePlaylistQueueInfo& other) const { return !(*this == other); }
	bool operator<(const FActivePlaylistQueueInfo& other) const { return memcmp(this, &other, sizeof(FActivePlaylistQueueInfo)) < 0; }
};

// ScriptStruct TAGame.MergePartyEvent_TA.MergePartyReplicatedData
// 0x0240
struct FMergePartyReplicatedData
{
	struct FUniqueNetId                                LeaderID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                InviteeIDs[7];                                 // 0x0048 (0x01F8) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMergePartyReplicatedData& other) const { return memcmp(this, &other, sizeof(FMergePartyReplicatedData)) == 0; }
	bool operator!=(const FMergePartyReplicatedData& other) const { return !(*this == other); }
	bool operator<(const FMergePartyReplicatedData& other) const { return memcmp(this, &other, sizeof(FMergePartyReplicatedData)) < 0; }
};

// ScriptStruct TAGame.MtxConfig_TA.CurrencyReplacement
// 0x0020
struct FCurrencyReplacement
{
	class FString                                      CurrencyString;                                // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SubstitutionString;                            // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCurrencyReplacement& other) const { return memcmp(this, &other, sizeof(FCurrencyReplacement)) == 0; }
	bool operator!=(const FCurrencyReplacement& other) const { return !(*this == other); }
	bool operator<(const FCurrencyReplacement& other) const { return memcmp(this, &other, sizeof(FCurrencyReplacement)) < 0; }
};

// ScriptStruct TAGame.MusicUrlConfig_TA.MusicConfigTrack
// 0x0018
struct FMusicConfigTrack
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FString                                      ExternalUrl;                                   // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMusicConfigTrack& other) const { return memcmp(this, &other, sizeof(FMusicConfigTrack)) == 0; }
	bool operator!=(const FMusicConfigTrack& other) const { return !(*this == other); }
	bool operator<(const FMusicConfigTrack& other) const { return memcmp(this, &other, sizeof(FMusicConfigTrack)) < 0; }
};

// ScriptStruct TAGame.Mutator_Ball_TA.MapBallArcOverride
// 0x0010
struct FMapBallArcOverride
{
	class UMapData_TA*                                 Map;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class ABall_TA*                                    BallArchetype;                                 // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FMapBallArcOverride& other) const { return memcmp(this, &other, sizeof(FMapBallArcOverride)) == 0; }
	bool operator!=(const FMapBallArcOverride& other) const { return !(*this == other); }
	bool operator<(const FMapBallArcOverride& other) const { return memcmp(this, &other, sizeof(FMapBallArcOverride)) < 0; }
};

// ScriptStruct TAGame.Mutator_Freeplay_TA.RumbleItemIndex
// 0x000C
struct FRumbleItemIndex
{
	class APlayerController_TA*                        PC;                                            // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            ItemIndex;                                     // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FRumbleItemIndex& other) const { return memcmp(this, &other, sizeof(FRumbleItemIndex)) == 0; }
	bool operator!=(const FRumbleItemIndex& other) const { return !(*this == other); }
	bool operator<(const FRumbleItemIndex& other) const { return memcmp(this, &other, sizeof(FRumbleItemIndex)) < 0; }
};

// ScriptStruct TAGame.NetMetricPlayerData_TA.NetBuckets
// 0x002C
struct FNetBuckets
{
	class TArray<struct FNetBucketMetrics>             Data;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      StatName;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            BannedBucketIndex;                             // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              KickThresholdSeconds;                          // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              TotalBannedSeconds;                            // 0x0028 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FNetBuckets& other) const { return memcmp(this, &other, sizeof(FNetBuckets)) == 0; }
	bool operator!=(const FNetBuckets& other) const { return !(*this == other); }
	bool operator<(const FNetBuckets& other) const { return memcmp(this, &other, sizeof(FNetBuckets)) < 0; }
};

// ScriptStruct TAGame.NetMetricsConfig_TA.NetBucketSetup
// 0x0018
struct FNetBucketSetup
{
	class TArray<int32_t>                              MinPossibleValue;                              // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            BannedBucketIndex;                             // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              KickThresholdSeconds;                          // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FNetBucketSetup& other) const { return memcmp(this, &other, sizeof(FNetBucketSetup)) == 0; }
	bool operator!=(const FNetBucketSetup& other) const { return !(*this == other); }
	bool operator<(const FNetBucketSetup& other) const { return memcmp(this, &other, sizeof(FNetBucketSetup)) < 0; }
};

// ScriptStruct TAGame.NetMetricPlayerDataExport_TA.NetBucketsExport
// 0x0020
struct FNetBucketsExport
{
	class TArray<struct FNetBucketMetrics>             Data;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      StatName;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNetBucketsExport& other) const { return memcmp(this, &other, sizeof(FNetBucketsExport)) == 0; }
	bool operator!=(const FNetBucketsExport& other) const { return !(*this == other); }
	bool operator<(const FNetBucketsExport& other) const { return memcmp(this, &other, sizeof(FNetBucketsExport)) < 0; }
};

// ScriptStruct TAGame.NetworkConfig_TA.NetworkLimit
// 0x0010
struct FNetworkLimit
{
	float                                              Min;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Max;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              OldMin;                                        // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              OldMax;                                        // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FNetworkLimit& other) const { return memcmp(this, &other, sizeof(FNetworkLimit)) == 0; }
	bool operator!=(const FNetworkLimit& other) const { return !(*this == other); }
	bool operator<(const FNetworkLimit& other) const { return memcmp(this, &other, sizeof(FNetworkLimit)) < 0; }
};

// ScriptStruct TAGame.PhysicsConfig_TA.ContinuousSimTimeScaleSettings
// 0x0034
struct FContinuousSimTimeScaleSettings
{
	float                                              TimeDilations[5];                              // 0x0000 (0x0014) [0x0000000000000000]               
	int32_t                                            Inputs_Starved;                                // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            Inputs_Good;                                   // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            Inputs_Saturated;                              // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            Inputs_ExtremelySaturated;                     // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            Inputs_Max;                                    // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            ExtraBufferMax;                                // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              ExtraBufferHistorySeconds;                     // 0x002C (0x0004) [0x0000000000000000]               
	float                                              ExtraBufferUpdatePeriod;                       // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FContinuousSimTimeScaleSettings& other) const { return memcmp(this, &other, sizeof(FContinuousSimTimeScaleSettings)) == 0; }
	bool operator!=(const FContinuousSimTimeScaleSettings& other) const { return !(*this == other); }
	bool operator<(const FContinuousSimTimeScaleSettings& other) const { return memcmp(this, &other, sizeof(FContinuousSimTimeScaleSettings)) < 0; }
};

// ScriptStruct TAGame.NetworkInputBuffer_STS_TA.SimTimeAdjustDebugData
// 0x0008
struct FSimTimeAdjustDebugData
{
	float                                              TimeLastSimTimeAdjustStarted;                  // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            NumSimTimeAdjustFrames;                        // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FSimTimeAdjustDebugData& other) const { return memcmp(this, &other, sizeof(FSimTimeAdjustDebugData)) == 0; }
	bool operator!=(const FSimTimeAdjustDebugData& other) const { return !(*this == other); }
	bool operator<(const FSimTimeAdjustDebugData& other) const { return memcmp(this, &other, sizeof(FSimTimeAdjustDebugData)) < 0; }
};

// ScriptStruct TAGame.OnlineGamePlayerTitles_TA.CachedPlayerData
// 0x0078
struct FCachedPlayerData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FName>                          Titles;                                        // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              CacheTime;                                     // 0x0058 (0x0004) [0x0000000000000000]               
	class URPC_X*                                      RPC;                                           // 0x0060 (0x0008) [0x0000000000000000]               
	class TArray<struct FScriptDelegate>               Callbacks;                                     // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCachedPlayerData& other) const { return memcmp(this, &other, sizeof(FCachedPlayerData)) == 0; }
	bool operator!=(const FCachedPlayerData& other) const { return !(*this == other); }
	bool operator<(const FCachedPlayerData& other) const { return memcmp(this, &other, sizeof(FCachedPlayerData)) < 0; }
};

// ScriptStruct TAGame.OrbitHitHandler_TA.OrbitCarData
// 0x0028
struct FOrbitCarData
{
	class AVehicle_TA*                                 CarHit;                                        // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	struct FVector                                     OrbitAxis;                                     // 0x0008 (0x000C) [0x0000000000002000] (CPF_Transient)
	struct FVector                                     OrbitLocation;                                 // 0x0014 (0x000C) [0x0000000000002000] (CPF_Transient)
	float                                              RotationAngleRadians;                          // 0x0020 (0x0004) [0x0000000000002000] (CPF_Transient)
	uint32_t                                           bShouldOrbit : 1;                              // 0x0024 (0x0004) [0x0000000000002000] [0x100000001] (CPF_Transient)

	bool operator==(const FOrbitCarData& other) const { return memcmp(this, &other, sizeof(FOrbitCarData)) == 0; }
	bool operator!=(const FOrbitCarData& other) const { return !(*this == other); }
	bool operator<(const FOrbitCarData& other) const { return memcmp(this, &other, sizeof(FOrbitCarData)) < 0; }
};

// ScriptStruct TAGame.OverrideMaterialsHitHandler_TA.SkeletalMeshMaterialCache
// 0x0018
struct FSkeletalMeshMaterialCache
{
	class UMeshComponent*                              TargetMesh;                                    // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class TArray<class UMaterialInterface*>            Materials;                                     // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSkeletalMeshMaterialCache& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshMaterialCache)) == 0; }
	bool operator!=(const FSkeletalMeshMaterialCache& other) const { return !(*this == other); }
	bool operator<(const FSkeletalMeshMaterialCache& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshMaterialCache)) < 0; }
};

// ScriptStruct TAGame.PartyMessage_Loadout_TA.PartyMemberLoadoutMessage
// 0x009D
struct FPartyMemberLoadoutMessage
{
	struct FUniqueNetId                                UniqueId;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLoadoutData                                Loadout;                                       // 0x0048 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineProductData>            OnlineLoadoutData;                             // 0x0088 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            GaragePreviewTeam;                             // 0x0098 (0x0004) [0x0000000000000000]               
	uint8_t                                            SortWeight;                                    // 0x009C (0x0001) [0x0000000000000000]               

	bool operator==(const FPartyMemberLoadoutMessage& other) const { return memcmp(this, &other, sizeof(FPartyMemberLoadoutMessage)) == 0; }
	bool operator!=(const FPartyMemberLoadoutMessage& other) const { return !(*this == other); }
	bool operator<(const FPartyMemberLoadoutMessage& other) const { return memcmp(this, &other, sizeof(FPartyMemberLoadoutMessage)) < 0; }
};

// ScriptStruct TAGame.PlayerController_TA.CrosshairExtentInfo
// 0x0010
struct FCrosshairExtentInfo
{
	struct FVector                                     Extent;                                        // 0x0000 (0x000C) [0x0000000000000000]               
	float                                              minDot;                                        // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FCrosshairExtentInfo& other) const { return memcmp(this, &other, sizeof(FCrosshairExtentInfo)) == 0; }
	bool operator!=(const FCrosshairExtentInfo& other) const { return !(*this == other); }
	bool operator<(const FCrosshairExtentInfo& other) const { return memcmp(this, &other, sizeof(FCrosshairExtentInfo)) < 0; }
};

// ScriptStruct TAGame.PlayerController_TA.ChatSpamData
// 0x0018
struct FChatSpamData
{
	float                                              RiseAmount;                                    // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              RiseMultiplier;                                // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DecayRate;                                     // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxValue;                                      // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Value;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              LastChatTime;                                  // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FChatSpamData& other) const { return memcmp(this, &other, sizeof(FChatSpamData)) == 0; }
	bool operator!=(const FChatSpamData& other) const { return !(*this == other); }
	bool operator<(const FChatSpamData& other) const { return memcmp(this, &other, sizeof(FChatSpamData)) < 0; }
};

// ScriptStruct TAGame.PlayerReportConfig_TA.PlayerReportReason
// 0x0018
struct FPlayerReportReason
{
	int32_t                                            ReasonID;                                      // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Reason;                                        // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FPlayerReportReason& other) const { return memcmp(this, &other, sizeof(FPlayerReportReason)) == 0; }
	bool operator!=(const FPlayerReportReason& other) const { return !(*this == other); }
	bool operator<(const FPlayerReportReason& other) const { return memcmp(this, &other, sizeof(FPlayerReportReason)) < 0; }
};

// ScriptStruct TAGame.PremiumSkinSet_TA.PremiumSkinSetItem
// 0x0008
struct FPremiumSkinSetItem
{
	class UPremiumSkin_TA*                             PremiumSkin;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPremiumSkinSetItem& other) const { return memcmp(this, &other, sizeof(FPremiumSkinSetItem)) == 0; }
	bool operator!=(const FPremiumSkinSetItem& other) const { return !(*this == other); }
	bool operator<(const FPremiumSkinSetItem& other) const { return memcmp(this, &other, sizeof(FPremiumSkinSetItem)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_TA.ProductReplacement
// 0x0018
struct FProductReplacement
{
	class TArray<EConsoleType>                         Platforms;                                     // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class UProductAsset_TA*                            Replacement;                                   // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FProductReplacement& other) const { return memcmp(this, &other, sizeof(FProductReplacement)) == 0; }
	bool operator!=(const FProductReplacement& other) const { return !(*this == other); }
	bool operator<(const FProductReplacement& other) const { return memcmp(this, &other, sizeof(FProductReplacement)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Body_TA.BoostAttachmentToggle
// 0x0028
struct FBoostAttachmentToggle
{
	class FName                                        BoostAttachment;                               // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UFXActorEvent_X*>               AttachAny;                                     // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<class UFXActorEvent_X*>               DetachAny;                                     // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FBoostAttachmentToggle& other) const { return memcmp(this, &other, sizeof(FBoostAttachmentToggle)) == 0; }
	bool operator!=(const FBoostAttachmentToggle& other) const { return !(*this == other); }
	bool operator<(const FBoostAttachmentToggle& other) const { return memcmp(this, &other, sizeof(FBoostAttachmentToggle)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_Body_TA.TeamPaintFinish
// 0x0010
struct FTeamPaintFinish
{
	class UProductAsset_PaintFinish_TA*                TeamFinish;                                    // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UProductAsset_PaintFinish_TA*                CustomFinish;                                  // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTeamPaintFinish& other) const { return memcmp(this, &other, sizeof(FTeamPaintFinish)) == 0; }
	bool operator!=(const FTeamPaintFinish& other) const { return !(*this == other); }
	bool operator<(const FTeamPaintFinish& other) const { return memcmp(this, &other, sizeof(FTeamPaintFinish)) < 0; }
};

// ScriptStruct TAGame.ProductAsset_GoalExplosion_TA.IgnoredGoalRotations
// 0x0004
struct FIgnoredGoalRotations
{
	uint32_t                                           bIgnorePitch : 1;                              // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bIgnoreYaw : 1;                                // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bIgnoreRoll : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x100000004] (CPF_Edit)

	bool operator==(const FIgnoredGoalRotations& other) const { return memcmp(this, &other, sizeof(FIgnoredGoalRotations)) == 0; }
	bool operator!=(const FIgnoredGoalRotations& other) const { return !(*this == other); }
	bool operator<(const FIgnoredGoalRotations& other) const { return memcmp(this, &other, sizeof(FIgnoredGoalRotations)) < 0; }
};

// ScriptStruct TAGame.ProductAssetLoader_TA.AssetLoadRequest
// 0x0050
struct FAssetLoadRequest
{
	struct FAssetLoadResult                            Result;                                        // 0x0000 (0x0020) [0x0000000000000000]               
	class UProduct_TA*                                 Product;                                       // 0x0020 (0x0008) [0x0000000000000000]               
	int32_t                                            LoadOrder;                                     // 0x0028 (0x0004) [0x0000000000000000]               
	EAssetLoadState                                    LoadState;                                     // 0x002C (0x0001) [0x0000000000000000]               
	uint32_t                                           bIsThumbnailRequest : 1;                       // 0x0030 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FScriptDelegate                             OnLoadedCallback;                              // 0x0038 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAssetLoadRequest& other) const { return memcmp(this, &other, sizeof(FAssetLoadRequest)) == 0; }
	bool operator!=(const FAssetLoadRequest& other) const { return !(*this == other); }
	bool operator<(const FAssetLoadRequest& other) const { return memcmp(this, &other, sizeof(FAssetLoadRequest)) < 0; }
};

// ScriptStruct TAGame.ProductAttribute_InheritCarSetting_TA.InheritedParameter
// 0x0010
struct FInheritedParameter
{
	class FName                                        ParentParameterName;                           // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AssetParameterName;                            // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInheritedParameter& other) const { return memcmp(this, &other, sizeof(FInheritedParameter)) == 0; }
	bool operator!=(const FInheritedParameter& other) const { return !(*this == other); }
	bool operator<(const FInheritedParameter& other) const { return memcmp(this, &other, sizeof(FInheritedParameter)) < 0; }
};

// ScriptStruct TAGame.ProductAttribute_SpecialEditionSettings_TA.SpecialEditionConfig
// 0x0010
struct FSpecialEditionConfig
{
	class UProductSpecialEdition_TA*                   SpecialEdition;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UProductAssetReference_TA*                   SpecialEditionProductAsset;                    // 0x0008 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FSpecialEditionConfig& other) const { return memcmp(this, &other, sizeof(FSpecialEditionConfig)) == 0; }
	bool operator!=(const FSpecialEditionConfig& other) const { return !(*this == other); }
	bool operator<(const FSpecialEditionConfig& other) const { return memcmp(this, &other, sizeof(FSpecialEditionConfig)) < 0; }
};

// ScriptStruct TAGame.ProductAttribute_SwapMICParameterValues_TA.MICSwapParameters
// 0x0018
struct FMICSwapParameters
{
	class UMaterialInstanceConstant*                   MICToChange;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        FirstParameter;                                // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        SecondParameter;                               // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMICSwapParameters& other) const { return memcmp(this, &other, sizeof(FMICSwapParameters)) == 0; }
	bool operator!=(const FMICSwapParameters& other) const { return !(*this == other); }
	bool operator<(const FMICSwapParameters& other) const { return memcmp(this, &other, sizeof(FMICSwapParameters)) < 0; }
};

// ScriptStruct TAGame.RPC_ProductsDebugAddProducts_TA.AddProductsRequestData
// 0x0020
struct FAddProductsRequestData
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Count;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            SeriesID;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductAttribute>       Attributes;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAddProductsRequestData& other) const { return memcmp(this, &other, sizeof(FAddProductsRequestData)) == 0; }
	bool operator!=(const FAddProductsRequestData& other) const { return !(*this == other); }
	bool operator<(const FAddProductsRequestData& other) const { return memcmp(this, &other, sizeof(FAddProductsRequestData)) < 0; }
};

// ScriptStruct TAGame.ProductMetrics_TA.PaintMetricsData
// 0x0010
struct FPaintMetricsData
{
	uint8_t                                            TeamColorID;                                   // 0x0000 (0x0001) [0x0000000000000000]               
	int32_t                                            TeamProductID;                                 // 0x0004 (0x0004) [0x0000000000000000]               
	uint8_t                                            CustomColorID;                                 // 0x0008 (0x0001) [0x0000000000000000]               
	int32_t                                            CustomProductID;                               // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FPaintMetricsData& other) const { return memcmp(this, &other, sizeof(FPaintMetricsData)) == 0; }
	bool operator!=(const FPaintMetricsData& other) const { return !(*this == other); }
	bool operator<(const FPaintMetricsData& other) const { return memcmp(this, &other, sizeof(FPaintMetricsData)) < 0; }
};

// ScriptStruct TAGame.ProductMetrics_TA.ProductMetricsData
// 0x0018
struct FProductMetricsData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FOnlineProductAttribute>       Attributes;                                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FProductMetricsData& other) const { return memcmp(this, &other, sizeof(FProductMetricsData)) == 0; }
	bool operator!=(const FProductMetricsData& other) const { return !(*this == other); }
	bool operator<(const FProductMetricsData& other) const { return memcmp(this, &other, sizeof(FProductMetricsData)) < 0; }
};

// ScriptStruct TAGame.ProductOverride_SpecificMaterials_TA.MaterialAndMaterialOverride
// 0x0010
struct FMaterialAndMaterialOverride
{
	class UMaterialInstanceConstant*                   MICToOverride;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInstanceConstant*                   MICTOOverrideWith;                             // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMaterialAndMaterialOverride& other) const { return memcmp(this, &other, sizeof(FMaterialAndMaterialOverride)) == 0; }
	bool operator!=(const FMaterialAndMaterialOverride& other) const { return !(*this == other); }
	bool operator<(const FMaterialAndMaterialOverride& other) const { return memcmp(this, &other, sizeof(FMaterialAndMaterialOverride)) < 0; }
};

// ScriptStruct TAGame.ProductsConfig_TA.ReplacementProduct
// 0x0050
struct FReplacementProduct
{
	int32_t                                            ProhibitedID;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bShowForOwningClient : 1;                      // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FOnlineProductData                          Replacement;                                   // 0x0008 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)
	class UOnlineProduct_TA*                           ReplacementInstance;                           // 0x0048 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FReplacementProduct& other) const { return memcmp(this, &other, sizeof(FReplacementProduct)) == 0; }
	bool operator!=(const FReplacementProduct& other) const { return !(*this == other); }
	bool operator<(const FReplacementProduct& other) const { return memcmp(this, &other, sizeof(FReplacementProduct)) < 0; }
};

// ScriptStruct TAGame.ProductsConfig_TA.SeriesGroup
// 0x0018
struct FSeriesGroup
{
	int32_t                                            SeriesID;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<EProductQuality>                      ExcludedQualities;                             // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSeriesGroup& other) const { return memcmp(this, &other, sizeof(FSeriesGroup)) == 0; }
	bool operator!=(const FSeriesGroup& other) const { return !(*this == other); }
	bool operator<(const FSeriesGroup& other) const { return memcmp(this, &other, sizeof(FSeriesGroup)) < 0; }
};

// ScriptStruct TAGame.ProductsConfig_TA.ProductTradeHoldOverride
// 0x0028
struct FProductTradeHoldOverride
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<EProductTradeRestriction>             TradeRestrictions;                             // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<EProductTradeRestriction>             DefaultRestrictions;                           // 0x0018 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FProductTradeHoldOverride& other) const { return memcmp(this, &other, sizeof(FProductTradeHoldOverride)) == 0; }
	bool operator!=(const FProductTradeHoldOverride& other) const { return !(*this == other); }
	bool operator<(const FProductTradeHoldOverride& other) const { return memcmp(this, &other, sizeof(FProductTradeHoldOverride)) < 0; }
};

// ScriptStruct TAGame.ProductThumbnailQueue_TA.RenderThumbnailScene
// 0x0034
struct FRenderThumbnailScene
{
	class UProductThumbnail_TA*                        Thumbnail;                                     // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UProductAsset_TA*                            Asset;                                         // 0x0008 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UOnlineProduct_TA*                           OnlineProduct;                                 // 0x0010 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UThumbnailScene_TA*                          Scene;                                         // 0x0018 (0x0008) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TextureWidth;                                  // 0x0020 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TextureHeight;                                 // 0x0024 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TeamID;                                        // 0x0028 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              NextRenderTime;                                // 0x002C (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bBeingRendered : 1;                            // 0x0030 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bCanceled : 1;                                 // 0x0030 (0x0004) [0x0000000000000002] [0x100000002] (CPF_Const)

	bool operator==(const FRenderThumbnailScene& other) const { return memcmp(this, &other, sizeof(FRenderThumbnailScene)) == 0; }
	bool operator!=(const FRenderThumbnailScene& other) const { return !(*this == other); }
	bool operator<(const FRenderThumbnailScene& other) const { return memcmp(this, &other, sizeof(FRenderThumbnailScene)) < 0; }
};

// ScriptStruct TAGame.ProductThumbnailQueue_TA.RenderThumbnailRequest
// 0x0030
struct FRenderThumbnailRequest
{
	struct FProductThumbnailResult                     Result;                                        // 0x0000 (0x0018) [0x0000000000000002] (CPF_Const)   
	struct FScriptDelegate                             Callback;                                      // 0x0018 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRenderThumbnailRequest& other) const { return memcmp(this, &other, sizeof(FRenderThumbnailRequest)) == 0; }
	bool operator!=(const FRenderThumbnailRequest& other) const { return !(*this == other); }
	bool operator<(const FRenderThumbnailRequest& other) const { return memcmp(this, &other, sizeof(FRenderThumbnailRequest)) < 0; }
};

// ScriptStruct TAGame.ProfileCameraSave_TA.CameraPresetFloatOverride
// 0x0028
struct FCameraPresetFloatOverride
{
	ECameraSettingsPreset                              Preset;                                        // 0x0000 (0x0001) [0x0000000000000000]               
	float                                              ValueKBM;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              ValueController;                               // 0x0008 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             ApplyFunc;                                     // 0x0010 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCameraPresetFloatOverride& other) const { return memcmp(this, &other, sizeof(FCameraPresetFloatOverride)) == 0; }
	bool operator!=(const FCameraPresetFloatOverride& other) const { return !(*this == other); }
	bool operator<(const FCameraPresetFloatOverride& other) const { return memcmp(this, &other, sizeof(FCameraPresetFloatOverride)) < 0; }
};

// ScriptStruct TAGame.ProfileCameraSave_TA.CameraPresetBoolOverride
// 0x0020
struct FCameraPresetBoolOverride
{
	ECameraSettingsPreset                              Preset;                                        // 0x0000 (0x0001) [0x0000000000000000]               
	uint32_t                                           bValueKBM : 1;                                 // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bValueController : 1;                          // 0x0004 (0x0004) [0x0000000000000000] [0x00000002] 
	struct FScriptDelegate                             ApplyFunc;                                     // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCameraPresetBoolOverride& other) const { return memcmp(this, &other, sizeof(FCameraPresetBoolOverride)) == 0; }
	bool operator!=(const FCameraPresetBoolOverride& other) const { return !(*this == other); }
	bool operator<(const FCameraPresetBoolOverride& other) const { return memcmp(this, &other, sizeof(FCameraPresetBoolOverride)) < 0; }
};

// ScriptStruct TAGame.RBHistory_TA.RBPhysicsSnapshot
// 0x0070
struct FRBPhysicsSnapshot
{
	struct FReplicatedRBState                          RBState;                                       // 0x0000 (0x0040) [0x0000000000000000]               
	struct FWorldContactData                           WorldContact;                                  // 0x0040 (0x0028) [0x0000000000000000]               
	class APhysicsVolume*                              PhysicsVolume;                                 // 0x0068 (0x0008) [0x0000000000000000]               

	bool operator==(const FRBPhysicsSnapshot& other) const { return memcmp(this, &other, sizeof(FRBPhysicsSnapshot)) == 0; }
	bool operator!=(const FRBPhysicsSnapshot& other) const { return !(*this == other); }
	bool operator<(const FRBPhysicsSnapshot& other) const { return memcmp(this, &other, sizeof(FRBPhysicsSnapshot)) < 0; }
};

// ScriptStruct TAGame.RBVehicleHistory_TA.RBVehicleSnapshot
// 0x0180
struct FRBVehicleSnapshot
{
	struct FVehicleInputs                              Input;                                         // 0x0000 (0x0024) [0x0000000000000000]               
	struct FWheelContactData                           WheelContact0;                                 // 0x0028 (0x0050) [0x0000000000080000] (CPF_Component)
	struct FWheelContactData                           WheelContact1;                                 // 0x0078 (0x0050) [0x0000000000080000] (CPF_Component)
	struct FWheelContactData                           WheelContact2;                                 // 0x00C8 (0x0050) [0x0000000000080000] (CPF_Component)
	struct FWheelContactData                           WheelContact3;                                 // 0x0118 (0x0050) [0x0000000000080000] (CPF_Component)
	struct FCarInteractionData                         CarInteraction;                                // 0x0168 (0x0010) [0x0000000000000000]               
	float                                              OutputHandbrake;                               // 0x0178 (0x0004) [0x0000000000000000]               
	int32_t                                            LastHitBallFrame;                              // 0x017C (0x0004) [0x0000000000000000]               

	bool operator==(const FRBVehicleSnapshot& other) const { return memcmp(this, &other, sizeof(FRBVehicleSnapshot)) == 0; }
	bool operator!=(const FRBVehicleSnapshot& other) const { return !(*this == other); }
	bool operator<(const FRBVehicleSnapshot& other) const { return memcmp(this, &other, sizeof(FRBVehicleSnapshot)) < 0; }
};

// ScriptStruct TAGame.RBVehicleHistory_TA.CarComponentSnapshot
// 0x0009
struct FCarComponentSnapshot
{
	uint32_t                                           bActive : 1;                                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              ActivityTime;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	uint8_t                                            ComponentData;                                 // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FCarComponentSnapshot& other) const { return memcmp(this, &other, sizeof(FCarComponentSnapshot)) == 0; }
	bool operator!=(const FCarComponentSnapshot& other) const { return !(*this == other); }
	bool operator<(const FCarComponentSnapshot& other) const { return memcmp(this, &other, sizeof(FCarComponentSnapshot)) < 0; }
};

// ScriptStruct TAGame.RBVehicleHistory_TA.CarComponentHistory
// 0x0024
struct FCarComponentHistory
{
	class ACarComponent_TA*                            CarComponent;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FCarComponentSnapshot>         Snapshots;                                     // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FCarComponentSnapshot                       BackupSnapshot;                                // 0x0018 (0x000C) [0x0000000000000000]               

	bool operator==(const FCarComponentHistory& other) const { return memcmp(this, &other, sizeof(FCarComponentHistory)) == 0; }
	bool operator!=(const FCarComponentHistory& other) const { return !(*this == other); }
	bool operator<(const FCarComponentHistory& other) const { return memcmp(this, &other, sizeof(FCarComponentHistory)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.CarFrameSettings
// 0x0060
struct FCarFrameSettings
{
	class FString                                      PlayerName;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FClientLoadoutData                          CarLoadout;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLinearColor                                TeamColor;                                     // 0x0020 (0x0010) [0x0000000000000000]               
	struct FLinearColor                                AccentColor;                                   // 0x0030 (0x0010) [0x0000000000000000]               
	class TArray<int32_t>                              PaintIDs;                                      // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              EsportsIDs;                                    // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCarFrameSettings& other) const { return memcmp(this, &other, sizeof(FCarFrameSettings)) == 0; }
	bool operator!=(const FCarFrameSettings& other) const { return !(*this == other); }
	bool operator<(const FCarFrameSettings& other) const { return memcmp(this, &other, sizeof(FCarFrameSettings)) < 0; }
};

// ScriptStruct TAGame.Replay_TA.SceneFrameCapture
// 0x0060
struct FSceneFrameCapture
{
	class FName                                        SceneName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        CameraModeName;                                // 0x0008 (0x0008) [0x0000000000000000]               
	class FString                                      FocusActorName;                                // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              TimeCaptured;                                  // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              CameraFOV;                                     // 0x0024 (0x0004) [0x0000000000000000]               
	struct FVector                                     CameraLocation;                                // 0x0028 (0x000C) [0x0000000000000000]               
	struct FRotator                                    CameraRotation;                                // 0x0034 (0x000C) [0x0000000000000000]               
	class TArray<struct FCarFrameSettings>             PlayerCarSettings;                             // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      OverrideBallType;                              // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSceneFrameCapture& other) const { return memcmp(this, &other, sizeof(FSceneFrameCapture)) == 0; }
	bool operator!=(const FSceneFrameCapture& other) const { return !(*this == other); }
	bool operator<(const FSceneFrameCapture& other) const { return memcmp(this, &other, sizeof(FSceneFrameCapture)) < 0; }
};

// ScriptStruct TAGame.Replay_Soccar_TA.ScoredGoal
// 0x001C
struct FScoredGoal
{
	int32_t                                            frame;                                         // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      PlayerName;                                    // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            PlayerTeam;                                    // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FScoredGoal& other) const { return memcmp(this, &other, sizeof(FScoredGoal)) == 0; }
	bool operator!=(const FScoredGoal& other) const { return !(*this == other); }
	bool operator<(const FScoredGoal& other) const { return memcmp(this, &other, sizeof(FScoredGoal)) < 0; }
};

// ScriptStruct TAGame.Replay_Soccar_TA.Highlight
// 0x001C
struct FHighlight
{
	int32_t                                            frame;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        CarName;                                       // 0x0004 (0x0008) [0x0000000000000000]               
	class FName                                        BallName;                                      // 0x000C (0x0008) [0x0000000000000000]               
	class FName                                        GoalActorName;                                 // 0x0014 (0x0008) [0x0000000000000000]               

	bool operator==(const FHighlight& other) const { return memcmp(this, &other, sizeof(FHighlight)) == 0; }
	bool operator!=(const FHighlight& other) const { return !(*this == other); }
	bool operator<(const FHighlight& other) const { return memcmp(this, &other, sizeof(FHighlight)) < 0; }
};

// ScriptStruct TAGame.ReplayCompatibilityActor_TA.ReplayRenamedActor
// 0x0020
struct FReplayRenamedActor
{
	class FString                                      OldPath;                                       // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      NewPath;                                       // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FReplayRenamedActor& other) const { return memcmp(this, &other, sizeof(FReplayRenamedActor)) == 0; }
	bool operator!=(const FReplayRenamedActor& other) const { return !(*this == other); }
	bool operator<(const FReplayRenamedActor& other) const { return memcmp(this, &other, sizeof(FReplayRenamedActor)) < 0; }
};

// ScriptStruct TAGame.ReplayDirector_TA.ReplayFocusCar
// 0x0014
struct FReplayFocusCar
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Duration;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	class FName                                        CarName;                                       // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            BallHitIndex;                                  // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FReplayFocusCar& other) const { return memcmp(this, &other, sizeof(FReplayFocusCar)) == 0; }
	bool operator!=(const FReplayFocusCar& other) const { return !(*this == other); }
	bool operator<(const FReplayFocusCar& other) const { return memcmp(this, &other, sizeof(FReplayFocusCar)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayIOTaskBase
// 0x0028
struct FReplayIOTaskBase
{
	class UReplay_TA*                                  Replay;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Path;                                          // 0x0008 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UErrorType*                                  Error;                                         // 0x0018 (0x0008) [0x0000000000000000]               
	struct FPointer                                    Ar;                                            // 0x0020 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FReplayIOTaskBase& other) const { return memcmp(this, &other, sizeof(FReplayIOTaskBase)) == 0; }
	bool operator!=(const FReplayIOTaskBase& other) const { return !(*this == other); }
	bool operator<(const FReplayIOTaskBase& other) const { return memcmp(this, &other, sizeof(FReplayIOTaskBase)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayExportCallbackData
// 0x0020
struct FReplayExportCallbackData
{
	struct FPointer                                    Task;                                          // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FReplayExportCallbackData& other) const { return memcmp(this, &other, sizeof(FReplayExportCallbackData)) == 0; }
	bool operator!=(const FReplayExportCallbackData& other) const { return !(*this == other); }
	bool operator<(const FReplayExportCallbackData& other) const { return memcmp(this, &other, sizeof(FReplayExportCallbackData)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayImportCallbackData
// 0x0020
struct FReplayImportCallbackData
{
	struct FPointer                                    Task;                                          // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FReplayImportCallbackData& other) const { return memcmp(this, &other, sizeof(FReplayImportCallbackData)) == 0; }
	bool operator!=(const FReplayImportCallbackData& other) const { return !(*this == other); }
	bool operator<(const FReplayImportCallbackData& other) const { return memcmp(this, &other, sizeof(FReplayImportCallbackData)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayExportTask
// 0x0014 (0x0028 - 0x003C)
struct FReplayExportTask : FReplayIOTaskBase
{
	class TArray<uint8_t>                              Data;                                          // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	uint32_t                                           bDebug : 1;                                    // 0x0038 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FReplayExportTask& other) const { return memcmp(this, &other, sizeof(FReplayExportTask)) == 0; }
	bool operator!=(const FReplayExportTask& other) const { return !(*this == other); }
	bool operator<(const FReplayExportTask& other) const { return memcmp(this, &other, sizeof(FReplayExportTask)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayClassTask
// 0x0010 (0x0028 - 0x0038)
struct FReplayClassTask : FReplayIOTaskBase
{
	class FString                                      ClassPath;                                     // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FReplayClassTask& other) const { return memcmp(this, &other, sizeof(FReplayClassTask)) == 0; }
	bool operator!=(const FReplayClassTask& other) const { return !(*this == other); }
	bool operator<(const FReplayClassTask& other) const { return memcmp(this, &other, sizeof(FReplayClassTask)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayHeaderImportTask
// 0x0000 (0x0028 - 0x0028)
struct FReplayHeaderImportTask : FReplayIOTaskBase
{

	bool operator==(const FReplayHeaderImportTask& other) const { return memcmp(this, &other, sizeof(FReplayHeaderImportTask)) == 0; }
	bool operator!=(const FReplayHeaderImportTask& other) const { return !(*this == other); }
	bool operator<(const FReplayHeaderImportTask& other) const { return memcmp(this, &other, sizeof(FReplayHeaderImportTask)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayImportTask
// 0x0010 (0x0028 - 0x0038)
struct FReplayImportTask : FReplayIOTaskBase
{
	class TArray<uint8_t>                              Data;                                          // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FReplayImportTask& other) const { return memcmp(this, &other, sizeof(FReplayImportTask)) == 0; }
	bool operator!=(const FReplayImportTask& other) const { return !(*this == other); }
	bool operator<(const FReplayImportTask& other) const { return memcmp(this, &other, sizeof(FReplayImportTask)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayTypeData
// 0x0020
struct FReplayTypeData
{
	class FString                                      FilePath;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ClassPath;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FReplayTypeData& other) const { return memcmp(this, &other, sizeof(FReplayTypeData)) == 0; }
	bool operator!=(const FReplayTypeData& other) const { return !(*this == other); }
	bool operator<(const FReplayTypeData& other) const { return memcmp(this, &other, sizeof(FReplayTypeData)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayHeadersCountTask
// 0x0038
struct FReplayHeadersCountTask
{
	class FString                                      Path;                                          // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class TArray<class FString>                        FileNameFilters;                               // 0x0010 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class TArray<struct FReplayTypeData>               Replays;                                       // 0x0020 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UErrorType*                                  Error;                                         // 0x0030 (0x0008) [0x0000000000000000]               

	bool operator==(const FReplayHeadersCountTask& other) const { return memcmp(this, &other, sizeof(FReplayHeadersCountTask)) == 0; }
	bool operator!=(const FReplayHeadersCountTask& other) const { return !(*this == other); }
	bool operator<(const FReplayHeadersCountTask& other) const { return memcmp(this, &other, sizeof(FReplayHeadersCountTask)) < 0; }
};

// ScriptStruct TAGame.ReplayManager_TA.ReplayUpdateDataMapTask
// 0x0060
struct FReplayUpdateDataMapTask
{
	struct FMap_Mirror                                 Data;                                          // 0x0000 (0x0050) [0x0000000000101000] (CPF_Native)  
	int32_t                                            RemovedIndex;                                  // 0x0050 (0x0004) [0x0000000000100000]               
	class UErrorType*                                  Error;                                         // 0x0058 (0x0008) [0x0000000000000000]               

	bool operator==(const FReplayUpdateDataMapTask& other) const { return memcmp(this, &other, sizeof(FReplayUpdateDataMapTask)) == 0; }
	bool operator!=(const FReplayUpdateDataMapTask& other) const { return !(*this == other); }
	bool operator<(const FReplayUpdateDataMapTask& other) const { return memcmp(this, &other, sizeof(FReplayUpdateDataMapTask)) < 0; }
};

// ScriptStruct TAGame.RewardDropGroup_TA.GFxRewardDrop
// 0x0018
struct FGFxRewardDrop
{
	class FName                                        RewardName;                                    // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Total;                                         // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Base;                                          // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            BaseLevel;                                     // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Level;                                         // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FGFxRewardDrop& other) const { return memcmp(this, &other, sizeof(FGFxRewardDrop)) == 0; }
	bool operator!=(const FGFxRewardDrop& other) const { return !(*this == other); }
	bool operator<(const FGFxRewardDrop& other) const { return memcmp(this, &other, sizeof(FGFxRewardDrop)) < 0; }
};

// ScriptStruct TAGame.RLBot_Util_TA.BotLoadout
// 0x0028
struct FBotLoadout
{
	class TArray<int32_t>                              Products;                                      // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              Paints;                                        // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FColor                                      PrimaryColor;                                  // 0x0020 (0x0004) [0x0001000000000000]               
	struct FColor                                      SecondaryColor;                                // 0x0024 (0x0004) [0x0001000000000000]               

	bool operator==(const FBotLoadout& other) const { return memcmp(this, &other, sizeof(FBotLoadout)) == 0; }
	bool operator!=(const FBotLoadout& other) const { return !(*this == other); }
	bool operator<(const FBotLoadout& other) const { return memcmp(this, &other, sizeof(FBotLoadout)) < 0; }
};

// ScriptStruct TAGame.RLBot_Util_TA.PlayerStats
// 0x001C
struct FPlayerStats
{
	int32_t                                            Score;                                         // 0x0000 (0x0004) [0x0001000000000000]               
	int32_t                                            Goals;                                         // 0x0004 (0x0004) [0x0001000000000000]               
	int32_t                                            OwnGoals;                                      // 0x0008 (0x0004) [0x0001000000000000]               
	int32_t                                            Assists;                                       // 0x000C (0x0004) [0x0001000000000000]               
	int32_t                                            Saves;                                         // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            Shots;                                         // 0x0014 (0x0004) [0x0001000000000000]               
	int32_t                                            Demolitions;                                   // 0x0018 (0x0004) [0x0001000000000000]               

	bool operator==(const FPlayerStats& other) const { return memcmp(this, &other, sizeof(FPlayerStats)) == 0; }
	bool operator!=(const FPlayerStats& other) const { return !(*this == other); }
	bool operator<(const FPlayerStats& other) const { return memcmp(this, &other, sizeof(FPlayerStats)) < 0; }
};

// ScriptStruct TAGame.RLBot_Util_TA.PlayerPickupData
// 0x0010
struct FPlayerPickupData
{
	class FName                                        PickupClass;                                   // 0x0000 (0x0008) [0x0001000000000000]               
	int32_t                                            TimeTillItem;                                  // 0x0008 (0x0004) [0x0001000000000000]               
	int32_t                                            MaxTimeTillItem;                               // 0x000C (0x0004) [0x0001000000000000]               

	bool operator==(const FPlayerPickupData& other) const { return memcmp(this, &other, sizeof(FPlayerPickupData)) == 0; }
	bool operator!=(const FPlayerPickupData& other) const { return !(*this == other); }
	bool operator<(const FPlayerPickupData& other) const { return memcmp(this, &other, sizeof(FPlayerPickupData)) < 0; }
};

// ScriptStruct TAGame.RocketPassMetrics_TA.RocketPassPremiumData
// 0x0010
struct FRocketPassPremiumData
{
	uint64_t                                           StartTimestamp;                                // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FRocketPassPremiumData& other) const { return memcmp(this, &other, sizeof(FRocketPassPremiumData)) == 0; }
	bool operator!=(const FRocketPassPremiumData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassPremiumData& other) const { return memcmp(this, &other, sizeof(FRocketPassPremiumData)) < 0; }
};

// ScriptStruct TAGame.RocketPassMetrics_TA.RocketPassTiersData
// 0x0014
struct FRocketPassTiersData
{
	uint64_t                                           StartTimestamp;                                // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            PurchasableID;                                 // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FRocketPassTiersData& other) const { return memcmp(this, &other, sizeof(FRocketPassTiersData)) == 0; }
	bool operator!=(const FRocketPassTiersData& other) const { return !(*this == other); }
	bool operator<(const FRocketPassTiersData& other) const { return memcmp(this, &other, sizeof(FRocketPassTiersData)) < 0; }
};

// ScriptStruct TAGame.RocketPassPreviewSet_TA.SetPreviewProductParams
// 0x000C
struct FSetPreviewProductParams
{
	int32_t                                            SlotIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FProductHashID                              HashID;                                        // 0x0004 (0x0004) [0x0000000000000000]               
	uint32_t                                           bUseBaseLoadout : 1;                           // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FSetPreviewProductParams& other) const { return memcmp(this, &other, sizeof(FSetPreviewProductParams)) == 0; }
	bool operator!=(const FSetPreviewProductParams& other) const { return !(*this == other); }
	bool operator<(const FSetPreviewProductParams& other) const { return memcmp(this, &other, sizeof(FSetPreviewProductParams)) < 0; }
};

// ScriptStruct TAGame.RPC_ProductsDebugAddProduct_TA.AddProductAttribute
// 0x0018
struct FAddProductAttribute
{
	class FName                                        Key;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Value;                                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAddProductAttribute& other) const { return memcmp(this, &other, sizeof(FAddProductAttribute)) == 0; }
	bool operator!=(const FAddProductAttribute& other) const { return !(*this == other); }
	bool operator<(const FAddProductAttribute& other) const { return memcmp(this, &other, sizeof(FAddProductAttribute)) < 0; }
};

// ScriptStruct TAGame.RPC_ProductsDebugAddProducts_TA.AddProductsResponseData
// 0x0040
struct FAddProductsResponseData
{
	int32_t                                            ProductID;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000000000000000]               
	class TArray<struct FOnlineProductAttribute>       Attributes;                                    // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            SeriesID;                                      // 0x0028 (0x0004) [0x0000000000000000]               
	uint64_t                                           AddedTimestamp;                                // 0x0030 (0x0008) [0x0000000000000000]               
	uint64_t                                           UpdatedTimestamp;                              // 0x0038 (0x0008) [0x0000000000000000]               

	bool operator==(const FAddProductsResponseData& other) const { return memcmp(this, &other, sizeof(FAddProductsResponseData)) == 0; }
	bool operator!=(const FAddProductsResponseData& other) const { return !(*this == other); }
	bool operator<(const FAddProductsResponseData& other) const { return memcmp(this, &other, sizeof(FAddProductsResponseData)) < 0; }
};

// ScriptStruct TAGame.RPC_ProductsLoadoutGet_TA.InstanceToSlotRow
// 0x0018
struct FInstanceToSlotRow
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0000000000000000]               
	int32_t                                            SlotIndex;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            TeamIndex;                                     // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FInstanceToSlotRow& other) const { return memcmp(this, &other, sizeof(FInstanceToSlotRow)) == 0; }
	bool operator!=(const FInstanceToSlotRow& other) const { return !(*this == other); }
	bool operator<(const FInstanceToSlotRow& other) const { return memcmp(this, &other, sizeof(FInstanceToSlotRow)) < 0; }
};

// ScriptStruct TAGame.RPC_PsyNetGetVanities_TA.VanityProductInfo
// 0x0068
struct FVanityProductInfo
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              VanityTypes;                                   // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineProductData>            ProductData;                                   // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVanityProductInfo& other) const { return memcmp(this, &other, sizeof(FVanityProductInfo)) == 0; }
	bool operator!=(const FVanityProductInfo& other) const { return !(*this == other); }
	bool operator<(const FVanityProductInfo& other) const { return memcmp(this, &other, sizeof(FVanityProductInfo)) < 0; }
};

// ScriptStruct TAGame.RPC_PsyNetGetVanities_TA.VanityProductData
// 0x0068
struct FVanityProductData
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              VanityTypes;                                   // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UOnlineProduct_TA*>             VanityProducts;                                // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FVanityProductData& other) const { return memcmp(this, &other, sizeof(FVanityProductData)) == 0; }
	bool operator!=(const FVanityProductData& other) const { return !(*this == other); }
	bool operator<(const FVanityProductData& other) const { return memcmp(this, &other, sizeof(FVanityProductData)) < 0; }
};

// ScriptStruct TAGame.RPC_PsyNetSetVanity_TA.VanityLoadout
// 0x001C
struct FVanityLoadout
{
	int32_t                                            VanityType;                                    // 0x0000 (0x0004) [0x0000004000000000] (CPF_PrivateWrite)
	struct FProductInstanceID                          InstanceID;                                    // 0x0008 (0x0010) [0x0000004000000000] (CPF_PrivateWrite)
	int32_t                                            UserColor;                                     // 0x0018 (0x0004) [0x0000004000000000] (CPF_PrivateWrite)

	bool operator==(const FVanityLoadout& other) const { return memcmp(this, &other, sizeof(FVanityLoadout)) == 0; }
	bool operator!=(const FVanityLoadout& other) const { return !(*this == other); }
	bool operator<(const FVanityLoadout& other) const { return memcmp(this, &other, sizeof(FVanityLoadout)) < 0; }
};

// ScriptStruct TAGame.SampleHistory_TA.Sample
// 0x0008
struct FSample
{
	float                                              Low;                                           // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              High;                                          // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FSample& other) const { return memcmp(this, &other, sizeof(FSample)) == 0; }
	bool operator!=(const FSample& other) const { return !(*this == other); }
	bool operator<(const FSample& other) const { return memcmp(this, &other, sizeof(FSample)) < 0; }
};

// ScriptStruct TAGame.SampleHistory_TA.GraphSummaryMethod
// 0x000C
struct FGraphSummaryMethod
{
	EGraphSummaryType                                  Type;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	float                                              MaxSampleAge;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	uint32_t                                           bAbsoluteValue : 1;                            // 0x0008 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FGraphSummaryMethod& other) const { return memcmp(this, &other, sizeof(FGraphSummaryMethod)) == 0; }
	bool operator!=(const FGraphSummaryMethod& other) const { return !(*this == other); }
	bool operator<(const FGraphSummaryMethod& other) const { return memcmp(this, &other, sizeof(FGraphSummaryMethod)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.DingoContentCache
// 0x0008
struct FDingoContentCache
{
	uint64_t                                           UserXUID;                                      // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FDingoContentCache& other) const { return memcmp(this, &other, sizeof(FDingoContentCache)) == 0; }
	bool operator!=(const FDingoContentCache& other) const { return !(*this == other); }
	bool operator<(const FDingoContentCache& other) const { return memcmp(this, &other, sizeof(FDingoContentCache)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.SaveDataTask
// 0x0018
struct FSaveDataTask
{
	int32_t                                            ControllerIndex;                               // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      Path;                                          // 0x0008 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FSaveDataTask& other) const { return memcmp(this, &other, sizeof(FSaveDataTask)) == 0; }
	bool operator!=(const FSaveDataTask& other) const { return !(*this == other); }
	bool operator<(const FSaveDataTask& other) const { return memcmp(this, &other, sizeof(FSaveDataTask)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.SaveDataDeleteTask
// 0x0004 (0x0018 - 0x001C)
struct FSaveDataDeleteTask : FSaveDataTask
{
	int32_t                                            KeepNewestFileCount;                           // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FSaveDataDeleteTask& other) const { return memcmp(this, &other, sizeof(FSaveDataDeleteTask)) == 0; }
	bool operator!=(const FSaveDataDeleteTask& other) const { return !(*this == other); }
	bool operator<(const FSaveDataDeleteTask& other) const { return memcmp(this, &other, sizeof(FSaveDataDeleteTask)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.SaveDataListFilesTask
// 0x0021 (0x0018 - 0x0039)
struct FSaveDataListFilesTask : FSaveDataTask
{
	class FString                                      Pattern;                                       // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Files;                                         // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	EBasicLoadResult                                   Result;                                        // 0x0038 (0x0001) [0x0000000000000000]               

	bool operator==(const FSaveDataListFilesTask& other) const { return memcmp(this, &other, sizeof(FSaveDataListFilesTask)) == 0; }
	bool operator!=(const FSaveDataListFilesTask& other) const { return !(*this == other); }
	bool operator<(const FSaveDataListFilesTask& other) const { return memcmp(this, &other, sizeof(FSaveDataListFilesTask)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.SaveDataImportTask
// 0x0024 (0x0018 - 0x003C)
struct FSaveDataImportTask : FSaveDataTask
{
	class UObject*                                     SaveDataObject;                                // 0x0018 (0x0008) [0x0000000000100000]               
	EBasicLoadResult                                   Result;                                        // 0x0020 (0x0001) [0x0000000000000000]               
	class TArray<uint8_t>                              Data;                                          // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	uint32_t                                           bExactFileMatch : 1;                           // 0x0038 (0x0004) [0x0000000000100000] [0x00000001] 
	uint32_t                                           bPlayerSaveData : 1;                           // 0x0038 (0x0004) [0x0000000000100000] [0x100000002] 

	bool operator==(const FSaveDataImportTask& other) const { return memcmp(this, &other, sizeof(FSaveDataImportTask)) == 0; }
	bool operator!=(const FSaveDataImportTask& other) const { return !(*this == other); }
	bool operator<(const FSaveDataImportTask& other) const { return memcmp(this, &other, sizeof(FSaveDataImportTask)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.SaveDataExportTask
// 0x001C (0x0018 - 0x0034)
struct FSaveDataExportTask : FSaveDataTask
{
	class TArray<uint8_t>                              Data;                                          // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	uint32_t                                           bExactFileMatch : 1;                           // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bPlayerSaveData : 1;                           // 0x0028 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bEncryptAndCRC : 1;                            // 0x0028 (0x0004) [0x0000000000000000] [0x00000004] 
	ESaveGameResult                                    Result;                                        // 0x002C (0x0001) [0x0000000000000000]               
	int32_t                                            KeepNewestSaveFileCount;                       // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FSaveDataExportTask& other) const { return memcmp(this, &other, sizeof(FSaveDataExportTask)) == 0; }
	bool operator!=(const FSaveDataExportTask& other) const { return !(*this == other); }
	bool operator<(const FSaveDataExportTask& other) const { return memcmp(this, &other, sizeof(FSaveDataExportTask)) < 0; }
};

// ScriptStruct TAGame.SaveObjectManager_TA.InitSaveProviderTask
// 0x0001 (0x0018 - 0x0019)
struct FInitSaveProviderTask : FSaveDataTask
{
	EInitSaveProviderResult                            Result;                                        // 0x0018 (0x0001) [0x0000000000000000]               

	bool operator==(const FInitSaveProviderTask& other) const { return memcmp(this, &other, sizeof(FInitSaveProviderTask)) == 0; }
	bool operator!=(const FInitSaveProviderTask& other) const { return !(*this == other); }
	bool operator<(const FInitSaveProviderTask& other) const { return memcmp(this, &other, sizeof(FInitSaveProviderTask)) < 0; }
};

// ScriptStruct TAGame.SeqAct_DriveSpline_TA.CarSplineData
// 0x0018
struct FCarSplineData
{
	class ACar_TA*                                     Car;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class ASplineActor*                                Spline;                                        // 0x0008 (0x0008) [0x0000000000000000]               
	float                                              DistanceAlongSpline;                           // 0x0010 (0x0004) [0x0000000000000000]               
	uint32_t                                           bReachedSpline : 1;                            // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FCarSplineData& other) const { return memcmp(this, &other, sizeof(FCarSplineData)) == 0; }
	bool operator!=(const FCarSplineData& other) const { return !(*this == other); }
	bool operator<(const FCarSplineData& other) const { return memcmp(this, &other, sizeof(FCarSplineData)) < 0; }
};

// ScriptStruct TAGame.SeqAct_SpawnCarColors_TA.SpawnCarColorSet
// 0x000C
struct FSpawnCarColorSet
{
	class UCarColorSet_TA*                             ColorSet;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bRender : 1;                                   // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)

	bool operator==(const FSpawnCarColorSet& other) const { return memcmp(this, &other, sizeof(FSpawnCarColorSet)) == 0; }
	bool operator!=(const FSpawnCarColorSet& other) const { return !(*this == other); }
	bool operator<(const FSpawnCarColorSet& other) const { return memcmp(this, &other, sizeof(FSpawnCarColorSet)) < 0; }
};

// ScriptStruct TAGame.ShopCatalogueCacheSave_TA.CatalogueCacheItem
// 0x0018
struct FCatalogueCacheItem
{
	int32_t                                            ShopID;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FShopItemCacheItem>            StoreItems;                                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCatalogueCacheItem& other) const { return memcmp(this, &other, sizeof(FCatalogueCacheItem)) == 0; }
	bool operator!=(const FCatalogueCacheItem& other) const { return !(*this == other); }
	bool operator<(const FCatalogueCacheItem& other) const { return memcmp(this, &other, sizeof(FCatalogueCacheItem)) < 0; }
};

// ScriptStruct TAGame.ShopMetrics_TA.ShopItemData
// 0x0020
struct FShopItemData
{
	int32_t                                            ShopItemID;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            NumTimesPreviewed;                             // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            NumTimesPurchaseOpened;                        // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            NumTimesPurchaseCancelled;                     // 0x000C (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              Costs;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopItemData& other) const { return memcmp(this, &other, sizeof(FShopItemData)) == 0; }
	bool operator!=(const FShopItemData& other) const { return !(*this == other); }
	bool operator<(const FShopItemData& other) const { return memcmp(this, &other, sizeof(FShopItemData)) < 0; }
};

// ScriptStruct TAGame.ShopMetrics_TA.ShopTabData
// 0x0030
struct FShopTabData
{
	int32_t                                            FromShopID;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            NewShopID;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            FromCatalogID;                                 // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            NewCatalogID;                                  // 0x000C (0x0004) [0x0000000000000000]               
	uint64_t                                           StartTimestamp;                                // 0x0010 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0018 (0x0008) [0x0000000000000000]               
	class TArray<struct FShopItemData>                 ItemMetrics;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FShopTabData& other) const { return memcmp(this, &other, sizeof(FShopTabData)) == 0; }
	bool operator!=(const FShopTabData& other) const { return !(*this == other); }
	bool operator<(const FShopTabData& other) const { return memcmp(this, &other, sizeof(FShopTabData)) < 0; }
};

// ScriptStruct TAGame.SkelControlSingleBoneCopy_TA.AxisConversion
// 0x000C
struct FAxisConversion
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	ECopyAxis                                          Source;                                        // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              Scale;                                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAxisConversion& other) const { return memcmp(this, &other, sizeof(FAxisConversion)) == 0; }
	bool operator!=(const FAxisConversion& other) const { return !(*this == other); }
	bool operator<(const FAxisConversion& other) const { return memcmp(this, &other, sizeof(FAxisConversion)) < 0; }
};

// ScriptStruct TAGame.SkeletalMeshActorMAT_Products_TA.BothWheelAssets
// 0x0010
struct FBothWheelAssets
{
	class UMeshComponent*                              Left;                                          // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class UMeshComponent*                              Right;                                         // 0x0008 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FBothWheelAssets& other) const { return memcmp(this, &other, sizeof(FBothWheelAssets)) == 0; }
	bool operator!=(const FBothWheelAssets& other) const { return !(*this == other); }
	bool operator<(const FBothWheelAssets& other) const { return memcmp(this, &other, sizeof(FBothWheelAssets)) < 0; }
};

// ScriptStruct TAGame.SonyPricingInfo_TA.BaseInput
// 0x0044
struct FBaseInput
{
	class FString                                      Country;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      offerName;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      retailPrice;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      currencySymbol;                                // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            CurrencyAmount;                                // 0x0040 (0x0004) [0x0000000000000000]               

	bool operator==(const FBaseInput& other) const { return memcmp(this, &other, sizeof(FBaseInput)) == 0; }
	bool operator!=(const FBaseInput& other) const { return !(*this == other); }
	bool operator<(const FBaseInput& other) const { return memcmp(this, &other, sizeof(FBaseInput)) < 0; }
};

// ScriptStruct TAGame.SpecialEventConfig_TA.DebugMicroEventPlaylistID
// 0x0004
struct FDebugMicroEventPlaylistID
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)

	bool operator==(const FDebugMicroEventPlaylistID& other) const { return memcmp(this, &other, sizeof(FDebugMicroEventPlaylistID)) == 0; }
	bool operator!=(const FDebugMicroEventPlaylistID& other) const { return !(*this == other); }
	bool operator<(const FDebugMicroEventPlaylistID& other) const { return memcmp(this, &other, sizeof(FDebugMicroEventPlaylistID)) < 0; }
};

// ScriptStruct TAGame.SpecialPickup_TA.PickupReplacement
// 0x0010
struct FPickupReplacement
{
	class UProduct_TA*                                 Body;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class ASpecialPickup_TA*                           Pickup;                                        // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FPickupReplacement& other) const { return memcmp(this, &other, sizeof(FPickupReplacement)) == 0; }
	bool operator!=(const FPickupReplacement& other) const { return !(*this == other); }
	bool operator<(const FPickupReplacement& other) const { return memcmp(this, &other, sizeof(FPickupReplacement)) < 0; }
};

// ScriptStruct TAGame.SpecialPickup_Football_TA.ThrowSetting
// 0x001C
struct FThrowSetting
{
	float                                              Pitch;                                         // 0x0000 (0x0004) [0x0001000000000000]               
	float                                              LinearScale;                                   // 0x0004 (0x0004) [0x0001000000000000]               
	float                                              AngularScale;                                  // 0x0008 (0x0004) [0x0001000000000000]               
	float                                              MinLinearForce;                                // 0x000C (0x0004) [0x0001000000000000]               
	float                                              MaxLinearForce;                                // 0x0010 (0x0004) [0x0001000000000000]               
	float                                              MinAngularForce;                               // 0x0014 (0x0004) [0x0001000000000000]               
	float                                              MaxAngularForce;                               // 0x0018 (0x0004) [0x0001000000000000]               

	bool operator==(const FThrowSetting& other) const { return memcmp(this, &other, sizeof(FThrowSetting)) == 0; }
	bool operator!=(const FThrowSetting& other) const { return !(*this == other); }
	bool operator<(const FThrowSetting& other) const { return memcmp(this, &other, sizeof(FThrowSetting)) < 0; }
};

// ScriptStruct TAGame.StatFactory_TA.BallInfo
// 0x0040
struct FBallInfo
{
	class ABall_TA*                                    Ball;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class UGoal_TA*                                    ShotGoal;                                      // 0x0008 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class UGoal_TA*                                    RedZoneGoal;                                   // 0x0010 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class APRI_TA*                                     RedZonePRI;                                    // 0x0018 (0x0008) [0x0000000000000000]               
	int32_t                                            RedZoneHitID;                                  // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              GroundHitTime;                                 // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              JuggleTime;                                    // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              SpecialHitTime;                                // 0x002C (0x0004) [0x0000000000000000]               
	float                                              BallHitTime;                                   // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              SaveTime;                                      // 0x0034 (0x0004) [0x0000000000000000]               
	float                                              ShotTime;                                      // 0x0038 (0x0004) [0x0000000000000000]               
	float                                              CrossbarHitTime;                               // 0x003C (0x0004) [0x0001000000000000]               

	bool operator==(const FBallInfo& other) const { return memcmp(this, &other, sizeof(FBallInfo)) == 0; }
	bool operator!=(const FBallInfo& other) const { return !(*this == other); }
	bool operator<(const FBallInfo& other) const { return memcmp(this, &other, sizeof(FBallInfo)) < 0; }
};

// ScriptStruct TAGame.StatFactory_TA.StatGroupCollection
// 0x0030
struct FStatGroupCollection
{
	class UStatGroup_TA*                               Wins;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatGroup_TA*                               Losses;                                        // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatGroup_TA*                               Goals;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatGroup_TA*                               Saves;                                         // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatGroup_TA*                               Shots;                                         // 0x0020 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStatGroup_TA*                               Assists;                                       // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FStatGroupCollection& other) const { return memcmp(this, &other, sizeof(FStatGroupCollection)) == 0; }
	bool operator!=(const FStatGroupCollection& other) const { return !(*this == other); }
	bool operator<(const FStatGroupCollection& other) const { return memcmp(this, &other, sizeof(FStatGroupCollection)) < 0; }
};

// ScriptStruct TAGame.StatFactory_KnockOut_TA.StatEventCollection_KO
// 0x0098
struct FStatEventCollection_KO
{
	class UStatEvent_TA*                               Knockout;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               KnockoutAssist;                                // 0x0008 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               Death;                                         // 0x0010 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               PlayerGrabbed;                                 // 0x0018 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               PlayerThrown;                                  // 0x0020 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               Grabbed;                                       // 0x0028 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               Thrown;                                        // 0x0030 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               HeavyHit;                                      // 0x0038 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               LightHit;                                      // 0x0040 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               AerialHeavyHit;                                // 0x0048 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               AerialLightHit;                                // 0x0050 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               HitTaken;                                      // 0x0058 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               HeavyBlock;                                    // 0x0060 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               LightBlock;                                    // 0x0068 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               BlockTaken;                                    // 0x0070 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               DoubleKO;                                      // 0x0078 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               TripleKO;                                      // 0x0080 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               MassKO;                                        // 0x0088 (0x0008) [0x0000000000000000]               
	class UStatEvent_TA*                               Winner;                                        // 0x0090 (0x0008) [0x0000000000000000]               

	bool operator==(const FStatEventCollection_KO& other) const { return memcmp(this, &other, sizeof(FStatEventCollection_KO)) == 0; }
	bool operator!=(const FStatEventCollection_KO& other) const { return !(*this == other); }
	bool operator<(const FStatEventCollection_KO& other) const { return memcmp(this, &other, sizeof(FStatEventCollection_KO)) < 0; }
};

// ScriptStruct TAGame.StatGraphDrawer_TA.SummaryLabel
// 0x0024
struct FSummaryLabel
{
	class FString                                      Label;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            LabelWidth;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	struct FLinearColor                                Color;                                         // 0x0014 (0x0010) [0x0000000000000000]               

	bool operator==(const FSummaryLabel& other) const { return memcmp(this, &other, sizeof(FSummaryLabel)) == 0; }
	bool operator!=(const FSummaryLabel& other) const { return !(*this == other); }
	bool operator<(const FSummaryLabel& other) const { return memcmp(this, &other, sizeof(FSummaryLabel)) < 0; }
};

// ScriptStruct TAGame.StatGraphDrawer_TA.GraphLine
// 0x0028
struct FGraphLine
{
	struct FVector                                     Start;                                         // 0x0000 (0x000C) [0x0000000000100000]               
	struct FVector                                     End;                                           // 0x000C (0x000C) [0x0000000000100000]               
	struct FLinearColor                                Color;                                         // 0x0018 (0x0010) [0x0000000000100000]               

	bool operator==(const FGraphLine& other) const { return memcmp(this, &other, sizeof(FGraphLine)) == 0; }
	bool operator!=(const FGraphLine& other) const { return !(*this == other); }
	bool operator<(const FGraphLine& other) const { return memcmp(this, &other, sizeof(FGraphLine)) < 0; }
};

// ScriptStruct TAGame.StayAsPartyMetrics_TA.PartyMergeResult
// 0x009C
struct FPartyMergeResult
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                LeaderID;                                      // 0x0048 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bSuccess : 1;                                  // 0x0090 (0x0004) [0x0000000000000000] [0x00000001] 
	class FName                                        FailReason;                                    // 0x0094 (0x0008) [0x0000000000000000]               

	bool operator==(const FPartyMergeResult& other) const { return memcmp(this, &other, sizeof(FPartyMergeResult)) == 0; }
	bool operator!=(const FPartyMergeResult& other) const { return !(*this == other); }
	bool operator<(const FPartyMergeResult& other) const { return memcmp(this, &other, sizeof(FPartyMergeResult)) < 0; }
};

// ScriptStruct TAGame.TourCredentials_TA.CredentialItem
// 0x0028
struct FCredentialItem
{
	uint64_t                                           TourID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	struct FTourPrivateCredentials                     Credentials;                                   // 0x0008 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCredentialItem& other) const { return memcmp(this, &other, sizeof(FCredentialItem)) == 0; }
	bool operator!=(const FCredentialItem& other) const { return !(*this == other); }
	bool operator<(const FCredentialItem& other) const { return memcmp(this, &other, sizeof(FCredentialItem)) < 0; }
};

// ScriptStruct TAGame.TourRewards_TA.RewardsResult
// 0x0018
struct FRewardsResult
{
	uint64_t                                           TourID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FTourReward>                   Rewards;                                       // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRewardsResult& other) const { return memcmp(this, &other, sizeof(FRewardsResult)) == 0; }
	bool operator!=(const FRewardsResult& other) const { return !(*this == other); }
	bool operator<(const FRewardsResult& other) const { return memcmp(this, &other, sizeof(FRewardsResult)) < 0; }
};

// ScriptStruct TAGame.TourRewards_TA.RewardsRequest
// 0x0028
struct FRewardsRequest
{
	uint64_t                                           TourID;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class UAsyncTask*                                  Task;                                          // 0x0008 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0010 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRewardsRequest& other) const { return memcmp(this, &other, sizeof(FRewardsRequest)) == 0; }
	bool operator!=(const FRewardsRequest& other) const { return !(*this == other); }
	bool operator<(const FRewardsRequest& other) const { return memcmp(this, &other, sizeof(FRewardsRequest)) < 0; }
};

// ScriptStruct TAGame.TourSeeder_TA.TeamSeeds
// 0x0010
struct FTeamSeeds
{
	class TArray<uint64_t>                             Seeds;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTeamSeeds& other) const { return memcmp(this, &other, sizeof(FTeamSeeds)) == 0; }
	bool operator!=(const FTeamSeeds& other) const { return !(*this == other); }
	bool operator<(const FTeamSeeds& other) const { return memcmp(this, &other, sizeof(FTeamSeeds)) < 0; }
};

// ScriptStruct TAGame.TrainingEditorMetrics_TA.TrainingManipulationEvent
// 0x0014
struct FTrainingManipulationEvent
{
	uint64_t                                           TimeStamp;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	ETrainingManipulationCommand                       CommandUsed;                                   // 0x0008 (0x0001) [0x0000000000000000]               
	int32_t                                            RoundNum;                                      // 0x000C (0x0004) [0x0000000000000000]               
	uint32_t                                           bMirror : 1;                                   // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FTrainingManipulationEvent& other) const { return memcmp(this, &other, sizeof(FTrainingManipulationEvent)) == 0; }
	bool operator!=(const FTrainingManipulationEvent& other) const { return !(*this == other); }
	bool operator<(const FTrainingManipulationEvent& other) const { return memcmp(this, &other, sizeof(FTrainingManipulationEvent)) < 0; }
};

// ScriptStruct TAGame.Tutorial_TA.ButtonInfo
// 0x002C
struct FButtonInfo
{
	class FString                                      Text;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             ClickDelegate;                                 // 0x0010 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCorrectAnswer : 1;                            // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FButtonInfo& other) const { return memcmp(this, &other, sizeof(FButtonInfo)) == 0; }
	bool operator!=(const FButtonInfo& other) const { return !(*this == other); }
	bool operator<(const FButtonInfo& other) const { return memcmp(this, &other, sizeof(FButtonInfo)) < 0; }
};

// ScriptStruct TAGame.Tutorial_TA.ActionNameInfo
// 0x0010
struct FActionNameInfo
{
	class TArray<class FName>                          ActionNames;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FActionNameInfo& other) const { return memcmp(this, &other, sizeof(FActionNameInfo)) == 0; }
	bool operator!=(const FActionNameInfo& other) const { return !(*this == other); }
	bool operator<(const FActionNameInfo& other) const { return memcmp(this, &other, sizeof(FActionNameInfo)) < 0; }
};

// ScriptStruct TAGame.Tutorial_TA.MessageInfo
// 0x0040
struct FMessageInfo
{
	class FString                                      Title;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Body;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FButtonInfo>                   Buttons;                                       // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FActionNameInfo>               ActionNameList;                                // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMessageInfo& other) const { return memcmp(this, &other, sizeof(FMessageInfo)) == 0; }
	bool operator!=(const FMessageInfo& other) const { return !(*this == other); }
	bool operator<(const FMessageInfo& other) const { return memcmp(this, &other, sizeof(FMessageInfo)) < 0; }
};

// ScriptStruct TAGame.UserBugReportBulkData_TA.UserReportVideoSetting
// 0x0020
struct FUserReportVideoSetting
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUserReportVideoSetting& other) const { return memcmp(this, &other, sizeof(FUserReportVideoSetting)) == 0; }
	bool operator!=(const FUserReportVideoSetting& other) const { return !(*this == other); }
	bool operator<(const FUserReportVideoSetting& other) const { return memcmp(this, &other, sizeof(FUserReportVideoSetting)) < 0; }
};

// ScriptStruct TAGame.VanityQuery_TA.VanityQuerySet
// 0x0018
struct FVanityQuerySet
{
	class TArray<struct FUniqueNetId>                  PlayerIds;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EVanityType                                        VanityType;                                    // 0x0010 (0x0001) [0x0000000000000000]               
	uint32_t                                           bForced : 1;                                   // 0x0014 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FVanityQuerySet& other) const { return memcmp(this, &other, sizeof(FVanityQuerySet)) == 0; }
	bool operator!=(const FVanityQuerySet& other) const { return !(*this == other); }
	bool operator<(const FVanityQuerySet& other) const { return memcmp(this, &other, sizeof(FVanityQuerySet)) < 0; }
};

// ScriptStruct TAGame.VehiclePickup_TA.PickupData
// 0x000C
struct FPickupData
{
	class ACar_TA*                                     Instigator;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	uint32_t                                           bPickedUp : 1;                                 // 0x0008 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FPickupData& other) const { return memcmp(this, &other, sizeof(FPickupData)) == 0; }
	bool operator!=(const FPickupData& other) const { return !(*this == other); }
	bool operator<(const FPickupData& other) const { return memcmp(this, &other, sizeof(FPickupData)) < 0; }
};

// ScriptStruct TAGame.VehiclePickup_TA.PickupData2
// 0x0009
struct FPickupData2
{
	class ACar_TA*                                     Instigator;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	uint8_t                                            PickedUp;                                      // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FPickupData2& other) const { return memcmp(this, &other, sizeof(FPickupData2)) == 0; }
	bool operator!=(const FPickupData2& other) const { return !(*this == other); }
	bool operator<(const FPickupData2& other) const { return memcmp(this, &other, sizeof(FPickupData2)) < 0; }
};

// ScriptStruct TAGame.ViewMetrics_TA.InteractableData
// 0x0010
struct FInteractableData
{
	class FName                                        InteractableDescriptor;                        // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            InteractableID;                                // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            NumInteractions;                               // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FInteractableData& other) const { return memcmp(this, &other, sizeof(FInteractableData)) == 0; }
	bool operator!=(const FInteractableData& other) const { return !(*this == other); }
	bool operator<(const FInteractableData& other) const { return memcmp(this, &other, sizeof(FInteractableData)) < 0; }
};

// ScriptStruct TAGame.ViewMetrics_TA.ViewData
// 0x0028
struct FViewData
{
	int32_t                                            ExitedViewID;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            EnteredViewID;                                 // 0x0004 (0x0004) [0x0000000000000000]               
	uint64_t                                           StartTimestamp;                                // 0x0008 (0x0008) [0x0000000000000000]               
	uint64_t                                           EndTimestamp;                                  // 0x0010 (0x0008) [0x0000000000000000]               
	class TArray<struct FInteractableData>             InteractableMetrics;                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FViewData& other) const { return memcmp(this, &other, sizeof(FViewData)) == 0; }
	bool operator!=(const FViewData& other) const { return !(*this == other); }
	bool operator<(const FViewData& other) const { return memcmp(this, &other, sizeof(FViewData)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.StatsSocketEvent
// 0x0020
struct FStatsSocketEvent
{
	class FString                                      Event;                                         // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Data;                                          // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FStatsSocketEvent& other) const { return memcmp(this, &other, sizeof(FStatsSocketEvent)) == 0; }
	bool operator!=(const FStatsSocketEvent& other) const { return !(*this == other); }
	bool operator<(const FStatsSocketEvent& other) const { return memcmp(this, &other, sizeof(FStatsSocketEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.PlayerDataPacket
// 0x0018
struct FPlayerDataPacket
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            Shortcut;                                      // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            TeamNum;                                       // 0x0014 (0x0004) [0x0001000000000000]               

	bool operator==(const FPlayerDataPacket& other) const { return memcmp(this, &other, sizeof(FPlayerDataPacket)) == 0; }
	bool operator!=(const FPlayerDataPacket& other) const { return !(*this == other); }
	bool operator<(const FPlayerDataPacket& other) const { return memcmp(this, &other, sizeof(FPlayerDataPacket)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.PlayerUpdateState
// 0x0098
struct FPlayerUpdateState
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      PrimaryID;                                     // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            Shortcut;                                      // 0x0020 (0x0004) [0x0001000000000000]               
	int32_t                                            TeamNum;                                       // 0x0024 (0x0004) [0x0001000000000000]               
	int32_t                                            Score;                                         // 0x0028 (0x0004) [0x0001000000000000]               
	int32_t                                            Goals;                                         // 0x002C (0x0004) [0x0001000000000000]               
	int32_t                                            Shots;                                         // 0x0030 (0x0004) [0x0001000000000000]               
	int32_t                                            Assists;                                       // 0x0034 (0x0004) [0x0001000000000000]               
	int32_t                                            Saves;                                         // 0x0038 (0x0004) [0x0001000000000000]               
	int32_t                                            Touches;                                       // 0x003C (0x0004) [0x0001000000000000]               
	int32_t                                            CarTouches;                                    // 0x0040 (0x0004) [0x0001000000000000]               
	int32_t                                            Demos;                                         // 0x0044 (0x0004) [0x0001000000000000]               
	class TArray<class FString>                        Loadout;                                       // 0x0048 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bOnWall : 1;                                   // 0x0058 (0x0004) [0x0021000000000000] [0x00000001] 
	uint32_t                                           bOnGround : 1;                                 // 0x0058 (0x0004) [0x0021000000000000] [0x00000002] 
	uint32_t                                           bPowersliding : 1;                             // 0x0058 (0x0004) [0x0021000000000000] [0x00000004] 
	uint32_t                                           bDemolished : 1;                               // 0x0058 (0x0004) [0x0021000000000000] [0x00000008] 
	struct FPlayerDataPacket                           Attacker;                                      // 0x0060 (0x0018) [0x0021000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasCar : 1;                                   // 0x0078 (0x0004) [0x0021000000000000] [0x00000001] 
	float                                              Speed;                                         // 0x007C (0x0004) [0x0021000000000000]               
	int32_t                                            Boost;                                         // 0x0080 (0x0004) [0x0021000000000000]               
	uint32_t                                           bBoosting : 1;                                 // 0x0084 (0x0004) [0x0021000000000000] [0x00000001] 
	uint32_t                                           bSupersonic : 1;                               // 0x0084 (0x0004) [0x0021000000000000] [0x00000002] 
	class FString                                      PickupClass;                                   // 0x0088 (0x0010) [0x0021000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerUpdateState& other) const { return memcmp(this, &other, sizeof(FPlayerUpdateState)) == 0; }
	bool operator!=(const FPlayerUpdateState& other) const { return !(*this == other); }
	bool operator<(const FPlayerUpdateState& other) const { return memcmp(this, &other, sizeof(FPlayerUpdateState)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.TeamUpdateState
// 0x0038
struct FTeamUpdateState
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            TeamNum;                                       // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            Score;                                         // 0x0014 (0x0004) [0x0001000000000000]               
	class FString                                      ColorPrimary;                                  // 0x0018 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      ColorSecondary;                                // 0x0028 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTeamUpdateState& other) const { return memcmp(this, &other, sizeof(FTeamUpdateState)) == 0; }
	bool operator!=(const FTeamUpdateState& other) const { return !(*this == other); }
	bool operator<(const FTeamUpdateState& other) const { return memcmp(this, &other, sizeof(FTeamUpdateState)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.BallUpdateState
// 0x0008
struct FBallUpdateState
{
	float                                              Speed;                                         // 0x0000 (0x0004) [0x0001000000000000]               
	int32_t                                            TeamNum;                                       // 0x0004 (0x0004) [0x0001000000000000]               

	bool operator==(const FBallUpdateState& other) const { return memcmp(this, &other, sizeof(FBallUpdateState)) == 0; }
	bool operator!=(const FBallUpdateState& other) const { return !(*this == other); }
	bool operator<(const FBallUpdateState& other) const { return memcmp(this, &other, sizeof(FBallUpdateState)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.GameUpdateState
// 0x0070
struct FGameUpdateState
{
	class TArray<struct FTeamUpdateState>              Teams;                                         // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            PlaylistId;                                    // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            TimeSeconds;                                   // 0x0014 (0x0004) [0x0001000000000000]               
	uint32_t                                           bOverTime : 1;                                 // 0x0018 (0x0004) [0x0001000000000000] [0x00000001] 
	int32_t                                            frame;                                         // 0x001C (0x0004) [0x0021000000000000]               
	float                                              Elapsed;                                       // 0x0020 (0x0004) [0x0021000000000000]               
	struct FBallUpdateState                            Ball;                                          // 0x0024 (0x0008) [0x0001000000000000]               
	uint32_t                                           bReplay : 1;                                   // 0x002C (0x0004) [0x0001000000000000] [0x00000001] 
	uint32_t                                           bHasWinner : 1;                                // 0x002C (0x0004) [0x0001000000000000] [0x00000002] 
	class FString                                      Winner;                                        // 0x0030 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Arena;                                         // 0x0040 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasTarget : 1;                                // 0x0050 (0x0004) [0x0001000000000000] [0x00000001] 
	struct FPlayerDataPacket                           Target;                                        // 0x0058 (0x0018) [0x0021000000400000] (CPF_NeedCtorLink)

	bool operator==(const FGameUpdateState& other) const { return memcmp(this, &other, sizeof(FGameUpdateState)) == 0; }
	bool operator!=(const FGameUpdateState& other) const { return !(*this == other); }
	bool operator<(const FGameUpdateState& other) const { return memcmp(this, &other, sizeof(FGameUpdateState)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.UpdateStateData
// 0x0090
struct FUpdateStateData
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class TArray<struct FPlayerUpdateState>            Players;                                       // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FGameUpdateState                            Game;                                          // 0x0020 (0x0070) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUpdateStateData& other) const { return memcmp(this, &other, sizeof(FUpdateStateData)) == 0; }
	bool operator!=(const FUpdateStateData& other) const { return !(*this == other); }
	bool operator<(const FUpdateStateData& other) const { return memcmp(this, &other, sizeof(FUpdateStateData)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.BoostPickupEvent
// 0x004C
struct FBoostPickupEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FPlayerDataPacket                           Player;                                        // 0x0010 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FVector                                     Location;                                      // 0x0028 (0x000C) [0x0001000000000000]               
	float                                              BoostAmount;                                   // 0x0034 (0x0004) [0x0001000000000000]               
	class FString                                      BoostType;                                     // 0x0038 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bReplay : 1;                                   // 0x0048 (0x0004) [0x0001000000000000] [0x00000001] 

	bool operator==(const FBoostPickupEvent& other) const { return memcmp(this, &other, sizeof(FBoostPickupEvent)) == 0; }
	bool operator!=(const FBoostPickupEvent& other) const { return !(*this == other); }
	bool operator<(const FBoostPickupEvent& other) const { return memcmp(this, &other, sizeof(FBoostPickupEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.ReplayStartedEvent
// 0x0020
struct FReplayStartedEvent
{
	class FString                                      Filename;                                      // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Date;                                          // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FReplayStartedEvent& other) const { return memcmp(this, &other, sizeof(FReplayStartedEvent)) == 0; }
	bool operator!=(const FReplayStartedEvent& other) const { return !(*this == other); }
	bool operator<(const FReplayStartedEvent& other) const { return memcmp(this, &other, sizeof(FReplayStartedEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.PlayerChangeEvent
// 0x0030
struct FPlayerChangeEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      PlayerName;                                    // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      PrimaryID;                                     // 0x0020 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerChangeEvent& other) const { return memcmp(this, &other, sizeof(FPlayerChangeEvent)) == 0; }
	bool operator!=(const FPlayerChangeEvent& other) const { return !(*this == other); }
	bool operator<(const FPlayerChangeEvent& other) const { return memcmp(this, &other, sizeof(FPlayerChangeEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.ClockUpdatedEvent
// 0x0018
struct FClockUpdatedEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            TimeSeconds;                                   // 0x0010 (0x0004) [0x0001000000000000]               
	uint32_t                                           bOverTime : 1;                                 // 0x0014 (0x0004) [0x0001000000000000] [0x00000001] 

	bool operator==(const FClockUpdatedEvent& other) const { return memcmp(this, &other, sizeof(FClockUpdatedEvent)) == 0; }
	bool operator!=(const FClockUpdatedEvent& other) const { return !(*this == other); }
	bool operator<(const FClockUpdatedEvent& other) const { return memcmp(this, &other, sizeof(FClockUpdatedEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.BallLastTouchData
// 0x001C
struct FBallLastTouchData
{
	struct FPlayerDataPacket                           Player;                                        // 0x0000 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)
	float                                              Speed;                                         // 0x0018 (0x0004) [0x0001000000000000]               

	bool operator==(const FBallLastTouchData& other) const { return memcmp(this, &other, sizeof(FBallLastTouchData)) == 0; }
	bool operator!=(const FBallLastTouchData& other) const { return !(*this == other); }
	bool operator<(const FBallLastTouchData& other) const { return memcmp(this, &other, sizeof(FBallLastTouchData)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.GoalScoreDataEvent
// 0x0078
struct FGoalScoreDataEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	float                                              GoalSpeed;                                     // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            GoalTime;                                      // 0x0014 (0x0004) [0x0001000000000000]               
	struct FVector                                     ImpactLocation;                                // 0x0018 (0x000C) [0x0001000000000000]               
	struct FPlayerDataPacket                           Scorer;                                        // 0x0028 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FPlayerDataPacket                           Assister;                                      // 0x0040 (0x0018) [0x0021000000400000] (CPF_NeedCtorLink)
	struct FBallLastTouchData                          BallLastTouch;                                 // 0x0058 (0x0020) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FGoalScoreDataEvent& other) const { return memcmp(this, &other, sizeof(FGoalScoreDataEvent)) == 0; }
	bool operator!=(const FGoalScoreDataEvent& other) const { return !(*this == other); }
	bool operator<(const FGoalScoreDataEvent& other) const { return memcmp(this, &other, sizeof(FGoalScoreDataEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.StatTickerEvent
// 0x0060
struct FStatTickerEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      EventName;                                     // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Type;                                          // 0x0020 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FPlayerDataPacket                           MainTarget;                                    // 0x0030 (0x0018) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FPlayerDataPacket                           SecondaryTarget;                               // 0x0048 (0x0018) [0x0021000000400000] (CPF_NeedCtorLink)

	bool operator==(const FStatTickerEvent& other) const { return memcmp(this, &other, sizeof(FStatTickerEvent)) == 0; }
	bool operator!=(const FStatTickerEvent& other) const { return !(*this == other); }
	bool operator<(const FStatTickerEvent& other) const { return memcmp(this, &other, sizeof(FStatTickerEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.MatchWinnerEvent
// 0x0014
struct FMatchWinnerEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            WinnerTeamNum;                                 // 0x0010 (0x0004) [0x0001000000000000]               

	bool operator==(const FMatchWinnerEvent& other) const { return memcmp(this, &other, sizeof(FMatchWinnerEvent)) == 0; }
	bool operator!=(const FMatchWinnerEvent& other) const { return !(*this == other); }
	bool operator<(const FMatchWinnerEvent& other) const { return memcmp(this, &other, sizeof(FMatchWinnerEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.MatchGUIDEvent
// 0x0010
struct FMatchGUIDEvent
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMatchGUIDEvent& other) const { return memcmp(this, &other, sizeof(FMatchGUIDEvent)) == 0; }
	bool operator!=(const FMatchGUIDEvent& other) const { return !(*this == other); }
	bool operator<(const FMatchGUIDEvent& other) const { return memcmp(this, &other, sizeof(FMatchGUIDEvent)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.BallPreHitData
// 0x0014
struct FBallPreHitData
{
	float                                              PreHitSpeed;                                   // 0x0000 (0x0004) [0x0001000000000000]               
	float                                              PostHitSpeed;                                  // 0x0004 (0x0004) [0x0001000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0001000000000000]               

	bool operator==(const FBallPreHitData& other) const { return memcmp(this, &other, sizeof(FBallPreHitData)) == 0; }
	bool operator!=(const FBallPreHitData& other) const { return !(*this == other); }
	bool operator<(const FBallPreHitData& other) const { return memcmp(this, &other, sizeof(FBallPreHitData)) < 0; }
};

// ScriptStruct TAGame._StatsAPITypes_TA.CrossbarHitData
// 0x0048
struct FCrossbarHitData
{
	class FString                                      MatchGUID;                                     // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	struct FVector                                     BallLocation;                                  // 0x0010 (0x000C) [0x0001000000000000]               
	float                                              BallSpeed;                                     // 0x001C (0x0004) [0x0001000000000000]               
	float                                              ImpactForce;                                   // 0x0020 (0x0004) [0x0001000000000000]               
	struct FBallLastTouchData                          BallLastTouch;                                 // 0x0028 (0x0020) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCrossbarHitData& other) const { return memcmp(this, &other, sizeof(FCrossbarHitData)) == 0; }
	bool operator!=(const FCrossbarHitData& other) const { return !(*this == other); }
	bool operator<(const FCrossbarHitData& other) const { return memcmp(this, &other, sizeof(FCrossbarHitData)) < 0; }
};

// ScriptStruct TAGame.AntiCheatMessenger_TA.AntiCheatMessage
// 0x0018
struct FAntiCheatMessage
{
	int32_t                                            MessageId;                                     // 0x0000 (0x0004) [0x0001000000000000]               
	class TArray<class FString>                        MessageParts;                                  // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAntiCheatMessage& other) const { return memcmp(this, &other, sizeof(FAntiCheatMessage)) == 0; }
	bool operator!=(const FAntiCheatMessage& other) const { return !(*this == other); }
	bool operator<(const FAntiCheatMessage& other) const { return memcmp(this, &other, sizeof(FAntiCheatMessage)) < 0; }
};

// ScriptStruct TAGame.SettingsSnapshotManager_TA.ProductData
// 0x0020
struct FProductData
{
	struct FProductInstanceID                          InstanceID;                                    // 0x0000 (0x0010) [0x0001000000000000]               
	int32_t                                            ProductID;                                     // 0x0010 (0x0004) [0x0001000000000000]               
	int32_t                                            PaintID;                                       // 0x0014 (0x0004) [0x0001000000000000]               
	int32_t                                            SpecialEditionID;                              // 0x0018 (0x0004) [0x0001000000000000]               
	int32_t                                            TeamEditionId;                                 // 0x001C (0x0004) [0x0001000000000000]               

	bool operator==(const FProductData& other) const { return memcmp(this, &other, sizeof(FProductData)) == 0; }
	bool operator!=(const FProductData& other) const { return !(*this == other); }
	bool operator<(const FProductData& other) const { return memcmp(this, &other, sizeof(FProductData)) < 0; }
};

// ScriptStruct TAGame.SettingsSnapshotManager_TA.JsonMetadata
// 0x0070
struct FJsonMetadata
{
	struct FUniqueNetId                                UserId;                                        // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      platformKey;                                   // 0x0048 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            SchemaVersion;                                 // 0x0058 (0x0004) [0x0001000000000000]               
	int32_t                                            clientVersion;                                 // 0x005C (0x0004) [0x0001000000000000]               
	uint64_t                                           timestampUtc;                                  // 0x0060 (0x0008) [0x0001000000000000]               
	int32_t                                            settingsVersion;                               // 0x0068 (0x0004) [0x0001000000000000]               
	int32_t                                            Checksum;                                      // 0x006C (0x0004) [0x0001000000000000]               

	bool operator==(const FJsonMetadata& other) const { return memcmp(this, &other, sizeof(FJsonMetadata)) == 0; }
	bool operator!=(const FJsonMetadata& other) const { return !(*this == other); }
	bool operator<(const FJsonMetadata& other) const { return memcmp(this, &other, sizeof(FJsonMetadata)) < 0; }
};

// ScriptStruct TAGame.CustomScoreboardConfig_TA.ScoreboardGameModeDef
// 0x0010
struct FScoreboardGameModeDef
{
	class FName                                        ModeID;                                        // 0x0000 (0x0008) [0x0001000000000000]               
	class UClass*                                      GameInfoClass;                                 // 0x0008 (0x0008) [0x0001000000000000]               

	bool operator==(const FScoreboardGameModeDef& other) const { return memcmp(this, &other, sizeof(FScoreboardGameModeDef)) == 0; }
	bool operator!=(const FScoreboardGameModeDef& other) const { return !(*this == other); }
	bool operator<(const FScoreboardGameModeDef& other) const { return memcmp(this, &other, sizeof(FScoreboardGameModeDef)) < 0; }
};

// ScriptStruct TAGame.CustomScoreboardConfig_TA.ScoreboardStatRestriction
// 0x0018
struct FScoreboardStatRestriction
{
	ECustomScoreboardStat                              Stat;                                          // 0x0000 (0x0001) [0x0001000000000000]               
	class TArray<class FName>                          ModeIDs;                                       // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FScoreboardStatRestriction& other) const { return memcmp(this, &other, sizeof(FScoreboardStatRestriction)) == 0; }
	bool operator!=(const FScoreboardStatRestriction& other) const { return !(*this == other); }
	bool operator<(const FScoreboardStatRestriction& other) const { return memcmp(this, &other, sizeof(FScoreboardStatRestriction)) < 0; }
};

// ScriptStruct TAGame.DemoSpawnSelectMetrics_TA.DemoSpawnEvent
// 0x0058
struct FDemoSpawnEvent
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0001000000400000] (CPF_NeedCtorLink)
	EDemoSpawnPreference                               Preference;                                    // 0x0048 (0x0001) [0x0001000000000000]               
	int32_t                                            TeamNum;                                       // 0x004C (0x0004) [0x0001000000000000]               
	float                                              SecondsRemaining;                              // 0x0050 (0x0004) [0x0001000000000000]               
	uint32_t                                           bOverTime : 1;                                 // 0x0054 (0x0004) [0x0001000000000000] [0x00000001] 

	bool operator==(const FDemoSpawnEvent& other) const { return memcmp(this, &other, sizeof(FDemoSpawnEvent)) == 0; }
	bool operator!=(const FDemoSpawnEvent& other) const { return !(*this == other); }
	bool operator<(const FDemoSpawnEvent& other) const { return memcmp(this, &other, sizeof(FDemoSpawnEvent)) < 0; }
};

// ScriptStruct TAGame.GFxData_CustomScoreboardMenu_TA.GFxScoreboardStatOption
// 0x0030
struct FGFxScoreboardStatOption
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0001000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Label;                                         // 0x0010 (0x0010) [0x0001000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      RestrictModes;                                 // 0x0020 (0x0010) [0x0001000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FGFxScoreboardStatOption& other) const { return memcmp(this, &other, sizeof(FGFxScoreboardStatOption)) == 0; }
	bool operator!=(const FGFxScoreboardStatOption& other) const { return !(*this == other); }
	bool operator<(const FGFxScoreboardStatOption& other) const { return memcmp(this, &other, sizeof(FGFxScoreboardStatOption)) < 0; }
};

// ScriptStruct TAGame.GFxData_CustomScoreboardMenu_TA.GFxScoreboardGameMode
// 0x0014
struct FGFxScoreboardGameMode
{
	class FString                                      Title;                                         // 0x0000 (0x0010) [0x0001000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	int32_t                                            ModeIndex;                                     // 0x0010 (0x0004) [0x0001000040000000] (CPF_DataBinding)

	bool operator==(const FGFxScoreboardGameMode& other) const { return memcmp(this, &other, sizeof(FGFxScoreboardGameMode)) == 0; }
	bool operator!=(const FGFxScoreboardGameMode& other) const { return !(*this == other); }
	bool operator<(const FGFxScoreboardGameMode& other) const { return memcmp(this, &other, sizeof(FGFxScoreboardGameMode)) < 0; }
};

// ScriptStruct TAGame.ProfileScoreboardSave_TA.ScoreboardModePreference
// 0x0018
struct FScoreboardModePreference
{
	class FName                                        ModeID;                                        // 0x0000 (0x0008) [0x0001000000000000]               
	class TArray<ECustomScoreboardStat>                Stats;                                         // 0x0008 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)

	bool operator==(const FScoreboardModePreference& other) const { return memcmp(this, &other, sizeof(FScoreboardModePreference)) == 0; }
	bool operator!=(const FScoreboardModePreference& other) const { return !(*this == other); }
	bool operator<(const FScoreboardModePreference& other) const { return memcmp(this, &other, sizeof(FScoreboardModePreference)) < 0; }
};

// ScriptStruct TAGame.SpecialEvent_TA.SpecialEventStoreConfigs
// 0x0040
struct FSpecialEventStoreConfigs
{
	int32_t                                            EventID;                                       // 0x0000 (0x0004) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	class FString                                      TabTitle;                                      // 0x0008 (0x0010) [0x0000000040400001] (CPF_Edit | CPF_NeedCtorLink | CPF_DataBinding)
	class UTexture*                                    TabIconTexture;                                // 0x0018 (0x0008) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	uint64_t                                           StartTime;                                     // 0x0020 (0x0008) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	uint64_t                                           EndTime;                                       // 0x0028 (0x0008) [0x0000000040000001] (CPF_Edit | CPF_DataBinding)
	class FString                                      TabIconImageURL;                               // 0x0030 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FSpecialEventStoreConfigs& other) const { return memcmp(this, &other, sizeof(FSpecialEventStoreConfigs)) == 0; }
	bool operator!=(const FSpecialEventStoreConfigs& other) const { return !(*this == other); }
	bool operator<(const FSpecialEventStoreConfigs& other) const { return memcmp(this, &other, sizeof(FSpecialEventStoreConfigs)) < 0; }
};

// ScriptStruct TAGame.RPC_NewsSendInteractionEvents_TA.NewsInteractionEvent
// 0x0024
struct FNewsInteractionEvent
{
	class FString                                      TrackingId;                                    // 0x0000 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	class FString                                      Type;                                          // 0x0010 (0x0010) [0x0001000000400000] (CPF_NeedCtorLink)
	int32_t                                            Count;                                         // 0x0020 (0x0004) [0x0001000000000000]               

	bool operator==(const FNewsInteractionEvent& other) const { return memcmp(this, &other, sizeof(FNewsInteractionEvent)) == 0; }
	bool operator!=(const FNewsInteractionEvent& other) const { return !(*this == other); }
	bool operator<(const FNewsInteractionEvent& other) const { return memcmp(this, &other, sizeof(FNewsInteractionEvent)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
