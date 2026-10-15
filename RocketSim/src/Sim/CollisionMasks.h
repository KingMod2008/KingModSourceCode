#pragma once
#include "../Framework.h"

RS_NS_START

                                                 
                                                              
enum CollisionMasks : uint32_t {
	HOOPS_NET = (1 << 8),
	DROPSHOT_TILE = (1 << 9),
	DROPSHOT_FLOOR = (1 << 10),
};

RS_NS_END