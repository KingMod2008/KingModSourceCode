  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_DISPATCHER_H
#define BT_DISPATCHER_H
#include "../../LinearMath/btScalar.h"

class btCollisionAlgorithm;
struct btBroadphaseProxy;
class btRigidBody;
class btCollisionObject;
class btOverlappingPairCache;
struct btCollisionObjectWrapper;

class btPersistentManifold;
class btPoolAllocator;

struct btDispatcherInfo
{
	enum DispatchFunc
	{
		DISPATCH_DISCRETE = 1,
		DISPATCH_CONTINUOUS
	};
	btDispatcherInfo()
		: m_timeStep(btScalar(0.)),
		  m_stepCount(0),
		  m_dispatchFunc(DISPATCH_DISCRETE),
		  m_timeOfImpact(btScalar(1.)),
		  m_useContinuous(true),
		  m_enableSatConvex(false),
		  m_enableSPU(true),
		  m_useEpa(true),
		  m_allowedCcdPenetration(btScalar(0.04)),
		  m_useConvexConservativeDistanceUtil(false),
		  m_convexConservativeDistanceThreshold(0.0f),
		  m_deterministicOverlappingPairs(false)
	{
	}
	btScalar m_timeStep;
	int m_stepCount;
	int m_dispatchFunc;
	mutable btScalar m_timeOfImpact;
	bool m_useContinuous;
	bool m_enableSatConvex;
	bool m_enableSPU;
	bool m_useEpa;
	btScalar m_allowedCcdPenetration;
	bool m_useConvexConservativeDistanceUtil;
	btScalar m_convexConservativeDistanceThreshold;
	bool m_deterministicOverlappingPairs;
};

enum ebtDispatcherQueryType
{
	BT_CONTACT_POINT_ALGORITHMS = 1,
	BT_CLOSEST_POINT_ALGORITHMS = 2
};

#endif                  