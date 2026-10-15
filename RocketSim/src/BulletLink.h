#pragma once

                                                                                                       

                                                       
#include "../libsrc/bullet3-3.24/LinearMath/btVector3.h"
#include "../libsrc/bullet3-3.24/LinearMath/btMatrix3x3.h"

#include <ostream>

                                                                   
#define BT_TO_UU (50.f)

                                                                  
#define UU_TO_BT (1.f/50.f)

                                                          
enum : int {
	BT_USERINFO_NONE,

	BT_USERINFO_TYPE_CAR,
	BT_USERINFO_TYPE_BALL,
	BT_USERINFO_TYPE_DROPSHOT_TILE,
};
