/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: OnlineSubsystemSteamworks\OnlineSubsystemSteamworks_structs.hpp
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

// ScriptStruct OnlineSubsystemSteamworks.OnlineCommunityContentInterfaceSteamworks.WorkshopItemData
// 0x00A0
struct FWorkshopItemData
{
	class FString                                      Title;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      MetaData;                                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Content;                                       // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Preview;                                       // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Tags;                                          // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AddPairs;                                      // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      RemovePairs;                                   // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Visibility;                                    // 0x0080 (0x0004) [0x0000000000000000]               
	uint64_t                                           ItemID;                                        // 0x0088 (0x0008) [0x0000000000000000]               
	uint32_t                                           bIsUploading : 1;                              // 0x0090 (0x0004) [0x0000000000000000] [0x00000001] 
	uint64_t                                           UpdateHandle;                                  // 0x0098 (0x0008) [0x0000000000000000]               

	bool operator==(const FWorkshopItemData& other) const { return memcmp(this, &other, sizeof(FWorkshopItemData)) == 0; }
	bool operator!=(const FWorkshopItemData& other) const { return !(*this == other); }
	bool operator<(const FWorkshopItemData& other) const { return memcmp(this, &other, sizeof(FWorkshopItemData)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.ServerQueryToPingResponseMapping
// 0x0010
struct FServerQueryToPingResponseMapping
{
	int32_t                                            Query;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	struct FPointer                                    Response;                                      // 0x0008 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FServerQueryToPingResponseMapping& other) const { return memcmp(this, &other, sizeof(FServerQueryToPingResponseMapping)) == 0; }
	bool operator!=(const FServerQueryToPingResponseMapping& other) const { return !(*this == other); }
	bool operator<(const FServerQueryToPingResponseMapping& other) const { return memcmp(this, &other, sizeof(FServerQueryToPingResponseMapping)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.FilterKeyToSteamKeyMapping
// 0x0040
struct FFilterKeyToSteamKeyMapping
{
	int32_t                                            KeyId;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	EOnlineGameSearchEntryType                         KeyType;                                       // 0x0004 (0x0001) [0x0000000000000000]               
	class FString                                      RawKey;                                        // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SteamKey;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bReverseFilter : 1;                            // 0x0028 (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      IgnoreValue;                                   // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFilterKeyToSteamKeyMapping& other) const { return memcmp(this, &other, sizeof(FFilterKeyToSteamKeyMapping)) == 0; }
	bool operator!=(const FFilterKeyToSteamKeyMapping& other) const { return !(*this == other); }
	bool operator<(const FFilterKeyToSteamKeyMapping& other) const { return memcmp(this, &other, sizeof(FFilterKeyToSteamKeyMapping)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.ClientFilterORClause
// 0x0050
struct FClientFilterORClause
{
	struct FMultiMap_Mirror                            OrParams;                                      // 0x0000 (0x0050) [0x0000000000003000] (CPF_Native | CPF_Transient)

	bool operator==(const FClientFilterORClause& other) const { return memcmp(this, &other, sizeof(FClientFilterORClause)) == 0; }
	bool operator!=(const FClientFilterORClause& other) const { return !(*this == other); }
	bool operator<(const FClientFilterORClause& other) const { return memcmp(this, &other, sizeof(FClientFilterORClause)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.ServerQueryToRulesResponseMapping
// 0x0010
struct FServerQueryToRulesResponseMapping
{
	int32_t                                            Query;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	struct FPointer                                    Response;                                      // 0x0008 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FServerQueryToRulesResponseMapping& other) const { return memcmp(this, &other, sizeof(FServerQueryToRulesResponseMapping)) == 0; }
	bool operator!=(const FServerQueryToRulesResponseMapping& other) const { return !(*this == other); }
	bool operator<(const FServerQueryToRulesResponseMapping& other) const { return memcmp(this, &other, sizeof(FServerQueryToRulesResponseMapping)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.MatchmakingQueryState
// 0x0078
struct FMatchmakingQueryState
{
	class UOnlineGameSearch*                           GameSearch;                                    // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FServerQueryToRulesResponseMapping> QueryToRulesResponseMap;                       // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FServerQueryToPingResponseMapping> QueryToPingResponseMap;                        // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FPointer                                    ServerListResponse;                            // 0x0028 (0x0008) [0x0000000000001000] (CPF_Native)  
	ESteamMatchmakingType                              CurrentMatchmakingType;                        // 0x0030 (0x0001) [0x0000000000000000]               
	struct FPointer                                    CurrentMatchmakingQuery;                       // 0x0038 (0x0008) [0x0000000000001000] (CPF_Native)  
	class TArray<struct FClientFilterORClause>         ActiveClientsideFilters;                       // 0x0040 (0x0010) [0x0000000000003000] (CPF_Native | CPF_Transient)
	class TArray<class UOnlineGameSettings*>           PendingRulesSearchSettings;                    // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UOnlineGameSettings*>           PendingPingSearchSettings;                     // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIgnoreRefreshComplete : 1;                    // 0x0070 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              LastActivityTimestamp;                         // 0x0074 (0x0004) [0x0000000000000000]               

	bool operator==(const FMatchmakingQueryState& other) const { return memcmp(this, &other, sizeof(FMatchmakingQueryState)) == 0; }
	bool operator!=(const FMatchmakingQueryState& other) const { return !(*this == other); }
	bool operator<(const FMatchmakingQueryState& other) const { return memcmp(this, &other, sizeof(FMatchmakingQueryState)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlinePurchaseInterfaceSteamworks.AppPriceInfoRequest
// 0x0030
struct FAppPriceInfoRequest
{
	class UHttpRequestInterface*                       HTTPRequest;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<class FName>                          AppNames;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             Callback;                                      // 0x0018 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAppPriceInfoRequest& other) const { return memcmp(this, &other, sizeof(FAppPriceInfoRequest)) == 0; }
	bool operator!=(const FAppPriceInfoRequest& other) const { return !(*this == other); }
	bool operator<(const FAppPriceInfoRequest& other) const { return memcmp(this, &other, sizeof(FAppPriceInfoRequest)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.LeaderboardHandle
// 0x0008
struct FLeaderboardHandle
{
	uint64_t                                           Dud;                                           // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FLeaderboardHandle& other) const { return memcmp(this, &other, sizeof(FLeaderboardHandle)) == 0; }
	bool operator!=(const FLeaderboardHandle& other) const { return !(*this == other); }
	bool operator<(const FLeaderboardHandle& other) const { return memcmp(this, &other, sizeof(FLeaderboardHandle)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.LeaderboardTemplate
// 0x002C
struct FLeaderboardTemplate
{
	class FString                                      LeaderboardName;                               // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	ELeaderboardUpdateType                             UpdateType;                                    // 0x0010 (0x0001) [0x0000000000000000]               
	int32_t                                            LeaderboardSize;                               // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	ELeaderboardSortType                               SortType;                                      // 0x0018 (0x0001) [0x0000000000000002] (CPF_Const)   
	ELeaderboardFormat                                 DisplayFormat;                                 // 0x0019 (0x0001) [0x0000000000000002] (CPF_Const)   
	struct FLeaderboardHandle                          LeaderboardRef;                                // 0x0020 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bLeaderboardInitializing : 1;                  // 0x0028 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bLeaderboardInitiated : 1;                     // 0x0028 (0x0004) [0x0000000000000002] [0x100000002] (CPF_Const)

	bool operator==(const FLeaderboardTemplate& other) const { return memcmp(this, &other, sizeof(FLeaderboardTemplate)) == 0; }
	bool operator!=(const FLeaderboardTemplate& other) const { return !(*this == other); }
	bool operator<(const FLeaderboardTemplate& other) const { return memcmp(this, &other, sizeof(FLeaderboardTemplate)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.DeferredLeaderboardRead
// 0x0030
struct FDeferredLeaderboardRead
{
	class FString                                      LeaderboardName;                               // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint8_t                                            RequestType;                                   // 0x0010 (0x0001) [0x0000000000000000]               
	int32_t                                            Start;                                         // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            End;                                           // 0x0018 (0x0004) [0x0000000000000000]               
	class TArray<struct FUniqueNetId>                  PlayerList;                                    // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDeferredLeaderboardRead& other) const { return memcmp(this, &other, sizeof(FDeferredLeaderboardRead)) == 0; }
	bool operator!=(const FDeferredLeaderboardRead& other) const { return !(*this == other); }
	bool operator<(const FDeferredLeaderboardRead& other) const { return memcmp(this, &other, sizeof(FDeferredLeaderboardRead)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.DeferredLeaderboardWrite
// 0x0028
struct FDeferredLeaderboardWrite
{
	class FString                                      LeaderboardName;                               // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Score;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              LeaderboardData;                               // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDeferredLeaderboardWrite& other) const { return memcmp(this, &other, sizeof(FDeferredLeaderboardWrite)) == 0; }
	bool operator!=(const FDeferredLeaderboardWrite& other) const { return !(*this == other); }
	bool operator<(const FDeferredLeaderboardWrite& other) const { return memcmp(this, &other, sizeof(FDeferredLeaderboardWrite)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.LeaderboardEntry
// 0x0060
struct FLeaderboardEntry
{
	struct FUniqueNetId                                PlayerUID;                                     // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Rank;                                          // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            Score;                                         // 0x004C (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              LeaderboardData;                               // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLeaderboardEntry& other) const { return memcmp(this, &other, sizeof(FLeaderboardEntry)) == 0; }
	bool operator!=(const FLeaderboardEntry& other) const { return !(*this == other); }
	bool operator<(const FLeaderboardEntry& other) const { return memcmp(this, &other, sizeof(FLeaderboardEntry)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ViewIdToLeaderboardName
// 0x0018
struct FViewIdToLeaderboardName
{
	int32_t                                            ViewId;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      LeaderboardName;                               // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FViewIdToLeaderboardName& other) const { return memcmp(this, &other, sizeof(FViewIdToLeaderboardName)) == 0; }
	bool operator!=(const FViewIdToLeaderboardName& other) const { return !(*this == other); }
	bool operator<(const FViewIdToLeaderboardName& other) const { return memcmp(this, &other, sizeof(FViewIdToLeaderboardName)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.SteamPlayerClanData
// 0x0020
struct FSteamPlayerClanData
{
	class FString                                      ClanName;                                      // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ClanTag;                                       // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FSteamPlayerClanData& other) const { return memcmp(this, &other, sizeof(FSteamPlayerClanData)) == 0; }
	bool operator!=(const FSteamPlayerClanData& other) const { return !(*this == other); }
	bool operator<(const FSteamPlayerClanData& other) const { return memcmp(this, &other, sizeof(FSteamPlayerClanData)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ProfileSettingsCache
// 0x0038
struct FProfileSettingsCache
{
	class UOnlineProfileSettings*                      Profile;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<struct FScriptDelegate>               ReadDelegates;                                 // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               WriteDelegates;                                // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ProfileDataChangedDelegates;                   // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FProfileSettingsCache& other) const { return memcmp(this, &other, sizeof(FProfileSettingsCache)) == 0; }
	bool operator!=(const FProfileSettingsCache& other) const { return !(*this == other); }
	bool operator<(const FProfileSettingsCache& other) const { return memcmp(this, &other, sizeof(FProfileSettingsCache)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.LocalTalkerSteam
// 0x0005 (0x004C - 0x0051)
struct FLocalTalkerSteam : FLocalTalker
{
	EMuteType                                          MuteType;                                      // 0x0050 (0x0001) [0x0000000000000000]               

	bool operator==(const FLocalTalkerSteam& other) const { return memcmp(this, &other, sizeof(FLocalTalkerSteam)) == 0; }
	bool operator!=(const FLocalTalkerSteam& other) const { return !(*this == other); }
	bool operator<(const FLocalTalkerSteam& other) const { return memcmp(this, &other, sizeof(FLocalTalkerSteam)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.AchievementProgressStat
// 0x0010
struct FAchievementProgressStat
{
	int32_t                                            AchievementId;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Progress;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxProgress;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bUnlock : 1;                                   // 0x000C (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FAchievementProgressStat& other) const { return memcmp(this, &other, sizeof(FAchievementProgressStat)) == 0; }
	bool operator!=(const FAchievementProgressStat& other) const { return !(*this == other); }
	bool operator<(const FAchievementProgressStat& other) const { return memcmp(this, &other, sizeof(FAchievementProgressStat)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.AchievementMappingInfo
// 0x001C
struct FAchievementMappingInfo
{
	int32_t                                            AchievementId;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        AchievementName;                               // 0x0004 (0x0008) [0x0000000000000000]               
	int32_t                                            ViewId;                                        // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            ProgressCount;                                 // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxProgress;                                   // 0x0014 (0x0004) [0x0000000000000000]               
	uint32_t                                           bAutoUnlock : 1;                               // 0x0018 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FAchievementMappingInfo& other) const { return memcmp(this, &other, sizeof(FAchievementMappingInfo)) == 0; }
	bool operator!=(const FAchievementMappingInfo& other) const { return !(*this == other); }
	bool operator<(const FAchievementMappingInfo& other) const { return memcmp(this, &other, sizeof(FAchievementMappingInfo)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.QueuedAvatarRequest
// 0x0070
struct FQueuedAvatarRequest
{
	float                                              CheckTime;                                     // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            NumberOfAttempts;                              // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   
	struct FUniqueNetId                                PlayerNetId;                                   // 0x0008 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            Size;                                          // 0x0050 (0x0004) [0x0000000000000002] (CPF_Const)   
	struct FScriptDelegate                             ReadOnlineAvatarCompleteDelegate;              // 0x0058 (0x0018) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FQueuedAvatarRequest& other) const { return memcmp(this, &other, sizeof(FQueuedAvatarRequest)) == 0; }
	bool operator!=(const FQueuedAvatarRequest& other) const { return !(*this == other); }
	bool operator<(const FQueuedAvatarRequest& other) const { return memcmp(this, &other, sizeof(FQueuedAvatarRequest)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.SteamUserCloudMetadata
// 0x0020
struct FSteamUserCloudMetadata
{
	class FString                                      UserId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FEmsFile>                      UserCloudMetadata;                             // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSteamUserCloudMetadata& other) const { return memcmp(this, &other, sizeof(FSteamUserCloudMetadata)) == 0; }
	bool operator!=(const FSteamUserCloudMetadata& other) const { return !(*this == other); }
	bool operator<(const FSteamUserCloudMetadata& other) const { return memcmp(this, &other, sizeof(FSteamUserCloudMetadata)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.SteamUserCloud
// 0x0020
struct FSteamUserCloud
{
	class FString                                      UserId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTitleFile>                    UserCloudFileData;                             // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSteamUserCloud& other) const { return memcmp(this, &other, sizeof(FSteamUserCloud)) == 0; }
	bool operator!=(const FSteamUserCloud& other) const { return !(*this == other); }
	bool operator<(const FSteamUserCloud& other) const { return memcmp(this, &other, sizeof(FSteamUserCloud)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ControllerConnectionState
// 0x0008
struct FControllerConnectionState
{
	int32_t                                            bIsControllerConnected;                        // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            bLastIsControllerConnected;                    // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FControllerConnectionState& other) const { return memcmp(this, &other, sizeof(FControllerConnectionState)) == 0; }
	bool operator!=(const FControllerConnectionState& other) const { return !(*this == other); }
	bool operator<(const FControllerConnectionState& other) const { return memcmp(this, &other, sizeof(FControllerConnectionState)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.OnlineStatusMapping
// 0x0018
struct FOnlineStatusMapping
{
	int32_t                                            StatusId;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      StatusString;                                  // 0x0008 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FOnlineStatusMapping& other) const { return memcmp(this, &other, sizeof(FOnlineStatusMapping)) == 0; }
	bool operator!=(const FOnlineStatusMapping& other) const { return !(*this == other); }
	bool operator<(const FOnlineStatusMapping& other) const { return memcmp(this, &other, sizeof(FOnlineStatusMapping)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.DeviceIdCache
// 0x0030
struct FDeviceIdCache
{
	int32_t                                            DeviceID;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             DeviceSelectionMulticast;                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               DeviceSelectionDelegates;                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDeviceIdCache& other) const { return memcmp(this, &other, sizeof(FDeviceIdCache)) == 0; }
	bool operator!=(const FDeviceIdCache& other) const { return !(*this == other); }
	bool operator<(const FDeviceIdCache& other) const { return memcmp(this, &other, sizeof(FDeviceIdCache)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.PlayerStat
// 0x0018
struct FPlayerStat
{
	int32_t                                            ViewId;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ColumnId;                                      // 0x0004 (0x0004) [0x0000000000000000]               
	struct FSettingsData                               Data;                                          // 0x0008 (0x0010) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FPlayerStat& other) const { return memcmp(this, &other, sizeof(FPlayerStat)) == 0; }
	bool operator!=(const FPlayerStat& other) const { return !(*this == other); }
	bool operator<(const FPlayerStat& other) const { return memcmp(this, &other, sizeof(FPlayerStat)) < 0; }
};

// ScriptStruct OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.PendingPlayerStats
// 0x00D8
struct FPendingPlayerStats
{
	struct FUniqueNetId                                Player;                                        // 0x0000 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      PlayerName;                                    // 0x0048 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      StatGuid;                                      // 0x0058 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FPlayerStat>                   Stats;                                         // 0x0068 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FOnlinePlayerScore                          Score;                                         // 0x0078 (0x0050) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      Place;                                         // 0x00C8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FPendingPlayerStats& other) const { return memcmp(this, &other, sizeof(FPendingPlayerStats)) == 0; }
	bool operator!=(const FPendingPlayerStats& other) const { return !(*this == other); }
	bool operator<(const FPendingPlayerStats& other) const { return memcmp(this, &other, sizeof(FPendingPlayerStats)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
