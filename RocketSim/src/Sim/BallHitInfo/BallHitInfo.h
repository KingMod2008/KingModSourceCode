#pragma once

#include "../../RLConst.h"
#include "../../DataStream/DataStreamIn.h"
#include "../../DataStream/DataStreamOut.h"

RS_NS_START

struct BallHitInfo {
	                                                                      
	bool isValid = false;

	Vec relativePosOnBall;                                                       
	Vec ballPos;                                                   
	Vec extraHitVel;                                                   

	                                        
	uint64_t tickCountWhenHit = ~0ULL; 

	                                                                        
	                                                                                                 
	uint64_t tickCountWhenExtraImpulseApplied = ~0ULL;

	void Serialize(DataStreamOut& out) const;
	void Deserialize(DataStreamIn& in);
};

                                 
#define BALLHITINFO_SERIALIZATION_FIELDS \
relativePosOnBall, ballPos, extraHitVel, tickCountWhenHit, tickCountWhenExtraImpulseApplied

RS_NS_END