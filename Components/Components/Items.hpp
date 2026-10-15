#pragma once
#include "../Component.hpp"

#include <vector>
#include <array>

struct GameItem {
	int id;
	                                                                         
	                                                                           
	                               
	int hashId = -1;
	                                                                        
	                                                                          
	int slotIndex = -1;
	std::string category;
	std::string internalName;
	std::string displayName;
	int quality = -1;
	int paintId = -1;
	bool paintable = false;
};

struct EquippedLoadoutItem {
	int slotIndex = -1;
	int productId = -1;
	int paintId = 0;
};

using EquippedLoadoutPreset = std::array<EquippedLoadoutItem, 12>;

                                                                        
                                                              
struct LoadoutColorOption {
	int colorId = -1;
	uint8_t red = 0;
	uint8_t green = 0;
	uint8_t blue = 0;
	uint8_t alpha = 255;
};

              
enum class EProductCertif : uint8_t
{
	EPQ_Aviator       = 0,
	EPQ_Playmaker     = 1,
	EPQ_Showoff       = 2,
	EPQ_Acrobat       = 3,
	EPQ_Tactician     = 4,
	EPQ_Sweeper       = 5,
	EPQ_Guardian      = 6,
	EPQ_Scorer        = 7,
	EPQ_Juggler       = 8,
	EPQ_Sniper        = 9,
	EPQ_Paragon       = 10,
	EPQ_Goalkeeper    = 11,
	EPQ_Striker       = 12,
	EPQ_Turtle        = 13,
	EPQ_Victor        = 14,
	EPQ_None          = 15
};

             
enum class EProductPaint : uint8_t
{
	EPQ_Red           = 0,
	EPQ_Lime          = 1,
	EPQ_Black         = 2,
	EPQ_SkyBlue       = 3,
	EPQ_Cobalt        = 4,
	EPQ_BurntSienna   = 5,
	EPQ_ForestGreen   = 6,
	EPQ_Purple        = 7,
	EPQ_Pink          = 8,
	EPQ_Orange        = 9,
	EPQ_Grey          = 10,
	EPQ_TitaniumWhite = 11,
	EPQ_Saffron       = 12,
	EPQ_Gold          = 13,
	EPQ_RoseGold      = 14,
	EPQ_WhiteGold     = 15,
	EPQ_Onyx          = 16,
	EPQ_Platinum      = 17,
	EPQ_None          = 18
};

class ItemComponent : public Component
{
private:
	std::vector<long long> generatedPIIDs;

public:
	ItemComponent();
	~ItemComponent() override;

public:
	void OnCreate() override;

	void LoadItems();
	void EnsureItemsLoaded();                                             

	std::vector<GameItem> allItems;
	char itemSearch[128] = "";
	void OnDestroy() override;

	                            
	uint8_t Quality = 0;                    
	uint8_t Paint = 0;                      
	uint8_t Certif = 0;                     

public:
	UOnlineProduct_TA* SpawnProduct(
		int item,
		int seriesid,
		int tradehold,
		bool log,
		const std::string& spawnMessage,
		bool animation
	);

	                                                            
    bool custompainttrim = false;
    bool custompainttrimrgb = false;
    float customtrimcolors[3] = { 1.0f, 1.0f, 1.0f };
    bool hasresetpainttrim = true;

                                                                      
    bool customunderglow = false;
    bool customunderglowrgb = false;
    float customunderglowcolors[3] = { 0.0f, 1.0f, 1.0f };
    bool hasresetunderglow = true;

                                                                             
                                                                               
                                                                            
                                                                           
    bool  plateFrontEnabled = false;
    bool  plateRearEnabled = false;
    char  plateFrontImagePath[512] = "";
    char  plateRearImagePath[512] = "";
    float plateFrontBgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float plateRearBgColor[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float plateFrontOffset[3] = { 60.0f, 0.0f, 15.0f };                                               
    float plateRearOffset[3] = { -60.0f, 0.0f, 15.0f };
                                                                             
                                                   
    float plateFrontRoll = 0.0f;
    float plateRearRoll = 0.0f;
    float plateFrontPitch = 0.0f;
    float plateRearPitch = 0.0f;
    float plateFrontYaw = 0.0f;
    float plateRearYaw = 0.0f;
                                                                            
                                                                             
                                                             
    float plateFrontWidth = 0.10f;
    float plateFrontHeight = 0.05f;
    float plateRearWidth = 0.10f;
    float plateRearHeight = 0.05f;
    bool  plateFrontDirty = true;                                           
    bool  plateRearDirty = true;
	
	                            
	bool SpawnCredits(int amount, bool isTournamentCredits = false, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnNormalCredits(int amount, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnTournamentCredits(int amount, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnSpecialCredits(int amount, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnEsportJeton(int amount, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnTogrogs(int amount, const std::string& spawnMessage = "", bool animation = true);
	bool SpawnProductData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation);
	
	                                    
	void CreateAndSpawnProduct(int productId, int quality, int paintId, int certId, int seriesId);
	
	                                                                          
	                                                                            
	bool EquipProductToSlot(int productId, int slotIndex);
	                                                                                       
	                                                     
	bool EquipProductToSlotPainted(int productId, int slotIndex, int paintId);
	int GetEquippedProductId(int slotIndex);
	int GetEquippedPaintId(int slotIndex) const;
	bool IsProductPaintable(int productId) const;
	                                                                         
	                                                                         
	void RequestEquippedCosmeticOverrideReapply();
	void ReassertEquippedCosmeticOverrides();
	                                                                      
	                                                            
	void RefreshEquippedCosmeticLobbyPreview();
	bool SaveLoadoutPreset(const std::string& name, const EquippedLoadoutPreset& products);
	bool LoadLoadoutPreset(const std::string& name, EquippedLoadoutPreset& products);
	bool DeleteLoadoutPreset(const std::string& name);
	std::vector<std::string> ListLoadoutPresets() const;
	void QueueAutoApplyLoadoutPreset();
	std::vector<LoadoutColorOption> GetLoadoutColorOptions(int teamIndex, bool accentPalette) const;
	bool SetLoadoutTeamColors(int teamIndex, int primaryColorId, int accentColorId);

	                                                                          
	                                                                    
	bool ApplyPaintedItem(int slotIndex, int paintId);

	                                                                         
	bool EquipProduct(int productId);
	
	                                                           
	void ApplyFakeLoadout(int bodyId = -1, int skinId = -1, int wheelId = -1, int boostId = -1, int antennaId = -1, int hatId = -1, int paintFinishId = -1, int customFinishId = -1, int paintColor = -1);
	
	FProductInstanceID GeneratePIID(int64_t Product);
	FProductInstanceID IntToProductInstanceID(int64_t Value);
	unsigned long long GetTimestampLong();

	                                            
	bool ShouldSkipProduct(class UProduct_TA* product);
	std::string GetItemCategory(class UProduct_TA* product);

};

extern class ItemComponent Items;
