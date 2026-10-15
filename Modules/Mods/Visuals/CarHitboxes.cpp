#include "CarHitboxes.hpp"
#include "../../../ImGui/imgui.h"
#include "../../Includes.hpp"
#include <tuple>
#include <cstring>

                                                                
extern std::tuple<FVector, FVector, FVector> get_axes(FRotator rotation);

namespace Visuals
{
	static bool TryReadMemoryLocal(uintptr_t address, void* outBuffer, size_t size)
	{
		__try { memcpy(outBuffer, reinterpret_cast<void*>(address), size); return true; }
		__except (EXCEPTION_EXECUTE_HANDLER) { return false; }
	}

	template<typename T>
	static T SafeReadLocal(uintptr_t address)
	{
		T result = T{};
		TryReadMemoryLocal(address, &result, sizeof(T));
		return result;
	}

	static FVector getLocalCollisionOffset(ACar_TA* car) {
		return car->LocalCollisionOffset;
	}

	static FVector getLocalCollisionExtent(ACar_TA* car) {
		return car->LocalCollisionExtent;
	}

	void DrawCarHitboxes()
	{
		if (!GameEventHookModule::IsInitialized || !GameEventHookModule::IsInGame) return;
		if (!GameEventHookModule::Hitboxes) return;

		ImDrawList* drawList = ImGui::GetBackgroundDrawList();
		if (!drawList) return;

		if (!GameEventHookModule::CurrentGameEvent) return;
		TArray<ACar_TA*> cars = GameEventHookModule::CurrentGameEvent->Cars;

		for (ACar_TA* car : cars) {
			if (!car) continue;

			FVector car_location = car->Location;
			FRotator car_rotation = car->Rotation;
			FVector hitbox_offset = getLocalCollisionOffset(car);
			FVector hitbox_extent = getLocalCollisionExtent(car);

			auto [axis_x, axis_y, axis_z] = get_axes(car_rotation);

			FVector world_offset;
			world_offset.X = axis_x.X * hitbox_offset.X + axis_y.X * hitbox_offset.Y + axis_z.X * hitbox_offset.Z;
			world_offset.Y = axis_x.Y * hitbox_offset.X + axis_y.Y * hitbox_offset.Y + axis_z.Y * hitbox_offset.Z;
			world_offset.Z = axis_x.Z * hitbox_offset.X + axis_y.Z * hitbox_offset.Y + axis_z.Z * hitbox_offset.Z;

			FVector hitbox_center;
			hitbox_center.X = car_location.X + world_offset.X;
			hitbox_center.Y = car_location.Y + world_offset.Y;
			hitbox_center.Z = car_location.Z + world_offset.Z;

			FVector corners_local[8] = {
				{-hitbox_extent.X, -hitbox_extent.Y, -hitbox_extent.Z}, { hitbox_extent.X, -hitbox_extent.Y, -hitbox_extent.Z},
				{ hitbox_extent.X,  hitbox_extent.Y, -hitbox_extent.Z}, {-hitbox_extent.X,  hitbox_extent.Y, -hitbox_extent.Z},
				{-hitbox_extent.X, -hitbox_extent.Y,  hitbox_extent.Z}, { hitbox_extent.X, -hitbox_extent.Y,  hitbox_extent.Z},
				{ hitbox_extent.X,  hitbox_extent.Y,  hitbox_extent.Z}, {-hitbox_extent.X,  hitbox_extent.Y,  hitbox_extent.Z}
			};

			FVector corners_world[8];
			for (int i = 0; i < 8; ++i) {
				FVector rotated_corner;
				rotated_corner.X = axis_x.X * corners_local[i].X + axis_y.X * corners_local[i].Y + axis_z.X * corners_local[i].Z;
				rotated_corner.Y = axis_x.Y * corners_local[i].X + axis_y.Y * corners_local[i].Y + axis_z.Y * corners_local[i].Z;
				rotated_corner.Z = axis_x.Z * corners_local[i].X + axis_y.Z * corners_local[i].Y + axis_z.Z * corners_local[i].Z;
				corners_world[i].X = hitbox_center.X + rotated_corner.X;
				corners_world[i].Y = hitbox_center.Y + rotated_corner.Y;
				corners_world[i].Z = hitbox_center.Z + rotated_corner.Z;
			}

			FVector2D screen_corners[8];
			float depths[8];
			bool valid_corners[8];
			for (int i = 0; i < 8; ++i) {
				valid_corners[i] = GameEventHookModule::WorldToScreen(corners_world[i], screen_corners[i], depths[i]);
			}
			int edges[12][2] = { {0,1},{1,2},{2,3},{3,0},{4,5},{5,6},{6,7},{7,4},{0,4},{1,5},{2,6},{3,7} };
			float avg_depth = 0.0f; int valid_depth_count = 0;
			for (int i = 0; i < 8; ++i) { if (valid_corners[i]) { avg_depth += depths[i]; valid_depth_count++; } }
			if (valid_depth_count > 0) avg_depth /= valid_depth_count;
			float thickness = (std::max)(0.5f, (std::min)(2000.0f / avg_depth, 3.0f));
			ImU32 hitbox_color = ImGui::ColorConvertFloat4ToU32(GameEventHookModule::HitboxColor);
			for (int i = 0; i < 12; ++i) {
				int p1_idx = edges[i][0]; int p2_idx = edges[i][1];
				if (valid_corners[p1_idx] && valid_corners[p2_idx]) {
					drawList->AddLine(
						ImVec2(screen_corners[p1_idx].X, screen_corners[p1_idx].Y),
						ImVec2(screen_corners[p2_idx].X, screen_corners[p2_idx].Y),
						hitbox_color, thickness);
				}
			}
		}
	}
}


