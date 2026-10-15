#pragma once
#include "Sim/Car/Car.h"
#include "Sim/Ball/Ball.h"
#include "Sim/Arena/Arena.h"

#include "Math/Math.h"

                                
                                                                             
                                                         
                                                                                               

class btBvhTriangleMeshShape;

namespace RocketSim {
	enum class RocketSimStage : byte {
		UNINITIALIZED,
		INITIALIZING,
		INITIALIZED
	};

	typedef std::vector<byte> FileData;

	extern std::filesystem::path _collisionMeshesFolder;
	extern std::mutex _beginInitMutex;

	void Init(std::filesystem::path collisionMeshesFolder, bool silent = false);

	                                                                                                      
	                                                                                                         
	                                                 
	void InitFromMem(const std::map<GameMode, std::vector<FileData>>& meshFilesMap, bool silent = false);

	void AssertInitialized(const char* errorMsgPrefix);

	RocketSimStage GetStage();

	std::vector<btBvhTriangleMeshShape*>& GetArenaCollisionShapes(GameMode gameMode);
}