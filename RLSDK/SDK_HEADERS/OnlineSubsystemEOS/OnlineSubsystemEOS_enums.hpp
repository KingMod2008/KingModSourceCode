/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: OnlineSubsystemEOS\OnlineSubsystemEOS_enums.hpp
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

// Enum OnlineSubsystemEOS.OnlineVoiceInterfaceEOS.EPlayerVoiceAgreementStatus
enum class EPlayerVoiceAgreementStatus : uint8_t
{
	PVAS_None                                          = 0,
	PVAS_NotResponded                                  = 1,
	PVAS_Accepted                                      = 2,
	PVAS_Declined                                      = 3,
	PVAS_END                                           = 4
};

// Enum OnlineSubsystemEOS.OnlineVoiceInterfaceEOS.EPlayerVoiceTransitionState
enum class EPlayerVoiceTransitionState : uint8_t
{
	PVTS_Idle                                          = 0,
	PVTS_Joining                                       = 1,
	PVTS_Leaving                                       = 2,
	PVTS_END                                           = 3
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
