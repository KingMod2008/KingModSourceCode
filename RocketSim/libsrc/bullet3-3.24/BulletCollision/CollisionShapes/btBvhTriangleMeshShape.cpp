  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

                     

#include "../CollisionShapes/btBvhTriangleMeshShape.h"
#include "../CollisionShapes/btOptimizedBvh.h"

                                                                                                         
                                                                                             
btBvhTriangleMeshShape::btBvhTriangleMeshShape(btStridingMeshInterface* meshInterface, bool useQuantizedAabbCompression, bool buildBvh)
	: btTriangleMeshShape(meshInterface),
	  m_bvh(0),
	  m_triangleInfoMap(0),
	  m_useQuantizedAabbCompression(useQuantizedAabbCompression),
	  m_ownsBvh(false)
{
	m_shapeType = TRIANGLE_MESH_SHAPE_PROXYTYPE;
	                                  
#ifndef DISABLE_BVH

	if (buildBvh)
	{
		buildOptimizedBvh();
	}

#endif               
}

btBvhTriangleMeshShape::btBvhTriangleMeshShape(btStridingMeshInterface* meshInterface, bool useQuantizedAabbCompression, const btVector3& bvhAabbMin, const btVector3& bvhAabbMax, bool buildBvh)
	: btTriangleMeshShape(meshInterface),
	  m_bvh(0),
	  m_triangleInfoMap(0),
	  m_useQuantizedAabbCompression(useQuantizedAabbCompression),
	  m_ownsBvh(false)
{
	m_shapeType = TRIANGLE_MESH_SHAPE_PROXYTYPE;
	                                  
#ifndef DISABLE_BVH

	if (buildBvh)
	{
		void* mem = btAlignedAlloc(sizeof(btOptimizedBvh), 16);
		m_bvh = new (mem) btOptimizedBvh();

		m_bvh->build(meshInterface, m_useQuantizedAabbCompression, bvhAabbMin, bvhAabbMax);
		m_ownsBvh = true;
	}

#endif               
}

void btBvhTriangleMeshShape::partialRefitTree(const btVector3& aabbMin, const btVector3& aabbMax)
{
	m_bvh->refitPartial(m_meshInterface, aabbMin, aabbMax);

	m_localAabbMin.setMin(aabbMin);
	m_localAabbMax.setMax(aabbMax);
}

void btBvhTriangleMeshShape::refitTree(const btVector3& aabbMin, const btVector3& aabbMax)
{
	m_bvh->refit(m_meshInterface, aabbMin, aabbMax);

	recalcLocalAabb();
}

btBvhTriangleMeshShape::~btBvhTriangleMeshShape()
{
	if (m_ownsBvh)
	{
		m_bvh->~btOptimizedBvh();
		btAlignedFree(m_bvh);
	}
}

void btBvhTriangleMeshShape::performRaycast(btTriangleCallback* callback, const btVector3& raySource, const btVector3& rayTarget)
{
	MyNodeOverlapCallback myNodeCallback(callback, m_meshInterface);

	m_bvh->reportRayOverlappingNodex(&myNodeCallback, raySource, rayTarget);
}

void btBvhTriangleMeshShape::performConvexcast(btTriangleCallback* callback, const btVector3& raySource, const btVector3& rayTarget, const btVector3& aabbMin, const btVector3& aabbMax)
{
	MyNodeOverlapCallback myNodeCallback(callback, m_meshInterface);

	m_bvh->reportBoxCastOverlappingNodex(&myNodeCallback, raySource, rayTarget, aabbMin, aabbMax);
}

                                                                           
void btBvhTriangleMeshShape::processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const
{
#ifdef DISABLE_BVH
	                                    
	btTriangleMeshShape::processAllTriangles(callback, aabbMin, aabbMax);
#else

	                         

	

	MyNodeOverlapCallback myNodeCallback(callback, m_meshInterface);

	m_bvh->reportAabbOverlappingNodex(&myNodeCallback, aabbMin, aabbMax);

#endif               
}

void btBvhTriangleMeshShape::buildOptimizedBvh()
{
	if (m_ownsBvh)
	{
		m_bvh->~btOptimizedBvh();
		btAlignedFree(m_bvh);
	}
	                                                                                                                                         
	void* mem = btAlignedAlloc(sizeof(btOptimizedBvh), 16);
	m_bvh = new (mem) btOptimizedBvh();
	                    
	m_bvh->build(m_meshInterface, m_useQuantizedAabbCompression, m_localAabbMin, m_localAabbMax);
	m_ownsBvh = true;
}

void btBvhTriangleMeshShape::setOptimizedBvh(btOptimizedBvh* bvh, const btVector3& scaling)
{
	btAssert(!m_bvh);
	btAssert(!m_ownsBvh);

	m_bvh = bvh;
	m_ownsBvh = false;
}