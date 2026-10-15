  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_BVH_TRIANGLE_MESH_SHAPE_H
#define BT_BVH_TRIANGLE_MESH_SHAPE_H

#include "btTriangleMeshShape.h"
#include "btOptimizedBvh.h"
#include "../../LinearMath/btAlignedAllocator.h"
#include "btTriangleInfoMap.h"

                                                                                                                
                                                                                                    
                                                        
                                                                                    
                                                                                          
                                                       
                                                                                   
                                                                                                                                                                                                           
                                                                                                                                                                    
                                                               
ATTRIBUTE_ALIGNED16(class)
btBvhTriangleMeshShape : public btTriangleMeshShape
{

public:
	btOptimizedBvh* m_bvh;
	btTriangleInfoMap* m_triangleInfoMap;

	bool m_useQuantizedAabbCompression;
	bool m_ownsBvh;
#ifdef __clang__
	bool m_pad[11] __attribute__((unused));                                   
#else
	bool m_pad[11];                                   
#endif

	BT_DECLARE_ALIGNED_ALLOCATOR();

	btBvhTriangleMeshShape() {}

	btBvhTriangleMeshShape(btStridingMeshInterface * meshInterface, bool useQuantizedAabbCompression, bool buildBvh = true);

	                                                                                                             
	btBvhTriangleMeshShape(btStridingMeshInterface * meshInterface, bool useQuantizedAabbCompression, const btVector3& bvhAabbMin, const btVector3& bvhAabbMax, bool buildBvh = true);

	virtual ~btBvhTriangleMeshShape();

	bool getOwnsBvh() const
	{
		return m_ownsBvh;
	}

	void performRaycast(btTriangleCallback * callback, const btVector3& raySource, const btVector3& rayTarget);
	void performConvexcast(btTriangleCallback * callback, const btVector3& boxSource, const btVector3& boxTarget, const btVector3& boxMin, const btVector3& boxMax);

	void processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	void refitTree(const btVector3& aabbMin, const btVector3& aabbMax);

	                                                                                                                                       
	void partialRefitTree(const btVector3& aabbMin, const btVector3& aabbMax);

	           
	virtual const char* getName() const { return "BVHTRIANGLEMESH"; }

	btOptimizedBvh* getOptimizedBvh()
	{
		return m_bvh;
	}

	void setOptimizedBvh(btOptimizedBvh * bvh, const btVector3& localScaling = btVector3(1, 1, 1));

	void buildOptimizedBvh();

	bool usesQuantizedAabbCompression() const
	{
		return m_useQuantizedAabbCompression;
	}

	void setTriangleInfoMap(btTriangleInfoMap * triangleInfoMap)
	{
		m_triangleInfoMap = triangleInfoMap;
	}

	const btTriangleInfoMap* getTriangleInfoMap() const
	{
		return m_triangleInfoMap;
	}

	btTriangleInfoMap* getTriangleInfoMap()
	{
		return m_triangleInfoMap;
	}
};

#endif                                
