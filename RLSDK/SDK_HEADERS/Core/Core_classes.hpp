/*
#############################################################################################
# Rocket League (RLSDK) SDK 261001.2867.529371
# Generated with the RLSDKGenerator v2.4.6
# ========================================================================================= #
# File: Core\Core_classes.hpp
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
# Classes
# ========================================================================================= #
*/

// Class Core.Object
// 0x0060
class UObject
{
public:
	struct FPointer                                    VfTableObject;                                 // 0x0000 (0x0008) [0x0000000000821002] (CPF_Const | CPF_Native | CPF_EditConst | CPF_NoExport)
	struct FPointer                                    HashNext;                                      // 0x0008 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	uint64_t                                           ObjectFlags;                                   // 0x0010 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	struct FPointer                                    HashOuterNext;                                 // 0x0018 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	struct FPointer                                    StateFrame;                                    // 0x0020 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	class UObject*                                     Linker;                                        // 0x0028 (0x0008) [0x0000000000821002] (CPF_Const | CPF_Native | CPF_EditConst | CPF_NoExport)
	struct FPointer                                    LinkerIndex;                                   // 0x0030 (0x0008) [0x0000000000821002] (CPF_Const | CPF_Native | CPF_EditConst | CPF_NoExport)
	int32_t                                            ObjectInternalInteger;                         // 0x0038 (0x0004) [0x0000000000821002] (CPF_Const | CPF_Native | CPF_EditConst | CPF_NoExport)
	int32_t                                            NetIndex;                                      // 0x003C (0x0004) [0x0000000000821002] (CPF_Const | CPF_Native | CPF_EditConst | CPF_NoExport)
	class UObject*                                     Outer;                                         // 0x0040 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	class FName                                        Name;                                          // 0x0048 (0x0008) [0x0000000000021003] (CPF_Edit | CPF_Const | CPF_Native | CPF_EditConst)
	class UClass*                                      Class;                                         // 0x0050 (0x0008) [0x0000000000021002] (CPF_Const | CPF_Native | CPF_EditConst)
	class UObject*                                     ObjectArchetype;                               // 0x0058 (0x0008) [0x0000000000021003] (CPF_Edit | CPF_Const | CPF_Native | CPF_EditConst)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Object");
		}

		return uClassPointer;
	};

	static class TArray<class UObject*>* GObjObjects();

	std::string GetName();
	std::string GetNameCPP();
	std::string GetFullName();
	class UObject* GetPackageObj();
	template<typename T> static T* FindObject(const std::string& objectFullName)
	{
		for (UObject* uObject : *UObject::GObjObjects())
		{
			if (uObject && uObject->IsA<T>())
			{
				if (uObject->GetFullName() == objectFullName)
				{
					return reinterpret_cast<T*>(uObject);
				}
			}
		}

		return nullptr;
	}
	static class UClass* FindClass(const std::string& classFullName);
	bool IsA(class UClass* uClass);
	bool IsA(int32_t objInternalInteger);
	template<typename T> bool IsA()
	{
		return IsA(T::StaticClass());
	}

	static struct FRotator RSmoothInterpTo(const struct FRotator& From, const struct FRotator& To, float Lambda, float DeltaTime);
	static struct FVector VSmoothInterpTo(const struct FVector& From, const struct FVector& To, float Lambda, float DeltaTime);
	static float FSmoothInterpTo(float From, float To, float Lambda, float DeltaTime);
	static float GetSmoothInterpLerpValue(float Lambda, float DeltaTime);
	static class UObject* GetTypedOuter(class UClass* ObjClass);
	void MarkPendingKill();
	static bool NotNone(class UObject* O);
	static void SwapArrayItems();
	static void Swap();
	static float SumFloat(float Total, float Value);
	static int32_t SumInt(int32_t Total, int32_t Value);
	static int32_t SortDescendingFloat(float A, float B);
	static int32_t SortAscendingFloat(float A, float B);
	static int32_t SortDescendingString(const class FString& A, const class FString& B);
	static int32_t SortAscendingString(const class FString& A, const class FString& B);
	static int32_t SortDescendingQWORD(uint64_t A, uint64_t B);
	static int32_t SortAscendingQWORD(uint64_t A, uint64_t B);
	static int32_t SortDescendingInt(int32_t A, int32_t B);
	static int32_t SortAscendingInt(int32_t A, int32_t B);
	static class FString PadString(const class FString& Str, int32_t Characters);
	static uint64_t GetFrameCounter();
	static float GetScaledAxisValue(float Value, float Sensitivity, float MaxSensitivity);
	static class UObject* GetSingleton(class UClass* ObjClass);
	static class UObjectProvider* GetObjectProviderW();
	static bool IsAutomationTest();
	class FString ToJson();
	void SetRooted(bool bRooted);
	static void ProfNodeEvent(const class FString& EventName);
	static void ProfNodeSetDepthThreshold(int32_t Depth);
	static void ProfNodeSetTimeThresholdSeconds(float Threshold);
	static void ProfNodeStop(int32_t optionalAssumedTimerIndex = {});
	static int32_t ProfNodeStart(const class FString& TimerName);
	static class FString CreateGuidString();
	static class FString GetStringFromGuid(struct FGuid& outInGuid);
	static struct FGuid GetGuidFromString(class FString& outInGuidString);
	static struct FGuid CreateGuid();
	static bool IsGuidValid(struct FGuid& outInGuid);
	static void InvalidateGuid(struct FGuid& outInGuid);
	class UObject* FindStructProperty(class UClass* PropertyClass, const class FName& PropertyName, const class FName& StructName);
	class UObject* FindProperty(class UClass* PropertyClass, const class FName& PropertyName);
	class UObject* DuplicateObject(class UObject* Template, class UObject* optionalObjOuter = {}, class UClass* optionalDestClass = {});
	float RunningAverage(float OldAverage, float NewValue, int32_t NewCount);
	static float GetCurrentTimeW();
	struct FLinearColor GetMaxLinearColorBrightness(const struct FLinearColor& C);
	struct FColor GetMaxColorBrightness(const struct FColor& C);
	static struct FLinearColor LABtoRGB(const struct FLinearColor& C);
	static struct FLinearColor RGBtoLAB(const struct FLinearColor& C);
	static struct FLinearColor HSVtoRGB(const struct FLinearColor& C);
	static struct FLinearColor RGBtoHSV(const struct FLinearColor& C);
	static struct FLinearColor IntToLinearColor(int32_t I);
	static struct FColor IntToColor(int32_t I);
	static int32_t LinearColorToInt(const struct FLinearColor& C);
	static int32_t ColorToInt(const struct FColor& C);
	bool SolveVelocityQuadratic(float Distance, float Speed, float Accel, float& outTime);
	float Sign(float X);
	static struct FVector2D MakeVector2D(float X, float Y);
	static struct FVector VAbs(const struct FVector& V);
	static struct FVector MakeVector(float X, float Y, float Z);
	struct FVector FlattenVector(const struct FVector& NormalToFlatten, const struct FVector& PlaneNormal);
	class FName GetRealArchetypeName();
	static class FString FormatTime(int32_t Seconds);
	static class UObject* GetTextArchetype(class UClass* ArchetypeClass, const class FString& Path);
	bool IsArchetype();
	void UnsubscribeFromAllEvents();
	class UObject* NewInstance(class UObject* optionalObjOuter = {}, const class FName& optionalObjName = {});
	void PrintDebugInfo(class UDebugDrawer* Drawer);
	static struct FRotator RotatorFromInt(int32_t RotationPitchAndYaw);
	static int32_t RotatorToInt(const struct FRotator& Rotation);
	static class FString GetLanguage();
	int32_t GetRandomOptionSumFrequency(class TArray<float>& outFreqList);
	int32_t GetBuildChangelistNumber();
	int32_t GetEngineVersion();
	float GetAppSeconds();
	void GetSystemTime(int32_t& outYear, int32_t& outMonth, int32_t& outDayOfWeek, int32_t& outDay, int32_t& outHour, int32_t& outMin, int32_t& outSec, int32_t& outMSec);
	class FString TimeStamp();
	struct FVector TransformVectorByRotation(const struct FRotator& SourceRotation, const struct FVector& SourceVector, bool optionalBInverse = {});
	class FName GetPackageName();
	bool IsPendingKill();
	float RangeByteToFloatUnsigned(uint8_t inputByte);
	float RangeByteToFloatSigned(uint8_t inputByte);
	uint8_t FloatToRangeByteUnsigned(float inputFloat);
	uint8_t FloatToRangeByteSigned(float inputFloat);
	static float UnwindHeading(float A);
	static float FindDeltaAngle(float A1, float A2);
	static float GetHeadingAngle(const struct FVector& Dir);
	static void GetAngularDegreesFromRadians(struct FVector2D& outOutFOV);
	static void GetAngularFromDotDist(const struct FVector2D& DotDist, struct FVector2D& outOutAngDist);
	static bool GetAngularDistance(const struct FVector& Direction, const struct FVector& AxisX, const struct FVector& AxisY, const struct FVector& AxisZ, struct FVector2D& outOutAngularDist);
	static bool GetDotDistance(const struct FVector& Direction, const struct FVector& AxisX, const struct FVector& AxisY, const struct FVector& AxisZ, struct FVector2D& outOutDotDist);
	bool LinePlaneIntersection(const struct FVector& LineStart, const struct FVector& LineEnd, const struct FVector& PlaneOrigin, const struct FVector& PlaneNormal, bool optionalBCheckLineSegment, struct FVector& outOut_Intersection, float& outOut_T);
	static struct FVector PointProjectToPlane(const struct FVector& Point, const struct FVector& A, const struct FVector& B, const struct FVector& C);
	float PointDistToPlane(const struct FVector& Point, const struct FRotator& Orientation, const struct FVector& Origin, struct FVector& outOut_ClosestPoint);
	float PointDistToSegment(const struct FVector& Point, const struct FVector& StartPoint, const struct FVector& EndPoint, struct FVector& outOutClosestPoint);
	static float PointDistToLine(const struct FVector& Point, const struct FVector& Line, const struct FVector& Origin, struct FVector& outOutClosestPoint);
	static void GetPerObjectConfigObjects(class UClass* SearchClass, class UObject* optionalObjectOuter, int32_t optionalMaxResults, class UObject*& outOutObject);
	static bool GetPerObjectConfigSections(class UClass* SearchClass, class UObject* optionalObjectOuter, int32_t optionalMaxResults, class TArray<class FString>& outOut_SectionNames);
	static void ImportJSON(const class FString& PropertyName, class FString& outJSON);
	static void StaticSaveConfig();
	void SaveConfig();
	static class UObject* LoadSeekFreeObject(class UClass* ObjClass, const class FString& Path);
	static class UObject* FindObject(const class FString& ObjectName, class UClass* ObjectClass);
	static class UObject* DynamicLoadObject(const class FString& ObjectName, class UClass* ObjectClass, bool optionalMayFail = {});
	static int32_t EnumFromString(class UObject* E, const class FName& ValueName);
	static class FName GetEnum(class UObject* E, int32_t I);
	void Disable(const class FName& ProbeFunc);
	void Enable(const class FName& ProbeFunc);
	void eventContinuedState();
	void eventPausedState();
	void eventPoppedState();
	void eventPushedState();
	void eventEndState(const class FName& NextStateName);
	void eventBeginState(const class FName& PreviousStateName);
	void DumpStateStack();
	void PopState(bool optionalBPopAll = {});
	void PushState(const class FName& NewState, const class FName& optionalNewLabel = {});
	class FName GetStateName();
	bool IsChildState(const class FName& TestState, const class FName& TestParentState);
	bool IsInState(const class FName& TestState, bool optionalBTestStateStack = {});
	void GotoState(const class FName& optionalNewState = {}, const class FName& optionalLabel = {}, bool optionalBForceEvents = {}, bool optionalBKeepStack = {});
	static bool IsUTracing();
	static void SetUTracing(bool bShouldUTrace);
	static class FName GetFuncName();
	static void DebugBreak(int32_t optionalUserFlags = {}, EDebugBreakType optionalDebuggerType = {});
	static class FString GetScriptTrace();
	static void ScriptTrace();
	static class FString ParseLocalizedPropertyPath(const class FString& PathName);
	static class FString Localize(const class FString& SectionName, const class FString& KeyName, const class FString& optionalPackageName = {}, bool optionalBOptional = {});
	static void WarnInternal(const class FString& S);
	static void LogInternal(const class FString& S, const class FName& optionalTag = {}, bool optionalBFileOnly = {});
	static struct FLinearColor LinearColorLerp(const struct FLinearColor& ColorA, const struct FLinearColor& ColorB, float Alpha);
	static struct FLinearColor Subtract_LinearColorLinearColor(const struct FLinearColor& A, const struct FLinearColor& B);
	static struct FLinearColor Multiply_LinearColorFloat(const struct FLinearColor& LC, float Mult);
	static struct FLinearColor ConvertFromSRGB(const struct FLinearColor& OldColor);
	static struct FColor LinearColorToColor(const struct FLinearColor& OldColor);
	static struct FLinearColor ColorToLinearColor(const struct FColor& OldColor);
	static struct FLinearColor MakeLinearColor(float R, float G, float B, float optionalA = {});
	static struct FColor LerpColor(const struct FColor& A, const struct FColor& B, float Alpha);
	static struct FColor MakeColor(uint8_t R, uint8_t G, uint8_t B, uint8_t optionalA = {});
	static struct FColor Add_ColorColor(const struct FColor& A, const struct FColor& B);
	static struct FColor Multiply_ColorFloat(const struct FColor& A, float B);
	static struct FColor Multiply_FloatColor(float A, const struct FColor& B);
	static struct FColor Subtract_ColorColor(const struct FColor& A, const struct FColor& B);
	static struct FVector2D EvalInterpCurveVector2D(float InVal, struct FInterpCurveVector2D& outVector2DCurve);
	static void AutoSetTangentsVector(struct FInterpCurveVector& outCurve);
	static struct FVector EvalInterpCurveVector(float InVal, struct FInterpCurveVector& outVectorCurve);
	static void AutoSetTangentsFloat(struct FInterpCurveFloat& outCurve);
	static float EvalInterpCurveFloat(float InVal, struct FInterpCurveFloat& outFloatCurve);
	static struct FVector2D vect2d(float InX, float InY);
	static float GetMappedRangeValue(const struct FVector2D& InputRange, const struct FVector2D& OutputRange, float Value);
	static float GetRangePctByValue(const struct FVector2D& Range, float Value);
	static float GetRangeValueByPct(const struct FVector2D& Range, float Pct);
	static struct FVector2D V2DNormal(const struct FVector2D& A);
	static float V2DSizeSq(const struct FVector2D& A);
	static float V2DSize(const struct FVector2D& A);
	static float Dot_Vector2DVector2D(const struct FVector2D& A, const struct FVector2D& B);
	static struct FVector2D SubtractEqual_Vector2DVector2D(const struct FVector2D& B, struct FVector2D& outA);
	static struct FVector2D AddEqual_Vector2DVector2D(const struct FVector2D& B, struct FVector2D& outA);
	static struct FVector2D DivideEqual_Vector2DFloat(float B, struct FVector2D& outA);
	static struct FVector2D MultiplyEqual_Vector2DFloat(float B, struct FVector2D& outA);
	static struct FVector2D Divide_Vector2DFloat(const struct FVector2D& A, float B);
	static struct FVector2D Multiply_Vector2DFloat(const struct FVector2D& A, float B);
	static struct FVector2D Subtract_Vector2DVector2D(const struct FVector2D& A, const struct FVector2D& B);
	static struct FVector2D Add_Vector2DVector2D(const struct FVector2D& A, const struct FVector2D& B);
	static struct FQuat Subtract_QuatQuat(const struct FQuat& A, const struct FQuat& B);
	static struct FQuat Add_QuatQuat(const struct FQuat& A, const struct FQuat& B);
	static struct FQuat QuatSlerp(const struct FQuat& A, const struct FQuat& B, float Alpha, bool optionalBShortestPath = {});
	static struct FRotator QuatToRotator(const struct FQuat& A);
	static struct FQuat QuatFromRotator(const struct FRotator& A);
	static struct FQuat QuatFromAxisAndAngle(const struct FVector& Axis, float Angle);
	static struct FQuat QuatFindBetween(const struct FVector& A, const struct FVector& B);
	static struct FVector QuatRotateVector(const struct FQuat& A, const struct FVector& B);
	static struct FQuat QuatInvert(const struct FQuat& A);
	static float QuatDot(const struct FQuat& A, const struct FQuat& B);
	static struct FQuat QuatProduct(const struct FQuat& A, const struct FQuat& B);
	static struct FVector MatrixGetAxis(const struct FMatrix& TM, EAxis Axis);
	static struct FVector MatrixGetOrigin(const struct FMatrix& TM);
	static struct FRotator MatrixGetRotator(const struct FMatrix& TM);
	static struct FMatrix MakeRotationMatrix(const struct FRotator& Rotation);
	static struct FMatrix MakeRotationTranslationMatrix(const struct FVector& Translation, const struct FRotator& Rotation);
	static struct FVector InverseTransformNormal(const struct FMatrix& TM, const struct FVector& A);
	static struct FVector TransformNormal(const struct FMatrix& TM, const struct FVector& A);
	static struct FVector InverseTransformVector(const struct FMatrix& TM, const struct FVector& A);
	static struct FVector TransformVector(const struct FMatrix& TM, const struct FVector& A);
	static struct FMatrix Multiply_MatrixMatrix(const struct FMatrix& A, const struct FMatrix& B);
	static bool NotEqual_NameName(const class FName& A, const class FName& B);
	static bool EqualEqual_NameName(const class FName& A, const class FName& B);
	bool IsA(const class FName& ClassName);
	static bool ClassIsChildOf(class UClass* TestClass, class UClass* ParentClass);
	static bool NotEqual_InterfaceInterface(class UInterface* A, class UInterface* B);
	static bool EqualEqual_InterfaceInterface(class UInterface* A, class UInterface* B);
	static bool NotEqual_ObjectObject(class UObject* A, class UObject* B);
	static bool EqualEqual_ObjectObject(class UObject* A, class UObject* B);
	class FString GetPathName();
	static class FString PathName(class UObject* CheckObject);
	static class TArray<class FString> SplitString(const class FString& Source, const class FString& optionalDelimiter = {}, bool optionalBCullEmpty = {});
	static void ParseStringIntoArray(const class FString& BaseString, const class FString& delim, bool bCullEmpty, class TArray<class FString>& outPieces);
	static bool ContainsWhitespace(const class FString& Text);
	static class FString RepeatString(const class FString& InValue, int32_t Count);
	static class FString JoinArrayQWord(const class FString& optionalDelim, bool optionalBIgnoreBlanks, class TArray<uint64_t>& outQWordArray);
	static class FString JoinArrayInt(const class FString& optionalDelim, bool optionalBIgnoreBlanks, class TArray<int32_t>& outIntArray);
	static class FString JoinArrayName(const class FString& optionalDelim, bool optionalBIgnoreBlanks, class TArray<class FName>& outNameArray);
	static class FString JoinArrayStr(const class FString& optionalDelim, bool optionalBIgnoreBlanks, class TArray<class FString>& outStringArray);
	static void JoinArray(const class FString& optionalDelim, bool optionalBIgnoreBlanks, class TArray<class FString>& outStringArray, class FString& outOut_Result);
	static class FString GetRightMost(const class FString& Text);
	static class FString Split(const class FString& Text, const class FString& SplitStr, bool optionalBOmitSplitStr = {});
	static class FString TCharToUTF8(const class FString& Src);
	static class FString UTF8ToTChar(const class FString& Src);
	static class FString MakeAsciiSafe(const class FString& InStr);
	static class FString PadRight(const class FString& S, int32_t optionalWidthChars = {});
	static bool StartsWith(const class FString& Src, const class FString& Prefix);
	static class FString Trim(const class FString& Src);
	static class FString Repl(const class FString& Src, const class FString& Match, const class FString& With, bool optionalBCaseSensitive = {});
	static int32_t Asc(const class FString& S);
	static class FString Chr(int32_t I);
	static class FString Locs(const class FString& S);
	static class FString Caps(const class FString& S);
	static class FString Right(const class FString& S, int32_t I);
	static class FString Left(const class FString& S, int32_t I);
	static class FString Mid(const class FString& S, int32_t I, int32_t optionalJ = {});
	static int32_t InStr(const class FString& S, const class FString& T, bool optionalBSearchFromRight = {}, bool optionalBIgnoreCase = {}, int32_t optionalStartPos = {});
	static int32_t Len(const class FString& S);
	static class FString SubtractEqual_StrStr(const class FString& B, class FString& outA);
	static class FString AtEqual_StrStr(const class FString& B, class FString& outA);
	static class FString ConcatEqual_StrStr(const class FString& B, class FString& outA);
	static bool ComplementEqual_StrStr(const class FString& A, const class FString& B);
	static bool NotEqual_StrStr(const class FString& A, const class FString& B);
	static bool EqualEqual_StrStr(const class FString& A, const class FString& B);
	static bool GreaterEqual_StrStr(const class FString& A, const class FString& B);
	static bool LessEqual_StrStr(const class FString& A, const class FString& B);
	static bool Greater_StrStr(const class FString& A, const class FString& B);
	static bool Less_StrStr(const class FString& A, const class FString& B);
	static class FString At_StrStr(const class FString& A, const class FString& B);
	static class FString Concat_StrStr(const class FString& A, const class FString& B);
	static struct FRotator RotateRotator(const struct FVector& Axis, const struct FRotator& Rot, const struct FRotator& Direction, float Amount);
	static struct FQuat MakeQuat(float X, float Y, float Z, float W);
	static struct FRotator MakeRotator(int32_t Pitch, int32_t Yaw, int32_t Roll);
	static bool SClampRotAxis(float DeltaTime, int32_t ViewAxis, int32_t MaxLimit, int32_t MinLimit, float InterpolationSpeed, int32_t& outOut_DeltaViewAxis);
	static int32_t ClampRotAxisFromRange(int32_t Current, int32_t Min, int32_t Max);
	static int32_t ClampRotAxisFromBase(int32_t Current, int32_t Center, int32_t MaxDelta);
	static void ClampRotAxis(int32_t ViewAxis, int32_t MaxLimit, int32_t MinLimit, int32_t& outOut_DeltaViewAxis);
	static struct FRotator FlattenRotatorOnAxis(const struct FVector& AxisToRemove, const struct FRotator& RotToFlatten, const struct FRotator& optionalRotToFlattenTo);
	static float RSize(const struct FRotator& R);
	static float RDiff(const struct FRotator& A, const struct FRotator& B);
	static int32_t NormalizeRotAxis(int32_t Angle);
	static struct FRotator RInterpTo(const struct FRotator& Current, const struct FRotator& Target, float DeltaTime, float InterpSpeed, bool optionalBConstantInterpSpeed = {});
	static struct FRotator RTransform(const struct FRotator& R, const struct FRotator& RBasis);
	static struct FRotator RLerp(const struct FRotator& A, const struct FRotator& B, float Alpha, bool optionalBShortestPath = {});
	static struct FRotator Normalize(const struct FRotator& Rot);
	static struct FRotator OrthoRotation(const struct FVector& X, const struct FVector& Y, const struct FVector& Z);
	static struct FRotator RotRand(bool optionalBRoll = {});
	static struct FVector GetRotatorAxis(const struct FRotator& A, int32_t Axis);
	static void GetUnAxes(const struct FRotator& A, struct FVector& outX, struct FVector& outY, struct FVector& outZ);
	static void GetAxes(const struct FRotator& A, struct FVector& outX, struct FVector& outY, struct FVector& outZ);
	static bool ClockwiseFrom_IntInt(int32_t A, int32_t B);
	static struct FRotator SubtractEqual_RotatorRotator(const struct FRotator& B, struct FRotator& outA);
	static struct FRotator AddEqual_RotatorRotator(const struct FRotator& B, struct FRotator& outA);
	static struct FRotator Subtract_RotatorRotator(const struct FRotator& A, const struct FRotator& B);
	static struct FRotator Add_RotatorRotator(const struct FRotator& A, const struct FRotator& B);
	static struct FRotator DivideEqual_RotatorFloat(float B, struct FRotator& outA);
	static struct FRotator MultiplyEqual_RotatorFloat(float B, struct FRotator& outA);
	static struct FRotator Divide_RotatorFloat(const struct FRotator& A, float B);
	static struct FRotator Multiply_FloatRotator(float A, const struct FRotator& B);
	static struct FRotator Multiply_RotatorFloat(const struct FRotator& A, float B);
	static bool NotEqual_RotatorRotator(const struct FRotator& A, const struct FRotator& B);
	static bool EqualEqual_RotatorRotator(const struct FRotator& A, const struct FRotator& B);
	static float GetRadiansBetweenVectors(const struct FVector& V0, const struct FVector& v1);
	static struct FVector VClamp(const struct FVector& A, const struct FVector& Min, const struct FVector& Max);
	static struct FVector vect3d(float X, float Y, float Z);
	bool InCylinder(const struct FVector& Origin, const struct FRotator& Dir, float Width, const struct FVector& A, bool optionalBIgnoreZ = {});
	static float NoZDot(const struct FVector& A, const struct FVector& B);
	static struct FVector ClampLength(const struct FVector& V, float MaxLength);
	static struct FVector VInterpConstantTo(const struct FVector& Current, const struct FVector& Target, float DeltaTime, float InterpSpeed);
	static struct FVector VInterpTo(const struct FVector& Current, const struct FVector& Target, float DeltaTime, float InterpSpeed);
	void eventConstruct();
	static struct FVector ProjectOnToPlane(const struct FVector& InVector, const struct FVector& InNormal, float optionalOverBounce = {});
	static bool IsZero(const struct FVector& A);
	static struct FVector ProjectOnTo(const struct FVector& X, const struct FVector& Y);
	static struct FVector MirrorVectorByNormal(const struct FVector& InVect, const struct FVector& InNormal);
	static struct FVector VRandCone2(const struct FVector& Dir, float HorizontalConeHalfAngleRadians, float VerticalConeHalfAngleRadians);
	static struct FVector VRandCone(const struct FVector& Dir, float ConeHalfAngleRadians);
	static struct FVector VRand();
	static struct FVector VLerp(const struct FVector& A, const struct FVector& B, float Alpha);
	static struct FVector Normal2D(const struct FVector& A);
	static struct FVector Normal(const struct FVector& A);
	static float VSizeSq2D(const struct FVector& A);
	static float VSizeSq(const struct FVector& A);
	static float VSize2D(const struct FVector& A);
	static float VSize(const struct FVector& A);
	static struct FVector SubtractEqual_VectorVector(const struct FVector& B, struct FVector& outA);
	static struct FVector AddEqual_VectorVector(const struct FVector& B, struct FVector& outA);
	static struct FVector DivideEqual_VectorFloat(float B, struct FVector& outA);
	static struct FVector MultiplyEqual_VectorVector(const struct FVector& B, struct FVector& outA);
	static struct FVector MultiplyEqual_VectorFloat(float B, struct FVector& outA);
	static struct FVector Cross_VectorVector(const struct FVector& A, const struct FVector& B);
	static float Dot_VectorVector(const struct FVector& A, const struct FVector& B);
	static bool NotEqual_VectorVector(const struct FVector& A, const struct FVector& B);
	static bool EqualEqual_VectorVector(const struct FVector& A, const struct FVector& B);
	static struct FVector GreaterGreater_VectorRotator(const struct FVector& A, const struct FRotator& B);
	static struct FVector LessLess_VectorRotator(const struct FVector& A, const struct FRotator& B);
	static struct FVector Subtract_VectorVector(const struct FVector& A, const struct FVector& B);
	static struct FVector Add_VectorVector(const struct FVector& A, const struct FVector& B);
	static struct FVector Divide_VectorFloat(const struct FVector& A, float B);
	static struct FVector Multiply_VectorVector(const struct FVector& A, const struct FVector& B);
	static struct FVector Multiply_FloatVector(float A, const struct FVector& B);
	static struct FVector Multiply_VectorFloat(const struct FVector& A, float B);
	static struct FVector Subtract_PreVector(const struct FVector& A);
	static float FInterpConstantTo(float Current, float Target, float DeltaTime, float InterpSpeed);
	static float FInterpTo(float Current, float Target, float DeltaTime, float InterpSpeed);
	static float FPctByRange(float Value, float InMin, float InMax);
	static float RandSign(float optionalValue = {});
	static struct FVector CalculateGravityPosition(const struct FVector& Location, const struct FVector& Velocity, float Gravity, float Time, const struct FVector& optionalGravityDirection);
	static float RandRange(float InMin, float InMax);
	static float FInterpEaseInOut(float A, float B, float Alpha, float Exp);
	static float FInterpEaseOut(float A, float B, float Alpha, float Exp);
	static float FInterpEaseIn(float A, float B, float Alpha, float Exp);
	static float FCubicInterp(float P0, float T0, float P1, float T1, float A);
	static int32_t FloorLog2(int32_t Value);
	static int32_t FCeil(float A);
	static int32_t FFloor(float A);
	static int32_t Round(float A);
	static float Lerp(float A, float B, float Alpha);
	static float FClamp(float V, float A, float B);
	static float FMax(float A, float B);
	static float FMin(float A, float B);
	static float FRand();
	static float Square(float A);
	static float Sqrt(float A);
	static float Loge(float A);
	static float Exp(float A);
	static float Atan2(float A, float B);
	static float Atan(float A);
	static float Tan(float A);
	static float Acos(float A);
	static float Cos(float A);
	static float Asin(float A);
	static float Sin(float A);
	static float Abs(float A);
	static float SubtractEqual_FloatFloat(float B, float& outA);
	static float AddEqual_FloatFloat(float B, float& outA);
	static float DivideEqual_FloatFloat(float B, float& outA);
	static float MultiplyEqual_FloatFloat(float B, float& outA);
	static bool NotEqual_FloatFloat(float A, float B);
	static bool ComplementEqual_FloatFloat(float A, float B);
	static bool EqualEqual_FloatFloat(float A, float B);
	static bool GreaterEqual_FloatFloat(float A, float B);
	static bool LessEqual_FloatFloat(float A, float B);
	static bool Greater_FloatFloat(float A, float B);
	static bool Less_FloatFloat(float A, float B);
	static float Subtract_FloatFloat(float A, float B);
	static float Add_FloatFloat(float A, float B);
	static float Percent_FloatFloat(float A, float B);
	static float Divide_FloatFloat(float A, float B);
	static float Multiply_FloatFloat(float A, float B);
	static float MultiplyMultiply_FloatFloat(float Base, float Exp);
	static float Subtract_PreFloat(float A);
	static class FString ToHex(int32_t A);
	static int32_t Clamp(int32_t V, int32_t A, int32_t B);
	static int32_t Max(int32_t A, int32_t B);
	static int32_t Min(int32_t A, int32_t B);
	static int32_t Rand(int32_t Max);
	static struct FColor FromHexColor(const class FString& Hex);
	static int32_t FromHex(const class FString& Hex);
	static void SQWordMin();
	static void SQWordMax();
	static void SubtractEqual_SQWordSQWord();
	static void AddEqual_SQWordSQWord();
	static bool NotEqual_SQWordSQWord();
	static bool EqualEqual_SQWordSQWord();
	static bool GreaterEqual_SQWordSQWord();
	static bool LessEqual_SQWordSQWord();
	static bool Greater_SQWordSQWord();
	static bool Less_SQWordSQWord();
	static void Subtract_SQWordSQWord();
	static void Add_SQWordSQWord();
	static void Divide_SQWordSQWord();
	static void Multiply_SQWordSQWord();
	static uint64_t QMin(uint64_t A, uint64_t B);
	static uint64_t QMax(uint64_t A, uint64_t B);
	static uint64_t QSubtractNoUnderflow(uint64_t A, uint64_t B);
	static bool NotEqual_QWordInt(uint64_t A, int32_t B);
	static bool EqualEqual_QWordInt(uint64_t A, int32_t B);
	static uint64_t SubtractEqual_QWordQWord(uint64_t B, uint64_t& outA);
	static uint64_t AddEqual_QWordQWord(uint64_t B, uint64_t& outA);
	static bool NotEqual_QWordQWord(uint64_t A, uint64_t B);
	static bool EqualEqual_QWordQWord(uint64_t A, uint64_t B);
	static bool GreaterEqual_QWordQWord(uint64_t A, uint64_t B);
	static bool LessEqual_QWordQWord(uint64_t A, uint64_t B);
	static bool Greater_QWordQWord(uint64_t A, uint64_t B);
	static bool Less_QWordQWord(uint64_t A, uint64_t B);
	static int32_t Subtract_QWordQWord(uint64_t A, uint64_t B);
	static uint64_t Add_QWordQWord(uint64_t A, uint64_t B);
	static uint64_t Divide_QWordQWord(uint64_t A, uint64_t B);
	static uint64_t Multiply_QWordQWord(uint64_t A, uint64_t B);
	static int32_t SubtractSubtract_Int(int32_t& outA);
	static int32_t AddAdd_Int(int32_t& outA);
	static int32_t SubtractSubtract_PreInt(int32_t& outA);
	static int32_t AddAdd_PreInt(int32_t& outA);
	static int32_t SubtractEqual_IntInt(int32_t B, int32_t& outA);
	static int32_t AddEqual_IntInt(int32_t B, int32_t& outA);
	static int32_t DivideEqual_IntFloat(float B, int32_t& outA);
	static int32_t MultiplyEqual_IntFloat(float B, int32_t& outA);
	static int32_t Or_IntInt(int32_t A, int32_t B);
	static int32_t Xor_IntInt(int32_t A, int32_t B);
	static int32_t And_IntInt(int32_t A, int32_t B);
	static bool NotEqual_IntInt(int32_t A, int32_t B);
	static bool EqualEqual_IntInt(int32_t A, int32_t B);
	static bool GreaterEqual_IntInt(int32_t A, int32_t B);
	static bool LessEqual_IntInt(int32_t A, int32_t B);
	static bool Greater_IntInt(int32_t A, int32_t B);
	static bool Less_IntInt(int32_t A, int32_t B);
	static int32_t GreaterGreaterGreater_IntInt(int32_t A, int32_t B);
	static int32_t GreaterGreater_IntInt(int32_t A, int32_t B);
	static int32_t LessLess_IntInt(int32_t A, int32_t B);
	static int32_t Subtract_IntInt(int32_t A, int32_t B);
	static int32_t Add_IntInt(int32_t A, int32_t B);
	static int32_t Percent_IntInt(int32_t A, int32_t B);
	static int32_t Divide_IntInt(int32_t A, int32_t B);
	static int32_t Multiply_IntInt(int32_t A, int32_t B);
	static int32_t Subtract_PreInt(int32_t A);
	static int32_t Complement_PreInt(int32_t A);
	static uint8_t SubtractSubtract_Byte(uint8_t& outA);
	static uint8_t AddAdd_Byte(uint8_t& outA);
	static uint8_t SubtractSubtract_PreByte(uint8_t& outA);
	static uint8_t AddAdd_PreByte(uint8_t& outA);
	static uint8_t SubtractEqual_ByteByte(uint8_t B, uint8_t& outA);
	static uint8_t AddEqual_ByteByte(uint8_t B, uint8_t& outA);
	static uint8_t DivideEqual_ByteByte(uint8_t B, uint8_t& outA);
	static uint8_t MultiplyEqual_ByteFloat(float B, uint8_t& outA);
	static uint8_t MultiplyEqual_ByteByte(uint8_t B, uint8_t& outA);
	static bool OrOr_BoolBool(bool A, bool B);
	static bool XorXor_BoolBool(bool A, bool B);
	static bool AndAnd_BoolBool(bool A, bool B);
	static bool NotEqual_BoolBool(bool A, bool B);
	static bool EqualEqual_BoolBool(bool A, bool B);
	static bool Not_PreBool(bool A);
	void CallFunction(struct FFrame& Stack, RESULT_DECL, class UFunction* function);
	void ProcessEvent(class UFunction* uFunction, void* uParams, void* uResult = {});
};

// Class Core.Config_ORS
// 0x0060 (0x0060 - 0x00C0)
class UConfig_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0x60];                            // 0x0060 (0x0060) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Config_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.ClassTupleCollection_ORS
// 0x0060 (0x0060 - 0x00C0)
class UClassTupleCollection_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0x60];                            // 0x0060 (0x0060) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ClassTupleCollection_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.ClassTuple_ORS
// 0x0068 (0x0060 - 0x00C8)
class UClassTuple_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0x68];                            // 0x0060 (0x0068) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ClassTuple_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.SubscriptionCollection_ORS
// 0x0020 (0x0060 - 0x0080)
class USubscriptionCollection_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0x20];                            // 0x0060 (0x0020) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.SubscriptionCollection_ORS");
		}

		return uClassPointer;
	};

};

// Class Engine.ScriptGroup_ORS
// 0x0008 (0x0060 - 0x0068)
class UScriptGroup_ORS : public UObject
{
public:
	class UObject*                                     GroupOwner;                                    // 0x0060 (0x0008) [0x0000000000000002] (CPF_Const)   

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Engine.ScriptGroup_ORS");
		}

		return uClassPointer;
	};

	void ClearTimerClass(class UClass* EventClass);
	void ClearTimer(class UObject* Event);
	void SetGameTimer(class UObject* Event, float Delay, const struct FTimerOptions& optionalOptions);
	void SetTimer(class UObject* Event, float Delay, const struct FTimerOptions& optionalOptions);
	void Broadcast(class UObject* Event);
	void CreateObjects(class UObject* optionalObjOuter, class TArray<class UClass*>& outObjectClasses);
	class UObject* CreateObject(class UClass* ObjectClass, class UObject* optionalObjOuter = {});
	class UObject* GetOrCreateObject(class UClass* ObjectClass, class UObject* optionalObjOuter = {});
	class UObject* GetObjectW(class UClass* ObjectClass);
	template<typename C>
	typename C* GetObjectW()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)GetObjectW(staticClass);
		}

		return nullptr;
	}

	class UObject* DestroyClass(class UClass* ObjectClass);
	template<typename C>
	typename C* DestroyClass()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)DestroyClass(staticClass);
		}

		return nullptr;
	}

	void RemoveAllClasses(class UClass* ObjectClass);
	class UObject* RemoveClass(class UClass* ObjectClass);
	template<typename C>
	typename C* RemoveClass()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)RemoveClass(staticClass);
		}

		return nullptr;
	}

	void DestroyObject(class UObject* Object);
	void RemoveObject(class UObject* Object);
	void AddObject(class UObject* Object);
	void SetGroupParent(class UObject* optionalParentGroup = {});
};

// Class Core.Group_ORS
// 0x00D0 (0x0068 - 0x0138)
class UGroup_ORS : public UScriptGroup_ORS
{
public:
	uint8_t                                            UnknownData00[0xD0];                            // 0x0068 (0x00D0) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Group_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.Instance_ORS
// 0x00B0 (0x0060 - 0x0110)
class UInstance_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0xB0];                            // 0x0060 (0x00B0) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Instance_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.Global_ORS
// 0x0018 (0x0060 - 0x0078)
class UGlobal_ORS : public UObject
{
public:
	uint8_t                                            UnknownData00[0x18];                            // 0x0060 (0x0018) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Global_ORS");
		}

		return uClassPointer;
	};

};

// Class Core.UTF8
// 0x0000 (0x0060 - 0x0060)
class UUTF8 : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.UTF8");
		}

		return uClassPointer;
	};

	static void DecodeInline(class TArray<uint8_t>& outInput, class FString& outOutput);
	static class FString Decode(class TArray<uint8_t>& outInput);
	static void EncodeInline(const class FString& Input, class TArray<uint8_t>& outOutput);
	static class TArray<uint8_t> Encode(const class FString& Input);
};

// Class Core.TextBuffer
// 0x0030 (0x0060 - 0x0090)
class UTextBuffer : public UObject
{
public:
	uint8_t                                            UnknownData00[0x30];                            // 0x0060 (0x0030) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.TextBuffer");
		}

		return uClassPointer;
	};

};

// Class Core.Subsystem
// 0x0008 (0x0060 - 0x0068)
class USubsystem : public UObject
{
public:
	struct FPointer                                    VfTable_FExec;                                 // 0x0060 (0x0008) [0x0000000000801002] (CPF_Const | CPF_Native | CPF_NoExport)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Subsystem");
		}

		return uClassPointer;
	};

};

// Class Core.System
// 0x00F8 (0x0068 - 0x0160)
class USystem : public USubsystem
{
public:
	int32_t                                            StaleCacheDays;                                // 0x0068 (0x0004) [0x0000000000004000] (CPF_Config)  
	int32_t                                            MaxStaleCacheSize;                             // 0x006C (0x0004) [0x0000000000004000] (CPF_Config)  
	int32_t                                            MaxOverallCacheSize;                           // 0x0070 (0x0004) [0x0000000000004000] (CPF_Config)  
	int32_t                                            PackageSizeSoftLimit;                          // 0x0074 (0x0004) [0x0000000000004000] (CPF_Config)  
	float                                              AsyncIOBandwidthLimit;                         // 0x0078 (0x0004) [0x0000000000004000] (CPF_Config)  
	class FString                                      SavePath;                                      // 0x0080 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class FString                                      CachePath;                                     // 0x0090 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class FString                                      CacheExt;                                      // 0x00A0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        Paths;                                         // 0x00B0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        SeekFreePCPaths;                               // 0x00C0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        ScriptPaths;                                   // 0x00D0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        FRScriptPaths;                                 // 0x00E0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        CutdownPaths;                                  // 0x00F0 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FName>                          Suppress;                                      // 0x0100 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FName>                          SuppressPublic;                                // 0x0110 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        Extensions;                                    // 0x0120 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        SeekFreePCExtensions;                          // 0x0130 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class TArray<class FString>                        LocalizationPaths;                             // 0x0140 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)
	class FString                                      TextureFileCacheExtension;                     // 0x0150 (0x0010) [0x0000000000404000] (CPF_Config | CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.System");
		}

		return uClassPointer;
	};

};

// Class Core.Subscription
// 0x0018 (0x0060 - 0x0078)
class USubscription : public UObject
{
public:
	struct FScriptDelegate                             __SubscriberCallback__Delegate;                // 0x0060 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Subscription");
		}

		return uClassPointer;
	};

	static void __Subscription__TriggerAll_0x1(class USubscription* S);
	static class USubscription* GetNone();
	static void TriggerAll(class TArray<class USubscription*>& outSubscriptions);
	static class USubscription* Create(const struct FScriptDelegate& InCallback);
	void eventDispose();
	void TriggerCallback();
	void SetCallback(const struct FScriptDelegate& InCallback);
	void SubscriberCallback();
};

// Class Core.PropertyChangeDispatcher
// 0x0010 (0x0060 - 0x0070)
class UPropertyChangeDispatcher : public UObject
{
public:
	uint8_t                                            UnknownData00[0x10];                            // 0x0060 (0x0010) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.PropertyChangeDispatcher");
		}

		return uClassPointer;
	};

};

// Class Core.PackageMap
// 0x00B8 (0x0060 - 0x0118)
class UPackageMap : public UObject
{
public:
	uint8_t                                            UnknownData00[0xB8];                            // 0x0060 (0x00B8) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.PackageMap");
		}

		return uClassPointer;
	};

};

// Class Core.ObjectUtil
// 0x0000 (0x0060 - 0x0060)
class UObjectUtil : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ObjectUtil");
		}

		return uClassPointer;
	};

	static class UClass* FindClass(const class FName& ClassName);
	static void ClearNaNValues(class UObject* InObject);
	static bool IdenticalDeep(class UObject* Left, class UObject* Right);
	static bool Identical(class UObject* Left, class UObject* Right);
	static void InitProperties(class UObject* InObject);
	static void AllCDOs(class UClass* BaseClass, bool optionalBIncludeAbstract, class UObject*& outOutCDO);
	static class UObject* GetCDO(class UClass* InClass);
};

// Class Core.ObjectSerializer
// 0x0010 (0x0060 - 0x0070)
class UObjectSerializer : public UObject
{
public:
	uint8_t                                            UnknownData00[0x10];                            // 0x0060 (0x0010) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ObjectSerializer");
		}

		return uClassPointer;
	};

};

// Class Core.ObjectRedirector
// 0x0008 (0x0060 - 0x0068)
class UObjectRedirector : public UObject
{
public:
	uint8_t                                            UnknownData00[0x8];                              // 0x0060 (0x0008) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ObjectRedirector");
		}

		return uClassPointer;
	};

};

// Class Core.MetaData
// 0x0050 (0x0060 - 0x00B0)
class UMetaData : public UObject
{
public:
	uint8_t                                            UnknownData00[0x50];                            // 0x0060 (0x0050) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.MetaData");
		}

		return uClassPointer;
	};

};

// Class Core.Linker
// 0x0190 (0x0060 - 0x01F0)
class ULinker : public UObject
{
public:
	uint8_t                                            UnknownData00[0x190];                          // 0x0060 (0x0190) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Linker");
		}

		return uClassPointer;
	};

};

// Class Core.LinkerSave
// 0x00C0 (0x01F0 - 0x02B0)
class ULinkerSave : public ULinker
{
public:
	uint8_t                                            UnknownData00[0xC0];                            // 0x01F0 (0x00C0) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.LinkerSave");
		}

		return uClassPointer;
	};

};

// Class Core.LinkerLoad
// 0x0628 (0x01F0 - 0x0818)
class ULinkerLoad : public ULinker
{
public:
	uint8_t                                            UnknownData00[0x628];                          // 0x01F0 (0x0628) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.LinkerLoad");
		}

		return uClassPointer;
	};

};

// Class Core.Interface
// 0x0000 (0x0060 - 0x0060)
class UInterface : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Interface");
		}

		return uClassPointer;
	};

};

// Class Core.FileSystem
// 0x0000 (0x0060 - 0x0060)
class UFileSystem : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.FileSystem");
		}

		return uClassPointer;
	};

	static bool IsCookedBuild();
	static void CloseLogFile();
	static class FString GetLogFileName();
	static bool DeleteDirectoryTree(const class FString& Path);
	static bool DeleteFileW(const class FString& Path);
	static bool AppendStringToFile(const class FString& Path, const class FString& Text);
	static bool SaveStringToFile(const class FString& Path, const class FString& Text);
	static bool SaveBytesToFile(const class FString& Path, class TArray<uint8_t>& outBytes);
	static bool LoadFileToBytes(const class FString& Path, int32_t optionalStartOffset, int32_t optionalLength, class TArray<uint8_t>& outOutBytes);
	static bool LoadFileToString(const class FString& Path, class FString& outOutText);
	static int32_t GetFileSize(const class FString& Path);
	static class FString GetFileExtensionWithoutDot(const class FString& Path);
	static class FString GetFileExtension(const class FString& Path);
	static class FString GetFilePathWithoutExtension(const class FString& Path);
	static class FString GetFileNameWithoutExtension(const class FString& Path);
	static class FString GetFilename(const class FString& Path);
	static void FindFiles(const class FString& Path, class TArray<class FString>& outOutFilenames);
};

// Class Core.Field
// 0x0010 (0x0060 - 0x0070)
class UField : public UObject
{
public:
	class UField* Next; // 0x0060 (0x0008)
	uint64_t UniqueFeatureValue; // 0x0068 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Field");
		}

		return uClassPointer;
	};

};

// Class Core.Struct
// 0x00C0 (0x0070 - 0x0130)
class UStruct : public UField
{
public:
	uint8_t UnknownData00[0x10];// 0x0070 (0x0010) DYNAMIC FIELD PADDING
	class UField* SuperField; // 0x0080 (0x0008)
	class UField* Children; // 0x0088 (0x0008)
	int32_t PropertySize; // 0x0090 (0x0004)
	uint8_t UnknownData01[0x18];// 0x0094 (0x0018) DYNAMIC FIELD PADDING
	int32_t MinAlignment; // 0x00AC (0x0004)
	uint8_t UnknownData02[0x80];// 0x00B0 (0x0080) DYNAMIC FIELD PADDING

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Struct");
		}

		return uClassPointer;
	};

};

// Class Core.ScriptStruct
// 0x0028 (0x0130 - 0x0158)
class UScriptStruct : public UStruct
{
public:
	uint8_t                                            UnknownData00[0x28];                            // 0x0130 (0x0028) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ScriptStruct");
		}

		return uClassPointer;
	};

};

// Class Core.Enum
// 0x0010 (0x0070 - 0x0080)
class UEnum : public UField
{
public:
	class TArray<class FName> Names; // 0x0070 (0x0010)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Enum");
		}

		return uClassPointer;
	};

};

// Class Core.Function
// 0x0030 (0x0130 - 0x0160)
class UFunction : public UStruct
{
public:
	uint64_t FunctionFlags; // 0x0130 (0x0008)
	uint16_t iNative; // 0x0138 (0x0002)
	uint16_t RepOffset; // 0x013A (0x0002)
	class FName FriendlyName; // 0x013C (0x0008)
	uint8_t OperPrecedence; // 0x0144 (0x0001)
	uint8_t NumParms; // 0x0145 (0x0001)
	uint16_t ParmsSize; // 0x0146 (0x0002)
	uint16_t ReturnValueOffset; // 0x0148 (0x0004)
	uint8_t UnknownData00[0xC];// 0x014C (0x000C) DYNAMIC FIELD PADDING
	FPointer Func; // 0x0158 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Function");
		}

		return uClassPointer;
	};

	static UFunction* FindFunction(const std::string& functionFullName);
};

// Class Core.Property
// 0x0058 (0x0070 - 0x00C8)
class UProperty : public UField
{
public:
	int32_t ArraySize; // 0x0070 (0x0004)
	int32_t PropertySize; // 0x0074 (0x0004)
	uint64_t PropertyFlags; // 0x0078 (0x0008)
	uint16_t RepOffset; // 0x0080 (0x0002)
	uint16_t RepIndex; // 0x0082 (0x0002)
	FName Category; // 0x0084 (0x0008)
	UEnum* ArraySizeEnum; // 0x0090 (0x0008)
	uint32_t Offset; // 0x0098 (0x0004)
	UProperty* PropertyLinkNext; // 0x00A0 (0x0008)
	UProperty* ConstructorLinkNext; // 0x00A8 (0x0008)
	UProperty* NextRef; // 0x00B0 (0x0008)
	FString Alias; // 0x00B8 (0x0010)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Property");
		}

		return uClassPointer;
	};

};

// Class Core.DelegateProperty
// 0x0010 (0x00C8 - 0x00D8)
class UDelegateProperty : public UProperty
{
public:
	UFunction* SuccessCallback; // 0x00C8 (0x0008)
	UFunction* FailureCallback; // 0x00D0 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.DelegateProperty");
		}

		return uClassPointer;
	};

};

// Class Core.StructProperty
// 0x0008 (0x00C8 - 0x00D0)
class UStructProperty : public UProperty
{
public:
	class UStruct* Struct; // 0x00C8 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.StructProperty");
		}

		return uClassPointer;
	};

};

// Class Core.StrProperty
// 0x0000 (0x00C8 - 0x00C8)
class UStrProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.StrProperty");
		}

		return uClassPointer;
	};

};

// Class Core.SQWordProperty
// 0x0000 (0x00C8 - 0x00C8)
class USQWordProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.SQWordProperty");
		}

		return uClassPointer;
	};

};

// Class Core.QWordProperty
// 0x0000 (0x00C8 - 0x00C8)
class UQWordProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.QWordProperty");
		}

		return uClassPointer;
	};

};

// Class Core.ObjectProperty
// 0x0010 (0x00C8 - 0x00D8)
class UObjectProperty : public UProperty
{
public:
	class UClass* PropertyClass; // 0x00C8 (0x0008)
	uint8_t UnknownData00[0x8];// 0x00D0 (0x0008) DYNAMIC FIELD PADDING

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ObjectProperty");
		}

		return uClassPointer;
	};

};

// Class Core.ComponentProperty
// 0x0000 (0x00D8 - 0x00D8)
class UComponentProperty : public UObjectProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ComponentProperty");
		}

		return uClassPointer;
	};

};

// Class Core.ClassProperty
// 0x0008 (0x00D8 - 0x00E0)
class UClassProperty : public UObjectProperty
{
public:
	class UClass* MetaClass; // 0x00D8 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ClassProperty");
		}

		return uClassPointer;
	};

};

// Class Core.NameProperty
// 0x0000 (0x00C8 - 0x00C8)
class UNameProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.NameProperty");
		}

		return uClassPointer;
	};

};

// Class Core.MapProperty
// 0x0010 (0x00C8 - 0x00D8)
class UMapProperty : public UProperty
{
public:
	class UProperty* Key; // 0x00C8 (0x0008)
	class UProperty* Value; // 0x00D0 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.MapProperty");
		}

		return uClassPointer;
	};

};

// Class Core.IntProperty
// 0x0000 (0x00C8 - 0x00C8)
class UIntProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.IntProperty");
		}

		return uClassPointer;
	};

};

// Class Core.InterfaceProperty
// 0x0010 (0x00C8 - 0x00D8)
class UInterfaceProperty : public UProperty
{
public:
	class UClass* InterfaceClass; // 0x00C8 (0x0008)
	uint8_t UnknownData00[0x8];// 0x00D0 (0x0008) DYNAMIC FIELD PADDING

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.InterfaceProperty");
		}

		return uClassPointer;
	};

};

// Class Core.FloatProperty
// 0x0000 (0x00C8 - 0x00C8)
class UFloatProperty : public UProperty
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.FloatProperty");
		}

		return uClassPointer;
	};

};

// Class Core.ByteProperty
// 0x0008 (0x00C8 - 0x00D0)
class UByteProperty : public UProperty
{
public:
	class UEnum* Enum; // 0x00C8 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ByteProperty");
		}

		return uClassPointer;
	};

};

// Class Core.BoolProperty
// 0x0008 (0x00C8 - 0x00D0)
class UBoolProperty : public UProperty
{
public:
	uint32_t BitMask; // 0x00C8 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.BoolProperty");
		}

		return uClassPointer;
	};

};

// Class Core.ArrayProperty
// 0x0008 (0x00C8 - 0x00D0)
class UArrayProperty : public UProperty
{
public:
	class UProperty* Inner; // 0x00C8 (0x0008)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ArrayProperty");
		}

		return uClassPointer;
	};

};

// Class Core.Const
// 0x0010 (0x0070 - 0x0080)
class UConst : public UField
{
public:
	class FString Value; // 0x0070 (0x0010)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Const");
		}

		return uClassPointer;
	};

};

// Class Core.FeatureSystem
// 0x0020 (0x0060 - 0x0080)
class UFeatureSystem : public UObject
{
public:
	uint8_t                                            UnknownData00[0x8];                              // 0x0060 (0x0008) MISSED OFFSET
	uint32_t                                           AlwaysEnabledFeature : 1;                      // 0x0068 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           AlwaysDisabledFeature : 1;                     // 0x0068 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint32_t                                           Prime : 1;                                     // 0x0068 (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           Matchmaking : 1;                               // 0x0068 (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           PrivateMatch : 1;                              // 0x0068 (0x0004) [0x0000000040000000] [0x00000040] (CPF_DataBinding)
	uint32_t                                           SplitscreenMatch : 1;                          // 0x0068 (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           SplitscreenJoin : 1;                           // 0x0068 (0x0004) [0x0000000040000000] [0x00000100] (CPF_DataBinding)
	uint32_t                                           SeasonMode : 1;                                // 0x0068 (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           Tutorial : 1;                                  // 0x0068 (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           Garage : 1;                                    // 0x0068 (0x0004) [0x0000000040000000] [0x00000800] (CPF_DataBinding)
	uint32_t                                           Options : 1;                                   // 0x0068 (0x0004) [0x0000000040000000] [0x00001000] (CPF_DataBinding)
	uint32_t                                           ReplaySaves : 1;                               // 0x0068 (0x0004) [0x0000000040000000] [0x00002000] (CPF_DataBinding)
	uint32_t                                           MainMenu : 1;                                  // 0x0068 (0x0004) [0x0000000040000000] [0x00004000] (CPF_DataBinding)
	uint32_t                                           MidgameMenu : 1;                               // 0x0068 (0x0004) [0x0000000040000000] [0x00008000] (CPF_DataBinding)
	uint32_t                                           Party : 1;                                     // 0x0068 (0x0004) [0x0000000040000000] [0x00010000] (CPF_DataBinding)
	uint32_t                                           PsyNetParty : 1;                               // 0x0068 (0x0004) [0x0000000040000000] [0x00020000] (CPF_DataBinding)
	uint32_t                                           Achievements : 1;                              // 0x0068 (0x0004) [0x0000000040000000] [0x00040000] (CPF_DataBinding)
	uint32_t                                           Stats : 1;                                     // 0x0068 (0x0004) [0x0000000040000000] [0x00080000] (CPF_DataBinding)
	uint32_t                                           Leaderboards : 1;                              // 0x0068 (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           XP : 1;                                        // 0x0068 (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           Chat : 1;                                      // 0x0068 (0x0004) [0x0000000040000000] [0x00400000] (CPF_DataBinding)
	uint32_t                                           TrainingDifficulties : 1;                      // 0x0068 (0x0004) [0x0000000040000000] [0x00800000] (CPF_DataBinding)
	uint32_t                                           Spectator : 1;                                 // 0x0068 (0x0004) [0x0000000040000000] [0x01000000] (CPF_DataBinding)
	uint32_t                                           CrossPlatformPrivateMatch : 1;                 // 0x0068 (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           Lan : 1;                                       // 0x0068 (0x0004) [0x0000000040000000] [0x04000000] (CPF_DataBinding)
	uint32_t                                           PlayerReporting : 1;                           // 0x0068 (0x0004) [0x0000000040000000] [0x08000000] (CPF_DataBinding)
	uint32_t                                           OnlineServices : 1;                            // 0x006C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           RemoveCrossPlatformProducts : 1;               // 0x006C (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           ProductValidation : 1;                         // 0x006C (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint32_t                                           MapPrefs : 1;                                  // 0x006C (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           PreMatchLobby : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           Challenges : 1;                                // 0x006C (0x0004) [0x0000000040000000] [0x00000040] (CPF_DataBinding)
	uint32_t                                           AntiAddiction : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           TrainingEditor : 1;                            // 0x006C (0x0004) [0x0000000040000000] [0x00000100] (CPF_DataBinding)
	uint32_t                                           VoiceChat : 1;                                 // 0x006C (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           SplitScreen : 1;                               // 0x006C (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           Clubs : 1;                                     // 0x006C (0x0004) [0x0000000040000000] [0x00000800] (CPF_DataBinding)
	uint32_t                                           FilterContent : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x00001000] (CPF_DataBinding)
	uint32_t                                           EncryptContent : 1;                            // 0x006C (0x0004) [0x0000000040000000] [0x00002000] (CPF_DataBinding)
	uint32_t                                           EsportsCamera : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x00010000] (CPF_DataBinding)
	uint32_t                                           OnlineXP : 1;                                  // 0x006C (0x0004) [0x0000000040000000] [0x00020000] (CPF_DataBinding)
	uint32_t                                           ClanforgeReservation : 1;                      // 0x006C (0x0004) [0x0000000040000000] [0x00080000] (CPF_DataBinding)
	uint32_t                                           UserSettingObserver : 1;                       // 0x006C (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           Metrics : 1;                                   // 0x006C (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           EOSMetrics : 1;                                // 0x006C (0x0004) [0x0000000040000000] [0x00400000] (CPF_DataBinding)
	uint32_t                                           MusicPlaylistSelection : 1;                    // 0x006C (0x0004) [0x0000000040000000] [0x00800000] (CPF_DataBinding)
	uint32_t                                           SpecialEvents : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x01000000] (CPF_DataBinding)
	uint32_t                                           PlayerBannerCustomization : 1;                 // 0x006C (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           SecureUDP : 1;                                 // 0x006C (0x0004) [0x0000000040000000] [0x04000000] (CPF_DataBinding)
	uint32_t                                           PsyNet : 1;                                    // 0x006C (0x0004) [0x0000000040000000] [0x08000000] (CPF_DataBinding)
	uint32_t                                           OnlinePlayerStorage : 1;                       // 0x006C (0x0004) [0x0000000040000000] [0x10000000] (CPF_DataBinding)
	uint32_t                                           LocalSaveData : 1;                             // 0x006C (0x0004) [0x0000000040000000] [0x20000000] (CPF_DataBinding)
	uint32_t                                           CrowdV2 : 1;                                   // 0x006C (0x0004) [0x0000000040000000] [0x40000000] (CPF_DataBinding)
	uint32_t                                           ChatBan : 1;                                   // 0x006C (0x0004) [0x0000000040000000] [0x80000000] (CPF_DataBinding)
	uint32_t                                           BacktraceCrashDumps : 1;                       // 0x0070 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           SpotifyButton : 1;                             // 0x0070 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           SeasonRewards : 1;                             // 0x0070 (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint32_t                                           FaceIt : 1;                                    // 0x0070 (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           OnlinePlayerTitles : 1;                        // 0x0070 (0x0004) [0x0000000040000000] [0x00000010] (CPF_DataBinding)
	uint32_t                                           RestrictByRegion : 1;                          // 0x0070 (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           FirstTimeExperience : 1;                       // 0x0070 (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           RLBot : 1;                                     // 0x0070 (0x0004) [0x0000000040000000] [0x00000100] (CPF_DataBinding)
	uint32_t                                           UserBugReport : 1;                             // 0x0070 (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           SteamInput : 1;                                // 0x0070 (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           ReplayFXControls : 1;                          // 0x0070 (0x0004) [0x0000000040000000] [0x00008000] (CPF_DataBinding)
	uint32_t                                           ESportsShop : 1;                               // 0x0070 (0x0004) [0x0000000040000000] [0x00010000] (CPF_DataBinding)
	uint32_t                                           MatchHistory : 1;                              // 0x0070 (0x0004) [0x0000000040000000] [0x00020000] (CPF_DataBinding)
	uint32_t                                           DynamicRangeAudioSettings : 1;                 // 0x0070 (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           QuickPlay : 1;                                 // 0x0070 (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           NewsPanelV2 : 1;                               // 0x0070 (0x0004) [0x0000000040000000] [0x00400000] (CPF_DataBinding)
	uint32_t                                           Blueprints : 1;                                // 0x0070 (0x0004) [0x0000000040000000] [0x00800000] (CPF_DataBinding)
	uint32_t                                           RocketBucks : 1;                               // 0x0070 (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           Tritip : 1;                                    // 0x0070 (0x0004) [0x0000000040000000] [0x08000000] (CPF_DataBinding)
	uint32_t                                           DiscordRichPresence : 1;                       // 0x0070 (0x0004) [0x0000000040000000] [0x20000000] (CPF_DataBinding)
	uint32_t                                           SupportACreator : 1;                           // 0x0070 (0x0004) [0x0000000040000000] [0x40000000] (CPF_DataBinding)
	uint32_t                                           CinematicIntro : 1;                            // 0x0070 (0x0004) [0x0000000040000000] [0x80000000] (CPF_DataBinding)
	uint32_t                                           TinyCrowd : 1;                                 // 0x0074 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           CrumbTrail : 1;                                // 0x0074 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           XPGatedPlaylists : 1;                          // 0x0074 (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           Football : 1;                                  // 0x0074 (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           RumbleSelection : 1;                           // 0x0074 (0x0004) [0x0000000040000000] [0x00000040] (CPF_DataBinding)
	uint32_t                                           UndersizedParty : 1;                           // 0x0074 (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           StreamerSafeAudio : 1;                         // 0x0074 (0x0004) [0x0000000040000000] [0x00000100] (CPF_DataBinding)
	uint32_t                                           FreeplayCommands : 1;                          // 0x0074 (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           Rumble_BM : 1;                                 // 0x0074 (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           PlayerReportingV2 : 1;                         // 0x0074 (0x0004) [0x0000000040000000] [0x00000800] (CPF_DataBinding)
	uint32_t                                           EOSVoice : 1;                                  // 0x0074 (0x0004) [0x0000000040000000] [0x00002000] (CPF_DataBinding)
	uint32_t                                           QuickPostMatchRequeue : 1;                     // 0x0074 (0x0004) [0x0000000040000000] [0x00004000] (CPF_DataBinding)
	uint32_t                                           HonorDuel : 1;                                 // 0x0074 (0x0004) [0x0000000040000000] [0x00010000] (CPF_DataBinding)
	uint32_t                                           TrainingNavigation : 1;                        // 0x0074 (0x0004) [0x0000000040000000] [0x00020000] (CPF_DataBinding)
	uint32_t                                           TrainingManipulation : 1;                      // 0x0074 (0x0004) [0x0000000040000000] [0x00040000] (CPF_DataBinding)
	uint32_t                                           FilterByColor : 1;                             // 0x0074 (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           Scoreboard : 1;                                // 0x0074 (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           DynamicMapEvents : 1;                          // 0x0074 (0x0004) [0x0000000040000000] [0x00400000] (CPF_DataBinding)
	uint32_t                                           NameplateBoost : 1;                            // 0x0074 (0x0004) [0x0000000040000000] [0x01000000] (CPF_DataBinding)
	uint32_t                                           DynamicLogos : 1;                              // 0x0074 (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           PlayMenuV4 : 1;                                // 0x0074 (0x0004) [0x0000000040000000] [0x04000000] (CPF_DataBinding)
	uint32_t                                           QuickChatTimeStamp : 1;                        // 0x0074 (0x0004) [0x0000000040000000] [0x08000000] (CPF_DataBinding)
	uint32_t                                           SoccarPong : 1;                                // 0x0074 (0x0004) [0x0000000040000000] [0x10000000] (CPF_DataBinding)
	uint32_t                                           OnlineFreeplay : 1;                            // 0x0074 (0x0004) [0x0000000040000000] [0x20000000] (CPF_DataBinding)
	uint32_t                                           MatchmakingSubRegion : 1;                      // 0x0074 (0x0004) [0x0000000040000000] [0x80000000] (CPF_DataBinding)
	uint32_t                                           CrossbarSFX : 1;                               // 0x0078 (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           RugbyIteration : 1;                            // 0x0078 (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           ChallengesV2 : 1;                              // 0x0078 (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           PossessionExpanded : 1;                        // 0x0078 (0x0004) [0x0000000040000000] [0x00000010] (CPF_DataBinding)
	uint32_t                                           TargetFind : 1;                                // 0x0078 (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           KeepUp : 1;                                    // 0x0078 (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           RocketPassUpgrades : 1;                        // 0x0078 (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           PentathlonTournaments : 1;                     // 0x0078 (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           DemolishUpdates : 1;                           // 0x0078 (0x0004) [0x0000000040000000] [0x00000800] (CPF_DataBinding)
	uint32_t                                           ViralItem : 1;                                 // 0x0078 (0x0004) [0x0000000040000000] [0x00001000] (CPF_DataBinding)
	uint32_t                                           ThankYouMessage : 1;                           // 0x0078 (0x0004) [0x0000000040000000] [0x00002000] (CPF_DataBinding)
	uint32_t                                           AttackerDemoFX : 1;                            // 0x0078 (0x0004) [0x0000000040000000] [0x00004000] (CPF_DataBinding)
	uint32_t                                           NewDriverChallengesV2 : 1;                     // 0x0078 (0x0004) [0x0000000040000000] [0x00008000] (CPF_DataBinding)
	uint32_t                                           TextModeration : 1;                            // 0x0078 (0x0004) [0x0000000040000000] [0x00040000] (CPF_DataBinding)
	uint32_t                                           FilterToggle : 1;                              // 0x0078 (0x0004) [0x0000000040000000] [0x00080000] (CPF_DataBinding)
	uint32_t                                           DdosPrevention : 1;                            // 0x0078 (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           OunceEnhancements : 1;                         // 0x0078 (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           FastFreeplay : 1;                              // 0x0078 (0x0004) [0x0000000040000000] [0x00400000] (CPF_DataBinding)
	uint32_t                                           MatchAdminMutator : 1;                         // 0x0078 (0x0004) [0x0000000040000000] [0x00800000] (CPF_DataBinding)
	uint32_t                                           Thistle : 1;                                   // 0x0078 (0x0004) [0x0000000040000000] [0x01000000] (CPF_DataBinding)
	uint32_t                                           DemoFXMutator : 1;                             // 0x0078 (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           OffProdHandling : 1;                           // 0x0078 (0x0004) [0x0000000040000000] [0x04000000] (CPF_DataBinding)
	uint32_t                                           FlipResetIndicator : 1;                        // 0x0078 (0x0004) [0x0000000040000000] [0x10000000] (CPF_DataBinding)
	uint32_t                                           NewsOverhaul : 1;                              // 0x0078 (0x0004) [0x0000000040000000] [0x20000000] (CPF_DataBinding)
	uint32_t                                           QueueMenuChanges : 1;                          // 0x0078 (0x0004) [0x0000000040000000] [0x40000000] (CPF_DataBinding)
	uint32_t                                           VisibleMMR : 1;                                // 0x0078 (0x0004) [0x0000000040000000] [0x80000000] (CPF_DataBinding)
	uint32_t                                           EasyAntiCheat : 1;                             // 0x007C (0x0004) [0x0000000040000000] [0x00000001] (CPF_DataBinding)
	uint32_t                                           OverrideBoostSound : 1;                        // 0x007C (0x0004) [0x0000000040000000] [0x00000002] (CPF_DataBinding)
	uint32_t                                           SettingsExport : 1;                            // 0x007C (0x0004) [0x0000000040000000] [0x00000004] (CPF_DataBinding)
	uint32_t                                           ImprovedSwivelCameraSettings : 1;              // 0x007C (0x0004) [0x0000000040000000] [0x00000008] (CPF_DataBinding)
	uint32_t                                           RBActorStatGraphs : 1;                         // 0x007C (0x0004) [0x0000000040000000] [0x00000020] (CPF_DataBinding)
	uint32_t                                           DemoSpawnSelection : 1;                        // 0x007C (0x0004) [0x0000000040000000] [0x00000040] (CPF_DataBinding)
	uint32_t                                           FreeplayTeamColors : 1;                        // 0x007C (0x0004) [0x0000000040000000] [0x00000080] (CPF_DataBinding)
	uint32_t                                           HitboxVisualizer : 1;                          // 0x007C (0x0004) [0x0000000040000000] [0x00000100] (CPF_DataBinding)
	uint32_t                                           StatsAPI : 1;                                  // 0x007C (0x0004) [0x0000000040000000] [0x00000200] (CPF_DataBinding)
	uint32_t                                           TrainingAdditions : 1;                         // 0x007C (0x0004) [0x0000000040000000] [0x00000400] (CPF_DataBinding)
	uint32_t                                           ScorerGoalViewToggle : 1;                      // 0x007C (0x0004) [0x0000000040000000] [0x00000800] (CPF_DataBinding)
	uint32_t                                           StreamerSafe : 1;                              // 0x007C (0x0004) [0x0000000040000000] [0x00001000] (CPF_DataBinding)
	uint32_t                                           WorldCup : 1;                                  // 0x007C (0x0004) [0x0000000040000000] [0x00002000] (CPF_DataBinding)
	uint32_t                                           BladeBall : 1;                                 // 0x007C (0x0004) [0x0000000040000000] [0x00008000] (CPF_DataBinding)
	uint32_t                                           ImprovedPresence : 1;                          // 0x007C (0x0004) [0x0000000040000000] [0x00010000] (CPF_DataBinding)
	uint32_t                                           AutoSkipGoalReplay : 1;                        // 0x007C (0x0004) [0x0000000040000000] [0x00020000] (CPF_DataBinding)
	uint32_t                                           BlackMarketTradeIn : 1;                        // 0x007C (0x0004) [0x0000000040000000] [0x00100000] (CPF_DataBinding)
	uint32_t                                           WinnersExplosion : 1;                          // 0x007C (0x0004) [0x0000000040000000] [0x00200000] (CPF_DataBinding)
	uint32_t                                           MMRRefund : 1;                                 // 0x007C (0x0004) [0x0000000040000000] [0x01000000] (CPF_DataBinding)
	uint32_t                                           CustomScoreboard : 1;                          // 0x007C (0x0004) [0x0000000040000000] [0x02000000] (CPF_DataBinding)
	uint32_t                                           StatTitles : 1;                                // 0x007C (0x0004) [0x0000000040000000] [0x04000000] (CPF_DataBinding)
	uint32_t                                           ReactiveExplosion : 1;                         // 0x007C (0x0004) [0x0000000040000000] [0x08000000] (CPF_DataBinding)
	uint32_t                                           Crosshair : 1;                                 // 0x007C (0x0004) [0x0000000040000000] [0x10000000] (CPF_DataBinding)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.FeatureSystem");
		}

		return uClassPointer;
	};

};

// Class Core.Factory
// 0x0058 (0x0060 - 0x00B8)
class UFactory : public UObject
{
public:
	class FString                                      Category;                                      // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class UClass*                                      SupportedClass;                                // 0x0070 (0x0008) [0x0000000000000000]               
	class UClass*                                      ContextClass;                                  // 0x0078 (0x0008) [0x0000000000000000]               
	class FString                                      Description;                                   // 0x0080 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        Formats;                                       // 0x0090 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint32_t                                           bCreateNew : 1;                                // 0x00A0 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           bEditAfterNew : 1;                             // 0x00A0 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           bEditorImport : 1;                             // 0x00A0 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           bText : 1;                                     // 0x00A0 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           bAssetNameMatchesPackageName : 1;              // 0x00A0 (0x0004) [0x0000000000000000] [0x00000010] 
	int32_t                                            AutoPriority;                                  // 0x00A4 (0x0004) [0x0000000000000000]               
	class TArray<class FString>                        ValidGameNames;                                // 0x00A8 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Factory");
		}

		return uClassPointer;
	};

};

// Class Core.TextBufferFactory
// 0x0000 (0x00B8 - 0x00B8)
class UTextBufferFactory : public UFactory
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.TextBufferFactory");
		}

		return uClassPointer;
	};

};

// Class Core.Exporter
// 0x0038 (0x0060 - 0x0098)
class UExporter : public UObject
{
public:
	uint8_t                                            UnknownData00[0x8];                              // 0x0060 (0x0008) MISSED OFFSET
	class TArray<class FString>                        FormatExtension;                               // 0x0068 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        FormatDescription;                             // 0x0078 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	uint8_t                                            UnknownData01[0x10];                            // 0x0088 (0x0010) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Exporter");
		}

		return uClassPointer;
	};

};

// Class Core.ErrorType
// 0x0010 (0x0060 - 0x0070)
class UErrorType : public UObject
{
public:
	class FString                                      LocalizationKey;                               // 0x0060 (0x0010) [0x0000000000400002] (CPF_Const | CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ErrorType");
		}

		return uClassPointer;
	};

	class UError* CreateError(const class FString& optionalInErrorMessage = {}, int32_t optionalInErrorCode = {});
	class FString GetLocalizedMessage();
};

// Class Core.ErrorList
// 0x0020 (0x0060 - 0x0080)
class UErrorList : public UObject
{
public:
	class FString                                      LocalizationPackage;                           // 0x0060 (0x0010) [0x0000000000400003] (CPF_Edit | CPF_Const | CPF_NeedCtorLink)
	class FString                                      LocalizationSection;                           // 0x0070 (0x0010) [0x0000000000400003] (CPF_Edit | CPF_Const | CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ErrorList");
		}

		return uClassPointer;
	};

	static class UErrorType* GetErrorType(const class FName& Error);
};

// Class Core.ArrayErrors
// 0x0010 (0x0080 - 0x0090)
class UArrayErrors : public UErrorList
{
public:
	class UErrorType*                                  Remove_NegativeNumberOfElements;               // 0x0080 (0x0008) [0x0000000000000002] (CPF_Const)   
	class UErrorType*                                  Remove_OutOfBounds;                            // 0x0088 (0x0008) [0x0000000000000002] (CPF_Const)   

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ArrayErrors");
		}

		return uClassPointer;
	};

};

// Class Core.Error
// 0x0024 (0x0060 - 0x0084)
class UError : public UObject
{
public:
	class UErrorType*                                  Type;                                          // 0x0060 (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)
	class FString                                      Message;                                       // 0x0068 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	int32_t                                            Code;                                          // 0x0078 (0x0004) [0x0000000000002002] (CPF_Const | CPF_Transient)
	class FName                                        RetryKey;                                      // 0x007C (0x0008) [0x0000000000002002] (CPF_Const | CPF_Transient)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Error");
		}

		return uClassPointer;
	};

	class FString GetDebugMessage();
	class FString GetLocalizedMessage();
};

// Class Core.DelegateTracker
// 0x0028 (0x0060 - 0x0088)
class UDelegateTracker : public UObject
{
public:
	class TArray<struct FAsyncDelegateInfo>            AsyncDelegates;                                // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __PlaceholderDelegate__Delegate;               // 0x0070 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.DelegateTracker");
		}

		return uClassPointer;
	};

	struct FScriptDelegate RemoveDelegate(int32_t CallbackId);
	int32_t AddDelegate(const struct FScriptDelegate& Callback);
	void PlaceholderDelegate();
};

// Class Core.DebugDrawer
// 0x0060 (0x0060 - 0x00C0)
class UDebugDrawer : public UObject
{
public:
	struct FColor                                      DefaultTextColor;                              // 0x0060 (0x0004) [0x0000000000000001] (CPF_Edit)    
	uint32_t                                           bSilent : 1;                                   // 0x0064 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bPrintActorsInline : 1;                        // 0x0064 (0x0004) [0x0000000000000001] [0x00000002] (CPF_Edit)
	int32_t                                            Indentation;                                   // 0x0068 (0x0004) [0x0000008000002000] (CPF_Transient | CPF_ProtectedWrite)
	class FString                                      IndentationString;                             // 0x0070 (0x0010) [0x0000008000402000] (CPF_Transient | CPF_NeedCtorLink | CPF_ProtectedWrite)
	class TArray<class UObject*>                       PrintedObjects;                                // 0x0080 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	class TArray<class UObject*>                       QueuedObjects;                                 // 0x0090 (0x0010) [0x0000000000402000] (CPF_Transient | CPF_NeedCtorLink)
	int32_t                                            PrintObjectCount;                              // 0x00A0 (0x0004) [0x0000000000002000] (CPF_Transient)
	struct FScriptDelegate                             __LogFunc__Delegate;                           // 0x00A8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.DebugDrawer");
		}

		return uClassPointer;
	};

	void Reset();
	void PrintText(const class FString& Text, const struct FColor& optionalInColor);
	void eventPrintArrayProperty(const class FString& PropertyName, int32_t Index, const class FString& Value);
	void eventPrintProperty(const class FString& PropertyName, const class FString& Value);
	void eventEndSection();
	void eventStartSection();
	void eventPrintObject(const class FString& Title, class UObject* ForObj);
	void eventPrintSeperater();
	void eventDebugArrayObject(const class FString& Title, int32_t Index, class UObject* ForObj);
	void eventDebugObject(const class FString& Title, class UObject* ForObj);
	bool ShouldDisplayDebug(const class FName& Category);
	void LogFunc(const class FString& Str);
};

// Class Core.Compression
// 0x0000 (0x0060 - 0x0060)
class UCompression : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Compression");
		}

		return uClassPointer;
	};

	static bool ZLibCompress(class TArray<uint8_t>& outUncompressed, class TArray<uint8_t>& outOutCompressed);
};

// Class Core.Component
// 0x0010 (0x0060 - 0x0070)
class UComponent : public UObject
{
public:
	class UClass*                                      TemplateOwnerClass;                            // 0x0060 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)
	class FName                                        TemplateName;                                  // 0x0068 (0x0008) [0x0000000000001002] (CPF_Const | CPF_Native)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Component");
		}

		return uClassPointer;
	};

};

// Class Core.StringObjectMap
// 0x0050 (0x0070 - 0x00C0)
class UStringObjectMap : public UComponent
{
public:
	struct FMap_Mirror                                 Map;                                           // 0x0070 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.StringObjectMap");
		}

		return uClassPointer;
	};

	bool Contains(const class FString& Key);
	void Remove(const class FString& Key);
	bool TryGetObjectW(const class FString& Key, class UObject*& outOutValue);
	void TryGet();
	class UObject* GetObjectW(const class FString& Key);
	void Get();
	void Set(const class FString& Key, class UObject* Value);
};

// Class Core.StringMap
// 0x0068 (0x0070 - 0x00D8)
class UStringMap : public UComponent
{
public:
	struct FMap_Mirror                                 Map;                                           // 0x0070 (0x0050) [0x0000000000001002] (CPF_Const | CPF_Native)
	struct FScriptDelegate                             __PairCallback__Delegate;                      // 0x00C0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.StringMap");
		}

		return uClassPointer;
	};

	void ForEach(const struct FScriptDelegate& Callback);
	void Append(class UStringMap* Other);
	bool Contains(const class FString& Key);
	void Remove(const class FString& Key);
	bool TryGet(const class FString& Key, class FString& outOutValue);
	class FString Get(const class FString& Key);
	void Set(const class FString& Key, const class FString& Value);
	void PairCallback(const class FString& Key, const class FString& Value);
};

// Class Core.ObjectProvider
// 0x0170 (0x0070 - 0x01E0)
class UObjectProvider : public UComponent
{
public:
	struct FPointer                                    VfTable_FObjectDestructionSubscriber;          // 0x0070 (0x0008) [0x0000000000801002] (CPF_Const | CPF_Native | CPF_NoExport)
	class TArray<class UObject*>                       MyObjects;                                     // 0x0078 (0x0010) [0x0000004000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink | CPF_PrivateWrite)
	struct FMap_Mirror                                 ObjectRefs;                                    // 0x0088 (0x0050) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)
	class TArray<class UObject*>                       TreeObjects;                                   // 0x00D8 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FObjectProviderSubscription>   SubscribedToAdds;                              // 0x00E8 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FObjectProviderSubscription>   SubscribedToRemoves;                           // 0x00F8 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FObjectProviderSubscription>   SubscribedToLists;                             // 0x0108 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	struct FArray_Mirror                               Injections;                                    // 0x0118 (0x0010) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)
	struct FArray_Mirror                               InterfaceInjections;                           // 0x0128 (0x0010) [0x0000000000003002] (CPF_Const | CPF_Native | CPF_Transient)
	class TArray<class UClass*>                        PendingInjectionClasses;                       // 0x0138 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	class TArray<struct FObjectProviderPendingCallback> PendingCallbacks;                              // 0x0148 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	uint8_t                                            bTriggeringCallbacks;                          // 0x0158 (0x0001) [0x0000000000002002] (CPF_Const | CPF_Transient)
	class UObjectProvider*                             Parent;                                        // 0x0160 (0x0008) [0x000000000408200A] (CPF_Const | CPF_ExportObject | CPF_Transient | CPF_Component | CPF_EditInline)
	class TArray<class UObjectProvider*>               Children;                                      // 0x0168 (0x0010) [0x000000000448200A] (CPF_Const | CPF_ExportObject | CPF_Transient | CPF_Component | CPF_NeedCtorLink | CPF_EditInline)
	class TArray<class UObjectProvider*>               Proxies;                                       // 0x0178 (0x0010) [0x000000000448200A] (CPF_Const | CPF_ExportObject | CPF_Transient | CPF_Component | CPF_NeedCtorLink | CPF_EditInline)
	class TArray<struct FObjectProviderPendingCallback> PendingInjectionCallbacks;                     // 0x0188 (0x0010) [0x0000000000402002] (CPF_Const | CPF_Transient | CPF_NeedCtorLink)
	struct FScriptDelegate                             __ObjectSubscriptionCallback__Delegate;        // 0x0198 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __ObjectListSubscriptionCallback__Delegate;    // 0x01B0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __ObjectChangeCallback__Delegate;              // 0x01C8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ObjectProvider");
		}

		return uClassPointer;
	};

	void SetParent(class UObjectProvider* InParent);
	void RemoveProxy(class UObjectProvider* InProxy);
	void AddProxy(class UObjectProvider* InProxy);
	void SetSingleton(class UClass* ObjClass, class UObject* Replacement);
	void Replace(class UObject* Existing, class UObject* Replacement);
	void AddAndRemoveObjects(class TArray<class UObject*>& outAddObjects, class TArray<class UObject*>& outRemoveObjects);
	void RemoveObjects(class TArray<class UObject*>& outInObjects);
	void RemoveAllObjects(class UClass* ObjectClass);
	void RemoveObject(class UObject* Obj);
	void AddObjects(class TArray<class UObject*>& outInObjects);
	void AddObject(class UObject* Obj);
	int32_t GetExactCount(class UClass* ObjClass);
	int32_t GetCount(class UClass* ObjClass);
	class UObject* GetOrCreate(class UClass* ObjClass);
	template<typename C>
	typename C* GetOrCreate()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)GetOrCreate(staticClass);
		}

		return nullptr;
	}

	class UObject* GetExact(class UClass* ObjClass);
	template<typename C>
	typename C* GetExact()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)GetExact(staticClass);
		}

		return nullptr;
	}

	class UObject* GetUnsafe(class UClass* ObjClass);
	template<typename C>
	typename C* GetUnsafe()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)GetUnsafe(staticClass);
		}

		return nullptr;
	}

	class UObject* Get(class UClass* ObjClass);
	template<typename C>
	typename C* Get()
	{
		UClass* staticClass = C::StaticClass();

		if (staticClass)
		{
			return (C*)Get(staticClass);
		}

		return nullptr;
	}

	void AllObjects(class UClass* BaseClass, class UClass* optionalInterfaceClass, class UObject*& outObj);
	bool IsRegisteredForInjection(class UObject* Subscriber);
	void InjectDelayed(class UObject* Subscriber);
	void Inject(class UObject* Subscriber);
	void UnsubscribeAll(class UObject* Subscriber);
	void Unsubscribe(const struct FScriptDelegate& Callback, const struct FScriptDelegate& optionalCallback2 = {});
	void SubscribeList(class UClass* BaseClass, const struct FScriptDelegate& Callback);
	void SubscribeOnce(class UClass* BaseClass, const struct FScriptDelegate& optionalOnAdd = {}, const struct FScriptDelegate& optionalOnRemove = {});
	void Subscribe(class UClass* BaseClass, const struct FScriptDelegate& optionalOnAdd = {}, const struct FScriptDelegate& optionalOnRemove = {});
	void ObjectChangeCallback();
	void ObjectListSubscriptionCallback(class UObjectProvider* Provider);
	void ObjectSubscriptionCallback(class UObject* Obj);
};

// Class Core.DistributionVector
// 0x000C (0x0070 - 0x007C)
class UDistributionVector : public UComponent
{
public:
	struct FPointer                                    VfTable_FCurveEdInterface;                     // 0x0070 (0x0008) [0x0000000000801002] (CPF_Const | CPF_Native | CPF_NoExport)
	uint32_t                                           bCanBeBaked : 1;                               // 0x0078 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bIsDirty : 1;                                  // 0x0078 (0x0004) [0x0000000000000000] [0x100000002] 

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.DistributionVector");
		}

		return uClassPointer;
	};

	struct FVector GetVectorValue(float optionalF = {}, int32_t optionalLastExtreme = {});
};

// Class Core.DistributionFloat
// 0x000C (0x0070 - 0x007C)
class UDistributionFloat : public UComponent
{
public:
	struct FPointer                                    VfTable_FCurveEdInterface;                     // 0x0070 (0x0008) [0x0000000000801002] (CPF_Const | CPF_Native | CPF_NoExport)
	uint32_t                                           bCanBeBaked : 1;                               // 0x0078 (0x0004) [0x0000000000000001] [0x00000001] (CPF_Edit)
	uint32_t                                           bIsDirty : 1;                                  // 0x0078 (0x0004) [0x0000000000000000] [0x100000002] 

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.DistributionFloat");
		}

		return uClassPointer;
	};

	float GetFloatValue(float optionalF = {});
};

// Class Core.Commandlet
// 0x0054 (0x0060 - 0x00B4)
class UCommandlet : public UObject
{
public:
	class FString                                      HelpDescription;                               // 0x0060 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class FString                                      HelpUsage;                                     // 0x0070 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class FString                                      HelpWebLink;                                   // 0x0080 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class TArray<class FString>                        HelpParamNames;                                // 0x0090 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	class TArray<class FString>                        HelpParamDescriptions;                         // 0x00A0 (0x0010) [0x0000000000408002] (CPF_Const | CPF_Localized | CPF_NeedCtorLink)
	uint32_t                                           IsServer : 1;                                  // 0x00B0 (0x0004) [0x0000000000000000] [0x00000001] 
	uint32_t                                           IsClient : 1;                                  // 0x00B0 (0x0004) [0x0000000000000000] [0x00000002] 
	uint32_t                                           IsEditor : 1;                                  // 0x00B0 (0x0004) [0x0000000000000000] [0x00000004] 
	uint32_t                                           LogToConsole : 1;                              // 0x00B0 (0x0004) [0x0000000000000000] [0x00000008] 
	uint32_t                                           ShowErrorCount : 1;                            // 0x00B0 (0x0004) [0x0000000000000000] [0x100000010] 

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Commandlet");
		}

		return uClassPointer;
	};

	int32_t eventMain(const class FString& Params);
};

// Class Core.HelpCommandlet
// 0x0004 (0x00B4 - 0x00B8)
class UHelpCommandlet : public UCommandlet
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.HelpCommandlet");
		}

		return uClassPointer;
	};

	int32_t eventMain(const class FString& Params);
};

// Class Core.Breadcrumbs
// 0x0008 (0x0060 - 0x0068)
class UBreadcrumbs : public UObject
{
public:
	struct FPointer                                    BreadcrumbInstance;                            // 0x0060 (0x0008) [0x0000000000001000] (CPF_Native)  

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Breadcrumbs");
		}

		return uClassPointer;
	};

	void BreadcrumbFloat(const class FString& Category, float Value);
	void BreadcrumbString(const class FString& Category, const class FString& Value);
};

// Class Core.Base64
// 0x0000 (0x0060 - 0x0060)
class UBase64 : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Base64");
		}

		return uClassPointer;
	};

	static class TArray<uint8_t> PadAndDecodeString(const class FString& Input);
	static void DecodeStringInline(const class FString& Input, class TArray<uint8_t>& outOutput);
	static class TArray<uint8_t> DecodeString(const class FString& Input);
	static void DecodeInline(class TArray<uint8_t>& outInput, class TArray<uint8_t>& outOutput);
	static class TArray<uint8_t> Decode(class TArray<uint8_t>& outInput);
	static void EncodeStringInline(class TArray<uint8_t>& outInput, class FString& outOutput);
	static class FString EncodeString(class TArray<uint8_t>& outInput);
	static void EncodeInline(class TArray<uint8_t>& outInput, class TArray<uint8_t>& outOutput);
	static class TArray<uint8_t> Encode(class TArray<uint8_t>& outInput);
};

// Class Core.AutomationTest
// 0x0040 (0x0060 - 0x00A0)
class UAutomationTest : public UObject
{
public:
	class TArray<class FString>                        MaterialsCompiled;                             // 0x0060 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        MaterialsFailedCompile;                        // 0x0070 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<class FString>                        AsyncPreloadPackagesMissing;                   // 0x0080 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)
	class TArray<struct FScriptWarning>                ScriptWarnings;                                // 0x0090 (0x0010) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.AutomationTest");
		}

		return uClassPointer;
	};

};

// Class Core.AsyncTask
// 0x0070 (0x0060 - 0x00D0)
class UAsyncTask : public UObject
{
public:
	uint32_t                                           bComplete : 1;                                 // 0x0060 (0x0004) [0x0000004000000000] [0x00000001] (CPF_PrivateWrite)
	uint32_t                                           bDisposed : 1;                                 // 0x0060 (0x0004) [0x0000004000000000] [0x00000002] (CPF_PrivateWrite)
	class UError*                                      Error;                                         // 0x0068 (0x0008) [0x0000004000000000] (CPF_PrivateWrite)
	struct FScriptDelegate                             __EventAsyncTaskSuccess__Delegate;             // 0x0070 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __EventAsyncTaskFail__Delegate;                // 0x0088 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __EventAsyncTaskComplete__Delegate;            // 0x00A0 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)
	struct FScriptDelegate                             __EventDisposed__Delegate;                     // 0x00B8 (0x0018) [0x0000000000400000] (CPF_NeedCtorLink)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.AsyncTask");
		}

		return uClassPointer;
	};

	void QueCallbacks();
	static class UAsyncTask* CreateError(class UError* InError);
	static class UAsyncTask* CreateSuccess();
	static class UAsyncTask* Create();
	class UAsyncTask* Watch(class UAsyncTask* Other);
	static class UAsyncTask* All(const class TArray<class UAsyncTask*>& Dependents);
	class UAsyncTask* DependOn(class UAsyncTask* Other);
	class UAsyncTask* eventNotifyOnDispose(const struct FScriptDelegate& Callback);
	void eventClearCallbacks();
	void eventDispose();
	void SetComplete(class UError* optionalInError = {});
	void eventSetError(class UError* InError);
	class UAsyncTask* eventNotifyOnComplete(const struct FScriptDelegate& Callback);
	class UAsyncTask* eventNotifyOnFail(const struct FScriptDelegate& Callback);
	class UAsyncTask* eventNotifyOnSuccess(const struct FScriptDelegate& Callback);
	void EventDisposed();
	void EventAsyncTaskComplete(class UError* TaskError);
	void EventAsyncTaskFail(class UError* TaskError);
	void EventAsyncTaskSuccess();
};

// Class Core.AsyncResult
// 0x0000 (0x00D0 - 0x00D0)
class UAsyncResult : public UAsyncTask
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.AsyncResult");
		}

		return uClassPointer;
	};

};

// Class Core._Types_Core
// 0x0000 (0x0060 - 0x0060)
class U_Types_Core : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core._Types_Core");
		}

		return uClassPointer;
	};

};

// Class Core.State
// 0x0060 (0x0130 - 0x0190)
class UState : public UStruct
{
public:
	uint8_t                                            UnknownData00[0x60];                            // 0x0130 (0x0060) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.State");
		}

		return uClassPointer;
	};

};

// Class Core.Package
// 0x00E8 (0x0060 - 0x0148)
class UPackage : public UObject
{
public:
	uint8_t                                            UnknownData00[0xE8];                            // 0x0060 (0x00E8) MISSED OFFSET

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Package");
		}

		return uClassPointer;
	};

};

// Class Core.Class
// 0x0228 (0x0190 - 0x03B8)
class UClass : public UState
{
public:
	uint32_t ClassFlags; // 0x0190 (0x0004)
	uint32_t ClassUnique; // 0x0194 (0x0004)
	TMap<FName, UDelegateProperty*> ClassDelegates; // 0x0198 (0x0050)
	uint32_t ClassCastFlags; // 0x01E8 (0x0004)
	UClass* ClassWithin; // 0x01F0 (0x0008)
	FName Category; // 0x01F8 (0x0008)
	TArray<FRepRecord> ClassReps; // 0x0200 (0x0010)
	TArray<UField*> NetFields; // 0x0210 (0x0010)
	TArray<FName> HideCategories; // 0x0220 (0x0010)
	TArray<FName> AutoExpandCategories; // 0x0230 (0x0010)
	TArray<FName> AutoCollapseCategories; // 0x0240 (0x0010)
	TArray<FName> DontSortCategories; // 0x0250 (0x0010)
	TArray<FName> DependentOn; // 0x0260 (0x0010)
	TArray<FName> ClassGroupNames; // 0x0270 (0x0010)
	uint32_t bForceScriptOrder; // 0x0280 (0x0004)
	FString ClassHeaderFilename; // 0x0284 (0x0010)
	uint8_t ManualPad[40]; // 0x0294 (0x0028)
	UObject* ClassDefaultObject; // 0x02C0 (0x0008)
	void* ClassConstructor; // 0x02C8 (0x0008)
	void* ClassStaticConstructor; // 0x02D0 (0x0008)
	void* ClassStaticInitializer; // 0x02D8 (0x0008)
	TMap<FName, UObject*> ComponentNameToDefaultObjectMap; // 0x02E0 (0x0050)
	TArray<FImplementedInterface> Interfaces; // 0x0330 (0x0010)
	FString DefaultPropText; // 0x0340 (0x0010)
	uint32_t bNeedsPropertiesLinked; // 0x0350 (0x0004)
	TArray<uint32_t> ReferenceTokenStream; // 0x0354 (0x0010)
	TMap<FName, UState*> ClassStates; // 0x0364 (0x0050)

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.Class");
		}

		return uClassPointer;
	};

};

// Class Core.__AsyncTask__All_0x1
// 0x0010 (0x0060 - 0x0070)
class U__AsyncTask__All_0x1 : public UObject
{
public:
	int32_t                                            DependentsCount;                               // 0x0060 (0x0004) [0x0000000000000000]               
	class UAsyncTask*                                  Parent;                                        // 0x0068 (0x0008) [0x0000000000000000]               

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.__AsyncTask__All_0x1");
		}

		return uClassPointer;
	};

	void __AsyncTask__All_0x1();
};

// Class Core._LoggingDoc
// 0x0000 (0x0060 - 0x0060)
class U_LoggingDoc : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core._LoggingDoc");
		}

		return uClassPointer;
	};

	static void TestSpecialLogging();
};

// Class Core._Types_Generated
// 0x0000 (0x0060 - 0x0060)
class U_Types_Generated : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core._Types_Generated");
		}

		return uClassPointer;
	};

};

// Class Core.ArrayFuncs
// 0x0000 (0x0060 - 0x0060)
class UArrayFuncs : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.ArrayFuncs");
		}

		return uClassPointer;
	};

	static void GetRandomElement();
	static void ShuffleArray();
};

// Class Core.IDisposable
// 0x0000 (0x0060 - 0x0060)
class UIDisposable : public UInterface
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.IDisposable");
		}

		return uClassPointer;
	};

	void eventDispose();
};

// Class Core.RotatorConversions
// 0x0000 (0x0060 - 0x0060)
class URotatorConversions : public UObject
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.RotatorConversions");
		}

		return uClassPointer;
	};

	static struct FRotatorRadians GetAsRadians(const struct FRotator& InRotator);
	static struct FRotatorDegrees GetAsDegrees(const struct FRotator& InRotator);
};

// Class Core.TAsyncResult
// 0x0000 (0x00D0 - 0x00D0)
class UTAsyncResult : public UAsyncTask
{
public:

public:
	static UClass* StaticClass()
	{
		static UClass* uClassPointer = nullptr;

		if (!uClassPointer)
		{
			uClassPointer = UObject::FindClass("Class Core.TAsyncResult");
		}

		return uClassPointer;
	};

};

/*
# ========================================================================================= #
#
# ========================================================================================= #
*/

#ifdef _MSC_VER
#pragma pack(pop)
#endif
