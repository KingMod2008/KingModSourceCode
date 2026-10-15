#include "VelocityArrows.hpp"
#include "../../../ImGui/imgui.h"
#include <cmath>

namespace
{
	static inline void drawArrow2D(ImDrawList* dl, ImVec2 p0, ImVec2 p1, ImU32 color, float thickness)
	{
		dl->AddLine(p0, p1, color, thickness);
		                             
		ImVec2 dir = ImVec2(p1.x - p0.x, p1.y - p0.y);
		float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
		if (len < 1.0f) return;
		dir.x /= len; dir.y /= len;
		ImVec2 perp = ImVec2(-dir.y, dir.x);
		float headLen = 10.0f + thickness * 1.5f;
		float headWidth = 6.0f + thickness;
		ImVec2 left = ImVec2(p1.x - dir.x * headLen + perp.x * headWidth, p1.y - dir.y * headLen + perp.y * headWidth);
		ImVec2 right = ImVec2(p1.x - dir.x * headLen - perp.x * headWidth, p1.y - dir.y * headLen - perp.y * headWidth);
		dl->AddLine(p1, left, color, thickness);
		dl->AddLine(p1, right, color, thickness);
	}
}

namespace Visuals
{
	void DrawVelocityArrows()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::VelocityArrowsEnabled) return;

		const GameTickPacket& pkt = GameEventHookModule::CurrentGameTickPacket;
		if (pkt.num_cars <= 0) return;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		if (!drawList) return;

		                                
		auto w2s = [](const Vector3& v, ImVec2& out) -> bool
		{
			FVector w; w.X = v.x; w.Y = v.y; w.Z = v.z;
			FVector2D s; float d = 0.0f;
			if (!GameEventHookModule::WorldToScreen(w, s, d)) return false;
			out = ImVec2(s.X, s.Y);
			return true;
		};

		                      
		{
			ImVec2 s0, s1;
			Vector3 start = pkt.game_ball.physics.location;
			Vector3 vel = pkt.game_ball.physics.velocity;
			float speed = std::sqrt(vel.x*vel.x + vel.y*vel.y + vel.z*vel.z);
			if (speed > 10.0f)
			{
				float scale = 0.08f;                                              
				Vector3 end = { start.x + vel.x * scale, start.y + vel.y * scale, start.z + vel.z * scale };
				if (w2s(start, s0) && w2s(end, s1))
				{
					float thickness = 2.0f;
					ImU32 color = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::VelocityArrowBallColor);
					drawArrow2D(drawList, s0, s1, color, thickness);
				}
			}
		}

		                                            
		for (int i = 0; i < pkt.num_cars; ++i)
		{
			if (pkt.localPlayerIndex >= 0 && i == pkt.localPlayerIndex) continue;
			const auto& car = pkt.game_cars[i];
			ImVec2 s0, s1;
			Vector3 start = car.physics.location;
			Vector3 vel = car.physics.velocity;
			float speed = std::sqrt(vel.x*vel.x + vel.y*vel.y + vel.z*vel.z);
			if (speed <= 10.0f) continue;

			float scale = 0.06f;
			Vector3 end = { start.x + vel.x * scale, start.y + vel.y * scale, start.z + vel.z * scale };
			if (w2s(start, s0) && w2s(end, s1))
			{
				float thickness = 2.0f;
				ImU32 color = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::VelocityArrowCarColor);
				drawArrow2D(drawList, s0, s1, color, thickness);
			}
		}
	}
}


