#pragma once
#include "../../../BaseInc.h"

RS_NS_START

struct WheelPairConfig {
	                        
	float wheelRadius;

	                                   
	float suspensionRestLength;

	                                                                
	                                                                                                       
	Vec connectionPointOffset;
};

#define WHEEL_PAIR_CONFIG_SERIALIZATION_FIELDS(name) \
name.connectionPointOffset, name.suspensionRestLength, name.wheelRadius

struct CarConfig {
	                                                 
	Vec hitboxSize;

	                                          
	                                                                             
	Vec hitboxPosOffset;

	WheelPairConfig frontWheels, backWheels;

	                                          
	                                                                       
	                                              
	bool threeWheels = false;

	                                                                      
	float dodgeDeadzone = 0.5f;
};

#define CAR_CONFIG_SERIALIZATION_FIELDS(name) \
name.dodgeDeadzone, name.hitboxPosOffset, name.hitboxSize, \
WHEEL_PAIR_CONFIG_SERIALIZATION_FIELDS(name.frontWheels), \
WHEEL_PAIR_CONFIG_SERIALIZATION_FIELDS(name.backWheels) \

                                                     
                                                 
const extern CarConfig
	CAR_CONFIG_OCTANE, CAR_CONFIG_DOMINUS, CAR_CONFIG_PLANK, CAR_CONFIG_BREAKOUT, CAR_CONFIG_HYBRID, CAR_CONFIG_MERC, CAR_CONFIG_PSYCLOPS;

RS_NS_END