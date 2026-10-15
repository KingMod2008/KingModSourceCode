#pragma once
#include "../../BaseInc.h"
#include "../Car/Car.h"
#include "../Ball/Ball.h"
#include "../BoostPad/BoostPad.h"
#include "../CollisionMasks.h"

#include "../../CollisionMeshFile/CollisionMeshFile.h"
#include "../BoostPad/BoostPadGrid/BoostPadGrid.h"
#include "../MutatorConfig/MutatorConfig.h"
#include "ArenaConfig/ArenaConfig.h"
#include "DropshotTiles/DropshotTiles.h"

#include "../../../libsrc/bullet3-3.24/BulletCollision/BroadphaseCollision/btDbvtBroadphase.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionShapes/btStaticPlaneShape.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "../../../libsrc/bullet3-3.24/BulletDynamics/ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "../../../libsrc/bullet3-3.24/BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionDispatch/btDefaultCollisionConfiguration.h"

RS_NS_START

typedef std::function<void(class Arena* arena, Team scoringTeam, void* userInfo)> GoalScoreEventFn;
typedef std::function<void(class Arena* arena, Car* bumper, Car* victim, bool isDemo, void* userInfo)> CarBumpEventFn;

                                        
                                                                                  
class Arena {
public:

	GameMode gameMode;

	uint32_t _lastCarID = 0;
	std::unordered_set<Car*> _cars;
	bool ownsCars = true;                                                          

	std::unordered_map<uint32_t, Car*> _carIDMap;
	
	Ball* ball;
	bool ownsBall = true;                                                          
	
	std::vector<BoostPad*> _boostPads;
	bool ownsBoostPads = true;                                                               
	
	BoostPadGrid _boostPadGrid;

	MutatorConfig _mutatorConfig;

	DropshotTilesState _dropshotTilesState;

	const MutatorConfig& GetMutatorConfig() { return _mutatorConfig; }
	void SetMutatorConfig(const MutatorConfig& mutatorConfig);

	                                         
	float tickTime; 

	                         
	float GetTickRate() const {
		return 1 / tickTime;
	}

	                                                                       
	uint64_t tickCount = 0;

	const std::unordered_set<Car*>& GetCars() { return _cars; }
	const std::vector<BoostPad*>& GetBoostPads() { return _boostPads; }

	                                                        
	bool _AddCarFromPtr(Car* car);
	Car* AddCar(Team team, const CarConfig& config = CAR_CONFIG_OCTANE);

	                                                             
	bool RemoveCar(uint32_t id);

	                                                          
	                                                                                           
	bool RemoveCar(Car* car) {
		return RemoveCar(car->id);
	}

	Car* GetCar(uint32_t id);

	btDiscreteDynamicsWorld _bulletWorld;
	struct {
		btDefaultCollisionConfiguration collisionConfig;
		btCollisionDispatcher collisionDispatcher;
		btOverlappingPairCache* overlappingPairCache;
		btBroadphaseInterface* broadphase;
		btSequentialImpulseConstraintSolver constraintSolver;
	} _bulletWorldParams;

	std::vector<btRigidBody*> _worldCollisionRBs = {};
	std::vector<btBvhTriangleMeshShape*> _worldCollisionBvhShapes = {};
	std::vector<btStaticPlaneShape*> _worldCollisionPlaneShapes = {};
	std::vector<btRigidBody*> _worldDropshotTileRBs = {};

	struct {
		GoalScoreEventFn func = NULL;
		void* userInfo = NULL;
	} _goalScoreCallback;
	void SetGoalScoreCallback(GoalScoreEventFn callbackFn, void* userInfo = NULL);

	struct {
		CarBumpEventFn func = NULL;
		void* userInfo = NULL;
	} _carBumpCallback;
	void SetCarBumpCallback(CarBumpEventFn callbackFn, void* userInfo = NULL);

	                                            
	static Arena* Create(GameMode gameMode, const ArenaConfig& arenaConfig = {}, float tickRate = 120);
	
	                                                                   
	void Serialize(DataStreamOut& out) const;

	                                      
	static Arena* DeserializeNew(DataStreamIn& in);

	Arena(const Arena& other) = delete;                                                   
	Arena& operator =(const Arena& other) = delete;                                                

	Arena(Arena&& other) = delete;                       
	Arena& operator =(Arena&& other) = delete;                    

	                               
	Arena* Clone(bool copyCallbacks);

	                                    
	Car* DeserializeNewCar(DataStreamIn& in, Team team);

	                                                               
	void Step(int ticksToSimulate = 1);

	void ResetToRandomKickoff(int seed = -1);

	                                                                                              
	                                                                            
	                                                                
	                                                                                        
	bool IsBallProbablyGoingIn(float maxTime = 2.f, float extraMargin = 0, Team* goalTeamOut = NULL) const;

	                                         
	                                                         
	bool IsBallScored() const;

	                             
	~Arena();

	                                                                       
	                                                                                   
	btRigidBody* _AddStaticCollisionShape(
		btCollisionShape* shape,
		btVector3 posBT = btVector3(0, 0, 0),
		int group = 0, int mask = 0);

	void _SetupArenaCollisionShapes();

	                                                                            
	static bool _BulletContactAddedCallback(
		btManifoldPoint& cp,
		const btCollisionObjectWrapper* colObjA, int partID_A, int indexA,
		const btCollisionObjectWrapper* colObjB, int partID_B, int indexB
	);

	void _BtCallback_OnCarBallCollision(Car* car, Ball* ball, btManifoldPoint& manifoldPoint, bool ballIsBodyA);
	void _BtCallback_OnCarCarCollision(Car* car1, Car* car2, btManifoldPoint& manifoldPoint);
	void _BtCallback_OnCarWorldCollision(Car* car, btCollisionObject* worldObject, btManifoldPoint& manifoldPoint);

	const ArenaConfig& GetArenaConfig() const {
		return _config;
	}

	                          
	ArenaMemWeightMode GetMemWeightMode() {
		return _config.memWeightMode;
	}

	DropshotTilesState GetDropshotTilesState() const { return _dropshotTilesState; };
	void SetDropshotTilesState(const DropshotTilesState& tilesState);

private:
	
	                                         
	Arena(GameMode gameMode, const ArenaConfig& config, float tickRate = 120);

	                                                                                     
	ArenaConfig _config;
};

RS_NS_END