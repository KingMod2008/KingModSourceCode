#pragma once
#include "../Component.hpp"
#include <mutex>
#include <utility>

class MainComponent : public Component
{
public:
	MainComponent();
	~MainComponent() override;

	void OnCreate() override;
	void OnDestroy() override;

	void Initialize();

public:
	static std::vector<std::function<void()>> GameFunctions;
	static std::mutex GameFunctionsMutex;

	static void Execute(std::function<void()> FunctionToExecute)
	{
		if (!FunctionToExecute)
			return;
		std::lock_guard<std::mutex> lock(GameFunctionsMutex);
		GameFunctions.push_back(std::move(FunctionToExecute));
	}

	void ReadyUp();
	void Forfeit();

	static UNotification_TA* SpawnNotification(const std::string& Title, const std::string& Content, int Duration, UClass* NotificationClass = nullptr);
	                                                                            
	static void SpawnItemShopToast(const std::string& Title, const std::string& Content, int Duration);
	static void SendChatMessage(const std::string& message, bool isTeamChat);
	static void SendQuickChatMessage(const FName& MessageId, bool isTeamChat);
	static bool SpawnItem(int productId, int seriesId, int tradeHold, std::string spawnMsg, bool doAnim);
	static void AddSplitscreenPlayer();
	void StartMatchmaking();
	void LeaveMatch();
};

extern class MainComponent Main;
