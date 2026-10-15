/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: Core\Core_structs.hpp
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

// ScriptStruct Core.Object.Rotator
// 0x000C
struct FRotator
{
	int32_t                                            Pitch;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Yaw;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Roll;                                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRotator& other) const { return memcmp(this, &other, sizeof(FRotator)) == 0; }
	bool operator!=(const FRotator& other) const { return !(*this == other); }
	bool operator<(const FRotator& other) const { return memcmp(this, &other, sizeof(FRotator)) < 0; }
};

// ScriptStruct Core.Object.Vector
// 0x000C
struct FVector
{
	float                                              X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Z;                                             // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVector& other) const { return memcmp(this, &other, sizeof(FVector)) == 0; }
	bool operator!=(const FVector& other) const { return !(*this == other); }
	bool operator<(const FVector& other) const { return memcmp(this, &other, sizeof(FVector)) < 0; }
};

// ScriptStruct Core.Object.Plane
// 0x0004 (0x000C - 0x0010)
struct alignas(16) FPlane : FVector
{
	float                                              W;                                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPlane& other) const { return memcmp(this, &other, sizeof(FPlane)) == 0; }
	bool operator!=(const FPlane& other) const { return !(*this == other); }
	bool operator<(const FPlane& other) const { return memcmp(this, &other, sizeof(FPlane)) < 0; }
};

// ScriptStruct Core.Object.Guid
// 0x0010
struct FGuid
{
	int32_t                                            A;                                             // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            B;                                             // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            C;                                             // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            D;                                             // 0x000C (0x0004) [0x0000000000000000]               

	bool operator==(const FGuid& other) const { return memcmp(this, &other, sizeof(FGuid)) == 0; }
	bool operator!=(const FGuid& other) const { return !(*this == other); }
	bool operator<(const FGuid& other) const { return memcmp(this, &other, sizeof(FGuid)) < 0; }
};

// ScriptStruct Core.Object.Array_Mirror
// 0x0010
struct FArray_Mirror
{
	struct FPointer                                    Data;                                          // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ArrayNum;                                      // 0x0008 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ArrayMax;                                      // 0x000C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FArray_Mirror& other) const { return memcmp(this, &other, sizeof(FArray_Mirror)) == 0; }
	bool operator!=(const FArray_Mirror& other) const { return !(*this == other); }
	bool operator<(const FArray_Mirror& other) const { return memcmp(this, &other, sizeof(FArray_Mirror)) < 0; }
};

// ScriptStruct Core.Object.InlinePointerArray_Mirror
// 0x0018
struct FInlinePointerArray_Mirror
{
	struct FPointer                                    InlineData;                                    // 0x0000 (0x0008) [0x0000000000000002] (CPF_Const)   
	struct FArray_Mirror                               SecondaryData;                                 // 0x0008 (0x0010) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FInlinePointerArray_Mirror& other) const { return memcmp(this, &other, sizeof(FInlinePointerArray_Mirror)) == 0; }
	bool operator!=(const FInlinePointerArray_Mirror& other) const { return !(*this == other); }
	bool operator<(const FInlinePointerArray_Mirror& other) const { return memcmp(this, &other, sizeof(FInlinePointerArray_Mirror)) < 0; }
};

// ScriptStruct Core.Object.LinearColor
// 0x0010
struct FLinearColor
{
	float                                              R;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              G;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              B;                                             // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              A;                                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FLinearColor& other) const { return memcmp(this, &other, sizeof(FLinearColor)) == 0; }
	bool operator!=(const FLinearColor& other) const { return !(*this == other); }
	bool operator<(const FLinearColor& other) const { return memcmp(this, &other, sizeof(FLinearColor)) < 0; }
};

// ScriptStruct Core.Object.Color
// 0x0004
struct FColor
{
	uint8_t                                            B;                                             // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            G;                                             // 0x0001 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            R;                                             // 0x0002 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            A;                                             // 0x0003 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FColor& other) const { return memcmp(this, &other, sizeof(FColor)) == 0; }
	bool operator!=(const FColor& other) const { return !(*this == other); }
	bool operator<(const FColor& other) const { return memcmp(this, &other, sizeof(FColor)) < 0; }
};

// ScriptStruct Core.Object.Vector2D
// 0x0008
struct FVector2D
{
	float                                              X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVector2D& other) const { return memcmp(this, &other, sizeof(FVector2D)) == 0; }
	bool operator!=(const FVector2D& other) const { return !(*this == other); }
	bool operator<(const FVector2D& other) const { return memcmp(this, &other, sizeof(FVector2D)) < 0; }
};

// ScriptStruct Core.Object.Vector4
// 0x0010
struct alignas(16) FVector4
{
	float                                              X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Z;                                             // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              W;                                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FVector4& other) const { return memcmp(this, &other, sizeof(FVector4)) == 0; }
	bool operator!=(const FVector4& other) const { return !(*this == other); }
	bool operator<(const FVector4& other) const { return memcmp(this, &other, sizeof(FVector4)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointVector2D
// 0x002D
struct FInterpCurvePointVector2D
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   OutVal;                                        // 0x0004 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   ArriveTangent;                                 // 0x000C (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   LeaveTangent;                                  // 0x0014 (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   ArriveWeight;                                  // 0x001C (0x0008) [0x0000000000000001] (CPF_Edit)    
	struct FVector2D                                   LeaveWeight;                                   // 0x0024 (0x0008) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x002C (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpCurvePointVector2D& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointVector2D)) == 0; }
	bool operator!=(const FInterpCurvePointVector2D& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointVector2D& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointVector2D)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveVector2D
// 0x0011
struct FInterpCurveVector2D
{
	class TArray<struct FInterpCurvePointVector2D>     Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveVector2D& other) const { return memcmp(this, &other, sizeof(FInterpCurveVector2D)) == 0; }
	bool operator!=(const FInterpCurveVector2D& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveVector2D& other) const { return memcmp(this, &other, sizeof(FInterpCurveVector2D)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointFloat
// 0x0019
struct FInterpCurvePointFloat
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              OutVal;                                        // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ArriveTangent;                                 // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LeaveTangent;                                  // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              ArriveWeight;                                  // 0x0010 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              LeaveWeight;                                   // 0x0014 (0x0004) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x0018 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpCurvePointFloat& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointFloat)) == 0; }
	bool operator!=(const FInterpCurvePointFloat& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointFloat& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointFloat)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveFloat
// 0x0011
struct FInterpCurveFloat
{
	class TArray<struct FInterpCurvePointFloat>        Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveFloat& other) const { return memcmp(this, &other, sizeof(FInterpCurveFloat)) == 0; }
	bool operator!=(const FInterpCurveFloat& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveFloat& other) const { return memcmp(this, &other, sizeof(FInterpCurveFloat)) < 0; }
};

// ScriptStruct Core.Object.Cylinder
// 0x0008
struct FCylinder
{
	float                                              Radius;                                        // 0x0000 (0x0004) [0x0000000000000000]               
	float                                              Height;                                        // 0x0004 (0x0004) [0x0000000000000000]               

	bool operator==(const FCylinder& other) const { return memcmp(this, &other, sizeof(FCylinder)) == 0; }
	bool operator!=(const FCylinder& other) const { return !(*this == other); }
	bool operator<(const FCylinder& other) const { return memcmp(this, &other, sizeof(FCylinder)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointVector
// 0x0041
struct FInterpCurvePointVector
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     OutVal;                                        // 0x0004 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     ArriveTangent;                                 // 0x0010 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     LeaveTangent;                                  // 0x001C (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     ArriveWeight;                                  // 0x0028 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     LeaveWeight;                                   // 0x0034 (0x000C) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x0040 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpCurvePointVector& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointVector)) == 0; }
	bool operator!=(const FInterpCurvePointVector& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointVector& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointVector)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveVector
// 0x0011
struct FInterpCurveVector
{
	class TArray<struct FInterpCurvePointVector>       Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveVector& other) const { return memcmp(this, &other, sizeof(FInterpCurveVector)) == 0; }
	bool operator!=(const FInterpCurveVector& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveVector& other) const { return memcmp(this, &other, sizeof(FInterpCurveVector)) < 0; }
};

// ScriptStruct Core.Object.Quat
// 0x0010
struct alignas(16) FQuat
{
	float                                              X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Z;                                             // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              W;                                             // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FQuat& other) const { return memcmp(this, &other, sizeof(FQuat)) == 0; }
	bool operator!=(const FQuat& other) const { return !(*this == other); }
	bool operator<(const FQuat& other) const { return memcmp(this, &other, sizeof(FQuat)) < 0; }
};

// ScriptStruct Core.Object.Matrix
// 0x0040
struct alignas(16) FMatrix
{
	struct FPlane                                      XPlane;                                        // 0x0000 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FPlane                                      YPlane;                                        // 0x0010 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FPlane                                      ZPlane;                                        // 0x0020 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FPlane                                      WPlane;                                        // 0x0030 (0x0010) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FMatrix& other) const { return memcmp(this, &other, sizeof(FMatrix)) == 0; }
	bool operator!=(const FMatrix& other) const { return !(*this == other); }
	bool operator<(const FMatrix& other) const { return memcmp(this, &other, sizeof(FMatrix)) < 0; }
};

// ScriptStruct Core.Object.BoxSphereBounds
// 0x001C
struct FBoxSphereBounds
{
	struct FVector                                     Origin;                                        // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     BoxExtent;                                     // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              SphereRadius;                                  // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FBoxSphereBounds& other) const { return memcmp(this, &other, sizeof(FBoxSphereBounds)) == 0; }
	bool operator!=(const FBoxSphereBounds& other) const { return !(*this == other); }
	bool operator<(const FBoxSphereBounds& other) const { return memcmp(this, &other, sizeof(FBoxSphereBounds)) < 0; }
};

// ScriptStruct Core.Object.TwoVectors
// 0x0018
struct FTwoVectors
{
	struct FVector                                     v1;                                            // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     v2;                                            // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTwoVectors& other) const { return memcmp(this, &other, sizeof(FTwoVectors)) == 0; }
	bool operator!=(const FTwoVectors& other) const { return !(*this == other); }
	bool operator<(const FTwoVectors& other) const { return memcmp(this, &other, sizeof(FTwoVectors)) < 0; }
};

// ScriptStruct Core.Object.TAlphaBlend
// 0x0015
struct FTAlphaBlend
{
	float                                              AlphaIn;                                       // 0x0000 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              AlphaOut;                                      // 0x0004 (0x0004) [0x0000000000000002] (CPF_Const)   
	float                                              AlphaTarget;                                   // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendTime;                                     // 0x000C (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              BlendTimeToGo;                                 // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   
	EAlphaBlendType                                    BlendType;                                     // 0x0014 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTAlphaBlend& other) const { return memcmp(this, &other, sizeof(FTAlphaBlend)) == 0; }
	bool operator!=(const FTAlphaBlend& other) const { return !(*this == other); }
	bool operator<(const FTAlphaBlend& other) const { return memcmp(this, &other, sizeof(FTAlphaBlend)) < 0; }
};

// ScriptStruct Core.Object.BoneAtom
// 0x0020
struct alignas(16) FBoneAtom
{
	struct FQuat                                       Rotation;                                      // 0x0000 (0x0010) [0x0000000000000000]               
	struct FVector                                     Translation;                                   // 0x0010 (0x000C) [0x0000000000000000]               
	float                                              Scale;                                         // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FBoneAtom& other) const { return memcmp(this, &other, sizeof(FBoneAtom)) == 0; }
	bool operator!=(const FBoneAtom& other) const { return !(*this == other); }
	bool operator<(const FBoneAtom& other) const { return memcmp(this, &other, sizeof(FBoneAtom)) < 0; }
};

// ScriptStruct Core.Object.OctreeElementId
// 0x000C
struct FOctreeElementId
{
	struct FPointer                                    Node;                                          // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ElementIndex;                                  // 0x0008 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FOctreeElementId& other) const { return memcmp(this, &other, sizeof(FOctreeElementId)) == 0; }
	bool operator!=(const FOctreeElementId& other) const { return !(*this == other); }
	bool operator<(const FOctreeElementId& other) const { return memcmp(this, &other, sizeof(FOctreeElementId)) < 0; }
};

// ScriptStruct Core.Object.RenderCommandFence
// 0x0004
struct FRenderCommandFence
{
	int32_t                                            NumPendingFences;                              // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FRenderCommandFence& other) const { return memcmp(this, &other, sizeof(FRenderCommandFence)) == 0; }
	bool operator!=(const FRenderCommandFence& other) const { return !(*this == other); }
	bool operator<(const FRenderCommandFence& other) const { return memcmp(this, &other, sizeof(FRenderCommandFence)) < 0; }
};

// ScriptStruct Core.Object.RawDistribution
// 0x0020
struct FRawDistribution
{
	uint8_t                                            Type;                                          // 0x0000 (0x0001) [0x0000000000000000]               
	uint8_t                                            Op;                                            // 0x0001 (0x0001) [0x0000000000000000]               
	uint8_t                                            LookupTableNumElements;                        // 0x0002 (0x0001) [0x0000000000000000]               
	uint8_t                                            LookupTableChunkSize;                          // 0x0003 (0x0001) [0x0000000000000000]               
	class TArray<float>                                LookupTable;                                   // 0x0008 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	float                                              LookupTableTimeScale;                          // 0x0018 (0x0004) [0x0000000000000000]               
	float                                              LookupTableStartTime;                          // 0x001C (0x0004) [0x0000000000000000]               

	bool operator==(const FRawDistribution& other) const { return memcmp(this, &other, sizeof(FRawDistribution)) == 0; }
	bool operator!=(const FRawDistribution& other) const { return !(*this == other); }
	bool operator<(const FRawDistribution& other) const { return memcmp(this, &other, sizeof(FRawDistribution)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointLinearColor
// 0x0055
struct FInterpCurvePointLinearColor
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                OutVal;                                        // 0x0004 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                ArriveTangent;                                 // 0x0014 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                LeaveTangent;                                  // 0x0024 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                ArriveWeight;                                  // 0x0034 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FLinearColor                                LeaveWeight;                                   // 0x0044 (0x0010) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x0054 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpCurvePointLinearColor& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointLinearColor)) == 0; }
	bool operator!=(const FInterpCurvePointLinearColor& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointLinearColor& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointLinearColor)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveLinearColor
// 0x0011
struct FInterpCurveLinearColor
{
	class TArray<struct FInterpCurvePointLinearColor>  Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveLinearColor& other) const { return memcmp(this, &other, sizeof(FInterpCurveLinearColor)) == 0; }
	bool operator!=(const FInterpCurveLinearColor& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveLinearColor& other) const { return memcmp(this, &other, sizeof(FInterpCurveLinearColor)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointQuat
// 0x0061
struct FInterpCurvePointQuat
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            UnknownData00[0xC];                              // 0x0004 (0x000C) MISSED OFFSET
	struct FQuat                                       OutVal;                                        // 0x0010 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FQuat                                       ArriveTangent;                                 // 0x0020 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FQuat                                       LeaveTangent;                                  // 0x0030 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FQuat                                       ArriveWeight;                                  // 0x0040 (0x0010) [0x0000000000000001] (CPF_Edit)    
	struct FQuat                                       LeaveWeight;                                   // 0x0050 (0x0010) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x0060 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            MinStructAlignment[0xF];                         // 0x0061 (0x000F) ADDED PADDING

	bool operator==(const FInterpCurvePointQuat& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointQuat)) == 0; }
	bool operator!=(const FInterpCurvePointQuat& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointQuat& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointQuat)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveQuat
// 0x0011
struct FInterpCurveQuat
{
	class TArray<struct FInterpCurvePointQuat>         Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveQuat& other) const { return memcmp(this, &other, sizeof(FInterpCurveQuat)) == 0; }
	bool operator!=(const FInterpCurveQuat& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveQuat& other) const { return memcmp(this, &other, sizeof(FInterpCurveQuat)) < 0; }
};

// ScriptStruct Core.Object.InterpCurvePointTwoVectors
// 0x007D
struct FInterpCurvePointTwoVectors
{
	float                                              InVal;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	struct FTwoVectors                                 OutVal;                                        // 0x0004 (0x0018) [0x0000000000000001] (CPF_Edit)    
	struct FTwoVectors                                 ArriveTangent;                                 // 0x001C (0x0018) [0x0000000000000001] (CPF_Edit)    
	struct FTwoVectors                                 LeaveTangent;                                  // 0x0034 (0x0018) [0x0000000000000001] (CPF_Edit)    
	struct FTwoVectors                                 ArriveWeight;                                  // 0x004C (0x0018) [0x0000000000000001] (CPF_Edit)    
	struct FTwoVectors                                 LeaveWeight;                                   // 0x0064 (0x0018) [0x0000000000000001] (CPF_Edit)    
	EInterpCurveMode                                   InterpMode;                                    // 0x007C (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FInterpCurvePointTwoVectors& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointTwoVectors)) == 0; }
	bool operator!=(const FInterpCurvePointTwoVectors& other) const { return !(*this == other); }
	bool operator<(const FInterpCurvePointTwoVectors& other) const { return memcmp(this, &other, sizeof(FInterpCurvePointTwoVectors)) < 0; }
};

// ScriptStruct Core.Object.InterpCurveTwoVectors
// 0x0011
struct FInterpCurveTwoVectors
{
	class TArray<struct FInterpCurvePointTwoVectors>   Points;                                        // 0x0000 (0x0010) [0x0000000000400001] (CPF_Edit | CPF_NeedCtorLink)
	EInterpMethodType                                  InterpMethod;                                  // 0x0010 (0x0001) [0x0000000000000000]               

	bool operator==(const FInterpCurveTwoVectors& other) const { return memcmp(this, &other, sizeof(FInterpCurveTwoVectors)) == 0; }
	bool operator!=(const FInterpCurveTwoVectors& other) const { return !(*this == other); }
	bool operator<(const FInterpCurveTwoVectors& other) const { return memcmp(this, &other, sizeof(FInterpCurveTwoVectors)) < 0; }
};

// ScriptStruct Core.Object.Box
// 0x0019
struct FBox
{
	struct FVector                                     Min;                                           // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FVector                                     Max;                                           // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            IsValid;                                       // 0x0018 (0x0001) [0x0000000000000000]               

	bool operator==(const FBox& other) const { return memcmp(this, &other, sizeof(FBox)) == 0; }
	bool operator!=(const FBox& other) const { return !(*this == other); }
	bool operator<(const FBox& other) const { return memcmp(this, &other, sizeof(FBox)) < 0; }
};

// ScriptStruct Core.Object.TPOV
// 0x001C
struct FTPOV
{
	struct FVector                                     Location;                                      // 0x0000 (0x000C) [0x0000000000000001] (CPF_Edit)    
	struct FRotator                                    Rotation;                                      // 0x000C (0x000C) [0x0000000000000001] (CPF_Edit)    
	float                                              FOV;                                           // 0x0018 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FTPOV& other) const { return memcmp(this, &other, sizeof(FTPOV)) == 0; }
	bool operator!=(const FTPOV& other) const { return !(*this == other); }
	bool operator<(const FTPOV& other) const { return memcmp(this, &other, sizeof(FTPOV)) < 0; }
};

// ScriptStruct Core.Object.SHVector
// 0x0030
struct alignas(16) FSHVector
{
	float                                              V[9];                                          // 0x0000 (0x0024) [0x0000000000000001] (CPF_Edit)    
	float                                              Padding[3];                                    // 0x0024 (0x000C) [0x0000000000000000]               

	bool operator==(const FSHVector& other) const { return memcmp(this, &other, sizeof(FSHVector)) == 0; }
	bool operator!=(const FSHVector& other) const { return !(*this == other); }
	bool operator<(const FSHVector& other) const { return memcmp(this, &other, sizeof(FSHVector)) < 0; }
};

// ScriptStruct Core.Object.SHVectorRGB
// 0x0090
struct FSHVectorRGB
{
	struct FSHVector                                   R;                                             // 0x0000 (0x0030) [0x0000000000000001] (CPF_Edit)    
	struct FSHVector                                   G;                                             // 0x0030 (0x0030) [0x0000000000000001] (CPF_Edit)    
	struct FSHVector                                   B;                                             // 0x0060 (0x0030) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FSHVectorRGB& other) const { return memcmp(this, &other, sizeof(FSHVectorRGB)) == 0; }
	bool operator!=(const FSHVectorRGB& other) const { return !(*this == other); }
	bool operator<(const FSHVectorRGB& other) const { return memcmp(this, &other, sizeof(FSHVectorRGB)) < 0; }
};

// ScriptStruct Core.Object.IntPoint
// 0x0008
struct FIntPoint
{
	int32_t                                            X;                                             // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	int32_t                                            Y;                                             // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FIntPoint& other) const { return memcmp(this, &other, sizeof(FIntPoint)) == 0; }
	bool operator!=(const FIntPoint& other) const { return !(*this == other); }
	bool operator<(const FIntPoint& other) const { return memcmp(this, &other, sizeof(FIntPoint)) < 0; }
};

// ScriptStruct Core.Object.PackedNormal
// 0x0004
struct FPackedNormal
{
	uint8_t                                            X;                                             // 0x0000 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            Y;                                             // 0x0001 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            Z;                                             // 0x0002 (0x0001) [0x0000000000000001] (CPF_Edit)    
	uint8_t                                            W;                                             // 0x0003 (0x0001) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FPackedNormal& other) const { return memcmp(this, &other, sizeof(FPackedNormal)) == 0; }
	bool operator!=(const FPackedNormal& other) const { return !(*this == other); }
	bool operator<(const FPackedNormal& other) const { return memcmp(this, &other, sizeof(FPackedNormal)) < 0; }
};

// ScriptStruct Core.Object.IndirectArray_Mirror
// 0x0010
struct FIndirectArray_Mirror
{
	struct FPointer                                    Data;                                          // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ArrayNum;                                      // 0x0008 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ArrayMax;                                      // 0x000C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FIndirectArray_Mirror& other) const { return memcmp(this, &other, sizeof(FIndirectArray_Mirror)) == 0; }
	bool operator!=(const FIndirectArray_Mirror& other) const { return !(*this == other); }
	bool operator<(const FIndirectArray_Mirror& other) const { return memcmp(this, &other, sizeof(FIndirectArray_Mirror)) < 0; }
};

// ScriptStruct Core.Object.FColorVertexBuffer_Mirror
// 0x001C
struct FFColorVertexBuffer_Mirror
{
	struct FPointer                                    VfTable;                                       // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    VertexData;                                    // 0x0008 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            Data;                                          // 0x0010 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            Stride;                                        // 0x0014 (0x0004) [0x0000000000000002] (CPF_Const)   
	int32_t                                            NumVertices;                                   // 0x0018 (0x0004) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FFColorVertexBuffer_Mirror& other) const { return memcmp(this, &other, sizeof(FFColorVertexBuffer_Mirror)) == 0; }
	bool operator!=(const FFColorVertexBuffer_Mirror& other) const { return !(*this == other); }
	bool operator<(const FFColorVertexBuffer_Mirror& other) const { return memcmp(this, &other, sizeof(FFColorVertexBuffer_Mirror)) < 0; }
};

// ScriptStruct Core.Object.RenderCommandFence_Mirror
// 0x0004
struct FRenderCommandFence_Mirror
{
	int32_t                                            NumPendingFences;                              // 0x0000 (0x0004) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)

	bool operator==(const FRenderCommandFence_Mirror& other) const { return memcmp(this, &other, sizeof(FRenderCommandFence_Mirror)) == 0; }
	bool operator!=(const FRenderCommandFence_Mirror& other) const { return !(*this == other); }
	bool operator<(const FRenderCommandFence_Mirror& other) const { return memcmp(this, &other, sizeof(FRenderCommandFence_Mirror)) < 0; }
};

// ScriptStruct Core.Object.UntypedBulkData_Mirror
// 0x0054
struct FUntypedBulkData_Mirror
{
	struct FPointer                                    VfTable;                                       // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            BulkDataFlags;                                 // 0x0008 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            ElementCount;                                  // 0x000C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	uint64_t                                           BulkDataOffsetInFile;                          // 0x0010 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            BulkDataSizeOnDisk;                            // 0x0018 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            SavedBulkDataFlags;                            // 0x001C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            SavedElementCount;                             // 0x0020 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	uint64_t                                           SavedBulkDataOffsetInFile;                     // 0x0028 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            SavedBulkDataSizeOnDisk;                       // 0x0030 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    BulkData;                                      // 0x0038 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            LockStatus;                                    // 0x0040 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    AttachedAr;                                    // 0x0048 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            bShouldFreeOnEmpty;                            // 0x0050 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FUntypedBulkData_Mirror& other) const { return memcmp(this, &other, sizeof(FUntypedBulkData_Mirror)) == 0; }
	bool operator!=(const FUntypedBulkData_Mirror& other) const { return !(*this == other); }
	bool operator<(const FUntypedBulkData_Mirror& other) const { return memcmp(this, &other, sizeof(FUntypedBulkData_Mirror)) < 0; }
};

// ScriptStruct Core.Object.BitArray_Mirror
// 0x0020
struct FBitArray_Mirror
{
	struct FPointer                                    IndirectData;                                  // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            InlineData[4];                                 // 0x0008 (0x0010) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            NumBits;                                       // 0x0018 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            MaxBits;                                       // 0x001C (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FBitArray_Mirror& other) const { return memcmp(this, &other, sizeof(FBitArray_Mirror)) == 0; }
	bool operator!=(const FBitArray_Mirror& other) const { return !(*this == other); }
	bool operator<(const FBitArray_Mirror& other) const { return memcmp(this, &other, sizeof(FBitArray_Mirror)) < 0; }
};

// ScriptStruct Core.Object.SparseArray_Mirror
// 0x0038
struct FSparseArray_Mirror
{
	class TArray<int32_t>                              Elements;                                      // 0x0000 (0x0010) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FBitArray_Mirror                            AllocationFlags;                               // 0x0010 (0x0020) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            FirstFreeIndex;                                // 0x0030 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            NumFreeIndices;                                // 0x0034 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FSparseArray_Mirror& other) const { return memcmp(this, &other, sizeof(FSparseArray_Mirror)) == 0; }
	bool operator!=(const FSparseArray_Mirror& other) const { return !(*this == other); }
	bool operator<(const FSparseArray_Mirror& other) const { return memcmp(this, &other, sizeof(FSparseArray_Mirror)) < 0; }
};

// ScriptStruct Core.Object.Set_Mirror
// 0x004C
struct FSet_Mirror
{
	struct FSparseArray_Mirror                         Elements;                                      // 0x0000 (0x0038) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            InlineHash;                                    // 0x0038 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FPointer                                    Hash;                                          // 0x0040 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            HashSize;                                      // 0x0048 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FSet_Mirror& other) const { return memcmp(this, &other, sizeof(FSet_Mirror)) == 0; }
	bool operator!=(const FSet_Mirror& other) const { return !(*this == other); }
	bool operator<(const FSet_Mirror& other) const { return memcmp(this, &other, sizeof(FSet_Mirror)) < 0; }
};

// ScriptStruct Core.Object.MultiMap_Mirror
// 0x0050
struct FMultiMap_Mirror
{
	struct FSet_Mirror                                 Pairs;                                         // 0x0000 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FMultiMap_Mirror& other) const { return memcmp(this, &other, sizeof(FMultiMap_Mirror)) == 0; }
	bool operator!=(const FMultiMap_Mirror& other) const { return !(*this == other); }
	bool operator<(const FMultiMap_Mirror& other) const { return memcmp(this, &other, sizeof(FMultiMap_Mirror)) < 0; }
};

// ScriptStruct Core.Object.Map_Mirror
// 0x0050
struct FMap_Mirror
{
	struct FSet_Mirror                                 Pairs;                                         // 0x0000 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FMap_Mirror& other) const { return memcmp(this, &other, sizeof(FMap_Mirror)) == 0; }
	bool operator!=(const FMap_Mirror& other) const { return !(*this == other); }
	bool operator<(const FMap_Mirror& other) const { return memcmp(this, &other, sizeof(FMap_Mirror)) < 0; }
};

// ScriptStruct Core.Object.ThreadSafeCounter
// 0x0004
struct FThreadSafeCounter
{
	int32_t                                            Value;                                         // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FThreadSafeCounter& other) const { return memcmp(this, &other, sizeof(FThreadSafeCounter)) == 0; }
	bool operator!=(const FThreadSafeCounter& other) const { return !(*this == other); }
	bool operator<(const FThreadSafeCounter& other) const { return memcmp(this, &other, sizeof(FThreadSafeCounter)) < 0; }
};

// ScriptStruct Core.Object.Double
// 0x0008
struct FDouble
{
	int32_t                                            A;                                             // 0x0000 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)
	int32_t                                            B;                                             // 0x0004 (0x0004) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FDouble& other) const { return memcmp(this, &other, sizeof(FDouble)) == 0; }
	bool operator!=(const FDouble& other) const { return !(*this == other); }
	bool operator<(const FDouble& other) const { return memcmp(this, &other, sizeof(FDouble)) < 0; }
};

// ScriptStruct Core.Object.IpAddr
// 0x0014
struct FIpAddr
{
	int32_t                                            AddrA;                                         // 0x0000 (0x0004) [0x0000000000000000]               
	int32_t                                            AddrB;                                         // 0x0004 (0x0004) [0x0000000000000000]               
	int32_t                                            AddrC;                                         // 0x0008 (0x0004) [0x0000000000000000]               
	int32_t                                            AddrD;                                         // 0x000C (0x0004) [0x0000000000000000]               
	int32_t                                            Port;                                          // 0x0010 (0x0004) [0x0000000000000000]               

	bool operator==(const FIpAddr& other) const { return memcmp(this, &other, sizeof(FIpAddr)) == 0; }
	bool operator!=(const FIpAddr& other) const { return !(*this == other); }
	bool operator<(const FIpAddr& other) const { return memcmp(this, &other, sizeof(FIpAddr)) < 0; }
};

// ScriptStruct Core.Object.HatPointer
// 0x0008
struct FHatPointer
{
	uint64_t                                           Dummy;                                         // 0x0000 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

	bool operator==(const FHatPointer& other) const { return memcmp(this, &other, sizeof(FHatPointer)) == 0; }
	bool operator!=(const FHatPointer& other) const { return !(*this == other); }
	bool operator<(const FHatPointer& other) const { return memcmp(this, &other, sizeof(FHatPointer)) < 0; }
};

// ScriptStruct Core._Types_Core.SceNpOnlineId
// 0x0014
struct FSceNpOnlineId
{
	uint64_t                                           Data[2];                                       // 0x0000 (0x0010) [0x0000000000000000]               
	uint8_t                                            Term;                                          // 0x0010 (0x0001) [0x0000000000000000]               
	uint8_t                                            Dummy[3];                                      // 0x0011 (0x0003) [0x0000000000000000]               

	bool operator==(const FSceNpOnlineId& other) const { return memcmp(this, &other, sizeof(FSceNpOnlineId)) == 0; }
	bool operator!=(const FSceNpOnlineId& other) const { return !(*this == other); }
	bool operator<(const FSceNpOnlineId& other) const { return memcmp(this, &other, sizeof(FSceNpOnlineId)) < 0; }
};

// ScriptStruct Core._Types_Core.SceNpId
// 0x0028
struct FSceNpId
{
	struct FSceNpOnlineId                              Handle;                                        // 0x0000 (0x0018) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           Opt;                                           // 0x0018 (0x0008) [0x0000000000000002] (CPF_Const)   
	uint64_t                                           Reserved;                                      // 0x0020 (0x0008) [0x0000000000000002] (CPF_Const)   

	bool operator==(const FSceNpId& other) const { return memcmp(this, &other, sizeof(FSceNpId)) == 0; }
	bool operator!=(const FSceNpId& other) const { return !(*this == other); }
	bool operator<(const FSceNpId& other) const { return memcmp(this, &other, sizeof(FSceNpId)) < 0; }
};

// ScriptStruct Core._Types_Core.UniqueNetId
// 0x0042
struct FUniqueNetId
{
	uint64_t                                           Uid;                                           // 0x0000 (0x0008) [0x0000000000000000]               
	struct FSceNpId                                    NpId;                                          // 0x0008 (0x0028) [0x0000000000000000]               
	class FString                                      EpicAccountId;                                 // 0x0030 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	EOnlinePlatform                                    Platform;                                      // 0x0040 (0x0001) [0x0000000000000000]               
	uint8_t                                            SplitscreenID;                                 // 0x0041 (0x0001) [0x0000000000000000]               

	bool operator==(const FUniqueNetId& other) const { return memcmp(this, &other, sizeof(FUniqueNetId)) == 0; }
	bool operator!=(const FUniqueNetId& other) const { return !(*this == other); }
	bool operator<(const FUniqueNetId& other) const { return memcmp(this, &other, sizeof(FUniqueNetId)) < 0; }
};

// ScriptStruct Core._Types_Core.ProductHashID
// 0x0004
struct FProductHashID
{
	int32_t                                            Id;                                            // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FProductHashID& other) const { return memcmp(this, &other, sizeof(FProductHashID)) == 0; }
	bool operator!=(const FProductHashID& other) const { return !(*this == other); }
	bool operator<(const FProductHashID& other) const { return memcmp(this, &other, sizeof(FProductHashID)) < 0; }
};

// ScriptStruct Core._Types_Core.EncryptedKeyIndex
// 0x0004
struct FEncryptedKeyIndex
{
	int32_t                                            Index;                                         // 0x0000 (0x0004) [0x0000000000000000]               

	bool operator==(const FEncryptedKeyIndex& other) const { return memcmp(this, &other, sizeof(FEncryptedKeyIndex)) == 0; }
	bool operator!=(const FEncryptedKeyIndex& other) const { return !(*this == other); }
	bool operator<(const FEncryptedKeyIndex& other) const { return memcmp(this, &other, sizeof(FEncryptedKeyIndex)) < 0; }
};

// ScriptStruct Core._Types_Core.VoiceAudioDevice
// 0x0024
struct FVoiceAudioDevice
{
	class FString                                      Id;                                            // 0x0000 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	class FString                                      Name;                                          // 0x0010 (0x0010) [0x0000000040400000] (CPF_NeedCtorLink | CPF_DataBinding)
	uint32_t                                           bDefault : 1;                                  // 0x0020 (0x0004) [0x0000000040000000] [0x100000001] (CPF_DataBinding)

	bool operator==(const FVoiceAudioDevice& other) const { return memcmp(this, &other, sizeof(FVoiceAudioDevice)) == 0; }
	bool operator!=(const FVoiceAudioDevice& other) const { return !(*this == other); }
	bool operator<(const FVoiceAudioDevice& other) const { return memcmp(this, &other, sizeof(FVoiceAudioDevice)) < 0; }
};

// ScriptStruct Core._Types_Core.VoiceRoomMemberStatus
// 0x0004
struct FVoiceRoomMemberStatus
{
	uint32_t                                           bLocal : 1;                                    // 0x0000 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bSpeaking : 1;                                 // 0x0000 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bSelfMuted : 1;                                // 0x0000 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bLocalMuted : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bAdminMuted : 1;                               // 0x0000 (0x0004) [0x0000000000000000] [0x00000010] 
	uint32_t                                           bBlocked : 1;                                  // 0x0000 (0x0004) [0x0000000000000000] [0x100000020] 

	bool operator==(const FVoiceRoomMemberStatus& other) const { return memcmp(this, &other, sizeof(FVoiceRoomMemberStatus)) == 0; }
	bool operator!=(const FVoiceRoomMemberStatus& other) const { return !(*this == other); }
	bool operator<(const FVoiceRoomMemberStatus& other) const { return memcmp(this, &other, sizeof(FVoiceRoomMemberStatus)) < 0; }
};

// ScriptStruct Core._Types_Core.ProductInstanceID
// 0x0010
struct FProductInstanceID
{
	uint64_t                                           UpperBits;                                     // 0x0000 (0x0008) [0x0000000000000000]               
	uint64_t                                           LowerBits;                                     // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FProductInstanceID& other) const { return memcmp(this, &other, sizeof(FProductInstanceID)) == 0; }
	bool operator!=(const FProductInstanceID& other) const { return !(*this == other); }
	bool operator<(const FProductInstanceID& other) const { return memcmp(this, &other, sizeof(FProductInstanceID)) < 0; }
};

// ScriptStruct Core.AutomationTest.ScriptWarning
// 0x0034
struct FScriptWarning
{
	class FString                                      Node;                                          // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Message;                                       // 0x0010 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      StackTrace;                                    // 0x0020 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	int32_t                                            ScriptPosition;                                // 0x0030 (0x0004) [0x0000000000000000]               

	bool operator==(const FScriptWarning& other) const { return memcmp(this, &other, sizeof(FScriptWarning)) == 0; }
	bool operator!=(const FScriptWarning& other) const { return !(*this == other); }
	bool operator<(const FScriptWarning& other) const { return memcmp(this, &other, sizeof(FScriptWarning)) < 0; }
};

// ScriptStruct Core.Breadcrumbs.BreadcrumbEntry
// 0x0020
struct FBreadcrumbEntry
{
	class FString                                      Category;                                      // 0x0000 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)
	class FString                                      Value;                                         // 0x0010 (0x0010) [0x0000000000500000] (CPF_NeedCtorLink)

	bool operator==(const FBreadcrumbEntry& other) const { return memcmp(this, &other, sizeof(FBreadcrumbEntry)) == 0; }
	bool operator!=(const FBreadcrumbEntry& other) const { return !(*this == other); }
	bool operator<(const FBreadcrumbEntry& other) const { return memcmp(this, &other, sizeof(FBreadcrumbEntry)) < 0; }
};

// ScriptStruct Core.DelegateTracker.AsyncDelegateInfo
// 0x0020
struct FAsyncDelegateInfo
{
	int32_t                                            CallbackId;                                    // 0x0000 (0x0004) [0x0000000000000000]               
	struct FScriptDelegate                             AsyncDelegate;                                 // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

	bool operator==(const FAsyncDelegateInfo& other) const { return memcmp(this, &other, sizeof(FAsyncDelegateInfo)) == 0; }
	bool operator!=(const FAsyncDelegateInfo& other) const { return !(*this == other); }
	bool operator<(const FAsyncDelegateInfo& other) const { return memcmp(this, &other, sizeof(FAsyncDelegateInfo)) < 0; }
};

// ScriptStruct Core.DistributionFloat.RawDistributionFloat
// 0x0008 (0x0020 - 0x0028)
struct FRawDistributionFloat : FRawDistribution
{
	class UDistributionFloat*                          Distribution;                                  // 0x0020 (0x0008) [0x0000000006080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_NoClear | CPF_EditInline)

	bool operator==(const FRawDistributionFloat& other) const { return memcmp(this, &other, sizeof(FRawDistributionFloat)) == 0; }
	bool operator!=(const FRawDistributionFloat& other) const { return !(*this == other); }
	bool operator<(const FRawDistributionFloat& other) const { return memcmp(this, &other, sizeof(FRawDistributionFloat)) < 0; }
};

// ScriptStruct Core.DistributionFloat.MatineeRawDistributionFloat
// 0x0008 (0x0028 - 0x0030)
struct FMatineeRawDistributionFloat : FRawDistributionFloat
{
	float                                              MatineeValue;                                  // 0x0028 (0x0004) [0x0000000000000000]               
	uint32_t                                           bInMatinee : 1;                                // 0x002C (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FMatineeRawDistributionFloat& other) const { return memcmp(this, &other, sizeof(FMatineeRawDistributionFloat)) == 0; }
	bool operator!=(const FMatineeRawDistributionFloat& other) const { return !(*this == other); }
	bool operator<(const FMatineeRawDistributionFloat& other) const { return memcmp(this, &other, sizeof(FMatineeRawDistributionFloat)) < 0; }
};

// ScriptStruct Core.DistributionVector.RawDistributionVector
// 0x0008 (0x0020 - 0x0028)
struct FRawDistributionVector : FRawDistribution
{
	class UDistributionVector*                         Distribution;                                  // 0x0020 (0x0008) [0x0000000006080009] (CPF_Edit | CPF_ExportObject | CPF_Component | CPF_NoClear | CPF_EditInline)

	bool operator==(const FRawDistributionVector& other) const { return memcmp(this, &other, sizeof(FRawDistributionVector)) == 0; }
	bool operator!=(const FRawDistributionVector& other) const { return !(*this == other); }
	bool operator<(const FRawDistributionVector& other) const { return memcmp(this, &other, sizeof(FRawDistributionVector)) < 0; }
};

// ScriptStruct Core.ObjectProvider.ObjectProviderSubscription
// 0x0024
struct FObjectProviderSubscription
{
	class UClass*                                      ObjClass;                                      // 0x0000 (0x0008) [0x0000000000000000]               
	struct FScriptDelegate                             Callback;                                      // 0x0008 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bFireOnce : 1;                                 // 0x0020 (0x0004) [0x0000000000000000] [0x100000001] 

	bool operator==(const FObjectProviderSubscription& other) const { return memcmp(this, &other, sizeof(FObjectProviderSubscription)) == 0; }
	bool operator!=(const FObjectProviderSubscription& other) const { return !(*this == other); }
	bool operator<(const FObjectProviderSubscription& other) const { return memcmp(this, &other, sizeof(FObjectProviderSubscription)) < 0; }
};

// ScriptStruct Core.ObjectProvider.ObjectProviderPendingCallback
// 0x0020
struct FObjectProviderPendingCallback
{
	struct FScriptDelegate                             Callback;                                      // 0x0000 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	class UObject*                                     Value;                                         // 0x0018 (0x0008) [0x0000000000000000]               

	bool operator==(const FObjectProviderPendingCallback& other) const { return memcmp(this, &other, sizeof(FObjectProviderPendingCallback)) == 0; }
	bool operator!=(const FObjectProviderPendingCallback& other) const { return !(*this == other); }
	bool operator<(const FObjectProviderPendingCallback& other) const { return memcmp(this, &other, sizeof(FObjectProviderPendingCallback)) < 0; }
};

// ScriptStruct Core.ObjectProvider.ObjectPropertyInjection
// 0x0010
struct FObjectPropertyInjection
{
	class UObject*                                     Subscriber;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	class UObjectProperty*                             Property;                                      // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FObjectPropertyInjection& other) const { return memcmp(this, &other, sizeof(FObjectPropertyInjection)) == 0; }
	bool operator!=(const FObjectPropertyInjection& other) const { return !(*this == other); }
	bool operator<(const FObjectPropertyInjection& other) const { return memcmp(this, &other, sizeof(FObjectPropertyInjection)) < 0; }
};

// ScriptStruct Core.ObjectProvider.InterfacePropertyInjection
// 0x0010
struct FInterfacePropertyInjection
{
	class UObject*                                     Subscriber;                                    // 0x0000 (0x0008) [0x0000000000000000]               
	class UInterfaceProperty*                          Property;                                      // 0x0008 (0x0008) [0x0000000000000000]               

	bool operator==(const FInterfacePropertyInjection& other) const { return memcmp(this, &other, sizeof(FInterfacePropertyInjection)) == 0; }
	bool operator!=(const FInterfacePropertyInjection& other) const { return !(*this == other); }
	bool operator<(const FInterfacePropertyInjection& other) const { return memcmp(this, &other, sizeof(FInterfacePropertyInjection)) < 0; }
};

// ScriptStruct Core.RotatorConversions.RotatorDegrees
// 0x000C
struct FRotatorDegrees
{
	float                                              Pitch;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Yaw;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Roll;                                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRotatorDegrees& other) const { return memcmp(this, &other, sizeof(FRotatorDegrees)) == 0; }
	bool operator!=(const FRotatorDegrees& other) const { return !(*this == other); }
	bool operator<(const FRotatorDegrees& other) const { return memcmp(this, &other, sizeof(FRotatorDegrees)) < 0; }
};

// ScriptStruct Core.RotatorConversions.RotatorRadians
// 0x000C
struct FRotatorRadians
{
	float                                              Pitch;                                         // 0x0000 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Yaw;                                           // 0x0004 (0x0004) [0x0000000000000001] (CPF_Edit)    
	float                                              Roll;                                          // 0x0008 (0x0004) [0x0000000000000001] (CPF_Edit)    

	bool operator==(const FRotatorRadians& other) const { return memcmp(this, &other, sizeof(FRotatorRadians)) == 0; }
	bool operator!=(const FRotatorRadians& other) const { return !(*this == other); }
	bool operator<(const FRotatorRadians& other) const { return memcmp(this, &other, sizeof(FRotatorRadians)) < 0; }
};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
