#pragma once
#include "../Component.hpp"

#include <vector>

struct GameTitle {
	int id;
	std::string category;
	std::string internalName;
	std::string displayName;
};

class TitleComponent : public Component
{
private:
	std::vector<long long> generatedPIIDs;

public:
	TitleComponent();
	~TitleComponent() override;

public:
	void OnCreate() override;

	void LoadTitles();
	void EnsureTitlesLoaded();                                              

	std::vector<GameTitle> allTitles;
	char titleSearch[128] = "";
	int selectedTitleIndex = -1;
	void OnDestroy() override;

	       
	struct STitleData
	{
		std::string titleid;
		std::string titletext;
		FColor titlecolor;
		FColor titleglow;
	};

	std::vector<STitleData> TitlesForImGui;
	STitleData selectedTitleForSpawn;
	std::vector<FOnlineProductData> spawnedProducts;
	USaveData_TA* saveData = nullptr;

	                                                                        

public:
	UOnlineProduct_TA* SpawnTitle(
		int titleId,
		int seriesid,
		int tradehold,
		bool log,
		const std::string& spawnMessage,
		bool animation
	);
	bool SpawnTitleData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation);
	FProductInstanceID GeneratePIID(int64_t Product);
	FProductInstanceID IntToProductInstanceID(int64_t Value);
	unsigned long long GetTimestampLong();

	                                            
	bool ShouldSkipTitle(class UProduct_TA* product);
	std::string GetTitleCategory(class UProduct_TA* product);
	bool IsTitleProduct(class UProduct_TA* product);

	       
	void LoadAllTitle();

};

                                      
UOnlineProduct_TA* SpawnProduct(int item, TArray<FOnlineProductAttribute> attributes = {}, int seriesid = 0, int tradehold = 0, bool log = false);
bool SpawnProductData(const FOnlineProductData& productData, const std::string& spawnMessage, bool animation);

extern class TitleComponent Titles;
