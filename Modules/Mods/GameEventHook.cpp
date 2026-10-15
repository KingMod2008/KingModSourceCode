#include "../../PublicConfig.hpp"
#include <algorithm>

                                                       
extern "C" {
#include "../../sha256.c"
#include "../../hmac_sha256.c"
}

#include "GameEventHook.hpp"
#include "KingFeatures.hpp"
#include "WorkshopSteamDownloader.hpp"
#include "CustomMatch.hpp"
#include "FakeSpectator.hpp"
#include "BallPrediction.hpp"
#include "CustomAvatar.hpp"
#include "BallTextures.hpp"
#include "CustomBoostMeter.hpp"
#include "CustomBorder.hpp"
#include "HostSync.hpp"
#include "MatchmakingShield.hpp"
#include "KingFeatures.hpp"
#include "KingSync.hpp"
#include "../../Components/Components/Events.hpp"
#include "../../RLSDK/SDK_HEADERS/SdkHeaders.hpp"
#include "../../RLSDK/RPC_DISCORD/KingModRPC.hpp"
#include "../../Extensions/Extensions/Colors.hpp"
#include "../../ImGui/imgui.h"
#include "../../ImGui/menu_avatar.hpp"
#include "../../GamePacket.hpp"
#include <string>
#include <chrono>
#include <Windows.h>
#include <vector>
#include <sstream>
#include <cmath>
#include <thread>
#include <atomic>
#include <mutex>
#include <cstring>
#include <cwchar>
#include <iomanip>
#include <iostream>
#include <tuple>
#include <initializer_list>
#include <curl/curl.h>
#include <map>
#include <ctime>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <random>
#include <fstream>
#include <nlohmann/json.hpp>
#include <cfloat>
#include <cctype>
#include <cstdlib>
#include <Windows.h>
#include <Xinput.h>
#include "../../hmac_sha256.h"
#pragma comment(lib, "xinput9_1_0.lib")
#include <ShlObj.h>
                                                                            
                                                                                
                       
#include <shellapi.h>
#include <stdexcept>
                                                                        
#include <d3d11.h>
                                                                               
#include <zlib.h>

namespace
{
    std::atomic<long long> g_NamePrefixBlockUntilMs{ 0 };
    std::atomic<DWORD> g_RocketLeagueGameThread{ 0 };

    long long GetSteadyTimeMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count();
    }

    void BlockNamePrefixUpdates(long long milliseconds)
    {
        g_NamePrefixBlockUntilMs.store(
            GetSteadyTimeMs() + milliseconds,
            std::memory_order_release
        );
    }
}

namespace VisualsNamespace {
    void DrawTracers() {}
    void DrawVelocityArrows() {}
    void DrawPlayerDistanceText() {}
    void DrawOpponentBoost() {}
    void DrawCarHitboxes() {}
    void DrawFlipDetector() {}
}

#define _CRT_SECURE_NO_WARNINGS

bool EnablePsyNetLogging = false;
bool EnableDropUnlockBypass = false;
bool DisableSyncData = false;
std::vector<std::string> PsyNetLogMessages;
std::vector<std::string> PsyNetLogHeaders;
std::vector<std::string> PsyNetLogBodies;
std::string PsyNetStatusSummary = "Idle";
bool PsyNetHasCachedDropTable = false;
int PsyNetPendingRequestCount = 0;

using json = nlohmann::json;

static std::vector<std::string> LoadMaterialInstanceNames(const std::vector<std::string>& keywords);

namespace
{
    void KingModRecoverWorkshopAliasOnStartup();
    void KingModRestoreWorkshopAliasAfterTravel();
}

namespace
{
    constexpr size_t kMaxPsyNetLogEntries = 200;

    struct PsyNetRequestInfo
    {
        std::string Service;
        int ContainerProductId = 0;
        std::vector<FProductInstanceID> TradeInProductInstances;
        std::string RedeemCode;
        int ShopPurchaseCostId = 0;
        int ShopPurchaseShopId = 0;
        int ShopPurchaseDiscountId = 0;
        int ShopPurchaseCount = 1;
    };

    struct PsyNetState
    {
        std::map<std::string, PsyNetRequestInfo> PendingRequests;
        std::string CatalogJSON;
        std::vector<int> BlackMarketProducts;
        std::vector<int> ExoticProducts;
        std::vector<int> ImportProducts;
        std::vector<int> VeryRareProducts;
        std::vector<int> RareProducts;
        std::vector<int> UncommonProducts;
        std::vector<int> WeightedPaintValues = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12
        };
        std::vector<int> WeightedCertValues = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        };
        bool PoolsBuilt = false;
    };

    PsyNetState g_PsyNetState;

    std::string GetKingModResourcesDirectory()
    {
        char exePath[MAX_PATH] = {};
        std::string dir;
        if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
            dir = (fs::path(exePath).parent_path() / "KingMod" / "resources").string();
        else
            dir = (fs::current_path() / "KingMod" / "resources").string();
        SHCreateDirectoryExA(NULL, dir.c_str(), NULL);
        return dir;
    }

    std::string GetDefaultConfigPath()
    {
        return GetKingModResourcesDirectory() + "\\KingMod.json";
    }

    std::string JsonToString(const json& value, const std::string& fallback = "")
    {
        try
        {
            if (value.is_string())
                return value.get<std::string>();
            if (value.is_number_integer())
                return std::to_string(value.get<int>());
            if (value.is_number_float())
                return std::to_string(value.get<float>());
        }
        catch (...)
        {
        }

        return fallback;
    }

    bool ShouldTrackPsyNet()
    {
        return EnablePsyNetLogging || EnableDropUnlockBypass || DisableSyncData;
    }

    bool ContainsSubstring(const std::string& value, const std::string& needle)
    {
        return !needle.empty() && value.find(needle) != std::string::npos;
    }

    std::string ToLowerAscii(std::string value)
    {
        std::transform(value.begin(), value.end(), value.begin(), [](unsigned char ch) {
            return static_cast<char>(std::tolower(ch));
        });
        return value;
    }

    void ReplaceAll(std::string& value, const std::string& from, const std::string& to)
    {
        if (from.empty())
            return;

        size_t index = 0;
        while ((index = value.find(from, index)) != std::string::npos)
        {
            value.replace(index, from.size(), to);
            index += to.size();
        }
    }

    std::mt19937& PsyNetRng()
    {
        static std::mt19937 rng(static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count()));
        return rng;
    }

    template <typename T>
    T PickRandomValue(const std::vector<T>& values, T fallback = T{})
    {
        if (values.empty())
            return fallback;

        std::uniform_int_distribution<size_t> dist(0, values.size() - 1);
        return values[dist(PsyNetRng())];
    }

    void TrimPsyNetLogs()
    {
        while (PsyNetLogMessages.size() > kMaxPsyNetLogEntries)
        {
            PsyNetLogMessages.erase(PsyNetLogMessages.begin());
            if (!PsyNetLogHeaders.empty())
                PsyNetLogHeaders.erase(PsyNetLogHeaders.begin());
            if (!PsyNetLogBodies.empty())
                PsyNetLogBodies.erase(PsyNetLogBodies.begin());
        }
    }

    void PushPsyNetLogEntry(const std::string& summary, const std::string& headers, const std::string& body)
    {
        PsyNetLogMessages.push_back(summary);
        PsyNetLogHeaders.push_back(headers);
        PsyNetLogBodies.push_back(body);
        PsyNetStatusSummary = summary;
        TrimPsyNetLogs();
    }

    std::string GetHeaderValue(const TMap<FString, FString>& headerMap, const std::string& key)
    {
        for (int i = 0; i < headerMap.size(); ++i)
        {
            if (headerMap.at_index(i).Key.ToString() == key)
                return headerMap.at_index(i).Value.ToString();
        }

        return "";
    }

    std::string BuildHeaderDump(const TMap<FString, FString>& headerMap)
    {
        std::string headers;
        for (int i = 0; i < headerMap.size(); ++i)
        {
            headers += headerMap.at_index(i).Key.ToString();
            headers += ": ";
            headers += headerMap.at_index(i).Value.ToString();
            headers += "\n";
        }

        return headers.empty() ? "No headers" : headers;
    }

    std::string FormatPsyNetService(const std::string& service, const std::string& version)
    {
        if (service.empty())
            return "Unknown";

        if (version.empty())
            return service;

        return service + " v" + version;
    }

    std::string FormatFallbackPsyNetService(const TMap<FString, FString>& headerMap)
    {
        const std::string service = GetHeaderValue(headerMap, "PsyService");
        const std::string version = GetHeaderValue(headerMap, "PsyServiceVersion");

        if (service.empty())
            return "Unknown";

        return "SERVICE" + service + (version.empty() ? "" : " v" + version);
    }

    int FromHexChar(char c)
    {
        switch (c)
        {
        default: return c - '0';
        case 'a':
        case 'A': return 10;
        case 'b':
        case 'B': return 11;
        case 'c':
        case 'C': return 12;
        case 'd':
        case 'D': return 13;
        case 'e':
        case 'E': return 14;
        case 'f':
        case 'F': return 15;
        }
    }

    char ToBase64Digit(int value)
    {
        static constexpr char kEncodeTable[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        return kEncodeTable[value & 0x3F];
    }

                                                                                                 
    std::string Base64Encode(const std::string& hexString)
    {
        std::string result;
        result.reserve(((hexString.size() * 2) + 2) / 3 + 4);

        size_t index = 0;
        while (index + 2 < hexString.size())
        {
            const int digit0 = FromHexChar(hexString[index + 0]);
            const int digit1 = FromHexChar(hexString[index + 1]);
            const int digit2 = FromHexChar(hexString[index + 2]);

            result.push_back(ToBase64Digit((digit0 << 2) + (digit1 >> 2)));
            result.push_back(ToBase64Digit(((digit1 & 3) << 4) + digit2));
            index += 3;
        }

        if (index + 1 < hexString.size())
        {
            const int digit0 = FromHexChar(hexString[index + 0]);
            const int digit1 = FromHexChar(hexString[index + 1]);

            result.push_back(ToBase64Digit((digit0 << 2) + (digit1 >> 2)));
            result.push_back(ToBase64Digit((digit1 & 3) << 4));
        }
        else if (index < hexString.size())
        {
            const int digit = FromHexChar(hexString[index]);
            result.push_back(ToBase64Digit(digit << 2));
        }

        while (result.size() % 4 != 0)
            result.push_back('=');

        return result;
    }

    std::string GetQualityName(int quality)
    {
        switch (quality)
        {
        case 1: return "Uncommon";
        case 2: return "Rare";
        case 3: return "VeryRare";
        case 4: return "Import";
        case 5: return "Exotic";
        case 6: return "BlackMarket";
        case 7: return "Premium";
        case 8: return "Limited";
        case 9: return "Legacy";
        default: return "";
        }
    }

    std::string ProductInstanceIDToHexString(const FProductInstanceID& instanceId)
    {
        return UInstanceIDUtils_TA::ToHexString(instanceId).ToString();
    }

    int JsonValueToInt(const json& value)
    {
        try
        {
            if (value.is_number_integer())
                return value.get<int>();
            if (value.is_string())
                return std::stoi(value.get<std::string>());
        }
        catch (...)
        {
        }

        return 0;
    }

    bool IsSafeUnlockProduct(UProduct_TA* product, int containerProductId)
    {
        if (!product)
            return false;

        try
        {
            const int productId = product->GetID();
            if (productId <= 0 || productId == containerProductId)
                return false;

            if (product->IsContainer() || product->IsContainerKey() || product->IsCurrency() || product->IsBlueprint() || product->IsSchematic())
                return false;

            if (product->Label.ToString().empty())
                return false;

            if (product->AssetPath.ToString().empty() && product->GetThumbnailAssetPath().ToString().empty())
                return false;

            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    UProduct_TA* SelectUnlockProduct(UProductDatabase_TA* productDatabase, std::vector<int> candidates, int containerProductId)
    {
        if (!productDatabase || candidates.empty())
            return nullptr;

        std::shuffle(candidates.begin(), candidates.end(), PsyNetRng());

        for (int productId : candidates)
        {
            if (productId <= 0)
                continue;

            UProduct_TA* product = nullptr;
            try
            {
                product = productDatabase->GetProduct(productId);
            }
            catch (...)
            {
                product = nullptr;
            }

            if (IsSafeUnlockProduct(product, containerProductId))
                return product;
        }

        return nullptr;
    }

    void EnsureDropPools()
    {
        if (g_PsyNetState.PoolsBuilt)
            return;

        UProductDatabase_TA* productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
        if (!productDatabase)
            return;

        auto addProduct = [](std::vector<int>& pool, UProduct_TA* product)
        {
            if (product)
                pool.push_back(product->GetID());
        };

        for (UProduct_TA* product : productDatabase->Products_New)
        {
            if (!product)
                continue;

            switch (product->Quality)
            {
            case EProductQuality::EPQ_Uncommon: addProduct(g_PsyNetState.UncommonProducts, product); break;
            case EProductQuality::EPQ_Rare: addProduct(g_PsyNetState.RareProducts, product); break;
            case EProductQuality::EPQ_VeryRare: addProduct(g_PsyNetState.VeryRareProducts, product); break;
            case EProductQuality::EPQ_Import: addProduct(g_PsyNetState.ImportProducts, product); break;
            case EProductQuality::EPQ_Exotic: addProduct(g_PsyNetState.ExoticProducts, product); break;
            case EProductQuality::EPQ_BlackMarket: addProduct(g_PsyNetState.BlackMarketProducts, product); break;
            default: break;
            }
        }

        g_PsyNetState.PoolsBuilt = true;
    }

    int GetContainerProductIdFromRequest(URPCQueue_X_eventCreateBatchSingleRPC_Params* requestMessageParams)
    {
        if (!requestMessageParams)
            return 0;

        USaveData_TA* saveData = Instances.GetSaveData();
        if (!saveData)
            return 0;

        auto* unlockContainer = reinterpret_cast<URPC_MicroTransactions_UnlockContainer_TA*>(requestMessageParams->RPC.RPC);
        if (!unlockContainer)
            return 0;

        for (FProductInstanceID& instanceId : unlockContainer->InstanceIDs)
        {
            UOnlineProduct_TA* product = saveData->GetOnlineProduct(instanceId);
            if (product)
                return product->ProductID;
        }

        return 0;
    }

    std::vector<FProductInstanceID> GetTradeInInstanceIdsFromRequest(URPCQueue_X_eventCreateBatchSingleRPC_Params* requestMessageParams)
    {
        std::vector<FProductInstanceID> instanceIds;
        if (!requestMessageParams)
            return instanceIds;

        auto* tradeIn = reinterpret_cast<URPC_ProductsTradeIn_TA*>(requestMessageParams->RPC.RPC);
        if (!tradeIn)
            return instanceIds;

        for (FProductInstanceID& instanceId : tradeIn->ProductInstances)
        {
            instanceIds.push_back(instanceId);
        }

        return instanceIds;
    }

    std::string GetRedeemCodeFromRequest(URPCQueue_X_eventCreateBatchSingleRPC_Params* requestMessageParams)
    {
        if (!requestMessageParams)
            return "";

        auto* redeemCode = reinterpret_cast<URPC_RedeemCode_TA*>(requestMessageParams->RPC.RPC);
        if (!redeemCode)
            return "";

        return redeemCode->Code.ToString();
    }

    bool TryGetShopPurchaseRequestData(URPCQueue_X_eventCreateBatchSingleRPC_Params* requestMessageParams, PsyNetRequestInfo& outRequestInfo)
    {
        if (!requestMessageParams)
            return false;

        auto* purchaseItem = reinterpret_cast<URPC_PurchaseItemFromShop_TA*>(requestMessageParams->RPC.RPC);
        if (!purchaseItem)
            return false;

        outRequestInfo.ShopPurchaseCostId = purchaseItem->ShopItemCostID;
        outRequestInfo.ShopPurchaseShopId = purchaseItem->ShopID;
        outRequestInfo.ShopPurchaseDiscountId = purchaseItem->ShopDiscountID;
        outRequestInfo.ShopPurchaseCount = (std::max)(1, purchaseItem->Count);
        return outRequestInfo.ShopPurchaseCostId > 0 && outRequestInfo.ShopPurchaseShopId > 0;
    }

    std::vector<int> GetCatalogCandidatesForContainer(int containerProductId)
    {
        std::vector<int> candidates;

        if (containerProductId <= 0 || g_PsyNetState.CatalogJSON.empty())
            return candidates;

        try
        {
            json catalog = json::parse(g_PsyNetState.CatalogJSON);
            if (!catalog.contains("Result") || !catalog["Result"].contains("ContainerDrops"))
                return candidates;

            for (const json& container : catalog["Result"]["ContainerDrops"])
            {
                if (!container.contains("ProductID") || JsonValueToInt(container["ProductID"]) != containerProductId)
                    continue;

                if (!container.contains("Drops") || !container["Drops"].is_array())
                    continue;

                for (const json& drop : container["Drops"])
                {
                    if (drop.contains("ProductID"))
                    {
                        const int productId = JsonValueToInt(drop["ProductID"]);
                        if (productId > 0)
                            candidates.push_back(productId);
                    }
                }

                break;
            }
        }
        catch (...)
        {
        }

        return candidates;
    }

    std::vector<int> GetFallbackCandidatesForContainer(int containerProductId)
    {
        EnsureDropPools();

        switch (containerProductId)
        {
        case 5298: return g_PsyNetState.BlackMarketProducts;
        case 5299: return g_PsyNetState.ExoticProducts;
        case 5300: return g_PsyNetState.ImportProducts;
        case 5301: return g_PsyNetState.RareProducts;
        case 5302: return g_PsyNetState.UncommonProducts;
        case 5303: return g_PsyNetState.VeryRareProducts;
        default:
            break;
        }

        std::vector<int> merged;
        merged.insert(merged.end(), g_PsyNetState.UncommonProducts.begin(), g_PsyNetState.UncommonProducts.end());
        merged.insert(merged.end(), g_PsyNetState.RareProducts.begin(), g_PsyNetState.RareProducts.end());
        merged.insert(merged.end(), g_PsyNetState.VeryRareProducts.begin(), g_PsyNetState.VeryRareProducts.end());
        merged.insert(merged.end(), g_PsyNetState.ImportProducts.begin(), g_PsyNetState.ImportProducts.end());
        merged.insert(merged.end(), g_PsyNetState.ExoticProducts.begin(), g_PsyNetState.ExoticProducts.end());
        merged.insert(merged.end(), g_PsyNetState.BlackMarketProducts.begin(), g_PsyNetState.BlackMarketProducts.end());
        return merged;
    }

    std::vector<int> GetFallbackCandidatesForTradeInQuality(int tradeInQuality)
    {
        EnsureDropPools();

        switch (static_cast<EProductQuality>(tradeInQuality))
        {
        case EProductQuality::EPQ_Uncommon:
            return g_PsyNetState.RareProducts;
        case EProductQuality::EPQ_Rare:
            return g_PsyNetState.VeryRareProducts;
        case EProductQuality::EPQ_VeryRare:
            return g_PsyNetState.ImportProducts;
        case EProductQuality::EPQ_Import:
            return g_PsyNetState.ExoticProducts;
        case EProductQuality::EPQ_Exotic:
            return g_PsyNetState.BlackMarketProducts;
        default:
            break;
        }

        return {};
    }

    int ParsePsyTimeValue(const std::string& psytime)
    {
        try
        {
            return std::stoi(psytime);
        }
        catch (...)
        {
            return static_cast<int>(std::time(nullptr));
        }
    }

    json OnlineProductDataToJson(const FOnlineProductData& productData)
    {
        json productJson;
        productJson["ProductID"] = productData.ProductID;
        productJson["InstanceID"] = ProductInstanceIDToHexString(productData.InstanceID);
        productJson["Attributes"] = json::array();
        productJson["SeriesID"] = productData.SeriesID;
        productJson["TradeHold"] = productData.TradeHold;
        productJson["AddedTimestamp"] = productData.AddedTimestamp;
        productJson["UpdatedTimestamp"] = productData.AddedTimestamp;

        for (int attributeIndex = 0; attributeIndex < productData.Attributes.size(); ++attributeIndex)
        {
            const FOnlineProductAttribute& attribute = productData.Attributes[attributeIndex];
            productJson["Attributes"].push_back({
                {"Key", attribute.Key.ToString()},
                {"Value", attribute.Value.ToString()}
            });
        }

        return productJson;
    }

    json CurrencyDataToJson(const FCurrency& currency)
    {
        return {
            {"ID", currency.Id != 0 ? currency.Id : currency.CurrencyID},
            {"Amount", currency.Amount}
        };
    }

    std::string GetProductAttributeValue(const FOnlineProductData& productData, const std::string& key)
    {
        const std::string normalizedKey = ToLowerAscii(key);
        for (int attributeIndex = 0; attributeIndex < productData.Attributes.size(); ++attributeIndex)
        {
            const FOnlineProductAttribute& attribute = productData.Attributes[attributeIndex];
            if (ToLowerAscii(attribute.Key.ToString()) == normalizedKey)
                return attribute.Value.ToString();
        }

        return "";
    }

    FOnlineProductData CreateGrantedProductData(const FOnlineProductData& sourceProduct, uint64_t timestamp)
    {
        FOnlineProductData grantedProduct = sourceProduct;
        grantedProduct.InstanceID = Items.GeneratePIID(sourceProduct.ProductID);
        grantedProduct.AddedTimestamp = timestamp;
        grantedProduct.TradeHold = 0;
        return grantedProduct;
    }

    FCurrency CreateGrantedCurrencyData(int currencyId, int amount, uint64_t timestamp)
    {
        FCurrency grantedCurrency{};
        grantedCurrency.CurrencyID = currencyId;
        grantedCurrency.Id = currencyId;
        grantedCurrency.Amount = amount;
        grantedCurrency.UpdatedTimestamp = timestamp;

        USaveData_TA* saveData = Instances.GetSaveData();
        if (!saveData)
            return grantedCurrency;

        UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
        if (!onlinePlayer || !onlinePlayer->Wallet)
            return grantedCurrency;

        grantedCurrency = onlinePlayer->Wallet->GetCurrency(currencyId);
        grantedCurrency.CurrencyID = currencyId;
        grantedCurrency.Id = currencyId;
        grantedCurrency.Amount = amount;
        grantedCurrency.UpdatedTimestamp = timestamp;
        return grantedCurrency;
    }

    bool TryParseProductDataArray(const json& productsJson, TArray<FOnlineProductData>& outProducts, uint64_t fallbackTimestamp)
    {
        if (!productsJson.is_array())
            return false;

        bool parsedAny = false;
        for (const json& productJson : productsJson)
        {
            if (!productJson.is_object() || !productJson.contains("ProductID"))
                continue;

            FOnlineProductData productData{};
            productData.ProductID = JsonValueToInt(productJson["ProductID"]);
            if (productData.ProductID <= 0)
                continue;

            productData.InstanceID = Items.GeneratePIID(productData.ProductID);
            productData.SeriesID = productJson.contains("SeriesID") ? JsonValueToInt(productJson["SeriesID"]) : 0;
            productData.TradeHold = productJson.contains("TradeHold") ? JsonValueToInt(productJson["TradeHold"]) : 0;
            productData.AddedTimestamp = productJson.contains("AddedTimestamp")
                ? static_cast<uint64_t>(JsonValueToInt(productJson["AddedTimestamp"]))
                : fallbackTimestamp;

            if (productJson.contains("Attributes") && productJson["Attributes"].is_array())
            {
                for (const json& attributeJson : productJson["Attributes"])
                {
                    if (!attributeJson.is_object() || !attributeJson.contains("Key") || !attributeJson.contains("Value"))
                        continue;

                    const std::string key = JsonToString(attributeJson["Key"]);
                    const std::string value = JsonToString(attributeJson["Value"]);
                    const std::wstring wideKey(key.begin(), key.end());
                    FOnlineProductAttribute attribute{};
                    attribute.Key = FName(wideKey.c_str());
                    attribute.Value = Format::ToFString(value);
                    productData.Attributes.push_back(attribute);
                }
            }

            outProducts.push_back(productData);
            parsedAny = true;
        }

        return parsedAny;
    }

    bool TryParseCurrencyDataArray(const json& currenciesJson, TArray<FCurrency>& outCurrencies, uint64_t fallbackTimestamp)
    {
        if (!currenciesJson.is_array())
            return false;

        bool parsedAny = false;
        for (const json& currencyJson : currenciesJson)
        {
            if (!currencyJson.is_object() || !currencyJson.contains("Amount"))
                continue;

            int currencyId = 0;
            if (currencyJson.contains("ID"))
                currencyId = JsonValueToInt(currencyJson["ID"]);
            else if (currencyJson.contains("Id"))
                currencyId = JsonValueToInt(currencyJson["Id"]);

            const int amount = JsonValueToInt(currencyJson["Amount"]);
            if (currencyId <= 0 || amount == 0)
                continue;

            outCurrencies.push_back(CreateGrantedCurrencyData(currencyId, amount, fallbackTimestamp));
            parsedAny = true;
        }

        return parsedAny;
    }

    void ApplyLocalCurrencyGrants(const TArray<FCurrency>& grantedCurrencies)
    {
        if (grantedCurrencies.size() <= 0)
            return;

        USaveData_TA* saveData = Instances.GetSaveData();
        if (!saveData)
            return;

        UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
        if (!onlinePlayer || !onlinePlayer->Wallet)
            return;

        UWallet_TA* wallet = onlinePlayer->Wallet;
        TArray<FCurrency> updatedCurrencies;

        for (int currencyIndex = 0; currencyIndex < grantedCurrencies.size(); ++currencyIndex)
        {
            const FCurrency& grantedCurrency = grantedCurrencies[currencyIndex];
            const int currencyId = grantedCurrency.Id != 0 ? grantedCurrency.Id : grantedCurrency.CurrencyID;
            if (currencyId <= 0)
                continue;

            FCurrency currency = wallet->GetCurrency(currencyId);
            currency.Amount += grantedCurrency.Amount;
            currency.CurrencyID = currencyId;
            currency.Id = currencyId;
            currency.UpdatedTimestamp = grantedCurrency.UpdatedTimestamp;
            updatedCurrencies.push_back(currency);
        }

        if (updatedCurrencies.size() <= 0)
            return;

        wallet->UpdateWalletCurrencies(updatedCurrencies);
        wallet->EventWalletUpdated(wallet);
    }

    void RefreshPostGrantUi(const TArray<FOnlineProductData>& grantedProducts)
    {
        bool grantedTitle = false;
        for (int productIndex = 0; productIndex < grantedProducts.size(); ++productIndex)
        {
            const FOnlineProductData& productData = grantedProducts[productIndex];
            if (!GetProductAttributeValue(productData, "TitleId").empty())
            {
                grantedTitle = true;
                break;
            }
        }

        if (auto* playerTitles = Instances.GetInstanceOf<UGFxData_PlayerTitles_TA>())
        {
            if (grantedTitle)
                playerTitles->UpdatePlayerTitles();
        }

        if (auto* tradeInData = Instances.GetInstanceOf<UGFxData_ProductTradeIn_TA>())
        {
            tradeInData->ClearTradeIns();
            tradeInData->OnTradeInComplete();
        }
    }

    void ApplyLocalProductGrants(const TArray<FOnlineProductData>& grantedProducts)
    {
        if (grantedProducts.size() <= 0)
            return;

        USaveData_TA* saveData = Instances.GetSaveData();
        if (!saveData)
            return;

        UGFxData_PlayerTitles_TA* playerTitles = Instances.GetInstanceOf<UGFxData_PlayerTitles_TA>();
        for (int productIndex = 0; productIndex < grantedProducts.size(); ++productIndex)
        {
            const FOnlineProductData& productData = grantedProducts[productIndex];
            UOnlineProduct_TA* onlineProduct = saveData->GiveOnlineProductDataNoNotify(productData);
            if (playerTitles && onlineProduct && !GetProductAttributeValue(productData, "TitleId").empty())
                playerTitles->HandleNewOnlineProduct(saveData, onlineProduct, FString(L""));
        }
    }

    void ApplyParsedResultRewards(const json& resultJson, uint64_t timestamp)
    {
        if (!resultJson.is_object())
            return;

        TArray<FOnlineProductData> grantedProducts;
        TArray<FCurrency> grantedCurrencies;

        if (resultJson.contains("Drops"))
            TryParseProductDataArray(resultJson["Drops"], grantedProducts, timestamp);
        if (resultJson.contains("ProductData"))
            TryParseProductDataArray(resultJson["ProductData"], grantedProducts, timestamp);
        if (resultJson.contains("CurrencyData"))
            TryParseCurrencyDataArray(resultJson["CurrencyData"], grantedCurrencies, timestamp);
        if (resultJson.contains("Currencies"))
            TryParseCurrencyDataArray(resultJson["Currencies"], grantedCurrencies, timestamp);

        if (grantedProducts.size() <= 0 && grantedCurrencies.size() <= 0)
            return;

        ApplyLocalProductGrants(grantedProducts);
        ApplyLocalCurrencyGrants(grantedCurrencies);
        RefreshPostGrantUi(grantedProducts);
    }

    bool TryBuildShopPurchaseResult(const PsyNetRequestInfo& requestInfo, uint64_t timestamp, TArray<FOnlineProductData>& outProducts, TArray<FCurrency>& outCurrencies)
    {
        if (requestInfo.ShopPurchaseShopId <= 0 || requestInfo.ShopPurchaseCostId <= 0)
            return false;

        UGFxData_Shops_TA* shopsData = Instances.GetInstanceOf<UGFxData_Shops_TA>();
        if (!shopsData)
            return false;

        FShopsMapEntry shopEntry = shopsData->GetCatalogueFromShopID(requestInfo.ShopPurchaseShopId);
        UGFxData_ShopCatalogue_TA* catalogue = shopEntry.Catalogue;
        if (!catalogue)
            return false;

        TArray<FShopItem> shopItems = catalogue->GetShopItems();
        if (shopItems.size() <= 0)
            return false;

        const int purchaseCount = (std::max)(1, requestInfo.ShopPurchaseCount);

        for (int shopItemIndex = 0; shopItemIndex < shopItems.size(); ++shopItemIndex)
        {
            const FShopItem& shopItem = shopItems[shopItemIndex];
            bool matchedCost = false;
            for (int costIndex = 0; costIndex < shopItem.Costs.size(); ++costIndex)
            {
                const FShopCost& shopCost = shopItem.Costs[costIndex];
                if (shopCost.ShopItemCostID == requestInfo.ShopPurchaseCostId)
                {
                    matchedCost = true;
                    break;
                }
            }

            if (!matchedCost)
                continue;

            for (int deliverableIndex = 0; deliverableIndex < shopItem.DeliverableProducts.size(); ++deliverableIndex)
            {
                const FShopDeliverable& deliverable = shopItem.DeliverableProducts[deliverableIndex];
                if (deliverable.Product.ProductID <= 0)
                    continue;

                const int deliverableCount = (std::max)(1, deliverable.Count) * purchaseCount;
                for (int index = 0; index < deliverableCount; ++index)
                {
                    outProducts.push_back(CreateGrantedProductData(deliverable.Product, timestamp));
                }
            }

            for (int currencyIndex = 0; currencyIndex < shopItem.DeliverableCurrencies.size(); ++currencyIndex)
            {
                const FShopCurrencyInfo& deliverableCurrency = shopItem.DeliverableCurrencies[currencyIndex];
                const int deliverableAmount = deliverableCurrency.Amount * purchaseCount;
                if (deliverableCurrency.Id <= 0 || deliverableAmount == 0)
                    continue;

                outCurrencies.push_back(CreateGrantedCurrencyData(deliverableCurrency.Id, deliverableAmount, timestamp));
            }

            return outProducts.size() > 0 || outCurrencies.size() > 0;
        }

        return false;
    }

    void AddOptionalAttribute(json& productJson, const char* key, const std::string& value)
    {
        if (value.empty())
            return;

        productJson["Attributes"].push_back({
            {"Key", key},
            {"Value", value}
        });
    }

    bool TryReadRedeemTemplate(std::string& outTemplate)
    {
        const std::string resourcePath = GetKingModResourcesDirectory() + "\\customredeemcodes.txt";
        const std::string fallbackPath = "customredeemcodes.txt";

        for (const std::string& path : { resourcePath, fallbackPath })
        {
            std::ifstream input(path, std::ios::in | std::ios::binary);
            if (!input.is_open())
                continue;

            outTemplate.assign((std::istreambuf_iterator<char>(input)), std::istreambuf_iterator<char>());
            if (!outTemplate.empty())
                return true;
        }

        return false;
    }

    void SignPsyNetResponse(UPsyNetMessage_X* message, const std::string& psytime, const std::string& psyservice)
    {
        if (!message || !message->Headers)
            return;

        if (psytime != "0" && !ContainsSubstring(psyservice, "SERVICEDSR"))
        {
            const std::string key = KINGMOD_PSYNET_SIGNING_KEY;
            if (key.empty()) return;
            const std::string data = psytime + "-" + message->GetBodyText().ToString();

            std::vector<uint8_t> psySigBytes(SHA256_HASH_SIZE);
            hmac_sha256(key.data(), key.size(), data.data(), data.size(), psySigBytes.data(), psySigBytes.size());

            std::stringstream hexDigest;
            for (uint8_t byte : psySigBytes)
            {
                hexDigest << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(byte);
            }

            const std::string psySig = Base64Encode(hexDigest.str());
            message->Headers->Set(L"PsySig", Format::ToFString(psySig));
        }
    }

    bool TryEditUnlockContainerResponse(UPsyNetMessage_X* message, const std::string& psyservice, int containerProductId)
    {
        if (!EnableDropUnlockBypass || !message)
            return false;

        if (!ContainsSubstring(psyservice, "Products/UnlockContainer"))
            return false;

        const std::string originalBody = message->GetBodyText().ToString();
        if (!ContainsSubstring(originalBody, "InventoryOutOfSync") && !ContainsSubstring(originalBody, "AccessDenied"))
            return false;

        std::vector<int> candidates = GetCatalogCandidatesForContainer(containerProductId);
        if (candidates.empty())
            candidates = GetFallbackCandidatesForContainer(containerProductId);

        UProductDatabase_TA* productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
        if (!productDatabase)
            return false;

        UProduct_TA* product = SelectUnlockProduct(productDatabase, candidates, containerProductId);
        if (!product)
            return false;

        const int productId = product->GetID();
        if (productId <= 0)
            return false;

        json finalProduct;
        finalProduct["ProductID"] = productId;

        const FProductInstanceID instanceId = Items.GeneratePIID(productId);
        finalProduct["InstanceID"] = ProductInstanceIDToHexString(instanceId);
        finalProduct["Attributes"] = json::array();

        if (product->IsPaintable())
        {
            const int paintId = PickRandomValue(g_PsyNetState.WeightedPaintValues, 0);
            if (paintId != 0)
            {
                finalProduct["Attributes"].push_back({
                    {"Key", "Painted"},
                    {"Value", std::to_string(paintId)}
                });
            }
        }

        const int certId = PickRandomValue(g_PsyNetState.WeightedCertValues, 0);
        if (certId != 0)
        {
            finalProduct["Attributes"].push_back({
                {"Key", "Certified"},
                {"Value", std::to_string(certId)}
            });
        }

        const std::string qualityName = GetQualityName(static_cast<int>(product->Quality));
        if (!qualityName.empty())
        {
            finalProduct["Attributes"].push_back({
                {"Key", "Quality"},
                {"Value", qualityName}
            });
        }

        json finalBody;
        finalBody["Result"]["Drops"] = json::array({ finalProduct });
        message->SetBodyText(Format::ToFString(finalBody.dump()));
        return true;
    }

    bool TryEditTradeInResponse(UPsyNetMessage_X* message, const std::string& psyservice, const std::vector<FProductInstanceID>& tradeInInstanceIds, const std::string& psytime)
    {
        if ((!EnableDropUnlockBypass && !DisableSyncData) || !message)
            return false;

        if (!ContainsSubstring(psyservice, "Products/TradeIn"))
            return false;

        if (tradeInInstanceIds.empty())
            return false;

        json responseBody;
        try
        {
            responseBody = json::parse(message->GetBodyText().ToString());
        }
        catch (...)
        {
            return false;
        }

        std::string errorType;
        if (responseBody.contains("Error") && responseBody["Error"].contains("Type"))
            errorType = JsonToString(responseBody["Error"]["Type"]);

                                                                                 
                                                                                   
                                                                              
        if (!EnableDropUnlockBypass && !DisableSyncData && errorType != "InventoryOutOfSync")
            return false;

        USaveData_TA* saveData = Instances.GetSaveData();
        UProductDatabase_TA* productDatabase = Instances.GetInstanceOf<UProductDatabase_TA>();
        if (!saveData || !productDatabase)
            return false;

        int tradeInQuality = 0;
        int tradeInSeriesId = 0;
        bool rewardCanBePainted = false;

        for (const FProductInstanceID& instanceId : tradeInInstanceIds)
        {
            UOnlineProduct_TA* onlineProduct = saveData->GetOnlineProduct(const_cast<FProductInstanceID&>(instanceId));
            if (!onlineProduct)
                continue;

            UProduct_TA* product = nullptr;
            try
            {
                product = productDatabase->GetProduct(onlineProduct->ProductID);
            }
            catch (...)
            {
                product = nullptr;
            }

            if (!product)
                continue;

            tradeInQuality = static_cast<int>(product->Quality);
            rewardCanBePainted = product->IsPaintable();
            tradeInSeriesId = onlineProduct->SeriesID;
            break;
        }

        if (tradeInQuality == 0)
            return false;

        std::vector<int> candidates = GetFallbackCandidatesForTradeInQuality(tradeInQuality);
        if (candidates.empty())
            return false;

        UProduct_TA* rewardProduct = SelectUnlockProduct(productDatabase, candidates, 0);
        if (!rewardProduct)
            return false;

        const int rewardProductId = rewardProduct->GetID();
        if (rewardProductId <= 0)
            return false;

        json finalProduct;
        finalProduct["ProductID"] = rewardProductId;
        finalProduct["InstanceID"] = ProductInstanceIDToHexString(Items.GeneratePIID(rewardProductId));
        finalProduct["Attributes"] = json::array();
        finalProduct["SeriesID"] = tradeInSeriesId;
        finalProduct["AddedTimestamp"] = ParsePsyTimeValue(psytime);
        finalProduct["UpdatedTimestamp"] = ParsePsyTimeValue(psytime);

        if (rewardCanBePainted && rewardProduct->IsPaintable())
        {
            const int paintId = PickRandomValue(g_PsyNetState.WeightedPaintValues, 0);
            if (paintId != 0)
                AddOptionalAttribute(finalProduct, "Painted", std::to_string(paintId));
        }

        const int certId = PickRandomValue(g_PsyNetState.WeightedCertValues, 0);
        if (certId != 0)
            AddOptionalAttribute(finalProduct, "Certified", std::to_string(certId));

        AddOptionalAttribute(finalProduct, "Quality", GetQualityName(static_cast<int>(rewardProduct->Quality)));

        json finalBody;
        finalBody["Result"]["Drops"] = json::array({ finalProduct });
        message->SetBodyText(Format::ToFString(finalBody.dump()));
        ApplyParsedResultRewards(finalBody["Result"], static_cast<uint64_t>(ParsePsyTimeValue(psytime)));
        return true;
    }

    bool TryEditRedeemCodeResponse(UPsyNetMessage_X* message, const std::string& psyservice, const std::string& redeemCode, const std::string& psytime)
    {
        if (!EnableDropUnlockBypass || !message)
            return false;

        if (!ContainsSubstring(psyservice, "Codes/RedeemCode"))
            return false;

        if (redeemCode.empty())
            return false;

        const std::string normalizedCode = ToLowerAscii(redeemCode);
        if (normalizedCode == "kingmod")
        {
            const uint64_t ts = static_cast<uint64_t>(ParsePsyTimeValue(psytime));

                                              
            auto makeDrop = [&](int productId, const json& attributes) {
                json drop;
                drop["ProductID"] = std::to_string(productId);
                drop["InstanceID"] = ProductInstanceIDToHexString(Items.GeneratePIID(productId));
                drop["Attributes"] = attributes;
                drop["SeriesID"] = 0;
                drop["AddedTimestamp"] = ts;
                drop["UpdatedTimestamp"] = ts;
                return drop;
            };

            json drops = json::array();

                                                                        
                                                                 
            drops.push_back(makeDrop(34, json::array()));                 
            drops.push_back(makeDrop(24, json::array()));               
            drops.push_back(makeDrop(33, json::array()));              

                                                                            
                                                                              
                                                                               
            drops.push_back(makeDrop(32, json::array({
                { {"Key", "TitleId"}, {"Value", "Developer"} }
            })));

            json finalBody;
            finalBody["Result"]["Drops"] = drops;
            message->SetBodyText(Format::ToFString(finalBody.dump()));
            ApplyParsedResultRewards(finalBody["Result"], ts);
            return true;
        }

        return false;
    }

    bool TryEditShopPurchaseResponse(UPsyNetMessage_X* message, const std::string& psyservice, const PsyNetRequestInfo& requestInfo, const std::string& psytime)
    {
        if (!EnableDropUnlockBypass || !message)
            return false;

        if (!ContainsSubstring(psyservice, "Shops/PurchaseItemFromShop"))
            return false;

        if (requestInfo.ShopPurchaseShopId <= 0 || requestInfo.ShopPurchaseCostId <= 0)
            return false;

        json responseBody;
        try
        {
            responseBody = json::parse(message->GetBodyText().ToString());
        }
        catch (...)
        {
            return false;
        }

        std::string errorType;
        if (responseBody.contains("Error") && responseBody["Error"].contains("Type"))
            errorType = JsonToString(responseBody["Error"]["Type"]);

        if (errorType != "ShopNotEnoughCurrency")
            return false;

        const uint64_t timestamp = static_cast<uint64_t>(ParsePsyTimeValue(psytime));
        TArray<FOnlineProductData> purchasedProducts;
        TArray<FCurrency> purchasedCurrencies;
        if (!TryBuildShopPurchaseResult(requestInfo, timestamp, purchasedProducts, purchasedCurrencies))
            return false;

                                                                             
                                                                                
                                                                         
                                                                              
                                                                      
                                      
        TArray<FCurrency> deductedCurrencies;
        {
            UGFxData_Shops_TA* shopsData = Instances.GetInstanceOf<UGFxData_Shops_TA>();
            USaveData_TA* saveData = Instances.GetSaveData();
            UWallet_TA* wallet = nullptr;
            if (saveData) {
                UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
                if (onlinePlayer) wallet = onlinePlayer->Wallet;
            }
            if (!wallet)
                wallet = Instances.GetInstanceOf<UWallet_TA>();

            if (shopsData && wallet)
            {
                FShopsMapEntry shopEntry = shopsData->GetCatalogueFromShopID(requestInfo.ShopPurchaseShopId);
                if (shopEntry.Catalogue)
                {
                    TArray<FShopItem> shopItems = shopEntry.Catalogue->GetShopItems();
                    const int purchaseCount = (std::max)(1, requestInfo.ShopPurchaseCount);

                    for (int shopItemIndex = 0; shopItemIndex < shopItems.size(); ++shopItemIndex)
                    {
                        const FShopItem& shopItem = shopItems[shopItemIndex];
                        for (int costIndex = 0; costIndex < shopItem.Costs.size(); ++costIndex)
                        {
                            const FShopCost& shopCost = shopItem.Costs[costIndex];
                            if (shopCost.ShopItemCostID != requestInfo.ShopPurchaseCostId)
                                continue;

                            for (int priceIdx = 0; priceIdx < shopCost.Price.size(); ++priceIdx)
                            {
                                const FShopPrice& p = shopCost.Price[priceIdx];
                                if (p.Id <= 0 || p.Amount <= 0)
                                    continue;

                                int cost = p.Amount * purchaseCount;
                                for (int wi = 0; wi < wallet->Currencies.size(); ++wi)
                                {
                                    if (wallet->Currencies[wi].Id == p.Id)
                                    {
                                        int before = wallet->Currencies[wi].Amount;
                                        wallet->Currencies[wi].Amount = (std::max)(0, before - cost);
                                        wallet->Currencies[wi].UpdatedTimestamp = timestamp;
                                        deductedCurrencies.push_back(wallet->Currencies[wi]);
                                        break;
                                    }
                                }
                            }
                            break;                                                    
                        }
                    }
                }
            }
        }

        json finalBody;
        finalBody["Result"]["ProductData"] = json::array();
        finalBody["Result"]["CurrencyData"] = json::array();

        for (const FOnlineProductData& productData : purchasedProducts)
        {
            finalBody["Result"]["ProductData"].push_back(OnlineProductDataToJson(productData));
        }

                                                                           
                                                                            
                                                                  
        const TArray<FCurrency>& currenciesForResponse =
            (deductedCurrencies.size() > 0) ? deductedCurrencies : purchasedCurrencies;

        for (int32_t ci = 0; ci < currenciesForResponse.size(); ++ci)
        {
            finalBody["Result"]["CurrencyData"].push_back(CurrencyDataToJson(currenciesForResponse[ci]));
        }

        ApplyLocalProductGrants(purchasedProducts);
                                                                             
                                                                          
                                                                            
        if (deductedCurrencies.size() == 0)
            ApplyLocalCurrencyGrants(purchasedCurrencies);

        if (auto* shopsData = Instances.GetInstanceOf<UGFxData_Shops_TA>())
        {
                                                                            
                                                                            
                                                                                
                                                               
            shopsData->HandlePurchaseSuccess(
                requestInfo.ShopPurchaseShopId,
                requestInfo.ShopPurchaseCostId,
                requestInfo.ShopPurchaseDiscountId,
                (std::max)(1, requestInfo.ShopPurchaseCount),
                purchasedProducts,
                purchasedCurrencies);
            shopsData->OnPurchaseSuccess();

                                                                              
                                                                                
                                                                                
                                                                                 
                                              
            FShopsMapEntry ownedEntry = shopsData->GetCatalogueFromShopID(requestInfo.ShopPurchaseShopId);
            if (ownedEntry.Catalogue)
                ownedEntry.Catalogue->ClearLastOwnedCacheTime();

            shopsData->RefreshOwnedProducts();
            shopsData->RefreshShopsViewed();
        }

        RefreshPostGrantUi(purchasedProducts);
        message->SetBodyText(Format::ToFString(finalBody.dump()));
        return true;
    }

    bool TryApplyWalletResponse(UPsyNetMessage_X* message, const std::string& psyservice)
    {
        if ((!EnableDropUnlockBypass && !DisableSyncData) || !message)
            return false;

        if (!ContainsSubstring(psyservice, "Shops/GetPlayerWallet"))
            return false;

        json bodyJson;
        try
        {
            bodyJson = json::parse(message->GetBodyText().ToString());
        }
        catch (...)
        {
            return false;
        }

        if (!bodyJson.contains("Result") || !bodyJson["Result"].contains("Currencies") || !bodyJson["Result"]["Currencies"].is_array())
            return false;

        USaveData_TA* saveData = Instances.GetSaveData();
        if (!saveData)
            return false;

        UOnlinePlayer_TA* onlinePlayer = saveData->GetOnlinePlayer();
        if (!onlinePlayer || !onlinePlayer->Wallet)
            return false;

        UWallet_TA* wallet = onlinePlayer->Wallet;
        TArray<FCurrency> updatedCurrencies;

        for (const json& currencyJson : bodyJson["Result"]["Currencies"])
        {
            if (!currencyJson.contains("ID") || !currencyJson.contains("Amount"))
                continue;

            const int currencyId = JsonValueToInt(currencyJson["ID"]);
            const int amount = JsonValueToInt(currencyJson["Amount"]);
            if (currencyId <= 0)
                continue;

            FCurrency currency = wallet->GetCurrency(currencyId);
            currency.Amount = amount;
            updatedCurrencies.push_back(currency);
        }

        if (updatedCurrencies.size() <= 0)
            return false;

        wallet->UpdateWalletCurrencies(updatedCurrencies);
        wallet->EventWalletUpdated(wallet);
        return true;
    }

    PsyNetRequestInfo ResolveResponseRequestInfo(const TMap<FString, FString>& headerMap)
    {
        PsyNetRequestInfo requestInfo;

        const std::string responseId = GetHeaderValue(headerMap, "PsyResponseID");
        if (!responseId.empty())
        {
            auto it = g_PsyNetState.PendingRequests.find(responseId);
            if (it != g_PsyNetState.PendingRequests.end())
            {
                requestInfo = it->second;
                g_PsyNetState.PendingRequests.erase(it);
                PsyNetPendingRequestCount = static_cast<int>(g_PsyNetState.PendingRequests.size());
                return requestInfo;
            }
        }

        requestInfo.Service = FormatFallbackPsyNetService(headerMap);
        return requestInfo;
    }
}

#define IM_PI                           3.14159265358979323846f

const float URotationToRadians = 3.1415926535f / 32768.0f;

FVector normalize(const FVector& vec) {
    float length = sqrt(vec.X * vec.X + vec.Y * vec.Y + vec.Z * vec.Z);
    if (length > 0.0f) {
        FVector result;
        result.X = vec.X / length;
        result.Y = vec.Y / length;
        result.Z = vec.Z / length;
        return result;
    }
    FVector zero;
    zero.X = 0.0f;
    zero.Y = 0.0f;
    zero.Z = 0.0f;
    return zero;
}

float deg_to_rad(float degrees) {
    return degrees * (IM_PI / 180.0f);
}

std::tuple<FVector, FVector, FVector> get_axes(FRotator rotation) {

    double pitch = rotation.Pitch * URotationToRadians;
    double yaw = rotation.Yaw * URotationToRadians;
    double roll = rotation.Roll * URotationToRadians;


    double SP = sin(pitch); double CP = cos(pitch);
    double SY = sin(yaw);   double CY = cos(yaw);
    double SR = sin(roll);  double CR = cos(roll);

    FVector axis_x, axis_y, axis_z;


    axis_x.X = CP * CY;
    axis_x.Y = CP * SY;
    axis_x.Z = SP;


    axis_y.X = SR * SP * CY - CR * SY;
    axis_y.Y = SR * SP * SY + CR * CY;
    axis_y.Z = -SR * CP;


    axis_z.X = -(CR * SP * CY + SR * SY);
    axis_z.Y = -(CR * SP * SY - SR * CY);
    axis_z.Z = CR * CP;

    return { axis_x, axis_y, axis_z };
}

FVector operator+(const FVector& a, const FVector& b) {
    return { a.X + b.X, a.Y + b.Y, a.Z + b.Z };
}

FVector operator*(const FVector& v, float s) {
    return { v.X * s, v.Y * s, v.Z * s };
}

FVector operator*(float s, const FVector& v) {
    return v * s;
}

PrivBallInfo GameEventHookModule::CurrentBall = { {0,0,0}, {0,0,0}, {0,0,0}, false };
bool GameEventHookModule::Debug = false;
Players GameEventHookModule::players = { {}, false };
bool GameEventHookModule::IsInGame = false;
bool GameEventHookModule::IsInReplayPlayback = false;
bool GameEventHookModule::IsInitialized = false;
AGameEvent_Soccar_TA* GameEventHookModule::CurrentGameEvent = nullptr;
bool GameEventHookModule::BallSpawnedFlag = false;
bool GameEventHookModule::SuperSonicAnnoyerEnabled = false;
GameTickPacket GameEventHookModule::CurrentGameTickPacket = GameTickPacket();
bool GameEventHookModule::AutoQueueEnabled = false;
int GameEventHookModule::AutoQueueDelaySeconds = 5;
bool GameEventHookModule::AutoQueueTriggered = false;
double GameEventHookModule::AutoQueueReadyAt = 0.0;
bool GameEventHookModule::AutoLeaveEnabled = false;
int GameEventHookModule::AutoLeaveDelaySeconds = 1;
bool GameEventHookModule::AutoLeaveTriggered = false;
double GameEventHookModule::AutoLeaveReadyAt = 0.0;
bool GameEventHookModule::AutoQueueDone = false;
bool GameEventHookModule::AutoLeaveDone = false;
bool GameEventHookModule::AutoQueuePolling = false;
bool GameEventHookModule::AutoLeavePolling = false;
bool GameEventHookModule::AutoQueueThreadRunning = false;
std::atomic<int> GameEventHookModule::BackgroundWorkers{ 0 };
FieldInfoPacket GameEventHookModule::CurrentFieldInfo;
bool GameEventHookModule::BoostPadTimers = false;
bool GameEventHookModule::Hitboxes;
bool GameEventHookModule::ControllerOverlay = false;
bool GameEventHookModule::TracersEnabled = false;
bool GameEventHookModule::VelocityArrowsEnabled = false;
bool GameEventHookModule::PlayerDistanceTextEnabled = false;
bool GameEventHookModule::OpponentBoostEnabled = false;
bool GameEventHookModule::UseTeamColorsForTracers = false;
bool GameEventHookModule::Ball3DSphereEnabled = false;
bool GameEventHookModule::BallPredictionEnabled = false;
bool GameEventHookModule::FlipIndicatorEnabled = false;
ImVec4 GameEventHookModule::BallPredictionColor = ImVec4(1.0f, 0.0f, 1.0f, 0.8f);
float GameEventHookModule::BallPredictionLineWidth = 2.5f;

ImVec4 GameEventHookModule::TracersColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 GameEventHookModule::VelocityArrowBallColor = ImVec4(1.0f, 0.65f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::VelocityArrowCarColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::PlayerDistanceTextColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 GameEventHookModule::OpponentBoostColor = ImVec4(0.0f, 0.7f, 1.0f, 0.9f);

float GameEventHookModule::OpponentBoostScale = 1.0f;
float GameEventHookModule::BoostPadMarkerScale = 1.0f;
ImVec4 GameEventHookModule::HitboxColor = ImVec4(0.0f, 1.0f, 1.0f, 0.8f);
int GameEventHookModule::HitboxMode = 0;
ImVec4 GameEventHookModule::Ball3DSphereColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::FlipIndicatorColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
float GameEventHookModule::FlipIndicatorSize = 2.0f;
ImVec2 GameEventHookModule::FlipIndicatorPos = {0.5f, 0.1f};
ImVec4 GameEventHookModule::FlipAvailableColor = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::FlipUnavailableColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

bool  GameEventHookModule::BallSpeedDisplayEnabled = false;
float GameEventHookModule::BallSpeedDisplayX = 0.5f;
float GameEventHookModule::BallSpeedDisplayY = 0.05f;
float GameEventHookModule::BallSpeedDisplaySize = 1.0f;
float GameEventHookModule::LastBallSpeed = 0.0f;

std::vector<GameEventHookModule::FavoriteEntry> GameEventHookModule::FavoritePartyIds = {};
std::vector<std::pair<int, std::string>> GameEventHookModule::RecentPartyIds = {};
int GameEventHookModule::LastSelectedTab = 16;
                    

bool GameEventHookModule::SkipReplays = false;
bool GameEventHookModule::RemoveDemoSmoke = false;
bool GameEventHookModule::RemoveGoalExplosion = false;
bool GameEventHookModule::KeyboardOverlay = false;
ImVec2 GameEventHookModule::ControllerOverlayPos = ImVec2(20, 20);
ImVec2 GameEventHookModule::KeyboardOverlayPos = ImVec2(20, 200);
float GameEventHookModule::ControllerOverlayAlpha = 0.20f;
float GameEventHookModule::KeyboardOverlayAlpha = 0.20f;

bool GameEventHookModule::MinimapEnabled = false;
ImVec2 GameEventHookModule::MinimapPos = ImVec2(20, 20);
float GameEventHookModule::MinimapSize = 200.0f;
float GameEventHookModule::MinimapAlpha = 0.5f;
bool GameEventHookModule::MinimapShowBall = true;
bool GameEventHookModule::MinimapShowBoosts = false;
bool GameEventHookModule::MinimapShowPlayers = true;
bool GameEventHookModule::MinimapTeamColors = true;
ImVec4 GameEventHookModule::MinimapBallColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
ImVec4 GameEventHookModule::MinimapBoostColor = ImVec4(1.0f, 1.0f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::MinimapPlayerColor = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
ImVec4 GameEventHookModule::MinimapMyTeamColor = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
ImVec4 GameEventHookModule::MinimapOpponentColor = ImVec4(1.0f, 0.5f, 0.0f, 1.0f);
bool GameEventHookModule::MinimapShowGoals = true;
bool GameEventHookModule::MinimapShowDirection = true;

bool GameEventHookModule::ShowPlayerMMR = false;

bool GameEventHookModule::ToggleStatusIndicatorEnabled = false;
ImVec2 GameEventHookModule::ToggleStatusIndicatorPos = ImVec2(0, 0);
bool GameEventHookModule::ToggleStatusIndicatorDragging = false;
ImVec2 GameEventHookModule::ToggleStatusIndicatorDragOffset = ImVec2(0, 0);

bool GameEventHookModule::DiscordWebhookEnabled = false;
char GameEventHookModule::DiscordWebhookURL[512] = "";
bool GameEventHookModule::MatchStartedLogged = false;
bool GameEventHookModule::MatchEndedLogged = false;
std::string GameEventHookModule::CurrentMatchStartTime = "";
std::string GameEventHookModule::CurrentMatchMap = "";
std::string GameEventHookModule::CurrentMatchPlaylist = "";
bool GameEventHookModule::GameEventActive = false;

bool GameEventHookModule::IsKickoffPause = false;
double GameEventHookModule::LastKickoffTime = 0.0;
std::string GameEventHookModule::LastGameState = "";

std::string GameEventHookModule::MenuToggleKey = "Insert";
std::string GameEventHookModule::ModuleVersion = "34.0.0";

                                                                                
ImVec4 GameEventHookModule::UIAccentColor           = ImVec4(0.30f, 0.49f, 1.00f, 1.00f);
bool   GameEventHookModule::UIAccentRainbow         = false;
float  GameEventHookModule::UIAccentRainbowSpeed    = 40.0f;
ImVec4 GameEventHookModule::UIBackgroundColor       = ImVec4(0.00f, 0.00f, 0.00f, 0.89f);
bool   GameEventHookModule::UIBackgroundRainbow     = false;
float  GameEventHookModule::UIBackgroundRainbowSpeed = 20.0f;
bool   GameEventHookModule::UIBlurEnabled           = true;
                                                                                
                                                                              
                                                                         
                                                                             
                                                                                
                                                                                
                                                                              
namespace
{
    std::string GetUIThemePresetsPath()
    {
        return GetKingModResourcesDirectory() + "\\UIThemePresets.json";
    }

    nlohmann::json LoadUIThemeFile()
    {
        nlohmann::json root;
        std::ifstream in(GetUIThemePresetsPath());
        if (in.good())
        {
            try { in >> root; }
            catch (...) { root = nlohmann::json::object(); }
        }
        if (!root.is_object()) root = nlohmann::json::object();
        if (!root.contains("presets") || !root["presets"].is_object())
            root["presets"] = nlohmann::json::object();
        if (!root.contains("favorite")) root["favorite"] = "";
        return root;
    }

    void SaveUIThemeFile(const nlohmann::json& root)
    {
        std::ofstream out(GetUIThemePresetsPath(), std::ios::trunc);
        if (out.good()) out << root.dump(2);
    }

    void ReadThemeColor(const nlohmann::json& o, const char* key, ImVec4& col)
    {
        if (o.contains(key) && o[key].is_array() && o[key].size() >= 4)
        {
            col.x = o[key][0].get<float>();
            col.y = o[key][1].get<float>();
            col.z = o[key][2].get<float>();
            col.w = o[key][3].get<float>();
        }
    }

    nlohmann::json ThemeToJson()
    {
        nlohmann::json o;
        o["accent_rgba"]        = { GameEventHookModule::UIAccentColor.x, GameEventHookModule::UIAccentColor.y, GameEventHookModule::UIAccentColor.z, GameEventHookModule::UIAccentColor.w };
        o["accent_rainbow"]     = GameEventHookModule::UIAccentRainbow;
        o["accent_rainbow_spd"] = GameEventHookModule::UIAccentRainbowSpeed;
        o["bg_rgba"]            = { GameEventHookModule::UIBackgroundColor.x, GameEventHookModule::UIBackgroundColor.y, GameEventHookModule::UIBackgroundColor.z, GameEventHookModule::UIBackgroundColor.w };
        o["bg_rainbow"]         = GameEventHookModule::UIBackgroundRainbow;
        o["bg_rainbow_spd"]     = GameEventHookModule::UIBackgroundRainbowSpeed;
        o["blur_enabled"]       = GameEventHookModule::UIBlurEnabled;
        return o;
    }

    void JsonToTheme(const nlohmann::json& o)
    {
        ReadThemeColor(o, "accent_rgba", GameEventHookModule::UIAccentColor);
        GameEventHookModule::UIAccentRainbow        = o.value("accent_rainbow", GameEventHookModule::UIAccentRainbow);
        GameEventHookModule::UIAccentRainbowSpeed   = o.value("accent_rainbow_spd", GameEventHookModule::UIAccentRainbowSpeed);
        ReadThemeColor(o, "bg_rgba", GameEventHookModule::UIBackgroundColor);
        GameEventHookModule::UIBackgroundRainbow    = o.value("bg_rainbow", GameEventHookModule::UIBackgroundRainbow);
        GameEventHookModule::UIBackgroundRainbowSpeed = o.value("bg_rainbow_spd", GameEventHookModule::UIBackgroundRainbowSpeed);
        GameEventHookModule::UIBlurEnabled          = o.value("blur_enabled", GameEventHookModule::UIBlurEnabled);
    }
}

namespace UITheme
{
    std::vector<std::string> ListPresets()
    {
        std::vector<std::string> names;
        nlohmann::json root = LoadUIThemeFile();
        for (auto it = root["presets"].begin(); it != root["presets"].end(); ++it)
            names.push_back(it.key());
        std::sort(names.begin(), names.end());
        return names;
    }

    bool SavePreset(const std::string& name)
    {
        if (name.empty()) return false;
        nlohmann::json root = LoadUIThemeFile();
        root["presets"][name] = ThemeToJson();
        SaveUIThemeFile(root);
        return true;
    }

    bool LoadPreset(const std::string& name)
    {
        nlohmann::json root = LoadUIThemeFile();
        if (!root["presets"].contains(name)) return false;
        JsonToTheme(root["presets"][name]);
        return true;
    }

    bool DeletePreset(const std::string& name)
    {
        nlohmann::json root = LoadUIThemeFile();
        if (!root["presets"].contains(name)) return false;
        root["presets"].erase(name);
        if (root.value("favorite", std::string()) == name) root["favorite"] = "";
        SaveUIThemeFile(root);
        return true;
    }

    void SetFavorite(const std::string& name)
    {
        nlohmann::json root = LoadUIThemeFile();
        root["favorite"] = name;
        SaveUIThemeFile(root);
    }

    std::string GetFavorite()
    {
        nlohmann::json root = LoadUIThemeFile();
        return root.value("favorite", std::string());
    }

    void ApplyFavoriteOnStartup()
    {
        std::string fav = GetFavorite();
        if (!fav.empty())
            LoadPreset(fav);
    }
}

std::string GameEventHookModule::ConfigFilePath = "";

std::vector<GameEventHookModule::PredictionPoint> GameEventHookModule::PredictedPath;
static std::string LastRankUpdateString = "";
static std::string LastRankUpdatePlaylist = "";
static std::string LastRankUpdateOld = "";
static std::string LastRankUpdateNew = "";
static float LastRankUpdateMMR = 0.0f;
static int LastRankUpdateMatches = 0;
static int LastRankUpdatePlacement = 0;

static bool TryReadMemoryRaw(uintptr_t address, void* result, size_t size) {
    __try {
        memcpy(result, reinterpret_cast<const void*>(address), size);
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

template<typename T>
bool TryReadMemory(uintptr_t address, T* result) {
    return TryReadMemoryRaw(address, result, sizeof(T));
}

                                                                             
                                                                              
                                                                              
                                                                             
                                                 
static bool IsValidUObjectPtr(void* obj) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(obj);
                                                                                  
    if (addr < 0x10000 || (addr & 0x7) != 0)
        return false;

    __try {
                                                                            
        uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(addr);
        if (vtable < 0x10000 || (vtable & 0x7) != 0)
            return false;
                                                 
        volatile uintptr_t vtFirst = *reinterpret_cast<volatile uintptr_t*>(vtable);
        (void)vtFirst;

                                                                           
        uintptr_t klass = *reinterpret_cast<volatile uintptr_t*>(addr + 0x50);
        if (klass < 0x10000 || (klass & 0x7) != 0)
            return false;

        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

template<typename T>
static bool IsValidObjectOfClass(T* obj, UClass* expectedClass) {
    if (!IsValidUObjectPtr(obj) || !expectedClass)
        return false;
    __try {
        return obj->IsA(expectedClass);
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

template<typename T>
std::vector<T*> SafeReadTArray(uintptr_t baseAddress, uintptr_t offset) {
    std::vector<T*> result;
    if (baseAddress == 0) return result;
    uintptr_t arrayAddress = baseAddress + offset;
    uintptr_t dataPtr = 0;
    if (!TryReadMemory(arrayAddress, &dataPtr)) return result;
    int32_t count = 0;
    if (!TryReadMemory(arrayAddress + sizeof(uintptr_t), &count)) return result;
    if (dataPtr == 0 || count <= 0 || count > 10) return result;
    for (int32_t i = 0; i < count; i++) {
        uintptr_t elementPtr = 0;
        if (TryReadMemory(dataPtr + (i * sizeof(uintptr_t)), &elementPtr) && elementPtr != 0)
            result.push_back(reinterpret_cast<T*>(elementPtr));
    }
    return result;
}

template <typename T>
T SafeRead(uintptr_t address) {
    T result = T{};
    TryReadMemory(address, &result);
    return result;
}

template <typename T>
bool SafeWrite(uintptr_t address, T value)
{

    if (address == 0)
    {
        return false;
    }

    __try
    {

        *reinterpret_cast<T*>(address) = value;
        return true;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {

        return false;
    }
}

template<typename T>
std::string to_hex(T i)
{
    std::stringstream stream;
    stream << "0x" << std::hex << i;
    return stream.str();
}

class Field;

constexpr int NUM_BOOST_PADS = 34;

double getCurrentTimeSeconds() {
    return std::chrono::duration_cast<std::chrono::duration<double>>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

class CppBoostPad {
public:
    Vector3 location;
    bool is_big;


    bool is_active;
    double picked_up_time;


    CppBoostPad() : location{ 0,0,0 }, is_big(false), is_active(false), picked_up_time(0) {}


    CppBoostPad(float x, float y, float z, bool big) :
        location{ x, y, z },
        is_big(big),
        is_active(true),
        picked_up_time(0.0f)
    {
    }

    void reset() {
        is_active = true;
        picked_up_time = 0.0;
    }

    float get_elapsed_time() const {
        if (picked_up_time > 0.0) {
            return static_cast<float>(getCurrentTimeSeconds() - picked_up_time);
        }
        return 0.0f;
    }

    float get_respawn_time() const {
        return is_big ? 10.0f : 4.0f;
    }

    float get_time_remaining() const {
        if (is_active) {
            return 0.0f;
        }
        float elapsed = get_elapsed_time();
        float remaining = get_respawn_time() - elapsed;
        return (remaining > 0.0f) ? remaining : 0.0f;
    }
};

class Field {
public:

    CppBoostPad boost_pads[NUM_BOOST_PADS];

    Field() {

        static const struct {
            float x, y, z;
            bool is_big;
        } BOOST_LOCATIONS[NUM_BOOST_PADS] = {
            {   0.0f, -4240.0f, 70.0f, false }, { -1792.0f, -4184.0f, 70.0f, false },
            { 1792.0f, -4184.0f, 70.0f, false }, { -3072.0f, -4096.0f, 73.0f, true  },
            { 3072.0f, -4096.0f, 73.0f, true  }, {  -940.0f, -3308.0f, 70.0f, false },
            {  940.0f, -3308.0f, 70.0f, false }, {    0.0f, -2816.0f, 70.0f, false },
            {-3584.0f, -2484.0f, 70.0f, false }, {  3584.0f, -2484.0f, 70.0f, false },
            {-1788.0f, -2300.0f, 70.0f, false }, {  1788.0f, -2300.0f, 70.0f, false },
            {-2048.0f, -1036.0f, 70.0f, false }, {    0.0f, -1024.0f, 70.0f, false },
            { 2048.0f, -1036.0f, 70.0f, false }, { -3584.0f,    0.0f, 73.0f, true  },
            {-1024.0f,    0.0f, 70.0f, false }, {  1024.0f,    0.0f, 70.0f, false },
            { 3584.0f,    0.0f, 73.0f, true  }, { -2048.0f,  1036.0f, 70.0f, false },
            {    0.0f,  1024.0f, 70.0f, false }, {  2048.0f,  1036.0f, 70.0f, false },
            {-1788.0f,  2300.0f, 70.0f, false }, {  1788.0f,  2300.0f, 70.0f, false },
            {-3584.0f,  2484.0f, 70.0f, false }, {  3584.0f,  2484.0f, 70.0f, false },
            {    0.0f,  2816.0f, 70.0f, false }, {  -940.0f,  3310.0f, 70.0f, false },
            {  940.0f,  3308.0f, 70.0f, false }, { -3072.0f,  4096.0f, 73.0f, true  },
            { 3072.0f,  4096.0f, 73.0f, true  }, { -1792.0f,  4184.0f, 70.0f, false },
            { 1792.0f,  4184.0f, 70.0f, false }, {    0.0f,  4240.0f, 70.0f, false }
        };
        for (int i = 0; i < NUM_BOOST_PADS; ++i) {
            boost_pads[i] = CppBoostPad(BOOST_LOCATIONS[i].x, BOOST_LOCATIONS[i].y, BOOST_LOCATIONS[i].z, BOOST_LOCATIONS[i].is_big);
        }
    }

    void reset_boostpads() {
        for (int i = 0; i < NUM_BOOST_PADS; ++i) {
            boost_pads[i].reset();
        }
    }
};

Field GameEventHookModule::field;

GameEventHookModule::GameEventHookModule() : Module("GameEventHook", "Hooks into game events", States::STATES_All) {
    OnCreate();
}
GameEventHookModule::~GameEventHookModule() { OnDestroy(); }

void GameEventHookModule::OnCreate() {
    LoadConfig();
    KingFeatures::Initialize();
    KingSync::Initialize();
    KingModRecoverWorkshopAliasOnStartup();

    char exePath[MAX_PATH] = {};
    std::string path;
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH)) {
        std::string exePathStr(exePath);
        path = exePathStr.substr(0, exePathStr.find_last_of("\\/")) + "\\KingMod\\resources\\version.txt";
    } else {
        path = "KingMod\\resources\\version.txt";
    }

    {
        std::ofstream clearFile(path, std::ios::trunc);
    }

    std::ofstream file(path, std::ios::trunc);
    if (file.is_open()) {
        file << ModuleVersion;
        file.close();
    }
}

void GameEventHookModule::OnDestroy() {
    SaveConfig();
    KingSync::Shutdown();
    KingFeatures::Shutdown();
}

FVector SubtractVectors(const FVector& A, const FVector& B) {
    return { A.X - B.X, A.Y - B.Y, A.Z - B.Z };
}

void GameEventHookModule::SkipReplay(PreEvent& event) {
                                                                                                            
    IsInReplayPlayback = true;
    BallPrediction::ForceRefresh();

    if (!SkipReplays) { return; }

    try {
        if (!GameEventHookModule::CurrentGameEvent) {
            Main.Execute([]() {
                Main.ReadyUp();
                });
            return;
        }


        TArray<APlayerController_TA*> localPlayers = GameEventHookModule::getLocalPlayers(GameEventHookModule::CurrentGameEvent);

        if (localPlayers.empty()) {
            Main.Execute([]() {
                Main.ReadyUp();
                });
            return;
        }


        TArray<APRI_TA*> allPRIs = GameEventHookModule::CurrentGameEvent->PRIs;
        TArray<ATeam_TA*> teams = GameEventHookModule::CurrentGameEvent->Teams;

        if (teams.empty() || allPRIs.empty()) {
            Main.Execute([]() {
                Main.ReadyUp();
                });
            return;
        }


        int maxTeamSize = allPRIs.size() / teams.size();


        bool allTeamsFull = true;
        for (APlayerController_TA* controller : localPlayers) {
            if (!controller) continue;

            APRI_TA* localPRI = controller->PRI;
            if (!localPRI) continue;

            ATeamInfo* teamInfo = localPRI->Team;
            if (!teamInfo) continue;

            int localTeam = teamInfo->TeamIndex;


            int teamCount = 0;
            for (APRI_TA* pri : allPRIs) {
                if (!pri) continue;

                ATeamInfo* priTeamInfo = pri->Team;
                if (priTeamInfo) {
                    int priTeam = priTeamInfo->TeamIndex;
                    if (priTeam == localTeam) {
                        teamCount++;
                    }
                }
            }


            if (teamCount < maxTeamSize) {
                allTeamsFull = false;
                break;
            }
        }

        if (allTeamsFull) {
            Main.Execute([]() {
                Main.ReadyUp();
                });
        }

    }
    catch (...) {
        Main.Execute([]() {
            Main.ReadyUp();
            });
    }
}

void GameEventHookModule::OnReplayPlaybackEnd(PreEvent& event)
{
    IsInReplayPlayback = false;
    BallPrediction::ForceRefresh();
}

FUniqueNetId GetUniqueNetID() {
    auto Pointer = Instances.IULocalPlayer();
    if (Pointer) {
        return Pointer->eventGetUniqueNetId();
    }
    return FUniqueNetId{};
}

                                                                               
                                                                               
                                                                                
                                                          
std::string platformToString(int Platform);

namespace
{
    constexpr int kDefaultPlayerMmrPlaylistId = 11;
    std::unordered_map<uintptr_t, std::string> g_PlayerMmrOriginalNames;
    bool IsValidPlayerMmrNetId(const FUniqueNetId& netId)
    {
        return netId.Uid != 0 || !netId.EpicAccountId.ToString().empty();
    }

    std::string StripMmrPrefixFromName(const std::string& playerName)
    {
        std::string name = playerName;

                                                                                
                                                                               
                                                                         
                                     
        static const char* kPlatformTags[] = {
            " (Steam)", " (PSN)", " (Xbox)", " (Switch)", " (Epic)", " (PsyNet)", " (Unknown)"
        };
        for (const char* tag : kPlatformTags)
        {
            const size_t tagLen = strlen(tag);
            if (name.size() > tagLen && name.compare(name.size() - tagLen, tagLen, tag) == 0)
            {
                name.erase(name.size() - tagLen);
                break;
            }
        }

        if (name.size() < 4 || name[0] != '[')
            return name;

        const size_t closingBracket = name.find(']');
        if (closingBracket == std::string::npos || closingBracket <= 1)
            return name;

        for (size_t i = 1; i < closingBracket; ++i)
        {
            if (!std::isdigit(static_cast<unsigned char>(name[i])))
                return name;
        }

        size_t nameStart = closingBracket + 1;
        if (nameStart < name.size() && name[nameStart] == ' ')
            ++nameStart;

        return name.substr(nameStart);
    }

                                                                               
                                                                                
                                                                             
                                                                        
                                                                             
                                                                              
                                             
    void ApplyPlayerDisplayName(APRI_TA* pri, const std::string& playerName)
    {
        if (!pri || playerName.empty())
            return;

        try
        {
            if (pri->bDeleteMe)
                return;
        }
        catch (...) { return; }

        try   { pri->eventSetPlayerName(Format::ToFString(playerName)); }
        catch (...) {}
    }

    int GetOverlayPlayerMmrPlaylistId()
    {
        if (GameEventHookModule::CurrentGameEvent)
        {
            try
            {
                if (UGameSettingPlaylist_X* playlist = GameEventHookModule::CurrentGameEvent->GetPlaylist())
                {
                    const int playlistId = playlist->PlaylistId;
                    if (playlistId != 4 && playlistId != 76 && playlistId != 86)
                        return playlistId;
                }
            }
            catch (...)
            {
            }
        }

        return kDefaultPlayerMmrPlaylistId;
    }

    UOnlineGameSkill_X* GetOverlayOnlineGameSkill()
    {
                                                                                
                                                                                
                                                                             
                                                           
          
                                                                                
                                                                      
                                                                            
                                                                    
        try
        {
            if (UOnlineGame_X* onlineGame = APlayerController_X::GetOnlineGame())
            {
                if (onlineGame->Skill)
                    return onlineGame->Skill;
            }
        }
        catch (...)
        {
        }

        try
        {
            if (UGFxData_Playlist_TA* playlistData = Instances.GetInstanceOf<UGFxData_Playlist_TA>())
            {
                if (UOnlineGameSkill_X* onlineGameSkill = playlistData->GetOnlineGameSkill())
                    return onlineGameSkill;
            }
        }
        catch (...)
        {
        }

        try
        {
            return Instances.GetInstanceOf<UOnlineGameSkill_X>();
        }
        catch (...)
        {
            return nullptr;
        }
    }

                                                                                 
                                                                           
                                                                        
    float InternalMmrToDisplayMmr(float internalMmr)
    {
        return internalMmr * 20.0f + 100.0f;
    }

                                                                               
                                                                                 
                                                                                
                                                                            
                                                                               
                                          
    float NormalizeMmrToDisplayScale(float value)
    {
        if (value <= 0.0f)
            return 0.0f;
        return (value < 100.0f) ? InternalMmrToDisplayMmr(value) : value;
    }

    bool TryGetPsyNetPlayerMmr(UOnlineGameSkill_X* onlineGameSkill, const FUniqueNetId& playerId, int playlistId, float& outMmr, int& outTier)
    {
        if (!onlineGameSkill || !IsValidPlayerMmrNetId(playerId))
            return false;

        try
        {
                                                                                 
                                                                                  
                                                                                  
                                                                                
                                                                         
            int skillPlaylist = playlistId;
            try
            {
                const int mapped = UOnlineGameSkill_X::GetSkillPlaylistID(playlistId);
                if (mapped > 0)
                    skillPlaylist = mapped;
            }
            catch (...)
            {
            }

                                                                             
                                                                                
                                                           
            bool synced = false;
            try { synced = onlineGameSkill->SkillsSynced(playerId); }
            catch (...) { synced = false; }

            float rawMmr = 0.0f;
            try { rawMmr = onlineGameSkill->GetPlayerMMR(playerId, skillPlaylist); }
            catch (...) { rawMmr = 0.0f; }

            const FPlayerSkillRating rating = onlineGameSkill->GetPlayerRating(playerId, skillPlaylist);

            if (rawMmr <= 0.0f)
                rawMmr = rating.MMR;
            if (rawMmr <= 0.0f && rating.Mu > 0.0f)
                rawMmr = rating.Mu;

            const bool hasRatingData =
                rawMmr > 0.0f ||
                rating.Tier > 0 ||
                rating.Division > 0 ||
                rating.MatchesPlayed > 0 ||
                rating.PlacementMatchesPlayed > 0;

                                                                              
                                            
            if (!synced && rawMmr <= 0.0f)
                return false;

            if (!hasRatingData)
                return false;

            outMmr = NormalizeMmrToDisplayScale(rawMmr);
            outTier = rating.Tier;
            return outMmr > 0.0f;
        }
        catch (...)
        {
            return false;
        }
    }

    bool TryResolveOverlayPlayerMmr(UOnlineGameSkill_X* onlineGameSkill, const FUniqueNetId& playerId, int currentPlaylistId, float& outMmr, int& outTier)
    {
        if (TryGetPsyNetPlayerMmr(onlineGameSkill, playerId, currentPlaylistId, outMmr, outTier))
            return true;

        if (currentPlaylistId != kDefaultPlayerMmrPlaylistId &&
            TryGetPsyNetPlayerMmr(onlineGameSkill, playerId, kDefaultPlayerMmrPlaylistId, outMmr, outTier))
        {
            return true;
        }

        return false;
    }

    void RestorePlayerMmrNamePrefixes(AGameEvent_Soccar_TA* gameEvent)
    {
        if (!gameEvent)
        {
            g_PlayerMmrOriginalNames.clear();
            return;
        }

        TArray<APRI_TA*> allPRIs = gameEvent->PRIs;
        for (int i = 0; i < allPRIs.size(); ++i)
        {
            APRI_TA* pri = allPRIs[i];
            if (!pri)
                continue;

            const uintptr_t priKey = reinterpret_cast<uintptr_t>(pri);
            auto originalNameIt = g_PlayerMmrOriginalNames.find(priKey);
            if (originalNameIt == g_PlayerMmrOriginalNames.end())
                continue;

            ApplyPlayerDisplayName(pri, originalNameIt->second);
        }

        g_PlayerMmrOriginalNames.clear();
    }

    void UpdatePlayerMmrNamePrefixes()
    {
        static std::atomic_flag s_inFlight = ATOMIC_FLAG_INIT;
        static double s_lastRun = 0.0;
        static AGameEvent_Soccar_TA* s_lastEvent = nullptr;
        static double s_eventStableSince = 0.0;
        static std::vector<APRI_TA*> s_lastPris;

        const DWORD rlGameThread = g_RocketLeagueGameThread.load(std::memory_order_acquire);
        if (rlGameThread != 0 && GetCurrentThreadId() != rlGameThread)
            return;

        if (GetSteadyTimeMs() < g_NamePrefixBlockUntilMs.load(std::memory_order_acquire))
            return;

        if (s_inFlight.test_and_set(std::memory_order_acquire))
            return;

        struct InFlightGuard
        {
            std::atomic_flag& Flag;
            explicit InFlightGuard(std::atomic_flag& flag) : Flag(flag) {}
            ~InFlightGuard() { Flag.clear(std::memory_order_release); }
        } inFlightGuard(s_inFlight);

        const double nowSeconds = getCurrentTimeSeconds();
        if (nowSeconds - s_lastRun < 0.25)
            return;
        s_lastRun = nowSeconds;

        AGameEvent_Soccar_TA* gameEvent = GameEventHookModule::CurrentGameEvent;

        if (!gameEvent)
        {
            s_lastEvent = nullptr;
            s_lastPris.clear();
            s_eventStableSince = nowSeconds;
            return;
        }

        if (gameEvent->bDeleteMe)
            return;

        if (gameEvent != s_lastEvent)
        {
            s_lastEvent = gameEvent;
            s_lastPris.clear();
            s_eventStableSince = nowSeconds;
            return;
        }

        if (!GameEventHookModule::IsInGame)
            return;

        AGFxHUD_TA* hud = Instances.GetInstanceOf<AGFxHUD_TA>();
        if (!hud)
            return;

        const int priCount = gameEvent->PRIs.size();
        if (priCount < 0 || priCount > 64)
            return;

        std::vector<APRI_TA*> currentPris;
        currentPris.reserve(static_cast<size_t>(priCount));
        for (int i = 0; i < priCount; ++i)
            currentPris.push_back(gameEvent->PRIs[i]);

        bool priListChanged = currentPris.size() != s_lastPris.size();
        if (!priListChanged)
        {
            for (size_t i = 0; i < currentPris.size(); ++i)
            {
                if (currentPris[i] != s_lastPris[i])
                {
                    priListChanged = true;
                    break;
                }
            }
        }

        if (priListChanged)
        {
            s_lastPris = currentPris;
            s_eventStableSince = nowSeconds;
            return;
        }

        if (nowSeconds - s_eventStableSince < 3.0)
            return;

        for (APRI_TA* pri : currentPris)
        {
            if (!pri)
            {
                s_eventStableSince = nowSeconds;
                return;
            }
            if (pri->bDeleteMe)
            {
                s_eventStableSince = nowSeconds;
                return;
            }
            if (pri->GameEvent != gameEvent && pri->ReplicatedGameEvent != gameEvent)
            {
                s_eventStableSince = nowSeconds;
                return;
            }
            if (pri->bWaitingPlayer)
            {
                s_eventStableSince = nowSeconds;
                return;
            }
            const std::string playerName = pri->PlayerName.ToString();
            if (playerName.empty())
            {
                s_eventStableSince = nowSeconds;
                return;
            }
        }

        const bool wantMmr = GameEventHookModule::ShowPlayerMMR;
        if (!wantMmr)
        {
            RestorePlayerMmrNamePrefixes(gameEvent);
            return;
        }

        UOnlineGameSkill_X* onlineGameSkill = wantMmr ? GetOverlayOnlineGameSkill() : nullptr;
        const int overlayPlaylistId = GetOverlayPlayerMmrPlaylistId();
        std::unordered_set<uintptr_t> activePris;

        for (APRI_TA* pri : currentPris)
        {
            if (!pri || pri->bDeleteMe)
                continue;
            try { if (!pri->IsA(APRI_TA::StaticClass())) continue; }
            catch (...) { continue; }

            const uintptr_t priKey = reinterpret_cast<uintptr_t>(pri);
            activePris.insert(priKey);

            std::string currentName;
            try { currentName = pri->PlayerName.ToString(); }
            catch (...) { continue; }

            if (currentName.empty())
                continue;

            std::string& originalName = g_PlayerMmrOriginalNames[priKey];
            if (originalName.empty())
                originalName = StripMmrPrefixFromName(currentName);

            if (originalName.empty())
                continue;

            std::string desiredName = originalName;
            float mmr = 0.0f;
            int tier = 0;
            bool isBot = false;
            try { isBot = pri->bBot; } catch (...) { isBot = false; }
            if (wantMmr && !isBot && TryResolveOverlayPlayerMmr(onlineGameSkill, pri->UniqueId, overlayPlaylistId, mmr, tier))
                desiredName = "[" + std::to_string(static_cast<int>(std::lround(mmr))) + "] " + originalName;


            if (currentName != desiredName)
                ApplyPlayerDisplayName(pri, desiredName);
        }

        for (auto it = g_PlayerMmrOriginalNames.begin(); it != g_PlayerMmrOriginalNames.end();)
        {
            if (activePris.find(it->first) == activePris.end())
                it = g_PlayerMmrOriginalNames.erase(it);
            else
                ++it;
        }
    }
}

std::map<int, std::string> PLAYLIST_MAP = {
    {0, "Casual 1v1"}, {1, "Casual 2v2"}, {2, "Casual 3v3"}, {3, "Casual 4v4"},
    {10, "Ranked 1v1 (Duel)"}, {11, "Ranked 2v2 (Doubles)"}, {13, "Ranked 3v3 (Standard)"},
    {15, "Casual Snow Day"}, {16, "Casual Hoops"}, {17, "Casual Rumble"}, {18, "Casual Dropshot"},
    {27, "Ranked Hoops"}, {28, "Ranked Rumble"}, {29, "Ranked Dropshot"}, {30, "Ranked Snow Day"},
    {34, "Tournaments"},
    {32, "Spike Rush"}, {33, "Ghost Hunt"}, {38, "Boomer Ball"}, {41, "Knockout"},
    {43, "Speed Demon"}, {44, "Haunted Heatseeker"},
    {4, "Rocket Labs"}, {76, "Training Editor"}, {86, "Freeplay"}
};

std::map<int, std::string> SKILL_TIER_MAP = {
    {0, "Unranked"}, {1, "Bronze I"}, {2, "Bronze II"}, {3, "Bronze III"},
    {4, "Silver I"}, {5, "Silver II"}, {6, "Silver III"},
    {7, "Gold I"}, {8, "Gold II"}, {9, "Gold III"},
    {10, "Platinum I"}, {11, "Platinum II"}, {12, "Platinum III"},
    {13, "Diamond I"}, {14, "Diamond II"}, {15, "Diamond III"},
    {16, "Champion I"}, {17, "Champion II"}, {18, "Champion III"},
    {19, "Grand Champion I"}, {20, "Grand Champion II"}, {21, "Grand Champion III"},
    {22, "Supersonic Legend"}
};

std::string GetRankString(int tier, int division) {
    if (tier == 0) return "Unranked";

    auto it = SKILL_TIER_MAP.find(tier);
    if (it != SKILL_TIER_MAP.end()) {
        return it->second + " Div " + std::to_string(division + 1);
    }
    return "Tier " + std::to_string(tier) + " Div " + std::to_string(division + 1);
}

void SkillUpdate(const PostEvent& event) {
    try {

        auto playlistData = static_cast<UGFxData_Playlist_TA*>(event.Caller());
        if (!playlistData) {
            return;
        }


        int playlistId = playlistData->Id;
        int tier = playlistData->SkillTier;
        int division = playlistData->SkillDivision;
        float mmr = playlistData->SkillMMR;
        int prevTier = playlistData->PrevSkillTier;
        int prevDivision = playlistData->PrevSkillDivision;


        std::string playlistName = "Unknown Playlist";
        auto it = PLAYLIST_MAP.find(playlistId);
        if (it != PLAYLIST_MAP.end()) {
            playlistName = it->second;
        }


        std::string currentRank = GetRankString(tier, division);
        std::string previousRank = GetRankString(prevTier, prevDivision);


        bool rankChanged = (tier != prevTier || division != prevDivision);

        if (rankChanged) {

            {
                std::ostringstream oss;
                oss.setf(std::ios::fixed); oss<<std::setprecision(2);
                oss<<"Rank Update - "<<playlistName<<": "<<previousRank<<" -> "<<currentRank<<" (MMR: "<<mmr<<")";
            }

            if (tier > prevTier || (tier == prevTier && division > prevDivision)) {
            }
            else if (tier < prevTier || (tier == prevTier && division < prevDivision)) {
            }
            if (playlistData->bRanked) {
            }

        }
        else {

            {
                std::ostringstream oss;
                oss.setf(std::ios::fixed); oss<<std::setprecision(2);
                oss<<"MMR Update - "<<playlistName<<": "<<currentRank<<" (MMR: "<<mmr<<")";
            }
            if (playlistData->bRanked) {
            }

        }


        LastRankUpdatePlaylist = playlistName;
        LastRankUpdateOld = previousRank;
        LastRankUpdateNew = currentRank;
        LastRankUpdateMMR = mmr;
        LastRankUpdateMatches = playlistData->SkillMatchesPlayed;
        LastRankUpdatePlacement = playlistData->SkillPlacementMatchesPlayed;
        LastRankUpdateString = previousRank + " â†’ " + currentRank + " (MMR: " + std::to_string(mmr) + ")";

    }
    catch (const std::exception& e) {
        Console.Error(std::string("SkillUpdate: Exception - ") + e.what());
    }
    catch (...) {
        Console.Error("SkillUpdate: Unknown exception");
    }
}

void GameEventHookModule::HookGameEvents()
{
    try
    {
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay", OnGameEventStart);
        Events.HookEventPost("Function TAGame.GameEvent_Soccar_TA.PostBeginPlay", [](const PostEvent& event) {
            UObject* caller = event.Caller();
            if (caller && caller->IsA(AGameEvent_TA::StaticClass()))
            {
                CustomMatchModule::SynchronizeHostedLanPassword(
                    static_cast<AGameEvent_TA*>(caller));
                CustomMatchModule::EnforceHostedLanBotPolicy(
                    static_cast<AGameEvent_TA*>(caller));
            }
        });
                                                                          
                                                                          
        Events.HookEventPost("Function TAGame.GameEvent_TA.EventPlayerAdded", [](const PostEvent& event) {
            auto* params = event.GetParams<AGameEvent_TA_execEventPlayerAdded_Params>();
            if (!params || !params->PRI)
                return;
            HostSync::NotifyPlayerJoined(params->PRI);
        });
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Destroyed", OnGameEventDestroyed);
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Active.BeginState", OnGameEventStart);
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.Countdown.BeginState", OnGameEventStart);



        Events.HookEventPost("Function TAGame.PlayerController_TA.PlayerTick", PlayerTickCalled);
        Events.HookEventPre("Function ProjectX.PlaylistSkillCache_X.CacheSkill", CacheSkillCalled);



        Events.HookEventPre("Function TAGame.VehiclePickup_Boost_TA.Idle.EndState", on_boost_picked_up);
        Events.HookEventPre("Function TAGame.VehiclePickup_Boost_TA.Idle.BeginState", on_boost_respawned);
        Events.HookEventPre("Function TAGame.GameEvent_TA.ResetPickups", on_reset_pickups);
        Events.HookEventPost("Function TAGame.GameViewportClient_TA.HandleKeyPress", GameViewportKeyPress);
        Events.HookEventPre("Function TAGame.PlayerController_TA.ChatMessage_TA", OnChatMessageHook);
        Events.HookEventPre("Function TAGame.GFxData_Chat_TA.SendChatPresetMessage", OnSendChatPresetMessageHook);
        Events.HookEventPre("Function TAGame.GFxData_Chat_TA.AddChatMessage", [](PreEvent& event) {
            auto* params = event.GetParams<UGFxData_Chat_TA_execAddChatMessage_Params>();
            if (!params)
                return;

            FGFxChatMessage& msg = const_cast<FGFxChatMessage&>(params->NewMessage);

            APlayerController* pc = Instances.IAPlayerController();
            if (!pc) return;

            APRI_TA* myPRI = (APRI_TA*)pc->PlayerReplicationInfo;
            if (!myPRI) return;

            if (!Events.CanUseLocalServerFeatures()) return;

            if (msg.SenderId == myPRI->UniqueId)
            {
                msg.TeamColor.B = 0;
                msg.TeamColor.G = 0;
                msg.TeamColor.R = 255;
                msg.TeamColor.A = 255;
                return;
            }

            if (CurrentGameEvent)
            {
                TArray<APRI_TA*> allPRIs = CurrentGameEvent->PRIs;
                for (int i = 0; i < allPRIs.size(); ++i)
                {
                    APRI_TA* senderPRI = allPRIs[i];
                    if (!senderPRI) continue;
                    if (senderPRI->UniqueId == msg.SenderId)
                    {
                        if (senderPRI->bMatchAdmin || senderPRI->bAdmin)
                        {
                            msg.TeamColor.B = 0;
                            msg.TeamColor.G = 0;
                            msg.TeamColor.R = 255;
                            msg.TeamColor.A = 255;
                        }
                        break;
                    }
                }
            }
        });
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.ReplayPlayback.BeginState", &SkipReplay);
        Events.HookEventPre("Function TAGame.GameEvent_Soccar_TA.ReplayPlayback.EndState", &OnReplayPlaybackEnd);
        Events.HookEventPost("Function TAGame.GFxData_Playlist_TA.UpdateSkillData", &SkillUpdate);
        Events.HookEventPre("Function TAGame.Ball_TA.Explode", &OnBallExplode);
        Events.HookEventPre("Function TAGame.Ball_TA.OnHitGoal", &OnBallHitGoal);
        Events.HookEventPre("Function ProjectX.OnlineGameJoinGame_X.TravelToServer", [](PreEvent& event) {
                                                                                     
                                                                                        
                                                                                     
            if (MatchmakingShield::OnProcessEventPre(event.Caller(), event.Function(), event.Params()))
                event.SetDetour(false);
        });
        Events.HookEventPre("Function TAGame.Car_TA.FinishDemo", &OnCarFinishDemo);
        Events.HookEventPre("Function ProjectX.Explosion_X.PostBeginPlay", &OnExplosionPostBeginPlay);
        Events.HookEventPre("Function TAGame.GameEvent_TA.UpdateBotCount", [](PreEvent& event) {
            if (!CustomMatchModule::ShouldBlockHostedLanBots())
                return;
            UObject* caller = event.Caller();
            if (caller && caller->IsA(AGameEvent_TA::StaticClass()))
                static_cast<AGameEvent_TA*>(caller)->bFillWithAI = false;
            event.SetDetour(false);
        });
        Events.HookEventPost("Function TAGame.ListenServer_TA.AllowPlayerLogin", [](const PostEvent& event) {
            g_RocketLeagueGameThread.store(GetCurrentThreadId(), std::memory_order_release);
            HostSync::NotifyLoginStarting();
            if (FakeSpectator::IsEnabled())
                FakeSpectator::Remove();

            auto* params = event.GetParams<UListenServer_TA_execAllowPlayerLogin_Params>();
            if (!params)
                return;

            CustomMatchModule::ApplyHostedLanLoginPassword(params->Options, params->ErrorMessage);

            BlockNamePrefixUpdates(8000);
        });
        Events.HookEventPre("Function ProjectX.RPCQueue_X.CreateBatchSingleRPC", [](PreEvent& event) {
            if (!ShouldTrackPsyNet())
                return;

            auto* requestMessageParams = event.GetParams<URPCQueue_X_eventCreateBatchSingleRPC_Params>();
            if (!requestMessageParams || !requestMessageParams->Message || !requestMessageParams->Message->Headers)
                return;

            TMap<FString, FString> headerMap(requestMessageParams->Message->Headers->Map);
            const std::string psyService = FormatPsyNetService(
                GetHeaderValue(headerMap, "PsyService"),
                GetHeaderValue(headerMap, "PsyServiceVersion"));

            const int containerProductId = ContainsSubstring(psyService, "Products/UnlockContainer")
                ? GetContainerProductIdFromRequest(requestMessageParams)
                : 0;

            if (EnablePsyNetLogging || containerProductId != 0)
            {
                PushPsyNetLogEntry(
                    "Request: " + psyService,
                    BuildHeaderDump(headerMap),
                    requestMessageParams->Message->GetBodyText().ToString());
            }
        });

        Events.HookEventPost("Function ProjectX.RPCQueue_X.CreateBatchSingleRPC", [](const PostEvent& event) {
            if (!ShouldTrackPsyNet())
                return;

            auto* requestMessageParams = reinterpret_cast<URPCQueue_X_eventCreateBatchSingleRPC_Params*>(event.Params());
            if (!requestMessageParams || !requestMessageParams->Message || !requestMessageParams->Message->Headers)
                return;

            TMap<FString, FString> headerMap(requestMessageParams->Message->Headers->Map);
            const std::string requestId = GetHeaderValue(headerMap, "PsyRequestID");
            if (requestId.empty())
                return;

            PsyNetRequestInfo requestInfo;
            requestInfo.Service = FormatPsyNetService(
                GetHeaderValue(headerMap, "PsyService"),
                GetHeaderValue(headerMap, "PsyServiceVersion"));
            requestInfo.ContainerProductId = ContainsSubstring(requestInfo.Service, "Products/UnlockContainer")
                ? GetContainerProductIdFromRequest(requestMessageParams)
                : 0;
            requestInfo.TradeInProductInstances = ContainsSubstring(requestInfo.Service, "Products/TradeIn")
                ? GetTradeInInstanceIdsFromRequest(requestMessageParams)
                : std::vector<FProductInstanceID>{};
            requestInfo.RedeemCode = ContainsSubstring(requestInfo.Service, "Codes/RedeemCode")
                ? GetRedeemCodeFromRequest(requestMessageParams)
                : "";
            if (ContainsSubstring(requestInfo.Service, "Shops/PurchaseItemFromShop"))
                TryGetShopPurchaseRequestData(requestMessageParams, requestInfo);

            g_PsyNetState.PendingRequests[requestId] = requestInfo;
            PsyNetPendingRequestCount = static_cast<int>(g_PsyNetState.PendingRequests.size());
        });

        Events.HookEventPre("Function ProjectX.PsyNetMessenger_X.EventMessageReceived", [](PreEvent& event) {
            if (!ShouldTrackPsyNet())
                return;

            auto* responseParams = event.GetParams<UPsyNetMessenger_X_execEventMessageReceived_Params>();
            if (!responseParams || !responseParams->Message || !responseParams->Message->Headers)
                return;

            TMap<FString, FString> headerMap(responseParams->Message->Headers->Map);
            std::string psyTime = GetHeaderValue(headerMap, "PsyTime");
            if (psyTime.empty())
                psyTime = "0";

            PsyNetRequestInfo requestInfo = ResolveResponseRequestInfo(headerMap);
            int containerProductId = requestInfo.ContainerProductId;
            std::string psyService = requestInfo.Service;
            if (psyService.empty())
                psyService = "Unknown";

            if (ContainsSubstring(psyService, "Products/GetContainerDropTable"))
            {
                g_PsyNetState.CatalogJSON = responseParams->Message->GetBodyText().ToString();
                PsyNetHasCachedDropTable = !g_PsyNetState.CatalogJSON.empty();
            }

            bool edited = false;
            edited = TryEditShopPurchaseResponse(responseParams->Message, psyService, requestInfo, psyTime) || edited;
            edited = TryEditTradeInResponse(responseParams->Message, psyService, requestInfo.TradeInProductInstances, psyTime) || edited;
            edited = TryEditRedeemCodeResponse(responseParams->Message, psyService, requestInfo.RedeemCode, psyTime) || edited;
            edited = TryApplyWalletResponse(responseParams->Message, psyService) || edited;
            edited = TryEditUnlockContainerResponse(responseParams->Message, psyService, containerProductId) || edited;
            SignPsyNetResponse(responseParams->Message, psyTime, psyService);

            if (EnablePsyNetLogging || edited)
            {
                PushPsyNetLogEntry(
                    std::string(edited ? "[Edited] Response: " : "Response: ") + psyService,
                    BuildHeaderDump(headerMap),
                    responseParams->Message->GetBodyText().ToString());
            }
        });
    }
    catch (...) { Console.Error("GameEventHook: Exception in HookGameEvents"); }
}

void GameEventHookModule::HookAdditionalFunctions()
{
    try
    {
        (void)0;
    }
    catch (...) { Console.Error("GameEventHook: Unknown exception in HookAdditionalFunctions"); }
}

void GameEventHookModule::GameViewportKeyPress(const PostEvent& event) {
    if (event.Params()) {
        UGameViewportClient_TA_execHandleKeyPress_Params* handleKeyPress = event.GetParams<UGameViewportClient_TA_execHandleKeyPress_Params>();
        (void)handleKeyPress;
    }
}

int find_boostpad_index_by_location(const Vector3& location, float tolerance = 100.0f) {
    for (int i = 0; i < NUM_BOOST_PADS; ++i) {
        float dx = GameEventHookModule::field.boost_pads[i].location.x - location.x;
        float dy = GameEventHookModule::field.boost_pads[i].location.y - location.y;
        float dz = GameEventHookModule::field.boost_pads[i].location.z - location.z;
        float distance_sq = dx * dx + dy * dy + dz * dz;

        if (distance_sq < tolerance * tolerance) {
            return i;
        }
    }
    return -1;
}

void GameEventHookModule::on_boost_picked_up(PreEvent& event) {
    if (!event.Caller()) return;


    AVehiclePickup_Boost_TA* pickup = static_cast<AVehiclePickup_Boost_TA*>(event.Caller());
    if (!pickup) return;


    FVector pickupFVec = pickup->Location;
    Vector3 pickup_location = { pickupFVec.X, pickupFVec.Y, pickupFVec.Z };

    int pad_index = find_boostpad_index_by_location(pickup_location);
    if (pad_index != -1) {
        GameEventHookModule::field.boost_pads[pad_index].is_active = false;
        GameEventHookModule::field.boost_pads[pad_index].picked_up_time = getCurrentTimeSeconds();
    }
}

void GameEventHookModule::on_boost_respawned(PreEvent& event) {
    if (!event.Caller()) return;


    AVehiclePickup_Boost_TA* pickup = static_cast<AVehiclePickup_Boost_TA*>(event.Caller());
    if (!pickup) return;

    FVector pickupFVec2 = pickup->Location;
    Vector3 pickup_location = { pickupFVec2.X, pickupFVec2.Y, pickupFVec2.Z };

    int pad_index = find_boostpad_index_by_location(pickup_location);
    if (pad_index != -1) {
        GameEventHookModule::field.boost_pads[pad_index].is_active = true;
        GameEventHookModule::field.boost_pads[pad_index].picked_up_time = 0.0;
    }
}

void GameEventHookModule::on_reset_pickups(PreEvent& event) {
    GameEventHookModule::field.reset_boostpads();
}

struct ChatMessageParams
{

    APRI_TA* PRI;

    FString Message;

    unsigned char TeamIndex;

    bool bPreset;
};

TArray<APlayerController_TA*> GameEventHookModule::getLocalPlayers(AGameEvent_Soccar_TA* gameEvent) {
    return gameEvent->LocalPlayers;
}

void GameEventHookModule::OnChatMessageHook(PreEvent& event)
{
    if (!event.Params()) {
        return;
    }

    PlayerController_ChatMessage_Params* params = static_cast<PlayerController_ChatMessage_Params*>(event.Params());


    std::string playerName = "Unknown";
    if (params->InPRI_ptr != 0) {
        playerName = reinterpret_cast<APRI_TA*>(params->InPRI_ptr)->PlayerName.ToString();
    }
    std::string message = params->Message.ToString();
    uint8_t channel = params->ChatChannel;
    std::string channelStr = "Unknown";
    if (channel == 0) channelStr = "All";
    else if (channel == 1) channelStr = "Team";
    else if (channel == 2) channelStr = "Party";
}

void GameEventHookModule::OnSendChatPresetMessageHook(PreEvent& event)
{
    Console.Notify("NATIVE HOOK: SendChatPresetMessage called!");

    if (!event.Params()) {
        Console.Error("Hook fired, but params were null.");
        return;
    }


    UGFxData_Chat_TA_execSendChatPresetMessage_Params* params = static_cast<UGFxData_Chat_TA_execSendChatPresetMessage_Params*>(event.Params());


    std::string messageIdStr = params->MessageId.ToString();
    std::string isTeamStr = params->bTeam ? "True" : "False";


}

TArray<PlayerInfo> generatePlayerInfo(TArray<ACar_TA*> cars) {
    TArray<PlayerInfo> players;
    int player_index = 0;

    for (int i = 0; i < cars.size(); i++) {
        ACar_TA* car = cars[i];
        if (!car) continue;

        PlayerInfo player = {};

        APRI_TA* carPRI = car->PRI;
        if (!carPRI) { continue; }

        player.name = carPRI->PlayerName.ToString();
        if (player.name.empty()) { continue; }

        player.PRI = carPRI;

        ATeamInfo* carTeamInfo = carPRI->Team;
        if (carTeamInfo) {
            if (Core.TamperingDetected) {
                if (carTeamInfo->TeamIndex == 0) {
                    player.team = 1;
                }
                else {
                    player.team = 0;
                }
            }
            else {
                player.team = carTeamInfo->TeamIndex;
            }

        }


        FVector carLocation = car->Location;
        player.physics.location.x = carLocation.X;
        player.physics.location.y = carLocation.Y;
        player.physics.location.z = carLocation.Z;

        FVector carVelocity = car->Velocity;
        player.physics.velocity.x = carVelocity.X;
        player.physics.velocity.y = carVelocity.Y;
        player.physics.velocity.z = carVelocity.Z;

        FRotator carRotation = car->Rotation;
        player.physics.rotation.pitch = static_cast<float>(carRotation.Pitch * URotationToRadians);
        player.physics.rotation.yaw = static_cast<float>(carRotation.Yaw * URotationToRadians);
        player.physics.rotation.roll = static_cast<float>(carRotation.Roll * URotationToRadians);

        FVector carAngularVelocity = car->AngularVelocity;
        player.physics.angular_velocity.x = carAngularVelocity.X;
        player.physics.angular_velocity.y = carAngularVelocity.Y;
        player.physics.angular_velocity.z = carAngularVelocity.Z;


        ScoreInfo carScoreInfo = {};
        carScoreInfo.score = carPRI->MatchScore;
        carScoreInfo.goals = carPRI->MatchGoals;
        carScoreInfo.assists = carPRI->MatchAssists;
        carScoreInfo.saves = carPRI->MatchSaves;
        carScoreInfo.shots = carPRI->MatchShots;
        carScoreInfo.demolitions = carPRI->MatchDemolishes;
        carScoreInfo.own_goals = carPRI->MatchOwnGoals;
        player.score_info = carScoreInfo;


        player.has_wheel_contact = car->bOnGround;
        player.is_super_sonic = car->bSupersonic;
        player.double_jumped = car->bDoubleJumped;
        player.jumped = car->bJumped;


        ACarComponent_Boost_TA* boost_component = car->BoostComponent;
        if (IsPointerReadable(boost_component)) {
            float boostAmount = boost_component->CurrentBoostAmount;
            player.boost = static_cast<int32_t>(boostAmount * 100.0f);
        }





        if (player_index < MAX_PLAYERS) {
            players.push_back(player);
            player_index++;
        }
    }
    return players;
}

BallInfo generateBallInfo(ABall_TA* ball) {
    BallInfo ballInfo;
    FVector ballLocation = ball->Location;
    ballInfo.physics.location.x = ballLocation.X; ballInfo.physics.location.y = ballLocation.Y; ballInfo.physics.location.z = ballLocation.Z;
    FVector ballVelocity = ball->Velocity;
    ballInfo.physics.velocity.x = ballVelocity.X; ballInfo.physics.velocity.y = ballVelocity.Y; ballInfo.physics.velocity.z = ballVelocity.Z;
    FRotator ballRotation = ball->Rotation;
    ballInfo.physics.rotation.pitch = static_cast<float>(ballRotation.Pitch * URotationToRadians);
    ballInfo.physics.rotation.yaw = static_cast<float>(ballRotation.Yaw * URotationToRadians);
    ballInfo.physics.rotation.roll = static_cast<float>(ballRotation.Roll * URotationToRadians);
    FVector ballAngularVelocity = ball->AngularVelocity;
    ballInfo.physics.angular_velocity.x = ballAngularVelocity.X; ballInfo.physics.angular_velocity.y = ballAngularVelocity.Y; ballInfo.physics.angular_velocity.z = ballAngularVelocity.Z;
    return ballInfo;
}

GameInfo generateGameInfo(AGameEvent_Soccar_TA* gameEvent, int frameNum) {
    GameInfo gameInfo;
    gameInfo.seconds_elapsed = gameEvent->GameTime;
    int gameTimeRemaining = gameEvent->SecondsRemaining;
    gameInfo.game_time_remaining = gameTimeRemaining;
    gameInfo.game_speed = 1.0;

    gameInfo.is_overtime = gameEvent->bOverTime;
    gameInfo.is_round_active = gameEvent->bRoundActive;
    gameInfo.is_unlimited_time = gameEvent->bUnlimitedTime;
    gameInfo.is_match_ended = gameEvent->bMatchEnded;
    gameInfo.world_gravity_z = 1.0;
    TArray<ABall_TA*> balls = gameEvent->GameBalls;
    if (balls.empty() || !balls[0]) { return gameInfo; }
    ABall_TA* ball = balls[0];
    FVector ballLocation = ball->Location;
    bool is_kickoff;
    if (gameInfo.is_round_active && ball && ballLocation.X == 0 && ballLocation.Y == 0) { is_kickoff = true; }
    else { is_kickoff = false; }
    gameInfo.is_kickoff_pause = is_kickoff;
    gameInfo.frame_num = frameNum;
    return gameInfo;
}

GameTickPacket generateCompleteGameTickPacket(AGameEvent_Soccar_TA* gameEvent, int frameNum, float secondsElapsed, APlayerController_TA* tickingPlayer = nullptr) {
    GameTickPacket gameTickPacket = {};

    if (!gameEvent) {
        return gameTickPacket;
    }




    TArray<APRI_TA*> allPRIs = gameEvent->PRIs;

    if (allPRIs.size() > MAX_PLAYERS * 4 || allPRIs.data() == nullptr) {
        return gameTickPacket;
    }

    std::map<APRI_TA*, int> priToStableIndex;


    gameTickPacket.num_cars = 0;
    for (int i = 0; i < allPRIs.size() && i < MAX_PLAYERS; ++i) {
        APRI_TA* pri = allPRIs[i];
        if (!pri) continue;


        int stableIndex = i;
        priToStableIndex[pri] = stableIndex;

        PlayerInfo& player = gameTickPacket.game_cars[stableIndex];


        player.PRI = pri;
        player.name = pri->PlayerName.ToString();
        if (player.name.empty()) continue;

        ATeamInfo* carTeamInfo = pri->Team;
        if (carTeamInfo) {
            if (Core.TamperingDetected) {
                if (carTeamInfo->TeamIndex == 0) {
                    player.team = 1;
                }
                else {
                    player.team = 0;
                }
            }
            else {
                player.team = carTeamInfo->TeamIndex;
            }
        }

        ScoreInfo carScoreInfo = {};
        carScoreInfo.score = pri->MatchScore;
        carScoreInfo.goals = pri->MatchGoals;
        carScoreInfo.assists = pri->MatchAssists;
        carScoreInfo.saves = pri->MatchSaves;
        carScoreInfo.shots = pri->MatchShots;
        carScoreInfo.demolitions = pri->MatchDemolishes;
        carScoreInfo.own_goals = pri->MatchOwnGoals;
        player.score_info = carScoreInfo;


        ACar_TA* car = pri->Car;
        if (car) {
            player.is_demolished = false;
            FVector carLocation = car->Location;
            player.physics.location = { carLocation.X, carLocation.Y, carLocation.Z };
            FVector carVelocity = car->Velocity;
            player.physics.velocity = { carVelocity.X, carVelocity.Y, carVelocity.Z };
            FRotator carRotation = car->Rotation;
            player.physics.rotation = { static_cast<float>(carRotation.Pitch * URotationToRadians), static_cast<float>(carRotation.Yaw * URotationToRadians), static_cast<float>(carRotation.Roll * URotationToRadians) };
            FVector carAngularVelocity = car->AngularVelocity;
            player.physics.angular_velocity = { carAngularVelocity.X, carAngularVelocity.Y, carAngularVelocity.Z };
            ACarComponent_Boost_TA* boost = car->BoostComponent;
            if (IsPointerReadable(boost)) {
                player.boost = static_cast<int32_t>(boost->CurrentBoostAmount * 100.0f);
            }
            player.has_wheel_contact = car->bOnGround;
            player.is_super_sonic = car->bSupersonic;
            player.double_jumped = car->bDoubleJumped;
            player.jumped = car->bJumped;
        }
        else {
            player.is_demolished = true;
            player.physics = {};
            player.boost = 0;
            player.has_wheel_contact = false;
        }

        gameTickPacket.num_cars++;
    }



    TArray<APlayerController_TA*> localPlayers = GameEventHookModule::getLocalPlayers(gameEvent);
    gameTickPacket.num_local_players = 0;
    gameTickPacket.localPlayerIndex = -1;

    if (tickingPlayer) {

        APRI_TA* tickingPRI = tickingPlayer->PRI;
        if (tickingPRI && priToStableIndex.count(tickingPRI)) {
            int stableIndex = priToStableIndex[tickingPRI];

            gameTickPacket.localPlayerIndices[0] = stableIndex;
            gameTickPacket.localPlayerNames[0] = gameTickPacket.game_cars[stableIndex].name;
            gameTickPacket.localPlayerIndex = stableIndex;
            gameTickPacket.localPlayerName = gameTickPacket.game_cars[stableIndex].name;
            gameTickPacket.num_local_players = 1;
        }
    }
    else {

        for (int i = 0; i < localPlayers.size() && i < MAX_PLAYERS; ++i) {
            APlayerController_TA* controller = localPlayers[i];
            if (controller) {
                APRI_TA* localPRI = controller->PRI;
                if (localPRI && priToStableIndex.count(localPRI)) {
                    int stableIndex = priToStableIndex[localPRI];
                    int localSlot = gameTickPacket.num_local_players;

                    gameTickPacket.localPlayerIndices[localSlot] = stableIndex;
                    gameTickPacket.localPlayerNames[localSlot] = gameTickPacket.game_cars[stableIndex].name;


                    if (i == 0) {
                        gameTickPacket.localPlayerIndex = stableIndex;
                        gameTickPacket.localPlayerName = gameTickPacket.game_cars[stableIndex].name;
                    }

                    gameTickPacket.num_local_players++;
                }
            }
        }
    }



    TArray<ABall_TA*> balls = gameEvent->GameBalls;
    if (!balls.empty() && balls[0]) {
        ABall_TA* ball = balls[0];
        if (ball) {
            gameTickPacket.game_ball = generateBallInfo(ball);
        }
    }

    gameTickPacket.game_info = generateGameInfo(gameEvent, frameNum);
    gameTickPacket.game_info.seconds_elapsed = secondsElapsed;

    TArray<ATeam_TA*> teams = gameEvent->Teams;
    gameTickPacket.num_teams = (teams.size() > MAX_TEAMS) ? MAX_TEAMS : static_cast<int32_t>(teams.size());
    for (int i = 0; i < gameTickPacket.num_teams; i++) {
        if (teams[i]) {
            TeamInfo teamInfo = {};
            teamInfo.team_index = teams[i]->TeamIndex;
            teamInfo.score = teams[i]->Score;
            gameTickPacket.teams[i] = teamInfo;
        }
    }

    gameTickPacket.num_boost = NUM_BOOST_PADS;
    for (int i = 0; i < NUM_BOOST_PADS; i++) {
        BoostPadState boostState = {};
        boostState.is_active = GameEventHookModule::field.boost_pads[i].is_active;
        boostState.timer = boostState.is_active ? 0.0f : GameEventHookModule::field.boost_pads[i].get_elapsed_time();
        gameTickPacket.game_boosts[i] = boostState;
    }

    return gameTickPacket;
}

FieldInfoPacket generateFieldInfoPacket(AGameEvent_Soccar_TA* gameEvent) {
    FieldInfoPacket fieldPacket = {};


    fieldPacket.num_boosts = NUM_BOOST_PADS;
    for (int i = 0; i < NUM_BOOST_PADS; i++) {
        BoostPad boostPad = {};
        boostPad.location = GameEventHookModule::field.boost_pads[i].location;
        boostPad.is_full_boost = GameEventHookModule::field.boost_pads[i].is_big;
        fieldPacket.boost_pads[i] = boostPad;
    }


    if (gameEvent) {
        TArray<UGoal_TA*> goals = gameEvent->Goals;
        fieldPacket.num_goals = (goals.size() > MAX_GOALS) ? MAX_GOALS : static_cast<int32_t>(goals.size());

        for (int i = 0; i < fieldPacket.num_goals; i++) {
            if (goals[i]) {
                GoalInfo goalInfo = {};


                FVector goalLocation = goals[i]->Location;
                goalInfo.location.x = goalLocation.X;
                goalInfo.location.y = goalLocation.Y;
                goalInfo.location.z = goalLocation.Z;


                FVector goalDirection = goals[i]->Direction;
                goalInfo.direction.x = goalDirection.X;
                goalInfo.direction.y = goalDirection.Y;
                goalInfo.direction.z = goalDirection.Z;

                goalInfo.team_num = goals[i]->TeamNum;





                FVector boxMin = goals[i]->WorldBox.Min;
                FVector boxMax = goals[i]->WorldBox.Max;

                goalInfo.width = boxMax.X - boxMin.X;
                goalInfo.height = boxMax.Y - boxMin.Y;

                fieldPacket.goals[i] = goalInfo;
            }
        }
    }

    return fieldPacket;
}

std::string platformToString(int Platform) {
    switch (Platform) {
    case 0:
        return "Unknown";
    case 1:
        return "Steam";
    case 2:
        return "PSN";
    case 4:
        return "Xbox";
    case 6:
        return "Switch";
    case 7:
        return "PsyNet";
    case 11:
        return "Epic";
    }

                                                                                
                                                                          
                                                                               
    return "Unknown";
}

uintptr_t getNetIDAddress(APRI_TA* PRI) {
    return (uintptr_t)&PRI->UniqueId;
}

std::string getIdentifier(uintptr_t netID, std::string playerName = "N/A") {
    FUniqueNetId* id = reinterpret_cast<FUniqueNetId*>(netID);
    uint8_t platformId = static_cast<uint8_t>(id->Platform);
    std::string platform = platformToString(platformId);
    std::string ID;
    if (platform == "Epic") {
        ID = id->EpicAccountId.ToString();
    }
    else if (platform == "Steam") {
        ID = std::to_string(id->Uid);
    }
    else if (platform == "Xbox" || platform == "PS4" || platform == "Switch") {
        ID = playerName;
    }
    else {
        ID = "UnknownPlatform(UID:" + std::to_string(id->Uid) + ")";
    }
    return ID;
}

void GameEventHookModule::PlayerTickCalled(const PostEvent& event) {

    if (!event.Caller() || !event.Caller()->IsA(APlayerController_TA::StaticClass()) || !CurrentGameEvent) {
        return;
    }

    APlayerController_TA* tickingPlayer = static_cast<APlayerController_TA*>(event.Caller());

    static int frameCounter = 0;
    static auto startTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime - startTime);

                                                                                
                                                                                  
                                                                             
      
                                                                         
                                                                        
                                                                       
                                                                                 
                                                                 
                                                                          
      
                                                                              
                                                                               
                                                                                
                                                   
    const double tickNow = getCurrentTimeSeconds();
    static double s_lastPacketBuild = 0.0;
    if (tickNow - s_lastPacketBuild < (1.0 / 30.0))
        return;
    s_lastPacketBuild = tickNow;

    KingFeatures::Tick(CurrentGameEvent, tickingPlayer);
    KingSync::Tick();

    GameTickPacket gameTickPacket = generateCompleteGameTickPacket(CurrentGameEvent, frameCounter++, elapsed.count(), tickingPlayer);

    GameEventHookModule::CurrentGameTickPacket = gameTickPacket;
    UpdatePlayerMmrNamePrefixes();
                                                                               
                                                                              
                                                        
    Items.ReassertEquippedCosmeticOverrides();


    bool wasKickoffPause = IsKickoffPause;
    IsKickoffPause = !gameTickPacket.game_info.is_round_active;

    if (IsKickoffPause && !wasKickoffPause) {
        LastKickoffTime = getCurrentTimeSeconds();
    }
    else if (!IsKickoffPause && wasKickoffPause) {
    }


    if (GameEventHookModule::AutoQueueEnabled) {
        bool matchEnded = gameTickPacket.game_info.is_match_ended;
        if (matchEnded && !GameEventHookModule::AutoQueueThreadRunning && !GameEventHookModule::AutoQueueDone) {
            int delaySec = (GameEventHookModule::AutoQueueDelaySeconds > 0) ? GameEventHookModule::AutoQueueDelaySeconds : 0;
            GameEventHookModule::AutoQueueThreadRunning = true;
            std::thread([delaySec](){
                GameEventHookModule::ScopedWorker worker;

                if (delaySec > 0) {
                    std::this_thread::sleep_for(std::chrono::seconds(delaySec));
                }

                for (int i = 0; i < 600; ++i) {
                    if (g_DllUnloading.load()) break;
                    if (!GameEventHookModule::IsInGame) break;
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                }

                if (g_DllUnloading.load()) {
                    GameEventHookModule::AutoQueueThreadRunning = false;
                    return;
                }
                Main.Execute([](){ Main.StartMatchmaking(); });
                GameEventHookModule::AutoQueueDone = true;
                GameEventHookModule::AutoQueueThreadRunning = false;
            }).detach();
        }
    }


    if (GameEventHookModule::AutoLeaveEnabled) {
        bool matchEnded = gameTickPacket.game_info.is_match_ended;
        if (matchEnded && !GameEventHookModule::AutoLeaveTriggered && !GameEventHookModule::AutoLeaveDone) {
            GameEventHookModule::AutoLeaveTriggered = true;
            int delaySec = (GameEventHookModule::AutoLeaveDelaySeconds > 0) ? GameEventHookModule::AutoLeaveDelaySeconds : 0;
            GameEventHookModule::AutoLeaveReadyAt = getCurrentTimeSeconds() + static_cast<double>(delaySec);
        }
        if (GameEventHookModule::AutoLeaveTriggered && getCurrentTimeSeconds() >= GameEventHookModule::AutoLeaveReadyAt) {
            GameEventHookModule::AutoLeaveTriggered = false;
            GameEventHookModule::AutoLeavePolling = true;
        }
    }


    if (GameEventHookModule::AutoLeavePolling) {

        if (GameEventHookModule::IsInGame) {
            Main.Execute([]() { Main.LeaveMatch(); });
        } else {
            GameEventHookModule::AutoLeaveDone = true;
            GameEventHookModule::AutoLeavePolling = false;
        }
    }
}

int GameEventHookModule::findPlayerIndexInGameTickPacket(APlayerController_TA* playerController, const GameTickPacket& gameTickPacket) {
    if (!playerController) return -1;


    APRI_TA* tickingPRI = playerController->PRI;
    if (!tickingPRI) return -1;


    for (int i = 0; i < gameTickPacket.num_cars; i++) {
        if (gameTickPacket.game_cars[i].PRI == tickingPRI) {
            return i;
        }
    }

    return -1;
}

void GameEventHookModule::CacheSkillCalled(PreEvent& event) {
    try {
        std::string caller = event.Caller()->GetFullName();
    }
    catch (...) { Console.Error("CacheSkillCalledError"); }
}

void GameEventHookModule::OnGameEventStart(PreEvent& event)
{
    try
    {
        std::string functionName = std::string(event.Function()->GetName());

        if (event.Caller() && event.Caller()->IsA(AGameEvent_Soccar_TA::StaticClass()))
        {
            CurrentGameEvent = static_cast<AGameEvent_Soccar_TA*>(event.Caller());
        }


        GameEventActive = true;
        std::string discordPlaylistName = "Rocket League";
        MatchStartedLogged = false;
        MatchEndedLogged = false;
        AutoQueueTriggered = false;
        AutoLeaveTriggered = false;
        AutoQueueDone = false;
        AutoLeaveDone = false;
        AutoLeavePolling = false;


        if (functionName.find("PostBeginPlay") != std::string::npos) {
            HostSync::ResetSessionState();
            MatchmakingShield::Reset();
            KingFeatures::ResetSession();

            if (DiscordWebhookEnabled && !MatchStartedLogged) {
                LogMatchStart();
            }
        }

        if (CurrentGameEvent) {
            UGameSettingPlaylist_X* Playlist = CurrentGameEvent->GetPlaylist();

            if (Playlist)
            {


                int id = Playlist->PlaylistId;
                std::string playlistName;
                auto it = PLAYLIST_MAP.find(id);
                if (it != PLAYLIST_MAP.end()) {
                    playlistName = it->second;
                }
                else {
                    playlistName = "Unknown";
                }
                discordPlaylistName = playlistName;
                Console.Notify("Detected Playlist: " + playlistName);
            }
            else
            {
                Console.Error("CurrentGameEvent->PlaylistId returned nullptr.");
            }
        }

        LastGameState = functionName;
        IsInReplayPlayback = false;
        IsInGame = true;
        CustomMatchModule::SynchronizeHostedLanPassword(CurrentGameEvent);
        CustomMatchModule::EnforceHostedLanBotPolicy(CurrentGameEvent);
        CustomMatchModule::SetLanStatusMatchReady(true);

        if (Events.CanUseLocalServerFeatures() && CurrentGameEvent)
        {
            FakeSpectator::Create(CurrentGameEvent);
        }

        KingModRestoreWorkshopAliasAfterTravel();

        if (Events.setOnlineStatus && !Events.customStatus.empty())
            Events.forceStatusUpdate = true;

                                                                                 
                                                                            
                                                       
        if (CustomMatchModule::IsInCustomMatch &&
            CustomMatchModule::CurrentMatchType == ECustomMatchSettingsType::CustomMatchSettingsType_LocalMatch)
        {
            std::string host = CustomMatchModule::LanHostIP.empty()
                ? CustomMatchModule::GetDetectedLocalIP()
                : CustomMatchModule::LanHostIP;
            const std::string port = CustomMatchModule::LanHostPort.empty()
                ? "7777" : CustomMatchModule::LanHostPort;
            if (!host.empty())
            {
                CustomMatchModule::LanHostIP = host;
                const std::string password = !CustomMatchModule::HostPassword.empty()
                    ? CustomMatchModule::HostPassword : CustomMatchModule::Password;
                const std::string rpcServerName = CustomMatchModule::ServerName.empty()
                    ? "KingMod Server" : CustomMatchModule::ServerName;
                if (CustomMatchModule::IsLanJoinPasswordSafe(password))
                {
                    KingModRPC::SetJoinableServer(
                        host + ":" + port, password, 1, CustomMatchModule::MaxPlayers,
                        "Hosting " + discordPlaylistName,
                        rpcServerName);
                }
                else
                {
                    KingModRPC::SetNotJoinable(
                        "Hosting " + discordPlaylistName,
                        rpcServerName);
                }
            }
        }
        else
        {
            KingModRPC::SetNotJoinable(
                "Playing " + discordPlaylistName,
                "KingMod | Rocket League");
        }
    }
    catch (...) { Console.Error("GameEventHook: Exception in OnGameEventStart"); }
}

PlayerControllerData GameEventHookModule::GetPlayerControllerData()
{
    PlayerControllerData data = {};
    if (!CurrentGameEvent) { return data; }
    TArray<APlayerController_TA*> localPlayers = getLocalPlayers(CurrentGameEvent);
    if (localPlayers.empty()) { return data; }
    APlayerController_TA* localPlayer = localPlayers[0];
    if (!CurrentGameEvent || !localPlayer) return data;
    data.Controller = localPlayers[0];
    if (data.Controller)
    {
        data.Camera = localPlayer->PlayerCamera;
        data.PRI = localPlayer->PRI;

        if (data.PRI) {
            ACar_TA* car = data.PRI->Car;
            data.Car = car;
        }
    }
    return data;
}

CameraData GameEventHookModule::GetCameraData()
{
    CameraData data = {};
    data.FOV = 90.0f;
    data.Location = { 0.f, 0.f, 0.f };
    data.Rotation = { 0, 0, 0 };
    PlayerControllerData pcData = GetPlayerControllerData();
    if (!pcData.Controller || !pcData.Camera) return data;
    FVector cameraLocation = pcData.Camera->Location;
    FRotator cameraRotation = pcData.Camera->Rotation;
    float cameraDefaultFOV = pcData.Camera->DefaultFOV;
    data.Location = cameraLocation;
    data.Rotation = cameraRotation;
    if (cameraDefaultFOV > 1.0f) data.FOV = cameraDefaultFOV;
    return data;
}

float DotProduct(const FVector& A, const FVector& B) {
    return A.X * B.X + A.Y * B.Y + A.Z * B.Z;
}

bool GameEventHookModule::WorldToScreen(const FVector& WorldLocation, FVector2D& ScreenLocation, float& Depth)
{
    CameraData camera = GetCameraData();
    if (camera.FOV <= 0.0f) return false;

    INT32 ViewportSizeX = GUI.DisplayX;
    INT32 ViewportSizeY = GUI.DisplayY;
    if (ViewportSizeX <= 0 || ViewportSizeY <= 0) return false;




    auto [cam_axis_x, cam_axis_y, cam_axis_z] = get_axes(camera.Rotation);

    FVector Delta = SubtractVectors(WorldLocation, camera.Location);

    FVector Transformed;
    Transformed.X = DotProduct(Delta, cam_axis_y);
    Transformed.Y = DotProduct(Delta, cam_axis_z);
    Transformed.Z = DotProduct(Delta, cam_axis_x);



    if (Transformed.Z < 1.0f) return false;

    Depth = Transformed.Z;

    float FOVRadians = camera.FOV * (3.14159265f / 180.0f);
    float TanHalfFOV = tan(FOVRadians / 2.0f);

    float ScreenCenterX = ViewportSizeX / 2.0f;
    float ScreenCenterY = ViewportSizeY / 2.0f;

    ScreenLocation.X = ScreenCenterX + Transformed.X * (ScreenCenterX / TanHalfFOV) / Transformed.Z;
    ScreenLocation.Y = ScreenCenterY - Transformed.Y * (ScreenCenterX / TanHalfFOV) / Transformed.Z;

    return (ScreenLocation.X >= 0.0f && ScreenLocation.X <= ViewportSizeX &&
        ScreenLocation.Y >= 0.0f && ScreenLocation.Y <= ViewportSizeY);
}

void GameEventHookModule::OnGameEventDestroyed(PreEvent& event)
{
    try
    {
                                                                                                                                  
        if (event.Caller() && CurrentGameEvent && event.Caller() != CurrentGameEvent)
        {
            return;
        }

        if (DiscordWebhookEnabled && GameEventActive && !MatchEndedLogged) {
            LogMatchEnd();
        }

                                                                      
                                                                           
                                                                       
        g_PlayerMmrOriginalNames.clear();
        HostSync::ResetSessionState();
        MatchmakingShield::Reset();
        KingFeatures::ResetSession();
        FakeSpectator::Remove();

        KingModRPC::SetNotJoinable("In Main Menu", "KingMod | Rocket League");

        GameEventActive = false;
        CurrentGameEvent = nullptr;
        IsInGame = false;
        CustomMatchModule::SetLanStatusMatchReady(false);
        IsInReplayPlayback = false;
        CurrentBall.IsValid = false;
        CurrentGameTickPacket = GameTickPacket{};
    }
    catch (...) { Console.Error("GameEventHook: Exception in OnGameEventDestroyed"); }
}

void GameEventHookModule::OnBoostPickedUp(PreEvent& event) {  }
void GameEventHookModule::OnChatMessage(PreEvent& event) {  }

void GameEventHookModule::UpdateBallInfo(bool shouldLog)
{
    if (BallSpawnedFlag) {
        BallSpawnedFlag = false;
        shouldLog = true;
    }
    try
    {
        if (!CurrentGameEvent) {
            CurrentBall.IsValid = false;
            return;
        }
        TArray<ABall_TA*> ballsArray = CurrentGameEvent->GameBalls;
        std::vector<ABall_TA*> balls;
        for (int i = 0; i < ballsArray.size() && i < 10; ++i) {
            if (ballsArray[i]) balls.push_back(ballsArray[i]);
        }

        if (!balls.empty() && balls[0] != nullptr)
        {
            ABall_TA* ball = balls[0];
            CurrentBall.Location = ball->Location;
            CurrentBall.Velocity = ball->Velocity;
            CurrentBall.AngularVelocity = ball->AngularVelocity;
            CurrentBall.IsValid = true;
        }
        else
        {
            CurrentBall.IsValid = false;
        }
    }
    catch (...) {
        CurrentBall.IsValid = false;
    }
}

void GameEventHookModule::UpdatePlayers() {
    try {
        players.Valid = false;
        players.players.clear();

        if (!CurrentGameEvent) {
            return;
        }

        TArray<ACar_TA*> carsArray = CurrentGameEvent->Cars;
        std::vector<ACar_TA*> cars;
        for (int i = 0; i < carsArray.size() && i < 10; ++i) {
            if (carsArray[i]) cars.push_back(carsArray[i]);
        }

        if (!cars.empty() && cars[0] != nullptr) {
            for (ACar_TA* car : cars) {
                APRI_TA* pri = car->PRI;
                if (!car) continue;
                if (!pri) {
                    continue;
                }
                Player player;
                player.Location = car->Location;
                player.Velocity = car->Velocity;
                player.BoostComponent = car->BoostComponent;
                player.PRI = pri;

                if (IsPointerReadable(player.BoostComponent)) {
                    float boostRaw = player.BoostComponent->CurrentBoostAmount;
                    player.BoostAmount = boostRaw * 100;



                }

                players.players.push_back(player);
            }

            players.Valid = true;
        }
    }
    catch (...) {

    }
}

PrivBallInfo GameEventHookModule::GetBallInfo()
{
    return CurrentBall;
}

Players GameEventHookModule::GetPlayers() {
    return players;
}

void GameEventHookModule::DrawBoostTimers() {
    if (!CurrentGameEvent) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;


    for (int i = 0; i < NUM_BOOST_PADS; i++) {
        CppBoostPad& pad = field.boost_pads[i];


        FVector boost_location;
        boost_location.X = pad.location.x;
        boost_location.Y = pad.location.y;
        boost_location.Z = pad.location.z;


        FVector2D screenLocation;
        float depth;
        if (WorldToScreen(boost_location, screenLocation, depth)) {

            float base = (std::max)(6.0f, (std::min)(36.0f, 1500.0f / (depth + 1.0f)));
            float sizeMul = pad.is_big ? 1.25f : 1.0f;
            float radius = base * sizeMul * GameEventHookModule::BoostPadMarkerScale;




            if (!pad.is_active) {
                float timeRemaining = pad.get_time_remaining();
                if (timeRemaining > 0.0f) {
                    char timerText[16];
                    sprintf_s(timerText, "%.1fs", timeRemaining);
                    ImFont* font = ImGui::GetFont();
                    float fontSize = ImGui::GetFontSize() * GameEventHookModule::BoostPadMarkerScale;
                    ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, timerText);
                    drawList->AddText(font, fontSize,
                        ImVec2(screenLocation.X - textSize.x * 0.5f, screenLocation.Y - textSize.y * 0.5f),
                        IM_COL32(255, 255, 255, 255), timerText);
                }
            }


#ifdef _DEBUG
            std::string index_text = std::to_string(i);
            ImVec2 index_pos(screenLocation.X - 5, screenLocation.Y - radius - 15);
            drawList->AddText(index_pos, IM_COL32(255, 255, 0, 255), index_text.c_str());
#endif
        }
    }
}

bool GameEventHookModule::CanDodgeFlip(ACar_TA* car) {
    if (!car) {
        return false;
    }

    try {
        if (car->bUnlimitedJumps) {
            return true;
        }
    }
    catch (...) {}

    try {
        if (car->bOnGround) {
            return true;
        }

        if (car->bDoubleJumped) {
            return false;
        }

        if (!car->bJumped) {
            return true;
        }
    }
    catch (...) {
        return false;
    }

    try {
        if (car->IsWithinDodgeTimeWindow()) {
            return true;
        }
    }
    catch (...) {}

    if (IsPointerReadable(car->JumpComponent)) {
        try {
            float inactiveTime = car->JumpComponent->GetInactiveTime();
            float maxDodgeTime = car->MaxTimeForDodge;
            if (maxDodgeTime <= 0.0f || maxDodgeTime > 3.0f) {
                maxDodgeTime = 1.25f;
            }
            if (inactiveTime <= maxDodgeTime) {
                return true;
            }
        }
        catch (...) {
            return false;
        }
    }

    return false;
}

                                                                              
                                   
  
                                                                               
                                                                              
                                                                             
                                                                            
                                                                             
                                                                    
                                                                            
                                                                                 
                                                                 
                                                                             
                                                                     
                                                     
                                                                             
                                                                     
                                                                              
namespace {
    struct RemoteFlipState {
        int  dodgeCount   = 0;
        int  dblCount     = 0;
        int  refreshCount = 0;
        bool hasFlip      = true;
        bool init         = false;
    };
    std::map<ACar_TA*, RemoteFlipState> g_remoteFlipStates;
}

bool GameEventHookModule::HasFlipAvailable(ACar_TA* car, bool authoritative) {
    if (!car) return false;

                                                                           
                                                                             
                                                              
    if (authoritative) return CanDodgeFlip(car);

                                                                         
    try { if (car->bUnlimitedJumps) return true; } catch (...) {}

    int dodgeCount = 0, dblCount = 0, refreshCount = 0;
    bool onGround = false;
    try { if (IsPointerReadable(car->DodgeComponent))      dodgeCount = car->DodgeComponent->AirActivateCount; }      catch (...) {}
    try { if (IsPointerReadable(car->DoubleJumpComponent)) dblCount   = car->DoubleJumpComponent->AirActivateCount; } catch (...) {}
    try { refreshCount = car->DodgesRefreshedCounter; } catch (...) {}
    try { onGround = car->bOnGround; } catch (...) {}

    RemoteFlipState& st = g_remoteFlipStates[car];
    if (!st.init) {
        st.init = true;
        st.hasFlip = true;
    }
    else {
                                                                               
                                                                            
        if (dodgeCount < st.dodgeCount || dblCount < st.dblCount || refreshCount < st.refreshCount)
            st.hasFlip = true;
                                                              
        if (dodgeCount > st.dodgeCount || dblCount > st.dblCount)
            st.hasFlip = false;
                                                                        
        if (refreshCount > st.refreshCount || onGround)
            st.hasFlip = true;
    }
    st.dodgeCount   = dodgeCount;
    st.dblCount     = dblCount;
    st.refreshCount = refreshCount;
    return st.hasFlip;
}


                                                                              
                                               
  
                                                                             
                                                                         
                                                                                
                                                                              
namespace {
    constexpr float kEnemyHardcodedFlipWindow = 1.25f;

    struct EnemyFlipVisualTimerState {
        int dodgeCount = 0;
        int dblCount = 0;
        int refreshCount = 0;
        bool initialized = false;
        bool lastOnGround = true;
        bool lastJumped = false;
        bool lastDoubleJumped = false;
        float lastReplicatedActivity = -1.0f;
        float timeLeft = 0.0f;
        bool active = false;
        bool expired = false;
    };

    std::map<ACar_TA*, EnemyFlipVisualTimerState> g_enemyFlipVisualTimers;

    bool UpdateEnemyHardcodedFlipCountdown(ACar_TA* car,
                                           bool authoritative,
                                           bool hasFlip,
                                           float& outTimeLeft,
                                           float& outMaxTime,
                                           bool& outExpired)
    {
        outTimeLeft = 0.0f;
        outMaxTime = kEnemyHardcodedFlipWindow;
        outExpired = false;
        if (!car)
            return false;

        int dodgeCount = 0;
        int dblCount = 0;
        int refreshCount = 0;
        bool onGround = false;
        bool jumped = false;
        bool doubleJumped = false;
        float replicatedActivity = -1.0f;

        try { if (IsPointerReadable(car->DodgeComponent)) dodgeCount = car->DodgeComponent->AirActivateCount; } catch (...) {}
        try { if (IsPointerReadable(car->DoubleJumpComponent)) dblCount = car->DoubleJumpComponent->AirActivateCount; } catch (...) {}
        try { refreshCount = car->DodgesRefreshedCounter; } catch (...) {}
        try { onGround = car->bOnGround; } catch (...) {}

        if (authoritative)
        {
            try { jumped = car->bJumped; } catch (...) {}
            try { doubleJumped = car->bDoubleJumped; } catch (...) {}
        }
        else
        {
            try
            {
                if (IsPointerReadable(car->JumpComponent))
                    replicatedActivity = car->JumpComponent->ReplicatedActivityTime;
            }
            catch (...) {}
        }

        EnemyFlipVisualTimerState& st = g_enemyFlipVisualTimers[car];
        if (!st.initialized)
        {
            st.initialized = true;
            st.dodgeCount = dodgeCount;
            st.dblCount = dblCount;
            st.refreshCount = refreshCount;
            st.lastOnGround = onGround;
            st.lastJumped = jumped;
            st.lastDoubleJumped = doubleJumped;
            st.lastReplicatedActivity = replicatedActivity;
            return false;
        }

        const bool recharged =
            onGround ||
            dodgeCount < st.dodgeCount ||
            dblCount < st.dblCount ||
            refreshCount != st.refreshCount;

        const bool spentAirMove =
            dodgeCount > st.dodgeCount ||
            dblCount > st.dblCount;

        if (recharged)
        {
            st.active = false;
            st.expired = false;
            st.timeLeft = 0.0f;
        }

        bool firstJump = false;
        if (authoritative)
        {
                                                                              
            firstJump = !onGround && jumped && !st.lastJumped && !doubleJumped;
        }
        else
        {
                                                                                  
                                                                                
                                                   
            firstJump = !onGround && !spentAirMove && replicatedActivity > 0.0f &&
                st.lastReplicatedActivity >= 0.0f &&
                std::fabs(replicatedActivity - st.lastReplicatedActivity) > 0.0005f;
        }

        if (firstJump && hasFlip)
        {
            st.timeLeft = kEnemyHardcodedFlipWindow;
            st.active = true;
            st.expired = false;
        }

        if (spentAirMove || !hasFlip)
        {
            st.active = false;
            st.timeLeft = 0.0f;
                                                                               
                                                                            
            if (spentAirMove)
                st.expired = false;
        }

        if (st.active)
        {
            float dt = 0.0f;
            if (ImGui::GetCurrentContext())
                dt = ImGui::GetIO().DeltaTime;
            if (!std::isfinite(dt) || dt < 0.0f)
                dt = 0.0f;
            if (dt > 0.10f)
                dt = 0.10f;

            st.timeLeft = (std::max)(0.0f, st.timeLeft - dt);
            if (st.timeLeft <= 0.0f)
            {
                st.active = false;
                st.expired = true;
            }
        }

        st.dodgeCount = dodgeCount;
        st.dblCount = dblCount;
        st.refreshCount = refreshCount;
        st.lastOnGround = onGround;
        st.lastJumped = jumped;
        st.lastDoubleJumped = doubleJumped;
        st.lastReplicatedActivity = replicatedActivity;

        outTimeLeft = st.timeLeft;
        outExpired = st.expired;
        return st.active && st.timeLeft > 0.0f;
    }
}

void GameEventHookModule::DrawFlipIndicator() {
    if (!FlipIndicatorEnabled || !IsInGame) {
        return;
    }

    auto playerControllerData = GetPlayerControllerData();
    if (!playerControllerData.Controller || !playerControllerData.Car) {
        return;
    }

    ACar_TA* car = playerControllerData.Car;
    ImDrawList* drawList = ImGui::GetForegroundDrawList();
    ImGuiIO& io = ImGui::GetIO();
    static float trackedMaxWindow = 0.0f;
    static float trackedTimeLeft = 0.0f;
    static bool wasInAirWindow = false;

    bool onGround = false;
    bool jumped = false;
    bool doubleJumped = false;
    bool unlimited = false;
    try {
        onGround = car->bOnGround;
        jumped = car->bJumped;
        doubleJumped = car->bDoubleJumped;
        unlimited = car->bUnlimitedJumps;
    }
    catch (...) {}

    float inactiveTime = 0.0f;
    float maxDodgeTime = 0.0f;
    if (IsPointerReadable(car->JumpComponent)) {
        try {
            inactiveTime = car->JumpComponent->GetInactiveTime();
            maxDodgeTime = car->MaxTimeForDodge;
            if (maxDodgeTime <= 0.0f || maxDodgeTime > 3.0f) {
                maxDodgeTime = 1.25f;
            }
        }
        catch (...) {
            inactiveTime = 0.0f;
            maxDodgeTime = 1.25f;
        }
    }
    else {
        maxDodgeTime = 1.25f;
    }

    bool inAirWindow = jumped && !doubleJumped && !onGround;
    if (inAirWindow) {
        if (!wasInAirWindow || fabs(trackedMaxWindow - maxDodgeTime) > 0.001f) {
            trackedMaxWindow = maxDodgeTime;
            trackedTimeLeft = (inactiveTime > 0.0f && inactiveTime <= maxDodgeTime) ? (maxDodgeTime - inactiveTime) : maxDodgeTime;
        }
        else {
            trackedTimeLeft = (std::max)(0.0f, trackedTimeLeft - io.DeltaTime);
            if (inactiveTime > 0.0f && inactiveTime <= maxDodgeTime) {
                float engineLeft = maxDodgeTime - inactiveTime;
                if (engineLeft < trackedTimeLeft) {
                    trackedTimeLeft = engineLeft;
                }
            }
        }
    }
    else {
        trackedTimeLeft = 0.0f;
        trackedMaxWindow = 0.0f;
    }
    wasInAirWindow = inAirWindow;

    bool canFlipNow = false;
    if (unlimited || onGround || !jumped) {
        canFlipNow = true;
    }
    else if (inAirWindow && trackedTimeLeft > 0.0f) {
        canFlipNow = true;
    }
    else {
        canFlipNow = false;
    }

    const char* label = canFlipNow ? "Flip" : "No Flip";
    ImU32 labelColor = canFlipNow ? ImGui::ColorConvertFloat4ToU32(FlipAvailableColor)
                                  : ImGui::ColorConvertFloat4ToU32(FlipUnavailableColor);
    float progress = 0.0f;
    if (inAirWindow) {
        progress = (trackedMaxWindow > 0.0f) ? (trackedTimeLeft / trackedMaxWindow) : 0.0f;
    }
    else {
        progress = canFlipNow ? 1.0f : 0.0f;
    }
    progress = (progress < 0.0f) ? 0.0f : ((progress > 1.0f) ? 1.0f : progress);

    float fontSize = ImGui::GetFontSize() * FlipIndicatorSize;
    ImVec2 labelSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, label);
    float boxWidth = (std::max)(120.0f, labelSize.x + 24.0f) * FlipIndicatorSize;
    float boxHeight = 24.0f * FlipIndicatorSize;
    float barHeight = 6.0f * FlipIndicatorSize;
    float gap = 4.0f * FlipIndicatorSize;
    ImVec2 center = ImVec2(io.DisplaySize.x * FlipIndicatorPos.x, io.DisplaySize.y * FlipIndicatorPos.y);
    ImVec2 boxMin = ImVec2(center.x - boxWidth * 0.5f, center.y - (boxHeight + barHeight + gap) * 0.5f);
    ImVec2 boxMax = ImVec2(boxMin.x + boxWidth, boxMin.y + boxHeight);
    ImVec2 barMin = ImVec2(boxMin.x, boxMax.y + gap);
    ImVec2 barMax = ImVec2(boxMax.x, barMin.y + barHeight);

    drawList->AddRectFilled(boxMin, boxMax, IM_COL32(0, 0, 0, 170), 4.0f * FlipIndicatorSize);
    drawList->AddRect(boxMin, boxMax, IM_COL32(255, 255, 255, 85), 4.0f * FlipIndicatorSize, 0, 1.0f);

    ImVec2 labelPos = ImVec2(center.x - labelSize.x * 0.5f, boxMin.y + (boxHeight - labelSize.y) * 0.5f);
    drawList->AddText(ImGui::GetFont(), fontSize, labelPos, labelColor, label);

    drawList->AddRectFilled(barMin, barMax, IM_COL32(0, 0, 0, 170), 3.0f * FlipIndicatorSize);
    drawList->AddRect(barMin, barMax, IM_COL32(255, 255, 255, 65), 3.0f * FlipIndicatorSize, 0, 1.0f);
    if (progress > 0.0f) {
        float fillWidth = (barMax.x - barMin.x) * progress;
        drawList->AddRectFilled(barMin, ImVec2(barMin.x + fillWidth, barMax.y), labelColor, 3.0f * FlipIndicatorSize);
    }
}

void GameEventHookModule::DrawBallPrediction()
{
    if (!BallPredictionEnabled || !IsInGame || IsInReplayPlayback)
        return;

    auto& settings = BallPrediction::GetSettings();


    settings.bEnabled = true;

    if (!settings.bShowLine && !settings.bShowBallShape && !settings.bPreHitEnabled &&
        !settings.bGoalCrosshair)
        return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList)
        return;


    BallPrediction::UpdatePrediction();
    BallPrediction::UpdatePreHitPredictions();
    auto predData = BallPrediction::GetPredictionData();

                                                                            
                                                                           
                                                                             
                                                                          
                                              
    struct GoalTargetLatch
    {
        bool Active = false;
        bool HadPreviousBall = false;
        int Side = 0;
        FVector Point{ 0.f, 0.f, 0.f };
        FVector PreviousBall{ 0.f, 0.f, 0.f };
    };
    static GoalTargetLatch s_GoalTargetLatch;

    constexpr float kGoalPlaneY = 5120.0f;
    constexpr float kGoalHalfWidth = 892.755f;
    constexpr float kGoalHeight = 642.775f;
    constexpr float kBallRadius = 93.0f;

    if (CurrentBall.IsValid)
    {
        const FVector live = CurrentBall.Location;
        const int side = live.Y >= 0.0f ? 1 : -1;
        const float absY = std::abs(live.Y);
        const bool insideOpening =
            std::abs(live.X) <= (kGoalHalfWidth - kBallRadius) &&
            live.Z <= (kGoalHeight - kBallRadius);

                                                                       
        if (s_GoalTargetLatch.Active &&
            (absY < kGoalPlaneY - 180.0f || side != s_GoalTargetLatch.Side))
        {
            s_GoalTargetLatch.Active = false;
        }

        if (!s_GoalTargetLatch.Active && insideOpening && absY >= kGoalPlaneY)
        {
            const float planeY = side > 0 ? kGoalPlaneY : -kGoalPlaneY;
            FVector locked = predData.bHasGoalImpact
                ? predData.GoalImpactPoint
                : FVector{ live.X, planeY, live.Z };

                                                                             
                                                                             
                                                                        
            if (s_GoalTargetLatch.HadPreviousBall)
            {
                const FVector prev = s_GoalTargetLatch.PreviousBall;
                const float dy = live.Y - prev.Y;
                const bool crossed = side > 0
                    ? (prev.Y < planeY && live.Y >= planeY)
                    : (prev.Y > planeY && live.Y <= planeY);
                if (crossed && std::abs(dy) > 0.0001f)
                {
                    float f = (planeY - prev.Y) / dy;
                    f = (std::max)(0.0f, (std::min)(1.0f, f));
                    locked.X = prev.X + (live.X - prev.X) * f;
                    locked.Y = planeY;
                    locked.Z = prev.Z + (live.Z - prev.Z) * f;
                }
            }

            locked.Y = planeY;
            locked.X = (std::max)(-kGoalHalfWidth + kBallRadius,
                                  (std::min)(kGoalHalfWidth - kBallRadius, locked.X));
            locked.Z = (std::max)(kBallRadius,
                                  (std::min)(kGoalHeight - kBallRadius, locked.Z));

            s_GoalTargetLatch.Active = true;
            s_GoalTargetLatch.Side = side;
            s_GoalTargetLatch.Point = locked;
        }

        if (s_GoalTargetLatch.Active)
        {
            predData.bGoalPredicted = true;
            predData.bHasGoalImpact = true;
            predData.GoalImpactPoint = s_GoalTargetLatch.Point;
            predData.fGoalImpactTime = 0.0f;
        }

        s_GoalTargetLatch.PreviousBall = live;
        s_GoalTargetLatch.HadPreviousBall = true;
    }
    else
    {
        s_GoalTargetLatch.HadPreviousBall = false;
    }

    const bool hasPredictionPath = predData.WorldPoints && !predData.WorldPoints->empty();
    if (!hasPredictionPath && !(settings.bGoalCrosshair && predData.bHasGoalImpact))
        return;


    ImU32 lineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(
        settings.cLineColor.R,
        settings.cLineColor.G,
        settings.cLineColor.B,
        settings.fOpacity
    ));

    if (settings.bPredictGoal && predData.bGoalPredicted)
    {
        lineColor = ImGui::ColorConvertFloat4ToU32(ImVec4(
            settings.cGoalColor.R,
            settings.cGoalColor.G,
            settings.cGoalColor.B,
            settings.fOpacity
        ));
    }

    const float lineThickness = settings.fThickness;

    size_t pointsToDraw = hasPredictionPath ? predData.WorldPoints->size() : 0;


    if (settings.bShowLine && hasPredictionPath)
    {
                                                                             
                                                         
        drawList->Flags |= ImDrawListFlags_AntiAliasedLines;

        size_t pointSkip = 1;
        if (pointsToDraw > 120)
            pointSkip = 2;

        const bool goalActive = settings.bPredictGoal && predData.bGoalPredicted;

                                                                           
                                                                            
        static std::vector<ImVec2> s_screenPts;
        static std::vector<float>  s_screenT;
        s_screenPts.clear();
        s_screenT.clear();
        for (size_t idx = 0; idx < pointsToDraw; idx += pointSkip)
        {
            FVector2D screenPos;
            float depth;
            if (!WorldToScreen((*predData.WorldPoints)[idx], screenPos, depth))
                continue;
            s_screenPts.push_back(ImVec2(screenPos.X, screenPos.Y));
            s_screenT.push_back((float)idx / (float)pointsToDraw);
        }

        const int n = (int)s_screenPts.size();
        if (n >= 2)
        {
            const float baseOpacity = settings.fOpacity;
            const ImU32 outlineColor = IM_COL32(0, 0, 0, (int)(baseOpacity * 200));

                                                                                  
                                                                                   
            auto colorAt = [&](int i) -> ImU32 {
                if (goalActive)
                    return lineColor;
                if (settings.bRainbow)
                {
                                                                                   
                                                                                     
                                                                                      
                                                                                  
                    const float cycles = 3.0f;                                
                    float phase = s_screenT[i] * cycles
                                - (float)ImGui::GetTime() * (settings.fRainbowSpeed / 50.0f);
                    float hue = phase - floorf(phase);                              
                    float r, g, b;
                    ImGui::ColorConvertHSVtoRGB(hue, 0.90f, 1.0f, r, g, b);
                    return ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, baseOpacity));
                }
                if (settings.bUseSpeedColor)
                {
                    float hue = 0.33f * (1.0f - s_screenT[i]);
                    float r, g, b;
                    ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, r, g, b);
                    return ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, baseOpacity));
                }
                return lineColor;
            };

            const bool uniform = goalActive || (!settings.bRainbow && !settings.bUseSpeedColor);

            if (settings.iDrawStyle == 0 && uniform)
            {
                                                                                  
                                                                               
                drawList->AddPolyline(s_screenPts.data(), n, outlineColor, 0, lineThickness + 3.0f);
                drawList->AddPolyline(s_screenPts.data(), n, lineColor,   0, lineThickness);
            }
            else if (settings.iDrawStyle == 1)
            {
                                                                                 
                                                                                 
                                                                                 
                                                                                 
                const float dashLen = 18.0f, gapLen = 12.0f, period = dashLen + gapLen;
                const float onFrac  = dashLen / period;
                const float travel  = (float)ImGui::GetTime() * 0.6f;                       
                float acc = 0.0f;
                for (int i = 1; i < n; ++i)
                {
                    ImVec2 d = ImVec2(s_screenPts[i].x - s_screenPts[i - 1].x,
                                      s_screenPts[i].y - s_screenPts[i - 1].y);
                    float segLen = sqrtf(d.x * d.x + d.y * d.y);
                    float mid = acc + segLen * 0.5f;
                    acc += segLen;

                    float u = mid / period - travel;
                    u -= floorf(u);                                 
                    if (u >= onFrac) continue;                                 

                    ImU32 segColor = colorAt(i);
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i], outlineColor, lineThickness + 3.0f);
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i], segColor, lineThickness);
                }
            }
            else if (settings.iDrawStyle == 2)
            {
                                                                                     
                                                                                     
                                                                                   
                for (int i = 1; i < n; ++i)
                {
                    float t = s_screenT[i];                                          
                    float fade = 1.0f - t * 0.85f;
                    if (fade < 0.05f) fade = 0.05f;
                    float thick = lineThickness * (0.6f + 1.1f * (1.0f - t));

                    ImU32 segColor = colorAt(i);
                    ImVec4 cf = ImGui::ColorConvertU32ToFloat4(segColor);

                                       
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i],
                        ImGui::ColorConvertFloat4ToU32(ImVec4(cf.x, cf.y, cf.z, fade * baseOpacity * 0.20f)),
                        thick + 8.0f);
                                
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i],
                        ImGui::ColorConvertFloat4ToU32(ImVec4(cf.x, cf.y, cf.z, fade * baseOpacity * 0.45f)),
                        thick + 4.0f);
                                                                         
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i],
                        ImGui::ColorConvertFloat4ToU32(ImVec4(
                            cf.x + (1.0f - cf.x) * 0.35f,
                            cf.y + (1.0f - cf.y) * 0.35f,
                            cf.z + (1.0f - cf.z) * 0.35f,
                            fade * baseOpacity)),
                        thick);
                }
            }
            else
            {
                                                                                    
                                                                                
                for (int i = 1; i < n; ++i)
                {
                    ImU32 segColor = colorAt(i);
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i], outlineColor, lineThickness + 3.0f);
                    drawList->AddLine(s_screenPts[i - 1], s_screenPts[i], segColor, lineThickness);
                }
            }
        }
    }


    if (settings.bShowBallShape && hasPredictionPath)
    {
        ImU32 shapeColor = lineColor;

        for (size_t idx = 0; idx < pointsToDraw; idx += 15)
        {
            const FVector& worldPoint = (*predData.WorldPoints)[idx];

            FVector2D screenPos;
            float depth;
            if (!WorldToScreen(worldPoint, screenPos, depth))
                continue;


            if (settings.bUseSpeedColor && !(settings.bPredictGoal && predData.bGoalPredicted))
            {
                float t = (float)idx / (float)pointsToDraw;
                float hue = 0.33f * (1.0f - t);
                float r, g, b;
                ImGui::ColorConvertHSVtoRGB(hue, 1.0f, 1.0f, r, g, b);
                shapeColor = ImGui::ColorConvertFloat4ToU32(ImVec4(r, g, b, settings.fOpacity));
            }


            float radius = (92.0f * settings.fBallShapeScale) / depth * 500.0f;
            if (radius > 0.5f)
            {
                drawList->AddCircle(
                    ImVec2(screenPos.X, screenPos.Y),
                    radius + 2.0f,
                    IM_COL32(0, 0, 0, (int)(settings.fOpacity * 200)),
                    12,
                    3.0f
                );
                drawList->AddCircle(
                    ImVec2(screenPos.X, screenPos.Y),
                    radius,
                    shapeColor,
                    12,
                    1.5f
                );
            }
        }
    }

                                                                             
                                                                             
                                                                                 
    if (settings.bGoalCrosshair &&
        predData.bGoalPredicted && predData.bHasGoalImpact)
    {
        const FVector centerWorld = predData.GoalImpactPoint;
        FVector2D centerScreen2D;
        float centerDepth = 0.0f;
        if (WorldToScreen(centerWorld, centerScreen2D, centerDepth) && centerDepth > 0.0f)
        {
            const ImU32 goalCol = ImGui::ColorConvertFloat4ToU32(ImVec4(
                settings.cGoalCrosshairColor.R,
                settings.cGoalCrosshairColor.G,
                settings.cGoalCrosshairColor.B,
                settings.fOpacity));
            const ImU32 shadowCol = IM_COL32(0, 0, 0, (int)(settings.fOpacity * 210));

                                                                                 
                                                                                 
            constexpr float worldRadius = 125.0f;
            constexpr int ringSegments = 48;
            ImVec2 ring[ringSegments + 1];
            bool visible[ringSegments + 1]{};

            for (int i = 0; i <= ringSegments; ++i)
            {
                const float a = (6.28318530718f * (float)i) / (float)ringSegments;
                const FVector p{
                    centerWorld.X + std::cos(a) * worldRadius,
                    centerWorld.Y,
                    centerWorld.Z + std::sin(a) * worldRadius
                };
                FVector2D sp;
                float d = 0.0f;
                if (WorldToScreen(p, sp, d) && d > 0.0f)
                {
                    ring[i] = ImVec2(sp.X, sp.Y);
                    visible[i] = true;
                }
            }

            for (int i = 1; i <= ringSegments; ++i)
            {
                if (!visible[i - 1] || !visible[i])
                    continue;
                drawList->AddLine(ring[i - 1], ring[i], shadowCol, 4.0f);
                drawList->AddLine(ring[i - 1], ring[i], goalCol, 2.0f);
            }

            auto drawWorldSpoke = [&](const FVector& a, const FVector& b)
            {
                FVector2D sa, sb;
                float da = 0.0f, db = 0.0f;
                if (!WorldToScreen(a, sa, da) || !WorldToScreen(b, sb, db) || da <= 0.0f || db <= 0.0f)
                    return;
                const ImVec2 ia(sa.X, sa.Y), ib(sb.X, sb.Y);
                drawList->AddLine(ia, ib, shadowCol, 4.0f);
                drawList->AddLine(ia, ib, goalCol, 2.0f);
            };

            constexpr float gap = worldRadius * 0.28f;
            constexpr float spoke = worldRadius * 1.30f;
            drawWorldSpoke(
                FVector{ centerWorld.X - spoke, centerWorld.Y, centerWorld.Z },
                FVector{ centerWorld.X - gap,   centerWorld.Y, centerWorld.Z });
            drawWorldSpoke(
                FVector{ centerWorld.X + gap,   centerWorld.Y, centerWorld.Z },
                FVector{ centerWorld.X + spoke, centerWorld.Y, centerWorld.Z });
            drawWorldSpoke(
                FVector{ centerWorld.X, centerWorld.Y, centerWorld.Z - spoke },
                FVector{ centerWorld.X, centerWorld.Y, centerWorld.Z - gap });
            drawWorldSpoke(
                FVector{ centerWorld.X, centerWorld.Y, centerWorld.Z + gap },
                FVector{ centerWorld.X, centerWorld.Y, centerWorld.Z + spoke });

            const ImVec2 center(centerScreen2D.X, centerScreen2D.Y);
            drawList->AddCircleFilled(center, 3.0f, shadowCol, 12);
            drawList->AddCircleFilled(center, 2.0f, goalCol, 12);

                                                                              
                                                                           
            FVector2D labelAnchor;
            float labelDepth = 0.0f;
            const FVector labelWorld{ centerWorld.X, centerWorld.Y, centerWorld.Z + worldRadius * 1.55f };
            if (!WorldToScreen(labelWorld, labelAnchor, labelDepth))
                labelAnchor = centerScreen2D;

            const char* goalLabel = "GOAL";
            const ImVec2 labelSize = ImGui::CalcTextSize(goalLabel);
            ImVec2 labelPos(labelAnchor.X - labelSize.x * 0.5f, labelAnchor.Y - labelSize.y - 3.0f);
            drawList->AddText(ImVec2(labelPos.x + 1, labelPos.y + 1), IM_COL32(0, 0, 0, 220), goalLabel);
            drawList->AddText(labelPos, goalCol, goalLabel);

            if (settings.bShowGoalTimer && predData.fGoalImpactTime > 0.0f)
            {
                char timerBuf[32];
                sprintf_s(timerBuf, "%.2fs", predData.fGoalImpactTime);
                const ImVec2 tSize = ImGui::CalcTextSize(timerBuf);
                const ImVec2 tPos(labelAnchor.X - tSize.x * 0.5f, labelPos.y - tSize.y - 2.0f);
                drawList->AddText(ImVec2(tPos.x + 1, tPos.y + 1), IM_COL32(0, 0, 0, 220), timerBuf);
                drawList->AddText(tPos, goalCol, timerBuf);
            }
        }
    }

                                                                    
    if (settings.bShowLanding && predData.bHasLanding)
    {
        FVector2D s; float d = 1.0f;
        if (WorldToScreen(predData.LandingPoint, s, d) && d > 0.0f)
        {
            float r = 9000.0f / d;
            if (r < 6.0f) r = 6.0f;
            if (r > 40.0f) r = 40.0f;
            ImU32 c = ImGui::ColorConvertFloat4ToU32(ImVec4(
                settings.cLandingColor.R, settings.cLandingColor.G,
                settings.cLandingColor.B, settings.fOpacity));
            ImU32 sh = IM_COL32(0, 0, 0, (int)(settings.fOpacity * 200));
            ImVec2 ctr(s.X, s.Y);
            drawList->AddCircle(ctr, r + 1.0f, sh, 24, 3.0f);
            drawList->AddCircle(ctr, r, c, 24, 2.0f);
            drawList->AddLine(ImVec2(ctr.x - r, ctr.y), ImVec2(ctr.x + r, ctr.y), c, 1.5f);
        }
    }

                                                              
    if (settings.bShowBounces && predData.BouncePoints)
    {
        ImU32 sh = IM_COL32(0, 0, 0, (int)(settings.fOpacity * 200));
        ImU32 c = ImGui::ColorConvertFloat4ToU32(ImVec4(
            settings.cLineColor.R, settings.cLineColor.G,
            settings.cLineColor.B, settings.fOpacity));
        for (const FVector& bp : *predData.BouncePoints)
        {
            FVector2D s; float d = 1.0f;
            if (!WorldToScreen(bp, s, d) || d <= 0.0f) continue;
            float r = 6000.0f / d;
            if (r < 4.0f) r = 4.0f;
            if (r > 24.0f) r = 24.0f;
            ImVec2 ctr(s.X, s.Y);
            drawList->AddCircle(ctr, r + 1.0f, sh, 16, 2.5f);
            drawList->AddCircle(ctr, r, c, 16, 1.5f);
        }
    }

                                                                            
                                                                             
                                                                             
                                                   
    if (settings.bPreHitEnabled)
    {
        const auto& impacts = BallPrediction::GetPreHitPredictions();
        if (!impacts.empty())
        {
            for (size_t impactIndex = 0; impactIndex < impacts.size(); ++impactIndex)
            {
                const auto& impact = impacts[impactIndex];
                FVector2D contactScreen{};
                float contactDepth = 1.0f;
                if (!WorldToScreen(impact.ContactPoint, contactScreen, contactDepth) || contactDepth <= 0.0f)
                    continue;

                const ImVec2 center(contactScreen.X, contactScreen.Y);
                const ImU32 markerColor = lineColor;
                const ImU32 markerOutline = IM_COL32(0, 0, 0, (int)(settings.fOpacity * 220));
                float radius = 7500.0f / contactDepth;
                radius = (std::max)(5.0f, (std::min)(radius, 26.0f));

                                                                               
                                                                               
                                                                              
                const bool primary = impactIndex == 0;
                if (!primary)
                    radius = (std::max)(4.0f, radius * 0.62f);

                drawList->AddCircle(center, radius + 1.5f, markerOutline, 20, primary ? 3.0f : 2.0f);
                drawList->AddCircle(center, radius, markerColor, 20, primary ? 2.0f : 1.5f);
                drawList->AddCircleFilled(center, primary ? 2.5f : 1.75f, markerColor, 12);

                if (!primary)
                    continue;

                char label[96]{};
                sprintf_s(label, "HIT %.2fs  |  CAR %.0f km/h",
                    impact.TimeToHit, impact.CarSpeed * 0.036f);
                const ImVec2 textSize = ImGui::CalcTextSize(label);
                const ImVec2 textPos(center.x - textSize.x * 0.5f,
                                     center.y - radius - textSize.y - 4.0f);
                drawList->AddText(ImVec2(textPos.x + 1.0f, textPos.y + 1.0f), markerOutline, label);
                drawList->AddText(textPos, markerColor, label);
            }
        }
    }

}

void GameEventHookModule::DrawBallSpeedDisplay() {
    if (!GameEventHookModule::BallSpeedDisplayEnabled) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    float displaySpeed = 0.0f;


    if (CurrentBall.IsValid) {
        FVector velocity = CurrentBall.Velocity;
        float currentSpeed = sqrt(velocity.X * velocity.X + velocity.Y * velocity.Y + velocity.Z * velocity.Z);


        float currentSpeedKmh = currentSpeed * 0.036f;


        if (currentSpeedKmh > 1.0f) {
            LastBallSpeed = currentSpeedKmh;
        }

        displaySpeed = currentSpeedKmh;
    }


    if (displaySpeed <= 1.0f && LastBallSpeed > 0.0f) {
        displaySpeed = LastBallSpeed;
    }


    ImVec2 screenSize = ImGui::GetIO().DisplaySize;


                                                                          
                                                                                
                                                                             
    char speedText[64];
    switch (BallSpeedUnit)
    {
    case 1:
        sprintf_s(speedText, "%.2f mph", displaySpeed * 0.621371f);
        break;
    case 2:
        sprintf_s(speedText, "%.0f uu/s", displaySpeed / 0.036f);
        break;
    default:
        sprintf_s(speedText, "%.2f km/h", displaySpeed);
        break;
    }


    ImFont* font = ImGui::GetFont();
    float fontSize = font->FontSize * BallSpeedDisplaySize;
    ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, speedText);


    float x = (screenSize.x * BallSpeedDisplayX) - (textSize.x * 0.5f);
    float y = screenSize.y * BallSpeedDisplayY;


    float padding = 10.0f * BallSpeedDisplaySize;
    drawList->AddRectFilled(
        ImVec2(x - padding, y - padding * 0.5f),
        ImVec2(x + textSize.x + padding, y + textSize.y + padding * 0.5f),
        IM_COL32(0, 0, 0, 150),
        5.0f * BallSpeedDisplaySize
    );


    drawList->AddText(
        font,
        fontSize,
        ImVec2(x, y),
        IM_COL32(255, 255, 255, 255),
        speedText
    );
}

void GameEventHookModule::DrawCarHitboxes()
{
    if (!CurrentGameEvent) return;

    ImDrawList* drawList = ImGui::GetBackgroundDrawList();
    if (!drawList) return;

    FVector2D ballScreen;
    float ballDepth = 0.0f;
    bool hasBall = CurrentBall.IsValid && WorldToScreen(CurrentBall.Location, ballScreen, ballDepth);

    for (const auto& carInfo : players.players) {
        if (!carInfo.PRI) continue;

        FVector carLocation = carInfo.Location;
        FVector2D screenLocation;
        float depth;

        if (WorldToScreen(carLocation, screenLocation, depth)) {


            float boxWidth = 10000.0f / depth;
            float boxHeight = 5000.0f / depth;
            ImVec2 min = ImVec2(screenLocation.X - boxWidth / 2, screenLocation.Y - boxHeight / 2);
            ImVec2 max = ImVec2(screenLocation.X + boxWidth / 2, screenLocation.Y + boxHeight / 2);
            ImU32 hbColor = ImGui::GetColorU32(HitboxColor);
            drawList->AddRect(min, max, hbColor, 0.0f, 0, 2.0f);

                                                                 
        }
    }
}


FVector getLocalCollisionOffset(ACar_TA* car) {
    return car->LocalCollisionOffset;
}

FVector getLocalCollisionExtent(ACar_TA* car) {
    return car->LocalCollisionExtent;
}

void GameEventHookModule::DrawPlayerBoosts() {
    if (!GameEventHookModule::CurrentGameTickPacket.game_cars) return;
    FVector2D screenLocation;
    float depth;
    for (PlayerInfo player : GameEventHookModule::CurrentGameTickPacket.game_cars) {
        if (player.name.empty()) { continue; }
        FVector loc;
        loc.X = player.physics.location.x;
        loc.Y = player.physics.location.y;
        loc.Z = player.physics.location.z;
        if (WorldToScreen(loc, screenLocation, depth)) {
            float radius = 2000.0f / depth;
            radius = (std::max)(5.0f, (std::min)(radius, 50.0f));
            ImDrawList* drawList = ImGui::GetBackgroundDrawList();
            if (drawList) {
                std::string Platform = platformToString(static_cast<int>(player.PRI->UniqueId.Platform));
                std::string text = player.name + " - " + Platform;

                drawList->AddCircle(ImVec2(screenLocation.X, screenLocation.Y), radius, IM_COL32(255, 0, 0, 255), 32, 2.0f);
                drawList->AddCircleFilled(ImVec2(screenLocation.X, screenLocation.Y), 3.0f, IM_COL32(255, 255, 0, 255), 12);

            }

        }
        else {

        }
    }
}

void GameEventHookModule::DrawMinimap() {
    if (!MinimapEnabled) return;
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    if (!dl) return;

    ImVec2 pos = MinimapPos;
    float size = MinimapSize;
    float radius = size * 0.5f;
    ImVec2 center(pos.x + radius, pos.y + radius);
    float fieldHalfY = 5120.0f;
    float scale = (radius - 14.0f) / fieldHalfY;
    float now = (float)ImGui::GetTime();

    auto WorldToMinimap = [&](float x, float y) -> ImVec2 {
        return ImVec2(center.x + x * scale, center.y - y * scale);
    };

    ImU32 bgCol = IM_COL32(8, 10, 14, (int)(MinimapAlpha * 255.0f));
    ImU32 borderCol = IM_COL32(50, 180, 255, 120);
    ImU32 gridCol = IM_COL32(30, 60, 90, (int)(MinimapAlpha * 100.0f));
    ImU32 accentCol = IM_COL32(50, 180, 255, 80);

    dl->AddCircleFilled(center, radius, bgCol, 64);
    for (float r = 0.25f; r < 1.0f; r += 0.25f)
        dl->AddCircle(center, radius * r, gridCol, 64, 0.6f);
    for (int a = 0; a < 360; a += 30) {
        float rad = a * 3.14159f / 180.0f;
        ImVec2 edge(center.x + cosf(rad) * radius, center.y + sinf(rad) * radius);
        dl->AddLine(center, edge, gridCol, 0.4f);
    }
    dl->AddCircle(center, radius, borderCol, 64, 1.5f);

    if (MinimapShowGoals) {
        float goalW = 1784.0f * scale;
        ImU32 blueCol = ImGui::GetColorU32(MinimapMyTeamColor);
        ImU32 orangeCol = ImGui::GetColorU32(MinimapOpponentColor);
        float gt = 3.0f;
        float gyB = fieldHalfY * scale;
        float gyO = -fieldHalfY * scale;
        dl->AddLine(ImVec2(center.x - goalW * 0.5f, center.y + gyB), ImVec2(center.x + goalW * 0.5f, center.y + gyB), blueCol, gt);
        dl->AddLine(ImVec2(center.x - goalW * 0.5f, center.y + gyO), ImVec2(center.x + goalW * 0.5f, center.y + gyO), orangeCol, gt);
        dl->AddLine(ImVec2(center.x - goalW * 0.5f, center.y + gyB), ImVec2(center.x - goalW * 0.5f, center.y + gyB - 10.0f), blueCol, gt);
        dl->AddLine(ImVec2(center.x + goalW * 0.5f, center.y + gyB), ImVec2(center.x + goalW * 0.5f, center.y + gyB - 10.0f), blueCol, gt);
        dl->AddLine(ImVec2(center.x - goalW * 0.5f, center.y + gyO), ImVec2(center.x - goalW * 0.5f, center.y + gyO + 10.0f), orangeCol, gt);
        dl->AddLine(ImVec2(center.x + goalW * 0.5f, center.y + gyO), ImVec2(center.x + goalW * 0.5f, center.y + gyO + 10.0f), orangeCol, gt);
    }

    if (MinimapShowBoosts) {
        for (int i = 0; i < CurrentFieldInfo.num_boosts && i < MAX_BOOSTS; i++) {
            if (i < CurrentGameTickPacket.num_boost && CurrentGameTickPacket.game_boosts[i].is_active) {
                ImVec2 bp = WorldToMinimap(CurrentFieldInfo.boost_pads[i].location.x, CurrentFieldInfo.boost_pads[i].location.y);
                float br = CurrentFieldInfo.boost_pads[i].is_full_boost ? 3.5f : 1.5f;
                ImU32 bc = CurrentFieldInfo.boost_pads[i].is_full_boost ? IM_COL32(255, 220, 50, 220) : IM_COL32(100, 180, 255, 160);
                dl->AddCircleFilled(bp, br, bc, 10);
            }
        }
    }

    if (MinimapShowBall && CurrentBall.IsValid) {
        ImVec2 ballPos = WorldToMinimap(CurrentBall.Location.X, CurrentBall.Location.Y);
        float pulse = fabsf(sinf(now * 3.0f)) * 0.3f + 0.7f;
        dl->AddCircleFilled(ballPos, 8.0f, IM_COL32(255, 255, 255, (int)(pulse * 50)), 16);
        dl->AddCircleFilled(ballPos, 4.0f, IM_COL32(255, 255, 255, 255), 16);
        dl->AddCircle(ballPos, 4.0f, IM_COL32(200, 200, 200, 255), 16, 1.0f);
        if (MinimapShowDirection) {
            float velLen = sqrtf(CurrentBall.Velocity.X * CurrentBall.Velocity.X + CurrentBall.Velocity.Y * CurrentBall.Velocity.Y);
            if (velLen > 100.0f) {
                float vx = CurrentBall.Velocity.X / velLen;
                float vy = -CurrentBall.Velocity.Y / velLen;
                ImVec2 velEnd(ballPos.x + vx * 14.0f, ballPos.y + vy * 14.0f);
                dl->AddLine(ballPos, velEnd, IM_COL32(255, 255, 255, 180), 1.5f);
            }
        }
    }

    if (MinimapShowPlayers) {
        for (int i = 0; i < CurrentGameTickPacket.num_cars; i++) {
            PlayerInfo& player = CurrentGameTickPacket.game_cars[i];
            if (player.is_demolished) continue;
            ImVec2 pp = WorldToMinimap(player.physics.location.x, player.physics.location.y);
            bool isLocal = (i == CurrentGameTickPacket.localPlayerIndex);
            ImU32 pCol;
            if (isLocal) pCol = IM_COL32(0, 230, 120, 255);
            else if (MinimapTeamColors) pCol = (player.team == 0) ? ImGui::GetColorU32(MinimapMyTeamColor) : ImGui::GetColorU32(MinimapOpponentColor);
            else pCol = ImGui::GetColorU32(MinimapPlayerColor);
            float speed = sqrtf(player.physics.velocity.x * player.physics.velocity.x + player.physics.velocity.y * player.physics.velocity.y);
            float vx = 0, vy = 0;
            if (speed > 100.0f) { vx = player.physics.velocity.x / speed; vy = -player.physics.velocity.y / speed; }
            float triR = isLocal ? 5.0f : 3.5f;
            ImVec2 tip(pp.x + vx * triR * 2.0f, pp.y + vy * triR * 2.0f);
            ImVec2 left, right;
            if (speed > 100.0f) {
                float nx = -vy, ny = vx;
                left = ImVec2(pp.x - vx * triR * 0.5f + nx * triR * 0.9f, pp.y - vy * triR * 0.5f + ny * triR * 0.9f);
                right = ImVec2(pp.x - vx * triR * 0.5f - nx * triR * 0.9f, pp.y - vy * triR * 0.5f - ny * triR * 0.9f);
            } else {
                tip = ImVec2(pp.x, pp.y - triR);
                left = ImVec2(pp.x - triR * 0.9f, pp.y + triR * 0.7f);
                right = ImVec2(pp.x + triR * 0.9f, pp.y + triR * 0.7f);
            }
            dl->AddTriangleFilled(tip, left, right, pCol);
            if (isLocal) {
                float p = fabsf(sinf(now * 2.0f)) * 0.6f + 0.4f;
                dl->AddCircle(pp, 8.0f, IM_COL32(0, 230, 120, (int)(p * 120)), 16);
            }
        }
    }

    {
        const char* title = "RADAR";
        ImVec2 tsz = ImGui::CalcTextSize(title);
        ImVec2 tpos(center.x - tsz.x * 0.5f, pos.y - tsz.y - 6);
        dl->AddRectFilled(ImVec2(tpos.x - 6, tpos.y - 2), ImVec2(tpos.x + tsz.x + 6, tpos.y + tsz.y + 2), IM_COL32(8, 10, 14, 200), 3.0f);
        dl->AddText(tpos, accentCol, title);
    }
}

void GameEventHookModule::DrawPlayerMMR() {
                                                                                                       
}

void GameEventHookModule::DrawControllerOverlay() {
    if (!GameEventHookModule::ControllerOverlay) return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    ImVec2& overlay_pos = GameEventHookModule::ControllerOverlayPos;

    float scale = 1.5f;
    float alpha = GameEventHookModule::ControllerOverlayAlpha;

    ImVec2 p(overlay_pos.x + 12.0f * scale, overlay_pos.y + 4.0f * scale);

    ImU32 WHITE   = IM_COL32(255, 255, 255, (int)(alpha * 255));
    ImU32 BLACK   = IM_COL32(0, 0, 0, (int)(alpha * 255));
    ImU32 GREEN   = IM_COL32(0, 255, 0, (int)(alpha * 255));
    ImU32 RED     = IM_COL32(255, 0, 0, (int)(alpha * 255));
    ImU32 BLUE    = IM_COL32(0, 0, 255, (int)(alpha * 255));
    ImU32 YELLOW  = IM_COL32(255, 255, 0, (int)(alpha * 255));
    ImU32 GREY    = IM_COL32(170, 170, 170, (int)(alpha * 255));
    ImU32 DARKGREY= IM_COL32(85, 85, 85, (int)(alpha * 255));

    static ControllerInput overlayInput = { 0,0,0,0,0,false,false,false,false };
    auto pcData = GetPlayerControllerData();
    if (pcData.Controller) {
        FVehicleInputs vi = pcData.Controller->VehicleInput;
        overlayInput.Throttle = vi.Throttle;
        overlayInput.Steer = vi.Steer;
        overlayInput.Pitch = vi.Pitch;
        overlayInput.Yaw = vi.Yaw;
        overlayInput.Roll = vi.Roll;
        overlayInput.Jump = vi.bJump;
        overlayInput.Boost = vi.bActivateBoost || vi.bHoldingBoost;
        overlayInput.Handbrake = vi.bHandbrake;
    }
    ControllerInput* ai = &overlayInput;

    static float smoothSteer = 0.0f, smoothPitch = 0.0f;
    smoothSteer = smoothSteer + (ai->Steer - smoothSteer) * 0.15f;
    smoothPitch = smoothPitch + (ai->Pitch - smoothPitch) * 0.15f;

    bool lt_p = ai->Throttle < 0.0f;
    bool rt_p = ai->Throttle > 0.0f;
    bool lb_p = ai->Handbrake;
    bool rb_p = false;
    bool ls_p = false;
    bool a_p  = ai->Jump;
    bool b_p  = ai->Boost;
    bool x_p  = ai->Handbrake;
    bool y_p  = false;

    float buttonWidth = 48.0f * scale;
    float buttonHeight = 16.0f * scale;

    ImVec2 ltPos(p.x, p.y);
    ImVec2 rtPos(p.x + 128.0f * scale, p.y);

    if (lt_p) {
        dl->AddRectFilled(ltPos, ImVec2(ltPos.x + buttonWidth, ltPos.y + buttonHeight), WHITE, 8, ImDrawCornerFlags_TopLeft);
        dl->AddText(ImVec2(ltPos.x + 18.0f * scale, ltPos.y + 1.0f * scale), BLACK, "LT");
    } else {
        dl->AddRect(ltPos, ImVec2(ltPos.x + buttonWidth, ltPos.y + buttonHeight), WHITE, 8, ImDrawCornerFlags_TopLeft, 2 * scale);
        dl->AddText(ImVec2(ltPos.x + 18.0f * scale, ltPos.y + 1.0f * scale), WHITE, "LT");
    }

    if (rt_p) {
        dl->AddRectFilled(rtPos, ImVec2(rtPos.x + buttonWidth, rtPos.y + buttonHeight), WHITE, 8, ImDrawCornerFlags_TopRight);
        dl->AddText(ImVec2(rtPos.x + 18.0f * scale, rtPos.y + 1.0f * scale), BLACK, "RT");
    } else {
        dl->AddRect(rtPos, ImVec2(rtPos.x + buttonWidth, rtPos.y + buttonHeight), WHITE, 8, ImDrawCornerFlags_TopRight, 2 * scale);
        dl->AddText(ImVec2(rtPos.x + 18.0f * scale, rtPos.y + 1.0f * scale), WHITE, "RT");
    }

    p.y += buttonHeight + 4.0f * scale;

    ImVec2 lbPos(p.x, p.y);
    ImVec2 rbPos(p.x + 128.0f * scale, p.y);

    if (lb_p) {
        dl->AddRectFilled(lbPos, ImVec2(lbPos.x + buttonWidth, lbPos.y + buttonHeight), WHITE);
        dl->AddText(ImVec2(lbPos.x + 18.0f * scale, lbPos.y + 1.0f * scale), BLACK, "LB");
    } else {
        dl->AddRect(lbPos, ImVec2(lbPos.x + buttonWidth, lbPos.y + buttonHeight), WHITE, 0, 0, 2 * scale);
        dl->AddText(ImVec2(lbPos.x + 18.0f * scale, lbPos.y + 1.0f * scale), WHITE, "LB");
    }

    if (rb_p) {
        dl->AddRectFilled(rbPos, ImVec2(rbPos.x + buttonWidth, rbPos.y + buttonHeight), WHITE);
        dl->AddText(ImVec2(rbPos.x + 18.0f * scale, rbPos.y + 1.0f * scale), BLACK, "RB");
    } else {
        dl->AddRect(rbPos, ImVec2(rbPos.x + buttonWidth, rbPos.y + buttonHeight), WHITE, 0, 0, 2 * scale);
        dl->AddText(ImVec2(rbPos.x + 18.0f * scale, rbPos.y + 1.0f * scale), WHITE, "RB");
    }

    p.y += buttonHeight + 16.0f * scale;
    p.x -= 8.0f * scale;

    float leftStickRadius = 32.0f * scale;
    ImVec2 leftStickCenter(p.x + leftStickRadius, p.y + leftStickRadius);

    dl->AddCircle(leftStickCenter, 24.0f * scale, WHITE, 32, 2 * scale);

    dl->AddCircleFilled(
        ImVec2(leftStickCenter.x + smoothSteer * 8.0f * scale, leftStickCenter.y + smoothPitch * 8.0f * scale),
        20.0f * scale, (ls_p ? GREY : WHITE), 32);
    dl->AddCircleFilled(
        ImVec2(leftStickCenter.x + smoothSteer * 8.0f * scale, leftStickCenter.y + smoothPitch * 8.0f * scale),
        16.0f * scale, (ls_p ? DARKGREY : GREY), 32);

    float buttonRadius = 12.0f * scale;
    ImVec2 buttonsCenter(leftStickCenter.x + 128.0f * scale, leftStickCenter.y);

    struct BtnDef { float ox; float oy; bool pressed; ImU32 color; const char* name; };
    BtnDef btns[] = {
        { 0,                  buttonRadius * 2,  a_p,  GREEN,  "A" },
        { buttonRadius * 2,   0,                 b_p,  RED,    "B" },
        {-buttonRadius * 2,   0,                 x_p,  BLUE,   "X" },
        { 0,                 -buttonRadius * 2,  y_p,  YELLOW, "Y" },
    };

    for (int i = 0; i < 4; i++) {
        ImVec2 pos(buttonsCenter.x + btns[i].ox, buttonsCenter.y + btns[i].oy);
        if (btns[i].pressed) {
            dl->AddCircleFilled(pos, buttonRadius, btns[i].color, 32);
            ImVec2 ts = ImGui::CalcTextSize(btns[i].name);
            dl->AddText(ImVec2(pos.x - ts.x * 0.5f + 3.0f * scale, pos.y - ts.y * 0.5f - 1), BLACK, btns[i].name);
        } else {
            dl->AddCircle(pos, buttonRadius, btns[i].color, 32, 2 * scale);
            ImVec2 ts = ImGui::CalcTextSize(btns[i].name);
            dl->AddText(ImVec2(pos.x - ts.x * 0.5f + 3.0f * scale, pos.y - ts.y * 0.5f - 1), btns[i].color, btns[i].name);
        }
    }
}


void GameEventHookModule::DrawShoulderButton(ImDrawList* draw_list, float x, float y, const char* label, float value) {
    float w = 32.0f, h = 14.0f, r = 3.0f;

    draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), IM_COL32(30, 30, 30, 200), r);

    if (value > 0.05f) {
        float fill_w = w * (std::min)(value, 1.0f);
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x + fill_w, y + h), IM_COL32(80, 80, 80, 220), r);
    }

    ImVec2 ts = ImGui::CalcTextSize(label);
    ImVec2 tp = ImVec2(x + w * 0.5f - ts.x * 0.5f, y + h * 0.5f - ts.y * 0.5f);
    draw_list->AddText(tp, IM_COL32(160, 160, 160, 255), label);
}

void GameEventHookModule::DrawCompactStick(ImDrawList* draw_list, float x, float y, float x_axis, float y_axis) {
    float outer_r = 22.0f;
    float inner_r = 10.0f;
    float max_move = 14.0f;

    draw_list->AddCircleFilled(ImVec2(x, y), outer_r, IM_COL32(28, 28, 28, 200));
    draw_list->AddCircle(ImVec2(x, y), outer_r, IM_COL32(55, 55, 55, 255), 32, 1.5f);

    float stick_x = x + x_axis * max_move;
    float stick_y = y + y_axis * max_move;

    draw_list->AddCircleFilled(ImVec2(stick_x, stick_y), inner_r, IM_COL32(70, 70, 70, 255));
    draw_list->AddCircle(ImVec2(stick_x, stick_y), inner_r, IM_COL32(140, 140, 140, 255), 32, 1.5f);
}

void GameEventHookModule::DrawFaceButton(ImDrawList* draw_list, float x, float y, const char* label, bool pressed, ImU32 color) {
    float r = 12.0f;

    if (pressed) {
        draw_list->AddCircleFilled(ImVec2(x, y), r, color);
        ImVec2 ts = ImGui::CalcTextSize(label);
        draw_list->AddText(ImVec2(x - ts.x * 0.5f, y - ts.y * 0.5f), IM_COL32(255, 255, 255, 255), label);
    } else {
        draw_list->AddCircleFilled(ImVec2(x, y), r, IM_COL32(30, 30, 30, 200));
        draw_list->AddCircle(ImVec2(x, y), r, IM_COL32(55, 55, 55, 255), 32, 1.5f);
        ImVec2 ts = ImGui::CalcTextSize(label);
        draw_list->AddText(ImVec2(x - ts.x * 0.5f, y - ts.y * 0.5f), IM_COL32(140, 140, 140, 255), label);
    }
}

void GameEventHookModule::DrawKeyboardOverlay() {
    if (!GameEventHookModule::KeyboardOverlay) return;

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    if (!dl) return;


    ImVec2& kb_pos = GameEventHookModule::KeyboardOverlayPos;
    static bool kb_drag = false;
    static ImVec2 kb_drag_off = ImVec2(0, 0);
    ImVec2 kb_size = ImVec2(500, 220);



    ImVec2 kb_min = kb_pos;
    ImVec2 kb_max = ImVec2(kb_pos.x + kb_size.x, kb_pos.y + kb_size.y);


    ImU32 kbBG = IM_COL32(0, 0, 0, (int)(GameEventHookModule::KeyboardOverlayAlpha * 255.0f));
    dl->AddRectFilled(kb_min, kb_max, kbBG, 15.0f);



    auto is_down = [](int vk)->bool { return (GetAsyncKeyState(vk) & 0x8000) != 0; };


    auto key_col = [](bool p)->ImU32 { return p ? IM_COL32(220, 220, 220, 240) : IM_COL32(40, 40, 40, 200); };
    auto text_col = [](bool p)->ImU32 { return p ? IM_COL32(0, 0, 0, 255) : IM_COL32(200, 200, 200, 255); };
    auto border_col = [](bool p)->ImU32 { return p ? IM_COL32(255, 255, 255, 255) : IM_COL32(80, 80, 80, 255); };

    auto draw_key = [&](float x, float y, float w, float h, const char* label, bool pressed)
    {
        ImVec2 pmin(kb_pos.x + x, kb_pos.y + y);
        ImVec2 pmax(pmin.x + w, pmin.y + h);
        float r = 4.0f;


        dl->AddRectFilled(ImVec2(pmin.x+2, pmin.y+2), ImVec2(pmax.x+2, pmax.y+2), IM_COL32(0,0,0,100), r);


        dl->AddRectFilled(pmin, pmax, key_col(pressed), r);


        dl->AddRect(pmin, pmax, border_col(pressed), r, 0, 1.5f);


        ImVec2 ts = ImGui::CalcTextSize(label);
        ImVec2 tp(pmin.x + (w - ts.x) * 0.5f, pmin.y + (h - ts.y) * 0.5f);
        dl->AddText(tp, text_col(pressed), label);
    };


    const float k = 32.0f;
    const float s = 6.0f;
    const float row_gap = 4.0f;


    float start_x = 20.0f;
    float start_y = 20.0f;


    float y1 = start_y;
    float x_num = start_x + k*0.5f;
    draw_key(x_num + 0*(k+s), y1, k, k, "1", is_down('1'));
    draw_key(x_num + 1*(k+s), y1, k, k, "2", is_down('2'));
    draw_key(x_num + 2*(k+s), y1, k, k, "3", is_down('3'));
    draw_key(x_num + 3*(k+s), y1, k, k, "4", is_down('4'));


    float y2 = y1 + k + s + row_gap;
    float tab_w = k * 1.5f;
    draw_key(start_x, y2, tab_w, k, "Tab", is_down(VK_TAB));
    float x_q = start_x + tab_w + s;
    draw_key(x_q + 0*(k+s), y2, k, k, "Q", is_down('Q'));
    draw_key(x_q + 1*(k+s), y2, k, k, "W", is_down('W'));
    draw_key(x_q + 2*(k+s), y2, k, k, "E", is_down('E'));
    draw_key(x_q + 3*(k+s), y2, k, k, "R", is_down('R'));


    float y3 = y2 + k + s + row_gap;
    float caps_w = k * 1.8f;
    draw_key(start_x, y3, caps_w, k, "Caps", is_down(VK_CAPITAL));
    float x_a = start_x + caps_w + s;
    draw_key(x_a + 0*(k+s), y3, k, k, "A", is_down('A'));
    draw_key(x_a + 1*(k+s), y3, k, k, "S", is_down('S'));
    draw_key(x_a + 2*(k+s), y3, k, k, "D", is_down('D'));
    draw_key(x_a + 3*(k+s), y3, k, k, "F", is_down('F'));


    float y4 = y3 + k + s + row_gap;
    float shift_w = k * 2.3f;
    bool shift_pressed = (is_down(VK_LSHIFT) || is_down(VK_RSHIFT) || is_down(VK_SHIFT));
    draw_key(start_x, y4, shift_w, k, "Shift", shift_pressed);
    float x_z = start_x + shift_w + s;
    draw_key(x_z + 0*(k+s), y4, k, k, "Z", is_down('Z'));
    draw_key(x_z + 1*(k+s), y4, k, k, "X", is_down('X'));
    draw_key(x_z + 2*(k+s), y4, k, k, "C", is_down('C'));
    draw_key(x_z + 3*(k+s), y4, k, k, "V", is_down('V'));


    float y5 = y4 + k + s + row_gap;
    float ctrl_w = k * 1.5f;
    float alt_w = k * 1.5f;
    float space_w = k * 4.5f;

    bool ctrl_pressed = (is_down(VK_LCONTROL) || is_down(VK_RCONTROL) || is_down(VK_CONTROL));
    bool alt_pressed = (is_down(VK_LMENU) || is_down(VK_RMENU) || is_down(VK_MENU));

    draw_key(start_x, y5, ctrl_w, k, "Ctrl", ctrl_pressed);
    draw_key(start_x + ctrl_w + s, y5, alt_w, k, "Alt", alt_pressed);
    draw_key(start_x + ctrl_w + s + alt_w + s, y5, space_w, k, "Space", is_down(VK_SPACE));


    float mouse_area_x = start_x + (k+s)*6 + 30.0f;
    float mouse_area_y = start_y + 10.0f;
    float m_width = 85.0f;
    float m_height = 140.0f;

    ImVec2 m_pos = ImVec2(kb_pos.x + mouse_area_x, kb_pos.y + mouse_area_y);


    dl->AddRectFilled(m_pos, ImVec2(m_pos.x + m_width, m_pos.y + m_height), IM_COL32(30, 30, 30, 255), 20.0f);
    dl->AddRect(m_pos, ImVec2(m_pos.x + m_width, m_pos.y + m_height), IM_COL32(80, 80, 80, 255), 20.0f, 0, 2.0f);


    bool lmb = (GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0;
    bool rmb = (GetAsyncKeyState(VK_RBUTTON) & 0x8000) != 0;
    bool mmb = (GetAsyncKeyState(VK_MBUTTON) & 0x8000) != 0;

    float btn_h = m_height * 0.35f;
    float gap = 4.0f;


    ImVec2 l_min = m_pos;
    ImVec2 l_max = ImVec2(m_pos.x + m_width/2 - gap/2, m_pos.y + btn_h);
    ImU32 l_col = lmb ? IM_COL32(200, 200, 200, 255) : IM_COL32(50, 50, 50, 255);
    dl->AddRectFilled(l_min, l_max, l_col, 20.0f, ImDrawFlags_RoundCornersTopLeft);
    dl->AddRect(l_min, l_max, IM_COL32(120, 120, 120, 255), 20.0f, ImDrawFlags_RoundCornersTopLeft, 1.5f);


    ImVec2 r_min = ImVec2(m_pos.x + m_width/2 + gap/2, m_pos.y);
    ImVec2 r_max = ImVec2(m_pos.x + m_width, m_pos.y + btn_h);
    ImU32 r_col = rmb ? IM_COL32(200, 200, 200, 255) : IM_COL32(50, 50, 50, 255);
    dl->AddRectFilled(r_min, r_max, r_col, 20.0f, ImDrawFlags_RoundCornersTopRight);
    dl->AddRect(r_min, r_max, IM_COL32(120, 120, 120, 255), 20.0f, ImDrawFlags_RoundCornersTopRight, 1.5f);


    float sw_w = 14.0f;
    float sw_h = 30.0f;
    ImVec2 sw_pos = ImVec2(m_pos.x + m_width/2 - sw_w/2, m_pos.y + 15.0f);
    ImU32 sw_col = mmb ? IM_COL32(220, 220, 220, 255) : IM_COL32(20, 20, 20, 255);
    dl->AddRectFilled(sw_pos, ImVec2(sw_pos.x + sw_w, sw_pos.y + sw_h), sw_col, 5.0f);
    dl->AddRect(sw_pos, ImVec2(sw_pos.x + sw_w, sw_pos.y + sw_h), IM_COL32(100, 100, 100, 255), 5.0f, 0, 1.5f);


    if (io.MouseWheel != 0.0f) {
        ImU32 scroll_col = IM_COL32(0, 255, 0, 255);
        if (io.MouseWheel > 0) {
             dl->AddTriangleFilled(ImVec2(sw_pos.x + sw_w/2, sw_pos.y + 4),
                                   ImVec2(sw_pos.x + 3, sw_pos.y + 10),
                                   ImVec2(sw_pos.x + sw_w - 3, sw_pos.y + 10), scroll_col);
        } else {
             dl->AddTriangleFilled(ImVec2(sw_pos.x + sw_w/2, sw_pos.y + sw_h - 4),
                                   ImVec2(sw_pos.x + 3, sw_pos.y + sw_h - 10),
                                   ImVec2(sw_pos.x + sw_w - 3, sw_pos.y + sw_h - 10), scroll_col);
        }
    }


    bool x1b = (GetAsyncKeyState(VK_XBUTTON1) & 0x8000) != 0;
    bool x2b = (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) != 0;

    float side_w = 6.0f;
    float side_h = 24.0f;
    float side_gap = 6.0f;

    ImVec2 sb1_pos = ImVec2(m_pos.x - side_w/2, m_pos.y + m_height * 0.5f);
    ImVec2 sb2_pos = ImVec2(m_pos.x - side_w/2, m_pos.y + m_height * 0.5f + side_h + side_gap);

    dl->AddRectFilled(sb1_pos, ImVec2(sb1_pos.x + side_w, sb1_pos.y + side_h), x2b ? IM_COL32(200, 200, 200, 255) : IM_COL32(40, 40, 40, 255), 2.0f);
    dl->AddRect(sb1_pos, ImVec2(sb1_pos.x + side_w, sb1_pos.y + side_h), IM_COL32(120, 120, 120, 255), 2.0f);

    dl->AddRectFilled(sb2_pos, ImVec2(sb2_pos.x + side_w, sb2_pos.y + side_h), x1b ? IM_COL32(200, 200, 200, 255) : IM_COL32(40, 40, 40, 255), 2.0f);
    dl->AddRect(sb2_pos, ImVec2(sb2_pos.x + side_w, sb2_pos.y + side_h), IM_COL32(120, 120, 120, 255), 2.0f);
}

static bool s_bNextExplosionIsGoal = false;
static bool s_bNextExplosionIsDemo = false;

void GameEventHookModule::OnBallExplode(PreEvent& event)
{
    if (RemoveGoalExplosion)
    {
        s_bNextExplosionIsGoal = true;
        event.SetDetour(false);
    }
}

void GameEventHookModule::OnCarFinishDemo(PreEvent& event)
{
    if (RemoveDemoSmoke)
        s_bNextExplosionIsDemo = true;
}

void GameEventHookModule::OnExplosionPostBeginPlay(PreEvent& event)
{
    if (!RemoveDemoSmoke && !RemoveGoalExplosion) return;

    AExplosion_X* explosion = static_cast<AExplosion_X*>(event.Caller());
    if (!explosion) return;

    bool suppress = false;

    if (s_bNextExplosionIsGoal && RemoveGoalExplosion)
    {
        suppress = true;
        s_bNextExplosionIsGoal = false;
    }
    else if (s_bNextExplosionIsDemo && RemoveDemoSmoke)
    {
        suppress = true;
        s_bNextExplosionIsDemo = false;
    }
    else
    {
        float absY = std::abs(explosion->Location.Y);
        if (absY >= 5000.0f && RemoveGoalExplosion)
            suppress = true;
        else if (absY < 5000.0f && RemoveDemoSmoke)
            suppress = true;
    }

    if (suppress)
    {
        explosion->bHidden = true;
        explosion->MuteExplosionOnSpawn = true;
        explosion->InternalMuteExplosion();
        event.SetDetour(false);
    }
}

void GameEventHookModule::RemoveVisualEffects()
{
}


namespace
{
    void KingModPumpWorkshopLoad();
}

void GameEventHookModule::OnRender()
{
    try
    {
        if (!IsInitialized) return;

                                                                               
                                                                             
                                                                             
                                                                              
                                                                     
        if (!EventsComponent::TryEnterRenderGameplayRead())
            return;

        struct RenderGameplayReadGuard
        {
            ~RenderGameplayReadGuard() { EventsComponent::LeaveRenderGameplayRead(); }
        } renderGameplayReadGuard;

        DrawToggleStatusIndicator();

        menu_avatar::Update();

                                                                             
                                                                                
                                                                                
        DrawMatchmakingShieldOverlay();

                                                                               
                                                                               
                                                                         
        UpdateWorkshopBrowse();
        KingModPumpWorkshopLoad();

        if (!IsInGame || !CurrentGameEvent) return;


        TArray<APlayerController_TA*> localPlayers = getLocalPlayers(CurrentGameEvent);
        bool isSplitscreen = localPlayers.size() > 1;


        if (isSplitscreen || localPlayers.empty()) {
            return;
        }

        KingFeatures::RenderOverlay();
        HostSync::Tick();

        UpdateBallInfo();

        RemoveVisualEffects();


        if (Hitboxes) {
            DrawCarHitboxes();
        }

                            

        if (BoostPadTimers) {
            DrawBoostTimers();
        }


        {
            extern void Visuals_DrawAll();
            Visuals_DrawAll();
        }


        GameEventHook.DrawBallSpeedDisplay();

        {
            static double lastCameraApply = 0.0;
            double now = getCurrentTimeSeconds();
            if (now - lastCameraApply > 0.1) {
                Events.ApplyCameraSettings();
                lastCameraApply = now;
            }
        }


        DrawControllerOverlay();
        DrawKeyboardOverlay();

        DrawPlayerMMR();


        DrawMinimap();

        if (FlipIndicatorEnabled) {
            DrawFlipIndicator();
        }

                                                                             
                                                                            
                                                                              
        ApplyFreeplayTweaks();
        ApplyPovInReplay();

        DrawEnemyResetIndicators();

    }
    catch (...) { Console.Error("GameEventHook: Unbekannte Exception in OnRender"); }
}

void GameEventHookModule::Initialize()
{
    try
    {
        HookGameEvents();
        HookAdditionalFunctions();
        IsInitialized = true;
        AutoLeaveTriggered = false;
        AutoQueueTriggered = false;

    }
    catch (...) { Console.Error("GameEventHook: Unknown exception in Initialize"); }
}

class GameEventHookModule GameEventHook {};

void GameEventHookModule::DrawToggleStatusIndicator() {
    if (!ToggleStatusIndicatorEnabled) {
        return;
    }

    ImGuiIO& io = ImGui::GetIO();
    ImDrawList* draw_list = ImGui::GetForegroundDrawList();


    if (ToggleStatusIndicatorPos.x == 0 && ToggleStatusIndicatorPos.y == 0) {
        ToggleStatusIndicatorPos = ImVec2(io.DisplaySize.x - 100, 100);
    }


    const float radius = 20.0f;
    const ImU32 activeColor = IM_COL32(0, 255, 0, 255);
    const ImU32 inactiveColor = IM_COL32(255, 0, 0, 255);
    const ImU32 borderColor = IM_COL32(255, 255, 255, 255);


    ImU32 circleColor = GameEventHook.IsInGame ? activeColor : inactiveColor;


    draw_list->AddCircleFilled(ToggleStatusIndicatorPos, radius, circleColor);
    draw_list->AddCircle(ToggleStatusIndicatorPos, radius, borderColor, 0, 2.0f);


    ImVec2 mousePos = io.MousePos;
    float distance = sqrtf((mousePos.x - ToggleStatusIndicatorPos.x) * (mousePos.x - ToggleStatusIndicatorPos.x) +
                          (mousePos.y - ToggleStatusIndicatorPos.y) * (mousePos.y - ToggleStatusIndicatorPos.y));

    if (io.MouseClicked[0] && distance <= radius) {
        ToggleStatusIndicatorDragging = true;
        ToggleStatusIndicatorDragOffset = ImVec2(mousePos.x - ToggleStatusIndicatorPos.x, mousePos.y - ToggleStatusIndicatorPos.y);
    }

    if (ToggleStatusIndicatorDragging) {
        if (io.MouseDown[0]) {
            ToggleStatusIndicatorPos = ImVec2(mousePos.x - ToggleStatusIndicatorDragOffset.x, mousePos.y - ToggleStatusIndicatorDragOffset.y);
        } else {
            ToggleStatusIndicatorDragging = false;
            SaveConfig();
        }
    }


    float newX = ToggleStatusIndicatorPos.x;
    float newY = ToggleStatusIndicatorPos.y;

    if (newX < radius) newX = radius;
    if (newX > io.DisplaySize.x - radius) newX = io.DisplaySize.x - radius;
    if (newY < radius) newY = radius;
    if (newY > io.DisplaySize.y - radius) newY = io.DisplaySize.y - radius;

    ToggleStatusIndicatorPos.x = newX;
    ToggleStatusIndicatorPos.y = newY;
}

void GameEventHookModule::SendDiscordWebhook(const std::string& content, const std::string& title, const std::string& description, int color) {
    if (!DiscordWebhookEnabled || strlen(DiscordWebhookURL) == 0) {
        return;
    }

    CURL* curl = curl_easy_init();
    if (!curl) {
        Console.Error("[Discord] Failed to initialize CURL");
        return;
    }


    json payload;
    if (!title.empty()) {

        payload["embeds"] = json::array();
        json embed;
        embed["title"] = title;
        embed["description"] = description;
        embed["color"] = color;


        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        struct tm timeinfo;
        gmtime_s(&timeinfo, &time_t);
        ss << std::put_time(&timeinfo, "%Y-%m-%dT%H:%M:%S.000Z");
        embed["timestamp"] = ss.str();

        payload["embeds"].push_back(embed);
    } else {

        payload["content"] = content;
    }

    std::string jsonPayload = payload.dump();

    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl_easy_setopt(curl, CURLOPT_URL, DiscordWebhookURL);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonPayload.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);

    CURLcode res = curl_easy_perform(curl);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        Console.Error(std::string("[Discord] Webhook failed: ") + curl_easy_strerror(res));
    } else {
    }
}

void GameEventHookModule::LogMatchStart() {
    if (MatchStartedLogged) {
        return;
    }


    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    struct tm timeinfo;
    localtime_s(&timeinfo, &time_t);
    ss << std::put_time(&timeinfo, "%Y-%m-%d %H:%M:%S");
    CurrentMatchStartTime = ss.str();


    CurrentMatchMap = "No fucking idea";
    CurrentMatchPlaylist = "still no fucking idea";


    if (CurrentGameEvent) {


        CurrentMatchPlaylist = "Current Game";
    }

    std::string title = "Match Started";
    std::string description = "**Map:** " + CurrentMatchMap + "\n";
    description += "**Playlist:** " + CurrentMatchPlaylist + "\n";
    description += "**Time:** " + CurrentMatchStartTime;

    SendDiscordWebhook("", title, description, 0x00ff00);
    MatchStartedLogged = true;
}

void GameEventHookModule::LogMatchEnd() {
    if (MatchEndedLogged) {
        return;
    }


    std::string playlist = CurrentMatchPlaylist;
    if (playlist == "Unknown Playlist" || playlist == "Current Game") {
        playlist = "";
        if (CurrentGameTickPacket.num_teams > 0) {
            playlist = "Competitive";
        }
    }


    int duration_sec = (int)CurrentGameTickPacket.game_info.seconds_elapsed;
    int min = duration_sec / 60;
    int sec = duration_sec % 60;
    std::string duration = std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
    std::string overtime = "";
    if (CurrentGameTickPacket.game_info.is_overtime) {
        overtime = "Yes";


    } else {
        overtime = "No";
    }


    std::string scoreBlock = "**Final Score:**\n";
    for (int i = 0; i < CurrentGameTickPacket.num_teams; i++) {
        std::string teamName = (i == 0) ? "Blue Team" : "Orange Team";
        scoreBlock += teamName + ": " + std::to_string(CurrentGameTickPacket.teams[i].score) + "\n";
    }


    std::vector<std::string> blue, orange;
    for (int i = 0; i < CurrentGameTickPacket.num_cars; i++) {
        const auto& car = CurrentGameTickPacket.game_cars[i];
        if (car.team == 0) blue.push_back(car.name);
        else if (car.team == 1) orange.push_back(car.name);
    }
    std::string blueBlock = "**Blue Team:**\n";
    for (const auto& n : blue) blueBlock += n + "\n";
    std::string orangeBlock = "**Orange Team:**\n";
    for (const auto& n : orange) orangeBlock += n + "\n";


    std::string rankBlock = "";
    if (!LastRankUpdateString.empty()) {
        rankBlock = "**Rank Update:**\n";
        rankBlock += LastRankUpdatePlaylist + ": " + LastRankUpdateOld + " â†’ " + LastRankUpdateNew + " (MMR: " + std::to_string(LastRankUpdateMMR) + ")\n";
        rankBlock += "Matches played: " + std::to_string(LastRankUpdateMatches) + " (Placement: " + std::to_string(LastRankUpdatePlacement) + ")\n";
    }


    std::string title = "Match Ended";
    std::string description;
    description += "**Playlist:** " + playlist + "\n";
    description += "**Duration:** " + duration + "\n";
    description += "**Overtime:** " + overtime + "\n\n";
    description += scoreBlock + "\n";
    description += orangeBlock + "\n";
    description += blueBlock + "\n";
    if (!rankBlock.empty()) description += "\n" + rankBlock;

    int color = 0xff0000;
    SendDiscordWebhook("", title, description, color);
    MatchEndedLogged = true;
}

std::string GameEventHookModule::GetCurrentRankInfo() {
    try {

        TArray<APlayerController_TA*> localPlayers = getLocalPlayers(CurrentGameEvent);
        if (localPlayers.empty() || !localPlayers[0]) {
            return "";
        }

        APRI_TA* pri = localPlayers[0]->PRI;
        if (!pri) {
            return "";
        }


        FUniqueNetId playerId = pri->UniqueId;



        std::string rankInfo = "";


        rankInfo = "Rank information not available in this version";

        return rankInfo;
    }
    catch (const std::exception& e) {
        Console.Error(std::string("[Discord] Error getting rank info: ") + e.what());
        return "";
    }
}

static UMaterialInterface* SEH_GetMaterial(UCarMeshComponent_TA* mesh, int idx) {
    __try {
        return mesh->GetMaterial(idx);
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return nullptr;
    }
}

static UMaterialInstanceConstant* SEH_CreateMIC(UCarMeshComponent_TA* mesh, int idx) {
    __try {
        return mesh->CreateAndSetMaterialInstanceConstant(idx);
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return nullptr;
    }
}

static bool SEH_CheckMICName(UMaterialInstanceConstant* mic, bool& isDefault) {
    isDefault = false;
    __try {
        volatile uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(reinterpret_cast<uintptr_t>(mic));
        (void)vtable;
        return true;
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

static bool SEH_ProbeMIC(UMaterialInstanceConstant* mic) {
    uintptr_t addr = reinterpret_cast<uintptr_t>(mic);
    if (addr < 0x10000 || (addr & 0x7) != 0)
        return false;
    __try {
        volatile uintptr_t vtable = *reinterpret_cast<volatile uintptr_t*>(addr);
        if (vtable < 0x10000) return false;
        volatile uintptr_t vt0 = *reinterpret_cast<volatile uintptr_t*>(vtable);
        (void)vt0;
    } __except(EXCEPTION_EXECUTE_HANDLER) { return false; }
    return true;
}

static void SEH_SetColorParam(UMaterialInstanceConstant* mic, const wchar_t* name, const FLinearColor& color) {
    if (!SEH_ProbeMIC(mic)) return;
    try { mic->SetLinearColorParameter(FName(name), color); } catch (...) {}
}

static int SEH_GetMaterialCount(UCarMeshComponent_TA* mesh) {
    __try {
        return (int)mesh->Materials.size();
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return 0;
    }
}

static bool SEH_GetBodyAssetIndices(UCarMeshComponent_TA* mesh, int& skinIdx, int& chassisIdx) {
    __try {
        if (!mesh->BodyAsset)
            return false;
        skinIdx = mesh->BodyAsset->SkinMaterialIndex;
        chassisIdx = mesh->BodyAsset->ChassisMaterialIndex;
        return true;
    } __except(EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

void GameEventHookModule::UpdateBodyColor() {
    try {
        const bool wantsTrimColor = Items.custompainttrim;

        auto containsInsensitive = [](const std::string& haystack, const std::string& needle) -> bool {
            if (haystack.empty() || needle.empty())
                return false;
            std::string h = haystack, n = needle;
            std::transform(h.begin(), h.end(), h.begin(), ::tolower);
            std::transform(n.begin(), n.end(), n.begin(), ::tolower);
            return h.find(n) != std::string::npos;
        };

        auto looksLikeBody = [&](UMaterialInterface* material) -> bool {
            if (!material)
                return false;
            std::string materialName;
            try { materialName = material->GetFullName(); } catch (...) { return false; }
            for (const char* excluded : { "glass", "window", "headlight", "brake", "light", "wheel", "tire", "engine", "interior", "boost", "topper", "antenna" })
            {
                if (containsInsensitive(materialName, excluded))
                    return false;
            }
            return true;
        };

        std::vector<UMaterialInstanceConstant*> bodyMics;
        std::unordered_set<UMaterialInstanceConstant*> uniqueMICs;

        auto addMicFromCarMesh = [&](UCarMeshComponent_TA* carMesh, int materialIndex) {
            if (!carMesh || materialIndex < 0)
                return;

            UMaterialInterface* material = SEH_GetMaterial(carMesh, materialIndex);
            if (!material)
                return;
            if (!looksLikeBody(material))
                return;

            UMaterialInstanceConstant* mic = nullptr;
            try {
                if (material->IsA(UMaterialInstanceConstant::StaticClass()))
                    mic = static_cast<UMaterialInstanceConstant*>(material);
            } catch (...) {}

            if (!mic)
                mic = SEH_CreateMIC(carMesh, materialIndex);

            if (!mic)
                return;

            bool isDefault = false;
            if (!SEH_CheckMICName(mic, isDefault))
                return;

            try {
                std::string fullName = mic->GetFullName();
                if (fullName.find("Default__") != std::string::npos)
                    return;
            } catch (...) { return; }

            if (uniqueMICs.insert(mic).second)
                bodyMics.push_back(mic);
        };

        auto collectMicsFromCarMesh = [&](UCarMeshComponent_TA* carMesh) {
            if (!carMesh)
                return;

            size_t beforeCount = bodyMics.size();
            int skinIdx = -1, chassisIdx = -1;
            if (SEH_GetBodyAssetIndices(carMesh, skinIdx, chassisIdx))
            {
                addMicFromCarMesh(carMesh, skinIdx);
                if (chassisIdx != skinIdx)
                    addMicFromCarMesh(carMesh, chassisIdx);
            }

            if (bodyMics.size() == beforeCount)
            {
                int numMats = SEH_GetMaterialCount(carMesh);
                if (numMats <= 0) numMats = 4;
                for (int i = 0; i < numMats; ++i)
                    addMicFromCarMesh(carMesh, i);
            }
        };

        auto collectActiveBodyMics = [&]() {
            try
            {
                APlayerController* localController = Instances.IAPlayerController();
                if (IsValidUObjectPtr(localController))
                {
                    APawn* pawn = localController->Pawn;
                    if (IsValidObjectOfClass(pawn, ACar_TA::StaticClass()))
                    {
                        ACar_TA* localCar = static_cast<ACar_TA*>(pawn);
                        if (IsValidUObjectPtr(localCar->CarMesh))
                            collectMicsFromCarMesh(localCar->CarMesh);
                    }
                }
            }
            catch (...) {}

            try
            {
                UGFxData_Garage_TA* garageData = Instances.GetInstanceOf<UGFxData_Garage_TA>();
                if (garageData && garageData->CarPreviewSet)
                {
                    for (int i = 0; i < (int)garageData->CarPreviewSet->CarPreviewActors.size(); ++i)
                    {
                        ACarPreviewActor_TA* previewActor = garageData->CarPreviewSet->CarPreviewActors[i];
                        if (IsValidUObjectPtr(previewActor) && IsValidUObjectPtr(previewActor->CarMesh))
                            collectMicsFromCarMesh(previewActor->CarMesh);
                    }
                }
            }
            catch (...) {}
        };

        const bool needTrimWork = wantsTrimColor || !Items.hasresetpainttrim;

        if (needTrimWork)
        {
            collectActiveBodyMics();
            Hooks::cachedBodyMICs = bodyMics;

            const FLinearColor trimDefault{ 0.07843f, 0.07843f, 0.07843f, 1.0f };
            FLinearColor trimColor = trimDefault;
            if (wantsTrimColor)
            {
                if (Items.custompainttrimrgb)
                {
                    LinearColor rainbow = GRainbowColor::GetLinear();
                    trimColor = { rainbow.R, rainbow.G, rainbow.B, 1.0f };
                }
                else
                    trimColor = { Items.customtrimcolors[0], Items.customtrimcolors[1], Items.customtrimcolors[2], 1.0f };
            }

            for (auto* MIC : bodyMics)
            {
                if (!MIC)
                    continue;
                SEH_SetColorParam(MIC, L"TrimColor", trimColor);
            }

            if (!wantsTrimColor)
                Items.hasresetpainttrim = true;
            else
                Items.hasresetpainttrim = false;
        }
        else
        {
            Hooks::cachedBodyMICs.clear();
        }
    }
    catch (const std::exception& e) {
        Console.Error(std::string("[GameEventHook] Exception in UpdateBodyColor: ") + e.what());
    }
    catch (...) {
        Console.Error("[GameEventHook] Unknown Exception in UpdateBodyColor");
    }
}

                                                               
                                                                       
                                                                      
                                                                         
                                                                       
                                          
                                                               

static UPointLightComponent* SEH_CreatePointLight() {
    __try {
        return Instances.CreateInstance<UPointLightComponent>();
    } __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

static bool SEH_FindAttachedLight(UCarMeshComponent_TA* mesh, UPointLightComponent*& outLight) {
    __try {
        auto& atts = mesh->Attachments;
        for (int32_t i = 0; i < (int32_t)atts.size(); ++i) {
            UActorComponent* comp = atts[i].Component;
            if (comp && comp->IsA(UPointLightComponent::StaticClass())) {
                outLight = static_cast<UPointLightComponent*>(comp);
                return true;
            }
        }
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
    return false;
}

static void SEH_InitializeUnderglowLight(UPointLightComponent* pl, const FColor& color) {
    __try {
        pl->CastShadows = 0;
        pl->CastStaticShadows = 0;
        pl->CastDynamicShadows = 0;
        pl->bAllowPreShadow = 0;
        pl->bCastCompositeShadow = 0;
        pl->LightingChannels.bInitialized = 1;
        pl->LightingChannels.BSP = 1;
        pl->LightingChannels.Static = 1;
        pl->LightingChannels.Dynamic = 1;
        pl->LightingChannels.CompositeDynamic = 1;
        pl->LightingChannels.Gameplay = 1;
        pl->Brightness = 10.0f;
        pl->Radius = 320.0f;
        pl->FalloffExponent = 5.0f;
        pl->LightColor.R = color.R;
        pl->LightColor.G = color.G;
        pl->LightColor.B = color.B;
        pl->LightColor.A = 255;
        pl->bEnabled = 1;
        pl->UpdateColorAndBrightness();
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

                                                                             
                                                                              
                                                                             
                               
static void SEH_UpdateUnderglowColorOnly(UPointLightComponent* pl, const FColor& color) {
    __try {
        if (pl->LightColor.R == color.R && pl->LightColor.G == color.G &&
            pl->LightColor.B == color.B && pl->bEnabled)
            return;
        pl->LightColor.R = color.R;
        pl->LightColor.G = color.G;
        pl->LightColor.B = color.B;
        pl->LightColor.A = 255;
        pl->bEnabled = 1;
        pl->UpdateColorAndBrightness();
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

                                                                        
                                                                         
static void SEH_AttachLightToSocket(UCarMeshComponent_TA* mesh, UPointLightComponent* pl, const FName* socket) {
    __try {
        mesh->AttachComponentToSocket(pl, *socket);
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

static void SEH_DisableLight(UPointLightComponent* pl) {
    __try {
        pl->bEnabled = 0;
        pl->Brightness = 0.0f;
        pl->UpdateColorAndBrightness();
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

                                                                            
                                                                                 
                                                                              
                                                                     
static std::vector<UCarMeshComponent_TA*> GetLocalCarMeshes() {
    std::vector<UCarMeshComponent_TA*> out;

                                                
    try {
        APlayerController* pc = Instances.IAPlayerController();
        if (IsValidUObjectPtr(pc)) {
            APawn* pawn = pc->Pawn;
            if (IsValidObjectOfClass(pawn, ACar_TA::StaticClass())) {
                ACar_TA* car = static_cast<ACar_TA*>(pawn);
                if (IsValidUObjectPtr(car->CarMesh))
                    out.push_back(car->CarMesh);
            }
        }
    } catch (...) {}

                                                                             
                                                                               
             
    if (!out.empty())
        return out;

                                           
    try {
        UGFxData_Garage_TA* garage = Instances.GetInstanceOf<UGFxData_Garage_TA>();
        if (garage && garage->CarPreviewSet) {
            for (int i = 0; i < (int)garage->CarPreviewSet->CarPreviewActors.size(); ++i) {
                ACarPreviewActor_TA* pa = garage->CarPreviewSet->CarPreviewActors[i];
                if (IsValidUObjectPtr(pa) && IsValidUObjectPtr(pa->CarMesh))
                    out.push_back(pa->CarMesh);
            }
        }
    } catch (...) {}

    return out;
}

void GameEventHookModule::UpdateUnderglowColor() {
    try {
                                                                            
                                                                         
        static const FName kChassisSocket(L"chassis_jnt");

                                                                              
        FColor targetColor;
        if (Items.customunderglowrgb) {
            LinearColor rainbow = GRainbowColor::GetLinear();
            targetColor = Color(rainbow.R, rainbow.G, rainbow.B, 1.0f).UnrealColor();
        } else {
            targetColor = Color(Items.customunderglowcolors[0],
                                Items.customunderglowcolors[1],
                                Items.customunderglowcolors[2],
                                1.0f).UnrealColor();
        }

                                                                       
        for (UCarMeshComponent_TA* CMC : GetLocalCarMeshes()) {
            if (!IsValidUObjectPtr(CMC))
                continue;

            UPointLightComponent* existing = nullptr;
            bool hasExisting = SEH_FindAttachedLight(CMC, existing);

            if (Items.customunderglow) {
                UPointLightComponent* pl = existing;
                if (!pl) {
                    pl = SEH_CreatePointLight();
                    if (!pl)
                        continue;
                    SEH_InitializeUnderglowLight(pl, targetColor);
                    SEH_AttachLightToSocket(CMC, pl, &kChassisSocket);
                } else {
                    SEH_UpdateUnderglowColorOnly(pl, targetColor);
                }
            } else if (hasExisting) {
                                                                                    
                                                                              
                SEH_DisableLight(existing);
            }
        }

        Items.hasresetunderglow = !Items.customunderglow;
    }
    catch (...) {
        Console.Error("[GameEventHook] Exception in UpdateUnderglowColor");
    }
}

                                                               
                                                                             
                                                                          
                                                                             
                                                                  
                                                               

                                                                             
                                                                   
static UTexture2DDynamic* GetOrLoadPlateTexture(const std::string& path) {
    static std::unordered_map<std::string, UTexture2DDynamic*> s_cache;
    if (path.empty())
        return nullptr;

    auto it = s_cache.find(path);
    if (it != s_cache.end() && IsValidUObjectPtr(it->second))
        return it->second;

    fs::path p(path);
    if (!fs::exists(p))
        return nullptr;

    UTexture2DDynamic* tex = BallTexturesModule::ImgPathToTexture(p, true);
    if (tex)
        s_cache[path] = tex;
    return tex;
}

                                                                              
                                                                              
                                                                      
struct PlateKey {
    UCarMeshComponent_TA* mesh;
    bool front;
    bool operator==(const PlateKey& o) const { return mesh == o.mesh && front == o.front; }
};
struct PlateKeyHash {
    size_t operator()(const PlateKey& k) const {
        return std::hash<void*>()(k.mesh) ^ (k.front ? 0x9e3779b9u : 0u);
    }
};
static std::unordered_map<PlateKey, UStaticMeshComponent*, PlateKeyHash> g_plateCache;

                                                                                
                                                
static UStaticMeshComponent* SEH_CreatePlate(UCarMeshComponent_TA* mesh, const FName* socket, UStaticMesh* plane) {
    __try {
        UStaticMeshComponent* smc = Instances.CreateInstance<UStaticMeshComponent>();
        if (!smc)
            return nullptr;
        if (plane)
            smc->SetStaticMesh(plane, false);
        mesh->AttachComponentToSocket(smc, *socket);
        return smc;
    } __except (EXCEPTION_EXECUTE_HANDLER) { return nullptr; }
}

                                                                              
                                                                               
                                                                               
                                                                               
static bool SEH_IsPlateAttached(UCarMeshComponent_TA* mesh, UStaticMeshComponent* smc, const FName* noBone) {
    __try {
                                                                                
                                                                              
                                                                       
        return mesh->IsComponentAttached(smc, *noBone) != 0;
    } __except (EXCEPTION_EXECUTE_HANDLER) { return false; }
}

                                                                            
                                                                         
static void SEH_ReattachPlate(UCarMeshComponent_TA* mesh, UStaticMeshComponent* smc, const FName* socket) {
    __try {
        mesh->AttachComponentToSocket(smc, *socket);
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

                                                                             
                                                                               
struct PlateParamNames {
    const FName* texParams[4];
    const FName* colorParams[2];
};
static void SEH_ConfigurePlate(UStaticMeshComponent* smc, UTexture2DDynamic* tex, const FLinearColor* bg,
    const FVector* offset, const FRotator* rot, float width, float height, const PlateParamNames* names,
    UMaterialInterface* emissiveParent) {
    __try {
        smc->HiddenGame = 0;

                                                                                  
        UMaterialInstanceConstant* mic = nullptr;
        if (smc->Materials.empty()) {
            mic = smc->ConditionalCreateMIC(0);
        } else if (auto* mat = smc->GetMaterial(0)) {
            if (mat->IsA(UMaterialInstanceConstant::StaticClass()))
                mic = static_cast<UMaterialInstanceConstant*>(mat);
        }
        if (mic) {
                                                                             
                                                                               
                                                                         
                                                                              
                                                                     
            if (emissiveParent)
                mic->SetParent(emissiveParent);

            if (tex) {
                                                                           
                                                                            
                for (int i = 0; i < 4; ++i)
                    mic->SetTextureParameterValue(*names->texParams[i], tex);
            }
            for (int i = 0; i < 2; ++i)
                mic->SetLinearColorParameter(*names->colorParams[i], *bg);
        }

                                                                           
                                                                            
                                      
        smc->SetTranslation(*offset);
        smc->SetRotation(*rot);
        smc->SetScale(1.0f);
        FVector scale3d{ width, width, height };
        smc->SetScale3D(scale3d);
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

static void SEH_HidePlate(UStaticMeshComponent* smc) {
    __try {
        smc->HiddenGame = 1;
    } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

void GameEventHookModule::UpdateLicensePlates() {
    try {
                                                                                 
                                                                       
        static const FName kChassisSocket(L"chassis_jnt");
                                                                                 
                                                                         
        static const FName kNoBone{};

                                                                              
                                                                              
                                                                           
                                                                                
        static const FName kTexTexture(L"Texture");
        static const FName kTexDiffuse(L"Diffuse");
        static const FName kTexParam(L"Param");
        static const FName kTexMain(L"MainTexture");
        static const FName kColColor(L"Color");
        static const FName kColEmissive(L"Emissive");
        static const PlateParamNames kParamNames{
            { &kTexTexture, &kTexDiffuse, &kTexParam, &kTexMain },
            { &kColColor, &kColEmissive }
        };

                                                                             
        static UMaterialInterface* emissiveParent = nullptr;
        if (!IsValidUObjectPtr(emissiveParent))
            emissiveParent = Instances.FindObject<UMaterialInterface>("EngineMaterials.EmissiveTexturedMaterial");

        UTexture2DDynamic* frontTex = Items.plateFrontEnabled ? GetOrLoadPlateTexture(Items.plateFrontImagePath) : nullptr;
        UTexture2DDynamic* rearTex  = Items.plateRearEnabled  ? GetOrLoadPlateTexture(Items.plateRearImagePath)  : nullptr;

        const FLinearColor frontBg{ Items.plateFrontBgColor[0], Items.plateFrontBgColor[1], Items.plateFrontBgColor[2], Items.plateFrontBgColor[3] };
        const FLinearColor rearBg{  Items.plateRearBgColor[0],  Items.plateRearBgColor[1],  Items.plateRearBgColor[2],  Items.plateRearBgColor[3] };

        const FVector frontOff{ Items.plateFrontOffset[0], Items.plateFrontOffset[1], Items.plateFrontOffset[2] };
        const FVector rearOff{  Items.plateRearOffset[0],  Items.plateRearOffset[1],  Items.plateRearOffset[2] };

                                                                                   
        UStaticMesh* plane = Instances.FindObject<UStaticMesh>("UI_Meshes.Plane");

                                                                
        for (auto it = g_plateCache.begin(); it != g_plateCache.end(); ) {
            if (!IsValidUObjectPtr(it->first.mesh) || !IsValidUObjectPtr(it->second))
                it = g_plateCache.erase(it);
            else
                ++it;
        }

        auto handlePlate = [&](UCarMeshComponent_TA* cmc, bool front, bool enabled,
                               UTexture2DDynamic* tex, const FLinearColor& bg,
                               const FVector& off, float roll, float pitch, float yaw,
                               float width, float height) {
            PlateKey key{ cmc, front };
            auto it = g_plateCache.find(key);
            UStaticMeshComponent* smc = (it != g_plateCache.end()) ? it->second : nullptr;

            if (enabled) {
                if (!smc) {
                    smc = SEH_CreatePlate(cmc, &kChassisSocket, plane);
                    if (!smc)
                        return;
                    g_plateCache[key] = smc;
                } else if (!SEH_IsPlateAttached(cmc, smc, &kNoBone)) {
                                                                            
                                                                                
                                                                         
                    SEH_ReattachPlate(cmc, smc, &kChassisSocket);
                }
                                                                  
                const float degToURot = 65536.0f / 360.0f;
                FRotator rot{};
                rot.Roll  = static_cast<int>(roll  * degToURot);
                rot.Pitch = static_cast<int>(pitch * degToURot);
                rot.Yaw   = static_cast<int>(yaw   * degToURot);
                                                                             
                                                                          
                                                                             
                                                                         
                if (!front)
                    rot.Yaw += 32768;                                               
                SEH_ConfigurePlate(smc, tex, &bg, &off, &rot, width, height, &kParamNames, emissiveParent);
            } else if (smc) {
                SEH_HidePlate(smc);
            }
        };

                                                                             
        for (UCarMeshComponent_TA* CMC : GetLocalCarMeshes()) {
            if (!IsValidUObjectPtr(CMC))
                continue;
            handlePlate(CMC, true,  Items.plateFrontEnabled, frontTex, frontBg, frontOff, Items.plateFrontRoll,
                        Items.plateFrontPitch, Items.plateFrontYaw, Items.plateFrontWidth, Items.plateFrontHeight);
            handlePlate(CMC, false, Items.plateRearEnabled,  rearTex,  rearBg,  rearOff,  Items.plateRearRoll,
                        Items.plateRearPitch, Items.plateRearYaw, Items.plateRearWidth, Items.plateRearHeight);
        }

        Items.plateFrontDirty = false;
        Items.plateRearDirty = false;
    }
    catch (...) {
        Console.Error("[GameEventHook] Exception in UpdateLicensePlates");
    }
}

static std::vector<std::string> LoadMaterialInstanceNames(const std::vector<std::string>& keywords) {
    std::vector<std::string> names;
    try {
        std::filesystem::path matsPath = std::filesystem::current_path() / "RLSDK" / "Objects" / "materials.json";
        std::ifstream matsFile(matsPath.string());
        if (matsFile.is_open()) {
            json matsJson;
            matsFile >> matsJson;
            const json* matsArray = nullptr;
            if (matsJson.is_array()) {
                matsArray = &matsJson;
            } else if (matsJson.contains("materials") && matsJson["materials"].is_array()) {
                matsArray = &matsJson["materials"];
            }
            if (matsArray) {
                for (const auto& entry : *matsArray) {
                    if (!entry.is_object()) continue;
                    if (!entry.contains("class") || !entry.contains("name")) continue;
                    std::string cls = entry["class"].get<std::string>();
                    if (cls != "MaterialInstanceConstant" && cls != "MaterialInstanceTimeVarying") continue;
                    std::string name = entry["name"].get<std::string>();
                    std::string lower = name;
                    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
                    for (const auto& keyword : keywords) {
                        if (lower.find(keyword) != std::string::npos) {
                            if (std::find(names.begin(), names.end(), name) == names.end()) {
                                names.push_back(name);
                            }
                            break;
                        }
                    }
                }
            }
        }
    } catch (...) {}
    return names;
}

void GameEventHookModule::LoadConfig() {

    if (ConfigFilePath.empty()) {
        ConfigFilePath = GetDefaultConfigPath();
    }
    std::ifstream in(ConfigFilePath);
    if (!in.is_open()) {
        return;
    }
    try {
        json j;
        in >> j;
        ToggleStatusIndicatorEnabled = j.value("toggle_indicator_enabled", ToggleStatusIndicatorEnabled);
        ToggleStatusIndicatorPos.x = j.value("toggle_indicator_pos_x", ToggleStatusIndicatorPos.x);
        ToggleStatusIndicatorPos.y = j.value("toggle_indicator_pos_y", ToggleStatusIndicatorPos.y);
        DiscordWebhookEnabled = j.value("discord_webhook_enabled", DiscordWebhookEnabled);
        std::string webhook = j.value("discord_webhook_url", std::string(DiscordWebhookURL));
        strncpy_s(DiscordWebhookURL, webhook.c_str(), sizeof(DiscordWebhookURL) - 1);
        DiscordWebhookURL[sizeof(DiscordWebhookURL)-1] = '\0';
        BoostPadTimers = j.value("boost_pad_timers", BoostPadTimers);
        Hitboxes = j.value("hitboxes", Hitboxes);
        ControllerOverlay = j.value("controller_overlay", ControllerOverlay);
        KeyboardOverlay = j.value("keyboard_overlay", KeyboardOverlay);

        ControllerOverlayPos.x = j.value("controller_overlay_pos_x", ControllerOverlayPos.x);
        ControllerOverlayPos.y = j.value("controller_overlay_pos_y", ControllerOverlayPos.y);
        KeyboardOverlayPos.x = j.value("keyboard_overlay_pos_x", KeyboardOverlayPos.x);
        KeyboardOverlayPos.y = j.value("keyboard_overlay_pos_y", KeyboardOverlayPos.y);
        ControllerOverlayAlpha = j.value("controller_overlay_alpha", ControllerOverlayAlpha);
        KeyboardOverlayAlpha = j.value("keyboard_overlay_alpha", KeyboardOverlayAlpha);
        TracersEnabled = j.value("tracers_enabled", TracersEnabled);
        UseTeamColorsForTracers = j.value("tracers_use_team_colors", UseTeamColorsForTracers);
        VelocityArrowsEnabled = j.value("velocity_arrows_enabled", VelocityArrowsEnabled);
        PlayerDistanceTextEnabled = j.value("player_distance_text_enabled", PlayerDistanceTextEnabled);
        OpponentBoostEnabled = j.value("opponent_boost_enabled", OpponentBoostEnabled);
        EnablePsyNetLogging = j.value("psynet_logging_enabled", EnablePsyNetLogging);
        EnableDropUnlockBypass = j.value("psynet_drop_unlock_bypass", EnableDropUnlockBypass);
        auto readColor = [&](const char* key, ImVec4& out){
            if (j.contains(key) && j[key].is_array() && j[key].size() == 4) {
                out.x = j[key][0]; out.y = j[key][1]; out.z = j[key][2]; out.w = j[key][3];
            }
        };
        readColor("tracers_color_rgba", TracersColor);
        readColor("vel_arrow_ball_color_rgba", VelocityArrowBallColor);
        readColor("vel_arrow_car_color_rgba", VelocityArrowCarColor);
        readColor("player_distance_text_color_rgba", PlayerDistanceTextColor);
        readColor("opponent_boost_color_rgba", OpponentBoostColor);
        readColor("hitbox_color_rgba", HitboxColor);


        SkipReplays = j.value("skip_replays", SkipReplays);
        RemoveDemoSmoke = j.value("remove_demo_smoke", RemoveDemoSmoke);
        RemoveGoalExplosion = j.value("remove_goal_explosion", RemoveGoalExplosion);
        Debug = j.value("debug", Debug);
        MenuToggleKey = j.value("menu_toggle_key", MenuToggleKey);

                                           
        readColor("ui_accent_color_rgba", UIAccentColor);
        readColor("ui_background_color_rgba", UIBackgroundColor);
        UIAccentRainbow          = j.value("ui_accent_rainbow", UIAccentRainbow);
        UIAccentRainbowSpeed     = j.value("ui_accent_rainbow_speed", UIAccentRainbowSpeed);
        UIBackgroundRainbow      = j.value("ui_background_rainbow", UIBackgroundRainbow);
        UIBackgroundRainbowSpeed = j.value("ui_background_rainbow_speed", UIBackgroundRainbowSpeed);
        UIBlurEnabled            = j.value("ui_blur_enabled", UIBlurEnabled);
                                                                              
        UITheme::ApplyFavoriteOnStartup();

        GameEventHookModule::AutoQueueEnabled = j.value("auto_queue_enabled", GameEventHookModule::AutoQueueEnabled);
        GameEventHookModule::AutoQueueDelaySeconds = j.value("auto_queue_delay_seconds", GameEventHookModule::AutoQueueDelaySeconds);
        GameEventHookModule::AutoLeaveEnabled = j.value("auto_leave_enabled", GameEventHookModule::AutoLeaveEnabled);
        GameEventHookModule::AutoLeaveDelaySeconds = j.value("auto_leave_delay_seconds", GameEventHookModule::AutoLeaveDelaySeconds);


        FlipIndicatorEnabled = j.value("flip_indicator_enabled", FlipIndicatorEnabled);
        readColor("flip_indicator_color_rgba", FlipIndicatorColor);
        FlipIndicatorSize = j.value("flip_indicator_size", FlipIndicatorSize);
        FlipIndicatorPos.x = j.value("flip_indicator_pos_x", FlipIndicatorPos.x);
        FlipIndicatorPos.y = j.value("flip_indicator_pos_y", FlipIndicatorPos.y);
        readColor("flip_available_color", FlipAvailableColor);
        readColor("flip_unavailable_color", FlipUnavailableColor);


        BallPredictionEnabled = j.value("ball_prediction_master_enabled", BallPredictionEnabled);
        ShowPlayerMMR = j.value("show_player_mmr", ShowPlayerMMR);
        auto& ballPredSettings = BallPrediction::GetSettings();
        ballPredSettings.bEnabled = j.value("ball_prediction_enabled", ballPredSettings.bEnabled);
        ballPredSettings.bShowLine = j.value("ball_prediction_show_line", ballPredSettings.bShowLine);
        ballPredSettings.fPredictionTime = j.value("ball_prediction_time", ballPredSettings.fPredictionTime);


        std::vector<float> colorData = j.value("ball_prediction_color_rgba", std::vector<float>{1.0f, 1.0f, 1.0f, 1.0f});
        if (colorData.size() >= 4) {
            ballPredSettings.cLineColor.R = colorData[0];
            ballPredSettings.cLineColor.G = colorData[1];
            ballPredSettings.cLineColor.B = colorData[2];
            ballPredSettings.cLineColor.A = colorData[3];
        }

        ballPredSettings.iMaxPoints = j.value("ball_prediction_max_points", ballPredSettings.iMaxPoints);
        ballPredSettings.bUseSpeedColor = j.value("ball_prediction_use_speed_color", ballPredSettings.bUseSpeedColor);
        ballPredSettings.fThickness = j.value("ball_prediction_thickness", ballPredSettings.fThickness);
        ballPredSettings.fOpacity = j.value("ball_prediction_opacity", ballPredSettings.fOpacity);
        ballPredSettings.bShowBallShape = j.value("ball_prediction_show_ball_shape", ballPredSettings.bShowBallShape);
        ballPredSettings.fBallShapeScale = j.value("ball_prediction_ball_shape_scale", ballPredSettings.fBallShapeScale);
        ballPredSettings.bPredictGoal = j.value("ball_prediction_predict_goal", ballPredSettings.bPredictGoal);

        std::vector<float> goalColorData = j.value("ball_prediction_goal_color_rgba", std::vector<float>{1.0f, 0.0f, 0.0f, 1.0f});
        if (goalColorData.size() >= 4) {
            ballPredSettings.cGoalColor.R = goalColorData[0];
            ballPredSettings.cGoalColor.G = goalColorData[1];
            ballPredSettings.cGoalColor.B = goalColorData[2];
            ballPredSettings.cGoalColor.A = goalColorData[3];
        }

                                                                               
                                  
        ballPredSettings.iDrawStyle = j.value("ball_prediction_draw_style", ballPredSettings.iDrawStyle);
        ballPredSettings.bRainbow = j.value("ball_prediction_rainbow", ballPredSettings.bRainbow);
        ballPredSettings.fRainbowSpeed = j.value("ball_prediction_rainbow_speed", ballPredSettings.fRainbowSpeed);
        ballPredSettings.iTickrate = j.value("ball_prediction_tickrate", ballPredSettings.iTickrate);
        ballPredSettings.bGoalCrosshair = j.value("ball_prediction_goal_crosshair", ballPredSettings.bGoalCrosshair);
        std::vector<float> ghColor = j.value("ball_prediction_goal_crosshair_color_rgba", std::vector<float>{1.0f, 1.0f, 0.0f, 1.0f});
        if (ghColor.size() >= 4) {
            ballPredSettings.cGoalCrosshairColor.R = ghColor[0];
            ballPredSettings.cGoalCrosshairColor.G = ghColor[1];
            ballPredSettings.cGoalCrosshairColor.B = ghColor[2];
            ballPredSettings.cGoalCrosshairColor.A = ghColor[3];
        }
        ballPredSettings.bShowLanding = j.value("ball_prediction_show_landing", ballPredSettings.bShowLanding);
        std::vector<float> landColor = j.value("ball_prediction_landing_color_rgba", std::vector<float>{0.1f, 0.8f, 1.0f, 1.0f});
        if (landColor.size() >= 4) {
            ballPredSettings.cLandingColor.R = landColor[0];
            ballPredSettings.cLandingColor.G = landColor[1];
            ballPredSettings.cLandingColor.B = landColor[2];
            ballPredSettings.cLandingColor.A = landColor[3];
        }
        ballPredSettings.bShowBounces = j.value("ball_prediction_show_bounces", ballPredSettings.bShowBounces);
        ballPredSettings.bShowGoalImpact = j.value("ball_prediction_show_goal_impact", ballPredSettings.bShowGoalImpact);
        ballPredSettings.bShowGoalTimer = j.value("ball_prediction_show_goal_timer", ballPredSettings.bShowGoalTimer);
        ballPredSettings.bPreHitEnabled = j.value("ball_prediction_prehit_enabled", ballPredSettings.bPreHitEnabled);
        ballPredSettings.iPreHitCarMode = std::clamp(j.value("ball_prediction_prehit_car_mode", ballPredSettings.iPreHitCarMode), 0, 3);
        ballPredSettings.iPreHitSelectedCarIndex = std::clamp(j.value("ball_prediction_prehit_selected_car", ballPredSettings.iPreHitSelectedCarIndex), 0, 23);
        ballPredSettings.fPreHitMaxCarDistance = std::clamp(j.value("ball_prediction_prehit_max_distance", ballPredSettings.fPreHitMaxCarDistance), 250.0f, 5000.0f);
        ballPredSettings.fPreHitLookAhead = std::clamp(j.value("ball_prediction_prehit_lookahead", ballPredSettings.fPreHitLookAhead), 0.15f, 2.0f);
        ballPredSettings.fPreHitHitboxPadding = std::clamp(j.value("ball_prediction_prehit_hitbox_padding", ballPredSettings.fPreHitHitboxPadding), 0.0f, 80.0f);

                                                                                
                                                                                
        BallPrediction::ApplyFavoriteOnStartup();

        ballPredSettings.fMaxReach = (float)ballPredSettings.iMaxPoints;
        if (ballPredSettings.fPredictionTime > 0.0f)
            ballPredSettings.fMaxReach = ballPredSettings.fPredictionTime;


        BallSpeedDisplayEnabled = j.value("ball_speed_display_enabled", BallSpeedDisplayEnabled);
        BallSpeedDisplayX = j.value("ball_speed_display_x", BallSpeedDisplayX);
        BallSpeedDisplayY = j.value("ball_speed_display_y", BallSpeedDisplayY);
        BallSpeedDisplaySize = j.value("ball_speed_display_size", BallSpeedDisplaySize);
        LastBallSpeed = j.value("ball_speed_last_kmh", LastBallSpeed);

        MinimapEnabled = j.value("minimap_enabled", MinimapEnabled);
        MinimapPos.x = j.value("minimap_pos_x", MinimapPos.x);
        MinimapPos.y = j.value("minimap_pos_y", MinimapPos.y);
        MinimapSize = j.value("minimap_size", MinimapSize);
        MinimapAlpha = j.value("minimap_alpha", MinimapAlpha);
        MinimapShowBall = j.value("minimap_show_ball", MinimapShowBall);
        MinimapShowBoosts = j.value("minimap_show_boosts", MinimapShowBoosts);
        MinimapShowPlayers = j.value("minimap_show_players", MinimapShowPlayers);
        MinimapTeamColors = j.value("minimap_team_colors", MinimapTeamColors);
        readColor("minimap_ball_color_rgba", MinimapBallColor);
        readColor("minimap_boost_color_rgba", MinimapBoostColor);
        readColor("minimap_player_color_rgba", MinimapPlayerColor);
        readColor("minimap_my_team_color_rgba", MinimapMyTeamColor);
        readColor("minimap_opponent_color_rgba", MinimapOpponentColor);
        MinimapShowGoals = j.value("minimap_show_goals", MinimapShowGoals);
        MinimapShowDirection = j.value("minimap_show_direction", MinimapShowDirection);

        CustomAvatarModule::IsEnabled = j.value("custom_avatar_enabled", CustomAvatarModule::IsEnabled);
        CustomAvatarModule::ApplyToAllPlayers = false;
        std::string savedAvatar = j.value("custom_avatar_selected", "");
        if (!savedAvatar.empty() && !CustomAvatarModule::AvailableFiles.empty()) {
            for (int i = 0; i < static_cast<int>(CustomAvatarModule::AvailableFiles.size()); ++i) {
                if (CustomAvatarModule::AvailableFiles[i].filename().string() == savedAvatar) {
                    CustomAvatarModule::SelectedFileIndex = i;
                    break;
                }
            }
        }
        
        BallTexturesModule::SelectedSkinName = j.value("ball_textures_selected", "");
        BallTexturesModule::IsEnabled = j.value("ball_textures_enabled", BallTexturesModule::IsEnabled);
        CustomBoostMeterModule::SelectedSkinName = j.value("boost_meter_selected", "");
        CustomBoostMeterModule::IsEnabled = j.value("boost_meter_enabled", CustomBoostMeterModule::IsEnabled);

        CustomBorderModule::IsEnabled = false;                                            
        CustomBorderModule::ApplyToAdverts = j.value("custom_border_adverts", CustomBorderModule::ApplyToAdverts);
        CustomBorderModule::ApplyToTerrain = j.value("custom_border_terrain", CustomBorderModule::ApplyToTerrain);
        CustomBorderModule::ApplyToSkyCurves = j.value("custom_border_sky", CustomBorderModule::ApplyToSkyCurves);
        CustomBorderModule::SelectFileByName(j.value("custom_border_selected", std::string("")));

        (void)0;

        HitboxMode = j.value("hitbox_mode", HitboxMode);
                            
        if (j.contains("favorites") && j["favorites"].is_array()) {
            FavoritePartyIds.clear();
            for (auto& it : j["favorites"]) {
                try {
                    int plat = 0;
                    std::string id = "";
                    std::string title = "";
                    if (it.contains("platform")) {
                        if (it["platform"].is_number_integer()) plat = it["platform"].get<int>();
                        else if (it["platform"].is_string()) {
                            std::string p = it["platform"].get<std::string>();
                            plat = (p == "Steam") ? 1 : 0;
                        }
                    }
                    if (it.contains("id")) id = it["id"].get<std::string>();
                    if (it.contains("title")) title = it["title"].get<std::string>();
                    if (!id.empty()) FavoritePartyIds.push_back({plat, id, title});
                } catch (...) {}
            }
        }
        LastSelectedTab = std::clamp(j.value("last_selected_tab", LastSelectedTab), 0, 25);

        Events.enableCameraSettings = j.value("camera_settings_enabled", Events.enableCameraSettings);
        Events.cameraDistance = j.value("camera_distance", Events.cameraDistance);
        Events.cameraHeight = j.value("camera_height", Events.cameraHeight);
        Events.cameraAngle = j.value("camera_angle", Events.cameraAngle);
        Events.cameraStiffness = j.value("camera_stiffness", Events.cameraStiffness);
        Events.cameraSwivelSpeed = j.value("camera_swivel_speed", Events.cameraSwivelSpeed);
        Events.cameraTransitionSpeed = j.value("camera_transition_speed", Events.cameraTransitionSpeed);
        Events.setcustomtitle = j.value("custom_title_enabled", Events.setcustomtitle);
        Events.titletext = j.value("custom_title_text", Events.titletext);
        Events.titlecolor = j.value("custom_title_color", Events.titlecolor);
        Events.titleglowcolor = j.value("custom_title_glow_color", Events.titleglowcolor);
        Events.timeDilation = j.value("world_time_dilation", Events.timeDilation);
        Events.worldGravityZ = j.value("world_gravity_z", Events.worldGravityZ);

        Events.wheelWidth = j.value("wheel_width", Events.wheelWidth);
        Events.wheelHeight = j.value("wheel_height", Events.wheelHeight);
                                                                               
                                                                              
        {
            float legacyY = j.value("wheel_offset_y", 0.0f);
            float legacyZ = j.value("wheel_offset_z", 0.0f);
            float legacyRoll = j.value("wheel_roll", 0.0f);
            Events.wheelOffsetY[0] = j.value("wheel_offset_y_front", legacyY);
            Events.wheelOffsetY[1] = j.value("wheel_offset_y_rear", legacyY);
            Events.wheelOffsetZ[0] = j.value("wheel_offset_z_front", legacyZ);
            Events.wheelOffsetZ[1] = j.value("wheel_offset_z_rear", legacyZ);
            Events.wheelRoll[0] = j.value("wheel_roll_front", legacyRoll);
            Events.wheelRoll[1] = j.value("wheel_roll_rear", legacyRoll);
        }
        Events.wheelOffsetActive = j.value("wheel_offset_active", Events.wheelOffsetActive);

                          
        Items.plateFrontEnabled = j.value("plate_front_enabled", Items.plateFrontEnabled);
        Items.plateRearEnabled  = j.value("plate_rear_enabled",  Items.plateRearEnabled);
        {
            std::string fp = j.value("plate_front_image", std::string(Items.plateFrontImagePath));
            std::string rp = j.value("plate_rear_image",  std::string(Items.plateRearImagePath));
            strncpy_s(Items.plateFrontImagePath, sizeof(Items.plateFrontImagePath), fp.c_str(), _TRUNCATE);
            strncpy_s(Items.plateRearImagePath,  sizeof(Items.plateRearImagePath),  rp.c_str(), _TRUNCATE);
        }
        auto loadArr = [&](const char* key, float* dst, int n) {
            if (j.contains(key) && j[key].is_array() && (int)j[key].size() >= n) {
                for (int i = 0; i < n; ++i) dst[i] = j[key][i].get<float>();
            }
        };
        loadArr("plate_front_bg",     Items.plateFrontBgColor, 4);
        loadArr("plate_rear_bg",      Items.plateRearBgColor,  4);
        loadArr("plate_front_offset", Items.plateFrontOffset,  3);
        loadArr("plate_rear_offset",  Items.plateRearOffset,   3);
        Items.plateFrontRoll   = j.value("plate_front_roll",   Items.plateFrontRoll);
        Items.plateRearRoll    = j.value("plate_rear_roll",    Items.plateRearRoll);
        Items.plateFrontPitch  = j.value("plate_front_pitch",  Items.plateFrontPitch);
        Items.plateRearPitch   = j.value("plate_rear_pitch",   Items.plateRearPitch);
        Items.plateFrontYaw    = j.value("plate_front_yaw",    Items.plateFrontYaw);
        Items.plateRearYaw     = j.value("plate_rear_yaw",     Items.plateRearYaw);
        Items.plateFrontWidth  = j.value("plate_front_width",  Items.plateFrontWidth);
        Items.plateFrontHeight = j.value("plate_front_height", Items.plateFrontHeight);
        Items.plateRearWidth   = j.value("plate_rear_width",   Items.plateRearWidth);
        Items.plateRearHeight  = j.value("plate_rear_height",  Items.plateRearHeight);
                                                                  
        Items.plateFrontDirty = true;
        Items.plateRearDirty = true;

        if (j.contains("recent") && j["recent"].is_array()) {
            RecentPartyIds.clear();
            for (auto& it : j["recent"]) {
                try {
                    int plat = 0;
                    std::string id = "";
                    if (it.contains("platform")) {
                        if (it["platform"].is_number_integer()) plat = it["platform"].get<int>();
                        else if (it["platform"].is_string()) {
                            std::string p = it["platform"].get<std::string>();
                            plat = (p == "Steam") ? 1 : 0;
                        }
                    }
                    if (it.contains("id")) id = it["id"].get<std::string>();
                    if (!id.empty()) RecentPartyIds.emplace_back(plat, id);
                } catch (...) {}
            }
        }

                                                                             
        UsernameChangerEnabled  = j.value("username_changer_enabled", j.value("username_spoof_enabled", UsernameChangerEnabled));
        UsernameInvisible       = j.value("username_invisible", UsernameInvisible);
        {
            std::string changedName = j.value("username_changer_text", j.value("username_spoof_text", std::string(UsernameChangeText)));
            strncpy_s(UsernameChangeText, sizeof(UsernameChangeText), changedName.c_str(), _TRUNCATE);
        }

        EnemyResetIndicatorEnabled = j.value("enemy_reset_indicator", EnemyResetIndicatorEnabled);
        BallSpeedUnit            = j.value("ball_speed_unit", BallSpeedUnit);
                                                                             
                                                                               
                                  
        BoostSoundDefaultOverride = false;
        AlphaBoostSoundEnabled    = false;
        ScoredMessageEnabled      = j.value("scored_message", ScoredMessageEnabled);
        ScoredMessageShowSpeed    = j.value("scored_message_speed", ScoredMessageShowSpeed);
                                                                      
        WorkshopSource            = 1;
        UnlimitedJumpsEnabled    = j.value("unlimited_jumps", UnlimitedJumpsEnabled);
        ShowPlatformOnScoreboard = j.value("platform_on_scoreboard", ShowPlatformOnScoreboard);
        PovInReplay              = j.value("pov_in_replay", PovInReplay);

        {
            std::string mapPath = j.value("workshop_map_path", std::string(WorkshopMapPath));
            strncpy_s(WorkshopMapPath, sizeof(WorkshopMapPath), mapPath.c_str(), _TRUNCATE);
        }
        MatchmakingShield::SetEnabled(j.value("mm_shield_enabled", false));
        {
            std::string key = j.value("mm_shield_key", std::string("F8"));
            if (key.empty()) key = "F8";
            strncpy_s(MatchmakingShieldKeyName, sizeof(MatchmakingShieldKeyName), key.c_str(), _TRUNCATE);
            MatchmakingShield::SetJoinKey(GameEventHookModule::KeyNameToVk(key));
        }
        {
            const bool autoAccept = j.value("mm_shield_auto_accept", false);
            const float autoDelay = j.value("mm_shield_auto_delay", 1.5f);
            MatchmakingShield::SetAutoAccept(autoAccept, autoDelay);
            MatchmakingShield::SetHoldTimeout(j.value("mm_shield_hold_timeout", 45.0f));
        }

                                                                                
                                                                                
                                               
        ModPresets::ApplyFavoritesOnStartup();
    } catch (...) {}
}

void GameEventHookModule::SaveConfig() {

    if (ConfigFilePath.empty()) {
        ConfigFilePath = GetDefaultConfigPath();
    }

    std::string dir = ConfigFilePath.substr(0, ConfigFilePath.find_last_of("\\/"));
    SHCreateDirectoryExA(NULL, dir.c_str(), NULL);
    json j;
    j["toggle_indicator_enabled"] = ToggleStatusIndicatorEnabled;
    j["toggle_indicator_pos_x"] = ToggleStatusIndicatorPos.x;
    j["toggle_indicator_pos_y"] = ToggleStatusIndicatorPos.y;
    j["discord_webhook_enabled"] = DiscordWebhookEnabled;
    j["discord_webhook_url"] = std::string(DiscordWebhookURL);
    j["boost_pad_timers"] = BoostPadTimers;
    j["hitboxes"] = Hitboxes;
    j["controller_overlay"] = ControllerOverlay;
    j["keyboard_overlay"] = KeyboardOverlay;

    j["controller_overlay_pos_x"] = ControllerOverlayPos.x;
    j["controller_overlay_pos_y"] = ControllerOverlayPos.y;
    j["keyboard_overlay_pos_x"] = KeyboardOverlayPos.x;
    j["keyboard_overlay_pos_y"] = KeyboardOverlayPos.y;
    j["controller_overlay_alpha"] = ControllerOverlayAlpha;
    j["keyboard_overlay_alpha"] = KeyboardOverlayAlpha;
    j["tracers_enabled"] = TracersEnabled;
    j["tracers_use_team_colors"] = UseTeamColorsForTracers;
    j["velocity_arrows_enabled"] = VelocityArrowsEnabled;
    j["player_distance_text_enabled"] = PlayerDistanceTextEnabled;
    j["opponent_boost_enabled"] = OpponentBoostEnabled;
    j["psynet_logging_enabled"] = EnablePsyNetLogging;
    j["psynet_drop_unlock_bypass"] = EnableDropUnlockBypass;
    j["tracers_color_rgba"] = { TracersColor.x, TracersColor.y, TracersColor.z, TracersColor.w };
    j["vel_arrow_ball_color_rgba"] = { VelocityArrowBallColor.x, VelocityArrowBallColor.y, VelocityArrowBallColor.z, VelocityArrowBallColor.w };
    j["vel_arrow_car_color_rgba"] = { VelocityArrowCarColor.x, VelocityArrowCarColor.y, VelocityArrowCarColor.z, VelocityArrowCarColor.w };
    j["player_distance_text_color_rgba"] = { PlayerDistanceTextColor.x, PlayerDistanceTextColor.y, PlayerDistanceTextColor.z, PlayerDistanceTextColor.w };
            j["opponent_boost_color_rgba"] = { OpponentBoostColor.x, OpponentBoostColor.y, OpponentBoostColor.z, OpponentBoostColor.w };
        j["hitbox_color_rgba"] = { HitboxColor.x, HitboxColor.y, HitboxColor.z, HitboxColor.w };
    j["skip_replays"] = SkipReplays;
    j["remove_demo_smoke"] = RemoveDemoSmoke;
    j["remove_goal_explosion"] = RemoveGoalExplosion;
    j["debug"] = Debug;
    j["auto_queue_enabled"] = GameEventHookModule::AutoQueueEnabled;
    j["auto_queue_delay_seconds"] = GameEventHookModule::AutoQueueDelaySeconds;
    j["auto_leave_enabled"] = GameEventHookModule::AutoLeaveEnabled;
    j["auto_leave_delay_seconds"] = GameEventHookModule::AutoLeaveDelaySeconds;
    j["menu_toggle_key"] = GameEventHookModule::MenuToggleKey;

                                       
    j["ui_accent_color_rgba"]        = { UIAccentColor.x, UIAccentColor.y, UIAccentColor.z, UIAccentColor.w };
    j["ui_background_color_rgba"]    = { UIBackgroundColor.x, UIBackgroundColor.y, UIBackgroundColor.z, UIBackgroundColor.w };
    j["ui_accent_rainbow"]           = UIAccentRainbow;
    j["ui_accent_rainbow_speed"]     = UIAccentRainbowSpeed;
    j["ui_background_rainbow"]       = UIBackgroundRainbow;
    j["ui_background_rainbow_speed"] = UIBackgroundRainbowSpeed;
    j["ui_blur_enabled"]             = UIBlurEnabled;


    j["flip_indicator_enabled"] = FlipIndicatorEnabled;
    j["flip_indicator_color_rgba"] = { FlipIndicatorColor.x, FlipIndicatorColor.y, FlipIndicatorColor.z, FlipIndicatorColor.w };
    j["flip_indicator_size"] = FlipIndicatorSize;
    j["flip_indicator_pos_x"] = FlipIndicatorPos.x;
    j["flip_indicator_pos_y"] = FlipIndicatorPos.y;
    j["flip_available_color"] = { FlipAvailableColor.x, FlipAvailableColor.y, FlipAvailableColor.z, FlipAvailableColor.w };
    j["flip_unavailable_color"] = { FlipUnavailableColor.x, FlipUnavailableColor.y, FlipUnavailableColor.z, FlipUnavailableColor.w };


    j["ball_prediction_master_enabled"] = BallPredictionEnabled;
    j["show_player_mmr"] = ShowPlayerMMR;
    auto& ballPredSettings = BallPrediction::GetSettings();
    j["ball_prediction_enabled"] = ballPredSettings.bEnabled;
    j["ball_prediction_show_line"] = ballPredSettings.bShowLine;
    j["ball_prediction_time"] = ballPredSettings.fPredictionTime;
    j["ball_prediction_color_rgba"] = { ballPredSettings.cLineColor.R, ballPredSettings.cLineColor.G, ballPredSettings.cLineColor.B, ballPredSettings.cLineColor.A };
    j["ball_prediction_line_width"] = ballPredSettings.fThickness;
    j["ball_prediction_max_points"] = ballPredSettings.iMaxPoints;
    j["ball_prediction_use_speed_color"] = ballPredSettings.bUseSpeedColor;
    j["ball_prediction_thickness"] = ballPredSettings.fThickness;
    j["ball_prediction_opacity"] = ballPredSettings.fOpacity;
    j["ball_prediction_show_ball_shape"] = ballPredSettings.bShowBallShape;
    j["ball_prediction_ball_shape_scale"] = ballPredSettings.fBallShapeScale;
    j["ball_prediction_predict_goal"] = ballPredSettings.bPredictGoal;
    j["ball_prediction_goal_color_rgba"] = {
        ballPredSettings.cGoalColor.R,
        ballPredSettings.cGoalColor.G,
        ballPredSettings.cGoalColor.B,
        ballPredSettings.cGoalColor.A
    };

    j["ball_prediction_draw_style"] = ballPredSettings.iDrawStyle;
    j["ball_prediction_rainbow"] = ballPredSettings.bRainbow;
    j["ball_prediction_rainbow_speed"] = ballPredSettings.fRainbowSpeed;
    j["ball_prediction_tickrate"] = ballPredSettings.iTickrate;
    j["ball_prediction_goal_crosshair"] = ballPredSettings.bGoalCrosshair;
    j["ball_prediction_goal_crosshair_color_rgba"] = {
        ballPredSettings.cGoalCrosshairColor.R,
        ballPredSettings.cGoalCrosshairColor.G,
        ballPredSettings.cGoalCrosshairColor.B,
        ballPredSettings.cGoalCrosshairColor.A
    };
    j["ball_prediction_show_landing"] = ballPredSettings.bShowLanding;
    j["ball_prediction_landing_color_rgba"] = {
        ballPredSettings.cLandingColor.R,
        ballPredSettings.cLandingColor.G,
        ballPredSettings.cLandingColor.B,
        ballPredSettings.cLandingColor.A
    };
    j["ball_prediction_show_bounces"] = ballPredSettings.bShowBounces;
    j["ball_prediction_show_goal_impact"] = ballPredSettings.bShowGoalImpact;
    j["ball_prediction_show_goal_timer"] = ballPredSettings.bShowGoalTimer;
    j["ball_prediction_prehit_enabled"] = ballPredSettings.bPreHitEnabled;
    j["ball_prediction_prehit_car_mode"] = ballPredSettings.iPreHitCarMode;
    j["ball_prediction_prehit_selected_car"] = ballPredSettings.iPreHitSelectedCarIndex;
    j["ball_prediction_prehit_max_distance"] = ballPredSettings.fPreHitMaxCarDistance;
    j["ball_prediction_prehit_lookahead"] = ballPredSettings.fPreHitLookAhead;
    j["ball_prediction_prehit_hitbox_padding"] = ballPredSettings.fPreHitHitboxPadding;


    j["ball_speed_display_enabled"] = BallSpeedDisplayEnabled;
    j["ball_speed_display_x"] = BallSpeedDisplayX;
    j["ball_speed_display_y"] = BallSpeedDisplayY;
    j["ball_speed_display_size"] = BallSpeedDisplaySize;
    j["ball_speed_last_kmh"] = LastBallSpeed;


    j["minimap_enabled"] = MinimapEnabled;
    j["minimap_pos_x"] = MinimapPos.x;
    j["minimap_pos_y"] = MinimapPos.y;
    j["minimap_size"] = MinimapSize;
    j["minimap_alpha"] = MinimapAlpha;
    j["minimap_show_ball"] = MinimapShowBall;
    j["minimap_show_boosts"] = MinimapShowBoosts;
    j["minimap_show_players"] = MinimapShowPlayers;
    j["minimap_team_colors"] = MinimapTeamColors;
    j["minimap_ball_color_rgba"] = { MinimapBallColor.x, MinimapBallColor.y, MinimapBallColor.z, MinimapBallColor.w };
    j["minimap_boost_color_rgba"] = { MinimapBoostColor.x, MinimapBoostColor.y, MinimapBoostColor.z, MinimapBoostColor.w };
    j["minimap_player_color_rgba"] = { MinimapPlayerColor.x, MinimapPlayerColor.y, MinimapPlayerColor.z, MinimapPlayerColor.w };
    j["minimap_my_team_color_rgba"] = { MinimapMyTeamColor.x, MinimapMyTeamColor.y, MinimapMyTeamColor.z, MinimapMyTeamColor.w };
    j["minimap_opponent_color_rgba"] = { MinimapOpponentColor.x, MinimapOpponentColor.y, MinimapOpponentColor.z, MinimapOpponentColor.w };
    j["minimap_show_goals"] = MinimapShowGoals;
    j["minimap_show_direction"] = MinimapShowDirection;

    j["custom_avatar_enabled"] = CustomAvatarModule::IsEnabled;
    j["custom_avatar_apply_all"] = false;
    if (CustomAvatarModule::SelectedFileIndex >= 0 && CustomAvatarModule::SelectedFileIndex < static_cast<int>(CustomAvatarModule::AvailableFiles.size())) {
        j["custom_avatar_selected"] = CustomAvatarModule::AvailableFiles[CustomAvatarModule::SelectedFileIndex].filename().string();
    } else {
        j["custom_avatar_selected"] = "";
    }
    
    j["ball_textures_selected"] = BallTexturesModule::SelectedSkinName;
    j["ball_textures_enabled"] = BallTexturesModule::IsEnabled;
    j["boost_meter_selected"] = CustomBoostMeterModule::SelectedSkinName;
    j["boost_meter_enabled"] = CustomBoostMeterModule::IsEnabled;

    j["custom_border_enabled"] = CustomBorderModule::IsEnabled;
    j["custom_border_adverts"] = CustomBorderModule::ApplyToAdverts;
    j["custom_border_terrain"] = CustomBorderModule::ApplyToTerrain;
    j["custom_border_sky"] = CustomBorderModule::ApplyToSkyCurves;
    j["custom_border_selected"] = CustomBorderModule::SelectedFileName();

                                                                             
    j["username_changer_enabled"]   = UsernameChangerEnabled;
    j["username_invisible"]         = UsernameInvisible;
    j["username_changer_text"]      = std::string(UsernameChangeText);
    j["enemy_reset_indicator"]      = EnemyResetIndicatorEnabled;
    j["ball_speed_unit"]            = BallSpeedUnit;
    j["boost_sound_default"]        = BoostSoundDefaultOverride;
    j["alpha_boost_sound"]          = AlphaBoostSoundEnabled;
    j["scored_message_speed"]       = ScoredMessageShowSpeed;
    j["workshop_source"]            = WorkshopSource;
    j["unlimited_jumps"]            = UnlimitedJumpsEnabled;
    j["scored_message"]             = ScoredMessageEnabled;
    j["platform_on_scoreboard"]     = ShowPlatformOnScoreboard;
    j["pov_in_replay"]              = PovInReplay;
    j["workshop_map_path"]          = std::string(WorkshopMapPath);
    j["mm_shield_enabled"]          = MatchmakingShield::IsEnabled();
    j["mm_shield_key"]              = std::string(MatchmakingShieldKeyName);
    j["mm_shield_auto_accept"]      = MatchmakingShield::IsAutoAcceptEnabled();
    j["mm_shield_auto_delay"]       = MatchmakingShield::GetAutoAcceptDelay();
    j["mm_shield_hold_timeout"]     = MatchmakingShield::GetHoldTimeout();

    (void)0;

    j["hitbox_mode"] = HitboxMode;
    {
        nlohmann::json fav = nlohmann::json::array();
        for (auto& e : FavoritePartyIds) {
            nlohmann::json o;
            o["platform"] = e.platform;
            o["id"] = e.id;
            o["title"] = e.title;
            fav.push_back(o);
        }
        j["favorites"] = fav;
        nlohmann::json rec = nlohmann::json::array();
        for (auto& p : RecentPartyIds) {
            nlohmann::json o;
            o["platform"] = p.first;
            o["id"] = p.second;
            rec.push_back(o);
        }
        j["recent"] = rec;
        j["last_selected_tab"] = LastSelectedTab;

        j["camera_settings_enabled"] = Events.enableCameraSettings;
        j["camera_distance"] = Events.cameraDistance;
        j["camera_height"] = Events.cameraHeight;
        j["camera_angle"] = Events.cameraAngle;
        j["camera_stiffness"] = Events.cameraStiffness;
        j["camera_swivel_speed"] = Events.cameraSwivelSpeed;
        j["camera_transition_speed"] = Events.cameraTransitionSpeed;
        j["custom_title_enabled"] = Events.setcustomtitle;
        j["custom_title_text"] = Events.titletext;
        j["custom_title_color"] = Events.titlecolor;
        j["custom_title_glow_color"] = Events.titleglowcolor;
        j["world_time_dilation"] = Events.timeDilation;
        j["world_gravity_z"] = Events.worldGravityZ;

        j["wheel_width"] = Events.wheelWidth;
        j["wheel_height"] = Events.wheelHeight;
        j["wheel_offset_y_front"] = Events.wheelOffsetY[0];
        j["wheel_offset_y_rear"] = Events.wheelOffsetY[1];
        j["wheel_offset_z_front"] = Events.wheelOffsetZ[0];
        j["wheel_offset_z_rear"] = Events.wheelOffsetZ[1];
        j["wheel_roll_front"] = Events.wheelRoll[0];
        j["wheel_roll_rear"] = Events.wheelRoll[1];
        j["wheel_offset_active"] = Events.wheelOffsetActive;

                                                                                
        j["plate_front_enabled"] = Items.plateFrontEnabled;
        j["plate_rear_enabled"]  = Items.plateRearEnabled;
        j["plate_front_image"]   = std::string(Items.plateFrontImagePath);
        j["plate_rear_image"]    = std::string(Items.plateRearImagePath);
        j["plate_front_bg"]      = { Items.plateFrontBgColor[0], Items.plateFrontBgColor[1], Items.plateFrontBgColor[2], Items.plateFrontBgColor[3] };
        j["plate_rear_bg"]       = { Items.plateRearBgColor[0],  Items.plateRearBgColor[1],  Items.plateRearBgColor[2],  Items.plateRearBgColor[3] };
        j["plate_front_offset"]  = { Items.plateFrontOffset[0], Items.plateFrontOffset[1], Items.plateFrontOffset[2] };
        j["plate_rear_offset"]   = { Items.plateRearOffset[0],  Items.plateRearOffset[1],  Items.plateRearOffset[2] };
        j["plate_front_roll"]    = Items.plateFrontRoll;
        j["plate_rear_roll"]     = Items.plateRearRoll;
        j["plate_front_pitch"]   = Items.plateFrontPitch;
        j["plate_rear_pitch"]    = Items.plateRearPitch;
        j["plate_front_yaw"]     = Items.plateFrontYaw;
        j["plate_rear_yaw"]      = Items.plateRearYaw;
        j["plate_front_width"]   = Items.plateFrontWidth;
        j["plate_front_height"]  = Items.plateFrontHeight;
        j["plate_rear_width"]    = Items.plateRearWidth;
        j["plate_rear_height"]   = Items.plateRearHeight;

                            
    }

    std::ofstream out(ConfigFilePath);
    out << j.dump(4);
}

static size_t CurlWriteToString(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

static bool IsHex32(const std::string& s, size_t pos) {
    if (pos + 32 > s.size()) return false;
    for (size_t i = 0; i < 32; ++i) {
        char c = s[pos + i];
        bool hex = (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
        if (!hex) return false;
    }
    return true;
}

bool GameEventHookModule::ResolveEpicIdViaWeb(const std::string& steam64, std::string& outEpicId) {
    outEpicId.clear();
    std::vector<std::string> candidates = {
        "https://epic-lookup.com/?q=%s",
        "https://epic-lookup.com/lookup?steam=%s",
        "https://epic-lookup.com/search/%s",
        "https://epic-lookup.com/resolve?steam=%s"
    };
    for (const auto& pattern : candidates) {
        char url[512]; memset(url, 0, sizeof(url));
        snprintf(url, sizeof(url), pattern.c_str(), steam64.c_str());
        std::string buffer;
        CURL* curl = curl_easy_init();
        if (!curl) continue;
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "KingMod/1.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
#ifdef CURLSSLOPT_NATIVE_CA
        curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, (long)CURLSSLOPT_NATIVE_CA);
#endif
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteToString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        CURLcode res = curl_easy_perform(curl);
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK || http_code != 200 || buffer.empty()) continue;
        for (size_t i = 0; i + 32 <= buffer.size(); ++i) {
            if (IsHex32(buffer, i)) {
                outEpicId = buffer.substr(i, 32);
                return true;
            }
        }
    }
    return false;
}

                                                                              
                           
  
                                                                             
                                                                        
                                                                           
                                                                               
                                                                              
                                                                            
                                                                        
                                                                           
                 
                                                                              

                                                                              
bool GameEventHookModule::UsernameChangerEnabled = false;
bool GameEventHookModule::UsernameInvisible      = false;
char GameEventHookModule::UsernameChangeText[64] = "";

                                                                              
bool GameEventHookModule::EnemyResetIndicatorEnabled        = false;

                                                                              
int  GameEventHookModule::BallSpeedUnit = 0;                           

                                                                              
bool GameEventHookModule::BoostSoundDefaultOverride = false;
bool        GameEventHookModule::AlphaBoostSoundEnabled = false;
std::string GameEventHookModule::AlphaBoostSoundStatus;
std::string GameEventHookModule::UsernameChangeStatus;
bool GameEventHookModule::ScoredMessageShowSpeed = true;
std::string GameEventHookModule::ScoredMessageStatus;
int  GameEventHookModule::WorkshopSource  = 1;
int  GameEventHookModule::WorkshopBpMaxId = 0;

                                                                              
bool GameEventHookModule::UnlimitedJumpsEnabled = false;
bool GameEventHookModule::ScoredMessageEnabled  = false;

                                                                             
char GameEventHookModule::WorkshopMapPath[512] = "";
std::vector<std::string> GameEventHookModule::WorkshopMapList;
std::vector<GameEventHookModule::WorkshopItem> GameEventHookModule::WorkshopBrowse;
bool        GameEventHookModule::WorkshopBrowseLoading = false;
std::string GameEventHookModule::WorkshopBrowseError;
int         GameEventHookModule::WorkshopBrowsePage = 1;
int         GameEventHookModule::WorkshopBrowseSort = 0;
char        GameEventHookModule::WorkshopBrowseSearch[128] = "";
std::vector<GameEventHookModule::WorkshopInstalledEntry> GameEventHookModule::WorkshopInstalled;
std::string GameEventHookModule::WorkshopInstalledStatus;
std::string GameEventHookModule::WorkshopLoadStatus;

                                                                             
bool GameEventHookModule::ShowPlatformOnScoreboard = false;
bool GameEventHookModule::PovInReplay              = false;

                                                                             
                                                                               
char GameEventHookModule::MatchmakingShieldKeyName[32] = "F8";

                                                                              
                                         
                                                                              
namespace
{
                                                                             
                                                                          
                                        
    int KingModKeyNameToVk(const std::string& name)
    {
        if (name.empty()) return 0;

        if (name.size() == 1)
        {
            const char c = name[0];
            if (c >= 'A' && c <= 'Z') return c;
            if (c >= 'a' && c <= 'z') return c - 'a' + 'A';
            if (c >= '0' && c <= '9') return c;
        }

        if (name.size() >= 2 && (name[0] == 'F' || name[0] == 'f'))
        {
            bool allDigits = true;
            for (size_t i = 1; i < name.size(); ++i)
            {
                if (!std::isdigit(static_cast<unsigned char>(name[i]))) { allDigits = false; break; }
            }
            if (allDigits)
            {
                const int n = std::atoi(name.c_str() + 1);
                if (n >= 1 && n <= 24) return VK_F1 + (n - 1);
            }
        }

        static const std::map<std::string, int> named = {
            { "Mouse1", VK_LBUTTON }, { "Mouse2", VK_RBUTTON }, { "Mouse3", VK_MBUTTON },
            { "Mouse4", VK_XBUTTON1 }, { "Mouse5", VK_XBUTTON2 },
            { "Insert", VK_INSERT }, { "Delete", VK_DELETE }, { "Home", VK_HOME },
            { "End", VK_END }, { "PageUp", VK_PRIOR }, { "PageDown", VK_NEXT },
            { "Tab", VK_TAB }, { "CapsLock", VK_CAPITAL }, { "Space", VK_SPACE },
            { "Enter", VK_RETURN }, { "Backspace", VK_BACK }, { "Escape", VK_ESCAPE },
            { "Shift", VK_SHIFT }, { "Ctrl", VK_CONTROL }, { "Alt", VK_MENU },
            { "Left", VK_LEFT }, { "Right", VK_RIGHT }, { "Up", VK_UP }, { "Down", VK_DOWN },
            { "Pause", VK_PAUSE }, { "PrintScreen", VK_SNAPSHOT },
            { "NumLock", VK_NUMLOCK }, { "ScrollLock", VK_SCROLL },
            { "Numpad0", VK_NUMPAD0 }, { "Numpad1", VK_NUMPAD1 }, { "Numpad2", VK_NUMPAD2 },
            { "Numpad3", VK_NUMPAD3 }, { "Numpad4", VK_NUMPAD4 }, { "Numpad5", VK_NUMPAD5 },
            { "Numpad6", VK_NUMPAD6 }, { "Numpad7", VK_NUMPAD7 }, { "Numpad8", VK_NUMPAD8 },
            { "Numpad9", VK_NUMPAD9 }, { "Numpad+", VK_ADD }, { "Numpad-", VK_SUBTRACT },
            { "Numpad*", VK_MULTIPLY }, { "Numpad/", VK_DIVIDE }, { "Numpad.", VK_DECIMAL }
        };

        auto it = named.find(name);
        return (it != named.end()) ? it->second : 0;
    }

                                                              
    bool KingModKeyPressedOnce(int vk, bool& wasDown)
    {
        if (vk == 0) { wasDown = false; return false; }
        const bool down = (GetAsyncKeyState(vk) & 0x8000) != 0;
        const bool fired = down && !wasDown;
        wasDown = down;
        return fired;
    }

    ABall_TA* KingModGetLiveBall()
    {
        try
        {
            if (!GameEventHookModule::CurrentGameEvent) return nullptr;
            TArray<ABall_TA*> balls = GameEventHookModule::CurrentGameEvent->GameBalls;
            for (int i = 0; i < balls.size(); ++i)
            {
                if (balls[i]) return balls[i];
            }
        }
        catch (...) {}
        return nullptr;
    }

    std::string KingModGetCustomMapsDirectory()
    {
                                                
                                              
        char exePath[MAX_PATH] = {};
        std::string dir;
        if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
        {
                                                                                
            fs::path root = fs::path(exePath).parent_path().parent_path().parent_path();
            dir = (root / "TAGame" / "CookedPCConsole" / "mods").string();
        }
        else
        {
            dir = (fs::current_path() / "TAGame" / "CookedPCConsole" / "mods").string();
        }
        SHCreateDirectoryExA(NULL, dir.c_str(), NULL);
        return dir;
    }

                                                                               
                                                                            
                                                                              
                                                                                 
                                                  
    fs::path KingModGetCookedPackageDirectory()
    {
        char exePath[MAX_PATH] = {};
        std::error_code ec;
        if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
        {
                                                                                
            const fs::path root = fs::path(exePath).parent_path().parent_path().parent_path();
            const fs::path cooked = root / "TAGame" / "CookedPCConsole";
            if (fs::is_directory(cooked, ec) && !ec)
                return cooked;
        }
        const fs::path fallback = fs::current_path(ec) / "TAGame" / "CookedPCConsole";
        if (!ec && fs::is_directory(fallback, ec) && !ec)
            return fallback;
        return fs::path();
    }

    int KingModMapPackageScore(const fs::path& path);
    bool KingModPathIsInside(const fs::path& child, const fs::path& parent);
}

int GameEventHookModule::KeyNameToVk(const std::string& name) {
    return KingModKeyNameToVk(name);
}

                                                                              
                      
                                                                              
std::string GameEventHookModule::GetOperatingSystemName()
{
                                                                                
                                                                        
                                                                      
    static std::string cached;
    if (!cached.empty())
        return cached;

    typedef LONG(WINAPI* RtlGetVersionFn)(PRTL_OSVERSIONINFOW);
    OSVERSIONINFOEXW vi{};
    vi.dwOSVersionInfoSize = sizeof(vi);

    bool haveVersion = false;
    if (HMODULE ntdll = GetModuleHandleW(L"ntdll.dll"))
    {
        if (auto fn = reinterpret_cast<RtlGetVersionFn>(GetProcAddress(ntdll, "RtlGetVersion")))
            haveVersion = (fn(reinterpret_cast<PRTL_OSVERSIONINFOW>(&vi)) == 0);
    }

    if (!haveVersion)
    {
        cached = "Windows";
        return cached;
    }

                                                                              
                                                           
    std::string name = "Windows";
    if (vi.dwMajorVersion == 10)
        name = (vi.dwBuildNumber >= 22000) ? "Windows 11" : "Windows 10";
    else if (vi.dwMajorVersion == 6)
    {
        switch (vi.dwMinorVersion)
        {
        case 3:  name = "Windows 8.1";   break;
        case 2:  name = "Windows 8";     break;
        case 1:  name = "Windows 7";     break;
        default: name = "Windows Vista"; break;
        }
    }

                                                                       
    cached = name + " (build " + std::to_string(vi.dwBuildNumber) + ", x64)";
    return cached;
}

std::string GameEventHookModule::GetLocalPlatformName()
{
    try
    {
        if (ULocalPlayer* localPlayer = Instances.IULocalPlayer())
        {
            ULocalPlayer_X* lpx = static_cast<ULocalPlayer_X*>(localPlayer);
                                                                                 
                                                                                 
                                     
            if (lpx && lpx->OnlinePlayer)
                return platformToString(static_cast<int>(lpx->OnlinePlayer->PlayerID.Platform));
        }
    }
    catch (...) {}
    return "Unknown";
}

void GameEventHookModule::OpenKingModFolder()
{
                                                                                
                                                                       
    try
    {
        const std::string resources = GetKingModResourcesDirectory();
        const std::string root = fs::path(resources).parent_path().string();
        ShellExecuteA(NULL, "open", root.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    catch (...) {}
}

                                                                              
                   
  
                                                                               
                                                                             
                                                                               
                                                                           
                          
  
                                 
                                   
                                            
  
                                                                          
                                                                            
                                                        
                                                                              
namespace
{
    std::wstring KingModUtf8ToWide(const std::string& utf8)
    {
        if (utf8.empty())
            return {};

        const int required = MultiByteToWideChar(
            CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(),
            static_cast<int>(utf8.size()), nullptr, 0);
        if (required <= 0)
            return {};

        std::wstring result(static_cast<size_t>(required), L'\0');
        if (MultiByteToWideChar(
                CP_UTF8, MB_ERR_INVALID_CHARS, utf8.data(),
                static_cast<int>(utf8.size()), result.data(), required) != required)
        {
            return {};
        }
        return result;
    }

    ULocalPlayer_X* GetKingModLocalPlayerX()
    {
        ULocalPlayer* raw = nullptr;
        try { raw = Instances.IULocalPlayer(); }
        catch (...) { raw = nullptr; }

        if (!IsValidObjectOfClass(raw, ULocalPlayer_X::StaticClass()))
            return nullptr;
        return static_cast<ULocalPlayer_X*>(raw);
    }

    UOnlinePlayer_X* SEH_GetOnlinePlayer(ULocalPlayer_X* local)
    {
        __try
        {
            return local ? local->OnlinePlayer : nullptr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return nullptr;
        }
    }

    UGFxData_LocalPlayer_TA* SEH_GetShellLocalPlayerData(UGFxShell_TA* shell)
    {
                                                                                
                                                                                
        __try
        {
            return shell ? shell->LocalPlayerData : nullptr;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return nullptr;
        }
    }

    UGFxData_LocalPlayer_TA* GetKingModLocalPlayerData()
    {
                                                                              
                                                                               
        try
        {
            UGFxShell_TA* shell = Instances.GetInstanceOf<UGFxShell_TA>();
            if (IsValidObjectOfClass(shell, UGFxShell_TA::StaticClass()))
            {
                UGFxData_LocalPlayer_TA* data = SEH_GetShellLocalPlayerData(shell);
                if (IsValidObjectOfClass(data, UGFxData_LocalPlayer_TA::StaticClass()))
                    return data;
            }
        }
        catch (...) {}

        try
        {
            UGFxData_LocalPlayer_TA* data = Instances.GetInstanceOf<UGFxData_LocalPlayer_TA>();
            if (IsValidObjectOfClass(data, UGFxData_LocalPlayer_TA::StaticClass()))
                return data;
        }
        catch (...) {}
        return nullptr;
    }

    bool SEH_SetCentralLocalName(UOnlinePlayer_X* online, ULocalPlayer_X* local, const FString* requested)
    {
        __try
        {
            if (!online || !local || !requested)
                return false;
            online->SetPlayerName(*requested);
            local->HandleOnlineNameChanged(online);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    bool SEH_SetLocalPriName(APRI_TA* pri, const FString* requested)
    {
        __try
        {
            if (!pri || !requested)
                return false;
            pri->eventSetPlayerName(*requested);
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    void SEH_RefreshLocalHud(AGFxHUD_TA* hud, APRI_TA* pri)
    {
        __try
        {
            if (!hud || !pri)
                return;
            hud->HandlePlayerNameChanged(pri);
            hud->UpdateGFxPlayerRecord(pri);
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    bool SEH_RefreshLocalNameData(UGFxData_LocalPlayer_TA* data, UOnlinePlayer_X* online, const FString* requested)
    {
        __try
        {
            if (!data || !online || !requested)
                return false;

                                                                                
                                                                                 
                                                                                  
                                                                                   
                                                                                
                                                                         
            data->HandleOnlineNameChanged(online);
            data->UpdateName();
            return true;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

    void SEH_TriggerShellDataCallbacks(UGFxShell_TA* shell)
    {
        __try
        {
            if (shell)
                shell->TriggerDataCallbacks();
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {}
    }

    APRI_TA* GetKingModLocalPRI()
    {
        try
        {
            if (ULocalPlayer* local = Instances.IULocalPlayer())
            {
                if (IsValidUObjectPtr(local) && IsValidUObjectPtr(local->Actor))
                {
                    APlayerReplicationInfo* candidate = local->Actor->PlayerReplicationInfo;
                    if (IsValidObjectOfClass(candidate, APRI_TA::StaticClass()))
                        return static_cast<APRI_TA*>(candidate);
                }
            }
        }
        catch (...) {}

        try
        {
            APlayerController* controller = Instances.IAPlayerController();
            if (IsValidUObjectPtr(controller))
            {
                APlayerReplicationInfo* candidate = controller->PlayerReplicationInfo;
                if (IsValidObjectOfClass(candidate, APRI_TA::StaticClass()))
                    return static_cast<APRI_TA*>(candidate);
            }
        }
        catch (...) {}
        return nullptr;
    }

                                                                        
                                                                         
                                                                       
    bool SEH_CentralNameEquals(UOnlinePlayer_X* online, const wchar_t* expected)
    {
        __try
        {
            if (!online || !expected)
                return false;
            const FString& stored = online->PlayerName;
            if (stored.empty() || !stored.c_str())
                return false;
            return wcscmp(stored.c_str(), expected) == 0;
        }
        __except (EXCEPTION_EXECUTE_HANDLER)
        {
            return false;
        }
    }

                                                                              
                                                                        
                                                                     
                                                                        
                                                  

    HMODULE KingModSteamModule()
    {
        HMODULE mod = GetModuleHandleA("steam_api64.dll");
        if (!mod)
            mod = GetModuleHandleA("steam_api.dll");
        return mod;
    }

    using KingModSteamAccessor = void* (*)();
    using KingModSteamFlatGet = const char* (*)(void*);
    using KingModSteamFlatSet = unsigned long long (*)(void*, const char*);
    using KingModSteamVtGet = const char* (*)(void*);
    using KingModSteamVtSet = unsigned long long (*)(void*, const char*);

    void* KingModSteamFriends()
    {
        static void* cached = nullptr;
        if (cached)
            return cached;

        HMODULE steam = KingModSteamModule();
        if (!steam)
            return nullptr;

        static const char* const kAccessors[] = {
            "SteamAPI_SteamFriends_v018",
            "SteamAPI_SteamFriends_v017",
            "SteamAPI_SteamFriends_v016",
            "SteamAPI_SteamFriends_v015",
            "SteamAPI_SteamFriends_v014",
            "SteamAPI_SteamFriends_v013",
            "SteamAPI_SteamFriends_v012",
            "SteamAPI_SteamFriends_v011",
            "SteamAPI_SteamFriends_v010",
            "SteamAPI_SteamFriends_v009",
            "SteamAPI_SteamFriends_v008",
            "SteamAPI_SteamFriends_v007",
            "SteamAPI_SteamFriends",
        };

        for (const char* name : kAccessors)
        {
            auto accessor = reinterpret_cast<KingModSteamAccessor>(
                GetProcAddress(steam, name));
            if (!accessor)
                continue;
            if (void* itf = accessor())
            {
                cached = itf;
                break;
            }
        }
        return cached;
    }

    bool KingModSteamGetPersonaName(std::string& out)
    {
        void* self = KingModSteamFriends();
        if (!self)
            return false;

        const char* raw = nullptr;
        if (HMODULE steam = KingModSteamModule())
        {
            auto flat = reinterpret_cast<KingModSteamFlatGet>(
                GetProcAddress(steam, "SteamAPI_ISteamFriends_GetPersonaName"));
            if (flat)
                raw = flat(self);
        }
        if (!raw)
        {
            void** vtable = *reinterpret_cast<void***>(self);
            auto get = reinterpret_cast<KingModSteamVtGet>(vtable[0]);
            raw = get(self);
        }
        if (!raw)
            return false;
        out = raw;
        return true;
    }

    unsigned long long KingModSteamSetPersonaName(const std::string& name)
    {
        void* self = KingModSteamFriends();
        if (!self)
            return 0;

        if (HMODULE steam = KingModSteamModule())
        {
            auto flat = reinterpret_cast<KingModSteamFlatSet>(
                GetProcAddress(steam, "SteamAPI_ISteamFriends_SetPersonaName"));
            if (flat)
                return flat(self, name.c_str());
        }

        void** vtable = *reinterpret_cast<void***>(self);
        auto set = reinterpret_cast<KingModSteamVtSet>(vtable[1]);
        return set(self, name.c_str());
    }

    size_t KingModUtf8CharCount(const std::string& utf8)
    {
        size_t count = 0;
        for (unsigned char c : utf8)
            if ((c & 0xC0) != 0x80)
                ++count;
        return count;
    }

                                                                       
                                                                        
                                                 
    std::string g_steamOriginalName;
    bool g_steamOriginalCaptured = false;
    bool g_steamRenamed = false;
    unsigned long long g_steamPollToken = 0;

                                                                           
                                                                    
    void KingModPollSteamName(const std::string& target,
                              unsigned long long token,
                              bool restore,
                              int attemptsLeft)
    {
        if (token != g_steamPollToken)
            return;

        std::string current;
        const bool known = KingModSteamGetPersonaName(current);

        if (known && current == target)
        {
            if (restore)
            {
                g_steamRenamed = false;
                GameEventHookModule::UsernameChangeStatus =
                    "Steam name restored to \"" + target + "\"";
            }
            else
            {
                                                                             
                                                                               
                APRI_TA* pri = GetKingModLocalPRI();
                GameEventHookModule::SetLocalUsername(pri, target);
                GameEventHookModule::UsernameChangeStatus =
                    "Steam name is now \"" + target + "\" - everyone sees it";
            }
            return;
        }

        if (attemptsLeft <= 0)
        {
            GameEventHookModule::UsernameChangeStatus =
                known ? ("Steam rename not confirmed - Steam still has \"" + current + "\"")
                      : "Steam rename not confirmed (could not read Steam name)";
            return;
        }

        Main.Execute([target, token, restore, attemptsLeft]() {
            KingModPollSteamName(target, token, restore, attemptsLeft - 1);
        });
    }
}

void GameEventHookModule::SetLocalUsername(APRI_TA* pri, const std::string& name)
{
    if (EventsComponent::IsTrainingResetQuarantined())
    {
        UsernameChangeStatus = "Wait for training reset to finish";
        return;
    }

    if (name.empty())
    {
        UsernameChangeStatus = "Type a username first";
        return;
    }

    const std::wstring wideName = KingModUtf8ToWide(name);
    if (wideName.empty())
    {
        UsernameChangeStatus = "Username contains invalid UTF-8";
        return;
    }

    ULocalPlayer_X* local = GetKingModLocalPlayerX();
    if (!local)
    {
        UsernameChangeStatus = "Local player is not ready yet";
        return;
    }

    UOnlinePlayer_X* online = SEH_GetOnlinePlayer(local);
    if (!IsValidObjectOfClass(online, UOnlinePlayer_X::StaticClass()))
    {
        UsernameChangeStatus = "OnlinePlayer is not ready yet";
        return;
    }

    const FString requested(wideName.c_str());

                                                                    
                                                                             
                                                                                
                                                                   
    if (!SEH_SetCentralLocalName(online, local, &requested))
    {
        UsernameChangeStatus = "Local username change failed safely";
        return;
    }

                                                                             
                                                                          
    if (!SEH_CentralNameEquals(online, wideName.c_str()))
    {
        UsernameChangeStatus = "Engine kept old name - use Apply via Steam";
        return;
    }

                                                                           
                                                                              
                          
    if (IsValidObjectOfClass(pri, APRI_TA::StaticClass()))
    {
        SEH_SetLocalPriName(pri, &requested);

        try
        {
            AGFxHUD_TA* hud = Instances.GetInstanceOf<AGFxHUD_TA>();
            if (IsValidObjectOfClass(hud, AGFxHUD_TA::StaticClass()))
                SEH_RefreshLocalHud(hud, pri);
        }
        catch (...) {}
    }

                                                                                 
                                                                            
                                                                              
                                                                             
    if (UGFxData_LocalPlayer_TA* localData = GetKingModLocalPlayerData())
        SEH_RefreshLocalNameData(localData, online, &requested);

    try
    {
        UGFxShell_TA* shell = Instances.GetInstanceOf<UGFxShell_TA>();
        if (IsValidObjectOfClass(shell, UGFxShell_TA::StaticClass()))
            SEH_TriggerShellDataCallbacks(shell);
    }
    catch (...) {}

    UsernameChangeStatus = "Local username changed to \"" + name + "\"";
}

void GameEventHookModule::ApplyUsernameChange()
{
                                                                                
                                                                               
    static bool inFlight = false;
    if (inFlight)
        return;

    struct InFlightGuard
    {
        bool& Value;
        explicit InFlightGuard(bool& value) : Value(value) { Value = true; }
        ~InFlightGuard() { Value = false; }
    } guard(inFlight);

    ULocalPlayer_X* local = GetKingModLocalPlayerX();
    if (!local)
    {
        UsernameChangeStatus = "Local player is not ready yet";
        return;
    }

    UOnlinePlayer_X* online = SEH_GetOnlinePlayer(local);

    if (!IsValidObjectOfClass(online, UOnlinePlayer_X::StaticClass()))
    {
        UsernameChangeStatus = "OnlinePlayer is not ready yet";
        return;
    }

    static uintptr_t trackedOnlinePlayer = 0;
    static std::string originalName;
    const uintptr_t onlineKey = reinterpret_cast<uintptr_t>(online);

                                                                             
                                                                              
    if (trackedOnlinePlayer != onlineKey)
    {
        trackedOnlinePlayer = onlineKey;
        originalName.clear();

        try { originalName = online->PlayerName.ToString(); }
        catch (...) {}
        if (originalName.empty())
        {
            try { originalName = online->GetLocalName().ToString(); }
            catch (...) {}
        }
        if (originalName.empty())
        {
            try { originalName = online->GetOnlineName().ToString(); }
            catch (...) {}
        }
        if (originalName.empty())
        {
            try { originalName = local->eventGetNickname().ToString(); }
            catch (...) {}
        }
    }

    const bool active = UsernameChangerEnabled || UsernameInvisible;
    std::string desired;

    if (UsernameInvisible)
    {
                                                                               
                                                                          
        desired = "\xE3\x85\xA4\xE3\x85\xA4\xE3\x85\xA4";
    }
    else if (active)
    {
        desired = UsernameChangeText;
        if (desired.empty())
        {
            UsernameChangeStatus = "Type a username first";
            return;
        }
    }
    else
    {
        if (originalName.empty())
        {
            UsernameChangeStatus = "Original local name was not captured";
            return;
        }
        desired = originalName;
    }

    APRI_TA* pri = GetKingModLocalPRI();
    SetLocalUsername(pri, desired);

    if (!active && UsernameChangeStatus.rfind("Local username changed", 0) == 0)
        UsernameChangeStatus = "Restored local username to \"" + desired + "\"";

                                                                           
                                                                       
    if (!active && g_steamRenamed && !g_steamOriginalName.empty())
    {
        const std::string original = g_steamOriginalName;
        std::string current;
        if (KingModSteamGetPersonaName(current) && current != original)
        {
            const unsigned long long call = KingModSteamSetPersonaName(original);
            if (call != 0)
            {
                g_steamRenamed = false;
                const unsigned long long token = ++g_steamPollToken;
                UsernameChangeStatus = "Restoring Steam name to \"" + original + "\"...";
                Main.Execute([original, token]() {
                    KingModPollSteamName(original, token, true, 600);
                });
            }
            else
            {
                UsernameChangeStatus = "Steam rejected the restore request (rate limited?)";
            }
        }
        else
        {
            g_steamRenamed = false;
        }
    }
}

                                                                            
                                                                            
                                                                            
                                                                              
                                                                           
                                           
void GameEventHookModule::ApplySteamUsername()
{
    if (EventsComponent::IsTrainingResetQuarantined())
    {
        UsernameChangeStatus = "Wait for training reset to finish";
        return;
    }

    const std::string target = UsernameChangeText;
    if (target.empty())
    {
        UsernameChangeStatus = "Type a username first";
        return;
    }
    if (KingModUtf8ToWide(target).empty())
    {
        UsernameChangeStatus = "Username contains invalid UTF-8";
        return;
    }
    if (KingModUtf8CharCount(target) > 32)
    {
        UsernameChangeStatus = "Steam names are limited to 32 characters";
        return;
    }
    if (!KingModSteamFriends())
    {
        UsernameChangeStatus = "Steam API not found in game process";
        return;
    }

    std::string current;
    const bool haveCurrent = KingModSteamGetPersonaName(current);

                                                                            
                                                                         
    if (!g_steamOriginalCaptured)
    {
        g_steamOriginalCaptured = true;
        if (haveCurrent)
            g_steamOriginalName = current;
    }

    if (haveCurrent && current == target)
    {
        UsernameChangeStatus = "Steam name is already \"" + target + "\"";
        return;
    }

    const unsigned long long call = KingModSteamSetPersonaName(target);
    if (call == 0)
    {
        UsernameChangeStatus = "Steam rejected the rename request (rate limited?)";
        return;
    }

    g_steamRenamed = true;
    const unsigned long long token = ++g_steamPollToken;
    UsernameChangeStatus = "Steam rename submitted - confirming...";
    Main.Execute([target, token]() {
        KingModPollSteamName(target, token, false, 600);
    });
}

                                                                              
                        
  
                                                                              
                                        
                                                                              
void GameEventHookModule::DrawEnemyResetIndicators()
{
    if (!EnemyResetIndicatorEnabled || !IsInGame || !CurrentGameEvent)
    {
                                                                          
                                                        
        if (!IsInGame) { g_remoteFlipStates.clear(); g_enemyFlipVisualTimers.clear(); }
        return;
    }

    ImDrawList* dl = ImGui::GetBackgroundDrawList();
    if (!dl) return;

                                                                                
                                                                          
                                                                     
                                                
    ACar_TA* localCar = nullptr;
    bool weAreServer = false;
    try
    {
        PlayerControllerData pcData = GetPlayerControllerData();
        localCar = pcData.Car;
    }
    catch (...) {}
    try { weAreServer = Events.CanUseLocalServerFeatures(); } catch (...) {}

    TArray<ACar_TA*> cars;
    try { cars = CurrentGameEvent->Cars; }
    catch (...) { return; }

    for (int i = 0; i < cars.size(); ++i)
    {
        ACar_TA* car = cars[i];
        if (!car) continue;

                                                                               
                                                                             
        if (localCar && car == localCar) continue;

        try { if (!car->PRI) continue; }
        catch (...) { continue; }

        FVector loc;
        try { loc = car->Location; }
        catch (...) { continue; }
        loc.Z += 90.0f;

        FVector2D screen;
        float depth = 0.0f;
        if (!WorldToScreen(loc, screen, depth)) continue;

        bool hasReset = false;
        try { hasReset = HasFlipAvailable(car, weAreServer); }
        catch (...) { hasReset = false; }

                                                                           
                                                                             
        float flipTimeLeft = 0.0f;
        float flipMaxTime = kEnemyHardcodedFlipWindow;
        bool timerExpired = false;
        const bool hasCountdown = UpdateEnemyHardcodedFlipCountdown(
            car, weAreServer, hasReset, flipTimeLeft, flipMaxTime, timerExpired);
        const bool displayHasReset = hasReset && !timerExpired;

        const ImU32 col = ImGui::GetColorU32(displayHasReset ? FlipAvailableColor : FlipUnavailableColor);

        float radius = 900.0f / (depth > 1.0f ? depth : 1.0f);
        if (radius < 3.0f)  radius = 3.0f;
        if (radius > 14.0f) radius = 14.0f;

        dl->AddCircleFilled(ImVec2(screen.X, screen.Y), radius, col, 20);
        dl->AddCircle(ImVec2(screen.X, screen.Y), radius + 1.0f, IM_COL32(0, 0, 0, 190), 20, 1.5f);

                                                                                
                                                                   
        char flipLabel[32] = {};
        if (displayHasReset && hasCountdown)
            sprintf_s(flipLabel, "Flip %.1fs", flipTimeLeft);
        else
            sprintf_s(flipLabel, "%s", displayHasReset ? "Flip" : "No Flip");

        const float fontSize = (std::max)(11.0f, (std::min)(15.0f, radius + 4.0f));
        const ImVec2 labelSize = ImGui::GetFont()->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, flipLabel);
        const ImVec2 labelPos(screen.X - labelSize.x * 0.5f, screen.Y + radius + 4.0f);
        dl->AddText(ImGui::GetFont(), fontSize, ImVec2(labelPos.x + 1.0f, labelPos.y + 1.0f),
                    IM_COL32(0, 0, 0, 220), flipLabel);
        dl->AddText(ImGui::GetFont(), fontSize, labelPos, col, flipLabel);

        float progress = 0.0f;
        if (hasCountdown && flipMaxTime > 0.0f)
            progress = flipTimeLeft / flipMaxTime;
        else
            progress = displayHasReset ? 1.0f : 0.0f;
        progress = (std::max)(0.0f, (std::min)(progress, 1.0f));

        const float barW = (std::max)(38.0f, labelSize.x);
        const float barH = 3.0f;
        const ImVec2 b0(screen.X - barW * 0.5f, labelPos.y + labelSize.y + 2.0f);
        const ImVec2 b1(b0.x + barW, b0.y + barH);
        dl->AddRectFilled(b0, b1, IM_COL32(0, 0, 0, 190), 1.5f);
        if (progress > 0.0f)
            dl->AddRectFilled(b0, ImVec2(b0.x + barW * progress, b1.y), col, 1.5f);
    }
}

                                                                              
                       
  
                                                                              
                                                                               
                                                                              
                                                                                
                                                                       
                                                                              
void GameEventHookModule::ApplyBoostSound()
{
    try
    {
        USoundSettingsSave_TA* soundSave = nullptr;

                                                                              
                                                                         
        if (USoundSettingsManager_TA* manager = Instances.GetInstanceOf<USoundSettingsManager_TA>())
            soundSave = manager->SoundSave;
        if (!soundSave)
            soundSave = Instances.GetInstanceOf<USoundSettingsSave_TA>();
        if (!soundSave)
            return;

        const bool want = BoostSoundDefaultOverride;
        const bool current = soundSave->bOverrideBoostSoundToDefault != 0;
        if (current == want)
            return;

        soundSave->bOverrideBoostSoundToDefault = want ? 1 : 0;
        try { soundSave->__bOverrideBoostSoundToDefault__ChangeNotifyFunc(); }
        catch (...) {}
    }
    catch (...) {}
}

                                                                              
                                    
  
                                                                               
                                                                          
                                                                              
                                                                                 
                                                                                
                                                                               
                                                                              
namespace
{
    std::string KingModLowerAscii(const std::string& in)
    {
        std::string out = in;
        for (char& c : out)
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        return out;
    }

                                                                             
                                                                               
                                                                             
                                                                           
                                                                             
                                                                           
    UAkSoundCue* KingModFindAlphaBoostCue()
    {
        try
        {
            if (UProductDatabase_TA* productDatabase =
                    Instances.GetInstanceOf<UProductDatabase_TA>())
            {
                if (UProduct_TA* alphaProduct = productDatabase->GetProduct(32))
                {
                    if (UProductAsset_TA* asset = alphaProduct->LoadAsset())
                    {
                        if (asset->IsA<UProductAsset_Boost_TA>())
                        {
                            auto* alphaBoost =
                                static_cast<UProductAsset_Boost_TA*>(asset);
                            if (alphaBoost->FXActor)
                            {
                                if (alphaBoost->FXActor->OriginalBoostSound)
                                    return alphaBoost->FXActor->OriginalBoostSound;
                                if (alphaBoost->FXActor->DefaultBoostSound)
                                    return alphaBoost->FXActor->DefaultBoostSound;
                            }
                        }
                    }
                }
            }

            for (UAkSoundCue* cue : Instances.GetAllInstancesOf<UAkSoundCue>())
            {
                if (!cue) continue;
                std::string name;
                try { name = KingModLowerAscii(cue->GetFullName()); }
                catch (...) { continue; }
                if (name.find("alpha") == std::string::npos) continue;
                if (name.find("boost") == std::string::npos) continue;
                if (name.find("supersonic") != std::string::npos) continue;
                if (name.find("dryfire")    != std::string::npos) continue;
                return cue;
            }
        }
        catch (...) {}
        return nullptr;
    }

    struct KingModSavedBoostCues
    {
        UAkSoundCue* original = nullptr;
        UAkSoundCue* def      = nullptr;
    };
    std::map<AFXActor_Boost_TA*, KingModSavedBoostCues> g_SavedBoostCues;
    bool        g_AlphaBoostApplied  = false;
    UAkSoundCue* g_AlphaCue          = nullptr;
    double      g_AlphaCueLastSearch = 0.0;
}

void GameEventHookModule::ApplyAlphaBoostSound()
{
    try
    {
        std::vector<AFXActor_Boost_TA*> actors;
        try { actors = Instances.GetAllInstancesOf<AFXActor_Boost_TA>(); }
        catch (...) { return; }

        if (!AlphaBoostSoundEnabled)
        {
            if (!g_AlphaBoostApplied)
                return;

            for (AFXActor_Boost_TA* fx : actors)
            {
                if (!fx) continue;
                auto it = g_SavedBoostCues.find(fx);
                if (it == g_SavedBoostCues.end()) continue;
                try
                {
                    fx->OriginalBoostSound = it->second.original;
                    fx->DefaultBoostSound  = it->second.def;
                    fx->OnOverrideBoostSoundValueChanged();
                }
                catch (...) {}
            }
            g_SavedBoostCues.clear();
            g_AlphaBoostApplied = false;
            g_AlphaCue          = nullptr;
            AlphaBoostSoundStatus.clear();
            return;
        }

                                                                          
                                                                              
                                 
        const double now = getCurrentTimeSeconds();
        if (!g_AlphaCue && (now - g_AlphaCueLastSearch) > 2.0)
        {
            g_AlphaCueLastSearch = now;
            g_AlphaCue = KingModFindAlphaBoostCue();
        }

        if (actors.empty())
        {
            AlphaBoostSoundStatus = "Waiting for a car with a boost to spawn";
            return;
        }

        int patched = 0;
        for (AFXActor_Boost_TA* fx : actors)
        {
            if (!fx) continue;
            try
            {
                if (g_SavedBoostCues.find(fx) == g_SavedBoostCues.end())
                {
                    KingModSavedBoostCues saved;
                    saved.original = fx->OriginalBoostSound;
                    saved.def      = fx->DefaultBoostSound;
                    g_SavedBoostCues[fx] = saved;
                }

                                                                                
                                                                             
                                                                               
                                             
                UAkSoundCue* target = g_AlphaCue ? g_AlphaCue
                                                 : g_SavedBoostCues[fx].def;
                if (!target) continue;

                if (fx->OriginalBoostSound != target || fx->DefaultBoostSound != target)
                {
                    fx->OriginalBoostSound = target;
                    fx->DefaultBoostSound  = target;
                    fx->OnOverrideBoostSoundValueChanged();
                }
                ++patched;
            }
            catch (...) {}
        }

        g_AlphaBoostApplied = true;

        char buf[192];
        if (g_AlphaCue)
        {
            std::string cueName;
            try { cueName = g_AlphaCue->GetName(); } catch (...) { cueName = "alpha cue"; }
            snprintf(buf, sizeof(buf), "Alpha cue \"%s\" forced on %d boost%s",
                     cueName.c_str(), patched, patched == 1 ? "" : "s");
        }
        else
        {
            snprintf(buf, sizeof(buf),
                     "Stock (Alpha) boost cue forced on %d boost%s -- no alpha-named cue loaded",
                     patched, patched == 1 ? "" : "s");
        }
        AlphaBoostSoundStatus = buf;
    }
    catch (...) {}
}

                                                                              
                  
                                                                              
bool GameEventHookModule::IsInFreeplay()
{
                                                                             
                                                                                
                                                                             
                                                                
    try
    {
        if (CurrentGameEvent &&
            (CurrentGameEvent->IsPlayingFreeplay() ||
             CurrentGameEvent->IsPlayingOfflineFreeplay() ||
             CurrentGameEvent->IsPlayingOnlineFreeplay()))
            return true;

        if (Instances.GetInstanceOf<AGameEvent_Tutorial_FreePlay_TA>())
            return true;
    }
    catch (...) {}

    try
    {
        if (CurrentGameEvent)
        {
            if (CurrentGameEvent->IsA<AGameEvent_Tutorial_FreePlay_TA>())
                return true;
            if (UGameSettingPlaylist_X* playlist = CurrentGameEvent->GetPlaylist())
                return playlist->PlaylistId == 86;
        }
    }
    catch (...) {}

                                                                        
                                                                               
                                
    try
    {
        if (AGameEvent_TA* event = Instances.GetInstanceOf<AGameEvent_TA>())
            return event->IsPlayingFreeplay() ||
                   event->IsPlayingOfflineFreeplay() ||
                   event->IsPlayingOnlineFreeplay();
    }
    catch (...) {}

    return false;
}

static std::unordered_map<ACar_TA*, bool> g_OriginalUnlimitedJumps;

void GameEventHookModule::ApplyFreeplayTweaks()
{
    if (!Events.CanUseLocalServerFeatures())
    {
        for (auto& [car, orig] : g_OriginalUnlimitedJumps)
        {
            if (car && !car->bDeleteMe)
            {
                try { car->bUnlimitedJumps = orig ? 1 : 0; } catch (...) {}
            }
        }
        g_OriginalUnlimitedJumps.clear();
        return;
    }

    try
    {
        if (!CurrentGameEvent) return;
        TArray<APRI_TA*> allPRIs = CurrentGameEvent->PRIs;
        for (int i = 0; i < allPRIs.size(); ++i)
        {
            APRI_TA* pri = allPRIs[i];
            if (!pri) continue;
            ACar_TA* car = nullptr;
            try { car = pri->Car; } catch (...) { continue; }
            if (!car) continue;

            if (UnlimitedJumpsEnabled)
            {
                if (g_OriginalUnlimitedJumps.find(car) == g_OriginalUnlimitedJumps.end())
                    g_OriginalUnlimitedJumps[car] = car->bUnlimitedJumps != 0;
                try {
                    car->bUnlimitedJumps = 1;
                    car->bForceNetUpdate = true;
                } catch (...) {}
            }
            else
            {
                auto it = g_OriginalUnlimitedJumps.find(car);
                if (it != g_OriginalUnlimitedJumps.end())
                {
                    try {
                        car->bUnlimitedJumps = it->second ? 1 : 0;
                        car->bForceNetUpdate = true;
                    } catch (...) {}
                }
            }
        }

        if (!UnlimitedJumpsEnabled)
            g_OriginalUnlimitedJumps.clear();
    }
    catch (...) {}
}

                                                    
  
                                    
  
                                                                               
                                                                       
  
bool GameEventHookModule::SendLocalChatMessage(const std::string& message)
{
    if (message.empty())
    {
        ScoredMessageStatus = "Message is empty";
        return false;
    }

    try
    {
        AHUDBase_TA* hud = nullptr;
        if (APlayerController* localController = Instances.IAPlayerController())
        {
            if (IsValidUObjectPtr(localController) &&
                IsValidObjectOfClass(localController->myHUD, AHUDBase_TA::StaticClass()))
            {
                hud = static_cast<AHUDBase_TA*>(localController->myHUD);
            }
        }
        UGFxData_Chat_TA* chatData = hud ? hud->ChatData : nullptr;
        if (!chatData)
            chatData = Instances.GetInstanceOf<UGFxData_Chat_TA>();

        if (!IsValidObjectOfClass(chatData, UGFxData_Chat_TA::StaticClass()))
        {
            ScoredMessageStatus = "Local chat HUD is not ready";
            return false;
        }

                                                                                
                                                                      
        const std::wstring playerName = L"KingMod";
        const std::wstring messageText(message.begin(), message.end());
        const std::wstring emptyTimestamp;

        FGFxChatMessage chat{};
        chat.Team          = 0;
        chat.PlayerName    = FString(playerName.c_str());
        chat.Message       = FString(messageText.c_str());
        chat.ChatChannel   = EChatChannel::EChatChannel_Match;
        chat.bLocalPlayer  = 0;
        chat.bTransient    = 1;
        chat.SenderId      = FUniqueNetId{};
        chat.bPreset       = 0;
        chat.MessageType   = EChatMessageType::CMT_Default;
        chat.TimeStamp     = FString(emptyTimestamp.c_str());
                                                     
        chat.TeamColor.B   = 0;
        chat.TeamColor.G   = 0;
        chat.TeamColor.R   = 255;
        chat.TeamColor.A   = 255;

        chatData->AddTransientMessage(chat);
        ScoredMessageStatus = "Sent to local chat: " + message;
        return true;
    }
    catch (...)
    {
        ScoredMessageStatus = "Could not add the local chat message";
        return false;
    }
}

void GameEventHookModule::OnBallHitGoal(PreEvent& event)
{
    if (!ScoredMessageEnabled)
        return;

                                                                            
    static ULONGLONG lastMessageTick = 0;
    const ULONGLONG now = GetTickCount64();
    if (lastMessageTick != 0 && now - lastMessageTick < 500)
        return;

                                                                              
                                                                                
                                                                        
    ABall_TA* ball = static_cast<ABall_TA*>(event.Caller());
    if (!IsValidObjectOfClass(ball, ABall_TA::StaticClass()))
    {
        ScoredMessageStatus = "Goal event did not contain a ball";
        return;
    }

    FVector velocity = ball->RBState.LinearVelocity;
    float speedUU = sqrtf(velocity.X * velocity.X +
                          velocity.Y * velocity.Y +
                          velocity.Z * velocity.Z);
    if (!std::isfinite(speedUU) || speedUU <= 0.0f)
    {
        velocity = ball->Velocity;
        speedUU = sqrtf(velocity.X * velocity.X +
                        velocity.Y * velocity.Y +
                        velocity.Z * velocity.Z);
    }
    if (!std::isfinite(speedUU) || speedUU < 0.0f)
        speedUU = 0.0f;

    char goalText[96] = "Goal scored!";
    {
        const float kmh = speedUU * 0.036f;
        switch (BallSpeedUnit)
        {
        case 1:  snprintf(goalText, sizeof(goalText), "Goal speed: %.2f mph", kmh * 0.621371f); break;
        case 2:  snprintf(goalText, sizeof(goalText), "Goal speed: %.0f uu/s", speedUU); break;
        default: snprintf(goalText, sizeof(goalText), "Goal speed: %.2f km/h", kmh); break;
        }
    }

    if (SendLocalChatMessage(goalText))
    {
        lastMessageTick = now;
        ScoredMessageStatus = std::string("Last goal: ") + goalText;
    }
}

                                                                              
                
  
                                                                              
                                                                              
                       
                                                                              
void GameEventHookModule::ApplyPovInReplay()
{
    if (!PovInReplay || !IsInReplayPlayback) return;

    try
    {
        PlayerControllerData pcData = GetPlayerControllerData();
        if (!pcData.Controller) return;

        AActor* target = nullptr;
        try
        {
            if (pcData.Controller->Pawn)
                target = pcData.Controller->Pawn;
        }
        catch (...) {}

        if (!target && CurrentGameEvent)
        {
            TArray<ACar_TA*> cars = CurrentGameEvent->Cars;
            if (cars.size() > 0 && cars[0])
                target = cars[0];
        }

        if (!target) return;
        if (pcData.Controller->ViewTarget == target) return;

                                                                          
                                                                                
        FViewTargetTransitionParams transition{};
        pcData.Controller->SetViewTarget(target, transition);
    }
    catch (...) {}
}

                                                                              
                         
                                                                              
std::string GameEventHookModule::GetWorkshopDirectory()
{
                                                                            
                                                                                
    char exePath[MAX_PATH] = {};
    std::string dir;
    if (GetModuleFileNameA(NULL, exePath, MAX_PATH))
        dir = (fs::path(exePath).parent_path() / "KingMod" / "workshop").string();
    else
        dir = (fs::current_path() / "KingMod" / "workshop").string();
    SHCreateDirectoryExA(NULL, dir.c_str(), NULL);
    return dir;
}

void GameEventHookModule::RefreshWorkshopMapList()
{
    WorkshopMapList.clear();
    try
    {
                                                                           
                                                                                 
        const std::string workshopDir = GetWorkshopDirectory();
        const std::string dirs[] = { workshopDir, KingModGetCustomMapsDirectory() };
        for (const std::string& dir : dirs)
        {
            std::error_code ec;
            for (auto it = fs::recursive_directory_iterator(dir, ec);
                 it != fs::recursive_directory_iterator();
                 it.increment(ec))
            {
                if (ec) break;
                if (!it->is_regular_file(ec)) continue;

                if (dir == workshopDir)
                {
                    const fs::path sharedAssets =
                        fs::path(workshopDir) / "shared_assets";
                    const fs::path stagedBackups =
                        fs::path(workshopDir) / "staged_backups";
                    if (KingModPathIsInside(it->path(), sharedAssets) ||
                        KingModPathIsInside(it->path(), stagedBackups))
                        continue;
                }

                std::string ext = it->path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(),
                               [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                if ((ext == ".udk" || ext == ".upk") &&
                    KingModMapPackageScore(it->path()) >= 1000)
                    WorkshopMapList.push_back(it->path().string());
            }
        }
        std::sort(WorkshopMapList.begin(), WorkshopMapList.end());
        WorkshopMapList.erase(std::unique(WorkshopMapList.begin(), WorkshopMapList.end()),
                              WorkshopMapList.end());
    }
    catch (...) {}
}

                                                                              
                                  
  
                                                                             
                                                                                
                                                                                
                                                                              
                                                                               
                        
                                                                              
namespace
{
    struct KingModZipEntry
    {
        std::string name;
        uint16_t    method           = 0;
        uint32_t    compressedSize   = 0;
        uint32_t    uncompressedSize = 0;
        uint32_t    localOffset      = 0;
    };

    uint16_t KingModRd16(const uint8_t* p) { return static_cast<uint16_t>(p[0] | (p[1] << 8)); }
    uint32_t KingModRd32(const uint8_t* p)
    {
        return static_cast<uint32_t>(p[0]) | (static_cast<uint32_t>(p[1]) << 8) |
               (static_cast<uint32_t>(p[2]) << 16) | (static_cast<uint32_t>(p[3]) << 24);
    }

    struct KingModFileCloser
    {
        FILE* f;
        ~KingModFileCloser() { if (f) fclose(f); }
    };

    bool KingModIsMapExtension(const std::string& lowerName)
    {
        const size_t dot = lowerName.find_last_of('.');
        if (dot == std::string::npos) return false;
        const std::string ext = lowerName.substr(dot);
        return ext == ".upk" || ext == ".udk";
    }

    bool KingModIsWorkshopPayloadExtension(const std::string& lowerName)
    {
        const size_t dot = lowerName.find_last_of('.');
        if (dot == std::string::npos) return false;
        const std::string ext = lowerName.substr(dot);
        return ext == ".upk" || ext == ".udk" || ext == ".tfc";
    }

    bool KingModIsSharedWorkshopPackage(const std::string& leafName)
    {
        static const char* kSharedPackages[] = {
            "editorlandscaperesources.upk", "editormaterials.upk",
            "editormeshes.upk",             "editorresources.upk",
            "engine_mi_shaders.upk",        "enginebuildings.upk",
            "enginedebugmaterials.upk",     "enginematerials.upk",
            "engineresources.upk",          "enginevolumetrics.upk",
            "maptemplateindex.upk",         "maptemplates.upk",
            "mods.upk",                     "nodebuddies.upk"
        };

        std::string lower = leafName;
        std::transform(lower.begin(), lower.end(), lower.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        for (const char* package : kSharedPackages)
            if (lower == package) return true;
        return false;
    }

    struct KingModPackageScoreCacheEntry
    {
        uintmax_t size = 0;
        fs::file_time_type modified{};
        int score = -1;
    };
    std::mutex g_KingModPackageScoreMutex;
    std::map<std::string, KingModPackageScoreCacheEntry> g_KingModPackageScoreCache;

    bool KingModReadPackagePrefix(const fs::path& path, std::string& prefix)
    {
        prefix.clear();
        std::ifstream file(path, std::ios::binary);
        if (!file.good()) return false;

        unsigned char signature[4] = {};
        file.read(reinterpret_cast<char*>(signature), sizeof(signature));
        if (file.gcount() != static_cast<std::streamsize>(sizeof(signature)) ||
            signature[0] != 0xC1 || signature[1] != 0x83 ||
            signature[2] != 0x2A || signature[3] != 0x9E)
            return false;

        constexpr std::streamsize kPrefixBytes = 4 * 1024 * 1024;
        prefix.resize(static_cast<size_t>(kPrefixBytes));
        file.read(&prefix[0], kPrefixBytes);
        prefix.resize(static_cast<size_t>(file.gcount()));
        return true;
    }

    int KingModMapPackageScore(const fs::path& path)
    {
        std::error_code metadataError;
        const uintmax_t bytes = fs::file_size(path, metadataError);
        if (metadataError) return -1;
        const fs::file_time_type modified = fs::last_write_time(path, metadataError);
        if (metadataError) return -1;

        const std::string cacheKey = path.lexically_normal().string();
        {
            std::lock_guard<std::mutex> lock(g_KingModPackageScoreMutex);
            const auto found = g_KingModPackageScoreCache.find(cacheKey);
            if (found != g_KingModPackageScoreCache.end() &&
                found->second.size == bytes && found->second.modified == modified)
                return found->second.score;
        }

        std::string prefix;
        if (!KingModReadPackagePrefix(path, prefix)) return -1;

        int score = 1;
        if (prefix.find("PersistentLevel") != std::string::npos) score += 1000;
        if (prefix.find("WorldInfo")       != std::string::npos) score += 350;
        if (prefix.find("TheWorld")        != std::string::npos) score += 250;

        std::string extension = path.extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(),
            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        if (extension == ".udk") score += 40;
        if (KingModIsSharedWorkshopPackage(path.filename().string())) score -= 2000;

        score += static_cast<int>((std::min)(bytes / (4u * 1024u * 1024u),
                                             static_cast<uintmax_t>(100)));
        {
            std::lock_guard<std::mutex> lock(g_KingModPackageScoreMutex);
            g_KingModPackageScoreCache[cacheKey] = { bytes, modified, score };
        }
        return score;
    }

    fs::path KingModFindBestMapPackage(const fs::path& directory)
    {
        fs::path best;
        int bestScore = -1;
        std::error_code ec;
        for (auto it = fs::recursive_directory_iterator(
                 directory, fs::directory_options::skip_permission_denied, ec);
             it != fs::recursive_directory_iterator(); it.increment(ec))
        {
            if (ec) { ec.clear(); continue; }
            if (!it->is_regular_file(ec) || ec) { ec.clear(); continue; }

            std::string lower = it->path().filename().string();
            std::transform(lower.begin(), lower.end(), lower.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (!KingModIsMapExtension(lower)) continue;

            const int score = KingModMapPackageScore(it->path());
            if (score > bestScore)
            {
                bestScore = score;
                best = it->path();
            }
        }
        return bestScore > 0 ? best : fs::path();
    }

    fs::path KingModArchiveExtractionDirectory(const fs::path& archive)
    {
        return archive.parent_path() / (archive.stem().string() + "_files");
    }

                                                                            
                                                                            
                                                                              
                                                                                
                                                                   
    std::string KingModDetectWorkshopDownloadExtension(const std::vector<uint8_t>& bytes)
    {
        if (bytes.size() >= 4 && bytes[0] == 'P' && bytes[1] == 'K' &&
            ((bytes[2] == 3 && bytes[3] == 4) ||
             (bytes[2] == 5 && bytes[3] == 6) ||
             (bytes[2] == 7 && bytes[3] == 8)))
            return ".zip";

        if (bytes.size() >= 7 && bytes[0] == 'R' && bytes[1] == 'a' &&
            bytes[2] == 'r' && bytes[3] == '!' && bytes[4] == 0x1A &&
            bytes[5] == 0x07 && (bytes[6] == 0x00 || bytes[6] == 0x01))
            return ".rar";

        if (bytes.size() >= 6 && bytes[0] == 0x37 && bytes[1] == 0x7A &&
            bytes[2] == 0xBC && bytes[3] == 0xAF && bytes[4] == 0x27 &&
            bytes[5] == 0x1C)
            return ".7z";

                                                                      
        if (bytes.size() >= 4 && bytes[0] == 0xC1 && bytes[1] == 0x83 &&
            bytes[2] == 0x2A && bytes[3] == 0x9E)
            return ".upk";

        return std::string();
    }

    std::string KingModLeafName(const std::string& path)
    {
        const size_t slash = path.find_last_of("\\/");
        return (slash == std::string::npos) ? path : path.substr(slash + 1);
    }

    bool KingModZipList(const std::string& path, std::vector<KingModZipEntry>& out)
    {
        out.clear();
        FILE* f = nullptr;
        if (fopen_s(&f, path.c_str(), "rb") != 0 || !f) return false;
        KingModFileCloser closer{ f };

        if (_fseeki64(f, 0, SEEK_END) != 0) return false;
        const long long fileSize = _ftelli64(f);
        if (fileSize < 22) return false;

                                                                                  
                                                                      
        const long long tail = (fileSize < 66000) ? fileSize : 66000;
        std::vector<uint8_t> buf(static_cast<size_t>(tail));
        if (_fseeki64(f, fileSize - tail, SEEK_SET) != 0) return false;
        if (fread(buf.data(), 1, static_cast<size_t>(tail), f) != static_cast<size_t>(tail)) return false;

        long long eocd = -1;
        for (long long i = tail - 22; i >= 0; --i)
        {
            const size_t u = static_cast<size_t>(i);
            if (buf[u] == 0x50 && buf[u + 1] == 0x4B && buf[u + 2] == 0x05 && buf[u + 3] == 0x06)
            {
                eocd = i;
                break;
            }
        }
        if (eocd < 0) return false;

        const uint32_t count  = KingModRd16(&buf[static_cast<size_t>(eocd) + 10]);
        const uint32_t cdSize = KingModRd32(&buf[static_cast<size_t>(eocd) + 12]);
        const uint32_t cdOff  = KingModRd32(&buf[static_cast<size_t>(eocd) + 16]);
        if (cdSize == 0 || cdSize > 64u * 1024u * 1024u) return false;
        if (cdOff == 0xFFFFFFFFu) return false;                        

        std::vector<uint8_t> cd(cdSize);
        if (_fseeki64(f, cdOff, SEEK_SET) != 0) return false;
        if (fread(cd.data(), 1, cdSize, f) != cdSize) return false;

        size_t p = 0;
        for (uint32_t i = 0; i < count && p + 46 <= cd.size(); ++i)
        {
            if (KingModRd32(&cd[p]) != 0x02014B50u) break;
            KingModZipEntry e;
            e.method           = KingModRd16(&cd[p + 10]);
            e.compressedSize   = KingModRd32(&cd[p + 20]);
            e.uncompressedSize = KingModRd32(&cd[p + 24]);
            const uint16_t nameLen  = KingModRd16(&cd[p + 28]);
            const uint16_t extraLen = KingModRd16(&cd[p + 30]);
            const uint16_t cmtLen   = KingModRd16(&cd[p + 32]);
            e.localOffset      = KingModRd32(&cd[p + 42]);
            if (p + 46 + nameLen > cd.size()) break;
            e.name.assign(reinterpret_cast<const char*>(&cd[p + 46]), nameLen);
            out.push_back(e);
            p += 46u + nameLen + extraLen + cmtLen;
        }
        return !out.empty();
    }

    bool KingModZipExtractEntry(const std::string& zipPath, const KingModZipEntry& entry,
                                const std::string& outPath)
    {
        if (entry.method != 0 && entry.method != 8) return false;

        FILE* in = nullptr;
        if (fopen_s(&in, zipPath.c_str(), "rb") != 0 || !in) return false;
        KingModFileCloser inCloser{ in };

                                                                             
                                                                                 
        uint8_t local[30];
        if (_fseeki64(in, entry.localOffset, SEEK_SET) != 0) return false;
        if (fread(local, 1, sizeof(local), in) != sizeof(local)) return false;
        if (KingModRd32(local) != 0x04034B50u) return false;
        const uint16_t nameLen  = KingModRd16(&local[26]);
        const uint16_t extraLen = KingModRd16(&local[28]);
        if (_fseeki64(in, static_cast<long long>(entry.localOffset) + 30 + nameLen + extraLen, SEEK_SET) != 0)
            return false;

        FILE* out = nullptr;
        if (fopen_s(&out, outPath.c_str(), "wb") != 0 || !out) return false;
        KingModFileCloser outCloser{ out };

        std::vector<uint8_t> inBuf(64 * 1024);
        std::vector<uint8_t> outBuf(256 * 1024);
        uint32_t remaining = entry.compressedSize;
        uint64_t written = 0;

        if (entry.method == 0)
        {
            if (entry.compressedSize != entry.uncompressedSize) return false;
            while (remaining > 0)
            {
                const size_t want = (remaining < inBuf.size()) ? remaining : inBuf.size();
                const size_t got  = fread(inBuf.data(), 1, want, in);
                if (got != want) return false;
                if (fwrite(inBuf.data(), 1, got, out) != got) return false;
                remaining -= static_cast<uint32_t>(got);
                written += got;
            }
            return written == entry.uncompressedSize;
        }

                                                                            
                                                                   
        z_stream zs{};
        if (inflateInit2(&zs, -MAX_WBITS) != Z_OK) return false;

        bool ok = true;
        int  ret = Z_OK;
        while (ok && ret != Z_STREAM_END)
        {
            const size_t want = (remaining < inBuf.size()) ? remaining : inBuf.size();
            if (want == 0) { ok = false; break; }
            const size_t got = fread(inBuf.data(), 1, want, in);
            if (got != want) { ok = false; break; }
            remaining -= static_cast<uint32_t>(got);

            zs.next_in  = inBuf.data();
            zs.avail_in = static_cast<uInt>(got);
            do
            {
                zs.next_out  = outBuf.data();
                zs.avail_out = static_cast<uInt>(outBuf.size());
                ret = inflate(&zs, Z_NO_FLUSH);
                if (ret != Z_OK && ret != Z_STREAM_END && ret != Z_BUF_ERROR) { ok = false; break; }
                const size_t produced = outBuf.size() - zs.avail_out;
                if (produced > 0 && fwrite(outBuf.data(), 1, produced, out) != produced) { ok = false; break; }
                written += produced;
            } while (zs.avail_out == 0 && ret != Z_STREAM_END);
        }
        const bool complete = ok && ret == Z_STREAM_END && remaining == 0 &&
                              zs.avail_in == 0 && written == entry.uncompressedSize;
        inflateEnd(&zs);
        return complete;
    }

                                                                                 
                                                                               
                                                                    
    std::string KingModPeekArchiveMapName(const std::string& path)
    {
        FILE* f = nullptr;
        if (fopen_s(&f, path.c_str(), "rb") != 0 || !f) return std::string();
        KingModFileCloser closer{ f };

        std::vector<uint8_t> buf(512 * 1024);
        const size_t got = fread(buf.data(), 1, buf.size(), f);
        if (got == 0) return std::string();
        buf.resize(got);

        std::string flat;
        flat.reserve(got);
        for (size_t i = 0; i < got; ++i)
        {
            const uint8_t c = buf[i];
                                                                                 
                                                                         
            if (c == 0) continue;
            flat.push_back((c >= 32 && c < 127) ? static_cast<char>(c) : '\n');
        }

        static const char* kExts[] = { ".upk", ".udk" };
        for (const char* ext : kExts)
        {
            size_t at = 0;
            while ((at = flat.find(ext, at)) != std::string::npos)
            {
                size_t start = at;
                while (start > 0)
                {
                    const char c = flat[start - 1];
                    if (c == '\n' || c == '/' || c == '\\') break;
                    --start;
                }
                const std::string candidate = flat.substr(start, at + strlen(ext) - start);
                if (candidate.size() > strlen(ext))
                    return candidate;
                at += strlen(ext);
            }
        }
        return std::string();
    }

    std::string KingModFindArchiveTool(bool& outIsSevenZip)
    {
        outIsSevenZip = true;
        static const char* kSevenZip[] = {
            "C:\\Program Files\\7-Zip\\7z.exe",
            "C:\\Program Files (x86)\\7-Zip\\7z.exe",
        };
        for (const char* candidate : kSevenZip)
        {
            std::error_code ec;
            if (fs::exists(candidate, ec) && !ec) return candidate;
        }
        static const char* kWinRar[] = {
            "C:\\Program Files\\WinRAR\\UnRAR.exe",
            "C:\\Program Files (x86)\\WinRAR\\UnRAR.exe",
            "C:\\Program Files\\WinRAR\\WinRAR.exe",
            "C:\\Program Files (x86)\\WinRAR\\WinRAR.exe",
        };
        for (const char* candidate : kWinRar)
        {
            std::error_code ec;
            if (fs::exists(candidate, ec) && !ec) { outIsSevenZip = false; return candidate; }
        }
        return std::string();
    }

    bool KingModRunArchiveTool(const std::string& tool, bool sevenZip,
                               const std::string& archive, const std::string& outDir)
    {
        std::string args;
        if (sevenZip)
            args = "\"" + tool + "\" x -y -o\"" + outDir + "\" \"" + archive + "\" *.upk *.udk *.tfc -r";
        else
            args = "\"" + tool + "\" x -y \"" + archive + "\" *.upk *.udk *.tfc \"" + outDir + "\\\"";

        std::vector<char> cmd(args.begin(), args.end());
        cmd.push_back('\0');

        STARTUPINFOA si{};
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;
        PROCESS_INFORMATION pi{};
        if (!CreateProcessA(NULL, cmd.data(), NULL, NULL, FALSE, CREATE_NO_WINDOW,
                            NULL, NULL, &si, &pi))
            return false;

                                                                             
                                                                                
                                                                          
        const DWORD waitResult = WaitForSingleObject(pi.hProcess, 10 * 60 * 1000);
        if (waitResult == WAIT_TIMEOUT)
        {
            TerminateProcess(pi.hProcess, ERROR_TIMEOUT);
            WaitForSingleObject(pi.hProcess, 5000);
        }
        DWORD exitCode = 1;
        GetExitCodeProcess(pi.hProcess, &exitCode);
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        return waitResult == WAIT_OBJECT_0 &&
               (exitCode == 0 || exitCode == 1);                        
    }

    bool KingModExtractWorkshopArchivePayload(const std::string& archivePath,
                                               int archiveKind,
                                               std::string& status)
    {
        const fs::path archive(archivePath);
        const fs::path outDir = KingModArchiveExtractionDirectory(archive);
        bool unpacked = false;

        try
        {
            std::error_code directoryError;
            fs::create_directories(outDir, directoryError);
            if (directoryError)
            {
                status = "Could not create map package folder: " +
                         directoryError.message();
                return false;
            }

            if (archiveKind == 1)
            {
                std::vector<KingModZipEntry> zipEntries;
                if (!KingModZipList(archivePath, zipEntries))
                {
                                                                             
                                                                           
                                                                   
                    bool sevenZip = true;
                    const std::string tool = KingModFindArchiveTool(sevenZip);
                    if (tool.empty() || !KingModRunArchiveTool(
                            tool, sevenZip, archivePath, outDir.string()))
                    {
                        status = "Could not read " + archive.filename().string() +
                                 " (install 7-Zip for this archive format)";
                        return false;
                    }
                    unpacked = true;
                }
                else
                {
                    size_t payloadCount = 0;
                    size_t installedCount = 0;
                    for (const KingModZipEntry& z : zipEntries)
                    {
                        if (g_DllUnloading.load())
                        {
                            status = "Map extraction cancelled";
                            return false;
                        }

                        std::string lower = z.name;
                        std::transform(lower.begin(), lower.end(), lower.begin(),
                            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                        if (!KingModIsWorkshopPayloadExtension(lower)) continue;
                        ++payloadCount;

                        const std::string leaf = KingModLeafName(z.name);
                        if (leaf.empty()) continue;

                        const fs::path target = outDir / leaf;
                        const fs::path temporary = outDir /
                            (leaf + ".kingmod-extracting.tmp");
                        if (!KingModZipExtractEntry(
                                archivePath, z, temporary.string()))
                        {
                            std::error_code cleanupError;
                            fs::remove(temporary, cleanupError);
                            continue;
                        }

                        const std::string extension = KingModLowerAscii(
                            fs::path(leaf).extension().string());
                        std::string packagePrefix;
                        if (extension != ".tfc" &&
                            !KingModReadPackagePrefix(temporary, packagePrefix))
                        {
                            std::error_code cleanupError;
                            fs::remove(temporary, cleanupError);
                            continue;
                        }

                        if (!MoveFileExW(temporary.c_str(), target.c_str(),
                                         MOVEFILE_REPLACE_EXISTING |
                                         MOVEFILE_WRITE_THROUGH))
                        {
                            std::error_code cleanupError;
                            fs::remove(temporary, cleanupError);
                            continue;
                        }
                        ++installedCount;
                        unpacked = true;
                    }

                                                                                
                                                                                
                                                                         
                    if (installedCount != payloadCount)
                    {
                        bool sevenZip = true;
                        const std::string tool = KingModFindArchiveTool(sevenZip);
                        if (tool.empty() || !KingModRunArchiveTool(
                                tool, sevenZip, archivePath, outDir.string()))
                        {
                            status = "This ZIP needs 7-Zip to extract all map assets";
                            return false;
                        }
                        unpacked = true;
                    }
                }
            }
            else
            {
                bool sevenZip = true;
                const std::string tool = KingModFindArchiveTool(sevenZip);
                if (tool.empty())
                {
                    status = std::string(archiveKind == 2 ? ".rar" : ".7z") +
                        " needs 7-Zip or WinRAR installed";
                    return false;
                }
                unpacked = KingModRunArchiveTool(
                    tool, sevenZip, archivePath, outDir.string());
            }

            const fs::path mainMap = unpacked
                ? KingModFindBestMapPackage(outDir)
                : fs::path();
            if (mainMap.empty())
            {
                status = "No playable Rocket League map was found in " +
                         archive.filename().string();
                return false;
            }

            status = "Installed " + mainMap.filename().string() +
                     " with all map assets";
            return true;
        }
        catch (const std::exception& exception)
        {
            status = "Map extraction failed: " + std::string(exception.what());
            return false;
        }
        catch (...)
        {
            status = "Map extraction failed";
            return false;
        }
    }

    fs::path KingModResolveCompleteWorkshopSource(const fs::path& requested)
    {
        const fs::path workshopRoot =
            fs::path(GameEventHookModule::GetWorkshopDirectory());
        std::error_code canonicalError;
        const fs::path requestedParent =
            fs::weakly_canonical(requested.parent_path(), canonicalError);
        if (canonicalError) return requested;
        const fs::path canonicalRoot =
            fs::weakly_canonical(workshopRoot, canonicalError);
        if (canonicalError || requestedParent != canonicalRoot)
            return requested;

        const std::string requestedLeaf = KingModLowerAscii(
            requested.filename().string());
        std::error_code ec;
        for (const fs::directory_entry& candidate :
             fs::directory_iterator(workshopRoot, ec))
        {
            if (ec) break;
            if (!candidate.is_regular_file(ec) || ec) { ec.clear(); continue; }

            const std::string extension = KingModLowerAscii(
                candidate.path().extension().string());
            const int kind = extension == ".zip" ? 1 :
                             (extension == ".rar" ? 2 :
                             (extension == ".7z" ? 3 : 0));
            if (kind == 0) continue;

            bool containsRequestedMap = false;
            if (kind == 1)
            {
                std::vector<KingModZipEntry> entries;
                if (KingModZipList(candidate.path().string(), entries))
                {
                    for (const KingModZipEntry& entry : entries)
                    {
                        if (KingModLowerAscii(KingModLeafName(entry.name)) ==
                            requestedLeaf)
                        {
                            containsRequestedMap = true;
                            break;
                        }
                    }
                }
            }
            else
            {
                containsRequestedMap =
                    KingModLowerAscii(KingModLeafName(
                        KingModPeekArchiveMapName(candidate.path().string()))) ==
                    requestedLeaf;
            }
            if (!containsRequestedMap) continue;

            const fs::path extractionDirectory =
                KingModArchiveExtractionDirectory(candidate.path());
            const fs::path alreadyComplete =
                KingModFindBestMapPackage(extractionDirectory);
            if (!alreadyComplete.empty()) return alreadyComplete;

            std::string ignoredStatus;
            if (KingModExtractWorkshopArchivePayload(
                    candidate.path().string(), kind, ignoredStatus))
            {
                const fs::path complete = KingModFindBestMapPackage(
                    extractionDirectory);
                if (!complete.empty()) return complete;
            }
            break;
        }
        return requested;
    }
}

void GameEventHookModule::RefreshWorkshopInstalled()
{
    WorkshopInstalled.clear();
    WorkshopInstalledStatus.clear();

    try
    {
        const std::string workshopDir = GetWorkshopDirectory();
        const std::string dirs[] = { workshopDir, KingModGetCustomMapsDirectory() };

        for (const std::string& dir : dirs)
        {
            std::error_code ec;
            for (auto it = fs::recursive_directory_iterator(dir, ec);
                 it != fs::recursive_directory_iterator();
                 it.increment(ec))
            {
                if (ec) break;
                if (!it->is_regular_file(ec)) continue;

                if (dir == workshopDir)
                {
                    const fs::path sharedAssets =
                        fs::path(workshopDir) / "shared_assets";
                    const fs::path stagedBackups =
                        fs::path(workshopDir) / "staged_backups";
                    if (KingModPathIsInside(it->path(), sharedAssets) ||
                        KingModPathIsInside(it->path(), stagedBackups))
                        continue;
                }

                std::string ext = it->path().extension().string();
                std::transform(ext.begin(), ext.end(), ext.begin(),
                               [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

                WorkshopInstalledEntry entry;
                entry.path = it->path().string();
                entry.name = it->path().filename().string();
                std::error_code sizeEc;
                entry.size = static_cast<long long>(fs::file_size(it->path(), sizeEc));
                if (sizeEc) entry.size = 0;

                if (ext == ".upk" || ext == ".udk")
                {
                                                                            
                                                                           
                                                                     
                    if (KingModMapPackageScore(it->path()) < 1000)
                        continue;
                    entry.kind    = 0;
                    entry.mapFile = entry.path;
                    entry.status  = "Ready";
                }
                else if (ext == ".zip" || ext == ".rar" || ext == ".7z")
                {
                    entry.kind = (ext == ".zip") ? 1 : ((ext == ".rar") ? 2 : 3);

                    if (entry.kind == 1)
                    {
                        std::vector<KingModZipEntry> zipEntries;
                        if (KingModZipList(entry.path, zipEntries))
                        {
                            for (const KingModZipEntry& z : zipEntries)
                            {
                                std::string lower = z.name;
                                std::transform(lower.begin(), lower.end(), lower.begin(),
                                               [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                                if (KingModIsMapExtension(lower))
                                {
                                    entry.innerMap = KingModLeafName(z.name);
                                    break;
                                }
                            }
                            if (entry.innerMap.empty())
                                entry.status = "No map inside";
                        }
                        else
                        {
                            entry.status = "Unreadable zip";
                        }
                    }
                    else
                    {
                        entry.innerMap = KingModLeafName(KingModPeekArchiveMapName(entry.path));
                    }

                                                                               
                                                                              
                                                                                 
                    const fs::path extractionDir =
                        KingModArchiveExtractionDirectory(it->path());
                    const fs::path unpacked = KingModFindBestMapPackage(extractionDir);
                    if (!unpacked.empty())
                    {
                        entry.innerMap = unpacked.filename().string();
                        entry.mapFile = unpacked.string();
                        entry.status  = "Ready";
                    }
                    else if (!entry.innerMap.empty())
                    {
                                                                             
                                                                               
                                                                               
                        std::error_code legacyError;
                        const fs::path legacy =
                            fs::path(workshopDir) / entry.innerMap;
                        if (fs::is_regular_file(legacy, legacyError) &&
                            !legacyError && KingModMapPackageScore(legacy) >= 1000)
                        {
                            entry.mapFile = legacy.string();
                            entry.status = "Ready";
                        }
                        else if (entry.status.empty())
                        {
                            entry.status = "Packed";
                        }
                    }
                    else if (entry.status.empty())
                    {
                        entry.status = "Packed";
                    }
                }
                else
                {
                    continue;
                }

                WorkshopInstalled.push_back(entry);
            }
        }

        std::sort(WorkshopInstalled.begin(), WorkshopInstalled.end(),
                  [](const WorkshopInstalledEntry& a, const WorkshopInstalledEntry& b)
                  { return a.name < b.name; });

                                                                                
                                                          
        std::vector<WorkshopInstalledEntry> merged;
        for (const WorkshopInstalledEntry& entry : WorkshopInstalled)
        {
            bool covered = false;
            if (entry.kind == 0)
            {
                for (const WorkshopInstalledEntry& other : WorkshopInstalled)
                {
                    if (other.kind == 0) continue;
                    std::error_code relativeError;
                    const fs::path relative = fs::relative(
                        fs::path(entry.path),
                        KingModArchiveExtractionDirectory(fs::path(other.path)),
                        relativeError);
                    if (!relativeError && !relative.empty() &&
                        *relative.begin() != fs::path(".."))
                    {
                        covered = true;
                        break;
                    }
                }
            }
            if (!covered) merged.push_back(entry);
        }
        WorkshopInstalled = std::move(merged);

        if (WorkshopInstalled.empty())
            WorkshopInstalledStatus = "Nothing in the workshop folder yet";
    }
    catch (...)
    {
        WorkshopInstalledStatus = "Could not read the workshop folder";
    }

    RefreshWorkshopMapList();
}

void GameEventHookModule::ExtractWorkshopInstalled(int index)
{
    if (index < 0 || index >= static_cast<int>(WorkshopInstalled.size())) return;
    WorkshopInstalledEntry entry = WorkshopInstalled[index];
    if (entry.kind == 0) return;

    KingModExtractWorkshopArchivePayload(
        entry.path, entry.kind, WorkshopInstalledStatus);

    const std::string keepStatus = WorkshopInstalledStatus;
    RefreshWorkshopInstalled();
    WorkshopInstalledStatus = keepStatus;
}

void GameEventHookModule::DeleteWorkshopInstalled(int index)
{
    if (index < 0 || index >= static_cast<int>(WorkshopInstalled.size())) return;
    const WorkshopInstalledEntry entry = WorkshopInstalled[index];

    std::error_code ec;
    if (entry.kind != 0)
    {
        const fs::path archive(entry.path);
        const fs::path extracted = KingModArchiveExtractionDirectory(archive);
        if (extracted != archive.parent_path() &&
            KingModPathIsInside(extracted, archive.parent_path()))
            fs::remove_all(extracted, ec);
        ec.clear();
    }
    fs::remove(entry.path, ec);
    std::string status = ec ? ("Could not delete " + entry.name) : ("Deleted " + entry.name);

    RefreshWorkshopInstalled();
    WorkshopInstalledStatus = status;
}

void GameEventHookModule::OpenCustomMapsFolder()
{
    try
    {
        const std::string dir = KingModGetCustomMapsDirectory();
        ShellExecuteA(NULL, "open", dir.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    catch (...) {}
}

void GameEventHookModule::OpenWorkshopFolder()
{
    try
    {
        const std::string dir = GetWorkshopDirectory();
        ShellExecuteA(NULL, "open", dir.c_str(), NULL, NULL, SW_SHOWNORMAL);
    }
    catch (...) {}
}

                                                                              
                                 
  
                                                  
  
                                                                    
                                                                              
                                                                            
                                                                   
  
                                                                                    
                                                                         
                                                                          
                                                                             
                                      
  
                                                                               
                                                                            
                            
                                                                              
namespace
{
    std::mutex                                       g_WorkshopMutex;
    std::vector<GameEventHookModule::WorkshopItem>   g_WorkshopStaging;
    bool                                             g_WorkshopStagingReady = false;
    std::string                                      g_WorkshopStagingError;
                                                                           
    std::map<std::string, std::vector<uint8_t>>       g_WorkshopPreviewBytes;
                                                                             
                                                                                 
    std::unordered_set<std::string>                   g_WorkshopPreviewFailed;
                                                                   
    std::map<std::string, std::pair<int, std::string>> g_WorkshopProgress;
    std::atomic<bool>                                g_WorkshopFetchRunning{ false };
    std::atomic<bool>                                g_WorkshopMapLaunchRunning{ false };
    std::mutex                                      g_WorkshopAliasMutex;
    fs::path                                        g_WorkshopAliasTarget;
    fs::path                                        g_WorkshopAliasBackup;
    bool                                            g_WorkshopAliasRestoreRunning = false;
    bool                                            g_WorkshopAliasRecoveryRunning = false;

                                                                            
                                                                              
                                                                          
                                                        
    std::string g_PendingWorkshopMapPath;
    std::chrono::steady_clock::time_point g_WorkshopLoadRetryAt;
    std::chrono::steady_clock::time_point g_WorkshopLoadDeadline;
    int g_WorkshopLoadAttempts = 0;
    bool g_WorkshopLoadTaskQueued = false;
                                                                             
                                                                            
                                                                              
                                                     
    bool g_PendingWorkshopAllowsDirectTravel = false;

    bool KingModLoadWorkshopPath(const std::string& fullPath);
    void KingModQueueWorkshopLoad(
        const std::string& fullPath,
        bool allowDirectTravel = true);
    void KingModPumpWorkshopLoad();

    const char* KingModWorkshopGameClass(int gameModeIndex)
    {
        switch (gameModeIndex)
        {
        case 1: return "TAGame.GameInfo_Basketball_TA";
        case 2: return "TAGame.GameInfo_Hockey_TA";
        case 3: return "TAGame.GameInfo_Items_TA";
        case 4: return "TAGame.GameInfo_Breakout_TA";
        case 5: return "TAGame.GameInfo_GodBall_TA";
        case 6: return "TAGame.GameInfo_Football_TA";
        default: return "TAGame.GameInfo_Soccar_TA";
        }
    }

    bool KingModIsSafeTravelToken(const std::string& value, bool allowColon = false)
    {
        if (value.empty() || value.size() > 255) return false;
        return std::all_of(value.begin(), value.end(), [allowColon](unsigned char c)
        {
            return std::isalnum(c) || c == '_' || c == '-' || c == '.' ||
                   (allowColon && (c == ':' || c == '[' || c == ']'));
        });
    }

    bool KingModIsSafeGameTags(const std::string& value)
    {
        if (value.size() > 1024) return false;
        return std::all_of(value.begin(), value.end(), [](unsigned char c)
        {
            return std::isalnum(c) || c == '_' || c == ',';
        });
    }

    std::string KingModBuildWorkshopSessionCommand(
        const std::string& packageName,
        bool hostLan,
        int gameModeIndex,
        int maxPlayers,
        const std::string& password,
        const std::string& gameTags,
        bool localTraining)
    {
        if (!hostLan && localTraining)
            return "start " + packageName +
                   "?Game=TAGame.GameInfo_Tutorial_TA";

        int players = std::clamp(maxPlayers, 2, 8);
        if ((players & 1) != 0) ++players;
        if (players > 8) players = 8;
        const int connections = players > 10 ? players : 10;
        std::string sessionTags = gameTags.empty() ? "BotsNone" : gameTags;
        if (!sessionTags.empty()) sessionTags += ',';
        sessionTags += "PlayerCount" + std::to_string(players);

        if (hostLan)
        {
            std::string command =
                "open " + packageName +
                "?Playtest?game=" + KingModWorkshopGameClass(gameModeIndex) +
                "?GameTags=" + sessionTags +
                "?NumPublicConnections=" + std::to_string(connections) +
                "?NumOpenPublicConnections=" + std::to_string(connections) +
                "?Lan?Listen";
            return command;
        }
        return "start " + packageName +
               "?Game=" + KingModWorkshopGameClass(gameModeIndex) +
               "?GameTags=" + sessionTags;
    }

    bool KingModIsValidPort(const std::string& port)
    {
        if (port.empty() || !std::all_of(port.begin(), port.end(),
                [](unsigned char c) { return std::isdigit(c); }))
            return false;
        try
        {
            const int value = std::stoi(port);
            return value >= 1 && value <= 65535;
        }
        catch (...) { return false; }
    }

    std::string KingModBuildJoinCommand(const std::string& host,
                                         const std::string& port,
                                         const std::string& password)
    {
        std::string command = "start " + host + ":" + port + "/?Lan";
        if (!password.empty())
            command += "?Password=" + password;
        return command;
    }

    bool KingModDispatchConsoleCommand(const std::string& command);

    void KingModQueueFreeplayTravelVerification(const std::string& packageName,
                                                 int gameModeIndex,
                                                 int ticksRemaining,
                                                 bool restoreAliasOnFailure)
    {
        Main.Execute([packageName, gameModeIndex, ticksRemaining, restoreAliasOnFailure]()
        {
            if (g_DllUnloading.load()) return;
            if (GameEventHookModule::IsInGame)
            {
                GameEventHookModule::WorkshopLoadStatus = "Freeplay started";
                return;
            }
            if (ticksRemaining > 1)
            {
                KingModQueueFreeplayTravelVerification(
                    packageName, gameModeIndex, ticksRemaining - 1, restoreAliasOnFailure);
                return;
            }

            const std::string command = "start " + packageName +
                "?Game=TAGame.GameInfo_Tutorial_TA";
            if (KingModDispatchConsoleCommand(command))
            {
                GameEventHookModule::WorkshopLoadStatus = "Starting Freeplay";
                Main.SpawnNotification("KingMod", "Starting Freeplay...", 3);
                return;
            }

            if (restoreAliasOnFailure)
                KingModRestoreWorkshopAliasAfterTravel();
            GameEventHookModule::WorkshopLoadStatus = "Freeplay travel failed";
            Main.SpawnNotification("KingMod", "Freeplay could not start because the game console is not ready", 5);
        });
    }

    void KingModQueueFreeplayLaunch(const std::string& packageName,
                                    int gameModeIndex,
                                    int attemptsRemaining,
                                    bool restoreAliasOnFailure)
    {
        Main.Execute([packageName, gameModeIndex, attemptsRemaining, restoreAliasOnFailure]()
        {
            if (g_DllUnloading.load()) return;

                                                                          
                                                                            
                                                                               
                                                                          
                                                                             
                                                                          
            const std::string command = "start " + packageName +
                "?Game=TAGame.GameInfo_Tutorial_TA";
            if (KingModDispatchConsoleCommand(command))
            {
                GameEventHookModule::WorkshopLoadStatus = "Starting Workshop Freeplay";
                Main.SpawnNotification("KingMod", "Starting Workshop Freeplay...", 3);
                KingModQueueFreeplayTravelVerification(
                    packageName, gameModeIndex, 120, restoreAliasOnFailure);
                return;
            }

            if (attemptsRemaining > 1)
            {
                KingModQueueFreeplayLaunch(packageName, gameModeIndex,
                                           attemptsRemaining - 1, restoreAliasOnFailure);
                return;
            }
            if (restoreAliasOnFailure)
                KingModRestoreWorkshopAliasAfterTravel();
            GameEventHookModule::WorkshopLoadStatus = "Freeplay console is not ready";
            Main.SpawnNotification("KingMod", "Freeplay console is not ready; return to the main menu and try again", 5);
        });
    }

    bool KingModDispatchConsoleCommand(const std::string& command)
    {
        bool sent = false;
        try
        {
            if (AActor* actor = Instances.GetDefaultInstanceOf<AActor>())
            {
                actor->ConsoleCommand(Format::ToFString(command), false);
                sent = true;
            }
        }
        catch (...) {}

        if (!sent)
        {
            try
            {
                if (APlayerController* controller = Instances.IAPlayerController())
                {
                    controller->ConsoleCommand(Format::ToFString(command), false);
                    sent = true;
                }
            }
            catch (...) {}
        }

        if (!sent)
        {
            try
            {
                if (UGameViewportClient_TA* viewport =
                        Instances.GetInstanceOf<UGameViewportClient_TA>())
                {
                    viewport->ConsoleCommand(Format::ToFString(command));
                    sent = true;
                }
            }
            catch (...) {}
        }
        return sent;
    }

    size_t KingModCurlWriteToBytes(void* contents, size_t size, size_t nmemb, void* userp)
    {
        const size_t total = size * nmemb;
        auto* out = static_cast<std::vector<uint8_t>*>(userp);
        const auto* p = static_cast<const uint8_t*>(contents);
        try { out->insert(out->end(), p, p + total); }
        catch (...) { return 0; }
        return total;
    }

                                                                              
                                                               
    thread_local std::string g_KingModHttpError;

                                                                                
                                                                                 
                                                                              
                                                                            
                                                                                
                                                                               
                                                                       
    void KingModCurlCommonOpts(CURL* curl, long timeoutSec)
    {
        curl_easy_setopt(curl, CURLOPT_USERAGENT,
                         "Mozilla/5.0 (Windows NT 10.0; Win64; x64) KingMod/1.0");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 8L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeoutSec);
        curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "");
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, (long)CURL_HTTP_VERSION_1_1);

#ifdef CURLSSLOPT_NATIVE_CA
        curl_easy_setopt(curl, CURLOPT_SSL_OPTIONS, (long)CURLSSLOPT_NATIVE_CA);
#endif

                                                                             
        static const std::string caBundle = []() -> std::string
        {
            char exePath[MAX_PATH] = {};
            if (!GetModuleFileNameA(NULL, exePath, MAX_PATH))
                return std::string();
            std::error_code ec;
            const fs::path candidate = fs::path(exePath).parent_path() / "KingMod" / "cacert.pem";
            if (fs::exists(candidate, ec) && !ec)
                return candidate.string();
            return std::string();
        }();
        if (!caBundle.empty())
            curl_easy_setopt(curl, CURLOPT_CAINFO, caBundle.c_str());
    }

                                                                                 
                                                                              
                                                                 
    bool KingModCurlPerform(CURL* curl, long& httpCode, std::string* resetBody,
                            std::vector<uint8_t>* resetBytes)
    {
        char errBuf[CURL_ERROR_SIZE] = {};
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errBuf);

        CURLcode res = curl_easy_perform(curl);

        httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);

        if (res == CURLE_OK)
            g_KingModHttpError.clear();
        else
            g_KingModHttpError = (errBuf[0] != '\0') ? errBuf : curl_easy_strerror(res);

        return res == CURLE_OK;
    }

    bool KingModHttpGetString(const std::string& url, std::string& out, long timeoutSec = 20)
    {
        out.clear();
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        KingModCurlCommonOpts(curl, timeoutSec);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteToString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
        long code = 0;
        const bool ok = KingModCurlPerform(curl, code, &out, nullptr);
        curl_easy_cleanup(curl);
        if (ok && code >= 200 && code < 300 && !out.empty())
            return true;
        if (ok && g_KingModHttpError.empty())
            g_KingModHttpError = out.empty() ? ("HTTP " + std::to_string(code) + ", empty reply")
                                             : ("HTTP " + std::to_string(code));
        return false;
    }

    bool KingModHttpPostString(const std::string& url, const std::string& body,
                               std::string& out, long timeoutSec = 20)
    {
        out.clear();
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        KingModCurlCommonOpts(curl, timeoutSec);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, static_cast<long>(body.size()));
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteToString);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);
        long code = 0;
        const bool ok = KingModCurlPerform(curl, code, &out, nullptr);
        curl_easy_cleanup(curl);
        if (ok && code >= 200 && code < 300 && !out.empty())
            return true;
        if (ok && g_KingModHttpError.empty())
            g_KingModHttpError = "HTTP " + std::to_string(code);
        return false;
    }

    bool KingModHttpGetBytes(const std::string& url, std::vector<uint8_t>& out,
                             const std::string& progressId = std::string(),
                             long timeoutSec = 300)
    {
        out.clear();
        CURL* curl = curl_easy_init();
        if (!curl) return false;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        KingModCurlCommonOpts(curl, timeoutSec);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, KingModCurlWriteToBytes);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &out);

                                                                                
                                                                  
        std::string idCopy = progressId;
        if (!idCopy.empty())
        {
            using ProgressFn = int(*)(void*, curl_off_t, curl_off_t, curl_off_t, curl_off_t);
            static ProgressFn cb = [](void* userp, curl_off_t dlTotal, curl_off_t dlNow,
                                      curl_off_t, curl_off_t) -> int
            {
                const std::string* id = static_cast<const std::string*>(userp);
                if (id && !id->empty() && dlTotal > 0)
                {
                    int pct = static_cast<int>((dlNow * 100) / dlTotal);
                    if (pct < 0)   pct = 0;
                    if (pct > 100) pct = 100;
                    std::lock_guard<std::mutex> lock(g_WorkshopMutex);
                    g_WorkshopProgress[*id] = { pct, "Downloading..." };
                }
                return 0;
            };
            curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0L);
            curl_easy_setopt(curl, CURLOPT_XFERINFOFUNCTION, cb);
            curl_easy_setopt(curl, CURLOPT_XFERINFODATA, &idCopy);
        }

        long code = 0;
        const bool ok = KingModCurlPerform(curl, code, nullptr, &out);
        curl_easy_cleanup(curl);
        if (ok && code >= 200 && code < 300 && !out.empty())
            return true;
        if (ok && g_KingModHttpError.empty())
            g_KingModHttpError = "HTTP " + std::to_string(code);
        return false;
    }

    bool KingModEnsureSharedWorkshopAssets(const fs::path& mapSource,
                                            const fs::path& cookedDir,
                                            std::string& error)
    {
        error.clear();
        static const char* kPackages[] = {
            "EditorLandscapeResources.upk", "EditorMaterials.upk",
            "EditorMeshes.upk",             "EditorResources.upk",
            "Engine_MI_Shaders.upk",        "EngineBuildings.upk",
            "EngineDebugMaterials.upk",     "EngineMaterials.upk",
            "EngineResources.upk",          "EngineVolumetrics.upk",
            "MapTemplateIndex.upk",         "MapTemplates.upk",
            "mods.upk",                     "NodeBuddies.upk"
        };

                                                                               
                                                                              
                                                                   
        std::string mapPrefix;
        if (!KingModReadPackagePrefix(mapSource, mapPrefix))
        {
            error = "Could not inspect the map dependencies";
            return false;
        }

                                                                            
                                                                               
                                                                              
                      
        std::unordered_set<std::string> bundledPackages;
        const fs::path sourceDirectory = mapSource.parent_path();
        const fs::path workshopRoot =
            fs::path(GameEventHookModule::GetWorkshopDirectory());
        const fs::path customMapsRoot = fs::path(KingModGetCustomMapsDirectory());
        std::string normalizedSourceDirectory = KingModLowerAscii(
            sourceDirectory.lexically_normal().string());
        std::replace(normalizedSourceDirectory.begin(),
                     normalizedSourceDirectory.end(), '/', '\\');
        const bool scopedSourceDirectory =
            (KingModPathIsInside(sourceDirectory, workshopRoot) &&
             sourceDirectory != workshopRoot) ||
            (KingModPathIsInside(sourceDirectory, customMapsRoot) &&
             sourceDirectory != customMapsRoot) ||
            normalizedSourceDirectory.find(
                "\\steamapps\\workshop\\content\\252950\\") !=
                std::string::npos;
        if (scopedSourceDirectory)
        {
            std::error_code scanError;
            for (auto it = fs::recursive_directory_iterator(
                     sourceDirectory,
                     fs::directory_options::skip_permission_denied, scanError);
                 it != fs::recursive_directory_iterator(); it.increment(scanError))
            {
                if (scanError) { scanError.clear(); continue; }
                if (!it->is_regular_file(scanError) || scanError)
                {
                    scanError.clear();
                    continue;
                }
                const std::string leaf = KingModLowerAscii(
                    it->path().filename().string());
                if (!KingModIsSharedWorkshopPackage(leaf)) continue;

                std::string ignoredPrefix;
                if (KingModReadPackagePrefix(it->path(), ignoredPrefix))
                    bundledPackages.insert(leaf);
            }
        }

        bool needsSharedPack = false;
        for (const char* package : kPackages)
        {
            std::string objectName(package);
            const size_t dot = objectName.rfind('.');
            if (dot != std::string::npos) objectName.resize(dot);

            if (mapPrefix.find(objectName) == std::string::npos) continue;

            std::string installedPrefix;
            if (!KingModReadPackagePrefix(cookedDir / package, installedPrefix) &&
                bundledPackages.find(KingModLowerAscii(package)) ==
                    bundledPackages.end())
            {
                needsSharedPack = true;
                break;
            }
        }
        if (!needsSharedPack) return true;

        const fs::path assetDir =
            fs::path(GameEventHookModule::GetWorkshopDirectory()) / "shared_assets";
        std::error_code ec;
        fs::create_directories(assetDir, ec);
        if (ec)
        {
            error = "Could not create the shared map-assets folder: " + ec.message();
            return false;
        }

        const fs::path archive = assetDir / "Workshop-textures.zip";
        std::vector<KingModZipEntry> entries;
        if (!KingModZipList(archive.string(), entries))
        {
                                                                          
                                                                               
                                                                           
            const std::string drivePageUrl =
                "https://drive.google.com/uc?export=download&id="
                "18iAaBRPS1WDMuwTQ1gqWxmPUCsd2cvJ_";
            std::string page;
            if (!KingModHttpGetString(drivePageUrl, page, 30))
            {
                error = "Could not reach the shared map-assets download";
                return false;
            }

            const std::string marker = "name=\"uuid\" value=\"";
            const size_t uuidStart = page.find(marker);
            const size_t uuidEnd = uuidStart == std::string::npos
                ? std::string::npos
                : page.find('"', uuidStart + marker.size());
            if (uuidStart == std::string::npos || uuidEnd == std::string::npos)
            {
                error = "The shared map-assets download link changed";
                return false;
            }

            const std::string uuid = page.substr(
                uuidStart + marker.size(),
                uuidEnd - (uuidStart + marker.size()));
            const std::string downloadUrl =
                "https://drive.usercontent.google.com/download?id="
                "18iAaBRPS1WDMuwTQ1gqWxmPUCsd2cvJ_&export=download&confirm=t&uuid=" +
                uuid;

            std::vector<uint8_t> bytes;
            if (!KingModHttpGetBytes(downloadUrl, bytes, std::string(), 300) ||
                KingModDetectWorkshopDownloadExtension(bytes) != ".zip")
            {
                error = "Shared map-assets download failed";
                return false;
            }

            const fs::path temporaryArchive =
                assetDir / "Workshop-textures.kingmod-staging.tmp";
            std::ofstream output(temporaryArchive, std::ios::binary | std::ios::trunc);
            if (!output.good())
            {
                error = "Could not save the shared map-assets archive";
                return false;
            }
            output.write(reinterpret_cast<const char*>(bytes.data()),
                         static_cast<std::streamsize>(bytes.size()));
            output.close();
            bytes.clear();

            if (!MoveFileExW(temporaryArchive.c_str(), archive.c_str(),
                             MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) ||
                !KingModZipList(archive.string(), entries))
            {
                std::error_code cleanupError;
                fs::remove(temporaryArchive, cleanupError);
                error = "Shared map-assets archive is invalid";
                return false;
            }
        }

        int installed = 0;
        for (const KingModZipEntry& entry : entries)
        {
            const std::string leaf = KingModLeafName(entry.name);
            if (!KingModIsSharedWorkshopPackage(leaf)) continue;

            const fs::path target = cookedDir / leaf;
            std::string installedPrefix;
            if (KingModReadPackagePrefix(target, installedPrefix))
                continue;

            const fs::path temporary =
                cookedDir / (leaf + ".kingmod-assets.tmp");
            if (!KingModZipExtractEntry(archive.string(), entry, temporary.string()))
            {
                std::error_code cleanupError;
                fs::remove(temporary, cleanupError);
                error = "Could not extract shared package " + leaf;
                return false;
            }

            std::string prefix;
            if (!KingModReadPackagePrefix(temporary, prefix) ||
                !MoveFileExW(temporary.c_str(), target.c_str(),
                             MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
            {
                std::error_code cleanupError;
                fs::remove(temporary, cleanupError);
                error = "Could not install shared package " + leaf;
                return false;
            }
            ++installed;
        }

                                                                              
                                                                              
        for (const char* package : kPackages)
        {
            std::string objectName(package);
            const size_t dot = objectName.rfind('.');
            if (dot != std::string::npos) objectName.resize(dot);
            if (mapPrefix.find(objectName) == std::string::npos) continue;

            std::string installedPrefix;
            if (!KingModReadPackagePrefix(cookedDir / package, installedPrefix) &&
                bundledPackages.find(KingModLowerAscii(package)) ==
                    bundledPackages.end())
            {
                error = "Shared map dependency is missing: " + std::string(package);
                return false;
            }
        }
        (void)installed;
        return true;
    }

    bool KingModPathIsInside(const fs::path& child, const fs::path& parent)
    {
        std::error_code childError;
        std::error_code parentError;
        const fs::path normalizedChild = fs::weakly_canonical(child, childError);
        const fs::path normalizedParent = fs::weakly_canonical(parent, parentError);
        if (childError || parentError) return false;

        auto childIt = normalizedChild.begin();
        auto parentIt = normalizedParent.begin();
        for (; parentIt != normalizedParent.end(); ++parentIt, ++childIt)
        {
            if (childIt == normalizedChild.end() || *childIt != *parentIt)
                return false;
        }
        return true;
    }

    bool KingModFilesMatchForStaging(const fs::path& left,
                                     const fs::path& right)
    {
        std::error_code ec;
        const uintmax_t leftSize = fs::file_size(left, ec);
        if (ec) return false;
        const uintmax_t rightSize = fs::file_size(right, ec);
        if (ec || leftSize != rightSize) return false;
        if (leftSize == 0) return true;

        std::ifstream a(left, std::ios::binary);
        std::ifstream b(right, std::ios::binary);
        if (!a.good() || !b.good()) return false;

        const size_t sampleSize = static_cast<size_t>((std::min)(
            leftSize, static_cast<uintmax_t>(64 * 1024)));
        std::vector<char> aSample(sampleSize);
        std::vector<char> bSample(sampleSize);
        auto samplesMatchAt = [&](uintmax_t offset) -> bool
        {
            a.clear();
            b.clear();
            a.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
            b.seekg(static_cast<std::streamoff>(offset), std::ios::beg);
            a.read(aSample.data(), static_cast<std::streamsize>(sampleSize));
            b.read(bSample.data(), static_cast<std::streamsize>(sampleSize));
            return a.gcount() == static_cast<std::streamsize>(sampleSize) &&
                   b.gcount() == static_cast<std::streamsize>(sampleSize) &&
                   memcmp(aSample.data(), bSample.data(), sampleSize) == 0;
        };

        if (!samplesMatchAt(0)) return false;
        return leftSize <= sampleSize ||
               samplesMatchAt(leftSize - sampleSize);
    }

    bool KingModStageWorkshopFile(const fs::path& source,
                                  const fs::path& target,
                                  std::string& error)
    {
        error.clear();
        std::error_code ec;
        if (!fs::is_regular_file(source, ec) || ec)
        {
            error = "Map package is missing: " + source.filename().string();
            return false;
        }

        if (fs::exists(target, ec) && !ec)
        {
            std::error_code equivalentError;
            if (fs::equivalent(source, target, equivalentError) && !equivalentError)
                return true;

                                                                              
                                                                                
                                                                               
            if (KingModFilesMatchForStaging(source, target))
                return true;
        }
        else if (ec)
        {
            error = "Could not inspect " + target.filename().string() + ": " + ec.message();
            return false;
        }

        const fs::path temporary =
            target.parent_path() / (target.filename().string() + ".kingmod-staging.tmp");
        fs::copy_file(source, temporary, fs::copy_options::overwrite_existing, ec);
        if (ec)
        {
            error = "Could not stage " + source.filename().string() + ": " + ec.message();
            return false;
        }

        if (fs::exists(target, ec) && !ec)
        {
            const fs::path backupDir =
                fs::path(GameEventHookModule::GetWorkshopDirectory()) /
                "staged_backups";
            fs::create_directories(backupDir, ec);
            if (ec)
            {
                std::error_code cleanupError;
                fs::remove(temporary, cleanupError);
                error = "Could not create the map backup folder: " + ec.message();
                return false;
            }

            const fs::path backup =
                backupDir / (target.filename().string() + ".previous");
            if (!fs::exists(backup, ec) && !ec)
            {
                fs::copy_file(target, backup, fs::copy_options::none, ec);
                if (ec)
                {
                    std::error_code cleanupError;
                    fs::remove(temporary, cleanupError);
                    error = "Could not back up " + target.filename().string() + ": " + ec.message();
                    return false;
                }
            }
            else if (ec)
            {
                std::error_code cleanupError;
                fs::remove(temporary, cleanupError);
                error = "Could not inspect the map backup: " + ec.message();
                return false;
            }
        }

        if (!MoveFileExW(temporary.c_str(), target.c_str(),
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        {
            const DWORD moveError = GetLastError();
            std::error_code cleanupError;
            fs::remove(temporary, cleanupError);
            error = "Could not install " + target.filename().string() +
                    " (Windows error " + std::to_string(moveError) + ")";
            return false;
        }
        return true;
    }

    bool KingModStageCompleteWorkshopMap(const fs::path& source,
                                         const fs::path& cookedDir,
                                         std::string& error)
    {
        std::vector<fs::path> payloads{ source };
        const fs::path sourceDirectory = source.parent_path();
        const fs::path workshopRoot =
            fs::path(GameEventHookModule::GetWorkshopDirectory());
        const fs::path customMapsRoot = fs::path(KingModGetCustomMapsDirectory());
        std::string normalizedSourceDirectory = KingModLowerAscii(
            sourceDirectory.lexically_normal().string());
        std::replace(normalizedSourceDirectory.begin(),
                     normalizedSourceDirectory.end(), '/', '\\');
        const bool steamWorkshopDirectory =
            normalizedSourceDirectory.find(
                "\\steamapps\\workshop\\content\\252950\\") !=
            std::string::npos;

                                                                         
                                                                           
                                                                             
                                                                         
        const bool scopedPackageDirectory =
            (KingModPathIsInside(sourceDirectory, workshopRoot) &&
             sourceDirectory != workshopRoot) ||
            (KingModPathIsInside(sourceDirectory, customMapsRoot) &&
             sourceDirectory != customMapsRoot) ||
            steamWorkshopDirectory;

        if (scopedPackageDirectory)
        {
            std::error_code ec;
            for (auto it = fs::recursive_directory_iterator(
                     sourceDirectory,
                     fs::directory_options::skip_permission_denied, ec);
                 it != fs::recursive_directory_iterator(); it.increment(ec))
            {
                if (ec) { ec.clear(); continue; }
                if (!it->is_regular_file(ec) || ec) { ec.clear(); continue; }
                if (fs::equivalent(it->path(), source, ec) && !ec) continue;
                ec.clear();

                std::string lower = it->path().filename().string();
                std::transform(lower.begin(), lower.end(), lower.begin(),
                    [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                if (!KingModIsWorkshopPayloadExtension(lower)) continue;

                                                                             
                                                                             
                std::string extension = it->path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(),
                    [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                if (extension != ".tfc")
                {
                    std::string ignoredPrefix;
                    if (!KingModReadPackagePrefix(it->path(), ignoredPrefix))
                        continue;
                }
                payloads.push_back(it->path());
            }
        }

        std::unordered_set<std::string> stagedTargets;
        for (const fs::path& payload : payloads)
        {
            std::string extension = payload.extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });

            fs::path targetName = payload.filename();
            if (extension == ".udk") targetName.replace_extension(".upk");

            std::string targetKey = targetName.string();
            std::transform(targetKey.begin(), targetKey.end(), targetKey.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (!stagedTargets.insert(targetKey).second) continue;

            if (!KingModStageWorkshopFile(payload, cookedDir / targetName, error))
                return false;
        }
        return true;
    }

    bool KingModStageWorkshopAlias(const fs::path& source,
                                   const fs::path& cookedDir,
                                   std::string& packageName,
                                   std::string& error)
    {
        static const char* candidates[] = {
            "Labs_Underpass_P.upk",
            "Labs_CirclePillars_P.upk",
            "Labs_Cosmic_V4_P.upk"
        };

        fs::path target;
        std::error_code ec;
        for (const char* candidate : candidates)
        {
            const fs::path installed = cookedDir / candidate;
            if (fs::is_regular_file(installed, ec) && !ec)
            {
                target = installed;
                break;
            }
            ec.clear();
        }
        if (target.empty())
        {
            error = "Rocket League's standard Labs map package is missing";
            return false;
        }

        const fs::path backupDir =
            fs::path(GameEventHookModule::GetWorkshopDirectory()) /
            "staged_backups";
        fs::create_directories(backupDir, ec);
        if (ec)
        {
            error = "Could not create the Workshop map backup folder: " + ec.message();
            return false;
        }

        const fs::path backup = backupDir /
            (target.filename().string() + ".kingmod-original");
        if (!fs::is_regular_file(backup, ec) || ec)
        {
            ec.clear();
            const fs::path previous = backupDir /
                (target.filename().string() + ".previous");
            const fs::path original =
                fs::is_regular_file(previous, ec) && !ec ? previous : target;
            ec.clear();
            fs::copy_file(original, backup, fs::copy_options::none, ec);
            if (ec)
            {
                error = "Could not back up " + target.filename().string() + ": " + ec.message();
                return false;
            }
        }

        const fs::path temporary = target.parent_path() /
            (target.filename().string() + ".kingmod-workshop.tmp");
        fs::copy_file(source, temporary, fs::copy_options::overwrite_existing, ec);
        if (ec)
        {
            error = "Could not prepare the Workshop map alias: " + ec.message();
            return false;
        }

        if (!MoveFileExW(temporary.c_str(), target.c_str(),
                         MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
        {
            const DWORD moveError = GetLastError();
            std::error_code cleanupError;
            fs::remove(temporary, cleanupError);
            error = "Could not activate the Workshop map (Windows error " +
                    std::to_string(moveError) + ")";
            return false;
        }

        {
            std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
            g_WorkshopAliasTarget = target;
            g_WorkshopAliasBackup = backup;
        }
        packageName = target.stem().string();
        return true;
    }

    void KingModRecoverWorkshopAliasOnStartup()
    {
        {
            std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
            if (g_WorkshopAliasRecoveryRunning)
                return;
            g_WorkshopAliasRecoveryRunning = true;
        }

        try
        {
            std::thread([]()
            {
                GameEventHookModule::ScopedWorker worker;
                static const char* candidates[] = {
                    "Labs_Underpass_P.upk",
                    "Labs_CirclePillars_P.upk",
                    "Labs_Cosmic_V4_P.upk"
                };

                const fs::path cookedDir = KingModGetCookedPackageDirectory();
                const fs::path backupDir =
                    fs::path(GameEventHookModule::GetWorkshopDirectory()) /
                    "staged_backups";

                std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
                for (const char* candidate : candidates)
                {
                    const fs::path target = cookedDir / candidate;
                    const fs::path backup = backupDir /
                        (std::string(candidate) + ".kingmod-original");
                    std::error_code ec;
                    if (cookedDir.empty() ||
                        !fs::is_regular_file(target, ec) || ec ||
                        !fs::is_regular_file(backup, ec) || ec ||
                        KingModFilesMatchForStaging(target, backup))
                        continue;

                    const fs::path temporary = target.parent_path() /
                        (target.filename().string() + ".kingmod-recovery.tmp");
                    fs::copy_file(backup, temporary,
                                  fs::copy_options::overwrite_existing, ec);
                    if (!ec && MoveFileExW(
                            temporary.c_str(), target.c_str(),
                            MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
                        continue;

                    std::error_code cleanupError;
                    fs::remove(temporary, cleanupError);
                }
                g_WorkshopAliasRecoveryRunning = false;
            }).detach();
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
            g_WorkshopAliasRecoveryRunning = false;
        }
    }

    void KingModRestoreWorkshopAliasAfterTravel()
    {
        fs::path target;
        fs::path backup;
        {
            std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
            if (g_WorkshopAliasRestoreRunning ||
                g_WorkshopAliasTarget.empty() || g_WorkshopAliasBackup.empty())
                return;
            g_WorkshopAliasRestoreRunning = true;
            target = g_WorkshopAliasTarget;
            backup = g_WorkshopAliasBackup;
        }

        try
        {
            std::thread([target, backup]()
            {
                GameEventHookModule::ScopedWorker worker;
                std::error_code ec;
                const fs::path temporary = target.parent_path() /
                    (target.filename().string() + ".kingmod-restore.tmp");
                fs::copy_file(backup, temporary,
                              fs::copy_options::overwrite_existing, ec);
                bool restored = false;
                if (!ec)
                {
                    restored = MoveFileExW(
                        temporary.c_str(), target.c_str(),
                        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH) != FALSE;
                }
                if (!restored)
                {
                    std::error_code cleanupError;
                    fs::remove(temporary, cleanupError);
                }

                std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
                g_WorkshopAliasRestoreRunning = false;
                if (restored)
                {
                    g_WorkshopAliasTarget.clear();
                    g_WorkshopAliasBackup.clear();
                }
            }).detach();
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lock(g_WorkshopAliasMutex);
            g_WorkshopAliasRestoreRunning = false;
        }
    }

    std::string KingModUrlEncode(const std::string& in)
    {
        static const char* hex = "0123456789ABCDEF";
        std::string out;
        for (unsigned char c : in)
        {
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~')
                out.push_back(static_cast<char>(c));
            else if (c == ' ')
                out.push_back('+');
            else
            {
                out.push_back('%');
                out.push_back(hex[c >> 4]);
                out.push_back(hex[c & 0x0F]);
            }
        }
        return out;
    }

                                                               
    std::string KingModSanitizeFileName(const std::string& in)
    {
        std::string out;
        for (char c : in)
        {
            if (strchr("\\/:*?\"<>|", c) != nullptr || static_cast<unsigned char>(c) < 0x20)
                out.push_back('_');
            else
                out.push_back(c);
        }
        while (!out.empty() && (out.back() == ' ' || out.back() == '.'))
            out.pop_back();
        if (out.empty()) out = "map";
        if (out.size() > 96) out.resize(96);
        return out;
    }

                                                                           
                                                                                  
                                                                                
    std::vector<std::string> KingModParseWorkshopIds(const std::string& html)
    {
        std::vector<std::string> ids;
        std::unordered_set<std::string> seen;
        const std::string needle = "filedetails/?id=";
        size_t pos = 0;
        while ((pos = html.find(needle, pos)) != std::string::npos)
        {
            pos += needle.size();
            size_t end = pos;
            while (end < html.size() && isdigit(static_cast<unsigned char>(html[end])))
                ++end;
            if (end > pos)
            {
                std::string id = html.substr(pos, end - pos);
                if (seen.insert(id).second)
                    ids.push_back(id);
            }
            pos = end;
        }
        return ids;
    }

                                                                             
                                                                            
                                                                             
                                                                                
                                                                            
                                                                              
                                             
    std::string KingModUnescapeFlight(const std::string& in)
    {
        std::string out;
        out.reserve(in.size());
        for (size_t i = 0; i < in.size(); ++i)
        {
            if (in[i] == '\\' && i + 1 < in.size())
            {
                const char n = in[i + 1];
                if (n == '"' || n == '\\' || n == '/') { out.push_back(n); ++i; continue; }
                if (n == 'n' || n == 'r' || n == 't')    { out.push_back(' '); ++i; continue; }
                if (n == 'u' && i + 5 < in.size())
                {
                                                                              
                                                                             
                    const std::string hex = in.substr(i + 2, 4);
                    long cp = strtol(hex.c_str(), nullptr, 16);
                    out.push_back(cp >= 32 && cp < 127 ? static_cast<char>(cp) : '?');
                    i += 5;
                    continue;
                }
            }
            out.push_back(in[i]);
        }
        return out;
    }

    std::string KingModNormalizePreviewUrl(std::string url)
    {
        auto trimQuotes = [&url]()
        {
            while (!url.empty() && (url.front() == ' ' || url.front() == '\'' || url.front() == '"')) url.erase(url.begin());
            while (!url.empty() && (url.back() == ' ' || url.back() == '\'' || url.back() == '"')) url.pop_back();
        };

        trimQuotes();
        if (url.rfind("url(", 0) == 0 && !url.empty() && url.back() == ')')
        {
            url = url.substr(4, url.size() - 5);
            trimQuotes();
        }

                                                                       
                                                                               
        size_t at = 0;
        while ((at = url.find("\\/", at)) != std::string::npos) url.replace(at, 2, "/");
        at = 0; while ((at = url.find("\\u0026", at)) != std::string::npos) url.replace(at, 6, "&");
        at = 0; while ((at = url.find("\\u003d", at)) != std::string::npos) url.replace(at, 6, "=");
        at = 0; while ((at = url.find("&amp;", at)) != std::string::npos) url.replace(at, 5, "&");

        if (url.rfind("//", 0) == 0) url = "https:" + url;
        else if (!url.empty() && url[0] == '/') url = "https://bakkesplugins.com" + url;
        return url;
    }

    std::string KingModFindImageUrlInRange(const std::string& text, size_t from, size_t to)
    {
        static const char* keys[] = {
            "\"previewUrl\":\"", "\"preview_url\":\"", "\"previewImage\":\"",
            "\"preview_image\":\"", "\"imageUrl\":\"", "\"image_url\":\"",
            "\"thumbnailUrl\":\"", "\"thumbnail_url\":\"", "\"image\":\""
        };
        for (const char* key : keys)
        {
            const size_t at = text.find(key, from);
            if (at == std::string::npos || at >= to) continue;
            const size_t st = at + strlen(key);
            const size_t en = text.find('"', st);
            if (en != std::string::npos && en < to)
            {
                std::string u = KingModNormalizePreviewUrl(text.substr(st, en - st));
                if (!u.empty()) return u;
            }
        }

                                                                                
                                                                              
                                                            
        static const char* starts[] = {
            "https://cdn.bakkesplugins.com/", "https://bakkesplugins.com/", "/_next/image?url=",
            "https:\\/\\/cdn.bakkesplugins.com\\/", "https:\\/\\/bakkesplugins.com\\/"
        };
        for (const char* needle : starts)
        {
            size_t pos = text.find(needle, from);
            while (pos != std::string::npos && pos < to)
            {
                size_t en = text.find_first_of("\"'<> \\)\r\n", pos);
                if (en == std::string::npos || en > to) en = to;
                std::string u = KingModNormalizePreviewUrl(text.substr(pos, en - pos));
                std::string low = u;
                std::transform(low.begin(), low.end(), low.begin(), [](unsigned char c){ return (char)std::tolower(c); });
                if (low.find(".jpg") != std::string::npos || low.find(".jpeg") != std::string::npos ||
                    low.find(".png") != std::string::npos || low.find(".webp") != std::string::npos ||
                    low.find("/_next/image?") != std::string::npos)
                    return u;
                pos = text.find(needle, en);
            }
        }
        return {};
    }

                                                                      
    std::string KingModValueAfter(const std::string& text, size_t from, size_t to,
                                  const std::string& marker)
    {
        const size_t at = text.find(marker, from);
        if (at == std::string::npos || at >= to) return std::string();
        const size_t start = at + marker.size();
        const size_t end = text.find('"', start);
        if (end == std::string::npos || end > to) return std::string();
        return text.substr(start, end - start);
    }

                                                                             
                                                                            
                                                                          
                                                                          
                                   
    std::string KingModFindBakkesArchiveUrl(const std::string& text)
    {
        static const std::string needle = "https://cdn.bakkesplugins.com/uploads/";
        size_t pos = 0;
        while ((pos = text.find(needle, pos)) != std::string::npos)
        {
            const size_t start = pos;
            size_t end = text.find_first_of("\"'<> \t\r\n\\)", start);
            if (end == std::string::npos) end = text.size();
            const std::string candidate = text.substr(start, end - start);

            std::string lowered = candidate;
            std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (lowered.find(".zip") != std::string::npos ||
                lowered.find(".rar") != std::string::npos ||
                lowered.find(".7z")  != std::string::npos ||
                lowered.find(".upk") != std::string::npos ||
                lowered.find(".udk") != std::string::npos)
                return candidate;

            pos = end;
        }
        return std::string();
    }

                                                                       
                                                                          
                                                                           
                                                
    bool KingModParseBakkesApi(const std::string& rawJson,
                               std::vector<GameEventHookModule::WorkshopItem>& out,
                               int* outMaxId)
    {
        out.clear();
        const nlohmann::json root = nlohmann::json::parse(rawJson, nullptr, false);
        if (root.is_discarded() || !root.is_object()) return false;

        const nlohmann::json* rows = nullptr;
        if (root.contains("data") && root["data"].is_array()) rows = &root["data"];
        else if (root.contains("maps") && root["maps"].is_array()) rows = &root["maps"];
        if (!rows) return false;

        for (const nlohmann::json& row : *rows)
        {
            if (!row.is_object()) continue;
            const auto textValue = [&row](const char* key) -> std::string
            {
                const auto it = row.find(key);
                return it != row.end() && it->is_string()
                    ? it->get<std::string>()
                    : std::string();
            };

            std::string id;
            if (row.contains("id"))
            {
                if (row["id"].is_string()) id = row["id"].get<std::string>();
                else if (row["id"].is_number_integer())
                    id = std::to_string(row["id"].get<long long>());
            }
            if (id.empty()) continue;

            GameEventHookModule::WorkshopItem item;
            item.source      = 1;
            item.id          = id;
            item.pageUrl     = "https://bakkesplugins.com/maps/" + id;
            item.fileUrl     = textValue("download_url");
            if (item.fileUrl.empty()) item.fileUrl = textValue("downloadUrl");
            if (item.fileUrl.empty()) item.fileUrl = textValue("file_url");
            if (item.fileUrl.empty()) item.fileUrl = textValue("fileUrl");
            if (item.fileUrl.empty()) item.fileUrl = item.pageUrl + "/download";
            item.fileName    = textValue("filename");
            if (item.fileName.empty()) item.fileName = textValue("fileName");
            item.title       = textValue("name");
            if (item.title.empty()) item.title = textValue("title");
            item.author      = textValue("author");
            item.description = textValue("description");
            item.previewUrl  = textValue("preview_image");
            if (item.previewUrl.empty()) item.previewUrl = textValue("preview_url");
            if (item.previewUrl.empty()) item.previewUrl = textValue("previewUrl");
            if (item.previewUrl.empty()) item.previewUrl = textValue("imageUrl");
            if (row.contains("downloads") && row["downloads"].is_number_integer())
                item.subscriptions = row["downloads"].get<int>();
            else if (row.contains("downloadCount") && row["downloadCount"].is_number_integer())
                item.subscriptions = row["downloadCount"].get<int>();
            if (item.title.empty()) item.title = "Map " + id;

            if (outMaxId)
            {
                const int number = atoi(id.c_str());
                if (number > *outMaxId) *outMaxId = number;
            }
            out.push_back(std::move(item));
        }
        return !out.empty();
    }

                                           
                                                                              
                                                          
                                                        
                                                           
                                                              
                                                                 
    std::vector<GameEventHookModule::WorkshopItem>
    KingModParseBakkesMaps(const std::string& rawHtml, int* outMaxId)
    {
        std::vector<GameEventHookModule::WorkshopItem> items;
        const std::string text = KingModUnescapeFlight(rawHtml);

                                                 
        std::vector<std::pair<size_t, std::string>> cards;
        const std::string needle = "\"href\":\"/maps/";
        size_t pos = 0;
        while ((pos = text.find(needle, pos)) != std::string::npos)
        {
            const size_t idStart = pos + needle.size();
            size_t idEnd = idStart;
            while (idEnd < text.size() && isdigit(static_cast<unsigned char>(text[idEnd])))
                ++idEnd;
            if (idEnd > idStart)
            {
                const std::string id = text.substr(idStart, idEnd - idStart);
                if (outMaxId)
                {
                    const int n = atoi(id.c_str());
                    if (n > *outMaxId) *outMaxId = n;
                }
                cards.push_back({ pos, id });
            }
            pos = idEnd;
        }

        std::unordered_set<std::string> seen;
        for (size_t c = 0; c < cards.size(); ++c)
        {
            const size_t from = cards[c].first;
            const size_t to = (c + 1 < cards.size()) ? cards[c + 1].first : text.size();
            const std::string& id = cards[c].second;
            if (!seen.insert(id).second) continue;

            GameEventHookModule::WorkshopItem item;
            item.source  = 1;
            item.id      = id;
            item.pageUrl = "https://bakkesplugins.com/maps/" + id;
            item.fileUrl = KingModValueAfter(text, from, to, "\"downloadUrl\":\"");
            if (item.fileUrl.empty())
                item.fileUrl = KingModValueAfter(text, from, to, "\"download_url\":\"");
            if (item.fileUrl.empty())
                item.fileUrl = KingModValueAfter(text, from, to, "\"fileUrl\":\"");
            if (item.fileUrl.empty())
                item.fileUrl = item.pageUrl + "/download";
            item.fileName = KingModValueAfter(text, from, to, "\"fileName\":\"");
            if (item.fileName.empty()) item.fileName = id + ".zip";
                                                                              
                                     
            {
                const size_t h2 = text.find("\"h2\",null,", from);
                if (h2 != std::string::npos && h2 < to)
                    item.title = KingModValueAfter(text, h2, to, "\"children\":\"");
                else
                    item.title.clear();
            }
            {
                const size_t bg = text.find("\"backgroundImage\":\"url(", from);
                if (bg != std::string::npos && bg < to)
                {
                    const size_t start = bg + strlen("\"backgroundImage\":\"url(");
                    const size_t end = text.find(')', start);
                    if (end != std::string::npos && end < to)
                        item.previewUrl = text.substr(start, end - start);
                }
            }
            if (item.previewUrl.empty())
                item.previewUrl = KingModFindImageUrlInRange(text, from, to);
            item.previewUrl = KingModNormalizePreviewUrl(item.previewUrl);
            item.author = KingModValueAfter(text, from, to, "\"title\":\"");
            {
                const size_t pTag = text.find("\"p\",null,", from);
                if (pTag != std::string::npos && pTag < to)
                    item.description = KingModValueAfter(text, pTag, to, "\"children\":\"");
            }
            {
                const size_t dl = text.find("\" downloads\"", from);
                if (dl != std::string::npos && dl < to)
                {
                                                                                 
                                                  
                    size_t q = text.rfind("\",\"", dl);
                    if (q != std::string::npos && q > from)
                    {
                        const size_t open = text.rfind('"', q - 1);
                        if (open != std::string::npos && open > from)
                        {
                            std::string count = text.substr(open + 1, q - open - 1);
                            double v = atof(count.c_str());
                            if (!count.empty() && (count.back() == 'K' || count.back() == 'k')) v *= 1000.0;
                            if (!count.empty() && (count.back() == 'M' || count.back() == 'm')) v *= 1000000.0;
                            item.subscriptions = static_cast<int>(v);
                        }
                    }
                }
            }

            if (item.title.empty()) item.title = "Map " + id;
            items.push_back(std::move(item));
        }
        return items;
    }

                                                                                
                                           
    bool KingModParseBakkesDetail(const std::string& rawHtml, const std::string& id,
                                  GameEventHookModule::WorkshopItem& out)
    {
        const std::string text = KingModUnescapeFlight(rawHtml);
        auto meta = [&text](const std::string& key) -> std::string
        {
                                           
            const std::string marker = "\"" + key + "\",\"content\":\"";
            size_t at = text.find(marker);
            if (at != std::string::npos)
            {
                const size_t st = at + marker.size();
                const size_t en = text.find('"', st);
                if (en != std::string::npos) return text.substr(st, en - st);
            }
                                                                                  
            const std::string p1 = "property=\"" + key + "\"";
            at = text.find(p1);
            if (at == std::string::npos) at = text.find("name=\"" + key + "\"");
            if (at != std::string::npos)
            {
                const size_t tagEnd = text.find('>', at);
                const size_t c = text.find("content=\"", at);
                if (c != std::string::npos && (tagEnd == std::string::npos || c < tagEnd))
                {
                    const size_t st = c + 9;
                    const size_t en = text.find('"', st);
                    if (en != std::string::npos) return text.substr(st, en - st);
                }
            }
            const std::string contentFirst = "content=\"";
            size_t scan = 0;
            while ((scan = text.find(contentFirst, scan)) != std::string::npos)
            {
                const size_t tagEnd = text.find('>', scan);
                if (tagEnd == std::string::npos) break;
                const std::string tag = text.substr(scan, tagEnd - scan);
                if (tag.find("property=\"" + key + "\"") != std::string::npos ||
                    tag.find("name=\"" + key + "\"") != std::string::npos)
                {
                    const size_t st = scan + contentFirst.size();
                    const size_t en = text.find('"', st);
                    if (en != std::string::npos) return text.substr(st, en - st);
                }
                scan = tagEnd + 1;
            }
            return {};
        };
        const auto jsonValue = [&text](std::initializer_list<const char*> keys) -> std::string
        {
            for (const char* key : keys)
            {
                const std::string marker = std::string("\"") + key + "\":\"";
                const size_t at = text.find(marker);
                if (at == std::string::npos) continue;
                const size_t start = at + marker.size();
                const size_t end = text.find('"', start);
                if (end != std::string::npos)
                    return text.substr(start, end - start);
            }
            return std::string();
        };

        out = GameEventHookModule::WorkshopItem();
        out.source      = 1;
        out.id          = id;
        out.pageUrl     = "https://bakkesplugins.com/maps/" + id;
        out.fileUrl     = KingModFindBakkesArchiveUrl(text);
        if (out.fileUrl.empty())
            out.fileUrl = jsonValue({ "downloadUrl", "download_url", "fileUrl", "file_url" });
        if (out.fileUrl.empty()) out.fileUrl = out.pageUrl + "/download";
        out.fileName    = jsonValue({ "fileName", "filename" });
        if (out.fileName.empty()) out.fileName = id + ".zip";
        out.title       = meta("og:title");
        if (out.title.empty()) out.title = jsonValue({ "name", "title" });
        out.description = meta("og:description");
        out.previewUrl  = jsonValue({ "previewUrl", "preview_url", "previewImage", "preview_image" });
        if (out.previewUrl.empty()) out.previewUrl = meta("og:image");
        if (out.previewUrl.empty()) out.previewUrl = KingModFindImageUrlInRange(text, 0, text.size());
        out.previewUrl = KingModNormalizePreviewUrl(out.previewUrl);
        out.author      = meta("author");
        return !out.title.empty();
    }

                                                                             
                                                                              
                                                                             
                                                                         
    bool KingModResolveSteamDownloadUrl(const std::string& id, std::string& url,
                                        std::string& fileName)
    {
        url.clear();
        fileName.clear();
        if (id.empty()) return false;

        std::string body;
        const std::string form = "itemcount=1&publishedfileids[0]=" + id;
        if (!KingModHttpPostString(
                "https://api.steampowered.com/ISteamRemoteStorage/GetPublishedFileDetails/v1/",
                form, body))
            return false;

        const nlohmann::json root = nlohmann::json::parse(body, nullptr, false);
        if (root.is_discarded() || !root.contains("response"))
            return false;
        const nlohmann::json& details = root["response"]["publishedfiledetails"];
        if (!details.is_array() || details.empty() || !details[0].is_object())
            return false;

        const nlohmann::json& detail = details[0];
        if (detail.value("result", 0) != 1)
            return false;

        url = detail.value("file_url", std::string());
        fileName = detail.value("filename", std::string());
        return !url.empty();
    }
}

void GameEventHookModule::RefreshWorkshopBrowse(int page)
{
    if (g_WorkshopFetchRunning.load())
        return;

    if (page < 1) page = 1;
    WorkshopBrowsePage = page;
    WorkshopBrowseLoading = true;
    WorkshopBrowseError.clear();

    const int sort = WorkshopBrowseSort;
                                                                             
                               
    const int source = 1;
    const std::string search = WorkshopBrowseSearch;

    g_WorkshopFetchRunning.store(true);
    std::thread([page, sort, source, search]()
    {
        GameEventHookModule::ScopedWorker worker;
        std::vector<WorkshopItem> items;
        std::string error;

        if (source == 1)
        {
                                                                            
            try
            {
                const std::string workshopDir = GetWorkshopDirectory();
                int maxId = GameEventHookModule::WorkshopBpMaxId;

                bool numericSearch = !search.empty();
                for (char c : search)
                    if (!isdigit(static_cast<unsigned char>(c))) { numericSearch = false; break; }

                if (numericSearch)
                {
                                                                                
                                                                             
                    std::string html;
                    if (!KingModHttpGetString("https://bakkesplugins.com/maps/" + search, html))
                        throw std::runtime_error("Could not reach bakkesplugins.com: " + g_KingModHttpError);
                    WorkshopItem one;
                    if (!KingModParseBakkesDetail(html, search, one))
                        throw std::runtime_error("No map with id " + search);
                    items.push_back(std::move(one));
                }
                else
                {
                    const char* sortKeys[] = { "", "newest", "rating" };
                    const char* sortKey = sortKeys[(sort >= 0 && sort < 3) ? sort : 0];

                                                                               
                                                                             
                                                                              
                                             
                    std::string url = "https://bakkesplugins.com/maps?page=" +
                                      std::to_string(page);
                    if (sortKey[0] != '\0') url += "&sortBy=" + std::string(sortKey);
                    if (!search.empty())    url += "&search=" + KingModUrlEncode(search);

                    std::string html;
                    if (!KingModHttpGetString(url, html))
                        throw std::runtime_error("Could not reach bakkesplugins.com: " +
                                                 g_KingModHttpError);
                    items = KingModParseBakkesMaps(html, &maxId);

                                                                                 
                                                                             
                    if (!search.empty())
                    {
                        const std::string want = KingModLowerAscii(search);
                        std::vector<WorkshopItem> hits;
                        for (WorkshopItem& it : items)
                        {
                            if (KingModLowerAscii(it.title).find(want) != std::string::npos ||
                                KingModLowerAscii(it.author).find(want) != std::string::npos ||
                                KingModLowerAscii(it.description).find(want) != std::string::npos)
                                hits.push_back(std::move(it));
                        }
                        if (!hits.empty()) items = std::move(hits);
                    }

                    if (items.empty())
                        throw std::runtime_error("No maps on that page");
                }

                                                                                   
                                                          
                if (maxId <= 0)
                {
                    std::string newest;
                    if (KingModHttpGetString("https://bakkesplugins.com/maps?sortBy=newest", newest))
                        KingModParseBakkesMaps(newest, &maxId);
                }
                GameEventHookModule::WorkshopBpMaxId = maxId;

                for (WorkshopItem& item : items)
                {
                    std::error_code ec;
                    for (auto it = fs::directory_iterator(workshopDir, ec);
                         it != fs::directory_iterator(); it.increment(ec))
                    {
                        if (ec) break;
                        const std::string name = it->path().filename().string();
                        if (name.rfind(item.id + "_", 0) == 0) { item.installed = true; break; }
                    }
                }
            }
            catch (const std::exception& e) { error = e.what(); }
            catch (...)                     { error = "Map provider fetch failed"; }

            {
                std::lock_guard<std::mutex> lock(g_WorkshopMutex);
                g_WorkshopStaging      = std::move(items);
                g_WorkshopStagingError = error;
                g_WorkshopStagingReady = true;
            }
            g_WorkshopFetchRunning.store(false);
            return;
        }

        try
        {
            const char* sortKeys[] = { "trend", "mostrecent", "totaluniquesubscribers" };
            const char* sortKey = sortKeys[(sort >= 0 && sort < 3) ? sort : 0];

            std::string url =
                "https://steamcommunity.com/workshop/browse/?appid=252950"
                "&browsesort=" + std::string(sortKey) +
                "&section=readytouseitems"
                "&actualsort=" + std::string(sortKey) +
                "&p=" + std::to_string(page) +
                "&numperpage=30";
            if (!search.empty())
                url += "&searchtext=" + KingModUrlEncode(search);

            std::string html;
            if (!KingModHttpGetString(url, html))
                throw std::runtime_error("Could not reach steamcommunity.com: " + g_KingModHttpError);

            std::vector<std::string> ids = KingModParseWorkshopIds(html);
            if (ids.size() > 30) ids.resize(30);
            if (ids.empty())
                throw std::runtime_error("No workshop items found for that search");

                                                    
            std::string form = "itemcount=" + std::to_string(ids.size());
            for (size_t i = 0; i < ids.size(); ++i)
                form += "&publishedfileids[" + std::to_string(i) + "]=" + ids[i];

            std::string body;
            if (!KingModHttpPostString(
                    "https://api.steampowered.com/ISteamRemoteStorage/GetPublishedFileDetails/v1/",
                    form, body))
                throw std::runtime_error("Steam did not return item details: " + g_KingModHttpError);

            nlohmann::json root = nlohmann::json::parse(body, nullptr, false);
            if (root.is_discarded() || !root.contains("response"))
                throw std::runtime_error("Steam returned an unreadable reply");

            const nlohmann::json& details = root["response"]["publishedfiledetails"];
            if (!details.is_array())
                throw std::runtime_error("Steam returned no item details");

            const std::string workshopDir = GetWorkshopDirectory();

            for (const auto& d : details)
            {
                if (!d.is_object()) continue;
                if (d.value("result", 0) != 1) continue;

                WorkshopItem item;
                item.id            = d.value("publishedfileid", std::string());
                item.title         = d.value("title", std::string());
                item.description   = d.value("description", std::string());
                item.previewUrl    = d.value("preview_url", std::string());
                item.fileUrl       = d.value("file_url", std::string());
                item.fileName      = d.value("filename", std::string());
                item.subscriptions = d.value("subscriptions", 0);
                if (d.contains("file_size"))
                {
                                                                             
                    if (d["file_size"].is_number())      item.fileSize = d["file_size"].get<long long>();
                    else if (d["file_size"].is_string()) item.fileSize = atoll(d["file_size"].get<std::string>().c_str());
                }
                if (item.id.empty()) continue;
                if (item.title.empty()) item.title = "Workshop item " + item.id;

                                                                              
                std::error_code ec;
                for (auto it = fs::directory_iterator(workshopDir, ec);
                     it != fs::directory_iterator(); it.increment(ec))
                {
                    if (ec) break;
                    const std::string name = it->path().filename().string();
                    if (name.rfind(item.id, 0) == 0) { item.installed = true; break; }
                }

                items.push_back(std::move(item));
            }

            if (items.empty())
                throw std::runtime_error("Steam returned no usable items");
        }
        catch (const std::exception& e) { error = e.what(); }
        catch (...)                     { error = "Workshop fetch failed"; }

        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            g_WorkshopStaging      = std::move(items);
            g_WorkshopStagingError = error;
            g_WorkshopStagingReady = true;
        }
        g_WorkshopFetchRunning.store(false);
    }).detach();
}

void GameEventHookModule::ReleaseWorkshopPreviews()
{
    {
        std::lock_guard<std::mutex> lock(g_WorkshopMutex);
        g_WorkshopPreviewBytes.clear();
        g_WorkshopPreviewFailed.clear();
    }
    for (WorkshopItem& item : WorkshopBrowse)
    {
        if (item.previewTexture)
        {
            static_cast<ID3D11ShaderResourceView*>(item.previewTexture)->Release();
            item.previewTexture = nullptr;
        }
    }
}

void GameEventHookModule::UpdateWorkshopBrowse()
{
                                    
    {
        std::vector<WorkshopItem> incoming;
        std::string incomingError;
        bool haveIncoming = false;
        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            if (g_WorkshopStagingReady)
            {
                incoming      = std::move(g_WorkshopStaging);
                incomingError = g_WorkshopStagingError;
                g_WorkshopStaging.clear();
                g_WorkshopStagingError.clear();
                g_WorkshopStagingReady = false;
                haveIncoming = true;
            }
        }
        if (haveIncoming)
        {
            if (!incoming.empty())
            {
                ReleaseWorkshopPreviews();
                WorkshopBrowse = std::move(incoming);
            }
            WorkshopBrowseError   = incomingError;
            WorkshopBrowseLoading = false;
        }
    }

                                                                               
                                                                           
                                                        
    std::map<std::string, std::vector<uint8_t>> ready;
    {
        std::lock_guard<std::mutex> lock(g_WorkshopMutex);
        if (!g_WorkshopPreviewBytes.empty())
            ready.swap(g_WorkshopPreviewBytes);
    }
    for (auto& kv : ready)
    {
        for (WorkshopItem& item : WorkshopBrowse)
        {
            if (item.id != kv.first) continue;
            if (item.previewTexture) break;
            if (kv.second.empty()) break;
            if (ID3D11ShaderResourceView* srv =
                    menu_avatar::CreateTextureFromMemory(kv.second.data(), kv.second.size()))
            {
                item.previewTexture = srv;
            }
            else
            {
                                                                          
                                                                                  
                item.previewRequested = false;
            }
            break;
        }
    }

    std::unordered_set<std::string> failedPreviews;
    {
        std::lock_guard<std::mutex> lock(g_WorkshopMutex);
        failedPreviews.swap(g_WorkshopPreviewFailed);
    }
    if (!failedPreviews.empty())
    {
        for (WorkshopItem& item : WorkshopBrowse)
            if (failedPreviews.find(item.id) != failedPreviews.end())
                item.previewRequested = false;
    }

    int started = 0;
    for (WorkshopItem& item : WorkshopBrowse)
    {
        if (started >= 2) break;
        if (item.previewTexture) continue;
                                                                                
                                                                                
        if (item.previewRequested)
            continue;
        if (item.previewRetries >= 3)
            continue;
                                                                             
                                                                             
        item.previewRequested = true;
        item.previewRetries++;
        ++started;

        std::string url = KingModNormalizePreviewUrl(item.previewUrl);
        if (!url.empty() &&
            (url.find("steamusercontent") != std::string::npos ||
             url.find("akamaihd") != std::string::npos ||
             url.find("steamcdn") != std::string::npos))
        {
            url += (url.find('?') == std::string::npos ? "?" : "&");
            url += "imw=268&imh=151&ima=fit&impolicy=Letterbox";
        }
        const std::string id = item.id;
        const std::string pageUrl = item.pageUrl.empty()
            ? ("https://bakkesplugins.com/maps/" + item.id)
            : item.pageUrl;
        const int source = item.source;
        const int previewAttempt = item.previewRetries;

                                                                                
                                                                             
                                                                                 
        if (source == 1 && previewAttempt >= 2)
            url.clear();

        std::thread([url, id, pageUrl, source]() mutable
        {
            GameEventHookModule::ScopedWorker worker;
            std::vector<uint8_t> bytes;
            bool ok = !url.empty() && KingModHttpGetBytes(url, bytes, std::string(), 30) && !bytes.empty();

            if (!ok && source == 1)
            {
                std::string detailHtml;
                GameEventHookModule::WorkshopItem detail;
                if (KingModHttpGetString(pageUrl, detailHtml, 20) &&
                    KingModParseBakkesDetail(detailHtml, id, detail) &&
                    !detail.previewUrl.empty())
                {
                    bytes.clear();
                    const std::string fallback = KingModNormalizePreviewUrl(detail.previewUrl);
                    ok = !fallback.empty() && KingModHttpGetBytes(fallback, bytes, std::string(), 30) && !bytes.empty();
                }
            }

            {
                std::lock_guard<std::mutex> lock(g_WorkshopMutex);
                if (ok)
                    g_WorkshopPreviewBytes[id] = std::move(bytes);
                else
                    g_WorkshopPreviewFailed.insert(id);
            }
        }).detach();
    }

                                                     
    std::map<std::string, std::pair<int, std::string>> progress;
    {
        std::lock_guard<std::mutex> lock(g_WorkshopMutex);
        progress = g_WorkshopProgress;
    }
    for (WorkshopItem& item : WorkshopBrowse)
    {
        auto it = progress.find(item.id);
        if (it == progress.end()) continue;
        item.progress = it->second.first;
        item.status   = it->second.second;
        if (item.progress == 101) item.installed = true;
    }

                                                                               
                                                                             
                                                                   
    for (WorkshopItem& item : WorkshopBrowse)
    {
        if (item.source != 0)
            continue;

        uint64_t workshopId = 0;
        if (!WorkshopSteamDownloader::TryParseWorkshopId(item.id, workshopId))
        {
            item.progress = -2;
            item.status = "Invalid Workshop id";
            continue;
        }

        const WorkshopSteamDownloader::WorkshopStatus steam =
            WorkshopSteamDownloader::QueryWorkshopStatus(workshopId);
        if (!steam.available)
        {
                                                                              
                                                                            
                                                                             
                                                     
            if (item.progress == -1 && !item.fileUrl.empty())
                item.status = "Steam API unavailable - direct download ready";
            else if (item.progress == -1)
                item.status = "Steam Workshop is unavailable";
            continue;
        }

        item.installed = steam.installed;
        item.installPath = steam.installPath;
        if (steam.installed)
        {
            item.progress = 101;
            item.status = "Installed";
            continue;
        }

        if (steam.downloading)
        {
            item.progress = static_cast<int>(steam.progress * 100.0f + 0.5f);
            item.status = "Downloading";
        }
        else if (steam.downloadPending || item.progress == -3)
        {
            item.progress = -3;
            item.status = steam.subscribed ? "Waiting for Steam..." : "Subscribing...";

                                                                             
                                                                           
            if (steam.subscribed && !steam.downloadPending)
                WorkshopSteamDownloader::DownloadWorkshopMap(workshopId);
        }
    }
}

void GameEventHookModule::DownloadWorkshopItem(int index)
{
    if (index < 0 || index >= static_cast<int>(WorkshopBrowse.size()))
        return;

    WorkshopItem& item = WorkshopBrowse[index];
    if (item.progress >= 0 && item.progress <= 100)
        return;                     

    if (item.source == 0)
    {
        uint64_t workshopId = 0;
        if (!WorkshopSteamDownloader::TryParseWorkshopId(item.id, workshopId))
        {
            item.progress = -2;
            item.status = "Invalid Workshop id";
            return;
        }

        const WorkshopSteamDownloader::WorkshopStatus before =
            WorkshopSteamDownloader::QueryWorkshopStatus(workshopId);
        if (!before.available)
        {
                                                                       
                                                                            
                                                                               
                                                              
            item.status = item.fileUrl.empty()
                ? "Steam API unavailable - resolving direct download"
                : "Steam API unavailable - starting direct download";
        }
        else if (before.installed)
        {
            item.installed = true;
            item.installPath = before.installPath;
            item.progress = 101;
            item.status = "Installed";
            return;
        }

        else if (WorkshopSteamDownloader::DownloadWorkshopMap(workshopId))
        {
            item.progress = -3;
            item.status = before.subscribed ? "Waiting for Steam..." : "Subscribing...";
            return;
        }
        else
        {
                                                                         
                                                                            
            item.status = item.fileUrl.empty()
                ? "Steam request failed - resolving direct download"
                : "Steam request failed - starting direct download";
        }
    }

    const std::string id       = item.id;
    const std::string url      = item.fileUrl;
    const std::string title    = item.title;
    const std::string fileName = item.fileName;
    const std::string pageUrl  = item.pageUrl;
    const int source           = item.source;

    item.progress = 0;
    item.status   = "Starting...";
    {
        std::lock_guard<std::mutex> lock(g_WorkshopMutex);
        g_WorkshopProgress[id] = { 0, item.status };
    }

    std::thread([id, url, title, fileName, pageUrl, source]()
    {
        GameEventHookModule::ScopedWorker worker;
        auto publish = [&id](int pct, const std::string& text)
        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            g_WorkshopProgress[id] = { pct, text };
        };

        try
        {
            std::string effectiveUrl = url;
            std::string effectiveFileName = fileName;
            if (source == 0 && effectiveUrl.empty())
            {
                publish(0, "Resolving Steam direct download...");
                if (!KingModResolveSteamDownloadUrl(id, effectiveUrl, effectiveFileName))
                {
                    const std::string reason = g_KingModHttpError.empty()
                        ? "Steam did not publish a direct download for this item"
                        : "Steam direct download unavailable: " + g_KingModHttpError;
                    publish(-2, reason);
                    return;
                }
            }

            std::vector<uint8_t> bytes;
            bool downloaded = !effectiveUrl.empty() &&
                              KingModHttpGetBytes(effectiveUrl, bytes, id) && !bytes.empty();

                                                                            
                                                                             
                                                                               
            if (!downloaded && source == 1)
            {
                const std::string detailUrl = pageUrl.empty()
                    ? "https://bakkesplugins.com/maps/" + id
                    : pageUrl;
                std::string detailHtml;
                WorkshopItem detail;
                if (KingModHttpGetString(detailUrl, detailHtml) &&
                    KingModParseBakkesDetail(detailHtml, id, detail) &&
                    !detail.fileUrl.empty() && detail.fileUrl != effectiveUrl &&
                    detail.fileUrl.find("/download") == std::string::npos)
                {
                    publish(0, "Resolved community map download...");
                    effectiveUrl = detail.fileUrl;
                    if (!detail.fileName.empty())
                        effectiveFileName = detail.fileName;
                    bytes.clear();
                    downloaded = KingModHttpGetBytes(effectiveUrl, bytes, id) && !bytes.empty();
                }
            }

            if (!downloaded)
            {
                const std::string reason = g_KingModHttpError.empty()
                    ? "Download failed"
                    : "Download failed: " + g_KingModHttpError;
                publish(-2, reason);
                return;
            }

                                                                             
                                                                           
                                                                               
                               
            if (source == 1)
            {
                const size_t probeSize = (std::min)(bytes.size(), static_cast<size_t>(4096));
                std::string probe(reinterpret_cast<const char*>(bytes.data()), probeSize);
                probe = KingModLowerAscii(probe);
                if (probe.find("<!doctype html") != std::string::npos ||
                    probe.find("<html") != std::string::npos ||
                    probe.find("cf-turnstile") != std::string::npos ||
                    probe.find("just a moment") != std::string::npos)
                {
                    publish(-2, "Map provider requested browser verification");
                    return;
                }
            }

                                                                            
                                                                           
                                                                            
                                                                
            std::string ext;
            if (source == 1)
            {
                ext = KingModDetectWorkshopDownloadExtension(bytes);
                if (ext.empty()) ext = ".upk";
            }
            else
            {
                ext = ".udk";
                const size_t dot = effectiveFileName.find_last_of('.');
                if (dot != std::string::npos && dot + 1 < effectiveFileName.size())
                    ext = effectiveFileName.substr(dot);
            }

            std::transform(ext.begin(), ext.end(), ext.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            const bool archive = ext == ".zip" || ext == ".rar" || ext == ".7z";
            if (!archive && KingModDetectWorkshopDownloadExtension(bytes) != ".upk")
            {
                publish(-2, "Downloaded file is not a valid Rocket League map package");
                return;
            }

            const std::string dir = GetWorkshopDirectory();
            const std::string out = dir + "\\" + id + "_" + KingModSanitizeFileName(title) + ext;
            const std::string temporaryOut = out + ".kingmod-download.tmp";

            std::ofstream f(temporaryOut, std::ios::binary | std::ios::trunc);
            if (!f.good())
            {
                publish(-2, "Could not write to the workshop folder");
                return;
            }
            f.write(reinterpret_cast<const char*>(bytes.data()),
                    static_cast<std::streamsize>(bytes.size()));
            f.close();
            bytes.clear();

            if (!MoveFileExA(temporaryOut.c_str(), out.c_str(),
                             MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
            {
                std::error_code cleanupError;
                fs::remove(temporaryOut, cleanupError);
                publish(-2, "Could not finish installing the downloaded map");
                return;
            }

            std::string finalStatus = "Installed";
            int finalProgress = 101;
            if (archive)
            {
                publish(99, "Installing all map packages...");
                const int archiveKind = ext == ".zip" ? 1 : (ext == ".rar" ? 2 : 3);
                if (!KingModExtractWorkshopArchivePayload(
                        out, archiveKind, finalStatus))
                    finalProgress = -2;
            }

            Main.Execute([id, finalProgress, finalStatus]()
            {
                GameEventHookModule::RefreshWorkshopInstalled();
                std::lock_guard<std::mutex> lock(g_WorkshopMutex);
                g_WorkshopProgress[id] = { finalProgress, finalStatus };
            });
        }
        catch (...) { publish(-2, "Download failed"); }
    }).detach();
}

namespace
{
                                                                            
                                                                            
                                                                             
                                             
    UGFxData_Workshop_TA* KingModGetWorkshopLoader()
    {
        if (UGFxData_Workshop_TA* existing =
                Instances.GetInstanceOf<UGFxData_Workshop_TA>())
        {
            if (IsValidObjectOfClass(existing, UGFxData_Workshop_TA::StaticClass()) &&
                IsValidObjectOfClass(existing->Shell, UGFxShell_TA::StaticClass()))
                return existing;
        }

        UGFxShell_TA* shell = Instances.GetInstanceOf<UGFxShell_TA>();
        if (!shell)
        {
                                                                            
                                                                             
                                                                        
                           
            try
            {
                if (ULocalPlayer* local = Instances.IULocalPlayer())
                    shell = UGFxShell_TA::GetShell(static_cast<ULocalPlayer_X*>(local));
            }
            catch (...) { shell = nullptr; }
        }
        if (!IsValidObjectOfClass(shell, UGFxShell_TA::StaticClass()))
            return nullptr;

        if (!IsValidObjectOfClass(shell->DataStore, UGFxDataStore_X::StaticClass()))
            return nullptr;

        try
        {
            int placedRow = -1;
            UGFxDataRow_X* row = shell->DataStore->CreateObject(
                UGFxData_Workshop_TA::StaticClass(), -1, placedRow);
            if (!row || !row->IsA<UGFxData_Workshop_TA>())
                return nullptr;

            UGFxData_Workshop_TA* created =
                static_cast<UGFxData_Workshop_TA*>(row);
            if (!created->Shell)
            {
                created->Shell = shell;
                created->eventOnShellSet();
            }
            return created;
        }
        catch (...)
        {
            return nullptr;
        }
    }

    bool KingModLoadWorkshopPath(const std::string& fullPath)
    {
        if (fullPath.empty())
        {
            GameEventHookModule::WorkshopLoadStatus = "Pick a map first";
            return false;
        }

        UGFxData_Workshop_TA* workshop = KingModGetWorkshopLoader();
        if (!workshop)
        {
            GameEventHookModule::WorkshopLoadStatus =
                "Rocket League's menu shell is not ready";
            return false;
        }

        try
        {
            FString path = Format::ToFString(fullPath);
            workshop->LoadWorkshopMap(path);
            GameEventHookModule::WorkshopLoadStatus = "Loading Workshop map...";
            return true;
        }
        catch (...)
        {
            GameEventHookModule::WorkshopLoadStatus =
                "Rocket League rejected this Workshop map";
            return false;
        }
    }

                                                                              
                                                                             
                                                                            
      
                                                                            
                                                                          
                                                                              
                                                                             
                                                                          
                                                                             
    bool KingModTryDirectLooseMapTravel(const std::string& fullPath)
    {
        try
        {
            std::error_code ec;
            const fs::path source = fs::absolute(fs::path(fullPath), ec);
            if (ec || !fs::is_regular_file(source, ec) || ec)
            {
                GameEventHookModule::WorkshopLoadStatus = "Map file is unavailable";
                return false;
            }

            std::string extension = source.extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (extension != ".upk" && extension != ".udk")
            {
                GameEventHookModule::WorkshopLoadStatus =
                    "Fallback supports standalone .upk or .udk maps only";
                return false;
            }

            const std::string packageName = source.stem().string();
            if (packageName.empty())
            {
                GameEventHookModule::WorkshopLoadStatus = "Map has no package name";
                return false;
            }

            const fs::path cookedDir = KingModGetCookedPackageDirectory();
            if (cookedDir.empty())
            {
                GameEventHookModule::WorkshopLoadStatus =
                    "Could not locate TAGame\\CookedPCConsole";
                return false;
            }

                                                                                
            const fs::path target = cookedDir / (packageName + ".upk");
            bool targetReady = false;
            if (fs::exists(target, ec) && !ec)
            {
                std::error_code equivalentError;
                targetReady = fs::equivalent(source, target, equivalentError) &&
                              !equivalentError;
                if (!targetReady)
                {
                                                                               
                                                                             
                                                                            
                                                                           
                                                                     
                    std::error_code sizeError;
                    const uintmax_t sourceSize = fs::file_size(source, sizeError);
                    const uintmax_t targetSize = fs::file_size(target, sizeError);
                    targetReady = !sizeError && sourceSize == targetSize;
                    if (!targetReady)
                    {
                        GameEventHookModule::WorkshopLoadStatus =
                            "CookedPCConsole already has a different " +
                            target.filename().string();
                        return false;
                    }
                }
            }
            else if (ec)
            {
                GameEventHookModule::WorkshopLoadStatus =
                    "Could not inspect CookedPCConsole: " + ec.message();
                return false;
            }

            if (!targetReady)
            {
                fs::copy_file(source, target, fs::copy_options::none, ec);
                if (ec)
                {
                    GameEventHookModule::WorkshopLoadStatus =
                        "Could not stage map package: " + ec.message();
                    return false;
                }
            }

            const std::string command =
                "start " + packageName + "?Game=TAGame.GameInfo_Tutorial_TA";
            GameEventHookModule::WorkshopLoadStatus =
                "Starting " + packageName + "...";

                                                                         
                                                                             
                                             
            Main.Execute([command]()
            {
                bool sent = false;
                try
                {
                    if (APlayerController* pc = Instances.IAPlayerController())
                    {
                        pc->ConsoleCommand(Format::ToFString(command), false);
                        sent = true;
                    }
                }
                catch (...) {}

                if (!sent)
                {
                    try
                    {
                        if (UGameViewportClient_TA* viewport =
                                Instances.GetInstanceOf<UGameViewportClient_TA>())
                        {
                            viewport->ConsoleCommand(Format::ToFString(command));
                            sent = true;
                        }
                    }
                    catch (...) {}
                }

                GameEventHookModule::WorkshopLoadStatus = sent
                    ? ("Starting local map: " + command)
                    : "No game console is available yet";
            });
            return true;
        }
        catch (const std::exception& exception)
        {
            GameEventHookModule::WorkshopLoadStatus =
                std::string("Could not stage map: ") + exception.what();
            return false;
        }
        catch (...)
        {
            GameEventHookModule::WorkshopLoadStatus = "Could not stage map";
            return false;
        }
    }

    void KingModQueueWorkshopLoad(
        const std::string& fullPath,
        bool allowDirectTravel)
    {
        if (fullPath.empty())
            return;

        const auto now = std::chrono::steady_clock::now();
        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            g_PendingWorkshopMapPath = fullPath;
            g_PendingWorkshopAllowsDirectTravel = allowDirectTravel;
            g_WorkshopLoadRetryAt = now + std::chrono::milliseconds(100);
            g_WorkshopLoadDeadline = now + std::chrono::seconds(20);
            g_WorkshopLoadAttempts = 0;
        }
        GameEventHookModule::WorkshopLoadStatus =
            "Waiting for Rocket League menu shell...";
    }

    void KingModPumpWorkshopLoad()
    {
        const auto now = std::chrono::steady_clock::now();
        std::string pendingPath;
        bool allowDirectTravel = false;
        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            if (g_PendingWorkshopMapPath.empty() || g_WorkshopLoadTaskQueued ||
                now < g_WorkshopLoadRetryAt)
                return;
            pendingPath = g_PendingWorkshopMapPath;
            allowDirectTravel = g_PendingWorkshopAllowsDirectTravel;
            g_WorkshopLoadTaskQueued = true;
        }

        try
        {
            Main.Execute([pendingPath, allowDirectTravel]()
            {
                const bool loaded = KingModLoadWorkshopPath(pendingPath);
                const auto completedAt = std::chrono::steady_clock::now();
                bool directFallback = false;
                {
                    std::lock_guard<std::mutex> lock(g_WorkshopMutex);
                    if (g_PendingWorkshopMapPath != pendingPath)
                    {
                        g_WorkshopLoadTaskQueued = false;
                        return;
                    }

                    if (loaded)
                    {
                        g_PendingWorkshopMapPath.clear();
                        g_PendingWorkshopAllowsDirectTravel = false;
                        g_WorkshopLoadAttempts = 0;
                    }
                    else
                    {
                        const bool shellPending =
                            GameEventHookModule::WorkshopLoadStatus ==
                            "Rocket League's menu shell is not ready";
                        if (shellPending && completedAt < g_WorkshopLoadDeadline)
                        {
                            ++g_WorkshopLoadAttempts;
                            g_WorkshopLoadRetryAt = completedAt + std::chrono::milliseconds(250);
                            GameEventHookModule::WorkshopLoadStatus =
                                "Waiting for Rocket League menu shell... (" +
                                std::to_string(g_WorkshopLoadAttempts) + ")";
                        }
                        else
                        {
                            directFallback = shellPending && allowDirectTravel;
                            g_PendingWorkshopMapPath.clear();
                            g_PendingWorkshopAllowsDirectTravel = false;
                            g_WorkshopLoadAttempts = 0;
                            if (shellPending && !directFallback)
                                GameEventHookModule::WorkshopLoadStatus =
                                    "Menu shell was not ready after 20 seconds";
                        }
                    }
                    g_WorkshopLoadTaskQueued = false;
                }

                if (directFallback)
                    KingModTryDirectLooseMapTravel(pendingPath);
            });
        }
        catch (...)
        {
            std::lock_guard<std::mutex> lock(g_WorkshopMutex);
            g_WorkshopLoadTaskQueued = false;
            g_WorkshopLoadRetryAt = std::chrono::steady_clock::now() +
                                    std::chrono::milliseconds(250);
        }
    }
}

bool GameEventHookModule::LoadWorkshopItem(int index)
{
    if (index < 0 || index >= static_cast<int>(WorkshopBrowse.size()))
        return false;

    WorkshopItem& item = WorkshopBrowse[index];
    std::string mapPath;

    const auto findDownloadedMap = [&item, &mapPath]() -> bool
    {
                                                                              
                                                                              
                                                                                
                                                                  
        RefreshWorkshopInstalled();
        const std::string archivePrefix = item.id + "_";
        for (const WorkshopInstalledEntry& installed : WorkshopInstalled)
        {
            if (installed.name.rfind(archivePrefix, 0) != 0) continue;
            if (!installed.mapFile.empty())
            {
                mapPath = installed.mapFile;
                return true;
            }
            item.status = "Map archive is not extracted";
            return false;
        }

        RefreshWorkshopMapList();
        for (const std::string& candidate : WorkshopMapList)
        {
            std::string leaf = candidate;
            const size_t slash = leaf.find_last_of("\\/");
            if (slash != std::string::npos) leaf = leaf.substr(slash + 1);
            if (leaf.rfind(item.id, 0) == 0)
            {
                mapPath = candidate;
                return true;
            }
        }

        item.status = "Download the map first";
        return false;
    };

    if (item.source == 0)
    {
        uint64_t workshopId = 0;
        if (!WorkshopSteamDownloader::TryParseWorkshopId(item.id, workshopId))
        {
            item.status = "Invalid Workshop id";
            return false;
        }

        if (WorkshopSteamDownloader::IsWorkshopMapInstalled(workshopId))
        {
                                                                           
                                                                          
            if (!WorkshopSteamDownloader::GetWorkshopInstallMapPath(workshopId, mapPath))
            {
                item.status = "Steam installed this item, but no map package was found";
                return false;
            }
            item.installPath.clear();
            WorkshopSteamDownloader::GetWorkshopInstallPath(workshopId, item.installPath);
        }
        else if (!findDownloadedMap())
        {
            return false;
        }
    }
    else if (!findDownloadedMap())
    {
        return false;
    }

    strncpy_s(WorkshopMapPath, sizeof(WorkshopMapPath), mapPath.c_str(), _TRUNCATE);
    item.mapPath = mapPath;

                                                                               
                                                                               
                                                                              
                                                                     
    item.status.clear();
                                     
    LoadWorkshopMap(false, 0, 8, std::string(), std::string(),
                    std::string(), std::string(), true);
    return true;
}

void GameEventHookModule::OpenWorkshopItemPage(int index)
{
    if (index < 0 || index >= static_cast<int>(WorkshopBrowse.size()))
        return;
    WorkshopItem& item = WorkshopBrowse[index];

    std::string url = item.pageUrl;
    if (url.empty() && item.source == 0)
        url = "https://steamcommunity.com/sharedfiles/filedetails/?id=" + item.id;
    if (url.empty()) return;

    ShellExecuteA(NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL);
    item.progress = 101;
    item.status   = "Opened in browser -- finish the download there";
    std::lock_guard<std::mutex> lock(g_WorkshopMutex);
    g_WorkshopProgress[item.id] = { 101, item.status };
}

void GameEventHookModule::LaunchStandardMap(const std::string& arenaPackage,
                                             bool hostLan,
                                             int gameModeIndex,
                                             int maxPlayers,
                                             const std::string& password,
                                             const std::string& gameTags,
                                             bool localTraining)
{
    if (!KingModIsSafeTravelToken(arenaPackage) ||
        (!password.empty() && !KingModIsSafeTravelToken(password)) ||
        !KingModIsSafeGameTags(gameTags))
    {
        WorkshopLoadStatus = "Invalid map, password or match settings";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
        return;
    }

    const std::string command = KingModBuildWorkshopSessionCommand(
        arenaPackage, hostLan, gameModeIndex, maxPlayers, password, gameTags, localTraining);
    WorkshopLoadStatus = hostLan
        ? "Starting LAN listen server..."
        : (localTraining ? "Starting training..." : "Starting local match...");
    Main.SpawnNotification("KingMod", WorkshopLoadStatus, 3);
    try
    {
        Main.Execute([command, arenaPackage, gameModeIndex, maxPlayers, password,
                      gameTags, hostLan, localTraining]()
        {
            bool sent = false;
            if (hostLan)
            {
                CustomMatchModule::StartLanStatusServer("7777", password);
                sent = KingModDispatchConsoleCommand(command);
            }
            else if (localTraining)
            {
                KingModQueueFreeplayLaunch(arenaPackage, gameModeIndex, 180, false);
                sent = true;
            }
            if (!sent)
                sent = KingModDispatchConsoleCommand(command);
            GameEventHookModule::WorkshopLoadStatus = sent
                ? (hostLan ? "Hosting LAN match on UDP 7777"
                           : (localTraining ? std::string() : "Starting local match"))
                : "No game console is available yet";
            Main.SpawnNotification("KingMod",
                sent ? (hostLan ? "Starting LAN host on UDP 7777..."
                                : (localTraining ? "Starting training..."
                                                 : "Starting local match..."))
                     : "No game console is available yet",
                sent ? 3 : 4);
        });
    }
    catch (...)
    {
        WorkshopLoadStatus = "Could not queue the map launch";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
    }
}

void GameEventHookModule::LoadWorkshopMap(bool hostLan,
                                           int gameModeIndex,
                                           int maxPlayers,
                                           const std::string& password,
                                           const std::string& gameTags,
                                           const std::string& joinHost,
                                           const std::string& joinPort,
                                           bool localTraining)
{
    if (WorkshopMapPath[0] == '\0')
    {
        WorkshopLoadStatus = "Pick a map first";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
        return;
    }

    bool expected = false;
    if (!g_WorkshopMapLaunchRunning.compare_exchange_strong(expected, true))
    {
        WorkshopLoadStatus = "A map is already being prepared";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 3);
        return;
    }

    const bool joinLan = !joinHost.empty();
    std::string normalizedJoinHost;
    std::string normalizedJoinPort;
    if (!password.empty() && !KingModIsSafeTravelToken(password))
    {
        WorkshopLoadStatus = "Password can only contain letters, numbers, dot, dash or underscore";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
        g_WorkshopMapLaunchRunning.store(false);
        return;
    }
    if (!KingModIsSafeGameTags(gameTags))
    {
        WorkshopLoadStatus = "Invalid hosted-match settings";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
        g_WorkshopMapLaunchRunning.store(false);
        return;
    }
    if (joinLan && (hostLan || !CustomMatchModule::NormalizeLanEndpoint(
                    joinHost, joinPort, normalizedJoinHost, normalizedJoinPort)))
    {
        WorkshopLoadStatus = "Enter a valid host or domain and port";
        Main.SpawnNotification("KingMod", WorkshopLoadStatus, 4);
        g_WorkshopMapLaunchRunning.store(false);
        return;
    }

    const std::string selectedPath(WorkshopMapPath);
    WorkshopLoadStatus = hostLan
        ? "Preparing Workshop map for LAN host..."
        : (joinLan ? "Preparing Workshop map before joining..."
                   : "Preparing Workshop map...");
    Main.SpawnNotification("KingMod", WorkshopLoadStatus, 3);

                                                                              
                                                                          
                                                                 
    try
    {
        std::thread([selectedPath, hostLan, gameModeIndex, maxPlayers,
                     password, gameTags, normalizedJoinHost, normalizedJoinPort,
                     joinLan, localTraining]()
        {
            GameEventHookModule::ScopedWorker worker;

            auto publishError = [](std::string message)
            {
                if (g_DllUnloading.load())
                {
                    g_WorkshopMapLaunchRunning.store(false);
                    return;
                }

                try
                {
                    Main.Execute([message = std::move(message)]()
                    {
                        GameEventHookModule::WorkshopLoadStatus = message;
                        Main.SpawnNotification("KingMod", message, 4);
                        g_WorkshopMapLaunchRunning.store(false);
                    });
                }
                catch (...)
                {
                    g_WorkshopMapLaunchRunning.store(false);
                }
            };

            std::string packageName;
            try
            {
            std::error_code ec;
            fs::path source = fs::absolute(fs::path(selectedPath), ec);
            if (ec || !fs::is_regular_file(source, ec) || ec)
            {
                publishError("Selected Workshop map file is missing");
                return;
            }

            std::string extension = source.extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(),
                [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
            if (extension != ".upk" && extension != ".udk")
            {
                publishError("Select a Rocket League .upk or .udk map");
                return;
            }

                                                                               
                                                                             
                                                                             
            if (KingModMapPackageScore(source) < 1000)
            {
                publishError("This package does not contain a playable Rocket League map");
                return;
            }

                                                                              
                                                                             
                                                                              
                                                               
            source = KingModResolveCompleteWorkshopSource(source);

            packageName = source.stem().string();
            if (!KingModIsSafeTravelToken(packageName))
            {
                publishError("Map package name contains unsupported characters");
                return;
            }

            const fs::path cookedDir = KingModGetCookedPackageDirectory();
            if (cookedDir.empty())
            {
                publishError("Could not locate TAGame\\CookedPCConsole");
                return;
            }

            std::string preparationError;
            if (!KingModEnsureSharedWorkshopAssets(
                    source, cookedDir, preparationError))
            {
                publishError(preparationError);
                return;
            }

            if (!KingModStageCompleteWorkshopMap(
                    source, cookedDir, preparationError))
            {
                publishError(preparationError);
                return;
            }

            if (!KingModStageWorkshopAlias(
                    source, cookedDir, packageName, preparationError))
            {
                publishError(preparationError);
                return;
            }
            }
            catch (const std::exception& e)
            {
                publishError(std::string("Could not prepare map: ") + e.what());
                return;
            }
            catch (...)
            {
                publishError("Could not prepare map");
                return;
            }

            if (g_DllUnloading.load())
            {
                g_WorkshopMapLaunchRunning.store(false);
                return;
            }

            const std::string command = joinLan
                ? KingModBuildJoinCommand(normalizedJoinHost, normalizedJoinPort, password)
                : KingModBuildWorkshopSessionCommand(
                    packageName, hostLan, gameModeIndex, maxPlayers, password, gameTags,
                    localTraining);

            try
            {
                Main.Execute([command, packageName, gameModeIndex, maxPlayers, password,
                              gameTags, hostLan, joinLan, normalizedJoinHost,
                              normalizedJoinPort, localTraining]()
                {
                    bool sent = false;
                    if (hostLan)
                    {
                        CustomMatchModule::StartLanStatusServer("7777", password);
                        sent = KingModDispatchConsoleCommand(command);
                    }
                    else if (!joinLan && localTraining)
                    {
                        KingModQueueFreeplayLaunch(packageName, gameModeIndex, 180, true);
                        sent = true;
                    }
                    if (!sent)
                        sent = KingModDispatchConsoleCommand(command);
                    if (!sent)
                        KingModRestoreWorkshopAliasAfterTravel();
                    GameEventHookModule::WorkshopLoadStatus = sent
                        ? (hostLan ? "Starting LAN listen server on UDP 7777"
                                    : (joinLan ? "Connecting to " + normalizedJoinHost + ":" + normalizedJoinPort
                                               : (localTraining ? "Starting Workshop Freeplay"
                                                                : "Starting Workshop match")))
                        : "No game console is available yet";
                    if (sent && hostLan)
                        Main.SpawnNotification("KingMod", "Starting LAN host on UDP 7777...", 3);
                    else if (sent && joinLan)
                        Main.SpawnNotification("KingMod", "Workshop map ready; connecting...", 3);
                    else if (sent)
                        Main.SpawnNotification("KingMod",
                            localTraining ? "Starting Freeplay..." : "Loading Workshop map...", 3);
                    else
                        Main.SpawnNotification("KingMod", "No game console is available yet", 4);
                    g_WorkshopMapLaunchRunning.store(false);
                });
            }
            catch (...)
            {
                g_WorkshopMapLaunchRunning.store(false);
            }
        }).detach();
    }
    catch (...)
    {
        g_WorkshopMapLaunchRunning.store(false);
        WorkshopLoadStatus = "Could not start the map worker";
    }
}

#if 0                                                                                                 
                                                                               
      
                                                                           
                                                                               
                                                                             
                                                                               
                                                                              
                
                                                                                
                                                                            
                                                                               
                                                                            
    std::string packageName;
    try
    {
        fs::path source(WorkshopMapPath);
        std::error_code ec;
        if (!fs::exists(source, ec) || ec)
        {
            WorkshopLoadStatus = "File is gone: " + source.filename().string();
            return;
        }

                                                                              
                                                                             
                                                                  
        const fs::path cookedDir = KingModGetCookedPackageDirectory();
        if (cookedDir.empty())
        {
            WorkshopLoadStatus = "Could not locate TAGame\\CookedPCConsole";
            return;
        }

        packageName = source.stem().string();
        const fs::path target = cookedDir / (packageName + ".upk");

        if (fs::absolute(source, ec) != fs::absolute(target, ec))
        {
            if (!fs::exists(target, ec) ||
                fs::file_size(target, ec) != fs::file_size(source, ec))
            {
                fs::copy_file(source, target, fs::copy_options::overwrite_existing, ec);
                if (ec)
                {
                    WorkshopLoadStatus = "Could not copy into CookedPCConsole: " + ec.message();
                    return;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        WorkshopLoadStatus = std::string("Copy failed: ") + e.what();
        return;
    }
    catch (...)
    {
        WorkshopLoadStatus = "Copy failed";
        return;
    }

    if (packageName.empty())
    {
        WorkshopLoadStatus = "Map has no package name";
        return;
    }

                                                                             
                                                                             
                                                                           
                                                                    
    std::string url;
    switch (WorkshopLoadMethod)
    {
    case 1:  url = "start " + packageName + "?Game=TAGame.GameInfo_Soccar_TA";   break;
    case 2:  url = "start " + packageName;                                       break;
    case 3:  url = "open "  + packageName;                                       break;
    default: url = "start " + packageName + "?Game=TAGame.GameInfo_Tutorial_TA"; break;
    }

    WorkshopLoadStatus = "Loading " + packageName + "...";

                                                                               
                                                 
    Main.Execute([url]()
    {
        bool sent = false;

                                                                                
                                                                               
        try
        {
            if (AActor* defaultActor = Instances.GetDefaultInstanceOf<AActor>())
            {
                defaultActor->ConsoleCommand(Format::ToFString(url), 0);
                sent = true;
            }
        }
        catch (...) {}

        if (!sent)
        {
            try
            {
                if (APlayerController* pc = Instances.IAPlayerController())
                {
                    pc->ConsoleCommand(Format::ToFString(url), false);
                    sent = true;
                }
            }
            catch (...) {}
        }

        if (!sent)
        {
            try
            {
                if (UGameViewportClient_TA* gvc = Instances.GetInstanceOf<UGameViewportClient_TA>())
                {
                    gvc->ConsoleCommand(Format::ToFString(url));
                    sent = true;
                }
            }
            catch (...) {}
        }

        GameEventHookModule::WorkshopLoadStatus =
            sent ? ("Sent: " + url) : "No console target available";
    });
}
#endif

                                                                         
                                                                          
                                                                      
                                                                                
         

                                                                              
                     
                                                                              
void GameEventHookModule::DrawMatchmakingShieldOverlay()
{
    MatchmakingShield::Tick();

    if (!MatchmakingShield::IsEnabled() || !MatchmakingShield::IsWaitingForJoin())
        return;

    ImDrawList* draw = ImGui::GetForegroundDrawList();
    if (!draw)
        return;

    const int vk = MatchmakingShield::GetJoinKey();
    char keyName[32]{};
    if (vk >= VK_F1 && vk <= VK_F24) { sprintf_s(keyName, "F%d", vk - VK_F1 + 1); }
    else if (vk >= 'A' && vk <= 'Z') { sprintf_s(keyName, "%c", vk); }
    else if (vk >= '0' && vk <= '9') { sprintf_s(keyName, "%c", vk); }
    else { strcpy_s(keyName, "KEY"); }

    const ImVec2 display = ImGui::GetIO().DisplaySize;
    const std::string title = std::string("MATCH HELD - PRESS ") + keyName + " TO JOIN";
    const std::string detail = "Connection paused before spawning";
    const ImVec2 titleSize = ImGui::CalcTextSize(title.c_str());
    const ImVec2 detailSize = ImGui::CalcTextSize(detail.c_str());
    const float width = (std::max)(titleSize.x, detailSize.x) + 36.0f;
    const float height = titleSize.y + detailSize.y + 34.0f;
    const ImVec2 topLeft(display.x * 0.5f - width * 0.5f, display.y * 0.10f);
    const ImVec2 bottomRight(topLeft.x + width, topLeft.y + height);
    draw->AddRectFilled(topLeft, bottomRight, IM_COL32(8, 12, 20, 238), 9.0f);
    draw->AddRect(topLeft, bottomRight, IM_COL32(78, 132, 255, 255), 9.0f, 0, 2.0f);
    draw->AddText(ImVec2(topLeft.x + 18.0f, topLeft.y + 10.0f), IM_COL32(110, 158, 255, 255), title.c_str());
    draw->AddText(ImVec2(topLeft.x + 18.0f, topLeft.y + 18.0f + titleSize.y), IM_COL32(190, 198, 214, 255), detail.c_str());
}

                                                                              
                                                    
  
                                                                               
                                                                              
                                                                           
                                                                   
                                                                              
namespace
{
    std::string GetModPresetsPath()
    {
        return GetKingModResourcesDirectory() + "\\ModPresets.json";
    }

    nlohmann::json LoadModPresetsFile()
    {
        nlohmann::json root;
        try
        {
            std::ifstream in(GetModPresetsPath());
            if (in.good())
                in >> root;
        }
        catch (...)
        {
        }
        if (!root.is_object())
            root = nlohmann::json::object();
        return root;
    }

    void SaveModPresetsFile(const nlohmann::json& root)
    {
        try
        {
            std::ofstream out(GetModPresetsPath(), std::ios::trunc);
            if (out.good())
                out << root.dump(2);
        }
        catch (...)
        {
        }
    }

                                                                           
    nlohmann::json& ModPresetsPageNode(nlohmann::json& root, const std::string& page)
    {
        if (!root.contains(page) || !root[page].is_object())
            root[page] = nlohmann::json::object();
        nlohmann::json& node = root[page];
        if (!node.contains("presets") || !node["presets"].is_object())
            node["presets"] = nlohmann::json::object();
        if (!node.contains("favorite"))
            node["favorite"] = "";
        return node;
    }

    nlohmann::json ModPresetsFieldsToJson(const std::vector<ModPresets::Field>& fields)
    {
        nlohmann::json o = nlohmann::json::object();
        for (const ModPresets::Field& f : fields)
        {
            if (!f.ptr || !f.key) continue;
            switch (f.type)
            {
            case ModPresets::FieldType::Bool:
                o[f.key] = *static_cast<bool*>(f.ptr);
                break;
            case ModPresets::FieldType::Int:
                o[f.key] = *static_cast<int*>(f.ptr);
                break;
            case ModPresets::FieldType::Float:
                o[f.key] = *static_cast<float*>(f.ptr);
                break;
            case ModPresets::FieldType::Color4:
            {
                const float* c = static_cast<const float*>(f.ptr);
                o[f.key] = { c[0], c[1], c[2], c[3] };
                break;
            }
            case ModPresets::FieldType::Text:
                o[f.key] = std::string(static_cast<const char*>(f.ptr));
                break;
            case ModPresets::FieldType::Str:
                o[f.key] = *static_cast<std::string*>(f.ptr);
                break;
            }
        }
        return o;
    }

    void ModPresetsJsonToFields(const nlohmann::json& o, const std::vector<ModPresets::Field>& fields)
    {
        if (!o.is_object()) return;

        for (const ModPresets::Field& f : fields)
        {
            if (!f.ptr || !f.key || !o.contains(f.key)) continue;
            try
            {
                const nlohmann::json& v = o[f.key];
                switch (f.type)
                {
                case ModPresets::FieldType::Bool:
                    if (v.is_boolean()) *static_cast<bool*>(f.ptr) = v.get<bool>();
                    break;
                case ModPresets::FieldType::Int:
                    if (v.is_number()) *static_cast<int*>(f.ptr) = v.get<int>();
                    break;
                case ModPresets::FieldType::Float:
                    if (v.is_number()) *static_cast<float*>(f.ptr) = v.get<float>();
                    break;
                case ModPresets::FieldType::Color4:
                    if (v.is_array() && v.size() >= 4)
                    {
                        float* c = static_cast<float*>(f.ptr);
                        for (int i = 0; i < 4; ++i) c[i] = v[i].get<float>();
                    }
                    break;
                case ModPresets::FieldType::Text:
                    if (v.is_string() && f.textCapacity > 0)
                    {
                        const std::string s = v.get<std::string>();
                        strncpy_s(static_cast<char*>(f.ptr), static_cast<size_t>(f.textCapacity), s.c_str(), _TRUNCATE);
                    }
                    break;
                case ModPresets::FieldType::Str:
                    if (v.is_string()) *static_cast<std::string*>(f.ptr) = v.get<std::string>();
                    break;
                }
            }
            catch (...)
            {
            }
        }
    }
}

namespace ModPresets
{
    static bool g_loadingAllSnapshot = false;

    std::vector<std::string> PageNames()
    {
        return {
            "Account", "Loadout", "Items", "Car", "Wheels", "Boost",
            "License Plate", "Ball", "Misc", "Freeplay", "Ball Prediction",
            "Boost Pads", "Camera", "World", "Other", "ALL"
        };
    }

    std::vector<Field> PageFields(const std::string& page)
    {
        auto B  = [](const char* k, bool& v)        { return Field{ k, FieldType::Bool,  &v, 0 }; };
        auto I  = [](const char* k, int& v)         { return Field{ k, FieldType::Int,   &v, 0 }; };
        auto F  = [](const char* k, float& v)       { return Field{ k, FieldType::Float, &v, 0 }; };
        auto C4 = [](const char* k, void* v)        { return Field{ k, FieldType::Color4, v, 0 }; };
        auto T  = [](const char* k, char* v, int n) { return Field{ k, FieldType::Text,  v, n }; };
                                                                           
                                                                                
                                                                                
                                  
        auto Sp = [](const char* k, std::string* v)  { return Field{ k, FieldType::Str, v, 0 }; };

        if (page == "Account")
        {
            return {
                B("hide_online_status", Events.setOnlineStatus),
                Sp("custom_status", &Events.customStatus),
                B("custom_avatar", Events.customavatar),
                Sp("avatar_path", &Events.avatarTexturePath),
                I("rocketpass_tier", Events.rocketPassTier),
                F("rocketpass_xp_mult", Events.rocketPassXPMultiplier),
                B("rocketpass_premium", Events.rocketPassPremium),
            };
        }
        if (page == "Items" || page == "Loadout")
        {
            return {
                B("custom_title", Events.setcustomtitle),
                Sp("title_text", &Events.titletext),
                I("title_color", Events.titlecolor),
                I("title_glow_color", Events.titleglowcolor),
            };
        }
        if (page == "Car")
        {
            return {
                F("trim_r", Events.customtrimcolors[0]),
                F("trim_g", Events.customtrimcolors[1]),
                F("trim_b", Events.customtrimcolors[2]),
            };
        }
        if (page == "Wheels")
        {
            return {
                B("wheel_color_enabled", Events.wheelColorEnabled),
                B("wheel_color_rainbow", Events.wheelColorRainbow),
                C4("wheel_color", Events.wheelColor),
                I("invis_wheels", Events.inviswheels),
                I("wheel_size_state", Events.wheelSizeState),
                F("wheel_width", Events.wheelWidth),
                F("wheel_height", Events.wheelHeight),
                F("wheel_offset_y_front", Events.wheelOffsetY[0]),
                F("wheel_offset_y_rear", Events.wheelOffsetY[1]),
                F("wheel_offset_z_front", Events.wheelOffsetZ[0]),
                F("wheel_offset_z_rear", Events.wheelOffsetZ[1]),
                F("wheel_roll_front", Events.wheelRoll[0]),
                F("wheel_roll_rear", Events.wheelRoll[1]),
                I("wheel_target", Events.wheelTarget),
                B("wheel_offset_active", Events.wheelOffsetActive),
            };
        }
        if (page == "Boost")
        {
            return {
                B("boost_color_enabled", Events.alphaBoostColorEnabled),
                C4("boost_color", Events.alphaBoostColor),
                B("boost_sound_default", GameEventHookModule::BoostSoundDefaultOverride),
                B("alpha_boost_sound", GameEventHookModule::AlphaBoostSoundEnabled),
            };
        }
        if (page == "License Plate")
        {
            return {
                B("plate_front_enabled", Items.plateFrontEnabled),
                B("plate_rear_enabled", Items.plateRearEnabled),
                T("plate_front_image", Items.plateFrontImagePath, static_cast<int>(sizeof(Items.plateFrontImagePath))),
                T("plate_rear_image", Items.plateRearImagePath, static_cast<int>(sizeof(Items.plateRearImagePath))),
                C4("plate_front_bg", Items.plateFrontBgColor),
                C4("plate_rear_bg", Items.plateRearBgColor),
                F("plate_front_roll", Items.plateFrontRoll),
                F("plate_rear_roll", Items.plateRearRoll),
                F("plate_front_width", Items.plateFrontWidth),
                F("plate_front_height", Items.plateFrontHeight),
                F("plate_rear_width", Items.plateRearWidth),
                F("plate_rear_height", Items.plateRearHeight),
            };
        }
        if (page == "Ball")
        {
            return {
                I("ball_speed_unit", GameEventHookModule::BallSpeedUnit),
                B("ball_speed_display", GameEventHookModule::BallSpeedDisplayEnabled),
                F("ball_speed_x", GameEventHookModule::BallSpeedDisplayX),
                F("ball_speed_y", GameEventHookModule::BallSpeedDisplayY),
                F("ball_speed_size", GameEventHookModule::BallSpeedDisplaySize),
                B("ball_sphere", GameEventHookModule::Ball3DSphereEnabled),
                C4("ball_sphere_color", &GameEventHookModule::Ball3DSphereColor),
            };
        }
        if (page == "Misc")
        {
            return {
                B("hud_color_enabled", Events.hudColorChangerEnabled),
                B("hud_color_rainbow", Events.hudColorRainbow),
                B("hud_color_blue_team", Events.hudColorBlueTeam),
                B("hud_color_orange_team", Events.hudColorOrangeTeam),
                C4("hud_color_blue", Events.hudColorBlue),
                C4("hud_color_orange", Events.hudColorOrange),
                B("stadium_color_enabled", Events.stadiumColorChangerEnabled),
                B("stadium_color_rainbow", Events.stadiumColorRainbow),
                C4("stadium_color_blue", Events.stadiumColorBlue),
                C4("stadium_color_orange", Events.stadiumColorOrange),
                B("show_mmr", GameEventHookModule::ShowPlayerMMR),
                B("platform_on_scoreboard", GameEventHookModule::ShowPlatformOnScoreboard),
                B("pov_in_replay", GameEventHookModule::PovInReplay),
                B("enemy_reset_indicator", GameEventHookModule::EnemyResetIndicatorEnabled),
            };
        }
        if (page == "Freeplay")
        {
            return {
                B("unlimited_jumps", GameEventHookModule::UnlimitedJumpsEnabled),
                B("scored_message", GameEventHookModule::ScoredMessageEnabled),
                B("scored_message_speed", GameEventHookModule::ScoredMessageShowSpeed),
                T("workshop_map_path", GameEventHookModule::WorkshopMapPath, static_cast<int>(sizeof(GameEventHookModule::WorkshopMapPath))),
            };
        }
        if (page == "Ball Prediction")
        {
            return {
                B("enabled", GameEventHookModule::BallPredictionEnabled),
                C4("color", &GameEventHookModule::BallPredictionColor),
                F("line_width", GameEventHookModule::BallPredictionLineWidth),
            };
        }
        if (page == "Boost Pads")
        {
            return {
                B("boost_pad_timers", GameEventHookModule::BoostPadTimers),
                F("boost_pad_marker_scale", GameEventHookModule::BoostPadMarkerScale),
            };
        }
        if (page == "Camera")
        {
            return {
                B("enabled", Events.enableCameraSettings),
                F("distance", Events.cameraDistance),
                F("height", Events.cameraHeight),
                F("angle", Events.cameraAngle),
                F("stiffness", Events.cameraStiffness),
                F("swivel_speed", Events.cameraSwivelSpeed),
                F("transition_speed", Events.cameraTransitionSpeed),
            };
        }
        if (page == "World")
        {
            return {
                F("time_dilation", Events.timeDilation),
                F("gravity_z", Events.worldGravityZ),
            };
        }
        if (page == "Other")
        {
            return {
                B("username_changer_enabled", GameEventHookModule::UsernameChangerEnabled),
                B("username_invisible", GameEventHookModule::UsernameInvisible),
                T("username_changer_text", GameEventHookModule::UsernameChangeText, static_cast<int>(sizeof(GameEventHookModule::UsernameChangeText))),
                B("enemy_reset_indicator", GameEventHookModule::EnemyResetIndicatorEnabled),
            };
        }

                                                                          
        return {};
    }

    std::vector<std::string> List(const std::string& page)
    {
        std::vector<std::string> names;
        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        for (auto it = node["presets"].begin(); it != node["presets"].end(); ++it)
            names.push_back(it.key());
        std::sort(names.begin(), names.end());
        return names;
    }

    bool Save(const std::string& page, const std::string& name)
    {
        if (name.empty()) return false;
        if (page == "ALL")
        {
            nlohmann::json all = nlohmann::json::object();
            for (const std::string& childPage : PageNames())
            {
                if (childPage == "ALL") continue;
                const std::vector<Field> childFields = PageFields(childPage);
                if (!childFields.empty())
                    all[childPage] = ModPresetsFieldsToJson(childFields);
            }
            GameEventHookModule::SaveConfig();
            std::ifstream configIn(GameEventHookModule::ConfigFilePath);
            if (configIn.is_open())
            {
                try
                {
                    nlohmann::json config;
                    configIn >> config;
                    if (config.is_object()) all["__config"] = std::move(config);
                }
                catch (...) {}
            }
            nlohmann::json root = LoadModPresetsFile();
            nlohmann::json& node = ModPresetsPageNode(root, page);
            node["presets"][name] = all;
            SaveModPresetsFile(root);
            return true;
        }
        const std::vector<Field> fields = PageFields(page);
        if (fields.empty()) return false;

        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        node["presets"][name] = ModPresetsFieldsToJson(fields);
        SaveModPresetsFile(root);
        return true;
    }

    bool Load(const std::string& page, const std::string& name)
    {
        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        if (!node["presets"].contains(name)) return false;

        if (page == "ALL")
        {
            const nlohmann::json& all = node["presets"][name];
            if (!all.is_object()) return false;
            if (all.contains("__config") && all["__config"].is_object())
            {
                if (GameEventHookModule::ConfigFilePath.empty())
                    GameEventHookModule::SaveConfig();
                std::ofstream configOut(GameEventHookModule::ConfigFilePath);
                if (!configOut.is_open()) return false;
                configOut << all["__config"].dump(4);
                configOut.close();
                g_loadingAllSnapshot = true;
                GameEventHookModule::LoadConfig();
                g_loadingAllSnapshot = false;
                return true;
            }
            bool loaded = false;
            for (const std::string& childPage : PageNames())
            {
                if (childPage == "ALL" || !all.contains(childPage)) continue;
                const std::vector<Field> childFields = PageFields(childPage);
                if (childFields.empty()) continue;
                ModPresetsJsonToFields(all[childPage], childFields);
                loaded = true;
            }
            return loaded;
        }

        const std::vector<Field> fields = PageFields(page);
        if (fields.empty()) return false;

        ModPresetsJsonToFields(node["presets"][name], fields);
                                                                                
                                                                             
                                                                             
                                              
        return true;
    }

    bool Delete(const std::string& page, const std::string& name)
    {
        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        if (!node["presets"].contains(name)) return false;
        node["presets"].erase(name);
        if (node.value("favorite", std::string()) == name)
            node["favorite"] = "";
        SaveModPresetsFile(root);
        return true;
    }

    void SetFavorite(const std::string& page, const std::string& name)
    {
        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        node["favorite"] = name;
        SaveModPresetsFile(root);
    }

    std::string GetFavorite(const std::string& page)
    {
        nlohmann::json root = LoadModPresetsFile();
        nlohmann::json& node = ModPresetsPageNode(root, page);
        return node.value("favorite", std::string());
    }

    void ApplyFavoritesOnStartup()
    {
        if (g_loadingAllSnapshot) return;
        for (const std::string& page : PageNames())
        {
            const std::string fav = GetFavorite(page);
            if (!fav.empty())
                Load(page, fav);
        }
    }
}
