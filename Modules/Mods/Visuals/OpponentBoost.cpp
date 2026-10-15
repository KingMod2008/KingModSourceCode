#include "OpponentBoost.hpp"
#include "../../../ImGui/imgui.h"
#include <algorithm>
#include <cfloat>

namespace Visuals
{
	void DrawOpponentBoost()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::OpponentBoostEnabled) return;

		const GameTickPacket& pkt = GameEventHookModule::CurrentGameTickPacket;
		if (pkt.num_cars <= 0) return;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		if (!drawList) return;

		for (int i = 0; i < pkt.num_cars; ++i)
		{
			if (pkt.localPlayerIndex >= 0 && i == pkt.localPlayerIndex) continue;
			const auto& car = pkt.game_cars[i];

			FVector world;
			world.X = car.physics.location.x;
			world.Y = car.physics.location.y;
			world.Z = car.physics.location.z + 120.0f;

			FVector2D screen; float depth = 0.0f;
			if (!GameEventHookModule::WorldToScreen(world, screen, depth)) continue;

			                                                          
			float radius = (std::max)(10.0f, (std::min)(40.0f, 2000.0f / depth)) * GameEventHookModule::OpponentBoostScale;
			ImU32 circleColor = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::OpponentBoostColor);
			
			                                  
			ImVec4 bgColor = GameEventHookModule::OpponentBoostColor;
			bgColor.x *= 0.3f; bgColor.y *= 0.3f; bgColor.z *= 0.3f; bgColor.w *= 0.7f;
			ImU32 bgCircleColor = ImGui::ColorConvertFloat4ToU32(bgColor);
			drawList->AddCircleFilled(ImVec2(screen.X, screen.Y), radius - 1.0f, bgCircleColor, 24);
			
			                                   
			float boostPct = (std::max)(0.0f, (std::min)((float)car.boost, 100.0f));
			if (boostPct > 0.001f) {
				float fillAngle = (boostPct / 100.0f) * 2.0f * 3.14159f;
				float startAngle = 3.14159f / 2.0f;                     
				
				                                                 
				drawList->PathArcTo(ImVec2(screen.X, screen.Y), radius - 1.0f, startAngle, startAngle + fillAngle, 24);
				drawList->PathFillConvex(circleColor);
			}
			
			                      
			drawList->AddCircle(ImVec2(screen.X, screen.Y), radius, circleColor, 24, 2.0f);

			                                 
			int boostPctInt = (int)boostPct;
			char buf[8]; snprintf(buf, sizeof(buf), "%d", boostPctInt);
			ImFont* font = ImGui::GetFont();
			float fontSize = ImGui::GetFontSize() * GameEventHookModule::OpponentBoostScale;
			ImVec2 textSize = font->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, buf);
			ImU32 textColor = IM_COL32(255,255,255, (int)(GameEventHookModule::OpponentBoostColor.w * 255.0f));
			drawList->AddText(font, fontSize, ImVec2(screen.X - textSize.x * 0.5f, screen.Y - textSize.y * 0.5f), textColor, buf);
		}
	}
}


