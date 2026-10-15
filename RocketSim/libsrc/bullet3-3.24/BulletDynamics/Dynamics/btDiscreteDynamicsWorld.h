  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_DISCRETE_DYNAMICS_WORLD_H
#define BT_DISCRETE_DYNAMICS_WORLD_H

#include "btDynamicsWorld.h"
class btCollisionDispatcher;
class btOverlappingPairCache;
class btSequentialImpulseConstraintSolver;
class btSimulationIslandManager;
class btTypedConstraint;
class btActionInterface;
class btPersistentManifold;

struct InplaceSolverIslandCallback;

#include "../../LinearMath/btAlignedObjectArray.h"
#include "../../LinearMath/btThreads.h"

                                                                  
                                                                                
ATTRIBUTE_ALIGNED16(class)
btDiscreteDynamicsWorld : public btDynamicsWorld
{
protected:
	btAlignedObjectArray<btTypedConstraint*> m_sortedConstraints;
	InplaceSolverIslandCallback* m_solverIslandCallback;

	btSequentialImpulseConstraintSolver* m_constraintSolver;

	btSimulationIslandManager* m_islandManager;

	btAlignedObjectArray<btTypedConstraint*> m_constraints;

	btAlignedObjectArray<btRigidBody*> m_nonStaticRigidBodies;

	btVector3 m_gravity;

	                        
	btScalar m_localTime;
	btScalar m_fixedTimeStep;
	                        

	bool m_ownsIslandManager;
	bool m_ownsConstraintSolver;
	bool m_synchronizeAllMotionStates;
	bool m_applySpeculativeContactRestitution;

	btAlignedObjectArray<btActionInterface*> m_actions;

	int m_profileTimings;

	bool m_latencyMotionStateInterpolation;

	btAlignedObjectArray<btPersistentManifold*> m_predictiveManifolds;
	btSpinMutex m_predictiveManifoldsMutex;                                                             

	virtual void predictUnconstraintMotion(btScalar timeStep);

	void integrateTransformsInternal(btRigidBody * *bodies, int numBodies, btScalar timeStep);                              
	virtual void integrateTransforms(btScalar timeStep);

	virtual void calculateSimulationIslands();

	virtual void updateActivationState(btScalar timeStep);

	void updateActions(btScalar timeStep);

	void startProfiling(btScalar timeStep);

	void internalSingleStepSimulation(btScalar timeStep);

	void releasePredictiveContacts();
	void createPredictiveContactsInternal(btRigidBody * *bodies, int numBodies, btScalar timeStep);                              
	virtual void createPredictiveContacts(btScalar timeStep);

	virtual void saveKinematicState(btScalar timeStep);

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btDiscreteDynamicsWorld() {}

	                                                                                                         
	void setup(btCollisionDispatcher* dispatcher, btBroadphaseInterface* pairCache, btSequentialImpulseConstraintSolver* constraintSolver, btCollisionConfiguration* collisionConfiguration);

	virtual ~btDiscreteDynamicsWorld();

	                                                                         
	int stepSimulation(btScalar timeStep, int maxSubSteps = 1, btScalar fixedTimeStep = btScalar(1.) / btScalar(60.));

    void solveConstraints(btContactSolverInfo & solverInfo);
    
	virtual void synchronizeMotionStates();

	                                                                           
	void synchronizeSingleMotionState(btRigidBody * body);

	virtual void addConstraint(btTypedConstraint * constraint, bool disableCollisionsBetweenLinkedBodies = false);

	virtual void removeConstraint(btTypedConstraint * constraint);

	virtual void addAction(btActionInterface*);

	virtual void removeAction(btActionInterface*);

	btSimulationIslandManager* getSimulationIslandManager()
	{
		return m_islandManager;
	}

	const btSimulationIslandManager* getSimulationIslandManager() const
	{
		return m_islandManager;
	}

	btCollisionWorld* getCollisionWorld()
	{
		return this;
	}

	virtual void setGravity(const btVector3& gravity);

	virtual btVector3 getGravity() const;

	virtual void addCollisionObject(btCollisionObject * collisionObject, int collisionFilterGroup = btBroadphaseProxy::StaticFilter, int collisionFilterMask = btBroadphaseProxy::AllFilter ^ btBroadphaseProxy::StaticFilter);

	virtual void addRigidBody(btRigidBody * body);

	virtual void addRigidBody(btRigidBody * body, int group, int mask);

	virtual void removeRigidBody(btRigidBody * body);

	                                                                                                                                                  
	virtual void removeCollisionObject(btCollisionObject * collisionObject);

	virtual void setConstraintSolver(btSequentialImpulseConstraintSolver* solver);

	virtual btSequentialImpulseConstraintSolver* getConstraintSolver();

	virtual int getNumConstraints() const;

	virtual btTypedConstraint* getConstraint(int index);

	virtual const btTypedConstraint* getConstraint(int index) const;

	virtual btDynamicsWorldType getWorldType() const
	{
		return BT_DISCRETE_DYNAMICS_WORLD;
	}

	                                                                                                      
	virtual void clearForces();

	                                             
	virtual void applyGravity();

	virtual void setNumTasks(int numTasks)
	{
		(void)numTasks;
	}

	                                      
	virtual void updateVehicles(btScalar timeStep)
	{
		updateActions(timeStep);
	}

	                                  
	virtual void addVehicle(btActionInterface * vehicle);
	                                     
	virtual void removeVehicle(btActionInterface * vehicle);
	                                  
	virtual void addCharacter(btActionInterface * character);
	                                     
	virtual void removeCharacter(btActionInterface * character);

	void setSynchronizeAllMotionStates(bool synchronizeAll)
	{
		m_synchronizeAllMotionStates = synchronizeAll;
	}
	bool getSynchronizeAllMotionStates() const
	{
		return m_synchronizeAllMotionStates;
	}

	void setApplySpeculativeContactRestitution(bool enable)
	{
		m_applySpeculativeContactRestitution = enable;
	}

	bool getApplySpeculativeContactRestitution() const
	{
		return m_applySpeculativeContactRestitution;
	}

	                                                                                                          
	                                                                         
	void setLatencyMotionStateInterpolation(bool latencyInterpolation)
	{
		m_latencyMotionStateInterpolation = latencyInterpolation;
	}
	bool getLatencyMotionStateInterpolation() const
	{
		return m_latencyMotionStateInterpolation;
	}
    
    btAlignedObjectArray<btRigidBody*>& getNonStaticRigidBodies()
    {
        return m_nonStaticRigidBodies;
    }
    
    const btAlignedObjectArray<btRigidBody*>& getNonStaticRigidBodies() const
    {
        return m_nonStaticRigidBodies;
    }
};

#endif                                
