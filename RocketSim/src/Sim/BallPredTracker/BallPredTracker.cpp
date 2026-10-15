#include "BallPredTracker.h"

RS_NS_START

BallPredTracker::BallPredTracker(Arena* arena, size_t numPredTicks) : numPredTicks(numPredTicks) {
	                       
	this->ballPredArena = Arena::Create(arena->gameMode, arena->GetArenaConfig(), arena->GetTickRate());
	lastUpdateTickCount = 0;

	predData.reserve(numPredTicks);
	UpdatePredFromArena(arena);
}

BallPredTracker::~BallPredTracker() {
	delete this->ballPredArena;
}

void BallPredTracker::UpdatePredFromArena(Arena* arena) {
	BallState bs = arena->ball->GetState();

	int ticksSinceLastUpdate = arena->tickCount - lastUpdateTickCount;
	UpdatePredManual(bs, ticksSinceLastUpdate);
}

void BallPredTracker::UpdatePredManual(const BallState& curBallState, int ticksSinceLastUpdate) {

	bool needsFullRepred;
	if (ticksSinceLastUpdate < predData.size()) {
		
		if (predData[ticksSinceLastUpdate].Matches(curBallState)) {
			                                     
			needsFullRepred = false;

			if (ticksSinceLastUpdate > 0) {
				                                                                                
				predData.erase(predData.begin(), predData.begin() + ticksSinceLastUpdate);

				                                                 
				ballPredArena->ball->SetState(predData.back());
				while (predData.size() < numPredTicks) {
					ballPredArena->Step(1);
					predData.push_back(ballPredArena->ball->GetState());
				}
			} else {
				                              
			}
		} else {
			needsFullRepred = true;
		}
 
	} else {
		needsFullRepred = true;
	}

	if (needsFullRepred) {
		                              
		ForceUpdateAllPred(curBallState);
	}

	lastUpdateTickCount += ticksSinceLastUpdate;
}

void BallPredTracker::ForceUpdateAllPred(const BallState& initialBallState) {
	ballPredArena->ball->SetState(initialBallState);
	predData.resize(numPredTicks);
	predData[0] = initialBallState;
	for (size_t i = 1; i < numPredTicks; i++) {
		ballPredArena->Step();
		predData[i] = ballPredArena->ball->GetState();
	}
}

BallState BallPredTracker::GetBallStateForTime(float predTime) const {
	if (predData.empty())
		RS_ERR_CLOSE("BallPredTracker::GetBallStateForTime(): Predicted ball data is empty, update prediction before calling");

	int index = RS_CLAMP(predTime / ballPredArena->tickTime, 0, predData.size() - 1);
	return predData[index];
}

RS_NS_END