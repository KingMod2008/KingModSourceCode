#include "GameEventTracker.h"

RS_NS_START

bool GetShooterPasser(Arena* arena, Team team, Car*& shooterOut, bool findPasser, Car*& passerOut, uint64_t maxShooterTicks, uint64_t maxPasserTicks) {
	shooterOut = passerOut = NULL;
	                                                                                  

	for (Car* car : arena->_cars) {
		if (car->team != team)
			continue;

		if (!car->_internalState.ballHitInfo.isValid)
			continue;

		if (car->_internalState.ballHitInfo.tickCountWhenHit + maxShooterTicks >= arena->tickCount) {
			if (!shooterOut || car->_internalState.ballHitInfo.tickCountWhenHit > shooterOut->_internalState.ballHitInfo.tickCountWhenHit) {
				shooterOut = car;
			}
		}
	}

	if (shooterOut && findPasser) {                   
		uint64_t shootTick = shooterOut->_internalState.ballHitInfo.tickCountWhenHit;

		                        
		for (Car* car : arena->_cars) {
			if (car->team != team)
				continue;

			if (!car->_internalState.ballHitInfo.isValid)
				continue;

			if (car == shooterOut)
				continue;

			if (car->_internalState.ballHitInfo.tickCountWhenHit + maxPasserTicks >= shootTick) {
				if (!passerOut || car->_internalState.ballHitInfo.tickCountWhenHit > passerOut->_internalState.ballHitInfo.tickCountWhenHit) {
					passerOut = car;
				}
			}
		}
	}

	return shooterOut != NULL;
}

void GameEventTracker::Update(Arena* arena) {
	bool scored = arena->IsBallScored();
	
	float tickrate = arena->GetTickRate();
	uint64_t ballUpdateCount = arena->ball->_internalState.tickCountSinceUpdate;

	if (ballUpdateCount > _lastBallUpdateCount || !autoStateSetDetection) {
		                     

		uint64_t deltaTicks = ballUpdateCount - _lastBallUpdateCount;

		                         
		float deltaTime = deltaTicks * arena->tickTime;

		             
		if (scored && !_ballScoredLast) {
			Car* shooter;
			Car* passer;
			if (GetShooterPasser(
				arena,
				RS_TEAM_FROM_Y(-arena->ball->_rigidBody.getWorldTransform().m_origin.y()),
				shooter, true, passer,
				config.goalMaxTouchTime * tickrate,
				config.passMaxTouchTime * tickrate
			)) {

				if (_goalCallback.func)
					_goalCallback.func(arena, shooter, passer, _goalCallback.userInfo);
			}
		} else {
			if (!_ballShot) {                              

				if (_shotCooldown > 0) {
					_shotCooldown = RS_MAX(_shotCooldown - deltaTime, 0);
					                        
				} else {

					float speedSq = (arena->ball->_rigidBody.m_linearVelocity * BT_TO_UU).length2();
					if (speedSq >= config.shotMinSpeed * config.shotMinSpeed) {
						Team goalTeam;
						if (arena->IsBallProbablyGoingIn(config.shotMinScoreTime, config.predScoreExtraMargin, &goalTeam)) {
							Team shooterTeam = RS_OPPOSITE_TEAM(goalTeam);

							uint64_t shotMinTouchDelayTicks = config.shotTouchMinDelay * tickrate;

							Car* shooter;
							Car* passer;
							if (GetShooterPasser(
								arena,
								shooterTeam,
								shooter, true, passer,
								deltaTicks + shotMinTouchDelayTicks,
								config.passMaxTouchTime * tickrate
							)) {

								uint64_t ticksSinceHit = arena->tickCount - shooter->_internalState.ballHitInfo.tickCountWhenHit;
								if (ticksSinceHit >= shotMinTouchDelayTicks) {

									                                 
									_ballShot = true;
									_ballShotGoalTeam = goalTeam;
									_shotCooldown = config.shotEventCooldown;
									if (_shotCallback.func)
										_shotCallback.func(arena, shooter, passer, _shotCallback.userInfo);
								}
							}
						}
					}
				}
			} else {
				                         

				bool willScore = arena->IsBallProbablyGoingIn(config.shotMinScoreTime, config.predScoreExtraMargin);
				if (!willScore) {
					                             
					                                         

					Car* saver;
					Car* _unused;
					if (GetShooterPasser(
						arena,
						_ballShotGoalTeam,
						saver, false, _unused,
						deltaTicks,
						0
					)) {

						                                                     
						                                                
						if (_saveCallback.func)
							_saveCallback.func(arena, saver, _saveCallback.userInfo);
					} else {
						                                             
					}
					
					_ballShot = false;
				}
			}
		}
	} else if (ballUpdateCount == _lastBallUpdateCount) {
		                   
		return;
	} else {
		                              
		                        
		ResetPersistentInfo();
	}

	_ballScoredLast = scored;
	_lastBallUpdateCount = ballUpdateCount;
}

void GameEventTracker::ResetPersistentInfo() {
	_ballScoredLast = false;
	_ballShot = false;
	_shotCooldown = 0;

	                                             
}

RS_NS_END