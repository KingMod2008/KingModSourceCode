#pragma once
#include "../Framework.h"

RS_NS_START

enum class GameMode : byte {
	SOCCAR,
	HOOPS,
	HEATSEEKER,
	SNOWDAY,
	DROPSHOT,

	                                                                                                                                       

	                                                                                                   
	THE_VOID,
};

constexpr const char* GAMEMODE_STRS[] = {
	"soccar",
	"hoops",
	"heatseeker",
	"snowday",
	"dropshot",
	"void"
};

RS_NS_END