#include "Tracers.hpp"
#include "VelocityArrows.hpp"
#include "PlayerDistanceText.hpp"
#include "OpponentBoost.hpp"
#include "BallSphere.hpp"
#include "CarHitboxes.hpp"
#include "../GameEventHook.hpp"

                                                                    
void Visuals_DrawAll()
{
	Visuals::DrawBallSphere();
	Visuals::DrawCarHitboxes();
	Visuals::DrawTracers();
	Visuals::DrawVelocityArrows();
	Visuals::DrawPlayerDistanceText();
	Visuals::DrawOpponentBoost();
	GameEventHookModule::DrawBallPrediction();
}


