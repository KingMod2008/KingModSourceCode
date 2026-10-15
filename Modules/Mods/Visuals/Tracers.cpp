#include "Tracers.hpp"
#include "../../../ImGui/imgui.h"
#include <cmath>

namespace
{
	inline ImU32 teamColor(uint8_t team)
	{
		                     
		return team == 0 ? IM_COL32(0, 100, 255, 230) : IM_COL32(255, 128, 0, 230);
	}
}

namespace Visuals
{
	void DrawTracers()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::TracersEnabled) return;

		const GameTickPacket& pkt = GameEventHookModule::CurrentGameTickPacket;
		if (pkt.num_cars <= 0 || pkt.localPlayerIndex < 0 || pkt.localPlayerIndex >= pkt.num_cars) return;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		if (!drawList) return;

		                                    
		FVector localWorld;
		localWorld.X = pkt.game_cars[pkt.localPlayerIndex].physics.location.x;
		localWorld.Y = pkt.game_cars[pkt.localPlayerIndex].physics.location.y;
		localWorld.Z = pkt.game_cars[pkt.localPlayerIndex].physics.location.z;

		FVector2D startScreen; float startDepth = 0.0f;
		if (!GameEventHookModule::WorldToScreen(localWorld, startScreen, startDepth)) return;

		const ImU32 defaultColor = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::TracersColor);
		const float thickness = 2.5f;

		for (int i = 0; i < pkt.num_cars; ++i)
		{
			if (i == pkt.localPlayerIndex) continue;
			const auto& car = pkt.game_cars[i];

			FVector targetWorld;
			targetWorld.X = car.physics.location.x;
			targetWorld.Y = car.physics.location.y;
			targetWorld.Z = car.physics.location.z;

			FVector2D endScreen; float endDepth = 0.0f;
			if (!GameEventHookModule::WorldToScreen(targetWorld, endScreen, endDepth)) continue;

			ImU32 color = defaultColor;
			if (GameEventHookModule::UseTeamColorsForTracers)
				color = teamColor(car.team);

			drawList->AddLine(ImVec2(startScreen.X, startScreen.Y), ImVec2(endScreen.X, endScreen.Y), color, thickness);
		}
	}
}


