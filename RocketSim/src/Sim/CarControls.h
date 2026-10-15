#pragma once
#include "../BaseInc.h"

RS_NS_START

                                     
struct CarControls {
	                  
	float throttle, steer;

	                          
	float pitch, yaw, roll;

	                        
	bool jump, boost, handbrake;

	                   
	                

	CarControls() {
		                                
		memset(this, 0, sizeof(CarControls));
	}

	                                                     
	void ClampFix() {
		throttle	= RS_CLAMP(throttle,	-1, 1);
		steer		= RS_CLAMP(steer,		-1, 1);
		pitch		= RS_CLAMP(pitch,		-1, 1);
		yaw			= RS_CLAMP(yaw,		-1, 1);
		roll		= RS_CLAMP(roll,		-1, 1);
	}
};

#define CAR_CONTROLS_SERIALIZATION_FIELDS(name) \
name.throttle, name.steer, \
name.pitch, name.yaw, name.roll, \
name.boost, name.jump, name.handbrake

RS_NS_END