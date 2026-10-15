#pragma once
#include "../Component.hpp"
#include "../../resource.h"
#include <d3d11.h>
#include <string>
#include <atomic>
#include "Items.hpp"
#include "../ImGui/imgui.h"

extern std::atomic<bool> g_DllUnloading;

class GUIComponent : public Component
{
public:
	GUIComponent();
	~GUIComponent() override;

public:
	void OnCreate() override;
	void OnDestroy() override;
	
	                                           
	static void Initialize();
	static void Unload();

	                                                                         
	                                                                          
	                                                                            
	static void RequestUnload();

public:
	static HANDLE InterfaceThread;
	static HINSTANCE DllModule;
	static bool IsOpen;
	static bool showFPSCounter;
	static float fpsCounterSize;
	static ImVec2 fpsCounterPos;
	static int lowFPScounter;
	static int midFPScounter;
	int DisplayX;
	int DisplayY;

public:
	static void InitImGui();
	static void InitMainTab();
	static LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static void Render();
	static void NotifyTradeUpSimulatorItemSpawned(int itemId, int quantity = 1, const std::string& source = "");

public:
	               
	static ImFont* FontKingRegular;
	static ImFont* FontKingMedium;
	static ImFont* FontKingItalic;
	static ImFont* FontKingMono;		                                        

private:
	static void RenderFPSCounter();
	static char notificationTitle[128];
	static char notificationContent[256];
	static int notificationDuration;
	static char chatMessage[128];
	static bool isTeamChat;
	static int selectedQuickChatIndex;
};

extern class GUIComponent GUI;
