  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_COLLISION__DISPATCHER_H
#define BT_COLLISION__DISPATCHER_H

#include "../BroadphaseCollision/btDispatcher.h"
#include "../NarrowPhaseCollision/btPersistentManifold.h"

#include "../CollisionDispatch/btManifoldResult.h"

#include "../BroadphaseCollision/btBroadphaseProxy.h"
#include "../../LinearMath/btAlignedObjectArray.h"

class btOverlappingPairCache;
class btPoolAllocator;
class btCollisionConfiguration;

#include "btCollisionCreateFunc.h"

#define USE_DISPATCH_REGISTRY_ARRAY 1

class btCollisionDispatcher;
                                                                                                                    
typedef void (*btNearCallback)(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo);

                                                                                                        
                                                        
class btCollisionDispatcher
{
protected:
	int m_dispatcherFlags;

	btAlignedObjectArray<btPersistentManifold*> m_manifoldsPtr;

	btNearCallback m_nearCallback;

	btPoolAllocator* m_collisionAlgorithmPoolAllocator;

	btPoolAllocator* m_persistentManifoldPoolAllocator;

	btCollisionAlgorithmCreateFunc* m_doubleDispatchContactPoints[MAX_BROADPHASE_COLLISION_TYPES][MAX_BROADPHASE_COLLISION_TYPES];

	btCollisionAlgorithmCreateFunc* m_doubleDispatchClosestPoints[MAX_BROADPHASE_COLLISION_TYPES][MAX_BROADPHASE_COLLISION_TYPES];

	btCollisionConfiguration* m_collisionConfiguration;

public:
	enum DispatcherFlags
	{
		CD_STATIC_STATIC_REPORTED = 1,
		CD_USE_RELATIVE_CONTACT_BREAKING_THRESHOLD = 2,
		CD_DISABLE_CONTACTPOOL_DYNAMIC_ALLOCATION = 4
	};

	int getDispatcherFlags() const
	{
		return m_dispatcherFlags;
	}

	void setDispatcherFlags(int flags)
	{
		m_dispatcherFlags = flags;
	}

	                                                                                                   
	void registerCollisionCreateFunc(int proxyType0, int proxyType1, btCollisionAlgorithmCreateFunc* createFunc);

	void registerClosestPointsCreateFunc(int proxyType0, int proxyType1, btCollisionAlgorithmCreateFunc* createFunc);

	int getNumManifolds() const
	{
		return int(m_manifoldsPtr.size());
	}

	btPersistentManifold** getInternalManifoldPointer()
	{
		return m_manifoldsPtr.size() ? &m_manifoldsPtr[0] : 0;
	}

	btPersistentManifold* getManifoldByIndexInternal(int index)
	{
		btAssert(index>=0);
		btAssert(index<m_manifoldsPtr.size());
		return m_manifoldsPtr[index];
	}

	const btPersistentManifold* getManifoldByIndexInternal(int index) const
	{
		btAssert(index>=0);
		btAssert(index<m_manifoldsPtr.size());
		return m_manifoldsPtr[index];
	}

	btCollisionDispatcher() {}

	void setup(btCollisionConfiguration* collisionConfiguration);

	~btCollisionDispatcher();

	btPersistentManifold* getNewManifold(const btCollisionObject* b0, const btCollisionObject* b1);

	void releaseManifold(btPersistentManifold* manifold);

	void clearManifold(btPersistentManifold* manifold);

	btCollisionAlgorithm* findAlgorithm(const btCollisionObjectWrapper* body0Wrap, const btCollisionObjectWrapper* body1Wrap, btPersistentManifold* sharedManifold, ebtDispatcherQueryType queryType);

	bool needsCollision(const btCollisionObject* body0, const btCollisionObject* body1);

	bool needsResponse(const btCollisionObject* body0, const btCollisionObject* body1);

	void dispatchAllCollisionPairs(btOverlappingPairCache* pairCache, const btDispatcherInfo& dispatchInfo, btCollisionDispatcher* dispatcher);

	void setNearCallback(btNearCallback nearCallback)
	{
		m_nearCallback = nearCallback;
	}

	btNearCallback getNearCallback() const
	{
		return m_nearCallback;
	}

	                                                
	static void defaultNearCallback(btBroadphasePair& collisionPair, btCollisionDispatcher& dispatcher, const btDispatcherInfo& dispatchInfo);

	void* allocateCollisionAlgorithm(int size);

	void freeCollisionAlgorithm(void* ptr);

	btCollisionConfiguration* getCollisionConfiguration()
	{
		return m_collisionConfiguration;
	}

	const btCollisionConfiguration* getCollisionConfiguration() const
	{
		return m_collisionConfiguration;
	}

	void setCollisionConfiguration(btCollisionConfiguration* config)
	{
		m_collisionConfiguration = config;
	}

	btPoolAllocator* getInternalManifoldPool()
	{
		return m_persistentManifoldPoolAllocator;
	}

	const btPoolAllocator* getInternalManifoldPool() const
	{
		return m_persistentManifoldPoolAllocator;
	}
};

#endif                              
