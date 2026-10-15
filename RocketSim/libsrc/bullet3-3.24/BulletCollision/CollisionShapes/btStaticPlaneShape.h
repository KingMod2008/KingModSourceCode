  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_STATIC_PLANE_SHAPE_H
#define BT_STATIC_PLANE_SHAPE_H

#include "btConcaveShape.h"

                                                                                    
ATTRIBUTE_ALIGNED16(class)
btStaticPlaneShape : public btConcaveShape
{
public:
	btVector3 m_localAabbMin;
	btVector3 m_localAabbMax;

	btVector3 m_planeNormal;
	btScalar m_planeConstant;
	
	                                        
	bool m_isSingleAxis;
	int m_singleAxisIdx;
	bool m_singleAxisBackwards;

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btStaticPlaneShape() {}

	btStaticPlaneShape(const btVector3& planeNormal, btScalar planeConstant);

	virtual ~btStaticPlaneShape();

	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

	void processAllTriangles(btTriangleCallback * callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	void calculateLocalInertia(btScalar mass, btVector3 & inertia) const;

	const btVector3& getPlaneNormal() const
	{
		return m_planeNormal;
	}

	const btScalar& getPlaneConstant() const
	{
		return m_planeConstant;
	}

	           
	virtual const char* getName() const { return "STATICPLANE"; }
};
#endif                           
