/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: AkAudio\AkAudio_structs.hpp
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

// ScriptStruct AkAudio.AkParamGroup.AkParamSet
// 0x00A0
struct FAkParamSet
{
	struct FMap_Mirror                                 RTCPs;                                         // 0x0000 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FMap_Mirror                                 Switches;                                      // 0x0050 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FAkParamSet& other) const { return memcmp(this, &other, sizeof(FAkParamSet)) == 0; }
	bool operator!=(const FAkParamSet& other) const { return !(*this == other); }
	bool operator<(const FAkParamSet& other) const { return memcmp(this, &other, sizeof(FAkParamSet)) < 0; }
};

// ScriptStruct AkAudio.AkSoundSource.ActiveSound
// 0x0010
struct FActiveSound
{
	class UAkSoundCue*                                 Sound;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            PlayId;                                        // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            StopId;                                        // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FActiveSound& other) const { return memcmp(this, &other, sizeof(FActiveSound)) == 0; }
	bool operator!=(const FActiveSound& other) const { return !(*this == other); }
	bool operator<(const FActiveSound& other) const { return memcmp(this, &other, sizeof(FActiveSound)) < 0; }
};

// ScriptStruct AkAudio.AkEnvironments.uint
// 0x0004
struct Fuint
{
	int32_t                                            dummyint;                                      // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const Fuint& other) const { return memcmp(this, &other, sizeof(Fuint)) == 0; }
	bool operator!=(const Fuint& other) const { return !(*this == other); }
	bool operator<(const Fuint& other) const { return memcmp(this, &other, sizeof(Fuint)) < 0; }
};

// ScriptStruct AkAudio.AkEnvironments.AkEnvironment
// 0x0020
struct FAkEnvironment
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            Priority;                                      // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WetValue;                                      // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DryValue;                                      // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct Fuint                                       HashedEnvID;                                   // 0x001C (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAkEnvironment& other) const { return memcmp(this, &other, sizeof(FAkEnvironment)) == 0; }
	bool operator!=(const FAkEnvironment& other) const { return !(*this == other); }
	bool operator<(const FAkEnvironment& other) const { return memcmp(this, &other, sizeof(FAkEnvironment)) < 0; }
};

// ScriptStruct AkAudio.AkEnvironments.AkActorEnvironment
// 0x0018
struct FAkActorEnvironment
{
	class TArray<struct FAkEnvironment>                Environments;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class AActor*                                      TargetActor;                                   // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FAkActorEnvironment& other) const { return memcmp(this, &other, sizeof(FAkActorEnvironment)) == 0; }
	bool operator!=(const FAkActorEnvironment& other) const { return !(*this == other); }
	bool operator<(const FAkActorEnvironment& other) const { return memcmp(this, &other, sizeof(FAkActorEnvironment)) < 0; }
};

// ScriptStruct AkAudio.AkMusicAnalysis.MusicAnalysisInfo
// 0x001C
struct FMusicAnalysisInfo
{
	float                                              LowEnergy;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<float>                                Frequencies;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              HighEnergy;                                    // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FMusicAnalysisInfo& other) const { return memcmp(this, &other, sizeof(FMusicAnalysisInfo)) == 0; }
	bool operator!=(const FMusicAnalysisInfo& other) const { return !(*this == other); }
	bool operator<(const FMusicAnalysisInfo& other) const { return memcmp(this, &other, sizeof(FMusicAnalysisInfo)) < 0; }
};

// ScriptStruct AkAudio.AkRevPhysicsSimulation.AkRevSimPhysicsControls
// 0x0020
struct FAkRevSimPhysicsControls
{
	float                                              Weight;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EngineTorque;                                  // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              BreakingHorsePower;                            // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<float>                                GearRatios;                                    // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FAkRevSimPhysicsControls& other) const { return memcmp(this, &other, sizeof(FAkRevSimPhysicsControls)) == 0; }
	bool operator!=(const FAkRevSimPhysicsControls& other) const { return !(*this == other); }
	bool operator<(const FAkRevSimPhysicsControls& other) const { return memcmp(this, &other, sizeof(FAkRevSimPhysicsControls)) < 0; }
};

// ScriptStruct AkAudio.AkRevPhysicsSimulation.AkRevSimFrame
// 0x0010
struct FAkRevSimFrame
{
	float                                              RPM;                                           // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Gear;                                          // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            RevGear;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              Velocity;                                      // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FAkRevSimFrame& other) const { return memcmp(this, &other, sizeof(FAkRevSimFrame)) == 0; }
	bool operator!=(const FAkRevSimFrame& other) const { return !(*this == other); }
	bool operator<(const FAkRevSimFrame& other) const { return memcmp(this, &other, sizeof(FAkRevSimFrame)) < 0; }
};

// ScriptStruct AkAudio.AkRevPhysicsSimulation.AkRevSimUpdateParams
// 0x0048
struct FAkRevSimUpdateParams
{
	float                                              Throttle;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Brake;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              EngineFrictionScale;                           // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              GroundFrictionScale;                           // 0x000C (0x0004) [0x0000000000000000]               
	float                                              ClutchedGearRatio;                             // 0x0010 (0x0004) [0x0000000000000000]               
	uint32_t                                           bEnableUpShifting : 1;                         // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FAkRevSimPhysicsControls                    Controls;                                      // 0x0018 (0x0020) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FAkRevSimFrame                              frame;                                         // 0x0038 (0x0010) [0x0000000000000000]               

	bool operator==(const FAkRevSimUpdateParams& other) const { return memcmp(this, &other, sizeof(FAkRevSimUpdateParams)) == 0; }
	bool operator!=(const FAkRevSimUpdateParams& other) const { return !(*this == other); }
	bool operator<(const FAkRevSimUpdateParams& other) const { return memcmp(this, &other, sizeof(FAkRevSimUpdateParams)) < 0; }
};

// ScriptStruct AkAudio.AkSoundBanksInfo.SoundBankInfo
// 0x0030
struct FSoundBankInfo
{
	class FString                                      ShortName;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      RelativePath;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Language;                                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSoundBankInfo& other) const { return memcmp(this, &other, sizeof(FSoundBankInfo)) == 0; }
	bool operator!=(const FSoundBankInfo& other) const { return !(*this == other); }
	bool operator<(const FSoundBankInfo& other) const { return memcmp(this, &other, sizeof(FSoundBankInfo)) < 0; }
};

// ScriptStruct AkAudio.InterpTrackAkEvent.AkEventTrackKey
// 0x0010
struct FAkEventTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class UAkSoundCue*                                 Event;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAkEventTrackKey& other) const { return memcmp(this, &other, sizeof(FAkEventTrackKey)) == 0; }
	bool operator!=(const FAkEventTrackKey& other) const { return !(*this == other); }
	bool operator<(const FAkEventTrackKey& other) const { return memcmp(this, &other, sizeof(FAkEventTrackKey)) < 0; }
};

// ScriptStruct AkAudio.SeqAct_AkPlayMusicWithCues.MusicSyncEvent
// 0x0011
struct FMusicSyncEvent
{
	class FString                                      CueName;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EMusicSyncType                                     CueType;                                       // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FMusicSyncEvent& other) const { return memcmp(this, &other, sizeof(FMusicSyncEvent)) == 0; }
	bool operator!=(const FMusicSyncEvent& other) const { return !(*this == other); }
	bool operator<(const FMusicSyncEvent& other) const { return memcmp(this, &other, sizeof(FMusicSyncEvent)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
