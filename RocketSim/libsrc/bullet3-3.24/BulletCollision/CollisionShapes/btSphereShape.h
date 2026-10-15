  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  
#ifndef BT_SPHERE_MINKOWSKI_H
#define BT_SPHERE_MINKOWSKI_H

#include "btConvexInternalShape.h"
#include "../BroadphaseCollision/btBroadphaseProxy.h"                  

                                                                                               
ATTRIBUTE_ALIGNED16(class)
btSphereShape : public btConvexInternalShape

{
public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btSphereShape() {}

	btSphereShape(btScalar radius) : btConvexInternalShape()
	{
		m_shapeType = SPHERE_SHAPE_PROXYTYPE;
		m_implicitShapeDimensions.setZero();
		m_implicitShapeDimensions.setX(radius);
		m_collisionMargin = radius;
		m_padding = 0;
	}

	btVector3 localGetSupportingVertex(const btVector3& vec) const;
	btVector3 localGetSupportingVertexWithoutMargin(const btVector3& vec) const;
	                                               
	void batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors, btVector3* supportVerticesOut, int numVectors) const;

	void calculateLocalInertia(btScalar mass, btVector3 & inertia) const;

	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

	btScalar getRadius() const { return m_implicitShapeDimensions.x(); }

	void setUnscaledRadius(btScalar radius)
	{
		m_implicitShapeDimensions.setX(radius);
		btConvexInternalShape::setMargin(radius);
	}

	           
	const char* getName() const { return "SPHERE"; }

	void setMargin(btScalar margin)
	{
		btConvexInternalShape::setMargin(margin);
	}
	btScalar getMargin() const
	{
		                                                                                                        
		                                                          
		return getRadius();
	}
};

#endif                         
