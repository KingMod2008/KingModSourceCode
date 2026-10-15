/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: ProjectX\ProjectX_enums.hpp
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
# Enums
# ========================================================================================= #
*/

// Enum ProjectX._Types_X.EChatChannel
enum class EChatChannel : uint8_t
{
	EChatChannel_Match                                 = 0,
	EChatChannel_Team                                  = 1,
	EChatChannel_Party                                 = 2,
	EChatChannel_Individual                            = 3,
	EChatChannel_END                                   = 4
};

// Enum ProjectX._Types_X.EBanType
enum class EBanType : uint8_t
{
	BanType_None                                       = 0,
	BanType_Auth                                       = 1,
	BanType_Chat                                       = 2,
	BanType_Voice                                      = 3,
	BanType_Club                                       = 4,
	BanType_Trade                                      = 5,
	BanType_QuitPenalty                                = 6,
	BanType_Social                                     = 7,
	BanType_END                                        = 8
};

// Enum ProjectX._Types_X.ESeverityType
enum class ESeverityType : uint8_t
{
	SeverityType_None                                  = 0,
	SeverityType_Low                                   = 1,
	SeverityType_Medium                                = 2,
	SeverityType_High                                  = 3,
	SeverityType_END                                   = 4
};

// Enum ProjectX._Types_X.ENewsInteractionType
enum class ENewsInteractionType : uint8_t
{
	NIT_VIEW                                           = 0,
	NIT_ENGAGED                                        = 1,
	NIT_END                                            = 2
};

// Enum ProjectX._Types_X.EConsoleQualityMode
enum class EConsoleQualityMode : uint8_t
{
	ConsoleQualityMode_Performance                     = 0,
	ConsoleQualityMode_Quality                         = 1,
	ConsoleQualityMode_END                             = 2
};

// Enum ProjectX._Types_X.EReservationStatus
enum class EReservationStatus : uint8_t
{
	ReservationStatus_None                             = 0,
	ReservationStatus_Reserved                         = 1,
	ReservationStatus_Joining                          = 2,
	ReservationStatus_InGame                           = 3,
	ReservationStatus_END                              = 4
};

// Enum ProjectX._Types_X.EPsyNetEnvironment
enum class EPsyNetEnvironment : uint8_t
{
	EPE_Unset                                          = 0,
	EPE_Environment1                                   = 1,
	EPE_Environment2                                   = 2,
	EPE_Environment3                                   = 3,
	EPE_Environment4                                   = 4,
	EPE_Environment5                                   = 5,
	EPE_END                                            = 6
};

// Enum ProjectX._Types_X.EClubBadge
enum class EClubBadge : uint8_t
{
	ClubBadge_None                                     = 0,
	ClubBadge_Tier1                                    = 1,
	ClubBadge_Tier2                                    = 2,
	ClubBadge_Tier3                                    = 3,
	ClubBadge_END                                      = 4
};

// Enum ProjectX._Types_X.EJoinMatchType
enum class EJoinMatchType : uint8_t
{
	JMT_Public                                         = 0,
	JMT_Private                                        = 1,
	JMT_END                                            = 2
};

// Enum ProjectX._Types_X.EDatabaseEnvironment
enum class EDatabaseEnvironment : uint8_t
{
	DBE_DevLocal                                       = 0,
	DBE_Dev                                            = 1,
	DBE_Test                                           = 2,
	DBE_Production                                     = 3,
	DBE_END                                            = 4
};

// Enum ProjectX._Types_X.EAxisSign
enum class EAxisSign : uint8_t
{
	AxisSign_None                                      = 0,
	AxisSign_Positive                                  = 1,
	AxisSign_Negative                                  = 2,
	AxisSign_END                                       = 3
};

// Enum ProjectX._Types_X.EButtonPressType
enum class EButtonPressType : uint8_t
{
	BPT_Normal                                         = 0,
	BPT_Tap                                            = 1,
	BPT_Hold                                           = 2,
	BPT_DoubleTap                                      = 3,
	BPT_Toggle                                         = 4,
	BPT_END                                            = 5
};

// Enum ProjectX._Types_X.ERemappable
enum class ERemappable : uint8_t
{
	Remappable_All                                     = 0,
	Remappable_Key                                     = 1,
	Remappable_Axis                                    = 2,
	Remappable_KeyTriggerAxis                          = 3,
	Remappable_None                                    = 4,
	Remappable_END                                     = 5
};

// Enum ProjectX._Types_X.ETrackingPermissionType
enum class ETrackingPermissionType : uint8_t
{
	Tracking_Marketing                                 = 0,
	Tracking_Functional                                = 1,
	Tracking_Experience                                = 2,
	Tracking_END                                       = 3
};

// Enum ProjectX._Types_X.EChatPermissionLevel
enum class EChatPermissionLevel : uint8_t
{
	CPL_Everybody                                      = 0,
	CPL_FriendsAndTeam                                 = 1,
	CPL_Friends                                        = 2,
	CPL_Nobody                                         = 3,
	CPL_END                                            = 4
};

// Enum ProjectX._Types_X.ETradePermissionLevel
enum class ETradePermissionLevel : uint8_t
{
	TPL_Everybody                                      = 0,
	TPL_FriendsAndParty                                = 1,
	TPL_Friends                                        = 2,
	TPL_Nobody                                         = 3,
	TPL_END                                            = 4
};

// Enum ProjectX._Types_X.EChatReportingLevel
enum class EChatReportingLevel : uint8_t
{
	VRP_OffWhenPossible                                = 0,
	VRP_Always                                         = 1,
	VRP_END                                            = 2
};

// Enum ProjectX._Types_X.EPartyMatchmakingRestriction
enum class EPartyMatchmakingRestriction : uint8_t
{
	PMR_NotOriginalAppOwner                            = 0,
	PMR_PendingLicenseAgreement                        = 1,
	PMR_InMainMenu                                     = 2,
	PMR_NotLoggedInPsyNet                              = 3,
	PMR_END                                            = 4
};

// Enum ProjectX._Types_X.EClubInviteEventType
enum class EClubInviteEventType : uint8_t
{
	CIET_Accept                                        = 0,
	CIET_Reject                                        = 1,
	CIET_Send                                          = 2,
	CIET_END                                           = 3
};

// Enum ProjectX._Types_X.EClubMemberAction
enum class EClubMemberAction : uint8_t
{
	ClubMemberAction_RemoveMember                      = 0,
	ClubMemberAction_SetClubOwner                      = 1,
	ClubMemberAction_SetClubManager                    = 2,
	ClubMemberAction_RemoveClubManager                 = 3,
	ClubMemberAction_InviteParty                       = 4,
	ClubMemberAction_RequestJoinParty                  = 5,
	ClubMemberAction_ViewProfile                       = 6,
	ClubMemberAction_BlockMember                       = 7,
	ClubMemberAction_UnblockMember                     = 8,
	ClubMemberAction_AddEpicFriend                     = 9,
	ClubMemberAction_RemoveEpicFriend                  = 10,
	ClubMemberAction_ReportMember                      = 11,
	ClubMemberAction_END                               = 12
};

// Enum ProjectX._Types_X.EClubRole
enum class EClubRole : uint8_t
{
	ClubRole_Member                                    = 0,
	ClubRole_Owner                                     = 1,
	ClubRole_Manager                                   = 2,
	ClubRole_None                                      = 3,
	ClubRole_END                                       = 4
};

// Enum ProjectX._Types_X.EOnlineStorageFiles
enum class EOnlineStorageFiles : uint8_t
{
	OSF_Save                                           = 0,
	OSF_Settings                                       = 1,
	OSF_END                                            = 2
};

// Enum ProjectX._Types_X.EOnlinePlayerPermission
enum class EOnlinePlayerPermission : uint8_t
{
	OPP_PrivateMatchAdmin                              = 0,
	OPP_SuperPrivateMatchAdmin                         = 1,
	OPP_AntiCheatExempt                                = 2,
	OPP_END                                            = 3
};

// Enum ProjectX._Types_X.EOnlinePlayerRole
enum class EOnlinePlayerRole : uint8_t
{
	OPR_PrivateMatchAdmin                              = 0,
	OPR_SuperPrivateMatchAdmin                         = 1,
	OPR_AntiCheatExempt                                = 2,
	OPR_END                                            = 3
};

// Enum ProjectX._Types_X.EConnectionType_X
enum class EConnectionType_X : uint8_t
{
	ConnectionType_Unknown                             = 0,
	ConnectionType_Wired                               = 1,
	ConnectionType_WiFi                                = 2,
	ConnectionType_Mixed                               = 3,
	ConnectionType_Docked                              = 4,
	ConnectionType_END                                 = 5
};

// Enum ProjectX.EpicLogin_X.AgeGateState
enum class EAgeGateState : uint8_t
{
	AGS_Unknown                                        = 0,
	AGS_Active                                         = 1,
	AGS_Complete                                       = 2,
	AGS_END                                            = 3
};

// Enum ProjectX.EpicLogin_X.ELoginMethod
enum class ELoginMethod : uint8_t
{
	LoginMethod_RefreshToken                           = 0,
	LoginMethod_PlatformAuthTicket                     = 1,
	LoginMethod_END                                    = 2
};

// Enum ProjectX.OnlineGameParty_X.PartyProcessingStatus
enum class EPartyProcessingStatus : uint8_t
{
	PPS_None                                           = 0,
	PPS_Create                                         = 1,
	PPS_Join                                           = 2,
	PPS_END                                            = 3
};

// Enum ProjectX.OnlineLegalTextEOS_X.ELegalSyncState
enum class ELegalSyncState : uint8_t
{
	LSS_NotStarted                                     = 0,
	LSS_Failed                                         = 1,
	LSS_InProgress                                     = 2,
	LSS_AcceptanceRequired                             = 3,
	LSS_Accepted                                       = 4,
	LSS_END                                            = 5
};

// Enum ProjectX.EncodeObject_X.EObjectEncoding
enum class EObjectEncoding : uint8_t
{
	OPSE_UObject                                       = 0,
	OPSE_Json                                          = 1,
	OPSE_END                                           = 2
};

// Enum ProjectX.WordFilterTypes_X.EWordFilterUsage
enum class EWordFilterUsage : uint8_t
{
	WordFilterUsage_PlayerName                         = 0,
	WordFilterUsage_TrainingName                       = 1,
	WordFilterUsage_LanServerName                      = 2,
	WordFilterUsage_CustomTeamName                     = 3,
	WordFilterUsage_TourName                           = 4,
	WordFilterUsage_TourTeamName                       = 5,
	WordFilterUsage_ClubName                           = 6,
	WordFilterUsage_ClubTag                            = 7,
	WordFilterUsage_ClubTagPlayerName                  = 8,
	WordFilterUsage_MatchChat                          = 9,
	WordFilterUsage_PartyChat                          = 10,
	WordFilterUsage_END                                = 11
};

// Enum ProjectX.RPC_X.ERPCPriority
enum class ERPCPriority : uint8_t
{
	RPC_Low                                            = 0,
	RPC_Medium                                         = 1,
	RPC_High                                           = 2,
	RPC_END                                            = 3
};

// Enum ProjectX.AnimNodeSeries_X.EAnimNodeSeriesChild
enum class EAnimNodeSeriesChild : uint8_t
{
	AnimNodeSeries_Idle                                = 0,
	AnimNodeSeries_Intro                               = 1,
	AnimNodeSeries_Loop                                = 2,
	AnimNodeSeries_Outro                               = 3,
	AnimNodeSeries_END                                 = 4
};

// Enum ProjectX.BlogTile_X.ELinkType
enum class ELinkType : uint8_t
{
	LinkType_None                                      = 0,
	LinkType_RocketPass                                = 1,
	LinkType_Event                                     = 2,
	LinkType_ESports                                   = 3,
	LinkType_Clubs                                     = 4,
	LinkType_END                                       = 5
};

// Enum ProjectX.ClanforgeReservation_X.EReserveState
enum class EReserveState : uint8_t
{
	ReserveState_Unitialized                           = 0,
	ReserveState_Unreserved                            = 1,
	ReserveState_Reserved                              = 2,
	ReserveState_END                                   = 3
};

// Enum ProjectX.ClubUtil_X.EClubColorChange
enum class EClubColorChange : uint8_t
{
	ClubColorChange_None                               = 0,
	ClubColorChange_SwapTeams                          = 1,
	ClubColorChange_SwapPrimaryAccent0                 = 2,
	ClubColorChange_SwapPrimaryAccent1                 = 3,
	ClubColorChange_SwapPrimaryAccent                  = 4,
	ClubColorChange_WhiteVsBlack                       = 5,
	ClubColorChange_Gray1                              = 6,
	ClubColorChange_END                                = 7
};

// Enum ProjectX.DynamicValue_X.EDynamicValueModType
enum class EDynamicValueModType : uint8_t
{
	ModType_Add                                        = 0,
	ModType_Multiply                                   = 1,
	ModType_MultiplyAdd                                = 2,
	ModType_Set                                        = 3,
	ModType_END                                        = 4
};

// Enum ProjectX.FXActor_X.EAttachActorLocationUnlockFlags
enum class EAttachActorLocationUnlockFlags : uint8_t
{
	EAALUF_None                                        = 0,
	EAALUF_X                                           = 1,
	EAALUF_Y                                           = 2,
	EAALUF_Z                                           = 3,
	EAALUF_END                                         = 4
};

// Enum ProjectX.FXActor_X.EFXComponentTarget
enum class EFXComponentTarget : uint8_t
{
	FXComponentTarget_All                              = 0,
	FXComponentTarget_Local                            = 1,
	FXComponentTarget_NonLocal                         = 2,
	FXComponentTarget_END                              = 3
};

// Enum ProjectX.FXActor_X.EFXLocality
enum class EFXLocality : uint8_t
{
	FXLocality_Controller                              = 0,
	FXLocality_AlwaysLocal                             = 1,
	FXLocality_NeverLocal                              = 2,
	FXLocality_END                                     = 3
};

// Enum ProjectX.FXActor_X.EFXComponentState
enum class EFXComponentState : uint8_t
{
	FXComponentState_Detached                          = 0,
	FXComponentState_Attached                          = 1,
	FXComponentState_PendingDetach                     = 2,
	FXComponentState_END                               = 3
};

// Enum ProjectX.FXActor_X.EFXOverrideAttachBehavior
enum class EFXOverrideAttachBehavior : uint8_t
{
	FXOverrideAttach_None                              = 0,
	FXOverrideAttach_Owner                             = 1,
	FXOverrideAttach_END                               = 2
};

// Enum ProjectX.FakeData_X.FakeDataEnum
enum class EFakeDataEnum : uint8_t
{
	FakeData                                           = 0,
	FakeData01                                         = 1,
	FakeData02                                         = 2,
	FakeData_Count                                     = 3,
	FakeData_END                                       = 4
};

// Enum ProjectX.GFxDataCallback_X.EDataCallbackType
enum class EDataCallbackType : uint8_t
{
	DataCallbackType_All                               = 0,
	DataCallbackType_Table                             = 1,
	DataCallbackType_Row                               = 2,
	DataCallbackType_Value                             = 3,
	DataCallbackType_END                               = 4
};

// Enum ProjectX.MaterialEffect_X.EMaterialEffectStage
enum class EMaterialEffectStage : uint8_t
{
	EFFECT_INACTIVE                                    = 0,
	EFFECT_FADE_IN                                     = 1,
	EFFECT_ACTIVE                                      = 2,
	EFFECT_FADE_OUT                                    = 3,
	EFFECT_END                                         = 4
};

// Enum ProjectX.OnlineGameDLC_X.DLCOwnershipState
enum class EDLCOwnershipState : uint8_t
{
	DLCOwnershipState_Unknown                          = 0,
	DLCOwnershipState_Owned                            = 1,
	DLCOwnershipState_NotOwned                         = 2,
	DLCOwnershipState_Error                            = 3,
	DLCOwnershipState_END                              = 4
};

// Enum ProjectX.OnlinePlayerRegionRestrictions_X.ERegionRestriction
enum class ERegionRestriction : uint8_t
{
	RegionRestriction_Unknown                          = 0,
	RegionRestriction_KeyCrate                         = 1,
	RegionRestriction_Trade                            = 2,
	RegionRestriction_KeyRocketPassTier                = 3,
	RegionRestriction_END                              = 4
};

// Enum ProjectX.PerCon_X.EPerConStatus
enum class EPerConStatus : uint8_t
{
	PerConStatus_Disabled                              = 0,
	PerConStatus_Enabled                               = 1,
	PerConStatus_END                                   = 2
};

// Enum ProjectX.RegionPing_X.RegionPingResult
enum class ERegionPingResult : uint8_t
{
	PingResult_NotUsable                               = 0,
	PingResult_UsingCache                              = 1,
	PingResult_UsingSuccessfulPing                     = 2,
	PingResult_END                                     = 3
};

// Enum ProjectX.RemoteAvatarPermissions_X.EAvatarRequestTryGetResult
enum class EAvatarRequestTryGetResult : uint8_t
{
	ARTGR_NotFound                                     = 0,
	ARTGR_False                                        = 1,
	ARTGR_True                                         = 2,
	ARTGR_Hidden                                       = 3,
	ARTGR_END                                          = 4
};

// Enum ProjectX.RemoteAvatarPermissions_X.EAvatarPermission
enum class EAvatarPermission : uint8_t
{
	AP_True                                            = 0,
	AP_False                                           = 1,
	AP_Hidden                                          = 2,
	AP_END                                             = 3
};

// Enum ProjectX.ReservationsPasswordMessage_X.EPasswordFailureReason
enum class EPasswordFailureReason : uint8_t
{
	PFR_Empty                                          = 0,
	PFR_Mismatch                                       = 1,
	PFR_END                                            = 2
};

// Enum ProjectX.RPC_ReportExploiter_X.EExploitType
enum class EExploitType : uint8_t
{
	ET_FakeProducts                                    = 0,
	ET_InvisibleCar                                    = 1,
	ET_MultipleSplitscreen                             = 2,
	ET_URLPrivateMatchInjection                        = 3,
	ET_END                                             = 4
};

// Enum ProjectX.ShakeComponent_X.EShakeReceiver
enum class EShakeReceiver : uint8_t
{
	ShakeReceiver_All                                  = 0,
	ShakeReceiver_Local                                = 1,
	ShakeReceiver_NonLocal                             = 2,
	ShakeReceiver_END                                  = 3
};

// Enum ProjectX.TcpConnection.EWebSocketState
enum class EWebSocketState : uint8_t
{
	WebSocketState_NotRequired                         = 0,
	WebSocketState_NeedsHandshake                      = 1,
	WebSocketState_Connected                           = 2,
	WebSocketState_END                                 = 3
};

// Enum ProjectX.TcpConnection.ETcpConnectionState
enum class ETcpConnectionState : uint8_t
{
	TcpConnectionState_Invalid                         = 0,
	TcpConnectionState_Connecting                      = 1,
	TcpConnectionState_Connected                       = 2,
	TcpConnectionState_Disconnected                    = 3,
	TcpConnectionState_END                             = 4
};

// Enum ProjectX.WebRequest_X.EWebRequestState
enum class EWebRequestState : uint8_t
{
	WebRequestState_PendingSend                        = 0,
	WebRequestState_PendingResponse                    = 1,
	WebRequestState_Success                            = 2,
	WebRequestState_Error                              = 3,
	WebRequestState_END                                = 4
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
