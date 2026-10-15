/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: TAGame\TAGame_enums.hpp
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

// Enum TAGame._Types_TA.ESettingsAutoUpdateReason
enum class ESettingsAutoUpdateReason : uint8_t
{
	SAUR_PartyJoin                                     = 0,
	SAUR_PartyLeave                                    = 1,
	SAUR_SplitScreenJoin                               = 2,
	SAUR_SplitScreenLeave                              = 3,
	SAUR_GenericUpdate                                 = 4,
	SAUR_END                                           = 5
};

// Enum TAGame._Types_TA.EProductQuality
enum class EProductQuality : uint8_t
{
	EPQ_Common                                         = 0,
	EPQ_Uncommon                                       = 1,
	EPQ_Rare                                           = 2,
	EPQ_VeryRare                                       = 3,
	EPQ_Import                                         = 4,
	EPQ_Exotic                                         = 5,
	EPQ_BlackMarket                                    = 6,
	EPQ_Premium                                        = 7,
	EPQ_Limited                                        = 8,
	EPQ_Legacy                                         = 9,
	EPQ_END                                            = 10
};

// Enum TAGame._Types_TA.EUnlockMethod
enum class EUnlockMethod : uint8_t
{
	UnlockMethod_Default                               = 0,
	UnlockMethod_Online                                = 1,
	UnlockMethod_DLC                                   = 2,
	UnlockMethod_Never                                 = 3,
	UnlockMethod_END                                   = 4
};

// Enum TAGame._Types_TA.EVoiceRoomType
enum class EVoiceRoomType : uint8_t
{
	VRT_Invalid                                        = 0,
	VRT_Match                                          = 1,
	VRT_Party                                          = 2,
	VRT_END                                            = 3
};

// Enum TAGame._Types_TA.EActiveVoiceLocation
enum class EActiveVoiceLocation : uint8_t
{
	AVL_MainMenu                                       = 0,
	AVL_LoadingScreen                                  = 1,
	AVL_OfflineMatch                                   = 2,
	AVL_OnlineMatch                                    = 3,
	AVL_END                                            = 4
};

// Enum TAGame._Types_TA.EVoiceInputMode
enum class EVoiceInputMode : uint8_t
{
	VIM_OpenMic                                        = 0,
	VIM_PushToTalk                                     = 1,
	VIM_ToggleMute                                     = 2,
	VIM_END                                            = 3
};

// Enum TAGame._Types_TA.EVoiceNotificationLevel
enum class EVoiceNotificationLevel : uint8_t
{
	VNL_None                                           = 0,
	VNL_Text                                           = 1,
	VNL_Match                                          = 2,
	VNL_TextMatch                                      = 3,
	VNL_MainMenu                                       = 4,
	VNL_TextMainMenu                                   = 5,
	VNL_MatchMainMenu                                  = 6,
	VNL_All                                            = 7,
	VNL_END                                            = 8
};

// Enum TAGame._Types_TA.EPackageSaveStatus
enum class EPackageSaveStatus : uint8_t
{
	PSS_Warning                                        = 0,
	PSS_Error                                          = 1,
	PSS_Success                                        = 2,
	PSS_END                                            = 3
};

// Enum TAGame._Types_TA.EMatchHistoryUI
enum class EMatchHistoryUI : uint8_t
{
	MatchHistoryUI_MatchHistoryTab                     = 0,
	MatchHistoryUI_SavedReplaysTab                     = 1,
	MatchHistoryUI_PostGame                            = 2,
	MatchHistoryUI_MidGameReplayMenu                   = 3,
	MatchHistoryUI_END                                 = 4
};

// Enum TAGame._Types_TA.EMatchHistoryNavigableButton
enum class EMatchHistoryNavigableButton : uint8_t
{
	MatchHistoryNavigableButton_ChangeTabButton        = 0,
	MatchHistoryNavigableButton_GoToSaveReplay         = 1,
	MatchHistoryNavigableButton_WatchReplay            = 2,
	MatchHistoryNavigableButton_END                    = 3
};

// Enum TAGame._Types_TA.ERequestResolvedStatus
enum class ERequestResolvedStatus : uint8_t
{
	ERequestResolvedStatus_Success                     = 0,
	ERequestResolvedStatus_FinalRetryFailed            = 1,
	ERequestResolvedStatus_FailureRetryInProgress      = 2,
	ERequestResolvedStatus_UpdatedByUser               = 3,
	ERequestResolvedStatus_END                         = 4
};

// Enum TAGame._Types_TA.ESpecialEventState
enum class ESpecialEventState : uint8_t
{
	SES_Inactive                                       = 0,
	SES_Active                                         = 1,
	SES_Redemption                                     = 2,
	SES_END                                            = 3
};

// Enum TAGame._Types_TA.EControlsVisibilityType
enum class EControlsVisibilityType : uint8_t
{
	ControlsVisibility_Visible                         = 0,
	ControlsVisibility_Hidden                          = 1,
	ControlsVisibility_FadeOut                         = 2,
	ControlsVisibility_END                             = 3
};

// Enum TAGame._Types_TA.ESkinType
enum class ESkinType : uint8_t
{
	EST_Default                                        = 0,
	EST_Animated                                       = 1,
	EST_AnimatedPrimaryOnly                            = 2,
	EST_NonAnimatedPrimaryOnly                         = 3,
	EST_END                                            = 4
};

// Enum TAGame._Types_TA.EInfectedType
enum class EInfectedType : uint8_t
{
	InfectedType_NotInfected                           = 0,
	InfectedType_NormalInfected                        = 1,
	InfectedType_SpecialInfected                       = 2,
	InfectedType_END                                   = 3
};

// Enum TAGame._Types_TA.ETAStatType
enum class ETAStatType : uint8_t
{
	StatType_Private                                   = 0,
	StatType_Unranked                                  = 1,
	StatType_Ranked                                    = 2,
	StatType_END                                       = 3
};

// Enum TAGame._Types_TA.EVisibleMMRPreference
enum class EVisibleMMRPreference : uint8_t
{
	VMP_None                                           = 0,
	VMP_MenuOnly                                       = 1,
	VMP_InGameOnly                                     = 2,
	VMP_Everywhere                                     = 3,
	VMP_END                                            = 4
};

// Enum TAGame._Types_TA.ECrossEntitlementStatus
enum class ECrossEntitlementStatus : uint8_t
{
	CES_None                                           = 0,
	CES_Pending                                        = 1,
	CES_Locked                                         = 2,
	CES_XEItem                                         = 3,
	CES_END                                            = 4
};

// Enum TAGame._Types_TA.ETieBreakDecision
enum class ETieBreakDecision : uint8_t
{
	TBD_None                                           = 0,
	TBD_Goals                                          = 1,
	TBD_Shots                                          = 2,
	TBD_CoinToss                                       = 3,
	TBD_END                                            = 4
};

// Enum TAGame._Types_TA.EChatValidationFailureReason
enum class EChatValidationFailureReason : uint8_t
{
	CVFR_MisconfiguredJWT                              = 0,
	CVFR_MissingKey                                    = 1,
	CVFR_BadSignature                                  = 2,
	CVFR_END                                           = 3
};

// Enum TAGame._Types_TA.EMainMenuBackground
enum class EMainMenuBackground : uint8_t
{
	MMBG_Default                                       = 0,
	MMBG_UtopiaSnow                                    = 1,
	MMBG_HauntedStation                                = 2,
	MMBG_Beach                                         = 3,
	MMBG_Beach_Night                                   = 4,
	MMBG_Halloween                                     = 5,
	MMBG_China                                         = 6,
	MMBG_ParkDay                                       = 7,
	MMBG_Music                                         = 8,
	MMBG_ThrowbackHockey                               = 9,
	MMBG_Circuit                                       = 10,
	MMBG_Outlaw                                        = 11,
	MMBG_Arc                                           = 12,
	MMBG_ParkSnowy                                     = 13,
	MMBG_TokyoToon                                     = 14,
	MMBG_UtopiaLux                                     = 15,
	MMBG_Street                                        = 16,
	MMBG_FireAndIce                                    = 17,
	MMBG_Oasis                                         = 18,
	MMBG_Vida                                          = 19,
	MMBG_TokyoHax                                      = 20,
	MMBG_EuroDusk                                      = 21,
	MMBG_AquaGrass                                     = 22,
	MMBG_BeachNightGrass                               = 23,
	MMBG_Woods                                         = 24,
	MMBG_WoodsNight                                    = 25,
	MMBG_TokyoArcade                                   = 26,
	MMBG_FutureUtopia                                  = 27,
	MMBG_Anniversary                                   = 28,
	MMBG_Mall                                          = 29,
	MMBG_Paris                                         = 30,
	MMBG_FuturaNight                                   = 31,
	MMBG_END                                           = 32
};

// Enum TAGame._Types_TA.EPersonaInfoOrigin
enum class EPersonaInfoOrigin : uint8_t
{
	PersonaOrigin_Platform                             = 0,
	PersonaOrigin_PsyNet                               = 1,
	PersonaOrigin_Epic                                 = 2,
	PersonaOrigin_All                                  = 3,
	PersonaOrigin_END                                  = 4
};

// Enum TAGame._Types_TA.EPresenceGroup
enum class EPresenceGroup : uint8_t
{
	EPG_Offline                                        = 0,
	EPG_Online                                         = 1,
	EPG_InGame                                         = 2,
	EPG_Friends                                        = 3,
	EPG_END                                            = 4
};

// Enum TAGame._Types_TA.EMatchTieBreaker
enum class EMatchTieBreaker : uint8_t
{
	MatchTieBreaker_FirstScore                         = 0,
	MatchTieBreaker_Random                             = 1,
	MatchTieBreaker_END                                = 2
};

// Enum TAGame._Types_TA.EMusicStingersSetting
enum class EMusicStingersSetting : uint8_t
{
	MusicStingers_Off                                  = 0,
	MusicStingers_MatchesOnly                          = 1,
	MusicStingers_AlwaysOn                             = 2,
	MusicStingers_END                                  = 3
};

// Enum TAGame._Types_TA.EAnonymizationTargets
enum class EAnonymizationTargets : uint8_t
{
	ToNobody                                           = 0,
	ToTeammates                                        = 1,
	ToOpponents                                        = 2,
	ToEveryone                                         = 3,
	EAnonymizationTargets_END                          = 4
};

// Enum TAGame._Types_TA.ENameplateMode
enum class ENameplateMode : uint8_t
{
	NameplateMode_DistanceFade                         = 0,
	NameplateMode_AlwaysVisible                        = 1,
	NameplateMode_Simplified                           = 2,
	NameplateMode_END                                  = 3
};

// Enum TAGame._Types_TA.EHUDMessageLevel
enum class EHUDMessageLevel : uint8_t
{
	HUDMessageLevel_All                                = 0,
	HUDMessageLevel_GameUpdates                        = 1,
	HUDMessageLevel_Essential                          = 2,
	HUDMessageLevel_END                                = 3
};

// Enum TAGame._Types_TA.EForceFeedbackMode
enum class EForceFeedbackMode : uint8_t
{
	ForceFeedbackMode_Disabled                         = 0,
	ForceFeedbackMode_Impact                           = 1,
	ForceFeedbackMode_All                              = 2,
	ForceFeedbackMode_END                              = 3
};

// Enum TAGame._Types_TA.EForceFeedbackType
enum class EForceFeedbackType : uint8_t
{
	ForceFeedbackType_Disabled                         = 0,
	ForceFeedbackType_VeryLight                        = 1,
	ForceFeedbackType_Light                            = 2,
	ForceFeedbackType_Medium                           = 3,
	ForceFeedbackType_Heavy                            = 4,
	ForceFeedbackType_Legacy                           = 5,
	ForceFeedbackType_END                              = 6
};

// Enum TAGame._Types_TA.ECameraSettingsPreset
enum class ECameraSettingsPreset : uint8_t
{
	CameraSettingsPreset_Default                       = 0,
	CameraSettingsPreset_Balanced                      = 1,
	CameraSettingsPreset_Wide                          = 2,
	CameraSettingsPreset_Custom                        = 3,
	CameraSettingsPreset_Legacy                        = 4,
	CameraSettingsPreset_Modern                        = 5,
	CameraSettingsPreset_END                           = 6
};

// Enum TAGame._Types_TA.EMTXCatalogCategory
enum class EMTXCatalogCategory : uint8_t
{
	MTX_None                                           = 0,
	MTX_Keys                                           = 1,
	MTX_EsportsTokens                                  = 2,
	MTX_RocketBucks                                    = 3,
	MTX_StarterPack                                    = 4,
	MTX_StandardPack                                   = 5,
	MTX_ExactAmountVCPack                              = 6,
	MTX_END                                            = 7
};

// Enum TAGame._Types_TA.EEquippableProductSlot
enum class EEquippableProductSlot : uint8_t
{
	EPS_Skin                                           = 0,
	EPS_Wheels                                         = 1,
	EPS_Boost                                          = 2,
	EPS_Hat                                            = 3,
	EPS_Antenna                                        = 4,
	EPS_END                                            = 5
};

// Enum TAGame._Types_TA.ECurrency
enum class ECurrency : uint8_t
{
	Currency_Soft                                      = 0,
	Currency_Hard                                      = 1,
	Currency_END                                       = 2
};

// Enum TAGame._Types_TA.EOnlineXPModifierType
enum class EOnlineXPModifierType : uint8_t
{
	OnlineXPModifier_Additive                          = 0,
	OnlineXPModifier_Multiplicative                    = 1,
	OnlineXPModifier_END                               = 2
};

// Enum TAGame._Types_TA.EVanityType
enum class EVanityType : uint8_t
{
	VT_None                                            = 0,
	VT_Banner                                          = 1,
	VT_Avatar                                          = 2,
	VT_AvatarBorder                                    = 3,
	VT_END                                             = 4
};

// Enum TAGame._Types_TA.EPaintFinishType
enum class EPaintFinishType : uint8_t
{
	PaintFinishType_Standard                           = 0,
	PaintFinishType_Metallic                           = 1,
	PaintFinishType_END                                = 2
};

// Enum TAGame._Types_TA.EPaintColorVariant
enum class EPaintColorVariant : uint8_t
{
	PaintColorVariant_Primary                          = 0,
	PaintColorVariant_LightAccent                      = 1,
	PaintColorVariant_DarkAccent                       = 2,
	PaintColorVariant_Emissive                         = 3,
	PaintColorVariant_DeEmissive                       = 4,
	PaintColorVariant_Complementary                    = 5,
	PaintColorVariant_Balanced                         = 6,
	PaintColorVariant_Tertiary                         = 7,
	PaintColorVariant_Additive                         = 8,
	PaintColorVariant_Unused3                          = 9,
	PaintColorVariant_Unused4                          = 10,
	PaintColorVariant_Unused5                          = 11,
	PaintColorVariant_END                              = 12
};

// Enum TAGame._Types_TA.ECustomMatchSettingsType
enum class ECustomMatchSettingsType : uint8_t
{
	CustomMatchSettingsType_PrivateMatch               = 0,
	CustomMatchSettingsType_LocalMatch                 = 1,
	CustomMatchSettingsType_TourCreate                 = 2,
	CustomMatchSettingsType_OnlineFreeplay             = 3,
	CustomMatchSettingsType_END                        = 4
};

// Enum TAGame._Types_TA.EEditingType
enum class EEditingType : uint8_t
{
	ET_FreeCam                                         = 0,
	ET_Ball                                            = 1,
	ET_Car                                             = 2,
	ET_END                                             = 3
};

// Enum TAGame._Types_TA.ERankInfoDisplayType
enum class ERankInfoDisplayType : uint8_t
{
	RankInfoDisplayType_None                           = 0,
	RankInfoDisplayType_ExtraModesOnly                 = 1,
	RankInfoDisplayType_StandardOnly                   = 2,
	RankInfoDisplayType_All                            = 3,
	RankInfoDisplayType_END                            = 4
};

// Enum TAGame._Types_TA.EEquipAction
enum class EEquipAction : uint8_t
{
	EquipAction_Both                                   = 0,
	EquipAction_Team0                                  = 1,
	EquipAction_Team1                                  = 2,
	EquipAction_END                                    = 3
};

// Enum TAGame._Types_TA.EHistory
enum class EHistory : uint8_t
{
	H_None                                             = 0,
	H_Add                                              = 1,
	H_Remove                                           = 2,
	H_END                                              = 3
};

// Enum TAGame._Types_TA.EHistoryType
enum class EHistoryType : uint8_t
{
	HT_None                                            = 0,
	HT_Undo                                            = 1,
	HT_Redo                                            = 2,
	HT_END                                             = 3
};

// Enum TAGame._Types_TA.EPawnType
enum class EPawnType : uint8_t
{
	PT_Player                                          = 0,
	PT_Spectator                                       = 1,
	PT_Editor                                          = 2,
	PT_END                                             = 3
};

// Enum TAGame._Types_TA.ETrainingSaveType
enum class ETrainingSaveType : uint8_t
{
	ETS_MyTraining                                     = 0,
	ETS_Favorited                                      = 1,
	ETS_Downloaded                                     = 2,
	ETS_END                                            = 3
};

// Enum TAGame._Types_TA.ESaveGameResult
enum class ESaveGameResult : uint8_t
{
	SaveGameResult_Pending                             = 0,
	SaveGameResult_Success                             = 1,
	SaveGameResult_UserNotSignedIn                     = 2,
	SaveGameResult_Error                               = 3,
	SaveGameResult_NoSpace                             = 4,
	SaveGameResult_Corrupt                             = 5,
	SaveGameResult_END                                 = 6
};

// Enum TAGame._Types_TA.EGoalResetType
enum class EGoalResetType : uint8_t
{
	GoalReset_Standard                                 = 0,
	GoalReset_BallReset                                = 1,
	GoalReset_Disabled                                 = 2,
	GoalReset_END                                      = 3
};

// Enum TAGame._Types_TA.EBoostFillType
enum class EBoostFillType : uint8_t
{
	BoostFill_Unlimited                                = 0,
	BoostFill_Standard                                 = 1,
	BoostFill_Auto                                     = 2,
	BoostFill_NoBoost                                  = 3,
	BoostFill_END                                      = 4
};

// Enum TAGame._Types_TA.EProductThumbnailSize
enum class EProductThumbnailSize : uint8_t
{
	PTS_Garage                                         = 0,
	PTS_Drop                                           = 1,
	PTS_Preview                                        = 2,
	PTS_ShopItem                                       = 3,
	PTS_END                                            = 4
};

// Enum TAGame._Types_TA.EHonorDuelStatus
enum class EHonorDuelStatus : uint8_t
{
	HonorDuelStatus_None                               = 0,
	HonorDuelStatus_Ineligible                         = 1,
	HonorDuelStatus_LocalChallenged                    = 2,
	HonorDuelStatus_WantsChallenge                     = 3,
	HonorDuelStatus_AgreedDuel                         = 4,
	HonorDuelStatus_END                                = 5
};

// Enum TAGame._Types_TA.EPlayerStatusType
enum class EPlayerStatusType : uint8_t
{
	PlayerStatus_Unset                                 = 0,
	PlayerStatus_None                                  = 1,
	PlayerStatus_HonorDuelLaurel                       = 2,
	PlayerStatus_END                                   = 3
};

// Enum TAGame._Types_TA.EChatMessageType
enum class EChatMessageType : uint8_t
{
	CMT_Default                                        = 0,
	CMT_Warning                                        = 1,
	CMT_VoiceNotification                              = 2,
	CMT_HonorDuel                                      = 3,
	CMT_END                                            = 4
};

// Enum TAGame._Types_TA.EUIMenuState
enum class EUIMenuState : uint8_t
{
	UIMS_StartMenu                                     = 0,
	UIMS_MainMenu                                      = 1,
	UIMS_END                                           = 2
};

// Enum TAGame._Types_TA.EMirrorFieldType
enum class EMirrorFieldType : uint8_t
{
	MFT_None                                           = 0,
	MFT_X                                              = 1,
	MFT_Y                                              = 2,
	MFT_XY                                             = 3,
	MFT_TeamIndex                                      = 4,
	MFT_END                                            = 5
};

// Enum TAGame._Types_TA.EProductAttachmentSocket
enum class EProductAttachmentSocket : uint8_t
{
	PAS_Hat                                            = 0,
	PAS_Front                                          = 1,
	PAS_Antenna                                        = 2,
	PAS_UnderGlow                                      = 3,
	PAS_Root                                           = 4,
	PAS_END                                            = 5
};

// Enum TAGame._Types_TA.EDuelNotifications
enum class EDuelNotifications : uint8_t
{
	HDN_None                                           = 0,
	HDN_Challenges                                     = 1,
	HDN_Spectators                                     = 2,
	HDN_All                                            = 3,
	HDN_END                                            = 4
};

// Enum TAGame._Types_TA.EBallHitType
enum class EBallHitType : uint8_t
{
	HitType_Item0                                      = 0,
	HitType_Item1                                      = 1,
	HitType_Item2                                      = 2,
	HitType_Car                                        = 3,
	HitType_END                                        = 4
};

// Enum TAGame._Types_TA.EInputRestriction
enum class EInputRestriction : uint8_t
{
	EIR_None                                           = 0,
	EIR_BackwardsMode                                  = 1,
	EIR_END                                            = 2
};

// Enum TAGame._Types_TA.EBoostRestriction
enum class EBoostRestriction : uint8_t
{
	EBR_None                                           = 0,
	EBR_GroundedOnly                                   = 1,
	EBR_AerialOnly                                     = 2,
	EBR_END                                            = 3
};

// Enum TAGame._Types_TA.EVehicleDemolishMode
enum class EVehicleDemolishMode : uint8_t
{
	VDM_None                                           = 0,
	VDM_Team                                           = 1,
	VDM_FFA                                            = 2,
	VDM_END                                            = 3
};

// Enum TAGame._Types_TA.EVoteStatus
enum class EVoteStatus : uint8_t
{
	VOTE_Pending                                       = 0,
	VOTE_Yes                                           = 1,
	VOTE_No                                            = 2,
	VOTE_END                                           = 3
};

// Enum TAGame._Types_TA.EStatEventDisplayLevels
enum class EStatEventDisplayLevels : uint8_t
{
	SEDL_None                                          = 0,
	SEDL_Primary                                       = 1,
	SEDL_All                                           = 2,
	SEDL_END                                           = 3
};

// Enum TAGame._Types_TA.ETrainingTag
enum class ETrainingTag : uint8_t
{
	Tag_Aerials                                        = 0,
	Tag_Bounces                                        = 1,
	Tag_Shots                                          = 2,
	Tag_Saves                                          = 3,
	Tag_Clears                                         = 4,
	Tag_Rebounds                                       = 5,
	Tag_Redirects                                      = 6,
	Tag_Freestyles                                     = 7,
	Tag_Dribbles                                       = 8,
	Tag_AirDribbles                                    = 9,
	Tag_Kickoffs                                       = 10,
	Tag_WallShots                                      = 11,
	Tag_LongShots                                      = 12,
	Tag_CloseShots                                     = 13,
	Tag_AngleShots                                     = 14,
	Tag_BackwardsShots                                 = 15,
	Tag_Offense                                        = 16,
	Tag_Defense                                        = 17,
	Tag_PinchShots                                     = 18,
	Tag_END                                            = 19
};

// Enum TAGame._Types_TA.EDifficulty
enum class EDifficulty : uint8_t
{
	D_Easy                                             = 0,
	D_Medium                                           = 1,
	D_Hard                                             = 2,
	D_END                                              = 3
};

// Enum TAGame._Types_TA.ETrainingType
enum class ETrainingType : uint8_t
{
	Training_None                                      = 0,
	Training_Aerial                                    = 1,
	Training_Goalie                                    = 2,
	Training_Striker                                   = 3,
	Training_END                                       = 4
};

// Enum TAGame._Types_TA.EFlipResetFxPref
enum class EFlipResetFxPref : uint8_t
{
	EFRP_Off                                           = 0,
	EFRP_AudioOnly                                     = 1,
	EFRP_VisualOnly                                    = 2,
	EFRP_Enabled                                       = 3,
	EFRP_END                                           = 4
};

// Enum TAGame._Types_TA.EShowOnly
enum class EShowOnly : uint8_t
{
	SHOW_Everything                                    = 0,
	SHOW_Body                                          = 1,
	SHOW_Wheels                                        = 2,
	SHOW_Arena                                         = 3,
	SHOW_END                                           = 4
};

// Enum TAGame._Types_TA.ECarImpactResult
enum class ECarImpactResult : uint8_t
{
	CarImpactResult_None                               = 0,
	CarImpactResult_ZeroSpeed                          = 1,
	CarImpactResult_ZeroSpeedTowardsCar                = 2,
	CarImpactResult_OtherCarFaster                     = 3,
	CarImpactResult_Success                            = 4,
	CarImpactResult_FailDemolishTargetNone             = 5,
	CarImpactResult_FailNotSupersonic                  = 6,
	CarImpactResult_FailInsufficientForwardSpeed       = 7,
	CarImpactResult_FailNotWithinForwardEllipticalCone = 8,
	CarImpactResult_FailSameTeam                       = 9,
	CarImpactResult_FailNotWithinVictimHitLocationAngle = 10,
	CarImpactResult_FailNotWithinForwardHitAngle       = 11,
	CarImpactResult_FailNotWithinImpactNormalAngle     = 12,
	CarImpactResult_Bump                               = 13,
	CarImpactResult_END                                = 14
};

// Enum TAGame._Types_TA.EDemolishSpeed
enum class EDemolishSpeed : uint8_t
{
	DemolishSpeed_Unset                                = 0,
	DemolishSpeed_None                                 = 1,
	DemolishSpeed_Low                                  = 2,
	DemolishSpeed_Medium                               = 3,
	DemolishSpeed_High                                 = 4,
	DemolishSpeed_Supersonic                           = 5,
	DemolishSpeed_END                                  = 6
};

// Enum TAGame._Types_TA.EDemolishTarget
enum class EDemolishTarget : uint8_t
{
	DemolishTarget_Unset                               = 0,
	DemolishTarget_OtherTeam                           = 1,
	DemolishTarget_Everyone                            = 2,
	DemolishTarget_None                                = 3,
	DemolishTarget_END                                 = 4
};

// Enum TAGame._Types_TA.EDuplicatesFilterType
enum class EDuplicatesFilterType : uint8_t
{
	EDFT_None                                          = 0,
	EDFT_DuplicateXE                                   = 1,
	EDFT_AnyDuplicate                                  = 2,
	EDFT_END                                           = 3
};

// Enum TAGame._Types_TA.EProductTradeRestriction
enum class EProductTradeRestriction : uint8_t
{
	ProductTradeRestriction_P2P                        = 0,
	ProductTradeRestriction_TradeIn                    = 1,
	ProductTradeRestriction_END                        = 2
};

// Enum TAGame._Types_TA.EProductFilterSortType
enum class EProductFilterSortType : uint8_t
{
	ProductFilterSortType_Alphabetical                 = 0,
	ProductFilterSortType_UnlockDate                   = 1,
	ProductFilterSortType_Quality                      = 2,
	ProductFilterSortType_Quantity                     = 3,
	ProductFilterSortType_Series                       = 4,
	ProductFilterSortType_END                          = 5
};

// Enum TAGame._Types_TA.EArchiveProductFilter
enum class EArchiveProductFilter : uint8_t
{
	ArchiveFilter_ExcludeArchivedProducts              = 0,
	ArchiveFilter_IncludeArchivedProducts              = 1,
	ArchiveFilter_OnlyShowArchivedProducts             = 2,
	ArchiveFilter_END                                  = 3
};

// Enum TAGame._Types_TA.EProductFilterLogLevel
enum class EProductFilterLogLevel : uint8_t
{
	ProductFilterLogLevel_Filtered                     = 0,
	ProductFilterLogLevel_UnFiltered                   = 1,
	ProductFilterLogLevel_END                          = 2
};

// Enum TAGame._Types_TA.EFavoritedProductFilter
enum class EFavoritedProductFilter : uint8_t
{
	FavoritedFilter_ExcludeFavoritedProducts           = 0,
	FavoritedFilter_IncludeFavoritedProducts           = 1,
	FavoritedFilter_OnlyShowFavoritedProducts          = 2,
	FavoritedFilter_END                                = 3
};

// Enum TAGame._Types_TA.EBlueprintType
enum class EBlueprintType : uint8_t
{
	BlueprintType_Unrevealed                           = 0,
	BlueprintType_Revealed                             = 1,
	BlueprintType_NotABlueprint                        = 2,
	BlueprintType_END                                  = 3
};

// Enum TAGame._Types_TA.ERocketPassTierType
enum class ERocketPassTierType : uint8_t
{
	Unknown                                            = 0,
	Filler                                             = 1,
	Reinforcement                                      = 2,
	Anchor                                             = 3,
	ProTier                                            = 4,
	ERocketPassTierType_END                            = 5
};

// Enum TAGame._Types_TA.ERocketPassTierLockState
enum class ERocketPassTierLockState : uint8_t
{
	RPTLock_Unknown                                    = 0,
	RPTLock_Locked                                     = 1,
	RPTLock_Unlocked                                   = 2,
	RPTLock_Claimed                                    = 3,
	RPTLock_END                                        = 4
};

// Enum TAGame._Types_TA.ERocketPassNotificationRewardType
enum class ERocketPassNotificationRewardType : uint8_t
{
	RPNRT_None                                         = 0,
	RPNRT_Premium                                      = 1,
	RPNRT_Free                                         = 2,
	RPNRT_END                                          = 3
};

// Enum TAGame._Types_TA.ERocketPassRewardType
enum class ERocketPassRewardType : uint8_t
{
	RewardType_Product                                 = 0,
	RewardType_Currency                                = 1,
	RewardType_END                                     = 2
};

// Enum TAGame._Types_TA.ELegacyBoxStatus
enum class ELegacyBoxStatus : uint8_t
{
	LBS_ExistingBox                                    = 0,
	LBS_NewBox                                         = 1,
	LBS_New                                            = 2,
	LBS_END                                            = 3
};

// Enum TAGame._Types_TA.EXPTier
enum class EXPTier : uint8_t
{
	XPTier_Low                                         = 0,
	XPTier_Medium                                      = 1,
	XPTier_High                                        = 2,
	XPTier_VeryHigh                                    = 3,
	XPTier_END                                         = 4
};

// Enum TAGame._Types_TA.ELicenseGroup
enum class ELicenseGroup : uint8_t
{
	LicenseGroup_Default                               = 0,
	LicenseGroup_Mario                                 = 1,
	LicenseGroup_Berry                                 = 2,
	LicenseGroup_Maple                                 = 3,
	LicenseGroup_DC                                    = 4,
	LicenseGroup_FastNFurious                          = 5,
	LicenseGroup_Dodge                                 = 6,
	LicenseGroup_Nissan                                = 7,
	LicenseGroup_RickNMorty                            = 8,
	LicenseGroup_HotWheels                             = 9,
	LicenseGroup_WWE                                   = 10,
	LicenseGroup_Jurassic                              = 11,
	LicenseGroup_Microsoft                             = 12,
	LicenseGroup_Nintendo                              = 13,
	LicenseGroup_Sony                                  = 14,
	LicenseGroup_Back2Future                           = 15,
	LicenseGroup_Ghostbusters                          = 16,
	LicenseGroup_Stranger                              = 17,
	LicenseGroup_Fortnite                              = 18,
	LicenseGroup_McLaren                               = 19,
	LicenseGroup_KnightRider                           = 20,
	LicenseGroup_Pele                                  = 21,
	LicenseGroup_MLB                                   = 22,
	LicenseGroup_NFL                                   = 23,
	LicenseGroup_NBA                                   = 24,
	LicenseGroup_Community                             = 25,
	LicenseGroup_Esports                               = 26,
	LicenseGroup_ESPN                                  = 27,
	LicenseGroup_Monstercat                            = 28,
	LicenseGroup_Kaskade                               = 29,
	LicenseGroup_Ford                                  = 30,
	LicenseGroup_Misc                                  = 31,
	LicenseGroup_Lambo                                 = 32,
	LicenseGroup_Nascar                                = 33,
	LicenseGroup_F1                                    = 34,
	LicenseGroup_Bond                                  = 35,
	LicenseGroup_BMW                                   = 36,
	LicenseGroup_Grimes                                = 37,
	LicenseGroup_Ferrari                               = 38,
	LicenseGroup_Honda                                 = 39,
	LicenseGroup_Bugatti                               = 40,
	LicenseGroup_Volkswagen                            = 41,
	LicenseGroup_Transformers                          = 42,
	LicenseGroup                                       = 43,
	LicenseGroup01                                     = 44,
	LicenseGroup02                                     = 45,
	LicenseGroup03                                     = 46,
	LicenseGroup04                                     = 47,
	LicenseGroup05                                     = 48,
	LicenseGroup06                                     = 49,
	LicenseGroup_END                                   = 50
};

// Enum TAGame._Types_TA.EEffectsIntensity
enum class EEffectsIntensity : uint8_t
{
	EI_Default                                         = 0,
	EI_Low                                             = 1,
	EI_END                                             = 2
};

// Enum TAGame._Types_TA.EPlayMusicMode
enum class EPlayMusicMode : uint8_t
{
	EPMM_Menu_Only                                     = 0,
	EPMM_Menu_Training                                 = 1,
	EPMM_Training_Only                                 = 2,
	EPMM_Game_Only                                     = 3,
	EPMM_Game_Training                                 = 4,
	EPMM_Game_Menu                                     = 5,
	EPMM_Everywhere                                    = 6,
	EPMM_Mute                                          = 7,
	EPMM_END                                           = 8
};

// Enum TAGame._Types_TA.EControllerSoundMode
enum class EControllerSoundMode : uint8_t
{
	CSM_Multiplayer                                    = 0,
	CSM_On                                             = 1,
	CSM_Off                                            = 2,
	CSM_END                                            = 3
};

// Enum TAGame._Types_TA.EChatFilter
enum class EChatFilter : uint8_t
{
	ChatFilter_All                                     = 0,
	ChatFilter_Team                                    = 1,
	ChatFilter_Friends                                 = 2,
	ChatFilter_Preset                                  = 3,
	ChatFilter_TeamPreset                              = 4,
	ChatFilter_TacticalPreset                          = 5,
	ChatFilter_None                                    = 6,
	ChatFilter_END                                     = 7
};

// Enum TAGame._Types_TA.EVoiceFilter
enum class EVoiceFilter : uint8_t
{
	VoiceFilter_All                                    = 0,
	VoiceFilter_Preset                                 = 1,
	VoiceFilter_TeamPreset                             = 2,
	VoiceFilter_TacticalPreset                         = 3,
	VoiceFilter_Team                                   = 4,
	VoiceFilter_Friends                                = 5,
	VoiceFilter_None                                   = 6,
	VoiceFilter_END                                    = 7
};

// Enum TAGame._Types_TA.ESupportType
enum class ESupportType : uint8_t
{
	SupportType_Creator                                = 0,
	SupportType_Charity                                = 1,
	SupportType_END                                    = 2
};

// Enum TAGame._Types_TA.ETargetCamSwivelMode
enum class ETargetCamSwivelMode : uint8_t
{
	TCSM_ZeroOut                                       = 0,
	TCSM_AllowKickoff                                  = 1,
	TCSM_AllowAlways                                   = 2,
	TCSM_END                                           = 3
};

// Enum TAGame._Types_TA.EPaintTeam
enum class EPaintTeam : uint8_t
{
	PaintTeam_Blue                                     = 0,
	PaintTeam_Orange                                   = 1,
	PaintTeam_None                                     = 2,
	PaintTeam_END                                      = 3
};

// Enum TAGame._Types_TA.ETeam
enum class ETeam : uint8_t
{
	Team_Blue                                          = 0,
	Team_Orange                                        = 1,
	Team_END                                           = 2
};

// Enum TAGame._Types_TA.EDemolishSource
enum class EDemolishSource : uint8_t
{
	EDS_None                                           = 0,
	EDS_Car                                            = 1,
	EDS_Ball                                           = 2,
	EDS_END                                            = 3
};

// Enum TAGame._Types_TA.ESettingDisplayMode
enum class ESettingDisplayMode : uint8_t
{
	ESD_None                                           = 0,
	ESD_Percentage                                     = 1,
	ESD_Degrees                                        = 2,
	ESD_END                                            = 3
};

// Enum TAGame._Types_TA.SearchStatusOwner
enum class ESearchStatusOwner : uint8_t
{
	StatusOwner_None                                   = 0,
	StatusOwner_Matchmaking                            = 1,
	StatusOwner_PrivateMatch                           = 2,
	StatusOwner_Tournaments                            = 3,
	StatusOwner_END                                    = 4
};

// Enum TAGame._Types_TA.EMatchmakingViewTab
enum class EMatchmakingViewTab : uint8_t
{
	MatchmakingViewTab_Unranked                        = 0,
	MatchmakingViewTab_Ranked                          = 1,
	MatchmakingViewTab_RankedSports                    = 2,
	MatchmakingViewTab_UnrankedSports                  = 3,
	MatchmakingViewTab_MicroEvent                      = 4,
	MatchmakingViewTab_DebugMicroEvent                 = 5,
	MatchmakingViewTab_Casual                          = 6,
	MatchmakingViewTab_MenuTree                        = 7,
	MatchmakingViewTab_END                             = 8
};

// Enum TAGame._Types_TA.EWheelPosition
enum class EWheelPosition : uint8_t
{
	WP_FrontLeft                                       = 0,
	WP_FrontRight                                      = 1,
	WP_BackLeft                                        = 2,
	WP_BackRight                                       = 3,
	WP_END                                             = 4
};

// Enum TAGame._Types_TA.EVoteSubject
enum class EVoteSubject : uint8_t
{
	VoteSubject_Rematch                                = 0,
	VoteSubject_Forfeit                                = 1,
	VoteSubject_END                                    = 2
};

// Enum TAGame._Types_TA.ENetworkInputBuffer
enum class ENetworkInputBuffer : uint8_t
{
	NetworkInputBuffer_ServerConsume                   = 0,
	NetworkInputBuffer_STS                             = 1,
	NetworkInputBuffer_CSTS                            = 2,
	NetworkInputBuffer_END                             = 3
};

// Enum TAGame._Types_TA.ENetworkValue
enum class ENetworkValue : uint8_t
{
	Net_Low                                            = 0,
	Net_Medium                                         = 1,
	Net_High                                           = 2,
	Net_END                                            = 3
};

// Enum TAGame._Types_TA.EMeshMirrorMode
enum class EMeshMirrorMode : uint8_t
{
	MeshMirrorMode_Mirror                              = 0,
	MeshMirrorMode_Rotate                              = 1,
	MeshMirrorMode_END                                 = 2
};

// Enum TAGame._Types_TA.EDemoSelectionState
enum class EDemoSelectionState : uint8_t
{
	EDSS_None                                          = 0,
	EDSS_Locked                                        = 1,
	EDSS_Active                                        = 2,
	EDSS_END                                           = 3
};

// Enum TAGame._Types_TA.EDemoSpawnPreference
enum class EDemoSpawnPreference : uint8_t
{
	EDSP_None                                          = 0,
	EDSP_Left                                          = 1,
	EDSP_Right                                         = 2,
	EDSP_END                                           = 3
};

// Enum TAGame._Types_TA.EStatGraphLevel
enum class EStatGraphLevel : uint8_t
{
	StatGraphLevel_None                                = 0,
	StatGraphLevel_PerfSummary                         = 1,
	StatGraphLevel_PerfGraphShort                      = 2,
	StatGraphLevel_PerfGraphLong                       = 3,
	StatGraphLevel_NetSummary                          = 4,
	StatGraphLevel_NetGraphShort                       = 5,
	StatGraphLevel_NetGraphLong                        = 6,
	StatGraphLevel_ActorGraphSummary                   = 7,
	StatGraphLevel_ActorGraphShort                     = 8,
	StatGraphLevel_ActorGraphLong                      = 9,
	StatGraphLevel_END                                 = 10
};

// Enum TAGame._Types_TA.EInputBufferSaturationLevel
enum class EInputBufferSaturationLevel : uint8_t
{
	IBSL_ExtremelyStarved                              = 0,
	IBSL_Starved                                       = 1,
	IBSL_Good                                          = 2,
	IBSL_Saturated                                     = 3,
	IBSL_ExtremelySaturated                            = 4,
	IBSL_END                                           = 5
};

// Enum TAGame._Types_TA.EAchievementType
enum class EAchievementType : uint8_t
{
	AT_Game                                            = 0,
	AT_EXP0                                            = 1,
	AT_DLC0                                            = 2,
	AT_DLC1                                            = 3,
	AT_DLC2                                            = 4,
	AT_XBO0                                            = 5,
	AT_DLC3                                            = 6,
	AT_DLC4                                            = 7,
	AT_DLC5                                            = 8,
	AT_DLC6                                            = 9,
	AT_DLC7                                            = 10,
	AT_Meta                                            = 11,
	AT_END                                             = 12
};

// Enum TAGame._Types_TA.ECustomScoreboardStat
enum class ECustomScoreboardStat : uint8_t
{
	CSStat_None                                        = 0,
	CSStat_Goal                                        = 1,
	CSStat_Assist                                      = 2,
	CSStat_Save                                        = 3,
	CSStat_EpicSave                                    = 4,
	CSStat_Shot                                        = 5,
	CSStat_Center                                      = 6,
	CSStat_Clear                                       = 7,
	CSStat_AerialHit                                   = 8,
	CSStat_BicycleHit                                  = 9,
	CSStat_JuggleHit                                   = 10,
	CSStat_Demolish                                    = 11,
	CSStat_FirstTouch                                  = 12,
	CSStat_PoolShot                                    = 13,
	CSStat_LowFive                                     = 14,
	CSStat_HighFive                                    = 15,
	CSStat_FlipReset                                   = 16,
	CSStat_BreakoutDamage                              = 17,
	CSStat_BallHit                                     = 18,
	CSStat_Demolished                                  = 19,
	CSStat_Dodges                                      = 20,
	CSStat_CrossbarHits                                = 21,
	CSStat_CarTouches                                  = 22,
	CSStat_BoostPickups                                = 23,
	CSStat_PowerupsUsed                                = 24,
	CSStat_END                                         = 25
};

// Enum TAGame._ShopTypes_TA.EShopDeliverableType
enum class EShopDeliverableType : uint8_t
{
	Deliverable_Product                                = 0,
	Deliverable_END                                    = 1
};

// Enum TAGame._ShopTypes_TA.EItemDisplayType
enum class EItemDisplayType : uint8_t
{
	DisplayDaily                                       = 0,
	DisplayFull                                        = 1,
	EItemDisplayType_END                               = 2
};

// Enum TAGame._TourTypes_TA.ETourSeedType
enum class ETourSeedType : uint8_t
{
	TourSeedType_Skill                                 = 0,
	TourSeedType_Random                                = 1,
	TourSeedType_END                                   = 2
};

// Enum TAGame.EpicAccountSave_TA.EProfilePCSaveVersion
enum class EProfilePCSaveVersion : uint8_t
{
	EpicAccountSaveVersion_bPrompted                   = 0,
	EpicAccountSaveVersion_END                         = 1
};

// Enum TAGame.FirstTimeExperienceManager_TA.FTELegacyGroupType
enum class EFTELegacyGroupType : uint8_t
{
	LGT_All                                            = 0,
	LGT_NewUser                                        = 1,
	LGT_LegacyUser                                     = 2,
	LGT_END                                            = 3
};

// Enum TAGame.FirstTimeExperienceManager_TA.FTEVersioning
enum class EFTEVersioning : uint8_t
{
	FTEV_InitialVersion                                = 0,
	FTEV_CustomizationRework                           = 1,
	FTEV_END                                           = 2
};

// Enum TAGame.FXActor_SafeZone_Knockout_TA.EZoneEvent
enum class EZoneEvent : uint8_t
{
	ZE_None                                            = 0,
	ZE_FinalZone                                       = 1,
	ZE_END                                             = 2
};

// Enum TAGame.ClientConnectionTracker_TA.EConnectionQualityState
enum class EConnectionQualityState : uint8_t
{
	CQS_Good                                           = 0,
	CQS_Mediocre                                       = 1,
	CQS_Bad                                            = 2,
	CQS_END                                            = 3
};

// Enum TAGame.GameEvent_TrainingEditor_TA.EPlayTestType
enum class EPlayTestType : uint8_t
{
	PlayTest_LoopRound                                 = 0,
	PlayTest_IncrementRound                            = 1,
	PlayTest_IncrementRoundLoop                        = 2,
	PlayTest_END                                       = 3
};

// Enum TAGame.GFxData_ProductFilter_TA.EProductFilterType
enum class EProductFilterType : uint8_t
{
	ProductFilterType_TradeIn                          = 0,
	ProductFilterType_P2P                              = 1,
	ProductFilterType_Garage                           = 2,
	ProductFilterType_PremiumInventory                 = 3,
	ProductFilterType_END                              = 4
};

// Enum TAGame.RPC_GetActivePlaylists_TA.EActivePlaylistType
enum class EActivePlaylistType : uint8_t
{
	ActivePlaylistType_Unused                          = 0,
	ActivePlaylistType_Standard                        = 1,
	ActivePlaylistType_Extra                           = 2,
	ActivePlaylistType_Arcade                          = 3,
	ActivePlaylistType_LTM                             = 4,
	ActivePlaylistType_LargeParty                      = 5,
	ActivePlaylistType_Dueling                         = 6,
	ActivePlaylistType_END                             = 7
};

// Enum TAGame.RocketPassNotificationsManager_TA.RocketPassNotificationType
enum class ERocketPassNotificationType : uint8_t
{
	RPNT_Product                                       = 0,
	RPNT_Currency                                      = 1,
	RPNT_Other                                         = 2,
	RPNT_END                                           = 3
};

// Enum TAGame.TourStatus_TA.ETourStatus
enum class ETourStatus : uint8_t
{
	TourStatus_None                                    = 0,
	TourStatus_Cancelled                               = 1,
	TourStatus_Full                                    = 2,
	TourStatus_END                                     = 3
};

// Enum TAGame._UserBugReportTypes_TA.EUserBugReportCategoryType
enum class EUserBugReportCategoryType : uint8_t
{
	UBRCT_UserInput                                    = 0,
	UBRCT_AutoReport                                   = 1,
	UBRCT_CustomerSupport                              = 2,
	UBRCT_Parent                                       = 3,
	UBRCT_END                                          = 4
};

// Enum TAGame._AITypes_TA.EAITeam
enum class EAITeam : uint8_t
{
	AITeam_Self                                        = 0,
	AITeam_Enemy                                       = 1,
	AITeam_Any                                         = 2,
	AITeam_END                                         = 3
};

// Enum TAGame._AITypes_TA.EBTStatus
enum class EBTStatus : uint8_t
{
	BTStatus_Fail                                      = 0,
	BTStatus_Success                                   = 1,
	BTStatus_Running                                   = 2,
	BTStatus_END                                       = 3
};

// Enum TAGame._CrowdTypes_TA.ECrowdValueType
enum class ECrowdValueType : uint8_t
{
	CVT_Excitement                                     = 0,
	CVT_Tension                                        = 1,
	CVT_Anticipation                                   = 2,
	CVT_Upset                                          = 3,
	CVT_END                                            = 4
};

// Enum TAGame._FreeplayCommandsTypes_TA.EFreeplayCommand
enum class EFreeplayCommand : uint8_t
{
	FreeplayCommand_BallInFront                        = 0,
	FreeplayCommand_BallOnCar                          = 1,
	FreeplayCommand_RedirectPass                       = 2,
	FreeplayCommand_PopBallUp                          = 3,
	FreeplayCommand_DefendShot                         = 4,
	FreeplayCommand_PlayerReset                        = 5,
	FreeplayCommand_END                                = 6
};

// Enum TAGame._TrainingTypes_TA.ETrainingRoundAttempt
enum class ETrainingRoundAttempt : uint8_t
{
	TrainingRoundAttempt_NotAttempted                  = 0,
	TrainingRoundAttempt_Attempted                     = 1,
	TrainingRoundAttempt_Completed                     = 2,
	TrainingRoundAttempt_END                           = 3
};

// Enum TAGame._TrainingTypes_TA.ETrainingNavigationCommand
enum class ETrainingNavigationCommand : uint8_t
{
	TrainingNavigationCommand_SelectShot               = 0,
	TrainingNavigationCommand_PreviousShot             = 1,
	TrainingNavigationCommand_NextShot                 = 2,
	TrainingNavigationCommand_ToggleShuffle            = 3,
	TrainingNavigationCommand_END                      = 4
};

// Enum TAGame._TrainingTypes_TA.ETrainingManipulationCommand
enum class ETrainingManipulationCommand : uint8_t
{
	TrainingManipulationCommand_MirrorShot             = 0,
	TrainingManipulationCommand_END                    = 1
};

// Enum TAGame.AchievementManager_TA.EAchievementGame
enum class EAchievementGame : uint8_t
{
	AG_Virtuoso                                        = 0,
	AG_Stocked                                         = 1,
	AG_FarFarAway                                      = 2,
	AG_SuperVictorious                                 = 3,
	AG_Champion                                        = 4,
	AG_TheStreak                                       = 5,
	AG_HelensPride                                     = 6,
	AG_BattleCarCollector                              = 7,
	AG_DropsintheBucket                                = 8,
	AG_Rocketeer                                       = 9,
	AG_GreaseMonkey                                    = 10,
	AG_PitchVeteran                                    = 11,
	AG_RidersBlock                                     = 12,
	AG_BreakShot                                       = 13,
	AG_Turbocharger                                    = 14,
	AG_DrillSergeant                                   = 15,
	AG_MinutetoWinit                                   = 16,
	AG_SpeedDemon                                      = 17,
	AG_PickMeUp                                        = 18,
	AG_WallCrawler                                     = 19,
	AG_TeamPlayer                                      = 20,
	AG_SARPBCForever                                   = 21,
	AG_FeatherinYourRecap                              = 22,
	AG_Winner                                          = 23,
	AG_CleanSheet                                      = 24,
	AG_TripleThreat                                    = 25,
	AG_DoubleUp                                        = 26,
	AG_SinglesClub                                     = 27,
	AG_PerfectStart                                    = 28,
	AG_StillAShowOff                                   = 29,
	AG_KnowTheDrill                                    = 30,
	AG_Traveler                                        = 31,
	AG_Tinkerer                                        = 32,
	AG_FirstTimer                                      = 33,
	AG_BarrasBravas                                    = 34,
	AG_Friendly                                        = 35,
	AG_END                                             = 36
};

// Enum TAGame.AchievementManager_TA.EAchievementEXP0
enum class EAchievementEXP0 : uint8_t
{
	AEXP0_SkyHigh                                      = 0,
	AEXP0_AllFours                                     = 1,
	AEXP0_Gladiator                                    = 2,
	AEXP0_END                                          = 3
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC0
enum class EAchievementDLC0 : uint8_t
{
	ADLC0_WinningIsWinning                             = 0,
	ADLC0_AnInchAnd62Miles                             = 1,
	ADLC0_RideOrDie                                    = 2,
	ADLC0_DontLookBack                                 = 3,
	ADLC0_FamilyNotFriends                             = 4,
	ADLC0_DriftKing                                    = 5,
	ADLC0_END                                          = 6
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC1
enum class EAchievementDLC1 : uint8_t
{
	ADLC1_SurvivalOfTheFittest                         = 0,
	ADLC1_Heartbreaker                                 = 1,
	ADLC1_NaturalProgression                           = 2,
	ADLC1_Throwback                                    = 3,
	ADLC1_HotShotPartTwo                               = 4,
	ADLC1_END                                          = 5
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC2
enum class EAchievementDLC2 : uint8_t
{
	ADLC2_MyWorldIsFire                                = 0,
	ADLC2_Spectacular                                  = 1,
	ADLC2_Savage                                       = 2,
	ADLC2_Ruthless                                     = 3,
	ADLC2_PsychoMasterExploder                         = 4,
	ADLC2_END                                          = 5
};

// Enum TAGame.AchievementManager_TA.EAchievementXBO0
enum class EAchievementXBO0 : uint8_t
{
	AXBO0_NiceHat                                      = 0,
	AXBO0_MarcusVMasterChief                           = 1,
	AXBO0_END                                          = 2
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC3
enum class EAchievementDLC3 : uint8_t
{
	ADLC3_MadScientist                                 = 0,
	ADLC3_IcingTheCake                                 = 1,
	ADLC3_LeftWingRightWing                            = 2,
	ADLC3_FastBreak                                    = 3,
	ADLC3_BuzzerBeater                                 = 4,
	ADLC3_BuddingArtist                                = 5,
	ADLC3_OneBetter                                    = 6,
	ADLC3_Certifiable                                  = 7,
	ADLC3_END                                          = 8
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC4
enum class EAchievementDLC4 : uint8_t
{
	ADLC4_GG                                           = 0,
	ADLC4_Trifecta                                     = 1,
	ADLC4_InfinitePower                                = 2,
	ADLC4_StoppedCold                                  = 3,
	ADLC4_SeaTurtle                                    = 4,
	ADLC4_GetUpMrBubbles                               = 5,
	ADLC4_RocketGenocider                              = 6,
	ADLC4_END                                          = 7
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC5
enum class EAchievementDLC5 : uint8_t
{
	ADLC5_RegisteredVoter                              = 0,
	ADLC5_Metaverse                                    = 1,
	ADLC5_BraveTheElements                             = 2,
	ADLC5_DamageControl                                = 3,
	ADLC5_FullCourse                                   = 4,
	ADLC5_BuckminsterX10                               = 5,
	ADLC5_END                                          = 6
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC6
enum class EAchievementDLC6 : uint8_t
{
	ADLC6_StormTrooper                                 = 0,
	ADLC6_GoodTimes                                    = 1,
	ADLC6_NewProfileWhoThis                            = 2,
	ADLC6_TradeSecret                                  = 3,
	ADLC6_RankUp                                       = 4,
	ADLC6_ComingOnStrong                               = 5,
	ADLC6_END                                          = 6
};

// Enum TAGame.AchievementManager_TA.EAchievementDLC7
enum class EAchievementDLC7 : uint8_t
{
	ADLC7_JoinTheClub                                  = 0,
	ADLC7_TogetherIsBetter                             = 1,
	ADLC7_NewChallenger                                = 2,
	ADLC7_PeoplePerson                                 = 3,
	ADLC7_SquadGoals                                   = 4,
	ADLC7_BestOfTheBunch                               = 5,
	ADLC7_END                                          = 6
};

// Enum TAGame.AchievementManager_TA.EAchievementMeta
enum class EAchievementMeta : uint8_t
{
	AMeta_PointCollector                               = 0,
	AMeta_END                                          = 1
};

// Enum TAGame.AchievementSave_TA.EAchievementSaveVersion
enum class EAchievementSaveVersion : uint8_t
{
	AchievementSaveVersion_FreeToPlayLaunch            = 0,
	AchievementSaveVersion_END                         = 1
};

// Enum TAGame.ActivityFeedManager_TA.EActivityFeedType
enum class EActivityFeedType : uint8_t
{
	AF_UnlockedBody                                    = 0,
	AF_DrivenDistance                                  = 1,
	AF_ScoredGoal                                      = 2,
	AF_BlockedShot                                     = 3,
	AF_WonGame                                         = 4,
	AF_MVPScore                                        = 5,
	AF_DefeatedFriend                                  = 6,
	AF_CompletedRegularSeason                          = 7,
	AF_WonChampionship                                 = 8,
	AF_UnlockedItem                                    = 9,
	AF_UnlockedSweetTooth                              = 10,
	AF_END                                             = 11
};

// Enum TAGame.AnimNotify_SetBoneVisibility_TA.VisibilityType
enum class EVisibilityType : uint8_t
{
	VT_Socket                                          = 0,
	VT_Bone                                            = 1,
	VT_END                                             = 2
};

// Enum TAGame.GameplayMusicPlayer_TA.EPlaylistType
enum class EPlaylistType : uint8_t
{
	PlaylistType_Training                              = 0,
	PlaylistType_Match                                 = 1,
	PlaylistType_END                                   = 2
};

// Enum TAGame.GameplayMusicPlayer_TA.EMusicPlayerState
enum class EMusicPlayerState : uint8_t
{
	MusicPlayerState_None                              = 0,
	MusicPlayerState_Enabled                           = 1,
	MusicPlayerState_Muted                             = 2,
	MusicPlayerState_Disabled                          = 3,
	MusicPlayerState_END                               = 4
};

// Enum TAGame.AssetAttribute_ForceWheelAxle_TA.EAxleToForce
enum class EAxleToForce : uint8_t
{
	ForceFrontAxle                                     = 0,
	ForceBackAxle                                      = 1,
	EAxleToForce_END                                   = 2
};

// Enum TAGame.BackFillPolicy_TA.EPolicyType
enum class EPolicyType : uint8_t
{
	PolicyType_Soccar                                  = 0,
	PolicyType_Knockout                                = 1,
	PolicyType_END                                     = 2
};

// Enum TAGame.PitchTekDrawingComponent_TA.EPitchTekDecalType
enum class EPitchTekDecalType : uint8_t
{
	PTDT_Ball                                          = 0,
	PTDT_Car                                           = 1,
	PTDT_END                                           = 2
};

// Enum TAGame.BallKeepUpComponent_TA.EKeepUpState
enum class EKeepUpState : uint8_t
{
	KUS_None                                           = 0,
	KUS_Inactive                                       = 1,
	KUS_Active                                         = 2,
	KUS_END                                            = 3
};

// Enum TAGame.BotConfig_TA.EBotSkill
enum class EBotSkill : uint8_t
{
	BotSkill_Intro                                     = 0,
	BotSkill_Easy                                      = 1,
	BotSkill_Medium                                    = 2,
	BotSkill_Hard                                      = 3,
	BotSkill_Unfair                                    = 4,
	BotSkill_END                                       = 5
};

// Enum TAGame.BreakOutActor_Platform_TA.EBreakoutDamageState
enum class EBreakoutDamageState : uint8_t
{
	DamageState_Start                                  = 0,
	DamageState_Damaged                                = 1,
	DamageState_Broken                                 = 2,
	DamageState_END                                    = 3
};

// Enum TAGame.BTLock.ELockScope
enum class ELockScope : uint8_t
{
	LockScope_Local                                    = 0,
	LockScope_Global                                   = 1,
	LockScope_END                                      = 2
};

// Enum TAGame.CameraState_CameraTrack_TA.ECameraTrackFlyType
enum class ECameraTrackFlyType : uint8_t
{
	CameraTrackFly_Never                               = 0,
	CameraTrackFly_WhenMoving                          = 1,
	CameraTrackFly_WhenPaused                          = 2,
	CameraTrackFly_END                                 = 3
};

// Enum TAGame.CameraState_DirectorMoving_TA.ECameraLoopType
enum class ECameraLoopType : uint8_t
{
	CLT_StopAtEnd                                      = 0,
	CLT_PingPong                                       = 1,
	CLT_Loop                                           = 2,
	CLT_END                                            = 3
};

// Enum TAGame.CameraState_ReplayAutoCam_TA.ECountDownFocus
enum class ECountDownFocus : uint8_t
{
	CDF_None                                           = 0,
	CDF_Pan                                            = 1,
	CDF_Rotate                                         = 2,
	CDF_END                                            = 3
};

// Enum TAGame.CameraStateSelector_Priority_TA.EStatePriority
enum class EStatePriority : uint8_t
{
	SP_Default                                         = 0,
	SP_OverrideAny                                     = 1,
	SP_OverrideLower                                   = 2,
	SP_InitialOnly                                     = 3,
	SP_END                                             = 4
};

// Enum TAGame.CarComponent_TerritoryDemolish_TA.TerritoryAudioCueType
enum class ETerritoryAudioCueType : uint8_t
{
	CrossWallEnter                                     = 0,
	CrossWallExit                                      = 1,
	CrossWallMuffle                                    = 2,
	TerritoryAudioCueType_END                          = 3
};

// Enum TAGame.ItemDropGroup_TA.EDropGroupDisplayOrder
enum class EDropGroupDisplayOrder : uint8_t
{
	DropGroupDisplayOrder_Default                      = 0,
	DropGroupDisplayOrder_Challenge                    = 1,
	DropGroupDisplayOrder_RewardDrop                   = 2,
	DropGroupDisplayOrder_GarageSlot                   = 3,
	DropGroupDisplayOrder_LevelUpReward                = 4,
	DropGroupDisplayOrder_Currency                     = 5,
	DropGroupDisplayOrder_Container                    = 6,
	DropGroupDisplayOrder_OfflineInjectedProduct       = 7,
	DropGroupDisplayOrder_END                          = 8
};

// Enum TAGame.ChallengeFolder_TA.EChallengeSort
enum class EChallengeSort : uint8_t
{
	ECS_None                                           = 0,
	ECS_TopBottom                                      = 1,
	ECS_END                                            = 2
};

// Enum TAGame.ChallengeFolder_TA.EChallengeType
enum class EChallengeType : uint8_t
{
	ChallengeType_NewDriver                            = 0,
	ChallengeType_Week                                 = 1,
	ChallengeType_Season                               = 2,
	ChallengeType_Event                                = 3,
	ChallengeType_END                                  = 4
};

// Enum TAGame.CrumbTrailRedefinition_TA.CrumbRedefinitionType
enum class ECrumbRedefinitionType : uint8_t
{
	CR_TrailData                                       = 0,
	CR_Triggers                                        = 1,
	CR_CompletionTriggers                              = 2,
	CR_Crumbs                                          = 3,
	CR_END                                             = 4
};

// Enum TAGame.CrumbTrailRedefinition_TA.CrumbAction
enum class ECrumbAction : uint8_t
{
	CA_Add                                             = 0,
	CA_Remove                                          = 1,
	CA_Redo                                            = 2,
	CA_END                                             = 3
};

// Enum TAGame.DistributionFloatSpeed_TA.ESpeedDistributionSpace
enum class ESpeedDistributionSpace : uint8_t
{
	SDD_Forward                                        = 0,
	SDD_Side                                           = 1,
	SDD_Up                                             = 2,
	SDD_World                                          = 3,
	SDD_END                                            = 4
};

// Enum TAGame.EngagementEventsConfig_TA.EEngagementEventType
enum class EEngagementEventType : uint8_t
{
	EngagementEventType_DoubleXP                       = 0,
	EngagementEventType_DoublePaint                    = 1,
	EngagementEventType_END                            = 2
};

// Enum TAGame.K3SUserPermissions_TA.ERemediationMethod
enum class ERemediationMethod : uint8_t
{
	AGE_VERIFICATION                                   = 0,
	PARENT_VERIFICATION                                = 1,
	ERemediationMethod_END                             = 2
};

// Enum TAGame.EOSVoiceSettingsSave_TA.EVoiceSettingsSaveVersion
enum class EVoiceSettingsSaveVersion : uint8_t
{
	EVoiceSettingsSaveVersion_VoiceInputMode           = 0,
	EVoiceSettingsSaveVersion_VoiceChatFilter          = 1,
	EVoiceSettingsSaveVersion_VoiceNotificationLevel   = 2,
	EVoiceSettingsSaveVersion_END                      = 3
};

// Enum TAGame.FirstTimeExperienceRedefinition_TA.FTERedefinitionAction
enum class EFTERedefinitionAction : uint8_t
{
	RT_Rename                                          = 0,
	RT_Add                                             = 1,
	RT_Remove                                          = 2,
	RT_END                                             = 3
};

// Enum TAGame.FirstTimeExperienceRedefinition_TA.FTERedefinitionType
enum class EFTERedefinitionType : uint8_t
{
	ER_Group                                           = 0,
	ER_Checkpoint                                      = 1,
	ER_Triggers                                        = 2,
	ER_UserGroup                                       = 3,
	ER_SaveGroup                                       = 4,
	ER_SaveAll                                         = 5,
	ER_END                                             = 6
};

// Enum TAGame.ForceVolume_TA.EForceDirection
enum class EForceDirection : uint8_t
{
	EFD_VolumeRotation                                 = 0,
	EFD_ActorVelocity                                  = 1,
	EFD_Custom                                         = 2,
	EFD_END                                            = 3
};

// Enum TAGame.FXActor_Boost_TA.EmitterSocketBehavior
enum class EmitterSocketBehavior : uint8_t
{
	ESB_Default                                        = 0,
	ESB_SingleEmitterAveragePosition                   = 1,
	ESB_END                                            = 2
};

// Enum TAGame.FXActor_Car_Knockout_TA.EStateEvent
enum class EStateEvent : uint8_t
{
	SE_Block                                           = 0,
	SE_AttackStunned                                   = 1,
	SE_BlockStunned                                    = 2,
	SE_TradeStunned                                    = 3,
	SE_GrabStunned                                     = 4,
	SE_Grabbed                                         = 5,
	SE_Respawn                                         = 6,
	SE_END                                             = 7
};

// Enum TAGame.FXActor_Knockout_Attack_TA.EAttackType
enum class EAttackType : uint8_t
{
	AT_None                                            = 0,
	AT_Light                                           = 1,
	AT_Heavy                                           = 2,
	AT_END                                             = 3
};

// Enum TAGame.GameEditor_Ring_TA.EDetectionType
enum class EDetectionType : uint8_t
{
	DT_Ball                                            = 0,
	DT_Player                                          = 1,
	DT_END                                             = 2
};

// Enum TAGame.GameEvent_Tutorial_TA.ERotationType
enum class ERotationType : uint8_t
{
	Rot_Auto                                           = 0,
	Rot_AutoAim                                        = 1,
	Rot_AutoForward                                    = 2,
	Rot_AutoArch                                       = 3,
	Rot_World                                          = 4,
	Rot_MapCenter                                      = 5,
	Rot_END                                            = 6
};

// Enum TAGame.GameplaySettingsSave_TA.EGameplaySettingsSaveVersion
enum class EGameplaySettingsSaveVersion : uint8_t
{
	EGameplaySettingsSaveVersion_ChatFilterDisambiguation = 0,
	EGameplaySettingsSaveVersion_FlipResetFxAdjustment = 1,
	EGameplaySettingsSaveVersion_END                   = 2
};

// Enum TAGame.Crosshair_TA.ECrosshairType
enum class ECrosshairType : uint8_t
{
	Crosshair_None                                     = 0,
	Crosshair_Chevron                                  = 1,
	Crosshair_Dot                                      = 2,
	Crosshair_END                                      = 3
};

// Enum TAGame.GFxData_AdHoc_TA.EAdHocState
enum class EAdHocState : uint8_t
{
	AHS_Enabled                                        = 0,
	AHS_Disabled                                       = 1,
	AHS_END                                            = 2
};

// Enum TAGame.GFxData_CarKnockOut_TA.EStunlockType
enum class EStunlockType : uint8_t
{
	SL_None                                            = 0,
	SL_Stunned                                         = 1,
	SL_Grabbed                                         = 2,
	SL_END                                             = 3
};

// Enum TAGame.GFxData_ChallengeManager_TA.EChallengeFilter
enum class EChallengeFilter : uint8_t
{
	CF_Default                                         = 0,
	CF_Progress                                        = 1,
	CF_END                                             = 2
};

// Enum TAGame.GFxData_EngagementEventsConfig_TA.ENotificationType
enum class ENotificationType : uint8_t
{
	NotificationType_Start                             = 0,
	NotificationType_End                               = 1,
	NotificationType_END                               = 2
};

// Enum TAGame.GFxData_Friends_TA.ENameDisplayRelationshipProxy
enum class ENameDisplayRelationshipProxy : uint8_t
{
	NameDisplayRelationshipProxy_NoChange              = 0,
	NameDisplayRelationshipProxy_ForcePlatform         = 1,
	NameDisplayRelationshipProxy_ForcePsyNet           = 2,
	NameDisplayRelationshipProxy_ForceAll              = 3,
	NameDisplayRelationshipProxy_END                   = 4
};

// Enum TAGame.GFxData_LegacyStatus_TA.ELegacyStatusSetState
enum class ELegacyStatusSetState : uint8_t
{
	LSSS_NotSet                                        = 0,
	LSSS_Updating                                      = 1,
	LSSS_UnableToUpdate                                = 2,
	LSSS_Set                                           = 3,
	LSSS_END                                           = 4
};

// Enum TAGame.GFxData_LocalPlayer_TA.ESplitScreenPosition
enum class ESplitScreenPosition : uint8_t
{
	SSP_Center                                         = 0,
	SSP_Left                                           = 1,
	SSP_Right                                          = 2,
	SSP_Top                                            = 3,
	SSP_Bottom                                         = 4,
	SSP_TopLeft                                        = 5,
	SSP_TopRight                                       = 6,
	SSP_BottomLeft                                     = 7,
	SSP_BottomRight                                    = 8,
	SSP_END                                            = 9
};

// Enum TAGame.GFxData_LocalPlayer_TA.EChallengeManagerState
enum class EChallengeManagerState : uint8_t
{
	Challenge_Sync                                     = 0,
	Challenge_Success                                  = 1,
	Challenge_Error                                    = 2,
	Challenge_END                                      = 3
};

// Enum TAGame.GFxData_MapPrefs_TA.EMapPrefType
enum class EMapPrefType : uint8_t
{
	MapPrefType_None                                   = 0,
	MapPrefType_Like                                   = 1,
	MapPrefType_Dislike                                = 2,
	MapPrefType_END                                    = 3
};

// Enum TAGame.GFxData_MatchHistoryManager_TA.ESyncStatus
enum class ESyncStatus : uint8_t
{
	SyncStatus_None                                    = 0,
	SyncStatus_Syncing                                 = 1,
	SyncStatus_Success                                 = 2,
	SyncStatus_Error                                   = 3,
	SyncStatus_END                                     = 4
};

// Enum TAGame.GFxData_MenuTreeNode_TA.ENodeBannerType
enum class ENodeBannerType : uint8_t
{
	NodeBannerType_None                                = 0,
	NodeBannerType_Unavailable                         = 1,
	NodeBannerType_Searching                           = 2,
	NodeBannerType_Locked                              = 3,
	NodeBannerType_END                                 = 4
};

// Enum TAGame.GFxData_OnlineMatchStatus_TA.SearchMessageType
enum class ESearchMessageType : uint8_t
{
	MessageType_Status                                 = 0,
	MessageType_Warning                                = 1,
	MessageType_Error                                  = 2,
	MessageType_Countdown                              = 3,
	MessageType_END                                    = 4
};

// Enum TAGame.GFxData_Party_TA.EPsyNetPartyStatus
enum class EPsyNetPartyStatus : uint8_t
{
	PsyNetParty_Disabled                               = 0,
	PsyNetParty_Connecting                             = 1,
	PsyNetParty_Connected                              = 2,
	PsyNetParty_Disconnected                           = 3,
	PsyNetParty_END                                    = 4
};

// Enum TAGame.GFxData_ProductFilter_TA.EFilterProductAttribute
enum class EFilterProductAttribute : uint8_t
{
	FPA_Indestructible                                 = 0,
	FPA_END                                            = 1
};

// Enum TAGame.GFxData_QuickChatBindings_TA.EQuickChatState
enum class EQuickChatState : uint8_t
{
	QCS_InGame                                         = 0,
	QCS_PostGame                                       = 1,
	QCS_PreGame                                        = 2,
	QCS_END                                            = 3
};

// Enum TAGame.GFxData_Restrictions_TA.EReasonType
enum class EReasonType : uint8_t
{
	RT_NotRestricted                                   = 0,
	RT_Credits                                         = 1,
	RT_ESportsTokens                                   = 2,
	RT_Merchandise                                     = 3,
	RT_END                                             = 4
};

// Enum TAGame.GFxData_UserSetting_TA.EUserSettingType
enum class EUserSettingType : uint8_t
{
	UserSettingType_List                               = 0,
	UserSettingType_Boolean                            = 1,
	UserSettingType_Scalar                             = 2,
	UserSettingType_END                                = 3
};

// Enum TAGame.ShopTabs_TA.EShopTabType
enum class EShopTabType : uint8_t
{
	ShopTabType_ShopCatalogueTable                     = 0,
	ShopTabType_EMtxCatalogCategory                    = 1,
	ShopTabType_Esports                                = 2,
	ShopTabType_END                                    = 3
};

// Enum TAGame.GFxData_TourEvent_TA.ETourEventStatus
enum class ETourEventStatus : uint8_t
{
	TES_NonePending                                    = 0,
	TES_Registered                                     = 1,
	TES_CheckInOpen                                    = 2,
	TES_CheckedIn                                      = 3,
	TES_GeneratingBrackets                             = 4,
	TES_MatchPending                                   = 5,
	TES_MatchReady                                     = 6,
	TES_InMatch                                        = 7,
	TES_MatchResultsPending                            = 8,
	TES_Paused                                         = 9,
	TES_MatchEnding                                    = 10,
	TES_TroubleJoining                                 = 11,
	TES_END                                            = 12
};

// Enum TAGame.GFxData_TrainingModeBrowser_TA.ETrainingModeSearchTypes
enum class ETrainingModeSearchTypes : uint8_t
{
	TMST_AllPublic                                     = 0,
	TMST_FeaturedOnly                                  = 1,
	TMST_END                                           = 2
};

// Enum TAGame.GFxData_UserBugReport_TA.EUserBugReportSubmitStatus
enum class EUserBugReportSubmitStatus : uint8_t
{
	UBRSS_None                                         = 0,
	UBRSS_Generated                                    = 1,
	UBRSS_Submitting                                   = 2,
	UBRSS_Success                                      = 3,
	UBRSS_Error                                        = 4,
	UBRSS_END                                          = 5
};

// Enum TAGame.GFxEngine_TA.ESoundStatePriority
enum class ESoundStatePriority : uint8_t
{
	SSP_None                                           = 0,
	SSP_Scoreboard                                     = 1,
	SSP_Replay                                         = 2,
	SSP_MidGameMenu                                    = 3,
	SSP_Pause                                          = 4,
	SSP_BeginRound                                     = 5,
	SSP_EndRound                                       = 6,
	SSP_WinnerMenu                                     = 7,
	SSP_MainMenu                                       = 8,
	SSP_PremiumGarage                                  = 9,
	SSP_Roulette                                       = 10,
	SSP_AudioPreview                                   = 11,
	SSP_MusicPreview                                   = 12,
	SSP_ThirdPartyOverlay                              = 13,
	SSP_LoadingScreen                                  = 14,
	SSP_END                                            = 15
};

// Enum TAGame.Replay_TA.EReplayVersion
enum class EReplayVersion : uint8_t
{
	ReplayVersion_Base                                 = 0,
	ReplayVersion_OnlineLoadout                        = 1,
	ReplayVersion_CameraSettings                       = 2,
	ReplayVersion_TeamLoadouts                         = 3,
	ReplayVersion_MatchType                            = 4,
	ReplayVersion_ActorName                            = 5,
	ReplayVersion_MutatorSeekFree                      = 6,
	ReplayVersion_ClubColors                           = 7,
	ReplayVersion_CameraTrack                          = 8,
	ReplayVersion_CarColorSet                          = 9,
	ReplayVersion_END                                  = 10
};

// Enum TAGame.Replay_TA.EReplayState
enum class EReplayState : uint8_t
{
	ReplayState_Idle                                   = 0,
	ReplayState_Recording                              = 1,
	ReplayState_Playing                                = 2,
	ReplayState_END                                    = 3
};

// Enum TAGame.StatGraph_TA.EStatGraphLayer
enum class EStatGraphLayer : uint8_t
{
	StatGraphLayer_Background                          = 0,
	StatGraphLayer_Text                                = 1,
	StatGraphLayer_Graph                               = 2,
	StatGraphLayer_END                                 = 3
};

// Enum TAGame.InterpTrackSkelControlRotation_TA.ERotationAxis
enum class ERotationAxis : uint8_t
{
	ROTAXIS_Yaw                                        = 0,
	ROTAXIS_Pitch                                      = 1,
	ROTAXIS_Roll                                       = 2,
	ROTAXIS_END                                        = 3
};

// Enum TAGame.MenuSequencer_TA.ESequenceStatus
enum class ESequenceStatus : uint8_t
{
	SS_Idle                                            = 0,
	SS_Entering                                        = 1,
	SS_Leaving                                         = 2,
	SS_Pending                                         = 3,
	SS_END                                             = 4
};

// Enum TAGame.MenuTreeNode_TA.ENodeEnabledRequirement
enum class ENodeEnabledRequirement : uint8_t
{
	NodeEnabledRequirement_InMainMenu                  = 0,
	NodeEnabledRequirement_RankedEnabled               = 1,
	NodeEnabledRequirement_AntiCheat                   = 2,
	NodeEnabledRequirement_END                         = 3
};

// Enum TAGame.MenuTreeNode_TA.ENodeBadgeType
enum class ENodeBadgeType : uint8_t
{
	NodeBadgeType_None                                 = 0,
	NodeBadgeType_Default                              = 1,
	NodeBadgeType_Success                              = 2,
	NodeBadgeType_Viral                                = 3,
	NodeBadgeType_END                                  = 4
};

// Enum TAGame.MenuTreeNode_Playlist_TA.EPlaylistSpecialType
enum class EPlaylistSpecialType : uint8_t
{
	PlaylistSpecialType_None                           = 0,
	PlaylistSpecialType_Dueling                        = 1,
	PlaylistSpecialType_LTM                            = 2,
	PlaylistSpecialType_END                            = 3
};

// Enum TAGame.MusicPlayerSave_TA.EMusicPlayerSave
enum class EMusicPlayerSave : uint8_t
{
	MusicPlayerSaveVersion_NewGameplayMusicSettings    = 0,
	MusicPlayerSaveVersion_END                         = 1
};

// Enum TAGame.MusicPlayerSave_TA.EGameplayMusicSetting
enum class EGameplayMusicSetting : uint8_t
{
	GameplayMusic_Off                                  = 0,
	GameplayMusic_TraningOnly                          = 1,
	GameplayMusic_MatchesOnly                          = 2,
	GameplayMusic_AlwaysOn                             = 3,
	GameplayMusic_Undefined                            = 4,
	GameplayMusic_END                                  = 5
};

// Enum TAGame.OrbitHitHandler_TA.EOrbitCenterLocation
enum class EOrbitCenterLocation : uint8_t
{
	OCB_BallHitLocation                                = 0,
	OCB_CenterOfGoal                                   = 1,
	OCB_END                                            = 2
};

// Enum TAGame.OrbitHitHandler_TA.EOrbitAxisBehavior
enum class EOrbitAxisBehavior : uint8_t
{
	OAB_StaticRotationAxis                             = 0,
	OAB_RandomRotationAxis                             = 1,
	OAB_END                                            = 2
};

// Enum TAGame.OutOfWorldVolume_TA.EOutOfWorld
enum class EOutOfWorld : uint8_t
{
	OOW_Touch                                          = 0,
	OOW_Untouch                                        = 1,
	OOW_END                                            = 2
};

// Enum TAGame.OverrideMaterialsHitHandler_TA.OverrideMaterialMode_TA
enum class EOverrideMaterialMode_TA : uint8_t
{
	OverrideMaterial_SkinOnly                          = 0,
	OverrideMaterial_ChassisOnly                       = 1,
	OverrideMaterial_Everything                        = 2,
	OverrideMaterial_END                               = 3
};

// Enum TAGame.ProductAsset_Body_TA.EForcedThumbnailColors
enum class EForcedThumbnailColors : uint8_t
{
	USE_NO_FORCED_COLORS                               = 0,
	USE_FORCED_ALL_COLORS                              = 1,
	USE_FORCED_TEAM_COLOR                              = 2,
	USE_FORCED_CUSTOM_COLOR                            = 3,
	USE_END                                            = 4
};

// Enum TAGame.ProductAssetLoader_TA.EAssetLoadState
enum class EAssetLoadState : uint8_t
{
	AssetLoadState_New                                 = 0,
	AssetLoadState_WaitingAsyncLoad                    = 1,
	AssetLoadState_AsyncLoad                           = 2,
	AssetLoadState_Loaded                              = 3,
	AssetLoadState_END                                 = 4
};

// Enum TAGame.ProductAttribute_Trademark_TA.ETrademarkGlyph
enum class ETrademarkGlyph : uint8_t
{
	TrademarkGlyph_TradeMark                           = 0,
	TrademarkGlyph_Registered                          = 1,
	TrademarkGlyph_Copyright                           = 2,
	TrademarkGlyph_END                                 = 3
};

// Enum TAGame.ProductEquipProfileSlot_Custom_TA.EEnableSlotCustomization
enum class EEnableSlotCustomization : uint8_t
{
	EnableSlotCustomization_Enabled                    = 0,
	EnableSlotCustomization_Disabled                   = 1,
	EnableSlotCustomization_END                        = 2
};

// Enum TAGame.ProductsArchiveSave_TA.EProductsArchiveSaveVersion
enum class EProductsArchiveSaveVersion : uint8_t
{
	ProductsArchiveSaveVersion_ConvertHashIDsToInstanceIDs = 0,
	ProductsArchiveSaveVersion_InstanceIDV2            = 1,
	ProductsArchiveSaveVersion_END                     = 2
};

// Enum TAGame.ProductsFavoriteSave_TA.EProductsFavoriteSaveVersion
enum class EProductsFavoriteSaveVersion : uint8_t
{
	EProductsFavoriteSaveVersion_ConvertHashIDsToInstanceIDs = 0,
	EProductsFavoriteSaveVersion_InstanceIDV2          = 1,
	EProductsFavoriteSaveVersion_END                   = 2
};

// Enum TAGame.ProductsSave_TA.EProductsSaveVersion
enum class EProductsSaveVersion : uint8_t
{
	EProductsSaveVersion_InstanceIDV2                  = 0,
	EProductsSaveVersion_END                           = 1
};

// Enum TAGame.ProfileCameraSave_TA.EGameplaySettingsSaveVersion
enum class EGameplaySettingsSaveVersion_0 : uint8_t
{
	EProfileCameraSaveVersion_DemoSpawnSelection       = 0,
	EProfileCameraSaveVersion_PerInputDeviceSettings   = 1,
	EProfileCameraSaveVersion_END                      = 2
};

// Enum TAGame.ProfileControlsSave_TA.EProfilePCSaveVersion
enum class EProfilePCSaveVersion_0 : uint8_t
{
	ProfileControlsSaveVersion_NewVibrationSettings    = 0,
	ProfileControlsSaveVersion_END                     = 1
};

// Enum TAGame.ProfileGamepadSave_TA.EProfileGamepadSaveVersion
enum class EProfileGamepadSaveVersion : uint8_t
{
	ProfileGamepadSaveVersion_NewDefaultControls       = 0,
	ProfileGamepadSaveVersion_END                      = 1
};

// Enum TAGame.ProfileGameplaySave_TA.EProfileGameplaySaveVersion
enum class EProfileGameplaySaveVersion : uint8_t
{
	ProfileGameplaySaveVersion_RankInfoDisplayType     = 0,
	ProfileGameplaySaveVersion_END                     = 1
};

// Enum TAGame.ProfileLoadoutSave_TA.ELoadoutSaveVersion
enum class ELoadoutSaveVersion : uint8_t
{
	ELoadoutSaveVersion_InstanceIDV2                   = 0,
	ELoadoutSaveVersion_NewColorSet                    = 1,
	ELoadoutSaveVersion_END                            = 2
};

// Enum TAGame.ProfilePCSave_TA.EProfilePCSaveVersion
enum class EProfilePCSaveVersion_1 : uint8_t
{
	ProfilePCSaveVersion_NewDefaultControls            = 0,
	ProfilePCSaveVersion_ModernDefaultControls_Old     = 1,
	ProfilePCSaveVersion_ModernDefaultControls         = 2,
	ProfilePCSaveVersion_END                           = 3
};

// Enum TAGame.ProfileQuickChatSave_TA.EQuickChatVersion
enum class EQuickChatVersion : uint8_t
{
	QuickChatVersion_AddPreGameQuickChat               = 0,
	QuickChatVersion_END                               = 1
};

// Enum TAGame.SampleHistory_TA.EGraphSummaryType
enum class EGraphSummaryType : uint8_t
{
	GraphSummaryType_Latest                            = 0,
	GraphSummaryType_Avg                               = 1,
	GraphSummaryType_MinValue                          = 2,
	GraphSummaryType_MaxValue                          = 3,
	GraphSummaryType_Sum                               = 4,
	GraphSummaryType_END                               = 5
};

// Enum TAGame.SaveObjectManager_TA.EInitSaveProviderResult
enum class EInitSaveProviderResult : uint8_t
{
	InitSaveProviderResult_Pending                     = 0,
	InitSaveProviderResult_Success                     = 1,
	InitSaveProviderResult_UserNotSignedIn             = 2,
	InitSaveProviderResult_Error                       = 3,
	InitSaveProviderResult_END                         = 4
};

// Enum TAGame.SeasonSave_TA.ESeasonSaveVersion
enum class ESeasonSaveVersion : uint8_t
{
	SeasonSaveVersion_AddIntroBotDifficulty            = 0,
	SeasonSaveVersion_END                              = 1
};

// Enum TAGame.SeqAct_CheckRotationAngle_TA.ECheckAxis
enum class ECheckAxis : uint8_t
{
	ECA_Pitch                                          = 0,
	ECA_Yaw                                            = 1,
	ECA_Roll                                           = 2,
	ECA_END                                            = 3
};

// Enum TAGame.SeqAct_SetLoadout_TA.EForcedTeamOverride
enum class EForcedTeamOverride : uint8_t
{
	ForcedTeamOverride_None                            = 0,
	ForcedTeamOverride_Blue                            = 1,
	ForcedTeamOverride_Orange                          = 2,
	ForcedTeamOverride_END                             = 3
};

// Enum TAGame.SkelControlSingleBoneCopy_TA.ECopyAxis
enum class ECopyAxis : uint8_t
{
	CopyAxis_X                                         = 0,
	CopyAxis_Y                                         = 1,
	CopyAxis_Z                                         = 2,
	CopyAxis_Pitch                                     = 3,
	CopyAxis_Yaw                                       = 4,
	CopyAxis_Roll                                      = 5,
	CopyAxis_END                                       = 6
};

// Enum TAGame.SpecialPickup_Spring_TA.ESpringState
enum class ESpringState : uint8_t
{
	SpringState_Traveling                              = 0,
	SpringState_PostHit                                = 1,
	SpringState_END                                    = 2
};

// Enum TAGame.SpecialPickup_BallFreeze_TA.BallFreezeState
enum class EBallFreezeState : uint8_t
{
	BallFreezeState_Freezing                           = 0,
	BallFreezeState_Frozen                             = 1,
	BallFreezeState_END                                = 2
};

// Enum TAGame.SpecialPickup_Football_TA.EThrowSetting
enum class EThrowSetting : uint8_t
{
	ETS_Forward                                        = 0,
	ETS_Backward                                       = 1,
	ETS_Side                                           = 2,
	ETS_END                                            = 3
};

// Enum TAGame.SpecialPickup_GrapplingHook_TA.ERopeState
enum class ERopeState : uint8_t
{
	RopeState_Traveling                                = 0,
	RopeState_Attached                                 = 1,
	RopeState_END                                      = 2
};

// Enum TAGame.StatFactory_TA.EFiveHitType
enum class EFiveHitType : uint8_t
{
	FiveHit_None                                       = 0,
	FiveHit_Low                                        = 1,
	FiveHit_High                                       = 2,
	FiveHit_END                                        = 3
};

// Enum TAGame.StatTitle_TA.EStatTrackingUnitType
enum class EStatTrackingUnitType : uint8_t
{
	CountUnit                                          = 0,
	SpeedUnit                                          = 1,
	DistanceUnit                                       = 2,
	EStatTrackingUnitType_END                          = 3
};

// Enum TAGame.StatusTrigger_Numerical_TA.TriggerConditionNumericalType
enum class ETriggerConditionNumericalType : uint8_t
{
	TCNT_GreaterThan                                   = 0,
	TCNT_LessThan                                      = 1,
	TCNT_Equal                                         = 2,
	TCNT_GreaterEqual                                  = 3,
	TCNT_LessThanEqual                                 = 4,
	TCNT_END                                           = 5
};

// Enum TAGame.Tutorial_TA.ETutorialOutput
enum class ETutorialOutput : uint8_t
{
	TutorialOutput_Ended                               = 0,
	TutorialOutput_Completed                           = 1,
	TutorialOutput_Failed                              = 2,
	TutorialOutput_ScreenFadedIn                       = 3,
	TutorialOutput_ScreenFadedOut                      = 4,
	TutorialOutput_AllMessagesDisplayed                = 5,
	TutorialOutput_Started                             = 6,
	TutorialOutput_Reset                               = 7,
	TutorialOutput_Skipped                             = 8,
	TutorialOutput_AnswerRight                         = 9,
	TutorialOutput_AnswerWrong                         = 10,
	TutorialOutput_END                                 = 11
};

// Enum TAGame.Tutorial_TA.ETutorialStatus
enum class ETutorialStatus : uint8_t
{
	TutorialStatus_None                                = 0,
	TutorialStatus_Failed                              = 1,
	TutorialStatus_Completed                           = 2,
	TutorialStatus_END                                 = 3
};

// Enum TAGame.Tutorial_TA.EPlayerDriveType
enum class EPlayerDriveType : uint8_t
{
	PlayerDriveType_All                                = 0,
	PlayerDriveType_Player                             = 1,
	PlayerDriveType_Bot                                = 2,
	PlayerDriveType_END                                = 3
};

// Enum TAGame.VehiclePickup_Boost_TA.EBoostType
enum class EBoostType : uint8_t
{
	BoostType_Unknown                                  = 0,
	BoostType_Pill                                     = 1,
	BoostType_Pad                                      = 2,
	BoostType_END                                      = 3
};

// Enum TAGame.SettingsSnapshotManager_TA.ESaveExportSchemaVersion
enum class ESaveExportSchemaVersion : uint8_t
{
	SaveExportVersion_Base                             = 0,
	SaveExportVersion_Products                         = 1,
	SaveExportVersion_LoadoutUsage                     = 2,
	SaveExportVersion_Max                              = 3
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
