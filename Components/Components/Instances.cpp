#include "Instances.hpp"
#include "../Includes.hpp"
#include <windows.h>

namespace
{
    constexpr int32_t kMaxObjectCount = 2'000'000;

    bool IsReadableRange(const void* address, size_t byteCount)
    {
        if (!address || byteCount == 0)
            return false;

        MEMORY_BASIC_INFORMATION mbi{};
        if (VirtualQuery(address, &mbi, sizeof(mbi)) != sizeof(mbi))
            return false;

        const DWORD protection = mbi.Protect & 0xFF;
        if (mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_GUARD) != 0 || protection == PAGE_NOACCESS)
            return false;

        const auto begin = reinterpret_cast<uintptr_t>(address);
        const auto end = begin + byteCount;
        const auto regionEnd = reinterpret_cast<uintptr_t>(mbi.BaseAddress) + mbi.RegionSize;
        return end >= begin && end <= regionEnd;
    }

    bool HasSafeName(const FName& name)
    {
        auto* names = FName::Names();
        if (!IsReadableRange(names, sizeof(*names)) || !names->data())
            return false;

        const int32_t count = names->size();
        const int32_t index = name.GetDisplayIndex();
        if (count <= 0 || count > kMaxObjectCount || names->capacity() < count ||
            index < 0 || index >= count ||
            !IsReadableRange(names->data(), sizeof(FNameEntry*) * static_cast<size_t>(count)))
            return false;

        FNameEntry* entry = names->at(index);
        if (!IsReadableRange(entry, sizeof(FNameEntry)))
            return false;

                                                                            
                                                                          
        for (size_t i = 0; i < _countof(entry->Name); ++i)
        {
            if (entry->Name[i] == L'\0')
                return true;
        }
        return false;
    }

    bool SafeEntryEquals(FNameEntry* entry, const wchar_t* expected)
    {
        if (!entry || !expected)
            return false;

                                                                              
                                                                                  
        __try
        {
            for (size_t i = 0; i < _countof(entry->Name); ++i)
            {
                const wchar_t a = entry->Name[i];
                const wchar_t b = expected[i];
                if (a != b)
                    return false;
                if (a == L'\0')
                    return true;
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
        return false;
    }

    bool TryResolveNameIndex(const wchar_t* expected, int32_t* outIndex)
    {
        if (!expected || !outIndex)
            return false;

        auto* names = FName::Names();
        if (!IsReadableRange(names, sizeof(*names)) || !names->data())
            return false;

        const int32_t count = names->size();
        if (count <= 0 || count > kMaxObjectCount || names->capacity() < count ||
            !IsReadableRange(names->data(), sizeof(FNameEntry*) * static_cast<size_t>(count)))
            return false;

                                                                              
                                                                                 
                                                                                 
                                                         
        for (int32_t i = 0; i < count; ++i)
        {
            FNameEntry* entry = names->at(i);
            if (SafeEntryEquals(entry, expected))
            {
                *outIndex = i;
                return true;
            }
        }
        return false;
    }

    bool SafeReadMetaClassNameIndex(UObject* object, int32_t* outIndex)
    {
        if (!object || !outIndex)
            return false;

        __try
        {
            UObject* metaClass = object->Class;
            if (!metaClass)
                return false;
            *outIndex = metaClass->Name.GetDisplayIndex();
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool IsSafeObjectForFullName(UObject* object)
    {
                                                                               
                                                                                   
                                                                                  
                                                                                  
        auto* names = FName::Names();
        if (!names || !names->data())
            return false;

        const int32_t nameCount = names->size();
        if (nameCount <= 0 || nameCount > kMaxObjectCount || names->capacity() < nameCount)
            return false;

        __try
        {
            UObject* cursor = object;
            for (int outerDepth = 0; cursor && outerDepth < 64; ++outerDepth)
            {
                UObject* cls = cursor->Class;
                if (!cls)
                    return false;

                const int32_t objectName = cursor->Name.GetDisplayIndex();
                const int32_t className = cls->Name.GetDisplayIndex();
                if (objectName < 0 || objectName >= nameCount ||
                    className < 0 || className >= nameCount)
                {
                    return false;
                }

                cursor = cursor->Outer;
            }

                                                                             
                                      
            return cursor == nullptr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

}

InstancesComponent::InstancesComponent() : Component("Instances", "Manages class instances and objects.") { OnCreate(); }

InstancesComponent::~InstancesComponent() { OnDestroy(); }

void InstancesComponent::OnCreate()
{
	I_UCanvas = nullptr;
	I_AHUD = nullptr;
	I_UGameViewportClient = nullptr;
	I_APlayerController = nullptr;
	
}

void InstancesComponent::OnDestroy()
{
	for (UObject* instance : CreatedInstances)
	{
		if (instance)
		{
			MarkForDestory(instance);
		}
	}
}

class UClass* InstancesComponent::FindStaticClass(const std::string& className)
{
	if (StaticClasses.empty())
	{
		MapObjects();
	}

	if (StaticClasses.find(className) != StaticClasses.end())
	{
		return StaticClasses[className];
	}

	return nullptr;
}

class UFunction* InstancesComponent::FindStaticFunction(const std::string& className)
{
	if (StaticFunctions.empty())
	{
		MapObjects();
	}

	if (StaticFunctions.find(className) != StaticFunctions.end())
	{
		return StaticFunctions[className];
	}

	return nullptr;
}

void InstancesComponent::MarkInvincible(class UObject* object)
{
	if (object)
	{
		object->ObjectFlags &= ~RF_Transient;
		object->ObjectFlags &= ~RF_TagGarbage;
		object->ObjectFlags |= RF_Public;
		object->ObjectFlags |= RF_Standalone;
		object->ObjectFlags |= RF_RootSet;
	}
}

void InstancesComponent::MarkForDestory(class UObject* object)
{
	if (object)
	{
		object->ObjectFlags = 0;
		object->ObjectFlags |= RF_Public;
		object->ObjectFlags |= RF_Transient;
		object->ObjectFlags |= RF_TagGarbage;
	}
}

class UEngine* InstancesComponent::IUEngine()
{
	return UEngine::GetEngine();
}

class UAudioDevice* InstancesComponent::IUAudioDevice()
{
	return UEngine::GetAudioDevice();
}

class AWorldInfo* InstancesComponent::IAWorldInfo()
{
	return UEngine::GetCurrentWorldInfo();
}

class UCanvas* InstancesComponent::IUCanvas()
{
	return I_UCanvas;
}

class AHUD* InstancesComponent::IAHUD()
{
	return I_AHUD;
}

class UGameViewportClient* InstancesComponent::IUGameViewportClient()
{
	return I_UGameViewportClient;
}

class ULocalPlayer* InstancesComponent::IULocalPlayer()
{
	UEngine* engine = IUEngine();
	if (!IsReadableRange(engine, sizeof(UEngine)))
		return nullptr;

	const TArray<ULocalPlayer*>& players = engine->GamePlayers;
	const int32_t playerCount = players.size();
	if (playerCount <= 0 || playerCount > 4 || players.capacity() < playerCount ||
		!players.data() || !IsReadableRange(players.data(), sizeof(ULocalPlayer*) * static_cast<size_t>(playerCount)))
		return nullptr;

	ULocalPlayer* localPlayer = players[0];
	if (IsReadableRange(localPlayer, sizeof(ULocalPlayer)))
		return localPlayer;

	return nullptr;
}

class APlayerController* InstancesComponent::IAPlayerController()
{
	return I_APlayerController;
}

class USaveData_TA* InstancesComponent::GetSaveData() 
{
	USaveData_TA* saveData = Instances.GetInstanceOf<USaveData_TA>();
	return saveData;
}

struct FUniqueNetId InstancesComponent::GetUniqueID()
{
	ULocalPlayer* localPlayer = IULocalPlayer();
	if (!IsReadableRange(localPlayer, sizeof(ULocalPlayer)))
		return FUniqueNetId();

	APlayerController* controller = localPlayer->Actor;
	if (IsReadableRange(controller, sizeof(APlayerController)) &&
		IsReadableRange(controller->PlayerReplicationInfo, sizeof(APlayerReplicationInfo)))
	{
		return controller->PlayerReplicationInfo->UniqueId;
	}
	
	                                                             
	return FUniqueNetId();
}

void InstancesComponent::SetCanvas(class UCanvas* canvas)
{
	if (I_UCanvas != canvas)
	{
		I_UCanvas = canvas;
	}
}

void InstancesComponent::SetHUD(class AHUD* hud)
{
	if (I_AHUD != hud)
	{
		I_AHUD = hud;
	}
}

void InstancesComponent::SetGameViewportClient(class UGameViewportClient* viewportClient)
{
	if (I_UGameViewportClient != viewportClient)
	{
		I_UGameViewportClient = viewportClient;
	}
}

void InstancesComponent::SetPlayerController(class APlayerController* playerController)
{
	if (I_APlayerController != playerController)
	{
		I_APlayerController = playerController;
	}
}

void InstancesComponent::MapObjects()
{
	                                                                                
	                                                                            
	                                                                        
	                                                                      
	auto* objects = UObject::GObjObjects();
	if (!objects || !objects->data() || objects->size() <= 0 || objects->size() > kMaxObjectCount ||
		objects->capacity() < objects->size() ||
		!IsReadableRange(objects->data(), sizeof(UObject*) * static_cast<size_t>(objects->size())))
	{
		Console.Error(GetNameFormatted() + "Cannot map instances: global object array is not valid.");
		return;
	}

	StaticClasses.clear();
	StaticFunctions.clear();

	int32_t classNameIndex = -1;
	int32_t functionNameIndex = -1;
	if (!TryResolveNameIndex(L"Class", &classNameIndex) ||
		!TryResolveNameIndex(L"Function", &functionNameIndex))
	{
		Console.Error(GetNameFormatted() + "Cannot map instances: Class/Function FName indexes were not found.");
		return;
	}

	const int32_t objectCount = objects->size();
	for (int32_t index = 0; index < objectCount; ++index)
	{
		UObject* uObject = objects->at(index);
		int32_t metaNameIndex = -1;
		if (!SafeReadMetaClassNameIndex(uObject, &metaNameIndex) ||
			(metaNameIndex != classNameIndex && metaNameIndex != functionNameIndex))
		{
			continue;
		}

		                                                                       
		                                                                                     
		if (!IsSafeObjectForFullName(uObject))
			continue;

		std::string objectFullName = uObject->GetFullName();
		if (objectFullName.rfind("Class ", 0) == 0)
		{
			StaticClasses.emplace(objectFullName, reinterpret_cast<UClass*>(uObject));
		}
		else if (objectFullName.rfind("Function ", 0) == 0)
		{
			StaticFunctions.emplace(objectFullName, reinterpret_cast<UFunction*>(uObject));
		}
	}
}

FString to_fstring(const std::string& str)
{
	const char* Char = str.c_str();

	const size_t cSize = strlen(Char) + 1;
	wchar_t* wChar = new wchar_t[cSize];
	mbstowcs_s(nullptr, wChar, cSize, Char, cSize - 1);
	return FString(wChar);
}
FName to_fname(const std::string& s)
{
	wchar_t* p = new wchar_t[s.size() + 1];
	for (std::string::size_type i = 0; i < s.size(); ++i)
		p[i] = s[i];

	p[s.size()] = '\0';
	return FName(p);
}


void InstancesComponent::Initialize()
{
	const ULONGLONG started = GetTickCount64();
	MapObjects();
	const ULONGLONG elapsed = GetTickCount64() - started;
	Console.Write(GetNameFormatted() + "Instances Initialized in " + std::to_string(elapsed) + " ms!");
}

InstancesComponent Instances;
