  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_COLLISION_SHAPE_H
#define BT_COLLISION_SHAPE_H

#include "../../LinearMath/btTransform.h"
#include "../../LinearMath/btVector3.h"
#include "../../LinearMath/btMatrix3x3.h"
#include "../BroadphaseCollision/btBroadphaseProxy.h"                       

                                                                                                                     
ATTRIBUTE_ALIGNED16(class)
btCollisionShape
{
public:

	int m_shapeType;
	void* m_userPointer;
	int m_userIndex;
	int m_userIndex2;

	mutable bool m_aabbCached = false;
	mutable btVector3 m_aabbMinCache, m_aabbMaxCache;
	mutable btTransform m_aabbCacheTrans;

	BT_DECLARE_ALIGNED_ALLOCATOR();

	btCollisionShape() : 
		m_shapeType(INVALID_SHAPE_PROXYTYPE), m_userPointer(0), m_userIndex(-1), m_userIndex2(-1)
	{
	}

	virtual ~btCollisionShape()
	{
	}

	                                                                                                  
	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

	btScalar getMargin() const;
	void setMargin(btScalar margin);

	void getBoundingSphere(btVector3& center, btScalar& radius) const;

	                                                                                                                               
	btScalar getAngularMotionDisc() const;

	btScalar getContactBreakingThreshold(btScalar defaultContactThresholdFactor) const;

	                                                                                                        
	                         
	void calculateTemporalAabb(const btTransform& curTrans, const btVector3& linvel, const btVector3& angvel, btScalar timeStep, btVector3& temporalAabbMin, btVector3& temporalAabbMax) const;

	SIMD_FORCE_INLINE bool isPolyhedral() const
	{
		return btBroadphaseProxy::isPolyhedral(getShapeType());
	}

	SIMD_FORCE_INLINE bool isConvex2d() const
	{
		return btBroadphaseProxy::isConvex2d(getShapeType());
	}

	SIMD_FORCE_INLINE bool isConvex() const
	{
		return btBroadphaseProxy::isConvex(getShapeType());
	}
	SIMD_FORCE_INLINE bool isNonMoving() const
	{
		return btBroadphaseProxy::isNonMoving(getShapeType());
	}
	SIMD_FORCE_INLINE bool isConcave() const
	{
		return btBroadphaseProxy::isConcave(getShapeType());
	}
	SIMD_FORCE_INLINE bool isCompound() const
	{
		return btBroadphaseProxy::isCompound(getShapeType());
	}

	SIMD_FORCE_INLINE bool isSoftBody() const
	{
		return btBroadphaseProxy::isSoftBody(getShapeType());
	}

	                                                            
	SIMD_FORCE_INLINE bool isInfinite() const
	{
		return btBroadphaseProxy::isInfinite(getShapeType());
	}

#ifndef __SPU__

	void calculateLocalInertia(btScalar mass, btVector3& inertia) const {
		btAssert(false);
	}

	                   
	virtual const char* getName() const = 0;
#endif           

	int getShapeType() const
	{
		return m_shapeType;
	}

	                                                                                                    
	                                                      
	btVector3 getAnisotropicRollingFrictionDirection() const
	{
		return btVector3(1, 1, 1);
	}

	                             
	void setUserPointer(void* userPtr)
	{
		m_userPointer = userPtr;
	}

	void* getUserPointer() const
	{
		return m_userPointer;
	}
	void setUserIndex(int index)
	{
		m_userIndex = index;
	}

	int getUserIndex() const
	{
		return m_userIndex;
	}

	void setUserIndex2(int index)
	{
		m_userIndex2 = index;
	}

	int getUserIndex2() const
	{
		return m_userIndex2;
	}
};

#endif                        
