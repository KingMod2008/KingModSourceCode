/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: Engine\Engine_enums.hpp
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

// Enum Engine.Actor.EActorMetricsType
enum class EActorMetricsType : uint8_t
{
	METRICS_VERTS                                      = 0,
	METRICS_TRIS                                       = 1,
	METRICS_SECTIONS                                   = 2,
	METRICS_END                                        = 3
};

// Enum Engine.Actor.EMoveDir
enum class EMoveDir : uint8_t
{
	MD_Stationary                                      = 0,
	MD_Forward                                         = 1,
	MD_Backward                                        = 2,
	MD_Left                                            = 3,
	MD_Right                                           = 4,
	MD_Up                                              = 5,
	MD_Down                                            = 6,
	MD_END                                             = 7
};

// Enum Engine.Actor.EPhysics
enum class EPhysics : uint8_t
{
	PHYS_None                                          = 0,
	PHYS_Walking                                       = 1,
	PHYS_Falling                                       = 2,
	PHYS_Swimming                                      = 3,
	PHYS_Flying                                        = 4,
	PHYS_Rotating                                      = 5,
	PHYS_Projectile                                    = 6,
	PHYS_Interpolating                                 = 7,
	PHYS_Spider                                        = 8,
	PHYS_RigidBody                                     = 9,
	PHYS_SoftBody                                      = 10,
	PHYS_NavMeshWalking                                = 11,
	PHYS_Unused                                        = 12,
	PHYS_Custom                                        = 13,
	PHYS_END                                           = 14
};

// Enum Engine.Actor.EHighContrastRenderingID
enum class EHighContrastRenderingID : uint8_t
{
	HighContrastRenderingID_Team0                      = 0,
	HighContrastRenderingID_Team1                      = 1,
	HighContrastRenderingID_Neutral                    = 2,
	HighContrastRenderingID_Ball                       = 3,
	HighContrastRenderingID_END                        = 4
};

// Enum Engine.Actor.ECollisionType
enum class ECollisionType : uint8_t
{
	COLLIDE_CustomDefault                              = 0,
	COLLIDE_NoCollision                                = 1,
	COLLIDE_BlockAll                                   = 2,
	COLLIDE_BlockWeapons                               = 3,
	COLLIDE_TouchAll                                   = 4,
	COLLIDE_TouchWeapons                               = 5,
	COLLIDE_BlockAllButWeapons                         = 6,
	COLLIDE_TouchAllButWeapons                         = 7,
	COLLIDE_BlockWeaponsKickable                       = 8,
	COLLIDE_END                                        = 9
};

// Enum Engine.Actor.ETravelType
enum class ETravelType : uint8_t
{
	TRAVEL_Absolute                                    = 0,
	TRAVEL_Partial                                     = 1,
	TRAVEL_Relative                                    = 2,
	TRAVEL_END                                         = 3
};

// Enum Engine.Actor.EDoubleClickDir
enum class EDoubleClickDir : uint8_t
{
	DCLICK_None                                        = 0,
	DCLICK_Left                                        = 1,
	DCLICK_Right                                       = 2,
	DCLICK_Forward                                     = 3,
	DCLICK_Back                                        = 4,
	DCLICK_Active                                      = 5,
	DCLICK_Done                                        = 6,
	DCLICK_END                                         = 7
};

// Enum Engine.Actor.ENetRole
enum class ENetRole : uint8_t
{
	ROLE_None                                          = 0,
	ROLE_SimulatedProxy                                = 1,
	ROLE_AutonomousProxy                               = 2,
	ROLE_Authority                                     = 3,
	ROLE_END                                           = 4
};

// Enum Engine.Actor.EHighContrastRenderingMode
enum class EHighContrastRenderingMode : uint8_t
{
	HighContrastRenderingMode_Disabled                 = 0,
	HighContrastRenderingMode_WorldAndHighContrastPass = 1,
	HighContrastRenderingMode_OnlyHighContrastPass     = 2,
	HighContrastRenderingMode_AcceptsHighContrastDecals = 3,
	HighContrastRenderingMode_END                      = 4
};

// Enum Engine.Actor.EForceMode
enum class EForceMode : uint8_t
{
	ForceMode_Force                                    = 0,
	ForceMode_Impulse                                  = 1,
	ForceMode_Velocity                                 = 2,
	ForceMode_SmoothImpulse                            = 3,
	ForceMode_SmoothVelocity                           = 4,
	ForceMode_Acceleration                             = 5,
	ForceMode_END                                      = 6
};

// Enum Engine.PrimitiveComponent.GJKResult
enum class EGJKResult : uint8_t
{
	GJK_Intersect                                      = 0,
	GJK_NoIntersection                                 = 1,
	GJK_Fail                                           = 2,
	GJK_END                                            = 3
};

// Enum Engine.Scene.EDetailMode
enum class EDetailMode : uint8_t
{
	DM_Low                                             = 0,
	DM_Medium                                          = 1,
	DM_High                                            = 2,
	DM_END                                             = 3
};

// Enum Engine.Scene.ESceneDepthPriorityGroup
enum class ESceneDepthPriorityGroup : uint8_t
{
	SDPG_UnrealEdBackground                            = 0,
	SDPG_World                                         = 1,
	SDPG_Foreground                                    = 2,
	SDPG_UnrealEdForeground                            = 3,
	SDPG_PostProcess                                   = 4,
	SDPG_END                                           = 5
};

// Enum Engine.PrimitiveComponent.ERadialImpulseFalloff
enum class ERadialImpulseFalloff : uint8_t
{
	RIF_Constant                                       = 0,
	RIF_Linear                                         = 1,
	RIF_END                                            = 2
};

// Enum Engine.PrimitiveComponent.ERBCollisionChannel
enum class ERBCollisionChannel : uint8_t
{
	RBCC_Default                                       = 0,
	RBCC_Nothing                                       = 1,
	RBCC_Pawn                                          = 2,
	RBCC_Vehicle                                       = 3,
	RBCC_Water                                         = 4,
	RBCC_GameplayPhysics                               = 5,
	RBCC_EffectPhysics                                 = 6,
	RBCC_Ball                                          = 7,
	RBCC_VehicleBlocker                                = 8,
	RBCC_BallBlocker                                   = 9,
	RBCC_Untitled4                                     = 10,
	RBCC_Cloth                                         = 11,
	RBCC_FluidDrain                                    = 12,
	RBCC_SoftBody                                      = 13,
	RBCC_FracturedMeshPart                             = 14,
	RBCC_BlockingVolume                                = 15,
	RBCC_DeadPawn                                      = 16,
	RBCC_Clothing                                      = 17,
	RBCC_ClothingCollision                             = 18,
	RBCC_END                                           = 19
};

// Enum Engine.Pylon.ENavMeshEdgeType
enum class ENavMeshEdgeType : uint8_t
{
	NAVEDGE_Normal                                     = 0,
	NAVEDGE_Mantle                                     = 1,
	NAVEDGE_Coverslip                                  = 2,
	NAVEDGE_SwatTurn                                   = 3,
	NAVEDGE_DropDown                                   = 4,
	NAVEDGE_PathObject                                 = 5,
	NAVEDGE_BackRefDummy                               = 6,
	NAVEDGE_Jump                                       = 7,
	NAVEDGE_END                                        = 8
};

// Enum Engine.AkBank.EBankLoadStatus
enum class EBankLoadStatus : uint8_t
{
	BLS_Unloaded                                       = 0,
	BLS_Pending                                        = 1,
	BLS_Loaded                                         = 2,
	BLS_TimedOut                                       = 3,
	BLS_END                                            = 4
};

// Enum Engine.AmbientOcclusionEffect.EAmbientOcclusionQuality
enum class EAmbientOcclusionQuality : uint8_t
{
	AO_High                                            = 0,
	AO_Medium                                          = 1,
	AO_Low                                             = 2,
	AO_END                                             = 3
};

// Enum Engine.Brush.ECsgOper
enum class ECsgOper : uint8_t
{
	CSG_Active                                         = 0,
	CSG_Add                                            = 1,
	CSG_Subtract                                       = 2,
	CSG_Intersect                                      = 3,
	CSG_Deintersect                                    = 4,
	CSG_END                                            = 5
};

// Enum Engine.ReverbVolume.ReverbPreset
enum class EReverbPreset : uint8_t
{
	REVERB_Default                                     = 0,
	REVERB_Bathroom                                    = 1,
	REVERB_StoneRoom                                   = 2,
	REVERB_Auditorium                                  = 3,
	REVERB_ConcertHall                                 = 4,
	REVERB_Cave                                        = 5,
	REVERB_Hallway                                     = 6,
	REVERB_StoneCorridor                               = 7,
	REVERB_Alley                                       = 8,
	REVERB_Forest                                      = 9,
	REVERB_City                                        = 10,
	REVERB_Mountains                                   = 11,
	REVERB_Quarry                                      = 12,
	REVERB_Plain                                       = 13,
	REVERB_ParkingLot                                  = 14,
	REVERB_SewerPipe                                   = 15,
	REVERB_Underwater                                  = 16,
	REVERB_SmallRoom                                   = 17,
	REVERB_MediumRoom                                  = 18,
	REVERB_LargeRoom                                   = 19,
	REVERB_MediumHall                                  = 20,
	REVERB_LargeHall                                   = 21,
	REVERB_Plate                                       = 22,
	REVERB_END                                         = 23
};

// Enum Engine.EngineTypes.EInputPlatformType
enum class EInputPlatformType : uint8_t
{
	IPT_PC                                             = 0,
	IPT                                                = 1,
	IPT_PS3                                            = 2,
	IPT_PS4                                            = 3,
	IPT_XBOX_ONE                                       = 4,
	IPT_NNX                                            = 5,
	IPT_NNX_SINGLE                                     = 6,
	IPT_END                                            = 7
};

// Enum Engine.EngineTypes.EPathFindingError
enum class EPathFindingError : uint8_t
{
	PATHERROR_STARTPOLYNOTFOUND                        = 0,
	PATHERROR_GOALPOLYNOTFOUND                         = 1,
	PATHERROR_ANCHORPYLONNOTFOUND                      = 2,
	PATHERROR_NOPATHFOUND                              = 3,
	PATHERROR_COMPUTEVALIDFINALDEST_FAIL               = 4,
	PATHERROR_GETNEXTMOVELOCATION_FAIL                 = 5,
	PATHERROR_MOVETIMEOUT                              = 6,
	PATHERROR_END                                      = 7
};

// Enum Engine.AudioDevice.EDebugState
enum class EDebugState : uint8_t
{
	DEBUGSTATE_None                                    = 0,
	DEBUGSTATE_IsolateDryAudio                         = 1,
	DEBUGSTATE_IsolateReverb                           = 2,
	DEBUGSTATE_TestLPF                                 = 3,
	DEBUGSTATE_TestStereoBleed                         = 4,
	DEBUGSTATE_TestLFEBleed                            = 5,
	DEBUGSTATE_DisableLPF                              = 6,
	DEBUGSTATE_DisableRadio                            = 7,
	DEBUGSTATE_END                                     = 8
};

// Enum Engine.AudioDevice.ESoundClassName
enum class ESoundClassName : uint8_t
{
	Master                                             = 0,
	ESoundClassName_END                                = 1
};

// Enum Engine.AudioDevice.ETTSSpeaker
enum class ETTSSpeaker : uint8_t
{
	TTSSPEAKER_Paul                                    = 0,
	TTSSPEAKER_Harry                                   = 1,
	TTSSPEAKER_Frank                                   = 2,
	TTSSPEAKER_Dennis                                  = 3,
	TTSSPEAKER_Kit                                     = 4,
	TTSSPEAKER_Betty                                   = 5,
	TTSSPEAKER_Ursula                                  = 6,
	TTSSPEAKER_Rita                                    = 7,
	TTSSPEAKER_Wendy                                   = 8,
	TTSSPEAKER_END                                     = 9
};

// Enum Engine.SoundNodeAttenuation.ESoundDistanceCalc
enum class ESoundDistanceCalc : uint8_t
{
	SOUNDDISTANCE_Normal                               = 0,
	SOUNDDISTANCE_InfiniteXYPlane                      = 1,
	SOUNDDISTANCE_InfiniteXZPlane                      = 2,
	SOUNDDISTANCE_InfiniteYZPlane                      = 3,
	SOUNDDISTANCE_END                                  = 4
};

// Enum Engine.SoundNodeAttenuation.SoundDistanceModel
enum class ESoundDistanceModel : uint8_t
{
	ATTENUATION_Linear                                 = 0,
	ATTENUATION_Logarithmic                            = 1,
	ATTENUATION_Inverse                                = 2,
	ATTENUATION_LogReverse                             = 3,
	ATTENUATION_NaturalSound                           = 4,
	ATTENUATION_END                                    = 5
};

// Enum Engine.PlatformInterfaceBase.EPlatformInterfaceDataType
enum class EPlatformInterfaceDataType : uint8_t
{
	PIDT_None                                          = 0,
	PIDT_Int                                           = 1,
	PIDT_Float                                         = 2,
	PIDT_String                                        = 3,
	PIDT_Object                                        = 4,
	PIDT_Custom                                        = 5,
	PIDT_QWord                                         = 6,
	PIDT_END                                           = 7
};

// Enum Engine.AnimSequence.AnimationCompressionFormat
enum class EAnimationCompressionFormat : uint8_t
{
	ACF_None                                           = 0,
	ACF_Float96NoW                                     = 1,
	ACF_Fixed48NoW                                     = 2,
	ACF_IntervalFixed32NoW                             = 3,
	ACF_Fixed32NoW                                     = 4,
	ACF_Float32NoW                                     = 5,
	ACF_Identity                                       = 6,
	ACF_END                                            = 7
};

// Enum Engine.AnimSequence.AnimationKeyFormat
enum class EAnimationKeyFormat : uint8_t
{
	AKF_ConstantKeyLerp                                = 0,
	AKF_VariableKeyLerp                                = 1,
	AKF_PerTrackCompression                            = 2,
	AKF_END                                            = 3
};

// Enum Engine.AnimNode.ESliderType
enum class ESliderType : uint8_t
{
	ST_1D                                              = 0,
	ST_2D                                              = 1,
	ST_END                                             = 2
};

// Enum Engine.AnimNode_MultiBlendPerBone.EWeightCheck
enum class EWeightCheck : uint8_t
{
	EWC_AnimNodeSlotNotPlaying                         = 0,
	EWC_END                                            = 1
};

// Enum Engine.AnimNode_MultiBlendPerBone.EBlendType
enum class EBlendType : uint8_t
{
	EBT_ParentBoneSpace                                = 0,
	EBT_MeshSpace                                      = 1,
	EBT_END                                            = 2
};

// Enum Engine.AnimNodeAimOffset.EAnimAimDir
enum class EAnimAimDir : uint8_t
{
	ANIMAIM_LEFTUP                                     = 0,
	ANIMAIM_CENTERUP                                   = 1,
	ANIMAIM_RIGHTUP                                    = 2,
	ANIMAIM_LEFTCENTER                                 = 3,
	ANIMAIM_CENTERCENTER                               = 4,
	ANIMAIM_RIGHTCENTER                                = 5,
	ANIMAIM_LEFTDOWN                                   = 6,
	ANIMAIM_CENTERDOWN                                 = 7,
	ANIMAIM_RIGHTDOWN                                  = 8,
	ANIMAIM_END                                        = 9
};

// Enum Engine.AnimNodeAimOffset.EAimID
enum class EAimID : uint8_t
{
	EAID_LeftUp                                        = 0,
	EAID_LeftDown                                      = 1,
	EAID_RightUp                                       = 2,
	EAID_RightDown                                     = 3,
	EAID_ZeroUp                                        = 4,
	EAID_ZeroDown                                      = 5,
	EAID_ZeroLeft                                      = 6,
	EAID_ZeroRight                                     = 7,
	EAID_CellLU                                        = 8,
	EAID_CellCU                                        = 9,
	EAID_CellRU                                        = 10,
	EAID_CellLC                                        = 11,
	EAID_CellCC                                        = 12,
	EAID_CellRC                                        = 13,
	EAID_CellLD                                        = 14,
	EAID_CellCD                                        = 15,
	EAID_CellRD                                        = 16,
	EAID_END                                           = 17
};

// Enum Engine.AnimNodeBlendByBase.EBaseBlendType
enum class EBaseBlendType : uint8_t
{
	BBT_ByActorTag                                     = 0,
	BBT_ByActorClass                                   = 1,
	BBT_END                                            = 2
};

// Enum Engine.AnimNodeSequence.ERootRotationOption
enum class ERootRotationOption : uint8_t
{
	RRO_Default                                        = 0,
	RRO_Discard                                        = 1,
	RRO_Extract                                        = 2,
	RRO_END                                            = 3
};

// Enum Engine.AnimNodeSequence.ERootBoneAxis
enum class ERootBoneAxis : uint8_t
{
	RBA_Default                                        = 0,
	RBA_Discard                                        = 1,
	RBA_Translate                                      = 2,
	RBA_END                                            = 3
};

// Enum Engine.SkeletalMeshComponent.EPhysBodyOp
enum class EPhysBodyOp : uint8_t
{
	PBO_None                                           = 0,
	PBO_Term                                           = 1,
	PBO_Disable                                        = 2,
	PBO_END                                            = 3
};

// Enum Engine.SkeletalMeshComponent.EBoneVisibilityStatus
enum class EBoneVisibilityStatus : uint8_t
{
	BVS_HiddenByParent                                 = 0,
	BVS_Visible                                        = 1,
	BVS_ExplicitlyHidden                               = 2,
	BVS_END                                            = 3
};

// Enum Engine.SkeletalMeshComponent.EFaceFXRegOp
enum class EFaceFXRegOp : uint8_t
{
	FXRO_Add                                           = 0,
	FXRO_Multiply                                      = 1,
	FXRO_Replace                                       = 2,
	FXRO_END                                           = 3
};

// Enum Engine.SkeletalMeshComponent.EFaceFXBlendMode
enum class EFaceFXBlendMode : uint8_t
{
	FXBM_Overwrite                                     = 0,
	FXBM_Additive                                      = 1,
	FXBM_END                                           = 2
};

// Enum Engine.SkeletalMeshComponent.EInstanceWeightUsage
enum class EInstanceWeightUsage : uint8_t
{
	IWU_PartialSwap                                    = 0,
	IWU_FullSwap                                       = 1,
	IWU_END                                            = 2
};

// Enum Engine.SkeletalMeshComponent.EAnimRotationOnly
enum class EAnimRotationOnly : uint8_t
{
	EARO_AnimSet                                       = 0,
	EARO_ForceEnabled                                  = 1,
	EARO_ForceDisabled                                 = 2,
	EARO_END                                           = 3
};

// Enum Engine.SkeletalMeshComponent.ERootMotionRotationMode
enum class ERootMotionRotationMode : uint8_t
{
	RMRM_Ignore                                        = 0,
	RMRM_RotateActor                                   = 1,
	RMRM_END                                           = 2
};

// Enum Engine.SkeletalMeshComponent.ERootMotionMode
enum class ERootMotionMode : uint8_t
{
	RMM_Translate                                      = 0,
	RMM_Velocity                                       = 1,
	RMM_Ignore                                         = 2,
	RMM_Accel                                          = 3,
	RMM_Relative                                       = 4,
	RMM_END                                            = 5
};

// Enum Engine.SkeletalMeshComponent.EMaxDistanceScaleMode
enum class EMaxDistanceScaleMode : uint8_t
{
	MDSM_Multiply                                      = 0,
	MDSM_Substract                                     = 1,
	MDSM_END                                           = 2
};

// Enum Engine.EngineTypes.EBlendMode
enum class EBlendMode : uint8_t
{
	BLEND_Opaque                                       = 0,
	BLEND_Masked                                       = 1,
	BLEND_Translucent                                  = 2,
	BLEND_Additive                                     = 3,
	BLEND_Modulate                                     = 4,
	BLEND_ModulateAndAdd                               = 5,
	BLEND_SoftMasked                                   = 6,
	BLEND_AlphaComposite                               = 7,
	BLEND_DitheredTranslucent                          = 8,
	BLEND_END                                          = 9
};

// Enum Engine.EngineTypes.EMaterialLightingModel
enum class EMaterialLightingModel : uint8_t
{
	MLM_Phong                                          = 0,
	MLM_NonDirectional                                 = 1,
	MLM_Unlit                                          = 2,
	MLM_SHPRT                                          = 3,
	MLM_Custom                                         = 4,
	MLM_Anisotropic                                    = 5,
	MLM_END                                            = 6
};

// Enum Engine.EngineTypes.EMaterialTessellationMode
enum class EMaterialTessellationMode : uint8_t
{
	MTM_NoTessellation                                 = 0,
	MTM_FlatTessellation                               = 1,
	MTM_PNTriangles                                    = 2,
	MTM_END                                            = 3
};

// Enum Engine.EngineTypes.EMobileValueSource
enum class EMobileValueSource : uint8_t
{
	MVS_Constant                                       = 0,
	MVS_VertexColorRed                                 = 1,
	MVS_VertexColorGreen                               = 2,
	MVS_VertexColorBlue                                = 3,
	MVS_VertexColorAlpha                               = 4,
	MVS_BaseTextureRed                                 = 5,
	MVS_BaseTextureGreen                               = 6,
	MVS_BaseTextureBlue                                = 7,
	MVS_BaseTextureAlpha                               = 8,
	MVS_MaskTextureRed                                 = 9,
	MVS_MaskTextureGreen                               = 10,
	MVS_MaskTextureBlue                                = 11,
	MVS_MaskTextureAlpha                               = 12,
	MVS_NormalTextureAlpha                             = 13,
	MVS_EmissiveTextureRed                             = 14,
	MVS_EmissiveTextureGreen                           = 15,
	MVS_EmissiveTextureBlue                            = 16,
	MVS_EmissiveTextureAlpha                           = 17,
	MVS_END                                            = 18
};

// Enum Engine.EngineTypes.EMobileTextureBlendFactorSource
enum class EMobileTextureBlendFactorSource : uint8_t
{
	MTBFS_VertexColor                                  = 0,
	MTBFS_MaskTexture                                  = 1,
	MTBFS_END                                          = 2
};

// Enum Engine.EngineTypes.EMobileTexCoordsSource
enum class EMobileTexCoordsSource : uint8_t
{
	MTCS_TexCoords0                                    = 0,
	MTCS_TexCoords1                                    = 1,
	MTCS_TexCoords2                                    = 2,
	MTCS_TexCoords3                                    = 3,
	MTCS_END                                           = 4
};

// Enum Engine.EngineTypes.EMobileAlphaValueSource
enum class EMobileAlphaValueSource : uint8_t
{
	MAVS_DiffuseTextureAlpha                           = 0,
	MAVS_MaskTextureRed                                = 1,
	MAVS_MaskTextureGreen                              = 2,
	MAVS_MaskTextureBlue                               = 3,
	MAVS_END                                           = 4
};

// Enum Engine.EngineTypes.EMobileColorMultiplySource
enum class EMobileColorMultiplySource : uint8_t
{
	MCMS_None                                          = 0,
	MCMS_BaseTextureRed                                = 1,
	MCMS_BaseTextureGreen                              = 2,
	MCMS_BaseTextureBlue                               = 3,
	MCMS_BaseTextureAlpha                              = 4,
	MCMS_MaskTextureRed                                = 5,
	MCMS_MaskTextureGreen                              = 6,
	MCMS_MaskTextureBlue                               = 7,
	MCMS_MaskTextureAlpha                              = 8,
	MCMS_END                                           = 9
};

// Enum Engine.EngineTypes.EMobileEmissiveColorSource
enum class EMobileEmissiveColorSource : uint8_t
{
	MECS_EmissiveTexture                               = 0,
	MECS_BaseTexture                                   = 1,
	MECS_Constant                                      = 2,
	MECS_END                                           = 3
};

// Enum Engine.EngineTypes.EMobileEnvironmentBlendMode
enum class EMobileEnvironmentBlendMode : uint8_t
{
	MEBM_Add                                           = 0,
	MEBM_Lerp                                          = 1,
	MEBM_END                                           = 2
};

// Enum Engine.EngineTypes.EMobileSpecularMask
enum class EMobileSpecularMask : uint8_t
{
	MSM_Constant                                       = 0,
	MSM_Luminance                                      = 1,
	MSM_DiffuseRed                                     = 2,
	MSM_DiffuseGreen                                   = 3,
	MSM_DiffuseBlue                                    = 4,
	MSM_DiffuseAlpha                                   = 5,
	MSM_MaskTextureRGB                                 = 6,
	MSM_MaskTextureRed                                 = 7,
	MSM_MaskTextureGreen                               = 8,
	MSM_MaskTextureBlue                                = 9,
	MSM_MaskTextureAlpha                               = 10,
	MSM_END                                            = 11
};

// Enum Engine.EngineTypes.EMobileAmbientOcclusionSource
enum class EMobileAmbientOcclusionSource : uint8_t
{
	MAOS_Disabled                                      = 0,
	MAOS_VertexColorRed                                = 1,
	MAOS_VertexColorGreen                              = 2,
	MAOS_VertexColorBlue                               = 3,
	MAOS_VertexColorAlpha                              = 4,
	MAOS_END                                           = 5
};

// Enum Engine.EngineTypes.ELightingBuildQuality
enum class ELightingBuildQuality : uint8_t
{
	Quality_Preview                                    = 0,
	Quality_Medium                                     = 1,
	Quality_High                                       = 2,
	Quality_Production                                 = 3,
	Quality_NoGlobalIllumination                       = 4,
	Quality_END                                        = 5
};

// Enum Engine.Pawn.EPathSearchType
enum class EPathSearchType : uint8_t
{
	PST_Default                                        = 0,
	PST_Breadth                                        = 1,
	PST_NewBestPathTo                                  = 2,
	PST_Constraint                                     = 3,
	PST_END                                            = 4
};

// Enum Engine.DynamicLightEnvironmentComponent.EDynamicLightEnvironmentBoundsMethod
enum class EDynamicLightEnvironmentBoundsMethod : uint8_t
{
	DLEB_OwnerComponents                               = 0,
	DLEB_ManualOverride                                = 1,
	DLEB_ActiveComponents                              = 2,
	DLEB_END                                           = 3
};

// Enum Engine.ApexDestructibleAsset.EImpactDamageOverride
enum class EImpactDamageOverride : uint8_t
{
	IDO_None                                           = 0,
	IDO_On                                             = 1,
	IDO_Off                                            = 2,
	IDO_END                                            = 3
};

// Enum Engine.ApexDestructibleDamageParameters.EDamageParameterOverrideMode
enum class EDamageParameterOverrideMode : uint8_t
{
	DPOM_Absolute                                      = 0,
	DPOM_Multiplier                                    = 1,
	DPOM_END                                           = 2
};

// Enum Engine.Camera.ECameraAnimPlaySpace
enum class ECameraAnimPlaySpace : uint8_t
{
	CAPS_CameraLocal                                   = 0,
	CAPS_World                                         = 1,
	CAPS_UserDefined                                   = 2,
	CAPS_END                                           = 3
};

// Enum Engine.Camera.EViewTargetBlendFunction
enum class EViewTargetBlendFunction : uint8_t
{
	VTBlend_Linear                                     = 0,
	VTBlend_Cubic                                      = 1,
	VTBlend_EaseIn                                     = 2,
	VTBlend_EaseOut                                    = 3,
	VTBlend_EaseInOut                                  = 4,
	VTBlend_MidwayStep                                 = 5,
	VTBlend_END                                        = 6
};

// Enum Engine.DOFEffect.EFocusType
enum class EFocusType : uint8_t
{
	FOCUS_Distance                                     = 0,
	FOCUS_Position                                     = 1,
	FOCUS_END                                          = 2
};

// Enum Engine.CameraShake.EInitialOscillatorOffset
enum class EInitialOscillatorOffset : uint8_t
{
	EOO_OffsetRandom                                   = 0,
	EOO_OffsetZero                                     = 1,
	EOO_END                                            = 2
};

// Enum Engine.Canvas.ECanvasBlendMode
enum class ECanvasBlendMode : uint8_t
{
	BLEND_CANVAS_Opaque                                = 0,
	BLEND_CANVAS_Masked                                = 1,
	BLEND_CANVAS_Translucent                           = 2,
	BLEND_CANVAS_Additive                              = 3,
	BLEND_CANVAS_Modulate                              = 4,
	BLEND_CANVAS_ModulateAndAdd                        = 5,
	BLEND_CANVAS_SoftMasked                            = 6,
	BLEND_CANVAS_AlphaComposite                        = 7,
	BLEND_CANVAS_DitheredTranslucent                   = 8,
	BLEND_CANVAS_AlphaOnly                             = 9,
	BLEND_CANVAS_END                                   = 10
};

// Enum Engine.Texture.TextureCompressionSettings
enum class ETextureCompressionSettings : uint8_t
{
	TC_Default                                         = 0,
	TC_Normalmap                                       = 1,
	TC_Displacementmap                                 = 2,
	TC_NormalmapAlpha                                  = 3,
	TC_Grayscale                                       = 4,
	TC_HighDynamicRange                                = 5,
	TC_OneBitAlpha                                     = 6,
	TC_NormalmapUncompressed                           = 7,
	TC_NormalmapBC5                                    = 8,
	TC_NormalmapSwizzle                                = 9,
	TC_OneBitMonochrome                                = 10,
	TC_SimpleLightmapModification                      = 11,
	TC_VectorDisplacementmap                           = 12,
	TC_BC7                                             = 13,
	TC_END                                             = 14
};

// Enum Engine.Texture.EPixelFormat
enum class EPixelFormat : uint8_t
{
	PF_Unknown                                         = 0,
	PF_A32B32G32R32F                                   = 1,
	PF_A8R8G8B8                                        = 2,
	PF_G8                                              = 3,
	PF_G16                                             = 4,
	PF_DXT1                                            = 5,
	PF_DXT3                                            = 6,
	PF_DXT5                                            = 7,
	PF_UYVY                                            = 8,
	PF_FloatRGB                                        = 9,
	PF_FloatRGBA                                       = 10,
	PF_DepthStencil                                    = 11,
	PF_ShadowDepth                                     = 12,
	PF_FilteredShadowDepth                             = 13,
	PF_R32F                                            = 14,
	PF_G16R16                                          = 15,
	PF_G16R16F                                         = 16,
	PF_G16R16F_FILTER                                  = 17,
	PF_G32R32F                                         = 18,
	PF_A2B10G10R10                                     = 19,
	PF_A2R10G10B10                                     = 20,
	PF_A16B16G16R16                                    = 21,
	PF_D24                                             = 22,
	PF_R16F                                            = 23,
	PF_R16F_FILTER                                     = 24,
	PF_BC5                                             = 25,
	PF_V8U8                                            = 26,
	PF_A1                                              = 27,
	PF_FloatR11G11B10                                  = 28,
	PF_A4R4G4B4                                        = 29,
	PF_R5G6B5                                          = 30,
	PF_G8R8                                            = 31,
	PF_R32_UINT                                        = 32,
	PF_ASTC_4x4                                        = 33,
	PF_ASTC_6x6                                        = 34,
	PF_ASTC_8x8                                        = 35,
	PF_ASTC_10x10                                      = 36,
	PF_ASTC_12x12                                      = 37,
	PF_BC7                                             = 38,
	PF_COUNT                                           = 39,
	PF_END                                             = 40
};

// Enum Engine.Texture.TextureFilter
enum class ETextureFilter : uint8_t
{
	TF_Nearest                                         = 0,
	TF_Linear                                          = 1,
	TF_END                                             = 2
};

// Enum Engine.Texture.TextureAddress
enum class ETextureAddress : uint8_t
{
	TA_Wrap                                            = 0,
	TA_Clamp                                           = 1,
	TA_Mirror                                          = 2,
	TA_END                                             = 3
};

// Enum Engine.Texture.TextureGroup
enum class ETextureGroup : uint8_t
{
	TEXTUREGROUP_World                                 = 0,
	TEXTUREGROUP_WorldNormalMap                        = 1,
	TEXTUREGROUP_WorldSpecular                         = 2,
	TEXTUREGROUP_Character                             = 3,
	TEXTUREGROUP_CharacterNormalMap                    = 4,
	TEXTUREGROUP_CharacterSpecular                     = 5,
	TEXTUREGROUP_Weapon                                = 6,
	TEXTUREGROUP_WeaponNormalMap                       = 7,
	TEXTUREGROUP_WeaponSpecular                        = 8,
	TEXTUREGROUP_Vehicle                               = 9,
	TEXTUREGROUP_VehicleNormalMap                      = 10,
	TEXTUREGROUP_VehicleSpecular                       = 11,
	TEXTUREGROUP_Cinematic                             = 12,
	TEXTUREGROUP_Effects                               = 13,
	TEXTUREGROUP_EffectsNotFiltered                    = 14,
	TEXTUREGROUP_Skybox                                = 15,
	TEXTUREGROUP_UI                                    = 16,
	TEXTUREGROUP_Lightmap                              = 17,
	TEXTUREGROUP_RenderTarget                          = 18,
	TEXTUREGROUP_MobileFlattened                       = 19,
	TEXTUREGROUP_ProcBuilding_Face                     = 20,
	TEXTUREGROUP_ProcBuilding_LightMap                 = 21,
	TEXTUREGROUP_Shadowmap                             = 22,
	TEXTUREGROUP_ColorLookupTable                      = 23,
	TEXTUREGROUP_Terrain_Heightmap                     = 24,
	TEXTUREGROUP_Terrain_Weightmap                     = 25,
	TEXTUREGROUP_ImageBasedReflection                  = 26,
	TEXTUREGROUP_Bokeh                                 = 27,
	TEXTUREGROUP_Pitch                                 = 28,
	TEXTUREGROUP_END                                   = 29
};

// Enum Engine.Texture.TextureMipGenSettings
enum class ETextureMipGenSettings : uint8_t
{
	TMGS_FromTextureGroup                              = 0,
	TMGS_SimpleAverage                                 = 1,
	TMGS_Sharpen0                                      = 2,
	TMGS_Sharpen1                                      = 3,
	TMGS_Sharpen2                                      = 4,
	TMGS_Sharpen3                                      = 5,
	TMGS_Sharpen4                                      = 6,
	TMGS_Sharpen5                                      = 7,
	TMGS_Sharpen6                                      = 8,
	TMGS_Sharpen7                                      = 9,
	TMGS_Sharpen8                                      = 10,
	TMGS_Sharpen9                                      = 11,
	TMGS_Sharpen10                                     = 12,
	TMGS_NoMipmaps                                     = 13,
	TMGS_LeaveExistingMips                             = 14,
	TMGS_Blur1                                         = 15,
	TMGS_Blur2                                         = 16,
	TMGS_Blur3                                         = 17,
	TMGS_Blur4                                         = 18,
	TMGS_Blur5                                         = 19,
	TMGS_END                                           = 20
};

// Enum Engine.Texture.ETextureMipCount
enum class ETextureMipCount : uint8_t
{
	TMC_ResidentMips                                   = 0,
	TMC_AllMips                                        = 1,
	TMC_AllMipsBiased                                  = 2,
	TMC_END                                            = 3
};

// Enum Engine.CloudSaveSystem.SaveDataVersionSupport
enum class ESaveDataVersionSupport : uint8_t
{
	SaveDataVersionSupportLessThenEqual                = 0,
	SaveDataVersionSupportEqual                        = 1,
	SaveDataVersionSupportAny                          = 2,
	SaveDataVersionSupport_END                         = 3
};

// Enum Engine.CloudSaveSystem.SaveSlotOperationEnum
enum class ESaveSlotOperationEnum : uint8_t
{
	SSO_SET                                            = 0,
	SSO_GET                                            = 1,
	SSO_DELETE                                         = 2,
	SSO_END                                            = 3
};

// Enum Engine.CloudStorageBase.ECloudStorageDelegate
enum class ECloudStorageDelegate : uint8_t
{
	CSD_KeyValueReadComplete                           = 0,
	CSD_KeyValueWriteComplete                          = 1,
	CSD_ValueChanged                                   = 2,
	CSD_DocumentQueryComplete                          = 3,
	CSD_DocumentReadComplete                           = 4,
	CSD_DocumentWriteComplete                          = 5,
	CSD_DocumentConflictDetected                       = 6,
	CSD_END                                            = 7
};

// Enum Engine.Interaction.ETouchType
enum class ETouchType : uint8_t
{
	Touch_Began                                        = 0,
	Touch_Moved                                        = 1,
	Touch_Stationary                                   = 2,
	Touch_Ended                                        = 3,
	Touch_Cancelled                                    = 4,
	Touch_END                                          = 5
};

// Enum Engine.CoverGroup.ECoverGroupFillAction
enum class ECoverGroupFillAction : uint8_t
{
	CGFA_Overwrite                                     = 0,
	CGFA_Add                                           = 1,
	CGFA_Remove                                        = 2,
	CGFA_Clear                                         = 3,
	CGFA_Cylinder                                      = 4,
	CGFA_END                                           = 5
};

// Enum Engine.CoverLink.ECoverLocationDescription
enum class ECoverLocationDescription : uint8_t
{
	CoverDesc_None                                     = 0,
	CoverDesc_InWindow                                 = 1,
	CoverDesc_InDoorway                                = 2,
	CoverDesc_BehindCar                                = 3,
	CoverDesc_BehindTruck                              = 4,
	CoverDesc_OnTruck                                  = 5,
	CoverDesc_BehindBarrier                            = 6,
	CoverDesc_BehindColumn                             = 7,
	CoverDesc_BehindCrate                              = 8,
	CoverDesc_BehindWall                               = 9,
	CoverDesc_BehindStatue                             = 10,
	CoverDesc_BehindSandbags                           = 11,
	CoverDesc_END                                      = 12
};

// Enum Engine.CoverLink.ECoverType
enum class ECoverType : uint8_t
{
	CT_None                                            = 0,
	CT_Standing                                        = 1,
	CT_MidLevel                                        = 2,
	CT_END                                             = 3
};

// Enum Engine.CoverLink.ECoverAction
enum class ECoverAction : uint8_t
{
	CA_Default                                         = 0,
	CA_BlindLeft                                       = 1,
	CA_BlindRight                                      = 2,
	CA_LeanLeft                                        = 3,
	CA_LeanRight                                       = 4,
	CA_PopUp                                           = 5,
	CA_BlindUp                                         = 6,
	CA_PeekLeft                                        = 7,
	CA_PeekRight                                       = 8,
	CA_PeekUp                                          = 9,
	CA_END                                             = 10
};

// Enum Engine.CoverLink.ECoverDirection
enum class ECoverDirection : uint8_t
{
	CD_Default                                         = 0,
	CD_Left                                            = 1,
	CD_Right                                           = 2,
	CD_Up                                              = 3,
	CD_END                                             = 4
};

// Enum Engine.CoverLink.EFireLinkID
enum class EFireLinkID : uint8_t
{
	FLI_FireLink                                       = 0,
	FLI_RejectedFireLink                               = 1,
	FLI_END                                            = 2
};

// Enum Engine.StaticMeshComponent.ELightmapModificationFunction
enum class ELightmapModificationFunction : uint8_t
{
	MLMF_Modulate                                      = 0,
	MLMF_ModulateAlpha                                 = 1,
	MLMF_END                                           = 2
};

// Enum Engine.DateTime.ETimeZone
enum class ETimeZone : uint8_t
{
	TZ_UTC                                             = 0,
	TZ_Local                                           = 1,
	TZ_END                                             = 2
};

// Enum Engine.DecalComponent.EFilterMode
enum class EFilterMode : uint8_t
{
	FM_None                                            = 0,
	FM_Ignore                                          = 1,
	FM_Affect                                          = 2,
	FM_END                                             = 3
};

// Enum Engine.DecalComponent.EDecalTransform
enum class EDecalTransform : uint8_t
{
	DecalTransform_OwnerAbsolute                       = 0,
	DecalTransform_OwnerRelative                       = 1,
	DecalTransform_SpawnRelative                       = 2,
	DecalTransform_END                                 = 3
};

// Enum Engine.MaterialInterface.EMaterialUsage
enum class EMaterialUsage : uint8_t
{
	MATUSAGE_SkeletalMesh                              = 0,
	MATUSAGE_FracturedMeshes                           = 1,
	MATUSAGE_ParticleSprites                           = 2,
	MATUSAGE_BeamTrails                                = 3,
	MATUSAGE_ParticleSubUV                             = 4,
	MATUSAGE_SpeedTree                                 = 5,
	MATUSAGE_StaticLighting                            = 6,
	MATUSAGE_GammaCorrection                           = 7,
	MATUSAGE_LensFlare                                 = 8,
	MATUSAGE_InstancedMeshParticles                    = 9,
	MATUSAGE_FluidSurface                              = 10,
	MATUSAGE_Decals                                    = 11,
	MATUSAGE_MaterialEffect                            = 12,
	MATUSAGE_MorphTargets                              = 13,
	MATUSAGE_FogVolumes                                = 14,
	MATUSAGE_RadialBlur                                = 15,
	MATUSAGE_InstancedMeshes                           = 16,
	MATUSAGE_SplineMesh                                = 17,
	MATUSAGE_ScreenDoorFade                            = 18,
	MATUSAGE_APEXMesh                                  = 19,
	MATUSAGE_Terrain                                   = 20,
	MATUSAGE_Landscape                                 = 21,
	MATUSAGE_MobileLandscape                           = 22,
	MATUSAGE_END                                       = 23
};

// Enum Engine.LightComponent.EShadowFilterQuality
enum class EShadowFilterQuality : uint8_t
{
	SFQ_Low                                            = 0,
	SFQ_Medium                                         = 1,
	SFQ_High                                           = 2,
	SFQ_END                                            = 3
};

// Enum Engine.LightComponent.EShadowProjectionTechnique
enum class EShadowProjectionTechnique : uint8_t
{
	ShadowProjTech_Default                             = 0,
	ShadowProjTech_PCF                                 = 1,
	ShadowProjTech_VSM                                 = 2,
	ShadowProjTech_BPCF_Low                            = 3,
	ShadowProjTech_BPCF_Medium                         = 4,
	ShadowProjTech_BPCF_High                           = 5,
	ShadowProjTech_END                                 = 6
};

// Enum Engine.LightComponent.ELightShadowMode
enum class ELightShadowMode : uint8_t
{
	LightShadow_Normal                                 = 0,
	LightShadow_Modulate                               = 1,
	LightShadow_ModulateBetter                         = 2,
	LightShadow_END                                    = 3
};

// Enum Engine.LightComponent.ELightAffectsClassification
enum class ELightAffectsClassification : uint8_t
{
	LAC_USER_SELECTED                                  = 0,
	LAC_DYNAMIC_AFFECTING                              = 1,
	LAC_STATIC_AFFECTING                               = 2,
	LAC_DYNAMIC_AND_STATIC_AFFECTING                   = 3,
	LAC_END                                            = 4
};

// Enum Engine.DistributionFloatParameterBase.DistributionParamMode
enum class EDistributionParamMode : uint8_t
{
	DPM_Normal                                         = 0,
	DPM_Abs                                            = 1,
	DPM_Direct                                         = 2,
	DPM_END                                            = 3
};

// Enum Engine.DOFAndBloomEffect.EDOFQuality
enum class EDOFQuality : uint8_t
{
	DOFQuality_Low                                     = 0,
	DOFQuality_Medium                                  = 1,
	DOFQuality_High                                    = 2,
	DOFQuality_END                                     = 3
};

// Enum Engine.DOFAndBloomEffect.EDOFType
enum class EDOFType : uint8_t
{
	DOFType_SimpleDOF                                  = 0,
	DOFType_ReferenceDOF                               = 1,
	DOFType_BokehDOF                                   = 2,
	DOFType_END                                        = 3
};

// Enum Engine.OnlineSubsystem.EOnlineFriendState
enum class EOnlineFriendState : uint8_t
{
	OFS_Offline                                        = 0,
	OFS_Online                                         = 1,
	OFS_Away                                           = 2,
	OFS_Busy                                           = 3,
	OFS_Unknown                                        = 4,
	OFS_END                                            = 5
};

// Enum Engine.OnlineSubsystem.EFeaturePrivilege
enum class EFeaturePrivilege : uint8_t
{
	FP_OnlinePlay                                      = 0,
	FP_CommunicationText                               = 1,
	FP_CommunicationVideo                              = 2,
	FP_CommunicationVoice                              = 3,
	FP_ShareUserCreatedContent                         = 4,
	FP_PurchaseContent                                 = 5,
	FP_ViewPlayerProfile                               = 6,
	FP_ShowPresenceInformation                         = 7,
	FP_RecordDVRClips                                  = 8,
	FP_CloudStorage                                    = 9,
	FP_PremiumContent                                  = 10,
	FP_PremiumVideoContent                             = 11,
	FP_BrowseInternet                                  = 12,
	FP_SocialNetworkSharing                            = 13,
	FP_KinectSharing                                   = 14,
	FP_FitnessUpload                                   = 15,
	FP_Crossplay                                       = 16,
	FP_END                                             = 17
};

// Enum Engine.OnlineSubsystem.ELoginStatus
enum class ELoginStatus : uint8_t
{
	LS_NotLoggedIn                                     = 0,
	LS_UsingLocalProfile                               = 1,
	LS_LoggedIn                                        = 2,
	LS_END                                             = 3
};

// Enum Engine.OnlineSubsystem.EPlayerInteractionPerm
enum class EPlayerInteractionPerm : uint8_t
{
	PIP_Unset                                          = 0,
	PIP_Blocked                                        = 1,
	PIP_Allowed                                        = 2,
	PIP_END                                            = 3
};

// Enum Engine.OnlineSubsystem.ECommunicationMethod
enum class ECommunicationMethod : uint8_t
{
	COMM_Text                                          = 0,
	COMM_Voice                                         = 1,
	COMM_END                                           = 2
};

// Enum Engine.OnlineSubsystem.AvatarSize
enum class EAvatarSize : uint8_t
{
	AvatarSize_Small                                   = 0,
	AvatarSize_Medium                                  = 1,
	AvatarSize_Large                                   = 2,
	AvatarSize_END                                     = 3
};

// Enum Engine.OnlineSubsystem.EPinGrantResult
enum class EPinGrantResult : uint8_t
{
	PinGrantResult_Success                             = 0,
	PinGrantResult_Expired                             = 1,
	PinGrantResult_END                                 = 2
};

// Enum Engine.OnlineSubsystem.EFeaturePrivilegeLevel
enum class EFeaturePrivilegeLevel : uint8_t
{
	FPL_Disabled                                       = 0,
	FPL_Premium                                        = 1,
	FPL_EnabledFriendsOnly                             = 2,
	FPL_Enabled                                        = 3,
	FPL_Offline                                        = 4,
	FPL_END                                            = 5
};

// Enum Engine.OnlineSubsystem.EPS4ErrorDialog
enum class EPS4ErrorDialog : uint8_t
{
	PS4_ERROR_SIGNED_OUT                               = 0,
	PS4_ERROR_SIGNED_END                               = 1
};

// Enum Engine.OnlineSubsystem.EPS4DisplayMode
enum class EPS4DisplayMode : uint8_t
{
	PS4DM_CATEGORY                                     = 0,
	PS4DM_PRODUCT                                      = 1,
	PS4DM_PRODUCT_CODE                                 = 2,
	PS4DM_CHECKOUT                                     = 3,
	PS4DM_DOWNLOADLIST                                 = 4,
	PS4DM_PLUS                                         = 5,
	PS4DM_END                                          = 6
};

// Enum Engine.OnlineSubsystem.ENATType
enum class ENATType : uint8_t
{
	NAT_Unknown                                        = 0,
	NAT_Open                                           = 1,
	NAT_Moderate                                       = 2,
	NAT_Strict                                         = 3,
	NAT_END                                            = 4
};

// Enum Engine.OnlineSubsystem.EOnlineServerConnectionStatus
enum class EOnlineServerConnectionStatus : uint8_t
{
	OSCS_NotConnected                                  = 0,
	OSCS_Connected                                     = 1,
	OSCS_ConnectionDropped                             = 2,
	OSCS_NoNetworkConnection                           = 3,
	OSCS_ServiceUnavailable                            = 4,
	OSCS_UpdateRequired                                = 5,
	OSCS_ServersTooBusy                                = 6,
	OSCS_DuplicateLoginDetected                        = 7,
	OSCS_InvalidUser                                   = 8,
	OSCS_InvalidResponse                               = 9,
	OSCS_TooYoung                                      = 10,
	OSCS_EpicAccountLinkingFailed                      = 11,
	OSCS_END                                           = 12
};

// Enum Engine.OnlineSubsystem.ESessionMemberStatus
enum class ESessionMemberStatus : uint8_t
{
	DSMS_Reserved                                      = 0,
	DSMS_Inactive                                      = 1,
	DSMS_Ready                                         = 2,
	DSMS_Active                                        = 3,
	DSMS_END                                           = 4
};

// Enum Engine.OnlineSubsystem.EOnlineNewsType
enum class EOnlineNewsType : uint8_t
{
	ONT_Unknown                                        = 0,
	ONT_GameNews                                       = 1,
	ONT_ContentAnnouncements                           = 2,
	ONT_Misc                                           = 3,
	ONT_END                                            = 4
};

// Enum Engine.OnlineSubsystem.EInventoryItemState
enum class EInventoryItemState : uint8_t
{
	IIS_Unknown                                        = 0,
	IIS_All                                            = 1,
	IIS_Enabled                                        = 2,
	IIS_Suspended                                      = 3,
	IIS_Expired                                        = 4,
	IIS_Canceled                                       = 5,
	IIS_END                                            = 6
};

// Enum Engine.OnlineSubsystem.EMediaItemType
enum class EMediaItemType : uint8_t
{
	MIT_Unknown                                        = 0,
	MIT_Game                                           = 1,
	MIT_Application                                    = 2,
	MIT_GameContent                                    = 3,
	MIT_GameConsumable                                 = 4,
	MIT_Subscription                                   = 5,
	MIT_END                                            = 6
};

// Enum Engine.OnlineSubsystem.EOnlineEnumerationReadState
enum class EOnlineEnumerationReadState : uint8_t
{
	OERS_NotStarted                                    = 0,
	OERS_InProgress                                    = 1,
	OERS_Done                                          = 2,
	OERS_Failed                                        = 3,
	OERS_END                                           = 4
};

// Enum Engine.OnlineSubsystem.EOnlineGameState
enum class EOnlineGameState : uint8_t
{
	OGS_NoSession                                      = 0,
	OGS_Pending                                        = 1,
	OGS_Starting                                       = 2,
	OGS_InProgress                                     = 3,
	OGS_Ending                                         = 4,
	OGS_Ended                                          = 5,
	OGS_END                                            = 6
};

// Enum Engine.OnlineSubsystem.ECatalogSortOrder
enum class ECatalogSortOrder : uint8_t
{
	CSO_FreeAndPaidCountDaily                          = 0,
	CSO_PaidCountAllTime                               = 1,
	CSO_PaidCountDail                                  = 2,
	CSO_DigitalReleaseDate                             = 3,
	CSO_ReleaseDate                                    = 4,
	CSO_UserRatings                                    = 5,
	CSO_END                                            = 6
};

// Enum Engine.OnlineSubsystem.EAchievementUnlockType
enum class EAchievementUnlockType : uint8_t
{
	AUT_Unknown                                        = 0,
	AUT_All                                            = 1,
	AUT_Persistent                                     = 2,
	AUT_Challenge                                      = 3,
	AUT_END                                            = 4
};

// Enum Engine.OnlineSubsystem.EAchievementMediaAssetType
enum class EAchievementMediaAssetType : uint8_t
{
	AMAT_Unknown                                       = 0,
	AMAT_Icon                                          = 1,
	AMAT_Art                                           = 2,
	AMAT_END                                           = 3
};

// Enum Engine.OnlineSubsystem.EAchievementParticipationType
enum class EAchievementParticipationType : uint8_t
{
	APT_Unknown                                        = 0,
	APT_Individual                                     = 1,
	APT_Group                                          = 2,
	APT_END                                            = 3
};

// Enum Engine.OnlineSubsystem.EAchievementProgressState
enum class EAchievementProgressState : uint8_t
{
	APS_Unknown                                        = 0,
	APS_Achieved                                       = 1,
	APS_NotStarted                                     = 2,
	APS_InProgress                                     = 3,
	APS_END                                            = 4
};

// Enum Engine.OnlineSubsystem.EAchievementRewardType
enum class EAchievementRewardType : uint8_t
{
	ART_Unknown                                        = 0,
	ART_Gamerscore                                     = 1,
	ART_InApp                                          = 2,
	ART_Art                                            = 3,
	ART_END                                            = 4
};

// Enum Engine.Settings.ESettingsDataType
enum class ESettingsDataType : uint8_t
{
	SDT_Empty                                          = 0,
	SDT_Int32                                          = 1,
	SDT_Int64                                          = 2,
	SDT_Double                                         = 3,
	SDT_String                                         = 4,
	SDT_Float                                          = 5,
	SDT_Blob                                           = 6,
	SDT_DateTime                                       = 7,
	SDT_END                                            = 8
};

// Enum Engine.Settings.EOnlineDataAdvertisementType
enum class EOnlineDataAdvertisementType : uint8_t
{
	ODAT_DontAdvertise                                 = 0,
	ODAT_OnlineService                                 = 1,
	ODAT_QoS                                           = 2,
	ODAT_OnlineServiceAndQoS                           = 3,
	ODAT_END                                           = 4
};

// Enum Engine.OnlineSubsystem.EOnlineFileType
enum class EOnlineFileType : uint8_t
{
	OFT_Unknown                                        = 0,
	OFT_Binary                                         = 1,
	OFT_Json                                           = 2,
	OFT_END                                            = 3
};

// Enum Engine.OnlineSubsystem.EOnlineAccountCreateStatus
enum class EOnlineAccountCreateStatus : uint8_t
{
	OACS_CreateSuccessful                              = 0,
	OACS_UnknownError                                  = 1,
	OACS_InvalidUserName                               = 2,
	OACS_InvalidPassword                               = 3,
	OACS_InvalidUniqueUserName                         = 4,
	OACS_UniqueUserNameInUse                           = 5,
	OACS_ServiceUnavailable                            = 6,
	OACS_END                                           = 7
};

// Enum Engine.OnlineSubsystem.ELanBeaconState
enum class ELanBeaconState : uint8_t
{
	LANB_NotUsingLanBeacon                             = 0,
	LANB_Hosting                                       = 1,
	LANB_Searching                                     = 2,
	LANB_END                                           = 3
};

// Enum Engine.OnlineSubsystem.EOnlineContentType
enum class EOnlineContentType : uint8_t
{
	OCT_Downloaded                                     = 0,
	OCT_SaveGame                                       = 1,
	OCT_END                                            = 2
};

// Enum Engine.OnlineSubsystem.EOnlineCreateGameSessionFlag
enum class EOnlineCreateGameSessionFlag : uint8_t
{
	OCGSF_New                                          = 0,
	OCGSF_ReSubmit                                     = 1,
	OCGSF_END                                          = 2
};

// Enum Engine.OnlineSubsystem.EOnlineAccountTier
enum class EOnlineAccountTier : uint8_t
{
	OAT_Unknown                                        = 0,
	OAT_NewUser                                        = 1,
	OAT_Silver                                         = 2,
	OAT_Gold                                           = 3,
	OAT_FamilyGold                                     = 4,
	OAT_END                                            = 5
};

// Enum Engine.OnlineSubsystem.ENetworkNotificationPosition
enum class ENetworkNotificationPosition : uint8_t
{
	NNP_TopLeft                                        = 0,
	NNP_TopCenter                                      = 1,
	NNP_TopRight                                       = 2,
	NNP_CenterLeft                                     = 3,
	NNP_Center                                         = 4,
	NNP_CenterRight                                    = 5,
	NNP_BottomLeft                                     = 6,
	NNP_BottomCenter                                   = 7,
	NNP_BottomRight                                    = 8,
	NNP_END                                            = 9
};

// Enum Engine.OnlineSubsystem.EWordFilterCensorship
enum class EWordFilterCensorship : uint8_t
{
	WordFilterCensorship_Uncensored                    = 0,
	WordFilterCensorship_Censored                      = 1,
	WordFilterCensorship_Evil                          = 2,
	WordFilterCensorship_END                           = 3
};

// Enum Engine.ParticleSystemComponent.EParticleSysParamType
enum class EParticleSysParamType : uint8_t
{
	PSPT_None                                          = 0,
	PSPT_Scalar                                        = 1,
	PSPT_ScalarRand                                    = 2,
	PSPT_Vector                                        = 3,
	PSPT_VectorRand                                    = 4,
	PSPT_Color                                         = 5,
	PSPT_Actor                                         = 6,
	PSPT_Material                                      = 7,
	PSPT_Mesh                                          = 8,
	PSPT_END                                           = 9
};

// Enum Engine.ParticleSystemComponent.ParticleReplayState
enum class EParticleReplayState : uint8_t
{
	PRS_Disabled                                       = 0,
	PRS_Capturing                                      = 1,
	PRS_Replaying                                      = 2,
	PRS_END                                            = 3
};

// Enum Engine.ParticleSystemComponent.EParticleEventType
enum class EParticleEventType : uint8_t
{
	EPET_Any                                           = 0,
	EPET_Spawn                                         = 1,
	EPET_Death                                         = 2,
	EPET_Collision                                     = 3,
	EPET_WorldAttractorCollision                       = 4,
	EPET_Kismet                                        = 5,
	EPET_END                                           = 6
};

// Enum Engine.ParticleSystem.ParticleSystemLODMethod
enum class EParticleSystemLODMethod : uint8_t
{
	PARTICLESYSTEMLODMETHOD_Automatic                  = 0,
	PARTICLESYSTEMLODMETHOD_DirectSet                  = 1,
	PARTICLESYSTEMLODMETHOD_ActivateAutomatic          = 2,
	PARTICLESYSTEMLODMETHOD_END                        = 3
};

// Enum Engine.Engine.EBasicLoadResult
enum class EBasicLoadResult : uint8_t
{
	BasicLoadResult_Pending                            = 0,
	BasicLoadResult_Success                            = 1,
	BasicLoadResult_FileNotFound                       = 2,
	BasicLoadResult_WrongVersion                       = 3,
	BasicLoadResult_FileCorrupt                        = 4,
	BasicLoadResult_MountCorrupt                       = 5,
	BasicLoadResult_UserNotSignedIn                    = 6,
	BasicLoadResult_Error                              = 7,
	BasicLoadResult_END                                = 8
};

// Enum Engine.Engine.EImageFilterOptions
enum class EImageFilterOptions : uint8_t
{
	ImageFilter_NONE                                   = 0,
	ImageFilter_SEPIA                                  = 1,
	ImageFilter_GRAYSCALE                              = 2,
	ImageFilter_SCENE_DEPTH                            = 3,
	ImageFilter_GLOWY                                  = 4,
	ImageFilter_SUBPAR                                 = 5,
	ImageFilter_SOBEL                                  = 6,
	ImageFilter_SOBEL_STRIKER                          = 7,
	ImageFilter_COMIC_BOOK                             = 8,
	ImageFilter_TOON                                   = 9,
	ImageFilter_OUTLINES                               = 10,
	ImageFilter_CHROMATIC                              = 11,
	ImageFilter_NIGHT_VISION                           = 12,
	ImageFilter_END_FILTERS                            = 13,
	ImageFilter_END                                    = 14
};

// Enum Engine.Engine.EReplayFXProperties
enum class EReplayFXProperties : uint8_t
{
	ReplayFX_Distance                                  = 0,
	ReplayFX_Kernel                                    = 1,
	ReplayFX_MaxFar                                    = 2,
	ReplayFX_MaxNear                                   = 3,
	ReplayFX_END                                       = 4
};

// Enum Engine.Engine.ETransitionType
enum class ETransitionType : uint8_t
{
	TT_None                                            = 0,
	TT_Paused                                          = 1,
	TT_Loading                                         = 2,
	TT_Saving                                          = 3,
	TT_Connecting                                      = 4,
	TT_Precaching                                      = 5,
	TT_END                                             = 6
};

// Enum Engine.FacebookIntegration.EFacebookIntegrationDelegate
enum class EFacebookIntegrationDelegate : uint8_t
{
	FID_AuthorizationComplete                          = 0,
	FID_FacebookRequestComplete                        = 1,
	FID_DialogComplete                                 = 2,
	FID_FriendsListComplete                            = 3,
	FID_END                                            = 4
};

// Enum Engine.FileWriter.FWFileType
enum class EFWFileType : uint8_t
{
	FWFT_Log                                           = 0,
	FWFT_Stats                                         = 1,
	FWFT_HTML                                          = 2,
	FWFT_User                                          = 3,
	FWFT_Debug                                         = 4,
	FWFT_END                                           = 5
};

// Enum Engine.FluidInfluenceComponent.EInfluenceType
enum class EInfluenceType : uint8_t
{
	Fluid_Flow                                         = 0,
	Fluid_Raindrops                                    = 1,
	Fluid_Wave                                         = 2,
	Fluid_Sphere                                       = 3,
	Fluid_END                                          = 4
};

// Enum Engine.FontImportOptions.EFontImportCharacterSet
enum class EFontImportCharacterSet : uint8_t
{
	FontICS_Default                                    = 0,
	FontICS_Ansi                                       = 1,
	FontICS_Symbol                                     = 2,
	FontICS_END                                        = 3
};

// Enum Engine.ForceFeedbackWaveform.EWaveformFunction
enum class EWaveformFunction : uint8_t
{
	WF_Constant                                        = 0,
	WF_LinearIncreasing                                = 1,
	WF_LinearDecreasing                                = 2,
	WF_Sin0to90                                        = 3,
	WF_Sin90to180                                      = 4,
	WF_Sin0to180                                       = 5,
	WF_Noise                                           = 6,
	WF_END                                             = 7
};

// Enum Engine.GameEngine.EFullyLoadPackageType
enum class EFullyLoadPackageType : uint8_t
{
	FULLYLOAD_Map                                      = 0,
	FULLYLOAD_Game_PreLoadClass                        = 1,
	FULLYLOAD_Game_PostLoadClass                       = 2,
	FULLYLOAD_Always                                   = 3,
	FULLYLOAD_Mutator                                  = 4,
	FULLYLOAD_END                                      = 5
};

// Enum Engine.GameInfo.EStandbyType
enum class EStandbyType : uint8_t
{
	STDBY_Rx                                           = 0,
	STDBY_Tx                                           = 1,
	STDBY_BadPing                                      = 2,
	STDBY_END                                          = 3
};

// Enum Engine.GameplayEvents.EGameStatGroups
enum class EGameStatGroups : uint8_t
{
	GSG_EngineStats                                    = 0,
	GSG_Game                                           = 1,
	GSG_Team                                           = 2,
	GSG_Player                                         = 3,
	GSG_Weapon                                         = 4,
	GSG_Damage                                         = 5,
	GSG_Projectile                                     = 6,
	GSG_Pawn                                           = 7,
	GSG_GameSpecific                                   = 8,
	GSG_Aggregate                                      = 9,
	GSG_END                                            = 10
};

// Enum Engine.WorldInfo.EHostMigrationProgress
enum class EHostMigrationProgress : uint8_t
{
	HostMigration_None                                 = 0,
	HostMigration_FindingNewHost                       = 1,
	HostMigration_MigratingAsHost                      = 2,
	HostMigration_MigratingAsClient                    = 3,
	HostMigration_ClientTravel                         = 4,
	HostMigration_HostReadyToTravel                    = 5,
	HostMigration_Failed                               = 6,
	HostMigration_END                                  = 7
};

// Enum Engine.WorldInfo.EConsoleType
enum class EConsoleType : uint8_t
{
	CONSOLE_Any                                        = 0,
	CONSOLE_Xbox360                                    = 1,
	CONSOLE_PS3                                        = 2,
	CONSOLE_Mobile                                     = 3,
	CONSOLE_IPhone                                     = 4,
	CONSOLE_Android                                    = 5,
	CONSOLE_WiiU                                       = 6,
	CONSOLE_Flash                                      = 7,
	CONSOLE_Mobile_Retina                              = 8,
	CONSOLE_PC                                         = 9,
	CONSOLE_Kindle                                     = 10,
	CONSOLE_PS4                                        = 11,
	CONSOLE_Dingo                                      = 12,
	CONSOLE_NNX                                        = 13,
	CONSOLE_Lockhart                                   = 14,
	CONSOLE_Anaconda                                   = 15,
	CONSOLE_Prospero                                   = 16,
	CONSOLE_Scorpio                                    = 17,
	CONSOLE_Ounce                                      = 18,
	CONSOLE_Edmonton                                   = 19,
	CONSOLE_END                                        = 20
};

// Enum Engine.WorldInfo.EPreferredLightmapType
enum class EPreferredLightmapType : uint8_t
{
	EPLT_Default                                       = 0,
	EPLT_Directional                                   = 1,
	EPLT_Simple                                        = 2,
	EPLT_END                                           = 3
};

// Enum Engine.WorldInfo.EVisibilityAggressiveness
enum class EVisibilityAggressiveness : uint8_t
{
	VIS_LeastAggressive                                = 0,
	VIS_ModeratelyAggressive                           = 1,
	VIS_MostAggressive                                 = 2,
	VIS_Max                                            = 3
};

// Enum Engine.WorldInfo.ENetMode
enum class ENetMode : uint8_t
{
	NM_Standalone                                      = 0,
	NM_DedicatedServer                                 = 1,
	NM_ListenServer                                    = 2,
	NM_Client                                          = 3,
	NM_END                                             = 4
};

// Enum Engine.SeqAct_ControlMovieTexture.EMovieControlType
enum class EMovieControlType : uint8_t
{
	MCT_Play                                           = 0,
	MCT_Stop                                           = 1,
	MCT_Pause                                          = 2,
	MCT_END                                            = 3
};

// Enum Engine.Settings.EPropertyValueMappingType
enum class EPropertyValueMappingType : uint8_t
{
	PVMT_RawValue                                      = 0,
	PVMT_PredefinedValues                              = 1,
	PVMT_Ranged                                        = 2,
	PVMT_IdMapped                                      = 3,
	PVMT_END                                           = 4
};

// Enum Engine.OnlineGameSearch.EOnlineGameSearchComparisonType
enum class EOnlineGameSearchComparisonType : uint8_t
{
	OGSCT_Equals                                       = 0,
	OGSCT_NotEquals                                    = 1,
	OGSCT_GreaterThan                                  = 2,
	OGSCT_GreaterThanEquals                            = 3,
	OGSCT_LessThan                                     = 4,
	OGSCT_LessThanEquals                               = 5,
	OGSCT_END                                          = 6
};

// Enum Engine.OnlineGameSearch.EOnlineGameSearchEntryType
enum class EOnlineGameSearchEntryType : uint8_t
{
	OGSET_Property                                     = 0,
	OGSET_LocalizedSetting                             = 1,
	OGSET_ObjectProperty                               = 2,
	OGSET_END                                          = 3
};

// Enum Engine.OnlineGameSearch.EOnlineGameSearchSortType
enum class EOnlineGameSearchSortType : uint8_t
{
	OGSSO_Ascending                                    = 0,
	OGSSO_Descending                                   = 1,
	OGSSO_END                                          = 2
};

// Enum Engine.PlayerController.EProgressMessageType
enum class EProgressMessageType : uint8_t
{
	PMT_Clear                                          = 0,
	PMT_Information                                    = 1,
	PMT_AdminMessage                                   = 2,
	PMT_DownloadProgress                               = 3,
	PMT_ConnectionFailure                              = 4,
	PMT_PeerConnectionFailure                          = 5,
	PMT_PeerHostMigrationFailure                       = 6,
	PMT_SocketFailure                                  = 7,
	PMT_Reconnect                                      = 8,
	PMT_AntiCheatKick                                  = 9,
	PMT_END                                            = 10
};

// Enum Engine.PlayerController.EInputMatchAction
enum class EInputMatchAction : uint8_t
{
	IMA_GreaterThan                                    = 0,
	IMA_LessThan                                       = 1,
	IMA_END                                            = 2
};

// Enum Engine.PlayerController.EInputTypes
enum class EInputTypes : uint8_t
{
	IT_XAxis                                           = 0,
	IT_YAxis                                           = 1,
	IT_END                                             = 2
};

// Enum Engine.GameViewportClient.ESplitScreenType
enum class ESplitScreenType : uint8_t
{
	eSST_NONE                                          = 0,
	eSST_2P_HORIZONTAL                                 = 1,
	eSST_2P_VERTICAL                                   = 2,
	eSST_3P_FAVOR_TOP                                  = 3,
	eSST_3P_FAVOR_BOTTOM                               = 4,
	eSST_3P_FAVOR_SIDELEFT                             = 5,
	eSST_3P_FAVOR_SIDERIGHT                            = 6,
	eSST_4P                                            = 7,
	eSST_END                                           = 8
};

// Enum Engine.GameViewportClient.ESafeZoneType
enum class ESafeZoneType : uint8_t
{
	eSZ_TOP                                            = 0,
	eSZ_BOTTOM                                         = 1,
	eSZ_LEFT                                           = 2,
	eSZ_RIGHT                                          = 3,
	eSZ_END                                            = 4
};

// Enum Engine.GameViewportClient.ESetMode
enum class ESetMode : uint8_t
{
	SetMode_Toggle                                     = 0,
	SetMode_Enable                                     = 1,
	SetMode_Disable                                    = 2,
	SetMode_END                                        = 3
};

// Enum Engine.InAppMessageBase.EInAppMessageInterfaceDelegate
enum class EInAppMessageInterfaceDelegate : uint8_t
{
	IAMD_InAppSMSUIComplete                            = 0,
	IAMD_InAppEmailComplete                            = 1,
	IAMD_END                                           = 2
};

// Enum Engine.InGameAdManager.EAdManagerDelegate
enum class EAdManagerDelegate : uint8_t
{
	AMD_ClickedBanner                                  = 0,
	AMD_UserClosedAd                                   = 1,
	AMD_END                                            = 2
};

// Enum Engine.InstancedFoliageSettings.FoliageCullOption
enum class EFoliageCullOption : uint8_t
{
	FOLIAGECULL_Cull                                   = 0,
	FOLIAGECULL_ScaleZ                                 = 1,
	FOLIAGECULL_ScaleXYZ                               = 2,
	FOLIAGECULL_TranslateZ                             = 3,
	FOLIAGECULL_END                                    = 4
};

// Enum Engine.Interface_NavMeshPathObstacle.EEdgeHandlingStatus
enum class EEdgeHandlingStatus : uint8_t
{
	EHS_AddedBothDirs                                  = 0,
	EHS_Added0to1                                      = 1,
	EHS_Added1to0                                      = 2,
	EHS_AddedNone                                      = 3,
	EHS_END                                            = 4
};

// Enum Engine.InterpTrack.ETrackActiveCondition
enum class ETrackActiveCondition : uint8_t
{
	ETAC_Always                                        = 0,
	ETAC_GoreEnabled                                   = 1,
	ETAC_GoreDisabled                                  = 2,
	ETAC_END                                           = 3
};

// Enum Engine.InterpTrackHeadTracking.EHeadTrackingAction
enum class EHeadTrackingAction : uint8_t
{
	EHTA_DisableHeadTracking                           = 0,
	EHTA_EnableHeadTracking                            = 1,
	EHTA_END                                           = 2
};

// Enum Engine.InterpTrackToggle.ETrackToggleAction
enum class ETrackToggleAction : uint8_t
{
	ETTA_Off                                           = 0,
	ETTA_On                                            = 1,
	ETTA_Toggle                                        = 2,
	ETTA_Trigger                                       = 3,
	ETTA_END                                           = 4
};

// Enum Engine.InterpTrackVisibility.EVisibilityTrackCondition
enum class EVisibilityTrackCondition : uint8_t
{
	EVTC_Always                                        = 0,
	EVTC_GoreEnabled                                   = 1,
	EVTC_GoreDisabled                                  = 2,
	EVTC_END                                           = 3
};

// Enum Engine.InterpTrackVisibility.EVisibilityTrackAction
enum class EVisibilityTrackAction : uint8_t
{
	EVTA_Hide                                          = 0,
	EVTA_Show                                          = 1,
	EVTA_Toggle                                        = 2,
	EVTA_END                                           = 3
};

// Enum Engine.InterpTrackMove.EInterpTrackMoveRotMode
enum class EInterpTrackMoveRotMode : uint8_t
{
	IMR_Keyframed                                      = 0,
	IMR_LookAtGroup                                    = 1,
	IMR_Ignore                                         = 2,
	IMR_END                                            = 3
};

// Enum Engine.InterpTrackMove.EInterpTrackMoveFrame
enum class EInterpTrackMoveFrame : uint8_t
{
	IMF_World                                          = 0,
	IMF_RelativeToInitial                              = 1,
	IMF_END                                            = 2
};

// Enum Engine.InterpTrackMoveAxis.EInterpMoveAxis
enum class EInterpMoveAxis : uint8_t
{
	AXIS_TranslationX                                  = 0,
	AXIS_TranslationY                                  = 1,
	AXIS_TranslationZ                                  = 2,
	AXIS_RotationX                                     = 3,
	AXIS_RotationY                                     = 4,
	AXIS_RotationZ                                     = 5,
	AXIS_END                                           = 6
};

// Enum Engine.Landscape.ELandscapeSetupErrors
enum class ELandscapeSetupErrors : uint8_t
{
	LSE_None                                           = 0,
	LSE_NoLandscapeInfo                                = 1,
	LSE_CollsionXY                                     = 2,
	LSE_NoLayerInfo                                    = 3,
	LSE_END                                            = 4
};

// Enum Engine.LandscapeGizmoActiveActor.ELandscapeGizmoType
enum class ELandscapeGizmoType : uint8_t
{
	LGT_None                                           = 0,
	LGT_Height                                         = 1,
	LGT_Weight                                         = 2,
	LGT_END                                            = 3
};

// Enum Engine.LevelGridVolume.LevelGridCellShape
enum class ELevelGridCellShape : uint8_t
{
	LGCS_Box                                           = 0,
	LGCS_Hex                                           = 1,
	LGCS_END                                           = 2
};

// Enum Engine.LevelStreamingVolume.EStreamingVolumeUsage
enum class EStreamingVolumeUsage : uint8_t
{
	SVB_Loading                                        = 0,
	SVB_LoadingAndVisibility                           = 1,
	SVB_VisibilityBlockingOnLoad                       = 2,
	SVB_BlockingOnLoad                                 = 3,
	SVB_LoadingNotVisible                              = 4,
	SVB_END                                            = 5
};

// Enum Engine.OnlineAuthInterface.EAuthStatus
enum class EAuthStatus : uint8_t
{
	AUS_NotStarted                                     = 0,
	AUS_Pending                                        = 1,
	AUS_Authenticated                                  = 2,
	AUS_Failed                                         = 3,
	AUS_END                                            = 4
};

// Enum Engine.OnlineAuthInterface.EAuthTicketServiceRequester
enum class EAuthTicketServiceRequester : uint8_t
{
	AuthTicketServiceRequester_Psynet                  = 0,
	AuthTicketServiceRequester_EpicOnlineServices      = 1,
	AuthTicketServiceRequester_END                     = 2
};

// Enum Engine.MaterialExpressionAntialiasedTextureMask.ETextureColorChannel
enum class ETextureColorChannel : uint8_t
{
	TCC_Red                                            = 0,
	TCC_Green                                          = 1,
	TCC_Blue                                           = 2,
	TCC_Alpha                                          = 3,
	TCC_END                                            = 4
};

// Enum Engine.MaterialExpressionCustom.ECustomMaterialOutputType
enum class ECustomMaterialOutputType : uint8_t
{
	CMOT_Float1                                        = 0,
	CMOT_Float2                                        = 1,
	CMOT_Float3                                        = 2,
	CMOT_Float4                                        = 3,
	CMOT_END                                           = 4
};

// Enum Engine.MaterialExpressionDepthOfFieldFunction.EDepthOfFieldFunctionValue
enum class EDepthOfFieldFunctionValue : uint8_t
{
	TDOF_NearAndFarMask                                = 0,
	TDOF_NearMask                                      = 1,
	TDOF_FarMask                                       = 2,
	TDOF_END                                           = 3
};

// Enum Engine.MaterialExpressionFunctionInput.EFunctionInputType
enum class EFunctionInputType : uint8_t
{
	FunctionInput_Scalar                               = 0,
	FunctionInput_Vector2                              = 1,
	FunctionInput_Vector3                              = 2,
	FunctionInput_Vector4                              = 3,
	FunctionInput_Texture2D                            = 4,
	FunctionInput_TextureCube                          = 5,
	FunctionInput_StaticBool                           = 6,
	FunctionInput_END                                  = 7
};

// Enum Engine.MaterialExpressionGameObjectParameter.EGameObjectShaderParameterType
enum class EGameObjectShaderParameterType : uint8_t
{
	GOSPT_BallPositionAndSize                          = 0,
	GOSPT_BallVelocity                                 = 1,
	GOSPT_BallSpeed                                    = 2,
	GOSPT_BallMaxSpeed                                 = 3,
	GOSPT_IsSuperSonic                                 = 4,
	GOSPT_IsBoosting                                   = 5,
	GOSPT_IsMakingContactWithBall                      = 6,
	GOSPT_IsCarOnGround                                = 7,
	GOSPT_ObjectDistanceToBall                         = 8,
	GOSPT_ObjectSpeed                                  = 9,
	GOSPT_ObjectVelocity                               = 10,
	GOSPT_SuperSonicSpeed                              = 11,
	GOSPT_CarMaxSpeed                                  = 12,
	GOSPT_END                                          = 13
};

// Enum Engine.MaterialExpressionGameParameter.EGameShaderParameterType
enum class EGameShaderParameterType : uint8_t
{
	GSPT_Team0_ColorPrimary                            = 0,
	GSPT_Team0_ColorSecondary                          = 1,
	GSPT_Team1_ColorPrimary                            = 2,
	GSPT_Team1_ColorSecondary                          = 3,
	GSPT_Team0_ColorPrimaryFullBrightness              = 4,
	GSPT_Team0_ColorSecondaryFullBrightness            = 5,
	GSPT_Team1_ColorPrimaryFullBrightness              = 6,
	GSPT_Team1_ColorSecondaryFullBrightness            = 7,
	GSPT_END                                           = 8
};

// Enum Engine.MaterialExpressionLandscapeLayerBlend.ELandscapeLayerBlendType
enum class ELandscapeLayerBlendType : uint8_t
{
	LB_AlphaBlend                                      = 0,
	LB_HeightBlend                                     = 1,
	LB_END                                             = 2
};

// Enum Engine.MaterialExpressionMusicAnalysisParameter.EMusicAnalysisShaderParameterType
enum class EMusicAnalysisShaderParameterType : uint8_t
{
	MAPT_Music_Band                                    = 0,
	MAPT_Music_Band01                                  = 1,
	MAPT_Music_Band02                                  = 2,
	MAPT_Music_Band03                                  = 3,
	MAPT_Music_Band04                                  = 4,
	MAPT_Music_Band05                                  = 5,
	MAPT_Music_Band06                                  = 6,
	MAPT_Music_Band07                                  = 7,
	MAPT_Music_Band08                                  = 8,
	MAPT_Music_Band09                                  = 9,
	MAPT_Music_LowFreq_Envelope                        = 10,
	MAPT_Music_HighFreq_Envelope                       = 11,
	MAPT_Music_Band_Smoothed                           = 12,
	MAPT_Music_Band_Smoothed01                         = 13,
	MAPT_Music_Band_Smoothed02                         = 14,
	MAPT_Music_Band_Smoothed03                         = 15,
	MAPT_Music_Band_Smoothed04                         = 16,
	MAPT_Music_Band_Smoothed05                         = 17,
	MAPT_Music_Band_Smoothed06                         = 18,
	MAPT_Music_Band_Smoothed07                         = 19,
	MAPT_Music_Band_Smoothed08                         = 20,
	MAPT_Music_Band_Smoothed09                         = 21,
	MAPT_Music_LowFreq_Envelope_Smoothed               = 22,
	MAPT_Music_HighFreq_Envelope_Smoothed              = 23,
	MAPT_Music_END                                     = 24
};

// Enum Engine.MaterialExpressionPitchTekTextureSample.EPitchTekTextureType
enum class EPitchTekTextureType : uint8_t
{
	PitchTek_ColorTexture                              = 0,
	PitchTek_DataTexture                               = 1,
	PitchTek_END                                       = 2
};

// Enum Engine.MaterialExpressionSceneTexture.ESceneTextureType
enum class ESceneTextureType : uint8_t
{
	SceneTex_Lighting                                  = 0,
	SceneTex_END                                       = 1
};

// Enum Engine.MaterialExpressionTerrainLayerCoords.ETerrainCoordMappingType
enum class ETerrainCoordMappingType : uint8_t
{
	TCMT_Auto                                          = 0,
	TCMT_XY                                            = 1,
	TCMT_XZ                                            = 2,
	TCMT_YZ                                            = 3,
	TCMT_END                                           = 4
};

// Enum Engine.MaterialExpressionTransform.EMaterialVectorCoordTransform
enum class EMaterialVectorCoordTransform : uint8_t
{
	TRANSFORM_World                                    = 0,
	TRANSFORM_View                                     = 1,
	TRANSFORM_Local                                    = 2,
	TRANSFORM_Tangent                                  = 3,
	TRANSFORM_END                                      = 4
};

// Enum Engine.MaterialExpressionTransform.EMaterialVectorCoordTransformSource
enum class EMaterialVectorCoordTransformSource : uint8_t
{
	TRANSFORMSOURCE_World                              = 0,
	TRANSFORMSOURCE_Local                              = 1,
	TRANSFORMSOURCE_Tangent                            = 2,
	TRANSFORMSOURCE_View                               = 3,
	TRANSFORMSOURCE_END                                = 4
};

// Enum Engine.MaterialExpressionTransformPosition.EMaterialPositionTransform
enum class EMaterialPositionTransform : uint8_t
{
	TRANSFORMPOS_World                                 = 0,
	TRANSFORMPOS_END                                   = 1
};

// Enum Engine.MaterialExpressionTransformPosition.EMaterialPositionTransformSource
enum class EMaterialPositionTransformSource : uint8_t
{
	TRANSFORMPOSSOURCE_Local                           = 0,
	TRANSFORMPOSSOURCE_PostProjection                  = 1,
	TRANSFORMPOSSOURCE_END                             = 2
};

// Enum Engine.MicroTransactionBase.EMicroTransactionDelegate
enum class EMicroTransactionDelegate : uint8_t
{
	MTD_PurchaseQueryComplete                          = 0,
	MTD_PurchaseComplete                               = 1,
	MTD_END                                            = 2
};

// Enum Engine.MicroTransactionBase.EMicroTransactionResult
enum class EMicroTransactionResult : uint8_t
{
	MTR_Succeeded                                      = 0,
	MTR_Failed                                         = 1,
	MTR_Canceled                                       = 2,
	MTR_RestoredFromServer                             = 3,
	MTR_END                                            = 4
};

// Enum Engine.NxForceFieldGeneric.FFG_ForceFieldCoordinates
enum class EFFG_ForceFieldCoordinates : uint8_t
{
	FFG_CARTESIAN                                      = 0,
	FFG_SPHERICAL                                      = 1,
	FFG_CYLINDRICAL                                    = 2,
	FFG_TOROIDAL                                       = 3,
	FFG_END                                            = 4
};

// Enum Engine.NxGenericForceFieldBrush.FFB_ForceFieldCoordinates
enum class EFFB_ForceFieldCoordinates : uint8_t
{
	FFB_CARTESIAN                                      = 0,
	FFB_SPHERICAL                                      = 1,
	FFB_CYLINDRICAL                                    = 2,
	FFB_TOROIDAL                                       = 3,
	FFB_END                                            = 4
};

// Enum Engine.OnlineLobbySettings.ELobbyKickReason
enum class ELobbyKickReason : uint8_t
{
	LKR_Unknown                                        = 0,
	LKR_Kicked                                         = 1,
	LKR_Full                                           = 2,
	LKR_InGame                                         = 3,
	LKR_LeaveAction                                    = 4,
	LKR_OwnerDisappeared                               = 5,
	LKR_ConnectionError                                = 6,
	LKR_SignedOut                                      = 7,
	LKR_CrossplayDisabled                              = 8,
	LKR_LeaderPartyUp                                  = 9,
	LKR_NotInTourParty                                 = 10,
	LKR_TourCheckingIn                                 = 11,
	LKR_END                                            = 12
};

// Enum Engine.OnlineLobbySettings.ELobbyVisibility
enum class ELobbyVisibility : uint8_t
{
	LV_Public                                          = 0,
	LV_Friends                                         = 1,
	LV_Private                                         = 2,
	LV_Invisible                                       = 3,
	LV_END                                             = 4
};

// Enum Engine.OnlineLobbySettings.ELobbyDistance
enum class ELobbyDistance : uint8_t
{
	LD_Best                                            = 0,
	LD_Close                                           = 1,
	LD_Far                                             = 2,
	LD_Any                                             = 3,
	LD_END                                             = 4
};

// Enum Engine.OnlinePlayerStorage.EOnlineProfilePropertyOwner
enum class EOnlineProfilePropertyOwner : uint8_t
{
	OPPO_None                                          = 0,
	OPPO_OnlineService                                 = 1,
	OPPO_Game                                          = 2,
	OPPO_END                                           = 3
};

// Enum Engine.OnlinePlayerStorage.EOnlinePlayerStorageAsyncState
enum class EOnlinePlayerStorageAsyncState : uint8_t
{
	OPAS_NotStarted                                    = 0,
	OPAS_Read                                          = 1,
	OPAS_Write                                         = 2,
	OPAS_Finished                                      = 3,
	OPAS_END                                           = 4
};

// Enum Engine.OnlineProfileSettings.EProfileSettingID
enum class EProfileSettingID : uint8_t
{
	PSI_Unknown                                        = 0,
	PSI_ControllerVibration                            = 1,
	PSI_YInversion                                     = 2,
	PSI_GamerCred                                      = 3,
	PSI_GamerRep                                       = 4,
	PSI_VoiceMuted                                     = 5,
	PSI_VoiceThruSpeakers                              = 6,
	PSI_VoiceVolume                                    = 7,
	PSI_GamerPictureKey                                = 8,
	PSI_GamerMotto                                     = 9,
	PSI_GamerTitlesPlayed                              = 10,
	PSI_GamerAchievementsEarned                        = 11,
	PSI_GameDifficulty                                 = 12,
	PSI_ControllerSensitivity                          = 13,
	PSI_PreferredColor1                                = 14,
	PSI_PreferredColor2                                = 15,
	PSI_AutoAim                                        = 16,
	PSI_AutoCenter                                     = 17,
	PSI_MovementControl                                = 18,
	PSI_RaceTransmission                               = 19,
	PSI_RaceCameraLocation                             = 20,
	PSI_RaceBrakeControl                               = 21,
	PSI_RaceAcceleratorControl                         = 22,
	PSI_GameCredEarned                                 = 23,
	PSI_GameAchievementsEarned                         = 24,
	PSI_EndLiveIds                                     = 25,
	PSI_ProfileVersionNum                              = 26,
	PSI_ProfileSaveCount                               = 27,
	PSI_END                                            = 28
};

// Enum Engine.OnlineProfileSettings.EProfileDifficultyOptions
enum class EProfileDifficultyOptions : uint8_t
{
	PDO_Normal                                         = 0,
	PDO_Easy                                           = 1,
	PDO_Hard                                           = 2,
	PDO_END                                            = 3
};

// Enum Engine.OnlineProfileSettings.EProfileControllerSensitivityOptions
enum class EProfileControllerSensitivityOptions : uint8_t
{
	PCSO_Medium                                        = 0,
	PCSO_Low                                           = 1,
	PCSO_High                                          = 2,
	PCSO_END                                           = 3
};

// Enum Engine.OnlineProfileSettings.EProfilePreferredColorOptions
enum class EProfilePreferredColorOptions : uint8_t
{
	PPCO_None                                          = 0,
	PPCO_Black                                         = 1,
	PPCO_White                                         = 2,
	PPCO_Yellow                                        = 3,
	PPCO_Orange                                        = 4,
	PPCO_Pink                                          = 5,
	PPCO_Red                                           = 6,
	PPCO_Purple                                        = 7,
	PPCO_Blue                                          = 8,
	PPCO_Green                                         = 9,
	PPCO_Brown                                         = 10,
	PPCO_Silver                                        = 11,
	PPCO_END                                           = 12
};

// Enum Engine.OnlineProfileSettings.EProfileAutoAimOptions
enum class EProfileAutoAimOptions : uint8_t
{
	PAAO_Off                                           = 0,
	PAAO_On                                            = 1,
	PAAO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileAutoCenterOptions
enum class EProfileAutoCenterOptions : uint8_t
{
	PACO_Off                                           = 0,
	PACO_On                                            = 1,
	PACO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileMovementControlOptions
enum class EProfileMovementControlOptions : uint8_t
{
	PMCO_L_Thumbstick                                  = 0,
	PMCO_R_Thumbstick                                  = 1,
	PMCO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileRaceTransmissionOptions
enum class EProfileRaceTransmissionOptions : uint8_t
{
	PRTO_Auto                                          = 0,
	PRTO_Manual                                        = 1,
	PRTO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileRaceCameraLocationOptions
enum class EProfileRaceCameraLocationOptions : uint8_t
{
	PRCLO_Behind                                       = 0,
	PRCLO_Front                                        = 1,
	PRCLO_Inside                                       = 2,
	PRCLO_END                                          = 3
};

// Enum Engine.OnlineProfileSettings.EProfileRaceBrakeControlOptions
enum class EProfileRaceBrakeControlOptions : uint8_t
{
	PRBCO_Trigger                                      = 0,
	PRBCO_Button                                       = 1,
	PRBCO_END                                          = 2
};

// Enum Engine.OnlineProfileSettings.EProfileRaceAcceleratorControlOptions
enum class EProfileRaceAcceleratorControlOptions : uint8_t
{
	PRACO_Trigger                                      = 0,
	PRACO_Button                                       = 1,
	PRACO_END                                          = 2
};

// Enum Engine.OnlineProfileSettings.EProfileYInversionOptions
enum class EProfileYInversionOptions : uint8_t
{
	PYIO_Off                                           = 0,
	PYIO_On                                            = 1,
	PYIO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileXInversionOptions
enum class EProfileXInversionOptions : uint8_t
{
	PXIO_Off                                           = 0,
	PXIO_On                                            = 1,
	PXIO_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileOmniDirEvadeOptions
enum class EProfileOmniDirEvadeOptions : uint8_t
{
	PODI_Off                                           = 0,
	PODI_On                                            = 1,
	PODI_END                                           = 2
};

// Enum Engine.OnlineProfileSettings.EProfileControllerVibrationToggleOptions
enum class EProfileControllerVibrationToggleOptions : uint8_t
{
	PCVTO_Off                                          = 0,
	PCVTO_IgnoreThis                                   = 1,
	PCVTO_IgnoreThis2                                  = 2,
	PCVTO_On                                           = 3,
	PCVTO_END                                          = 4
};

// Enum Engine.OnlineProfileSettings.EProfileVoiceThruSpeakersOptions
enum class EProfileVoiceThruSpeakersOptions : uint8_t
{
	PVTSO_Off                                          = 0,
	PVTSO_On                                           = 1,
	PVTSO_Both                                         = 2,
	PVTSO_END                                          = 3
};

// Enum Engine.ParticleEmitter.EEmitterRenderMode
enum class EEmitterRenderMode : uint8_t
{
	ERM_Normal                                         = 0,
	ERM_Point                                          = 1,
	ERM_Cross                                          = 2,
	ERM_None                                           = 3,
	ERM_END                                            = 4
};

// Enum Engine.ParticleEmitter.EParticleSubUVInterpMethod
enum class EParticleSubUVInterpMethod : uint8_t
{
	PSUVIM_None                                        = 0,
	PSUVIM_Linear                                      = 1,
	PSUVIM_Linear_Blend                                = 2,
	PSUVIM_Random                                      = 3,
	PSUVIM_Random_Blend                                = 4,
	PSUVIM_END                                         = 5
};

// Enum Engine.ParticleEmitter.EParticleBurstMethod
enum class EParticleBurstMethod : uint8_t
{
	EPBM_Instant                                       = 0,
	EPBM_Interpolated                                  = 1,
	EPBM_END                                           = 2
};

// Enum Engine.ParticleModule.EModuleType
enum class EModuleType : uint8_t
{
	EPMT_General                                       = 0,
	EPMT_TypeData                                      = 1,
	EPMT_Beam                                          = 2,
	EPMT_Trail                                         = 3,
	EPMT_Spawn                                         = 4,
	EPMT_Required                                      = 5,
	EPMT_Event                                         = 6,
	EPMT_END                                           = 7
};

// Enum Engine.ParticleModule.EParticleSourceSelectionMethod
enum class EParticleSourceSelectionMethod : uint8_t
{
	EPSSM_Random                                       = 0,
	EPSSM_Sequential                                   = 1,
	EPSSM_END                                          = 2
};

// Enum Engine.ParticleModuleAttractorBoneSocket.EBoneSocketAttractorFalloffType
enum class EBoneSocketAttractorFalloffType : uint8_t
{
	BSFOFF_Constant                                    = 0,
	BSFOFF_Linear                                      = 1,
	BSFOFF_Exponent                                    = 2,
	BSFOFF_END                                         = 3
};

// Enum Engine.ParticleModuleAttractorBoneSocket.ELocationBoneSocketDestSelectionMethod
enum class ELocationBoneSocketDestSelectionMethod : uint8_t
{
	BONESOCKETDESTSEL_Sequential                       = 0,
	BONESOCKETDESTSEL_Random                           = 1,
	BONESOCKETDESTSEL_RandomExhaustive                 = 2,
	BONESOCKETDESTSEL_BlendAll                         = 3,
	BONESOCKETDESTSEL_END                              = 4
};

// Enum Engine.ParticleModuleAttractorBoneSocket.ELocationBoneSocketDestination
enum class ELocationBoneSocketDestination : uint8_t
{
	BONESOCKETDEST_Bones                               = 0,
	BONESOCKETDEST_Sockets                             = 1,
	BONESOCKETDEST_END                                 = 2
};

// Enum Engine.ParticleModuleAttractorParticle.EAttractorParticleSelectionMethod
enum class EAttractorParticleSelectionMethod : uint8_t
{
	EAPSM_Random                                       = 0,
	EAPSM_Sequential                                   = 1,
	EAPSM_END                                          = 2
};

// Enum Engine.ParticleModuleAttractorSkelVertSurface.EVertSurfaceAttractorFalloffType
enum class EVertSurfaceAttractorFalloffType : uint8_t
{
	VSFOFF_Constant                                    = 0,
	VSFOFF_Linear                                      = 1,
	VSFOFF_Exponent                                    = 2,
	VSFOFF_END                                         = 3
};

// Enum Engine.ParticleModuleAttractorSkelVertSurface.EAttractorSkelVertSurfaceDestination
enum class EAttractorSkelVertSurfaceDestination : uint8_t
{
	VERTSURFACEDEST_Vert                               = 0,
	VERTSURFACEDEST_Surface                            = 1,
	VERTSURFACEDEST_END                                = 2
};

// Enum Engine.ParticleModuleBeamBase.Beam2SourceTargetMethod
enum class EBeam2SourceTargetMethod : uint8_t
{
	PEB2STM_Default                                    = 0,
	PEB2STM_UserSet                                    = 1,
	PEB2STM_Emitter                                    = 2,
	PEB2STM_Particle                                   = 3,
	PEB2STM_Actor                                      = 4,
	PEB25TM_SkelMeshActor                              = 5,
	Beam2SourceTargetMethod_END                        = 6
};

// Enum Engine.ParticleModuleBeamBase.Beam2SourceTargetTangentMethod
enum class EBeam2SourceTargetTangentMethod : uint8_t
{
	PEB2STTM_Direct                                    = 0,
	PEB2STTM_UserSet                                   = 1,
	PEB2STTM_Distribution                              = 2,
	PEB2STTM_Emitter                                   = 3,
	PEB2STTM_END                                       = 4
};

// Enum Engine.ParticleModuleBeamModifier.BeamModifierType
enum class EBeamModifierType : uint8_t
{
	PEB2MT_Source                                      = 0,
	PEB2MT_Target                                      = 1,
	PEB2MT_END                                         = 2
};

// Enum Engine.ParticleModuleCameraOffset.EParticleCameraOffsetUpdateMethod
enum class EParticleCameraOffsetUpdateMethod : uint8_t
{
	EPCOUM_DirectSet                                   = 0,
	EPCOUM_Additive                                    = 1,
	EPCOUM_Scalar                                      = 2,
	EPCOUM_END                                         = 3
};

// Enum Engine.ParticleModuleCollisionBase.EParticleCollisionComplete
enum class EParticleCollisionComplete : uint8_t
{
	EPCC_Kill                                          = 0,
	EPCC_Freeze                                        = 1,
	EPCC_HaltCollisions                                = 2,
	EPCC_FreezeTranslation                             = 3,
	EPCC_FreezeRotation                                = 4,
	EPCC_FreezeMovement                                = 5,
	EPCC_END                                           = 6
};

// Enum Engine.ParticleModuleCollision.ParticleAttractorActionType
enum class EParticleAttractorActionType : uint8_t
{
	PAAT_None                                          = 0,
	PAAT_Destroy                                       = 1,
	PAAT_Freeze                                        = 2,
	PAAT_Event                                         = 3,
	PAAT_END                                           = 4
};

// Enum Engine.ParticleModuleLocationBoneSocket.ELocationBoneSocketSource
enum class ELocationBoneSocketSource : uint8_t
{
	BONESOCKETSOURCE_Bones                             = 0,
	BONESOCKETSOURCE_Sockets                           = 1,
	BONESOCKETSOURCE_END                               = 2
};

// Enum Engine.ParticleModuleLocationBoneSocket.ELocationBoneSocketSelectionMethod
enum class ELocationBoneSocketSelectionMethod : uint8_t
{
	BONESOCKETSEL_Sequential                           = 0,
	BONESOCKETSEL_Random                               = 1,
	BONESOCKETSEL_RandomExhaustive                     = 2,
	BONESOCKETSEL_END                                  = 3
};

// Enum Engine.ParticleModuleLocationEmitter.ELocationEmitterSelectionMethod
enum class ELocationEmitterSelectionMethod : uint8_t
{
	ELESM_Random                                       = 0,
	ELESM_Sequential                                   = 1,
	ELESM_END                                          = 2
};

// Enum Engine.ParticleModuleLocationPrimitiveCylinder.CylinderHeightAxis
enum class ECylinderHeightAxis : uint8_t
{
	PMLPC_HEIGHTAXIS_X                                 = 0,
	PMLPC_HEIGHTAXIS_Y                                 = 1,
	PMLPC_HEIGHTAXIS_Z                                 = 2,
	PMLPC_HEIGHTAXIS_END                               = 3
};

// Enum Engine.ParticleModuleLocationSkelVertSurface.ELocationSkelVertSurfaceSource
enum class ELocationSkelVertSurfaceSource : uint8_t
{
	VERTSURFACESOURCE_Vert                             = 0,
	VERTSURFACESOURCE_Surface                          = 1,
	VERTSURFACESOURCE_END                              = 2
};

// Enum Engine.ParticleModuleLocationStaticVertSurface.ELocationStaticVertSurfaceSource
enum class ELocationStaticVertSurfaceSource : uint8_t
{
	VERTSTATICSURFACESOURCE_Vert                       = 0,
	VERTSTATICSURFACESOURCE_Surface                    = 1,
	VERTSTATICSURFACESOURCE_END                        = 2
};

// Enum Engine.ParticleModuleOrbit.EOrbitChainMode
enum class EOrbitChainMode : uint8_t
{
	EOChainMode_Add                                    = 0,
	EOChainMode_Scale                                  = 1,
	EOChainMode_Link                                   = 2,
	EOChainMode_END                                    = 3
};

// Enum Engine.ParticleModuleOrientationAxisLock.EParticleAxisLock
enum class EParticleAxisLock : uint8_t
{
	EPAL_NONE                                          = 0,
	EPAL_X                                             = 1,
	EPAL_Y                                             = 2,
	EPAL_Z                                             = 3,
	EPAL_NEGATIVE_X                                    = 4,
	EPAL_NEGATIVE_Y                                    = 5,
	EPAL_NEGATIVE_Z                                    = 6,
	EPAL_ROTATE_X                                      = 7,
	EPAL_ROTATE_Y                                      = 8,
	EPAL_ROTATE_Z                                      = 9,
	EPAL_END                                           = 10
};

// Enum Engine.ParticleModuleParameterDynamic.EEmitterDynamicParameterValue
enum class EEmitterDynamicParameterValue : uint8_t
{
	EDPV_UserSet                                       = 0,
	EDPV_VelocityX                                     = 1,
	EDPV_VelocityY                                     = 2,
	EDPV_VelocityZ                                     = 3,
	EDPV_VelocityMag                                   = 4,
	EDPV_END                                           = 5
};

// Enum Engine.ParticleModulePhysicsVolumes.EParticleLevelInfluenceType
enum class EParticleLevelInfluenceType : uint8_t
{
	LIT_Never                                          = 0,
	LIT_OutsidePhysicsVolumes                          = 1,
	LIT_Always                                         = 2,
	LIT_END                                            = 3
};

// Enum Engine.ParticleSpriteEmitter.EParticleScreenAlignment
enum class EParticleScreenAlignment : uint8_t
{
	PSA_Square                                         = 0,
	PSA_Rectangle                                      = 1,
	PSA_Velocity                                       = 2,
	PSA_TypeSpecific                                   = 3,
	PSA_END                                            = 4
};

// Enum Engine.ParticleModuleRequired.EEmitterNormalsMode
enum class EEmitterNormalsMode : uint8_t
{
	ENM_CameraFacing                                   = 0,
	ENM_Spherical                                      = 1,
	ENM_Cylindrical                                    = 2,
	ENM_END                                            = 3
};

// Enum Engine.ParticleModuleRequired.EParticleSortMode
enum class EParticleSortMode : uint8_t
{
	PSORTMODE_None                                     = 0,
	PSORTMODE_ViewProjDepth                            = 1,
	PSORTMODE_DistanceToView                           = 2,
	PSORTMODE_Age_OldestFirst                          = 3,
	PSORTMODE_Age_NewestFirst                          = 4,
	PSORTMODE_END                                      = 5
};

// Enum Engine.ParticleModuleTrailSource.ETrail2SourceMethod
enum class ETrail2SourceMethod : uint8_t
{
	PET2SRCM_Default                                   = 0,
	PET2SRCM_Particle                                  = 1,
	PET2SRCM_Actor                                     = 2,
	PET2SRCM_END                                       = 3
};

// Enum Engine.ParticleModuleTrailSpawn.ETrail2SpawnMethod
enum class ETrail2SpawnMethod : uint8_t
{
	PET2SM_Emitter                                     = 0,
	PET2SM_Velocity                                    = 1,
	PET2SM_Distance                                    = 2,
	PET2SM_END                                         = 3
};

// Enum Engine.ParticleModuleTrailTaper.ETrailTaperMethod
enum class ETrailTaperMethod : uint8_t
{
	PETTM_None                                         = 0,
	PETTM_Full                                         = 1,
	PETTM_Partial                                      = 2,
	PETTM_END                                          = 3
};

// Enum Engine.ParticleModuleTypeDataBeam.EBeamMethod
enum class EBeamMethod : uint8_t
{
	PEBM_Distance                                      = 0,
	PEBM_EndPoints                                     = 1,
	PEBM_EndPoints_Interpolated                        = 2,
	PEBM_UserSet_EndPoints                             = 3,
	PEBM_UserSet_EndPoints_Interpolated                = 4,
	PEBM_END                                           = 5
};

// Enum Engine.ParticleModuleTypeDataBeam.EBeamEndPointMethod
enum class EBeamEndPointMethod : uint8_t
{
	PEBEPM_Calculated                                  = 0,
	PEBEPM_Distribution                                = 1,
	PEBEPM_Distribution_Constant                       = 2,
	PEBEPM_END                                         = 3
};

// Enum Engine.ParticleModuleTypeDataBeam2.EBeam2Method
enum class EBeam2Method : uint8_t
{
	PEB2M_Distance                                     = 0,
	PEB2M_Target                                       = 1,
	PEB2M_Branch                                       = 2,
	PEB2M_END                                          = 3
};

// Enum Engine.ParticleModuleTypeDataBeam2.EBeamTaperMethod
enum class EBeamTaperMethod : uint8_t
{
	PEBTM_None                                         = 0,
	PEBTM_Full                                         = 1,
	PEBTM_Partial                                      = 2,
	PEBTM_END                                          = 3
};

// Enum Engine.ParticleModuleTypeDataMesh.EMeshCameraFacingOptions
enum class EMeshCameraFacingOptions : uint8_t
{
	XAxisFacing_NoUp                                   = 0,
	XAxisFacing_ZUp                                    = 1,
	XAxisFacing_NegativeZUp                            = 2,
	XAxisFacing_YUp                                    = 3,
	XAxisFacing_NegativeYUp                            = 4,
	LockedAxis_ZAxisFacing                             = 5,
	LockedAxis_NegativeZAxisFacing                     = 6,
	LockedAxis_YAxisFacing                             = 7,
	LockedAxis_NegativeYAxisFacing                     = 8,
	VelocityAligned_ZAxisFacing                        = 9,
	VelocityAligned_NegativeZAxisFacing                = 10,
	VelocityAligned_YAxisFacing                        = 11,
	VelocityAligned_NegativeYAxisFacing                = 12,
	EMeshCameraFacingOptions_END                       = 13
};

// Enum Engine.ParticleModuleTypeDataMesh.EMeshCameraFacingUpAxis
enum class EMeshCameraFacingUpAxis : uint8_t
{
	CameraFacing_NoneUP                                = 0,
	CameraFacing_ZUp                                   = 1,
	CameraFacing_NegativeZUp                           = 2,
	CameraFacing_YUp                                   = 3,
	CameraFacing_NegativeYUp                           = 4,
	CameraFacing_END                                   = 5
};

// Enum Engine.ParticleModuleTypeDataMesh.EMeshScreenAlignment
enum class EMeshScreenAlignment : uint8_t
{
	PSMA_MeshFaceCameraWithRoll                        = 0,
	PSMA_MeshFaceCameraWithSpin                        = 1,
	PSMA_MeshFaceCameraWithLockedAxis                  = 2,
	PSMA_END                                           = 3
};

// Enum Engine.ParticleModuleTypeDataMeshPhysX.EPhysXMeshRotationMethod
enum class EPhysXMeshRotationMethod : uint8_t
{
	PMRM_Disabled                                      = 0,
	PMRM_Spherical                                     = 1,
	PMRM_Box                                           = 2,
	PMRM_LongBox                                       = 3,
	PMRM_FlatBox                                       = 4,
	PMRM_Velocity                                      = 5,
	PMRM_END                                           = 6
};

// Enum Engine.ParticleModuleTypeDataRibbon.ETrailsRenderAxisOption
enum class ETrailsRenderAxisOption : uint8_t
{
	Trails_CameraUp                                    = 0,
	Trails_SourceUp                                    = 1,
	Trails_WorldUp                                     = 2,
	Trails_SourceSideIsUp                              = 3,
	Trails_END                                         = 4
};

// Enum Engine.ParticleSystem.EParticleSystemOcclusionBoundsMethod
enum class EParticleSystemOcclusionBoundsMethod : uint8_t
{
	EPSOBM_None                                        = 0,
	EPSOBM_ParticleBounds                              = 1,
	EPSOBM_CustomBounds                                = 2,
	EPSOBM_END                                         = 3
};

// Enum Engine.ParticleSystem.EParticleSystemUpdateMode
enum class EParticleSystemUpdateMode : uint8_t
{
	EPSUM_RealTime                                     = 0,
	EPSUM_FixedTime                                    = 1,
	EPSUM_END                                          = 2
};

// Enum Engine.ProcBuildingRuleset.EProcBuildingAxis
enum class EProcBuildingAxis : uint8_t
{
	EPBAxis_X                                          = 0,
	EPBAxis_Z                                          = 1,
	EPBAxis_END                                        = 2
};

// Enum Engine.ProcBuilding.EScopeEdge
enum class EScopeEdge : uint8_t
{
	EPSA_Top                                           = 0,
	EPSA_Bottom                                        = 1,
	EPSA_Left                                          = 2,
	EPSA_Right                                         = 3,
	EPSA_None                                          = 4,
	EPSA_END                                           = 5
};

// Enum Engine.ProcBuilding.EBuildingStatsBrowserColumns
enum class EBuildingStatsBrowserColumns : uint8_t
{
	BSBC_Name                                          = 0,
	BSBC_Ruleset                                       = 1,
	BSBC_NumStaticMeshComps                            = 2,
	BSBC_NumInstancedStaticMeshComps                   = 3,
	BSBC_NumInstancedTris                              = 4,
	BSBC_LightmapMemBytes                              = 5,
	BSBC_ShadowmapMemBytes                             = 6,
	BSBC_LODDiffuseMemBytes                            = 7,
	BSBC_LODLightingMemBytes                           = 8,
	BSBC_END                                           = 9
};

// Enum Engine.ProcBuilding.EPBCornerType
enum class EPBCornerType : uint8_t
{
	EPBC_Default                                       = 0,
	EPBC_Chamfer                                       = 1,
	EPBC_Round                                         = 2,
	EPBC_END                                           = 3
};

// Enum Engine.PBRuleNodeEdgeAngle.EProcBuildingEdge
enum class EProcBuildingEdge : uint8_t
{
	EPBE_Top                                           = 0,
	EPBE_Bottom                                        = 1,
	EPBE_Left                                          = 2,
	EPBE_Right                                         = 3,
	EPBE_END                                           = 4
};

// Enum Engine.PhysicalMaterial.EPhysEffectType
enum class EPhysEffectType : uint8_t
{
	EPMET_Impact                                       = 0,
	EPMET_Slide                                        = 1,
	EPMET_END                                          = 2
};

// Enum Engine.PhysXParticleSystem.ESimulationMethod
enum class ESimulationMethod : uint8_t
{
	ESM_SPH                                            = 0,
	ESM_NO_PARTICLE_INTERACTION                        = 1,
	ESM_MIXED_MODE                                     = 2,
	ESM_END                                            = 3
};

// Enum Engine.PhysXParticleSystem.EPacketSizeMultiplier
enum class EPacketSizeMultiplier : uint8_t
{
	EPSM                                               = 0,
	EPSM01                                             = 1,
	EPSM02                                             = 2,
	EPSM03                                             = 3,
	EPSM04                                             = 4,
	EPSM05                                             = 5,
	EPSM_END                                           = 6
};

// Enum Engine.PitchTekSettings.EPitchTekTargetSize
enum class EPitchTekTargetSize : uint8_t
{
	PTTS                                               = 0,
	PTTS01                                             = 1,
	PTTS02                                             = 2,
	PTTS_END                                           = 3
};

// Enum Engine.PlatformAccountSettings.ECrossPlatformChatState
enum class ECrossPlatformChatState : uint8_t
{
	PCCS_Everybody                                     = 0,
	PCCS_InGameFriends                                 = 1,
	PCCS_Block                                         = 2,
	PCCS_END                                           = 3
};

// Enum Engine.PlatformBlockListStatus.EBlockListDownloadStatus
enum class EBlockListDownloadStatus : uint8_t
{
	EB_Pending                                         = 0,
	EB_Failure                                         = 1,
	EB_Success                                         = 2,
	EB_END                                             = 3
};

// Enum Engine.SceneCaptureComponent.ESceneCapturePostMethod
enum class ESceneCapturePostMethod : uint8_t
{
	SceneCapPost_None                                  = 0,
	SceneCapPost_Desat                                 = 1,
	SceneCapPost_Seamless                              = 2,
	SceneCapPost_END                                   = 3
};

// Enum Engine.SceneCaptureComponent.ESceneCaptureViewMode
enum class ESceneCaptureViewMode : uint8_t
{
	SceneCapView_Lit                                   = 0,
	SceneCapView_Unlit                                 = 1,
	SceneCapView_LitNoShadows                          = 2,
	SceneCapView_Wire                                  = 3,
	SceneCapView_END                                   = 4
};

// Enum Engine.RB_BodySetup.ESleepFamily
enum class ESleepFamily : uint8_t
{
	SF_Normal                                          = 0,
	SF_Sensitive                                       = 1,
	SF_END                                             = 2
};

// Enum Engine.RB_RadialForceActor.ERadialForceType
enum class ERadialForceType : uint8_t
{
	RFT_Force                                          = 0,
	RFT_Impulse                                        = 1,
	RFT_END                                            = 2
};

// Enum Engine.Route.ERouteDirection
enum class ERouteDirection : uint8_t
{
	ERD_Forward                                        = 0,
	ERD_Reverse                                        = 1,
	ERD_END                                            = 2
};

// Enum Engine.Route.ERouteFillAction
enum class ERouteFillAction : uint8_t
{
	RFA_Overwrite                                      = 0,
	RFA_Add                                            = 1,
	RFA_Remove                                         = 2,
	RFA_Clear                                          = 3,
	RFA_END                                            = 4
};

// Enum Engine.Route.ERouteType
enum class ERouteType : uint8_t
{
	ERT_Linear                                         = 0,
	ERT_Loop                                           = 1,
	ERT_Circle                                         = 2,
	ERT_END                                            = 3
};

// Enum Engine.SeqAct_ActorFactory.EPointSelection
enum class EPointSelection : uint8_t
{
	PS_Normal                                          = 0,
	PS_Random                                          = 1,
	PS_Reverse                                         = 2,
	PS_END                                             = 3
};

// Enum Engine.SeqAct_SetMesh.EMeshType
enum class EMeshType : uint8_t
{
	MeshType_StaticMesh                                = 0,
	MeshType_SkeletalMesh                              = 1,
	MeshType_END                                       = 2
};

// Enum Engine.WorldAttractor.EWorldAttractorFalloffType
enum class EWorldAttractorFalloffType : uint8_t
{
	FOFF_Constant                                      = 0,
	FOFF_Linear                                        = 1,
	FOFF_Exponent                                      = 2,
	FOFF_END                                           = 3
};

// Enum Engine.SeqEvent_ParticleEvent.EParticleEventOutputType
enum class EParticleEventOutputType : uint8_t
{
	ePARTICLEOUT_Spawn                                 = 0,
	ePARTICLEOUT_Death                                 = 1,
	ePARTICLEOUT_Collision                             = 2,
	ePARTICLEOUT_AttractorCollision                    = 3,
	ePARTICLEOUT_Kismet                                = 4,
	ePARTICLEOUT_END                                   = 5
};

// Enum Engine.SkelControlBase.EBoneControlSpace
enum class EBoneControlSpace : uint8_t
{
	BCS_WorldSpace                                     = 0,
	BCS_ActorSpace                                     = 1,
	BCS_ComponentSpace                                 = 2,
	BCS_ParentBoneSpace                                = 3,
	BCS_BoneSpace                                      = 4,
	BCS_OtherBoneSpace                                 = 5,
	BCS_BaseMeshSpace                                  = 6,
	BCS_END                                            = 7
};

// Enum Engine.SkelControlSpline.ESplineControlRotMode
enum class ESplineControlRotMode : uint8_t
{
	SCR_NoChange                                       = 0,
	SCR_AlongSpline                                    = 1,
	SCR_Interpolate                                    = 2,
	SCR_END                                            = 3
};

// Enum Engine.SkeletalMesh.SoftBodyBoneType
enum class ESoftBodyBoneType : uint8_t
{
	SOFTBODYBONE_Fixed                                 = 0,
	SOFTBODYBONE_BreakableAttachment                   = 1,
	SOFTBODYBONE_TwoWayAttachment                      = 2,
	SOFTBODYBONE_END                                   = 3
};

// Enum Engine.SkeletalMesh.ClothBoneType
enum class EClothBoneType : uint8_t
{
	CLOTHBONE_Fixed                                    = 0,
	CLOTHBONE_BreakableAttachment                      = 1,
	CLOTHBONE_TearLine                                 = 2,
	CLOTHBONE_END                                      = 3
};

// Enum Engine.SkeletalMesh.SkeletalMeshOptimizationNormalMode
enum class ESkeletalMeshOptimizationNormalMode : uint8_t
{
	SMONM_Recalculate                                  = 0,
	SMONM_RecalculateSoft                              = 1,
	SMONM_RecalculateHard                              = 2,
	SMONM_END                                          = 3
};

// Enum Engine.SkeletalMesh.SkeletalMeshOptimizationImportance
enum class ESkeletalMeshOptimizationImportance : uint8_t
{
	SMOI_Off                                           = 0,
	SMOI_Lowest                                        = 1,
	SMOI_Low                                           = 2,
	SMOI_Normal                                        = 3,
	SMOI_High                                          = 4,
	SMOI_Highest                                       = 5,
	SMOI_END                                           = 6
};

// Enum Engine.SkeletalMesh.SkeletalMeshOptimizationType
enum class ESkeletalMeshOptimizationType : uint8_t
{
	SMOT_NumOfTriangles                                = 0,
	SMOT_MaxDeviation                                  = 1,
	SMOT_END                                           = 2
};

// Enum Engine.SkeletalMesh.TriangleSortOption
enum class ETriangleSortOption : uint8_t
{
	TRISORT_None                                       = 0,
	TRISORT_CenterRadialDistance                       = 1,
	TRISORT_Random                                     = 2,
	TRISORT_MergeContiguous                            = 3,
	TRISORT_Custom                                     = 4,
	TRISORT_CustomLeftRight                            = 5,
	TRISORT_END                                        = 6
};

// Enum Engine.SkeletalMesh.BoneBreakOption
enum class EBoneBreakOption : uint8_t
{
	BONEBREAK_SoftPreferred                            = 0,
	BONEBREAK_AutoDetect                               = 1,
	BONEBREAK_RigidPreferred                           = 2,
	BONEBREAK_END                                      = 3
};

// Enum Engine.SkeletalMesh.TriangleSortAxis
enum class ETriangleSortAxis : uint8_t
{
	TSA_X_Axis                                         = 0,
	TSA_Y_Axis                                         = 1,
	TSA_Z_Axis                                         = 2,
	TSA_END                                            = 3
};

// Enum Engine.SkeletalMesh.ClothMovementScaleGen
enum class EClothMovementScaleGen : uint8_t
{
	ECMDM_DistToFixedVert                              = 0,
	ECMDM_VertexBoneWeight                             = 1,
	ECMDM_Empty                                        = 2,
	ECMDM_END                                          = 3
};

// Enum Engine.SoundNodeWave.EDecompressionType
enum class EDecompressionType : uint8_t
{
	DTYPE_Setup                                        = 0,
	DTYPE_Invalid                                      = 1,
	DTYPE_Preview                                      = 2,
	DTYPE_Native                                       = 3,
	DTYPE_RealTime                                     = 4,
	DTYPE_Procedural                                   = 5,
	DTYPE_Xenon                                        = 6,
	DTYPE_Dingo                                        = 7,
	DTYPE_END                                          = 8
};

// Enum Engine.SpeedTreeComponent.ESpeedTreeMeshType
enum class ESpeedTreeMeshType : uint8_t
{
	STMT_MinMinusOne                                   = 0,
	STMT_Branches1                                     = 1,
	STMT_Branches2                                     = 2,
	STMT_Fronds                                        = 3,
	STMT_LeafCards                                     = 4,
	STMT_LeafMeshes                                    = 5,
	STMT_Billboards                                    = 6,
	STMT_Max                                           = 7
};

// Enum Engine.TerrainMaterial.ETerrainMappingType
enum class ETerrainMappingType : uint8_t
{
	TMT_Auto                                           = 0,
	TMT_XY                                             = 1,
	TMT_XZ                                             = 2,
	TMT_YZ                                             = 3,
	TMT_END                                            = 4
};

// Enum Engine.TextureFlipBook.TextureFlipBookMethod
enum class ETextureFlipBookMethod : uint8_t
{
	TFBM_UL_ROW                                        = 0,
	TFBM_UL_COL                                        = 1,
	TFBM_UR_ROW                                        = 2,
	TFBM_UR_COL                                        = 3,
	TFBM_LL_ROW                                        = 4,
	TFBM_LL_COL                                        = 5,
	TFBM_LR_ROW                                        = 6,
	TFBM_LR_COL                                        = 7,
	TFBM_RANDOM                                        = 8,
	TFBM_END                                           = 9
};

// Enum Engine.TextureMovie.EMovieStreamSource
enum class EMovieStreamSource : uint8_t
{
	MovieStream_File                                   = 0,
	MovieStream_Memory                                 = 1,
	MovieStream_END                                    = 2
};

// Enum Engine.TwitterIntegrationBase.ETwitterRequestMethod
enum class ETwitterRequestMethod : uint8_t
{
	TRM_Get                                            = 0,
	TRM_Post                                           = 1,
	TRM_Delete                                         = 2,
	TRM_END                                            = 3
};

// Enum Engine.TwitterIntegrationBase.ETwitterIntegrationDelegate
enum class ETwitterIntegrationDelegate : uint8_t
{
	TID_AuthorizeComplete                              = 0,
	TID_TweetUIComplete                                = 1,
	TID_RequestComplete                                = 2,
	TID_END                                            = 3
};

// Enum Engine.UberPostProcessEffect.EPostProcessAAType
enum class EPostProcessAAType : uint8_t
{
	PostProcessAA_Off                                  = 0,
	PostProcessAA_FXAA0                                = 1,
	PostProcessAA_FXAA1                                = 2,
	PostProcessAA_FXAA2                                = 3,
	PostProcessAA_FXAA3                                = 4,
	PostProcessAA_FXAA4                                = 5,
	PostProcessAA_FXAA5                                = 6,
	PostProcessAA_MLAA                                 = 7,
	PostProcessAA_SMAA                                 = 8,
	PostProcessAA_END                                  = 9
};

// Enum Engine.UberPostProcessEffect.ETonemapperType
enum class ETonemapperType : uint8_t
{
	Tonemapper_Off                                     = 0,
	Tonemapper_Filmic                                  = 1,
	Tonemapper_Customizable                            = 2,
	Tonemapper_END                                     = 3
};

// Enum Engine.UIDataProvider_MenuItem.EMenuOptionType
enum class EMenuOptionType : uint8_t
{
	MENUOT_ComboReadOnly                               = 0,
	MENUOT_ComboNumeric                                = 1,
	MENUOT_CheckBox                                    = 2,
	MENUOT_Slider                                      = 3,
	MENUOT_Spinner                                     = 4,
	MENUOT_EditBox                                     = 5,
	MENUOT_CollectionCheckBox                          = 6,
	MENUOT_CollapsingList                              = 7,
	MENUOT_END                                         = 8
};

// Enum Engine.UIDataStore_OnlineStats.EStatsFetchType
enum class EStatsFetchType : uint8_t
{
	SFT_Player                                         = 0,
	SFT_CenteredOnPlayer                               = 1,
	SFT_Friends                                        = 2,
	SFT_TopRankings                                    = 3,
	SFT_END                                            = 4
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
