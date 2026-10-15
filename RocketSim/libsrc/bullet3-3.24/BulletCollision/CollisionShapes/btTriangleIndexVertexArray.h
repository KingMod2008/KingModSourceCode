  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_TRIANGLE_INDEX_VERTEX_ARRAY_H
#define BT_TRIANGLE_INDEX_VERTEX_ARRAY_H

#include "btStridingMeshInterface.h"
#include "../../LinearMath/btAlignedObjectArray.h"
#include "../../LinearMath/btScalar.h"

                                                                                                                                                                  
                                                                     
ATTRIBUTE_ALIGNED16(struct)
btIndexedMesh
{
	BT_DECLARE_ALIGNED_ALLOCATOR();

	int m_numTriangles;
	const unsigned char* m_triangleIndexBase;
	                                                                                                        
	int m_triangleIndexStride;
	int m_numVertices;
	const unsigned char* m_vertexBase;
	                             
	int m_vertexStride;

	btIndexedMesh()
	{
	}
};

typedef btAlignedObjectArray<btIndexedMesh> IndexedMeshArray;

                                                                                                                             
                                                      
                                                                                                    
                                                                                      
ATTRIBUTE_ALIGNED16(class)
btTriangleIndexVertexArray : public btStridingMeshInterface
{
protected:
	IndexedMeshArray m_indexedMeshes;
	int m_pad[2];
	mutable int m_hasAabb;                                                    
	mutable btVector3 m_aabbMin;
	mutable btVector3 m_aabbMax;

public:
	BT_DECLARE_ALIGNED_ALLOCATOR();

	btTriangleIndexVertexArray() : m_hasAabb(0)
	{
	}

	virtual ~btTriangleIndexVertexArray();

	                                 
	btTriangleIndexVertexArray(int numTriangles, int* triangleIndexBase, int triangleIndexStride, int numVertices, btScalar* vertexBase, int vertexStride);

	void addIndexedMesh(const btIndexedMesh& mesh)
	{
		m_indexedMeshes.push_back(mesh);
	}

	virtual void getLockedVertexIndexBase(unsigned char** vertexbase, int& numverts, int& vertexStride, unsigned char** indexbase, int& indexstride, int& numfaces, int subpart = 0);

	virtual void getLockedReadOnlyVertexIndexBase(const unsigned char** vertexbase, int& numverts, int& vertexStride, const unsigned char** indexbase, int& indexstride, int& numfaces, int subpart = 0) const;

	                                                                          
	                                                                                                               
	virtual void unLockVertexBase(int subpart) { (void)subpart; }

	virtual void unLockReadOnlyVertexBase(int subpart) const { (void)subpart; }

	                                                          
	                                                               
	virtual int getNumSubParts() const
	{
		return (int)m_indexedMeshes.size();
	}

	IndexedMeshArray& getIndexedMeshArray()
	{
		return m_indexedMeshes;
	}

	const IndexedMeshArray& getIndexedMeshArray() const
	{
		return m_indexedMeshes;
	}

	virtual void preallocateVertices(int numverts) { (void)numverts; }
	virtual void preallocateIndices(int numindices) { (void)numindices; }

	virtual bool hasPremadeAabb() const;
	virtual void setPremadeAabb(const btVector3& aabbMin, const btVector3& aabbMax) const;
	virtual void getPremadeAabb(btVector3 * aabbMin, btVector3 * aabbMax) const;
};

#endif                                    
