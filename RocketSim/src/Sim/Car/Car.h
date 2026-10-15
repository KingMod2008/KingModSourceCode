#pragma once
#include "../PhysState/PhysState.h"
#include "CarConfig/CarConfig.h"
#include "../btVehicleRL/btVehicleRL.h"
#include "../CarControls.h"
#include "../BallHitInfo/BallHitInfo.h"
#include "../MutatorConfig/MutatorConfig.h"

#include "../../../libsrc/bullet3-3.24/BulletDynamics/Dynamics/btRigidBody.h"
#include "../../../libsrc/bullet3-3.24/BulletDynamics/Vehicle/btDefaultVehicleRaycaster.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionShapes/btBoxShape.h"
#include "../../../libsrc/bullet3-3.24/BulletCollision/CollisionShapes/btCompoundShape.h"
#include "../../../src/Sim/btVehicleRL/btVehicleRL.h"

RS_NS_START

struct CarState : public PhysState {

	                                                            
	                                         
	                 
	uint64_t tickCountSinceUpdate = 0;

	                                        
	bool isOnGround = true;

	                                            
	                      
	                                                              
	bool wheelsWithContact[4] = {}; 

	                                        
	                                                                       
	bool hasJumped = false;

	                                                         
	                                                               
	bool hasDoubleJumped = false;

	                                                                          
	bool hasFlipped = false;

	                                        
	                                    
	Vec flipRelTorque = { 0, 0, 0 };

	float jumpTime = 0;                                                                     
	float flipTime = 0;                                                                       

	                                                              
	bool isFlipping = false;

	                     
	bool isJumping = false;

	                              
	float airTime = 0;

	                                        
	                              
	float airTimeSinceJump = 0;

	                     
	float boost = RLConst::BOOST_SPAWN_AMOUNT;

	                                                                  
	float timeSinceBoosted = 0.f;

	                               
	                                                                             
	bool isBoosting = false;
	float boostingTime = 0;

	bool isSupersonic = false;

	                                                                                        
	float supersonicTime = 0;

	                                                                                         
	float handbrakeVal = 0;

	bool isAutoFlipping = false;
	float autoFlipTimer = 0;                                  
	float autoFlipTorqueScale = 0;

	struct {
		bool hasContact = false;
		Vec contactNormal;
	} worldContact;

	struct {
		uint32_t otherCarID = 0;
		float cooldownTimer = 0;
	} carContact;

	bool isDemoed = false;
	float demoRespawnTimer = 0;

	BallHitInfo ballHitInfo = BallHitInfo();

	                                                                  
	CarControls lastControls = CarControls();

	CarState() : PhysState() {
		pos.z = RLConst::CAR_SPAWN_REST_Z;
	}

	                                                                          
	bool HasFlipOrJump() const;

	                                                                                             
	bool HasFlipReset() const;

	                                                                           
	                                                                        
	bool GotFlipReset() const;

	void Serialize(DataStreamOut& out) const;
	void Deserialize(DataStreamIn& in);
};

#define CARSTATE_SERIALIZATION_FIELDS \
pos, rotMat, vel, angVel, isOnGround, hasJumped, hasDoubleJumped, hasFlipped, \
flipRelTorque, jumpTime, isFlipping, flipTime, isJumping, airTimeSinceJump, \
boost, isBoosting, boostingTime, timeSinceBoosted, supersonicTime, handbrakeVal, isAutoFlipping, \
autoFlipTimer, autoFlipTorqueScale, isDemoed, demoRespawnTimer, lastControls, \
worldContact.hasContact, worldContact.contactNormal, \
carContact.otherCarID, carContact.cooldownTimer

enum class Team : byte {
	BLUE = 0,
	ORANGE = 1
};

#define RS_OPPOSITE_TEAM(team) ((team) == Team::BLUE ? Team::ORANGE : Team::BLUE)
#define RS_TEAM_FROM_Y(y) ((y) < 0 ? Team::BLUE : Team::ORANGE)

class Car {
public:
	                             
	CarConfig config;
	Team team;

	                                                          
	                                                                
	uint32_t id;

	                                        
	CarControls controls;

	CarState GetState();
	void SetState(const CarState& state);

	void Demolish(float respawnDelay = RLConst::DEMO_RESPAWN_TIME);

	                                                                                         
	void Respawn(GameMode gameMode, int seed = -1, float boostAmount = RLConst::BOOST_SPAWN_AMOUNT);

	btVehicleRL _bulletVehicle;
	btDefaultVehicleRaycaster _bulletVehicleRaycaster;
	btRigidBody _rigidBody;
	btCompoundShape _compoundShape;
	btBoxShape _childHitboxShape;

	                                                                                     
	                                                          
	CarState _internalState;

	                                             
	Vec GetForwardDir() const {
		return _internalState.rotMat.forward;
	}

	                                               
	Vec GetRightDir() const {
		return _internalState.rotMat.right;
	}

	                                            
	Vec GetUpDir() const {
		return _internalState.rotMat.up;
	}

	void _PreTickUpdate(GameMode gameMode, float tickTime, const MutatorConfig& mutatorConfig);
	void _PostTickUpdate(GameMode gameMode, float tickTime, const MutatorConfig& mutatorConfig);

	Vec _velocityImpulseCache = { 0,0,0 };
	void _FinishPhysicsTick(const MutatorConfig& mutatorConfig);

	void _BulletSetup(GameMode gameMode, class btDynamicsWorld* bulletWorld, const MutatorConfig& mutatorConfig);
	
	                            
	static Car* _AllocateCar() { return new Car(); }

	void Serialize(DataStreamOut& out);
	void _Deserialize(DataStreamIn& in);

	Car(const Car& other) = delete;
	Car& operator=(const Car& other) = delete;

	~Car() {}

private:
	void _UpdateWheels(float tickTime, const MutatorConfig& mutatorConfig, int numWheelsInContact, float forwardSpeed_UU);
	void _UpdateBoost(float tickTime, const MutatorConfig& mutatorConfig, float forwardSpeed_UU);
	void _UpdateJump(float tickTime, const MutatorConfig& mutatorConfig, bool jumpPressed);
	void _UpdateAirTorque(float tickTime, const MutatorConfig& mutatorConfig, bool doAirControl);
	void _UpdateDoubleJumpOrFlip(float tickTime, const MutatorConfig& mutatorConfig, bool jumpPressed, float forwardSpeed_UU);
	void _UpdateAutoFlip(float tickTime, const MutatorConfig& mutatorConfig, bool jumpPressed);
	void _UpdateAutoRoll(float tickTime, const MutatorConfig& mutatorConfig, int numWheelsInContact);

	Car() {}
};

RS_NS_END