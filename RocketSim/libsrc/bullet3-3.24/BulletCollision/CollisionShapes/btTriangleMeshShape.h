  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_TRIANGLE_MESH_SHAPE_H
#define BT_TRIANGLE_MESH_SHAPE_H

#include "btConcaveShape.h"
#include "btStridingMeshInterface.h"

                                                                                                                                             
ATTRIBUTE_ALIGNED16(class)
btTriangleMeshShape : public btConcaveShape
{
protected:
	btVector3 m_localAabbMin;
	btVector3 m_localAabbMax;
	btStridingMeshInterface* m_meshInterface;

	                                                                                                                 
	                                                                        
	btTriangleMeshShape(btStridingMeshInterface * meshInterface);

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btTriangleMeshShape() {}

	virtual ~btTriangleMeshShape();

	btVector3 localGetSupportingVertex(const btVector3& vec) const;

	btVector3 localGetSupportingVertexWithoutMargin(const btVector3& vec) const
	{
		btAssert(0);
		return localGetSupportingVertex(vec);
	}

	void recalcLocalAabb();

	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax);

	void processAllTriangles(btTriangleCallback * callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	void calculateLocalInertia(btScalar mass, btVector3 & inertia) const;

	btStridingMeshInterface* getMeshInterface()
	{
		return m_meshInterface;
	}

	const btStridingMeshInterface* getMeshInterface() const
	{
		return m_meshInterface;
	}

	const btVector3& getLocalAabbMin() const
	{
		return m_localAabbMin;
	}
	const btVector3& getLocalAabbMax() const
	{
		return m_localAabbMax;
	}

	           
	virtual const char* getName() const { return "TRIANGLEMESH"; }
};

#endif                            
