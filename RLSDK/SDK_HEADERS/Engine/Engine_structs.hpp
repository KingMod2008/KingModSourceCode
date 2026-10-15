/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: Engine\Engine_structs.hpp
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

// ScriptStruct Engine.Actor.AnimSlotDesc
// 0x000C
struct FAnimSlotDesc
{
	class FName                                        SlotName;                                      // 0x0000 (0x0008) [0x0000000000100000]               
	int32_t                                            NumChannels;                                   // 0x0008 (0x0004) [0x0000000000100000]               

	bool operator==(const FAnimSlotDesc& other) const { return memcmp(this, &other, sizeof(FAnimSlotDesc)) == 0; }
	bool operator!=(const FAnimSlotDesc& other) const { return !(*this == other); }
	bool operator<(const FAnimSlotDesc& other) const { return memcmp(this, &other, sizeof(FAnimSlotDesc)) < 0; }
};

// ScriptStruct Engine.Actor.RigidBodyState
// 0x0039
struct FRigidBodyState
{
	struct FVector                                     Position;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FQuat                                       Quaternion;                                    // 0x0010 (0x0010) [0x0000000000000000]               
	struct FVector                                     LinVel;                                        // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     AngVel;                                        // 0x002C (0x000C) [0x0000000000000000]               
	uint8_t                                            bNewData;                                      // 0x0038 (0x0001) [0x0000000000000000]               
	uint8_t                                            MinStructAlignment[0x7];                         // 0x0039 (0x0007) ADDED PADDING

	bool operator==(const FRigidBodyState& other) const { return memcmp(this, &other, sizeof(FRigidBodyState)) == 0; }
	bool operator!=(const FRigidBodyState& other) const { return !(*this == other); }
	bool operator<(const FRigidBodyState& other) const { return memcmp(this, &other, sizeof(FRigidBodyState)) < 0; }
};

// ScriptStruct Engine.Actor.RigidBodyContactInfo
// 0x0048
struct FRigidBodyContactInfo
{
	struct FVector                                     ContactPosition;                               // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     ContactNormal;                                 // 0x000C (0x000C) [0x0000000000000000]               
	float                                              ContactPenetration;                            // 0x0018 (0x0004) [0x0000000000000000]               
	struct FVector                                     ContactVelocity[2];                            // 0x001C (0x0018) [0x0000000000000000]               
	class UPhysicalMaterial*                           PhysMaterial[2];                               // 0x0038 (0x0010) [0x0000000000000000]               

	bool operator==(const FRigidBodyContactInfo& other) const { return memcmp(this, &other, sizeof(FRigidBodyContactInfo)) == 0; }
	bool operator!=(const FRigidBodyContactInfo& other) const { return !(*this == other); }
	bool operator<(const FRigidBodyContactInfo& other) const { return memcmp(this, &other, sizeof(FRigidBodyContactInfo)) < 0; }
};

// ScriptStruct Engine.Actor.CollisionImpactData
// 0x0028
struct FCollisionImpactData
{
	class TArray<struct FRigidBodyContactInfo>         ContactInfos;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FVector                                     TotalNormalForceVector;                        // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     TotalFrictionForceVector;                      // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FCollisionImpactData& other) const { return memcmp(this, &other, sizeof(FCollisionImpactData)) == 0; }
	bool operator!=(const FCollisionImpactData& other) const { return !(*this == other); }
	bool operator<(const FCollisionImpactData& other) const { return memcmp(this, &other, sizeof(FCollisionImpactData)) < 0; }
};

// ScriptStruct Engine.Actor.PhysEffectInfo
// 0x0018
struct FPhysEffectInfo
{
	float                                              Threshold;                                     // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ReFireDelay;                                   // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UParticleSystem*                             Effect;                                        // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USoundCue*                                   Sound;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPhysEffectInfo& other) const { return memcmp(this, &other, sizeof(FPhysEffectInfo)) == 0; }
	bool operator!=(const FPhysEffectInfo& other) const { return !(*this == other); }
	bool operator<(const FPhysEffectInfo& other) const { return memcmp(this, &other, sizeof(FPhysEffectInfo)) < 0; }
};

// ScriptStruct Engine.Actor.ActorReference
// 0x0018
struct FActorReference
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       Guid;                                          // 0x0008 (0x0010) [0x0000000000020003] (CPF_Edit | CPF_Const | CPF_EditConst)

	bool operator==(const FActorReference& other) const { return memcmp(this, &other, sizeof(FActorReference)) == 0; }
	bool operator!=(const FActorReference& other) const { return !(*this == other); }
	bool operator<(const FActorReference& other) const { return memcmp(this, &other, sizeof(FActorReference)) < 0; }
};

// ScriptStruct Engine.Actor.NavReference
// 0x0018
struct FNavReference
{
	class ANavigationPoint*                            Nav;                                           // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       Guid;                                          // 0x0008 (0x0010) [0x0000000000020003] (CPF_Edit | CPF_Const | CPF_EditConst)

	bool operator==(const FNavReference& other) const { return memcmp(this, &other, sizeof(FNavReference)) == 0; }
	bool operator!=(const FNavReference& other) const { return !(*this == other); }
	bool operator<(const FNavReference& other) const { return memcmp(this, &other, sizeof(FNavReference)) < 0; }
};

// ScriptStruct Engine.Actor.BasedPosition
// 0x0038
struct FBasedPosition
{
	class AActor*                                      Base;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Position;                                      // 0x0008 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     CachedBaseLocation;                            // 0x0014 (0x000C) [0x0000000000000000]               
	struct FRotator                                    CachedBaseRotation;                            // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     CachedTransPosition;                           // 0x002C (0x000C) [0x0000000000000000]               

	bool operator==(const FBasedPosition& other) const { return memcmp(this, &other, sizeof(FBasedPosition)) == 0; }
	bool operator!=(const FBasedPosition& other) const { return !(*this == other); }
	bool operator<(const FBasedPosition& other) const { return memcmp(this, &other, sizeof(FBasedPosition)) < 0; }
};

// ScriptStruct Engine.Actor.TraceHitInfo
// 0x0028
struct FTraceHitInfo
{
	class UMaterial*                                   Material;                                      // 0x0000 (0x0008) [0x0000000000100000]               
	class UPhysicalMaterial*                           PhysMaterial;                                  // 0x0008 (0x0008) [0x0000000000100000]               
	int32_t                                            Item;                                          // 0x0010 (0x0004) [0x0000000000100000]               
	int32_t                                            LevelIndex;                                    // 0x0014 (0x0004) [0x0000000000100000]               
	class FName                                        BoneName;                                      // 0x0018 (0x0008) [0x0000000000100000]               
	class UPrimitiveComponent*                         HitComponent;                                  // 0x0020 (0x0008) [0x0000000004180008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FTraceHitInfo& other) const { return memcmp(this, &other, sizeof(FTraceHitInfo)) == 0; }
	bool operator!=(const FTraceHitInfo& other) const { return !(*this == other); }
	bool operator<(const FTraceHitInfo& other) const { return memcmp(this, &other, sizeof(FTraceHitInfo)) < 0; }
};

// ScriptStruct Engine.Actor.ImpactInfo
// 0x0060
struct FImpactInfo
{
	class AActor*                                      HitActor;                                      // 0x0000 (0x0008) [0x0000000000100000]               
	struct FVector                                     HitLocation;                                   // 0x0008 (0x000C) [0x0000000000100000]               
	struct FVector                                     HitNormal;                                     // 0x0014 (0x000C) [0x0000000000100000]               
	struct FVector                                     RayDir;                                        // 0x0020 (0x000C) [0x0000000000100000]               
	struct FVector                                     StartTrace;                                    // 0x002C (0x000C) [0x0000000000100000]               
	struct FTraceHitInfo                               HitInfo;                                       // 0x0038 (0x0028) [0x0000000000180000] (CPF_Component)

	bool operator==(const FImpactInfo& other) const { return memcmp(this, &other, sizeof(FImpactInfo)) == 0; }
	bool operator!=(const FImpactInfo& other) const { return !(*this == other); }
	bool operator<(const FImpactInfo& other) const { return memcmp(this, &other, sizeof(FImpactInfo)) < 0; }
};

// ScriptStruct Engine.SequenceOp.SeqOpInputLink
// 0x003C
struct FSeqOpInputLink
{
	class FString                                      LinkDesc;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasImpulse : 1;                               // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            QueuedActivations;                             // 0x0014 (0x0004) [0x0000000000000000]               
	uint32_t                                           bDisabled : 1;                                 // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDisabledPIE : 1;                              // 0x0018 (0x0004) [0x0000000000000000] [0x00000002] 
	class USequenceOp*                                 LinkedOp;                                      // 0x0020 (0x0008) [0x0000000000000000]               
	int32_t                                            DrawY;                                         // 0x0028 (0x0004) [0x0000000000000000]               
	uint32_t                                           bHidden : 1;                                   // 0x002C (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              ActivateDelay;                                 // 0x0030 (0x0004) [0x0000000000000000]               
	uint32_t                                           bMoving : 1;                                   // 0x0034 (0x0004) [0x0000000800002000] [0x00000001] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bClampedMax : 1;                               // 0x0034 (0x0004) [0x0000000800000000] [0x00000002] (CPF_EditorOnly)
	uint32_t                                           bClampedMin : 1;                               // 0x0034 (0x0004) [0x0000000800000000] [0x100000004] (CPF_EditorOnly)
	int32_t                                            OverrideDelta;                                 // 0x0038 (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FSeqOpInputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpInputLink)) == 0; }
	bool operator!=(const FSeqOpInputLink& other) const { return !(*this == other); }
	bool operator<(const FSeqOpInputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpInputLink)) < 0; }
};

// ScriptStruct Engine.Actor.AnimSlotInfo
// 0x0018
struct FAnimSlotInfo
{
	class FName                                        SlotName;                                      // 0x0000 (0x0008) [0x0000000000100000]               
	class TArray<float>                                ChannelWeights;                                // 0x0008 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FAnimSlotInfo& other) const { return memcmp(this, &other, sizeof(FAnimSlotInfo)) == 0; }
	bool operator!=(const FAnimSlotInfo& other) const { return !(*this == other); }
	bool operator<(const FAnimSlotInfo& other) const { return memcmp(this, &other, sizeof(FAnimSlotInfo)) < 0; }
};

// ScriptStruct Engine.Actor.TimerData
// 0x0028
struct FTimerData
{
	uint32_t                                           bLoop : 1;                                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bPaused : 1;                                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bStateTimer : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	class FName                                        FuncName;                                      // 0x0004 (0x0008) [0x0000000000000000]               
	float                                              Rate;                                          // 0x000C (0x0004) [0x0000000000000000]               
	float                                              Count;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              TimerTimeDilation;                             // 0x0014 (0x0004) [0x0000000000000000]               
	class UObject*                                     TimerObj;                                      // 0x0018 (0x0008) [0x0000000000000000]               
	int32_t                                            StateGeneration;                               // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            SetFrame;                                      // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FTimerData& other) const { return memcmp(this, &other, sizeof(FTimerData)) == 0; }
	bool operator!=(const FTimerData& other) const { return !(*this == other); }
	bool operator<(const FTimerData& other) const { return memcmp(this, &other, sizeof(FTimerData)) < 0; }
};

// ScriptStruct Engine.PrimitiveComponent.RBCollisionChannelContainer
// 0x0004
struct FRBCollisionChannelContainer
{
	uint32_t                                           Default : 1;                                   // 0x0000 (0x0004) [0x0000000000000003] [0x00000001] (CPF_Edit | CPF_Const)
	uint32_t                                           Nothing : 1;                                   // 0x0000 (0x0004) [0x0000000000000002] [0x00000002] (CPF_Const)
	uint32_t                                           Pawn : 1;                                      // 0x0000 (0x0004) [0x0000000000000003] [0x00000004] (CPF_Edit | CPF_Const)
	uint32_t                                           Vehicle : 1;                                   // 0x0000 (0x0004) [0x0000000000000003] [0x00000008] (CPF_Edit | CPF_Const)
	uint32_t                                           Water : 1;                                     // 0x0000 (0x0004) [0x0000000000000003] [0x00000010] (CPF_Edit | CPF_Const)
	uint32_t                                           GameplayPhysics : 1;                           // 0x0000 (0x0004) [0x0000000000000003] [0x00000020] (CPF_Edit | CPF_Const)
	uint32_t                                           EffectPhysics : 1;                             // 0x0000 (0x0004) [0x0000000000000003] [0x00000040] (CPF_Edit | CPF_Const)
	uint32_t                                           Ball : 1;                                      // 0x0000 (0x0004) [0x0000000000000003] [0x00000080] (CPF_Edit | CPF_Const)
	uint32_t                                           VehicleBlocker : 1;                            // 0x0000 (0x0004) [0x0000000000000003] [0x00000100] (CPF_Edit | CPF_Const)
	uint32_t                                           BallBlocker : 1;                               // 0x0000 (0x0004) [0x0000000000000003] [0x00000200] (CPF_Edit | CPF_Const)
	uint32_t                                           Untitled4 : 1;                                 // 0x0000 (0x0004) [0x0000000000000003] [0x00000400] (CPF_Edit | CPF_Const)
	uint32_t                                           Cloth : 1;                                     // 0x0000 (0x0004) [0x0000000000000003] [0x00000800] (CPF_Edit | CPF_Const)
	uint32_t                                           FluidDrain : 1;                                // 0x0000 (0x0004) [0x0000000000000003] [0x00001000] (CPF_Edit | CPF_Const)
	uint32_t                                           SoftBody : 1;                                  // 0x0000 (0x0004) [0x0000000000000003] [0x00002000] (CPF_Edit | CPF_Const)
	uint32_t                                           FracturedMeshPart : 1;                         // 0x0000 (0x0004) [0x0000000000000003] [0x00004000] (CPF_Edit | CPF_Const)
	uint32_t                                           BlockingVolume : 1;                            // 0x0000 (0x0004) [0x0000000000000003] [0x00008000] (CPF_Edit | CPF_Const)
	uint32_t                                           DeadPawn : 1;                                  // 0x0000 (0x0004) [0x0000000000000003] [0x00010000] (CPF_Edit | CPF_Const)
	uint32_t                                           Clothing : 1;                                  // 0x0000 (0x0004) [0x0000000000000003] [0x00020000] (CPF_Edit | CPF_Const)
	uint32_t                                           ClothingCollision : 1;                         // 0x0000 (0x0004) [0x0000000000000003] [0x00040000] (CPF_Edit | CPF_Const)

	bool operator==(const FRBCollisionChannelContainer& other) const { return memcmp(this, &other, sizeof(FRBCollisionChannelContainer)) == 0; }
	bool operator!=(const FRBCollisionChannelContainer& other) const { return !(*this == other); }
	bool operator<(const FRBCollisionChannelContainer& other) const { return memcmp(this, &other, sizeof(FRBCollisionChannelContainer)) < 0; }
};

// ScriptStruct Engine.LightComponent.LightingChannelContainer
// 0x0004
struct FLightingChannelContainer
{
	uint32_t                                           bInitialized : 1;                              // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           BSP : 1;                                       // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           Static : 1;                                    // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           Dynamic : 1;                                   // 0x0000 (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           CompositeDynamic : 1;                          // 0x0000 (0x0004) [0x0000000000000001] [0x00000010] (CPF_Edit)
	uint32_t                                           Skybox : 1;                                    // 0x0000 (0x0004) [0x0000000000000001] [0x00000020] (CPF_Edit)
	uint32_t                                           Unnamed : 1;                                   // 0x0000 (0x0004) [0x0000000000000001] [0x00000040] (CPF_Edit)
	uint32_t                                           Unnamed01 : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000080] (CPF_Edit)
	uint32_t                                           Unnamed02 : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000100] (CPF_Edit)
	uint32_t                                           Unnamed03 : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000200] (CPF_Edit)
	uint32_t                                           Unnamed04 : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000400] (CPF_Edit)
	uint32_t                                           Unnamed05 : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000800] (CPF_Edit)
	uint32_t                                           Cinematic : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00001000] (CPF_Edit)
	uint32_t                                           Cinematic01 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00002000] (CPF_Edit)
	uint32_t                                           Cinematic02 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00004000] (CPF_Edit)
	uint32_t                                           Cinematic03 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00008000] (CPF_Edit)
	uint32_t                                           Cinematic04 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00010000] (CPF_Edit)
	uint32_t                                           Cinematic05 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00020000] (CPF_Edit)
	uint32_t                                           Cinematic06 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00040000] (CPF_Edit)
	uint32_t                                           Cinematic07 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00080000] (CPF_Edit)
	uint32_t                                           Cinematic08 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00100000] (CPF_Edit)
	uint32_t                                           Cinematic09 : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00200000] (CPF_Edit)
	uint32_t                                           Gameplay : 1;                                  // 0x0000 (0x0004) [0x0000000000000001] [0x00400000] (CPF_Edit)
	uint32_t                                           Gameplay01 : 1;                                // 0x0000 (0x0004) [0x0000000000000001] [0x00800000] (CPF_Edit)
	uint32_t                                           Gameplay02 : 1;                                // 0x0000 (0x0004) [0x0000000000000001] [0x01000000] (CPF_Edit)
	uint32_t                                           Gameplay03 : 1;                                // 0x0000 (0x0004) [0x0000000000000001] [0x02000000] (CPF_Edit)
	uint32_t                                           Crowd : 1;                                     // 0x0000 (0x0004) [0x0000000000000001] [0x04000000] (CPF_Edit)

	bool operator==(const FLightingChannelContainer& other) const { return memcmp(this, &other, sizeof(FLightingChannelContainer)) == 0; }
	bool operator!=(const FLightingChannelContainer& other) const { return !(*this == other); }
	bool operator<(const FLightingChannelContainer& other) const { return memcmp(this, &other, sizeof(FLightingChannelContainer)) < 0; }
};

// ScriptStruct Engine.PrimitiveComponent.MaterialViewRelevance
// 0x0004
struct FMaterialViewRelevance
{
	uint32_t                                           bOpaque : 1;                                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bTranslucent : 1;                              // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bDistortion : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bOneLayerDistortionRelevance : 1;              // 0x0000 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bLit : 1;                                      // 0x0000 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bUsesSceneColor : 1;                           // 0x0000 (0x0004) [0x0000000000000000] [0x00000020] 

	bool operator==(const FMaterialViewRelevance& other) const { return memcmp(this, &other, sizeof(FMaterialViewRelevance)) == 0; }
	bool operator!=(const FMaterialViewRelevance& other) const { return !(*this == other); }
	bool operator<(const FMaterialViewRelevance& other) const { return memcmp(this, &other, sizeof(FMaterialViewRelevance)) < 0; }
};

// ScriptStruct Engine.GroupComponent_ORS.ComponentTemplate
// 0x0020
struct FComponentTemplate
{
	struct FScriptDelegate                             Condition;                                     // 0x0000 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class UObject*                                     Object;                                        // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FComponentTemplate& other) const { return memcmp(this, &other, sizeof(FComponentTemplate)) == 0; }
	bool operator!=(const FComponentTemplate& other) const { return !(*this == other); }
	bool operator<(const FComponentTemplate& other) const { return memcmp(this, &other, sizeof(FComponentTemplate)) < 0; }
};

// ScriptStruct Engine.Controller.VisiblePortalInfo
// 0x0010
struct FVisiblePortalInfo
{
	class AActor*                                      Source;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	class AActor*                                      Destination;                                   // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FVisiblePortalInfo& other) const { return memcmp(this, &other, sizeof(FVisiblePortalInfo)) == 0; }
	bool operator!=(const FVisiblePortalInfo& other) const { return !(*this == other); }
	bool operator<(const FVisiblePortalInfo& other) const { return memcmp(this, &other, sizeof(FVisiblePortalInfo)) < 0; }
};

// ScriptStruct Engine.NavigationPoint.DebugNavCost
// 0x0014
struct FDebugNavCost
{
	class FString                                      Desc;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Cost;                                          // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FDebugNavCost& other) const { return memcmp(this, &other, sizeof(FDebugNavCost)) == 0; }
	bool operator!=(const FDebugNavCost& other) const { return !(*this == other); }
	bool operator<(const FDebugNavCost& other) const { return memcmp(this, &other, sizeof(FDebugNavCost)) < 0; }
};

// ScriptStruct Engine.NavigationPoint.NavigationOctreeObject
// 0x0039
struct FNavigationOctreeObject
{
	struct FBox                                        BoundingBox;                                   // 0x0000 (0x001C) [0x0000000000000000]               
	struct FVector                                     BoxCenter;                                     // 0x001C (0x000C) [0x0000000000000000]               
	struct FPointer                                    OctreeNode;                                    // 0x0028 (0x0008) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)
	class UObject*                                     Owner;                                         // 0x0030 (0x0008) [0x0000000000800002] (CPF_Const | CPF_NoExport)
	uint8_t                                            OwnerType;                                     // 0x0038 (0x0001) [0x0000000000800002] (CPF_Const | CPF_NoExport)

	bool operator==(const FNavigationOctreeObject& other) const { return memcmp(this, &other, sizeof(FNavigationOctreeObject)) == 0; }
	bool operator!=(const FNavigationOctreeObject& other) const { return !(*this == other); }
	bool operator<(const FNavigationOctreeObject& other) const { return memcmp(this, &other, sizeof(FNavigationOctreeObject)) < 0; }
};

// ScriptStruct Engine.NavigationPoint.CheckpointRecord
// 0x0004
struct ANavigationPoint_FCheckpointRecord
{
	uint32_t                                           bDisabled : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bBlocked : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const ANavigationPoint_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ANavigationPoint_FCheckpointRecord)) == 0; }
	bool operator!=(const ANavigationPoint_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ANavigationPoint_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ANavigationPoint_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.KMeshProps.KSphereElem
// 0x0048
struct FKSphereElem
{
	struct FMatrix                                     TM;                                            // 0x0000 (0x0040) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              Radius;                                        // 0x0040 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bNoRBCollision : 1;                            // 0x0044 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bPerPolyShape : 1;                             // 0x0044 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint8_t                                            MinStructAlignment[0x8];                         // 0x0048 (0x0008) ADDED PADDING

	bool operator==(const FKSphereElem& other) const { return memcmp(this, &other, sizeof(FKSphereElem)) == 0; }
	bool operator!=(const FKSphereElem& other) const { return !(*this == other); }
	bool operator<(const FKSphereElem& other) const { return memcmp(this, &other, sizeof(FKSphereElem)) < 0; }
};

// ScriptStruct Engine.KMeshProps.KBoxElem
// 0x0050
struct FKBoxElem
{
	struct FMatrix                                     TM;                                            // 0x0000 (0x0040) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              X;                                             // 0x0040 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              Y;                                             // 0x0044 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              Z;                                             // 0x0048 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bNoRBCollision : 1;                            // 0x004C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bPerPolyShape : 1;                             // 0x004C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)

	bool operator==(const FKBoxElem& other) const { return memcmp(this, &other, sizeof(FKBoxElem)) == 0; }
	bool operator!=(const FKBoxElem& other) const { return !(*this == other); }
	bool operator<(const FKBoxElem& other) const { return memcmp(this, &other, sizeof(FKBoxElem)) < 0; }
};

// ScriptStruct Engine.KMeshProps.KSphylElem
// 0x004C
struct FKSphylElem
{
	struct FMatrix                                     TM;                                            // 0x0000 (0x0040) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              Radius;                                        // 0x0040 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              Length;                                        // 0x0044 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bNoRBCollision : 1;                            // 0x0048 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bPerPolyShape : 1;                             // 0x0048 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint8_t                                            MinStructAlignment[0x4];                         // 0x004C (0x0004) ADDED PADDING

	bool operator==(const FKSphylElem& other) const { return memcmp(this, &other, sizeof(FKSphylElem)) == 0; }
	bool operator!=(const FKSphylElem& other) const { return !(*this == other); }
	bool operator<(const FKSphylElem& other) const { return memcmp(this, &other, sizeof(FKSphylElem)) < 0; }
};

// ScriptStruct Engine.KMeshProps.KConvexElem
// 0x007C
struct FKConvexElem
{
	class TArray<struct FVector>                       VertexData;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FPlane>                        PermutedVertexData;                            // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              FaceTriData;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FVector>                       EdgeDirections;                                // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FVector>                       FaceNormalDirections;                          // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FPlane>                        FacePlaneData;                                 // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FBox                                        ElemBox;                                       // 0x0060 (0x001C) [0x0000000000000000]               

	bool operator==(const FKConvexElem& other) const { return memcmp(this, &other, sizeof(FKConvexElem)) == 0; }
	bool operator!=(const FKConvexElem& other) const { return !(*this == other); }
	bool operator<(const FKConvexElem& other) const { return memcmp(this, &other, sizeof(FKConvexElem)) < 0; }
};

// ScriptStruct Engine.KMeshProps.KAggregateGeom
// 0x004C
struct FKAggregateGeom
{
	class TArray<struct FKSphereElem>                  SphereElems;                                   // 0x0000 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class TArray<struct FKBoxElem>                     BoxElems;                                      // 0x0010 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class TArray<struct FKSphylElem>                   SphylElems;                                    // 0x0020 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class TArray<struct FKConvexElem>                  ConvexElems;                                   // 0x0030 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	struct FPointer                                    RenderInfo;                                    // 0x0040 (0x0008) [0x0000000401001000] (CPF_Native | CPF_NonTransactional)
	uint32_t                                           bSkipCloseAndParallelChecks : 1;               // 0x0048 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bSimpleCollisionPlane : 1;                     // 0x0048 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)

	bool operator==(const FKAggregateGeom& other) const { return memcmp(this, &other, sizeof(FKAggregateGeom)) == 0; }
	bool operator!=(const FKAggregateGeom& other) const { return !(*this == other); }
	bool operator<(const FKAggregateGeom& other) const { return memcmp(this, &other, sizeof(FKAggregateGeom)) < 0; }
};

// ScriptStruct Engine.Pylon.PolyReference
// 0x0028
struct FPolyReference
{
	struct FActorReference                             OwningPylon;                                   // 0x0000 (0x0018) [0x0000000000000000]               
	int32_t                                            PolyId;                                        // 0x0018 (0x0004) [0x0000000000000000]               
	struct FPointer                                    CachedPoly;                                    // 0x0020 (0x0008) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FPolyReference& other) const { return memcmp(this, &other, sizeof(FPolyReference)) == 0; }
	bool operator!=(const FPolyReference& other) const { return !(*this == other); }
	bool operator<(const FPolyReference& other) const { return memcmp(this, &other, sizeof(FPolyReference)) < 0; }
};

// ScriptStruct Engine.Scout.PathSizeInfo
// 0x0015
struct FPathSizeInfo
{
	class FName                                        Desc;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Radius;                                        // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              Height;                                        // 0x000C (0x0004) [0x0000000000000000]               
	float                                              CrouchHeight;                                  // 0x0010 (0x0004) [0x0000000000000000]               
	uint8_t                                            PathColor;                                     // 0x0014 (0x0001) [0x0000000000000000]               

	bool operator==(const FPathSizeInfo& other) const { return memcmp(this, &other, sizeof(FPathSizeInfo)) == 0; }
	bool operator!=(const FPathSizeInfo& other) const { return !(*this == other); }
	bool operator<(const FPathSizeInfo& other) const { return memcmp(this, &other, sizeof(FPathSizeInfo)) < 0; }
};

// ScriptStruct Engine.AkBank.BankLoadState
// 0x000C
struct FBankLoadState
{
	EBankLoadStatus                                    Status;                                        // 0x0000 (0x0001) [0x0000000000000000]               
	float                                              AsyncLoadBegin;                                // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              AsyncLoadTimeout;                              // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FBankLoadState& other) const { return memcmp(this, &other, sizeof(FBankLoadState)) == 0; }
	bool operator!=(const FBankLoadState& other) const { return !(*this == other); }
	bool operator<(const FBankLoadState& other) const { return memcmp(this, &other, sizeof(FBankLoadState)) < 0; }
};

// ScriptStruct Engine.BrushComponent.KCachedConvexData_Mirror
// 0x0010
struct FKCachedConvexData_Mirror
{
	class TArray<int32_t>                              CachedConvexElements;                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FKCachedConvexData_Mirror& other) const { return memcmp(this, &other, sizeof(FKCachedConvexData_Mirror)) == 0; }
	bool operator!=(const FKCachedConvexData_Mirror& other) const { return !(*this == other); }
	bool operator<(const FKCachedConvexData_Mirror& other) const { return memcmp(this, &other, sizeof(FKCachedConvexData_Mirror)) < 0; }
};

// ScriptStruct Engine.Brush.GeomSelection
// 0x000C
struct FGeomSelection
{
	int32_t                                            Type;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Index;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            SelectionIndex;                                // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FGeomSelection& other) const { return memcmp(this, &other, sizeof(FGeomSelection)) == 0; }
	bool operator!=(const FGeomSelection& other) const { return !(*this == other); }
	bool operator<(const FGeomSelection& other) const { return memcmp(this, &other, sizeof(FGeomSelection)) < 0; }
};

// ScriptStruct Engine.ReverbVolume.InteriorSettings
// 0x0024
struct FInteriorSettings
{
	uint32_t                                           bIsWorldInfo : 1;                              // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              ExteriorVolume;                                // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ExteriorTime;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ExteriorLPF;                                   // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ExteriorLPFTime;                               // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              InteriorVolume;                                // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              InteriorTime;                                  // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              InteriorLPF;                                   // 0x001C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              InteriorLPFTime;                               // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInteriorSettings& other) const { return memcmp(this, &other, sizeof(FInteriorSettings)) == 0; }
	bool operator!=(const FInteriorSettings& other) const { return !(*this == other); }
	bool operator<(const FInteriorSettings& other) const { return memcmp(this, &other, sizeof(FInteriorSettings)) < 0; }
};

// ScriptStruct Engine.ReverbVolume.ReverbSettings
// 0x0010
struct FReverbSettings
{
	uint32_t                                           bApplyReverb : 1;                              // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	EReverbPreset                                      ReverbType;                                    // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              Volume;                                        // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeTime;                                      // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FReverbSettings& other) const { return memcmp(this, &other, sizeof(FReverbSettings)) == 0; }
	bool operator!=(const FReverbSettings& other) const { return !(*this == other); }
	bool operator<(const FReverbSettings& other) const { return memcmp(this, &other, sizeof(FReverbSettings)) < 0; }
};

// ScriptStruct Engine.AudioComponent.AudioComponentParam
// 0x0018
struct FAudioComponentParam
{
	class FName                                        ParamName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              FloatParam;                                    // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class USoundNodeWave*                              WaveParam;                                     // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAudioComponentParam& other) const { return memcmp(this, &other, sizeof(FAudioComponentParam)) == 0; }
	bool operator!=(const FAudioComponentParam& other) const { return !(*this == other); }
	bool operator<(const FAudioComponentParam& other) const { return memcmp(this, &other, sizeof(FAudioComponentParam)) < 0; }
};

// ScriptStruct Engine.EngineTypes.SubtitleCue
// 0x0014
struct FSubtitleCue
{
	class FString                                      Text;                                          // 0x0000 (0x0010) [0x0000000000408003] (CPF_Edit | CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	float                                              Time;                                          // 0x0010 (0x0004) [0x0000000000008003] (CPF_Edit | CPF_Const | CPF_Localized)

	bool operator==(const FSubtitleCue& other) const { return memcmp(this, &other, sizeof(FSubtitleCue)) == 0; }
	bool operator!=(const FSubtitleCue& other) const { return !(*this == other); }
	bool operator<(const FSubtitleCue& other) const { return memcmp(this, &other, sizeof(FSubtitleCue)) < 0; }
};

// ScriptStruct Engine.AudioDevice.Listener
// 0x0044
struct FListener
{
	class APortalVolume*                               PortalVolume;                                  // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     Up;                                            // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     Right;                                         // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     Front;                                         // 0x002C (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0038 (0x000C) [0x0000000000000000]               

	bool operator==(const FListener& other) const { return memcmp(this, &other, sizeof(FListener)) == 0; }
	bool operator!=(const FListener& other) const { return !(*this == other); }
	bool operator<(const FListener& other) const { return memcmp(this, &other, sizeof(FListener)) < 0; }
};

// ScriptStruct Engine.AudioDevice.AudioClassInfo
// 0x0010
struct FAudioClassInfo
{
	int32_t                                            NumResident;                                   // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            SizeResident;                                  // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            NumRealTime;                                   // 0x0008 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            SizeRealTime;                                  // 0x000C (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAudioClassInfo& other) const { return memcmp(this, &other, sizeof(FAudioClassInfo)) == 0; }
	bool operator!=(const FAudioClassInfo& other) const { return !(*this == other); }
	bool operator<(const FAudioClassInfo& other) const { return memcmp(this, &other, sizeof(FAudioClassInfo)) < 0; }
};

// ScriptStruct Engine.SoundCue.SoundNodeEditorData
// 0x0008
struct FSoundNodeEditorData
{
	int32_t                                            NodePosX;                                      // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            NodePosY;                                      // 0x0004 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FSoundNodeEditorData& other) const { return memcmp(this, &other, sizeof(FSoundNodeEditorData)) == 0; }
	bool operator!=(const FSoundNodeEditorData& other) const { return !(*this == other); }
	bool operator<(const FSoundNodeEditorData& other) const { return memcmp(this, &other, sizeof(FSoundNodeEditorData)) < 0; }
};

// ScriptStruct Engine.SoundNodeAmbient.AmbientSoundSlot
// 0x0014
struct FAmbientSoundSlot
{
	class USoundNodeWave*                              Wave;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              PitchScale;                                    // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VolumeScale;                                   // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Weight;                                        // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAmbientSoundSlot& other) const { return memcmp(this, &other, sizeof(FAmbientSoundSlot)) == 0; }
	bool operator!=(const FAmbientSoundSlot& other) const { return !(*this == other); }
	bool operator<(const FAmbientSoundSlot& other) const { return memcmp(this, &other, sizeof(FAmbientSoundSlot)) < 0; }
};

// ScriptStruct Engine.AmbientSoundSimpleToggleable.CheckpointRecord
// 0x0004
struct AAmbientSoundSimpleToggleable_FCheckpointRecord
{
	uint32_t                                           bCurrentlyPlaying : 1;                         // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const AAmbientSoundSimpleToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AAmbientSoundSimpleToggleable_FCheckpointRecord)) == 0; }
	bool operator!=(const AAmbientSoundSimpleToggleable_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const AAmbientSoundSimpleToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AAmbientSoundSimpleToggleable_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.SplineAudioComponent.InterpPointOnSpline
// 0x0014
struct FInterpPointOnSpline
{
	struct FVector                                     Position;                                      // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              InVal;                                         // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Length;                                        // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpPointOnSpline& other) const { return memcmp(this, &other, sizeof(FInterpPointOnSpline)) == 0; }
	bool operator!=(const FInterpPointOnSpline& other) const { return !(*this == other); }
	bool operator<(const FInterpPointOnSpline& other) const { return memcmp(this, &other, sizeof(FInterpPointOnSpline)) < 0; }
};

// ScriptStruct Engine.SimpleSplineAudioComponent.SplineSoundSlot
// 0x0038
struct FSplineSoundSlot
{
	class USoundNodeWave*                              Wave;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              PitchScale;                                    // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VolumeScale;                                   // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            StartPoint;                                    // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            EndPoint;                                      // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Weight;                                        // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FDouble                                     LastUpdateTime;                                // 0x0020 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              SourceInteriorVolume;                          // 0x0028 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              SourceInteriorLPF;                             // 0x002C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              CurrentInteriorVolume;                         // 0x0030 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              CurrentInteriorLPF;                            // 0x0034 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FSplineSoundSlot& other) const { return memcmp(this, &other, sizeof(FSplineSoundSlot)) == 0; }
	bool operator!=(const FSplineSoundSlot& other) const { return !(*this == other); }
	bool operator<(const FSplineSoundSlot& other) const { return memcmp(this, &other, sizeof(FSplineSoundSlot)) < 0; }
};

// ScriptStruct Engine.MultiCueSplineAudioComponent.MultiCueSplineSoundSlot
// 0x0034
struct FMultiCueSplineSoundSlot
{
	class USoundCue*                                   SoundCue;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              PitchScale;                                    // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VolumeScale;                                   // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            StartPoint;                                    // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            EndPoint;                                      // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FDouble                                     LastUpdateTime;                                // 0x0018 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              SourceInteriorVolume;                          // 0x0020 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              SourceInteriorLPF;                             // 0x0024 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              CurrentInteriorVolume;                         // 0x0028 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	float                                              CurrentInteriorLPF;                            // 0x002C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	uint32_t                                           bPlaying : 1;                                  // 0x0030 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FMultiCueSplineSoundSlot& other) const { return memcmp(this, &other, sizeof(FMultiCueSplineSoundSlot)) == 0; }
	bool operator!=(const FMultiCueSplineSoundSlot& other) const { return !(*this == other); }
	bool operator<(const FMultiCueSplineSoundSlot& other) const { return memcmp(this, &other, sizeof(FMultiCueSplineSoundSlot)) < 0; }
};

// ScriptStruct Engine.PlatformInterfaceBase.DelegateArray
// 0x0010
struct FDelegateArray
{
	class TArray<struct FScriptDelegate>               Delegates;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDelegateArray& other) const { return memcmp(this, &other, sizeof(FDelegateArray)) == 0; }
	bool operator!=(const FDelegateArray& other) const { return !(*this == other); }
	bool operator<(const FDelegateArray& other) const { return memcmp(this, &other, sizeof(FDelegateArray)) < 0; }
};

// ScriptStruct Engine.PlatformInterfaceBase.PlatformInterfaceData
// 0x0040
struct FPlatformInterfaceData
{
	class FName                                        DataName;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	EPlatformInterfaceDataType                         Type;                                          // 0x0008 (0x0001) [0x0000000000000000]               
	int32_t                                            IntValue;                                      // 0x000C (0x0004) [0x0000000000000000]               
	float                                              FloatValue;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	class FString                                      StringValue;                                   // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      StringValue2;                                  // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UObject*                                     ObjectValue;                                   // 0x0038 (0x0008) [0x0000000000000000]               

	bool operator==(const FPlatformInterfaceData& other) const { return memcmp(this, &other, sizeof(FPlatformInterfaceData)) == 0; }
	bool operator!=(const FPlatformInterfaceData& other) const { return !(*this == other); }
	bool operator<(const FPlatformInterfaceData& other) const { return memcmp(this, &other, sizeof(FPlatformInterfaceData)) < 0; }
};

// ScriptStruct Engine.PlatformInterfaceBase.PlatformInterfaceDelegateResult
// 0x0048
struct FPlatformInterfaceDelegateResult
{
	uint32_t                                           bSuccessful : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FPlatformInterfaceData                      Data;                                          // 0x0008 (0x0040) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPlatformInterfaceDelegateResult& other) const { return memcmp(this, &other, sizeof(FPlatformInterfaceDelegateResult)) == 0; }
	bool operator!=(const FPlatformInterfaceDelegateResult& other) const { return !(*this == other); }
	bool operator<(const FPlatformInterfaceDelegateResult& other) const { return memcmp(this, &other, sizeof(FPlatformInterfaceDelegateResult)) < 0; }
};

// ScriptStruct Engine.AnalyticEventsBase.EventStringParam
// 0x0020
struct FEventStringParam
{
	class FString                                      ParamName;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ParamValue;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FEventStringParam& other) const { return memcmp(this, &other, sizeof(FEventStringParam)) == 0; }
	bool operator!=(const FEventStringParam& other) const { return !(*this == other); }
	bool operator<(const FEventStringParam& other) const { return memcmp(this, &other, sizeof(FEventStringParam)) < 0; }
};

// ScriptStruct Engine.AnimSequence.CompressedTrack
// 0x0038
struct FCompressedTrack
{
	class TArray<uint8_t>                              ByteStream;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<float>                                Times;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              Mins[3];                                       // 0x0020 (0x000C) [0x0000000000000000]               
	float                                              Ranges[3];                                     // 0x002C (0x000C) [0x0000000000000000]               

	bool operator==(const FCompressedTrack& other) const { return memcmp(this, &other, sizeof(FCompressedTrack)) == 0; }
	bool operator!=(const FCompressedTrack& other) const { return !(*this == other); }
	bool operator<(const FCompressedTrack& other) const { return memcmp(this, &other, sizeof(FCompressedTrack)) < 0; }
};

// ScriptStruct Engine.AnimSequence.CurveTrack
// 0x0018
struct FCurveTrack
{
	class FName                                        CurveName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<float>                                CurveWeights;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCurveTrack& other) const { return memcmp(this, &other, sizeof(FCurveTrack)) == 0; }
	bool operator!=(const FCurveTrack& other) const { return !(*this == other); }
	bool operator<(const FCurveTrack& other) const { return memcmp(this, &other, sizeof(FCurveTrack)) < 0; }
};

// ScriptStruct Engine.AnimSequence.RotationTrack
// 0x0020
struct FRotationTrack
{
	class TArray<struct FQuat>                         RotKeys;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<float>                                Times;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRotationTrack& other) const { return memcmp(this, &other, sizeof(FRotationTrack)) == 0; }
	bool operator!=(const FRotationTrack& other) const { return !(*this == other); }
	bool operator<(const FRotationTrack& other) const { return memcmp(this, &other, sizeof(FRotationTrack)) < 0; }
};

// ScriptStruct Engine.AnimSequence.TranslationTrack
// 0x0020
struct FTranslationTrack
{
	class TArray<struct FVector>                       PosKeys;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<float>                                Times;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTranslationTrack& other) const { return memcmp(this, &other, sizeof(FTranslationTrack)) == 0; }
	bool operator!=(const FTranslationTrack& other) const { return !(*this == other); }
	bool operator<(const FTranslationTrack& other) const { return memcmp(this, &other, sizeof(FTranslationTrack)) < 0; }
};

// ScriptStruct Engine.AnimSequence.TimeModifier
// 0x0008
struct FTimeModifier
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              TargetStrength;                                // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTimeModifier& other) const { return memcmp(this, &other, sizeof(FTimeModifier)) == 0; }
	bool operator!=(const FTimeModifier& other) const { return !(*this == other); }
	bool operator<(const FTimeModifier& other) const { return memcmp(this, &other, sizeof(FTimeModifier)) < 0; }
};

// ScriptStruct Engine.AnimSequence.SkelControlModifier
// 0x0018
struct FSkelControlModifier
{
	class FName                                        SkelControlName;                               // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FTimeModifier>                 Modifiers;                                     // 0x0008 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)

	bool operator==(const FSkelControlModifier& other) const { return memcmp(this, &other, sizeof(FSkelControlModifier)) == 0; }
	bool operator!=(const FSkelControlModifier& other) const { return !(*this == other); }
	bool operator<(const FSkelControlModifier& other) const { return memcmp(this, &other, sizeof(FSkelControlModifier)) < 0; }
};

// ScriptStruct Engine.AnimSequence.AnimNotifyEvent
// 0x001C
struct FAnimNotifyEvent
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UAnimNotify*                                 Notify;                                        // 0x0008 (0x0008) [0x0000000004400009] (CPF_Edit | CPF_ExportObject | CPF_NeedCtorLink | CPF_EditInline)
	class FName                                        Comment;                                       // 0x0010 (0x0008) [0x0000000800000001] (CPF_Edit | CPF_EditorOnly)
	float                                              Duration;                                      // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAnimNotifyEvent& other) const { return memcmp(this, &other, sizeof(FAnimNotifyEvent)) == 0; }
	bool operator!=(const FAnimNotifyEvent& other) const { return !(*this == other); }
	bool operator<(const FAnimNotifyEvent& other) const { return memcmp(this, &other, sizeof(FAnimNotifyEvent)) < 0; }
};

// ScriptStruct Engine.AnimSequence.RawAnimSequenceTrack
// 0x0020
struct FRawAnimSequenceTrack
{
	class TArray<struct FVector>                       PosKeys;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FQuat>                         RotKeys;                                       // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRawAnimSequenceTrack& other) const { return memcmp(this, &other, sizeof(FRawAnimSequenceTrack)) == 0; }
	bool operator!=(const FRawAnimSequenceTrack& other) const { return !(*this == other); }
	bool operator<(const FRawAnimSequenceTrack& other) const { return memcmp(this, &other, sizeof(FRawAnimSequenceTrack)) < 0; }
};

// ScriptStruct Engine.AnimNode.CurveKey
// 0x000C
struct FCurveKey
{
	class FName                                        CurveName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Weight;                                        // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FCurveKey& other) const { return memcmp(this, &other, sizeof(FCurveKey)) == 0; }
	bool operator!=(const FCurveKey& other) const { return !(*this == other); }
	bool operator<(const FCurveKey& other) const { return memcmp(this, &other, sizeof(FCurveKey)) < 0; }
};

// ScriptStruct Engine.AnimNodeBlendBase.AnimBlendChild
// 0x0020
struct FAnimBlendChild
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UAnimNode*                                   Anim;                                          // 0x0008 (0x0008) [0x0000000004400008] (CPF_ExportObject | CPF_NeedCtorLink | CPF_EditInline)
	float                                              Weight;                                        // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              BlendWeight;                                   // 0x0014 (0x0004) [0x0000000000002002] (CPF_Const | CPF_Transient)
	uint32_t                                           bMirrorSkeleton : 1;                           // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsAdditive : 1;                               // 0x0018 (0x0004) [0x0000000000000000] [0x100000002] 
	int32_t                                            DrawY;                                         // 0x001C (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FAnimBlendChild& other) const { return memcmp(this, &other, sizeof(FAnimBlendChild)) == 0; }
	bool operator!=(const FAnimBlendChild& other) const { return !(*this == other); }
	bool operator<(const FAnimBlendChild& other) const { return memcmp(this, &other, sizeof(FAnimBlendChild)) < 0; }
};

// ScriptStruct Engine.AnimNode_MultiBlendPerBone.WeightNodeRule
// 0x0020
struct FWeightNodeRule
{
	class FName                                        NodeName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UAnimNodeBlendBase*                          CachedNode;                                    // 0x0008 (0x0008) [0x0000000000000000]               
	class UAnimNodeSlot*                               CachedSlotNode;                                // 0x0010 (0x0008) [0x0000000000000000]               
	EWeightCheck                                       WeightCheck;                                   // 0x0018 (0x0001) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ChildIndex;                                    // 0x001C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWeightNodeRule& other) const { return memcmp(this, &other, sizeof(FWeightNodeRule)) == 0; }
	bool operator!=(const FWeightNodeRule& other) const { return !(*this == other); }
	bool operator<(const FWeightNodeRule& other) const { return memcmp(this, &other, sizeof(FWeightNodeRule)) < 0; }
};

// ScriptStruct Engine.AnimNode_MultiBlendPerBone.WeightRule
// 0x0040
struct FWeightRule
{
	struct FWeightNodeRule                             FirstNode;                                     // 0x0000 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FWeightNodeRule                             SecondNode;                                    // 0x0020 (0x0020) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWeightRule& other) const { return memcmp(this, &other, sizeof(FWeightRule)) == 0; }
	bool operator!=(const FWeightRule& other) const { return !(*this == other); }
	bool operator<(const FWeightRule& other) const { return memcmp(this, &other, sizeof(FWeightRule)) < 0; }
};

// ScriptStruct Engine.AnimNode_MultiBlendPerBone.BranchInfo
// 0x000C
struct FBranchInfo
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              PerBoneWeightIncrease;                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBranchInfo& other) const { return memcmp(this, &other, sizeof(FBranchInfo)) == 0; }
	bool operator!=(const FBranchInfo& other) const { return !(*this == other); }
	bool operator<(const FBranchInfo& other) const { return memcmp(this, &other, sizeof(FBranchInfo)) < 0; }
};

// ScriptStruct Engine.AnimNode_MultiBlendPerBone.PerBoneMaskInfo
// 0x0054
struct FPerBoneMaskInfo
{
	class TArray<struct FBranchInfo>                   BranchList;                                    // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	float                                              DesiredWeight;                                 // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendTimeToGo;                                 // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FWeightRule>                   WeightRuleList;                                // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	uint32_t                                           bWeightBasedOnNodeRules : 1;                   // 0x0028 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bDisableForNonLocalHumanPlayers : 1;           // 0x0028 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bPendingBlend : 1;                             // 0x0028 (0x0004) [0x0000000000002000] [0x00000004] (CPF_Transient)
	class TArray<float>                                PerBoneWeights;                                // 0x0030 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<uint8_t>                              TransformReqBone;                              // 0x0040 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	int32_t                                            TransformReqBoneIndex;                         // 0x0050 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FPerBoneMaskInfo& other) const { return memcmp(this, &other, sizeof(FPerBoneMaskInfo)) == 0; }
	bool operator!=(const FPerBoneMaskInfo& other) const { return !(*this == other); }
	bool operator<(const FPerBoneMaskInfo& other) const { return memcmp(this, &other, sizeof(FPerBoneMaskInfo)) < 0; }
};

// ScriptStruct Engine.AnimNodeAimOffset.AimTransform
// 0x001C
struct FAimTransform
{
	struct FQuat                                       Quaternion;                                    // 0x0000 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Translation;                                   // 0x0010 (0x000C) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            MinStructAlignment[0x4];                         // 0x001C (0x0004) ADDED PADDING

	bool operator==(const FAimTransform& other) const { return memcmp(this, &other, sizeof(FAimTransform)) == 0; }
	bool operator!=(const FAimTransform& other) const { return !(*this == other); }
	bool operator<(const FAimTransform& other) const { return memcmp(this, &other, sizeof(FAimTransform)) < 0; }
};

// ScriptStruct Engine.AnimNodeAimOffset.AimComponent
// 0x0130
struct FAimComponent
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            UnknownData00[0x8];                              // 0x0008 (0x0008) MISSED OFFSET
	struct FAimTransform                               LU;                                            // 0x0010 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               LC;                                            // 0x0030 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               LD;                                            // 0x0050 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               CU;                                            // 0x0070 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               CC;                                            // 0x0090 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               CD;                                            // 0x00B0 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               RU;                                            // 0x00D0 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               RC;                                            // 0x00F0 (0x0020) [0x0000000000000001] (CPF_Edit)    
	struct FAimTransform                               RD;                                            // 0x0110 (0x0020) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAimComponent& other) const { return memcmp(this, &other, sizeof(FAimComponent)) == 0; }
	bool operator!=(const FAimComponent& other) const { return !(*this == other); }
	bool operator<(const FAimComponent& other) const { return memcmp(this, &other, sizeof(FAimComponent)) < 0; }
};

// ScriptStruct Engine.AnimNodeAimOffset.AimOffsetProfile
// 0x0070
struct FAimOffsetProfile
{
	class FName                                        ProfileName;                                   // 0x0000 (0x0008) [0x0000000000020003] (CPF_Edit | CPF_Const | CPF_EditConst)
	struct FVector2D                                   HorizontalRange;                               // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   VerticalRange;                                 // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FAimComponent>                 AimComponents;                                 // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        AnimName_LU;                                   // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_LC;                                   // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_LD;                                   // 0x0038 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_CU;                                   // 0x0040 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_CC;                                   // 0x0048 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_CD;                                   // 0x0050 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_RU;                                   // 0x0058 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_RC;                                   // 0x0060 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        AnimName_RD;                                   // 0x0068 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAimOffsetProfile& other) const { return memcmp(this, &other, sizeof(FAimOffsetProfile)) == 0; }
	bool operator!=(const FAimOffsetProfile& other) const { return !(*this == other); }
	bool operator<(const FAimOffsetProfile& other) const { return memcmp(this, &other, sizeof(FAimOffsetProfile)) < 0; }
};

// ScriptStruct Engine.AnimNodeBlendMultiBone.ChildBoneBlendInfo
// 0x0038
struct FChildBoneBlendInfo
{
	class TArray<float>                                TargetPerBoneWeight;                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        InitTargetStartBone;                           // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              InitPerBoneIncrease;                           // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FName                                        OldStartBone;                                  // 0x001C (0x0008) [0x0000000000000002] (CPF_Const)   
	float                                              OldBoneIncrease;                               // 0x0024 (0x0004) [0x0000000000000002] (CPF_Const)   
	class TArray<uint8_t>                              TargetRequiredBones;                           // 0x0028 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FChildBoneBlendInfo& other) const { return memcmp(this, &other, sizeof(FChildBoneBlendInfo)) == 0; }
	bool operator!=(const FChildBoneBlendInfo& other) const { return !(*this == other); }
	bool operator<(const FChildBoneBlendInfo& other) const { return memcmp(this, &other, sizeof(FChildBoneBlendInfo)) < 0; }
};

// ScriptStruct Engine.AnimNodeRandom.RandomAnimInfo
// 0x0020
struct FRandomAnimInfo
{
	float                                              Chance;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            LoopCountMin;                                  // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            LoopCountMax;                                  // 0x0005 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendInTime;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   PlayRateRange;                                 // 0x000C (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bStillFrame : 1;                               // 0x0014 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint8_t                                            LoopCount;                                     // 0x0018 (0x0001) [0x0000000000002000] (CPF_Transient)
	float                                              LastPosition;                                  // 0x001C (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FRandomAnimInfo& other) const { return memcmp(this, &other, sizeof(FRandomAnimInfo)) == 0; }
	bool operator!=(const FRandomAnimInfo& other) const { return !(*this == other); }
	bool operator<(const FRandomAnimInfo& other) const { return memcmp(this, &other, sizeof(FRandomAnimInfo)) < 0; }
};

// ScriptStruct Engine.AnimNodeSequenceBlendBase.AnimInfo
// 0x0014
struct FAnimInfo
{
	class FName                                        AnimSeqName;                                   // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UAnimSequence*                               AnimSeq;                                       // 0x0008 (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)
	int32_t                                            AnimLinkupIndex;                               // 0x0010 (0x0004) [0x0000000000002002] (CPF_Const | CPF_Transient)

	bool operator==(const FAnimInfo& other) const { return memcmp(this, &other, sizeof(FAnimInfo)) == 0; }
	bool operator!=(const FAnimInfo& other) const { return !(*this == other); }
	bool operator<(const FAnimInfo& other) const { return memcmp(this, &other, sizeof(FAnimInfo)) < 0; }
};

// ScriptStruct Engine.AnimNodeSequenceBlendBase.AnimBlendInfo
// 0x0024
struct FAnimBlendInfo
{
	class FName                                        AnimName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FAnimInfo                                   AnimInfo;                                      // 0x0008 (0x0018) [0x0000000000000000]               
	float                                              Weight;                                        // 0x0020 (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FAnimBlendInfo& other) const { return memcmp(this, &other, sizeof(FAnimBlendInfo)) == 0; }
	bool operator!=(const FAnimBlendInfo& other) const { return !(*this == other); }
	bool operator<(const FAnimBlendInfo& other) const { return memcmp(this, &other, sizeof(FAnimBlendInfo)) < 0; }
};

// ScriptStruct Engine.AnimNodeSynch.SynchGroup
// 0x0028
struct FSynchGroup
{
	class TArray<class UAnimNodeSequence*>             SeqNodes;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UAnimNodeSequence*                           MasterNode;                                    // 0x0010 (0x0008) [0x0000000000002000] (CPF_Transient)
	class FName                                        GroupName;                                     // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bFireSlaveNotifies : 1;                        // 0x0020 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              RateScale;                                     // 0x0024 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSynchGroup& other) const { return memcmp(this, &other, sizeof(FSynchGroup)) == 0; }
	bool operator!=(const FSynchGroup& other) const { return !(*this == other); }
	bool operator<(const FSynchGroup& other) const { return memcmp(this, &other, sizeof(FSynchGroup)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshComponent.BonePair
// 0x0010
struct FBonePair
{
	class FName                                        Bones[2];                                      // 0x0000 (0x0010) [0x0000000000000000]               

	bool operator==(const FBonePair& other) const { return memcmp(this, &other, sizeof(FBonePair)) == 0; }
	bool operator!=(const FBonePair& other) const { return !(*this == other); }
	bool operator<(const FBonePair& other) const { return memcmp(this, &other, sizeof(FBonePair)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshComponent.SkelMeshComponentLODInfo
// 0x001C
struct FSkelMeshComponentLODInfo
{
	class TArray<uint32_t>                             HiddenMaterials;                               // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint32_t                                           bNeedsInstanceWeightUpdate : 1;                // 0x0010 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bAlwaysUseInstanceWeights : 1;                 // 0x0010 (0x0004) [0x0000000000000002] [0x00000002] (CPF_Const)
	EInstanceWeightUsage                               InstanceWeightUsage;                           // 0x0014 (0x0001) [0x0000000000002002] (CPF_Const | CPF_Transient)
	int32_t                                            InstanceWeightIdx;                             // 0x0018 (0x0004) [0x0000000000002002] (CPF_Const | CPF_Transient)

	bool operator==(const FSkelMeshComponentLODInfo& other) const { return memcmp(this, &other, sizeof(FSkelMeshComponentLODInfo)) == 0; }
	bool operator!=(const FSkelMeshComponentLODInfo& other) const { return !(*this == other); }
	bool operator<(const FSkelMeshComponentLODInfo& other) const { return memcmp(this, &other, sizeof(FSkelMeshComponentLODInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshComponent.Attachment
// 0x0034
struct FAttachment
{
	class UActorComponent*                             Component;                                     // 0x0000 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class FName                                        BoneName;                                      // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     RelativeLocation;                              // 0x0010 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FRotator                                    RelativeRotation;                              // 0x001C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     RelativeScale;                                 // 0x0028 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAttachment& other) const { return memcmp(this, &other, sizeof(FAttachment)) == 0; }
	bool operator!=(const FAttachment& other) const { return !(*this == other); }
	bool operator<(const FAttachment& other) const { return memcmp(this, &other, sizeof(FAttachment)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshComponent.ActiveMorph
// 0x000C
struct FActiveMorph
{
	class UMorphTarget*                                Target;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Weight;                                        // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FActiveMorph& other) const { return memcmp(this, &other, sizeof(FActiveMorph)) == 0; }
	bool operator!=(const FActiveMorph& other) const { return !(*this == other); }
	bool operator<(const FActiveMorph& other) const { return memcmp(this, &other, sizeof(FActiveMorph)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LocalizedSubtitle
// 0x0024
struct FLocalizedSubtitle
{
	class FString                                      LanguageExt;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FSubtitleCue>                  Subtitles;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bMature : 1;                                   // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bManualWordWrap : 1;                           // 0x0020 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bSingleLine : 1;                               // 0x0020 (0x0004) [0x0000000000000000] [0x100000004] 

	bool operator==(const FLocalizedSubtitle& other) const { return memcmp(this, &other, sizeof(FLocalizedSubtitle)) == 0; }
	bool operator!=(const FLocalizedSubtitle& other) const { return !(*this == other); }
	bool operator<(const FLocalizedSubtitle& other) const { return memcmp(this, &other, sizeof(FLocalizedSubtitle)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightMapRef
// 0x0008
struct FLightMapRef
{
	struct FPointer                                    Reference;                                     // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FLightMapRef& other) const { return memcmp(this, &other, sizeof(FLightMapRef)) == 0; }
	bool operator!=(const FLightMapRef& other) const { return !(*this == other); }
	bool operator<(const FLightMapRef& other) const { return memcmp(this, &other, sizeof(FLightMapRef)) < 0; }
};

// ScriptStruct Engine.EngineTypes.DominantShadowInfo
// 0x00A4
struct FDominantShadowInfo
{
	struct FMatrix                                     WorldToLight;                                  // 0x0000 (0x0040) [0x0000000000000000]               
	struct FMatrix                                     LightToWorld;                                  // 0x0040 (0x0040) [0x0000000000000000]               
	struct FBox                                        LightSpaceImportanceBounds;                    // 0x0080 (0x001C) [0x0000000000000000]               
	int32_t                                            ShadowMapSizeX;                                // 0x009C (0x0004) [0x0000000000000000]               
	int32_t                                            ShadowMapSizeY;                                // 0x00A0 (0x0004) [0x0000000000000000]               
	uint8_t                                            MinStructAlignment[0xC];                         // 0x00A4 (0x000C) ADDED PADDING

	bool operator==(const FDominantShadowInfo& other) const { return memcmp(this, &other, sizeof(FDominantShadowInfo)) == 0; }
	bool operator!=(const FDominantShadowInfo& other) const { return !(*this == other); }
	bool operator<(const FDominantShadowInfo& other) const { return memcmp(this, &other, sizeof(FDominantShadowInfo)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightmassLightSettings
// 0x000C
struct FLightmassLightSettings
{
	float                                              IndirectLightingScale;                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              IndirectLightingSaturation;                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ShadowExponent;                                // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLightmassLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassLightSettings)) == 0; }
	bool operator!=(const FLightmassLightSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassLightSettings)) < 0; }
};

// ScriptStruct Engine.Pawn.ScalarParameterInterpStruct
// 0x0014
struct FScalarParameterInterpStruct
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              ParameterValue;                                // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              InterpTime;                                    // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WarmupTime;                                    // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FScalarParameterInterpStruct& other) const { return memcmp(this, &other, sizeof(FScalarParameterInterpStruct)) == 0; }
	bool operator!=(const FScalarParameterInterpStruct& other) const { return !(*this == other); }
	bool operator<(const FScalarParameterInterpStruct& other) const { return memcmp(this, &other, sizeof(FScalarParameterInterpStruct)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightmassPointLightSettings
// 0x0004 (0x000C - 0x0010)
struct FLightmassPointLightSettings : FLightmassLightSettings
{
	float                                              LightSourceRadius;                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLightmassPointLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassPointLightSettings)) == 0; }
	bool operator!=(const FLightmassPointLightSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassPointLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassPointLightSettings)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightmassDirectionalLightSettings
// 0x0004 (0x000C - 0x0010)
struct FLightmassDirectionalLightSettings : FLightmassLightSettings
{
	float                                              LightSourceAngle;                              // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLightmassDirectionalLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassDirectionalLightSettings)) == 0; }
	bool operator!=(const FLightmassDirectionalLightSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassDirectionalLightSettings& other) const { return memcmp(this, &other, sizeof(FLightmassDirectionalLightSettings)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightmassPrimitiveSettings
// 0x001C
struct FLightmassPrimitiveSettings
{
	uint32_t                                           bUseTwoSidedLighting : 1;                      // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bShadowIndirectOnly : 1;                       // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bUseEmissiveForStaticLighting : 1;             // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	float                                              EmissiveLightFalloffExponent;                  // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EmissiveLightExplicitInfluenceRadius;          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EmissiveBoost;                                 // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DiffuseBoost;                                  // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              SpecularBoost;                                 // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              FullyOccludedSamplesFraction;                  // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLightmassPrimitiveSettings& other) const { return memcmp(this, &other, sizeof(FLightmassPrimitiveSettings)) == 0; }
	bool operator!=(const FLightmassPrimitiveSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassPrimitiveSettings& other) const { return memcmp(this, &other, sizeof(FLightmassPrimitiveSettings)) < 0; }
};

// ScriptStruct Engine.EngineTypes.LightmassDebugOptions
// 0x0014
struct FLightmassDebugOptions
{
	uint32_t                                           bDebugMode : 1;                                // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bStatsEnabled : 1;                             // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bGatherBSPSurfacesAcrossComponents : 1;        // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	float                                              CoplanarTolerance;                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bUseDeterministicLighting : 1;                 // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bUseImmediateImport : 1;                       // 0x0008 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bImmediateProcessMappings : 1;                 // 0x0008 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bSortMappings : 1;                             // 0x0008 (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           bDumpBinaryFiles : 1;                          // 0x0008 (0x0004) [0x0000000000000001] [0x00000010] (CPF_Edit)
	uint32_t                                           bDebugMaterials : 1;                           // 0x0008 (0x0004) [0x0000000000000001] [0x00000020] (CPF_Edit)
	uint32_t                                           bPadMappings : 1;                              // 0x0008 (0x0004) [0x0000000000000001] [0x00000040] (CPF_Edit)
	uint32_t                                           bDebugPaddings : 1;                            // 0x0008 (0x0004) [0x0000000000000001] [0x00000080] (CPF_Edit)
	uint32_t                                           bOnlyCalcDebugTexelMappings : 1;               // 0x0008 (0x0004) [0x0000000000000001] [0x00000100] (CPF_Edit)
	uint32_t                                           bUseRandomColors : 1;                          // 0x0008 (0x0004) [0x0000000000000001] [0x00000200] (CPF_Edit)
	uint32_t                                           bColorBordersGreen : 1;                        // 0x0008 (0x0004) [0x0000000000000001] [0x00000400] (CPF_Edit)
	uint32_t                                           bColorByExecutionTime : 1;                     // 0x0008 (0x0004) [0x0000000000000001] [0x00000800] (CPF_Edit)
	float                                              ExecutionTimeDivisor;                          // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bInitialized : 1;                              // 0x0010 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FLightmassDebugOptions& other) const { return memcmp(this, &other, sizeof(FLightmassDebugOptions)) == 0; }
	bool operator!=(const FLightmassDebugOptions& other) const { return !(*this == other); }
	bool operator<(const FLightmassDebugOptions& other) const { return memcmp(this, &other, sizeof(FLightmassDebugOptions)) < 0; }
};

// ScriptStruct Engine.EngineTypes.SwarmDebugOptions
// 0x0004
struct FSwarmDebugOptions
{
	uint32_t                                           bDistributionEnabled : 1;                      // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bForceContentExport : 1;                       // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bInitialized : 1;                              // 0x0000 (0x0004) [0x0000000000000000] [0x100000004] 

	bool operator==(const FSwarmDebugOptions& other) const { return memcmp(this, &other, sizeof(FSwarmDebugOptions)) == 0; }
	bool operator!=(const FSwarmDebugOptions& other) const { return !(*this == other); }
	bool operator<(const FSwarmDebugOptions& other) const { return memcmp(this, &other, sizeof(FSwarmDebugOptions)) < 0; }
};

// ScriptStruct Engine.EngineTypes.RootMotionCurve
// 0x0024
struct FRootMotionCurve
{
	class FName                                        AnimName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveVector                          Curve;                                         // 0x0008 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	float                                              MaxCurveTime;                                  // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRootMotionCurve& other) const { return memcmp(this, &other, sizeof(FRootMotionCurve)) == 0; }
	bool operator!=(const FRootMotionCurve& other) const { return !(*this == other); }
	bool operator<(const FRootMotionCurve& other) const { return memcmp(this, &other, sizeof(FRootMotionCurve)) < 0; }
};

// ScriptStruct Engine.AnimNotify_Trails.TrailSocketSamplePoint
// 0x0018
struct FTrailSocketSamplePoint
{
	struct FVector                                     Position;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x000C (0x000C) [0x0000000000000000]               

	bool operator==(const FTrailSocketSamplePoint& other) const { return memcmp(this, &other, sizeof(FTrailSocketSamplePoint)) == 0; }
	bool operator!=(const FTrailSocketSamplePoint& other) const { return !(*this == other); }
	bool operator<(const FTrailSocketSamplePoint& other) const { return memcmp(this, &other, sizeof(FTrailSocketSamplePoint)) < 0; }
};

// ScriptStruct Engine.AnimNotify_Trails.TrailSamplePoint
// 0x004C
struct FTrailSamplePoint
{
	float                                              RelativeTime;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	struct FTrailSocketSamplePoint                     FirstEdgeSample;                               // 0x0004 (0x0018) [0x0000000000000000]               
	struct FTrailSocketSamplePoint                     ControlPointSample;                            // 0x001C (0x0018) [0x0000000000000000]               
	struct FTrailSocketSamplePoint                     SecondEdgeSample;                              // 0x0034 (0x0018) [0x0000000000000000]               

	bool operator==(const FTrailSamplePoint& other) const { return memcmp(this, &other, sizeof(FTrailSamplePoint)) == 0; }
	bool operator!=(const FTrailSamplePoint& other) const { return !(*this == other); }
	bool operator<(const FTrailSamplePoint& other) const { return memcmp(this, &other, sizeof(FTrailSamplePoint)) < 0; }
};

// ScriptStruct Engine.AnimNotify_Trails.TrailSample
// 0x0028
struct FTrailSample
{
	float                                              RelativeTime;                                  // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     FirstEdgeSample;                               // 0x0004 (0x000C) [0x0000000000000000]               
	struct FVector                                     ControlPointSample;                            // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     SecondEdgeSample;                              // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FTrailSample& other) const { return memcmp(this, &other, sizeof(FTrailSample)) == 0; }
	bool operator!=(const FTrailSample& other) const { return !(*this == other); }
	bool operator<(const FTrailSample& other) const { return memcmp(this, &other, sizeof(FTrailSample)) < 0; }
};

// ScriptStruct Engine.AnimSet.AnimSetMeshLinkup
// 0x0010
struct FAnimSetMeshLinkup
{
	class TArray<int32_t>                              BoneToTrackTable;                              // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAnimSetMeshLinkup& other) const { return memcmp(this, &other, sizeof(FAnimSetMeshLinkup)) == 0; }
	bool operator!=(const FAnimSetMeshLinkup& other) const { return !(*this == other); }
	bool operator<(const FAnimSetMeshLinkup& other) const { return memcmp(this, &other, sizeof(FAnimSetMeshLinkup)) < 0; }
};

// ScriptStruct Engine.AnimTree.AnimGroup
// 0x0030
struct FAnimGroup
{
	class TArray<class UAnimNodeSequence*>             SeqNodes;                                      // 0x0000 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	class UAnimNodeSequence*                           SynchMaster;                                   // 0x0010 (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)
	class UAnimNodeSequence*                           NotifyMaster;                                  // 0x0018 (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)
	class FName                                        GroupName;                                     // 0x0020 (0x0008) [0x0000000000000003] (CPF_Edit | CPF_Const)
	float                                              RateScale;                                     // 0x0028 (0x0004) [0x0000000000000003] (CPF_Edit | CPF_Const)
	float                                              SynchPctPosition;                              // 0x002C (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAnimGroup& other) const { return memcmp(this, &other, sizeof(FAnimGroup)) == 0; }
	bool operator!=(const FAnimGroup& other) const { return !(*this == other); }
	bool operator<(const FAnimGroup& other) const { return memcmp(this, &other, sizeof(FAnimGroup)) < 0; }
};

// ScriptStruct Engine.AnimTree.SkelControlListHead
// 0x0014
struct FSkelControlListHead
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class USkelControlBase*                            ControlHead;                                   // 0x0008 (0x0008) [0x0000000004400008] (CPF_ExportObject | CPF_NeedCtorLink | CPF_EditInline)
	int32_t                                            DrawY;                                         // 0x0010 (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FSkelControlListHead& other) const { return memcmp(this, &other, sizeof(FSkelControlListHead)) == 0; }
	bool operator!=(const FSkelControlListHead& other) const { return !(*this == other); }
	bool operator<(const FSkelControlListHead& other) const { return memcmp(this, &other, sizeof(FSkelControlListHead)) < 0; }
};

// ScriptStruct Engine.AnimTree.PreviewSkelMeshStruct
// 0x0020
struct FPreviewSkelMeshStruct
{
	class FName                                        DisplayName;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USkeletalMesh*                               PreviewSkelMesh;                               // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UMorphTargetSet*>               PreviewMorphSets;                              // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPreviewSkelMeshStruct& other) const { return memcmp(this, &other, sizeof(FPreviewSkelMeshStruct)) == 0; }
	bool operator!=(const FPreviewSkelMeshStruct& other) const { return !(*this == other); }
	bool operator<(const FPreviewSkelMeshStruct& other) const { return memcmp(this, &other, sizeof(FPreviewSkelMeshStruct)) < 0; }
};

// ScriptStruct Engine.AnimTree.PreviewSocketStruct
// 0x0020
struct FPreviewSocketStruct
{
	class FName                                        DisplayName;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        SocketName;                                    // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USkeletalMesh*                               PreviewSkelMesh;                               // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStaticMesh*                                 PreviewStaticMesh;                             // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPreviewSocketStruct& other) const { return memcmp(this, &other, sizeof(FPreviewSocketStruct)) == 0; }
	bool operator!=(const FPreviewSocketStruct& other) const { return !(*this == other); }
	bool operator<(const FPreviewSocketStruct& other) const { return memcmp(this, &other, sizeof(FPreviewSocketStruct)) < 0; }
};

// ScriptStruct Engine.AnimTree.PreviewAnimSetsStruct
// 0x0018
struct FPreviewAnimSetsStruct
{
	class FName                                        DisplayName;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UAnimSet*>                      PreviewAnimSets;                               // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPreviewAnimSetsStruct& other) const { return memcmp(this, &other, sizeof(FPreviewAnimSetsStruct)) == 0; }
	bool operator!=(const FPreviewAnimSetsStruct& other) const { return !(*this == other); }
	bool operator<(const FPreviewAnimSetsStruct& other) const { return memcmp(this, &other, sizeof(FPreviewAnimSetsStruct)) < 0; }
};

// ScriptStruct Engine.ApexClothingAsset.ClothingLodInfo
// 0x0010
struct FClothingLodInfo
{
	class TArray<int32_t>                              LODMaterialMap;                                // 0x0000 (0x0010) [0x0000000000500043] (CPF_Edit | CPF_Const | CPF_EditFixedSize | CPF_NeedCtorLink)

	bool operator==(const FClothingLodInfo& other) const { return memcmp(this, &other, sizeof(FClothingLodInfo)) == 0; }
	bool operator!=(const FClothingLodInfo& other) const { return !(*this == other); }
	bool operator<(const FClothingLodInfo& other) const { return memcmp(this, &other, sizeof(FClothingLodInfo)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleDamageParameters
// 0x0014
struct FNxDestructibleDamageParameters
{
	float                                              DamageThreshold;                               // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DamageSpread;                                  // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ImpactDamage;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ImpactResistance;                              // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            DefaultImpactDamageDepth;                      // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FNxDestructibleDamageParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDamageParameters)) == 0; }
	bool operator!=(const FNxDestructibleDamageParameters& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleDamageParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDamageParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleDebrisParameters
// 0x002C
struct FNxDestructibleDebrisParameters
{
	float                                              DebrisLifetimeMin;                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DebrisLifetimeMax;                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DebrisMaxSeparationMin;                        // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DebrisMaxSeparationMax;                        // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FBox                                        ValidBounds;                                   // 0x0010 (0x001C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FNxDestructibleDebrisParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDebrisParameters)) == 0; }
	bool operator!=(const FNxDestructibleDebrisParameters& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleDebrisParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDebrisParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleAdvancedParameters
// 0x0018
struct FNxDestructibleAdvancedParameters
{
	float                                              DamageCap;                                     // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ImpactVelocityThreshold;                       // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxChunkSpeed;                                 // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MassScaleExponent;                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MassScale;                                     // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FractureImpulseScale;                          // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FNxDestructibleAdvancedParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleAdvancedParameters)) == 0; }
	bool operator!=(const FNxDestructibleAdvancedParameters& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleAdvancedParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleAdvancedParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleParametersFlag
// 0x0004
struct FNxDestructibleParametersFlag
{
	uint32_t                                           ACCUMULATE_DAMAGE : 1;                         // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           ASSET_DEFINED_SUPPORT : 1;                     // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           WORLD_SUPPORT : 1;                             // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           DEBRIS_TIMEOUT : 1;                            // 0x0000 (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           DEBRIS_MAX_SEPARATION : 1;                     // 0x0000 (0x0004) [0x0000000000000001] [0x00000010] (CPF_Edit)
	uint32_t                                           CRUMBLE_SMALLEST_CHUNKS : 1;                   // 0x0000 (0x0004) [0x0000000000000001] [0x00000020] (CPF_Edit)
	uint32_t                                           ACCURATE_RAYCASTS : 1;                         // 0x0000 (0x0004) [0x0000000000000001] [0x00000040] (CPF_Edit)
	uint32_t                                           USE_VALID_BOUNDS : 1;                          // 0x0000 (0x0004) [0x0000000000000001] [0x00000080] (CPF_Edit)
	uint32_t                                           FORM_EXTENDED_STRUCTURES : 1;                  // 0x0000 (0x0004) [0x0000000000000001] [0x100000100] (CPF_Edit)

	bool operator==(const FNxDestructibleParametersFlag& other) const { return memcmp(this, &other, sizeof(FNxDestructibleParametersFlag)) == 0; }
	bool operator!=(const FNxDestructibleParametersFlag& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleParametersFlag& other) const { return memcmp(this, &other, sizeof(FNxDestructibleParametersFlag)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleDepthParameters
// 0x0005
struct FNxDestructibleDepthParameters
{
	uint32_t                                           TAKE_IMPACT_DAMAGE : 1;                        // 0x0000 (0x0004) [0x0000000020000000] [0x00000001]  CPF_Deprecated)
	uint32_t                                           IGNORE_POSE_UPDATES : 1;                       // 0x0000 (0x0004) [0x0000000020000000] [0x00000002]  CPF_Deprecated)
	uint32_t                                           IGNORE_RAYCAST_CALLBACKS : 1;                  // 0x0000 (0x0004) [0x0000000020000000] [0x00000004]  CPF_Deprecated)
	uint32_t                                           IGNORE_CONTACT_CALLBACKS : 1;                  // 0x0000 (0x0004) [0x0000000020000000] [0x00000008]  CPF_Deprecated)
	uint32_t                                           USER_FLAG : 1;                                 // 0x0000 (0x0004) [0x0000000020000000] [0x00000010]  CPF_Deprecated)
	uint32_t                                           USER_FLAG01 : 1;                               // 0x0000 (0x0004) [0x0000000020000000] [0x00000020]  CPF_Deprecated)
	uint32_t                                           USER_FLAG02 : 1;                               // 0x0000 (0x0004) [0x0000000020000000] [0x00000040]  CPF_Deprecated)
	uint32_t                                           USER_FLAG03 : 1;                               // 0x0000 (0x0004) [0x0000000020000000] [0x00000080]  CPF_Deprecated)
	EImpactDamageOverride                              ImpactDamageOverride;                          // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FNxDestructibleDepthParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDepthParameters)) == 0; }
	bool operator!=(const FNxDestructibleDepthParameters& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleDepthParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleDepthParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleAsset.NxDestructibleParameters
// 0x00F0
struct FNxDestructibleParameters
{
	struct FNxDestructibleDamageParameters             DamageParameters;                              // 0x0000 (0x0014) [0x0000000000000001] (CPF_Edit)    
	struct FNxDestructibleDebrisParameters             DebrisParameters;                              // 0x0014 (0x002C) [0x0000000000000001] (CPF_Edit)    
	struct FNxDestructibleAdvancedParameters           AdvancedParameters;                            // 0x0040 (0x0018) [0x0000000000000001] (CPF_Edit)    
	float                                              DamageThreshold;                               // 0x0058 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DamageToRadius;                                // 0x005C (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DamageCap;                                     // 0x0060 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              ForceToDamage;                                 // 0x0064 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              ImpactVelocityThreshold;                       // 0x0068 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              MaterialStrength;                              // 0x006C (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DamageToPercentDeformation;                    // 0x0070 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DeformationPercentLimit;                       // 0x0074 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	uint32_t                                           bFormExtendedStructures : 1;                   // 0x0078 (0x0004) [0x0000000020000000] [0x00000001]  CPF_Deprecated)
	int32_t                                            SupportDepth;                                  // 0x007C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MinimumFractureDepth;                          // 0x0080 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            DebrisDepth;                                   // 0x0084 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            EssentialDepth;                                // 0x0088 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DebrisLifetimeMin;                             // 0x008C (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DebrisLifetimeMax;                             // 0x0090 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DebrisMaxSeparationMin;                        // 0x0094 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              DebrisMaxSeparationMax;                        // 0x0098 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	struct FBox                                        ValidBounds;                                   // 0x009C (0x001C) [0x0000000020000000]  CPF_Deprecated)
	float                                              MaxChunkSpeed;                                 // 0x00B8 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              MassScaleExponent;                             // 0x00BC (0x0004) [0x0000000020000000]  CPF_Deprecated)
	struct FNxDestructibleParametersFlag               Flags;                                         // 0x00C0 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              GrbVolumeLimit;                                // 0x00C4 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              GrbParticleSpacing;                            // 0x00C8 (0x0004) [0x0000000020000000]  CPF_Deprecated)
	float                                              FractureImpulseScale;                          // 0x00CC (0x0004) [0x0000000020000000]  CPF_Deprecated)
	class TArray<struct FNxDestructibleDepthParameters> DepthParameters;                               // 0x00D0 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	int32_t                                            DynamicChunksDominanceGroup;                   // 0x00E0 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           UseDynamicChunksGroupsMask : 1;                // 0x00E4 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	ERBCollisionChannel                                DynamicChunksChannel;                          // 0x00E8 (0x0001) [0x0000000000000003] (CPF_Edit | CPF_Const)
	struct FRBCollisionChannelContainer                DynamicChunksCollideWithChannels;              // 0x00EC (0x0004) [0x0000000000000003] (CPF_Edit | CPF_Const)

	bool operator==(const FNxDestructibleParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleParameters)) == 0; }
	bool operator!=(const FNxDestructibleParameters& other) const { return !(*this == other); }
	bool operator<(const FNxDestructibleParameters& other) const { return memcmp(this, &other, sizeof(FNxDestructibleParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleDamageParameters.DamageParameters
// 0x0010
struct FDamageParameters
{
	EDamageParameterOverrideMode                       OverrideMode;                                  // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              BaseDamage;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Radius;                                        // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Momentum;                                      // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FDamageParameters& other) const { return memcmp(this, &other, sizeof(FDamageParameters)) == 0; }
	bool operator!=(const FDamageParameters& other) const { return !(*this == other); }
	bool operator<(const FDamageParameters& other) const { return memcmp(this, &other, sizeof(FDamageParameters)) < 0; }
};

// ScriptStruct Engine.ApexDestructibleDamageParameters.DamagePair
// 0x0018
struct FDamagePair
{
	class FName                                        DamageCauserName;                              // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FDamageParameters                           Params;                                        // 0x0008 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FDamagePair& other) const { return memcmp(this, &other, sizeof(FDamagePair)) == 0; }
	bool operator!=(const FDamagePair& other) const { return !(*this == other); }
	bool operator<(const FDamagePair& other) const { return memcmp(this, &other, sizeof(FDamagePair)) < 0; }
};

// ScriptStruct Engine.AppNotificationsBase.NotificationMessageInfo
// 0x0020
struct FNotificationMessageInfo
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNotificationMessageInfo& other) const { return memcmp(this, &other, sizeof(FNotificationMessageInfo)) == 0; }
	bool operator!=(const FNotificationMessageInfo& other) const { return !(*this == other); }
	bool operator<(const FNotificationMessageInfo& other) const { return memcmp(this, &other, sizeof(FNotificationMessageInfo)) < 0; }
};

// ScriptStruct Engine.AppNotificationsBase.NotificationInfo
// 0x0030
struct FNotificationInfo
{
	uint32_t                                           bIsLocal : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      MessageBody;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            BadgeNumber;                                   // 0x0018 (0x0004) [0x0000000000000000]               
	class TArray<struct FNotificationMessageInfo>      MessageInfo;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNotificationInfo& other) const { return memcmp(this, &other, sizeof(FNotificationInfo)) == 0; }
	bool operator!=(const FNotificationInfo& other) const { return !(*this == other); }
	bool operator<(const FNotificationInfo& other) const { return memcmp(this, &other, sizeof(FNotificationInfo)) < 0; }
};

// ScriptStruct Engine.AppNotificationsBase.LaunchNotificationInfo
// 0x0038
struct FLaunchNotificationInfo
{
	uint32_t                                           bWasLaunchedViaNotification : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FNotificationInfo                           Notification;                                  // 0x0008 (0x0030) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLaunchNotificationInfo& other) const { return memcmp(this, &other, sizeof(FLaunchNotificationInfo)) == 0; }
	bool operator!=(const FLaunchNotificationInfo& other) const { return !(*this == other); }
	bool operator<(const FLaunchNotificationInfo& other) const { return memcmp(this, &other, sizeof(FLaunchNotificationInfo)) < 0; }
};

// ScriptStruct Engine.Info.KeyValuePair
// 0x0020
struct FKeyValuePair
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FKeyValuePair& other) const { return memcmp(this, &other, sizeof(FKeyValuePair)) == 0; }
	bool operator!=(const FKeyValuePair& other) const { return !(*this == other); }
	bool operator<(const FKeyValuePair& other) const { return memcmp(this, &other, sizeof(FKeyValuePair)) < 0; }
};

// ScriptStruct Engine.Info.PlayerResponseLine
// 0x0038
struct FPlayerResponseLine
{
	int32_t                                            PlayerNum;                                     // 0x0000 (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            PlayerID;                                      // 0x0004 (0x0004) [0x0000000000100001] (CPF_Edit)    
	class FString                                      PlayerName;                                    // 0x0008 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            Ping;                                          // 0x0018 (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            Score;                                         // 0x001C (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            StatsID;                                       // 0x0020 (0x0004) [0x0000000000100001] (CPF_Edit)    
	class TArray<struct FKeyValuePair>                 PlayerInfo;                                    // 0x0028 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPlayerResponseLine& other) const { return memcmp(this, &other, sizeof(FPlayerResponseLine)) == 0; }
	bool operator!=(const FPlayerResponseLine& other) const { return !(*this == other); }
	bool operator<(const FPlayerResponseLine& other) const { return memcmp(this, &other, sizeof(FPlayerResponseLine)) < 0; }
};

// ScriptStruct Engine.Info.ServerResponseLine
// 0x0080
struct FServerResponseLine
{
	int32_t                                            ServerId;                                      // 0x0000 (0x0004) [0x0000000000100001] (CPF_Edit)    
	class FString                                      IP;                                            // 0x0008 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            Port;                                          // 0x0018 (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            QueryPort;                                     // 0x001C (0x0004) [0x0000000000100001] (CPF_Edit)    
	class FString                                      ServerName;                                    // 0x0020 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      MapName;                                       // 0x0030 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      GameType;                                      // 0x0040 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	int32_t                                            CurrentPlayers;                                // 0x0050 (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            MaxPlayers;                                    // 0x0054 (0x0004) [0x0000000000100001] (CPF_Edit)    
	int32_t                                            Ping;                                          // 0x0058 (0x0004) [0x0000000000100001] (CPF_Edit)    
	class TArray<struct FKeyValuePair>                 ServerInfo;                                    // 0x0060 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FPlayerResponseLine>           PlayerInfo;                                    // 0x0070 (0x0010) [0x0000000000500001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FServerResponseLine& other) const { return memcmp(this, &other, sizeof(FServerResponseLine)) == 0; }
	bool operator!=(const FServerResponseLine& other) const { return !(*this == other); }
	bool operator<(const FServerResponseLine& other) const { return memcmp(this, &other, sizeof(FServerResponseLine)) < 0; }
};

// ScriptStruct Engine.PlayerReplicationInfo.AutomatedTestingDatum
// 0x0008
struct FAutomatedTestingDatum
{
	int32_t                                            NumberOfMatchesPlayed;                         // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            NumMapListCyclesDone;                          // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FAutomatedTestingDatum& other) const { return memcmp(this, &other, sizeof(FAutomatedTestingDatum)) == 0; }
	bool operator!=(const FAutomatedTestingDatum& other) const { return !(*this == other); }
	bool operator<(const FAutomatedTestingDatum& other) const { return memcmp(this, &other, sizeof(FAutomatedTestingDatum)) < 0; }
};

// ScriptStruct Engine.Camera.ViewTargetTransitionParams
// 0x0010
struct FViewTargetTransitionParams
{
	float                                              BlendTime;                                     // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	EViewTargetBlendFunction                           BlendFunction;                                 // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendExp;                                      // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bLockOutgoing : 1;                             // 0x000C (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FViewTargetTransitionParams& other) const { return memcmp(this, &other, sizeof(FViewTargetTransitionParams)) == 0; }
	bool operator!=(const FViewTargetTransitionParams& other) const { return !(*this == other); }
	bool operator<(const FViewTargetTransitionParams& other) const { return memcmp(this, &other, sizeof(FViewTargetTransitionParams)) < 0; }
};

// ScriptStruct Engine.Camera.TCameraCache
// 0x0020
struct FTCameraCache
{
	float                                              TimeStamp;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FTPOV                                       POV;                                           // 0x0004 (0x001C) [0x0000000000000000]               

	bool operator==(const FTCameraCache& other) const { return memcmp(this, &other, sizeof(FTCameraCache)) == 0; }
	bool operator!=(const FTCameraCache& other) const { return !(*this == other); }
	bool operator<(const FTCameraCache& other) const { return memcmp(this, &other, sizeof(FTCameraCache)) < 0; }
};

// ScriptStruct Engine.Camera.TViewTarget
// 0x0038
struct FTViewTarget
{
	class AActor*                                      Target;                                        // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class AController*                                 Controller;                                    // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FTPOV                                       POV;                                           // 0x0010 (0x001C) [0x0000000000000001] (CPF_Edit)    
	float                                              AspectRatio;                                   // 0x002C (0x0004) [0x0000000000000001] (CPF_Edit)    
	class APlayerReplicationInfo*                      PRI;                                           // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTViewTarget& other) const { return memcmp(this, &other, sizeof(FTViewTarget)) == 0; }
	bool operator!=(const FTViewTarget& other) const { return !(*this == other); }
	bool operator<(const FTViewTarget& other) const { return memcmp(this, &other, sizeof(FTViewTarget)) < 0; }
};

// ScriptStruct Engine.PostProcessVolume.LUTBlender
// 0x0024
struct FLUTBlender
{
	class TArray<class UTexture*>                      LUTTextures;                                   // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<float>                                LUTWeights;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasChanged : 1;                               // 0x0020 (0x0004) [0x0000000000003002] [0x100000001] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FLUTBlender& other) const { return memcmp(this, &other, sizeof(FLUTBlender)) == 0; }
	bool operator!=(const FLUTBlender& other) const { return !(*this == other); }
	bool operator<(const FLUTBlender& other) const { return memcmp(this, &other, sizeof(FLUTBlender)) < 0; }
};

// ScriptStruct Engine.PostProcessVolume.MobileColorGradingParams
// 0x003C
struct FMobileColorGradingParams
{
	float                                              TransitionTime;                                // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Blend;                                         // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Desaturation;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                HighLights;                                    // 0x000C (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                MidTones;                                      // 0x001C (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                Shadows;                                       // 0x002C (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMobileColorGradingParams& other) const { return memcmp(this, &other, sizeof(FMobileColorGradingParams)) == 0; }
	bool operator!=(const FMobileColorGradingParams& other) const { return !(*this == other); }
	bool operator<(const FMobileColorGradingParams& other) const { return memcmp(this, &other, sizeof(FMobileColorGradingParams)) < 0; }
};

// ScriptStruct Engine.PostProcessVolume.MobilePostProcessSettings
// 0x0034
struct FMobilePostProcessSettings
{
	uint32_t                                           bOverride_Mobile_BlurAmount : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bOverride_Mobile_TransitionTime : 1;           // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bOverride_Mobile_Bloom_Scale : 1;              // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bOverride_Mobile_Bloom_Threshold : 1;          // 0x0000 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bOverride_Mobile_Bloom_Tint : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bOverride_Mobile_DOF_Distance : 1;             // 0x0000 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bOverride_Mobile_DOF_MinRange : 1;             // 0x0000 (0x0004) [0x0000000000000000] [0x00000040] 
	uint32_t                                           bOverride_Mobile_DOF_MaxRange : 1;             // 0x0000 (0x0004) [0x0000000000000000] [0x00000080] 
	uint32_t                                           bOverride_Mobile_DOF_FarBlurFactor : 1;        // 0x0000 (0x0004) [0x0000000000000000] [0x00000100] 
	float                                              Mobile_BlurAmount;                             // 0x0004 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_TransitionTime;                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Mobile_Bloom_Scale;                            // 0x000C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_Bloom_Threshold;                        // 0x0010 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FLinearColor                                Mobile_Bloom_Tint;                             // 0x0014 (0x0010) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_DOF_Distance;                           // 0x0024 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_DOF_MinRange;                           // 0x0028 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_DOF_MaxRange;                           // 0x002C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Mobile_DOF_FarBlurFactor;                      // 0x0030 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)

	bool operator==(const FMobilePostProcessSettings& other) const { return memcmp(this, &other, sizeof(FMobilePostProcessSettings)) == 0; }
	bool operator!=(const FMobilePostProcessSettings& other) const { return !(*this == other); }
	bool operator<(const FMobilePostProcessSettings& other) const { return memcmp(this, &other, sizeof(FMobilePostProcessSettings)) < 0; }
};

// ScriptStruct Engine.PostProcessVolume.PostProcessSettings
// 0x0168
struct FPostProcessSettings
{
	uint32_t                                           bOverride_EnableBloom : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bOverride_EnableDOF : 1;                       // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bOverride_EnableMotionBlur : 1;                // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bOverride_EnableSceneEffect : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bOverride_AllowAmbientOcclusion : 1;           // 0x0000 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bOverride_OverrideRimShaderColor : 1;          // 0x0000 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bOverride_Bloom_Scale : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000040] 
	uint32_t                                           bOverride_Bloom_Threshold : 1;                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000080] 
	uint32_t                                           bOverride_Bloom_Tint : 1;                      // 0x0000 (0x0004) [0x0000000000000000] [0x00000100] 
	uint32_t                                           bOverride_Bloom_ScreenBlendThreshold : 1;      // 0x0000 (0x0004) [0x0000000000000000] [0x00000200] 
	uint32_t                                           bOverride_Bloom_InterpolationDuration : 1;     // 0x0000 (0x0004) [0x0000000000000000] [0x00000400] 
	uint32_t                                           bOverride_DOF_FalloffExponent : 1;             // 0x0000 (0x0004) [0x0000000000000000] [0x00000800] 
	uint32_t                                           bOverride_DOF_BlurKernelSize : 1;              // 0x0000 (0x0004) [0x0000000000000000] [0x00001000] 
	uint32_t                                           bOverride_DOF_BlurBloomKernelSize : 1;         // 0x0000 (0x0004) [0x0000000000000000] [0x00002000] 
	uint32_t                                           bOverride_DOF_MaxNearBlurAmount : 1;           // 0x0000 (0x0004) [0x0000000000000000] [0x00004000] 
	uint32_t                                           bOverride_DOF_MinBlurAmount : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00008000] 
	uint32_t                                           bOverride_DOF_MaxFarBlurAmount : 1;            // 0x0000 (0x0004) [0x0000000000000000] [0x00010000] 
	uint32_t                                           bOverride_DOF_FocusType : 1;                   // 0x0000 (0x0004) [0x0000000000000000] [0x00020000] 
	uint32_t                                           bOverride_DOF_FocusInnerRadius : 1;            // 0x0000 (0x0004) [0x0000000000000000] [0x00040000] 
	uint32_t                                           bOverride_DOF_FocusDistance : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00080000] 
	uint32_t                                           bOverride_DOF_FocusPosition : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x00100000] 
	uint32_t                                           bOverride_DOF_InterpolationDuration : 1;       // 0x0000 (0x0004) [0x0000000000000000] [0x00200000] 
	uint32_t                                           bOverride_DOF_BokehTexture : 1;                // 0x0000 (0x0004) [0x0000000000000000] [0x00400000] 
	uint32_t                                           bOverride_MotionBlur_MaxVelocity : 1;          // 0x0000 (0x0004) [0x0000000000000000] [0x00800000] 
	uint32_t                                           bOverride_MotionBlur_Amount : 1;               // 0x0000 (0x0004) [0x0000000000000000] [0x01000000] 
	uint32_t                                           bOverride_MotionBlur_FullMotionBlur : 1;       // 0x0000 (0x0004) [0x0000000000000000] [0x02000000] 
	uint32_t                                           bOverride_MotionBlur_CameraRotationThreshold : 1;// 0x0000 (0x0004) [0x0000000000000000] [0x04000000] 
	uint32_t                                           bOverride_MotionBlur_CameraTranslationThreshold : 1;// 0x0000 (0x0004) [0x0000000000000000] [0x08000000] 
	uint32_t                                           bOverride_MotionBlur_InterpolationDuration : 1;// 0x0000 (0x0004) [0x0000000000000000] [0x10000000] 
	uint32_t                                           bOverride_Scene_Desaturation : 1;              // 0x0000 (0x0004) [0x0000000000000000] [0x20000000] 
	uint32_t                                           bOverride_Scene_Colorize : 1;                  // 0x0000 (0x0004) [0x0000000000000000] [0x40000000] 
	uint32_t                                           bOverride_Scene_TonemapperScale : 1;           // 0x0000 (0x0004) [0x0000000000000000] [0x80000000] 
	uint32_t                                           bOverride_Scene_ImageGrainScale : 1;           // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bOverride_Scene_HighLights : 1;                // 0x0004 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bOverride_Scene_MidTones : 1;                  // 0x0004 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bOverride_Scene_Shadows : 1;                   // 0x0004 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bOverride_Scene_InterpolationDuration : 1;     // 0x0004 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bOverride_Scene_ColorGradingLUT : 1;           // 0x0004 (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bOverride_RimShader_Color : 1;                 // 0x0004 (0x0004) [0x0000000000000000] [0x00000040] 
	uint32_t                                           bOverride_RimShader_InterpolationDuration : 1; // 0x0004 (0x0004) [0x0000000000000000] [0x00000080] 
	uint32_t                                           bOverride_MobileColorGrading : 1;              // 0x0004 (0x0004) [0x0000000000000000] [0x00000100] 
	uint32_t                                           bEnableBloom : 1;                              // 0x0004 (0x0004) [0x0000000000000001] [0x00000200] (CPF_Edit)
	uint32_t                                           bEnableDOF : 1;                                // 0x0004 (0x0004) [0x0000000000000001] [0x00000400] (CPF_Edit)
	uint32_t                                           bEnableMotionBlur : 1;                         // 0x0004 (0x0004) [0x0000000000000001] [0x00000800] (CPF_Edit)
	uint32_t                                           bEnableSceneEffect : 1;                        // 0x0004 (0x0004) [0x0000000000000001] [0x00001000] (CPF_Edit)
	uint32_t                                           bAllowAmbientOcclusion : 1;                    // 0x0004 (0x0004) [0x0000000000000001] [0x00002000] (CPF_Edit)
	uint32_t                                           bOverrideRimShaderColor : 1;                   // 0x0004 (0x0004) [0x0000000000000001] [0x00004000] (CPF_Edit)
	float                                              Bloom_Scale;                                   // 0x0008 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Bloom_Threshold;                               // 0x000C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FColor                                      Bloom_Tint;                                    // 0x0010 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Bloom_ScreenBlendThreshold;                    // 0x0014 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Bloom_InterpolationDuration;                   // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DOF_BlurBloomKernelSize;                       // 0x001C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_FalloffExponent;                           // 0x0020 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_BlurKernelSize;                            // 0x0024 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_MaxNearBlurAmount;                         // 0x0028 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_MinBlurAmount;                             // 0x002C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_MaxFarBlurAmount;                          // 0x0030 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	EFocusType                                         DOF_FocusType;                                 // 0x0034 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              DOF_FocusInnerRadius;                          // 0x0038 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_FocusDistance;                             // 0x003C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FVector                                     DOF_FocusPosition;                             // 0x0040 (0x000C) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              DOF_InterpolationDuration;                     // 0x004C (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UTexture2D*                                  DOF_BokehTexture;                              // 0x0050 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              MotionBlur_MaxVelocity;                        // 0x0058 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              MotionBlur_Amount;                             // 0x005C (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	uint32_t                                           MotionBlur_FullMotionBlur : 1;                 // 0x0060 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              MotionBlur_CameraRotationThreshold;            // 0x0064 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              MotionBlur_CameraTranslationThreshold;         // 0x0068 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              MotionBlur_InterpolationDuration;              // 0x006C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Scene_Desaturation;                            // 0x0070 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FVector                                     Scene_Colorize;                                // 0x0074 (0x000C) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Scene_TonemapperScale;                         // 0x0080 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Scene_ImageGrainScale;                         // 0x0084 (0x0004) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FVector                                     Scene_HighLights;                              // 0x0088 (0x000C) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FVector                                     Scene_MidTones;                                // 0x0094 (0x000C) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	struct FVector                                     Scene_Shadows;                                 // 0x00A0 (0x000C) [0x0000000200000001] (CPF_Edit | CPF_Interp)
	float                                              Scene_InterpolationDuration;                   // 0x00AC (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                RimShader_Color;                               // 0x00B0 (0x0010) [0x0000000000000001] (CPF_Edit)    
	float                                              RimShader_InterpolationDuration;               // 0x00C0 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UTexture*                                    ColorGrading_LookupTable;                      // 0x00C8 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FLUTBlender                                 ColorGradingLUT;                               // 0x00D0 (0x0028) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	struct FMobileColorGradingParams                   MobileColorGrading;                            // 0x00F8 (0x003C) [0x0000000000000001] (CPF_Edit)    
	struct FMobilePostProcessSettings                  MobilePostProcess;                             // 0x0134 (0x0034) [0x0000000200000001] (CPF_Edit | CPF_Interp)

	bool operator==(const FPostProcessSettings& other) const { return memcmp(this, &other, sizeof(FPostProcessSettings)) == 0; }
	bool operator!=(const FPostProcessSettings& other) const { return !(*this == other); }
	bool operator<(const FPostProcessSettings& other) const { return memcmp(this, &other, sizeof(FPostProcessSettings)) < 0; }
};

// ScriptStruct Engine.EngineBaseTypes.RenderingPerformanceOverrides
// 0x0004
struct FRenderingPerformanceOverrides
{
	uint32_t                                           bAllowAmbientOcclusion : 1;                    // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bAllowDominantWholeSceneDynamicShadows : 1;    // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bAllowMotionBlurSkinning : 1;                  // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bAllowTemporalAA : 1;                          // 0x0000 (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           bAllowLightShafts : 1;                         // 0x0000 (0x0004) [0x0000000000000001] [0x100000010] (CPF_Edit)

	bool operator==(const FRenderingPerformanceOverrides& other) const { return memcmp(this, &other, sizeof(FRenderingPerformanceOverrides)) == 0; }
	bool operator!=(const FRenderingPerformanceOverrides& other) const { return !(*this == other); }
	bool operator<(const FRenderingPerformanceOverrides& other) const { return memcmp(this, &other, sizeof(FRenderingPerformanceOverrides)) < 0; }
};

// ScriptStruct Engine.CameraShake.FOscillator
// 0x0009
struct FFOscillator
{
	float                                              Amplitude;                                     // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Frequency;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	EInitialOscillatorOffset                           InitialOffset;                                 // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFOscillator& other) const { return memcmp(this, &other, sizeof(FFOscillator)) == 0; }
	bool operator!=(const FFOscillator& other) const { return !(*this == other); }
	bool operator<(const FFOscillator& other) const { return memcmp(this, &other, sizeof(FFOscillator)) < 0; }
};

// ScriptStruct Engine.CameraShake.VOscillator
// 0x0024
struct FVOscillator
{
	struct FFOscillator                                X;                                             // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FFOscillator                                Y;                                             // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FFOscillator                                Z;                                             // 0x0018 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVOscillator& other) const { return memcmp(this, &other, sizeof(FVOscillator)) == 0; }
	bool operator!=(const FVOscillator& other) const { return !(*this == other); }
	bool operator<(const FVOscillator& other) const { return memcmp(this, &other, sizeof(FVOscillator)) < 0; }
};

// ScriptStruct Engine.CameraShake.ROscillator
// 0x0024
struct FROscillator
{
	struct FFOscillator                                Pitch;                                         // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FFOscillator                                Yaw;                                           // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FFOscillator                                Roll;                                          // 0x0018 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FROscillator& other) const { return memcmp(this, &other, sizeof(FROscillator)) == 0; }
	bool operator!=(const FROscillator& other) const { return !(*this == other); }
	bool operator<(const FROscillator& other) const { return memcmp(this, &other, sizeof(FROscillator)) < 0; }
};

// ScriptStruct Engine.CameraModifier_CameraShake.CameraShakeInstance
// 0x00A0
struct FCameraShakeInstance
{
	class UCameraShake*                                SourceShake;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        SourceShakeName;                               // 0x0008 (0x0008) [0x0000000000000000]               
	float                                              OscillatorTimeRemaining;                       // 0x0010 (0x0004) [0x0000000000000000]               
	uint32_t                                           bBlendingIn : 1;                               // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              CurrentBlendInTime;                            // 0x0018 (0x0004) [0x0000000000000000]               
	uint32_t                                           bBlendingOut : 1;                              // 0x001C (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              CurrentBlendOutTime;                           // 0x0020 (0x0004) [0x0000000000000000]               
	struct FVector                                     LocSinOffset;                                  // 0x0024 (0x000C) [0x0000000000000000]               
	struct FVector                                     RotSinOffset;                                  // 0x0030 (0x000C) [0x0000000000000000]               
	float                                              FOVSinOffset;                                  // 0x003C (0x0004) [0x0000000000000000]               
	float                                              Scale;                                         // 0x0040 (0x0004) [0x0000000000000000]               
	class UCameraAnimInst*                             AnimInst;                                      // 0x0048 (0x0008) [0x0000000000000000]               
	ECameraAnimPlaySpace                               PlaySpace;                                     // 0x0050 (0x0001) [0x0000000000000000]               
	uint8_t                                            UnknownData00[0xF];                              // 0x0051 (0x000F) MISSED OFFSET
	struct FMatrix                                     UserPlaySpaceMatrix;                           // 0x0060 (0x0040) [0x0000000000000000]               

	bool operator==(const FCameraShakeInstance& other) const { return memcmp(this, &other, sizeof(FCameraShakeInstance)) == 0; }
	bool operator!=(const FCameraShakeInstance& other) const { return !(*this == other); }
	bool operator<(const FCameraShakeInstance& other) const { return memcmp(this, &other, sizeof(FCameraShakeInstance)) < 0; }
};

// ScriptStruct Engine.Canvas.CanvasIcon
// 0x0018
struct FCanvasIcon
{
	class UTexture*                                    Texture;                                       // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              U;                                             // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              V;                                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              UL;                                            // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VL;                                            // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCanvasIcon& other) const { return memcmp(this, &other, sizeof(FCanvasIcon)) == 0; }
	bool operator!=(const FCanvasIcon& other) const { return !(*this == other); }
	bool operator<(const FCanvasIcon& other) const { return memcmp(this, &other, sizeof(FCanvasIcon)) < 0; }
};

// ScriptStruct Engine.Texture.TextureGroupContainer
// 0x0004
struct FTextureGroupContainer
{
	uint32_t                                           TEXTUREGROUP_World : 1;                        // 0x0000 (0x0004) [0x0000000000000003] [0x00000001] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_WorldNormalMap : 1;               // 0x0000 (0x0004) [0x0000000000000003] [0x00000002] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_WorldSpecular : 1;                // 0x0000 (0x0004) [0x0000000000000003] [0x00000004] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Character : 1;                    // 0x0000 (0x0004) [0x0000000000000003] [0x00000008] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_CharacterNormalMap : 1;           // 0x0000 (0x0004) [0x0000000000000003] [0x00000010] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_CharacterSpecular : 1;            // 0x0000 (0x0004) [0x0000000000000003] [0x00000020] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Weapon : 1;                       // 0x0000 (0x0004) [0x0000000000000003] [0x00000040] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_WeaponNormalMap : 1;              // 0x0000 (0x0004) [0x0000000000000003] [0x00000080] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_WeaponSpecular : 1;               // 0x0000 (0x0004) [0x0000000000000003] [0x00000100] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Vehicle : 1;                      // 0x0000 (0x0004) [0x0000000000000003] [0x00000200] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_VehicleNormalMap : 1;             // 0x0000 (0x0004) [0x0000000000000003] [0x00000400] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_VehicleSpecular : 1;              // 0x0000 (0x0004) [0x0000000000000003] [0x00000800] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Cinematic : 1;                    // 0x0000 (0x0004) [0x0000000000000003] [0x00001000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Effects : 1;                      // 0x0000 (0x0004) [0x0000000000000003] [0x00002000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_EffectsNotFiltered : 1;           // 0x0000 (0x0004) [0x0000000000000003] [0x00004000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Skybox : 1;                       // 0x0000 (0x0004) [0x0000000000000003] [0x00008000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_UI : 1;                           // 0x0000 (0x0004) [0x0000000000000003] [0x00010000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Lightmap : 1;                     // 0x0000 (0x0004) [0x0000000000000003] [0x00020000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_RenderTarget : 1;                 // 0x0000 (0x0004) [0x0000000000000003] [0x00040000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_MobileFlattened : 1;              // 0x0000 (0x0004) [0x0000000000000003] [0x00080000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_ProcBuilding_Face : 1;            // 0x0000 (0x0004) [0x0000000000000003] [0x00100000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_ProcBuilding_LightMap : 1;        // 0x0000 (0x0004) [0x0000000000000003] [0x00200000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Shadowmap : 1;                    // 0x0000 (0x0004) [0x0000000000000003] [0x00400000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_ColorLookupTable : 1;             // 0x0000 (0x0004) [0x0000000000000003] [0x00800000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Terrain_Heightmap : 1;            // 0x0000 (0x0004) [0x0000000000000003] [0x01000000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Terrain_Weightmap : 1;            // 0x0000 (0x0004) [0x0000000000000003] [0x02000000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_ImageBasedReflection : 1;         // 0x0000 (0x0004) [0x0000000000000003] [0x04000000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Bokeh : 1;                        // 0x0000 (0x0004) [0x0000000000000003] [0x08000000] (CPF_Edit | CPF_Const)
	uint32_t                                           TEXTUREGROUP_Pitch : 1;                        // 0x0000 (0x0004) [0x0000000000000003] [0x110000000] (CPF_Edit | CPF_Const)

	bool operator==(const FTextureGroupContainer& other) const { return memcmp(this, &other, sizeof(FTextureGroupContainer)) == 0; }
	bool operator!=(const FTextureGroupContainer& other) const { return !(*this == other); }
	bool operator<(const FTextureGroupContainer& other) const { return memcmp(this, &other, sizeof(FTextureGroupContainer)) < 0; }
};

// ScriptStruct Engine.Texture2D.Texture2DMipMap
// 0x0060
struct FTexture2DMipMap
{
	struct FUntypedBulkData_Mirror                     Data;                                          // 0x0000 (0x0058) [0x0000000000001000] (CPF_Native)  
	int32_t                                            SizeX;                                         // 0x0058 (0x0004) [0x0000000000001000] (CPF_Native)  
	int32_t                                            SizeY;                                         // 0x005C (0x0004) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FTexture2DMipMap& other) const { return memcmp(this, &other, sizeof(FTexture2DMipMap)) == 0; }
	bool operator!=(const FTexture2DMipMap& other) const { return !(*this == other); }
	bool operator<(const FTexture2DMipMap& other) const { return memcmp(this, &other, sizeof(FTexture2DMipMap)) < 0; }
};

// ScriptStruct Engine.Texture2D.TextureLinkedListMirror
// 0x0018
struct FTextureLinkedListMirror
{
	struct FPointer                                    Element;                                       // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    Next;                                          // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    PrevLink;                                      // 0x0010 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FTextureLinkedListMirror& other) const { return memcmp(this, &other, sizeof(FTextureLinkedListMirror)) == 0; }
	bool operator!=(const FTextureLinkedListMirror& other) const { return !(*this == other); }
	bool operator<(const FTextureLinkedListMirror& other) const { return memcmp(this, &other, sizeof(FTextureLinkedListMirror)) < 0; }
};

// ScriptStruct Engine.Canvas.DepthFieldGlowInfo
// 0x0024
struct FDepthFieldGlowInfo
{
	uint32_t                                           bEnableGlow : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FLinearColor                                GlowColor;                                     // 0x0004 (0x0010) [0x0000000000000000]               
	struct FVector2D                                   GlowOuterRadius;                               // 0x0014 (0x0008) [0x0000000000000000]               
	struct FVector2D                                   GlowInnerRadius;                               // 0x001C (0x0008) [0x0000000000000000]               

	bool operator==(const FDepthFieldGlowInfo& other) const { return memcmp(this, &other, sizeof(FDepthFieldGlowInfo)) == 0; }
	bool operator!=(const FDepthFieldGlowInfo& other) const { return !(*this == other); }
	bool operator<(const FDepthFieldGlowInfo& other) const { return memcmp(this, &other, sizeof(FDepthFieldGlowInfo)) < 0; }
};

// ScriptStruct Engine.Canvas.MobileDistanceFieldParams
// 0x0054
struct FMobileDistanceFieldParams
{
	float                                              Gamma;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              AlphaRefVal;                                   // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              SmoothWidth;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           EnableShadow : 1;                              // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector2D                                   ShadowDirection;                               // 0x0010 (0x0008) [0x0000000000000000]               
	struct FLinearColor                                ShadowColor;                                   // 0x0018 (0x0010) [0x0000000000000000]               
	float                                              ShadowSmoothWidth;                             // 0x0028 (0x0004) [0x0000000000000000]               
	struct FDepthFieldGlowInfo                         GlowInfo;                                      // 0x002C (0x0024) [0x0000000000001000] (CPF_Native)  
	int32_t                                            BlendMode;                                     // 0x0050 (0x0004) [0x0000000000000000]               

	bool operator==(const FMobileDistanceFieldParams& other) const { return memcmp(this, &other, sizeof(FMobileDistanceFieldParams)) == 0; }
	bool operator!=(const FMobileDistanceFieldParams& other) const { return !(*this == other); }
	bool operator<(const FMobileDistanceFieldParams& other) const { return memcmp(this, &other, sizeof(FMobileDistanceFieldParams)) < 0; }
};

// ScriptStruct Engine.Canvas.FontRenderInfo
// 0x0028
struct FFontRenderInfo
{
	uint32_t                                           bClipText : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bEnableShadow : 1;                             // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	struct FDepthFieldGlowInfo                         GlowInfo;                                      // 0x0004 (0x0024) [0x0000000000000000]               

	bool operator==(const FFontRenderInfo& other) const { return memcmp(this, &other, sizeof(FFontRenderInfo)) == 0; }
	bool operator!=(const FFontRenderInfo& other) const { return !(*this == other); }
	bool operator<(const FFontRenderInfo& other) const { return memcmp(this, &other, sizeof(FFontRenderInfo)) < 0; }
};

// ScriptStruct Engine.Canvas.CanvasUVTri
// 0x0030
struct FCanvasUVTri
{
	struct FVector2D                                   V0_Pos;                                        // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   V0_UV;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   V1_Pos;                                        // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   V1_UV;                                         // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   V2_Pos;                                        // 0x0020 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   V2_UV;                                         // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCanvasUVTri& other) const { return memcmp(this, &other, sizeof(FCanvasUVTri)) == 0; }
	bool operator!=(const FCanvasUVTri& other) const { return !(*this == other); }
	bool operator<(const FCanvasUVTri& other) const { return memcmp(this, &other, sizeof(FCanvasUVTri)) < 0; }
};

// ScriptStruct Engine.Canvas.TextSizingParameters
// 0x002C
struct FTextSizingParameters
{
	float                                              DrawX;                                         // 0x0000 (0x0004) [0x0000000000100000]               
	float                                              DrawY;                                         // 0x0004 (0x0004) [0x0000000000100000]               
	float                                              DrawXL;                                        // 0x0008 (0x0004) [0x0000000000100000]               
	float                                              DrawYL;                                        // 0x000C (0x0004) [0x0000000000100000]               
	struct FVector2D                                   Scaling;                                       // 0x0010 (0x0008) [0x0000000000100000]               
	class UFont*                                       DrawFont;                                      // 0x0018 (0x0008) [0x0000000000100000]               
	struct FVector2D                                   SpacingAdjust;                                 // 0x0020 (0x0008) [0x0000000000100000]               
	float                                              ViewportHeight;                                // 0x0028 (0x0004) [0x0000000000100000]               

	bool operator==(const FTextSizingParameters& other) const { return memcmp(this, &other, sizeof(FTextSizingParameters)) == 0; }
	bool operator!=(const FTextSizingParameters& other) const { return !(*this == other); }
	bool operator<(const FTextSizingParameters& other) const { return memcmp(this, &other, sizeof(FTextSizingParameters)) < 0; }
};

// ScriptStruct Engine.Canvas.WrappedStringElement
// 0x0018
struct FWrappedStringElement
{
	class FString                                      Value;                                         // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	struct FVector2D                                   LineExtent;                                    // 0x0010 (0x0008) [0x0000000000100000]               

	bool operator==(const FWrappedStringElement& other) const { return memcmp(this, &other, sizeof(FWrappedStringElement)) == 0; }
	bool operator!=(const FWrappedStringElement& other) const { return !(*this == other); }
	bool operator<(const FWrappedStringElement& other) const { return memcmp(this, &other, sizeof(FWrappedStringElement)) < 0; }
};

// ScriptStruct Engine.CloudSaveSystem.SetSaveDataCallbackStruct
// 0x0020
struct FSetSaveDataCallbackStruct
{
	int32_t                                            SlotIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSetSaveDataCallbackStruct& other) const { return memcmp(this, &other, sizeof(FSetSaveDataCallbackStruct)) == 0; }
	bool operator!=(const FSetSaveDataCallbackStruct& other) const { return !(*this == other); }
	bool operator<(const FSetSaveDataCallbackStruct& other) const { return memcmp(this, &other, sizeof(FSetSaveDataCallbackStruct)) < 0; }
};

// ScriptStruct Engine.CloudSaveSystem.SaveSlotOperation
// 0x0005
struct FSaveSlotOperation
{
	int32_t                                            SlotIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	ESaveSlotOperationEnum                             SlotOperation;                                 // 0x0004 (0x0001) [0x0000000000000000]               

	bool operator==(const FSaveSlotOperation& other) const { return memcmp(this, &other, sizeof(FSaveSlotOperation)) == 0; }
	bool operator!=(const FSaveSlotOperation& other) const { return !(*this == other); }
	bool operator<(const FSaveSlotOperation& other) const { return memcmp(this, &other, sizeof(FSaveSlotOperation)) < 0; }
};

// ScriptStruct Engine.CloudSaveSystem.GetSaveDataCallbackStruct
// 0x0020
struct FGetSaveDataCallbackStruct
{
	int32_t                                            SlotIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FGetSaveDataCallbackStruct& other) const { return memcmp(this, &other, sizeof(FGetSaveDataCallbackStruct)) == 0; }
	bool operator!=(const FGetSaveDataCallbackStruct& other) const { return !(*this == other); }
	bool operator<(const FGetSaveDataCallbackStruct& other) const { return memcmp(this, &other, sizeof(FGetSaveDataCallbackStruct)) < 0; }
};

// ScriptStruct Engine.UIRoot.UIRangeData
// 0x0014
struct FUIRangeData
{
	float                                              CurrentValue;                                  // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MinValue;                                      // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxValue;                                      // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              NudgeValue;                                    // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bIntRange : 1;                                 // 0x0010 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FUIRangeData& other) const { return memcmp(this, &other, sizeof(FUIRangeData)) == 0; }
	bool operator!=(const FUIRangeData& other) const { return !(*this == other); }
	bool operator<(const FUIRangeData& other) const { return memcmp(this, &other, sizeof(FUIRangeData)) < 0; }
};

// ScriptStruct Engine.UIRoot.TextureCoordinates
// 0x0010
struct FTextureCoordinates
{
	float                                              U;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              V;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              UL;                                            // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VL;                                            // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTextureCoordinates& other) const { return memcmp(this, &other, sizeof(FTextureCoordinates)) == 0; }
	bool operator!=(const FTextureCoordinates& other) const { return !(*this == other); }
	bool operator<(const FTextureCoordinates& other) const { return memcmp(this, &other, sizeof(FTextureCoordinates)) < 0; }
};

// ScriptStruct Engine.SequenceOp.SeqOpOutputInputLink
// 0x000C
struct FSeqOpOutputInputLink
{
	class USequenceOp*                                 LinkedOp;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            InputLinkIdx;                                  // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FSeqOpOutputInputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpOutputInputLink)) == 0; }
	bool operator!=(const FSeqOpOutputInputLink& other) const { return !(*this == other); }
	bool operator<(const FSeqOpOutputInputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpOutputInputLink)) < 0; }
};

// ScriptStruct Engine.SequenceOp.SeqOpOutputLink
// 0x0048
struct FSeqOpOutputLink
{
	class TArray<struct FSeqOpOutputInputLink>         Links;                                         // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LinkDesc;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasImpulse : 1;                               // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDisabled : 1;                                 // 0x0020 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bDisabledPIE : 1;                              // 0x0020 (0x0004) [0x0000000000000000] [0x00000004] 
	class USequenceOp*                                 LinkedOp;                                      // 0x0028 (0x0008) [0x0000000000000000]               
	float                                              ActivateDelay;                                 // 0x0030 (0x0004) [0x0000000000000000]               
	int32_t                                            DrawY;                                         // 0x0034 (0x0004) [0x0000000000000000]               
	uint32_t                                           bHidden : 1;                                   // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bMoving : 1;                                   // 0x0038 (0x0004) [0x0000000800002000] [0x00000002] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bClampedMax : 1;                               // 0x0038 (0x0004) [0x0000000800000000] [0x00000004] (CPF_EditorOnly)
	uint32_t                                           bClampedMin : 1;                               // 0x0038 (0x0004) [0x0000000800000000] [0x00000008] (CPF_EditorOnly)
	int32_t                                            OverrideDelta;                                 // 0x003C (0x0004) [0x0000000800000000] (CPF_EditorOnly)
	float                                              PIEActivationTime;                             // 0x0040 (0x0004) [0x0000000800002000] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bIsActivated : 1;                              // 0x0044 (0x0004) [0x0000000C01002000] [0x100000001] (CPF_Transient | CPF_NonTransactional | CPF_EditorOnly)

	bool operator==(const FSeqOpOutputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpOutputLink)) == 0; }
	bool operator!=(const FSeqOpOutputLink& other) const { return !(*this == other); }
	bool operator<(const FSeqOpOutputLink& other) const { return memcmp(this, &other, sizeof(FSeqOpOutputLink)) < 0; }
};

// ScriptStruct Engine.SequenceOp.SeqVarLink
// 0x0058
struct FSeqVarLink
{
	class UClass*                                      ExpectedType;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<class USequenceVariable*>             LinkedVariables;                               // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LinkDesc;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        LinkVar;                                       // 0x0028 (0x0008) [0x0000000000000000]               
	class FName                                        PropertyName;                                  // 0x0030 (0x0008) [0x0000000000000000]               
	uint32_t                                           bWriteable : 1;                                // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bSequenceNeverReadsOnlyWritesToThisVar : 1;    // 0x0038 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bModifiesLinkedObject : 1;                     // 0x0038 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bHidden : 1;                                   // 0x0038 (0x0004) [0x0000000000000000] [0x00000008] 
	int32_t                                            MinVars;                                       // 0x003C (0x0004) [0x0000000000000000]               
	int32_t                                            MaxVars;                                       // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            DrawX;                                         // 0x0044 (0x0004) [0x0000000000000000]               
	class UProperty*                                   CachedProperty;                                // 0x0048 (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)
	uint32_t                                           bAllowAnyType : 1;                             // 0x0050 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bMoving : 1;                                   // 0x0050 (0x0004) [0x0000000800002000] [0x00000002] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bClampedMax : 1;                               // 0x0050 (0x0004) [0x0000000800000000] [0x00000004] (CPF_EditorOnly)
	uint32_t                                           bClampedMin : 1;                               // 0x0050 (0x0004) [0x0000000800000000] [0x100000008] (CPF_EditorOnly)
	int32_t                                            OverrideDelta;                                 // 0x0054 (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FSeqVarLink& other) const { return memcmp(this, &other, sizeof(FSeqVarLink)) == 0; }
	bool operator!=(const FSeqVarLink& other) const { return !(*this == other); }
	bool operator<(const FSeqVarLink& other) const { return memcmp(this, &other, sizeof(FSeqVarLink)) < 0; }
};

// ScriptStruct Engine.SequenceOp.SeqEventLink
// 0x0034
struct FSeqEventLink
{
	class UClass*                                      ExpectedType;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<class USequenceEvent*>                LinkedEvents;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LinkDesc;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            DrawX;                                         // 0x0028 (0x0004) [0x0000000000000000]               
	uint32_t                                           bHidden : 1;                                   // 0x002C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bMoving : 1;                                   // 0x002C (0x0004) [0x0000000800002000] [0x00000002] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bClampedMax : 1;                               // 0x002C (0x0004) [0x0000000800000000] [0x00000004] (CPF_EditorOnly)
	uint32_t                                           bClampedMin : 1;                               // 0x002C (0x0004) [0x0000000800000000] [0x100000008] (CPF_EditorOnly)
	int32_t                                            OverrideDelta;                                 // 0x0030 (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FSeqEventLink& other) const { return memcmp(this, &other, sizeof(FSeqEventLink)) == 0; }
	bool operator!=(const FSeqEventLink& other) const { return !(*this == other); }
	bool operator<(const FSeqEventLink& other) const { return memcmp(this, &other, sizeof(FSeqEventLink)) < 0; }
};

// ScriptStruct Engine.UIRoot.InputKeyAction
// 0x0030
struct FInputKeyAction
{
	class FName                                        InputKeyName;                                  // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EInputEvent                                        InputKeyState;                                 // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FSeqOpOutputInputLink>         TriggeredOps;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class USequenceOp*>                   ActionsToExecute;                              // 0x0020 (0x0010) [0x0000000020400000] (CPF_NeedCtorLink | CPF_Deprecated)

	bool operator==(const FInputKeyAction& other) const { return memcmp(this, &other, sizeof(FInputKeyAction)) == 0; }
	bool operator!=(const FInputKeyAction& other) const { return !(*this == other); }
	bool operator<(const FInputKeyAction& other) const { return memcmp(this, &other, sizeof(FInputKeyAction)) < 0; }
};

// ScriptStruct Engine.UIRoot.InputEventParameters
// 0x0020
struct FInputEventParameters
{
	int32_t                                            PlayerIndex;                                   // 0x0000 (0x0004) [0x0000000000102002] (CPF_Const | CPF_Transient)
	int32_t                                            ControllerId;                                  // 0x0004 (0x0004) [0x0000000000102002] (CPF_Const | CPF_Transient)
	class FName                                        InputKeyName;                                  // 0x0008 (0x0008) [0x0000000000102002] (CPF_Const | CPF_Transient)
	EInputEvent                                        EventType;                                     // 0x0010 (0x0001) [0x0000000000102002] (CPF_Const | CPF_Transient)
	float                                              InputDelta;                                    // 0x0014 (0x0004) [0x0000000000102002] (CPF_Const | CPF_Transient)
	float                                              DeltaTime;                                     // 0x0018 (0x0004) [0x0000000000102002] (CPF_Const | CPF_Transient)
	uint32_t                                           bAltPressed : 1;                               // 0x001C (0x0004) [0x0000000000102002] [0x00000001] (CPF_Const | CPF_Transient)
	uint32_t                                           bCtrlPressed : 1;                              // 0x001C (0x0004) [0x0000000000102002] [0x00000002] (CPF_Const | CPF_Transient)
	uint32_t                                           bShiftPressed : 1;                             // 0x001C (0x0004) [0x0000000000102002] [0x100000004] (CPF_Const | CPF_Transient)

	bool operator==(const FInputEventParameters& other) const { return memcmp(this, &other, sizeof(FInputEventParameters)) == 0; }
	bool operator!=(const FInputEventParameters& other) const { return !(*this == other); }
	bool operator<(const FInputEventParameters& other) const { return memcmp(this, &other, sizeof(FInputEventParameters)) < 0; }
};

// ScriptStruct Engine.UIRoot.SubscribedInputEventParameters
// 0x0008 (0x0020 - 0x0028)
struct FSubscribedInputEventParameters : FInputEventParameters
{
	class FName                                        InputAliasName;                                // 0x0020 (0x0008) [0x0000000000102002] (CPF_Const | CPF_Transient)

	bool operator==(const FSubscribedInputEventParameters& other) const { return memcmp(this, &other, sizeof(FSubscribedInputEventParameters)) == 0; }
	bool operator!=(const FSubscribedInputEventParameters& other) const { return !(*this == other); }
	bool operator<(const FSubscribedInputEventParameters& other) const { return memcmp(this, &other, sizeof(FSubscribedInputEventParameters)) < 0; }
};

// ScriptStruct Engine.UIRoot.UIAxisEmulationDefinition
// 0x0024
struct FUIAxisEmulationDefinition
{
	class FName                                        AxisInputKey;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        AdjacentAxisInputKey;                          // 0x0008 (0x0008) [0x0000000000000000]               
	uint32_t                                           bEmulateButtonPress : 1;                       // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 
	class FName                                        InputKeyToEmulate[2];                          // 0x0014 (0x0010) [0x0000000000000000]               

	bool operator==(const FUIAxisEmulationDefinition& other) const { return memcmp(this, &other, sizeof(FUIAxisEmulationDefinition)) == 0; }
	bool operator!=(const FUIAxisEmulationDefinition& other) const { return !(*this == other); }
	bool operator<(const FUIAxisEmulationDefinition& other) const { return memcmp(this, &other, sizeof(FUIAxisEmulationDefinition)) < 0; }
};

// ScriptStruct Engine.UIRoot.RawInputKeyEventData
// 0x0009
struct FRawInputKeyEventData
{
	class FName                                        InputKeyName;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	uint8_t                                            ModifierKeyFlags;                              // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FRawInputKeyEventData& other) const { return memcmp(this, &other, sizeof(FRawInputKeyEventData)) == 0; }
	bool operator!=(const FRawInputKeyEventData& other) const { return !(*this == other); }
	bool operator<(const FRawInputKeyEventData& other) const { return memcmp(this, &other, sizeof(FRawInputKeyEventData)) < 0; }
};

// ScriptStruct Engine.Console.AutoCompleteCommand
// 0x0020
struct FAutoCompleteCommand
{
	class FString                                      Command;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Desc;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAutoCompleteCommand& other) const { return memcmp(this, &other, sizeof(FAutoCompleteCommand)) == 0; }
	bool operator!=(const FAutoCompleteCommand& other) const { return !(*this == other); }
	bool operator<(const FAutoCompleteCommand& other) const { return memcmp(this, &other, sizeof(FAutoCompleteCommand)) < 0; }
};

// ScriptStruct Engine.Console.AutoCompleteNode
// 0x0028
struct FAutoCompleteNode
{
	int32_t                                            IndexChar;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<int32_t>                              AutoCompleteListIndices;                       // 0x0008 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class TArray<struct FPointer>                      ChildNodes;                                    // 0x0018 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FAutoCompleteNode& other) const { return memcmp(this, &other, sizeof(FAutoCompleteNode)) == 0; }
	bool operator!=(const FAutoCompleteNode& other) const { return !(*this == other); }
	bool operator<(const FAutoCompleteNode& other) const { return memcmp(this, &other, sizeof(FAutoCompleteNode)) < 0; }
};

// ScriptStruct Engine.ControllerLayoutStack.ControllerLayout
// 0x000C
struct FControllerLayout
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0001000000000000]               
	int32_t                                            Priority;                                      // 0x0008 (0x0004) [0x0001000000000000]               

	bool operator==(const FControllerLayout& other) const { return memcmp(this, &other, sizeof(FControllerLayout)) == 0; }
	bool operator!=(const FControllerLayout& other) const { return !(*this == other); }
	bool operator<(const FControllerLayout& other) const { return memcmp(this, &other, sizeof(FControllerLayout)) < 0; }
};

// ScriptStruct Engine.CoverLink.CovPosInfo
// 0x0038
struct FCovPosInfo
{
	class ACoverLink*                                  Link;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            LtSlotIdx;                                     // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            RtSlotIdx;                                     // 0x000C (0x0004) [0x0000000000000000]               
	float                                              LtToRtPct;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     Normal;                                        // 0x0020 (0x000C) [0x0000000000000000]               
	struct FVector                                     Tangent;                                       // 0x002C (0x000C) [0x0000000000000000]               

	bool operator==(const FCovPosInfo& other) const { return memcmp(this, &other, sizeof(FCovPosInfo)) == 0; }
	bool operator!=(const FCovPosInfo& other) const { return !(*this == other); }
	bool operator<(const FCovPosInfo& other) const { return memcmp(this, &other, sizeof(FCovPosInfo)) < 0; }
};

// ScriptStruct Engine.CoverLink.FireLinkItem
// 0x0004
struct FFireLinkItem
{
	ECoverType                                         SrcType;                                       // 0x0000 (0x0001) [0x0000000000000000]               
	ECoverAction                                       SrcAction;                                     // 0x0001 (0x0001) [0x0000000000000000]               
	ECoverType                                         DestType;                                      // 0x0002 (0x0001) [0x0000000000000000]               
	ECoverAction                                       DestAction;                                    // 0x0003 (0x0001) [0x0000000000000000]               

	bool operator==(const FFireLinkItem& other) const { return memcmp(this, &other, sizeof(FFireLinkItem)) == 0; }
	bool operator!=(const FFireLinkItem& other) const { return !(*this == other); }
	bool operator<(const FFireLinkItem& other) const { return memcmp(this, &other, sizeof(FFireLinkItem)) < 0; }
};

// ScriptStruct Engine.CoverLink.FireLink
// 0x0018
struct FFireLink
{
	class TArray<uint8_t>                              Interactions;                                  // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            PackedProperties_CoverPairRefAndDynamicInfo;   // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bFallbackLink : 1;                             // 0x0014 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bDynamicIndexInited : 1;                       // 0x0014 (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FFireLink& other) const { return memcmp(this, &other, sizeof(FFireLink)) == 0; }
	bool operator!=(const FFireLink& other) const { return !(*this == other); }
	bool operator<(const FFireLink& other) const { return memcmp(this, &other, sizeof(FFireLink)) < 0; }
};

// ScriptStruct Engine.CoverLink.DynamicLinkInfo
// 0x0018
struct FDynamicLinkInfo
{
	struct FVector                                     LastTargetLocation;                            // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     LastSrcLocation;                               // 0x000C (0x000C) [0x0000000000000000]               

	bool operator==(const FDynamicLinkInfo& other) const { return memcmp(this, &other, sizeof(FDynamicLinkInfo)) == 0; }
	bool operator!=(const FDynamicLinkInfo& other) const { return !(*this == other); }
	bool operator<(const FDynamicLinkInfo& other) const { return memcmp(this, &other, sizeof(FDynamicLinkInfo)) < 0; }
};

// ScriptStruct Engine.CoverLink.CoverReference
// 0x0004 (0x0018 - 0x001C)
struct FCoverReference : FActorReference
{
	int32_t                                            SlotIdx;                                       // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCoverReference& other) const { return memcmp(this, &other, sizeof(FCoverReference)) == 0; }
	bool operator!=(const FCoverReference& other) const { return !(*this == other); }
	bool operator<(const FCoverReference& other) const { return memcmp(this, &other, sizeof(FCoverReference)) < 0; }
};

// ScriptStruct Engine.CoverLink.ExposedLink
// 0x0021
struct FExposedLink
{
	struct FCoverReference                             TargetActor;                                   // 0x0000 (0x0020) [0x0000000000020003] (CPF_Edit | CPF_Const | CPF_EditConst)
	uint8_t                                            ExposedScale;                                  // 0x0020 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FExposedLink& other) const { return memcmp(this, &other, sizeof(FExposedLink)) == 0; }
	bool operator!=(const FExposedLink& other) const { return !(*this == other); }
	bool operator<(const FExposedLink& other) const { return memcmp(this, &other, sizeof(FExposedLink)) < 0; }
};

// ScriptStruct Engine.CoverLink.SlotMoveRef
// 0x0064
struct FSlotMoveRef
{
	struct FPolyReference                              Poly;                                          // 0x0000 (0x0028) [0x0000000000000001] (CPF_Edit)    
	struct FBasedPosition                              Dest;                                          // 0x0028 (0x0038) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Direction;                                     // 0x0060 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSlotMoveRef& other) const { return memcmp(this, &other, sizeof(FSlotMoveRef)) == 0; }
	bool operator!=(const FSlotMoveRef& other) const { return !(*this == other); }
	bool operator<(const FSlotMoveRef& other) const { return memcmp(this, &other, sizeof(FSlotMoveRef)) < 0; }
};

// ScriptStruct Engine.CoverLink.CoverInfo
// 0x000C
struct FCoverInfo
{
	class ACoverLink*                                  Link;                                          // 0x0000 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	int32_t                                            SlotIdx;                                       // 0x0008 (0x0004) [0x0000000000020001] (CPF_Edit | CPF_EditConst)

	bool operator==(const FCoverInfo& other) const { return memcmp(this, &other, sizeof(FCoverInfo)) == 0; }
	bool operator!=(const FCoverInfo& other) const { return !(*this == other); }
	bool operator<(const FCoverInfo& other) const { return memcmp(this, &other, sizeof(FCoverInfo)) < 0; }
};

// ScriptStruct Engine.CoverLink.CoverSlot
// 0x0094
struct FCoverSlot
{
	class APawn*                                       SlotOwner;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              SlotValidAfterTime;                            // 0x0008 (0x0004) [0x0000000000002000] (CPF_Transient)
	ECoverType                                         ForceCoverType;                                // 0x000C (0x0001) [0x0000000000000001] (CPF_Edit)    
	ECoverType                                         CoverType;                                     // 0x000D (0x0001) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	ECoverLocationDescription                          LocationDescription;                           // 0x000E (0x0001) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     LocationOffset;                                // 0x0010 (0x000C) [0x0000000000000000]               
	struct FRotator                                    RotationOffset;                                // 0x001C (0x000C) [0x0000000000000000]               
	class TArray<ECoverAction>                         Actions;                                       // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FFireLink>                     FireLinks;                                     // 0x0038 (0x0010) [0x0000000000420001] (CPF_Edit | CPF_EditConst | CPF_NeedCtorLink)
	class TArray<struct FFireLink>                     RejectedFireLinks;                             // 0x0048 (0x0010) [0x0000000000422001] (CPF_Edit | CPF_Transient | CPF_EditConst | CPF_NeedCtorLink)
	class TArray<int32_t>                              ExposedCoverPackedProperties;                  // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TurnTargetPackedProperties;                    // 0x0068 (0x0004) [0x0000000000000000]               
	class TArray<struct FSlotMoveRef>                  SlipRefs;                                      // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCoverInfo>                    OverlapClaimsList;                             // 0x0080 (0x0010) [0x0000000000420001] (CPF_Edit | CPF_EditConst | CPF_NeedCtorLink)
	uint32_t                                           bLeanLeft : 1;                                 // 0x0090 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bLeanRight : 1;                                // 0x0090 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bForceCanPopUp : 1;                            // 0x0090 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bCanPopUp : 1;                                 // 0x0090 (0x0004) [0x0000000000020001] [0x00000008] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bCanMantle : 1;                                // 0x0090 (0x0004) [0x0000000000020001] [0x00000010] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bCanClimbUp : 1;                               // 0x0090 (0x0004) [0x0000000000020001] [0x00000020] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bForceCanCoverSlip_Left : 1;                   // 0x0090 (0x0004) [0x0000000000000001] [0x00000040] (CPF_Edit)
	uint32_t                                           bForceCanCoverSlip_Right : 1;                  // 0x0090 (0x0004) [0x0000000000000001] [0x00000080] (CPF_Edit)
	uint32_t                                           bCanCoverSlip_Left : 1;                        // 0x0090 (0x0004) [0x0000000000020001] [0x00000100] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bCanCoverSlip_Right : 1;                       // 0x0090 (0x0004) [0x0000000000020001] [0x00000200] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bCanSwatTurn_Left : 1;                         // 0x0090 (0x0004) [0x0000000000020001] [0x00000400] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bCanSwatTurn_Right : 1;                        // 0x0090 (0x0004) [0x0000000000020001] [0x00000800] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bEnabled : 1;                                  // 0x0090 (0x0004) [0x0000000000000001] [0x00001000] (CPF_Edit)
	uint32_t                                           bAllowPopup : 1;                               // 0x0090 (0x0004) [0x0000000000000001] [0x00002000] (CPF_Edit)
	uint32_t                                           bAllowMantle : 1;                              // 0x0090 (0x0004) [0x0000000000000001] [0x00004000] (CPF_Edit)
	uint32_t                                           bAllowCoverSlip : 1;                           // 0x0090 (0x0004) [0x0000000000000001] [0x00008000] (CPF_Edit)
	uint32_t                                           bAllowClimbUp : 1;                             // 0x0090 (0x0004) [0x0000000000000001] [0x00010000] (CPF_Edit)
	uint32_t                                           bAllowSwatTurn : 1;                            // 0x0090 (0x0004) [0x0000000000000001] [0x00020000] (CPF_Edit)
	uint32_t                                           bForceNoGroundAdjust : 1;                      // 0x0090 (0x0004) [0x0000000000000001] [0x00040000] (CPF_Edit)
	uint32_t                                           bPlayerOnly : 1;                               // 0x0090 (0x0004) [0x0000000000000001] [0x00080000] (CPF_Edit)
	uint32_t                                           bPreferLeanOverPopup : 1;                      // 0x0090 (0x0004) [0x0000000000000001] [0x00100000] (CPF_Edit)
	uint32_t                                           bDestructible : 1;                             // 0x0090 (0x0004) [0x0000000000002000] [0x00200000] (CPF_Transient)
	uint32_t                                           bSelected : 1;                                 // 0x0090 (0x0004) [0x0000000000002000] [0x00400000] (CPF_Transient)
	uint32_t                                           bFailedToFindSurface : 1;                      // 0x0090 (0x0004) [0x0000000000022001] [0x100800000] (CPF_Edit | CPF_Transient | CPF_EditConst)

	bool operator==(const FCoverSlot& other) const { return memcmp(this, &other, sizeof(FCoverSlot)) == 0; }
	bool operator!=(const FCoverSlot& other) const { return !(*this == other); }
	bool operator<(const FCoverSlot& other) const { return memcmp(this, &other, sizeof(FCoverSlot)) < 0; }
};

// ScriptStruct Engine.StaticMeshComponent.PaintedVertex
// 0x0014
struct FPaintedVertex
{
	struct FVector                                     Position;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FPackedNormal                               Normal;                                        // 0x000C (0x0004) [0x0000000000000000]               
	struct FColor                                      Color;                                         // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FPaintedVertex& other) const { return memcmp(this, &other, sizeof(FPaintedVertex)) == 0; }
	bool operator!=(const FPaintedVertex& other) const { return !(*this == other); }
	bool operator<(const FPaintedVertex& other) const { return memcmp(this, &other, sizeof(FPaintedVertex)) < 0; }
};

// ScriptStruct Engine.StaticMeshComponent.StaticMeshComponentLODInfo
// 0x0040
struct FStaticMeshComponentLODInfo
{
	class TArray<class UShadowMap2D*>                  ShadowMaps;                                    // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<class UObject*>                       ShadowVertexBuffers;                           // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FPointer                                    LightMap;                                      // 0x0020 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    OverrideVertexColors;                          // 0x0028 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	class TArray<struct FPaintedVertex>                PaintedVertices;                               // 0x0030 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FStaticMeshComponentLODInfo& other) const { return memcmp(this, &other, sizeof(FStaticMeshComponentLODInfo)) == 0; }
	bool operator!=(const FStaticMeshComponentLODInfo& other) const { return !(*this == other); }
	bool operator<(const FStaticMeshComponentLODInfo& other) const { return memcmp(this, &other, sizeof(FStaticMeshComponentLODInfo)) < 0; }
};

// ScriptStruct Engine.CoverMeshComponent.CoverMeshes
// 0x0068
struct FCoverMeshes
{
	class UStaticMesh*                                 Base;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 LeanLeft;                                      // 0x0008 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 LeanRight;                                     // 0x0010 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 LeanLeftPref;                                  // 0x0018 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 LeanRightPref;                                 // 0x0020 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 Climb;                                         // 0x0028 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 Mantle;                                        // 0x0030 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 SlipLeft;                                      // 0x0038 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 SlipRight;                                     // 0x0040 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 SwatLeft;                                      // 0x0048 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 SwatRight;                                     // 0x0050 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 PopUp;                                         // 0x0058 (0x0008) [0x0000000000000000]               
	class UStaticMesh*                                 PlayerOnly;                                    // 0x0060 (0x0008) [0x0000000000000000]               

	bool operator==(const FCoverMeshes& other) const { return memcmp(this, &other, sizeof(FCoverMeshes)) == 0; }
	bool operator!=(const FCoverMeshes& other) const { return !(*this == other); }
	bool operator<(const FCoverMeshes& other) const { return memcmp(this, &other, sizeof(FCoverMeshes)) < 0; }
};

// ScriptStruct Engine.CoverReplicator.ManualCoverTypeInfo
// 0x0002
struct FManualCoverTypeInfo
{
	uint8_t                                            SlotIndex;                                     // 0x0000 (0x0001) [0x0000000000000000]               
	ECoverType                                         ManualCoverType;                               // 0x0001 (0x0001) [0x0000000000000000]               

	bool operator==(const FManualCoverTypeInfo& other) const { return memcmp(this, &other, sizeof(FManualCoverTypeInfo)) == 0; }
	bool operator!=(const FManualCoverTypeInfo& other) const { return !(*this == other); }
	bool operator<(const FManualCoverTypeInfo& other) const { return memcmp(this, &other, sizeof(FManualCoverTypeInfo)) < 0; }
};

// ScriptStruct Engine.CoverReplicator.CoverReplicationInfo
// 0x0048
struct FCoverReplicationInfo
{
	class ACoverLink*                                  Link;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class TArray<uint8_t>                              SlotsEnabled;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              SlotsDisabled;                                 // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              SlotsAdjusted;                                 // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FManualCoverTypeInfo>          SlotsCoverTypeChanged;                         // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCoverReplicationInfo& other) const { return memcmp(this, &other, sizeof(FCoverReplicationInfo)) == 0; }
	bool operator!=(const FCoverReplicationInfo& other) const { return !(*this == other); }
	bool operator<(const FCoverReplicationInfo& other) const { return memcmp(this, &other, sizeof(FCoverReplicationInfo)) < 0; }
};

// ScriptStruct Engine.CullDistanceVolume.CullDistanceSizePair
// 0x0008
struct FCullDistanceSizePair
{
	float                                              Size;                                          // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              CullDistance;                                  // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCullDistanceSizePair& other) const { return memcmp(this, &other, sizeof(FCullDistanceSizePair)) == 0; }
	bool operator!=(const FCullDistanceSizePair& other) const { return !(*this == other); }
	bool operator<(const FCullDistanceSizePair& other) const { return memcmp(this, &other, sizeof(FCullDistanceSizePair)) < 0; }
};

// ScriptStruct Engine.CurveEdPresetCurve.PresetGeneratedPoint
// 0x0015
struct FPresetGeneratedPoint
{
	float                                              KeyIn;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              KeyOut;                                        // 0x0004 (0x0004) [0x0000000000000000]               
	uint32_t                                           TangentsValid : 1;                             // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              TangentIn;                                     // 0x000C (0x0004) [0x0000000000000000]               
	float                                              TangentOut;                                    // 0x0010 (0x0004) [0x0000000000000000]               
	EInterpCurveMode                                   IntepMode;                                     // 0x0014 (0x0001) [0x0000000000000000]               

	bool operator==(const FPresetGeneratedPoint& other) const { return memcmp(this, &other, sizeof(FPresetGeneratedPoint)) == 0; }
	bool operator!=(const FPresetGeneratedPoint& other) const { return !(*this == other); }
	bool operator<(const FPresetGeneratedPoint& other) const { return memcmp(this, &other, sizeof(FPresetGeneratedPoint)) < 0; }
};

// ScriptStruct Engine.DataStoreClient.PlayerDataStoreGroup
// 0x0018
struct FPlayerDataStoreGroup
{
	class ULocalPlayer*                                PlayerOwner;                                   // 0x0000 (0x0008) [0x0000000000102002] (CPF_Const | CPF_Transient)
	class TArray<class UUIDataStore*>                  DataStores;                                    // 0x0008 (0x0010) [0x0000000000502002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FPlayerDataStoreGroup& other) const { return memcmp(this, &other, sizeof(FPlayerDataStoreGroup)) == 0; }
	bool operator!=(const FPlayerDataStoreGroup& other) const { return !(*this == other); }
	bool operator<(const FPlayerDataStoreGroup& other) const { return memcmp(this, &other, sizeof(FPlayerDataStoreGroup)) < 0; }
};

// ScriptStruct Engine.DateTime.DateTimeStruct
// 0x001D
struct FDateTimeStruct
{
	int32_t                                            Year;                                          // 0x0000 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Month;                                         // 0x0004 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Day;                                           // 0x0008 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            WeekDay;                                       // 0x000C (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Hour;                                          // 0x0010 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Minute;                                        // 0x0014 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	int32_t                                            Second;                                        // 0x0018 (0x0004) [0x0000000040000000] (CPF_DataBinding)
	ETimeZone                                          TimeZone;                                      // 0x001C (0x0001) [0x0000000040000000] (CPF_DataBinding)

	bool operator==(const FDateTimeStruct& other) const { return memcmp(this, &other, sizeof(FDateTimeStruct)) == 0; }
	bool operator!=(const FDateTimeStruct& other) const { return !(*this == other); }
	bool operator<(const FDateTimeStruct& other) const { return memcmp(this, &other, sizeof(FDateTimeStruct)) < 0; }
};

// ScriptStruct Engine.DecalComponent.DecalReceiver
// 0x0010
struct FDecalReceiver
{
	class UPrimitiveComponent*                         Component;                                     // 0x0000 (0x0008) [0x000000000408000A] (CPF_Const | CPF_ExportObject | CPF_Component | CPF_EditInline)
	struct FPointer                                    RenderData;                                    // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FDecalReceiver& other) const { return memcmp(this, &other, sizeof(FDecalReceiver)) == 0; }
	bool operator!=(const FDecalReceiver& other) const { return !(*this == other); }
	bool operator<(const FDecalReceiver& other) const { return memcmp(this, &other, sizeof(FDecalReceiver)) < 0; }
};

// ScriptStruct Engine.DecalManager.ActiveDecalInfo
// 0x000C
struct FActiveDecalInfo
{
	class UDecalComponent*                             Decal;                                         // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	float                                              LifetimeRemaining;                             // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FActiveDecalInfo& other) const { return memcmp(this, &other, sizeof(FActiveDecalInfo)) == 0; }
	bool operator!=(const FActiveDecalInfo& other) const { return !(*this == other); }
	bool operator<(const FActiveDecalInfo& other) const { return memcmp(this, &other, sizeof(FActiveDecalInfo)) < 0; }
};

// ScriptStruct Engine.MaterialInterface.LightmassMaterialInterfaceSettings
// 0x001C
struct FLightmassMaterialInterfaceSettings
{
	uint32_t                                           bCastShadowAsMasked : 1;                       // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              EmissiveBoost;                                 // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DiffuseBoost;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              SpecularBoost;                                 // 0x000C (0x0004) [0x0000000000000000]               
	float                                              ExportResolutionScale;                         // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DistanceFieldPenumbraScale;                    // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bOverrideCastShadowAsMasked : 1;               // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bOverrideEmissiveBoost : 1;                    // 0x0018 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bOverrideDiffuseBoost : 1;                     // 0x0018 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bOverrideSpecularBoost : 1;                    // 0x0018 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bOverrideExportResolutionScale : 1;            // 0x0018 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bOverrideDistanceFieldPenumbraScale : 1;       // 0x0018 (0x0004) [0x0000000000000000] [0x100000020] 

	bool operator==(const FLightmassMaterialInterfaceSettings& other) const { return memcmp(this, &other, sizeof(FLightmassMaterialInterfaceSettings)) == 0; }
	bool operator!=(const FLightmassMaterialInterfaceSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassMaterialInterfaceSettings& other) const { return memcmp(this, &other, sizeof(FLightmassMaterialInterfaceSettings)) < 0; }
};

// ScriptStruct Engine.Material.MaterialInput
// 0x0038
struct FMaterialInput
{
	class UMaterialExpression*                         Expression;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            OutputIndex;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	class FString                                      InputName;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Mask;                                          // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskR;                                         // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskG;                                         // 0x0028 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskB;                                         // 0x002C (0x0004) [0x0000000000000000]               
	int32_t                                            MaskA;                                         // 0x0030 (0x0004) [0x0000000000000000]               
	int32_t                                            GCC64_Padding;                                 // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FMaterialInput& other) const { return memcmp(this, &other, sizeof(FMaterialInput)) == 0; }
	bool operator!=(const FMaterialInput& other) const { return !(*this == other); }
	bool operator<(const FMaterialInput& other) const { return memcmp(this, &other, sizeof(FMaterialInput)) < 0; }
};

// ScriptStruct Engine.Material.MaterialFunctionInfo
// 0x0018
struct FMaterialFunctionInfo
{
	struct FGuid                                       StateId;                                       // 0x0000 (0x0010) [0x0000000000000000]               
	class UMaterialFunction*                           Function;                                      // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FMaterialFunctionInfo& other) const { return memcmp(this, &other, sizeof(FMaterialFunctionInfo)) == 0; }
	bool operator!=(const FMaterialFunctionInfo& other) const { return !(*this == other); }
	bool operator<(const FMaterialFunctionInfo& other) const { return memcmp(this, &other, sizeof(FMaterialFunctionInfo)) < 0; }
};

// ScriptStruct Engine.Material.ColorMaterialInput
// 0x0008 (0x0038 - 0x0040)
struct FColorMaterialInput : FMaterialInput
{
	uint32_t                                           UseConstant : 1;                               // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FColor                                      Constant;                                      // 0x003C (0x0004) [0x0000000000000000]               

	bool operator==(const FColorMaterialInput& other) const { return memcmp(this, &other, sizeof(FColorMaterialInput)) == 0; }
	bool operator!=(const FColorMaterialInput& other) const { return !(*this == other); }
	bool operator<(const FColorMaterialInput& other) const { return memcmp(this, &other, sizeof(FColorMaterialInput)) < 0; }
};

// ScriptStruct Engine.Material.ScalarMaterialInput
// 0x0008 (0x0038 - 0x0040)
struct FScalarMaterialInput : FMaterialInput
{
	uint32_t                                           UseConstant : 1;                               // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              Constant;                                      // 0x003C (0x0004) [0x0000000000000000]               

	bool operator==(const FScalarMaterialInput& other) const { return memcmp(this, &other, sizeof(FScalarMaterialInput)) == 0; }
	bool operator!=(const FScalarMaterialInput& other) const { return !(*this == other); }
	bool operator<(const FScalarMaterialInput& other) const { return memcmp(this, &other, sizeof(FScalarMaterialInput)) < 0; }
};

// ScriptStruct Engine.Material.VectorMaterialInput
// 0x0010 (0x0038 - 0x0048)
struct FVectorMaterialInput : FMaterialInput
{
	uint32_t                                           UseConstant : 1;                               // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Constant;                                      // 0x003C (0x000C) [0x0000000000000000]               

	bool operator==(const FVectorMaterialInput& other) const { return memcmp(this, &other, sizeof(FVectorMaterialInput)) == 0; }
	bool operator!=(const FVectorMaterialInput& other) const { return !(*this == other); }
	bool operator<(const FVectorMaterialInput& other) const { return memcmp(this, &other, sizeof(FVectorMaterialInput)) < 0; }
};

// ScriptStruct Engine.Material.Vector2MaterialInput
// 0x000C (0x0038 - 0x0044)
struct FVector2MaterialInput : FMaterialInput
{
	uint32_t                                           UseConstant : 1;                               // 0x0038 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              ConstantX;                                     // 0x003C (0x0004) [0x0000000000000000]               
	float                                              ConstantY;                                     // 0x0040 (0x0004) [0x0000000000000000]               

	bool operator==(const FVector2MaterialInput& other) const { return memcmp(this, &other, sizeof(FVector2MaterialInput)) == 0; }
	bool operator!=(const FVector2MaterialInput& other) const { return !(*this == other); }
	bool operator<(const FVector2MaterialInput& other) const { return memcmp(this, &other, sizeof(FVector2MaterialInput)) < 0; }
};

// ScriptStruct Engine.PhysicsVolume.CheckpointRecord
// 0x0004
struct APhysicsVolume_FCheckpointRecord
{
	uint32_t                                           bActive : 1;                                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const APhysicsVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(APhysicsVolume_FCheckpointRecord)) == 0; }
	bool operator!=(const APhysicsVolume_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const APhysicsVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(APhysicsVolume_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.DistributionVectorConstantCurveParticleParameter.CurveParameterPoint
// 0x0031
struct FCurveParameterPoint
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              InVal;                                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     OutVal;                                        // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     LeaveTangent;                                  // 0x0018 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     ArriveTangent;                                 // 0x0024 (0x000C) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x0030 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FCurveParameterPoint& other) const { return memcmp(this, &other, sizeof(FCurveParameterPoint)) == 0; }
	bool operator!=(const FCurveParameterPoint& other) const { return !(*this == other); }
	bool operator<(const FCurveParameterPoint& other) const { return memcmp(this, &other, sizeof(FCurveParameterPoint)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineProfile
// 0x0078
struct FOnlineProfile
{
	class FString                                      UserId;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlineAccountTier                                 AccountTier;                                   // 0x0010 (0x0001) [0x0000000000000000]               
	int32_t                                            Gamerscore;                                    // 0x0014 (0x0004) [0x0000000000000000]               
	class FString                                      ApplicationDisplayName;                        // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GameDisplayName;                               // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayPictureURL;                             // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ApplicationDisplayPictureResizeURL;            // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PublicGamerPictureURL;                         // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GameDisplayPictureResizeURL;                   // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineProfile& other) const { return memcmp(this, &other, sizeof(FOnlineProfile)) == 0; }
	bool operator!=(const FOnlineProfile& other) const { return !(*this == other); }
	bool operator<(const FOnlineProfile& other) const { return memcmp(this, &other, sizeof(FOnlineProfile)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.UniqueLobbyId
// 0x0009
struct FUniqueLobbyId
{
	uint64_t                                           Uid;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	EOnlinePlatform                                    Platform;                                      // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FUniqueLobbyId& other) const { return memcmp(this, &other, sizeof(FUniqueLobbyId)) == 0; }
	bool operator!=(const FUniqueLobbyId& other) const { return !(*this == other); }
	bool operator<(const FUniqueLobbyId& other) const { return memcmp(this, &other, sizeof(FUniqueLobbyId)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineRegistrant
// 0x0048
struct FOnlineRegistrant
{
	struct FUniqueNetId                                PlayerNetId;                                   // 0x0000 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FOnlineRegistrant& other) const { return memcmp(this, &other, sizeof(FOnlineRegistrant)) == 0; }
	bool operator!=(const FOnlineRegistrant& other) const { return !(*this == other); }
	bool operator<(const FOnlineRegistrant& other) const { return memcmp(this, &other, sizeof(FOnlineRegistrant)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineArbitrationRegistrant
// 0x000C (0x0048 - 0x0054)
struct FOnlineArbitrationRegistrant : FOnlineRegistrant
{
	uint64_t                                           MachineId;                                     // 0x0048 (0x0008) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Trustworthiness;                               // 0x0050 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FOnlineArbitrationRegistrant& other) const { return memcmp(this, &other, sizeof(FOnlineArbitrationRegistrant)) == 0; }
	bool operator!=(const FOnlineArbitrationRegistrant& other) const { return !(*this == other); }
	bool operator<(const FOnlineArbitrationRegistrant& other) const { return memcmp(this, &other, sizeof(FOnlineArbitrationRegistrant)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.NamedSession
// 0x0038
struct FNamedSession
{
	class FName                                        SessionName;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	struct FPointer                                    SessionInfo;                                   // 0x0008 (0x0008) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)
	class UOnlineGameSettings*                         GameSettings;                                  // 0x0010 (0x0008) [0x0000000000000000]               
	class TArray<struct FOnlineRegistrant>             Registrants;                                   // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineArbitrationRegistrant>  ArbitrationRegistrants;                        // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNamedSession& other) const { return memcmp(this, &other, sizeof(FNamedSession)) == 0; }
	bool operator!=(const FNamedSession& other) const { return !(*this == other); }
	bool operator<(const FNamedSession& other) const { return memcmp(this, &other, sizeof(FNamedSession)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.FriendHistoryKey
// 0x0020
struct FFriendHistoryKey
{
	class TArray<uint8_t>                              Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFriendHistoryKey& other) const { return memcmp(this, &other, sizeof(FFriendHistoryKey)) == 0; }
	bool operator!=(const FFriendHistoryKey& other) const { return !(*this == other); }
	bool operator<(const FFriendHistoryKey& other) const { return memcmp(this, &other, sizeof(FFriendHistoryKey)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.NamedInterface
// 0x0010
struct FNamedInterface
{
	class FName                                        InterfaceName;                                 // 0x0000 (0x0008) [0x0000000000000000]               
	class UObject*                                     InterfaceObject;                               // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FNamedInterface& other) const { return memcmp(this, &other, sizeof(FNamedInterface)) == 0; }
	bool operator!=(const FNamedInterface& other) const { return !(*this == other); }
	bool operator<(const FNamedInterface& other) const { return memcmp(this, &other, sizeof(FNamedInterface)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SocialPostImageFlags
// 0x0004
struct FSocialPostImageFlags
{
	uint32_t                                           bIsUserGeneratedImage : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsGameGeneratedImage : 1;                     // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bIsAchievementImage : 1;                       // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bIsMediaImage : 1;                             // 0x0000 (0x0004) [0x0000000000000000] [0x100000008] 

	bool operator==(const FSocialPostImageFlags& other) const { return memcmp(this, &other, sizeof(FSocialPostImageFlags)) == 0; }
	bool operator!=(const FSocialPostImageFlags& other) const { return !(*this == other); }
	bool operator<(const FSocialPostImageFlags& other) const { return memcmp(this, &other, sizeof(FSocialPostImageFlags)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SocialPostImageInfo
// 0x0048
struct FSocialPostImageInfo
{
	struct FSocialPostImageFlags                       Flags;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      MessageText;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      TitleText;                                     // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PictureCaption;                                // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PictureDescription;                            // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSocialPostImageInfo& other) const { return memcmp(this, &other, sizeof(FSocialPostImageInfo)) == 0; }
	bool operator!=(const FSocialPostImageInfo& other) const { return !(*this == other); }
	bool operator<(const FSocialPostImageInfo& other) const { return memcmp(this, &other, sizeof(FSocialPostImageInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SocialPostLinkInfo
// 0x0020 (0x0048 - 0x0068)
struct FSocialPostLinkInfo : FSocialPostImageInfo
{
	class FString                                      TitleURL;                                      // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      PictureURL;                                    // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSocialPostLinkInfo& other) const { return memcmp(this, &other, sizeof(FSocialPostLinkInfo)) == 0; }
	bool operator!=(const FSocialPostLinkInfo& other) const { return !(*this == other); }
	bool operator<(const FSocialPostLinkInfo& other) const { return memcmp(this, &other, sizeof(FSocialPostLinkInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.DownloadedWorkshopData
// 0x00D0
struct FDownloadedWorkshopData
{
	uint64_t                                           ItemID;                                        // 0x0000 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Title;                                         // 0x0008 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      AuthorName;                                    // 0x0018 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	struct FUniqueNetId                                AuthorNetID;                                   // 0x0028 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class UTexture2DDynamic*                           Preview;                                       // 0x0070 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class UTexture*                                    Avatar;                                        // 0x0078 (0x0008) [0x0000000040000000] (CPF_DataBinding)
	class FString                                      Description;                                   // 0x0080 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      PreviewURL;                                    // 0x0090 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      ItemPath;                                      // 0x00A0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Filename;                                      // 0x00B0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      FullPath;                                      // 0x00C0 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)

	bool operator==(const FDownloadedWorkshopData& other) const { return memcmp(this, &other, sizeof(FDownloadedWorkshopData)) == 0; }
	bool operator!=(const FDownloadedWorkshopData& other) const { return !(*this == other); }
	bool operator<(const FDownloadedWorkshopData& other) const { return memcmp(this, &other, sizeof(FDownloadedWorkshopData)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SocialPostPrivileges
// 0x0004
struct FSocialPostPrivileges
{
	uint32_t                                           bCanPostImage : 1;                             // 0x0000 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bCanPostLink : 1;                              // 0x0000 (0x0004) [0x0000000000000002] [0x100000002] (CPF_Const)

	bool operator==(const FSocialPostPrivileges& other) const { return memcmp(this, &other, sizeof(FSocialPostPrivileges)) == 0; }
	bool operator!=(const FSocialPostPrivileges& other) const { return !(*this == other); }
	bool operator<(const FSocialPostPrivileges& other) const { return memcmp(this, &other, sizeof(FSocialPostPrivileges)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlinePartyMember
// 0x0080
struct FOnlinePartyMember
{
	struct FUniqueNetId                                UniqueId;                                      // 0x0000 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      NickName;                                      // 0x0048 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint8_t                                            LocalUserNum;                                  // 0x0058 (0x0001) [0x0000000000000002] (CPF_Const)   
	ENATType                                           NatType;                                       // 0x0059 (0x0001) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TitleId;                                       // 0x005C (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bIsLocal : 1;                                  // 0x0060 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bIsInPartyVoice : 1;                           // 0x0060 (0x0004) [0x0000000000000002] [0x00000002] (CPF_Const)
	uint32_t                                           bIsTalking : 1;                                // 0x0060 (0x0004) [0x0000000000000002] [0x00000004] (CPF_Const)
	uint32_t                                           bIsInGameSession : 1;                          // 0x0060 (0x0004) [0x0000000000000002] [0x00000008] (CPF_Const)
	uint32_t                                           bIsPlayingThisGame : 1;                        // 0x0060 (0x0004) [0x0000000000000002] [0x00000010] (CPF_Const)
	uint64_t                                           SessionId;                                     // 0x0068 (0x0008) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Data1;                                         // 0x0070 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Data2;                                         // 0x0074 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Data3;                                         // 0x0078 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Data4;                                         // 0x007C (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FOnlinePartyMember& other) const { return memcmp(this, &other, sizeof(FOnlinePartyMember)) == 0; }
	bool operator!=(const FOnlinePartyMember& other) const { return !(*this == other); }
	bool operator<(const FOnlinePartyMember& other) const { return memcmp(this, &other, sizeof(FOnlinePartyMember)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SessionMemberInfo
// 0x0049
struct FSessionMemberInfo
{
	struct FUniqueNetId                                PlayerNetId;                                   // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	ESessionMemberStatus                               MemberStatus;                                  // 0x0048 (0x0001) [0x0000000000000000]               

	bool operator==(const FSessionMemberInfo& other) const { return memcmp(this, &other, sizeof(FSessionMemberInfo)) == 0; }
	bool operator!=(const FSessionMemberInfo& other) const { return !(*this == other); }
	bool operator<(const FSessionMemberInfo& other) const { return memcmp(this, &other, sizeof(FSessionMemberInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.MarketplaceInventoryItem
// 0x0068
struct FMarketplaceInventoryItem
{
	class FString                                      ProductID;                                     // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EMediaItemType                                     MediaItemType;                                 // 0x0010 (0x0001) [0x0000000000000002] (CPF_Const)   
	EInventoryItemState                                ItemState;                                     // 0x0011 (0x0001) [0x0000000000000002] (CPF_Const)   
	int32_t                                            ConsumableBalance;                             // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TitleId;                                       // 0x0018 (0x0004) [0x0000000000000002] (CPF_Const)   
	class TArray<class FString>                        ContainerIds;                                  // 0x0020 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint64_t                                           StartDate;                                     // 0x0030 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           EndDate;                                       // 0x0038 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           RightsObtainedDate;                            // 0x0040 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      URL;                                           // 0x0048 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ConsumableUrl;                                 // 0x0058 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FMarketplaceInventoryItem& other) const { return memcmp(this, &other, sizeof(FMarketplaceInventoryItem)) == 0; }
	bool operator!=(const FMarketplaceInventoryItem& other) const { return !(*this == other); }
	bool operator<(const FMarketplaceInventoryItem& other) const { return memcmp(this, &other, sizeof(FMarketplaceInventoryItem)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.MarketplaceProductImage
// 0x0048
struct FMarketplaceProductImage
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            Height;                                        // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Width;                                         // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      Purpose;                                       // 0x0018 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<class FString>                        Purposes;                                      // 0x0028 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ResizeURL;                                     // 0x0038 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FMarketplaceProductImage& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductImage)) == 0; }
	bool operator!=(const FMarketplaceProductImage& other) const { return !(*this == other); }
	bool operator<(const FMarketplaceProductImage& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductImage)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.MarketplaceProductAvailability
// 0x00A0
struct FMarketplaceProductAvailability
{
	class TArray<class FString>                        AcceptablePaymentInstrumentTypes;              // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ContentId;                                     // 0x0020 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      CurrencyCode;                                  // 0x0030 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      DisplayListPrice;                              // 0x0040 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      DisplayPrice;                                  // 0x0050 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      DistributionType;                              // 0x0060 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint32_t                                           bIsPurchasable : 1;                            // 0x0070 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	float                                              ListPrice;                                     // 0x0074 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              Price;                                         // 0x0078 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      PromotionalText;                               // 0x0080 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      SignedOffer;                                   // 0x0090 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FMarketplaceProductAvailability& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductAvailability)) == 0; }
	bool operator!=(const FMarketplaceProductAvailability& other) const { return !(*this == other); }
	bool operator<(const FMarketplaceProductAvailability& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductAvailability)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.MarketplaceProductDetails
// 0x0090
struct FMarketplaceProductDetails
{
	class FString                                      StandardId;                                    // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EMediaItemType                                     MediaItemType;                                 // 0x0010 (0x0001) [0x0000000000000002] (CPF_Const)   
	class FString                                      ProductName;                                   // 0x0018 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ProductID;                                     // 0x0028 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint64_t                                           ReleaseDate;                                   // 0x0038 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      SandboxId;                                     // 0x0040 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            TitleId;                                       // 0x0050 (0x0004) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FMarketplaceProductImage>      Images;                                        // 0x0058 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EOnlineEnumerationReadState                        DetailsReadState;                              // 0x0068 (0x0001) [0x0000000000000000]               
	class TArray<struct FMarketplaceProductAvailability> Availabilities;                                // 0x0070 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ProductDescription;                            // 0x0080 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FMarketplaceProductDetails& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductDetails)) == 0; }
	bool operator!=(const FMarketplaceProductDetails& other) const { return !(*this == other); }
	bool operator<(const FMarketplaceProductDetails& other) const { return memcmp(this, &other, sizeof(FMarketplaceProductDetails)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.AchievementReward
// 0x0031
struct FAchievementReward
{
	class FString                                      RewardName;                                    // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      Data;                                          // 0x0020 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EAchievementRewardType                             RewardType;                                    // 0x0030 (0x0001) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAchievementReward& other) const { return memcmp(this, &other, sizeof(FAchievementReward)) == 0; }
	bool operator!=(const FAchievementReward& other) const { return !(*this == other); }
	bool operator<(const FAchievementReward& other) const { return memcmp(this, &other, sizeof(FAchievementReward)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.AchievementMediaAsset
// 0x0028
struct FAchievementMediaAsset
{
	class FString                                      AssetName;                                     // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EAchievementMediaAssetType                         AssetType;                                     // 0x0010 (0x0001) [0x0000000000000002] (CPF_Const)   
	class FString                                      AssetURL;                                      // 0x0018 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FAchievementMediaAsset& other) const { return memcmp(this, &other, sizeof(FAchievementMediaAsset)) == 0; }
	bool operator!=(const FAchievementMediaAsset& other) const { return !(*this == other); }
	bool operator<(const FAchievementMediaAsset& other) const { return memcmp(this, &other, sizeof(FAchievementMediaAsset)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.AchievementTitleAssociation
// 0x0014
struct FAchievementTitleAssociation
{
	class FString                                      LocalizedTitleName;                            // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            TitleId;                                       // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAchievementTitleAssociation& other) const { return memcmp(this, &other, sizeof(FAchievementTitleAssociation)) == 0; }
	bool operator!=(const FAchievementTitleAssociation& other) const { return !(*this == other); }
	bool operator<(const FAchievementTitleAssociation& other) const { return memcmp(this, &other, sizeof(FAchievementTitleAssociation)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.AchievementDetails
// 0x00F8
struct FAchievementDetails
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      StringId;                                      // 0x0008 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      AchievementName;                               // 0x0018 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      Description;                                   // 0x0028 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      HowTo;                                         // 0x0038 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class USurface*                                    Image;                                         // 0x0048 (0x0008) [0x0000000000000000]               
	uint8_t                                            MonthEarned;                                   // 0x0050 (0x0001) [0x0000000000000002] (CPF_Const)   
	uint8_t                                            DayEarned;                                     // 0x0051 (0x0001) [0x0000000000000002] (CPF_Const)   
	uint8_t                                            YearEarned;                                    // 0x0052 (0x0001) [0x0000000000000002] (CPF_Const)   
	uint8_t                                            DayOfWeekEarned;                               // 0x0053 (0x0001) [0x0000000000000002] (CPF_Const)   
	int32_t                                            GamerPoints;                                   // 0x0054 (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bIsSecret : 1;                                 // 0x0058 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	uint32_t                                           bWasAchievedOnline : 1;                        // 0x0058 (0x0004) [0x0000000000000002] [0x00000002] (CPF_Const)
	uint32_t                                           bWasAchievedOffline : 1;                       // 0x0058 (0x0004) [0x0000000000000002] [0x00000004] (CPF_Const)
	EAchievementUnlockType                             UnlockType;                                    // 0x005C (0x0001) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           ChallengeWindowBegin;                          // 0x0060 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           ChallengeWindowEnd;                            // 0x0068 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      DeepLink;                                      // 0x0070 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	uint64_t                                           EstimatedUnlockTime;                           // 0x0080 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bIsRevoked : 1;                                // 0x0088 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	EAchievementParticipationType                      ParticipationType;                             // 0x008C (0x0001) [0x0000000000000002] (CPF_Const)   
	class TArray<class FString>                        PlatformsAvailableOn;                          // 0x0090 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	EAchievementProgressState                          ProgressState;                                 // 0x00A0 (0x0001) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FAchievementReward>            Rewards;                                       // 0x00A8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FAchievementMediaAsset>        MediaAssets;                                   // 0x00B8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ProductID;                                     // 0x00C8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ServiceConfigurationID;                        // 0x00D8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FAchievementTitleAssociation>  TitleAssociations;                             // 0x00E8 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FAchievementDetails& other) const { return memcmp(this, &other, sizeof(FAchievementDetails)) == 0; }
	bool operator!=(const FAchievementDetails& other) const { return !(*this == other); }
	bool operator<(const FAchievementDetails& other) const { return memcmp(this, &other, sizeof(FAchievementDetails)) < 0; }
};

// ScriptStruct Engine.Settings.SettingsData
// 0x0010
struct FSettingsData
{
	ESettingsDataType                                  Type;                                          // 0x0000 (0x0001) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Value1;                                        // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   
	struct FPointer                                    Value2;                                        // 0x0008 (0x0008) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FSettingsData& other) const { return memcmp(this, &other, sizeof(FSettingsData)) == 0; }
	bool operator!=(const FSettingsData& other) const { return !(*this == other); }
	bool operator<(const FSettingsData& other) const { return memcmp(this, &other, sizeof(FSettingsData)) < 0; }
};

// ScriptStruct Engine.Settings.SettingsProperty
// 0x0019
struct FSettingsProperty
{
	int32_t                                            PropertyId;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	struct FSettingsData                               Data;                                          // 0x0008 (0x0010) [0x0000000000000000]               
	EOnlineDataAdvertisementType                       AdvertisementType;                             // 0x0018 (0x0001) [0x0000000000000000]               

	bool operator==(const FSettingsProperty& other) const { return memcmp(this, &other, sizeof(FSettingsProperty)) == 0; }
	bool operator!=(const FSettingsProperty& other) const { return !(*this == other); }
	bool operator<(const FSettingsProperty& other) const { return memcmp(this, &other, sizeof(FSettingsProperty)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.CommunityContentMetadata
// 0x0038
struct FCommunityContentMetadata
{
	int32_t                                            ContentType;                                   // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FSettingsProperty>             MetadataItems;                                 // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      RemotePath;                                    // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayName;                                   // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCommunityContentMetadata& other) const { return memcmp(this, &other, sizeof(FCommunityContentMetadata)) == 0; }
	bool operator!=(const FCommunityContentMetadata& other) const { return !(*this == other); }
	bool operator<(const FCommunityContentMetadata& other) const { return memcmp(this, &other, sizeof(FCommunityContentMetadata)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.CommunityContentFile
// 0x0090
struct FCommunityContentFile
{
	int32_t                                            ContentId;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      RemoteContentPath;                             // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            FileId;                                        // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            ContentType;                                   // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            FileSize;                                      // 0x0020 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                Owner;                                         // 0x0028 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            DownloadCount;                                 // 0x0070 (0x0004) [0x0000000000000000]               
	float                                              AverageRating;                                 // 0x0074 (0x0004) [0x0000000000000000]               
	int32_t                                            RatingCount;                                   // 0x0078 (0x0004) [0x0000000000000000]               
	int32_t                                            LastRatingGiven;                               // 0x007C (0x0004) [0x0000000000000000]               
	class FString                                      LocalFilePath;                                 // 0x0080 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCommunityContentFile& other) const { return memcmp(this, &other, sizeof(FCommunityContentFile)) == 0; }
	bool operator!=(const FCommunityContentFile& other) const { return !(*this == other); }
	bool operator<(const FCommunityContentFile& other) const { return memcmp(this, &other, sizeof(FCommunityContentFile)) < 0; }
};

// ScriptStruct Engine.Settings.LocalizedStringSetting
// 0x0009
struct FLocalizedStringSetting
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            ValueIndex;                                    // 0x0004 (0x0004) [0x0000000000000000]               
	EOnlineDataAdvertisementType                       AdvertisementType;                             // 0x0008 (0x0001) [0x0000000000000000]               

	bool operator==(const FLocalizedStringSetting& other) const { return memcmp(this, &other, sizeof(FLocalizedStringSetting)) == 0; }
	bool operator!=(const FLocalizedStringSetting& other) const { return !(*this == other); }
	bool operator<(const FLocalizedStringSetting& other) const { return memcmp(this, &other, sizeof(FLocalizedStringSetting)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.TitleFile
// 0x0028
struct FTitleFile
{
	class FString                                      Filename;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlineEnumerationReadState                        AsyncState;                                    // 0x0010 (0x0001) [0x0000000000000000]               
	class TArray<uint8_t>                              Data;                                          // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FTitleFile& other) const { return memcmp(this, &other, sizeof(FTitleFile)) == 0; }
	bool operator!=(const FTitleFile& other) const { return !(*this == other); }
	bool operator<(const FTitleFile& other) const { return memcmp(this, &other, sizeof(FTitleFile)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.EmsFile
// 0x0034
struct FEmsFile
{
	class FString                                      Hash;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DLName;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Filename;                                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            FileSize;                                      // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FEmsFile& other) const { return memcmp(this, &other, sizeof(FEmsFile)) == 0; }
	bool operator!=(const FEmsFile& other) const { return !(*this == other); }
	bool operator<(const FEmsFile& other) const { return memcmp(this, &other, sizeof(FEmsFile)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.NamedInterfaceDef
// 0x0018
struct FNamedInterfaceDef
{
	class FName                                        InterfaceName;                                 // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      InterfaceClassName;                            // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNamedInterfaceDef& other) const { return memcmp(this, &other, sizeof(FNamedInterfaceDef)) == 0; }
	bool operator!=(const FNamedInterfaceDef& other) const { return !(*this == other); }
	bool operator<(const FNamedInterfaceDef& other) const { return memcmp(this, &other, sizeof(FNamedInterfaceDef)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineFriendMessage
// 0x0070
struct FOnlineFriendMessage
{
	struct FUniqueNetId                                SendingPlayerId;                               // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SendingPlayerNick;                             // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsFriendInvite : 1;                           // 0x0058 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsGameInvite : 1;                             // 0x0058 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bWasAccepted : 1;                              // 0x0058 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bWasDenied : 1;                                // 0x0058 (0x0004) [0x0000000000000000] [0x00000008] 
	class FString                                      Message;                                       // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineFriendMessage& other) const { return memcmp(this, &other, sizeof(FOnlineFriendMessage)) == 0; }
	bool operator!=(const FOnlineFriendMessage& other) const { return !(*this == other); }
	bool operator<(const FOnlineFriendMessage& other) const { return memcmp(this, &other, sizeof(FOnlineFriendMessage)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.RemoteTalker
// 0x0050
struct FRemoteTalker
{
	struct FUniqueNetId                                TalkerId;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              LastNotificationTime;                          // 0x0048 (0x0004) [0x0000000000000000]               
	uint32_t                                           bWasTalking : 1;                               // 0x004C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsTalking : 1;                                // 0x004C (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bIsRegistered : 1;                             // 0x004C (0x0004) [0x0000000000000000] [0x100000004] 

	bool operator==(const FRemoteTalker& other) const { return memcmp(this, &other, sizeof(FRemoteTalker)) == 0; }
	bool operator!=(const FRemoteTalker& other) const { return !(*this == other); }
	bool operator<(const FRemoteTalker& other) const { return memcmp(this, &other, sizeof(FRemoteTalker)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.LocalTalker
// 0x004C
struct FLocalTalker
{
	struct FUniqueNetId                                TalkerId;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHasVoice : 1;                                 // 0x0048 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bHasNetworkedVoice : 1;                        // 0x0048 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bIsRecognizingSpeech : 1;                      // 0x0048 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bWasTalking : 1;                               // 0x0048 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bIsTalking : 1;                                // 0x0048 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bIsRegistered : 1;                             // 0x0048 (0x0004) [0x0000000000000000] [0x100000020] 

	bool operator==(const FLocalTalker& other) const { return memcmp(this, &other, sizeof(FLocalTalker)) == 0; }
	bool operator!=(const FLocalTalker& other) const { return !(*this == other); }
	bool operator<(const FLocalTalker& other) const { return memcmp(this, &other, sizeof(FLocalTalker)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlinePlayerScore
// 0x0050
struct FOnlinePlayerScore
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TeamID;                                        // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            Score;                                         // 0x004C (0x0004) [0x0000000000000000]               

	bool operator==(const FOnlinePlayerScore& other) const { return memcmp(this, &other, sizeof(FOnlinePlayerScore)) == 0; }
	bool operator!=(const FOnlinePlayerScore& other) const { return !(*this == other); }
	bool operator<(const FOnlinePlayerScore& other) const { return memcmp(this, &other, sizeof(FOnlinePlayerScore)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SpeechRecognizedWord
// 0x001C
struct FSpeechRecognizedWord
{
	int32_t                                            WordId;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      WordText;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              Confidence;                                    // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FSpeechRecognizedWord& other) const { return memcmp(this, &other, sizeof(FSpeechRecognizedWord)) == 0; }
	bool operator!=(const FSpeechRecognizedWord& other) const { return !(*this == other); }
	bool operator<(const FSpeechRecognizedWord& other) const { return memcmp(this, &other, sizeof(FSpeechRecognizedWord)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineContent
// 0x0060
struct FOnlineContent
{
	EOnlineContentType                                 ContentType;                                   // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            UserIndex;                                     // 0x0001 (0x0001) [0x0000000000000000]               
	uint32_t                                           bIsCorrupt : 1;                                // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	int32_t                                            DeviceID;                                      // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            LicenseMask;                                   // 0x000C (0x0004) [0x0000000000000000]               
	class FString                                      FriendlyName;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Filename;                                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ContentPath;                                   // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        ContentPackages;                               // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        ContentFiles;                                  // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineContent& other) const { return memcmp(this, &other, sizeof(FOnlineContent)) == 0; }
	bool operator!=(const FOnlineContent& other) const { return !(*this == other); }
	bool operator<(const FOnlineContent& other) const { return memcmp(this, &other, sizeof(FOnlineContent)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineCrossTitleContent
// 0x0004 (0x0060 - 0x0064)
struct FOnlineCrossTitleContent : FOnlineContent
{
	int32_t                                            TitleId;                                       // 0x0060 (0x0004) [0x0000000000000000]               

	bool operator==(const FOnlineCrossTitleContent& other) const { return memcmp(this, &other, sizeof(FOnlineCrossTitleContent)) == 0; }
	bool operator!=(const FOnlineCrossTitleContent& other) const { return !(*this == other); }
	bool operator<(const FOnlineCrossTitleContent& other) const { return memcmp(this, &other, sizeof(FOnlineCrossTitleContent)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineUser
// 0x0078
struct FOnlineUser
{
	struct FUniqueNetId                                UniqueId;                                      // 0x0000 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      NickName;                                      // 0x0048 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<class FString>                        AttrName;                                      // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        AttrValue;                                     // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineUser& other) const { return memcmp(this, &other, sizeof(FOnlineUser)) == 0; }
	bool operator!=(const FOnlineUser& other) const { return !(*this == other); }
	bool operator<(const FOnlineUser& other) const { return memcmp(this, &other, sizeof(FOnlineUser)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.OnlineFriend
// 0x009C (0x0078 - 0x0114)
struct FOnlineFriend : FOnlineUser
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0078 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint64_t                                           SessionId;                                     // 0x00C0 (0x0008) [0x0000000000000000]               
	EOnlinePlatform                                    PlatformOverride;                              // 0x00C8 (0x0001) [0x0000000000000000]               
	class FString                                      PlayerName;                                    // 0x00D0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      SecondaryPlayerName;                           // 0x00E0 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlinePlatform                                    SecondaryPlatform;                             // 0x00F0 (0x0001) [0x0000000000000000]               
	class FString                                      PresenceInfo;                                  // 0x00F8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlineFriendState                                 FriendState;                                   // 0x0108 (0x0001) [0x0000000000000000]               
	uint32_t                                           bIsOnline : 1;                                 // 0x010C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsPlaying : 1;                                // 0x010C (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bIsPlayingThisGame : 1;                        // 0x010C (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bIsJoinable : 1;                               // 0x010C (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bHasVoiceSupport : 1;                          // 0x010C (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bHaveInvited : 1;                              // 0x010C (0x0004) [0x0000000000000000] [0x00000020] 
	uint32_t                                           bHasInvitedYou : 1;                            // 0x010C (0x0004) [0x0000000000000000] [0x00000040] 
	int32_t                                            GroupId;                                       // 0x0110 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FOnlineFriend& other) const { return memcmp(this, &other, sizeof(FOnlineFriend)) == 0; }
	bool operator!=(const FOnlineFriend& other) const { return !(*this == other); }
	bool operator<(const FOnlineFriend& other) const { return memcmp(this, &other, sizeof(FOnlineFriend)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.FriendsQuery
// 0x004C
struct FFriendsQuery
{
	struct FUniqueNetId                                UniqueId;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsFriend : 1;                                 // 0x0048 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FFriendsQuery& other) const { return memcmp(this, &other, sizeof(FFriendsQuery)) == 0; }
	bool operator!=(const FFriendsQuery& other) const { return !(*this == other); }
	bool operator<(const FFriendsQuery& other) const { return memcmp(this, &other, sizeof(FFriendsQuery)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.WordFilterResult
// 0x0038
struct FWordFilterResult
{
	EWordFilterCensorship                              Censorship;                                    // 0x0000 (0x0001) [0x0000000000000000]               
	class FString                                      Original;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Sanitized;                                     // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      ErrorMessage;                                  // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FWordFilterResult& other) const { return memcmp(this, &other, sizeof(FWordFilterResult)) == 0; }
	bool operator!=(const FWordFilterResult& other) const { return !(*this == other); }
	bool operator<(const FWordFilterResult& other) const { return memcmp(this, &other, sizeof(FWordFilterResult)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.EpicDLCInfo
// 0x0018
struct FEpicDLCInfo
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        Value;                                         // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FEpicDLCInfo& other) const { return memcmp(this, &other, sizeof(FEpicDLCInfo)) == 0; }
	bool operator!=(const FEpicDLCInfo& other) const { return !(*this == other); }
	bool operator<(const FEpicDLCInfo& other) const { return memcmp(this, &other, sizeof(FEpicDLCInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SwitchDLCInfo
// 0x0018
struct FSwitchDLCInfo
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        Value;                                         // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FSwitchDLCInfo& other) const { return memcmp(this, &other, sizeof(FSwitchDLCInfo)) == 0; }
	bool operator!=(const FSwitchDLCInfo& other) const { return !(*this == other); }
	bool operator<(const FSwitchDLCInfo& other) const { return memcmp(this, &other, sizeof(FSwitchDLCInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.XboxOneDLCInfo
// 0x001C
struct FXboxOneDLCInfo
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        Value;                                         // 0x0010 (0x0008) [0x0000000000000000]               
	uint32_t                                           bDiscUnlock : 1;                               // 0x0018 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FXboxOneDLCInfo& other) const { return memcmp(this, &other, sizeof(FXboxOneDLCInfo)) == 0; }
	bool operator!=(const FXboxOneDLCInfo& other) const { return !(*this == other); }
	bool operator<(const FXboxOneDLCInfo& other) const { return memcmp(this, &other, sizeof(FXboxOneDLCInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.PS4DLCInfo
// 0x0018
struct FPS4DLCInfo
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        Value;                                         // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FPS4DLCInfo& other) const { return memcmp(this, &other, sizeof(FPS4DLCInfo)) == 0; }
	bool operator!=(const FPS4DLCInfo& other) const { return !(*this == other); }
	bool operator<(const FPS4DLCInfo& other) const { return memcmp(this, &other, sizeof(FPS4DLCInfo)) < 0; }
};

// ScriptStruct Engine.OnlineSubsystem.SteamDLCInfo
// 0x0010
struct FSteamDLCInfo
{
	uint64_t                                           AppID;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        Value;                                         // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FSteamDLCInfo& other) const { return memcmp(this, &other, sizeof(FSteamDLCInfo)) == 0; }
	bool operator!=(const FSteamDLCInfo& other) const { return !(*this == other); }
	bool operator<(const FSteamDLCInfo& other) const { return memcmp(this, &other, sizeof(FSteamDLCInfo)) < 0; }
};

// ScriptStruct Engine.DynamicBlockingVolume.CheckpointRecord
// 0x001C
struct ADynamicBlockingVolume_FCheckpointRecord
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000000]               
	uint32_t                                           bCollideActors : 1;                            // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bBlockActors : 1;                              // 0x0018 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bNeedsReplication : 1;                         // 0x0018 (0x0004) [0x0000000000000000] [0x00000004] 

	bool operator==(const ADynamicBlockingVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ADynamicBlockingVolume_FCheckpointRecord)) == 0; }
	bool operator!=(const ADynamicBlockingVolume_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ADynamicBlockingVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ADynamicBlockingVolume_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ViewParticleEmitterInstanceMotionBlurInfo
// 0x0050
struct FViewParticleEmitterInstanceMotionBlurInfo
{
	struct FMap_Mirror                                 EmitterInstanceMBInfoMap;                      // 0x0000 (0x0050) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FViewParticleEmitterInstanceMotionBlurInfo& other) const { return memcmp(this, &other, sizeof(FViewParticleEmitterInstanceMotionBlurInfo)) == 0; }
	bool operator!=(const FViewParticleEmitterInstanceMotionBlurInfo& other) const { return !(*this == other); }
	bool operator<(const FViewParticleEmitterInstanceMotionBlurInfo& other) const { return memcmp(this, &other, sizeof(FViewParticleEmitterInstanceMotionBlurInfo)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleSysParam
// 0x0048
struct FParticleSysParam
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EParticleSysParamType                              ParamType;                                     // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              Scalar;                                        // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Scalar_Low;                                    // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Vector;                                        // 0x0014 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Vector_Low;                                    // 0x0020 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FColor                                      Color;                                         // 0x002C (0x0004) [0x0000000000000001] (CPF_Edit)    
	class AActor*                                      Actor;                                         // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInterface*                          Material;                                      // 0x0038 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UStaticMesh*                                 Mesh;                                          // 0x0040 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FParticleSysParam& other) const { return memcmp(this, &other, sizeof(FParticleSysParam)) == 0; }
	bool operator!=(const FParticleSysParam& other) const { return !(*this == other); }
	bool operator<(const FParticleSysParam& other) const { return memcmp(this, &other, sizeof(FParticleSysParam)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventData
// 0x0034
struct FParticleEventData
{
	int32_t                                            Type;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        EventName;                                     // 0x0004 (0x0008) [0x0000000000000000]               
	float                                              EmitterTime;                                   // 0x000C (0x0004) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     Direction;                                     // 0x001C (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x0028 (0x000C) [0x0000000000000000]               

	bool operator==(const FParticleEventData& other) const { return memcmp(this, &other, sizeof(FParticleEventData)) == 0; }
	bool operator!=(const FParticleEventData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventData& other) const { return memcmp(this, &other, sizeof(FParticleEventData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventSpawnData
// 0x0000 (0x0034 - 0x0034)
struct FParticleEventSpawnData : FParticleEventData
{

	bool operator==(const FParticleEventSpawnData& other) const { return memcmp(this, &other, sizeof(FParticleEventSpawnData)) == 0; }
	bool operator!=(const FParticleEventSpawnData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventSpawnData& other) const { return memcmp(this, &other, sizeof(FParticleEventSpawnData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventDeathData
// 0x0004 (0x0034 - 0x0038)
struct FParticleEventDeathData : FParticleEventData
{
	float                                              ParticleTime;                                  // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FParticleEventDeathData& other) const { return memcmp(this, &other, sizeof(FParticleEventDeathData)) == 0; }
	bool operator!=(const FParticleEventDeathData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventDeathData& other) const { return memcmp(this, &other, sizeof(FParticleEventDeathData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventCollideData
// 0x0020 (0x0034 - 0x0054)
struct FParticleEventCollideData : FParticleEventData
{
	float                                              ParticleTime;                                  // 0x0034 (0x0004) [0x0000000000000000]               
	struct FVector                                     Normal;                                        // 0x0038 (0x000C) [0x0000000000000000]               
	float                                              Time;                                          // 0x0044 (0x0004) [0x0000000000000000]               
	int32_t                                            Item;                                          // 0x0048 (0x0004) [0x0000000000000000]               
	class FName                                        BoneName;                                      // 0x004C (0x0008) [0x0000000000000000]               

	bool operator==(const FParticleEventCollideData& other) const { return memcmp(this, &other, sizeof(FParticleEventCollideData)) == 0; }
	bool operator!=(const FParticleEventCollideData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventCollideData& other) const { return memcmp(this, &other, sizeof(FParticleEventCollideData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventAttractorCollideData
// 0x0000 (0x0054 - 0x0054)
struct FParticleEventAttractorCollideData : FParticleEventCollideData
{

	bool operator==(const FParticleEventAttractorCollideData& other) const { return memcmp(this, &other, sizeof(FParticleEventAttractorCollideData)) == 0; }
	bool operator!=(const FParticleEventAttractorCollideData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventAttractorCollideData& other) const { return memcmp(this, &other, sizeof(FParticleEventAttractorCollideData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEventKismetData
// 0x0010 (0x0034 - 0x0044)
struct FParticleEventKismetData : FParticleEventData
{
	uint32_t                                           UsePSysCompLocation : 1;                       // 0x0034 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Normal;                                        // 0x0038 (0x000C) [0x0000000000000000]               

	bool operator==(const FParticleEventKismetData& other) const { return memcmp(this, &other, sizeof(FParticleEventKismetData)) == 0; }
	bool operator!=(const FParticleEventKismetData& other) const { return !(*this == other); }
	bool operator<(const FParticleEventKismetData& other) const { return memcmp(this, &other, sizeof(FParticleEventKismetData)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEmitterInstanceMotionBlurInfo
// 0x0050
struct FParticleEmitterInstanceMotionBlurInfo
{
	struct FMap_Mirror                                 ParticleMBInfoMap;                             // 0x0000 (0x0050) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FParticleEmitterInstanceMotionBlurInfo& other) const { return memcmp(this, &other, sizeof(FParticleEmitterInstanceMotionBlurInfo)) == 0; }
	bool operator!=(const FParticleEmitterInstanceMotionBlurInfo& other) const { return !(*this == other); }
	bool operator<(const FParticleEmitterInstanceMotionBlurInfo& other) const { return memcmp(this, &other, sizeof(FParticleEmitterInstanceMotionBlurInfo)) < 0; }
};

// ScriptStruct Engine.ParticleSystemComponent.ParticleEmitterInstance
// 0x0000
struct FParticleEmitterInstance
{

	bool operator==(const FParticleEmitterInstance& other) const { return memcmp(this, &other, sizeof(FParticleEmitterInstance)) == 0; }
	bool operator!=(const FParticleEmitterInstance& other) const { return !(*this == other); }
	bool operator<(const FParticleEmitterInstance& other) const { return memcmp(this, &other, sizeof(FParticleEmitterInstance)) < 0; }
};

// ScriptStruct Engine.Emitter.CheckpointRecord
// 0x0004
struct AEmitter_FCheckpointRecord
{
	uint32_t                                           bIsActive : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const AEmitter_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AEmitter_FCheckpointRecord)) == 0; }
	bool operator!=(const AEmitter_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const AEmitter_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AEmitter_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.EmitterPool.EmitterBaseInfo
// 0x002C
struct FEmitterBaseInfo
{
	class UParticleSystemComponent*                    PSC;                                           // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	class AActor*                                      Base;                                          // 0x0008 (0x0008) [0x0000000000000000]               
	struct FVector                                     RelativeLocation;                              // 0x0010 (0x000C) [0x0000000000000000]               
	struct FRotator                                    RelativeRotation;                              // 0x001C (0x000C) [0x0000000000000000]               
	uint32_t                                           bInheritBaseScale : 1;                         // 0x0028 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FEmitterBaseInfo& other) const { return memcmp(this, &other, sizeof(FEmitterBaseInfo)) == 0; }
	bool operator!=(const FEmitterBaseInfo& other) const { return !(*this == other); }
	bool operator<(const FEmitterBaseInfo& other) const { return memcmp(this, &other, sizeof(FEmitterBaseInfo)) < 0; }
};

// ScriptStruct Engine.Engine.StatColorMapEntry
// 0x0008
struct FStatColorMapEntry
{
	float                                              In;                                            // 0x0000 (0x0004) [0x0000000000044000] (CPF_Config | CPF_GlobalConfig)
	struct FColor                                      Out;                                           // 0x0004 (0x0004) [0x0000000000044000] (CPF_Config | CPF_GlobalConfig)

	bool operator==(const FStatColorMapEntry& other) const { return memcmp(this, &other, sizeof(FStatColorMapEntry)) == 0; }
	bool operator!=(const FStatColorMapEntry& other) const { return !(*this == other); }
	bool operator<(const FStatColorMapEntry& other) const { return memcmp(this, &other, sizeof(FStatColorMapEntry)) < 0; }
};

// ScriptStruct Engine.Engine.StatColorMapping
// 0x0024
struct FStatColorMapping
{
	class FString                                      StatName;                                      // 0x0000 (0x0010) [0x0000000000444000] (CPF_Config | CPF_GlobalConfig | CPF_NeedCtorLink)
	class TArray<struct FStatColorMapEntry>            ColorMap;                                      // 0x0010 (0x0010) [0x0000000000444000] (CPF_Config | CPF_GlobalConfig | CPF_NeedCtorLink)
	uint32_t                                           DisableBlend : 1;                              // 0x0020 (0x0004) [0x0000000000044000] [0x100000001] (CPF_Config | CPF_GlobalConfig)

	bool operator==(const FStatColorMapping& other) const { return memcmp(this, &other, sizeof(FStatColorMapping)) == 0; }
	bool operator!=(const FStatColorMapping& other) const { return !(*this == other); }
	bool operator<(const FStatColorMapping& other) const { return memcmp(this, &other, sizeof(FStatColorMapping)) < 0; }
};

// ScriptStruct Engine.Engine.DropNoteInfo
// 0x0028
struct FDropNoteInfo
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000000]               
	class FString                                      Comment;                                       // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FDropNoteInfo& other) const { return memcmp(this, &other, sizeof(FDropNoteInfo)) == 0; }
	bool operator!=(const FDropNoteInfo& other) const { return !(*this == other); }
	bool operator<(const FDropNoteInfo& other) const { return memcmp(this, &other, sizeof(FDropNoteInfo)) < 0; }
};

// ScriptStruct Engine.EngineTypes.PrimitiveMaterialRef
// 0x000C
struct FPrimitiveMaterialRef
{
	class UPrimitiveComponent*                         Primitive;                                     // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	int32_t                                            MaterialIndex;                                 // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPrimitiveMaterialRef& other) const { return memcmp(this, &other, sizeof(FPrimitiveMaterialRef)) == 0; }
	bool operator!=(const FPrimitiveMaterialRef& other) const { return !(*this == other); }
	bool operator<(const FPrimitiveMaterialRef& other) const { return memcmp(this, &other, sizeof(FPrimitiveMaterialRef)) < 0; }
};

// ScriptStruct Engine.EngineTypes.PostProcessMaterialRef
// 0x0008
struct FPostProcessMaterialRef
{
	class UMaterialEffect*                             Effect;                                        // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FPostProcessMaterialRef& other) const { return memcmp(this, &other, sizeof(FPostProcessMaterialRef)) == 0; }
	bool operator!=(const FPostProcessMaterialRef& other) const { return !(*this == other); }
	bool operator<(const FPostProcessMaterialRef& other) const { return memcmp(this, &other, sizeof(FPostProcessMaterialRef)) < 0; }
};

// ScriptStruct Engine.EngineTypes.MaterialReferenceList
// 0x0028
struct FMaterialReferenceList
{
	class UMaterialInterface*                          TargetMaterial;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FPrimitiveMaterialRef>         AffectedMaterialRefs;                          // 0x0008 (0x0010) [0x0000020000480000] (CPF_Component | CPF_NeedCtorLink | CPF_EditHide)
	class TArray<struct FPostProcessMaterialRef>       AffectedPPChainMaterialRefs;                   // 0x0018 (0x0010) [0x0000020000400000] (CPF_NeedCtorLink | CPF_EditHide)

	bool operator==(const FMaterialReferenceList& other) const { return memcmp(this, &other, sizeof(FMaterialReferenceList)) == 0; }
	bool operator!=(const FMaterialReferenceList& other) const { return !(*this == other); }
	bool operator<(const FMaterialReferenceList& other) const { return memcmp(this, &other, sizeof(FMaterialReferenceList)) < 0; }
};

// ScriptStruct Engine.EngineTypes.VelocityObstacleStat
// 0x0020
struct FVelocityObstacleStat
{
	struct FVector                                     Position;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     Velocity;                                      // 0x000C (0x000C) [0x0000000000000000]               
	float                                              Radius;                                        // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            Priority;                                      // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FVelocityObstacleStat& other) const { return memcmp(this, &other, sizeof(FVelocityObstacleStat)) == 0; }
	bool operator!=(const FVelocityObstacleStat& other) const { return !(*this == other); }
	bool operator<(const FVelocityObstacleStat& other) const { return memcmp(this, &other, sizeof(FVelocityObstacleStat)) < 0; }
};

// ScriptStruct Engine.FacebookIntegration.FacebookFriend
// 0x0020
struct FFacebookFriend
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Id;                                            // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFacebookFriend& other) const { return memcmp(this, &other, sizeof(FFacebookFriend)) == 0; }
	bool operator!=(const FFacebookFriend& other) const { return !(*this == other); }
	bool operator<(const FFacebookFriend& other) const { return memcmp(this, &other, sizeof(FFacebookFriend)) < 0; }
};

// ScriptStruct Engine.FogVolumeDensityInfo.CheckpointRecord
// 0x0004
struct AFogVolumeDensityInfo_FCheckpointRecord
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const AFogVolumeDensityInfo_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AFogVolumeDensityInfo_FCheckpointRecord)) == 0; }
	bool operator!=(const AFogVolumeDensityInfo_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const AFogVolumeDensityInfo_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AFogVolumeDensityInfo_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.FontImportOptions.FontImportOptionsData
// 0x00AC
struct FFontImportOptionsData
{
	class FString                                      FontName;                                      // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	float                                              Height;                                        // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnableAntialiasing : 1;                       // 0x0014 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bEnableBold : 1;                               // 0x0014 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bEnableItalic : 1;                             // 0x0014 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bEnableUnderline : 1;                          // 0x0014 (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           bAlphaOnly : 1;                                // 0x0014 (0x0004) [0x0000000000000001] [0x00000010] (CPF_Edit)
	EFontImportCharacterSet                            CharacterSet;                                  // 0x0018 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class FString                                      Chars;                                         // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      UnicodeRange;                                  // 0x0030 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      CharsFilePath;                                 // 0x0040 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      CharsFileWildcard;                             // 0x0050 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	uint32_t                                           bCreatePrintableOnly : 1;                      // 0x0060 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bIncludeASCIIRange : 1;                        // 0x0060 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	struct FLinearColor                                ForegroundColor;                               // 0x0064 (0x0010) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnableDropShadow : 1;                         // 0x0074 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	int32_t                                            TexturePageWidth;                              // 0x0078 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            TexturePageMaxHeight;                          // 0x007C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            XPadding;                                      // 0x0080 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            YPadding;                                      // 0x0084 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ExtendBoxTop;                                  // 0x0088 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ExtendBoxBottom;                               // 0x008C (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ExtendBoxRight;                                // 0x0090 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ExtendBoxLeft;                                 // 0x0094 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnableLegacyMode : 1;                         // 0x0098 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	int32_t                                            Kerning;                                       // 0x009C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bUseDistanceFieldAlpha : 1;                    // 0x00A0 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	int32_t                                            DistanceFieldScaleFactor;                      // 0x00A4 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DistanceFieldScanRadiusScale;                  // 0x00A8 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFontImportOptionsData& other) const { return memcmp(this, &other, sizeof(FFontImportOptionsData)) == 0; }
	bool operator!=(const FFontImportOptionsData& other) const { return !(*this == other); }
	bool operator<(const FFontImportOptionsData& other) const { return memcmp(this, &other, sizeof(FFontImportOptionsData)) < 0; }
};

// ScriptStruct Engine.Font.FontCharacter
// 0x0018
struct FFontCharacter
{
	int32_t                                            StartU;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            StartV;                                        // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            USize;                                         // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            VSize;                                         // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            TextureIndex;                                  // 0x0010 (0x0001) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            VerticalOffset;                                // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFontCharacter& other) const { return memcmp(this, &other, sizeof(FFontCharacter)) == 0; }
	bool operator!=(const FFontCharacter& other) const { return !(*this == other); }
	bool operator<(const FFontCharacter& other) const { return memcmp(this, &other, sizeof(FFontCharacter)) < 0; }
};

// ScriptStruct Engine.ForceFeedbackWaveform.WaveformSample
// 0x000C
struct FWaveformSample
{
	uint8_t                                            LeftAmplitude;                                 // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            RightAmplitude;                                // 0x0001 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            LeftTriggerAmplitude;                          // 0x0002 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            RightTriggerAmplitude;                         // 0x0003 (0x0001) [0x0000000000000001] (CPF_Edit)    
	EWaveformFunction                                  LeftFunction;                                  // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	EWaveformFunction                                  RightFunction;                                 // 0x0005 (0x0001) [0x0000000000000001] (CPF_Edit)    
	EWaveformFunction                                  LeftTriggerFunction;                           // 0x0006 (0x0001) [0x0000000000000001] (CPF_Edit)    
	EWaveformFunction                                  RightTriggerFunction;                          // 0x0007 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              Duration;                                      // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FWaveformSample& other) const { return memcmp(this, &other, sizeof(FWaveformSample)) == 0; }
	bool operator!=(const FWaveformSample& other) const { return !(*this == other); }
	bool operator<(const FWaveformSample& other) const { return memcmp(this, &other, sizeof(FWaveformSample)) < 0; }
};

// ScriptStruct Engine.FracturedStaticMeshComponent.FragmentGroup
// 0x0014
struct FFragmentGroup
{
	class TArray<int32_t>                              FragmentIndices;                               // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bGroupIsRooted : 1;                            // 0x0010 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FFragmentGroup& other) const { return memcmp(this, &other, sizeof(FFragmentGroup)) == 0; }
	bool operator!=(const FFragmentGroup& other) const { return !(*this == other); }
	bool operator<(const FFragmentGroup& other) const { return memcmp(this, &other, sizeof(FFragmentGroup)) < 0; }
};

// ScriptStruct Engine.FracturedStaticMeshActor.DeferredPartToSpawn
// 0x0024
struct FDeferredPartToSpawn
{
	int32_t                                            ChunkIndex;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     InitialVel;                                    // 0x0004 (0x000C) [0x0000000000000000]               
	struct FVector                                     InitialAngVel;                                 // 0x0010 (0x000C) [0x0000000000000000]               
	float                                              RelativeScale;                                 // 0x001C (0x0004) [0x0000000000000000]               
	uint32_t                                           bExplosion : 1;                                // 0x0020 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FDeferredPartToSpawn& other) const { return memcmp(this, &other, sizeof(FDeferredPartToSpawn)) == 0; }
	bool operator!=(const FDeferredPartToSpawn& other) const { return !(*this == other); }
	bool operator<(const FDeferredPartToSpawn& other) const { return memcmp(this, &other, sizeof(FDeferredPartToSpawn)) < 0; }
};

// ScriptStruct Engine.FracturedStaticMeshActor.CheckpointRecord
// 0x0018
struct AFracturedStaticMeshActor_FCheckpointRecord
{
	uint32_t                                           bIsShutdown : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	class TArray<uint8_t>                              FragmentVis;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const AFracturedStaticMeshActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AFracturedStaticMeshActor_FCheckpointRecord)) == 0; }
	bool operator!=(const AFracturedStaticMeshActor_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const AFracturedStaticMeshActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AFracturedStaticMeshActor_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.GameEngine.LevelStreamingStatus
// 0x000C
struct FLevelStreamingStatus
{
	class FName                                        PackageName;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	uint32_t                                           bShouldBeLoaded : 1;                           // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bShouldBeVisible : 1;                          // 0x0008 (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FLevelStreamingStatus& other) const { return memcmp(this, &other, sizeof(FLevelStreamingStatus)) == 0; }
	bool operator!=(const FLevelStreamingStatus& other) const { return !(*this == other); }
	bool operator<(const FLevelStreamingStatus& other) const { return memcmp(this, &other, sizeof(FLevelStreamingStatus)) < 0; }
};

// ScriptStruct Engine.GameEngine.FullyLoadedPackagesInfo
// 0x0038
struct FFullyLoadedPackagesInfo
{
	EFullyLoadPackageType                              FullyLoadType;                                 // 0x0000 (0x0001) [0x0000000000000000]               
	class FString                                      Tag;                                           // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FName>                          PackagesToLoad;                                // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class UObject*>                       LoadedObjects;                                 // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFullyLoadedPackagesInfo& other) const { return memcmp(this, &other, sizeof(FFullyLoadedPackagesInfo)) == 0; }
	bool operator!=(const FFullyLoadedPackagesInfo& other) const { return !(*this == other); }
	bool operator<(const FFullyLoadedPackagesInfo& other) const { return memcmp(this, &other, sizeof(FFullyLoadedPackagesInfo)) < 0; }
};

// ScriptStruct Engine.GameEngine.NamedNetDriver
// 0x0010
struct FNamedNetDriver
{
	class FName                                        NetDriverName;                                 // 0x0000 (0x0008) [0x0000000000000000]               
	struct FPointer                                    NetDriver;                                     // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FNamedNetDriver& other) const { return memcmp(this, &other, sizeof(FNamedNetDriver)) == 0; }
	bool operator!=(const FNamedNetDriver& other) const { return !(*this == other); }
	bool operator<(const FNamedNetDriver& other) const { return memcmp(this, &other, sizeof(FNamedNetDriver)) < 0; }
};

// ScriptStruct Engine.GameEngine.AnimTag
// 0x0020
struct FAnimTag
{
	class FString                                      Tag;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Contains;                                      // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAnimTag& other) const { return memcmp(this, &other, sizeof(FAnimTag)) == 0; }
	bool operator!=(const FAnimTag& other) const { return !(*this == other); }
	bool operator<(const FAnimTag& other) const { return memcmp(this, &other, sizeof(FAnimTag)) < 0; }
};

// ScriptStruct Engine.GameEngine.URL
// 0x005C
struct FURL
{
	class FString                                      Protocol;                                      // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Host;                                          // 0x0010 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	int32_t                                            Port;                                          // 0x0020 (0x0004) [0x0000000000100000]               
	class FString                                      Map;                                           // 0x0028 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Op;                                            // 0x0038 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Portal;                                        // 0x0048 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	int32_t                                            Valid;                                         // 0x0058 (0x0004) [0x0000000000100000]               

	bool operator==(const FURL& other) const { return memcmp(this, &other, sizeof(FURL)) == 0; }
	bool operator!=(const FURL& other) const { return !(*this == other); }
	bool operator<(const FURL& other) const { return memcmp(this, &other, sizeof(FURL)) < 0; }
};

// ScriptStruct Engine.GameInfo.GameClassShortName
// 0x0020
struct FGameClassShortName
{
	class FString                                      ShortName;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GameClassName;                                 // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FGameClassShortName& other) const { return memcmp(this, &other, sizeof(FGameClassShortName)) == 0; }
	bool operator!=(const FGameClassShortName& other) const { return !(*this == other); }
	bool operator<(const FGameClassShortName& other) const { return memcmp(this, &other, sizeof(FGameClassShortName)) < 0; }
};

// ScriptStruct Engine.GameInfo.GameTypePrefix
// 0x0048
struct FGameTypePrefix
{
	class FString                                      Prefix;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bUsesCommonPackage : 1;                        // 0x0010 (0x0004) [0x0000000000000000] [0x00000001] 
	class FString                                      GameType;                                      // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        AdditionalGameTypes;                           // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        ForcedObjects;                                 // 0x0038 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FGameTypePrefix& other) const { return memcmp(this, &other, sizeof(FGameTypePrefix)) == 0; }
	bool operator!=(const FGameTypePrefix& other) const { return !(*this == other); }
	bool operator<(const FGameTypePrefix& other) const { return memcmp(this, &other, sizeof(FGameTypePrefix)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.PlayerInformation
// 0x0064
struct FPlayerInformation
{
	class FName                                        ControllerName;                                // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      PlayerName;                                    // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                UniqueId;                                      // 0x0018 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsBot : 1;                                    // 0x0060 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FPlayerInformation& other) const { return memcmp(this, &other, sizeof(FPlayerInformation)) == 0; }
	bool operator!=(const FPlayerInformation& other) const { return !(*this == other); }
	bool operator<(const FPlayerInformation& other) const { return memcmp(this, &other, sizeof(FPlayerInformation)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.TeamInformation
// 0x0020
struct FTeamInformation
{
	int32_t                                            TeamIndex;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      TeamName;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FColor                                      TeamColor;                                     // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxSize;                                       // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FTeamInformation& other) const { return memcmp(this, &other, sizeof(FTeamInformation)) == 0; }
	bool operator!=(const FTeamInformation& other) const { return !(*this == other); }
	bool operator<(const FTeamInformation& other) const { return memcmp(this, &other, sizeof(FTeamInformation)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.GameStatGroup
// 0x0008
struct FGameStatGroup
{
	EGameStatGroups                                    Group;                                         // 0x0000 (0x0001) [0x0000000000000000]               
	int32_t                                            Level;                                         // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FGameStatGroup& other) const { return memcmp(this, &other, sizeof(FGameStatGroup)) == 0; }
	bool operator!=(const FGameStatGroup& other) const { return !(*this == other); }
	bool operator<(const FGameStatGroup& other) const { return memcmp(this, &other, sizeof(FGameStatGroup)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.GameplayEventMetaData
// 0x0018
struct FGameplayEventMetaData
{
	int32_t                                            EventID;                                       // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FName                                        EventName;                                     // 0x0004 (0x0008) [0x0000000000000002] (CPF_Const)   
	struct FGameStatGroup                              StatGroup;                                     // 0x000C (0x0008) [0x0000000000000002] (CPF_Const)   
	int32_t                                            EventDataType;                                 // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FGameplayEventMetaData& other) const { return memcmp(this, &other, sizeof(FGameplayEventMetaData)) == 0; }
	bool operator!=(const FGameplayEventMetaData& other) const { return !(*this == other); }
	bool operator<(const FGameplayEventMetaData& other) const { return memcmp(this, &other, sizeof(FGameplayEventMetaData)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.WeaponClassEventData
// 0x0008
struct FWeaponClassEventData
{
	class FName                                        WeaponClassName;                               // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FWeaponClassEventData& other) const { return memcmp(this, &other, sizeof(FWeaponClassEventData)) == 0; }
	bool operator!=(const FWeaponClassEventData& other) const { return !(*this == other); }
	bool operator<(const FWeaponClassEventData& other) const { return memcmp(this, &other, sizeof(FWeaponClassEventData)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.DamageClassEventData
// 0x0008
struct FDamageClassEventData
{
	class FName                                        DamageClassName;                               // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FDamageClassEventData& other) const { return memcmp(this, &other, sizeof(FDamageClassEventData)) == 0; }
	bool operator!=(const FDamageClassEventData& other) const { return !(*this == other); }
	bool operator<(const FDamageClassEventData& other) const { return memcmp(this, &other, sizeof(FDamageClassEventData)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.ProjectileClassEventData
// 0x0008
struct FProjectileClassEventData
{
	class FName                                        ProjectileClassName;                           // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FProjectileClassEventData& other) const { return memcmp(this, &other, sizeof(FProjectileClassEventData)) == 0; }
	bool operator!=(const FProjectileClassEventData& other) const { return !(*this == other); }
	bool operator<(const FProjectileClassEventData& other) const { return memcmp(this, &other, sizeof(FProjectileClassEventData)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.PawnClassEventData
// 0x0008
struct FPawnClassEventData
{
	class FName                                        PawnClassName;                                 // 0x0000 (0x0008) [0x0000000000000000]               

	bool operator==(const FPawnClassEventData& other) const { return memcmp(this, &other, sizeof(FPawnClassEventData)) == 0; }
	bool operator!=(const FPawnClassEventData& other) const { return !(*this == other); }
	bool operator<(const FPawnClassEventData& other) const { return memcmp(this, &other, sizeof(FPawnClassEventData)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.GameplayEventsHeader
// 0x0034
struct FGameplayEventsHeader
{
	int32_t                                            EngineVersion;                                 // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            StatsWriterVersion;                            // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            StreamOffset;                                  // 0x0008 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            AggregateOffset;                               // 0x000C (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            FooterOffset;                                  // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            TotalStreamSize;                               // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            FileSize;                                      // 0x0018 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      FilterClass;                                   // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Flags;                                         // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FGameplayEventsHeader& other) const { return memcmp(this, &other, sizeof(FGameplayEventsHeader)) == 0; }
	bool operator!=(const FGameplayEventsHeader& other) const { return !(*this == other); }
	bool operator<(const FGameplayEventsHeader& other) const { return memcmp(this, &other, sizeof(FGameplayEventsHeader)) < 0; }
};

// ScriptStruct Engine.GameplayEvents.GameSessionInformation
// 0x00CC
struct FGameSessionInformation
{
	int32_t                                            AppTitleID;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            PlatformType;                                  // 0x0004 (0x0004) [0x0000000000000000]               
	class FString                                      Language;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      GameplaySessionTimestamp;                      // 0x0018 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	float                                              GameplaySessionStartTime;                      // 0x0028 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              GameplaySessionEndTime;                        // 0x002C (0x0004) [0x0000000000000002] (CPF_Const)   
	uint32_t                                           bGameplaySessionInProgress : 1;                // 0x0030 (0x0004) [0x0000000000000002] [0x00000001] (CPF_Const)
	class FString                                      GameplaySessionID;                             // 0x0038 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      GameClassName;                                 // 0x0048 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      MapName;                                       // 0x0058 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      MapURL;                                        // 0x0068 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            SessionInstance;                               // 0x0078 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            GameTypeId;                                    // 0x007C (0x0004) [0x0000000000000002] (CPF_Const)   
	struct FUniqueNetId                                OwningNetId;                                   // 0x0080 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	int32_t                                            PlaylistId;                                    // 0x00C8 (0x0004) [0x0000000000000000]               

	bool operator==(const FGameSessionInformation& other) const { return memcmp(this, &other, sizeof(FGameSessionInformation)) == 0; }
	bool operator!=(const FGameSessionInformation& other) const { return !(*this == other); }
	bool operator<(const FGameSessionInformation& other) const { return memcmp(this, &other, sizeof(FGameSessionInformation)) < 0; }
};

// ScriptStruct Engine.WorldInfo.NavMeshPathGoalEvaluatorCacheDatum
// 0x0030
struct FNavMeshPathGoalEvaluatorCacheDatum
{
	int32_t                                            ListIdx;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	class UNavMeshPathGoalEvaluator*                   List[5];                                       // 0x0008 (0x0028) [0x0000000000000000]               

	bool operator==(const FNavMeshPathGoalEvaluatorCacheDatum& other) const { return memcmp(this, &other, sizeof(FNavMeshPathGoalEvaluatorCacheDatum)) == 0; }
	bool operator!=(const FNavMeshPathGoalEvaluatorCacheDatum& other) const { return !(*this == other); }
	bool operator<(const FNavMeshPathGoalEvaluatorCacheDatum& other) const { return memcmp(this, &other, sizeof(FNavMeshPathGoalEvaluatorCacheDatum)) < 0; }
};

// ScriptStruct Engine.WorldInfo.PhysXEmitterVerticalProperties
// 0x0018
struct FPhysXEmitterVerticalProperties
{
	uint32_t                                           bDisableLod : 1;                               // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	int32_t                                            ParticlesLodMin;                               // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ParticlesLodMax;                               // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            PacketsPerPhysXParticleSystemMax;              // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bApplyCylindricalPacketCulling : 1;            // 0x0010 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              SpawnLodVsFifoBias;                            // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPhysXEmitterVerticalProperties& other) const { return memcmp(this, &other, sizeof(FPhysXEmitterVerticalProperties)) == 0; }
	bool operator!=(const FPhysXEmitterVerticalProperties& other) const { return !(*this == other); }
	bool operator<(const FPhysXEmitterVerticalProperties& other) const { return memcmp(this, &other, sizeof(FPhysXEmitterVerticalProperties)) < 0; }
};

// ScriptStruct Engine.WorldInfo.PhysXVerticalProperties
// 0x0018
struct FPhysXVerticalProperties
{
	struct FPhysXEmitterVerticalProperties             Emitters;                                      // 0x0000 (0x0018) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FPhysXVerticalProperties& other) const { return memcmp(this, &other, sizeof(FPhysXVerticalProperties)) == 0; }
	bool operator!=(const FPhysXVerticalProperties& other) const { return !(*this == other); }
	bool operator<(const FPhysXVerticalProperties& other) const { return memcmp(this, &other, sizeof(FPhysXVerticalProperties)) < 0; }
};

// ScriptStruct Engine.WorldInfo.HostMigrationState
// 0x0024
struct FHostMigrationState
{
	EHostMigrationProgress                             HostMigrationProgress;                         // 0x0000 (0x0001) [0x0000000000000000]               
	float                                              HostMigrationElapsedTime;                      // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              HostMigrationTravelCountdown;                  // 0x0008 (0x0004) [0x0000000000000000]               
	class FString                                      HostMigrationTravelURL;                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bHostMigrationEnabled : 1;                     // 0x0020 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FHostMigrationState& other) const { return memcmp(this, &other, sizeof(FHostMigrationState)) == 0; }
	bool operator!=(const FHostMigrationState& other) const { return !(*this == other); }
	bool operator<(const FHostMigrationState& other) const { return memcmp(this, &other, sizeof(FHostMigrationState)) < 0; }
};

// ScriptStruct Engine.MusicTrackDataStructures.MusicTrackStruct
// 0x0030
struct FMusicTrackStruct
{
	class USoundCue*                                   TheSoundCue;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bAutoPlay : 1;                                 // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bPersistentAcrossLevels : 1;                   // 0x0008 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	float                                              FadeInTime;                                    // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeInVolumeLevel;                             // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeOutTime;                                   // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeOutVolumeLevel;                            // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FString                                      MP3Filename;                                   // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FMusicTrackStruct& other) const { return memcmp(this, &other, sizeof(FMusicTrackStruct)) == 0; }
	bool operator!=(const FMusicTrackStruct& other) const { return !(*this == other); }
	bool operator<(const FMusicTrackStruct& other) const { return memcmp(this, &other, sizeof(FMusicTrackStruct)) < 0; }
};

// ScriptStruct Engine.WorldInfo.WorldFractureSettings
// 0x001C
struct FWorldFractureSettings
{
	float                                              ChanceOfPhysicsChunkOverride;                  // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           bEnableChanceOfPhysicsChunkOverride : 1;       // 0x0004 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bLimitExplosionChunkSize : 1;                  // 0x0004 (0x0004) [0x0000000000000000] [0x00000002] 
	float                                              MaxExplosionChunkSize;                         // 0x0008 (0x0004) [0x0000000000000000]               
	uint32_t                                           bLimitDamageChunkSize : 1;                     // 0x000C (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              MaxDamageChunkSize;                            // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxNumFacturedChunksToSpawnInAFrame;           // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              FractureExplosionVelScale;                     // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FWorldFractureSettings& other) const { return memcmp(this, &other, sizeof(FWorldFractureSettings)) == 0; }
	bool operator!=(const FWorldFractureSettings& other) const { return !(*this == other); }
	bool operator<(const FWorldFractureSettings& other) const { return memcmp(this, &other, sizeof(FWorldFractureSettings)) < 0; }
};

// ScriptStruct Engine.WorldInfo.NavMeshPathConstraintCacheDatum
// 0x0030
struct FNavMeshPathConstraintCacheDatum
{
	int32_t                                            ListIdx;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	class UNavMeshPathConstraint*                      List[5];                                       // 0x0008 (0x0028) [0x0000000000000000]               

	bool operator==(const FNavMeshPathConstraintCacheDatum& other) const { return memcmp(this, &other, sizeof(FNavMeshPathConstraintCacheDatum)) == 0; }
	bool operator!=(const FNavMeshPathConstraintCacheDatum& other) const { return !(*this == other); }
	bool operator<(const FNavMeshPathConstraintCacheDatum& other) const { return memcmp(this, &other, sizeof(FNavMeshPathConstraintCacheDatum)) < 0; }
};

// ScriptStruct Engine.WorldInfo.LightmassWorldInfoSettings
// 0x0058
struct FLightmassWorldInfoSettings
{
	float                                              StaticLightingLevelScale;                      // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            NumIndirectLightingBounces;                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FColor                                      EnvironmentColor;                              // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EnvironmentIntensity;                          // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnableAdvancedEnvironmentColor : 1;           // 0x0010 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FColor                                      EnvironmentSunColor;                           // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EnvironmentSunIntensity;                       // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              EnvironmentLightTerminatorAngle;               // 0x001C (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     EnvironmentLightDirection;                     // 0x0020 (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              EmissiveBoost;                                 // 0x002C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DiffuseBoost;                                  // 0x0030 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              SpecularBoost;                                 // 0x0034 (0x0004) [0x0000000000000000]               
	float                                              IndirectNormalInfluenceBoost;                  // 0x0038 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bUseAmbientOcclusion : 1;                      // 0x003C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bEnableImageReflectionShadowing : 1;           // 0x003C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	float                                              DirectIlluminationOcclusionFraction;           // 0x0040 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              IndirectIlluminationOcclusionFraction;         // 0x0044 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              OcclusionExponent;                             // 0x0048 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FullyOccludedSamplesFraction;                  // 0x004C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxOcclusionDistance;                          // 0x0050 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bVisualizeMaterialDiffuse : 1;                 // 0x0054 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bVisualizeAmbientOcclusion : 1;                // 0x0054 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bCompressShadowmap : 1;                        // 0x0054 (0x0004) [0x0000000000000001] [0x100000004] (CPF_Edit)

	bool operator==(const FLightmassWorldInfoSettings& other) const { return memcmp(this, &other, sizeof(FLightmassWorldInfoSettings)) == 0; }
	bool operator!=(const FLightmassWorldInfoSettings& other) const { return !(*this == other); }
	bool operator<(const FLightmassWorldInfoSettings& other) const { return memcmp(this, &other, sizeof(FLightmassWorldInfoSettings)) < 0; }
};

// ScriptStruct Engine.WorldInfo.ScreenMessageString
// 0x0024
struct FScreenMessageString
{
	uint64_t                                           Key;                                           // 0x0000 (0x0008) [0x0000000000102000] (CPF_Transient)
	class FString                                      ScreenMessage;                                 // 0x0008 (0x0010) [0x0000000000502000] (CPF_Transient | CPF_NeedCtorLink)
	struct FColor                                      DisplayColor;                                  // 0x0018 (0x0004) [0x0000000000102000] (CPF_Transient)
	float                                              TimeToDisplay;                                 // 0x001C (0x0004) [0x0000000000102000] (CPF_Transient)
	float                                              CurrentTimeDisplayed;                          // 0x0020 (0x0004) [0x0000000000102000] (CPF_Transient)

	bool operator==(const FScreenMessageString& other) const { return memcmp(this, &other, sizeof(FScreenMessageString)) == 0; }
	bool operator!=(const FScreenMessageString& other) const { return !(*this == other); }
	bool operator<(const FScreenMessageString& other) const { return memcmp(this, &other, sizeof(FScreenMessageString)) < 0; }
};

// ScriptStruct Engine.WorldInfo.ApexModuleDestructibleSettings
// 0x0014
struct FApexModuleDestructibleSettings
{
	int32_t                                            MaxChunkIslandCount;                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MaxShapeCount;                                 // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MaxRrbActorCount;                              // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              MaxChunkSeparationLOD;                         // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bOverrideMaxChunkSeparationLOD : 1;            // 0x0010 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FApexModuleDestructibleSettings& other) const { return memcmp(this, &other, sizeof(FApexModuleDestructibleSettings)) == 0; }
	bool operator!=(const FApexModuleDestructibleSettings& other) const { return !(*this == other); }
	bool operator<(const FApexModuleDestructibleSettings& other) const { return memcmp(this, &other, sizeof(FApexModuleDestructibleSettings)) < 0; }
};

// ScriptStruct Engine.WorldInfo.PhysXSimulationProperties
// 0x000C
struct FPhysXSimulationProperties
{
	uint32_t                                           bUseHardware : 1;                              // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bFixedTimeStep : 1;                            // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	float                                              TimeStep;                                      // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MaxSubSteps;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPhysXSimulationProperties& other) const { return memcmp(this, &other, sizeof(FPhysXSimulationProperties)) == 0; }
	bool operator!=(const FPhysXSimulationProperties& other) const { return !(*this == other); }
	bool operator<(const FPhysXSimulationProperties& other) const { return memcmp(this, &other, sizeof(FPhysXSimulationProperties)) < 0; }
};

// ScriptStruct Engine.WorldInfo.PhysXSceneProperties
// 0x003C
struct FPhysXSceneProperties
{
	struct FPhysXSimulationProperties                  PrimaryScene;                                  // 0x0000 (0x000C) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	struct FPhysXSimulationProperties                  CompartmentRigidBody;                          // 0x000C (0x000C) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	struct FPhysXSimulationProperties                  CompartmentFluid;                              // 0x0018 (0x000C) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	struct FPhysXSimulationProperties                  CompartmentCloth;                              // 0x0024 (0x000C) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	struct FPhysXSimulationProperties                  CompartmentSoftBody;                           // 0x0030 (0x000C) [0x0000000004000001] (CPF_Edit | CPF_EditInline)

	bool operator==(const FPhysXSceneProperties& other) const { return memcmp(this, &other, sizeof(FPhysXSceneProperties)) == 0; }
	bool operator!=(const FPhysXSceneProperties& other) const { return !(*this == other); }
	bool operator<(const FPhysXSceneProperties& other) const { return memcmp(this, &other, sizeof(FPhysXSceneProperties)) < 0; }
};

// ScriptStruct Engine.WorldInfo.CompartmentRunList
// 0x0004
struct FCompartmentRunList
{
	uint32_t                                           RigidBody : 1;                                 // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           Fluid : 1;                                     // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           Cloth : 1;                                     // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           SoftBody : 1;                                  // 0x0000 (0x0004) [0x0000000000000001] [0x100000008] (CPF_Edit)

	bool operator==(const FCompartmentRunList& other) const { return memcmp(this, &other, sizeof(FCompartmentRunList)) == 0; }
	bool operator!=(const FCompartmentRunList& other) const { return !(*this == other); }
	bool operator<(const FCompartmentRunList& other) const { return memcmp(this, &other, sizeof(FCompartmentRunList)) < 0; }
};

// ScriptStruct Engine.WorldInfo.NetViewer
// 0x0028
struct FNetViewer
{
	class APlayerController*                           InViewer;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class AActor*                                      Viewer;                                        // 0x0008 (0x0008) [0x0000000000000000]               
	struct FVector                                     ViewLocation;                                  // 0x0010 (0x000C) [0x0000000000000000]               
	struct FVector                                     ViewDir;                                       // 0x001C (0x000C) [0x0000000000000000]               

	bool operator==(const FNetViewer& other) const { return memcmp(this, &other, sizeof(FNetViewer)) == 0; }
	bool operator!=(const FNetViewer& other) const { return !(*this == other); }
	bool operator<(const FNetViewer& other) const { return memcmp(this, &other, sizeof(FNetViewer)) < 0; }
};

// ScriptStruct Engine.Settings.IdToStringMapping
// 0x000C
struct FIdToStringMapping
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000000008002] (CPF_Const | CPF_Localized)

	bool operator==(const FIdToStringMapping& other) const { return memcmp(this, &other, sizeof(FIdToStringMapping)) == 0; }
	bool operator!=(const FIdToStringMapping& other) const { return !(*this == other); }
	bool operator<(const FIdToStringMapping& other) const { return memcmp(this, &other, sizeof(FIdToStringMapping)) < 0; }
};

// ScriptStruct Engine.Settings.StringIdToStringMapping
// 0x0010
struct FStringIdToStringMapping
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000000008002] (CPF_Const | CPF_Localized)
	uint32_t                                           bIsWildcard : 1;                               // 0x000C (0x0004) [0x0000000000000002] [0x100000001] (CPF_Const)

	bool operator==(const FStringIdToStringMapping& other) const { return memcmp(this, &other, sizeof(FStringIdToStringMapping)) == 0; }
	bool operator!=(const FStringIdToStringMapping& other) const { return !(*this == other); }
	bool operator<(const FStringIdToStringMapping& other) const { return memcmp(this, &other, sizeof(FStringIdToStringMapping)) < 0; }
};

// ScriptStruct Engine.Settings.LocalizedStringSettingMetaData
// 0x0030
struct FLocalizedStringSettingMetaData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      ColumnHeaderText;                              // 0x0010 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class TArray<struct FStringIdToStringMapping>      ValueMappings;                                 // 0x0020 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FLocalizedStringSettingMetaData& other) const { return memcmp(this, &other, sizeof(FLocalizedStringSettingMetaData)) == 0; }
	bool operator!=(const FLocalizedStringSettingMetaData& other) const { return !(*this == other); }
	bool operator<(const FLocalizedStringSettingMetaData& other) const { return memcmp(this, &other, sizeof(FLocalizedStringSettingMetaData)) < 0; }
};

// ScriptStruct Engine.Settings.SettingsPropertyPropertyMetaData
// 0x0054
struct FSettingsPropertyPropertyMetaData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FName                                        Name;                                          // 0x0004 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      ColumnHeaderText;                              // 0x0010 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	EPropertyValueMappingType                          MappingType;                                   // 0x0020 (0x0001) [0x0000000000000002] (CPF_Const)   
	class TArray<struct FIdToStringMapping>            ValueMappings;                                 // 0x0028 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FSettingsData>                 PredefinedValues;                              // 0x0038 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	float                                              MinVal;                                        // 0x0048 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              MaxVal;                                        // 0x004C (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              RangeIncrement;                                // 0x0050 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FSettingsPropertyPropertyMetaData& other) const { return memcmp(this, &other, sizeof(FSettingsPropertyPropertyMetaData)) == 0; }
	bool operator!=(const FSettingsPropertyPropertyMetaData& other) const { return !(*this == other); }
	bool operator<(const FSettingsPropertyPropertyMetaData& other) const { return memcmp(this, &other, sizeof(FSettingsPropertyPropertyMetaData)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OnlineGameSearchParameter
// 0x000E
struct FOnlineGameSearchParameter
{
	int32_t                                            EntryId;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        ObjectPropertyName;                            // 0x0004 (0x0008) [0x0000000000000000]               
	EOnlineGameSearchEntryType                         EntryType;                                     // 0x000C (0x0001) [0x0000000000000000]               
	EOnlineGameSearchComparisonType                    ComparisonType;                                // 0x000D (0x0001) [0x0000000000000000]               

	bool operator==(const FOnlineGameSearchParameter& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchParameter)) == 0; }
	bool operator!=(const FOnlineGameSearchParameter& other) const { return !(*this == other); }
	bool operator<(const FOnlineGameSearchParameter& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchParameter)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OnlineGameSearchORClause
// 0x0010
struct FOnlineGameSearchORClause
{
	class TArray<struct FOnlineGameSearchParameter>    OrParams;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineGameSearchORClause& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchORClause)) == 0; }
	bool operator!=(const FOnlineGameSearchORClause& other) const { return !(*this == other); }
	bool operator<(const FOnlineGameSearchORClause& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchORClause)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OnlineGameSearchSortClause
// 0x000E
struct FOnlineGameSearchSortClause
{
	int32_t                                            EntryId;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        ObjectPropertyName;                            // 0x0004 (0x0008) [0x0000000000000000]               
	EOnlineGameSearchEntryType                         EntryType;                                     // 0x000C (0x0001) [0x0000000000000000]               
	EOnlineGameSearchSortType                          SortType;                                      // 0x000D (0x0001) [0x0000000000000000]               

	bool operator==(const FOnlineGameSearchSortClause& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchSortClause)) == 0; }
	bool operator!=(const FOnlineGameSearchSortClause& other) const { return !(*this == other); }
	bool operator<(const FOnlineGameSearchSortClause& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchSortClause)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OnlineGameSearchQuery
// 0x0020
struct FOnlineGameSearchQuery
{
	class TArray<struct FOnlineGameSearchORClause>     OrClauses;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FOnlineGameSearchSortClause>   SortClauses;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineGameSearchQuery& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchQuery)) == 0; }
	bool operator!=(const FOnlineGameSearchQuery& other) const { return !(*this == other); }
	bool operator<(const FOnlineGameSearchQuery& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchQuery)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OverrideSkill
// 0x0038
struct FOverrideSkill
{
	int32_t                                            LeaderboardId;                                 // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<struct FUniqueNetId>                  Players;                                       // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FDouble>                       Mus;                                           // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FDouble>                       Sigmas;                                        // 0x0028 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOverrideSkill& other) const { return memcmp(this, &other, sizeof(FOverrideSkill)) == 0; }
	bool operator!=(const FOverrideSkill& other) const { return !(*this == other); }
	bool operator<(const FOverrideSkill& other) const { return memcmp(this, &other, sizeof(FOverrideSkill)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.NamedObjectProperty
// 0x0018
struct FNamedObjectProperty
{
	class FName                                        ObjectPropertyName;                            // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      ObjectPropertyValue;                           // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FNamedObjectProperty& other) const { return memcmp(this, &other, sizeof(FNamedObjectProperty)) == 0; }
	bool operator!=(const FNamedObjectProperty& other) const { return !(*this == other); }
	bool operator<(const FNamedObjectProperty& other) const { return memcmp(this, &other, sizeof(FNamedObjectProperty)) < 0; }
};

// ScriptStruct Engine.OnlineGameSearch.OnlineGameSearchResult
// 0x0010
struct FOnlineGameSearchResult
{
	class UOnlineGameSettings*                         GameSettings;                                  // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	struct FPointer                                    PlatformData;                                  // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FOnlineGameSearchResult& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchResult)) == 0; }
	bool operator!=(const FOnlineGameSearchResult& other) const { return !(*this == other); }
	bool operator<(const FOnlineGameSearchResult& other) const { return memcmp(this, &other, sizeof(FOnlineGameSearchResult)) < 0; }
};

// ScriptStruct Engine.PlayerController.ConnectedPeerInfo
// 0x0050
struct FConnectedPeerInfo
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	ENATType                                           NatType;                                       // 0x0048 (0x0001) [0x0000000000000000]               
	uint32_t                                           bLostConnectionToHost : 1;                     // 0x004C (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FConnectedPeerInfo& other) const { return memcmp(this, &other, sizeof(FConnectedPeerInfo)) == 0; }
	bool operator!=(const FConnectedPeerInfo& other) const { return !(*this == other); }
	bool operator<(const FConnectedPeerInfo& other) const { return memcmp(this, &other, sizeof(FConnectedPeerInfo)) < 0; }
};

// ScriptStruct Engine.PlayerController.ClientAdjustment
// 0x0035
struct FClientAdjustment
{
	float                                              TimeStamp;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	EPhysics                                           newPhysics;                                    // 0x0004 (0x0001) [0x0000000000000000]               
	struct FVector                                     NewLoc;                                        // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     NewVel;                                        // 0x0014 (0x000C) [0x0000000000000000]               
	class AActor*                                      NewBase;                                       // 0x0020 (0x0008) [0x0000000000000000]               
	struct FVector                                     NewFloor;                                      // 0x0028 (0x000C) [0x0000000000000000]               
	uint8_t                                            bAckGoodMove;                                  // 0x0034 (0x0001) [0x0000000000000000]               

	bool operator==(const FClientAdjustment& other) const { return memcmp(this, &other, sizeof(FClientAdjustment)) == 0; }
	bool operator!=(const FClientAdjustment& other) const { return !(*this == other); }
	bool operator<(const FClientAdjustment& other) const { return memcmp(this, &other, sizeof(FClientAdjustment)) < 0; }
};

// ScriptStruct Engine.PlayerReplicationInfo.ClientConnectionStats
// 0x0058
struct FClientConnectionStats
{
	int32_t                                            ConnectionCount;                               // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            PingTotal;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            PingMin;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            PingMax;                                       // 0x000C (0x0004) [0x0000000000000000]               
	float                                              CurrentAckTime;                                // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              TotalAckTime;                                  // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              CurrentReceiveTime;                            // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              TotalReceiveTime;                              // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            TotalPacketsLost;                              // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalPacketsInOut;                             // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              InPacketLossPerSecMin;                         // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              InPacketLossPerSecMax;                         // 0x002C (0x0004) [0x0000000000000000]               
	float                                              OutPacketLossPerSecMin;                        // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              OutPacketLossPerSecMax;                        // 0x0034 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxInBPS;                                      // 0x0038 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalInBPS;                                    // 0x003C (0x0004) [0x0000000000000000]               
	int32_t                                            TotalInBytes;                                  // 0x0040 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxOutBPS;                                     // 0x0044 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalOutBPS;                                   // 0x0048 (0x0004) [0x0000000000000000]               
	int32_t                                            TotalOutBytes;                                 // 0x004C (0x0004) [0x0000000000000000]               
	float                                              CurrentLatency;                                // 0x0050 (0x0004) [0x0000000000000000]               
	float                                              CurrentJitter;                                 // 0x0054 (0x0004) [0x0000000000000000]               

	bool operator==(const FClientConnectionStats& other) const { return memcmp(this, &other, sizeof(FClientConnectionStats)) == 0; }
	bool operator!=(const FClientConnectionStats& other) const { return !(*this == other); }
	bool operator<(const FClientConnectionStats& other) const { return memcmp(this, &other, sizeof(FClientConnectionStats)) < 0; }
};

// ScriptStruct Engine.PlayerController.DebugTextInfo
// 0x0060
struct FDebugTextInfo
{
	class AActor*                                      SrcActor;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     SrcActorOffset;                                // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     SrcActorDesiredOffset;                         // 0x0014 (0x000C) [0x0000000000000000]               
	class FString                                      DebugText;                                     // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              TimeRemaining;                                 // 0x0030 (0x0004) [0x0000000000002000] (CPF_Transient)
	float                                              Duration;                                      // 0x0034 (0x0004) [0x0000000000000000]               
	struct FColor                                      TextColor;                                     // 0x0038 (0x0004) [0x0000000000000000]               
	uint32_t                                           bAbsoluteLocation : 1;                         // 0x003C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bKeepAttachedToActor : 1;                      // 0x003C (0x0004) [0x0000000000000000] [0x00000002] 
	struct FVector                                     OrigActorLocation;                             // 0x0040 (0x000C) [0x0000000000000000]               
	class UFont*                                       Font;                                          // 0x0050 (0x0008) [0x0000000000000000]               
	struct FVector2D                                   TextScale;                                     // 0x0058 (0x0008) [0x0000000000000000]               

	bool operator==(const FDebugTextInfo& other) const { return memcmp(this, &other, sizeof(FDebugTextInfo)) == 0; }
	bool operator!=(const FDebugTextInfo& other) const { return !(*this == other); }
	bool operator<(const FDebugTextInfo& other) const { return memcmp(this, &other, sizeof(FDebugTextInfo)) < 0; }
};

// ScriptStruct Engine.HUD.KismetDrawTextInfo
// 0x0040
struct FKismetDrawTextInfo
{
	class FString                                      MessageText;                                   // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      AppendedText;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UFont*                                       MessageFont;                                   // 0x0020 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   MessageFontScale;                              // 0x0028 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   MessageOffset;                                 // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FColor                                      MessageColor;                                  // 0x0038 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MessageEndTime;                                // 0x003C (0x0004) [0x0000000000000000]               

	bool operator==(const FKismetDrawTextInfo& other) const { return memcmp(this, &other, sizeof(FKismetDrawTextInfo)) == 0; }
	bool operator!=(const FKismetDrawTextInfo& other) const { return !(*this == other); }
	bool operator<(const FKismetDrawTextInfo& other) const { return memcmp(this, &other, sizeof(FKismetDrawTextInfo)) < 0; }
};

// ScriptStruct Engine.HUD.ConsoleMessage
// 0x0020
struct FConsoleMessage
{
	class FString                                      Text;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FColor                                      TextColor;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              MessageLife;                                   // 0x0014 (0x0004) [0x0000000000000000]               
	class APlayerReplicationInfo*                      PRI;                                           // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FConsoleMessage& other) const { return memcmp(this, &other, sizeof(FConsoleMessage)) == 0; }
	bool operator!=(const FConsoleMessage& other) const { return !(*this == other); }
	bool operator<(const FConsoleMessage& other) const { return memcmp(this, &other, sizeof(FConsoleMessage)) < 0; }
};

// ScriptStruct Engine.PlayerController.InputEntry
// 0x000D
struct FInputEntry
{
	EInputTypes                                        Type;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	float                                              Value;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              TimeDelta;                                     // 0x0008 (0x0004) [0x0000000000000000]               
	EInputMatchAction                                  Action;                                        // 0x000C (0x0001) [0x0000000000000000]               

	bool operator==(const FInputEntry& other) const { return memcmp(this, &other, sizeof(FInputEntry)) == 0; }
	bool operator!=(const FInputEntry& other) const { return !(*this == other); }
	bool operator<(const FInputEntry& other) const { return memcmp(this, &other, sizeof(FInputEntry)) < 0; }
};

// ScriptStruct Engine.PlayerController.InputMatchRequest
// 0x0050
struct FInputMatchRequest
{
	class TArray<struct FInputEntry>                   Inputs;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class AActor*                                      MatchActor;                                    // 0x0010 (0x0008) [0x0000000000000000]               
	class FName                                        MatchFuncName;                                 // 0x0018 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             MatchDelegate;                                 // 0x0020 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        FailedFuncName;                                // 0x0038 (0x0008) [0x0000000000000000]               
	class FName                                        RequestName;                                   // 0x0040 (0x0008) [0x0000000000000000]               
	int32_t                                            MatchIdx;                                      // 0x0048 (0x0004) [0x0000000000002000] (CPF_Transient)
	float                                              LastMatchTime;                                 // 0x004C (0x0004) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FInputMatchRequest& other) const { return memcmp(this, &other, sizeof(FInputMatchRequest)) == 0; }
	bool operator!=(const FInputMatchRequest& other) const { return !(*this == other); }
	bool operator<(const FInputMatchRequest& other) const { return memcmp(this, &other, sizeof(FInputMatchRequest)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.GamepadInfo
// 0x0008
struct FGamepadInfo
{
	EInputAPI                                          InputAPI;                                      // 0x0000 (0x0001) [0x0000000000000000]               
	uint32_t                                           bConnected : 1;                                // 0x0004 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FGamepadInfo& other) const { return memcmp(this, &other, sizeof(FGamepadInfo)) == 0; }
	bool operator!=(const FGamepadInfo& other) const { return !(*this == other); }
	bool operator<(const FGamepadInfo& other) const { return memcmp(this, &other, sizeof(FGamepadInfo)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.PerPlayerSplitscreenData
// 0x0010
struct FPerPlayerSplitscreenData
{
	float                                              SizeX;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              SizeY;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              OriginX;                                       // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              OriginY;                                       // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FPerPlayerSplitscreenData& other) const { return memcmp(this, &other, sizeof(FPerPlayerSplitscreenData)) == 0; }
	bool operator!=(const FPerPlayerSplitscreenData& other) const { return !(*this == other); }
	bool operator<(const FPerPlayerSplitscreenData& other) const { return memcmp(this, &other, sizeof(FPerPlayerSplitscreenData)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.SplitscreenData
// 0x0010
struct FSplitscreenData
{
	class TArray<struct FPerPlayerSplitscreenData>     PlayerData;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FSplitscreenData& other) const { return memcmp(this, &other, sizeof(FSplitscreenData)) == 0; }
	bool operator!=(const FSplitscreenData& other) const { return !(*this == other); }
	bool operator<(const FSplitscreenData& other) const { return memcmp(this, &other, sizeof(FSplitscreenData)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.DebugDisplayProperty
// 0x0014
struct FDebugDisplayProperty
{
	class UObject*                                     Obj;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        PropertyName;                                  // 0x0008 (0x0008) [0x0000000000000000]               
	uint32_t                                           bSpecialProperty : 1;                          // 0x0010 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FDebugDisplayProperty& other) const { return memcmp(this, &other, sizeof(FDebugDisplayProperty)) == 0; }
	bool operator!=(const FDebugDisplayProperty& other) const { return !(*this == other); }
	bool operator<(const FDebugDisplayProperty& other) const { return memcmp(this, &other, sizeof(FDebugDisplayProperty)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.TitleSafeZoneArea
// 0x0010
struct FTitleSafeZoneArea
{
	float                                              MaxPercentX;                                   // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              MaxPercentY;                                   // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              RecommendedPercentX;                           // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              RecommendedPercentY;                           // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FTitleSafeZoneArea& other) const { return memcmp(this, &other, sizeof(FTitleSafeZoneArea)) == 0; }
	bool operator!=(const FTitleSafeZoneArea& other) const { return !(*this == other); }
	bool operator<(const FTitleSafeZoneArea& other) const { return memcmp(this, &other, sizeof(FTitleSafeZoneArea)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.ShowFlags_Mirror
// 0x0010
struct FShowFlags_Mirror
{
	uint64_t                                           flags0;                                        // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	uint64_t                                           flags1;                                        // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FShowFlags_Mirror& other) const { return memcmp(this, &other, sizeof(FShowFlags_Mirror)) == 0; }
	bool operator!=(const FShowFlags_Mirror& other) const { return !(*this == other); }
	bool operator<(const FShowFlags_Mirror& other) const { return memcmp(this, &other, sizeof(FShowFlags_Mirror)) < 0; }
};

// ScriptStruct Engine.GameViewportClient.ExportShowFlags_Mirror
// 0x0000 (0x0010 - 0x0010)
struct FExportShowFlags_Mirror : FShowFlags_Mirror
{

	bool operator==(const FExportShowFlags_Mirror& other) const { return memcmp(this, &other, sizeof(FExportShowFlags_Mirror)) == 0; }
	bool operator!=(const FExportShowFlags_Mirror& other) const { return !(*this == other); }
	bool operator<(const FExportShowFlags_Mirror& other) const { return memcmp(this, &other, sizeof(FExportShowFlags_Mirror)) < 0; }
};

// ScriptStruct Engine.HeadTrackingComponent.ActorToLookAt
// 0x001C
struct FActorToLookAt
{
	class AActor*                                      Actor;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Rating;                                        // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              EnteredTime;                                   // 0x000C (0x0004) [0x0000000000000000]               
	float                                              LastKnownDistance;                             // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              StartTimeBeingLookedAt;                        // 0x0014 (0x0004) [0x0000000000000000]               
	uint32_t                                           CurrentlyBeingLookedAt : 1;                    // 0x0018 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FActorToLookAt& other) const { return memcmp(this, &other, sizeof(FActorToLookAt)) == 0; }
	bool operator!=(const FActorToLookAt& other) const { return !(*this == other); }
	bool operator<(const FActorToLookAt& other) const { return memcmp(this, &other, sizeof(FActorToLookAt)) < 0; }
};

// ScriptStruct Engine.IniLocPatcher.IniLocFileEntry
// 0x0035
struct FIniLocFileEntry
{
	class FString                                      Filename;                                      // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DLName;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      HashCode;                                      // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsUnicode : 1;                                // 0x0030 (0x0004) [0x0000000000000000] [0x00000001] 
	EOnlineEnumerationReadState                        ReadState;                                     // 0x0034 (0x0001) [0x0000000000000000]               

	bool operator==(const FIniLocFileEntry& other) const { return memcmp(this, &other, sizeof(FIniLocFileEntry)) == 0; }
	bool operator!=(const FIniLocFileEntry& other) const { return !(*this == other); }
	bool operator<(const FIniLocFileEntry& other) const { return memcmp(this, &other, sizeof(FIniLocFileEntry)) < 0; }
};

// ScriptStruct Engine.Input.KeyBind
// 0x001C
struct FKeyBind
{
	class FName                                        Name;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      Command;                                       // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           Control : 1;                                   // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           Shift : 1;                                     // 0x0018 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           Alt : 1;                                       // 0x0018 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bIgnoreCtrl : 1;                               // 0x0018 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bIgnoreShift : 1;                              // 0x0018 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bIgnoreAlt : 1;                                // 0x0018 (0x0004) [0x0000000000000000] [0x100000020] 

	bool operator==(const FKeyBind& other) const { return memcmp(this, &other, sizeof(FKeyBind)) == 0; }
	bool operator!=(const FKeyBind& other) const { return !(*this == other); }
	bool operator<(const FKeyBind& other) const { return memcmp(this, &other, sizeof(FKeyBind)) < 0; }
};

// ScriptStruct Engine.Input.TouchTracker
// 0x0018
struct FTouchTracker
{
	int32_t                                            Handle;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            TouchpadIndex;                                 // 0x0004 (0x0004) [0x0000000000000000]               
	struct FVector2D                                   Location;                                      // 0x0008 (0x0008) [0x0000000000000000]               
	EInputEvent                                        EventType;                                     // 0x0010 (0x0001) [0x0000000000000000]               
	uint32_t                                           bTrapInput : 1;                                // 0x0014 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FTouchTracker& other) const { return memcmp(this, &other, sizeof(FTouchTracker)) == 0; }
	bool operator!=(const FTouchTracker& other) const { return !(*this == other); }
	bool operator<(const FTouchTracker& other) const { return memcmp(this, &other, sizeof(FTouchTracker)) < 0; }
};

// ScriptStruct Engine.InstancedStaticMeshComponent.InstancedStaticMeshInstanceData
// 0x0050
struct FInstancedStaticMeshInstanceData
{
	struct FMatrix                                     Transform;                                     // 0x0000 (0x0040) [0x0000000000000000]               
	struct FVector2D                                   LightmapUVBias;                                // 0x0040 (0x0008) [0x0000000000000000]               
	struct FVector2D                                   ShadowmapUVBias;                               // 0x0048 (0x0008) [0x0000000000000000]               

	bool operator==(const FInstancedStaticMeshInstanceData& other) const { return memcmp(this, &other, sizeof(FInstancedStaticMeshInstanceData)) == 0; }
	bool operator!=(const FInstancedStaticMeshInstanceData& other) const { return !(*this == other); }
	bool operator<(const FInstancedStaticMeshInstanceData& other) const { return memcmp(this, &other, sizeof(FInstancedStaticMeshInstanceData)) < 0; }
};

// ScriptStruct Engine.InstancedStaticMeshComponent.InstancedStaticMeshMappingInfo
// 0x0020
struct FInstancedStaticMeshMappingInfo
{
	struct FPointer                                    Mapping;                                       // 0x0000 (0x0008) [0x0000000000001000] (CPF_Native)  
	struct FPointer                                    LightMap;                                      // 0x0008 (0x0008) [0x0000000000001000] (CPF_Native)  
	class UTexture2D*                                  LightmapTexture;                               // 0x0010 (0x0008) [0x0000000000000000]               
	class UShadowMap2D*                                ShadowmapTexture;                              // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FInstancedStaticMeshMappingInfo& other) const { return memcmp(this, &other, sizeof(FInstancedStaticMeshMappingInfo)) == 0; }
	bool operator!=(const FInstancedStaticMeshMappingInfo& other) const { return !(*this == other); }
	bool operator<(const FInstancedStaticMeshMappingInfo& other) const { return memcmp(this, &other, sizeof(FInstancedStaticMeshMappingInfo)) < 0; }
};

// ScriptStruct Engine.StaticMeshActor.PreCombinedStaticMeshActor
// 0x0048
struct FPreCombinedStaticMeshActor
{
	class UStaticMesh*                                 Mesh;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector                                     Location;                                      // 0x0008 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0014 (0x000C) [0x0000000000000000]               
	struct FVector                                     PrePivot;                                      // 0x0020 (0x000C) [0x0000000000000000]               
	float                                              DrawScale;                                     // 0x002C (0x0004) [0x0000000000000000]               
	struct FVector                                     DrawScale3D;                                   // 0x0030 (0x000C) [0x0000000000000000]               
	struct FVector                                     ComponentScale3D;                              // 0x003C (0x000C) [0x0000000000000000]               

	bool operator==(const FPreCombinedStaticMeshActor& other) const { return memcmp(this, &other, sizeof(FPreCombinedStaticMeshActor)) == 0; }
	bool operator!=(const FPreCombinedStaticMeshActor& other) const { return !(*this == other); }
	bool operator<(const FPreCombinedStaticMeshActor& other) const { return memcmp(this, &other, sizeof(FPreCombinedStaticMeshActor)) < 0; }
};

// ScriptStruct Engine.InterpActor.CheckpointRecord
// 0x0020
struct AInterpActor_FCheckpointRecord
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000000]               
	ECollisionType                                     CollisionType;                                 // 0x0018 (0x0001) [0x0000000000000000]               
	uint32_t                                           bHidden : 1;                                   // 0x001C (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsShutdown : 1;                               // 0x001C (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bNeedsPositionReplication : 1;                 // 0x001C (0x0004) [0x0000000000000000] [0x00000004] 

	bool operator==(const AInterpActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AInterpActor_FCheckpointRecord)) == 0; }
	bool operator!=(const AInterpActor_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const AInterpActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(AInterpActor_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.InterpCurveEdSetup.CurveEdEntry
// 0x0038
struct FCurveEdEntry
{
	class UObject*                                     CurveObject;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	struct FColor                                      CurveColor;                                    // 0x0008 (0x0004) [0x0000000000000000]               
	class FString                                      CurveName;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            bHideCurve;                                    // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            bColorCurve;                                   // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            bFloatingPointColorCurve;                      // 0x0028 (0x0004) [0x0000000000000000]               
	int32_t                                            bClamp;                                        // 0x002C (0x0004) [0x0000000000000000]               
	float                                              ClampLow;                                      // 0x0030 (0x0004) [0x0000000000000000]               
	float                                              ClampHigh;                                     // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FCurveEdEntry& other) const { return memcmp(this, &other, sizeof(FCurveEdEntry)) == 0; }
	bool operator!=(const FCurveEdEntry& other) const { return !(*this == other); }
	bool operator<(const FCurveEdEntry& other) const { return memcmp(this, &other, sizeof(FCurveEdEntry)) < 0; }
};

// ScriptStruct Engine.InterpCurveEdSetup.CurveEdTab
// 0x0030
struct FCurveEdTab
{
	class FString                                      TabName;                                       // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FCurveEdEntry>                 Curves;                                        // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              ViewStartInput;                                // 0x0020 (0x0004) [0x0000000000000000]               
	float                                              ViewEndInput;                                  // 0x0024 (0x0004) [0x0000000000000000]               
	float                                              ViewStartOutput;                               // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              ViewEndOutput;                                 // 0x002C (0x0004) [0x0000000000000000]               

	bool operator==(const FCurveEdTab& other) const { return memcmp(this, &other, sizeof(FCurveEdTab)) == 0; }
	bool operator!=(const FCurveEdTab& other) const { return !(*this == other); }
	bool operator<(const FCurveEdTab& other) const { return memcmp(this, &other, sizeof(FCurveEdTab)) < 0; }
};

// ScriptStruct Engine.InterpData.AnimSetBakeAndPruneStatus
// 0x0014
struct FAnimSetBakeAndPruneStatus
{
	class FString                                      AnimSetName;                                   // 0x0000 (0x0010) [0x0000000000420001] (CPF_Edit | CPF_EditConst | CPF_NeedCtorLink)
	uint32_t                                           bReferencedButUnused : 1;                      // 0x0010 (0x0004) [0x0000000000020001] [0x00000001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bSkipBakeAndPrune : 1;                         // 0x0010 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bSkipCooking : 1;                              // 0x0010 (0x0004) [0x0000000000000001] [0x100000004] (CPF_Edit)

	bool operator==(const FAnimSetBakeAndPruneStatus& other) const { return memcmp(this, &other, sizeof(FAnimSetBakeAndPruneStatus)) == 0; }
	bool operator!=(const FAnimSetBakeAndPruneStatus& other) const { return !(*this == other); }
	bool operator<(const FAnimSetBakeAndPruneStatus& other) const { return memcmp(this, &other, sizeof(FAnimSetBakeAndPruneStatus)) < 0; }
};

// ScriptStruct Engine.InterpGroup.InterpEdSelKey
// 0x0018
struct FInterpEdSelKey
{
	class UInterpGroup*                                Group;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	class UInterpTrack*                                Track;                                         // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            KeyIndex;                                      // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              UnsnappedPosition;                             // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FInterpEdSelKey& other) const { return memcmp(this, &other, sizeof(FInterpEdSelKey)) == 0; }
	bool operator!=(const FInterpEdSelKey& other) const { return !(*this == other); }
	bool operator<(const FInterpEdSelKey& other) const { return memcmp(this, &other, sizeof(FInterpEdSelKey)) < 0; }
};

// ScriptStruct Engine.InterpGroupCamera.CameraPreviewInfo
// 0x0040
struct FCameraPreviewInfo
{
	class UClass*                                      PawnClass;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UAnimSet*>                      PreviewAnimSets;                               // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FName                                        AnimSeqName;                                   // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Location;                                      // 0x0020 (0x000C) [0x0000000000020000] (CPF_EditConst)
	struct FRotator                                    Rotation;                                      // 0x002C (0x000C) [0x0000000000020000] (CPF_EditConst)
	class APawn*                                       PawnInst;                                      // 0x0038 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FCameraPreviewInfo& other) const { return memcmp(this, &other, sizeof(FCameraPreviewInfo)) == 0; }
	bool operator!=(const FCameraPreviewInfo& other) const { return !(*this == other); }
	bool operator<(const FCameraPreviewInfo& other) const { return memcmp(this, &other, sizeof(FCameraPreviewInfo)) < 0; }
};

// ScriptStruct Engine.InterpTrack.SubTrackGroup
// 0x0024
struct FSubTrackGroup
{
	class FString                                      GroupName;                                     // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<int32_t>                              TrackIndices;                                  // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bIsCollapsed : 1;                              // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bIsSelected : 1;                               // 0x0020 (0x0004) [0x0000000000002000] [0x00000002] (CPF_Transient)

	bool operator==(const FSubTrackGroup& other) const { return memcmp(this, &other, sizeof(FSubTrackGroup)) == 0; }
	bool operator!=(const FSubTrackGroup& other) const { return !(*this == other); }
	bool operator<(const FSubTrackGroup& other) const { return memcmp(this, &other, sizeof(FSubTrackGroup)) < 0; }
};

// ScriptStruct Engine.InterpTrack.SupportedSubTrackInfo
// 0x001C
struct FSupportedSubTrackInfo
{
	class UClass*                                      SupportedClass;                                // 0x0000 (0x0008) [0x0000000000000000]               
	class FString                                      SubTrackName;                                  // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            GroupIndex;                                    // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FSupportedSubTrackInfo& other) const { return memcmp(this, &other, sizeof(FSupportedSubTrackInfo)) == 0; }
	bool operator!=(const FSupportedSubTrackInfo& other) const { return !(*this == other); }
	bool operator<(const FSupportedSubTrackInfo& other) const { return memcmp(this, &other, sizeof(FSupportedSubTrackInfo)) < 0; }
};

// ScriptStruct Engine.InterpTrackAnimControl.AnimControlTrackKey
// 0x001C
struct FAnimControlTrackKey
{
	float                                              StartTime;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        AnimSeqName;                                   // 0x0004 (0x0008) [0x0000000000000000]               
	float                                              AnimStartOffset;                               // 0x000C (0x0004) [0x0000000000000000]               
	float                                              AnimEndOffset;                                 // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              AnimPlayRate;                                  // 0x0014 (0x0004) [0x0000000000000000]               
	uint32_t                                           bLooping : 1;                                  // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bReverse : 1;                                  // 0x0018 (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FAnimControlTrackKey& other) const { return memcmp(this, &other, sizeof(FAnimControlTrackKey)) == 0; }
	bool operator!=(const FAnimControlTrackKey& other) const { return !(*this == other); }
	bool operator<(const FAnimControlTrackKey& other) const { return memcmp(this, &other, sizeof(FAnimControlTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackBoolProp.BoolTrackKey
// 0x0008
struct FBoolTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	uint32_t                                           Value : 1;                                     // 0x0004 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FBoolTrackKey& other) const { return memcmp(this, &other, sizeof(FBoolTrackKey)) == 0; }
	bool operator!=(const FBoolTrackKey& other) const { return !(*this == other); }
	bool operator<(const FBoolTrackKey& other) const { return memcmp(this, &other, sizeof(FBoolTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackDirector.DirectorTrackCut
// 0x0014
struct FDirectorTrackCut
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              TransitionTime;                                // 0x0004 (0x0004) [0x0000000000000000]               
	class FName                                        TargetCamGroup;                                // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ShotNumber;                                    // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FDirectorTrackCut& other) const { return memcmp(this, &other, sizeof(FDirectorTrackCut)) == 0; }
	bool operator!=(const FDirectorTrackCut& other) const { return !(*this == other); }
	bool operator<(const FDirectorTrackCut& other) const { return memcmp(this, &other, sizeof(FDirectorTrackCut)) < 0; }
};

// ScriptStruct Engine.InterpTrackEvent.EventTrackKey
// 0x000C
struct FEventTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class FName                                        EventName;                                     // 0x0004 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FEventTrackKey& other) const { return memcmp(this, &other, sizeof(FEventTrackKey)) == 0; }
	bool operator!=(const FEventTrackKey& other) const { return !(*this == other); }
	bool operator<(const FEventTrackKey& other) const { return memcmp(this, &other, sizeof(FEventTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackFaceFX.FaceFXTrackKey
// 0x0028
struct FFaceFXTrackKey
{
	float                                              StartTime;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	class FString                                      FaceFXGroupName;                               // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      FaceFXSeqName;                                 // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFaceFXTrackKey& other) const { return memcmp(this, &other, sizeof(FFaceFXTrackKey)) == 0; }
	bool operator!=(const FFaceFXTrackKey& other) const { return !(*this == other); }
	bool operator<(const FFaceFXTrackKey& other) const { return memcmp(this, &other, sizeof(FFaceFXTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackFaceFX.FaceFXSoundCueKey
// 0x0010
struct FFaceFXSoundCueKey
{
	class USoundCue*                                   FaceFXSoundCue;                                // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UAkEvent*                                    FaceFXAkEvent;                                 // 0x0008 (0x0008) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FFaceFXSoundCueKey& other) const { return memcmp(this, &other, sizeof(FFaceFXSoundCueKey)) == 0; }
	bool operator!=(const FFaceFXSoundCueKey& other) const { return !(*this == other); }
	bool operator<(const FFaceFXSoundCueKey& other) const { return memcmp(this, &other, sizeof(FFaceFXSoundCueKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackHeadTracking.HeadTrackingKey
// 0x0005
struct FHeadTrackingKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	EHeadTrackingAction                                Action;                                        // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FHeadTrackingKey& other) const { return memcmp(this, &other, sizeof(FHeadTrackingKey)) == 0; }
	bool operator!=(const FHeadTrackingKey& other) const { return !(*this == other); }
	bool operator<(const FHeadTrackingKey& other) const { return memcmp(this, &other, sizeof(FHeadTrackingKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackInstFloatMaterialParam.FloatMaterialParamMICData
// 0x0020
struct FFloatMaterialParamMICData
{
	class TArray<class UMaterialInstanceConstant*>     MICs;                                          // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<float>                                MICResetFloats;                                // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FFloatMaterialParamMICData& other) const { return memcmp(this, &other, sizeof(FFloatMaterialParamMICData)) == 0; }
	bool operator!=(const FFloatMaterialParamMICData& other) const { return !(*this == other); }
	bool operator<(const FFloatMaterialParamMICData& other) const { return memcmp(this, &other, sizeof(FFloatMaterialParamMICData)) < 0; }
};

// ScriptStruct Engine.InterpTrackToggle.ToggleTrackKey
// 0x0005
struct FToggleTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	ETrackToggleAction                                 ToggleAction;                                  // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FToggleTrackKey& other) const { return memcmp(this, &other, sizeof(FToggleTrackKey)) == 0; }
	bool operator!=(const FToggleTrackKey& other) const { return !(*this == other); }
	bool operator<(const FToggleTrackKey& other) const { return memcmp(this, &other, sizeof(FToggleTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackInstVectorMaterialParam.VectorMaterialParamMICData
// 0x0020
struct FVectorMaterialParamMICData
{
	class TArray<class UMaterialInstanceConstant*>     MICs;                                          // 0x0000 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FVector>                       MICResetVectors;                               // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FVectorMaterialParamMICData& other) const { return memcmp(this, &other, sizeof(FVectorMaterialParamMICData)) == 0; }
	bool operator!=(const FVectorMaterialParamMICData& other) const { return !(*this == other); }
	bool operator<(const FVectorMaterialParamMICData& other) const { return memcmp(this, &other, sizeof(FVectorMaterialParamMICData)) < 0; }
};

// ScriptStruct Engine.InterpTrackVisibility.VisibilityTrackKey
// 0x0006
struct FVisibilityTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	EVisibilityTrackAction                             Action;                                        // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    
	EVisibilityTrackCondition                          ActiveCondition;                               // 0x0005 (0x0001) [0x0000000000000000]               

	bool operator==(const FVisibilityTrackKey& other) const { return memcmp(this, &other, sizeof(FVisibilityTrackKey)) == 0; }
	bool operator!=(const FVisibilityTrackKey& other) const { return !(*this == other); }
	bool operator<(const FVisibilityTrackKey& other) const { return memcmp(this, &other, sizeof(FVisibilityTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackMove.InterpLookupPoint
// 0x000C
struct FInterpLookupPoint
{
	class FName                                        GroupName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	float                                              Time;                                          // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FInterpLookupPoint& other) const { return memcmp(this, &other, sizeof(FInterpLookupPoint)) == 0; }
	bool operator!=(const FInterpLookupPoint& other) const { return !(*this == other); }
	bool operator<(const FInterpLookupPoint& other) const { return memcmp(this, &other, sizeof(FInterpLookupPoint)) < 0; }
};

// ScriptStruct Engine.InterpTrackMove.InterpLookupTrack
// 0x0010
struct FInterpLookupTrack
{
	class TArray<struct FInterpLookupPoint>            Points;                                        // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FInterpLookupTrack& other) const { return memcmp(this, &other, sizeof(FInterpLookupTrack)) == 0; }
	bool operator!=(const FInterpLookupTrack& other) const { return !(*this == other); }
	bool operator<(const FInterpLookupTrack& other) const { return memcmp(this, &other, sizeof(FInterpLookupTrack)) < 0; }
};

// ScriptStruct Engine.InterpTrackNotify.NotifyTrackKey
// 0x0010
struct FNotifyTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	class UAnimNotify*                                 Notify;                                        // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FNotifyTrackKey& other) const { return memcmp(this, &other, sizeof(FNotifyTrackKey)) == 0; }
	bool operator!=(const FNotifyTrackKey& other) const { return !(*this == other); }
	bool operator<(const FNotifyTrackKey& other) const { return memcmp(this, &other, sizeof(FNotifyTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackParticleReplay.ParticleReplayTrackKey
// 0x000C
struct FParticleReplayTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Duration;                                      // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ClipIDNumber;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FParticleReplayTrackKey& other) const { return memcmp(this, &other, sizeof(FParticleReplayTrackKey)) == 0; }
	bool operator!=(const FParticleReplayTrackKey& other) const { return !(*this == other); }
	bool operator<(const FParticleReplayTrackKey& other) const { return memcmp(this, &other, sizeof(FParticleReplayTrackKey)) < 0; }
};

// ScriptStruct Engine.InterpTrackSound.SoundTrackKey
// 0x0018
struct FSoundTrackKey
{
	float                                              Time;                                          // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Volume;                                        // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              Pitch;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	class USoundCue*                                   Sound;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSoundTrackKey& other) const { return memcmp(this, &other, sizeof(FSoundTrackKey)) == 0; }
	bool operator!=(const FSoundTrackKey& other) const { return !(*this == other); }
	bool operator<(const FSoundTrackKey& other) const { return memcmp(this, &other, sizeof(FSoundTrackKey)) < 0; }
};

// ScriptStruct Engine.LandscapeProxy.LandscapeLayerStruct
// 0x0030
struct FLandscapeLayerStruct
{
	class ULandscapeLayerInfoObject*                   LayerInfoObj;                                  // 0x0000 (0x0008) [0x0000000000000000]               
	class UMaterialInstanceConstant*                   ThumbnailMIC;                                  // 0x0008 (0x0008) [0x0000000800000000] (CPF_EditorOnly)
	class ALandscapeProxy*                             Owner;                                         // 0x0010 (0x0008) [0x0000000800000000] (CPF_EditorOnly)
	int32_t                                            DebugColorChannel;                             // 0x0018 (0x0004) [0x0000000800002000] (CPF_Transient | CPF_EditorOnly)
	uint32_t                                           bSelected : 1;                                 // 0x001C (0x0004) [0x0000000800002000] [0x100000001] (CPF_Transient | CPF_EditorOnly)
	class FString                                      SourceFilePath;                                // 0x0020 (0x0010) [0x0000000800400000] (CPF_NeedCtorLink | CPF_EditorOnly)

	bool operator==(const FLandscapeLayerStruct& other) const { return memcmp(this, &other, sizeof(FLandscapeLayerStruct)) == 0; }
	bool operator!=(const FLandscapeLayerStruct& other) const { return !(*this == other); }
	bool operator<(const FLandscapeLayerStruct& other) const { return memcmp(this, &other, sizeof(FLandscapeLayerStruct)) < 0; }
};

// ScriptStruct Engine.LandscapeProxy.LandscapeWeightmapUsage
// 0x0020
struct FLandscapeWeightmapUsage
{
	class ULandscapeComponent*                         ChannelUsage[4];                               // 0x0000 (0x0020) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)

	bool operator==(const FLandscapeWeightmapUsage& other) const { return memcmp(this, &other, sizeof(FLandscapeWeightmapUsage)) == 0; }
	bool operator!=(const FLandscapeWeightmapUsage& other) const { return !(*this == other); }
	bool operator<(const FLandscapeWeightmapUsage& other) const { return memcmp(this, &other, sizeof(FLandscapeWeightmapUsage)) < 0; }
};

// ScriptStruct Engine.Landscape.LandscapeLayerInfo
// 0x0038
struct FLandscapeLayerInfo
{
	class FName                                        LayerName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              Hardness;                                      // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bNoWeightBlend : 1;                            // 0x000C (0x0004) [0x0000000800000000] [0x00000001] (CPF_EditorOnly)
	class UPhysicalMaterial*                           PhysMaterial;                                  // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInstanceConstant*                   ThumbnailMIC;                                  // 0x0018 (0x0008) [0x0000000800000000] (CPF_EditorOnly)
	uint32_t                                           bSelected : 1;                                 // 0x0020 (0x0004) [0x0000000800002000] [0x100000001] (CPF_Transient | CPF_EditorOnly)
	int32_t                                            DebugColorChannel;                             // 0x0024 (0x0004) [0x0000000800002000] (CPF_Transient | CPF_EditorOnly)
	class FString                                      LayerSourceFile;                               // 0x0028 (0x0010) [0x0000000800402000] (CPF_Transient | CPF_NeedCtorLink | CPF_EditorOnly)

	bool operator==(const FLandscapeLayerInfo& other) const { return memcmp(this, &other, sizeof(FLandscapeLayerInfo)) == 0; }
	bool operator!=(const FLandscapeLayerInfo& other) const { return !(*this == other); }
	bool operator<(const FLandscapeLayerInfo& other) const { return memcmp(this, &other, sizeof(FLandscapeLayerInfo)) < 0; }
};

// ScriptStruct Engine.LandscapeComponent.WeightmapLayerAllocationInfo
// 0x000A
struct FWeightmapLayerAllocationInfo
{
	class FName                                        LayerName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	uint8_t                                            WeightmapTextureIndex;                         // 0x0008 (0x0001) [0x0000000000000000]               
	uint8_t                                            WeightmapTextureChannel;                       // 0x0009 (0x0001) [0x0000000000000000]               

	bool operator==(const FWeightmapLayerAllocationInfo& other) const { return memcmp(this, &other, sizeof(FWeightmapLayerAllocationInfo)) == 0; }
	bool operator!=(const FWeightmapLayerAllocationInfo& other) const { return !(*this == other); }
	bool operator<(const FWeightmapLayerAllocationInfo& other) const { return memcmp(this, &other, sizeof(FWeightmapLayerAllocationInfo)) < 0; }
};

// ScriptStruct Engine.LandscapeGizmoActiveActor.GizmoSelectData
// 0x0058
struct FGizmoSelectData
{
	float                                              Ratio;                                         // 0x0000 (0x0004) [0x0000000800000000] (CPF_EditorOnly)
	float                                              HeightData;                                    // 0x0004 (0x0004) [0x0000000800000000] (CPF_EditorOnly)
	uint8_t                                            UnknownData00[0x50];                            // 0x0008 (0x0050) MISSED OFFSET

	bool operator==(const FGizmoSelectData& other) const { return memcmp(this, &other, sizeof(FGizmoSelectData)) == 0; }
	bool operator!=(const FGizmoSelectData& other) const { return !(*this == other); }
	bool operator<(const FGizmoSelectData& other) const { return memcmp(this, &other, sizeof(FGizmoSelectData)) < 0; }
};

// ScriptStruct Engine.LandscapeInfo.LandscapeAddCollision
// 0x0030
struct FLandscapeAddCollision
{
	struct FVector                                     Corners[4];                                    // 0x0000 (0x0030) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FLandscapeAddCollision& other) const { return memcmp(this, &other, sizeof(FLandscapeAddCollision)) == 0; }
	bool operator!=(const FLandscapeAddCollision& other) const { return !(*this == other); }
	bool operator<(const FLandscapeAddCollision& other) const { return memcmp(this, &other, sizeof(FLandscapeAddCollision)) < 0; }
};

// ScriptStruct Engine.MaterialInstance.FontParameterValue
// 0x0024
struct FFontParameterValue
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UFont*                                       FontValue;                                     // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            FontPage;                                      // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       ExpressionGUID;                                // 0x0014 (0x0010) [0x0000000000000000]               

	bool operator==(const FFontParameterValue& other) const { return memcmp(this, &other, sizeof(FFontParameterValue)) == 0; }
	bool operator!=(const FFontParameterValue& other) const { return !(*this == other); }
	bool operator<(const FFontParameterValue& other) const { return memcmp(this, &other, sizeof(FFontParameterValue)) < 0; }
};

// ScriptStruct Engine.MaterialInstance.ScalarParameterValue
// 0x001C
struct FScalarParameterValue
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              ParameterValue;                                // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       ExpressionGUID;                                // 0x000C (0x0010) [0x0000000000000000]               

	bool operator==(const FScalarParameterValue& other) const { return memcmp(this, &other, sizeof(FScalarParameterValue)) == 0; }
	bool operator!=(const FScalarParameterValue& other) const { return !(*this == other); }
	bool operator<(const FScalarParameterValue& other) const { return memcmp(this, &other, sizeof(FScalarParameterValue)) < 0; }
};

// ScriptStruct Engine.MaterialInstance.TextureParameterValue
// 0x0020
struct FTextureParameterValue
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class UTexture*                                    ParameterValue;                                // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       ExpressionGUID;                                // 0x0010 (0x0010) [0x0000000000000000]               

	bool operator==(const FTextureParameterValue& other) const { return memcmp(this, &other, sizeof(FTextureParameterValue)) == 0; }
	bool operator!=(const FTextureParameterValue& other) const { return !(*this == other); }
	bool operator<(const FTextureParameterValue& other) const { return memcmp(this, &other, sizeof(FTextureParameterValue)) < 0; }
};

// ScriptStruct Engine.MaterialInstance.VectorParameterValue
// 0x0028
struct FVectorParameterValue
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                ParameterValue;                                // 0x0008 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FGuid                                       ExpressionGUID;                                // 0x0018 (0x0010) [0x0000000000000000]               

	bool operator==(const FVectorParameterValue& other) const { return memcmp(this, &other, sizeof(FVectorParameterValue)) == 0; }
	bool operator!=(const FVectorParameterValue& other) const { return !(*this == other); }
	bool operator<(const FVectorParameterValue& other) const { return memcmp(this, &other, sizeof(FVectorParameterValue)) < 0; }
};

// ScriptStruct Engine.LensFlare.LensFlareElement
// 0x01C8
struct FLensFlareElement
{
	class FName                                        ElementName;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              RayDistance;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bIsEnabled : 1;                                // 0x000C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bUseSourceDistance : 1;                        // 0x000C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bNormalizeRadialDistance : 1;                  // 0x000C (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bModulateColorBySource : 1;                    // 0x000C (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	struct FVector                                     Size;                                          // 0x0010 (0x000C) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UMaterialInterface*>            LFMaterials;                                   // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	struct FRawDistributionFloat                       LFMaterialIndex;                               // 0x0030 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionFloat                       Scaling;                                       // 0x0058 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionVector                      AxisScaling;                                   // 0x0080 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionFloat                       Rotation;                                      // 0x00A8 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	uint32_t                                           bOrientTowardsSource : 1;                      // 0x00D0 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FRawDistributionVector                      Color;                                         // 0x00D8 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionFloat                       Alpha;                                         // 0x0100 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionVector                      Offset;                                        // 0x0128 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionVector                      DistMap_Scale;                                 // 0x0150 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionVector                      DistMap_Color;                                 // 0x0178 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	struct FRawDistributionFloat                       DistMap_Alpha;                                 // 0x01A0 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)

	bool operator==(const FLensFlareElement& other) const { return memcmp(this, &other, sizeof(FLensFlareElement)) == 0; }
	bool operator!=(const FLensFlareElement& other) const { return !(*this == other); }
	bool operator<(const FLensFlareElement& other) const { return memcmp(this, &other, sizeof(FLensFlareElement)) < 0; }
};

// ScriptStruct Engine.LensFlare.LensFlareElementCurvePair
// 0x0018
struct FLensFlareElementCurvePair
{
	class FString                                      CurveName;                                     // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UObject*                                     CurveObject;                                   // 0x0010 (0x0008) [0x0000000000100000]               

	bool operator==(const FLensFlareElementCurvePair& other) const { return memcmp(this, &other, sizeof(FLensFlareElementCurvePair)) == 0; }
	bool operator!=(const FLensFlareElementCurvePair& other) const { return !(*this == other); }
	bool operator<(const FLensFlareElementCurvePair& other) const { return memcmp(this, &other, sizeof(FLensFlareElementCurvePair)) < 0; }
};

// ScriptStruct Engine.LensFlareComponent.LensFlareElementMaterials
// 0x0010
struct FLensFlareElementMaterials
{
	class TArray<class UMaterialInterface*>            ElementMaterials;                              // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FLensFlareElementMaterials& other) const { return memcmp(this, &other, sizeof(FLensFlareElementMaterials)) == 0; }
	bool operator!=(const FLensFlareElementMaterials& other) const { return !(*this == other); }
	bool operator<(const FLensFlareElementMaterials& other) const { return memcmp(this, &other, sizeof(FLensFlareElementMaterials)) < 0; }
};

// ScriptStruct Engine.LensFlareComponent.LensFlareElementInstance
// 0x0000
struct FLensFlareElementInstance
{

	bool operator==(const FLensFlareElementInstance& other) const { return memcmp(this, &other, sizeof(FLensFlareElementInstance)) == 0; }
	bool operator!=(const FLensFlareElementInstance& other) const { return !(*this == other); }
	bool operator<(const FLensFlareElementInstance& other) const { return memcmp(this, &other, sizeof(FLensFlareElementInstance)) < 0; }
};

// ScriptStruct Engine.LevelGridVolume.LevelGridCellCoordinate
// 0x000C
struct FLevelGridCellCoordinate
{
	int32_t                                            X;                                             // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Y;                                             // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Z;                                             // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FLevelGridCellCoordinate& other) const { return memcmp(this, &other, sizeof(FLevelGridCellCoordinate)) == 0; }
	bool operator!=(const FLevelGridCellCoordinate& other) const { return !(*this == other); }
	bool operator<(const FLevelGridCellCoordinate& other) const { return memcmp(this, &other, sizeof(FLevelGridCellCoordinate)) < 0; }
};

// ScriptStruct Engine.LevelStreamingVolume.CheckpointRecord
// 0x0004
struct ALevelStreamingVolume_FCheckpointRecord
{
	uint32_t                                           bDisabled : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const ALevelStreamingVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ALevelStreamingVolume_FCheckpointRecord)) == 0; }
	bool operator!=(const ALevelStreamingVolume_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ALevelStreamingVolume_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ALevelStreamingVolume_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.LinkedAccountDetails.LinkedAccountData
// 0x00A8
struct FLinkedAccountData
{
	uint32_t                                           bSuccess : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FUniqueNetId                                OriginalId;                                    // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FUniqueNetId                                LinkedId;                                      // 0x0050 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      LinkedDisplayName;                             // 0x0098 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLinkedAccountData& other) const { return memcmp(this, &other, sizeof(FLinkedAccountData)) == 0; }
	bool operator!=(const FLinkedAccountData& other) const { return !(*this == other); }
	bool operator<(const FLinkedAccountData& other) const { return memcmp(this, &other, sizeof(FLinkedAccountData)) < 0; }
};

// ScriptStruct Engine.OnlineAuthInterface.BaseAuthSession
// 0x0060
struct FBaseAuthSession
{
	struct FIpAddr                                     EndPointIP;                                    // 0x0000 (0x0014) [0x0000000000000002] (CPF_Const)   
	int32_t                                            EndPointPort;                                  // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	struct FUniqueNetId                                EndPointUID;                                   // 0x0018 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FBaseAuthSession& other) const { return memcmp(this, &other, sizeof(FBaseAuthSession)) == 0; }
	bool operator!=(const FBaseAuthSession& other) const { return !(*this == other); }
	bool operator<(const FBaseAuthSession& other) const { return memcmp(this, &other, sizeof(FBaseAuthSession)) < 0; }
};

// ScriptStruct Engine.LocalPlayer.PostProcessSettingsOverride
// 0x0198
struct FPostProcessSettingsOverride
{
	struct FPostProcessSettings                        Settings;                                      // 0x0000 (0x0168) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bBlendingIn : 1;                               // 0x0168 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bBlendingOut : 1;                              // 0x0168 (0x0004) [0x0000000000000000] [0x00000002] 
	float                                              CurrentBlendInTime;                            // 0x016C (0x0004) [0x0000000000000000]               
	float                                              CurrentBlendOutTime;                           // 0x0170 (0x0004) [0x0000000000000000]               
	float                                              BlendInDuration;                               // 0x0174 (0x0004) [0x0000000000000000]               
	float                                              BlendOutDuration;                              // 0x0178 (0x0004) [0x0000000000000000]               
	float                                              BlendStartTime;                                // 0x017C (0x0004) [0x0000000000000000]               
	struct FInterpCurveFloat                           TimeAlphaCurve;                                // 0x0180 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPostProcessSettingsOverride& other) const { return memcmp(this, &other, sizeof(FPostProcessSettingsOverride)) == 0; }
	bool operator!=(const FPostProcessSettingsOverride& other) const { return !(*this == other); }
	bool operator<(const FPostProcessSettingsOverride& other) const { return memcmp(this, &other, sizeof(FPostProcessSettingsOverride)) < 0; }
};

// ScriptStruct Engine.LocalPlayer.CurrentPostProcessVolumeInfo
// 0x0178
struct FCurrentPostProcessVolumeInfo
{
	struct FPostProcessSettings                        LastSettings;                                  // 0x0000 (0x0168) [0x0000000000400000] (CPF_NeedCtorLink)
	class APostProcessVolume*                          LastVolumeUsed;                                // 0x0168 (0x0008) [0x0000000000000000]               
	float                                              BlendStartTime;                                // 0x0170 (0x0004) [0x0000000000000000]               
	float                                              LastBlendTime;                                 // 0x0174 (0x0004) [0x0000000000000000]               

	bool operator==(const FCurrentPostProcessVolumeInfo& other) const { return memcmp(this, &other, sizeof(FCurrentPostProcessVolumeInfo)) == 0; }
	bool operator!=(const FCurrentPostProcessVolumeInfo& other) const { return !(*this == other); }
	bool operator<(const FCurrentPostProcessVolumeInfo& other) const { return memcmp(this, &other, sizeof(FCurrentPostProcessVolumeInfo)) < 0; }
};

// ScriptStruct Engine.LocalPlayer.SynchronizedActorVisibilityHistory
// 0x0010
struct FSynchronizedActorVisibilityHistory
{
	struct FPointer                                    State;                                         // 0x0000 (0x0008) [0x0000000000000000]               
	struct FPointer                                    CriticalSection;                               // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FSynchronizedActorVisibilityHistory& other) const { return memcmp(this, &other, sizeof(FSynchronizedActorVisibilityHistory)) == 0; }
	bool operator!=(const FSynchronizedActorVisibilityHistory& other) const { return !(*this == other); }
	bool operator<(const FSynchronizedActorVisibilityHistory& other) const { return memcmp(this, &other, sizeof(FSynchronizedActorVisibilityHistory)) < 0; }
};

// ScriptStruct Engine.OnlineAuthInterface.AuthSession
// 0x0008 (0x0060 - 0x0068)
struct FAuthSession : FBaseAuthSession
{
	EAuthStatus                                        AuthStatus;                                    // 0x0060 (0x0001) [0x0000000000000002] (CPF_Const)   
	int32_t                                            AuthTicketUID;                                 // 0x0064 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FAuthSession& other) const { return memcmp(this, &other, sizeof(FAuthSession)) == 0; }
	bool operator!=(const FAuthSession& other) const { return !(*this == other); }
	bool operator<(const FAuthSession& other) const { return memcmp(this, &other, sizeof(FAuthSession)) < 0; }
};

// ScriptStruct Engine.OnlineAuthInterface.LocalAuthSession
// 0x0004 (0x0060 - 0x0064)
struct FLocalAuthSession : FBaseAuthSession
{
	int32_t                                            SessionUID;                                    // 0x0060 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FLocalAuthSession& other) const { return memcmp(this, &other, sizeof(FLocalAuthSession)) == 0; }
	bool operator!=(const FLocalAuthSession& other) const { return !(*this == other); }
	bool operator<(const FLocalAuthSession& other) const { return memcmp(this, &other, sizeof(FLocalAuthSession)) < 0; }
};

// ScriptStruct Engine.MaterialExpression.ExpressionOutput
// 0x0024
struct FExpressionOutput
{
	class FString                                      OutputName;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Mask;                                          // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskR;                                         // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskG;                                         // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskB;                                         // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            MaskA;                                         // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FExpressionOutput& other) const { return memcmp(this, &other, sizeof(FExpressionOutput)) == 0; }
	bool operator!=(const FExpressionOutput& other) const { return !(*this == other); }
	bool operator<(const FExpressionOutput& other) const { return memcmp(this, &other, sizeof(FExpressionOutput)) < 0; }
};

// ScriptStruct Engine.MaterialExpression.ExpressionInput
// 0x0038
struct FExpressionInput
{
	class UMaterialExpression*                         Expression;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            OutputIndex;                                   // 0x0008 (0x0004) [0x0000000000000000]               
	class FString                                      InputName;                                     // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            Mask;                                          // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskR;                                         // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskG;                                         // 0x0028 (0x0004) [0x0000000000000000]               
	int32_t                                            MaskB;                                         // 0x002C (0x0004) [0x0000000000000000]               
	int32_t                                            MaskA;                                         // 0x0030 (0x0004) [0x0000000000000000]               
	int32_t                                            GCC64_Padding;                                 // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FExpressionInput& other) const { return memcmp(this, &other, sizeof(FExpressionInput)) == 0; }
	bool operator!=(const FExpressionInput& other) const { return !(*this == other); }
	bool operator<(const FExpressionInput& other) const { return memcmp(this, &other, sizeof(FExpressionInput)) < 0; }
};

// ScriptStruct Engine.MaterialExpressionCustom.CustomInput
// 0x0048
struct FCustomInput
{
	class FString                                      InputName;                                     // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	struct FExpressionInput                            Input;                                         // 0x0010 (0x0038) [0x0000020000400000] (CPF_NeedCtorLink | CPF_EditHide)

	bool operator==(const FCustomInput& other) const { return memcmp(this, &other, sizeof(FCustomInput)) == 0; }
	bool operator!=(const FCustomInput& other) const { return !(*this == other); }
	bool operator<(const FCustomInput& other) const { return memcmp(this, &other, sizeof(FCustomInput)) < 0; }
};

// ScriptStruct Engine.MaterialExpressionLandscapeLayerBlend.LayerBlendInput
// 0x0090
struct FLayerBlendInput
{
	class FName                                        LayerName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	ELandscapeLayerBlendType                           BlendType;                                     // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	struct FExpressionInput                            LayerInput;                                    // 0x0010 (0x0038) [0x0000020000400000] (CPF_NeedCtorLink | CPF_EditHide)
	struct FExpressionInput                            HeightInput;                                   // 0x0048 (0x0038) [0x0000020000400000] (CPF_NeedCtorLink | CPF_EditHide)
	float                                              PreviewWeight;                                 // 0x0080 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FPointer                                    InstanceOverride;                              // 0x0088 (0x0008) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FLayerBlendInput& other) const { return memcmp(this, &other, sizeof(FLayerBlendInput)) == 0; }
	bool operator!=(const FLayerBlendInput& other) const { return !(*this == other); }
	bool operator<(const FLayerBlendInput& other) const { return memcmp(this, &other, sizeof(FLayerBlendInput)) < 0; }
};

// ScriptStruct Engine.MaterialExpressionMaterialFunctionCall.FunctionExpressionInput
// 0x0050
struct FFunctionExpressionInput
{
	class UMaterialExpressionFunctionInput*            ExpressionInput;                               // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	struct FGuid                                       ExpressionInputId;                             // 0x0008 (0x0010) [0x0000000000000000]               
	struct FExpressionInput                            Input;                                         // 0x0018 (0x0038) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFunctionExpressionInput& other) const { return memcmp(this, &other, sizeof(FFunctionExpressionInput)) == 0; }
	bool operator!=(const FFunctionExpressionInput& other) const { return !(*this == other); }
	bool operator<(const FFunctionExpressionInput& other) const { return memcmp(this, &other, sizeof(FFunctionExpressionInput)) < 0; }
};

// ScriptStruct Engine.MaterialExpressionMaterialFunctionCall.FunctionExpressionOutput
// 0x0040
struct FFunctionExpressionOutput
{
	class UMaterialExpressionFunctionOutput*           ExpressionOutput;                              // 0x0000 (0x0008) [0x0000000000002000] (CPF_Transient)
	struct FGuid                                       ExpressionOutputId;                            // 0x0008 (0x0010) [0x0000000000000000]               
	struct FExpressionOutput                           Output;                                        // 0x0018 (0x0028) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FFunctionExpressionOutput& other) const { return memcmp(this, &other, sizeof(FFunctionExpressionOutput)) == 0; }
	bool operator!=(const FFunctionExpressionOutput& other) const { return !(*this == other); }
	bool operator<(const FFunctionExpressionOutput& other) const { return memcmp(this, &other, sizeof(FFunctionExpressionOutput)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.ParameterValueOverTime
// 0x0030
struct FParameterValueOverTime
{
	struct FGuid                                       ExpressionGUID;                                // 0x0000 (0x0010) [0x0000000000000000]               
	float                                              StartTime;                                     // 0x0010 (0x0004) [0x0000000000000000]               
	class FName                                        ParameterName;                                 // 0x0014 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bLoop : 1;                                     // 0x001C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bAutoActivate : 1;                             // 0x001C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	float                                              CycleTime;                                     // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bNormalizeTime : 1;                            // 0x0024 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              OffsetTime;                                    // 0x0028 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bOffsetFromEnd : 1;                            // 0x002C (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FParameterValueOverTime)) == 0; }
	bool operator!=(const FParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.FontParameterValueOverTime
// 0x000C (0x0030 - 0x003C)
struct FFontParameterValueOverTime : FParameterValueOverTime
{
	class UFont*                                       FontValue;                                     // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            FontPage;                                      // 0x0038 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFontParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FFontParameterValueOverTime)) == 0; }
	bool operator!=(const FFontParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FFontParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FFontParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.ScalarParameterValueOverTime
// 0x0020 (0x0030 - 0x0050)
struct FScalarParameterValueOverTime : FParameterValueOverTime
{
	float                                              ParameterValue;                                // 0x0030 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveFloat                           ParameterValueCurve;                           // 0x0038 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FScalarParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FScalarParameterValueOverTime)) == 0; }
	bool operator!=(const FScalarParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FScalarParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FScalarParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.TextureParameterValueOverTime
// 0x0008 (0x0030 - 0x0038)
struct FTextureParameterValueOverTime : FParameterValueOverTime
{
	class UTexture*                                    ParameterValue;                                // 0x0030 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTextureParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FTextureParameterValueOverTime)) == 0; }
	bool operator!=(const FTextureParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FTextureParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FTextureParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.VectorParameterValueOverTime
// 0x0028 (0x0030 - 0x0058)
struct FVectorParameterValueOverTime : FParameterValueOverTime
{
	struct FLinearColor                                ParameterValue;                                // 0x0030 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveVector                          ParameterValueCurve;                           // 0x0040 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FVectorParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FVectorParameterValueOverTime)) == 0; }
	bool operator!=(const FVectorParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FVectorParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FVectorParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MaterialInstanceTimeVarying.LinearColorParameterValueOverTime
// 0x0028 (0x0030 - 0x0058)
struct FLinearColorParameterValueOverTime : FParameterValueOverTime
{
	struct FLinearColor                                ParameterValue;                                // 0x0030 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FInterpCurveLinearColor                     ParameterValueCurve;                           // 0x0040 (0x0018) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FLinearColorParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FLinearColorParameterValueOverTime)) == 0; }
	bool operator!=(const FLinearColorParameterValueOverTime& other) const { return !(*this == other); }
	bool operator<(const FLinearColorParameterValueOverTime& other) const { return memcmp(this, &other, sizeof(FLinearColorParameterValueOverTime)) < 0; }
};

// ScriptStruct Engine.MicroTransactionBase.PurchaseInfo
// 0x0050
struct FPurchaseInfo
{
	class FString                                      Identifier;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayName;                                   // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayDescription;                            // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      DisplayPrice;                                  // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      CurrencyType;                                  // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FPurchaseInfo& other) const { return memcmp(this, &other, sizeof(FPurchaseInfo)) == 0; }
	bool operator!=(const FPurchaseInfo& other) const { return !(*this == other); }
	bool operator<(const FPurchaseInfo& other) const { return memcmp(this, &other, sizeof(FPurchaseInfo)) < 0; }
};

// ScriptStruct Engine.MorphNodeWeightBase.MorphNodeConn
// 0x001C
struct FMorphNodeConn
{
	class TArray<class UMorphNodeBase*>                ChildNodes;                                    // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FName                                        ConnName;                                      // 0x0010 (0x0008) [0x0000000000000000]               
	int32_t                                            DrawY;                                         // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FMorphNodeConn& other) const { return memcmp(this, &other, sizeof(FMorphNodeConn)) == 0; }
	bool operator!=(const FMorphNodeConn& other) const { return !(*this == other); }
	bool operator<(const FMorphNodeConn& other) const { return memcmp(this, &other, sizeof(FMorphNodeConn)) < 0; }
};

// ScriptStruct Engine.MorphNodeWeightByBoneAngle.BoneAngleMorph
// 0x0008
struct FBoneAngleMorph
{
	float                                              Angle;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              TargetWeight;                                  // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBoneAngleMorph& other) const { return memcmp(this, &other, sizeof(FBoneAngleMorph)) == 0; }
	bool operator!=(const FBoneAngleMorph& other) const { return !(*this == other); }
	bool operator<(const FBoneAngleMorph& other) const { return memcmp(this, &other, sizeof(FBoneAngleMorph)) < 0; }
};

// ScriptStruct Engine.NavigationHandle.PolySegmentSpan
// 0x0020
struct FPolySegmentSpan
{
	struct FPointer                                    Poly;                                          // 0x0000 (0x0008) [0x0000000000001000] (CPF_Native)  
	struct FVector                                     P1;                                            // 0x0008 (0x000C) [0x0000000000000000]               
	struct FVector                                     P2;                                            // 0x0014 (0x000C) [0x0000000000000000]               

	bool operator==(const FPolySegmentSpan& other) const { return memcmp(this, &other, sizeof(FPolySegmentSpan)) == 0; }
	bool operator!=(const FPolySegmentSpan& other) const { return !(*this == other); }
	bool operator<(const FPolySegmentSpan& other) const { return memcmp(this, &other, sizeof(FPolySegmentSpan)) < 0; }
};

// ScriptStruct Engine.NavigationHandle.NavMeshPathParams
// 0x0034
struct FNavMeshPathParams
{
	struct FPointer                                    Interface;                                     // 0x0000 (0x0008) [0x0000000000001000] (CPF_Native)  
	uint32_t                                           bCanMantle : 1;                                // 0x0008 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bNeedsMantleValidityTest : 1;                  // 0x0008 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bAbleToSearch : 1;                             // 0x0008 (0x0004) [0x0000000000000000] [0x00000004] 
	struct FVector                                     SearchExtent;                                  // 0x000C (0x000C) [0x0000000000000000]               
	float                                              SearchLaneMultiplier;                          // 0x0018 (0x0004) [0x0000000000000000]               
	struct FVector                                     SearchStart;                                   // 0x001C (0x000C) [0x0000000000000000]               
	float                                              MaxDropHeight;                                 // 0x0028 (0x0004) [0x0000000000000000]               
	float                                              MinWalkableZ;                                  // 0x002C (0x0004) [0x0000000000000000]               
	float                                              MaxHoverDistance;                              // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FNavMeshPathParams& other) const { return memcmp(this, &other, sizeof(FNavMeshPathParams)) == 0; }
	bool operator!=(const FNavMeshPathParams& other) const { return !(*this == other); }
	bool operator<(const FNavMeshPathParams& other) const { return memcmp(this, &other, sizeof(FNavMeshPathParams)) < 0; }
};

// ScriptStruct Engine.NavigationHandle.EdgePointer
// 0x0008
struct FEdgePointer
{
	struct FPointer                                    Dummy;                                         // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FEdgePointer& other) const { return memcmp(this, &other, sizeof(FEdgePointer)) == 0; }
	bool operator!=(const FEdgePointer& other) const { return !(*this == other); }
	bool operator<(const FEdgePointer& other) const { return memcmp(this, &other, sizeof(FEdgePointer)) < 0; }
};

// ScriptStruct Engine.NavigationHandle.PathStore
// 0x0010
struct FPathStore
{
	class TArray<struct FEdgePointer>                  EdgeList;                                      // 0x0000 (0x0010) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FPathStore& other) const { return memcmp(this, &other, sizeof(FPathStore)) == 0; }
	bool operator!=(const FPathStore& other) const { return !(*this == other); }
	bool operator<(const FPathStore& other) const { return memcmp(this, &other, sizeof(FPathStore)) < 0; }
};

// ScriptStruct Engine.NavMeshPathGoalEvaluator.BiasedGoalActor
// 0x000C
struct FBiasedGoalActor
{
	class AActor*                                      Goal;                                          // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            ExtraCost;                                     // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FBiasedGoalActor& other) const { return memcmp(this, &other, sizeof(FBiasedGoalActor)) == 0; }
	bool operator!=(const FBiasedGoalActor& other) const { return !(*this == other); }
	bool operator<(const FBiasedGoalActor& other) const { return memcmp(this, &other, sizeof(FBiasedGoalActor)) < 0; }
};

// ScriptStruct Engine.NavMeshObstacle.CheckpointRecord
// 0x0004
struct ANavMeshObstacle_FCheckpointRecord
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const ANavMeshObstacle_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ANavMeshObstacle_FCheckpointRecord)) == 0; }
	bool operator!=(const ANavMeshObstacle_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ANavMeshObstacle_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ANavMeshObstacle_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.LobbyMetaData
// 0x0020
struct FLobbyMetaData
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FLobbyMetaData& other) const { return memcmp(this, &other, sizeof(FLobbyMetaData)) == 0; }
	bool operator!=(const FLobbyMetaData& other) const { return !(*this == other); }
	bool operator<(const FLobbyMetaData& other) const { return memcmp(this, &other, sizeof(FLobbyMetaData)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.BasicLobbyInfo
// 0x0020
struct FBasicLobbyInfo
{
	struct FUniqueLobbyId                              LobbyUID;                                      // 0x0000 (0x0010) [0x0000000000000000]               
	class TArray<struct FLobbyMetaData>                LobbySettings;                                 // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FBasicLobbyInfo& other) const { return memcmp(this, &other, sizeof(FBasicLobbyInfo)) == 0; }
	bool operator!=(const FBasicLobbyInfo& other) const { return !(*this == other); }
	bool operator<(const FBasicLobbyInfo& other) const { return memcmp(this, &other, sizeof(FBasicLobbyInfo)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.LobbyMember
// 0x0068
struct FLobbyMember
{
	struct FUniqueNetId                                PlayerUID;                                     // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FLobbyMetaData>                PlayerSettings;                                // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      OnlineName;                                    // 0x0058 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FLobbyMember& other) const { return memcmp(this, &other, sizeof(FLobbyMember)) == 0; }
	bool operator!=(const FLobbyMember& other) const { return !(*this == other); }
	bool operator<(const FLobbyMember& other) const { return memcmp(this, &other, sizeof(FLobbyMember)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.ActiveLobbyInfo
// 0x0010 (0x0020 - 0x0030)
struct FActiveLobbyInfo : FBasicLobbyInfo
{
	class TArray<struct FLobbyMember>                  Members;                                       // 0x0020 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FActiveLobbyInfo& other) const { return memcmp(this, &other, sizeof(FActiveLobbyInfo)) == 0; }
	bool operator!=(const FActiveLobbyInfo& other) const { return !(*this == other); }
	bool operator<(const FActiveLobbyInfo& other) const { return memcmp(this, &other, sizeof(FActiveLobbyInfo)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.LobbyFilter
// 0x0028
struct FLobbyFilter
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlineGameSearchComparisonType                    Operator;                                      // 0x0020 (0x0001) [0x0000000000000000]               
	uint32_t                                           bNumeric : 1;                                  // 0x0024 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FLobbyFilter& other) const { return memcmp(this, &other, sizeof(FLobbyFilter)) == 0; }
	bool operator!=(const FLobbyFilter& other) const { return !(*this == other); }
	bool operator<(const FLobbyFilter& other) const { return memcmp(this, &other, sizeof(FLobbyFilter)) < 0; }
};

// ScriptStruct Engine.OnlineLobbySettings.LobbySortFilter
// 0x0014
struct FLobbySortFilter
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            TargetValue;                                   // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FLobbySortFilter& other) const { return memcmp(this, &other, sizeof(FLobbySortFilter)) == 0; }
	bool operator!=(const FLobbySortFilter& other) const { return !(*this == other); }
	bool operator<(const FLobbySortFilter& other) const { return memcmp(this, &other, sizeof(FLobbySortFilter)) < 0; }
};

// ScriptStruct Engine.OnlineMatchmakingStats.MMStats_Timer
// 0x0010
struct FMMStats_Timer
{
	uint32_t                                           bInProgress : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FDouble                                     MSecs;                                         // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FMMStats_Timer& other) const { return memcmp(this, &other, sizeof(FMMStats_Timer)) == 0; }
	bool operator!=(const FMMStats_Timer& other) const { return !(*this == other); }
	bool operator<(const FMMStats_Timer& other) const { return memcmp(this, &other, sizeof(FMMStats_Timer)) < 0; }
};

// ScriptStruct Engine.OnlinePlayerStorage.OnlineProfileSetting
// 0x0028
struct FOnlineProfileSetting
{
	EOnlineProfilePropertyOwner                        Owner;                                         // 0x0000 (0x0001) [0x0000000000000000]               
	struct FSettingsProperty                           ProfileSetting;                                // 0x0008 (0x0020) [0x0000000000000000]               

	bool operator==(const FOnlineProfileSetting& other) const { return memcmp(this, &other, sizeof(FOnlineProfileSetting)) == 0; }
	bool operator!=(const FOnlineProfileSetting& other) const { return !(*this == other); }
	bool operator<(const FOnlineProfileSetting& other) const { return memcmp(this, &other, sizeof(FOnlineProfileSetting)) < 0; }
};

// ScriptStruct Engine.OnlineRecentPlayersList.RecentParty
// 0x0058
struct FRecentParty
{
	struct FUniqueNetId                                PartyLeader;                                   // 0x0000 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FUniqueNetId>                  PartyMembers;                                  // 0x0048 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRecentParty& other) const { return memcmp(this, &other, sizeof(FRecentParty)) == 0; }
	bool operator!=(const FRecentParty& other) const { return !(*this == other); }
	bool operator<(const FRecentParty& other) const { return memcmp(this, &other, sizeof(FRecentParty)) < 0; }
};

// ScriptStruct Engine.OnlineRecentPlayersList.CurrentPlayerMet
// 0x0050
struct FCurrentPlayerMet
{
	int32_t                                            TeamNum;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Skill;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	struct FUniqueNetId                                NetId;                                         // 0x0008 (0x0048) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FCurrentPlayerMet& other) const { return memcmp(this, &other, sizeof(FCurrentPlayerMet)) == 0; }
	bool operator!=(const FCurrentPlayerMet& other) const { return !(*this == other); }
	bool operator<(const FCurrentPlayerMet& other) const { return memcmp(this, &other, sizeof(FCurrentPlayerMet)) < 0; }
};

// ScriptStruct Engine.OnlineStatsRead.OnlineStatsColumn
// 0x0018
struct FOnlineStatsColumn
{
	int32_t                                            ColumnNo;                                      // 0x0000 (0x0004) [0x0000000000000000]               
	struct FSettingsData                               StatValue;                                     // 0x0008 (0x0010) [0x0000000000000000]               

	bool operator==(const FOnlineStatsColumn& other) const { return memcmp(this, &other, sizeof(FOnlineStatsColumn)) == 0; }
	bool operator!=(const FOnlineStatsColumn& other) const { return !(*this == other); }
	bool operator<(const FOnlineStatsColumn& other) const { return memcmp(this, &other, sizeof(FOnlineStatsColumn)) < 0; }
};

// ScriptStruct Engine.OnlineStatsRead.OnlineStatsRow
// 0x0088
struct FOnlineStatsRow
{
	struct FUniqueNetId                                PlayerID;                                      // 0x0000 (0x0048) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	struct FSettingsData                               Rank;                                          // 0x0048 (0x0010) [0x0000000000000002] (CPF_Const)   
	class FString                                      NickName;                                      // 0x0058 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class TArray<struct FOnlineStatsColumn>            Columns;                                       // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FSettingsData>                 StatValues;                                    // 0x0078 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FOnlineStatsRow& other) const { return memcmp(this, &other, sizeof(FOnlineStatsRow)) == 0; }
	bool operator!=(const FOnlineStatsRow& other) const { return !(*this == other); }
	bool operator<(const FOnlineStatsRow& other) const { return memcmp(this, &other, sizeof(FOnlineStatsRow)) < 0; }
};

// ScriptStruct Engine.OnlineStatsRead.ColumnMetaData
// 0x0028
struct FColumnMetaData
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	class FString                                      Name;                                          // 0x0008 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)
	class FString                                      ColumnName;                                    // 0x0018 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FColumnMetaData& other) const { return memcmp(this, &other, sizeof(FColumnMetaData)) == 0; }
	bool operator!=(const FColumnMetaData& other) const { return !(*this == other); }
	bool operator<(const FColumnMetaData& other) const { return memcmp(this, &other, sizeof(FColumnMetaData)) < 0; }
};

// ScriptStruct Engine.ORS.TimerOptions
// 0x0004
struct FTimerOptions
{
	uint32_t                                           bLooping : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FTimerOptions& other) const { return memcmp(this, &other, sizeof(FTimerOptions)) == 0; }
	bool operator!=(const FTimerOptions& other) const { return !(*this == other); }
	bool operator<(const FTimerOptions& other) const { return memcmp(this, &other, sizeof(FTimerOptions)) < 0; }
};

// ScriptStruct Engine.ParticleEmitter.ParticleBurst
// 0x000C
struct FParticleBurst
{
	int32_t                                            Count;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            CountLow;                                      // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Time;                                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FParticleBurst& other) const { return memcmp(this, &other, sizeof(FParticleBurst)) == 0; }
	bool operator!=(const FParticleBurst& other) const { return !(*this == other); }
	bool operator<(const FParticleBurst& other) const { return memcmp(this, &other, sizeof(FParticleBurst)) < 0; }
};

// ScriptStruct Engine.ParticleModule.ParticleCurvePair
// 0x0018
struct FParticleCurvePair
{
	class FString                                      CurveName;                                     // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class UObject*                                     CurveObject;                                   // 0x0010 (0x0008) [0x0000000000100000]               

	bool operator==(const FParticleCurvePair& other) const { return memcmp(this, &other, sizeof(FParticleCurvePair)) == 0; }
	bool operator!=(const FParticleCurvePair& other) const { return !(*this == other); }
	bool operator<(const FParticleCurvePair& other) const { return memcmp(this, &other, sizeof(FParticleCurvePair)) < 0; }
};

// ScriptStruct Engine.ParticleModule.ParticleRandomSeedInfo
// 0x0020
struct FParticleRandomSeedInfo
{
	class FName                                        ParameterName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bGetSeedFromInstance : 1;                      // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bInstanceSeedIsIndex : 1;                      // 0x0008 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bResetSeedOnEmitterLooping : 1;                // 0x0008 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	class TArray<int32_t>                              RandomSeeds;                                   // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FParticleRandomSeedInfo& other) const { return memcmp(this, &other, sizeof(FParticleRandomSeedInfo)) == 0; }
	bool operator!=(const FParticleRandomSeedInfo& other) const { return !(*this == other); }
	bool operator<(const FParticleRandomSeedInfo& other) const { return memcmp(this, &other, sizeof(FParticleRandomSeedInfo)) < 0; }
};

// ScriptStruct Engine.ParticleModuleAttractorBoneSocket.AttractLocationBoneSocketInfo
// 0x0014
struct FAttractLocationBoneSocketInfo
{
	class FName                                        BoneSocketName;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Offset;                                        // 0x0008 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAttractLocationBoneSocketInfo& other) const { return memcmp(this, &other, sizeof(FAttractLocationBoneSocketInfo)) == 0; }
	bool operator!=(const FAttractLocationBoneSocketInfo& other) const { return !(*this == other); }
	bool operator<(const FAttractLocationBoneSocketInfo& other) const { return memcmp(this, &other, sizeof(FAttractLocationBoneSocketInfo)) < 0; }
};

// ScriptStruct Engine.ParticleModuleBeamModifier.BeamModifierOptions
// 0x0004
struct FBeamModifierOptions
{
	uint32_t                                           bModify : 1;                                   // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bScale : 1;                                    // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bLock : 1;                                     // 0x0000 (0x0004) [0x0000000000000001] [0x100000004] (CPF_Edit)

	bool operator==(const FBeamModifierOptions& other) const { return memcmp(this, &other, sizeof(FBeamModifierOptions)) == 0; }
	bool operator!=(const FBeamModifierOptions& other) const { return !(*this == other); }
	bool operator<(const FBeamModifierOptions& other) const { return memcmp(this, &other, sizeof(FBeamModifierOptions)) < 0; }
};

// ScriptStruct Engine.ParticleModuleCollision.ParticleAttractorCollisionAction
// 0x0018
struct FParticleAttractorCollisionAction
{
	EParticleAttractorActionType                       Type;                                          // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class FString                                      EventName;                                     // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FParticleAttractorCollisionAction& other) const { return memcmp(this, &other, sizeof(FParticleAttractorCollisionAction)) == 0; }
	bool operator!=(const FParticleAttractorCollisionAction& other) const { return !(*this == other); }
	bool operator<(const FParticleAttractorCollisionAction& other) const { return memcmp(this, &other, sizeof(FParticleAttractorCollisionAction)) < 0; }
};

// ScriptStruct Engine.ParticleModuleEventGenerator.ParticleEvent_GenerateInfo
// 0x0030
struct FParticleEvent_GenerateInfo
{
	EParticleEventType                                 Type;                                          // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Frequency;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            LowFreq;                                       // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            ParticleFrequency;                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           FirstTimeOnly : 1;                             // 0x0010 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           LastTimeOnly : 1;                              // 0x0010 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           UseReflectedImpactVector : 1;                  // 0x0010 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	class FName                                        CustomName;                                    // 0x0014 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UParticleModuleEventSendToGame*> ParticleModuleEventsToSendToGame;              // 0x0020 (0x0010) [0x0000000004400001] (CPF_Edit | CPF_NeedCtorLink | CPF_EditInline)

	bool operator==(const FParticleEvent_GenerateInfo& other) const { return memcmp(this, &other, sizeof(FParticleEvent_GenerateInfo)) == 0; }
	bool operator!=(const FParticleEvent_GenerateInfo& other) const { return !(*this == other); }
	bool operator<(const FParticleEvent_GenerateInfo& other) const { return memcmp(this, &other, sizeof(FParticleEvent_GenerateInfo)) < 0; }
};

// ScriptStruct Engine.ParticleModuleLocationBoneSocket.LocationBoneSocketInfo
// 0x0014
struct FLocationBoneSocketInfo
{
	class FName                                        BoneSocketName;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Offset;                                        // 0x0008 (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLocationBoneSocketInfo& other) const { return memcmp(this, &other, sizeof(FLocationBoneSocketInfo)) == 0; }
	bool operator!=(const FLocationBoneSocketInfo& other) const { return !(*this == other); }
	bool operator<(const FLocationBoneSocketInfo& other) const { return memcmp(this, &other, sizeof(FLocationBoneSocketInfo)) < 0; }
};

// ScriptStruct Engine.ParticleModuleOrbit.OrbitOptions
// 0x0004
struct FOrbitOptions
{
	uint32_t                                           bProcessDuringSpawn : 1;                       // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bProcessDuringUpdate : 1;                      // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bUseEmitterTime : 1;                           // 0x0000 (0x0004) [0x0000000000000001] [0x100000004] (CPF_Edit)

	bool operator==(const FOrbitOptions& other) const { return memcmp(this, &other, sizeof(FOrbitOptions)) == 0; }
	bool operator!=(const FOrbitOptions& other) const { return !(*this == other); }
	bool operator<(const FOrbitOptions& other) const { return memcmp(this, &other, sizeof(FOrbitOptions)) < 0; }
};

// ScriptStruct Engine.ParticleModuleParameterDynamic.EmitterDynamicParameter
// 0x0040
struct FEmitterDynamicParameter
{
	class FName                                        ParamName;                                     // 0x0000 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	uint32_t                                           bUseEmitterTime : 1;                           // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bSpawnTimeOnly : 1;                            // 0x0008 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	EEmitterDynamicParameterValue                      ValueMethod;                                   // 0x000C (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bScaleVelocityByParamValue : 1;                // 0x0010 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FRawDistributionFloat                       ParamValue;                                    // 0x0018 (0x0028) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)

	bool operator==(const FEmitterDynamicParameter& other) const { return memcmp(this, &other, sizeof(FEmitterDynamicParameter)) == 0; }
	bool operator!=(const FEmitterDynamicParameter& other) const { return !(*this == other); }
	bool operator<(const FEmitterDynamicParameter& other) const { return memcmp(this, &other, sizeof(FEmitterDynamicParameter)) < 0; }
};

// ScriptStruct Engine.ParticleModuleTypeDataBeam2.BeamTargetData
// 0x000C
struct FBeamTargetData
{
	class FName                                        TargetName;                                    // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              TargetPercentage;                              // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBeamTargetData& other) const { return memcmp(this, &other, sizeof(FBeamTargetData)) == 0; }
	bool operator!=(const FBeamTargetData& other) const { return !(*this == other); }
	bool operator<(const FBeamTargetData& other) const { return memcmp(this, &other, sizeof(FBeamTargetData)) < 0; }
};

// ScriptStruct Engine.ParticleModuleTypeDataPhysX.PhysXEmitterVerticalLodProperties
// 0x0010
struct FPhysXEmitterVerticalLodProperties
{
	float                                              WeightForFifo;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              WeightForSpawnLod;                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              SpawnLodRateVsLifeBias;                        // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              RelativeFadeoutTime;                           // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPhysXEmitterVerticalLodProperties& other) const { return memcmp(this, &other, sizeof(FPhysXEmitterVerticalLodProperties)) == 0; }
	bool operator!=(const FPhysXEmitterVerticalLodProperties& other) const { return !(*this == other); }
	bool operator<(const FPhysXEmitterVerticalLodProperties& other) const { return memcmp(this, &other, sizeof(FPhysXEmitterVerticalLodProperties)) < 0; }
};

// ScriptStruct Engine.ParticleSystem.ParticleSystemLOD
// 0x0004
struct FParticleSystemLOD
{
	uint32_t                                           bLit : 1;                                      // 0x0000 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FParticleSystemLOD& other) const { return memcmp(this, &other, sizeof(FParticleSystemLOD)) == 0; }
	bool operator!=(const FParticleSystemLOD& other) const { return !(*this == other); }
	bool operator<(const FParticleSystemLOD& other) const { return memcmp(this, &other, sizeof(FParticleSystemLOD)) < 0; }
};

// ScriptStruct Engine.ParticleSystem.LODSoloTrack
// 0x0010
struct FLODSoloTrack
{
	class TArray<uint8_t>                              SoloEnableSetting;                             // 0x0000 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)

	bool operator==(const FLODSoloTrack& other) const { return memcmp(this, &other, sizeof(FLODSoloTrack)) == 0; }
	bool operator!=(const FLODSoloTrack& other) const { return !(*this == other); }
	bool operator<(const FLODSoloTrack& other) const { return memcmp(this, &other, sizeof(FLODSoloTrack)) < 0; }
};

// ScriptStruct Engine.ParticleSystemReplay.ParticleEmitterReplayFrame
// 0x0010
struct FParticleEmitterReplayFrame
{
	int32_t                                            EmitterType;                                   // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            OriginalEmitterIndex;                          // 0x0004 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    FrameState;                                    // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FParticleEmitterReplayFrame& other) const { return memcmp(this, &other, sizeof(FParticleEmitterReplayFrame)) == 0; }
	bool operator!=(const FParticleEmitterReplayFrame& other) const { return !(*this == other); }
	bool operator<(const FParticleEmitterReplayFrame& other) const { return memcmp(this, &other, sizeof(FParticleEmitterReplayFrame)) < 0; }
};

// ScriptStruct Engine.ParticleSystemReplay.ParticleSystemReplayFrame
// 0x0010
struct FParticleSystemReplayFrame
{
	class TArray<struct FParticleEmitterReplayFrame>   Emitters;                                      // 0x0000 (0x0010) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FParticleSystemReplayFrame& other) const { return memcmp(this, &other, sizeof(FParticleSystemReplayFrame)) == 0; }
	bool operator!=(const FParticleSystemReplayFrame& other) const { return !(*this == other); }
	bool operator<(const FParticleSystemReplayFrame& other) const { return memcmp(this, &other, sizeof(FParticleSystemReplayFrame)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeBase.PBRuleLink
// 0x0014
struct FPBRuleLink
{
	class UPBRuleNodeBase*                             NextRule;                                      // 0x0000 (0x0008) [0x0000000004400009] (CPF_Edit | CPF_ExportObject | CPF_NeedCtorLink | CPF_EditInline)
	class FName                                        LinkName;                                      // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            DrawY;                                         // 0x0010 (0x0004) [0x0000000800000000] (CPF_EditorOnly)

	bool operator==(const FPBRuleLink& other) const { return memcmp(this, &other, sizeof(FPBRuleLink)) == 0; }
	bool operator!=(const FPBRuleLink& other) const { return !(*this == other); }
	bool operator<(const FPBRuleLink& other) const { return memcmp(this, &other, sizeof(FPBRuleLink)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBMaterialParam
// 0x0018
struct FPBMaterialParam
{
	class FName                                        ParamName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                Color;                                         // 0x0008 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPBMaterialParam& other) const { return memcmp(this, &other, sizeof(FPBMaterialParam)) == 0; }
	bool operator!=(const FPBMaterialParam& other) const { return !(*this == other); }
	bool operator<(const FPBMaterialParam& other) const { return memcmp(this, &other, sizeof(FPBMaterialParam)) < 0; }
};

// ScriptStruct Engine.ProcBuildingRuleset.PBParamSwatch
// 0x0018
struct FPBParamSwatch
{
	class FName                                        SwatchName;                                    // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FPBMaterialParam>              Params;                                        // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FPBParamSwatch& other) const { return memcmp(this, &other, sizeof(FPBParamSwatch)) == 0; }
	bool operator!=(const FPBParamSwatch& other) const { return !(*this == other); }
	bool operator<(const FPBParamSwatch& other) const { return memcmp(this, &other, sizeof(FPBParamSwatch)) < 0; }
};

// ScriptStruct Engine.ProcBuildingRuleset.PBVariationInfo
// 0x000C
struct FPBVariationInfo
{
	class FName                                        VariationName;                                 // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bMeshOnTopOfFacePoly : 1;                      // 0x0008 (0x0004) [0x0000000000000001] [0x100000001] (CPF_Edit)

	bool operator==(const FPBVariationInfo& other) const { return memcmp(this, &other, sizeof(FPBVariationInfo)) == 0; }
	bool operator!=(const FPBVariationInfo& other) const { return !(*this == other); }
	bool operator<(const FPBVariationInfo& other) const { return memcmp(this, &other, sizeof(FPBVariationInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBFracMeshCompInfo
// 0x000C
struct FPBFracMeshCompInfo
{
	class UFracturedStaticMeshComponent*               FracMeshComp;                                  // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	int32_t                                            TopLevelScopeIndex;                            // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPBFracMeshCompInfo& other) const { return memcmp(this, &other, sizeof(FPBFracMeshCompInfo)) == 0; }
	bool operator!=(const FPBFracMeshCompInfo& other) const { return !(*this == other); }
	bool operator<(const FPBFracMeshCompInfo& other) const { return memcmp(this, &other, sizeof(FPBFracMeshCompInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBFaceUVInfo
// 0x0010
struct FPBFaceUVInfo
{
	struct FVector2D                                   Offset;                                        // 0x0000 (0x0008) [0x0000000000000000]               
	struct FVector2D                                   Size;                                          // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FPBFaceUVInfo& other) const { return memcmp(this, &other, sizeof(FPBFaceUVInfo)) == 0; }
	bool operator!=(const FPBFaceUVInfo& other) const { return !(*this == other); }
	bool operator<(const FPBFaceUVInfo& other) const { return memcmp(this, &other, sizeof(FPBFaceUVInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBMemUsageInfo
// 0x002C
struct FPBMemUsageInfo
{
	class AProcBuilding*                               Building;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	class UProcBuildingRuleset*                        Ruleset;                                       // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            NumStaticMeshComponent;                        // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            NumInstancedStaticMeshComponents;              // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            NumInstancedTris;                              // 0x0018 (0x0004) [0x0000000000000000]               
	int32_t                                            LightmapMemBytes;                              // 0x001C (0x0004) [0x0000000000000000]               
	int32_t                                            ShadowmapMemBytes;                             // 0x0020 (0x0004) [0x0000000000000000]               
	int32_t                                            LODDiffuseMemBytes;                            // 0x0024 (0x0004) [0x0000000000000000]               
	int32_t                                            LODLightingMemBytes;                           // 0x0028 (0x0004) [0x0000000000000000]               

	bool operator==(const FPBMemUsageInfo& other) const { return memcmp(this, &other, sizeof(FPBMemUsageInfo)) == 0; }
	bool operator!=(const FPBMemUsageInfo& other) const { return !(*this == other); }
	bool operator<(const FPBMemUsageInfo& other) const { return memcmp(this, &other, sizeof(FPBMemUsageInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBMeshCompInfo
// 0x000C
struct FPBMeshCompInfo
{
	class UStaticMeshComponent*                        MeshComp;                                      // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	int32_t                                            TopLevelScopeIndex;                            // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FPBMeshCompInfo& other) const { return memcmp(this, &other, sizeof(FPBMeshCompInfo)) == 0; }
	bool operator!=(const FPBMeshCompInfo& other) const { return !(*this == other); }
	bool operator<(const FPBMeshCompInfo& other) const { return memcmp(this, &other, sizeof(FPBMeshCompInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBScopeProcessInfo
// 0x001C
struct FPBScopeProcessInfo
{
	class AProcBuilding*                               OwningBuilding;                                // 0x0000 (0x0008) [0x0000000000000000]               
	class UProcBuildingRuleset*                        Ruleset;                                       // 0x0008 (0x0008) [0x0000000000000000]               
	class FName                                        RulesetVariation;                              // 0x0010 (0x0008) [0x0000000000000000]               
	uint32_t                                           bGenerateLODPoly : 1;                          // 0x0018 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bPartOfNonRect : 1;                            // 0x0018 (0x0004) [0x0000000000000000] [0x100000002] 

	bool operator==(const FPBScopeProcessInfo& other) const { return memcmp(this, &other, sizeof(FPBScopeProcessInfo)) == 0; }
	bool operator!=(const FPBScopeProcessInfo& other) const { return !(*this == other); }
	bool operator<(const FPBScopeProcessInfo& other) const { return memcmp(this, &other, sizeof(FPBScopeProcessInfo)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBScope2D
// 0x0048
struct FPBScope2D
{
	struct FMatrix                                     ScopeFrame;                                    // 0x0000 (0x0040) [0x0000000000000000]               
	float                                              DimX;                                          // 0x0040 (0x0004) [0x0000000000000000]               
	float                                              DimZ;                                          // 0x0044 (0x0004) [0x0000000000000000]               
	uint8_t                                            MinStructAlignment[0x8];                         // 0x0048 (0x0008) ADDED PADDING

	bool operator==(const FPBScope2D& other) const { return memcmp(this, &other, sizeof(FPBScope2D)) == 0; }
	bool operator!=(const FPBScope2D& other) const { return !(*this == other); }
	bool operator<(const FPBScope2D& other) const { return memcmp(this, &other, sizeof(FPBScope2D)) < 0; }
};

// ScriptStruct Engine.ProcBuilding.PBEdgeInfo
// 0x002C
struct FPBEdgeInfo
{
	struct FVector                                     EdgeEnd;                                       // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     EdgeStart;                                     // 0x000C (0x000C) [0x0000000000000000]               
	int32_t                                            ScopeAIndex;                                   // 0x0018 (0x0004) [0x0000000000000000]               
	EScopeEdge                                         ScopeAEdge;                                    // 0x001C (0x0001) [0x0000000000000000]               
	int32_t                                            ScopeBIndex;                                   // 0x0020 (0x0004) [0x0000000000000000]               
	EScopeEdge                                         ScopeBEdge;                                    // 0x0024 (0x0001) [0x0000000000000000]               
	float                                              EdgeAngle;                                     // 0x0028 (0x0004) [0x0000000000000000]               

	bool operator==(const FPBEdgeInfo& other) const { return memcmp(this, &other, sizeof(FPBEdgeInfo)) == 0; }
	bool operator!=(const FPBEdgeInfo& other) const { return !(*this == other); }
	bool operator<(const FPBEdgeInfo& other) const { return memcmp(this, &other, sizeof(FPBEdgeInfo)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeCorner.RBCornerAngleInfo
// 0x0008
struct FRBCornerAngleInfo
{
	float                                              Angle;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              CornerSize;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRBCornerAngleInfo& other) const { return memcmp(this, &other, sizeof(FRBCornerAngleInfo)) == 0; }
	bool operator!=(const FRBCornerAngleInfo& other) const { return !(*this == other); }
	bool operator<(const FRBCornerAngleInfo& other) const { return memcmp(this, &other, sizeof(FRBCornerAngleInfo)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeEdgeAngle.RBEdgeAngleInfo
// 0x0004
struct FRBEdgeAngleInfo
{
	float                                              Angle;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRBEdgeAngleInfo& other) const { return memcmp(this, &other, sizeof(FRBEdgeAngleInfo)) == 0; }
	bool operator!=(const FRBEdgeAngleInfo& other) const { return !(*this == other); }
	bool operator<(const FRBEdgeAngleInfo& other) const { return memcmp(this, &other, sizeof(FRBEdgeAngleInfo)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeMesh.BuildingMatOverrides
// 0x0010
struct FBuildingMatOverrides
{
	class TArray<class UMaterialInterface*>            MaterialOptions;                               // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FBuildingMatOverrides& other) const { return memcmp(this, &other, sizeof(FBuildingMatOverrides)) == 0; }
	bool operator!=(const FBuildingMatOverrides& other) const { return !(*this == other); }
	bool operator<(const FBuildingMatOverrides& other) const { return memcmp(this, &other, sizeof(FBuildingMatOverrides)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeMesh.BuildingMeshInfo
// 0x0050
struct FBuildingMeshInfo
{
	class UStaticMesh*                                 Mesh;                                          // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	float                                              DimX;                                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              DimZ;                                          // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Chance;                                        // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UDistributionVector*                         Translation;                                   // 0x0018 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class UDistributionVector*                         Rotation;                                      // 0x0020 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	uint32_t                                           bMeshScaleTranslation : 1;                     // 0x0028 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bOverrideMeshLightMapRes : 1;                  // 0x0028 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	int32_t                                            OverriddenMeshLightMapRes;                     // 0x002C (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<class UMaterialInterface*>            MaterialOverrides;                             // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FBuildingMatOverrides>         SectionOverrides;                              // 0x0040 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FBuildingMeshInfo& other) const { return memcmp(this, &other, sizeof(FBuildingMeshInfo)) == 0; }
	bool operator!=(const FBuildingMeshInfo& other) const { return !(*this == other); }
	bool operator<(const FBuildingMeshInfo& other) const { return memcmp(this, &other, sizeof(FBuildingMeshInfo)) < 0; }
};

// ScriptStruct Engine.PBRuleNodeSplit.RBSplitInfo
// 0x0014
struct FRBSplitInfo
{
	uint32_t                                           bFixSize : 1;                                  // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              FixedSize;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ExpandRatio;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FName                                        SplitName;                                     // 0x000C (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRBSplitInfo& other) const { return memcmp(this, &other, sizeof(FRBSplitInfo)) == 0; }
	bool operator!=(const FRBSplitInfo& other) const { return !(*this == other); }
	bool operator<(const FRBSplitInfo& other) const { return memcmp(this, &other, sizeof(FRBSplitInfo)) < 0; }
};

// ScriptStruct Engine.PitchTekSettings.PitchTekTextureDecalSettings
// 0x0020
struct FPitchTekTextureDecalSettings
{
	uint32_t                                           bDrawColorDecal : 1;                           // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              ColorTextureScale;                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UTexture2D*                                  ColorTexture;                                  // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bDrawDataDecal : 1;                            // 0x0010 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              DataTextureScale;                              // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UTexture2D*                                  DataTexture;                                   // 0x0018 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPitchTekTextureDecalSettings& other) const { return memcmp(this, &other, sizeof(FPitchTekTextureDecalSettings)) == 0; }
	bool operator!=(const FPitchTekTextureDecalSettings& other) const { return !(*this == other); }
	bool operator<(const FPitchTekTextureDecalSettings& other) const { return memcmp(this, &other, sizeof(FPitchTekTextureDecalSettings)) < 0; }
};

// ScriptStruct Engine.PitchTekSettings.PitchTekClearSettings
// 0x0010
struct FPitchTekClearSettings
{
	uint32_t                                           bClearColorTargetEveryFrame : 1;               // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FColor                                      ColorTargetClearColor;                         // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bClearDataTargetEveryFrame : 1;                // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	struct FColor                                      DataTargetClearColor;                          // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPitchTekClearSettings& other) const { return memcmp(this, &other, sizeof(FPitchTekClearSettings)) == 0; }
	bool operator!=(const FPitchTekClearSettings& other) const { return !(*this == other); }
	bool operator<(const FPitchTekClearSettings& other) const { return memcmp(this, &other, sizeof(FPitchTekClearSettings)) < 0; }
};

// ScriptStruct Engine.PlayerReplicationInfo.PRIRemoteUserData
// 0x0010
struct FPRIRemoteUserData
{
	class FString                                      UserId;                                        // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FPRIRemoteUserData& other) const { return memcmp(this, &other, sizeof(FPRIRemoteUserData)) == 0; }
	bool operator!=(const FPRIRemoteUserData& other) const { return !(*this == other); }
	bool operator<(const FPRIRemoteUserData& other) const { return memcmp(this, &other, sizeof(FPRIRemoteUserData)) < 0; }
};

// ScriptStruct Engine.PlayerReplicationInfo.NetPacketStats
// 0x001C
struct FNetPacketStats
{
	int32_t                                            OutPackets;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            InPackets;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            OutPacketsLost;                                // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            InPacketsLost;                                 // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            OutOfOrderPackets;                             // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            OutBytes;                                      // 0x0014 (0x0004) [0x0000000000000000]               
	int32_t                                            InBytes;                                       // 0x0018 (0x0004) [0x0000000000000000]               

	bool operator==(const FNetPacketStats& other) const { return memcmp(this, &other, sizeof(FNetPacketStats)) == 0; }
	bool operator!=(const FNetPacketStats& other) const { return !(*this == other); }
	bool operator<(const FNetPacketStats& other) const { return memcmp(this, &other, sizeof(FNetPacketStats)) < 0; }
};

// ScriptStruct Engine.PointLightToggleable.CheckpointRecord
// 0x0004
struct APointLightToggleable_FCheckpointRecord
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const APointLightToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(APointLightToggleable_FCheckpointRecord)) == 0; }
	bool operator!=(const APointLightToggleable_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const APointLightToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(APointLightToggleable_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.Sequence.ActivateOp
// 0x0018
struct FActivateOp
{
	class USequenceOp*                                 ActivatorOp;                                   // 0x0000 (0x0008) [0x0000000000000000]               
	class USequenceOp*                                 Op;                                            // 0x0008 (0x0008) [0x0000000000000000]               
	int32_t                                            InputIdx;                                      // 0x0010 (0x0004) [0x0000000000000000]               
	float                                              RemainingDelay;                                // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FActivateOp& other) const { return memcmp(this, &other, sizeof(FActivateOp)) == 0; }
	bool operator!=(const FActivateOp& other) const { return !(*this == other); }
	bool operator<(const FActivateOp& other) const { return memcmp(this, &other, sizeof(FActivateOp)) < 0; }
};

// ScriptStruct Engine.Sequence.QueuedActivationInfo
// 0x002C
struct FQueuedActivationInfo
{
	class USequenceEvent*                              ActivatedEvent;                                // 0x0000 (0x0008) [0x0000000000000000]               
	class AActor*                                      InOriginator;                                  // 0x0008 (0x0008) [0x0000000000000000]               
	class AActor*                                      InInstigator;                                  // 0x0010 (0x0008) [0x0000000000000000]               
	class TArray<int32_t>                              ActivateIndices;                               // 0x0018 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bPushTop : 1;                                  // 0x0028 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FQueuedActivationInfo& other) const { return memcmp(this, &other, sizeof(FQueuedActivationInfo)) == 0; }
	bool operator!=(const FQueuedActivationInfo& other) const { return !(*this == other); }
	bool operator<(const FQueuedActivationInfo& other) const { return memcmp(this, &other, sizeof(FQueuedActivationInfo)) < 0; }
};

// ScriptStruct Engine.RB_BodyInstance.BulletBodyData
// 0x0010
struct FBulletBodyData
{
	int32_t                                            SceneIndex;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	struct FPointer                                    Body;                                          // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FBulletBodyData& other) const { return memcmp(this, &other, sizeof(FBulletBodyData)) == 0; }
	bool operator!=(const FBulletBodyData& other) const { return !(*this == other); }
	bool operator<(const FBulletBodyData& other) const { return memcmp(this, &other, sizeof(FBulletBodyData)) < 0; }
};

// ScriptStruct Engine.RB_BodySetup.KCachedConvexDataElement
// 0x0010
struct FKCachedConvexDataElement
{
	class TArray<uint8_t>                              ConvexElementData;                             // 0x0000 (0x0010) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FKCachedConvexDataElement& other) const { return memcmp(this, &other, sizeof(FKCachedConvexDataElement)) == 0; }
	bool operator!=(const FKCachedConvexDataElement& other) const { return !(*this == other); }
	bool operator<(const FKCachedConvexDataElement& other) const { return memcmp(this, &other, sizeof(FKCachedConvexDataElement)) < 0; }
};

// ScriptStruct Engine.RB_BodySetup.KCachedConvexData
// 0x0010
struct FKCachedConvexData
{
	class TArray<struct FKCachedConvexDataElement>     CachedConvexElements;                          // 0x0000 (0x0010) [0x0000000000001000] (CPF_Native)  

	bool operator==(const FKCachedConvexData& other) const { return memcmp(this, &other, sizeof(FKCachedConvexData)) == 0; }
	bool operator!=(const FKCachedConvexData& other) const { return !(*this == other); }
	bool operator<(const FKCachedConvexData& other) const { return memcmp(this, &other, sizeof(FKCachedConvexData)) < 0; }
};

// ScriptStruct Engine.RB_ConstraintSetup.LinearDOFSetup
// 0x0008
struct FLinearDOFSetup
{
	uint8_t                                            bLimited;                                      // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	float                                              LimitSize;                                     // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLinearDOFSetup& other) const { return memcmp(this, &other, sizeof(FLinearDOFSetup)) == 0; }
	bool operator!=(const FLinearDOFSetup& other) const { return !(*this == other); }
	bool operator<(const FLinearDOFSetup& other) const { return memcmp(this, &other, sizeof(FLinearDOFSetup)) < 0; }
};

// ScriptStruct Engine.SeqAct_Interp.CameraCutInfo
// 0x0010
struct FCameraCutInfo
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	float                                              TimeStamp;                                     // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FCameraCutInfo& other) const { return memcmp(this, &other, sizeof(FCameraCutInfo)) == 0; }
	bool operator!=(const FCameraCutInfo& other) const { return !(*this == other); }
	bool operator<(const FCameraCutInfo& other) const { return memcmp(this, &other, sizeof(FCameraCutInfo)) < 0; }
};

// ScriptStruct Engine.SeqAct_Interp.SavedTransform
// 0x0018
struct FSavedTransform
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000000]               

	bool operator==(const FSavedTransform& other) const { return memcmp(this, &other, sizeof(FSavedTransform)) == 0; }
	bool operator!=(const FSavedTransform& other) const { return !(*this == other); }
	bool operator<(const FSavedTransform& other) const { return memcmp(this, &other, sizeof(FSavedTransform)) < 0; }
};

// ScriptStruct Engine.SeqAct_MultiLevelStreaming.LevelStreamingNameCombo
// 0x0010
struct FLevelStreamingNameCombo
{
	class ULevelStreaming*                             Level;                                         // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FName                                        LevelName;                                     // 0x0008 (0x0008) [0x0000000000000003] (CPF_Edit | CPF_Const)

	bool operator==(const FLevelStreamingNameCombo& other) const { return memcmp(this, &other, sizeof(FLevelStreamingNameCombo)) == 0; }
	bool operator!=(const FLevelStreamingNameCombo& other) const { return !(*this == other); }
	bool operator<(const FLevelStreamingNameCombo& other) const { return memcmp(this, &other, sizeof(FLevelStreamingNameCombo)) < 0; }
};

// ScriptStruct Engine.SeqAct_RangeSwitch.SwitchRange
// 0x0008
struct FSwitchRange
{
	int32_t                                            Min;                                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Max;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSwitchRange& other) const { return memcmp(this, &other, sizeof(FSwitchRange)) == 0; }
	bool operator!=(const FSwitchRange& other) const { return !(*this == other); }
	bool operator<(const FSwitchRange& other) const { return memcmp(this, &other, sizeof(FSwitchRange)) < 0; }
};

// ScriptStruct Engine.WorldAttractor.WorldAttractorData
// 0x0020
struct FWorldAttractorData
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	EWorldAttractorFalloffType                         FalloffType;                                   // 0x0010 (0x0001) [0x0000000000000000]               
	float                                              FalloffExponent;                               // 0x0014 (0x0004) [0x0000000000000000]               
	float                                              Range;                                         // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              Strength;                                      // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FWorldAttractorData& other) const { return memcmp(this, &other, sizeof(FWorldAttractorData)) == 0; }
	bool operator!=(const FWorldAttractorData& other) const { return !(*this == other); }
	bool operator<(const FWorldAttractorData& other) const { return memcmp(this, &other, sizeof(FWorldAttractorData)) < 0; }
};

// ScriptStruct Engine.SeqCond_SwitchClass.SwitchClassInfo
// 0x0009
struct FSwitchClassInfo
{
	class FName                                        ClassName;                                     // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            bFallThru;                                     // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSwitchClassInfo& other) const { return memcmp(this, &other, sizeof(FSwitchClassInfo)) == 0; }
	bool operator!=(const FSwitchClassInfo& other) const { return !(*this == other); }
	bool operator<(const FSwitchClassInfo& other) const { return memcmp(this, &other, sizeof(FSwitchClassInfo)) < 0; }
};

// ScriptStruct Engine.SeqCond_SwitchObject.SwitchObjectCase
// 0x000C
struct FSwitchObjectCase
{
	class UObject*                                     ObjectValue;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bFallThru : 1;                                 // 0x0008 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bDefaultValue : 1;                             // 0x0008 (0x0004) [0x0000000000000001] [0x100000002] (CPF_Edit)

	bool operator==(const FSwitchObjectCase& other) const { return memcmp(this, &other, sizeof(FSwitchObjectCase)) == 0; }
	bool operator!=(const FSwitchObjectCase& other) const { return !(*this == other); }
	bool operator<(const FSwitchObjectCase& other) const { return memcmp(this, &other, sizeof(FSwitchObjectCase)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.SoftBodyTetraLink
// 0x0010
struct FSoftBodyTetraLink
{
	int32_t                                            Index;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	struct FVector                                     Bary;                                          // 0x0004 (0x000C) [0x0000000000000000]               

	bool operator==(const FSoftBodyTetraLink& other) const { return memcmp(this, &other, sizeof(FSoftBodyTetraLink)) == 0; }
	bool operator!=(const FSoftBodyTetraLink& other) const { return !(*this == other); }
	bool operator<(const FSoftBodyTetraLink& other) const { return memcmp(this, &other, sizeof(FSoftBodyTetraLink)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.SoftBodySpecialBoneInfo
// 0x0020
struct FSoftBodySpecialBoneInfo
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	ESoftBodyBoneType                                  BoneType;                                      // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class TArray<int32_t>                              AttachedVertexIndices;                         // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FSoftBodySpecialBoneInfo& other) const { return memcmp(this, &other, sizeof(FSoftBodySpecialBoneInfo)) == 0; }
	bool operator!=(const FSoftBodySpecialBoneInfo& other) const { return !(*this == other); }
	bool operator<(const FSoftBodySpecialBoneInfo& other) const { return memcmp(this, &other, sizeof(FSoftBodySpecialBoneInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.ClothSpecialBoneInfo
// 0x0020
struct FClothSpecialBoneInfo
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EClothBoneType                                     BoneType;                                      // 0x0008 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class TArray<int32_t>                              AttachedVertexIndices;                         // 0x0010 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

	bool operator==(const FClothSpecialBoneInfo& other) const { return memcmp(this, &other, sizeof(FClothSpecialBoneInfo)) == 0; }
	bool operator!=(const FClothSpecialBoneInfo& other) const { return !(*this == other); }
	bool operator<(const FClothSpecialBoneInfo& other) const { return memcmp(this, &other, sizeof(FClothSpecialBoneInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.SkeletalMeshOptimizationSettings
// 0x0028
struct FSkeletalMeshOptimizationSettings
{
	float                                              MaxDeviationPercentage;                        // 0x0000 (0x0004) [0x0000000000000000]               
	ESkeletalMeshOptimizationImportance                SilhouetteImportance;                          // 0x0004 (0x0001) [0x0000000000000000]               
	ESkeletalMeshOptimizationImportance                TextureImportance;                             // 0x0005 (0x0001) [0x0000000000000000]               
	ESkeletalMeshOptimizationImportance                ShadingImportance;                             // 0x0006 (0x0001) [0x0000000000000000]               
	ESkeletalMeshOptimizationImportance                SkinningImportance;                            // 0x0007 (0x0001) [0x0000000000000000]               
	ESkeletalMeshOptimizationNormalMode                NormalMode;                                    // 0x0008 (0x0001) [0x0000000020000000]  CPF_Deprecated)
	float                                              BoneReductionRatio;                            // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            MaxBonesPerVertex;                             // 0x0010 (0x0004) [0x0000000000000000]               
	ESkeletalMeshOptimizationType                      ReductionMethod;                               // 0x0014 (0x0001) [0x0000000000000000]               
	float                                              NumOfTrianglesPercentage;                      // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              WeldingThreshold;                              // 0x001C (0x0004) [0x0000000000000000]               
	uint32_t                                           bRecalcNormals : 1;                            // 0x0020 (0x0004) [0x0000000000000000] [0x00000001] 
	float                                              NormalsThreshold;                              // 0x0024 (0x0004) [0x0000000000000000]               

	bool operator==(const FSkeletalMeshOptimizationSettings& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshOptimizationSettings)) == 0; }
	bool operator!=(const FSkeletalMeshOptimizationSettings& other) const { return !(*this == other); }
	bool operator<(const FSkeletalMeshOptimizationSettings& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshOptimizationSettings)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.SkeletalMeshLODDistanceInfo
// 0x0008
struct FSkeletalMeshLODDistanceInfo
{
	float                                              DisplayFactor;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LODHysteresis;                                 // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSkeletalMeshLODDistanceInfo& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshLODDistanceInfo)) == 0; }
	bool operator!=(const FSkeletalMeshLODDistanceInfo& other) const { return !(*this == other); }
	bool operator<(const FSkeletalMeshLODDistanceInfo& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshLODDistanceInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.TriangleSortSettings
// 0x000C
struct FTriangleSortSettings
{
	ETriangleSortOption                                TriangleSorting;                               // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	ETriangleSortAxis                                  CustomLeftRightAxis;                           // 0x0001 (0x0001) [0x0000000000000001] (CPF_Edit)    
	class FName                                        CustomLeftRightBoneName;                       // 0x0004 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTriangleSortSettings& other) const { return memcmp(this, &other, sizeof(FTriangleSortSettings)) == 0; }
	bool operator!=(const FTriangleSortSettings& other) const { return !(*this == other); }
	bool operator<(const FTriangleSortSettings& other) const { return memcmp(this, &other, sizeof(FTriangleSortSettings)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.SkeletalMeshLODInfo
// 0x004C
struct FSkeletalMeshLODInfo
{
	float                                              DisplayFactor;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LODHysteresis;                                 // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<int32_t>                              LODMaterialMap;                                // 0x0008 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class TArray<uint32_t>                             bEnableShadowCasting;                          // 0x0018 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class TArray<ETriangleSortOption>                  TriangleSorting;                               // 0x0028 (0x0010) [0x0000000020400000] (CPF_NeedCtorLink | CPF_Deprecated)
	class TArray<struct FTriangleSortSettings>         TriangleSortSettings;                          // 0x0038 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	uint32_t                                           bDisableCompressions : 1;                      // 0x0048 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bHasBeenSimplified : 1;                        // 0x0048 (0x0004) [0x0000000000000000] [0x00000002] 

	bool operator==(const FSkeletalMeshLODInfo& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshLODInfo)) == 0; }
	bool operator!=(const FSkeletalMeshLODInfo& other) const { return !(*this == other); }
	bool operator<(const FSkeletalMeshLODInfo& other) const { return memcmp(this, &other, sizeof(FSkeletalMeshLODInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.BoneMirrorExport
// 0x0011
struct FBoneMirrorExport
{
	class FName                                        BoneName;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class FName                                        SourceBoneName;                                // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EAxis                                              BoneFlipAxis;                                  // 0x0010 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBoneMirrorExport& other) const { return memcmp(this, &other, sizeof(FBoneMirrorExport)) == 0; }
	bool operator!=(const FBoneMirrorExport& other) const { return !(*this == other); }
	bool operator<(const FBoneMirrorExport& other) const { return memcmp(this, &other, sizeof(FBoneMirrorExport)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.BoneMirrorInfo
// 0x0005
struct FBoneMirrorInfo
{
	int32_t                                            SourceIndex;                                   // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	EAxis                                              BoneFlipAxis;                                  // 0x0004 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBoneMirrorInfo& other) const { return memcmp(this, &other, sizeof(FBoneMirrorInfo)) == 0; }
	bool operator!=(const FBoneMirrorInfo& other) const { return !(*this == other); }
	bool operator<(const FBoneMirrorInfo& other) const { return memcmp(this, &other, sizeof(FBoneMirrorInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.ApexClothingLodInfo
// 0x0010
struct FApexClothingLodInfo
{
	class TArray<int32_t>                              ClothingSectionInfo;                           // 0x0000 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)

	bool operator==(const FApexClothingLodInfo& other) const { return memcmp(this, &other, sizeof(FApexClothingLodInfo)) == 0; }
	bool operator!=(const FApexClothingLodInfo& other) const { return !(*this == other); }
	bool operator<(const FApexClothingLodInfo& other) const { return memcmp(this, &other, sizeof(FApexClothingLodInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMesh.ApexClothingAssetInfo
// 0x0018
struct FApexClothingAssetInfo
{
	class TArray<struct FApexClothingLodInfo>          ClothingLodInfo;                               // 0x0000 (0x0010) [0x0000000000400041] (CPF_Edit | CPF_EditFixedSize | CPF_NeedCtorLink)
	class FName                                        ClothingAssetName;                             // 0x0010 (0x0008) [0x0000000000000000]               

	bool operator==(const FApexClothingAssetInfo& other) const { return memcmp(this, &other, sizeof(FApexClothingAssetInfo)) == 0; }
	bool operator!=(const FApexClothingAssetInfo& other) const { return !(*this == other); }
	bool operator<(const FApexClothingAssetInfo& other) const { return memcmp(this, &other, sizeof(FApexClothingAssetInfo)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshActor.SkelMeshActorControlTarget
// 0x0010
struct FSkelMeshActorControlTarget
{
	class FName                                        ControlName;                                   // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class AActor*                                      TargetActor;                                   // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSkelMeshActorControlTarget& other) const { return memcmp(this, &other, sizeof(FSkelMeshActorControlTarget)) == 0; }
	bool operator!=(const FSkelMeshActorControlTarget& other) const { return !(*this == other); }
	bool operator<(const FSkelMeshActorControlTarget& other) const { return memcmp(this, &other, sizeof(FSkelMeshActorControlTarget)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshActor.CheckpointRecord
// 0x001C
struct ASkeletalMeshActor_FCheckpointRecord
{
	uint32_t                                           bReplicated : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bHidden : 1;                                   // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bSavedPosition : 1;                            // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	struct FVector                                     Location;                                      // 0x0004 (0x000C) [0x0000000000000000]               
	struct FRotator                                    Rotation;                                      // 0x0010 (0x000C) [0x0000000000000000]               

	bool operator==(const ASkeletalMeshActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ASkeletalMeshActor_FCheckpointRecord)) == 0; }
	bool operator!=(const ASkeletalMeshActor_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ASkeletalMeshActor_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ASkeletalMeshActor_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.SkeletalMeshActorBasedOnExtremeContent.SkelMaterialSetterDatum
// 0x0010
struct FSkelMaterialSetterDatum
{
	int32_t                                            MaterialIndex;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInterface*                          TheMaterial;                                   // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSkelMaterialSetterDatum& other) const { return memcmp(this, &other, sizeof(FSkelMaterialSetterDatum)) == 0; }
	bool operator!=(const FSkelMaterialSetterDatum& other) const { return !(*this == other); }
	bool operator<(const FSkelMaterialSetterDatum& other) const { return memcmp(this, &other, sizeof(FSkelMaterialSetterDatum)) < 0; }
};

// ScriptStruct Engine.SoundClass.SoundClassEditorData
// 0x0008
struct FSoundClassEditorData
{
	int32_t                                            NodePosX;                                      // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            NodePosY;                                      // 0x0004 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FSoundClassEditorData& other) const { return memcmp(this, &other, sizeof(FSoundClassEditorData)) == 0; }
	bool operator!=(const FSoundClassEditorData& other) const { return !(*this == other); }
	bool operator<(const FSoundClassEditorData& other) const { return memcmp(this, &other, sizeof(FSoundClassEditorData)) < 0; }
};

// ScriptStruct Engine.SoundClass.SoundClassProperties
// 0x0020
struct FSoundClassProperties
{
	float                                              Volume;                                        // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Pitch;                                         // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              StereoBleed;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LFEBleed;                                      // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              VoiceCenterChannelVolume;                      // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              RadioFilterVolume;                             // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              RadioFilterVolumeThreshold;                    // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bApplyEffects : 1;                             // 0x001C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bAlwaysPlay : 1;                               // 0x001C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bIsUISound : 1;                                // 0x001C (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	uint32_t                                           bIsMusic : 1;                                  // 0x001C (0x0004) [0x0000000000000001] [0x00000008] (CPF_Edit)
	uint32_t                                           bReverb : 1;                                   // 0x001C (0x0004) [0x0000000000000001] [0x00000010] (CPF_Edit)
	uint32_t                                           bCenterChannelOnly : 1;                        // 0x001C (0x0004) [0x0000000000000001] [0x00000020] (CPF_Edit)
	uint32_t                                           bApplyAmbientVolumes : 1;                      // 0x001C (0x0004) [0x0000000000000001] [0x100000040] (CPF_Edit)

	bool operator==(const FSoundClassProperties& other) const { return memcmp(this, &other, sizeof(FSoundClassProperties)) == 0; }
	bool operator!=(const FSoundClassProperties& other) const { return !(*this == other); }
	bool operator<(const FSoundClassProperties& other) const { return memcmp(this, &other, sizeof(FSoundClassProperties)) < 0; }
};

// ScriptStruct Engine.SoundMode.SoundClassAdjuster
// 0x001C
struct FSoundClassAdjuster
{
	ESoundClassName                                    SoundClassName;                                // 0x0000 (0x0001) [0x0000000000002001] (CPF_Edit | CPF_Transient)
	class FName                                        SoundClass;                                    // 0x0004 (0x0008) [0x0000000000020001] (CPF_Edit | CPF_EditConst)
	float                                              VolumeAdjuster;                                // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              PitchAdjuster;                                 // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bApplyToChildren : 1;                          // 0x0014 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              VoiceCenterChannelVolumeAdjuster;              // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSoundClassAdjuster& other) const { return memcmp(this, &other, sizeof(FSoundClassAdjuster)) == 0; }
	bool operator!=(const FSoundClassAdjuster& other) const { return !(*this == other); }
	bool operator<(const FSoundClassAdjuster& other) const { return memcmp(this, &other, sizeof(FSoundClassAdjuster)) < 0; }
};

// ScriptStruct Engine.SoundMode.AudioEQEffect
// 0x0024
struct FAudioEQEffect
{
	struct FDouble                                     RootTime;                                      // 0x0000 (0x0008) [0x0000000000003000] (CPF_Native | CPF_Transient)
	float                                              HFFrequency;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              HFGain;                                        // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MFCutoffFrequency;                             // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MFBandwidth;                                   // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MFGain;                                        // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LFFrequency;                                   // 0x001C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LFGain;                                        // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FAudioEQEffect& other) const { return memcmp(this, &other, sizeof(FAudioEQEffect)) == 0; }
	bool operator!=(const FAudioEQEffect& other) const { return !(*this == other); }
	bool operator<(const FAudioEQEffect& other) const { return memcmp(this, &other, sizeof(FAudioEQEffect)) < 0; }
};

// ScriptStruct Engine.SoundNodeDistanceCrossFade.DistanceDatum
// 0x0068
struct FDistanceDatum
{
	float                                              FadeInDistanceStart;                           // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeInDistanceEnd;                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeOutDistanceStart;                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              FadeOutDistanceEnd;                            // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Volume;                                        // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FRawDistributionFloat                       FadeInDistance;                                // 0x0018 (0x0028) [0x0000000020480000] (CPF_Component | CPF_NeedCtorLink | CPF_Deprecated)
	struct FRawDistributionFloat                       FadeOutDistance;                               // 0x0040 (0x0028) [0x0000000020480000] (CPF_Component | CPF_NeedCtorLink | CPF_Deprecated)

	bool operator==(const FDistanceDatum& other) const { return memcmp(this, &other, sizeof(FDistanceDatum)) == 0; }
	bool operator!=(const FDistanceDatum& other) const { return !(*this == other); }
	bool operator<(const FDistanceDatum& other) const { return memcmp(this, &other, sizeof(FDistanceDatum)) < 0; }
};

// ScriptStruct Engine.SpeechRecognition.RecognisableWord
// 0x0028
struct FRecognisableWord
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class FString                                      ReferenceWord;                                 // 0x0008 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      PhoneticWord;                                  // 0x0018 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)

	bool operator==(const FRecognisableWord& other) const { return memcmp(this, &other, sizeof(FRecognisableWord)) == 0; }
	bool operator!=(const FRecognisableWord& other) const { return !(*this == other); }
	bool operator<(const FRecognisableWord& other) const { return memcmp(this, &other, sizeof(FRecognisableWord)) < 0; }
};

// ScriptStruct Engine.SpeechRecognition.RecogVocabulary
// 0x0060
struct FRecogVocabulary
{
	class TArray<struct FRecognisableWord>             WhoDictionary;                                 // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FRecognisableWord>             WhatDictionary;                                // 0x0010 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FRecognisableWord>             WhereDictionary;                               // 0x0020 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class FString                                      VocabName;                                     // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              VocabData;                                     // 0x0040 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<uint8_t>                              WorkingVocabData;                              // 0x0050 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRecogVocabulary& other) const { return memcmp(this, &other, sizeof(FRecogVocabulary)) == 0; }
	bool operator!=(const FRecogVocabulary& other) const { return !(*this == other); }
	bool operator<(const FRecogVocabulary& other) const { return memcmp(this, &other, sizeof(FRecogVocabulary)) < 0; }
};

// ScriptStruct Engine.SpeechRecognition.RecogUserData
// 0x0018
struct FRecogUserData
{
	int32_t                                            ActiveVocabularies;                            // 0x0000 (0x0004) [0x0000000000000000]               
	class TArray<uint8_t>                              UserData;                                      // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRecogUserData& other) const { return memcmp(this, &other, sizeof(FRecogUserData)) == 0; }
	bool operator!=(const FRecogUserData& other) const { return !(*this == other); }
	bool operator<(const FRecogUserData& other) const { return memcmp(this, &other, sizeof(FRecogUserData)) < 0; }
};

// ScriptStruct Engine.SpeedTreeComponent.SpeedTreeStaticLight
// 0x0038
struct FSpeedTreeStaticLight
{
	struct FGuid                                       Guid;                                          // 0x0000 (0x0010) [0x0000000000000002] (CPF_Const)   
	class UShadowMap1D*                                BranchShadowMap;                               // 0x0010 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UShadowMap1D*                                FrondShadowMap;                                // 0x0018 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UShadowMap1D*                                LeafMeshShadowMap;                             // 0x0020 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UShadowMap1D*                                LeafCardShadowMap;                             // 0x0028 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UShadowMap1D*                                BillboardShadowMap;                            // 0x0030 (0x0008) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FSpeedTreeStaticLight& other) const { return memcmp(this, &other, sizeof(FSpeedTreeStaticLight)) == 0; }
	bool operator!=(const FSpeedTreeStaticLight& other) const { return !(*this == other); }
	bool operator<(const FSpeedTreeStaticLight& other) const { return memcmp(this, &other, sizeof(FSpeedTreeStaticLight)) < 0; }
};

// ScriptStruct Engine.SplineActor.SplineConnection
// 0x0010
struct FSplineConnection
{
	class USplineComponent*                            SplineComponent;                               // 0x0000 (0x0008) [0x0000000004080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_EditInline)
	class ASplineActor*                                ConnectTo;                                     // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSplineConnection& other) const { return memcmp(this, &other, sizeof(FSplineConnection)) == 0; }
	bool operator!=(const FSplineConnection& other) const { return !(*this == other); }
	bool operator<(const FSplineConnection& other) const { return memcmp(this, &other, sizeof(FSplineConnection)) < 0; }
};

// ScriptStruct Engine.SplineMeshComponent.SplineMeshParams
// 0x0058
struct FSplineMeshParams
{
	struct FVector                                     StartPos;                                      // 0x0000 (0x000C) [0x0000000000000000]               
	struct FVector                                     StartTangent;                                  // 0x000C (0x000C) [0x0000000000000000]               
	struct FVector2D                                   StartScale;                                    // 0x0018 (0x0008) [0x0000000000000000]               
	float                                              StartRoll;                                     // 0x0020 (0x0004) [0x0000000000000000]               
	struct FVector2D                                   StartOffset;                                   // 0x0024 (0x0008) [0x0000000000000000]               
	struct FVector                                     EndPos;                                        // 0x002C (0x000C) [0x0000000000000000]               
	struct FVector                                     EndTangent;                                    // 0x0038 (0x000C) [0x0000000000000000]               
	struct FVector2D                                   EndScale;                                      // 0x0044 (0x0008) [0x0000000000000000]               
	float                                              EndRoll;                                       // 0x004C (0x0004) [0x0000000000000000]               
	struct FVector2D                                   EndOffset;                                     // 0x0050 (0x0008) [0x0000000000000000]               

	bool operator==(const FSplineMeshParams& other) const { return memcmp(this, &other, sizeof(FSplineMeshParams)) == 0; }
	bool operator!=(const FSplineMeshParams& other) const { return !(*this == other); }
	bool operator<(const FSplineMeshParams& other) const { return memcmp(this, &other, sizeof(FSplineMeshParams)) < 0; }
};

// ScriptStruct Engine.SpotLightToggleable.CheckpointRecord
// 0x0004
struct ASpotLightToggleable_FCheckpointRecord
{
	uint32_t                                           bEnabled : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const ASpotLightToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ASpotLightToggleable_FCheckpointRecord)) == 0; }
	bool operator!=(const ASpotLightToggleable_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ASpotLightToggleable_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ASpotLightToggleable_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.StaticMeshActorBasedOnExtremeContent.SMMaterialSetterDatum
// 0x0010
struct FSMMaterialSetterDatum
{
	int32_t                                            MaterialIndex;                                 // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UMaterialInterface*                          TheMaterial;                                   // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSMMaterialSetterDatum& other) const { return memcmp(this, &other, sizeof(FSMMaterialSetterDatum)) == 0; }
	bool operator!=(const FSMMaterialSetterDatum& other) const { return !(*this == other); }
	bool operator<(const FSMMaterialSetterDatum& other) const { return memcmp(this, &other, sizeof(FSMMaterialSetterDatum)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainHeight
// 0x0000
struct FTerrainHeight
{

	bool operator==(const FTerrainHeight& other) const { return memcmp(this, &other, sizeof(FTerrainHeight)) == 0; }
	bool operator!=(const FTerrainHeight& other) const { return !(*this == other); }
	bool operator<(const FTerrainHeight& other) const { return memcmp(this, &other, sizeof(FTerrainHeight)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainInfoData
// 0x0000
struct FTerrainInfoData
{

	bool operator==(const FTerrainInfoData& other) const { return memcmp(this, &other, sizeof(FTerrainInfoData)) == 0; }
	bool operator!=(const FTerrainInfoData& other) const { return !(*this == other); }
	bool operator<(const FTerrainInfoData& other) const { return memcmp(this, &other, sizeof(FTerrainInfoData)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainLayer
// 0x0038
struct FTerrainLayer
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class UTerrainLayerSetup*                          Setup;                                         // 0x0010 (0x0008) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            AlphaMapIndex;                                 // 0x0018 (0x0004) [0x0000000000000000]               
	uint32_t                                           Highlighted : 1;                               // 0x001C (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           WireframeHighlighted : 1;                      // 0x001C (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           Hidden : 1;                                    // 0x001C (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	struct FColor                                      HighlightColor;                                // 0x0020 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FColor                                      WireframeColor;                                // 0x0024 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            MinX;                                          // 0x0028 (0x0004) [0x0000000000000000]               
	int32_t                                            MinY;                                          // 0x002C (0x0004) [0x0000000000000000]               
	int32_t                                            MaxX;                                          // 0x0030 (0x0004) [0x0000000000000000]               
	int32_t                                            MaxY;                                          // 0x0034 (0x0004) [0x0000000000000000]               

	bool operator==(const FTerrainLayer& other) const { return memcmp(this, &other, sizeof(FTerrainLayer)) == 0; }
	bool operator!=(const FTerrainLayer& other) const { return !(*this == other); }
	bool operator<(const FTerrainLayer& other) const { return memcmp(this, &other, sizeof(FTerrainLayer)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainDecorationInstance
// 0x0018
struct FTerrainDecorationInstance
{
	class UPrimitiveComponent*                         Component;                                     // 0x0000 (0x0008) [0x0000000004080008] (CPF_ExportObject | CPF_Component | CPF_EditInline)
	float                                              X;                                             // 0x0008 (0x0004) [0x0000000000000000]               
	float                                              Y;                                             // 0x000C (0x0004) [0x0000000000000000]               
	float                                              Scale;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            Yaw;                                           // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FTerrainDecorationInstance& other) const { return memcmp(this, &other, sizeof(FTerrainDecorationInstance)) == 0; }
	bool operator!=(const FTerrainDecorationInstance& other) const { return !(*this == other); }
	bool operator<(const FTerrainDecorationInstance& other) const { return memcmp(this, &other, sizeof(FTerrainDecorationInstance)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainDecoration
// 0x0030
struct FTerrainDecoration
{
	class UPrimitiveComponentFactory*                  Factory;                                       // 0x0000 (0x0008) [0x0000000004000001] (CPF_Edit | CPF_EditInline)
	float                                              MinScale;                                      // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              MaxScale;                                      // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Density;                                       // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              SlopeRotationBlend;                            // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            RandSeed;                                      // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    
	class TArray<struct FTerrainDecorationInstance>    Instances;                                     // 0x0020 (0x0010) [0x0000000000480000] (CPF_Component | CPF_NeedCtorLink)

	bool operator==(const FTerrainDecoration& other) const { return memcmp(this, &other, sizeof(FTerrainDecoration)) == 0; }
	bool operator!=(const FTerrainDecoration& other) const { return !(*this == other); }
	bool operator<(const FTerrainDecoration& other) const { return memcmp(this, &other, sizeof(FTerrainDecoration)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainDecoLayer
// 0x0024
struct FTerrainDecoLayer
{
	class FString                                      Name;                                          // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	class TArray<struct FTerrainDecoration>            Decorations;                                   // 0x0010 (0x0010) [0x0000000000480001] (CPF_Edit | CPF_Component | CPF_NeedCtorLink)
	int32_t                                            AlphaMapIndex;                                 // 0x0020 (0x0004) [0x0000000000000000]               

	bool operator==(const FTerrainDecoLayer& other) const { return memcmp(this, &other, sizeof(FTerrainDecoLayer)) == 0; }
	bool operator!=(const FTerrainDecoLayer& other) const { return !(*this == other); }
	bool operator<(const FTerrainDecoLayer& other) const { return memcmp(this, &other, sizeof(FTerrainDecoLayer)) < 0; }
};

// ScriptStruct Engine.Terrain.AlphaMap
// 0x0000
struct FAlphaMap
{

	bool operator==(const FAlphaMap& other) const { return memcmp(this, &other, sizeof(FAlphaMap)) == 0; }
	bool operator!=(const FAlphaMap& other) const { return !(*this == other); }
	bool operator<(const FAlphaMap& other) const { return memcmp(this, &other, sizeof(FAlphaMap)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainWeightedMaterial
// 0x0000
struct ATerrain_FTerrainWeightedMaterial
{

	bool operator==(const ATerrain_FTerrainWeightedMaterial& other) const { return memcmp(this, &other, sizeof(ATerrain_FTerrainWeightedMaterial)) == 0; }
	bool operator!=(const ATerrain_FTerrainWeightedMaterial& other) const { return !(*this == other); }
	bool operator<(const ATerrain_FTerrainWeightedMaterial& other) const { return memcmp(this, &other, sizeof(ATerrain_FTerrainWeightedMaterial)) < 0; }
};

// ScriptStruct Engine.Terrain.SelectedTerrainVertex
// 0x000C
struct FSelectedTerrainVertex
{
	int32_t                                            X;                                             // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            Y;                                             // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            Weight;                                        // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FSelectedTerrainVertex& other) const { return memcmp(this, &other, sizeof(FSelectedTerrainVertex)) == 0; }
	bool operator!=(const FSelectedTerrainVertex& other) const { return !(*this == other); }
	bool operator<(const FSelectedTerrainVertex& other) const { return memcmp(this, &other, sizeof(FSelectedTerrainVertex)) < 0; }
};

// ScriptStruct Engine.Terrain.TerrainMaterialResource
// 0x0000
struct FTerrainMaterialResource
{

	bool operator==(const FTerrainMaterialResource& other) const { return memcmp(this, &other, sizeof(FTerrainMaterialResource)) == 0; }
	bool operator!=(const FTerrainMaterialResource& other) const { return !(*this == other); }
	bool operator<(const FTerrainMaterialResource& other) const { return memcmp(this, &other, sizeof(FTerrainMaterialResource)) < 0; }
};

// ScriptStruct Engine.Terrain.CachedTerrainMaterialArray
// 0x0010
struct FCachedTerrainMaterialArray
{
	class TArray<struct FPointer>                      CachedMaterials;                               // 0x0000 (0x0010) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FCachedTerrainMaterialArray& other) const { return memcmp(this, &other, sizeof(FCachedTerrainMaterialArray)) == 0; }
	bool operator!=(const FCachedTerrainMaterialArray& other) const { return !(*this == other); }
	bool operator<(const FCachedTerrainMaterialArray& other) const { return memcmp(this, &other, sizeof(FCachedTerrainMaterialArray)) < 0; }
};

// ScriptStruct Engine.TerrainComponent.TerrainPatchBounds
// 0x000C
struct FTerrainPatchBounds
{
	float                                              MinHeight;                                     // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              MaxHeight;                                     // 0x0004 (0x0004) [0x0000000000000000]               
	float                                              MaxDisplacement;                               // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FTerrainPatchBounds& other) const { return memcmp(this, &other, sizeof(FTerrainPatchBounds)) == 0; }
	bool operator!=(const FTerrainPatchBounds& other) const { return !(*this == other); }
	bool operator<(const FTerrainPatchBounds& other) const { return memcmp(this, &other, sizeof(FTerrainPatchBounds)) < 0; }
};

// ScriptStruct Engine.TerrainComponent.TerrainMaterialMask
// 0x000C
struct FTerrainMaterialMask
{
	uint64_t                                           BitMask;                                       // 0x0000 (0x0008) [0x0000000000000000]               
	int32_t                                            NumBits;                                       // 0x0008 (0x0004) [0x0000000000000000]               

	bool operator==(const FTerrainMaterialMask& other) const { return memcmp(this, &other, sizeof(FTerrainMaterialMask)) == 0; }
	bool operator!=(const FTerrainMaterialMask& other) const { return !(*this == other); }
	bool operator<(const FTerrainMaterialMask& other) const { return memcmp(this, &other, sizeof(FTerrainMaterialMask)) < 0; }
};

// ScriptStruct Engine.TerrainComponent.TerrainBVTree
// 0x0010
struct FTerrainBVTree
{
	class TArray<int32_t>                              Nodes;                                         // 0x0000 (0x0010) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FTerrainBVTree& other) const { return memcmp(this, &other, sizeof(FTerrainBVTree)) == 0; }
	bool operator!=(const FTerrainBVTree& other) const { return !(*this == other); }
	bool operator<(const FTerrainBVTree& other) const { return memcmp(this, &other, sizeof(FTerrainBVTree)) < 0; }
};

// ScriptStruct Engine.TerrainLayerSetup.FilterLimit
// 0x0010
struct FFilterLimit
{
	uint32_t                                           Enabled : 1;                                   // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              Base;                                          // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              NoiseScale;                                    // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              NoiseAmount;                                   // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FFilterLimit& other) const { return memcmp(this, &other, sizeof(FFilterLimit)) == 0; }
	bool operator!=(const FFilterLimit& other) const { return !(*this == other); }
	bool operator<(const FFilterLimit& other) const { return memcmp(this, &other, sizeof(FFilterLimit)) < 0; }
};

// ScriptStruct Engine.TerrainLayerSetup.TerrainFilteredMaterial
// 0x0058
struct FTerrainFilteredMaterial
{
	uint32_t                                           UseNoise : 1;                                  // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	float                                              NoiseScale;                                    // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              NoisePercent;                                  // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FFilterLimit                                MinHeight;                                     // 0x000C (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FFilterLimit                                MaxHeight;                                     // 0x001C (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FFilterLimit                                MinSlope;                                      // 0x002C (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FFilterLimit                                MaxSlope;                                      // 0x003C (0x0010) [0x0000000000000001] (CPF_Edit)    
	float                                              Alpha;                                         // 0x004C (0x0004) [0x0000000000000001] (CPF_Edit)    
	class UTerrainMaterial*                            Material;                                      // 0x0050 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTerrainFilteredMaterial& other) const { return memcmp(this, &other, sizeof(FTerrainFilteredMaterial)) == 0; }
	bool operator!=(const FTerrainFilteredMaterial& other) const { return !(*this == other); }
	bool operator<(const FTerrainFilteredMaterial& other) const { return memcmp(this, &other, sizeof(FTerrainFilteredMaterial)) < 0; }
};

// ScriptStruct Engine.TerrainWeightMapTexture.TerrainWeightedMaterial
// 0x0000
struct UTerrainWeightMapTexture_FTerrainWeightedMaterial
{

	bool operator==(const UTerrainWeightMapTexture_FTerrainWeightedMaterial& other) const { return memcmp(this, &other, sizeof(UTerrainWeightMapTexture_FTerrainWeightedMaterial)) == 0; }
	bool operator!=(const UTerrainWeightMapTexture_FTerrainWeightedMaterial& other) const { return !(*this == other); }
	bool operator<(const UTerrainWeightMapTexture_FTerrainWeightedMaterial& other) const { return memcmp(this, &other, sizeof(UTerrainWeightMapTexture_FTerrainWeightedMaterial)) < 0; }
};

// ScriptStruct Engine.Texture2DComposite.SourceTexture2DRegion
// 0x0020
struct FSourceTexture2DRegion
{
	int32_t                                            OffsetX;                                       // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            OffsetY;                                       // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            SizeX;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            SizeY;                                         // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            DestOffsetX;                                   // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            DestOffsetY;                                   // 0x0014 (0x0004) [0x0000000000000000]               
	class UTexture2D*                                  Texture2D;                                     // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FSourceTexture2DRegion& other) const { return memcmp(this, &other, sizeof(FSourceTexture2DRegion)) == 0; }
	bool operator!=(const FSourceTexture2DRegion& other) const { return !(*this == other); }
	bool operator<(const FSourceTexture2DRegion& other) const { return memcmp(this, &other, sizeof(FSourceTexture2DRegion)) < 0; }
};

// ScriptStruct Engine.Texture2DDynamic.ImageLayout
// 0x0018
struct FImageLayout
{
	class TArray<uint8_t>                              Data;                                          // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	int32_t                                            SizeX;                                         // 0x0010 (0x0004) [0x0000000000000000]               
	int32_t                                            SizeY;                                         // 0x0014 (0x0004) [0x0000000000000000]               

	bool operator==(const FImageLayout& other) const { return memcmp(this, &other, sizeof(FImageLayout)) == 0; }
	bool operator!=(const FImageLayout& other) const { return !(*this == other); }
	bool operator<(const FImageLayout& other) const { return memcmp(this, &other, sizeof(FImageLayout)) < 0; }
};

// ScriptStruct Engine.Trigger.CheckpointRecord
// 0x0004
struct ATrigger_FCheckpointRecord
{
	uint32_t                                           bCollideActors : 1;                            // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 

	bool operator==(const ATrigger_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ATrigger_FCheckpointRecord)) == 0; }
	bool operator!=(const ATrigger_FCheckpointRecord& other) const { return !(*this == other); }
	bool operator<(const ATrigger_FCheckpointRecord& other) const { return memcmp(this, &other, sizeof(ATrigger_FCheckpointRecord)) < 0; }
};

// ScriptStruct Engine.TriggerStreamingLevel.LevelStreamingData
// 0x0010
struct FLevelStreamingData
{
	uint32_t                                           bShouldBeLoaded : 1;                           // 0x0000 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bShouldBeVisible : 1;                          // 0x0000 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	uint32_t                                           bShouldBlockOnLoad : 1;                        // 0x0000 (0x0004) [0x0000000000000001] [0x00000004] (CPF_Edit)
	class ULevelStreaming*                             Level;                                         // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLevelStreamingData& other) const { return memcmp(this, &other, sizeof(FLevelStreamingData)) == 0; }
	bool operator!=(const FLevelStreamingData& other) const { return !(*this == other); }
	bool operator<(const FLevelStreamingData& other) const { return memcmp(this, &other, sizeof(FLevelStreamingData)) < 0; }
};

// ScriptStruct Engine.UIDataProvider_OnlinePlayerStorage.PlayerStorageArrayProvider
// 0x0010
struct FPlayerStorageArrayProvider
{
	int32_t                                            PlayerStorageId;                               // 0x0000 (0x0004) [0x0000000000000000]               
	class UUIDataProvider_OnlinePlayerStorageArray*    Provider;                                      // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FPlayerStorageArrayProvider& other) const { return memcmp(this, &other, sizeof(FPlayerStorageArrayProvider)) == 0; }
	bool operator!=(const FPlayerStorageArrayProvider& other) const { return !(*this == other); }
	bool operator<(const FPlayerStorageArrayProvider& other) const { return memcmp(this, &other, sizeof(FPlayerStorageArrayProvider)) < 0; }
};

// ScriptStruct Engine.UIDataStore_DynamicResource.DynamicResourceProviderDefinition
// 0x0020
struct FDynamicResourceProviderDefinition
{
	class FName                                        ProviderTag;                                   // 0x0000 (0x0008) [0x0000000000004000] (CPF_Config)  
	class FString                                      ProviderClassName;                             // 0x0008 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class UClass*                                      ProviderClass;                                 // 0x0018 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FDynamicResourceProviderDefinition& other) const { return memcmp(this, &other, sizeof(FDynamicResourceProviderDefinition)) == 0; }
	bool operator!=(const FDynamicResourceProviderDefinition& other) const { return !(*this == other); }
	bool operator<(const FDynamicResourceProviderDefinition& other) const { return memcmp(this, &other, sizeof(FDynamicResourceProviderDefinition)) < 0; }
};

// ScriptStruct Engine.UIDataStore_GameResource.GameResourceDataProvider
// 0x0028
struct FGameResourceDataProvider
{
	class FName                                        ProviderTag;                                   // 0x0000 (0x0008) [0x0000000000004000] (CPF_Config)  
	class FString                                      ProviderClassName;                             // 0x0008 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	uint32_t                                           bExpandProviders : 1;                          // 0x0018 (0x0004) [0x0000000000004000] [0x00000001] (CPF_Config)
	class UClass*                                      ProviderClass;                                 // 0x0020 (0x0008) [0x0000000000002000] (CPF_Transient)

	bool operator==(const FGameResourceDataProvider& other) const { return memcmp(this, &other, sizeof(FGameResourceDataProvider)) == 0; }
	bool operator!=(const FGameResourceDataProvider& other) const { return !(*this == other); }
	bool operator<(const FGameResourceDataProvider& other) const { return memcmp(this, &other, sizeof(FGameResourceDataProvider)) < 0; }
};

// ScriptStruct Engine.UIDataStore_InputAlias.UIInputKeyData
// 0x0020
struct FUIInputKeyData
{
	struct FRawInputKeyEventData                       InputKeyData;                                  // 0x0000 (0x000C) [0x0000000000004000] (CPF_Config)  
	class FString                                      ButtonFontMarkupString;                        // 0x0010 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)

	bool operator==(const FUIInputKeyData& other) const { return memcmp(this, &other, sizeof(FUIInputKeyData)) == 0; }
	bool operator!=(const FUIInputKeyData& other) const { return !(*this == other); }
	bool operator<(const FUIInputKeyData& other) const { return memcmp(this, &other, sizeof(FUIInputKeyData)) < 0; }
};

// ScriptStruct Engine.UIDataStore_InputAlias.UIDataStoreInputAlias
// 0x00E8
struct FUIDataStoreInputAlias
{
	class FName                                        AliasName;                                     // 0x0000 (0x0008) [0x0000000000004000] (CPF_Config)  
	struct FUIInputKeyData                             PlatformInputKeys[7];                          // 0x0008 (0x00E0) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)

	bool operator==(const FUIDataStoreInputAlias& other) const { return memcmp(this, &other, sizeof(FUIDataStoreInputAlias)) == 0; }
	bool operator!=(const FUIDataStoreInputAlias& other) const { return !(*this == other); }
	bool operator<(const FUIDataStoreInputAlias& other) const { return memcmp(this, &other, sizeof(FUIDataStoreInputAlias)) < 0; }
};

// ScriptStruct Engine.UIDataStore_OnlineGameSearch.GameSearchCfg
// 0x0030
struct FGameSearchCfg
{
	class UClass*                                      GameSearchClass;                               // 0x0000 (0x0008) [0x0000000000000000]               
	class UClass*                                      DefaultGameSettingsClass;                      // 0x0008 (0x0008) [0x0000000000000000]               
	class UClass*                                      SearchResultsProviderClass;                    // 0x0010 (0x0008) [0x0000000000000000]               
	class UUIDataProvider_Settings*                    DesiredSettingsProvider;                       // 0x0018 (0x0008) [0x0000000000000000]               
	class UOnlineGameSearch*                           Search;                                        // 0x0020 (0x0008) [0x0000000000000000]               
	class FName                                        SearchName;                                    // 0x0028 (0x0008) [0x0000000000000000]               

	bool operator==(const FGameSearchCfg& other) const { return memcmp(this, &other, sizeof(FGameSearchCfg)) == 0; }
	bool operator!=(const FGameSearchCfg& other) const { return !(*this == other); }
	bool operator<(const FGameSearchCfg& other) const { return memcmp(this, &other, sizeof(FGameSearchCfg)) < 0; }
};

// ScriptStruct Engine.UIDataStore_OnlineGameSettings.GameSettingsCfg
// 0x0020
struct FGameSettingsCfg
{
	class UClass*                                      GameSettingsClass;                             // 0x0000 (0x0008) [0x0000000000000000]               
	class UUIDataProvider_Settings*                    Provider;                                      // 0x0008 (0x0008) [0x0000000000000000]               
	class UOnlineGameSettings*                         GameSettings;                                  // 0x0010 (0x0008) [0x0000000000000000]               
	class FName                                        SettingsName;                                  // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FGameSettingsCfg& other) const { return memcmp(this, &other, sizeof(FGameSettingsCfg)) == 0; }
	bool operator!=(const FGameSettingsCfg& other) const { return !(*this == other); }
	bool operator<(const FGameSettingsCfg& other) const { return memcmp(this, &other, sizeof(FGameSettingsCfg)) < 0; }
};

// ScriptStruct Engine.UIDataStore_OnlineStats.RankMetaData
// 0x0018
struct FRankMetaData
{
	class FName                                        RankName;                                      // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      RankColumnName;                                // 0x0008 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FRankMetaData& other) const { return memcmp(this, &other, sizeof(FRankMetaData)) == 0; }
	bool operator!=(const FRankMetaData& other) const { return !(*this == other); }
	bool operator<(const FRankMetaData& other) const { return memcmp(this, &other, sizeof(FRankMetaData)) < 0; }
};

// ScriptStruct Engine.UIDataStore_OnlineStats.PlayerNickMetaData
// 0x0018
struct FPlayerNickMetaData
{
	class FName                                        PlayerNickName;                                // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	class FString                                      PlayerNickColumnName;                          // 0x0008 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)

	bool operator==(const FPlayerNickMetaData& other) const { return memcmp(this, &other, sizeof(FPlayerNickMetaData)) == 0; }
	bool operator!=(const FPlayerNickMetaData& other) const { return !(*this == other); }
	bool operator<(const FPlayerNickMetaData& other) const { return memcmp(this, &other, sizeof(FPlayerNickMetaData)) < 0; }
};

// ScriptStruct Engine.UIDataStore_Registry.RegistryKeyValuePair
// 0x0020
struct FRegistryKeyValuePair
{
	class FString                                      Key;                                           // 0x0000 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FRegistryKeyValuePair& other) const { return memcmp(this, &other, sizeof(FRegistryKeyValuePair)) == 0; }
	bool operator!=(const FRegistryKeyValuePair& other) const { return !(*this == other); }
	bool operator<(const FRegistryKeyValuePair& other) const { return memcmp(this, &other, sizeof(FRegistryKeyValuePair)) < 0; }
};

// ScriptStruct Engine.UIDataStore_StringAliasMap.UIMenuInputMap
// 0x0020
struct FUIMenuInputMap
{
	class FName                                        FieldName;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	class FName                                        Set;                                           // 0x0008 (0x0008) [0x0000000000000000]               
	class FString                                      MappedText;                                    // 0x0010 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FUIMenuInputMap& other) const { return memcmp(this, &other, sizeof(FUIMenuInputMap)) == 0; }
	bool operator!=(const FUIMenuInputMap& other) const { return !(*this == other); }
	bool operator<(const FUIMenuInputMap& other) const { return memcmp(this, &other, sizeof(FUIMenuInputMap)) < 0; }
};

// ScriptStruct Engine.UIInteraction.UIKeyRepeatData
// 0x0010
struct FUIKeyRepeatData
{
	class FName                                        CurrentRepeatKey;                              // 0x0000 (0x0008) [0x0000000000100000]               
	struct FDouble                                     NextRepeatTime;                                // 0x0008 (0x0008) [0x0000000000100000]               

	bool operator==(const FUIKeyRepeatData& other) const { return memcmp(this, &other, sizeof(FUIKeyRepeatData)) == 0; }
	bool operator!=(const FUIKeyRepeatData& other) const { return !(*this == other); }
	bool operator<(const FUIKeyRepeatData& other) const { return memcmp(this, &other, sizeof(FUIKeyRepeatData)) < 0; }
};

// ScriptStruct Engine.UIInteraction.UIAxisEmulationData
// 0x0004 (0x0010 - 0x0014)
struct FUIAxisEmulationData : FUIKeyRepeatData
{
	uint32_t                                           bEnabled : 1;                                  // 0x0010 (0x0004) [0x0000000000100000] [0x100000001] 

	bool operator==(const FUIAxisEmulationData& other) const { return memcmp(this, &other, sizeof(FUIAxisEmulationData)) == 0; }
	bool operator!=(const FUIAxisEmulationData& other) const { return !(*this == other); }
	bool operator<(const FUIAxisEmulationData& other) const { return memcmp(this, &other, sizeof(FUIAxisEmulationData)) < 0; }
};

// ScriptStruct Engine.UISoundTheme.SoundEventMapping
// 0x0010
struct FSoundEventMapping
{
	class FName                                        SoundEventName;                                // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	class USoundCue*                                   SoundToPlay;                                   // 0x0008 (0x0008) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSoundEventMapping& other) const { return memcmp(this, &other, sizeof(FSoundEventMapping)) == 0; }
	bool operator!=(const FSoundEventMapping& other) const { return !(*this == other); }
	bool operator<(const FSoundEventMapping& other) const { return memcmp(this, &other, sizeof(FSoundEventMapping)) < 0; }
};

// ScriptStruct Engine.StaticMesh.StaticMeshLODElement
// 0x0018
struct FStaticMeshLODElement
{
	class UMaterialInterface*                          Material;                                      // 0x0000 (0x0008) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bEnableShadowCasting : 1;                      // 0x0008 (0x0004) [0x0000000000001001] [0x00000001] (CPF_Edit | CPF_Native)
	uint32_t                                           bEnableCollision : 1;                          // 0x0010 (0x0004) [0x0000000000001001] [0x00000001] (CPF_Edit | CPF_Native)

	bool operator==(const FStaticMeshLODElement& other) const { return memcmp(this, &other, sizeof(FStaticMeshLODElement)) == 0; }
	bool operator!=(const FStaticMeshLODElement& other) const { return !(*this == other); }
	bool operator<(const FStaticMeshLODElement& other) const { return memcmp(this, &other, sizeof(FStaticMeshLODElement)) < 0; }
};

// ScriptStruct Engine.StaticMesh.StaticMeshLODInfo
// 0x0010
struct FStaticMeshLODInfo
{
	class TArray<struct FStaticMeshLODElement>         Elements;                                      // 0x0000 (0x0010) [0x0000000000001041] (CPF_Edit | CPF_EditFixedSize | CPF_Native)

	bool operator==(const FStaticMeshLODInfo& other) const { return memcmp(this, &other, sizeof(FStaticMeshLODInfo)) == 0; }
	bool operator!=(const FStaticMeshLODInfo& other) const { return !(*this == other); }
	bool operator<(const FStaticMeshLODInfo& other) const { return memcmp(this, &other, sizeof(FStaticMeshLODInfo)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
