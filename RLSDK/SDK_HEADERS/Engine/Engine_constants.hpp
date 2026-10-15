/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: Engine\Engine_constants.hpp
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
# Constants
# ========================================================================================= #
*/

#define CONST_MINFLOORZ                                             0.7
#define CONST_ACTORMAXSTEPHEIGHT                                    35.0
#define CONST_RBSTATE_LOCATIONSCALE                                 100.0
#define CONST_RBSTATE_QUATBITS                                      18
#define CONST_RBSTATE_LINVELSCALE                                   100.0
#define CONST_RBSTATE_ANGVELSCALE                                   10000.0
#define CONST_RB_None                                               0x00
#define CONST_RB_NeedsUpdate                                        0x01
#define CONST_RB_Sleeping                                           0x02
#define CONST_REP_RBLOCATION_ERROR_TOLERANCE_SQ                     16.0f
#define CONST_TRACEFLAG_ForceController                             16
#define CONST_TRACEFLAG_Blocking                                    8
#define CONST_TRACEFLAG_SkipMovers                                  4
#define CONST_TRACEFLAG_PhysicsVolumes                              2
#define CONST_TRACEFLAG_Bullet                                      1
#define CONST_SDPG_NumBits                                          3
#define CONST_BLOCKEDPATHCOST                                       10000000
#define CONST_LATENT_MOVETOWARD                                     503
#define CONST_INFINITE_PATH_COST                                    10000000
#define CONST_MAX_ACTIVE_CAMERA_ANIMS                               8
#define CONST_GET_SAVE_SLOT_INVALID                                 -1
#define CONST_GET_SAVE_SLOT_ERROR                                   -2
#define CONST_COMMON_DATA_SAVE_SLOT_INDEX                           -1
#define CONST_SAVE_SYSTEM_VERSION_KEY                               "CloudSaveSystemVersion"
#define CONST_SAVE_DATA_BLOB_NAME_KEY                               "DataBlobName"
#define CONST_DATA_STORE_ID_KEY                                     "DataStoreID"
#define CONST_NUM_SAVE_SLOTS_KEY                                    "NumSaveSlots"
#define CONST_DEFAULT_SIZE_X                                        1024
#define CONST_DEFAULT_SIZE_Y                                        768
#define CONST_MAX_SUPPORTED_GAMEPADS                                4
#define CONST_MaxHistory                                            16
#define CONST_COVERLINK_DangerDist                                  1536.f
#define CONST_COVERLINK_EdgeExposureDot                             0.85f
#define CONST_COVERLINK_EdgeCheckDot                                0.25f
#define CONST_COVERLINK_ExposureDot                                 0.4f
#define CONST_EpochYear                                             1970
#define CONST_SecondsInMinute                                       60
#define CONST_SecondsInHour                                         3600
#define CONST_SecondsInDay                                          86400
#define CONST_SecondsInMonth                                        2629743
#define CONST_SecondsInYear                                         31556926
#define CONST_NULLCHARACTER                                         127
#define CONST_FSM_DEFAULTRECYCLETIME                                0.2
#define CONST_HeaderFlags_NoEventStrings                            1
#define CONST_GAMEEVENT_MATCH_STARTED                               0
#define CONST_GAMEEVENT_MATCH_ENDED                                 1
#define CONST_GAMEEVENT_ROUND_STARTED                               2
#define CONST_GAMEEVENT_ROUND_ENDED                                 3
#define CONST_GAMEEVENT_GAME_CLASS                                  6
#define CONST_GAMEEVENT_GAME_OPTION_URL                             7
#define CONST_GAMEEVENT_GAME_MAPNAME                                8
#define CONST_GAMEEVENT_MEMORYUSAGE_POLL                            35
#define CONST_GAMEEVENT_FRAMERATE_POLL                              36
#define CONST_GAMEEVENT_NETWORKUSAGEIN_POLL                         37
#define CONST_GAMEEVENT_NETWORKUSAGEOUT_POLL                        38
#define CONST_GAMEEVENT_PING_POLL                                   39
#define CONST_GAMEEVENT_RENDERTHREAD_POLL                           40
#define CONST_GAMEEVENT_GAMETHREAD_POLL                             41
#define CONST_GAMEEVENT_GPUFRAMETIME_POLL                           42
#define CONST_GAMEEVENT_FRAMETIME_POLL                              43
#define CONST_GAMEEVENT_TEAM_CREATED                                50
#define CONST_GAMEEVENT_TEAM_GAME_SCORE                             51
#define CONST_GAMEEVENT_TEAM_MATCH_WON                              4
#define CONST_GAMEEVENT_TEAM_ROUND_WON                              5
#define CONST_GAMEEVENT_TEAM_ROUND_STALEMATE                        52
#define CONST_GAMEEVENT_PLAYER_LOGIN                                100
#define CONST_GAMEEVENT_PLAYER_LOGOUT                               101
#define CONST_GAMEEVENT_PLAYER_SPAWN                                102
#define CONST_GAMEEVENT_PLAYER_MATCH_WON                            103
#define CONST_GAMEEVENT_PLAYER_KILL                                 104
#define CONST_GAMEEVENT_PLAYER_LOCATION_POLL                        105
#define CONST_GAMEEVENT_PLAYER_TEAMCHANGE                           106
#define CONST_GAMEEVENT_PLAYER_KILL_STREAK                          107
#define CONST_GAMEEVENT_PLAYER_DEATH                                108
#define CONST_GAMEEVENT_PLAYER_ROUND_WON                            109
#define CONST_GAMEEVENT_PLAYER_ROUND_STALEMATE                      110
#define CONST_GAMEEVENT_WEAPON_DAMAGE                               150
#define CONST_GAMEEVENT_WEAPON_DAMAGE_MELEE                         151
#define CONST_GAMEEVENT_WEAPON_FIRED                                152
#define CONST_GAMEEVENT_PLAYER_KILL_NORMAL                          200
#define CONST_GAMEEVENT_GENERIC_PARAM_LIST_START                    300
#define CONST_GAMEEVENT_GENERIC_PARAM_LIST_END                      400
#define CONST_GAMEEVENT_GAME_SPECIFIC                               1000
#define CONST_GAMEEVENT_MAX_EVENTID                                 0x0000FFFF
#define CONST_SCENEFILTER_None                                      0x00000000
#define CONST_SCENEFILTER_IncludeTransient                          0x00000001
#define CONST_SCENEFILTER_InputProcessorOnly                        0x00000002
#define CONST_SCENEFILTER_PausersOnly                               0x00000004
#define CONST_SCENEFILTER_PrimitiveUsersOnly                        0x00000008
#define CONST_SCENEFILTER_UsesPostProcessing                        0x00000010
#define CONST_SCENEFILTER_ReceivesFocus                             0x00000020
#define CONST_SCENEFILTER_Any                                       0xFFFFFFFF
#define CONST_MAX_INSTANCES_PER_CLASS                               5
#define CONST_MAX_BOOKMARK_NUMBER                                   10
#define CONST_MAXCLIENTUPDATEINTERVAL                               0.25
#define CONST_CLIENTADJUSTUPDATECOST                                180.0
#define CONST_MAXNEARZEROVELOCITYSQUARED                            9.0
#define CONST_MAXPOSITIONERRORSQUARED                               3.0
#define CONST_MAX_AIGROUP_NUMBER                                    10
#define CONST_LINECHECK_GRANULARITY                                 768.f
#define CONST_NUM_PATHFINDING_PARAMS                                9
#define CONST_NumBreadCrumbs                                        10
#define CONST_PROCBUILDING_VERSION                                  1
#define CONST_ROOF_MINZ                                             0.7
/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
