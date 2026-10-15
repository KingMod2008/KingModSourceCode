#include "BallSphere.hpp"
#include "../../../ImGui/imgui.h"

namespace Visuals
{
	static void DrawWireSphereProjected(const FVector& center, float radius, int segments,
		const ImU32 color)
	{
		ImDrawList* draw = ImGui::GetForegroundDrawList();
		if (!draw) return;

		                 
		for (int i = 0; i <= segments; ++i)
		{
			float lat = 3.1415926f * (-0.5f + (float)i / segments);
			float cosLat = cosf(lat);
			float sinLat = sinf(lat);

			ImVec2 prev{}; bool prevValid = false;
			for (int j = 0; j <= segments; ++j)
			{
				float lon = 2.0f * 3.1415926f * (float)j / segments;
				float cosLon = cosf(lon);
				float sinLon = sinf(lon);

				FVector p;
				p.X = center.X + radius * cosLat * cosLon;
				p.Y = center.Y + radius * cosLat * sinLon;
				p.Z = center.Z + radius * sinLat;

				FVector2D screen; float depth;
				if (GameEventHookModule::WorldToScreen(p, screen, depth))
				{
					ImVec2 cur(screen.X, screen.Y);
					if (prevValid)
						draw->AddLine(prev, cur, color);
					prev = cur; prevValid = true;
				}
				else prevValid = false;
			}
		}

		                  
		for (int j = 0; j <= segments; ++j)
		{
			float lon = 2.0f * 3.1415926f * (float)j / segments;
			float cosLon = cosf(lon);
			float sinLon = sinf(lon);

			ImVec2 prev{}; bool prevValid = false;
			for (int i = 0; i <= segments; ++i)
			{
				float lat = 3.1415926f * (-0.5f + (float)i / segments);
				float cosLat = cosf(lat);
				float sinLat = sinf(lat);

				FVector p;
				p.X = center.X + radius * cosLat * cosLon;
				p.Y = center.Y + radius * cosLat * sinLon;
				p.Z = center.Z + radius * sinLat;

				FVector2D screen; float depth;
				if (GameEventHookModule::WorldToScreen(p, screen, depth))
				{
					ImVec2 cur(screen.X, screen.Y);
					if (prevValid)
						draw->AddLine(prev, cur, color);
					prev = cur; prevValid = true;
				}
				else prevValid = false;
			}
		}
	}

	void DrawBallSphere()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::Ball3DSphereEnabled) return;
		const PrivBallInfo& ball = GameEventHookModule::CurrentBall;
		if (!ball.IsValid) return;

		ImU32 color = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::Ball3DSphereColor);
		float radius = ball.Radius;            
		int segments = 12;
		DrawWireSphereProjected(ball.Location, radius, segments, color);
	}
}


