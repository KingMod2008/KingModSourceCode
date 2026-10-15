  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

                                              

#ifndef BT_OPTIMIZED_BVH_H
#define BT_OPTIMIZED_BVH_H

#include "../BroadphaseCollision/btQuantizedBvh.h"

class btStridingMeshInterface;

                                                                                                                              
ATTRIBUTE_ALIGNED16(class)
btOptimizedBvh : public btQuantizedBvh
{
public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

protected:
public:
	btOptimizedBvh();

	virtual ~btOptimizedBvh();

	void build(btStridingMeshInterface * triangles, bool useQuantizedAabbCompression, const btVector3& bvhAabbMin, const btVector3& bvhAabbMax);

	void refit(btStridingMeshInterface * triangles, const btVector3& aabbMin, const btVector3& aabbMax);

	void refitPartial(btStridingMeshInterface * triangles, const btVector3& aabbMin, const btVector3& aabbMax);

	void updateBvhNodes(btStridingMeshInterface * meshInterface, int firstNode, int endNode, int index);
};

#endif                      
