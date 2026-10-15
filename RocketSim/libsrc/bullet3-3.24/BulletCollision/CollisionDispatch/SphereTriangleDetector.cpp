  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "../../LinearMath/btScalar.h"
#include "SphereTriangleDetector.h"
#include "../CollisionShapes/btTriangleShape.h"
#include "../CollisionShapes/btSphereShape.h"

SphereTriangleDetector::SphereTriangleDetector(btSphereShape* sphere, btTriangleShape* triangle, btScalar contactBreakingThreshold)
	: m_sphere(sphere),
	  m_triangle(triangle),
	  m_contactBreakingThreshold(contactBreakingThreshold)
{
}

void SphereTriangleDetector::getClosestPoints(const ClosestPointInput& input, Result& output, bool swapResults)
{
	const btTransform& transformA = input.m_transformA;
	const btTransform& transformB = input.m_transformB;

	btVector3 point, normal;
	btScalar timeOfImpact = btScalar(1.);
	btScalar depth = btScalar(0.);
	                                                
	                                 
	btTransform sphereInTr = transformB.inverseTimes(transformA);

	if (collide(sphereInTr.getOrigin(), point, normal, depth, timeOfImpact, m_contactBreakingThreshold))
	{
		if (swapResults)
		{
			btVector3 normalOnB = transformB.getBasis() * normal;
			btVector3 normalOnA = -normalOnB;
			btVector3 pointOnA = transformB * point + normalOnB * depth;
			output.addContactPoint(normalOnA, pointOnA, depth);
		}
		else
		{
			output.addContactPoint(transformB.getBasis() * normal, transformB * point, depth);
		}
	}
}

                              
                                                                        
btScalar SegmentSqrDistance(const btVector3& from, const btVector3& to, const btVector3& p, btVector3& nearest);

btScalar SegmentSqrDistance(const btVector3& from, const btVector3& to, const btVector3& p, btVector3& nearest)
{
	btVector3 diff = p - from;
	btVector3 v = to - from;
	btScalar t = v.dot(diff);

	if (t > 0)
	{
		btScalar dotVV = v.dot(v);
		if (t < dotVV)
		{
			t /= dotVV;
			diff -= t * v;
		}
		else
		{
			t = 1;
			diff -= v;
		}
	}
	else
		t = 0;

	nearest = from + t * v;
	return diff.dot(diff);
}

                                                                                                             
btVector3 closestPointTriangle(btVector3 const& p, btVector3 const& a, btVector3 const& b, btVector3 const& c) {
	const btVector3 ab = b - a;
	const btVector3 ac = c - a;
	const btVector3 ap = p - a;

	const float d1 = ab.dot(ap);
	const float d2 = ac.dot(ap);
	if (d1 <= 0.f && d2 <= 0.f) return a;     

	const btVector3 bp = p - b;
	const float d3 = ab.dot(bp);
	const float d4 = ac.dot(bp);
	if (d3 >= 0.f && d4 <= d3) return b;     

	const btVector3 cp = p - c;
	const float d5 = ab.dot(cp);
	const float d6 = ac.dot(cp);
	if (d6 >= 0.f && d5 <= d6) return c;     

	const float vc = d1 * d4 - d3 * d2;
	if (vc <= 0.f && d1 >= 0.f && d3 <= 0.f) {
		const float v = d1 / (d1 - d3);
		return a + v * ab;     
	}

	const float vb = d5 * d2 - d1 * d6;
	if (vb <= 0.f && d2 >= 0.f && d6 <= 0.f) {
		const float v = d2 / (d2 - d6);
		return a + v * ac;     
	}

	const float va = d3 * d6 - d5 * d4;
	if (va <= 0.f && (d4 - d3) >= 0.f && (d5 - d6) >= 0.f) {
		const float v = (d4 - d3) / ((d4 - d3) + (d5 - d6));
		return b + v * (c - b);     
	}

	const float denom = 1.f / (va + vb + vc);
	const float v = vb * denom;
	const float w = vc * denom;
	return a + v * ab + w * ac;     
}

bool SphereTriangleDetector::facecontains(const btVector3& p, const btVector3* vertices, btVector3& normal)
{
	btVector3 lp(p);
	btVector3 lnormal(normal);

	return pointInTriangle(vertices, lnormal, &lp);
}

bool SphereTriangleDetector::collide(const btVector3& sphereCenter, btVector3& point, btVector3& resultNormal, btScalar& depth, btScalar& timeOfImpact, btScalar contactBreakingThreshold)
{
	const btVector3* vertices = &m_triangle->getVertexPtr(0);

	btScalar radius = m_sphere->getRadius();
	btScalar radiusWithThreshold = radius + contactBreakingThreshold;

	btVector3 normal = (vertices[1] - vertices[0]).cross(vertices[2] - vertices[0]);

	btScalar l2 = normal.length2();
	bool hasContact = false;
	btVector3 contactPoint;

	if (l2 >= SIMD_EPSILON * SIMD_EPSILON)
	{
		normal /= btSqrt(l2);

		btVector3 p1ToCentre = sphereCenter - vertices[0];
		btScalar distanceFromPlane = p1ToCentre.dot(normal);

		if (distanceFromPlane < btScalar(0.))
		{
			                               
			distanceFromPlane *= btScalar(-1.);
			normal *= btScalar(-1.);
		}

		bool isInsideContactPlane = distanceFromPlane < radiusWithThreshold;

		                                   

		if (isInsideContactPlane)
		{
			if (facecontains(sphereCenter, vertices, normal))
			{
				                                                                
				hasContact = true;
				contactPoint = sphereCenter - normal * distanceFromPlane;
			}
			else
			{
				                                              
				btScalar contactCapsuleRadiusSqr = radiusWithThreshold * radiusWithThreshold;
				btScalar minDistSqr = contactCapsuleRadiusSqr;

#if 0                   
				btVector3 nearestOnEdge;
				for (int i = 0; i < 3; i++)
				{
					btVector3 pa;
					btVector3 pb;

					m_triangle->getEdge(i, pa, pb);

					btScalar distanceSqr = SegmentSqrDistance(pa, pb, sphereCenter, nearestOnEdge);
					if (distanceSqr < minDistSqr)
					{
						                                                                             
						minDistSqr = distanceSqr;
						hasContact = true;
						contactPoint = nearestOnEdge;
					}
				}
#else                                 
				                                                                                                                 
				btVector3 nearestOnEdge = closestPointTriangle(sphereCenter, vertices[0], vertices[1], vertices[2]);
				btScalar distanceSqr = nearestOnEdge.distance2(sphereCenter);
				if (distanceSqr < minDistSqr) {
					minDistSqr = distanceSqr;
					hasContact = true;
					contactPoint = nearestOnEdge;
				}
#endif
			}
		}

	}

	if (hasContact)
	{
		btVector3 contactToCentre = sphereCenter - contactPoint;
		btScalar distanceSqr = contactToCentre.length2();

		if (distanceSqr < radiusWithThreshold * radiusWithThreshold)
		{
			if (distanceSqr > SIMD_EPSILON)
			{
				btScalar distance = btSqrt(distanceSqr);
				resultNormal = contactToCentre;
				resultNormal.normalize();
				point = contactPoint;
				depth = -(radius - distance);
			}
			else
			{
				resultNormal = normal;
				point = contactPoint;
				depth = -radius;
			}
			return true;
		}
	}

	return false;
}

bool SphereTriangleDetector::pointInTriangle(const btVector3 vertices[], const btVector3& normal, btVector3* p)
{
	
#if 0                   
	const btVector3* p1 = &vertices[0];
	const btVector3* p2 = &vertices[1];
	const btVector3* p3 = &vertices[2];

	btVector3 edge1(*p2 - *p1);
	btVector3 edge2(*p3 - *p2);
	btVector3 edge3(*p1 - *p3);

	btVector3 p1_to_p(*p - *p1);
	btVector3 p2_to_p(*p - *p2);
	btVector3 p3_to_p(*p - *p3);

	btVector3 edge1_normal(edge1.cross(normal));
	btVector3 edge2_normal(edge2.cross(normal));
	btVector3 edge3_normal(edge3.cross(normal));

	btScalar r1, r2, r3;
	r1 = edge1_normal.dot(p1_to_p);
	r2 = edge2_normal.dot(p2_to_p);
	r3 = edge3_normal.dot(p3_to_p);
	if ((r1 > 0 && r2 > 0 && r3 > 0) ||
		(r1 <= 0 && r2 <= 0 && r3 <= 0))
		return true;
	return false;
#else                                                                                                                                                         

	const btVector3&
		p0 = vertices[0],
		p1 = vertices[1],
		p2 = vertices[2];

	btVector3 u = p1 - p0;
	btVector3 v = p2 - p0;
	btVector3 n = u.cross(v);
	float nLenSq = n.dot(n);

	btVector3 w = *p - p0;

	float gamma = u.cross(w).dot(n) / nLenSq;

	float beta = w.cross(v).dot(n) / nLenSq;
	float alpha = 1 - gamma - beta;

	return ((0 <= alpha) && (alpha <= 1) &&
		(0 <= beta) && (beta <= 1) &&
		(0 <= gamma) && (gamma <= 1));
#endif
}
