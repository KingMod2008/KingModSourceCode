#pragma once
#include "../../BaseInc.h"

RS_NS_START

struct PhysState {
	                               
	Vec pos = {};
	
	                                 
	RotMat rotMat = RotMat::GetIdentity();

	                  
	Vec vel = {};

	                           
	Vec angVel = {};

	                                                              
	                                                             
	PhysState GetInvertedY() const;
};

RS_NS_END