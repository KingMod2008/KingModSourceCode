#pragma once
#include "../../../Math/MathTypes/MathTypes.h"
#include "../../../DataStream/DataStreamOut.h"
#include "../../../DataStream/DataStreamIn.h"

#include "../../BoostPad/BoostPad.h"

RS_NS_START

                                                  
                                                                                        
enum class ArenaMemWeightMode : byte {
	HEAVY,                                  
	LIGHT                                 
	                                     
};

struct ArenaConfig {

	ArenaMemWeightMode memWeightMode = ArenaMemWeightMode::HEAVY;

	                                                      
	Vec minPos = Vec(-5600, -6000, 0),
		maxPos = Vec( 5600,  6000, 2200);
	
	                               
	                                                       
	float
		maxAABBLen = 370;

	                                                           
	                      
	bool noBallRot = true;

	                                                 
	                                                              
	                                               
	bool useCustomBroadphase = true;

	                            
	int maxObjects = 512;

	                                                                              
	                                                                              
	bool useCustomBoostPads = false;
	std::vector<BoostPadConfig> customBoostPads = {};                                                   

	void Serialize(DataStreamOut& out) const;
	void Deserialize(DataStreamIn& in);
};

#define ARENA_CONFIG_SERIALIZATION_FIELDS \
minPos, maxPos, maxAABBLen, noBallRot, useCustomBroadphase

RS_NS_END