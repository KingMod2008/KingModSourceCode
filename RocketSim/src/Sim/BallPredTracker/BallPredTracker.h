#pragma once
#include "../Arena/Arena.h"

RS_NS_START

                                                                  
struct BallPredTracker {
	Arena* ballPredArena;
	std::vector<BallState> predData;
	size_t numPredTicks;

	int lastUpdateTickCount;

	                                                                                                              
	                                                                                 
	BallPredTracker(Arena* arena, size_t numPredTicks);
	~BallPredTracker();

	             
	BallPredTracker(const BallPredTracker& other) = delete;
	BallPredTracker& operator=(const BallPredTracker& other) = delete;

	                                                                                                  
	                                                                                                                
	void UpdatePredFromArena(Arena* arena);

	                                                                       
	                                                                                                            
	void UpdatePredManual(const BallState& curBallState, int ticksSinceLastUpdate);

	                                   
	void ForceUpdateAllPred(const BallState& initialBallState);

	                                                            
	BallState GetBallStateForTime(float predTime) const;
};

RS_NS_END