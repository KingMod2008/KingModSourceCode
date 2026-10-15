/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: OnlineSubsystemSteamworks\OnlineSubsystemSteamworks_enums.hpp
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

// Enum OnlineSubsystemSteamworks.OnlineGameInterfaceSteamworks.ESteamMatchmakingType
enum class ESteamMatchmakingType : uint8_t
{
	SMT_Invalid                                        = 0,
	SMT_LAN                                            = 1,
	SMT_Internet                                       = 2,
	SMT_END                                            = 3
};

// Enum OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ELeaderboardSortType
enum class ELeaderboardSortType : uint8_t
{
	LST_Ascending                                      = 0,
	LST_Descending                                     = 1,
	LST_END                                            = 2
};

// Enum OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ELeaderboardRequestType
enum class ELeaderboardRequestType : uint8_t
{
	LRT_Global                                         = 0,
	LRT_Player                                         = 1,
	LRT_Friends                                        = 2,
	LRT_END                                            = 3
};

// Enum OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ELeaderboardFormat
enum class ELeaderboardFormat : uint8_t
{
	LF_Number                                          = 0,
	LF_Seconds                                         = 1,
	LF_Milliseconds                                    = 2,
	LF_END                                             = 3
};

// Enum OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.ELeaderboardUpdateType
enum class ELeaderboardUpdateType : uint8_t
{
	LUT_KeepBest                                       = 0,
	LUT_Force                                          = 1,
	LUT_END                                            = 2
};

// Enum OnlineSubsystemSteamworks.OnlineSubsystemSteamworks.EMuteType
enum class EMuteType : uint8_t
{
	MUTE_None                                          = 0,
	MUTE_AllButFriends                                 = 1,
	MUTE_All                                           = 2,
	MUTE_END                                           = 3
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
