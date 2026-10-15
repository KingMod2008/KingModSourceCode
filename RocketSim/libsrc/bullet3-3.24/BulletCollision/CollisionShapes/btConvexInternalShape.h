  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_CONVEX_INTERNAL_SHAPE_H
#define BT_CONVEX_INTERNAL_SHAPE_H

#include "btConvexShape.h"
#include "../../LinearMath/btAabbUtil2.h"

                                                                                                    
                                                                                           
                                                                                            
                                                                             
                                                                                     
                                                                                        
ATTRIBUTE_ALIGNED16(class)
btConvexInternalShape : public btConvexShape
{
protected:
	btVector3 m_implicitShapeDimensions;

	btScalar m_collisionMargin;

	btScalar m_padding;

	btConvexInternalShape();

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	virtual ~btConvexInternalShape()
	{
	}

	virtual btVector3 localGetSupportingVertex(const btVector3& vec) const;

	const btVector3& getImplicitShapeDimensions() const
	{
		return m_implicitShapeDimensions;
	}

	                                                    
	                                                                                
	                                                                                    
	                                                                                      
	void setImplicitShapeDimensions(const btVector3& dimensions)
	{
		m_implicitShapeDimensions = dimensions;
	}

	void setSafeMargin(btScalar minDimension, btScalar defaultMarginMultiplier = 0.1f)
	{
		btScalar safeMargin = defaultMarginMultiplier * minDimension;
		if (safeMargin < getMargin())
		{
			setMargin(safeMargin);
		}
	}
	void setSafeMargin(const btVector3& halfExtents, btScalar defaultMarginMultiplier = 0.1f)
	{
		                                                          
		                                                                       
		                                      
		btScalar minDimension = halfExtents[halfExtents.minAxis()];
		setSafeMargin(minDimension, defaultMarginMultiplier);
	}

	                                                                                                                  
	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const
	{
		getAabbSlow(t, aabbMin, aabbMax);
	}

	void getAabbSlow(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;
	
	void setMargin(btScalar margin)
	{
		m_collisionMargin = margin;
	}
	btScalar getMargin() const
	{
		return m_collisionMargin;
	}

	btScalar getMarginNV() const
	{
		return m_collisionMargin;
	}

	int getNumPreferredPenetrationDirections() const
	{
		return 0;
	}

	void getPreferredPenetrationDirection(int index, btVector3& penetrationVector) const
	{
		(void)penetrationVector;
		(void)index;
		btAssert(0);
	}
};

                                                                                                                           
class btConvexInternalAabbCachingShape : public btConvexInternalShape
{
	btVector3 m_localAabbMin;
	btVector3 m_localAabbMax;
	bool m_isLocalAabbValid;

protected:
	btConvexInternalAabbCachingShape();

	void setCachedLocalAabb(const btVector3& aabbMin, const btVector3& aabbMax)
	{
		m_isLocalAabbValid = true;
		m_localAabbMin = aabbMin;
		m_localAabbMax = aabbMax;
	}

	inline void getCachedLocalAabb(btVector3& aabbMin, btVector3& aabbMax) const
	{
		btAssert(m_isLocalAabbValid);
		aabbMin = m_localAabbMin;
		aabbMax = m_localAabbMax;
	}

	inline void getNonvirtualAabb(const btTransform& trans, btVector3& aabbMin, btVector3& aabbMax, btScalar margin) const
	{
		                               
		btAssert(m_isLocalAabbValid);
		btTransformAabb(m_localAabbMin, m_localAabbMax, margin, trans, aabbMin, aabbMax);
	}

public:

	void getAabb(const btTransform& t, btVector3& aabbMin, btVector3& aabbMax) const;

	void recalcLocalAabb();
};

#endif                              
