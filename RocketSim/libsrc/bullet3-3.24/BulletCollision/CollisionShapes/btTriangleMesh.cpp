  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btTriangleMesh.h"

btTriangleMesh::btTriangleMesh() : 
	m_weldingThreshold(0.0)
{
	btIndexedMesh meshIndex;
	meshIndex.m_numTriangles = 0;
	meshIndex.m_numVertices = 0;
	meshIndex.m_triangleIndexBase = 0;
	meshIndex.m_triangleIndexStride = 3 * sizeof(int);
	meshIndex.m_vertexBase = 0;
	meshIndex.m_vertexStride = sizeof(btVector3);
	m_indexedMeshes.push_back(meshIndex);

	m_indexedMeshes[0].m_numTriangles = m_32bitIndices.size() / 3;
	m_indexedMeshes[0].m_triangleIndexBase = 0;
	m_indexedMeshes[0].m_triangleIndexStride = 3 * sizeof(int);

	m_indexedMeshes[0].m_numVertices = m_4componentVertices.size();
	m_indexedMeshes[0].m_vertexBase = 0;
	m_indexedMeshes[0].m_vertexStride = sizeof(btVector3);
}

void btTriangleMesh::addIndex(int index)
{
	m_32bitIndices.push_back(index);
	m_indexedMeshes[0].m_triangleIndexBase = (unsigned char*)&m_32bitIndices[0];
}

void btTriangleMesh::addTriangleIndices(int index1, int index2, int index3)
{
	m_indexedMeshes[0].m_numTriangles++;
	addIndex(index1);
	addIndex(index2);
	addIndex(index3);
}

int btTriangleMesh::findOrAddVertex(const btVector3& vertex, bool removeDuplicateVertices)
{
	                                     
	                                                   
	if (removeDuplicateVertices) {
		for (int i = 0; i < m_4componentVertices.size(); i++) {
			if ((m_4componentVertices[i] - vertex).length2() <= m_weldingThreshold) {
				return i;
			}
		}
	}
	m_indexedMeshes[0].m_numVertices++;
	m_4componentVertices.push_back(vertex);
	m_indexedMeshes[0].m_vertexBase = (unsigned char*)&m_4componentVertices[0];

	return m_4componentVertices.size() - 1;
}

void btTriangleMesh::addTriangle(const btVector3& vertex0, const btVector3& vertex1, const btVector3& vertex2, bool removeDuplicateVertices)
{
	m_indexedMeshes[0].m_numTriangles++;
	addIndex(findOrAddVertex(vertex0, removeDuplicateVertices));
	addIndex(findOrAddVertex(vertex1, removeDuplicateVertices));
	addIndex(findOrAddVertex(vertex2, removeDuplicateVertices));
}

int btTriangleMesh::getNumTriangles() const
{
	return m_32bitIndices.size() / 3;
}

void btTriangleMesh::preallocateVertices(int numverts)
{
	m_4componentVertices.reserve(numverts);
}

void btTriangleMesh::preallocateIndices(int numindices)
{
	m_32bitIndices.reserve(numindices);
}
