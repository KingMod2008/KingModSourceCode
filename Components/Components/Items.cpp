#include "Items.hpp"
#include <fstream>
#include <sstream>
#include <chrono>
#include <array>
#include <atomic>
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <windows.h>
#include <nlohmann/json.hpp>
#include "../Includes.hpp"
#include "../../Extensions/Extensions/Formatting.hpp"
#include "GUI.hpp"
#include "Main.hpp"
#include "Events.hpp"

namespace
{
	using json = nlohmann::json;
	namespace fs = std::filesystem;

	std::atomic<bool> g_autoLoadoutApplied{ false };
	std::atomic<bool> g_autoLoadoutQueued{ false };
	std::chrono::steady_clock::time_point g_lastAutoLoadoutAttempt{};
	std::chrono::steady_clock::time_point g_loadoutReadySince{};
	std::atomic<bool> g_cosmeticOverrideReapplyRequested{ false };
	ACar_TA* g_lastCosmeticOverrideCar = nullptr;
	int g_lastCosmeticOverrideTeam = -1;
	std::array<int, 32> g_equippedCosmeticOverrides = [] {
		std::array<int, 32> overrides{};
		overrides.fill(-1);
		return overrides;
	}();

	                                                                             
	                                                                  
	std::array<int, 32> g_itemPaintIds{};

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

	template <typename T>
	bool IsReadableObject(const T* object)
	{
		return object && reinterpret_cast<uintptr_t>(object) > 0x10000 &&
			IsReadableRange(object, sizeof(T));
	}

	template <typename T>
	bool IsSaneArray(const TArray<T>& values, int32_t maximumSize = 64)
	{
		const int32_t size = values.size();
		if (size < 0 || size > maximumSize || values.capacity() < size)
			return false;
		return size == 0 || (values.data() && IsReadableRange(values.data(), sizeof(T) * static_cast<size_t>(size)));
	}

	bool IsLoadoutSetReady(ULoadoutSet_TA* loadoutSet)
	{
		if (!IsReadableObject(loadoutSet))
			return false;

		for (int team = 0; team < 2; ++team)
		{
			ULoadout_TA* loadout = loadoutSet->Loadouts[team];
			if (!IsReadableObject(loadout) || !IsSaneArray(loadout->Products))
				return false;
		}
		return true;
	}

	std::string SanitizeLoadoutPresetName(const std::string& name)
	{
		std::string safe;
		safe.reserve((std::min)(name.size(), static_cast<size_t>(40)));
		for (unsigned char c : name)
		{
			if (std::isalnum(c) || c == '_' || c == '-' || c == ' ')
				safe.push_back(static_cast<char>(c));
		}
		return safe.empty() ? "Default" : safe;
	}

	fs::path LoadoutPresetDirectory()
	{
		                                                                  
		                                                                    
		char exePath[MAX_PATH] = {};
		fs::path directory = GetModuleFileNameA(NULL, exePath, MAX_PATH)
			? fs::path(exePath).parent_path() / "KingMod" / "LoadoutPresets"
			: fs::current_path() / "KingMod" / "LoadoutPresets";
		std::error_code error;
		fs::create_directories(directory, error);
		return directory;
	}

	fs::path ActiveLoadoutPresetPath()
	{
		return LoadoutPresetDirectory() / "active.json";
	}
}

ItemComponent::ItemComponent() : Component("GameState", "Tracks which game state the player is currently in.") { OnCreate(); }

ItemComponent::~ItemComponent() { OnDestroy(); }

void ItemComponent::LoadItems()
{
	                                    
	static bool loadingAttempted = false;
	if (loadingAttempted && !allItems.empty()) {
		return;                               
	}
	loadingAttempted = true;

	try
	{
		                                                
		static int attemptCount = 0;
		attemptCount++;
		
		if (attemptCount < 3) {
			Console.Write("[Items] Waiting for game initialization... (attempt " + std::to_string(attemptCount) + "/3)");
			loadingAttempted = false;               
			return;
		}

		                                      
		auto productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (!productDatabase) {
			Console.Write("[Items] ProductDatabase not available yet");
			loadingAttempted = false;               
			return;
		}

		                          
		if (!productDatabase->Products_New.data()) {
			Console.Write("[Items] Products array not initialized");
			loadingAttempted = false;               
			return;
		}

		                               
		if (productDatabase->Products_New.size() <= 0) {
			Console.Write("[Items] No products available in database");
			loadingAttempted = false;               
			return;
		}

		allItems.clear();
		int loadedCount = 0;
		int itemCount = productDatabase->Products_New.size();
		                                       

		for (int i = 0; i < itemCount; i++)
		{
			try {
				auto product = productDatabase->Products_New[i];
				if (!product || ShouldSkipProduct(product))
					continue;

				GameItem item;
				
				                                                                   
				                                                                  
				                                         
				int realProductId = 0;
				int productHashId = -1;
				try {
					realProductId = product->GetID();
				} catch (...) {}
				try {
					productHashId = product->GetHashID().Id;
				} catch (...) {}
				
				                                       
				if (realProductId == 0 && productHashId > 0)
					realProductId = productHashId;
				
				                                
				if (realProductId == 0) {
					realProductId = i;
				}
				
				item.id = realProductId;
				item.hashId = productHashId > 0 ? productHashId : realProductId;
				try {
					if (product->Slot)
						item.slotIndex = product->Slot->SlotIndex;
				}
				catch (...) {
					item.slotIndex = -1;
				}
				try {
					item.quality = static_cast<int>(product->Quality);
				}
				catch (...) {
					item.quality = -1;
				}
				try {
					item.paintable = product->IsPaintable();
				}
				catch (...) {
					item.paintable = false;
				}

				                                      
				FString productLabel = product->Label;
				if (productLabel.c_str() && wcslen(productLabel.c_str()) > 0)
				{
					std::wstring wideStr(productLabel.c_str());
					                                        
					if (wideStr.length() > 256) {
						wideStr = wideStr.substr(0, 256);
					}
					item.displayName = std::string(wideStr.begin(), wideStr.end());
					
					                         
					item.category = GetItemCategory(product);

					                                                                        
					                                                                   
					                                                                      
					                                                                       
					                                                                         
					                                                                       
					                                                                        
					                                                                       
					if (!item.paintable)
					{
						std::string paintCategory = item.category;
						std::transform(paintCategory.begin(), paintCategory.end(), paintCategory.begin(),
							[](unsigned char c) { return static_cast<char>(std::tolower(c)); });
						item.paintable =
							paintCategory == "body" ||
							paintCategory == "decal" || paintCategory == "skin" ||
							paintCategory == "wheels" || paintCategory == "wheel" ||
							paintCategory == "rocket boost" || paintCategory == "boost" ||
							paintCategory == "hat" || paintCategory == "topper" ||
							paintCategory == "antenna" ||
							paintCategory == "trail" || paintCategory == "supersonic trail" || paintCategory == "supersonictrail" ||
							paintCategory == "goal explosion" || paintCategory == "goalexplosion";
					}
					
					                                                          
					item.internalName = item.displayName;

					allItems.push_back(item);
					loadedCount++;
					
					                                 
					if (item.displayName == "Fennec") {
						Console.Write("[Items] Found Fennec with ID: " + std::to_string(item.id));
					}
				}
			}
			catch (...) {
				                                  
				continue;
			}
		}

		Console.Write("[Items] Loaded " + std::to_string(loadedCount) + " items from RLSDK database");
	}
	catch (const std::exception& e)
	{
		Console.Write("[Items] Error loading items: " + std::string(e.what()));
	}
	catch (...)
	{
		Console.Write("[Items] Unknown error loading items from database");
	}
}

void ItemComponent::OnCreate()
{
	                                                                       
	                                                                             
	Console.Write("[Items] ItemComponent initialized - items will load when needed");
}

void ItemComponent::OnDestroy() {}

UOnlineProduct_TA* ItemComponent::SpawnProduct(
	int item,
	int seriesid,
	int tradehold,
	bool log,
	const std::string& spawnMessage,
	bool animation
)
{
	FOnlineProductData productData;
	productData.ProductID = item;
	productData.SeriesID = seriesid;
	productData.InstanceID = GeneratePIID(item);
	productData.TradeHold = tradehold;
	productData.AddedTimestamp = GetTimestampLong();

	                                                         
	productData.Attributes = TArray<FOnlineProductAttribute>();

	Console.Write("[Items] Attempting to spawn item ID: " + std::to_string(item) + 
		" with Series ID: " + std::to_string(productData.SeriesID));

	UOnlineProduct_TA* product = UOnlineProduct_TA::CreateOnlineProduct(productData);
	if (!product) {
		Console.Write("[Items] Failed to create product - UOnlineProduct_TA::CreateOnlineProduct returned null");
		return nullptr;
	}

	Console.Write("[Items] Product created successfully, attempting to spawn...");
	if (SpawnProductData(product->InstanceOnlineProductData(), spawnMessage, animation))
	{
		GUIComponent::NotifyTradeUpSimulatorItemSpawned(item, 1, spawnMessage.empty() ? "Spawned Item" : spawnMessage);
		return product;
	}
	Console.Write("[Items] Failed to SpawnProductData");
	return nullptr;
}

bool ItemComponent::SpawnProductData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation)
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

	Console.Write("Successfully spawned product: " + (onlineProduct->ToJson().ToString()));

	return true;
}

FProductInstanceID ItemComponent::GeneratePIID(int64_t Product)
{
	long long newPIID = GetTimestampLong() * Product + static_cast<long long>(generatedPIIDs.size());
	generatedPIIDs.push_back(newPIID);
	return IntToProductInstanceID(newPIID);
}

FProductInstanceID ItemComponent::IntToProductInstanceID(int64_t Value)
{
	FProductInstanceID ID;
	ID.UpperBits = static_cast<uint64_t>(Value >> 32);
	ID.LowerBits = static_cast<uint64_t>(Value & 0xffffffff);
	return ID;
}

unsigned long long ItemComponent::GetTimestampLong()
{
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void ItemComponent::EnsureItemsLoaded()
{
	                                                            
	if (allItems.empty()) {
		                                               
		auto productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (productDatabase && productDatabase->Products_New.data() && productDatabase->Products_New.size() > 0) {
			LoadItems();
		}
	}
}

bool ItemComponent::ShouldSkipProduct(class UProduct_TA* product)
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

std::string ItemComponent::GetItemCategory(class UProduct_TA* product)
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

	return "Miscellaneous";
}

                                           
bool ItemComponent::SpawnCredits(int amount, bool isTournamentCredits, const std::string& spawnMessage, bool animation)
{
	if (isTournamentCredits) {
		return SpawnTournamentCredits(amount, spawnMessage, animation);
	} else {
		return SpawnNormalCredits(amount, spawnMessage, animation);
	}
}

bool ItemComponent::SpawnNormalCredits(int amount, const std::string& spawnMessage, bool animation)
{
	try {
		                                                        
		if (amount <= 0) {
			Console.Write("[Credits] Invalid amount: " + std::to_string(amount));
			return false;
		}
		if (amount > 10000) {
			Console.Write("[Credits] Amount too large (max 10000): " + std::to_string(amount));
			return false;
		}

		                                                            
		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Credits] USaveData_TA is null!");
			return false;
		}

		                                          
		UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
		if (!onlinePlayer) {
			Console.Write("[Credits] onlinePlayer is null!");
			return false;
		}
		Console.Write("[Credits] onlinePlayer found successfully");

		                                                        
		UWallet_TA* wallet = Instances.GetInstanceOf<UWallet_TA>();
		if (!wallet) {
			Console.Write("[Credits] Direct wallet access failed, trying onlinePlayer->Wallet");
			wallet = onlinePlayer->Wallet;
			if (!wallet) {
				Console.Write("[Credits] onlinePlayer->Wallet is also null!");
				return false;
			}
		}
		Console.Write("[Credits] wallet found successfully");

		                                               
		int32_t credID = wallet->RocketBucksCurrencyID;
		Console.Write("[Credits] currency id: " + std::to_string(credID));
		Console.Write("[Credits] currency quantity: " + std::to_string(amount));

		                                     
		FCurrency currency = wallet->GetCurrency(credID);
		currency.Amount += amount;                          
		currency.UpdatedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
		currency.bCanBeTraded = true;
		currency.TradeHold = 0;                        

		                                
		TArray<FCurrency> arr;
		arr.push_back(currency);

		                                               
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			if (wallet->Currencies[i].Id == credID) {
				int32_t oldAmount = wallet->Currencies[i].Amount;
				wallet->Currencies[i].Amount += amount;
				wallet->Currencies[i].UpdatedTimestamp = currency.UpdatedTimestamp;
				wallet->Currencies[i].bCanBeTraded = true;
				Console.Write("[Credits] Tournament credits updated: " + std::to_string(oldAmount) + " -> " + std::to_string(wallet->Currencies[i].Amount));
				break;
			}
		}

		                      
		std::wstring wideMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
		wallet->GiveCurrencyDrops(false, wideMsg.c_str(), arr);

		                                       
		try {
			wallet->EventWalletCurrencyUpdated(wallet, credID);
			wallet->EventWalletUpdated(wallet);
		} catch (...) {
			Console.Write("[Credits] Warning: Could not trigger wallet events");
		}

		Console.Write("[Credits] Currency given.");
		
		if (animation) {
			                    
			std::string notifMsg = "Spawned " + std::to_string(amount) + " Credits";
			Main.SpawnNotification("KingMod", notifMsg, 3);
		}

		return true;
	}
	catch (const std::exception& e) {
		Console.Write("[Credits] Error spawning normal credits: " + std::string(e.what()));
		return false;
	}
	catch (...) {
		Console.Write("[Credits] Unknown error spawning normal credits");
		return false;
	}
}

bool ItemComponent::SpawnTournamentCredits(int amount, const std::string& spawnMessage, bool animation)
{
	try {
		                   
		if (amount <= 0) {
			Console.Write("[Credits] Invalid amount (must be > 0): " + std::to_string(amount));
			return false;
		}
		if (amount > 10000) {
			Console.Write("[Credits] Amount too large (max 10000): " + std::to_string(amount));
			return false;
		}

		                                                            
		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Credits] USaveData_TA is null!");
			return false;
		}

		                                          
		UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
		if (!onlinePlayer) {
			Console.Write("[Credits] onlinePlayer is null!");
			return false;
		}
		Console.Write("[Credits] onlinePlayer found successfully");

		                                                        
		UWallet_TA* wallet = Instances.GetInstanceOf<UWallet_TA>();
		if (!wallet) {
			Console.Write("[Credits] Direct wallet access failed, trying onlinePlayer->Wallet");
			wallet = onlinePlayer->Wallet;
			if (!wallet) {
				Console.Write("[Credits] onlinePlayer->Wallet is also null!");
				return false;
			}
		}
		Console.Write("[Credits] wallet found successfully");

		                                                                   
		std::vector<int32_t> tournamentCurrencyIDs;
		
		                                                                         
		Console.Write("[Credits] Available currencies in wallet:");
		int32_t firstTournamentID = 0;
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			Console.Write("[Credits] Currency ID: " + std::to_string(wallet->Currencies[i].Id) + 
						  ", Amount: " + std::to_string(wallet->Currencies[i].Amount) + 
				", Type: " + std::to_string(*(uint8_t*)wallet->Currencies[i].Type));
			
			                                                                         
			if (firstTournamentID == 0 && wallet->Currencies[i].Id != wallet->RocketBucksCurrencyID && 
				wallet->Currencies[i].Id != 4 && 
				wallet->Currencies[i].Id != 5 && 
				wallet->Currencies[i].Id != 17 && 
				wallet->Currencies[i].Id > 0) {
				firstTournamentID = wallet->Currencies[i].Id;
				Console.Write("[Credits] Found first other tournament currency ID: " + std::to_string(firstTournamentID));
			}
		}
		
		                                    
		if (firstTournamentID == 0) {
			firstTournamentID = 6;               
			bool exists = false;
			for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
				if (wallet->Currencies[i].Id == firstTournamentID) {
					exists = true;
					break;
				}
			}
			if (!exists) {
				Console.Write("[Credits] Creating tournament currency ID: " + std::to_string(firstTournamentID));
				
				                            
				FCurrency newTournamentCurrency;
				memset(&newTournamentCurrency, 0, sizeof(newTournamentCurrency));
				newTournamentCurrency.Id = firstTournamentID;
				newTournamentCurrency.CurrencyID = firstTournamentID;
				newTournamentCurrency.Amount = 0;
				newTournamentCurrency.Type = ECurrency::Currency_Hard;                   
				newTournamentCurrency.bCanBeTraded = true;
				newTournamentCurrency.TradeHold = 0;
				wallet->Currencies.push_back(newTournamentCurrency);
				Console.Write("[Credits] Created new tournament currency entry with ID: " + std::to_string(firstTournamentID));
			}
		}
		tournamentCurrencyIDs.push_back(firstTournamentID);
		
		                        
		int32_t tCreditsID = 17;
		bool tCreditsExists = false;
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			if (wallet->Currencies[i].Id == tCreditsID) {
				tCreditsExists = true;
				break;
			}
		}
		if (!tCreditsExists) {
			Console.Write("[Credits] Creating T-Credits currency ID: " + std::to_string(tCreditsID));
			
			                         
			FCurrency newTCredits;
			memset(&newTCredits, 0, sizeof(newTCredits));
			newTCredits.Id = tCreditsID;
			newTCredits.CurrencyID = tCreditsID;
			newTCredits.Amount = 0;
			newTCredits.Type = ECurrency::Currency_Hard;                   
			newTCredits.bCanBeTraded = true;
			newTCredits.TradeHold = 0;
			wallet->Currencies.push_back(newTCredits);
			Console.Write("[Credits] Created T-Credits currency entry with ID: " + std::to_string(tCreditsID));
		}
		tournamentCurrencyIDs.push_back(tCreditsID);
		
		Console.Write("[Credits] Spawning to " + std::to_string(tournamentCurrencyIDs.size()) + " tournament currencies");
		
		                                   
		TArray<FCurrency> allCurrencies;
		for (int32_t credID : tournamentCurrencyIDs) {
			Console.Write("[Credits] Processing currency id: " + std::to_string(credID));
			Console.Write("[Credits] currency quantity: " + std::to_string(amount));

			                                     
			FCurrency currency = wallet->GetCurrency(credID);
			currency.Amount += amount;                          
			currency.UpdatedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
			currency.bCanBeTraded = true;
			currency.TradeHold = 0;                        

			                                     
			allCurrencies.push_back(currency);

			                                               
			for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
				if (wallet->Currencies[i].Id == credID) {
					int32_t oldAmount = wallet->Currencies[i].Amount;
					wallet->Currencies[i].Amount += amount;
					wallet->Currencies[i].UpdatedTimestamp = currency.UpdatedTimestamp;
					wallet->Currencies[i].bCanBeTraded = true;
					std::string currencyName = (credID == 17) ? "T-Credits" : "Tournament currency " + std::to_string(credID);
					Console.Write("[Credits] " + currencyName + " updated: " + std::to_string(oldAmount) + " -> " + std::to_string(wallet->Currencies[i].Amount));
					break;
				}
			}

			                                          
			try {
				wallet->EventWalletCurrencyUpdated(wallet, credID);
			} catch (...) {
				Console.Write("[Credits] Warning: Could not trigger wallet event for currency " + std::to_string(credID));
			}
		}

		                                  
		std::wstring wideMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
		wallet->GiveCurrencyDrops(false, wideMsg.c_str(), allCurrencies);

		                                
		try {
			wallet->EventWalletUpdated(wallet);
		} catch (...) {
			Console.Write("[Credits] Warning: Could not trigger general wallet update");
		}

		                            
		std::string notifMsg = "Spawned " + std::to_string(amount) + " tournament credits to " + std::to_string(tournamentCurrencyIDs.size()) + " currencies!";
		Main.SpawnNotification("KingMod", notifMsg, 3);

		return true;
	}
	catch (const std::exception& e) {
		Console.Write("[Credits] Error spawning tournament credits: " + std::string(e.what()));
		return false;
	}
	catch (...) {
		Console.Write("[Credits] Unknown error spawning tournament credits");
		return false;
	}
}

                                            
bool ItemComponent::SpawnSpecialCredits(int amount, const std::string& spawnMessage, bool animation)
{
	try {
		                   
		if (amount <= 0) {
			Console.Write("[Credits] Invalid amount (must be > 0): " + std::to_string(amount));
			return false;
		}
		if (amount > 10000) {
			Console.Write("[Credits] Amount too large (max 10000): " + std::to_string(amount));
			return false;
		}

		                                                            
		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Credits] USaveData_TA is null!");
			return false;
		}

		UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
		if (!onlinePlayer) {
			Console.Write("[Credits] onlinePlayer is null!");
			return false;
		}

		                                                        
		UWallet_TA* wallet = Instances.GetInstanceOf<UWallet_TA>();
		if (!wallet) {
			Console.Write("[Credits] Direct wallet access failed, trying onlinePlayer->Wallet");
			wallet = onlinePlayer->Wallet;
			if (!wallet) {
				Console.Write("[Credits] onlinePlayer->Wallet is also null!");
				return false;
			}
		}

		int32_t credID = 13;                      
		Console.Write("[Credits] Processing Special Credits (ID 13)");

		                                     
		FCurrency currency = wallet->GetCurrency(credID);
		currency.Amount += amount;
		currency.UpdatedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
		currency.bCanBeTraded = true;
		currency.TradeHold = 0;

		                                
		TArray<FCurrency> arr;
		arr.push_back(currency);

		                                               
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			if (wallet->Currencies[i].Id == credID) {
				int32_t oldAmount = wallet->Currencies[i].Amount;
				wallet->Currencies[i].Amount += amount;
				wallet->Currencies[i].UpdatedTimestamp = currency.UpdatedTimestamp;
				wallet->Currencies[i].bCanBeTraded = true;
				Console.Write("[Credits] Special Credits updated: " + std::to_string(oldAmount) + " -> " + std::to_string(wallet->Currencies[i].Amount));
				break;
			}
		}

		                      
		std::wstring wideMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
		wallet->GiveCurrencyDrops(false, wideMsg.c_str(), arr);

		                        
		try {
			wallet->EventWalletCurrencyUpdated(wallet, credID);
			wallet->EventWalletUpdated(wallet);
		} catch (...) {
			Console.Write("[Credits] Warning: Could not trigger wallet events");
		}

		                            
		std::string notifMsg = "Spawned " + std::to_string(amount) + " Special Credits!";
		Main.SpawnNotification("KingMod", notifMsg, 3);

		return true;
	}
	catch (const std::exception& e) {
		Console.Write("[Credits] Error spawning Special Credits: " + std::string(e.what()));
		return false;
	}
	catch (...) {
		Console.Write("[Credits] Unknown error spawning Special Credits");
		return false;
	}
}

                                       
bool ItemComponent::SpawnEsportJeton(int amount, const std::string& spawnMessage, bool animation)
{
	try {
		                   
		if (amount <= 0) {
			Console.Write("[Credits] Invalid amount (must be > 0): " + std::to_string(amount));
			return false;
		}
		if (amount > 10000) {
			Console.Write("[Credits] Amount too large (max 10000): " + std::to_string(amount));
			return false;
		}

		                                                            
		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Credits] USaveData_TA is null!");
			return false;
		}

		UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
		if (!onlinePlayer) {
			Console.Write("[Credits] onlinePlayer is null!");
			return false;
		}

		                                                        
		UWallet_TA* wallet = Instances.GetInstanceOf<UWallet_TA>();
		if (!wallet) {
			Console.Write("[Credits] Direct wallet access failed, trying onlinePlayer->Wallet");
			wallet = onlinePlayer->Wallet;
			if (!wallet) {
				Console.Write("[Credits] onlinePlayer->Wallet is also null!");
				return false;
			}
		}

		int32_t credID = 8;                  
		Console.Write("[Credits] Processing EsportJeton (ID 8)");

		                                     
		FCurrency currency = wallet->GetCurrency(credID);
		currency.Amount += amount;
		currency.UpdatedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
		currency.bCanBeTraded = true;
		currency.TradeHold = 0;

		                                
		TArray<FCurrency> arr;
		arr.push_back(currency);

		                                               
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			if (wallet->Currencies[i].Id == credID) {
				int32_t oldAmount = wallet->Currencies[i].Amount;
				wallet->Currencies[i].Amount += amount;
				wallet->Currencies[i].UpdatedTimestamp = currency.UpdatedTimestamp;
				wallet->Currencies[i].bCanBeTraded = true;
				Console.Write("[Credits] EsportJeton updated: " + std::to_string(oldAmount) + " -> " + std::to_string(wallet->Currencies[i].Amount));
				break;
			}
		}

		                      
		std::wstring wideMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
		wallet->GiveCurrencyDrops(false, wideMsg.c_str(), arr);

		                        
		try {
			wallet->EventWalletCurrencyUpdated(wallet, credID);
			wallet->EventWalletUpdated(wallet);
		} catch (...) {
			Console.Write("[Credits] Warning: Could not trigger wallet events");
		}

		                            
		std::string notifMsg = "Spawned " + std::to_string(amount) + " EsportJeton!";
		Main.SpawnNotification("KingMod", notifMsg, 3);

		return true;
	}
	catch (const std::exception& e) {
		Console.Write("[Credits] Error spawning EsportJeton: " + std::string(e.what()));
		return false;
	}
	catch (...) {
		Console.Write("[Credits] Unknown error spawning EsportJeton");
		return false;
	}
}

                                    
bool ItemComponent::SpawnTogrogs(int amount, const std::string& spawnMessage, bool animation)
{
	try {
		                   
		if (amount <= 0) {
			Console.Write("[Credits] Invalid amount (must be > 0): " + std::to_string(amount));
			return false;
		}
		if (amount > 10000) {
			Console.Write("[Credits] Amount too large (max 10000): " + std::to_string(amount));
			return false;
		}

		                                                            
		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Credits] USaveData_TA is null!");
			return false;
		}

		UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
		if (!onlinePlayer) {
			Console.Write("[Credits] onlinePlayer is null!");
			return false;
		}

		                                                        
		UWallet_TA* wallet = Instances.GetInstanceOf<UWallet_TA>();
		if (!wallet) {
			Console.Write("[Credits] Direct wallet access failed, trying onlinePlayer->Wallet");
			wallet = onlinePlayer->Wallet;
			if (!wallet) {
				Console.Write("[Credits] onlinePlayer->Wallet is also null!");
				return false;
			}
		}

		int32_t credID = 35;              
		Console.Write("[Credits] Processing Togrogs (ID 35)");

		                                     
		FCurrency currency = wallet->GetCurrency(credID);
		currency.Amount += amount;
		currency.UpdatedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();
		currency.bCanBeTraded = true;
		currency.TradeHold = 0;

		                                
		TArray<FCurrency> arr;
		arr.push_back(currency);

		                                               
		for (int32_t i = 0; i < wallet->Currencies.size(); i++) {
			if (wallet->Currencies[i].Id == credID) {
				int32_t oldAmount = wallet->Currencies[i].Amount;
				wallet->Currencies[i].Amount += amount;
				wallet->Currencies[i].UpdatedTimestamp = currency.UpdatedTimestamp;
				wallet->Currencies[i].bCanBeTraded = true;
				Console.Write("[Credits] Togrogs updated: " + std::to_string(oldAmount) + " -> " + std::to_string(wallet->Currencies[i].Amount));
				break;
			}
		}

		                      
		std::wstring wideMsg = std::wstring(spawnMessage.begin(), spawnMessage.end());
		wallet->GiveCurrencyDrops(false, wideMsg.c_str(), arr);

		                        
		try {
			wallet->EventWalletCurrencyUpdated(wallet, credID);
			wallet->EventWalletUpdated(wallet);
		} catch (...) {
			Console.Write("[Credits] Warning: Could not trigger wallet events");
		}

		                            
		std::string notifMsg = "Spawned " + std::to_string(amount) + " Togrogs!";
		Main.SpawnNotification("KingMod", notifMsg, 3);

		return true;
	}
	catch (const std::exception& e) {
		Console.Write("[Credits] Error spawning Togrogs: " + std::string(e.what()));
		return false;
	}
	catch (...) {
		Console.Write("[Credits] Unknown error spawning Togrogs");
		return false;
	}
}

                                                                                
void ItemComponent::CreateAndSpawnProduct(int productId, int quality, int paintId, int certId, int seriesId)
{
	try {
		Console.Write("[Items] CreateAndSpawnProduct called - ProductID: " + std::to_string(productId) + 
					  ", Quality: " + std::to_string(quality) + ", Paint: " + std::to_string(paintId) + 
					  ", Cert: " + std::to_string(certId) + ", Series: " + std::to_string(seriesId));

		USaveData_TA* saveData = Instances.GetSaveData();
		if (!saveData) {
			Console.Write("[Items] SaveData is null!");
			return;
		}

		                                                                      
		FOnlineProductData productData;
		productData.ProductID = productId;
		productData.InstanceID = GeneratePIID(productId);
		productData.SeriesID = seriesId;
		productData.TradeHold = 0;                                        
		productData.AddedTimestamp = std::chrono::system_clock::now().time_since_epoch().count();

		                                                          
		                                                  
		std::wstring qualityName;
		int finalQuality = quality;                                                 
		
		switch (finalQuality) {
			case 0: qualityName = L"None"; break;
			case 1: qualityName = L"Uncommon"; break;
			case 2: qualityName = L"Rare"; break;
			case 3: qualityName = L"VeryRare"; break;
			case 4: qualityName = L"Import"; break;
			case 5: qualityName = L"Exotic"; break;
			case 6: qualityName = L"BlackMarket"; break;
			case 7: qualityName = L"Premium"; break;
			case 8: qualityName = L"Limited"; break;
			case 9: qualityName = L"Legacy"; break;
			default: qualityName = L"None"; break;
		}
		
		                                                                
		std::vector<std::wstring> qualityKeys = {
			L"Quality", L"ProductQuality", L"ItemQuality", L"Rarity", 
			L"QualityID", L"ProductQualityID", L"ItemQualityID", L"RarityID",
			L"QualityLevel", L"ProductQualityLevel", L"ItemRarity", L"ProductRarity"
		};
		
		for (const auto& key : qualityKeys) {
			                     
			FOnlineProductAttribute qualityAttr;
			qualityAttr.Key = FName(key.c_str());
			qualityAttr.Value = FString(qualityName.c_str());
			productData.Attributes.push_back(qualityAttr);
			
			                      
			FOnlineProductAttribute qualityAttrNum;
			qualityAttrNum.Key = FName(key.c_str());
			qualityAttrNum.Value = Format::ToFString(std::to_string(finalQuality));
			productData.Attributes.push_back(qualityAttrNum);
		}
		
		Console.Write("[Items] Added enhanced Quality attributes: " + std::to_string(finalQuality) + " (" + std::string(qualityName.begin(), qualityName.end()) + ")");

		                                                                      
		                                                                   
		                                                                       
		                                                                       
		                                                                     
		                                                                      
		                                                          
		                                                                  
		                                                                     
		static const int kMenuPaintToGamePaint[18] = {
			0,            
			1,               
			2,            
			7,                    
			9,            
			5,              
			6,                    
			13,              
			12,                     
			11,           
			10,             
			8,              
			4,                
			3,             
			14,           
			15,                
			16,                 
			17            
		};
		if (paintId > 0 && paintId < 18) {
			int mappedPaint = kMenuPaintToGamePaint[paintId];
			Console.Write("[Items] Paint remap: menu " + std::to_string(paintId) + " -> game " + std::to_string(mappedPaint));
			paintId = mappedPaint;
		}

		                                                                     
		if (paintId > 0 && paintId < 18) {
			std::wstring paintName;
			switch (paintId) {
				case 1: paintName = L"Crimson"; break;                            
				case 2: paintName = L"Lime"; break;                            
				case 3: paintName = L"ForestGreen"; break;                            
				case 4: paintName = L"Pink"; break;                            
				case 5: paintName = L"Cobalt"; break;                            
				case 6: paintName = L"BurntSienna"; break;                            
				case 7: paintName = L"Saffron"; break;                            
				case 8: paintName = L"TitaniumWhite"; break;                            
				case 9: paintName = L"Grey"; break;                            
				case 10: paintName = L"Orange"; break;                            
				case 11: paintName = L"Purple"; break;                            
				case 12: paintName = L"SkyBlue"; break;                            
				case 13: paintName = L"Black"; break;                            
				case 14: paintName = L"Gold"; break;                            
				case 15: paintName = L"RoseGold"; break;                            
				case 16: paintName = L"WhiteGold"; break;                            
				case 17: paintName = L"Onyx"; break;                            
				default: paintName = L"None"; break;
			}
			
			                                                                
			FOnlineProductAttribute paintAttr;
			paintAttr.Key = FName(L"Painted");
			paintAttr.Value = Format::ToFString(std::to_string(paintId));                       
			productData.Attributes.push_back(paintAttr);
			
			Console.Write("[Items] FORCED Paint override: " + std::to_string(paintId) + " (" + std::string(paintName.begin(), paintName.end()) + ")");
		}

		                                                                   
		if (certId > 0 && certId < 16) {
			std::wstring certName;
			switch (certId) {
				case 1: certName = L"Aviator"; break;                                 
				case 2: certName = L"Playmaker"; break;                                 
				case 3: certName = L"Show-off"; break;                                
				case 4: certName = L"Acrobat"; break;                                 
				case 5: certName = L"Tactician"; break;                                 
				case 6: certName = L"Sweeper"; break;                                 
				case 7: certName = L"Guardian"; break;                                 
				case 8: certName = L"Scorer"; break;                                 
				case 9: certName = L"Juggler"; break;                                 
				case 10: certName = L"Sniper"; break;                                 
				case 11: certName = L"Paragon"; break;                                  
				case 12: certName = L"Goalkeeper"; break;                                  
				case 13: certName = L"Striker"; break;                                  
				case 14: certName = L"Turtle"; break;                                  
				case 15: certName = L"Victor"; break;                                  
				default: certName = L"Striker"; break;
			}
			
			                                                                        
			FOnlineProductAttribute certAttr;
			certAttr.Key = FName(L"Certified");
			certAttr.Value = Format::ToFString(std::to_string(certId));                       
			productData.Attributes.push_back(certAttr);
			
			Console.Write("[Items] FORCED Cert override: " + std::to_string(certId) + " (" + std::string(certName.begin(), certName.end()) + ")");
		}

		                                               
		productData.SeriesID = 0;
		
		                                                                         
		                                                                           
		                                                                            
		                                                                      
		                                                                            
		                                                                          
		                                                                        
		                                                                            
		UOnlineProduct_TA* onlineProduct = saveData->GiveOnlineProductDataNoNotify(productData);
		if (onlineProduct) {
			                                                                   
			                                                                       
			                                                            
			if (paintId > 0 && paintId < 18) {
				try {
					if (UClass* paintedClass = UProductAttribute_Painted_TA::StaticClass())
						onlineProduct->RemoveAttributes(paintedClass);

					if (UProductAttribute_Painted_TA* painted = UProductAttribute_Painted_TA::CreateInstance(paintId)) {
						painted->PaintID = paintId;
						onlineProduct->AddAttribute(painted);
						Console.Write("[Items] Attached painted thumbnail attribute (PaintID " + std::to_string(paintId) + ")");
					}
				}
				catch (...) {
					Console.Write("[Items] Warning: could not attach painted thumbnail attribute");
				}
			}

			                                                               
			try {
				if (UGFxData_ProductFilter_TA* filter = Instances.GetInstanceOf<UGFxData_ProductFilter_TA>())
					filter->HandleNewProductUnlocked(saveData, onlineProduct, FString());
			}
			catch (...) {
				Console.Write("[Items] Warning: could not raise unlock popup");
			}

			Console.Write("[Items] Successfully spawned item with enhanced attributes!");
			GUIComponent::NotifyTradeUpSimulatorItemSpawned(productId, 1, "Spawned Item");
			Main.SpawnNotification("KingMod", "Spawned item with attributes!", 3);
		} else {
			Console.Write("[Items] Failed to spawn item - GiveOnlineProductDataNoNotify returned null");
		}

	} catch (const std::exception& e) {
		Console.Write("[Items] Exception in CreateAndSpawnProduct: " + std::string(e.what()));
	} catch (...) {
		Console.Write("[Items] Unknown exception in CreateAndSpawnProduct");
	}
}

namespace
{
	ULoadoutSet_TA* GetLocalEquippedLoadoutSet(UProfile_TA** outProfile = nullptr)
	{
		if (outProfile)
			*outProfile = nullptr;

		                                                                    
		                                                                       
		                                                                          
		ULocalPlayer* rawLocalPlayer = Instances.IULocalPlayer();
		if (IsReadableObject(rawLocalPlayer))
		{
			auto* localPlayer = reinterpret_cast<ULocalPlayer_TA*>(rawLocalPlayer);
			if (!IsReadableObject(localPlayer))
				return nullptr;

			UProfile_TA* profile = localPlayer->Profile;
			if (IsReadableObject(profile) && IsReadableObject(profile->LoadoutSave) &&
				IsLoadoutSetReady(profile->LoadoutSave->EquippedLoadoutSet))
			{
				if (outProfile)
					*outProfile = profile;
				return profile->LoadoutSave->EquippedLoadoutSet;
			}
		}

		                                                                         
		                                                                       
		                                                                   
		return nullptr;
	}

	void RefreshGarageLoadoutPreview(UProfile_TA* profile)
	{
		if (!IsReadableObject(profile))
			return;
		try
		{
			UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
			if (IsReadableObject(garage) && IsReadableObject(garage->PreviewActor))
				garage->PreviewActor->RefreshLoadout(profile);
		}
		catch (...) {}
	}

	bool HasEquippedCosmeticOverrides()
	{
		return std::any_of(g_equippedCosmeticOverrides.begin(), g_equippedCosmeticOverrides.end(),
			[](int productId) { return productId > 0; });
	}

	bool RequestProductAssetLoad(int productId)
	{
		                                                                     
		                                                                      
		                                                          
		UProductDatabase_TA* productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
		if (IsReadableObject(productDatabase))
		{
			UProduct_TA* product = productDatabase->GetProduct(productId);
			if (!IsReadableObject(product))
				return false;

			if (IsReadableObject(productDatabase->LoadAsset(productId)))
				return true;
		}

		UProductAssetLoader_TA* loader = UProductAssetLoader_TA::GetInstance();
		return IsReadableObject(loader) && IsReadableObject(loader->LoadAsset(productId));
	}

	UProductAsset_TA* GetLoadedProductAsset(int productId)
	{
		if (productId <= 0)
			return nullptr;

		try
		{
			if (UProductDatabase_TA* productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>())
			{
				if (IsReadableObject(productDatabase))
				{
					if (UProductAsset_TA* asset = productDatabase->LoadAsset(productId))
						return asset;
				}
			}

			if (UProductAssetLoader_TA* loader = UProductAssetLoader_TA::GetInstance())
				return loader->LoadAsset(productId);
		}
		catch (...) {}
		return nullptr;
	}

	struct WheelHandlingSnapshot
	{
		UWheel_TA* wheel = nullptr;
		float SteerFactor = 0.0f;
		float WheelRadius = 0.0f;
		float SuspensionStiffness = 0.0f;
		float SuspensionDampingCompression = 0.0f;
		float SuspensionDampingRelaxation = 0.0f;
		float SuspensionTravel = 0.0f;
		float SuspensionMaxRaise = 0.0f;
		float ContactForceDistance = 0.0f;
		float PushForceConstant = 0.0f;
		float AerialThrottleToVelocityFactor = 0.0f;
		float AerialAccelerationFactor = 0.0f;
	};

	struct VehicleHandlingSnapshot
	{
		bool valid = false;
		FVector collisionOffset{};
		FVector collisionExtent{};
		float replicatedCarScale = 1.0f;
		float maxLinearSpeedScale = 1.0f;
		float addedBallForce = 0.0f;
		float addedCarForce = 0.0f;
		float maxTimeForDodge = 0.0f;
		int maxNumJumps = 0;

		UVehicleSim_TA* sim = nullptr;
		float driveTorque = 0.0f;
		float brakeTorque = 0.0f;
		FInputRate handbrakeRate{};
		float stopThreshold = 0.0f;
		float idleBrakeFactor = 0.0f;
		float oppositeBrakeFactor = 0.0f;
		bool useAckermann = false;
		float steeringSensitivity = 0.0f;
		float tireFrictionScale = 1.0f;
		std::array<WheelHandlingSnapshot, 8> wheels{};
		int wheelCount = 0;

		ACarComponent_AirControl_TA* air = nullptr;
		FRotator airTorque{};
		FRotator airDamping{};
		float airTorqueScalar = 0.0f;
		float airDampingScalar = 0.0f;
		float throttleForce = 0.0f;
		float airControlSensitivity = 0.0f;

		ACarComponent_Boost_TA* boost = nullptr;
		float boostConsumptionRate = 0.0f;
		float maxBoostAmount = 0.0f;
		float boostModifier = 0.0f;
		float boostForce = 0.0f;
		float minBoostTime = 0.0f;
		float rechargeRate = 0.0f;
		float rechargeDelay = 0.0f;

		ACarComponent_Dodge_TA* dodge = nullptr;
		float sideDodgeImpulse = 0.0f;
		float forwardDodgeImpulse = 0.0f;
		float backwardDodgeImpulse = 0.0f;
		float sideDodgeTorque = 0.0f;
		float forwardDodgeTorque = 0.0f;
		float dodgeImpulseScale = 0.0f;
		float dodgeTorqueScale = 0.0f;

		ACarComponent_Jump_TA* jump = nullptr;
		float minJumpTime = 0.0f;
		float jumpImpulse = 0.0f;
		float jumpForce = 0.0f;
		float jumpForceTime = 0.0f;

		ACarComponent_DoubleJump_TA* doubleJump = nullptr;
		float doubleJumpImpulse = 0.0f;
		float doubleJumpScale = 0.0f;
	};

	bool CaptureVehicleHandling(ACar_TA* car, VehicleHandlingSnapshot& out)
	{
		if (!IsReadableObject(car))
			return false;

		try
		{
			out.collisionOffset = car->LocalCollisionOffset;
			out.collisionExtent = car->LocalCollisionExtent;
			out.replicatedCarScale = car->ReplicatedCarScale;
			out.maxLinearSpeedScale = car->ReplicatedCarMaxLinearSpeedScale;
			out.addedBallForce = car->AddedBallForceMultiplier;
			out.addedCarForce = car->AddedCarForceMultiplier;
			out.maxTimeForDodge = car->MaxTimeForDodge;
			out.maxNumJumps = car->MaxNumJumps;

			out.sim = car->VehicleSim;
			if (IsReadableObject(out.sim))
			{
				out.driveTorque = out.sim->DriveTorque;
				out.brakeTorque = out.sim->BrakeTorque;
				out.handbrakeRate = out.sim->HandbrakeRate;
				out.stopThreshold = out.sim->StopThreshold;
				out.idleBrakeFactor = out.sim->IdleBrakeFactor;
				out.oppositeBrakeFactor = out.sim->OppositeBrakeFactor;
				out.useAckermann = out.sim->bUseAckermannSteering != 0;
				out.steeringSensitivity = out.sim->SteeringSensitivity;
				out.tireFrictionScale = out.sim->TireFrictionScale;

				if (IsSaneArray(out.sim->Wheels, 8))
				{
					out.wheelCount = (std::min)(out.sim->Wheels.size(), 8);
					for (int i = 0; i < out.wheelCount; ++i)
					{
						UWheel_TA* wheel = out.sim->Wheels[i];
						if (!IsReadableObject(wheel)) continue;
						auto& w = out.wheels[i];
						w.wheel = wheel;
						w.SteerFactor = wheel->SteerFactor;
						w.WheelRadius = wheel->WheelRadius;
						w.SuspensionStiffness = wheel->SuspensionStiffness;
						w.SuspensionDampingCompression = wheel->SuspensionDampingCompression;
						w.SuspensionDampingRelaxation = wheel->SuspensionDampingRelaxation;
						w.SuspensionTravel = wheel->SuspensionTravel;
						w.SuspensionMaxRaise = wheel->SuspensionMaxRaise;
						w.ContactForceDistance = wheel->ContactForceDistance;
						w.PushForceConstant = wheel->PushForceConstant;
						w.AerialThrottleToVelocityFactor = wheel->AerialThrottleToVelocityFactor;
						w.AerialAccelerationFactor = wheel->AerialAccelerationFactor;
					}
				}
			}

			out.air = car->AirControlComponent;
			if (IsReadableObject(out.air))
			{
				out.airTorque = out.air->AirTorque;
				out.airDamping = out.air->AirDamping;
				out.airTorqueScalar = out.air->AirTorqueScalar;
				out.airDampingScalar = out.air->AirDampingScalar;
				out.throttleForce = out.air->ThrottleForce;
				out.airControlSensitivity = out.air->AirControlSensitivity;
			}

			out.boost = car->BoostComponent;
			if (IsReadableObject(out.boost))
			{
				out.boostConsumptionRate = out.boost->BoostConsumptionRate;
				out.maxBoostAmount = out.boost->MaxBoostAmount;
				out.boostModifier = out.boost->BoostModifier;
				out.boostForce = out.boost->BoostForce;
				out.minBoostTime = out.boost->MinBoostTime;
				out.rechargeRate = out.boost->RechargeRate;
				out.rechargeDelay = out.boost->RechargeDelay;
			}

			out.dodge = car->DodgeComponent;
			if (IsReadableObject(out.dodge))
			{
				out.sideDodgeImpulse = out.dodge->SideDodgeImpulse;
				out.forwardDodgeImpulse = out.dodge->ForwardDodgeImpulse;
				out.backwardDodgeImpulse = out.dodge->BackwardDodgeImpulse;
				out.sideDodgeTorque = out.dodge->SideDodgeTorque;
				out.forwardDodgeTorque = out.dodge->ForwardDodgeTorque;
				out.dodgeImpulseScale = out.dodge->DodgeImpulseScale;
				out.dodgeTorqueScale = out.dodge->DodgeTorqueScale;
			}

			out.jump = car->JumpComponent;
			if (IsReadableObject(out.jump))
			{
				out.minJumpTime = out.jump->MinJumpTime;
				out.jumpImpulse = out.jump->JumpImpulse;
				out.jumpForce = out.jump->JumpForce;
				out.jumpForceTime = out.jump->JumpForceTime;
			}

			out.doubleJump = car->DoubleJumpComponent;
			if (IsReadableObject(out.doubleJump))
			{
				out.doubleJumpImpulse = out.doubleJump->JumpImpulse;
				out.doubleJumpScale = out.doubleJump->ImpulseScale;
			}

			out.valid = true;
			return true;
		}
		catch (...) {}
		return false;
	}

	void RestoreVehicleHandling(ACar_TA* car, const VehicleHandlingSnapshot& in)
	{
		if (!in.valid || !IsReadableObject(car))
			return;
		try
		{
			car->LocalCollisionOffset = in.collisionOffset;
			car->LocalCollisionExtent = in.collisionExtent;
			car->ReplicatedCarScale = in.replicatedCarScale;
			car->ReplicatedCarMaxLinearSpeedScale = in.maxLinearSpeedScale;
			car->AddedBallForceMultiplier = in.addedBallForce;
			car->AddedCarForceMultiplier = in.addedCarForce;
			car->MaxTimeForDodge = in.maxTimeForDodge;
			car->MaxNumJumps = in.maxNumJumps;

			if (IsReadableObject(in.sim))
			{
				in.sim->DriveTorque = in.driveTorque;
				in.sim->BrakeTorque = in.brakeTorque;
				in.sim->HandbrakeRate = in.handbrakeRate;
				in.sim->StopThreshold = in.stopThreshold;
				in.sim->IdleBrakeFactor = in.idleBrakeFactor;
				in.sim->OppositeBrakeFactor = in.oppositeBrakeFactor;
				in.sim->bUseAckermannSteering = in.useAckermann ? 1 : 0;
				in.sim->SteeringSensitivity = in.steeringSensitivity;
				in.sim->TireFrictionScale = in.tireFrictionScale;
			}

			for (int i = 0; i < in.wheelCount; ++i)
			{
				const auto& w = in.wheels[i];
				if (!IsReadableObject(w.wheel)) continue;
				w.wheel->SteerFactor = w.SteerFactor;
				w.wheel->WheelRadius = w.WheelRadius;
				w.wheel->SuspensionStiffness = w.SuspensionStiffness;
				w.wheel->SuspensionDampingCompression = w.SuspensionDampingCompression;
				w.wheel->SuspensionDampingRelaxation = w.SuspensionDampingRelaxation;
				w.wheel->SuspensionTravel = w.SuspensionTravel;
				w.wheel->SuspensionMaxRaise = w.SuspensionMaxRaise;
				w.wheel->ContactForceDistance = w.ContactForceDistance;
				w.wheel->PushForceConstant = w.PushForceConstant;
				w.wheel->AerialThrottleToVelocityFactor = w.AerialThrottleToVelocityFactor;
				w.wheel->AerialAccelerationFactor = w.AerialAccelerationFactor;
			}

			if (IsReadableObject(in.air))
			{
				in.air->AirTorque = in.airTorque;
				in.air->AirDamping = in.airDamping;
				in.air->AirTorqueScalar = in.airTorqueScalar;
				in.air->AirDampingScalar = in.airDampingScalar;
				in.air->ThrottleForce = in.throttleForce;
				in.air->AirControlSensitivity = in.airControlSensitivity;
			}
			if (IsReadableObject(in.boost))
			{
				in.boost->BoostConsumptionRate = in.boostConsumptionRate;
				in.boost->MaxBoostAmount = in.maxBoostAmount;
				in.boost->BoostModifier = in.boostModifier;
				in.boost->BoostForce = in.boostForce;
				in.boost->MinBoostTime = in.minBoostTime;
				in.boost->RechargeRate = in.rechargeRate;
				in.boost->RechargeDelay = in.rechargeDelay;
			}
			if (IsReadableObject(in.dodge))
			{
				in.dodge->SideDodgeImpulse = in.sideDodgeImpulse;
				in.dodge->ForwardDodgeImpulse = in.forwardDodgeImpulse;
				in.dodge->BackwardDodgeImpulse = in.backwardDodgeImpulse;
				in.dodge->SideDodgeTorque = in.sideDodgeTorque;
				in.dodge->ForwardDodgeTorque = in.forwardDodgeTorque;
				in.dodge->DodgeImpulseScale = in.dodgeImpulseScale;
				in.dodge->DodgeTorqueScale = in.dodgeTorqueScale;
			}
			if (IsReadableObject(in.jump))
			{
				in.jump->MinJumpTime = in.minJumpTime;
				in.jump->JumpImpulse = in.jumpImpulse;
				in.jump->JumpForce = in.jumpForce;
				in.jump->JumpForceTime = in.jumpForceTime;
			}
			if (IsReadableObject(in.doubleJump))
			{
				in.doubleJump->JumpImpulse = in.doubleJumpImpulse;
				in.doubleJump->ImpulseScale = in.doubleJumpScale;
			}
		}
		catch (...) {}
	}

	std::string LowerCategory(std::string value)
	{
		std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
		return value;
	}


	bool ApplyPaintedVisualUsingEngine(UCarMeshComponent_TA* mesh, UProductAsset_TA* asset, int paintId)
	{
		if (EventsComponent::IsTrainingResetQuarantined())
			return false;
		if (!IsReadableObject(mesh) || !IsReadableObject(asset) || paintId <= 0)
			return false;

		try
		{
			UProductAttribute_Painted_TA* painted = UProductAttribute_Painted_TA::CreateInstance(paintId);
			if (!IsReadableObject(painted))
				return false;
			painted->PaintID = paintId;

			bool applied = false;
			auto applyTo = [&](UObject* target)
			{
				if (!IsReadableObject(target))
					return;
				try
				{
					                                                                    
					                                                                      
					                                                                      
					                                                    
					painted->ApplyToObject(asset, target);
					applied = true;
				}
				catch (...) {}
			};

			if (asset->IsA(UProductAsset_Body_TA::StaticClass()) ||
				asset->IsA(UProductAsset_Skin_TA::StaticClass()) ||
				asset->IsA(UProductAsset_PaintFinish_TA::StaticClass()))
			{
				applyTo(mesh);
			}
			else if (asset->IsA(UProductAsset_Wheel_TA::StaticClass()))
			{
				if (IsSaneArray(mesh->WheelMeshes, 16))
				{
					for (int i = 0; i < mesh->WheelMeshes.size(); ++i)
						applyTo(mesh->WheelMeshes[i]);
				}
				                                                                       
				applyTo(mesh);
			}
			else if (asset->IsA(UProductAsset_Attachment_TA::StaticClass()))
			{
				if (IsSaneArray(mesh->Antennas, 16))
				{
					for (int i = 0; i < mesh->Antennas.size(); ++i)
						applyTo(mesh->Antennas[i]);
				}
				applyTo(mesh);
			}
			else
			{
				                                                                        
				if (IsSaneArray(mesh->FXActors, 64))
				{
					for (int i = 0; i < mesh->FXActors.size(); ++i)
						applyTo(mesh->FXActors[i]);
				}
				applyTo(mesh->BodyFX);
				applyTo(mesh->BodyFXActor);
				applyTo(mesh);
			}

			mesh->ApplyPaintSettings();
			mesh->OnPaintChanged();
			return applied;
		}
		catch (...)
		{
			return false;
		}
	}

	bool ApplyVisualProductToLiveCar(ACar_TA* car, int productId, int slotIndex)
	{
		if (!IsReadableObject(car) || !IsReadableObject(car->CarMesh) || productId <= 0)
			return false;

		UProductAsset_TA* asset = GetLoadedProductAsset(productId);
		if (!IsReadableObject(asset))
			return false;

		std::string category;
		for (const GameItem& item : Items.allItems)
		{
			if (item.id == productId && item.slotIndex == slotIndex)
			{
				category = LowerCategory(item.category);
				break;
			}
		}

		                                                                         
		                                                                     
		if (category.find("goal explosion") != std::string::npos || category.find("goalexplosion") != std::string::npos ||
			category.find("player anthem") != std::string::npos || category.find("playeranthem") != std::string::npos ||
			category.find("music stinger") != std::string::npos)
			return true;

		                                                                          
		                                                                      
		                                                                         
		                                                                            
		static ACar_TA* s_baselineCar = nullptr;
		static VehicleHandlingSnapshot s_baselineHandling{};
		if (s_baselineCar != car || !s_baselineHandling.valid)
		{
			s_baselineCar = car;
			s_baselineHandling = VehicleHandlingSnapshot{};
			CaptureVehicleHandling(car, s_baselineHandling);
		}

		bool applied = false;
		try
		{
			UCarMeshComponent_TA* mesh = car->CarMesh;
			if (asset->IsA(UProductAsset_Body_TA::StaticClass()))
			{
				mesh->SetBodyAsset(static_cast<UProductAsset_Body_TA*>(asset));
				mesh->InitBodyVisuals();
				mesh->OnPaintChanged();
				applied = true;
			}
			else if (asset->IsA(UProductAsset_PaintFinish_TA::StaticClass()))
			{
				auto* finish = static_cast<UProductAsset_PaintFinish_TA*>(asset);
				const bool secondary = category.find("finish 2") != std::string::npos ||
					category.find("custom finish") != std::string::npos || category.find("customfinish") != std::string::npos;
				if (secondary) mesh->SetCustomFinish(finish);
				else mesh->SetTeamFinish(finish);
				mesh->ApplyPaintSettings();
				mesh->OnPaintChanged();
				applied = true;
			}
			else if (asset->IsA(UProductAsset_EngineAudio_TA::StaticClass()))
			{
				auto* engineAsset = static_cast<UProductAsset_EngineAudio_TA*>(asset);
				if (IsReadableObject(car->EngineAudio))
					car->EngineAudio->InitFromAsset(engineAsset);
				if (IsReadableObject(car->EngineAudioRev))
					car->EngineAudioRev->InitFromAsset(engineAsset);
				applied = true;
			}
			else
			{
				                                                                    
				                                                                        
				mesh->AddVisualAsset(asset);
				mesh->OnPaintChanged();
				applied = true;
			}
		}
		catch (...)
		{
			applied = false;
		}

		if (applied && slotIndex >= 0 && slotIndex < static_cast<int>(g_itemPaintIds.size()) && g_itemPaintIds[slotIndex] > 0)
		{
			ApplyPaintedVisualUsingEngine(car->CarMesh, asset, g_itemPaintIds[slotIndex]);
		}

		RestoreVehicleHandling(car, s_baselineHandling);
		return applied;
	}

	bool BuildLocalCosmeticLoadout(ULoadout_TA* sourceLoadout, FLoadoutData& localLoadout)
	{
		if (!IsReadableObject(sourceLoadout))
			return false;

		const FLoadoutData savedData = sourceLoadout->GetData();
		if (!IsSaneArray(savedData.Products))
			return false;

		                                                                         
		                                                                      
		                           
		localLoadout.TeamPaint = savedData.TeamPaint;
		localLoadout.Title = savedData.Title;
		localLoadout.TeamIndex = savedData.TeamIndex;
		const bool hasOnlineProducts = IsSaneArray(savedData.OnlineProducts);
		bool changed = false;

		for (int32_t index = 0; index < savedData.Products.size(); ++index)
		{
			const bool hasOverride = index < static_cast<int32_t>(g_equippedCosmeticOverrides.size()) &&
				g_equippedCosmeticOverrides[index] > 0;
			localLoadout.Products.push_back(hasOverride
				? g_equippedCosmeticOverrides[index]
				: savedData.Products[index]);
			changed = changed || hasOverride;

			                                                                    
			                                                 
			FProductInstanceID onlineProduct{};
			if (!hasOverride && hasOnlineProducts && index < savedData.OnlineProducts.size())
				onlineProduct = savedData.OnlineProducts[index];
			localLoadout.OnlineProducts.push_back(onlineProduct);
		}

		return changed && IsSaneArray(localLoadout.Products);
	}

	bool ApplyCosmeticOverridesToGaragePreview()
	{
		if (!HasEquippedCosmeticOverrides())
			return false;

		ULoadoutSet_TA* loadoutSet = GetLocalEquippedLoadoutSet();
		UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
		if (!IsLoadoutSetReady(loadoutSet) || !IsReadableObject(garage) ||
			!IsReadableObject(garage->PreviewActor))
			return false;

		const int previewTeam = garage->PreviewTeam == 1 ? 1 : 0;
		FLoadoutData localLoadout{};
		if (!BuildLocalCosmeticLoadout(loadoutSet->Loadouts[previewTeam], localLoadout))
			return false;

		garage->PreviewActor->SetLoadout(localLoadout);
		return true;
	}

	ACar_TA* GetLocalMatchCar(int& outTeamIndex)
	{
		outTeamIndex = -1;
		ULocalPlayer* localPlayer = Instances.IULocalPlayer();
		if (!IsReadableObject(localPlayer))
			return nullptr;

		APlayerController* controller = localPlayer->Actor;
		if (!IsReadableObject(controller) || !IsReadableObject(controller->PlayerReplicationInfo))
			return nullptr;

		auto* pri = static_cast<APRI_TA*>(controller->PlayerReplicationInfo);
		if (!IsReadableObject(pri) || !IsReadableObject(pri->Car))
			return nullptr;

		outTeamIndex = IsReadableObject(pri->Team) && pri->Team->TeamIndex != 0 ? 1 : 0;
		return pri->Car;
	}

	bool ApplyCosmeticOverridesToLiveCar()
	{
		                                                                     
		                                                                          
		                                                                      
		                                                                     
		                                                                    
		if (!HasEquippedCosmeticOverrides())
			return false;

		int activeTeam = -1;
		ACar_TA* localCar = GetLocalMatchCar(activeTeam);
		if (!IsReadableObject(localCar) || !IsReadableObject(localCar->CarMesh) || activeTeam < 0 || activeTeam > 1)
			return false;

		bool anyApplied = false;
		bool allReady = true;
		for (int slotIndex = 0; slotIndex < static_cast<int>(g_equippedCosmeticOverrides.size()); ++slotIndex)
		{
			const int productId = g_equippedCosmeticOverrides[slotIndex];
			if (productId <= 0)
				continue;

			if (ApplyVisualProductToLiveCar(localCar, productId, slotIndex))
				anyApplied = true;
			else
				allReady = false;
		}

		if (anyApplied)
		{
			g_lastCosmeticOverrideCar = localCar;
			g_lastCosmeticOverrideTeam = activeTeam;
		}
		return anyApplied && allReady;
	}

	void ApplyPaintedItemToMesh(UCarMeshComponent_TA* mesh, int slot, int paintId)
	{
		if (!IsReadableObject(mesh) || slot < 0 || slot >= 32 || EventsComponent::IsTrainingResetQuarantined())
			return;

		try
		{
			                                                                         
			                                                                              
			                                                                        
			if (IsSaneArray(mesh->ProductAttributes.Products, 128) &&
				slot < mesh->ProductAttributes.Products.size())
			{
				mesh->RemoveProductAttributeFromProduct(UProductAttribute_Painted_TA::StaticClass(), slot);

				FClientLoadoutOnlineData rebuilt{};
				const FClientLoadoutOnlineData& current = mesh->ProductAttributes;
				for (int productIndex = 0; productIndex < current.Products.size(); ++productIndex)
				{
					FClientLoadoutOnlineProduct outProduct{};
					const FClientLoadoutOnlineProduct& inProduct = current.Products[productIndex];
					if (IsSaneArray(inProduct.Attributes, 128))
					{
						for (int a = 0; a < inProduct.Attributes.size(); ++a)
							outProduct.Attributes.push_back(inProduct.Attributes[a]);
					}

					if (productIndex == slot && paintId > 0)
					{
						if (UProductAttribute_Painted_TA* painted = UProductAttribute_Painted_TA::CreateInstance(paintId))
						{
							painted->PaintID = paintId;
							outProduct.Attributes.push_back(painted);
						}
					}
					rebuilt.Products.push_back(outProduct);
				}
				mesh->SetProductAttributes(rebuilt);
			}

			                                                                         
			                                                        
			if (slot < static_cast<int>(g_equippedCosmeticOverrides.size()))
			{
				const int productId = g_equippedCosmeticOverrides[slot];
				if (productId > 0)
				{
					if (UProductAsset_TA* asset = GetLoadedProductAsset(productId))
					{
						if (paintId > 0)
							ApplyPaintedVisualUsingEngine(mesh, asset, paintId);
					}
				}
			}

			mesh->ApplyPaintSettings();
			mesh->OnPaintChanged();
		}
		catch (...) {}
	}

	bool HasPaintedItemOverrides()
	{
		for (int paintId : g_itemPaintIds)
			if (paintId > 0)
				return true;
		return false;
	}

	void ReapplyPaintedItemOverrides()
	{
		try
		{
			int liveTeam = -1;
			ACar_TA* liveCar = GetLocalMatchCar(liveTeam);
			if (IsReadableObject(liveCar) && IsReadableObject(liveCar->CarMesh))
			{
				for (int slot = 0; slot < static_cast<int>(g_itemPaintIds.size()); ++slot)
				{
					if (g_itemPaintIds[slot] > 0)
						ApplyPaintedItemToMesh(liveCar->CarMesh, slot, g_itemPaintIds[slot]);
				}
			}

			UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
			if (IsReadableObject(garage) && IsReadableObject(garage->PreviewActor) &&
				IsReadableObject(garage->PreviewActor->CarMesh))
			{
				for (int slot = 0; slot < static_cast<int>(g_itemPaintIds.size()); ++slot)
				{
					if (g_itemPaintIds[slot] > 0)
						ApplyPaintedItemToMesh(garage->PreviewActor->CarMesh, slot, g_itemPaintIds[slot]);
				}
			}
		}
		catch (...) {}
	}

}

int ItemComponent::GetEquippedProductId(int slotIndex)
{
	if (slotIndex < 0 || slotIndex > 31)
		return -1;
	if (g_equippedCosmeticOverrides[slotIndex] > 0)
		return g_equippedCosmeticOverrides[slotIndex];

	try
	{
		ULoadoutSet_TA* loadoutSet = GetLocalEquippedLoadoutSet();
		ULoadout_TA* loadout = loadoutSet ? loadoutSet->Loadouts[0] : nullptr;
		if (!IsReadableObject(loadout) || !IsSaneArray(loadout->Products) || slotIndex >= loadout->Products.size())
			return -1;
		return loadout->Products[slotIndex];
	}
	catch (...)
	{
		return -1;
	}
}

int ItemComponent::GetEquippedPaintId(int slotIndex) const
{
	if (slotIndex < 0 || slotIndex >= static_cast<int>(g_itemPaintIds.size()))
		return 0;
	return g_itemPaintIds[slotIndex];
}

bool ItemComponent::IsProductPaintable(int productId) const
{
	if (productId <= 0) return false;
	for (const GameItem& item : allItems)
		if (item.id == productId)
			return item.paintable;
	return false;
}

bool ItemComponent::SaveLoadoutPreset(const std::string& name, const EquippedLoadoutPreset& products)
{
	try
	{
		const std::string safeName = SanitizeLoadoutPresetName(name);
		json entries = json::array();
		for (const EquippedLoadoutItem& entry : products)
		{
			if (entry.slotIndex >= 0 && entry.productId > 0)
				entries.push_back({ { "slot", entry.slotIndex }, { "product", entry.productId }, { "paint", entry.paintId } });
		}

		json preset = {
			{ "version", 3 },
			{ "name", safeName },
			{ "entries", entries }
		};

		const fs::path filePath = LoadoutPresetDirectory() / (safeName + ".json");
		std::ofstream output(filePath, std::ios::trunc);
		if (!output.is_open())
			return false;
		output << preset.dump(2);
		output.close();

		std::ofstream active(ActiveLoadoutPresetPath(), std::ios::trunc);
		if (active.is_open())
			active << json{ { "preset", safeName } }.dump(2);

		Console.Write("[Loadout] Saved preset '" + safeName + "'.");
		return true;
	}
	catch (...)
	{
		Console.Warning("[Loadout] Failed to save preset.");
		return false;
	}
}

bool ItemComponent::LoadLoadoutPreset(const std::string& name, EquippedLoadoutPreset& products)
{
	try
	{
		const std::string safeName = SanitizeLoadoutPresetName(name);
		std::ifstream input(LoadoutPresetDirectory() / (safeName + ".json"));
		if (!input.is_open())
			return false;

		json preset;
		input >> preset;
		EquippedLoadoutPreset loaded{};
		for (EquippedLoadoutItem& entry : loaded)
			entry = {};

		if (preset.contains("entries") && preset["entries"].is_array())
		{
			if (preset["entries"].size() > loaded.size())
				return false;

			for (size_t index = 0; index < preset["entries"].size(); ++index)
			{
				const json& entry = preset["entries"][index];
				if (!entry.is_object() || !entry.contains("slot") || !entry.contains("product") ||
					!entry["slot"].is_number_integer() || !entry["product"].is_number_integer())
					return false;

				loaded[index].slotIndex = entry["slot"].get<int>();
				loaded[index].productId = entry["product"].get<int>();
				loaded[index].paintId = entry.value("paint", 0);
				if (loaded[index].slotIndex < 0 || loaded[index].slotIndex > 31 ||
					loaded[index].productId < -1 || loaded[index].productId > 2000000000 ||
					loaded[index].paintId < 0 || loaded[index].paintId > 32)
					return false;
			}
		}
		else if (preset.contains("slots") && preset["slots"].is_array())
		{
			                                                                        
			if (preset["slots"].size() != 4)
				return false;
			for (size_t slot = 0; slot < preset["slots"].size(); ++slot)
			{
				if (!preset["slots"][slot].is_number_integer())
					return false;
				loaded[slot].slotIndex = static_cast<int>(slot);
				loaded[slot].productId = preset["slots"][slot].get<int>();
				if (loaded[slot].productId < -1 || loaded[slot].productId > 2000000000)
					return false;
			}
		}
		else
		{
			return false;
		}

		products = loaded;
		std::ofstream active(ActiveLoadoutPresetPath(), std::ios::trunc);
		if (active.is_open())
			active << json{ { "preset", safeName } }.dump(2);

		Console.Write("[Loadout] Loaded preset '" + safeName + "'.");
		return true;
	}
	catch (...)
	{
		Console.Warning("[Loadout] Failed to load preset.");
		return false;
	}
}

bool ItemComponent::DeleteLoadoutPreset(const std::string& name)
{
	try
	{
		const std::string safeName = SanitizeLoadoutPresetName(name);
		const fs::path presetPath = LoadoutPresetDirectory() / (safeName + ".json");
		std::error_code error;
		if (!fs::is_regular_file(presetPath, error) || error || !fs::remove(presetPath, error) || error)
			return false;

		                                                                             
		std::ifstream activeInput(ActiveLoadoutPresetPath());
		json activePreset;
		if (activeInput.is_open() && (activeInput >> activePreset) &&
			activePreset.contains("preset") && activePreset["preset"].is_string() &&
			activePreset["preset"].get<std::string>() == safeName)
		{
			std::error_code activeError;
			fs::remove(ActiveLoadoutPresetPath(), activeError);
			g_autoLoadoutApplied = true;
		}

		Console.Write("[Loadout] Deleted preset '" + safeName + "'.");
		return true;
	}
	catch (...)
	{
		Console.Warning("[Loadout] Failed to delete preset.");
		return false;
	}
}

std::vector<std::string> ItemComponent::ListLoadoutPresets() const
{
	std::vector<std::string> presets;
	std::error_code error;
	const fs::path directory = LoadoutPresetDirectory();
	for (const fs::directory_entry& entry : fs::directory_iterator(directory, error))
	{
		if (error || !entry.is_regular_file() || entry.path().extension() != ".json")
			continue;
		const std::string name = entry.path().stem().string();
		if (name != "active")
			presets.push_back(name);
	}
	std::sort(presets.begin(), presets.end());
	return presets;
}

void ItemComponent::QueueAutoApplyLoadoutPreset()
{
	if (g_autoLoadoutApplied.load() || g_autoLoadoutQueued.load())
		return;

	const auto now = std::chrono::steady_clock::now();
	if (now - g_lastAutoLoadoutAttempt < std::chrono::seconds(2))
		return;
	g_lastAutoLoadoutAttempt = now;

	                                                                      
	                                                                           
	                                                    
	if (!IsLoadoutSetReady(GetLocalEquippedLoadoutSet()))
	{
		g_loadoutReadySince = {};
		return;
	}
	if (g_loadoutReadySince == std::chrono::steady_clock::time_point{})
	{
		g_loadoutReadySince = now;
		return;
	}
	if (now - g_loadoutReadySince < std::chrono::seconds(5))
		return;

	try
	{
		std::ifstream active(ActiveLoadoutPresetPath());
		json activeData;
		if (!active.is_open() || !(active >> activeData) || !activeData.contains("preset"))
		{
			g_autoLoadoutApplied = true;                                         
			return;
		}

		const std::string activePresetName = activeData["preset"].get<std::string>();
		EquippedLoadoutPreset productIds{};
		if (!LoadLoadoutPreset(activePresetName, productIds))
		{
			g_autoLoadoutApplied = true;
			return;
		}

		bool hasProduct = false;
		for (const EquippedLoadoutItem& entry : productIds)
			hasProduct = hasProduct || (entry.slotIndex >= 0 && entry.productId > 0);
		if (!hasProduct)
		{
			g_autoLoadoutApplied = true;
			return;
		}

		g_autoLoadoutQueued = true;
		Main.Execute([productIds, activePresetName]() {
			bool complete = true;
			for (const EquippedLoadoutItem& entry : productIds)
			{
				if (entry.slotIndex >= 0 && entry.productId > 0 &&
					!Items.EquipProductToSlotPainted(entry.productId, entry.slotIndex, entry.paintId))
					complete = false;
			}
			if (complete)
				Main.SpawnItemShopToast("LOADOUT PRESET", activePresetName + " loaded!", 4);
			g_autoLoadoutApplied = complete;
			g_autoLoadoutQueued = false;
		});
	}
	catch (...)
	{
		g_autoLoadoutApplied = true;
	}
}

bool ItemComponent::EquipProductToSlot(int productId, int slotIndex)
{
	if (productId <= 0 || slotIndex < 0 || slotIndex > 31)
		return false;

	try
	{
		                                                                    
		                                                                   
		                                                                       
		                                                                          
		EnsureItemsLoaded();
		const auto itemIt = std::find_if(allItems.begin(), allItems.end(),
			[productId, slotIndex](const GameItem& item) {
				return item.id == productId && item.slotIndex == slotIndex;
			});
		if (itemIt == allItems.end())
		{
			Console.Write("[Items] Cannot equip: the preset product is missing or belongs to a different slot.");
			return false;
		}
		if (itemIt->hashId <= 0)
		{
			Console.Write("[Items] Cannot equip: the product has no valid Rocket League hash ID.");
			return false;
		}

		if (!IsLoadoutSetReady(GetLocalEquippedLoadoutSet()))
		{
			Console.Write("[Items] Cannot equip: the local profile loadout is not ready.");
			return false;
		}

		                                                                      
		                                                                     
		                                                                         
		                                                                     
		RequestProductAssetLoad(itemIt->id);
		g_equippedCosmeticOverrides[slotIndex] = itemIt->id;
		g_cosmeticOverrideReapplyRequested = true;
		ApplyCosmeticOverridesToGaragePreview();
		if (ApplyCosmeticOverridesToLiveCar())
			g_cosmeticOverrideReapplyRequested = false;

		Console.Write("[Items] Applied local cosmetic " + std::to_string(productId) + " in loadout slot " + std::to_string(slotIndex));
		return true;
	}
	catch (const std::exception& e)
	{
		Console.Write("[Items] Equip failed: " + std::string(e.what()));
		return false;
	}
	catch (...)
	{
		Console.Write("[Items] Equip failed with an unknown error.");
		return false;
	}
}


bool ItemComponent::EquipProductToSlotPainted(int productId, int slotIndex, int paintId)
{
	if (EventsComponent::IsTrainingResetQuarantined())
		return false;
	if (productId <= 0 || slotIndex < 0 || slotIndex >= static_cast<int>(g_itemPaintIds.size()))
		return false;
	if (paintId < 0 || paintId > 32)
		return false;

	                                                                                    
	                                                                                    
	g_itemPaintIds[slotIndex] = paintId;
	RequestProductAssetLoad(productId);

	if (!EquipProductToSlot(productId, slotIndex))
		return false;

	                                                                               
	ApplyPaintedItem(slotIndex, paintId);
	return true;
}

void ItemComponent::RequestEquippedCosmeticOverrideReapply()
{
	if (HasEquippedCosmeticOverrides())
		g_cosmeticOverrideReapplyRequested = true;
}

void ItemComponent::RefreshEquippedCosmeticLobbyPreview()
{
	if (!HasEquippedCosmeticOverrides())
		return;

	try
	{
		                                                                       
		                                                                 
		ApplyCosmeticOverridesToGaragePreview();
	}
	catch (...) {}
}

void ItemComponent::ReassertEquippedCosmeticOverrides()
{
	if (EventsComponent::IsTrainingResetQuarantined())
		return;

	const bool hasCosmetics = HasEquippedCosmeticOverrides();
	const bool hasPainted = HasPaintedItemOverrides();
	if (!hasCosmetics && !hasPainted)
		return;

		int activeTeam = -1;
		ACar_TA* currentCar = GetLocalMatchCar(activeTeam);
		const bool localCarChanged = currentCar &&
			(currentCar != g_lastCosmeticOverrideCar || activeTeam != g_lastCosmeticOverrideTeam);
		if (!g_cosmeticOverrideReapplyRequested.exchange(false) && !localCarChanged)
			return;

	try
	{
		                                                                         
		                                                                      
		if (hasCosmetics)
		{
			if (!ApplyCosmeticOverridesToLiveCar() && currentCar)
				g_cosmeticOverrideReapplyRequested = true;
		}
		else if (currentCar)
		{
			g_lastCosmeticOverrideCar = currentCar;
			g_lastCosmeticOverrideTeam = activeTeam;
		}

		if (hasPainted)
			ReapplyPaintedItemOverrides();
	}
	catch (...)
	{
		                                                                     
		                                                                   
	}
}

bool ItemComponent::EquipProduct(int productId)
{
	                                                                  
	return EquipProductToSlot(productId, 0);
}

std::vector<LoadoutColorOption> ItemComponent::GetLoadoutColorOptions(int teamIndex, bool accentPalette) const
{
	std::vector<LoadoutColorOption> options;
	if (teamIndex < 0 || teamIndex > 1)
		return options;

	try
	{
		UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
		if (!IsReadableObject(garage))
			return options;

		const TArray<FGFxTeamColor>& palette = accentPalette
			? garage->CustomColors
			: (teamIndex == 0 ? garage->Team0Colors : garage->Team1Colors);
		if (!IsSaneArray(palette, 512))
			return options;

		options.reserve(static_cast<size_t>(palette.size()));
		for (int index = 0; index < palette.size(); ++index)
		{
			const FGFxTeamColor& gameColor = palette[index];
			if (gameColor.ColorID < 0 || gameColor.ColorID > 255)
				continue;

			const bool alreadyPresent = std::any_of(options.begin(), options.end(),
				[&gameColor](const LoadoutColorOption& option) { return option.colorId == gameColor.ColorID; });
			if (alreadyPresent)
				continue;

			LoadoutColorOption option;
			option.colorId = gameColor.ColorID;
			option.red = gameColor.Value.R;
			option.green = gameColor.Value.G;
			option.blue = gameColor.Value.B;
			option.alpha = gameColor.Value.A == 0 ? 255 : gameColor.Value.A;
			options.push_back(option);
		}
	}
	catch (...)
	{
		options.clear();
	}

	return options;
}

bool ItemComponent::SetLoadoutTeamColors(int teamIndex, int primaryColorId, int accentColorId)
{
	if (teamIndex < 0 || teamIndex > 1 || primaryColorId < 0 || primaryColorId > 255 ||
		accentColorId < 0 || accentColorId > 255)
		return false;

	try
	{
		                                                                     
		                                                                     
		                                                     
		UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
		if (IsReadableObject(garage) && IsReadableObject(garage->LoadoutSet))
		{
			garage->SetTeamColor(teamIndex, primaryColorId);
			garage->SetCustomColor(teamIndex, accentColorId);
			garage->CommitLoadout();
			return true;
		}

		                                                                          
		                                                                          
		UProfile_TA* profile = nullptr;
		ULoadoutSet_TA* loadoutSet = GetLocalEquippedLoadoutSet(&profile);
		if (!IsLoadoutSetReady(loadoutSet))
			return false;

		ULoadout_TA* loadout = loadoutSet->Loadouts[teamIndex];
		if (!IsReadableObject(loadout))
			return false;
		FLoadoutData data = loadout->GetData();
		data.TeamPaint.Team = static_cast<uint8_t>(teamIndex);
		data.TeamPaint.TeamColorID = static_cast<uint8_t>(primaryColorId);
		data.TeamPaint.CustomColorID = static_cast<uint8_t>(accentColorId);
		data.TeamPaint.bSet = true;
		loadout->SetData(data);

		ULocalPlayer* localPlayer = Instances.IULocalPlayer();
		if (localPlayer && localPlayer->Actor && localPlayer->Actor->PlayerReplicationInfo)
		{
			APRI_TA* pri = static_cast<APRI_TA*>(localPlayer->Actor->PlayerReplicationInfo);
			if (pri)
			{
				pri->FullLoadouts[teamIndex].TeamPaint = data.TeamPaint;
				const int activeTeam = (pri->Team && pri->Team->TeamIndex != 0) ? 1 : 0;
				if (activeTeam == teamIndex)
				{
					pri->TeamPaint = data.TeamPaint;
					if (ACar_TA* car = pri->Car)
					{
						car->TeamPaint = data.TeamPaint;
						car->bNetDirty = true;
					}
				}
				pri->bNetDirty = true;
			}
		}

		RefreshGarageLoadoutPreview(profile);
		return true;
	}
	catch (...)
	{
		Console.Warning("[Loadout] Failed to set team colors.");
		return false;
	}
}

bool ItemComponent::ApplyPaintedItem(int slotIndex, int paintId)
{
	if (EventsComponent::IsTrainingResetQuarantined())
		return false;
	if (slotIndex < 0 || slotIndex >= static_cast<int>(g_itemPaintIds.size()))
		return false;

	                                                                          
	                                          
	if (paintId < 0 || paintId > 32)
		return false;

	g_itemPaintIds[slotIndex] = paintId;

	                                                                            
	                                                            
	try
	{
		int team = -1;
		ACar_TA* car = GetLocalMatchCar(team);
		if (IsReadableObject(car) && IsReadableObject(car->CarMesh))
			ApplyPaintedItemToMesh(car->CarMesh, slotIndex, paintId);

		UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
		if (IsReadableObject(garage) && IsReadableObject(garage->PreviewActor) &&
			IsReadableObject(garage->PreviewActor->CarMesh))
			ApplyPaintedItemToMesh(garage->PreviewActor->CarMesh, slotIndex, paintId);
	}
	catch (...) {}

	return true;
}

void ItemComponent::ApplyFakeLoadout(int bodyId, int skinId, int wheelId, int boostId, int antennaId, int hatId, int paintFinishId, int customFinishId, int paintColor)
{
	                                                                          
	                                                                        
	                                                                        
	                                                                            
	try
	{
		EnsureItemsLoaded();
		const int products[] = { bodyId, skinId, wheelId, boostId, antennaId, hatId, paintFinishId, customFinishId };
		int bodySlot = -1;
		for (int productId : products)
		{
			if (productId <= 0)
				continue;
			auto it = std::find_if(allItems.begin(), allItems.end(), [productId](const GameItem& item) { return item.id == productId; });
			if (it == allItems.end() || it->slotIndex < 0)
				continue;
			if (LowerCategory(it->category) == "body")
				bodySlot = it->slotIndex;
			EquipProductToSlot(productId, it->slotIndex);
		}

		if (paintColor > 0 && bodySlot >= 0)
			ApplyPaintedItem(bodySlot, paintColor);

		Console.Write("[Items] ApplyFakeLoadout routed through safe visual-only equip path");
	}
	catch (...)
	{
		Console.Write("[Items] ApplyFakeLoadout failed safely");
	}
}



ItemComponent Items;
