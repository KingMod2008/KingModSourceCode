  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_CONCAVE_SHAPE_H
#define BT_CONCAVE_SHAPE_H

#include "btCollisionShape.h"
#include "../BroadphaseCollision/btBroadphaseProxy.h"                  
#include "btTriangleCallback.h"

                                                                                         
                                                                                                           
ATTRIBUTE_ALIGNED16(class)
btConcaveShape : public btCollisionShape
{
protected:
	btScalar m_collisionMargin;

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btConcaveShape();

	virtual ~btConcaveShape();

	void processAllTriangles(btTriangleCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	btScalar getMargin() const
	{
		return m_collisionMargin;
	}
	void setMargin(btScalar collisionMargin)
	{
		m_collisionMargin = collisionMargin;
	}
};

#endif                      
