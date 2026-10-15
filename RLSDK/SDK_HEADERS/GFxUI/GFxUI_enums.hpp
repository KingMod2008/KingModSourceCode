/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: GFxUI\GFxUI_enums.hpp
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

// Enum GFxUI.SwfMovie.EEdition
enum class EEdition : uint8_t
{
	Edition_Default                                    = 0,
	Edition_China                                      = 1,
	Edition_END                                        = 2
};

// Enum GFxUI.SwfMovie.FlashTextureRescale
enum class EFlashTextureRescale : uint8_t
{
	FlashTextureScale_High                             = 0,
	FlashTextureScale_Low                              = 1,
	FlashTextureScale_NextLow                          = 2,
	FlashTextureScale_Mult4                            = 3,
	FlashTextureScale_None                             = 4,
	FlashTextureScale_END                              = 5
};

// Enum GFxUI.GFxMoviePlayer.ASType
enum class EASType : uint8_t
{
	AS_Undefined                                       = 0,
	AS_Null                                            = 1,
	AS_Number                                          = 2,
	AS_Int                                             = 3,
	AS_String                                          = 4,
	AS_Boolean                                         = 5,
	AS_Texture                                         = 6,
	AS_UInt                                            = 7,
	AS_END                                             = 8
};

// Enum GFxUI.GFxMoviePlayer.GFxAlign
enum class EGFxAlign : uint8_t
{
	Align_Center                                       = 0,
	Align_TopCenter                                    = 1,
	Align_BottomCenter                                 = 2,
	Align_CenterLeft                                   = 3,
	Align_CenterRight                                  = 4,
	Align_TopLeft                                      = 5,
	Align_TopRight                                     = 6,
	Align_BottomLeft                                   = 7,
	Align_BottomRight                                  = 8,
	Align_END                                          = 9
};

// Enum GFxUI.GFxMoviePlayer.GFxScaleMode
enum class EGFxScaleMode : uint8_t
{
	SM_NoScale                                         = 0,
	SM_ShowAll                                         = 1,
	SM_ExactFit                                        = 2,
	SM_NoBorder                                        = 3,
	SM_END                                             = 4
};

// Enum GFxUI.GFxMoviePlayer.GFxCollectionMode
enum class EGFxCollectionMode : uint8_t
{
	GC_Quick                                           = 0,
	GC_Medium                                          = 1,
	GC_Full                                            = 2,
	GC_END                                             = 3
};

// Enum GFxUI.GFxMoviePlayer.GFxTimingMode
enum class EGFxTimingMode : uint8_t
{
	TM_Game                                            = 0,
	TM_Real                                            = 1,
	TM_END                                             = 2
};

// Enum GFxUI.GFxMoviePlayer.GFxRenderTextureMode
enum class EGFxRenderTextureMode : uint8_t
{
	RTM_Opaque                                         = 0,
	RTM_Alpha                                          = 1,
	RTM_AlphaComposite                                 = 2,
	RTM_END                                            = 3
};

// Enum GFxUI.GFxEngine.EWeatherVariant
enum class EWeatherVariant : uint8_t
{
	WeatherVariant_None                                = 0,
	WeatherVariant_Dawn                                = 1,
	WeatherVariant_Day                                 = 2,
	WeatherVariant_Dusk                                = 3,
	WeatherVariant_Lab                                 = 4,
	WeatherVariant_Night                               = 5,
	WeatherVariant_Rain                                = 6,
	WeatherVariant_Snow                                = 7,
	WeatherVariant_END                                 = 8
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
