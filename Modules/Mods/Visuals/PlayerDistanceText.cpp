#include "PlayerDistanceText.hpp"
#include "../../../ImGui/imgui.h"
#include <cmath>

namespace Visuals
{
	void DrawPlayerDistanceText()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::PlayerDistanceTextEnabled) return;

		const GameTickPacket& pkt = GameEventHookModule::CurrentGameTickPacket;
		if (pkt.num_cars <= 0 || pkt.localPlayerIndex < 0 || pkt.localPlayerIndex >= pkt.num_cars) return;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		if (!drawList) return;

		Vector3 localPos = pkt.game_cars[pkt.localPlayerIndex].physics.location;

		for (int i = 0; i < pkt.num_cars; ++i)
		{
			if (i == pkt.localPlayerIndex) continue;
			const auto& car = pkt.game_cars[i];

			float dx = car.physics.location.x - localPos.x;
			float dy = car.physics.location.y - localPos.y;
			float dz = car.physics.location.z - localPos.z;
			float distUU = std::sqrt(dx*dx + dy*dy + dz*dz);
			float distMeters = distUU / 100.0f;

			FVector world; world.X = car.physics.location.x; world.Y = car.physics.location.y; world.Z = car.physics.location.z + 80.0f;
			FVector2D screen; float depth = 0.0f;
			if (!GameEventHookModule::WorldToScreen(world, screen, depth)) continue;

			char buf[32];
			snprintf(buf, sizeof(buf), "%.1fm", distMeters);
			ImU32 color = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::PlayerDistanceTextColor);
			drawList->AddText(ImVec2(screen.X, screen.Y), color, buf);
		}
	}
}


