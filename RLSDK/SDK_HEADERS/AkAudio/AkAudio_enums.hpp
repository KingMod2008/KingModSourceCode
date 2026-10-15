/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: AkAudio\AkAudio_enums.hpp
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

// Enum AkAudio.AkParamGroup.EAttenuationType
enum class EAttenuationType : uint8_t
{
	AttenuationType_Default                            = 0,
	AttenuationType_None                               = 1,
	AttenuationType_END                                = 2
};

// Enum AkAudio.AkParamGroup.EReflectionSendType
enum class EReflectionSendType : uint8_t
{
	ReflectionSendType_None                            = 0,
	ReflectionSendType_Slapback                        = 1,
	ReflectionSendType_ArenaReverb                     = 2,
	ReflectionSendType_END                             = 3
};

// Enum AkAudio.AkPlaySoundComponent.EAkPlaySoundReceiver
enum class EAkPlaySoundReceiver : uint8_t
{
	PlaySoundReceiver_All                              = 0,
	PlaySoundReceiver_Local                            = 1,
	PlaySoundReceiver_NonLocal                         = 2,
	PlaySoundReceiver_END                              = 3
};

// Enum AkAudio.AkBusActor.EPinnedAxisType
enum class EPinnedAxisType : uint8_t
{
	PinnedAxis_X                                       = 0,
	PinnedAxis_Y                                       = 1,
	PinnedAxis_Z                                       = 2,
	PinnedAxis_None                                    = 3,
	PinnedAxis_END                                     = 4
};

// Enum AkAudio.AkBusActor.EBusEmitterType
enum class EBusEmitterType : uint8_t
{
	BusEmitterType_Reflection                          = 0,
	BusEmitterType_Reverb                              = 1,
	BusEmitterType_None                                = 2,
	BusEmitterType_END                                 = 3
};

// Enum AkAudio.AkSoundSource.EAkEnvironmentType
enum class EAkEnvironmentType : uint8_t
{
	EnvironmentType_SpatializedAudio                   = 0,
	EnvironmentType_UnspatializedAudio                 = 1,
	EnvironmentType_Music                              = 2,
	EnvironmentType_None                               = 3,
	EnvironmentType_END                                = 4
};

// Enum AkAudio.AkSoundSource.EAkCallbackType
enum class EAkCallbackType : uint8_t
{
	AkCallbackType_Marker                              = 0,
	AkCallbackType_Duration                            = 1,
	AkCallbackType_END                                 = 2
};

// Enum AkAudio.AkDevice.EAkDynamicRangeType
enum class EAkDynamicRangeType : uint8_t
{
	AkDRT_Low                                          = 0,
	AkDRT_Medium                                       = 1,
	AkDRT_High                                         = 2,
	AkDRT_END                                          = 3
};

// Enum AkAudio.AkDevice.EAkOutputType
enum class EAkOutputType : uint8_t
{
	AkOT_Speakers                                      = 0,
	AKOT_Headphones                                    = 1,
	EAkOutputType_END                                  = 2
};

// Enum AkAudio.AkDevice.EAkListenerSpacialization
enum class EAkListenerSpacialization : uint8_t
{
	AkLS_3D                                            = 0,
	AkLS_Left                                          = 1,
	AkLS_Right                                         = 2,
	AkLS_END                                           = 3
};

// Enum AkAudio.SeqAct_AkEnvironment.EAkEnvironmentTarget
enum class EAkEnvironmentTarget : uint8_t
{
	AkEnvironmentTarget_LevelDefault                   = 0,
	AkEnvironmentTarget_Actor                          = 1,
	AkEnvironmentTarget_END                            = 2
};

// Enum AkAudio.SeqAct_AkPlayMusicWithCues.EMusicSyncType
enum class EMusicSyncType : uint8_t
{
	MusicSyncType_EndOfEvent                           = 0,
	MusicSyncType_UserCue                              = 1,
	MusicSyncType_END                                  = 2
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
