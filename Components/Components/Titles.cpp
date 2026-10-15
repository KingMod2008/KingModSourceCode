#define _CRT_SECURE_NO_WARNINGS
#include "Titles.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include "../Includes.hpp"
#include "../../Extensions/Extensions/Formatting.hpp"

TitleComponent::TitleComponent() : Component("Titles", "Manages game titles from database with spawn functionality.") { 
	saveData = nullptr;
	OnCreate(); 
}

TitleComponent::~TitleComponent() { OnDestroy(); }



void TitleComponent::LoadAllTitle()
{
	if (Titles.TitlesForImGui.size() == 0)
	{		
		                                                           
		if (!Core.AreGlobalsValid()) {
			Console.Write("[Titles] Game globals not ready, skipping title loading");
			return;
		}
		
		UTitleConfig_X* titleConfig = Instances.GetInstanceOf<UTitleConfig_X>();
		if (!titleConfig) {
			Console.Write("[Titles] UTitleConfig_X not available yet");
			return;
		}
		int autoTour = 0;
		for (int i = 0; i < titleConfig->Titles.size(); i++)
		{
			std::string titleId = titleConfig->Titles[i].Id.ToString();
			if (!titleId.find("AutoTour"))
				autoTour++;
			if (autoTour == 1)
				titleId = titleId + "_1";
			else if (autoTour == 2)
			{
				titleId = titleId + "_2";
				autoTour = 0;
			}
			Titles.TitlesForImGui.push_back({ titleId, titleConfig->Titles[i].Text.ToString(),
											titleConfig->Titles[i].Color, titleConfig->Titles[i].GlowColor });

		}
		Console.Write("All Titles has been loaded");
	}


}



                                                                

UOnlineProduct_TA* SpawnProduct(int item, TArray<FOnlineProductAttribute> attributes, int seriesid, int tradehold, bool log)
{
	                                  
	if (!Titles.saveData) {
		Titles.saveData = Instances.GetSaveData();
	}
	
	if (Titles.saveData)
	{
		if (UProductUtil_TA* utils = (UProductUtil_TA*)UProductUtil_TA::StaticClass())
		{
			FOnlineProductData productData;

			productData.ProductID = item;
			productData.SeriesID = seriesid;
			productData.InstanceID = Items.GeneratePIID(item);
			productData.TradeHold = tradehold;
			productData.AddedTimestamp = Items.GetTimestampLong();
			productData.Attributes = attributes;

			if (UOnlineProduct_TA* product = utils->CreateOnlineProduct(productData))
			{
				if (SpawnProductData(product->InstanceOnlineProductData(), "", true))
					return product;
			}
		}
		else
		{
			Console.Write("[Titles] UProductUtil_TA::StaticClass() returned null");
		}
	}
	else
	{
		Console.Write("[Titles] saveData is null - game may not be fully initialized");
	}

	return nullptr;
}

bool SpawnProductData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation)
{
	UGFxData_ContainerDrops_TA* containerDrops = Instances.GetInstanceOf<UGFxData_ContainerDrops_TA>();

	if (containerDrops)
	{
		UOnlineProduct_TA* onlineProduct = containerDrops->CreateTempOnlineProduct(productData);

		if (onlineProduct)
		{
			std::wstring wideSpawnMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
			FString Message = (spawnMessage.empty()) ? FString(L"") : FString(wideSpawnMsg.c_str());

			Titles.saveData->eventGiveOnlineProduct(onlineProduct, Message,0.0f);
			if (animation) {
				Titles.saveData->GiveOnlineProductHelper(onlineProduct);
				Titles.saveData->OnNewOnlineProduct(onlineProduct, Message);
				Titles.saveData->EventNewOnlineProduct(Titles.saveData, onlineProduct, Message);
			}

			if (Titles.saveData->OnlineProductSet) {
				Titles.saveData->OnlineProductSet->Add(onlineProduct);

				auto ProductData = onlineProduct->InstanceOnlineProductData();

				Titles.spawnedProducts.push_back(ProductData);
			}

			Console.Write("[Titles] Successfully spawned product: " + onlineProduct->ToJson().ToString());

			return true;
		}
	}

	return false;
}


                                                   

void TitleComponent::LoadTitles()
{
	                                    
	static bool loadingAttempted = false;
	if (loadingAttempted && !allTitles.empty()) {
		return;                               
	}
	loadingAttempted = true;

	try
	{
		                                                           
		if (!Core.AreGlobalsValid()) {
			Console.Write("[Titles] Game globals not ready, skipping title loading");
			loadingAttempted = false;               
			return;
		}

		                                                
		static int attemptCount = 0;
		attemptCount++;
		
		if (attemptCount < 3) {
			Console.Write("[Titles] Waiting for game initialization... (attempt " + std::to_string(attemptCount) + "/3)");
			loadingAttempted = false;               
			return;
		}

		                                      
		auto productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (!productDatabase) {
			Console.Write("[Titles] ProductDatabase not available yet");
			loadingAttempted = false;               
			return;
		}

		                          
		if (!productDatabase->Products_New.data()) {
			Console.Write("[Titles] Products array not initialized");
			loadingAttempted = false;               
			return;
		}

		                               
		if (productDatabase->Products_New.size() <= 0) {
			Console.Write("[Titles] No products available in database");
			loadingAttempted = false;               
			return;
		}

		allTitles.clear();
		int loadedCount = 0;
		int itemCount = productDatabase->Products_New.size();

		for (int i = 0; i < itemCount; i++)
		{
			try {
				auto product = productDatabase->Products_New[i];
				if (!product || ShouldSkipTitle(product) || !IsTitleProduct(product))
					continue;

				GameTitle title;
				
				                      
				int realProductId = 0;
				try {
					realProductId = product->GetID();
				} catch (...) {}
				
				                                       
				if (realProductId == 0) {
					try {
						auto hashID = product->GetHashID();
						realProductId = *reinterpret_cast<int*>(&hashID);
					} catch (...) {}
				}
				
				                                
				if (realProductId == 0) {
					realProductId = i;
				}
				
				title.id = realProductId;

				                                      
				FString productLabel = product->Label;
				if (productLabel.c_str() && wcslen(productLabel.c_str()) > 0)
				{
					std::wstring wideStr(productLabel.c_str());
					                                        
					if (wideStr.length() > 256) {
						wideStr = wideStr.substr(0, 256);
					}
					title.displayName = std::string(wideStr.begin(), wideStr.end());
					
					                         
					title.category = GetTitleCategory(product);
					
					                                                          
					title.internalName = title.displayName;

					allTitles.push_back(title);
					loadedCount++;
				}
			}
			catch (...) {
				                                   
				continue;
			}
		}

		Console.Write("[Titles] Loaded " + std::to_string(loadedCount) + " titles from RLSDK database");
	}
	catch (const std::exception& e)
	{
		Console.Write("[Titles] Error loading titles: " + std::string(e.what()));
	}
	catch (...)
	{
		Console.Write("[Titles] Unknown error loading titles from database");
	}
}

void TitleComponent::OnCreate()
{
	                                                                        
	                                                                              
	                                                              
	Console.Write("[Titles] TitleComponent initialized - titles will load when needed");
}

void TitleComponent::OnDestroy() {}

UOnlineProduct_TA* TitleComponent::SpawnTitle(
	int titleId,
	int seriesid,
	int tradehold,
	bool log,
	const std::string& spawnMessage,
	bool animation
)
{
	FOnlineProductData productData;
	productData.ProductID = titleId;
	productData.SeriesID = seriesid;
	productData.InstanceID = GeneratePIID(titleId);
	productData.TradeHold = tradehold;
	productData.AddedTimestamp = GetTimestampLong();

	                                                         
	productData.Attributes = TArray<FOnlineProductAttribute>();

	Console.Write("[Titles] Attempting to spawn title ID: " + std::to_string(titleId) + 
		" with Series ID: " + std::to_string(productData.SeriesID));

	UOnlineProduct_TA* product = UOnlineProduct_TA::CreateOnlineProduct(productData);
	if (!product) {
		Console.Write("[Titles] Failed to create product - UOnlineProduct_TA::CreateOnlineProduct returned null");
		return nullptr;
	}

	Console.Write("[Titles] Product created successfully, attempting to spawn...");
	if (SpawnTitleData(product->InstanceOnlineProductData(), spawnMessage, animation))
		return product;
	Console.Write("[Titles] Failed to SpawnTitleData");
	return nullptr;
}

bool TitleComponent::SpawnTitleData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation)
{
	UGFxData_ContainerDrops_TA* containerDrops = Instances.GetInstanceOf<UGFxData_ContainerDrops_TA>();
	if (!containerDrops)
	{
		Console.Write("UGFxData_ContainerDrops_TA is null!");
		return false;
	}

	UOnlineProduct_TA* onlineProduct = containerDrops->CreateTempOnlineProduct(productData);
	if (!onlineProduct)
	{
		Console.Write("UOnlineProduct_TA is null!");
		return false;
	}

	                                                                                                                        
	static int hashId = 0;
	if (hashId == INT32_MAX)
		hashId = INT32_MIN;
	onlineProduct->CachedHash.Id = hashId++;

	USaveData_TA* saveData = Instances.GetSaveData();
	if (!saveData)
	{
		Console.Write("USaveData_TA is null!");
		return false;
	}

	std::wstring wideSpawnMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
	FString messageFstr = (spawnMessage.empty()) ? FString(L"") : FString(wideSpawnMsg.c_str());

	saveData->eventGiveOnlineProduct(onlineProduct, messageFstr,0.0f);
	if (saveData->OnlineProductSet)
	{
		saveData->OnlineProductSet->Add(onlineProduct);
	}

	if (animation)
	{
		saveData->GiveOnlineProductHelper(onlineProduct);
		saveData->OnNewOnlineProduct(onlineProduct, messageFstr);
		saveData->EventNewOnlineProduct(saveData, onlineProduct, messageFstr);
	}

	Console.Write("Successfully spawned title: " + (onlineProduct->ToJson().ToString()));

	return true;
}

FProductInstanceID TitleComponent::GeneratePIID(int64_t Product)
{
	long long newPIID = GetTimestampLong() * Product + static_cast<long long>(generatedPIIDs.size());
	generatedPIIDs.push_back(newPIID);
	return IntToProductInstanceID(newPIID);
}

FProductInstanceID TitleComponent::IntToProductInstanceID(int64_t Value)
{
	FProductInstanceID ID;
	ID.UpperBits = static_cast<uint64_t>(Value >> 32);
	ID.LowerBits = static_cast<uint64_t>(Value & 0xffffffff);
	return ID;
}

unsigned long long TitleComponent::GetTimestampLong()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void TitleComponent::EnsureTitlesLoaded()
{
	                                                             
	if (allTitles.empty()) {
		                                                
		auto productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (productDatabase && productDatabase->Products_New.data() && productDatabase->Products_New.size() > 0) {
			LoadTitles();
		}
	}
}

bool TitleComponent::ShouldSkipTitle(class UProduct_TA* product)
{
	if (!product)
		return true;

	                                        
	FString productLabel = product->Label;
	if (!productLabel.c_str()) return true;
	
	std::wstring wideStr(productLabel.c_str());
	if (wideStr.length() > 256) return true;                          
	
	std::string name = std::string(wideStr.begin(), wideStr.end());
	
	                                      
	if (name.empty() || name.find("None") == 0)
		return true;

	return false;
}

bool TitleComponent::IsTitleProduct(class UProduct_TA* product)
{
	if (!product)
		return false;

	try
	{
		auto slot = product->Slot;
		if (slot)
		{
			FString slotLabel = slot->Label;
			if (slotLabel.c_str())
			{
				std::wstring wideStr(slotLabel.c_str());
				std::string slotName = std::string(wideStr.begin(), wideStr.end());
				
				                                
				return (slotName == "Title" || slotName == "PlayerTitle" || 
						slotName.find("Title") != std::string::npos);
			}
		}
	}
	catch (...)
	{
		                                
	}

	                                               
	FString productLabel = product->Label;
	if (productLabel.c_str())
	{
		std::wstring wideStr(productLabel.c_str());
		std::string name = std::string(wideStr.begin(), wideStr.end());
		
		                        
		if (name.find("Title") != std::string::npos ||
			name.find("Champion") != std::string::npos ||
			name.find("Master") != std::string::npos ||
			name.find("Legend") != std::string::npos)
		{
			return true;
		}
	}

	return false;
}

std::string TitleComponent::GetTitleCategory(class UProduct_TA* product)
{
	if (!product)
		return "Unknown";

	try
	{
		auto slot = product->Slot;
		if (slot)
		{
			FString slotLabel = slot->Label;
			if (slotLabel.c_str())
			{
				std::wstring wideStr(slotLabel.c_str());
				return std::string(wideStr.begin(), wideStr.end());
			}
		}
	}
	catch (...)
	{
		                                
	}

	return "Title";
}

TitleComponent Titles;
