/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: IpDrv\IpDrv_structs.hpp
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

// ScriptStruct IpDrv.AdHocDelegates.AdHocAccessPointInfo
// 0x0038
struct FAdHocAccessPointInfo
{
	class FString                                      Ipv4Addr;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Username;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      AdvertiseData;                                 // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            ScanResultIndex;                               // 0x0030 (0x0004) [0x0000000000000000]               
	int32_t                                            NetworkNodeIndex;                              // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FAdHocAccessPointInfo& other) const { return memcmp(this, &other, sizeof(FAdHocAccessPointInfo)) == 0; }
	bool operator!=(const FAdHocAccessPointInfo& other) const { return !(*this == other); }
	bool operator<(const FAdHocAccessPointInfo& other) const { return memcmp(this, &other, sizeof(FAdHocAccessPointInfo)) < 0; }
};

// ScriptStruct IpDrv.AdHocDelegates.AdHocStationInfo
// 0x0010
struct FAdHocStationInfo
{
	class FString                                      Username;                                      // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FAdHocStationInfo& other) const { return memcmp(this, &other, sizeof(FAdHocStationInfo)) == 0; }
	bool operator!=(const FAdHocStationInfo& other) const { return !(*this == other); }
	bool operator<(const FAdHocStationInfo& other) const { return memcmp(this, &other, sizeof(FAdHocStationInfo)) < 0; }
};

// ScriptStruct IpDrv.AvatarDownloadMap.AvatarKey
// 0x0049
struct FAvatarKey
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	EAvatarSize                                        Size;                                          // 0x0048 (0x0001) [0x0000000000000000]               

	bool operator==(const FAvatarKey& other) const { return memcmp(this, &other, sizeof(FAvatarKey)) == 0; }
	bool operator!=(const FAvatarKey& other) const { return !(*this == other); }
	bool operator<(const FAvatarKey& other) const { return memcmp(this, &other, sizeof(FAvatarKey)) < 0; }
};

// ScriptStruct IpDrv.OnlineImageDownloaderWeb.OnlineImageDownload
// 0x0040
struct FOnlineImageDownload
{
	class FString                                      URL;                                           // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       HTTPRequest;                                   // 0x0010 (0x0008) [0x0000000000000000]               
	EOnlineImageDownloadState                          Status;                                        // 0x0018 (0x0001) [0x0000000000000000]               
	class UTexture2DDynamic*                           Texture;                                       // 0x0020 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             DecodedCallbacks;                              // 0x0028 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineImageDownload& other) const { return memcmp(this, &other, sizeof(FOnlineImageDownload)) == 0; }
	bool operator!=(const FOnlineImageDownload& other) const { return !(*this == other); }
	bool operator<(const FOnlineImageDownload& other) const { return memcmp(this, &other, sizeof(FOnlineImageDownload)) < 0; }
};

// ScriptStruct IpDrv.ImageDecoder.DecodeImageRequest
// 0x0030
struct FDecodeImageRequest
{
	class FString                                      RequestURL;                                    // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             OnFinishedCallback;                            // 0x0010 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FPointer                                    Task;                                          // 0x0028 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FDecodeImageRequest& other) const { return memcmp(this, &other, sizeof(FDecodeImageRequest)) == 0; }
	bool operator!=(const FDecodeImageRequest& other) const { return !(*this == other); }
	bool operator<(const FDecodeImageRequest& other) const { return memcmp(this, &other, sizeof(FDecodeImageRequest)) < 0; }
};

// ScriptStruct IpDrv.ImageDecoder.DecodeImageTask
// 0x0040
struct FDecodeImageTask
{
	class FString                                      RequestURL;                                    // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	EImageType                                         ImageType;                                     // 0x0010 (0x0001) [0x0000000000000000]               
	class TArray<uint8_t>                              ImageData;                                     // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	struct FImageLayout                                Result;                                        // 0x0028 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDecodeImageTask& other) const { return memcmp(this, &other, sizeof(FDecodeImageTask)) == 0; }
	bool operator!=(const FDecodeImageTask& other) const { return !(*this == other); }
	bool operator<(const FDecodeImageTask& other) const { return memcmp(this, &other, sizeof(FDecodeImageTask)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobBase.McpClashMobChallengeFile
// 0x0059
struct FMcpClashMobChallengeFile
{
	uint32_t                                           should_keep_post_challenge : 1;                // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      title_id;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      file_name;                                     // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      dl_name;                                       // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      hash_code;                                     // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Type;                                          // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMcpChallengeFileStatus                            Status;                                        // 0x0058 (0x0001) [0x0000000000000000]               

	bool operator==(const FMcpClashMobChallengeFile& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeFile)) == 0; }
	bool operator!=(const FMcpClashMobChallengeFile& other) const { return !(*this == other); }
	bool operator<(const FMcpClashMobChallengeFile& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeFile)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobBase.McpClashMobPushNotificationParams
// 0x0004
struct FMcpClashMobPushNotificationParams
{
	int32_t                                            bah;                                           // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FMcpClashMobPushNotificationParams& other) const { return memcmp(this, &other, sizeof(FMcpClashMobPushNotificationParams)) == 0; }
	bool operator!=(const FMcpClashMobPushNotificationParams& other) const { return !(*this == other); }
	bool operator<(const FMcpClashMobPushNotificationParams& other) const { return memcmp(this, &other, sizeof(FMcpClashMobPushNotificationParams)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobBase.McpClashMobPushNotification
// 0x0044
struct FMcpClashMobPushNotification
{
	class TArray<class FString>                        device_tokens;                                 // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      badge_type;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Sound;                                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Message;                                       // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FMcpClashMobPushNotificationParams          Params;                                        // 0x0040 (0x0004) [0x0000000000000000]               

	bool operator==(const FMcpClashMobPushNotification& other) const { return memcmp(this, &other, sizeof(FMcpClashMobPushNotification)) == 0; }
	bool operator!=(const FMcpClashMobPushNotification& other) const { return !(*this == other); }
	bool operator<(const FMcpClashMobPushNotification& other) const { return memcmp(this, &other, sizeof(FMcpClashMobPushNotification)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobBase.McpClashMobChallengeEvent
// 0x00E0
struct FMcpClashMobChallengeEvent
{
	class FString                                      unique_challenge_id;                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      visible_date;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      start_date;                                    // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      end_date;                                      // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      completed_date;                                // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      purge_date;                                    // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      challenge_type;                                // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            num_attempts;                                  // 0x0070 (0x0004) [0x0000000000000000]               
	int32_t                                            num_successful_attempts;                       // 0x0074 (0x0004) [0x0000000000000000]               
	int32_t                                            goal_value;                                    // 0x0078 (0x0004) [0x0000000000000000]               
	int32_t                                            goal_start_value;                              // 0x007C (0x0004) [0x0000000000000000]               
	int32_t                                            goal_current_value;                            // 0x0080 (0x0004) [0x0000000000000000]               
	uint32_t                                           has_started : 1;                               // 0x0084 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           is_visible : 1;                                // 0x0084 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           has_completed : 1;                             // 0x0084 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           was_successful : 1;                            // 0x0084 (0x0004) [0x0000000000000000] [0x00000008] 
	class TArray<struct FMcpClashMobChallengeFile>     file_list;                                     // 0x0088 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            facebook_likes;                                // 0x0098 (0x0004) [0x0000000000000000]               
	int32_t                                            facebook_comments;                             // 0x009C (0x0004) [0x0000000000000000]               
	float                                              facebook_like_scaler;                          // 0x00A0 (0x0004) [0x0000000000000000]               
	float                                              facebook_comment_scaler;                       // 0x00A4 (0x0004) [0x0000000000000000]               
	int32_t                                            facebook_like_goal_progress;                   // 0x00A8 (0x0004) [0x0000000000000000]               
	int32_t                                            facebook_comment_goal_progress;                // 0x00AC (0x0004) [0x0000000000000000]               
	class FString                                      facebook_id;                                   // 0x00B0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            twitter_retweets;                              // 0x00C0 (0x0004) [0x0000000000000000]               
	float                                              twitter_retweets_scaler;                       // 0x00C4 (0x0004) [0x0000000000000000]               
	int32_t                                            twitter_goal_progress;                         // 0x00C8 (0x0004) [0x0000000000000000]               
	class FString                                      twitter_id;                                    // 0x00D0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpClashMobChallengeEvent& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeEvent)) == 0; }
	bool operator!=(const FMcpClashMobChallengeEvent& other) const { return !(*this == other); }
	bool operator<(const FMcpClashMobChallengeEvent& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeEvent)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobBase.McpClashMobChallengeUserStatus
// 0x008C
struct FMcpClashMobChallengeUserStatus
{
	class FString                                      unique_challenge_id;                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      unique_user_id;                                // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            num_attempts;                                  // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            num_successful_attempts;                       // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            goal_progress;                                 // 0x0028 (0x0004) [0x0000000000000000]               
	uint32_t                                           did_complete : 1;                              // 0x002C (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      last_update_time;                              // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            user_award_given;                              // 0x0040 (0x0004) [0x0000000000000000]               
	class FString                                      accept_time;                                   // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           did_preregister : 1;                           // 0x0058 (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      facebook_like_time;                            // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           enrolled_via_facebook : 1;                     // 0x0070 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           liked_via_facebook : 1;                        // 0x0070 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           commented_via_facebook : 1;                    // 0x0070 (0x0004) [0x0000000000000000] [0x00000004] 
	class FString                                      twitter_retweet_time;                          // 0x0078 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           enrolled_via_twitter : 1;                      // 0x0088 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           retweeted : 1;                                 // 0x0088 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FMcpClashMobChallengeUserStatus& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeUserStatus)) == 0; }
	bool operator!=(const FMcpClashMobChallengeUserStatus& other) const { return !(*this == other); }
	bool operator<(const FMcpClashMobChallengeUserStatus& other) const { return memcmp(this, &other, sizeof(FMcpClashMobChallengeUserStatus)) < 0; }
};

// ScriptStruct IpDrv.OnlineTitleFileDownloadBase.FileNameToURLMapping
// 0x0010
struct FFileNameToURLMapping
{
	class FName                                        Filename;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        UrlMapping;                                    // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FFileNameToURLMapping& other) const { return memcmp(this, &other, sizeof(FFileNameToURLMapping)) == 0; }
	bool operator!=(const FFileNameToURLMapping& other) const { return !(*this == other); }
	bool operator<(const FFileNameToURLMapping& other) const { return memcmp(this, &other, sizeof(FFileNameToURLMapping)) < 0; }
};

// ScriptStruct IpDrv.OnlineTitleFileDownloadBase.TitleFileWeb
// 0x0019 (0x0028 - 0x0041)
struct FTitleFileWeb : FTitleFile
{
	class FString                                      StringData;                                    // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       HTTPRequest;                                   // 0x0038 (0x0008) [0x0000000000000000]               
	EMcpFileCompressionType                            FileCompressionType;                           // 0x0040 (0x0001) [0x0000000000000000]               

	bool operator==(const FTitleFileWeb& other) const { return memcmp(this, &other, sizeof(FTitleFileWeb)) == 0; }
	bool operator!=(const FTitleFileWeb& other) const { return !(*this == other); }
	bool operator<(const FTitleFileWeb& other) const { return memcmp(this, &other, sizeof(FTitleFileWeb)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobManager.McpChallengeRequest
// 0x0018
struct FMcpChallengeRequest
{
	class FString                                      UniqueChallengeId;                             // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       HTTPRequest;                                   // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FMcpChallengeRequest& other) const { return memcmp(this, &other, sizeof(FMcpChallengeRequest)) == 0; }
	bool operator!=(const FMcpChallengeRequest& other) const { return !(*this == other); }
	bool operator<(const FMcpChallengeRequest& other) const { return memcmp(this, &other, sizeof(FMcpChallengeRequest)) < 0; }
};

// ScriptStruct IpDrv.McpClashMobManager.McpChallengeUserRequest
// 0x0050
struct FMcpChallengeUserRequest
{
	class FString                                      UniqueUserId;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpChallengeRequest>          ChallengeStatusRequests;                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpChallengeRequest>          ChallengeAcceptRequests;                       // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpChallengeRequest>          ChallengeUpdateProgressRequests;               // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpChallengeRequest>          ChallengeUpdateRewardRequests;                 // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpChallengeUserRequest& other) const { return memcmp(this, &other, sizeof(FMcpChallengeUserRequest)) == 0; }
	bool operator!=(const FMcpChallengeUserRequest& other) const { return !(*this == other); }
	bool operator<(const FMcpChallengeUserRequest& other) const { return memcmp(this, &other, sizeof(FMcpChallengeUserRequest)) < 0; }
};

// ScriptStruct IpDrv.McpGroupsBase.McpGroupMember
// 0x0011
struct FMcpGroupMember
{
	class FString                                      MemberId;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMcpGroupAcceptState                               AcceptState;                                   // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FMcpGroupMember& other) const { return memcmp(this, &other, sizeof(FMcpGroupMember)) == 0; }
	bool operator!=(const FMcpGroupMember& other) const { return !(*this == other); }
	bool operator<(const FMcpGroupMember& other) const { return memcmp(this, &other, sizeof(FMcpGroupMember)) < 0; }
};

// ScriptStruct IpDrv.McpGroupsBase.McpGroup
// 0x0048
struct FMcpGroup
{
	class FString                                      OwnerId;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GroupId;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GroupName;                                     // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMcpGroupAccessLevel                               AccessLevel;                                   // 0x0030 (0x0001) [0x0000000000000000]               
	class TArray<struct FMcpGroupMember>               Members;                                       // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpGroup& other) const { return memcmp(this, &other, sizeof(FMcpGroup)) == 0; }
	bool operator!=(const FMcpGroup& other) const { return !(*this == other); }
	bool operator<(const FMcpGroup& other) const { return memcmp(this, &other, sizeof(FMcpGroup)) < 0; }
};

// ScriptStruct IpDrv.McpGroupsBase.McpGroupList
// 0x0020
struct FMcpGroupList
{
	class FString                                      RequesterId;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpGroup>                     Groups;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpGroupList& other) const { return memcmp(this, &other, sizeof(FMcpGroupList)) == 0; }
	bool operator!=(const FMcpGroupList& other) const { return !(*this == other); }
	bool operator<(const FMcpGroupList& other) const { return memcmp(this, &other, sizeof(FMcpGroupList)) < 0; }
};

// ScriptStruct IpDrv.McpIdMappingBase.McpIdMapping
// 0x0030
struct FMcpIdMapping
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ExternalId;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ExternalType;                                  // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpIdMapping& other) const { return memcmp(this, &other, sizeof(FMcpIdMapping)) == 0; }
	bool operator!=(const FMcpIdMapping& other) const { return !(*this == other); }
	bool operator<(const FMcpIdMapping& other) const { return memcmp(this, &other, sizeof(FMcpIdMapping)) < 0; }
};

// ScriptStruct IpDrv.McpIdMappingManager.AddMappingRequest
// 0x0038
struct FAddMappingRequest
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ExternalId;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ExternalType;                                  // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       Request;                                       // 0x0030 (0x0008) [0x0000000000000000]               

	bool operator==(const FAddMappingRequest& other) const { return memcmp(this, &other, sizeof(FAddMappingRequest)) == 0; }
	bool operator!=(const FAddMappingRequest& other) const { return !(*this == other); }
	bool operator<(const FAddMappingRequest& other) const { return memcmp(this, &other, sizeof(FAddMappingRequest)) < 0; }
};

// ScriptStruct IpDrv.McpIdMappingManager.QueryMappingRequest
// 0x0018
struct FQueryMappingRequest
{
	class FString                                      ExternalType;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       Request;                                       // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FQueryMappingRequest& other) const { return memcmp(this, &other, sizeof(FQueryMappingRequest)) == 0; }
	bool operator!=(const FQueryMappingRequest& other) const { return !(*this == other); }
	bool operator<(const FQueryMappingRequest& other) const { return memcmp(this, &other, sizeof(FQueryMappingRequest)) < 0; }
};

// ScriptStruct IpDrv.McpManagedValueManagerBase.ManagedValue
// 0x000C
struct FManagedValue
{
	class FName                                        ValueId;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            Value;                                         // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FManagedValue& other) const { return memcmp(this, &other, sizeof(FManagedValue)) == 0; }
	bool operator!=(const FManagedValue& other) const { return !(*this == other); }
	bool operator<(const FManagedValue& other) const { return memcmp(this, &other, sizeof(FManagedValue)) < 0; }
};

// ScriptStruct IpDrv.McpManagedValueManagerBase.ManagedValueSaveSlot
// 0x0030
struct FManagedValueSaveSlot
{
	class FString                                      OwningMcpId;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SaveSlot;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FManagedValue>                 Values;                                        // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FManagedValueSaveSlot& other) const { return memcmp(this, &other, sizeof(FManagedValueSaveSlot)) == 0; }
	bool operator!=(const FManagedValueSaveSlot& other) const { return !(*this == other); }
	bool operator<(const FManagedValueSaveSlot& other) const { return memcmp(this, &other, sizeof(FManagedValueSaveSlot)) < 0; }
};

// ScriptStruct IpDrv.McpManagedValueManager.SaveSlotRequestState
// 0x0028
struct UMcpManagedValueManager_FSaveSlotRequestState
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SaveSlot;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       Request;                                       // 0x0020 (0x0008) [0x0000000000000000]               

	bool operator==(const UMcpManagedValueManager_FSaveSlotRequestState& other) const { return memcmp(this, &other, sizeof(UMcpManagedValueManager_FSaveSlotRequestState)) == 0; }
	bool operator!=(const UMcpManagedValueManager_FSaveSlotRequestState& other) const { return !(*this == other); }
	bool operator<(const UMcpManagedValueManager_FSaveSlotRequestState& other) const { return memcmp(this, &other, sizeof(UMcpManagedValueManager_FSaveSlotRequestState)) < 0; }
};

// ScriptStruct IpDrv.McpManagedValueManager.ValueRequestState
// 0x0008 (0x0028 - 0x0030)
struct FValueRequestState : UMcpManagedValueManager_FSaveSlotRequestState
{
	class FName                                        ValueId;                                       // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FValueRequestState& other) const { return memcmp(this, &other, sizeof(FValueRequestState)) == 0; }
	bool operator!=(const FValueRequestState& other) const { return !(*this == other); }
	bool operator<(const FValueRequestState& other) const { return memcmp(this, &other, sizeof(FValueRequestState)) < 0; }
};

// ScriptStruct IpDrv.McpMessageBase.McpMessage
// 0x0061
struct FMcpMessage
{
	class FString                                      MessageId;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ToUniqueUserId;                                // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      FromUniqueUserId;                              // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      FromFriendlyName;                              // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      MessageType;                                   // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ValidUntil;                                    // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMcpMessageCompressionType                         MessageCompressionType;                        // 0x0060 (0x0001) [0x0000000000000000]               

	bool operator==(const FMcpMessage& other) const { return memcmp(this, &other, sizeof(FMcpMessage)) == 0; }
	bool operator!=(const FMcpMessage& other) const { return !(*this == other); }
	bool operator<(const FMcpMessage& other) const { return memcmp(this, &other, sizeof(FMcpMessage)) < 0; }
};

// ScriptStruct IpDrv.McpMessageBase.McpMessageList
// 0x0020
struct FMcpMessageList
{
	class FString                                      ToUniqueUserId;                                // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpMessage>                   Messages;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpMessageList& other) const { return memcmp(this, &other, sizeof(FMcpMessageList)) == 0; }
	bool operator!=(const FMcpMessageList& other) const { return !(*this == other); }
	bool operator<(const FMcpMessageList& other) const { return memcmp(this, &other, sizeof(FMcpMessageList)) < 0; }
};

// ScriptStruct IpDrv.McpMessageBase.McpMessageContents
// 0x0020
struct FMcpMessageContents
{
	class FString                                      MessageId;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              MessageContents;                               // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpMessageContents& other) const { return memcmp(this, &other, sizeof(FMcpMessageContents)) == 0; }
	bool operator!=(const FMcpMessageContents& other) const { return !(*this == other); }
	bool operator<(const FMcpMessageContents& other) const { return memcmp(this, &other, sizeof(FMcpMessageContents)) < 0; }
};

// ScriptStruct IpDrv.McpMessageManager.McpCompressMessageRequest
// 0x0038
struct FMcpCompressMessageRequest
{
	class TArray<uint8_t>                              SourceBuffer;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              DestBuffer;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            OutCompressedSize;                             // 0x0020 (0x0004) [0x0000000000000000]               
	class UHttpRequestInterface*                       Request;                                       // 0x0028 (0x0008) [0x0000000000000000]               
	struct FPointer                                    CompressionWorker;                             // 0x0030 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FMcpCompressMessageRequest& other) const { return memcmp(this, &other, sizeof(FMcpCompressMessageRequest)) == 0; }
	bool operator!=(const FMcpCompressMessageRequest& other) const { return !(*this == other); }
	bool operator<(const FMcpCompressMessageRequest& other) const { return memcmp(this, &other, sizeof(FMcpCompressMessageRequest)) < 0; }
};

// ScriptStruct IpDrv.McpMessageManager.McpUncompressMessageRequest
// 0x0040
struct FMcpUncompressMessageRequest
{
	class FString                                      MessageId;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              SourceBuffer;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              DestBuffer;                                    // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            OutUncompressedSize;                           // 0x0030 (0x0004) [0x0000000000000000]               
	struct FPointer                                    UncompressionWorker;                           // 0x0038 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FMcpUncompressMessageRequest& other) const { return memcmp(this, &other, sizeof(FMcpUncompressMessageRequest)) == 0; }
	bool operator!=(const FMcpUncompressMessageRequest& other) const { return !(*this == other); }
	bool operator<(const FMcpUncompressMessageRequest& other) const { return memcmp(this, &other, sizeof(FMcpUncompressMessageRequest)) < 0; }
};

// ScriptStruct IpDrv.McpUserCloudFileDownload.McpUserCloudFileInfo
// 0x0034 (0x0034 - 0x0068)
struct FMcpUserCloudFileInfo : FEmsFile
{
	class FString                                      CreationDate;                                  // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LastUpdateDate;                                // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      CompressionType;                               // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpUserCloudFileInfo& other) const { return memcmp(this, &other, sizeof(FMcpUserCloudFileInfo)) == 0; }
	bool operator!=(const FMcpUserCloudFileInfo& other) const { return !(*this == other); }
	bool operator<(const FMcpUserCloudFileInfo& other) const { return memcmp(this, &other, sizeof(FMcpUserCloudFileInfo)) < 0; }
};

// ScriptStruct IpDrv.McpUserCloudFileDownload.McpUserCloudFilesEntry
// 0x0038
struct FMcpUserCloudFilesEntry
{
	class FString                                      UserId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FTitleFileWeb>                 DownloadedFiles;                               // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpUserCloudFileInfo>         EnumeratedFiles;                               // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       HTTPRequestEnumerateFiles;                     // 0x0030 (0x0008) [0x0000000000000000]               

	bool operator==(const FMcpUserCloudFilesEntry& other) const { return memcmp(this, &other, sizeof(FMcpUserCloudFilesEntry)) == 0; }
	bool operator!=(const FMcpUserCloudFilesEntry& other) const { return !(*this == other); }
	bool operator<(const FMcpUserCloudFilesEntry& other) const { return memcmp(this, &other, sizeof(FMcpUserCloudFilesEntry)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryBase.McpInventoryItemAttribute
// 0x0014
struct FMcpInventoryItemAttribute
{
	class FString                                      AttributeId;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Value;                                         // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FMcpInventoryItemAttribute& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItemAttribute)) == 0; }
	bool operator!=(const FMcpInventoryItemAttribute& other) const { return !(*this == other); }
	bool operator<(const FMcpInventoryItemAttribute& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItemAttribute)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryBase.McpInventoryItem
// 0x0050
struct FMcpInventoryItem
{
	class FString                                      InstanceItemId;                                // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GlobalItemId;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Quantity;                                      // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            QuantityIAP;                                   // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              Scalar;                                        // 0x0028 (0x0004) [0x0000000000000000]               
	class FString                                      LastUpdateTime;                                // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpInventoryItemAttribute>    Attributes;                                    // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpInventoryItem& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItem)) == 0; }
	bool operator!=(const FMcpInventoryItem& other) const { return !(*this == other); }
	bool operator<(const FMcpInventoryItem& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItem)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryBase.McpInventoryItemContainer
// 0x0014
struct FMcpInventoryItemContainer
{
	class FString                                      GlobalItemId;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Quantity;                                      // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FMcpInventoryItemContainer& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItemContainer)) == 0; }
	bool operator!=(const FMcpInventoryItemContainer& other) const { return !(*this == other); }
	bool operator<(const FMcpInventoryItemContainer& other) const { return memcmp(this, &other, sizeof(FMcpInventoryItemContainer)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryBase.McpInventorySaveSlot
// 0x0030
struct FMcpInventorySaveSlot
{
	class FString                                      OwningMcpId;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SaveSlotId;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FMcpInventoryItem>             Items;                                         // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FMcpInventorySaveSlot& other) const { return memcmp(this, &other, sizeof(FMcpInventorySaveSlot)) == 0; }
	bool operator!=(const FMcpInventorySaveSlot& other) const { return !(*this == other); }
	bool operator<(const FMcpInventorySaveSlot& other) const { return memcmp(this, &other, sizeof(FMcpInventorySaveSlot)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryManager.SaveSlotRequestState
// 0x0028
struct UMcpUserInventoryManager_FSaveSlotRequestState
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SaveSlotId;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       Request;                                       // 0x0020 (0x0008) [0x0000000000000000]               

	bool operator==(const UMcpUserInventoryManager_FSaveSlotRequestState& other) const { return memcmp(this, &other, sizeof(UMcpUserInventoryManager_FSaveSlotRequestState)) == 0; }
	bool operator!=(const UMcpUserInventoryManager_FSaveSlotRequestState& other) const { return !(*this == other); }
	bool operator<(const UMcpUserInventoryManager_FSaveSlotRequestState& other) const { return memcmp(this, &other, sizeof(UMcpUserInventoryManager_FSaveSlotRequestState)) < 0; }
};

// ScriptStruct IpDrv.McpUserInventoryManager.InventoryItemRequestState
// 0x0010 (0x0028 - 0x0038)
struct FInventoryItemRequestState : UMcpUserInventoryManager_FSaveSlotRequestState
{
	class FString                                      ItemID;                                        // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FInventoryItemRequestState& other) const { return memcmp(this, &other, sizeof(FInventoryItemRequestState)) == 0; }
	bool operator!=(const FInventoryItemRequestState& other) const { return !(*this == other); }
	bool operator<(const FInventoryItemRequestState& other) const { return memcmp(this, &other, sizeof(FInventoryItemRequestState)) < 0; }
};

// ScriptStruct IpDrv.McpUserManagerBase.McpUserStatus
// 0x0068
struct FMcpUserStatus
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SecretKey;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Ticket;                                        // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      UDID;                                          // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      RegisteredDate;                                // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LastActiveDate;                                // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            DaysInactive;                                  // 0x0060 (0x0004) [0x0000000000000000]               
	uint32_t                                           bIsBanned : 1;                                 // 0x0064 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const FMcpUserStatus& other) const { return memcmp(this, &other, sizeof(FMcpUserStatus)) == 0; }
	bool operator!=(const FMcpUserStatus& other) const { return !(*this == other); }
	bool operator<(const FMcpUserStatus& other) const { return memcmp(this, &other, sizeof(FMcpUserStatus)) < 0; }
};

// ScriptStruct IpDrv.McpUserManager.UserRequest
// 0x0018
struct FUserRequest
{
	class FString                                      McpId;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UHttpRequestInterface*                       Request;                                       // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FUserRequest& other) const { return memcmp(this, &other, sizeof(FUserRequest)) == 0; }
	bool operator!=(const FUserRequest& other) const { return !(*this == other); }
	bool operator<(const FUserRequest& other) const { return memcmp(this, &other, sizeof(FUserRequest)) < 0; }
};

// ScriptStruct IpDrv.MeshBeacon.ConnectionBandwidthStats
// 0x000C
struct FConnectionBandwidthStats
{
	int32_t                                            UpstreamRate;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            DownstreamRate;                                // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            RoundtripLatency;                              // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FConnectionBandwidthStats& other) const { return memcmp(this, &other, sizeof(FConnectionBandwidthStats)) == 0; }
	bool operator!=(const FConnectionBandwidthStats& other) const { return !(*this == other); }
	bool operator<(const FConnectionBandwidthStats& other) const { return memcmp(this, &other, sizeof(FConnectionBandwidthStats)) < 0; }
};

// ScriptStruct IpDrv.MeshBeacon.PlayerMember
// 0x0050
struct FPlayerMember
{
	int32_t                                            TeamNum;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Skill;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                NetId;                                         // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlayerMember& other) const { return memcmp(this, &other, sizeof(FPlayerMember)) == 0; }
	bool operator!=(const FPlayerMember& other) const { return !(*this == other); }
	bool operator<(const FPlayerMember& other) const { return memcmp(this, &other, sizeof(FPlayerMember)) < 0; }
};

// ScriptStruct IpDrv.MeshBeaconClient.ClientBandwidthTestData
// 0x0014
struct FClientBandwidthTestData
{
	EMeshBeaconBandwidthTestType                       TestType;                                      // 0x0000 (0x0001) [0x0000000000000000]               
	EMeshBeaconBandwidthTestState                      CurrentState;                                  // 0x0001 (0x0001) [0x0000000000000000]               
	int32_t                                            NumBytesToSendTotal;                           // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            NumBytesSentTotal;                             // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            NumBytesSentLast;                              // 0x000C (0x0004) [0x0000000000000000]               
	float                                              ElapsedTestTime;                               // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientBandwidthTestData& other) const { return memcmp(this, &other, sizeof(FClientBandwidthTestData)) == 0; }
	bool operator!=(const FClientBandwidthTestData& other) const { return !(*this == other); }
	bool operator<(const FClientBandwidthTestData& other) const { return memcmp(this, &other, sizeof(FClientBandwidthTestData)) < 0; }
};

// ScriptStruct IpDrv.MeshBeaconClient.ClientConnectionRequest
// 0x006C
struct FClientConnectionRequest
{
	struct FUniqueNetId                                PlayerNetId;                                   // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	ENATType                                           NatType;                                       // 0x0048 (0x0001) [0x0000000000000000]               
	uint32_t                                           bCanHostVs : 1;                                // 0x004C (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              GoodHostRatio;                                 // 0x0050 (0x0004) [0x0000000000000000]               
	class TArray<struct FConnectionBandwidthStats>     BandwidthHistory;                              // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            MinutesSinceLastTest;                          // 0x0068 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientConnectionRequest& other) const { return memcmp(this, &other, sizeof(FClientConnectionRequest)) == 0; }
	bool operator!=(const FClientConnectionRequest& other) const { return !(*this == other); }
	bool operator<(const FClientConnectionRequest& other) const { return memcmp(this, &other, sizeof(FClientConnectionRequest)) < 0; }
};

// ScriptStruct IpDrv.MeshBeaconHost.ClientConnectionBandwidthTestData
// 0x002C
struct FClientConnectionBandwidthTestData
{
	EMeshBeaconBandwidthTestState                      CurrentState;                                  // 0x0000 (0x0001) [0x0000000000000000]               
	EMeshBeaconBandwidthTestType                       TestType;                                      // 0x0001 (0x0001) [0x0000000000000000]               
	int32_t                                            BytesTotalNeeded;                              // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            BytesReceived;                                 // 0x0008 (0x0004) [0x0000000000000000]               
	struct FDouble                                     RequestTestStartTime;                          // 0x0010 (0x0008) [0x0000000000000000]               
	struct FDouble                                     TestStartTime;                                 // 0x0018 (0x0008) [0x0000000000000000]               
	struct FConnectionBandwidthStats                   BandwidthStats;                                // 0x0020 (0x000C) [0x0000000000000000]               

	bool operator==(const FClientConnectionBandwidthTestData& other) const { return memcmp(this, &other, sizeof(FClientConnectionBandwidthTestData)) == 0; }
	bool operator!=(const FClientConnectionBandwidthTestData& other) const { return !(*this == other); }
	bool operator<(const FClientConnectionBandwidthTestData& other) const { return memcmp(this, &other, sizeof(FClientConnectionBandwidthTestData)) < 0; }
};

// ScriptStruct IpDrv.MeshBeaconHost.ClientMeshBeaconConnection
// 0x00B4
struct FClientMeshBeaconConnection
{
	struct FUniqueNetId                                PlayerNetId;                                   // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              ElapsedHeartbeatTime;                          // 0x0048 (0x0004) [0x0000000000000000]               
	struct FPointer                                    Socket;                                        // 0x0050 (0x0008) [0x0000000000003000] (CPF_Native | CPF_Transient)
	uint32_t                                           bConnectionAccepted : 1;                       // 0x0058 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FClientConnectionBandwidthTestData          BandwidthTest;                                 // 0x0060 (0x0030) [0x0000000000000000]               
	ENATType                                           NatType;                                       // 0x0090 (0x0001) [0x0000000000000000]               
	uint32_t                                           bCanHostVs : 1;                                // 0x0094 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              GoodHostRatio;                                 // 0x0098 (0x0004) [0x0000000000000000]               
	class TArray<struct FConnectionBandwidthStats>     BandwidthHistory;                              // 0x00A0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            MinutesSinceLastTest;                          // 0x00B0 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientMeshBeaconConnection& other) const { return memcmp(this, &other, sizeof(FClientMeshBeaconConnection)) == 0; }
	bool operator!=(const FClientMeshBeaconConnection& other) const { return !(*this == other); }
	bool operator<(const FClientMeshBeaconConnection& other) const { return memcmp(this, &other, sizeof(FClientMeshBeaconConnection)) < 0; }
};

// ScriptStruct IpDrv.OnlineAuthInterfaceImpl.AuthCodeRequest
// 0x0064
struct FAuthCodeRequest
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             Callback;                                      // 0x0048 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            RequestID;                                     // 0x0060 (0x0004) [0x0000000000000000]               

	bool operator==(const FAuthCodeRequest& other) const { return memcmp(this, &other, sizeof(FAuthCodeRequest)) == 0; }
	bool operator!=(const FAuthCodeRequest& other) const { return !(*this == other); }
	bool operator<(const FAuthCodeRequest& other) const { return memcmp(this, &other, sizeof(FAuthCodeRequest)) < 0; }
};

// ScriptStruct IpDrv.OnlineEventsInterfaceMcp.EventUploadConfig
// 0x0020
struct FEventUploadConfig
{
	EEventUploadType                                   UploadType;                                    // 0x0000 (0x0001) [0x0000000000000002] (CPF_Const)   
	class FString                                      UploadUrl;                                     // 0x0008 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	float                                              Timeout;                                       // 0x0018 (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bUseCompression : 1;                           // 0x001C (0x0004) [0x0000000000000002] [0x100000001] (CPF_Const)

	bool operator==(const FEventUploadConfig& other) const { return memcmp(this, &other, sizeof(FEventUploadConfig)) == 0; }
	bool operator!=(const FEventUploadConfig& other) const { return !(*this == other); }
	bool operator<(const FEventUploadConfig& other) const { return memcmp(this, &other, sizeof(FEventUploadConfig)) < 0; }
};

// ScriptStruct IpDrv.OnlineNewsInterfaceMcp.NewsCacheEntry
// 0x0038
struct FNewsCacheEntry
{
	class FString                                      NewsUrl;                                       // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EOnlineEnumerationReadState                        ReadState;                                     // 0x0010 (0x0001) [0x0000000000000000]               
	EOnlineNewsType                                    NewsType;                                      // 0x0011 (0x0001) [0x0000000000000002] (CPF_Const)   
	class FString                                      NewsItem;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              Timeout;                                       // 0x0028 (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bIsUnicode : 1;                                // 0x002C (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	struct FPointer                                    HttpDownloader;                                // 0x0030 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FNewsCacheEntry& other) const { return memcmp(this, &other, sizeof(FNewsCacheEntry)) == 0; }
	bool operator!=(const FNewsCacheEntry& other) const { return !(*this == other); }
	bool operator<(const FNewsCacheEntry& other) const { return memcmp(this, &other, sizeof(FNewsCacheEntry)) < 0; }
};

// ScriptStruct IpDrv.OnlinePlaylistManager.ConfiguredGameSetting
// 0x0030
struct FConfiguredGameSetting
{
	int32_t                                            GameSettingId;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      GameSettingsClassName;                         // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      URL;                                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UOnlineGameSettings*                         GameSettings;                                  // 0x0028 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FConfiguredGameSetting& other) const { return memcmp(this, &other, sizeof(FConfiguredGameSetting)) == 0; }
	bool operator!=(const FConfiguredGameSetting& other) const { return !(*this == other); }
	bool operator<(const FConfiguredGameSetting& other) const { return memcmp(this, &other, sizeof(FConfiguredGameSetting)) < 0; }
};

// ScriptStruct IpDrv.OnlinePlaylistManager.Playlist
// 0x0080
struct FPlaylist
{
	class TArray<struct FConfiguredGameSetting>        ConfiguredGames;                               // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            PlaylistId;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            LoadBalanceId;                                 // 0x0014 (0x0004) [0x0000000000000000]               
	class FString                                      LocalizationString;                            // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              ContentIds;                                    // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TeamSize;                                      // 0x0038 (0x0004) [0x0000000000000000]               
	int32_t                                            TeamCount;                                     // 0x003C (0x0004) [0x0000000000000000]               
	int32_t                                            MaxPartySize;                                  // 0x0040 (0x0004) [0x0000000000000000]               
	class FString                                      Name;                                          // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      URL;                                           // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            MatchType;                                     // 0x0068 (0x0004) [0x0000000000000000]               
	uint32_t                                           bDisableDedicatedServerSearches : 1;           // 0x006C (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<class FName>                          MapCycle;                                      // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlaylist& other) const { return memcmp(this, &other, sizeof(FPlaylist)) == 0; }
	bool operator!=(const FPlaylist& other) const { return !(*this == other); }
	bool operator<(const FPlaylist& other) const { return memcmp(this, &other, sizeof(FPlaylist)) < 0; }
};

// ScriptStruct IpDrv.OnlinePlaylistManager.PlaylistPopulation
// 0x000C
struct FPlaylistPopulation
{
	int32_t                                            PlaylistId;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            WorldwideTotal;                                // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            RegionTotal;                                   // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPlaylistPopulation& other) const { return memcmp(this, &other, sizeof(FPlaylistPopulation)) == 0; }
	bool operator!=(const FPlaylistPopulation& other) const { return !(*this == other); }
	bool operator<(const FPlaylistPopulation& other) const { return memcmp(this, &other, sizeof(FPlaylistPopulation)) < 0; }
};

// ScriptStruct IpDrv.OnlineSubsystemCommonImpl.SanitizeCallbackData
// 0x0030
struct FSanitizeCallbackData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Comment;                                       // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSanitizeCallbackData& other) const { return memcmp(this, &other, sizeof(FSanitizeCallbackData)) == 0; }
	bool operator!=(const FSanitizeCallbackData& other) const { return !(*this == other); }
	bool operator<(const FSanitizeCallbackData& other) const { return memcmp(this, &other, sizeof(FSanitizeCallbackData)) < 0; }
};

// ScriptStruct IpDrv.OnlineTitleFileDownloadMcp.TitleFileMcp
// 0x0008 (0x0028 - 0x0030)
struct FTitleFileMcp : FTitleFile
{
	struct FPointer                                    HttpDownloader;                                // 0x0028 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FTitleFileMcp& other) const { return memcmp(this, &other, sizeof(FTitleFileMcp)) == 0; }
	bool operator!=(const FTitleFileMcp& other) const { return !(*this == other); }
	bool operator<(const FTitleFileMcp& other) const { return memcmp(this, &other, sizeof(FTitleFileMcp)) < 0; }
};

// ScriptStruct IpDrv.PartyBeacon.PlayerReservation
// 0x0064
struct FPlayerReservation
{
	struct FUniqueNetId                                NetId;                                         // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Skill;                                         // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            XpLevel;                                       // 0x004C (0x0004) [0x0000000000000000]               
	struct FDouble                                     Mu;                                            // 0x0050 (0x0008) [0x0000000000000000]               
	struct FDouble                                     Sigma;                                         // 0x0058 (0x0008) [0x0000000000000000]               
	float                                              ElapsedSessionTime;                            // 0x0060 (0x0004) [0x0000000000000000]               

	bool operator==(const FPlayerReservation& other) const { return memcmp(this, &other, sizeof(FPlayerReservation)) == 0; }
	bool operator!=(const FPlayerReservation& other) const { return !(*this == other); }
	bool operator<(const FPlayerReservation& other) const { return memcmp(this, &other, sizeof(FPlayerReservation)) < 0; }
};

// ScriptStruct IpDrv.PartyBeacon.PartyReservation
// 0x0060
struct FPartyReservation
{
	int32_t                                            TeamNum;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                PartyLeader;                                   // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FPlayerReservation>            PartyMembers;                                  // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPartyReservation& other) const { return memcmp(this, &other, sizeof(FPartyReservation)) == 0; }
	bool operator!=(const FPartyReservation& other) const { return !(*this == other); }
	bool operator<(const FPartyReservation& other) const { return memcmp(this, &other, sizeof(FPartyReservation)) < 0; }
};

// ScriptStruct IpDrv.PartyBeaconHost.ClientBeaconConnection
// 0x0058
struct FClientBeaconConnection
{
	struct FUniqueNetId                                PartyLeader;                                   // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              ElapsedHeartbeatTime;                          // 0x0048 (0x0004) [0x0000000000000000]               
	struct FPointer                                    Socket;                                        // 0x0050 (0x0008) [0x0000000000003000] (CPF_Native | CPF_Transient)

	bool operator==(const FClientBeaconConnection& other) const { return memcmp(this, &other, sizeof(FClientBeaconConnection)) == 0; }
	bool operator!=(const FClientBeaconConnection& other) const { return !(*this == other); }
	bool operator<(const FClientBeaconConnection& other) const { return memcmp(this, &other, sizeof(FClientBeaconConnection)) < 0; }
};

// ScriptStruct IpDrv.TitleFileDownloadCache.TitleFileCacheEntry
// 0x0030 (0x0028 - 0x0058)
struct FTitleFileCacheEntry : FTitleFile
{
	class FString                                      LogicalName;                                   // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Hash;                                          // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	ETitleFileFileOp                                   FileOp;                                        // 0x0048 (0x0001) [0x0000000000000000]               
	struct FPointer                                    Ar;                                            // 0x0050 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FTitleFileCacheEntry& other) const { return memcmp(this, &other, sizeof(FTitleFileCacheEntry)) == 0; }
	bool operator!=(const FTitleFileCacheEntry& other) const { return !(*this == other); }
	bool operator<(const FTitleFileCacheEntry& other) const { return memcmp(this, &other, sizeof(FTitleFileCacheEntry)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
