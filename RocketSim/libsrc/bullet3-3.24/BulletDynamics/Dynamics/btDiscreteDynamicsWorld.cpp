  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                     
                                                                              
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btDiscreteDynamicsWorld.h"

                     
#include "../../BulletCollision/CollisionDispatch/btCollisionDispatcher.h"
#include "../../BulletCollision/BroadphaseCollision/btCollisionAlgorithm.h"
#include "../../BulletCollision/CollisionShapes/btCollisionShape.h"
#include "../../BulletCollision/CollisionDispatch/btSimulationIslandManager.h"
#include "../../LinearMath/btTransformUtil.h"
#include "../../LinearMath/btQuickprof.h"

                         
#include "../Dynamics/btRigidBody.h"
#include "../ConstraintSolver/btSequentialImpulseConstraintSolver.h"
#include "../ConstraintSolver/btContactSolverInfo.h"
#include "../ConstraintSolver/btTypedConstraint.h"
#include "../ConstraintSolver/btContactConstraint.h"

#include "../../BulletCollision/CollisionShapes/btSphereShape.h"

#include "../Dynamics/btActionInterface.h"
#include "../../LinearMath/btQuickprof.h"
#include "../../LinearMath/btMotionState.h"
#include "../../LinearMath/btStackAlloc.h"

#if 0
btAlignedObjectArray<btVector3> debugContacts;
btAlignedObjectArray<btVector3> debugNormals;
int startHit=2;
int firstHit=startHit;
#endif

SIMD_FORCE_INLINE int btGetConstraintIslandId(const btTypedConstraint* lhs)
{
	int islandId;

	const btCollisionObject& rcolObj0 = lhs->getRigidBodyA();
	const btCollisionObject& rcolObj1 = lhs->getRigidBodyB();
	islandId = rcolObj0.getIslandTag() >= 0 ? rcolObj0.getIslandTag() : rcolObj1.getIslandTag();
	return islandId;
}

class btSortConstraintOnIslandPredicate
{
public:
	bool operator()(const btTypedConstraint* lhs, const btTypedConstraint* rhs) const
	{
		int rIslandId0, lIslandId0;
		rIslandId0 = btGetConstraintIslandId(rhs);
		lIslandId0 = btGetConstraintIslandId(lhs);
		return lIslandId0 < rIslandId0;
	}
};

struct InplaceSolverIslandCallback : public btSimulationIslandManager::IslandCallback
{
	btContactSolverInfo* m_solverInfo;
	btSequentialImpulseConstraintSolver* m_solver;
	btTypedConstraint** m_sortedConstraints;
	int m_numConstraints;
	btCollisionDispatcher* m_dispatcher;

	btAlignedObjectArray<btCollisionObject*> m_bodies;
	btAlignedObjectArray<btPersistentManifold*> m_manifolds;
	btAlignedObjectArray<btTypedConstraint*> m_constraints;

	InplaceSolverIslandCallback(
		btSequentialImpulseConstraintSolver* solver,
		btStackAlloc* stackAlloc,
		btCollisionDispatcher* dispatcher)
		: m_solverInfo(NULL),
		  m_solver(solver),
		  m_sortedConstraints(NULL),
		  m_numConstraints(0),
		  m_dispatcher(dispatcher)
	{
	}

	InplaceSolverIslandCallback& operator=(InplaceSolverIslandCallback& other)
	{
		btAssert(0);
		(void)other;
		return *this;
	}

	SIMD_FORCE_INLINE void setup(btContactSolverInfo* solverInfo, btTypedConstraint** sortedConstraints, int numConstraints)
	{
		btAssert(solverInfo);
		m_solverInfo = solverInfo;
		m_sortedConstraints = sortedConstraints;
		m_numConstraints = numConstraints;
		m_bodies.resize(0);
		m_manifolds.resize(0);
		m_constraints.resize(0);
	}

	virtual void processIsland(btCollisionObject** bodies, int numBodies, btPersistentManifold** manifolds, int numManifolds, int islandId)
	{
		if (islandId < 0)
		{
			                                                                                                                          
			m_solver->solveGroup(bodies, numBodies, manifolds, numManifolds, &m_sortedConstraints[0], m_numConstraints, *m_solverInfo, m_dispatcher);
		}
		else
		{
			                                                             
			btTypedConstraint** startConstraint = 0;
			int numCurConstraints = 0;
			int i;

			                                           
			for (i = 0; i < m_numConstraints; i++)
			{
				if (btGetConstraintIslandId(m_sortedConstraints[i]) == islandId)
				{
					startConstraint = &m_sortedConstraints[i];
					break;
				}
			}
			                                                
			for (; i < m_numConstraints; i++)
			{
				if (btGetConstraintIslandId(m_sortedConstraints[i]) == islandId)
				{
					numCurConstraints++;
				}
			}

			if (m_solverInfo->m_minimumSolverBatchSize <= 1)
			{
				m_solver->solveGroup(bodies, numBodies, manifolds, numManifolds, startConstraint, numCurConstraints, *m_solverInfo, m_dispatcher);
			}
			else
			{
				for (i = 0; i < numBodies; i++)
					m_bodies.push_back(bodies[i]);
				for (i = 0; i < numManifolds; i++)
					m_manifolds.push_back(manifolds[i]);
				for (i = 0; i < numCurConstraints; i++)
					m_constraints.push_back(startConstraint[i]);
				if ((m_constraints.size() + m_manifolds.size()) > m_solverInfo->m_minimumSolverBatchSize)
				{
					processConstraints();
				}
				else
				{
					                       
				}
			}
		}
	}
	void processConstraints()
	{
		btCollisionObject** bodies = m_bodies.size() ? &m_bodies[0] : 0;
		btPersistentManifold** manifold = m_manifolds.size() ? &m_manifolds[0] : 0;
		btTypedConstraint** constraints = m_constraints.size() ? &m_constraints[0] : 0;

		m_solver->solveGroup(bodies, m_bodies.size(), manifold, m_manifolds.size(), constraints, m_constraints.size(), *m_solverInfo, m_dispatcher);
		m_bodies.resize(0);
		m_manifolds.resize(0);
		m_constraints.resize(0);
	}
};

void btDiscreteDynamicsWorld::setup(btCollisionDispatcher* dispatcher, btBroadphaseInterface* pairCache, btSequentialImpulseConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration)
{
	btDynamicsWorld::setup(dispatcher, pairCache, collisionConfiguration);
	m_sortedConstraints = {};
	m_solverIslandCallback = NULL;
	m_constraintSolver = constraintSolver;
	m_gravity = btVector3(0, -10, 0);
	m_localTime = 0;
	m_fixedTimeStep = 0;
	m_synchronizeAllMotionStates = false;
	m_applySpeculativeContactRestitution = false;
	m_profileTimings = 0;
	m_latencyMotionStateInterpolation = true;

	if (!m_constraintSolver)
	{
		void* mem = btAlignedAlloc(sizeof(btSequentialImpulseConstraintSolver), 16);
		m_constraintSolver = new (mem) btSequentialImpulseConstraintSolver;
		m_ownsConstraintSolver = true;
	}
	else
	{
		m_ownsConstraintSolver = false;
	}

	{
		void* mem = btAlignedAlloc(sizeof(btSimulationIslandManager), 16);
		m_islandManager = new (mem) btSimulationIslandManager();
	}

	m_ownsIslandManager = true;

	{
		void* mem = btAlignedAlloc(sizeof(InplaceSolverIslandCallback), 16);
		m_solverIslandCallback = new (mem) InplaceSolverIslandCallback(m_constraintSolver, 0, dispatcher);
	}
}

btDiscreteDynamicsWorld::~btDiscreteDynamicsWorld()
{
	                                   
	if (m_ownsIslandManager)
	{
		m_islandManager->~btSimulationIslandManager();
		btAlignedFree(m_islandManager);
	}
	if (m_solverIslandCallback)
	{
		m_solverIslandCallback->~InplaceSolverIslandCallback();
		btAlignedFree(m_solverIslandCallback);
	}
	if (m_ownsConstraintSolver)
	{
		m_constraintSolver->~btSequentialImpulseConstraintSolver();
		btAlignedFree(m_constraintSolver);
	}
}

void btDiscreteDynamicsWorld::saveKinematicState(btScalar timeStep)
{
	                                                                              
	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btCollisionObject* colObj = m_collisionObjects[i];
		btRigidBody* body = btRigidBody::upcast(colObj);
		if (body && body->getActivationState() != ISLAND_SLEEPING)
		{
			                                    
			body->saveKinematicState(timeStep);
		}
	}
}

void btDiscreteDynamicsWorld::clearForces()
{
	                                                
	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		                                  
		                                                                                                                               
		body->clearForces();
	}
}

                                             
void btDiscreteDynamicsWorld::applyGravity()
{
	                                                
	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (body->isActive())
		{
			body->applyGravity();
		}
	}
}

void btDiscreteDynamicsWorld::synchronizeSingleMotionState(btRigidBody* body)
{
	btAssert(body);

	if (body->getMotionState() && !body->isStaticOrKinematicObject())
	{
		                                                                     
		                                                           
		                          
		                                                    
		{
			btTransform interpolatedTransform;
			btTransformUtil::integrateTransform(body->getInterpolationWorldTransform(),
												body->getInterpolationLinearVelocity(), body->getInterpolationAngularVelocity(),
												(m_latencyMotionStateInterpolation && m_fixedTimeStep) ? m_localTime - m_fixedTimeStep : m_localTime * body->getHitFraction(),
												interpolatedTransform);
			body->getMotionState()->setWorldTransform(interpolatedTransform);
		}
	}
}

void btDiscreteDynamicsWorld::synchronizeMotionStates()
{
	                                         
	if (m_synchronizeAllMotionStates)
	{
		                                     
		for (int i = 0; i < m_collisionObjects.size(); i++)
		{
			btCollisionObject* colObj = m_collisionObjects[i];
			btRigidBody* body = btRigidBody::upcast(colObj);
			if (body)
				synchronizeSingleMotionState(body);
		}
	}
	else
	{
		                                      
		for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
		{
			btRigidBody* body = m_nonStaticRigidBodies[i];
			if (body->isActive())
				synchronizeSingleMotionState(body);
		}
	}
}

int btDiscreteDynamicsWorld::stepSimulation(btScalar timeStep, int maxSubSteps, btScalar fixedTimeStep)
{
	startProfiling(timeStep);

	int numSimulationSubSteps = 0;

	if (maxSubSteps)
	{
		                                   
		m_fixedTimeStep = fixedTimeStep;
		m_localTime += timeStep;
		if (m_localTime >= fixedTimeStep)
		{
			numSimulationSubSteps = int(m_localTime / fixedTimeStep);
			m_localTime -= numSimulationSubSteps * fixedTimeStep;
		}
	}
	else
	{
		                   
		fixedTimeStep = timeStep;
		m_localTime = m_latencyMotionStateInterpolation ? 0 : timeStep;
		m_fixedTimeStep = 0;
		if (btFuzzyZero(timeStep))
		{
			numSimulationSubSteps = 0;
			maxSubSteps = 0;
		}
		else
		{
			numSimulationSubSteps = 1;
			maxSubSteps = 1;
		}
	}

	if (numSimulationSubSteps)
	{
		                                                                                        
		int clampedSimulationSteps = (numSimulationSubSteps > maxSubSteps) ? maxSubSteps : numSimulationSubSteps;

		                                        
		                                                             

		applyGravity();

		for (int i = 0; i < clampedSimulationSteps; i++)
		{
			internalSingleStepSimulation(fixedTimeStep);

			                                        
			                            
		}
	}
	else
	{
		                                        
		                            
	}

	clearForces();

#ifndef BT_NO_PROFILE
	CProfileManager::Increment_Frame_Counter();
#endif                 

	return numSimulationSubSteps;
}

void btDiscreteDynamicsWorld::internalSingleStepSimulation(btScalar timeStep)
{
	BT_PROFILE("internalSingleStepSimulation");

	if (0 != m_internalPreTickCallback)
	{
		(*m_internalPreTickCallback)(this, timeStep);
	}

	                                
	predictUnconstraintMotion(timeStep);

	btDispatcherInfo& dispatchInfo = getDispatchInfo();

	dispatchInfo.m_timeStep = timeStep;
	dispatchInfo.m_stepCount = 0;

	createPredictiveContacts(timeStep);

	                              
	performDiscreteCollisionDetection();

	calculateSimulationIslands();

	getSolverInfo().m_timeStep = timeStep;

	                                            
	solveConstraints(getSolverInfo());

	                      

	                       

	integrateTransforms(timeStep);

	                            
	updateActions(timeStep);

	updateActivationState(timeStep);

	if (0 != m_internalTickCallback)
	{
		(*m_internalTickCallback)(this, timeStep);
	}
}

void btDiscreteDynamicsWorld::setGravity(const btVector3& gravity)
{
	m_gravity = gravity;
	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (body->isActive() && !(body->getFlags() & BT_DISABLE_WORLD_GRAVITY))
		{
			body->setGravity(gravity);
		}
	}
}

btVector3 btDiscreteDynamicsWorld::getGravity() const
{
	return m_gravity;
}

void btDiscreteDynamicsWorld::addCollisionObject(btCollisionObject* collisionObject, int collisionFilterGroup, int collisionFilterMask)
{
	btCollisionWorld::addCollisionObject(collisionObject, collisionFilterGroup, collisionFilterMask);
}

void btDiscreteDynamicsWorld::removeCollisionObject(btCollisionObject* collisionObject)
{
	btRigidBody* body = btRigidBody::upcast(collisionObject);
	if (body)
		removeRigidBody(body);
	else
		btCollisionWorld::removeCollisionObject(collisionObject);
}

void btDiscreteDynamicsWorld::removeRigidBody(btRigidBody* body)
{
	m_nonStaticRigidBodies.remove(body);
	btCollisionWorld::removeCollisionObject(body);
}

void btDiscreteDynamicsWorld::addRigidBody(btRigidBody* body)
{
	if (!body->isStaticOrKinematicObject() && !(body->getFlags() & BT_DISABLE_WORLD_GRAVITY))
	{
		body->setGravity(m_gravity);
	}

	if (body->getCollisionShape())
	{
		if (!body->isStaticObject())
		{
			m_nonStaticRigidBodies.push_back(body);
		}
		else
		{
			body->setActivationState(ISLAND_SLEEPING);
		}

		bool isDynamic = !(body->isStaticObject() || body->isKinematicObject());
		int collisionFilterGroup = isDynamic ? int(btBroadphaseProxy::DefaultFilter) : int(btBroadphaseProxy::StaticFilter);
		int collisionFilterMask = isDynamic ? int(btBroadphaseProxy::AllFilter) : int(btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

		addCollisionObject(body, collisionFilterGroup, collisionFilterMask);
	}
}

void btDiscreteDynamicsWorld::addRigidBody(btRigidBody* body, int group, int mask)
{
	if (!body->isStaticOrKinematicObject() && !(body->getFlags() & BT_DISABLE_WORLD_GRAVITY))
	{
		body->setGravity(m_gravity);
	}

	if (body->getCollisionShape())
	{
		if (!body->isStaticObject())
		{
			m_nonStaticRigidBodies.push_back(body);
		}
		else
		{
			body->setActivationState(ISLAND_SLEEPING);
		}
		addCollisionObject(body, group, mask);
	}
}

void btDiscreteDynamicsWorld::updateActions(btScalar timeStep)
{
	BT_PROFILE("updateActions");

	for (int i = 0; i < m_actions.size(); i++)
	{
		m_actions[i]->updateAction(this, timeStep);
	}
}

void btDiscreteDynamicsWorld::updateActivationState(btScalar timeStep)
{
	BT_PROFILE("updateActivationState");

	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (body)
		{
			body->updateDeactivation(timeStep);

			if (body->wantsSleeping())
			{
				if (body->isStaticOrKinematicObject())
				{
					body->setActivationState(ISLAND_SLEEPING);
				}
				else
				{
					if (body->getActivationState() == ACTIVE_TAG)
						body->setActivationState(WANTS_DEACTIVATION);
					if (body->getActivationState() == ISLAND_SLEEPING)
					{
						body->setAngularVelocity(btVector3(0, 0, 0));
						body->setLinearVelocity(btVector3(0, 0, 0));
					}
				}
			}
			else
			{
				if (body->getActivationState() != DISABLE_DEACTIVATION)
					body->setActivationState(ACTIVE_TAG);
			}
		}
	}
}

void btDiscreteDynamicsWorld::addConstraint(btTypedConstraint* constraint, bool disableCollisionsBetweenLinkedBodies)
{
	m_constraints.push_back(constraint);
	                                                                                                                       
	btAssert(&constraint->getRigidBodyA() != &constraint->getRigidBodyB());

	if (disableCollisionsBetweenLinkedBodies)
	{
		constraint->getRigidBodyA().addConstraintRef(constraint);
		constraint->getRigidBodyB().addConstraintRef(constraint);
	}
}

void btDiscreteDynamicsWorld::removeConstraint(btTypedConstraint* constraint)
{
	m_constraints.remove(constraint);
	constraint->getRigidBodyA().removeConstraintRef(constraint);
	constraint->getRigidBodyB().removeConstraintRef(constraint);
}

void btDiscreteDynamicsWorld::addAction(btActionInterface* action)
{
	m_actions.push_back(action);
}

void btDiscreteDynamicsWorld::removeAction(btActionInterface* action)
{
	m_actions.remove(action);
}

void btDiscreteDynamicsWorld::addVehicle(btActionInterface* vehicle)
{
	addAction(vehicle);
}

void btDiscreteDynamicsWorld::removeVehicle(btActionInterface* vehicle)
{
	removeAction(vehicle);
}

void btDiscreteDynamicsWorld::addCharacter(btActionInterface* character)
{
	addAction(character);
}

void btDiscreteDynamicsWorld::removeCharacter(btActionInterface* character)
{
	removeAction(character);
}

void btDiscreteDynamicsWorld::solveConstraints(btContactSolverInfo& solverInfo)
{
	BT_PROFILE("solveConstraints");

	m_sortedConstraints.resize(m_constraints.size());
	int i;
	for (i = 0; i < getNumConstraints(); i++)
	{
		m_sortedConstraints[i] = m_constraints[i];
	}

	               

	m_sortedConstraints.quickSort(btSortConstraintOnIslandPredicate());

	btTypedConstraint** constraintsPtr = getNumConstraints() ? &m_sortedConstraints[0] : 0;

	m_solverIslandCallback->setup(&solverInfo, constraintsPtr, m_sortedConstraints.size());
	                                             
	m_islandManager->buildAndProcessIslands(getCollisionWorld()->getDispatcher(), getCollisionWorld(), m_solverIslandCallback);

	m_solverIslandCallback->processConstraints();
}

void btDiscreteDynamicsWorld::calculateSimulationIslands()
{
	BT_PROFILE("calculateSimulationIslands");

	auto islandManager = getSimulationIslandManager();
	auto dispatcher = this->getDispatcher();
	islandManager->updateActivationState(this, dispatcher);

	{
		                                                          
		for (int i = 0; i < this->m_predictiveManifolds.size(); i++)
		{
			btPersistentManifold* manifold = m_predictiveManifolds[i];

			const btCollisionObject* colObj0 = manifold->getBody0();
			const btCollisionObject* colObj1 = manifold->getBody1();

			if (((colObj0) && (!(colObj0)->isStaticOrKinematicObject())) &&
				((colObj1) && (!(colObj1)->isStaticOrKinematicObject())))
			{
				islandManager->getUnionFind().unite((colObj0)->getIslandTag(), (colObj1)->getIslandTag());
			}
		}
	}

	{
		int i;
		int numConstraints = int(m_constraints.size());
		for (i = 0; i < numConstraints; i++)
		{
			btTypedConstraint* constraint = m_constraints[i];
			if (constraint->isEnabled())
			{
				const btRigidBody* colObj0 = &constraint->getRigidBodyA();
				const btRigidBody* colObj1 = &constraint->getRigidBodyB();

				if (((colObj0) && (!(colObj0)->isStaticOrKinematicObject())) &&
					((colObj1) && (!(colObj1)->isStaticOrKinematicObject())))
				{
					getSimulationIslandManager()->getUnionFind().unite((colObj0)->getIslandTag(), (colObj1)->getIslandTag());
				}
			}
		}
	}

	                                  
	getSimulationIslandManager()->storeIslandActivationState(getCollisionWorld());
}

class btClosestNotMeConvexResultCallback : public btCollisionWorld::ClosestConvexResultCallback
{
public:
	btCollisionObject* m_me;
	btScalar m_allowedPenetration;
	btOverlappingPairCache* m_pairCache;
	btCollisionDispatcher* m_dispatcher;

public:
	btClosestNotMeConvexResultCallback(btCollisionObject* me, const btVector3& fromA, const btVector3& toA, btOverlappingPairCache* pairCache, btCollisionDispatcher* dispatcher) : btCollisionWorld::ClosestConvexResultCallback(fromA, toA),
																																										   m_me(me),
																																										   m_allowedPenetration(0.0f),
																																										   m_pairCache(pairCache),
																																										   m_dispatcher(dispatcher)
	{
	}

	virtual btScalar addSingleResult(btCollisionWorld::LocalConvexResult& convexResult, bool normalInWorldSpace)
	{
		if (convexResult.m_hitCollisionObject == m_me)
			return 1.0f;

		                                               
		if (!convexResult.m_hitCollisionObject->hasContactResponse())
			return 1.0f;

		btVector3 linVelA, linVelB;
		linVelA = m_convexToWorld - m_convexFromWorld;
		linVelB = btVector3(0, 0, 0);                                      

		btVector3 relativeVelocity = (linVelA - linVelB);
		                                                                                                   
		if (convexResult.m_hitNormalLocal.dot(relativeVelocity) >= -m_allowedPenetration)
			return 1.f;

		return ClosestConvexResultCallback::addSingleResult(convexResult, normalInWorldSpace);
	}

	virtual bool needsCollision(btBroadphaseProxy* proxy0) const
	{
		                           
		if (proxy0->m_clientObject == m_me)
			return false;

		                                                           
		if (!ClosestConvexResultCallback::needsCollision(proxy0))
			return false;
		if (m_pairCache->getOverlapFilterCallback()) {
			btBroadphaseProxy* proxy1 = m_me->getBroadphaseHandle();
			bool collides = m_pairCache->needsBroadphaseCollision(proxy0, proxy1);
			if (!collides)
			{
				return false;
			}
		}

		btCollisionObject* otherObj = (btCollisionObject*)proxy0->m_clientObject;

		if (!m_dispatcher->needsCollision(m_me, otherObj))
			return false;

		                                                                              
		if (m_dispatcher->needsResponse(m_me, otherObj))
		{
#if 0
			                                                                                    
			btAlignedObjectArray<btPersistentManifold*> manifoldArray;
			btBroadphasePair* collisionPair = m_pairCache->findPair(m_me->getBroadphaseHandle(),proxy0);
			if (collisionPair)
			{
				if (collisionPair->m_algorithm)
				{
					manifoldArray.resize(0);
					collisionPair->m_algorithm->getAllContactManifolds(manifoldArray);
					for (int j=0;j<manifoldArray.size();j++)
					{
						btPersistentManifold* manifold = manifoldArray[j];
						if (manifold->getNumContacts()>0)
							return false;
					}
				}
			}
#endif
			return true;
		}

		return false;
	}
};

                                                                
int gNumClampedCcdMotions = 0;

void btDiscreteDynamicsWorld::createPredictiveContactsInternal(btRigidBody** bodies, int numBodies, btScalar timeStep)
{
	btTransform predictedTrans;
	for (int i = 0; i < numBodies; i++)
	{
		btRigidBody* body = bodies[i];
		body->setHitFraction(1.f);

		if (body->isActive() && (!body->isStaticOrKinematicObject()))
		{
			body->predictIntegratedTransform(timeStep, predictedTrans);

			btScalar squareMotion = (predictedTrans.getOrigin() - body->getWorldTransform().getOrigin()).length2();

			if (getDispatchInfo().m_useContinuous && body->getCcdSquareMotionThreshold() && body->getCcdSquareMotionThreshold() < squareMotion)
			{
				BT_PROFILE("predictive convexSweepTest");
				if (body->getCollisionShape()->isConvex())
				{
					gNumClampedCcdMotions++;
#ifdef PREDICTIVE_CONTACT_USE_STATIC_ONLY
					class StaticOnlyCallback : public btClosestNotMeConvexResultCallback
					{
					public:
						StaticOnlyCallback(btCollisionObject* me, const btVector3& fromA, const btVector3& toA, btOverlappingPairCache* pairCache, btCollisionDispatcher* dispatcher) : btClosestNotMeConvexResultCallback(me, fromA, toA, pairCache, dispatcher)
						{
						}

						virtual bool needsCollision(btBroadphaseProxy* proxy0) const
						{
							btCollisionObject* otherObj = (btCollisionObject*)proxy0->m_clientObject;
							if (!otherObj->isStaticOrKinematicObject())
								return false;
							return btClosestNotMeConvexResultCallback::needsCollision(proxy0);
						}
					};

					StaticOnlyCallback sweepResults(body, body->getWorldTransform().getOrigin(), predictedTrans.getOrigin(), getBroadphase()->getOverlappingPairCache(), getDispatcher());
#else
					btClosestNotMeConvexResultCallback sweepResults(body, body->getWorldTransform().getOrigin(), predictedTrans.getOrigin(), getBroadphase()->getOverlappingPairCache(), getDispatcher());
#endif
					                                                                                      
					btSphereShape tmpSphere(body->getCcdSweptSphereRadius());                                                                                        
					sweepResults.m_allowedPenetration = getDispatchInfo().m_allowedCcdPenetration;

					sweepResults.m_collisionFilterGroup = body->getBroadphaseProxy()->m_collisionFilterGroup;
					sweepResults.m_collisionFilterMask = body->getBroadphaseProxy()->m_collisionFilterMask;
					btTransform modifiedPredictedTrans = predictedTrans;
					modifiedPredictedTrans.setBasis(body->getWorldTransform().getBasis());

					convexSweepTest(&tmpSphere, body->getWorldTransform(), modifiedPredictedTrans, sweepResults);
					if (sweepResults.hasHit() && (sweepResults.m_closestHitFraction < 1.f))
					{
						btVector3 distVec = (predictedTrans.getOrigin() - body->getWorldTransform().getOrigin()) * sweepResults.m_closestHitFraction;
						btScalar distance = distVec.dot(-sweepResults.m_hitNormalWorld);

						btMutexLock(&m_predictiveManifoldsMutex);
						btPersistentManifold* manifold = m_dispatcher1->getNewManifold(body, sweepResults.m_hitCollisionObject);
						m_predictiveManifolds.push_back(manifold);
						btMutexUnlock(&m_predictiveManifoldsMutex);

						btVector3 worldPointB = body->getWorldTransform().getOrigin() + distVec;
						btVector3 localPointB = sweepResults.m_hitCollisionObject->getWorldTransform().inverse() * worldPointB;

						btManifoldPoint newPoint(btVector3(0, 0, 0), localPointB, sweepResults.m_hitNormalWorld, distance);

						bool isPredictive = true;
						int index = manifold->addManifoldPoint(newPoint, isPredictive);
						btManifoldPoint& pt = manifold->getContactPoint(index);
						pt.m_combinedRestitution = 0;
						pt.m_combinedFriction = gCalculateCombinedFrictionCallback(body, sweepResults.m_hitCollisionObject);
						pt.m_positionWorldOnA = body->getWorldTransform().getOrigin();
						pt.m_positionWorldOnB = worldPointB;
					}
				}
			}
		}
	}
}

void btDiscreteDynamicsWorld::releasePredictiveContacts()
{
	BT_PROFILE("release predictive contact manifolds");

	for (int i = 0; i < m_predictiveManifolds.size(); i++)
	{
		btPersistentManifold* manifold = m_predictiveManifolds[i];
		this->m_dispatcher1->releaseManifold(manifold);
	}
	m_predictiveManifolds.clear();
}

void btDiscreteDynamicsWorld::createPredictiveContacts(btScalar timeStep)
{
	BT_PROFILE("createPredictiveContacts");
	releasePredictiveContacts();
	if (m_nonStaticRigidBodies.size() > 0)
	{
		createPredictiveContactsInternal(&m_nonStaticRigidBodies[0], m_nonStaticRigidBodies.size(), timeStep);
	}
}

void btDiscreteDynamicsWorld::integrateTransformsInternal(btRigidBody** bodies, int numBodies, btScalar timeStep)
{
	btTransform predictedTrans;
	for (int i = 0; i < numBodies; i++)
	{
		btRigidBody* body = bodies[i];
		body->setHitFraction(1.f);

		if (body->isActive() && (!body->isStaticOrKinematicObject()))
		{
			body->predictIntegratedTransform(timeStep, predictedTrans);

			btScalar squareMotion = (predictedTrans.getOrigin() - body->getWorldTransform().getOrigin()).length2();

			if (getDispatchInfo().m_useContinuous && body->getCcdSquareMotionThreshold() && body->getCcdSquareMotionThreshold() < squareMotion)
			{
				BT_PROFILE("CCD motion clamping");
				if (body->getCollisionShape()->isConvex())
				{
					gNumClampedCcdMotions++;
#ifdef USE_STATIC_ONLY
					class StaticOnlyCallback : public btClosestNotMeConvexResultCallback
					{
					public:
						StaticOnlyCallback(btCollisionObject* me, const btVector3& fromA, const btVector3& toA, btOverlappingPairCache* pairCache, btCollisionDispatcher* dispatcher) : btClosestNotMeConvexResultCallback(me, fromA, toA, pairCache, dispatcher)
						{
						}

						virtual bool needsCollision(btBroadphaseProxy* proxy0) const
						{
							btCollisionObject* otherObj = (btCollisionObject*)proxy0->m_clientObject;
							if (!otherObj->isStaticOrKinematicObject())
								return false;
							return btClosestNotMeConvexResultCallback::needsCollision(proxy0);
						}
					};

					StaticOnlyCallback sweepResults(body, body->getWorldTransform().getOrigin(), predictedTrans.getOrigin(), getBroadphase()->getOverlappingPairCache(), getDispatcher());
#else
					btClosestNotMeConvexResultCallback sweepResults(body, body->getWorldTransform().getOrigin(), predictedTrans.getOrigin(), getBroadphase()->getOverlappingPairCache(), getDispatcher());
#endif
					                                                                                      
					btSphereShape tmpSphere(body->getCcdSweptSphereRadius());                                                                                        
					sweepResults.m_allowedPenetration = getDispatchInfo().m_allowedCcdPenetration;

					sweepResults.m_collisionFilterGroup = body->getBroadphaseProxy()->m_collisionFilterGroup;
					sweepResults.m_collisionFilterMask = body->getBroadphaseProxy()->m_collisionFilterMask;
					btTransform modifiedPredictedTrans = predictedTrans;
					modifiedPredictedTrans.setBasis(body->getWorldTransform().getBasis());

					convexSweepTest(&tmpSphere, body->getWorldTransform(), modifiedPredictedTrans, sweepResults);
					if (sweepResults.hasHit() && (sweepResults.m_closestHitFraction < 1.f))
					{
						                                                                
						body->setHitFraction(sweepResults.m_closestHitFraction);
						body->predictIntegratedTransform(timeStep * body->getHitFraction(), predictedTrans);
						body->setHitFraction(0.f);
						body->proceedToTransform(predictedTrans);

#if 0
						btVector3 linVel = body->getLinearVelocity();

						btScalar maxSpeed = body->getCcdMotionThreshold()/getSolverInfo().m_timeStep;
						btScalar maxSpeedSqr = maxSpeed*maxSpeed;
						if (linVel.length2()>maxSpeedSqr)
						{
							linVel.normalize();
							linVel*= maxSpeed;
							body->setLinearVelocity(linVel);
							btScalar ms2 = body->getLinearVelocity().length2();
							body->predictIntegratedTransform(timeStep, predictedTrans);

							btScalar sm2 = (predictedTrans.getOrigin()-body->getWorldTransform().getOrigin()).length2();
							btScalar smt = body->getCcdSquareMotionThreshold();
							printf("sm2=%f\n",sm2);
						}
#else

						                                                                         
						                                                                                            
						                                
						                       
						                                                                                                                                                                                        

#endif

						continue;
					}
				}
			}

			body->proceedToTransform(predictedTrans);
		}
	}
}

void btDiscreteDynamicsWorld::integrateTransforms(btScalar timeStep)
{
	BT_PROFILE("integrateTransforms");
	if (m_nonStaticRigidBodies.size() > 0)
	{
		integrateTransformsInternal(&m_nonStaticRigidBodies[0], m_nonStaticRigidBodies.size(), timeStep);
	}

	                                                                                
	if (m_applySpeculativeContactRestitution)
	{
		BT_PROFILE("apply speculative contact restitution");
		for (int i = 0; i < m_predictiveManifolds.size(); i++)
		{
			btPersistentManifold* manifold = m_predictiveManifolds[i];
			btRigidBody* body0 = btRigidBody::upcast((btCollisionObject*)manifold->getBody0());
			btRigidBody* body1 = btRigidBody::upcast((btCollisionObject*)manifold->getBody1());

			for (int p = 0; p < manifold->getNumContacts(); p++)
			{
				const btManifoldPoint& pt = manifold->getContactPoint(p);
				btScalar combinedRestitution = gCalculateCombinedRestitutionCallback(body0, body1);

				if (combinedRestitution > 0 && pt.m_appliedImpulse != 0.f)
				                                                                                
				{
					btVector3 imp = -pt.m_normalWorldOnB * pt.m_appliedImpulse * combinedRestitution;

					const btVector3& pos1 = pt.getPositionWorldOnA();
					const btVector3& pos2 = pt.getPositionWorldOnB();

					btVector3 rel_pos0 = pos1 - body0->getWorldTransform().getOrigin();
					btVector3 rel_pos1 = pos2 - body1->getWorldTransform().getOrigin();

					if (body0)
						body0->applyImpulse(imp, rel_pos0);
					if (body1)
						body1->applyImpulse(-imp, rel_pos1);
				}
			}
		}
	}
}

void btDiscreteDynamicsWorld::predictUnconstraintMotion(btScalar timeStep)
{
	BT_PROFILE("predictUnconstraintMotion");
	for (int i = 0; i < m_nonStaticRigidBodies.size(); i++)
	{
		btRigidBody* body = m_nonStaticRigidBodies[i];
		if (!body->isStaticOrKinematicObject())
		{
			                                                                             

			body->applyDamping(timeStep);

			body->predictIntegratedTransform(timeStep, body->getInterpolationWorldTransform());
		}
	}
}

void btDiscreteDynamicsWorld::startProfiling(btScalar timeStep)
{
	(void)timeStep;

#ifndef BT_NO_PROFILE
	CProfileManager::Reset();
#endif                 
}

void btDiscreteDynamicsWorld::setConstraintSolver(btSequentialImpulseConstraintSolver* solver)
{
	if (m_ownsConstraintSolver)
	{
		btAlignedFree(m_constraintSolver);
	}
	m_ownsConstraintSolver = false;
	m_constraintSolver = solver;
	m_solverIslandCallback->m_solver = solver;
}

btSequentialImpulseConstraintSolver* btDiscreteDynamicsWorld::getConstraintSolver()
{
	return m_constraintSolver;
}

int btDiscreteDynamicsWorld::getNumConstraints() const
{
	return int(m_constraints.size());
}
btTypedConstraint* btDiscreteDynamicsWorld::getConstraint(int index)
{
	return m_constraints[index];
}
const btTypedConstraint* btDiscreteDynamicsWorld::getConstraint(int index) const
{
	return m_constraints[index];
}