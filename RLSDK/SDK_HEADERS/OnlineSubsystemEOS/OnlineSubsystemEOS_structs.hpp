/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: OnlineSubsystemEOS\OnlineSubsystemEOS_structs.hpp
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

// ScriptStruct OnlineSubsystemEOS.OnlinePlayerInterfaceEOS.OnlineStatusMappingEOS
// 0x0018
struct FOnlineStatusMappingEOS
{
	int32_t                                            StatusId;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      StatusString;                                  // 0x0008 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FOnlineStatusMappingEOS& other) const { return memcmp(this, &other, sizeof(FOnlineStatusMappingEOS)) == 0; }
	bool operator!=(const FOnlineStatusMappingEOS& other) const { return !(*this == other); }
	bool operator<(const FOnlineStatusMappingEOS& other) const { return memcmp(this, &other, sizeof(FOnlineStatusMappingEOS)) < 0; }
};

// ScriptStruct OnlineSubsystemEOS.OnlinePlayerInterfaceEOS.LoginDelegates
// 0x0010
struct FLoginDelegates
{
	class TArray<struct FScriptDelegate>               Delegates;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLoginDelegates& other) const { return memcmp(this, &other, sizeof(FLoginDelegates)) == 0; }
	bool operator!=(const FLoginDelegates& other) const { return !(*this == other); }
	bool operator<(const FLoginDelegates& other) const { return memcmp(this, &other, sizeof(FLoginDelegates)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
