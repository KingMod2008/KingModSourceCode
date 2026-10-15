  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btConcaveShape.h"

#include "btBvhTriangleMeshShape.h"
#include "btStaticPlaneShape.h"

btConcaveShape::btConcaveShape() : m_collisionMargin(btScalar(0.))
{
}

btConcaveShape::~btConcaveShape()
{
}

void btConcaveShape::processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const {
	switch (this->getShapeType()) {
	case TRIANGLE_MESH_SHAPE_PROXYTYPE:
		return ((btBvhTriangleMeshShape*)this)->processAllTriangles(callback, aabbMin, aabbMax);
	case STATIC_PLANE_PROXYTYPE:
		return ((btStaticPlaneShape*)this)->processAllTriangles(callback, aabbMin, aabbMax);
	default:
		btAssert(false);
	}
}