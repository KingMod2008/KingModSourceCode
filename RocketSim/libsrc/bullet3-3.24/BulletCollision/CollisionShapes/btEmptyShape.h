  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_EMPTY_SHAPE_H
#define BT_EMPTY_SHAPE_H

#include "btConcaveShape.h"

#include "../../LinearMath/btVector3.h"
#include "../../LinearMath/btTransform.h"
#include "../../LinearMath/btMatrix3x3.h"
#include "btCollisionMargin.h"

                                                                                                                           
                                                                                                    
ATTRIBUTE_ALIGNED16(class)
btEmptyShape : public btConcaveShape
{
public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btEmptyShape();

	virtual ~btEmptyShape();

	                                                                                                                  
	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

	void calculateLocalInertia(btScalar mass, btVector3 & inertia) const;

	const char* getName() const
	{
		return "Empty";
	}
};

#endif                    
