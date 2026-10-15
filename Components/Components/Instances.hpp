#pragma once
#include "../Component.hpp"

                                                   
                                                                                 
class InstancesComponent : public Component
{
public:
	InstancesComponent();
	~InstancesComponent() override;

public:
	void OnCreate() override;
	void OnDestroy() override;

private:
	std::map<std::string, class UClass*> StaticClasses;
	std::map<std::string, class UFunction*> StaticFunctions;
	std::vector<class UObject*> CreatedInstances;

public:                                                              
	                                                                                                                                           
	                                                                                                                    

	                                                                                                                       
	template<typename T> T* GetDefaultInstanceOf()
	{
		if (std::is_base_of<UObject, T>::value)
		{
			for (UObject* uObject : *UObject::GObjObjects())
			{
				if (uObject && uObject->IsA<T>())
				{
					if (uObject->GetFullName().find("Default__") != std::string::npos)
					{
						return static_cast<T*>(uObject);
					}
				}
			}
		}

		return nullptr;
	}

	template<typename T> T* GetInstanceOf()
	{
		if (std::is_base_of<UObject, T>::value)
		{
			                                         
			for (int32_t i = UObject::GObjObjects()->size() - 1; i >= 0; i--)
			{
				UObject* uObject = UObject::GObjObjects()->at(i);
				if (uObject && uObject->IsA<T>())
				{
					if (uObject->GetFullName().find("Default__") == std::string::npos)
					{
						return static_cast<T*>(uObject);
					}
				}
			}
		}
		return nullptr;
	}
	UTexture2DDynamic* PathToTexture(std::string imagePath)
	{
		FString fspath;
		wchar_t* p = new wchar_t[imagePath.size() + 1];
		for (std::string::size_type i = 0; i < imagePath.size(); ++i)
			p[i] = imagePath[i];
		p[imagePath.size()] = '\0';
		fspath = FString(p);
		delete[] p;

		std::filesystem::path path(imagePath);

		bool exists = std::filesystem::exists(path);

		if (exists == true) {
			TArray<uint8_t> filebytes;

			int filesize = UFileSystem::GetFileSize(fspath);

			if (filesize > 1) {
				bool filetobytes = UFileSystem::LoadFileToBytes(fspath, 0, filesize, filebytes);

				if (filetobytes)
				{
					UTexture2DDynamic* customtexture = CreateInstance<UTexture2DDynamic>();

					if (customtexture) {
						customtexture->CompressionNone = true;

						if (imagePath.find("png") != std::string::npos || imagePath.find("PNG") != std::string::npos || imagePath.find(".png") != std::string::npos || imagePath.find(".PNG") != std::string::npos)
							customtexture->UpdateMipFromPNG(0, filebytes);
						else { return customtexture; }

						if (!customtexture) { return nullptr; }

						return customtexture;
					}
				}
			}
		}

		return nullptr;
	}

	FProductInstanceID IntToProductInstanceID(int64_t Value)
	{
		FProductInstanceID ID;
		ID.UpperBits = static_cast<uint64_t>(Value >> 32);
		ID.LowerBits = static_cast<uint64_t>(Value & 0xffffffff);
		return ID;
	}

	                                                                                                             
	template<typename T> std::vector<T*> GetAllInstancesOf()
	{
		std::vector<T*> objectInstances;

		if (std::is_base_of<UObject, T>::value)
		{
			for (UObject* uObject : *UObject::GObjObjects())
			{
				if (uObject && uObject->IsA<T>())
				{
					if (uObject->GetFullName().find("Default__") == std::string::npos)
					{
						objectInstances.push_back(static_cast<T*>(uObject));
					}
				}
			}
		}

		return objectInstances;
	}

	                                             
	template<typename T> std::vector<T*> GetAllDefaultInstancesOf()
	{
		std::vector<T*> objectInstances;

		if (std::is_base_of<UObject, T>::value)
		{
			UClass* staticClass = T::StaticClass();

			if (staticClass)
			{
				for (UObject* uObject : *UObject::GObjObjects())
				{
					if (uObject && uObject->IsA<T>())
					{
						if (uObject->GetFullName().find("Default__") != std::string::npos)
						{
							objectInstances.push_back(static_cast<T*>(uObject));
						}
					}
				}
			}
		}

		return objectInstances;
	}

	                                                                                                                            
	template<typename T> T* FindObject(const std::string& objectName, bool bStrictFind = false)
	{
		if (std::is_base_of<UObject, T>::value)
		{
			                                                        
			for (int32_t i = UObject::GObjObjects()->size() - 1; i >= 0; i--)
			{
				UObject* uObject = UObject::GObjObjects()->at(i);

				if (uObject && uObject->IsA<T>())
				{
					std::string objectFullName = uObject->GetFullName();

					if (bStrictFind)
					{
						if (objectFullName == objectName)
						{
							return static_cast<T*>(uObject);
						}
					}
					else if (objectFullName.find(objectName) != std::string::npos)
					{
						return static_cast<T*>(uObject);
					}
				}
			}
		}

		return nullptr;
	}

	                                                                                                                                          
	template<typename T> std::vector<T*> FindAllObjects(const std::string& objectName)
	{
		std::vector<T*> objectInstances;

		if (std::is_base_of<UObject, T>::value)
		{
			                                                        
			for (int32_t i = UObject::GObjObjects()->size() - 1; i >= 0; i--)
			{
				UObject* uObject = UObject::GObjObjects()->at(i);

				if (uObject && uObject->IsA<T>())
				{
					if (uObject->GetFullName().find(objectName) != std::string::npos)
					{
						objectInstances.push_back(static_cast<T*>(uObject));
					}
				}
			}
		}

		return objectInstances;
	}

	class UClass* FindStaticClass(const std::string& className);

	class UFunction* FindStaticFunction(const std::string& functionName);

	                                                                             
	                                                                                                                      
	                                                           
	template<typename T> T* CreateInstance()
	{
		T* returnObject = nullptr;

		if (std::is_base_of<UObject, T>::value)
		{
			T* defaultObject = GetDefaultInstanceOf<T>();
			UClass* staticClass = T::StaticClass();

			if (defaultObject && staticClass)
			{
				returnObject = static_cast<T*>(defaultObject->DuplicateObject(defaultObject, defaultObject->Outer, staticClass));
			}

			                                                                                                                    
			if (returnObject)
			{
				MarkInvincible(returnObject);
				CreatedInstances.push_back(returnObject);
			}
		}

		return returnObject;
	}

	                                                            
	void MarkInvincible(class UObject* object);

	                                                                                      
	void MarkForDestory(class UObject* object);

private: 
	class UCanvas* I_UCanvas;
	class AHUD* I_AHUD;
	class UGameViewportClient* I_UGameViewportClient;
	class APlayerController* I_APlayerController;

public:                                                                                                                                
	class UEngine* IUEngine();
	class UAudioDevice* IUAudioDevice();
	class AWorldInfo* IAWorldInfo();
	class UCanvas* IUCanvas();
	class AHUD* IAHUD();
	class UGameViewportClient* IUGameViewportClient();
	class ULocalPlayer* IULocalPlayer();
	class APlayerController* IAPlayerController();
	class USaveData_TA* GetSaveData();
	struct FUniqueNetId GetUniqueID();

public:                                                                            
	void SetCanvas(class UCanvas* canvas);
	void SetHUD(class AHUD* hud);
	void SetGameViewportClient(class UGameViewportClient* viewportClient);
	void SetPlayerController(class APlayerController* playerController);
	void MapObjects();                                                                     
	void Initialize();                                                                 
};

extern class InstancesComponent Instances;