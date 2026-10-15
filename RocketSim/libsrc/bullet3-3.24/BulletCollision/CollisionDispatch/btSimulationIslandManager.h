  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_SIMULATION_ISLAND_MANAGER_H
#define BT_SIMULATION_ISLAND_MANAGER_H

#include "../CollisionDispatch/btUnionFind.h"
#include "btCollisionCreateFunc.h"
#include "../../LinearMath/btAlignedObjectArray.h"
#include "btCollisionObject.h"

class btCollisionObject;
class btCollisionWorld;
class btCollisionDispatcher;
class btPersistentManifold;

                                                                                    
class btSimulationIslandManager
{
	btUnionFind m_unionFind;

	btAlignedObjectArray<btPersistentManifold*> m_islandmanifold;
	btAlignedObjectArray<btCollisionObject*> m_islandBodies;

	bool m_splitIslands;

public:
	btSimulationIslandManager();
	virtual ~btSimulationIslandManager();

	void initUnionFind(int n);

	btUnionFind& getUnionFind() { return m_unionFind; }

	virtual void updateActivationState(btCollisionWorld* colWorld, btCollisionDispatcher* dispatcher);
	virtual void storeIslandActivationState(btCollisionWorld* world);

	void findUnions(btCollisionDispatcher* dispatcher, btCollisionWorld* colWorld);

	struct IslandCallback
	{
		virtual ~IslandCallback(){};

		virtual void processIsland(btCollisionObject** bodies, int numBodies, class btPersistentManifold** manifolds, int numManifolds, int islandId) = 0;
	};

	void buildAndProcessIslands(btCollisionDispatcher* dispatcher, btCollisionWorld* collisionWorld, IslandCallback* callback);
    
	void buildIslands(btCollisionDispatcher* dispatcher, btCollisionWorld* colWorld);

    void processIslands(btCollisionDispatcher* dispatcher, btCollisionWorld* collisionWorld, IslandCallback* callback);
    
	bool getSplitIslands()
	{
		return m_splitIslands;
	}
	void setSplitIslands(bool doSplitIslands)
	{
		m_splitIslands = doSplitIslands;
	}
};

#endif                                  
