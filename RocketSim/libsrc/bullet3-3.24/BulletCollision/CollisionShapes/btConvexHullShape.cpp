  
                                                         
                                                               

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#if defined(_WIN32) || defined(__i386__)
#define BT_USE_SSE_IN_API
#endif

#include "btConvexHullShape.h"
#include "btCollisionMargin.h"

#include "../../LinearMath/btQuaternion.h"
#include "btConvexPolyhedron.h"
#include "../../LinearMath/btConvexHullComputer.h"

btConvexHullShape::btConvexHullShape(const btScalar* points, int numPoints, int stride) : btPolyhedralConvexAabbCachingShape()
{
	m_shapeType = CONVEX_HULL_SHAPE_PROXYTYPE;
	m_unscaledPoints.resize(numPoints);

	unsigned char* pointsAddress = (unsigned char*)points;

	for (int i = 0; i < numPoints; i++)
	{
		btScalar* point = (btScalar*)pointsAddress;
		m_unscaledPoints[i] = btVector3(point[0], point[1], point[2]);
		pointsAddress += stride;
	}

	recalcLocalAabb();
}

void btConvexHullShape::addPoint(const btVector3& point, bool recalculateLocalAabb)
{
	m_unscaledPoints.push_back(point);
	if (recalculateLocalAabb)
		recalcLocalAabb();
}

btVector3 btConvexHullShape::localGetSupportingVertexWithoutMargin(const btVector3& vec) const
{
	btVector3 supVec(btScalar(0.), btScalar(0.), btScalar(0.));
	btScalar maxDot = btScalar(-BT_LARGE_FLOAT);

	                                                                                                                
	if (0 < m_unscaledPoints.size())
	{
		int index = (int)vec.maxDot(&m_unscaledPoints[0], m_unscaledPoints.size(), maxDot);                                                         
		return m_unscaledPoints[index];
	}

	return supVec;
}

void btConvexHullShape::batchedUnitVectorGetSupportingVertexWithoutMargin(const btVector3* vectors, btVector3* supportVerticesOut, int numVectors) const
{
	btScalar newDot;
	                                          
	{
		for (int i = 0; i < numVectors; i++)
		{
			supportVerticesOut[i][3] = btScalar(-BT_LARGE_FLOAT);
		}
	}

	for (int j = 0; j < numVectors; j++)
	{
		btVector3 vec = vectors[j];                            
		if (0 < m_unscaledPoints.size())
		{
			int i = (int)vec.maxDot(&m_unscaledPoints[0], m_unscaledPoints.size(), newDot);
			supportVerticesOut[j] = getScaledPoint(i);
			supportVerticesOut[j][3] = newDot;
		}
		else
			supportVerticesOut[j][3] = -BT_LARGE_FLOAT;
	}
}

btVector3 btConvexHullShape::localGetSupportingVertex(const btVector3& vec) const
{
	btVector3 supVertex = localGetSupportingVertexWithoutMargin(vec);

	if (getMargin() != btScalar(0.))
	{
		btVector3 vecnorm = vec;
		if (vecnorm.length2() < (SIMD_EPSILON * SIMD_EPSILON))
		{
			vecnorm.setValue(btScalar(-1.), btScalar(-1.), btScalar(-1.));
		}
		vecnorm.normalize();
		supVertex += getMargin() * vecnorm;
	}
	return supVertex;
}

void btConvexHullShape::optimizeConvexHull()
{
	btConvexHullComputer conv;
	conv.compute(&m_unscaledPoints[0].getX(), sizeof(btVector3), m_unscaledPoints.size(), 0.f, 0.f);
	int numVerts = conv.vertices.size();
	m_unscaledPoints.resize(0);
	for (int i = 0; i < numVerts; i++)
	{
		m_unscaledPoints.push_back(conv.vertices[i]);
	}
}

                                                                                                             
                                                                               
int btConvexHullShape::getNumVertices() const
{
	return m_unscaledPoints.size();
}

int btConvexHullShape::getNumEdges() const
{
	return m_unscaledPoints.size();
}

void btConvexHullShape::getEdge(int i, btVector3& pa, btVector3& pb) const
{
	int index0 = i % m_unscaledPoints.size();
	int index1 = (i + 1) % m_unscaledPoints.size();
	pa = getScaledPoint(index0);
	pb = getScaledPoint(index1);
}

void btConvexHullShape::getVertex(int i, btVector3& vtx) const
{
	vtx = getScaledPoint(i);
}

int btConvexHullShape::getNumPlanes() const
{
	return 0;
}

void btConvexHullShape::getPlane(btVector3&, btVector3&, int) const
{
	btAssert(0);
}

         
bool btConvexHullShape::isInside(const btVector3&, btScalar) const
{
	btAssert(0);
	return false;
}

void btConvexHullShape::project(const btTransform& trans, const btVector3& dir, btScalar& minProj, btScalar& maxProj, btVector3& witnesPtMin, btVector3& witnesPtMax) const
{
#if 1
	minProj = FLT_MAX;
	maxProj = -FLT_MAX;

	int numVerts = m_unscaledPoints.size();
	for (int i = 0; i < numVerts; i++)
	{
		btVector3 vtx = m_unscaledPoints[i];
		btVector3 pt = trans * vtx;
		btScalar dp = pt.dot(dir);
		if (dp < minProj)
		{
			minProj = dp;
			witnesPtMin = pt;
		}
		if (dp > maxProj)
		{
			maxProj = dp;
			witnesPtMax = pt;
		}
	}
#else
	btVector3 localAxis = dir * trans.getBasis();
	witnesPtMin = trans(localGetSupportingVertex(localAxis));
	witnesPtMax = trans(localGetSupportingVertex(-localAxis));

	minProj = witnesPtMin.dot(dir);
	maxProj = witnesPtMax.dot(dir);
#endif

	if (minProj > maxProj)
	{
		btSwap(minProj, maxProj);
		btSwap(witnesPtMin, witnesPtMax);
	}
}
