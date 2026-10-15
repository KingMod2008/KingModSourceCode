  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef BT_TRIANGLE_MESH_H
#define BT_TRIANGLE_MESH_H

#include "btTriangleIndexVertexArray.h"
#include "../../LinearMath/btVector3.h"
#include "../../LinearMath/btAlignedObjectArray.h"

                                                                                                                                                                                                     
                                                                                            
                                                                                                                                                                                                                     
                                                                                                             
class btTriangleMesh : public btTriangleIndexVertexArray
{
public:
	btAlignedObjectArray<btVector3> m_4componentVertices;

	btAlignedObjectArray<unsigned int> m_32bitIndices;

	btScalar m_weldingThreshold;

	btTriangleMesh();

	                                                                                                                         
	                                                                              
	void addTriangle(const btVector3& vertex0, const btVector3& vertex1, const btVector3& vertex2, bool removeDuplicateVertices = false);

	                                                                                                                                                                                  
	void addTriangleIndices(int index1, int index2, int index3);

	int getNumTriangles() const;

	virtual void preallocateVertices(int numverts);
	virtual void preallocateIndices(int numindices);

	                                                                 
	int findOrAddVertex(const btVector3& vertex, bool removeDuplicateVertices);
	                                                          
	void addIndex(int index);
};

#endif                      
