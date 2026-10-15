/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: OnlineSubsystemSteamworks\OnlineSubsystemSteamworks_classes.hpp
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
# Classes
# ========================================================================================= #
*/

// Class OnlineSubsystemSteamworks.OnlineAuthInterfaceSteamworks
// 0x0018 (0x03C8 - 0x03E0)
class UOnlineAuthInterfaceSteamworks : public UOnlineAuthInterfaceImpl
{
public:
	class TArray<uint8_t>                              EncryptedTicket;                               // 0x03C8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint64_t                                           EncryptedTicketHandle;                         // 0x03D8 (0x0008) [0x0000000000000002] (CPF_Const)   

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineAuthInterfaceSteamworks");
		}

		return uClassPointer;
	};

	bool RequestAuthTicket(const struct FUniqueNetId& PlayerID, const struct FScriptDelegate& Callback);
	bool RequiresAuthTicket();
	bool GetServerAddr(struct FIpAddr& outOutServerIP, int32_t& outOutServerPort);
	bool GetServerUniqueId(struct FUniqueNetId& outOutServerUID);
	bool VerifyServerAuthSession(const struct FUniqueNetId& ServerUID, const struct FIpAddr& ServerIP, int32_t AuthTicketUID);
	bool CreateServerAuthSession(const struct FUniqueNetId& ClientUID, const struct FIpAddr& ClientIP, int32_t ClientPort, int32_t& outOutAuthTicketUID);
	bool VerifyClientAuthSession(const struct FUniqueNetId& ClientUID, const struct FIpAddr& ClientIP, int32_t ClientPort, int32_t AuthTicketUID);
	bool CreateClientAuthSession(const struct FUniqueNetId& ServerUID, const struct FIpAddr& ServerIP, int32_t ServerPort, bool bSecure, int32_t& outOutAuthTicketUID);
	bool SendServerAuthRequest(const struct FUniqueNetId& ServerUID);
	bool SendClientAuthRequest(class UPlayer* ClientConnection, const struct FUniqueNetId& ClientUID);
};

// Class OnlineSubsystemSteamworks.OnlineCommunityContentInterfaceSteamworks
// 0x0138 (0x0060 - 0x0198)
class UOnlineCommunityContentInterfaceSteamworks : public UObject
{
public:
	class UOnlineSubsystemSteamworks*                  OwningSubsystem;                               // 0x0060 (0x0008) [0x0000000000000000]               
	struct FWorkshopItemData                           WorkshopItem;                                  // 0x0068 (0x00A0) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnDownloadedWorkshopData__Delegate;          // 0x0108 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadContentListComplete__Delegate;         // 0x0120 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadFriendsContentListComplete__Delegate;  // 0x0138 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUploadContentComplete__Delegate;           // 0x0150 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnDownloadContentComplete__Delegate;         // 0x0168 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnGetContentPayloadComplete__Delegate;       // 0x0180 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineCommunityContentInterfaceSteamworks");
		}

		return uClassPointer;
	};

	void UpdateWorkshopItemUploadProgress();
	void DownloadAllWorkshopData(const struct FScriptDelegate& Callback);
	void CreateWorkshopItem();
	void RateContent(uint8_t PlayerNum, int32_t NewRating, struct FCommunityContentFile& outFileToRate);
	void ClearGetContentPayloadCompleteDelegate(const struct FScriptDelegate& GetContentPayloadCompleteDelegate);
	void AddGetContentPayloadCompleteDelegate(const struct FScriptDelegate& GetContentPayloadCompleteDelegate);
	void OnGetContentPayloadComplete(bool bWasSuccessful, const struct FCommunityContentFile& FileDownloaded, class TArray<uint8_t>& outPayload);
	bool GetContentPayload(uint8_t PlayerNum, struct FCommunityContentFile& outFileDownloaded);
	void ClearDownloadContentCompleteDelegate(const struct FScriptDelegate& DownloadContentCompleteDelegate);
	void AddDownloadContentCompleteDelegate(const struct FScriptDelegate& DownloadContentCompleteDelegate);
	void OnDownloadContentComplete(bool bWasSuccessful, const struct FCommunityContentFile& FileDownloaded, const class TArray<uint8_t>& Payload);
	bool DownloadContent(uint8_t PlayerNum, struct FCommunityContentFile& outFileToDownload);
	void ClearUploadContentCompleteDelegate(const struct FScriptDelegate& UploadContentCompleteDelegate);
	void AddUploadContentCompleteDelegate(const struct FScriptDelegate& UploadContentCompleteDelegate);
	void OnUploadContentComplete(bool bWasSuccessful, const struct FCommunityContentFile& UploadedFile);
	bool UploadContent(uint8_t PlayerNum, class TArray<uint8_t>& outPayload, struct FCommunityContentMetadata& outMetaData);
	bool GetFriendsContentList(uint8_t PlayerNum, struct FOnlineFriend& outFriend, class TArray<struct FCommunityContentFile>& outContentFiles);
	void ClearReadFriendsContentListCompleteDelegate(const struct FScriptDelegate& ReadFriendsContentListCompleteDelegate);
	void AddReadFriendsContentListCompleteDelegate(const struct FScriptDelegate& ReadFriendsContentListCompleteDelegate);
	void OnReadFriendsContentListComplete(bool bWasSuccessful);
	bool ReadFriendsContentList(uint8_t PlayerNum, int32_t optionalStartAt, int32_t optionalNumToRead, class TArray<struct FOnlineFriend>& outFriends);
	bool GetContentList(uint8_t PlayerNum, class TArray<struct FCommunityContentFile>& outContentFiles);
	void ClearReadContentListCompleteDelegate(const struct FScriptDelegate& ReadContentListCompleteDelegate);
	void AddReadContentListCompleteDelegate(const struct FScriptDelegate& ReadContentListCompleteDelegate);
	void OnReadContentListComplete(bool bWasSuccessful, const class TArray<struct FCommunityContentFile>& ContentFiles);
	bool ReadContentList(uint8_t PlayerNum, const struct FUniqueNetId& NetId, const class FString& optionalPath = {}, int32_t optionalStartAt = {}, int32_t optionalNumToRead = {});
	void Exit();
	bool Init();
	void OnDownloadedWorkshopData(bool bSuccess, class TArray<struct FDownloadedWorkshopData>& outItems);
};

// Class OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks
// 0x0190 (0x0318 - 0x04A8)
class UOnlineGameInterfaceSteamworks : public UOnlineGameInterfaceImpl
{
public:
	struct FMatchmakingQueryState                      ServerBrowserSearchQuery;                      // 0x0318 (0x0078) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FMatchmakingQueryState                      InviteSearchQuery;                             // 0x0390 (0x0078) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	float                                              ServerBrowserTimeout;                          // 0x0408 (0x0004) [0x0000000000000000]               
	float                                              InviteTimeout;                                 // 0x040C (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                InviteServerUID;                               // 0x0410 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class UOnlineGameSearch*                           InviteGameSearch;                              // 0x0458 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      InviteLocationUrl;                             // 0x0460 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               RegisterPlayerCompleteDelegates;               // 0x0470 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               UnregisterPlayerCompleteDelegates;             // 0x0480 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bFilterEngineBuild : 1;                        // 0x0490 (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<struct FFilterKeyToSteamKeyMapping>   FilterKeyToSteamKeyMap;                        // 0x0498 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks");
		}

		return uClassPointer;
	};

	void PrintDebugInfoNative(class UDebugDrawer* Drawer);
	void PrintDebugInfo(class UDebugDrawer* Drawer);
	bool QueryNonAdvertisedData(int32_t StartAt, int32_t NumberToQuery);
	void ClearUnregisterPlayerCompleteDelegate(const struct FScriptDelegate& UnregisterPlayerCompleteDelegate);
	void AddUnregisterPlayerCompleteDelegate(const struct FScriptDelegate& UnregisterPlayerCompleteDelegate);
	void OnUnregisterPlayerComplete(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasSuccessful);
	bool UnregisterPlayer(const class FName& SessionName, const struct FUniqueNetId& PlayerID);
	void ClearRegisterPlayerCompleteDelegate(const struct FScriptDelegate& RegisterPlayerCompleteDelegate);
	void AddRegisterPlayerCompleteDelegate(const struct FScriptDelegate& RegisterPlayerCompleteDelegate);
	void OnRegisterPlayerComplete(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasSuccessful);
	bool RegisterPlayer(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasInvited);
	bool AcceptGameInvite(uint8_t LocalUserNum, const class FName& SessionName);
	void OnGameInviteAccepted(const class FString& ErrorString, struct FOnlineGameSearchResult& outInviteResult);
	bool UpdateOnlineGame(const class FName& SessionName, class UOnlineGameSettings* UpdatedGameSettings, bool optionalBShouldRefreshOnlineData = {});
};

// Class OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks_PsyNet
// 0x0020 (0x0318 - 0x0338)
class UOnlineGameInterfaceSteamworks_PsyNet : public UOnlineGameInterfaceImpl
{
public:
	class TArray<struct FScriptDelegate>               RegisterPlayerCompleteDelegates;               // 0x0318 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               UnregisterPlayerCompleteDelegates;             // 0x0328 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks_PsyNet");
		}

		return uClassPointer;
	};

	void ClearUnregisterPlayerCompleteDelegate(const struct FScriptDelegate& UnregisterPlayerCompleteDelegate);
	void AddUnregisterPlayerCompleteDelegate(const struct FScriptDelegate& UnregisterPlayerCompleteDelegate);
	void OnUnregisterPlayerComplete(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasSuccessful);
	bool UnregisterPlayer(const class FName& SessionName, const struct FUniqueNetId& PlayerID);
	void ClearRegisterPlayerCompleteDelegate(const struct FScriptDelegate& RegisterPlayerCompleteDelegate);
	void AddRegisterPlayerCompleteDelegate(const struct FScriptDelegate& RegisterPlayerCompleteDelegate);
	void OnRegisterPlayerComplete(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasSuccessful);
	bool RegisterPlayer(const class FName& SessionName, const struct FUniqueNetId& PlayerID, bool bWasInvited);
	bool QueryNonAdvertisedData(int32_t StartAt, int32_t NumberToQuery);
	bool AcceptGameInvite(uint8_t LocalUserNum, const class FName& SessionName);
	bool UpdateOnlineGame(const class FName& SessionName, class UOnlineGameSettings* UpdatedGameSettings, bool optionalBShouldRefreshOnlineData = {});
	void SetFriendJoinLocation(const struct FUniqueNetId& JoinablePlayerID, const class FString& ServerAddress, ELobbyVisibility Visibility);
};

// Class OnlineSubsystemSteamworks.OnlineLobbyInterfaceSteamworks
// 0x0050 (0x02C0 - 0x0310)
class UOnlineLobbyInterfaceSteamworks : public UOnlineLobbyInterfaceImpl
{
public:
	class TArray<struct FLobbyMetaData>                CreateLobbySettings;                           // 0x02C0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueLobbyId                              PendingCreateLobbyResult;                      // 0x02D0 (0x0010) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bLobbySearchInProgress : 1;                    // 0x02E0 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	class TArray<class FString>                        LobbyMemberKeys;                               // 0x02E8 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLobbyKicked__Delegate;                     // 0x02F8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineLobbyInterfaceSteamworks");
		}

		return uClassPointer;
	};

	bool KickPlayer(ELobbyKickReason Reason, struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outPlayerID);
	bool GetLobbyFromCommandline(bool optionalBMarkAsJoined, struct FUniqueLobbyId& outLobbyId);
	bool ShowInviteUI(uint8_t LocalUserNum, struct FUniqueLobbyId& outLobbyId);
	bool InviteToLobby(struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outPlayerID);
	bool CanInviteToLobby(struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outPlayerID);
	bool SetLobbyOwner(struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outNewOwner);
	bool SetLobbyLock(bool bLocked, struct FUniqueLobbyId& outLobbyId);
	bool SetLobbyType(ELobbyVisibility Type, struct FUniqueLobbyId& outLobbyId);
	bool SetLobbyServer(const class FString& ServerIP, struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outServerUID);
	bool RemoveLobbySetting(const class FString& Key, struct FUniqueLobbyId& outLobbyId);
	bool SetLobbySetting(const class FString& Key, const class FString& Value, struct FUniqueLobbyId& outLobbyId);
	bool GetLobbyAdmin(struct FUniqueLobbyId& outLobbyId, struct FUniqueNetId& outAdminId);
	void OnLobbyKicked(int32_t AdminIndex, struct FActiveLobbyInfo& outLobby);
	bool SendLobbyBinaryData(struct FUniqueLobbyId& outLobbyId, class TArray<uint8_t>& outData);
	bool SetLobbyUserSetting(const class FString& Key, const class FString& Value, struct FUniqueLobbyId& outLobbyId);
	bool LeaveLobby(struct FUniqueLobbyId& outLobbyId);
	bool JoinLobby(int32_t LocalPlayerNum, struct FUniqueLobbyId& outLobbyId);
	bool UpdateFoundLobbies(const struct FUniqueLobbyId& optionalLobbyId);
	bool FindLobbies(int32_t optionalMaxResults = {}, const class TArray<struct FLobbyFilter>& optionalFilters = {}, const class TArray<struct FLobbySortFilter>& optionalSortFilters = {}, int32_t optionalMinSlots = {}, ELobbyDistance optionalDistance = {});
	bool CreateLobby(int32_t LocalPlayerNum, int32_t MaxPlayers, ELobbyVisibility optionalType = {}, const class TArray<struct FLobbyMetaData>& optionalInitialSettings = {});
};

// Class OnlineSubsystemSteamworks.OnlineSubsystemSteamworks
// 0x0C70 (0x03B0 - 0x1020)
class UOnlineSubsystemSteamworks : public UOnlineSubsystemCommonImpl
{
public:
	struct FPointer                                    Discord;                                       // 0x03B0 (0x0008) [0x0000000000001000] (CPF_Native)  
	class TArray<class FName>                          UnlockedDLC;                                   // 0x03B8 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               UnlockedDLCDelegates;                          // 0x03C8 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	uint32_t                                           bStoringAchievement : 1;                       // 0x03D8 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bClientStatsStorePending : 1;                  // 0x03D8 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bGSStatsStoresSuccess : 1;                     // 0x03D8 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bNeedsKeyboardTicking : 1;                     // 0x03D8 (0x0004) [0x0000000000000002] [0x00000008] (CPF_Const)
	uint32_t                                           bLastHasConnection : 1;                        // 0x03D8 (0x0004) [0x0000000000000002] [0x00000010] (CPF_Const)
	uint32_t                                           bIsStatsSessionOk : 1;                         // 0x03D8 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bHasSteamworksAccount : 1;                     // 0x03D8 (0x0004) [0x0000000000004002] [0x00000040] (CPF_Const | CPF_Config)
	uint32_t                                           bShouldUseMcp : 1;                             // 0x03D8 (0x0004) [0x0000000000004002] [0x00000080] (CPF_Const | CPF_Config)
	uint32_t                                           bShowIPCCount : 1;                             // 0x03D8 (0x0004) [0x0000000000004002] [0x00000100] (CPF_Const | CPF_Config)
	uint32_t                                           bInterceptFriendMessages : 1;                  // 0x03D8 (0x0004) [0x0000000000004000] [0x00000200] (CPF_Config)
	int32_t                                            TotalGSStatsStoresPending;                     // 0x03DC (0x0004) [0x0000000000000000]               
	EOnlineEnumerationReadState                        UserStatsReceivedState;                        // 0x03E0 (0x0001) [0x0000000000000000]               
	ELoginStatus                                       LoggedInStatus;                                // 0x03E1 (0x0001) [0x0000000000000002] (CPF_Const)   
	uint8_t                                            KeyboardInputWasCanceled;                      // 0x03E2 (0x0001) [0x0000000000000000]               
	uint8_t                                            bWasKeyboardInputCanceled;                     // 0x03E3 (0x0001) [0x0000000000000002] (CPF_Const)   
	ENetworkNotificationPosition                       CurrentNotificationPosition;                   // 0x03E4 (0x0001) [0x0000000000004000] (CPF_Config)  
	class UOnlineGameInterfaceSteamworks*              CachedGameInt;                                 // 0x03E8 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      LocalProfileName;                              // 0x03F0 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class FString                                      LoggedInPlayerName;                            // 0x0400 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FUniqueNetId                                LoggedInPlayerId;                              // 0x0410 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            LoggedInPlayerNum;                             // 0x0458 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      LoggedInCountry;                               // 0x0460 (0x0010) [0x0000004000402000] (CPF_Transient | CPF_NeedCtorLink | CPF_PrivateWrite)
	class TArray<int32_t>                              AvatarSizes;                                   // 0x0470 (0x0010) [0x0000000000400003] (CPF_Edit | CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               WriteProfileSettingsDelegates;                 // 0x0480 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UOnlineProfileSettings*                      CachedProfile;                                 // 0x0490 (0x0008) [0x0000000000000000]               
	class TArray<struct FScriptDelegate>               LocalPlayerStorageReadDelegates;               // 0x0498 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               LocalPlayerStorageWriteDelegates;              // 0x04A8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               RemotePlayerStorageReadDelegates;              // 0x04B8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               SpeechRecognitionCompleteDelegates;            // 0x04C8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ReadFriendsDelegates;                          // 0x04D8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               FriendsChangeDelegates;                        // 0x04E8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               MutingChangeDelegates;                         // 0x04F8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               LoginChangeDelegates;                          // 0x0508 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               LoginFailedDelegates;                          // 0x0518 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               TalkingDelegates;                              // 0x0528 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ReadOnlineStatsCompleteDelegates;              // 0x0538 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               FlushOnlineStatsDelegates;                     // 0x0548 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ConnectionStatusChangeDelegates;               // 0x0558 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               LinkStatusDelegates;                           // 0x0568 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ReadTitleFileCompleteDelegates;                // 0x0578 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               AchievementDelegates;                          // 0x0588 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               AchievementReadDelegates;                      // 0x0598 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               EnumerateUserFilesCompleteDelegates;           // 0x05A8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ReadUserFileCompleteDelegates;                 // 0x05B8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               WriteUserFileCompleteDelegates;                // 0x05C8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               DeleteUserFileCompleteDelegates;               // 0x05D8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               SharedFileReadCompleteDelegates;               // 0x05E8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               SharedFileWriteCompleteDelegates;              // 0x05F8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ExternalUIChangeDelegates;                     // 0x0608 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               KeyboardInputCompleteDelegates;                // 0x0618 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class FString                                      KeyboardInputResults;                          // 0x0628 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FLocalTalkerSteam                           CurrentLocalTalker;                            // 0x0638 (0x0058) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              LastLocalTalkerNotificationTime;               // 0x0690 (0x0004) [0x0000000000002002] (CPF_Const | CPF_Transient)
	float                                              MaxTalkerNotificationTime;                     // 0x0694 (0x0004) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FUniqueNetId>                  PendingRequestUserInformation;                 // 0x0698 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FRemoteTalker>                 RemoteTalkers;                                 // 0x06A8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            AppID;                                         // 0x06B8 (0x0004) [0x0000000000000002] (CPF_Const)   
	class UOnlineStatsRead*                            CurrentStatsRead;                              // 0x06C0 (0x0008) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FPendingPlayerStats>           PendingStats;                                  // 0x06C8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      KeyboardResultsString;                         // 0x06D8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               KeyboardInputDelegates;                        // 0x06E8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               FriendInviteReceivedDelegates;                 // 0x06F8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               FriendMessageReceivedDelegates;                // 0x0708 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               AddFriendByNameCompleteDelegates;              // 0x0718 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FProfileSettingsCache                       ProfileCache;                                  // 0x0728 (0x0038) [0x0000000000400000] (CPF_NeedCtorLink)
	class UOnlinePlayerStorage*                        PlayerStorageCache;                            // 0x0760 (0x0008) [0x0000000000000000]               
	class FString                                      CachedFriendMessage;                           // 0x0768 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FDeviceIdCache                              DeviceCache;                                   // 0x0778 (0x0030) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        LocationUrlsForInvites;                        // 0x07A8 (0x0010) [0x0000000000404002] (CPF_Const | CPF_Config | CPF_NeedCtorLink)
	class FString                                      LocationUrl;                                   // 0x07B8 (0x0010) [0x0000000000404002] (CPF_Const | CPF_Config | CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               ReceivedGameInviteDelegates;                   // 0x07C8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               JoinFriendGameCompleteDelegates;               // 0x07D8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               GetNumberOfCurrentPlayersCompleteDelegates;    // 0x07E8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptDelegate>               RegisterHostStatGuidCompleteDelegates;         // 0x07F8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineFriendMessage>          CachedFriendMessages;                          // 0x0808 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineStatusMapping>          StatusMappings;                                // 0x0818 (0x0010) [0x0000000000404002] (CPF_Const | CPF_Config | CPF_NeedCtorLink)
	class FString                                      DefaultStatus;                                 // 0x0828 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class FString                                      GameInviteMessage;                             // 0x0838 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	struct FControllerConnectionState                  ControllerStates[4];                           // 0x0848 (0x0020) [0x0000000000000000]               
	float                                              ConnectionPresenceTimeInterval;                // 0x0868 (0x0004) [0x0000000000000000]               
	float                                              ConnectionPresenceElapsedTime;                 // 0x086C (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      EncryptedProductKey;                           // 0x0870 (0x0010) [0x0000000000404002] (CPF_Const | CPF_Config | CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  MuteList;                                      // 0x0880 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FSteamUserCloud>               UserCloudFiles;                                // 0x0890 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FSteamUserCloudMetadata>       UserCloudMetadata;                             // 0x08A0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTitleFile>                    SharedFileCache;                               // 0x08B0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FQueuedAvatarRequest>          QueuedAvatarRequests;                          // 0x08C0 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FAchievementMappingInfo>       AchievementMappings;                           // 0x08D0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<struct FAchievementProgressStat>      PendingAchievementProgress;                    // 0x08E0 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FLeaderboardTemplate>          LeaderboardList;                               // 0x08F0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FDeferredLeaderboardRead>      DeferredLeaderboardReads;                      // 0x0900 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FDeferredLeaderboardWrite>     DeferredLeaderboardWrites;                     // 0x0910 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FDeferredLeaderboardWrite>     PendingLeaderboardStats;                       // 0x0920 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FViewIdToLeaderboardName>      LeaderboardNameMappings;                       // 0x0930 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<int32_t>                              GameServerStatsMappings;                       // 0x0940 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class UOnlinePurchaseInterfaceSteamworks*          CachedPurchaseInt;                             // 0x0950 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UOnlineAuthInterfaceSteamworks*              CachedAuthInt;                                 // 0x0958 (0x0008) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FIpAddr>                       PendingRedirects;                              // 0x0960 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class UOnlineLobbyInterfaceSteamworks*             LobbyInterfaceImpl;                            // 0x0970 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             __CanPlayOnlineChanged__Delegate;              // 0x0978 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUserSwitchComplete__Delegate;              // 0x0990 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUserSignInComplete__Delegate;              // 0x09A8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLoginChange__Delegate;                     // 0x09C0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLoginCancelled__Delegate;                  // 0x09D8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnMutingChange__Delegate;                    // 0x09F0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFriendsChange__Delegate;                   // 0x0A08 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFriendInviteAccepted__Delegate;            // 0x0A20 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __FriendPresenceChange__Delegate;              // 0x0A38 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnAvatarChange__Delegate;                    // 0x0A50 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLoginFailed__Delegate;                     // 0x0A68 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLogoutCompleted__Delegate;                 // 0x0A80 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLoginStatusChange__Delegate;               // 0x0A98 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadProfileSettingsComplete__Delegate;     // 0x0AB0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnWriteProfileSettingsComplete__Delegate;    // 0x0AC8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadPlayerStorageComplete__Delegate;       // 0x0AE0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadPlayerStorageForNetIdComplete__Delegate;// 0x0AF8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnWritePlayerStorageComplete__Delegate;      // 0x0B10 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadFriendsComplete__Delegate;             // 0x0B28 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnPlayerTalkingStateChange__Delegate;        // 0x0B40 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnRecognitionComplete__Delegate;             // 0x0B58 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadOnlineStatsComplete__Delegate;         // 0x0B70 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFlushOnlineStatsComplete__Delegate;        // 0x0B88 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnLinkStatusChange__Delegate;                // 0x0BA0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnExternalUIChange__Delegate;                // 0x0BB8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnControllerChange__Delegate;                // 0x0BD0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUserOrphaned__Delegate;                    // 0x0BE8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUserRestored__Delegate;                    // 0x0C00 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnConnectionStatusChange__Delegate;          // 0x0C18 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnStorageDeviceChange__Delegate;             // 0x0C30 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadTitleFileComplete__Delegate;           // 0x0C48 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnKeyboardInputComplete__Delegate;           // 0x0C60 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnAddFriendComplete__Delegate;               // 0x0C78 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnQueryUserByDisplayName__Delegate;          // 0x0C90 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnAddFriendByNameComplete__Delegate;         // 0x0CA8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnRemoveFriendComplete__Delegate;            // 0x0CC0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnAcceptFriendInviteComplete__Delegate;      // 0x0CD8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnDenyFriendInviteComplete__Delegate;        // 0x0CF0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFriendInviteReceived__Delegate;            // 0x0D08 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFriendInviteCanceled__Delegate;            // 0x0D20 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReceivedGameInvite__Delegate;              // 0x0D38 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnJoinFriendGameComplete__Delegate;          // 0x0D50 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnFriendMessageReceived__Delegate;           // 0x0D68 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnRegisterHostStatGuidComplete__Delegate;    // 0x0D80 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnDeviceSelectionComplete__Delegate;         // 0x0D98 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUnlockAchievementComplete__Delegate;       // 0x0DB0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnProfileDataChanged__Delegate;              // 0x0DC8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadAchievementsComplete__Delegate;        // 0x0DE0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnGetNumberOfCurrentPlayersComplete__Delegate;// 0x0DF8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadCrossTitleProfileSettingsComplete__Delegate;// 0x0E10 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnEnumerateUserFilesComplete__Delegate;      // 0x0E28 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadUserFileComplete__Delegate;            // 0x0E40 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnWriteUserFileComplete__Delegate;           // 0x0E58 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnDeleteUserFileComplete__Delegate;          // 0x0E70 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnReadSharedFileComplete__Delegate;          // 0x0E88 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnWriteSharedFileComplete__Delegate;         // 0x0EA0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnStorePurchaseCompleteDelegate__Delegate;   // 0x0EB8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUnlockedDLCChange__Delegate;               // 0x0ED0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnSaveDataNoSpaceDialogComplete__Delegate;   // 0x0EE8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnCommerceDialogClosed__Delegate;            // 0x0F00 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnCloseKickPlayerDialog__Delegate;           // 0x0F18 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnErrorDialogClosed__Delegate;               // 0x0F30 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnRegisteredController__Delegate;            // 0x0F48 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnUnregisteredController__Delegate;          // 0x0F60 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnInputAPIChanged__Delegate;                 // 0x0F78 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnPlayerSigningOut__Delegate;                // 0x0F90 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __EpicIDToPlatformIDCallback__Delegate;        // 0x0FA8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnBlockListUpdated__Delegate;                // 0x0FC0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnPlayerBlocked__Delegate;                   // 0x0FD8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnPlayerUnblocked__Delegate;                 // 0x0FF0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __OnCaptureAvailabilityChange__Delegate;       // 0x1008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlineSubsystemSteamworks");
		}

		return uClassPointer;
	};

	void ClearCaptureAvailabilityChangeDelegate(const struct FScriptDelegate& CaptureAvailabilityDelegate);
	void AddCaptureAvailabilityChangeDelegate(const struct FScriptDelegate& CaptureAvailabilityDelegate);
	void OnCaptureAvailabilityChange(bool bCaptureAllowed);
	bool ReadBlockList(uint8_t LocalUserNum);
	void GetBlockList(uint8_t LocalUserNum, class TArray<struct FOnlineFriend>& outOutBlockList);
	void AddPlayerUnblockedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& Delegate);
	void OnPlayerUnblocked(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID, class UError* Error);
	void AddPlayerBlockedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& Delegate);
	void OnPlayerBlocked(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID, class UError* Error);
	void AddBlockListUpdatedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& Delegate);
	void OnBlockListUpdated(uint8_t LocalUserNum);
	void EpicIDToPlatformID(const struct FUniqueNetId& EpicAccountId, EOnlinePlatform TargetPlatform, const struct FScriptDelegate& Callback);
	void EpicIDToPlatformIDCallback(const struct FUniqueNetId& PlatformAccountId, const class FString& Error);
	struct FUniqueNetId GetEpicAccountId(const struct FUniqueNetId& PlatformId);
	void ClearPlayerSigningOutDelegate(const struct FScriptDelegate& InDelegate);
	void AddPlayerSigningOutDelegate(const struct FScriptDelegate& InDelegate);
	void OnPlayerSigningOut(uint8_t LocalUserNum);
	bool RefreshNetworkErrorToggle();
	bool TriggerScreenshot();
	void OnControllerConnectionStatusChanged(int32_t LocalPlayerNum, bool bConnected);
	void OnControllerInputAPIChanged(int32_t LocalPlayerNum, EInputAPI InputAPI);
	EInputPlatformType GetControllerPlatform(int32_t LocalPlayerNum);
	int32_t GetControllerID(int32_t LocalPlayerNum);
	class TArray<class FName> GetConnectedControllerNames();
	void OnLocalPlayerRemoved(int32_t LocalPlayerNum);
	void UnregisterController(int32_t LocalPlayerNum);
	void RegisterController(int32_t LocalPlayerNum, int32_t optionalControllerId = {});
	bool CanRegisterController(int32_t LocalPlayerNum);
	bool ShowBindings(int32_t ControllerId);
	void SetControllerLayout(int32_t ControllerId, const class FName& LayoutName);
	void SetInputAPI(EInputAPI TargetAPI);
	class TArray<class FName> GetActiveDiscDLC();
	void SetOnlineSubscriptionRequirement(bool bRequiresOnlineSubscription);
	void HandleGamepadConnectionStatusChanged(class UGameViewportClient* GVC, int32_t LocalPlayerNum, bool bConnected);
	void HandleGamepadInputAPIChanged(class UGameViewportClient* GVC, int32_t LocalPlayerNum, EInputAPI InputAPI);
	void ClearInputAPIChangedDelegate(const struct FScriptDelegate& InputAPIChangedDelegate);
	void AddInputAPIChangedDelegate(const struct FScriptDelegate& InputAPIChangedDelegate);
	void ClearUnregisteredControllerDelegate(const struct FScriptDelegate& UnregisteredControllerDelegate);
	void ClearRegisteredControllerDelegate(const struct FScriptDelegate& RegisteredControllerDelegate);
	void AddUnregisteredControllerDelegate(const struct FScriptDelegate& UnregisteredControllerDelegate);
	void AddRegisteredControllerDelegate(const struct FScriptDelegate& RegisteredControllerDelegate);
	void OnInputAPIChanged(EInputAPI TargetAPI);
	void OnUnregisteredController(int32_t LocalPlayerNum);
	void OnRegisteredController(int32_t LocalPlayerNum, int32_t ControllerId);
	bool HasIncomingFriendInvite(uint8_t LocalUserNum, const struct FUniqueNetId& InviteFrom);
	bool HasFriendsFunctionality();
	bool CanSendOfflinePartyInvite(const struct FUniqueNetId& PlayerID);
	bool CheckParentalControlInfo(bool bShowUi);
	bool RecordPlayersRecentlyMetKeys(uint8_t LocalUserNum, class TArray<struct FFriendHistoryKey>& outPlayerKeys);
	bool GetPlayHistoryRegistrationKey(class TArray<uint8_t>& outKey);
	bool IsOriginalAppOwner();
	void UpdateSessionStatusFromPlayers(int32_t CurrentPlayerCount, int32_t numBotPlayers);
	bool IsAchievementUnlocked(uint8_t LocalUserNum, int32_t AchievementId);
	void UpdateGameProgress(uint8_t LocalPlayerNum, float Progress);
	void FinishOnlineGameSession(const class FString& ServerId);
	void StartOnlineGameSession(const class FString& ServerId);
	void ClearSystemUserControllerPairingChangedDelegate(const struct FScriptDelegate& PairingChangeDelegate);
	void AddSystemUserControllerPairingChangedDelegate(const struct FScriptDelegate& PairingChangeDelegate);
	void OnSystemUserControllerPairingChanged(int32_t NewLocalUserNum, int32_t PreviousLocalUserNum);
	void ClearAccountPickerInput();
	void LookForAccountPickerInput();
	void AddPlayerToSession(uint8_t ControllerId);
	void ClearPrimaryPlayer();
	void RemoveUserAssociation(uint8_t ControllerId);
	void MapEnd();
	void MapStart();
	void OnlineMatchEnd();
	void OnlineMatchStart(const class FString& MapName);
	void SetSessionDifficultyLevel(int32_t DifficultyLevel);
	void SetSessionGameplayModeName(const class FName& GameplayModeName);
	void SetSessionGameplayMode(int32_t GameplayMode);
	class TArray<uint32_t> GetSyncedAchievements(uint8_t LocalUserNum);
	void SetPlayedWith(const struct FUniqueNetId& PlayerNetId);
	bool HandleBootMessage();
	void ClearErrorDialogClosedDelegate(const struct FScriptDelegate& InDelegate);
	void AddErrorDialogClosedDelegate(const struct FScriptDelegate& InDelegate);
	void OnErrorDialogClosed(int32_t LocalUserNum);
	void ClearCloseKickPlayerDialogDelegate(const struct FScriptDelegate& InDelegate);
	void AddCloseKickPlayerDialogDelegate(const struct FScriptDelegate& InDelegate);
	void OnCloseKickPlayerDialog();
	void ClearCommerceDialogClosedDelegate(const struct FScriptDelegate& InDelegate);
	void AddCommerceDialogClosedDelegate(const struct FScriptDelegate& InDelegate);
	void OnCommerceDialogClosed();
	bool WordFilterSanitizeString(const class FString& Comment, const struct FScriptDelegate& SanitizeDelegate, const struct FUniqueNetId& optionalPlayerID);
	void RemoveCanPlayOnlineChangedDelegate(const struct FScriptDelegate& Callback);
	void AddCanPlayOnlineChangedDelegate(const struct FScriptDelegate& Callback);
	bool RecordPlayersRecentlyMet(uint8_t LocalUserNum, const class FString& GameDescription, class TArray<struct FUniqueNetId>& outPlayers);
	void ClearSaveDataNoSpaceDialogCompleteDelegate(const struct FScriptDelegate& DeviceDelegate);
	void AddSaveDataNoSpaceDialogCompleteDelegate(const struct FScriptDelegate& DeviceDelegate);
	void OnSaveDataNoSpaceDialogComplete(bool bContinueWithoutSave);
	void ClearUnlockedDLCChangeDelegate(const struct FScriptDelegate& InDelegate);
	void AddUnlockedDLCChangeDelegate(const struct FScriptDelegate& InDelegate);
	class TArray<class FName> GetUnlockedDLC();
	void OnUnlockedDLCChange();
	bool GetOverlayEnabled();
	int32_t GetDLCPurchaseTime(const class FName& AppName);
	class FString GetPlayerCountry(uint8_t LocalUserNum);
	class FString GetPlayerLanguage(uint8_t LocalUserNum);
	bool AnyPlayerChatRestricted();
	void InitializeTrophyAPI();
	void OpenStoreForItems(uint8_t LocalUserNum, const class TArray<class FString>& Targets, const struct FScriptDelegate& OnStorePurchaseCompleteDelegate);
	void OpenStoreForDLC(uint8_t LocalUserNum, const class FName& DLC);
	void OpenStoreForItemsAsync(uint8_t LocalUserNum, const class TArray<class FString>& Targets, const struct FScriptDelegate& OnStorePurchaseCompleteDelegate);
	void OnStorePurchaseCompleteDelegate();
	void OpenErrorDialog(uint8_t LocalUserNum, EPS4ErrorDialog ErrorCode);
	void OpenPS4DisplayMode(uint8_t LocalUserNum, EPS4DisplayMode DisplayMode, const class TArray<class FString>& optionalTargets = {}, int32_t optionalServiceLabel = {});
	void ResetControllerColor(int32_t ControllerId);
	void SetControllerColor(int32_t ControllerId, const struct FColor& NewColor);
	bool AddInGamePost(const class FString& InPostID, uint8_t LocalUserNum, const class TArray<class FString>& StringReplaceList);
	bool IsEnabled();
	void SetRichPresence(uint8_t LocalUserNum, const class FString& PresenceString, const class FString& GameDataString);
	void ClearAllDelegates();
	void ClearWriteSharedFileCompleteDelegate(const struct FScriptDelegate& WriteSharedFileCompleteDelegate);
	void AddWriteSharedFileCompleteDelegate(const struct FScriptDelegate& WriteSharedFileCompleteDelegate);
	bool WriteSharedFile(const class FString& UserId, const class FString& Filename, class TArray<uint8_t>& outContents);
	void OnWriteSharedFileComplete(bool bWasSuccessful, const class FString& UserId, const class FString& Filename, const class FString& SharedHandle);
	void ClearReadSharedFileCompleteDelegate(const struct FScriptDelegate& ReadSharedFileCompleteDelegate);
	void AddReadSharedFileCompleteDelegate(const struct FScriptDelegate& ReadSharedFileCompleteDelegate);
	bool ReadSharedFile(const class FString& SharedHandle);
	void OnReadSharedFileComplete(bool bWasSuccessful, const class FString& SharedHandle);
	bool ClearSharedFile(const class FString& SharedHandle);
	bool ClearSharedFiles();
	bool GetSharedFileContents(const class FString& SharedHandle, class TArray<uint8_t>& outFileContents);
	void ClearDeleteUserFileCompleteDelegate(const struct FScriptDelegate& DeleteUserFileCompleteDelegate);
	void AddDeleteUserFileCompleteDelegate(const struct FScriptDelegate& DeleteUserFileCompleteDelegate);
	bool DeleteUserFile(const class FString& UserId, const class FString& Filename, bool bShouldCloudDelete, bool bShouldLocallyDelete);
	void OnDeleteUserFileComplete(bool bWasSuccessful, const class FString& UserId, const class FString& Filename);
	void ClearWriteUserFileCompleteDelegate(const struct FScriptDelegate& WriteUserFileCompleteDelegate);
	void AddWriteUserFileCompleteDelegate(const struct FScriptDelegate& WriteUserFileCompleteDelegate);
	bool WriteUserFile(const class FString& UserId, const class FString& Filename, class TArray<uint8_t>& outFileContents);
	void OnWriteUserFileComplete(bool bWasSuccessful, const class FString& UserId, const class FString& Filename);
	void ClearReadUserFileCompleteDelegate(const struct FScriptDelegate& ReadUserFileCompleteDelegate);
	void AddReadUserFileCompleteDelegate(const struct FScriptDelegate& ReadUserFileCompleteDelegate);
	bool ReadUserFile(const class FString& UserId, const class FString& Filename);
	void OnReadUserFileComplete(bool bWasSuccessful, const class FString& UserId, const class FString& Filename);
	void GetUserFileList(const class FString& UserId, class TArray<struct FEmsFile>& outUserFiles);
	void ClearEnumerateUserFileCompleteDelegate(const struct FScriptDelegate& EnumerateUserFileCompleteDelegate);
	void AddEnumerateUserFileCompleteDelegate(const struct FScriptDelegate& EnumerateUserFileCompleteDelegate);
	void EnumerateUserFiles(const class FString& UserId);
	void OnEnumerateUserFilesComplete(bool bWasSuccessful, const class FString& UserId);
	bool ClearFile(const class FString& UserId, const class FString& Filename);
	bool ClearFiles(const class FString& UserId);
	bool GetFileContents(const class FString& UserId, const class FString& Filename, class TArray<uint8_t>& outFileContents);
	bool WriteUserFileInternal(const class FString& UserId, const class FString& Filename, class TArray<uint8_t>& outFileContents);
	bool SetVoiceReceiveVolume(float VoiceVolume);
	bool GetFriendJoinURL(const struct FUniqueNetId& FriendUID, class FString& outServerURL, class FString& outServerUID);
	bool GetCommandlineJoinURL(bool bMarkAsJoined, class FString& outServerURL, class FString& outServerUID);
	bool Int64ToUniqueNetId(const class FString& UIDString, struct FUniqueNetId& outOutUID);
	class FString UniqueNetIdToInt64(struct FUniqueNetId& outUid);
	void NotifyVOIPPlaybackFinished(class UAudioComponent* VOIPAudioComponent);
	void OnVOIPPlaybackFinished(class UAudioComponent* AC);
	bool ShowProfileUI(uint8_t LocalUserNum, const class FString& optionalSubURL, const struct FUniqueNetId& optionalPlayerUID);
	class FString UniqueNetIdToPlayerName(struct FUniqueNetId& outUid);
	bool DisplayAchievementProgress(int32_t AchievementId, int32_t ProgressCount, int32_t MaxProgress);
	bool CreateLeaderboard(const class FString& LeaderboardName, ELeaderboardSortType SortType, ELeaderboardFormat DisplayFormat);
	bool ResetStats(bool bResetAchievements);
	bool ShowCustomMessageUI(uint8_t LocalUserNum, const class FString& MessageTitle, const class FString& NonEditableMessage, const class FString& optionalEditableMessage, class TArray<struct FUniqueNetId>& outRecipients);
	void ClearCrossTitleProfileSettings(uint8_t LocalUserNum, int32_t TitleId);
	class UOnlineProfileSettings* GetCrossTitleProfileSettings(uint8_t LocalUserNum, int32_t TitleId);
	void ClearReadCrossTitleProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadProfileSettingsCompleteDelegate);
	void AddReadCrossTitleProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadProfileSettingsCompleteDelegate);
	void OnReadCrossTitleProfileSettingsComplete(uint8_t LocalUserNum, int32_t TitleId, bool bWasSuccessful);
	bool ReadCrossTitleProfileSettings(uint8_t LocalUserNum, int32_t TitleId, class UOnlineProfileSettings* ProfileSettings);
	void GetSteamClanData(class TArray<struct FSteamPlayerClanData>& outResults);
	void ClearGetNumberOfCurrentPlayersCompleteDelegate(const struct FScriptDelegate& GetNumberOfCurrentPlayersCompleteDelegate);
	void AddGetNumberOfCurrentPlayersCompleteDelegate(const struct FScriptDelegate& GetNumberOfCurrentPlayersCompleteDelegate);
	void OnGetNumberOfCurrentPlayersComplete(int32_t TotalPlayers);
	bool GetNumberOfCurrentPlayers();
	void ReadOnlineAvatars(EAvatarSize Size, const struct FScriptDelegate& ReadOnlineAvatarCompleteDelegate, class TArray<struct FUniqueNetId>& outPlayerNetIds);
	bool ShowCustomPlayersUI(uint8_t LocalUserNum, const class FString& Title, const class FString& Description, class TArray<struct FUniqueNetId>& outPlayers);
	EOnlineEnumerationReadState GetAchievements(uint8_t LocalUserNum, int32_t optionalTitleId, class TArray<struct FAchievementDetails>& outAchievements);
	void ClearReadAchievementsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadAchievementsCompleteDelegate);
	void AddReadAchievementsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadAchievementsCompleteDelegate);
	void OnReadAchievementsComplete(int32_t TitleId);
	bool ReadAchievements(uint8_t LocalUserNum, int32_t optionalTitleId = {}, bool optionalBShouldReadText = {}, bool optionalBShouldReadImages = {});
	bool ShowPlayersUI(uint8_t LocalUserNum);
	bool ShowFriendsInviteUI(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID);
	bool ShowFriendsUI(uint8_t LocalUserNum);
	void ClearProfileDataChangedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ProfileDataChangedDelegate);
	void AddProfileDataChangedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ProfileDataChangedDelegate);
	void OnProfileDataChanged();
	bool UnlockGamerPicture(uint8_t LocalUserNum, int32_t PictureId);
	void ClearUnlockAchievementCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& UnlockAchievementCompleteDelegate);
	void AddUnlockAchievementCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& UnlockAchievementCompleteDelegate);
	void OnUnlockAchievementComplete(bool bWasSuccessful);
	bool UnlockAchievement(uint8_t LocalUserNum, int32_t AchievementId, float optionalPercentComplete = {});
	bool UpdateStat(uint8_t LocalUserNum, const class FName& StatName, int32_t Points);
	bool IsDeviceValid(int32_t DeviceID, int32_t optionalSizeNeeded = {});
	int32_t GetDeviceSelectionResults(uint8_t LocalUserNum, class FString& outDeviceName);
	void ClearDeviceSelectionDoneDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& DeviceDelegate);
	void AddDeviceSelectionDoneDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& DeviceDelegate);
	void OnDeviceSelectionComplete(bool bWasSuccessful);
	bool ShowDeviceSelectionUI(uint8_t LocalUserNum, int32_t SizeNeeded, bool optionalBManageStorage = {});
	bool ShowContentMarketplaceUI(uint8_t LocalUserNum, int32_t optionalCategoryMask = {}, int32_t optionalOfferId = {});
	bool ShowInviteUI(uint8_t LocalUserNum, const class FString& optionalInviteText = {});
	bool ShowAchievementsUI(uint8_t LocalUserNum);
	bool ShowMessagesUI(uint8_t LocalUserNum);
	bool ShowGamerCardUI(uint8_t LocalUserNum, const struct FUniqueNetId& optionalUniqueId, const class FString& optionalPlayerName = {});
	bool ShowFeedbackUI(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID);
	bool DeleteMessage(uint8_t LocalUserNum, int32_t MessageIndex);
	bool UnmuteAll(uint8_t LocalUserNum);
	bool MuteAll(uint8_t LocalUserNum, bool bAllowFriends);
	bool RegisterStatGuid(const struct FUniqueNetId& PlayerID, class FString& outClientStatGuid);
	class FString GetClientStatGuid();
	void ClearRegisterHostStatGuidCompleteDelegateDelegate(const struct FScriptDelegate& RegisterHostStatGuidCompleteDelegate);
	void AddRegisterHostStatGuidCompleteDelegate(const struct FScriptDelegate& RegisterHostStatGuidCompleteDelegate);
	void OnRegisterHostStatGuidComplete(bool bWasSuccessful);
	bool RegisterHostStatGuid(class FString& outHostStatGuid);
	class FString GetHostStatGuid();
	void ClearFriendMessageReceivedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& MessageDelegate);
	void AddFriendMessageReceivedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& MessageDelegate);
	void OnFriendMessageReceived(uint8_t LocalUserNum, const struct FUniqueNetId& SendingPlayer, const class FString& SendingNick, const class FString& Message);
	void GetFriendMessages(uint8_t LocalUserNum, class TArray<struct FOnlineFriendMessage>& outFriendMessages);
	void ClearJoinFriendGameCompleteDelegate(const struct FScriptDelegate& JoinFriendGameCompleteDelegate);
	void AddJoinFriendGameCompleteDelegate(const struct FScriptDelegate& JoinFriendGameCompleteDelegate);
	void OnJoinFriendGameComplete(bool bWasSuccessful);
	bool JoinFriendGame(uint8_t LocalUserNum, const struct FUniqueNetId& Friend);
	void ClearReceivedGameInviteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReceivedGameInviteDelegate);
	void AddReceivedGameInviteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReceivedGameInviteDelegate);
	void OnReceivedGameInvite(uint8_t LocalUserNum, const class FString& InviterName);
	bool SendGameInviteToFriends(uint8_t LocalUserNum, const class TArray<struct FUniqueNetId>& Friends, const class FString& optionalText = {});
	bool SendGameInviteToFriend(uint8_t LocalUserNum, const struct FUniqueNetId& Friend, const class FString& optionalText = {});
	bool SendMessageToFriendW(uint8_t LocalUserNum, const struct FUniqueNetId& Friend, const class FString& Message);
	void ClearFriendInviteCanceledDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& InviteDelegate);
	void AddFriendInviteCanceledDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& InviteDelegate);
	void OnFriendInviteCanceled(uint8_t LocalUserNum, const struct FUniqueNetId& CanceledUserId);
	void ClearFriendInviteReceivedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& InviteDelegate);
	void AddFriendInviteReceivedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& InviteDelegate);
	void OnFriendInviteReceived(uint8_t LocalUserNum, const struct FUniqueNetId& RequestingPlayer, const class FString& RequestingNick, const class FString& Message);
	bool DenyFriendInvite(uint8_t LocalUserNum, const struct FUniqueNetId& RequestingPlayer);
	void ClearDenyFriendInviteCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void AddDenyFriendInviteCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void OnDenyFriendInviteComplete(const struct FUniqueNetId& FriendId, class UError* Error);
	bool AcceptFriendInvite(uint8_t LocalUserNum, const struct FUniqueNetId& RequestingPlayer);
	void ClearAcceptFriendInviteCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void AddAcceptFriendInviteCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void OnAcceptFriendInviteComplete(const struct FUniqueNetId& FriendId, class UError* Error);
	bool RemoveFriend(uint8_t LocalUserNum, const struct FUniqueNetId& FormerFriend);
	void ClearRemoveFriendCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& RemoveFriendDelegate);
	void AddRemoveFriendCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& RemoveFriendDelegate);
	void OnRemoveFriendComplete(bool bWasSuccessful, const struct FUniqueNetId& RemovedID);
	void ClearAddFriendByNameCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void AddAddFriendByNameCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void OnAddFriendByNameComplete(bool bWasSuccessful);
	bool AddFriendByName(uint8_t LocalUserNum, const class FString& FriendName, const class FString& optionalMessage = {});
	bool QueryUserByDisplayName(uint8_t LocalUserNum, const class FString& DisplayName);
	void ClearQueryUserByDisplayNameCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& QueryDelegate);
	void AddQueryUserByDisplayNameCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& QueryDelegate);
	void OnQueryUserByDisplayName(bool bWasSuccessful, const class FString& QueriedDisplayName, const struct FUniqueNetId& UserId);
	bool AddFriend(uint8_t LocalUserNum, const struct FUniqueNetId& NewFriend, const class FString& optionalMessage = {});
	void ClearAddFriendCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void AddAddFriendCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendDelegate);
	void OnAddFriendComplete(const struct FUniqueNetId& NewFriendId, class UError* Error);
	class FString GetKeyboardInputResults(uint8_t& outBWasCanceled);
	void ClearKeyboardInputDoneDelegate(const struct FScriptDelegate& InputDelegate);
	void AddKeyboardInputDoneDelegate(const struct FScriptDelegate& InputDelegate);
	void OnKeyboardInputComplete(bool bWasSuccessful);
	bool HideKeyboardUI(uint8_t LocalUserNum);
	bool ShowKeyboardUI(uint8_t LocalUserNum, const class FString& TitleText, const class FString& DescriptionText, bool optionalBIsPassword = {}, bool optionalBShouldValidate = {}, const class FString& optionalDefaultText = {}, int32_t optionalMaxResultLength = {});
	void SetOnlineStatus(uint8_t LocalUserNum, int32_t StatusId, class TArray<struct FLocalizedStringSetting>& outLocalizedStringSettings, class TArray<struct FSettingsProperty>& outProperties);
	EOnlineEnumerationReadState GetTitleFileState(const class FString& Filename);
	bool GetTitleFileContents(const class FString& Filename, class TArray<uint8_t>& outFileContents);
	void ClearReadTitleFileCompleteDelegate(const struct FScriptDelegate& ReadTitleFileCompleteDelegate);
	void AddReadTitleFileCompleteDelegate(const struct FScriptDelegate& ReadTitleFileCompleteDelegate);
	bool ReadTitleFile(const class FString& FileToRead);
	void OnReadTitleFileComplete(bool bWasSuccessful, const class FString& Filename);
	void ClearStorageDeviceChangeDelegate(const struct FScriptDelegate& StorageDeviceChangeDelegate);
	void AddStorageDeviceChangeDelegate(const struct FScriptDelegate& StorageDeviceChangeDelegate);
	void OnStorageDeviceChange();
	ENATType GetNATType();
	void ClearConnectionStatusChangeDelegate(const struct FScriptDelegate& ConnectionStatusDelegate);
	void AddConnectionStatusChangeDelegate(const struct FScriptDelegate& ConnectionStatusDelegate);
	void OnConnectionStatusChange(EOnlineServerConnectionStatus ConnectionStatus);
	EOnlineServerConnectionStatus GetCurrentConnectionStatus();
	bool IsControllerConnected(int32_t ControllerId);
	void ClearUserRestoredDelegate(const struct FScriptDelegate& UserRestoredDelegate);
	void AddUserRestoredDelegate(const struct FScriptDelegate& UserRestoredDelegate);
	void OnUserRestored(uint8_t ControllerId);
	void ClearUserOrphanedDelegate(const struct FScriptDelegate& UserOrphanedDelegate);
	void AddUserOrphanedDelegate(const struct FScriptDelegate& UserOrphanedDelegate);
	void OnUserOrphaned(uint8_t ControllerId);
	void ClearControllerChangeDelegate(const struct FScriptDelegate& ControllerChangeDelegate);
	void AddControllerChangeDelegate(const struct FScriptDelegate& ControllerChangeDelegate);
	void OnControllerChange(int32_t ControllerId, bool bIsConnected);
	void SetNetworkNotificationPosition(ENetworkNotificationPosition NewPos);
	ENetworkNotificationPosition GetNetworkNotificationPosition();
	void ClearExternalUIChangeDelegate(const struct FScriptDelegate& ExternalUIDelegate);
	void AddExternalUIChangeDelegate(const struct FScriptDelegate& ExternalUIDelegate);
	void OnExternalUIChange(bool bIsOpening);
	void ClearLinkStatusChangeDelegate(const struct FScriptDelegate& LinkStatusDelegate);
	void AddLinkStatusChangeDelegate(const struct FScriptDelegate& LinkStatusDelegate);
	void OnLinkStatusChange(bool bIsConnected);
	bool HasLinkConnection();
	class FString eventGetPlayerNicknameFromIndex(int32_t UserIndex);
	bool WriteOnlinePlayerScores(const class FName& SessionName, int32_t LeaderboardId, class TArray<struct FOnlinePlayerScore>& outPlayerScores);
	void ClearFlushOnlineStatsCompleteDelegate(const struct FScriptDelegate& FlushOnlineStatsCompleteDelegate);
	void AddFlushOnlineStatsCompleteDelegate(const struct FScriptDelegate& FlushOnlineStatsCompleteDelegate);
	void OnFlushOnlineStatsComplete(const class FName& SessionName, bool bWasSuccessful);
	bool FlushOnlineStats(const class FName& SessionName);
	bool WriteOnlineStats(const class FName& SessionName, const struct FUniqueNetId& Player, class UOnlineStatsWrite* StatsWrite);
	void FreeStats(class UOnlineStatsRead* StatsRead);
	void ClearReadOnlineStatsCompleteDelegate(const struct FScriptDelegate& ReadOnlineStatsCompleteDelegate);
	void AddReadOnlineStatsCompleteDelegate(const struct FScriptDelegate& ReadOnlineStatsCompleteDelegate);
	void OnReadOnlineStatsComplete(bool bWasSuccessful);
	bool ReadOnlineStatsByRankAroundPlayer(uint8_t LocalUserNum, class UOnlineStatsRead* StatsRead, int32_t optionalNumRows = {});
	bool ReadOnlineStatsByRank(uint8_t LocalUserNum, class UOnlineStatsRead* StatsRead, int32_t optionalStartIndex = {}, int32_t optionalNumToRead = {});
	bool ReadOnlineStatsForFriends(uint8_t LocalUserNum, class UOnlineStatsRead* StatsRead);
	bool ReadOnlineStats(uint8_t LocalUserNum, class UOnlineStatsRead* StatsRead, class TArray<struct FUniqueNetId>& outPlayers);
	bool SetSpeechRecognitionObject(uint8_t LocalUserNum, class USpeechRecognition* SpeechRecogObj);
	bool SelectVocabulary(uint8_t LocalUserNum, int32_t VocabularyId);
	void ClearRecognitionCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& RecognitionDelegate);
	void AddRecognitionCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& RecognitionDelegate);
	void OnRecognitionComplete();
	bool GetRecognitionResults(uint8_t LocalUserNum, class TArray<struct FSpeechRecognizedWord>& outWords);
	bool StopSpeechRecognition(uint8_t LocalUserNum);
	bool StartSpeechRecognition(uint8_t LocalUserNum);
	void StopNetworkedVoice(uint8_t LocalUserNum);
	void StartNetworkedVoice(uint8_t LocalUserNum);
	void ClearPlayerTalkingDelegate(const struct FScriptDelegate& TalkerDelegate);
	void AddPlayerTalkingDelegate(const struct FScriptDelegate& TalkerDelegate);
	void OnPlayerTalkingStateChange(const struct FUniqueNetId& Player, bool bIsTalking);
	bool UnmuteRemoteTalker(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID, bool optionalBIsSystemWide = {});
	bool MuteRemoteTalker(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID, bool optionalBIsSystemWide = {});
	bool SetRemoteTalkerPriority(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID, int32_t Priority);
	bool IsHeadsetPresent(uint8_t LocalUserNum);
	bool IsRemotePlayerTalking(const struct FUniqueNetId& PlayerID);
	bool IsLocalPlayerTalking(uint8_t LocalUserNum);
	bool UnregisterRemoteTalker(const struct FUniqueNetId& PlayerID);
	bool RegisterRemoteTalker(const struct FUniqueNetId& PlayerID);
	bool UnregisterLocalTalker(uint8_t LocalUserNum);
	bool RegisterLocalTalker(uint8_t LocalUserNum);
	EOnlineEnumerationReadState GetFriendsList(uint8_t LocalUserNum, int32_t optionalCount, int32_t optionalStartingAt, class TArray<struct FOnlineFriend>& outFriends);
	void ClearReadFriendsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadFriendsCompleteDelegate);
	void AddReadFriendsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadFriendsCompleteDelegate);
	void OnReadFriendsComplete(bool bWasSuccessful);
	bool ReadFriendsList(uint8_t LocalUserNum, int32_t optionalCount = {}, int32_t optionalStartingAt = {});
	void ClearWritePlayerStorageCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& WritePlayerStorageCompleteDelegate);
	void AddWritePlayerStorageCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& WritePlayerStorageCompleteDelegate);
	void OnWritePlayerStorageComplete(uint8_t LocalUserNum, bool bWasSuccessful);
	bool WritePlayerStorage(uint8_t LocalUserNum, class UOnlinePlayerStorage* PlayerStorage, int32_t optionalDeviceID = {});
	class UOnlinePlayerStorage* GetPlayerStorage(uint8_t LocalUserNum);
	void ClearReadPlayerStorageForNetIdCompleteDelegate(const struct FUniqueNetId& NetId, const struct FScriptDelegate& ReadPlayerStorageForNetIdCompleteDelegate);
	void AddReadPlayerStorageForNetIdCompleteDelegate(const struct FUniqueNetId& NetId, const struct FScriptDelegate& ReadPlayerStorageForNetIdCompleteDelegate);
	void OnReadPlayerStorageForNetIdComplete(const struct FUniqueNetId& NetId, bool bWasSuccessful);
	bool ReadPlayerStorageForNetId(uint8_t LocalUserNum, const struct FUniqueNetId& NetId, class UOnlinePlayerStorage* PlayerStorage);
	void ClearReadPlayerStorageCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadPlayerStorageCompleteDelegate);
	void AddReadPlayerStorageCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadPlayerStorageCompleteDelegate);
	void OnReadPlayerStorageComplete(uint8_t LocalUserNum, bool bWasSuccessful);
	bool ReadPlayerStorage(uint8_t LocalUserNum, class UOnlinePlayerStorage* PlayerStorage, int32_t optionalDeviceID = {});
	void ClearWriteProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& WriteProfileSettingsCompleteDelegate);
	void AddWriteProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& WriteProfileSettingsCompleteDelegate);
	void OnWriteProfileSettingsComplete(uint8_t LocalUserNum, bool bWasSuccessful);
	bool WriteProfileSettings(uint8_t LocalUserNum, class UOnlineProfileSettings* ProfileSettings);
	class UOnlineProfileSettings* GetProfileSettings(uint8_t LocalUserNum);
	void ClearReadProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadProfileSettingsCompleteDelegate);
	void AddReadProfileSettingsCompleteDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& ReadProfileSettingsCompleteDelegate);
	void OnReadProfileSettingsComplete(uint8_t LocalUserNum, bool bWasSuccessful);
	bool ReadProfileSettings(uint8_t LocalUserNum, class UOnlineProfileSettings* ProfileSettings);
	void ClearFriendsChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendsDelegate);
	void ClearAvatarChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& AvatarDelegate);
	void AddAvatarChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& AvatarDelegate);
	void GetFriendPresence(struct FOnlineFriend& outFriendData);
	void ClearFriendPresenceChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& PresenceDelegate);
	void AddFriendPresenceChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& PresenceDelegate);
	void AddFriendsChangeDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& FriendsDelegate);
	void ClearMutingChangeDelegate(const struct FScriptDelegate& MutingDelegate);
	void AddMutingChangeDelegate(const struct FScriptDelegate& MutingDelegate);
	void ClearLoginCancelledDelegate(const struct FScriptDelegate& CancelledDelegate);
	void AddLoginCancelledDelegate(const struct FScriptDelegate& CancelledDelegate);
	void ClearLoginStatusChangeDelegate(const struct FScriptDelegate& LoginStatusDelegate, uint8_t LocalUserNum);
	void AddLoginStatusChangeDelegate(const struct FScriptDelegate& LoginStatusDelegate, uint8_t LocalUserNum);
	void OnLoginStatusChange(ELoginStatus NewStatus, const struct FUniqueNetId& NewId);
	void ClearLoginChangeDelegate(const struct FScriptDelegate& LoginDelegate);
	void AddLoginChangeDelegate(const struct FScriptDelegate& LoginDelegate);
	void ClearUserSignInCompleteDelegate(const struct FScriptDelegate& UserSignInCompleteDelegate);
	void AddUserSignInCompleteDelegate(const struct FScriptDelegate& UserSignInCompleteDelegate);
	void ClearUserSwitchCompleteDelegate(const struct FScriptDelegate& UserSwitchCompleteDelegate);
	void AddUserSwitchCompleteDelegate(const struct FScriptDelegate& UserSwitchCompleteDelegate);
	void SetPrimaryPlayerGamepadToLastInput();
	bool IsMuted(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID);
	bool AreAnyFriends(uint8_t LocalUserNum, class TArray<struct FFriendsQuery>& outQuery);
	bool IsFriend(uint8_t LocalUserNum, const struct FUniqueNetId& PlayerID);
	void RequestRestrictedFeatureMessaging(uint8_t LocalUserNum, EFeaturePrivilege RestrictedFeature);
	bool CanUploadFitnessData(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanShareKinectContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanShareWithSocialNetwork(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanBrowseInternet(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanAccessPremiumVideoContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanAccessPremiumContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanUseCloudStorage(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanRecordDVRClips(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanShowPresenceInformation(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanViewPlayerProfiles(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanPurchaseContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanDownloadUserContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanShareUserCreatedContent(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanCommunicateVoice(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanCommunicateVideo(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	bool CanCommunicateText(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	EFeaturePrivilegeLevel CanCommunicate(uint8_t LocalUserNum, ECommunicationMethod CommMethod, bool optionalBAttemptToResolve = {});
	bool CanPlayOnline(uint8_t LocalUserNum, bool optionalBAttemptToResolve, const class FString& optionalReason, EFeaturePrivilegeLevel& outPrivilegeLevelHint);
	class FString GetPlayerNickname(uint8_t LocalUserNum);
	bool GetUniquePlayerId(uint8_t LocalUserNum, struct FUniqueNetId& outPlayerID);
	bool IsGuestLogin(uint8_t LocalUserNum);
	ELoginStatus GetLoginStatus(uint8_t LocalUserNum);
	void ClearLogoutCompletedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& LogoutDelegate);
	void AddLogoutCompletedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& LogoutDelegate);
	void OnLogoutCompleted(bool bWasSuccessful);
	bool Logout(uint8_t LocalUserNum);
	void ClearLoginFailedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& LoginFailedDelegate);
	void AddLoginFailedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& LoginFailedDelegate);
	void OnLoginFailed(uint8_t LocalUserNum, EOnlineServerConnectionStatus ErrorCode);
	bool AutoLogin();
	bool Login(uint8_t LocalUserNum, const class FString& LoginName, const class FString& Password, bool optionalBWantsLocalOnly = {});
	void SetKickPlayerDialogActive(bool Active);
	bool IsUserSwitchActive();
	void SetKickPreviousUser(uint8_t LocalUserNum);
	bool SupportInGameLogin();
	bool ShowControllerUI();
	bool ShowLoginUIForOrphanedUser(uint8_t LocalUserNum);
	bool ShowLoginUI(uint8_t LocalUserNum, bool optionalBShowOnlineOnly = {});
	void OnAvatarChange(const struct FUniqueNetId& PlayerID);
	void FriendPresenceChange(const struct FUniqueNetId& PlayerID);
	void AddFriendInviteAcceptedDelegate(uint8_t LocalUserNum, const struct FScriptDelegate& InviteAccepted);
	void OnFriendInviteAccepted(const struct FUniqueNetId& AcceptingPlayerId);
	void OnFriendsChange();
	void OnMutingChange();
	void OnLoginCancelled();
	void OnLoginChange(uint8_t LocalUserNum);
	void OnUserSignInComplete(uint8_t LocalUserNum);
	void OnUserSwitchComplete(uint8_t LocalUserNum);
	void eventExit();
	bool eventPostInit();
	bool eventInit();
	void CanPlayOnlineChanged(uint8_t LocalUserNum);
};

// Class OnlineSubsystemSteamworks.OnlinePurchaseInterfaceSteamworks
// 0x0020 (0x0090 - 0x00B0)
class UOnlinePurchaseInterfaceSteamworks : public UOnlinePurchaseInterfaceImpl
{
public:
	class TArray<struct FAppPriceInfoRequest>          AppPriceInfoRequests;                          // 0x0090 (0x0010) [0x0000004000402000] (CPF_Transient | CPF_NeedCtorLink | CPF_PrivateWrite)
	class TArray<struct FScriptDelegate>               MicroTxnResponseDelegates;                     // 0x00A0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.OnlinePurchaseInterfaceSteamworks");
		}

		return uClassPointer;
	};

	void ClearMicroTxnResponseDelegate(const struct FScriptDelegate& ResponseMicroTxnDelegate);
	void AddMicroTxnResponseDelegate(const struct FScriptDelegate& ResponseMicroTxnDelegate);
	class FString FormatCurrency(const class FString& Currency, int32_t Price);
	void HandleGetAppPriceInfoComplete(class UHttpRequestInterface* Request, class UHttpResponseInterface* Response, bool bDidSucceed);
	bool GetAppPriceInfo(const struct FScriptDelegate& Callback, struct FUniqueNetId& outPlayerID, class TArray<class FName>& outAppNames);
	bool AppIdToName(const class FString& AppID, bool optionalBOptional, class FName& outAppName);
	bool AppNameToId(const class FName& AppName, bool optionalBOptional, class FString& outAppID);
};

// Class OnlineSubsystemSteamworks.SteamWorkshopCommandlet
// 0x000C (0x00B4 - 0x00C0)
class USteamWorkshopCommandlet : public UCommandlet
{
public:
	class UOnlineSubsystemCommonImpl*                  OnlineSub;                                     // 0x00B8 (0x0008) [0x0000000000002000] (CPF_Transient)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.SteamWorkshopCommandlet");
		}

		return uClassPointer;
	};

	bool eventInit();
};

// Class OnlineSubsystemSteamworks.SteamWorkshopEngine
// 0x0004 (0x0B60 - 0x0B64)
class USteamWorkshopEngine : public UGameEngine
{
public:
	uint32_t                                           bHasFinsihed : 1;                              // 0x0B60 (0x0004) [0x0000000000002000] [0x100000001] (CPF_Transient)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.SteamWorkshopEngine");
		}

		return uClassPointer;
	};

};

// Class OnlineSubsystemSteamworks.IpNetDriverSteamworks
// 0x0018 (0x0320 - 0x0338)
class UIpNetDriverSteamworks : public UTcpNetDriver
{
public:
	uint32_t                                           bSteamSocketsOnly : 1;                         // 0x0320 (0x0004) [0x0000000000004000] [0x00000001] (CPF_Config)
	uint8_t                                            UnknownData00[0x14];                            // 0x0324 (0x0014) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.IpNetDriverSteamworks");
		}

		return uClassPointer;
	};

};

// Class OnlineSubsystemSteamworks.IpNetConnectionSteamworks
// 0x0000 (0xB218 - 0xB218)
class UIpNetConnectionSteamworks : public UTcpipConnection
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class OnlineSubsystemSteamworks.IpNetConnectionSteamworks");
		}

		return uClassPointer;
	};

};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
