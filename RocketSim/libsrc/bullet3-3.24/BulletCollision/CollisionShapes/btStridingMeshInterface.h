  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_STRIDING_MESHINTERFACE_H
#define BT_STRIDING_MESHINTERFACE_H

#include "../../LinearMath/btVector3.h"
#include "btTriangleCallback.h"
#include "btConcaveShape.h"

                                                                                                                                                                                               
                                                                                                                                                  
                                                                                                                                      
ATTRIBUTE_ALIGNED16(class)
btStridingMeshInterface
{
protected:
	btVector3 m_scaling;

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btStridingMeshInterface() : m_scaling(btScalar(1.), btScalar(1.), btScalar(1.))
	{
	}

	virtual ~btStridingMeshInterface();

	virtual void InternalProcessAllTriangles(btInternalTriangleIndexCallback * callback, const btVector3& aabbMin, const btVector3& aabbMax) const;

	                                       
	void calculateAabbBruteForce(btVector3 & aabbMin, btVector3 & aabbMax);

	                                                             
	                                                               
	                                                                         
	                                              
	                                                                              
	virtual void getLockedVertexIndexBase(unsigned char** vertexbase, int& numverts, int& stride, unsigned char** indexbase, int& indexstride, int& numfaces, int subpart = 0) = 0;

	virtual void getLockedReadOnlyVertexIndexBase(const unsigned char** vertexbase, int& numverts, int& stride, const unsigned char** indexbase, int& indexstride, int& numfaces, int subpart = 0) const = 0;

	                                                                          
	                                                                                                               
	virtual void unLockVertexBase(int subpart) = 0;

	virtual void unLockReadOnlyVertexBase(int subpart) const = 0;

	                                                          
	                                                               
	virtual int getNumSubParts() const = 0;

	virtual void preallocateVertices(int numverts) = 0;
	virtual void preallocateIndices(int numindices) = 0;

	virtual bool hasPremadeAabb() const { return false; }
	virtual void setPremadeAabb(const btVector3& aabbMin, const btVector3& aabbMax) const
	{
		(void)aabbMin;
		(void)aabbMax;
	}
	virtual void getPremadeAabb(btVector3 * aabbMin, btVector3 * aabbMax) const
	{
		(void)aabbMin;
		(void)aabbMax;
	}

	const btVector3& getScaling() const
	{
		return m_scaling;
	}
	void setScaling(const btVector3& scaling)
	{
		m_scaling = scaling;
	}
};

struct btIntIndexData
{
	int m_value;
};

struct btShortIntIndexData
{
	short m_value;
	char m_pad[2];
};

struct btShortIntIndexTripletData
{
	short m_values[3];
	char m_pad[2];
};

struct btCharIndexTripletData
{
	unsigned char m_values[3];
	char m_pad;
};

#endif                               
