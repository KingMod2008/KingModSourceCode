  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btStridingMeshInterface.h"

btStridingMeshInterface::~btStridingMeshInterface()
{
}

void btStridingMeshInterface::InternalProcessAllTriangles(btInternalTriangleIndexCallback* callback, const btVector3& aabbMin, const btVector3& aabbMax) const
{
	(void)aabbMin;
	(void)aabbMax;
	int numtotalphysicsverts = 0;
	int part, graphicssubparts = getNumSubParts();
	const unsigned char* vertexbase;
	const unsigned char* indexbase;
	int indexstride;
	int stride, numverts, numtriangles;
	int gfxindex;
	btVector3 triangle[3];

	btVector3 meshScaling = getScaling();

	                                                                                                     
	for (part = 0; part < graphicssubparts; part++)
	{
		getLockedReadOnlyVertexIndexBase(&vertexbase, numverts, stride, &indexbase, indexstride, numtriangles, part);
		numtotalphysicsverts += numtriangles * 3;               

		float* graphicsbase;

		for (gfxindex = 0; gfxindex < numtriangles; gfxindex++) {
			unsigned int* tri_indices = (unsigned int*)(indexbase + gfxindex * indexstride);
			graphicsbase = (float*)(vertexbase + tri_indices[0] * stride);
			triangle[0].setValue(graphicsbase[0] * meshScaling.getX(), graphicsbase[1] * meshScaling.getY(), graphicsbase[2] * meshScaling.getZ());
			graphicsbase = (float*)(vertexbase + tri_indices[1] * stride);
			triangle[1].setValue(graphicsbase[0] * meshScaling.getX(), graphicsbase[1] * meshScaling.getY(), graphicsbase[2] * meshScaling.getZ());
			graphicsbase = (float*)(vertexbase + tri_indices[2] * stride);
			triangle[2].setValue(graphicsbase[0] * meshScaling.getX(), graphicsbase[1] * meshScaling.getY(), graphicsbase[2] * meshScaling.getZ());
			callback->internalProcessTriangleIndex(triangle, part, gfxindex);
		}

		unLockReadOnlyVertexBase(part);
	}
}

void btStridingMeshInterface::calculateAabbBruteForce(btVector3& aabbMin, btVector3& aabbMax)
{
	struct AabbCalculationCallback : public btInternalTriangleIndexCallback
	{
		btVector3 m_aabbMin;
		btVector3 m_aabbMax;

		AabbCalculationCallback()
		{
			m_aabbMin.setValue(btScalar(BT_LARGE_FLOAT), btScalar(BT_LARGE_FLOAT), btScalar(BT_LARGE_FLOAT));
			m_aabbMax.setValue(btScalar(-BT_LARGE_FLOAT), btScalar(-BT_LARGE_FLOAT), btScalar(-BT_LARGE_FLOAT));
		}

		virtual void internalProcessTriangleIndex(btVector3* triangle, int partId, int triangleIndex)
		{
			(void)partId;
			(void)triangleIndex;

			m_aabbMin.setMin(triangle[0]);
			m_aabbMax.setMax(triangle[0]);
			m_aabbMin.setMin(triangle[1]);
			m_aabbMax.setMax(triangle[1]);
			m_aabbMin.setMin(triangle[2]);
			m_aabbMax.setMax(triangle[2]);
		}
	};

	                                                  
	AabbCalculationCallback aabbCallback;
	aabbMin.setValue(btScalar(-BT_LARGE_FLOAT), btScalar(-BT_LARGE_FLOAT), btScalar(-BT_LARGE_FLOAT));
	aabbMax.setValue(btScalar(BT_LARGE_FLOAT), btScalar(BT_LARGE_FLOAT), btScalar(BT_LARGE_FLOAT));
	InternalProcessAllTriangles(&aabbCallback, aabbMin, aabbMax);

	aabbMin = aabbCallback.m_aabbMin;
	aabbMax = aabbCallback.m_aabbMax;
}