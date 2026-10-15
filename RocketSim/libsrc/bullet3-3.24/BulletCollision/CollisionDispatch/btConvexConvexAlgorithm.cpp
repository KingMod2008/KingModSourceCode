  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

                                                                                                                         
                                                                                                                                                  
                         
                                               
                     

#include "btConvexConvexAlgorithm.h"

                    
#include "../NarrowPhaseCollision/btDiscreteCollisionDetectorInterface.h"
#include "../BroadphaseCollision/btBroadphaseInterface.h"
#include "../CollisionDispatch/btCollisionObject.h"
#include "../CollisionShapes/btConvexShape.h"
#include "../CollisionShapes/btTriangleShape.h"
#include "../CollisionShapes/btConvexPolyhedron.h"

#include "../NarrowPhaseCollision/btGjkPairDetector.h"
#include "../BroadphaseCollision/btBroadphaseProxy.h"
#include "../CollisionDispatch/btCollisionDispatcher.h"
#include "../CollisionShapes/btBoxShape.h"
#include "../CollisionDispatch/btManifoldResult.h"

#include "../NarrowPhaseCollision/btConvexPenetrationDepthSolver.h"
#include "../NarrowPhaseCollision/btContinuousConvexCollision.h"
#include "../NarrowPhaseCollision/btSubSimplexConvexCast.h"
#include "../NarrowPhaseCollision/btGjkConvexCast.h"

#include "../NarrowPhaseCollision/btVoronoiSimplexSolver.h"
#include "../CollisionShapes/btSphereShape.h"

#include "../NarrowPhaseCollision/btGjkEpa2.h"
#include "../NarrowPhaseCollision/btGjkEpaPenetrationDepthSolver.h"
#include "../NarrowPhaseCollision/btPolyhedralContactClipping.h"
#include "../CollisionDispatch/btCollisionObjectWrapper.h"

           

static SIMD_FORCE_INLINE void segmentsClosestPoints(
	btVector3& ptsVector,
	btVector3& offsetA,
	btVector3& offsetB,
	btScalar& tA, btScalar& tB,
	const btVector3& translation,
	const btVector3& dirA, btScalar hlenA,
	const btVector3& dirB, btScalar hlenB)
{
	                                                                    

	btScalar dirA_dot_dirB = btDot(dirA, dirB);
	btScalar dirA_dot_trans = btDot(dirA, translation);
	btScalar dirB_dot_trans = btDot(dirB, translation);

	btScalar denom = 1.0f - dirA_dot_dirB * dirA_dot_dirB;

	if (denom == 0.0f)
	{
		tA = 0.0f;
	}
	else
	{
		tA = (dirA_dot_trans - dirB_dot_trans * dirA_dot_dirB) / denom;
		if (tA < -hlenA)
			tA = -hlenA;
		else if (tA > hlenA)
			tA = hlenA;
	}

	tB = tA * dirA_dot_dirB - dirB_dot_trans;

	if (tB < -hlenB)
	{
		tB = -hlenB;
		tA = tB * dirA_dot_dirB + dirA_dot_trans;

		if (tA < -hlenA)
			tA = -hlenA;
		else if (tA > hlenA)
			tA = hlenA;
	}
	else if (tB > hlenB)
	{
		tB = hlenB;
		tA = tB * dirA_dot_dirB + dirA_dot_trans;

		if (tA < -hlenA)
			tA = -hlenA;
		else if (tA > hlenA)
			tA = hlenA;
	}

	                                                          

	offsetA = dirA * tA;
	offsetB = dirB * tB;

	ptsVector = translation - offsetA + offsetB;
}

static SIMD_FORCE_INLINE btScalar capsuleCapsuleDistance(
	btVector3& normalOnB,
	btVector3& pointOnB,
	btScalar capsuleLengthA,
	btScalar capsuleRadiusA,
	btScalar capsuleLengthB,
	btScalar capsuleRadiusB,
	int capsuleAxisA,
	int capsuleAxisB,
	const btTransform& transformA,
	const btTransform& transformB,
	btScalar distanceThreshold)
{
	btVector3 directionA = transformA.getBasis().getColumn(capsuleAxisA);
	btVector3 translationA = transformA.getOrigin();
	btVector3 directionB = transformB.getBasis().getColumn(capsuleAxisB);
	btVector3 translationB = transformB.getOrigin();

	                              

	btVector3 translation = translationB - translationA;

	                                                          

	btVector3 ptsVector;                                          

	btVector3 offsetA, offsetB;                                                         
	btScalar tA, tB;                                          

	segmentsClosestPoints(ptsVector, offsetA, offsetB, tA, tB, translation,
						  directionA, capsuleLengthA, directionB, capsuleLengthB);

	btScalar distance = ptsVector.length() - capsuleRadiusA - capsuleRadiusB;

	if (distance > distanceThreshold)
		return distance;

	btScalar lenSqr = ptsVector.length2();
	if (lenSqr <= (SIMD_EPSILON * SIMD_EPSILON))
	{
		                                                                                                            
		btVector3 q;
		btPlaneSpace1(directionA, normalOnB, q);
	}
	else
	{
		                             
		normalOnB = ptsVector * -btRecipSqrt(lenSqr);
	}
	pointOnB = transformB.getOrigin() + offsetB + normalOnB * capsuleRadiusB;

	return distance;
}

          

btConvexConvexAlgorithm::CreateFunc::CreateFunc(btConvexPenetrationDepthSolver* pdSolver)
{
	m_numPerturbationIterations = 0;
	m_minimumPointsPerturbationThreshold = 3;
	m_pdSolver = pdSolver;
}

btConvexConvexAlgorithm::CreateFunc::~CreateFunc()
{
}

btConvexConvexAlgorithm::btConvexConvexAlgorithm(btPersistentManifold* mf, const btCollisionAlgorithmConstructionInfo& ci, const btCollisionObjectWrapper* body0Wrap, const btCollisionObjectWrapper* body1Wrap, btConvexPenetrationDepthSolver* pdSolver, int numPerturbationIterations, int minimumPointsPerturbationThreshold)
	: btActivatingCollisionAlgorithm(ci, body0Wrap, body1Wrap),
	  m_pdSolver(pdSolver),
	  m_ownManifold(false),
	  m_manifoldPtr(mf),
	  m_lowLevelOfDetail(false),
#ifdef USE_SEPDISTANCE_UTIL2
	  m_sepDistance((static_cast<btConvexShape*>(body0->getCollisionShape()))->getAngularMotionDisc(),
					(static_cast<btConvexShape*>(body1->getCollisionShape()))->getAngularMotionDisc()),
#endif
	  m_numPerturbationIterations(numPerturbationIterations),
	  m_minimumPointsPerturbationThreshold(minimumPointsPerturbationThreshold)
{
	(void)body0Wrap;
	(void)body1Wrap;
}

btConvexConvexAlgorithm::~btConvexConvexAlgorithm()
{
	if (m_ownManifold)
	{
		if (m_manifoldPtr)
			m_dispatcher->releaseManifold(m_manifoldPtr);
	}
}

void btConvexConvexAlgorithm ::setLowLevelOfDetail(bool useLowLevel)
{
	m_lowLevelOfDetail = useLowLevel;
}

struct btPerturbedContactResult : public btManifoldResult
{
	btManifoldResult* m_originalManifoldResult;
	btTransform m_transformA;
	btTransform m_transformB;
	btTransform m_unPerturbedTransform;
	bool m_perturbA;

	btPerturbedContactResult(btManifoldResult* originalResult, const btTransform& transformA, const btTransform& transformB, const btTransform& unPerturbedTransform, bool perturbA)
		: m_originalManifoldResult(originalResult),
		  m_transformA(transformA),
		  m_transformB(transformB),
		  m_unPerturbedTransform(unPerturbedTransform),
		  m_perturbA(perturbA)
	{
	}
	virtual ~btPerturbedContactResult()
	{
	}

	virtual void addContactPoint(const btVector3& normalOnBInWorld, const btVector3& pointInWorld, btScalar orgDepth)
	{
		btVector3 endPt, startPt;
		btScalar newDepth;
		btVector3 newNormal;

		if (m_perturbA)
		{
			btVector3 endPtOrg = pointInWorld + normalOnBInWorld * orgDepth;
			endPt = (m_unPerturbedTransform * m_transformA.inverse())(endPtOrg);
			newDepth = (endPt - pointInWorld).dot(normalOnBInWorld);
			startPt = endPt - normalOnBInWorld * newDepth;
		}
		else
		{
			endPt = pointInWorld + normalOnBInWorld * orgDepth;
			startPt = (m_unPerturbedTransform * m_transformB.inverse())(pointInWorld);
			newDepth = (endPt - startPt).dot(normalOnBInWorld);
		}

                          
#ifdef DEBUG_CONTACTS
		m_debugDrawer->drawLine(startPt, endPt, btVector3(1, 0, 0));
		m_debugDrawer->drawSphere(startPt, 0.05, btVector3(0, 1, 0));
		m_debugDrawer->drawSphere(endPt, 0.05, btVector3(0, 0, 1));
#endif                  

		m_originalManifoldResult->addContactPoint(normalOnBInWorld, startPt, newDepth);
	}
};

extern btScalar gContactBreakingThreshold;

  
                                    
  
void btConvexConvexAlgorithm ::processCollision(const btCollisionObjectWrapper* body0Wrap, const btCollisionObjectWrapper* body1Wrap, const btDispatcherInfo& dispatchInfo, btManifoldResult* resultOut)
{
	if (!m_manifoldPtr) {
		          
		m_manifoldPtr = m_dispatcher->getNewManifold(body0Wrap->getCollisionObject(), body1Wrap->getCollisionObject());
		m_ownManifold = true;
	}
	resultOut->setPersistentManifold(m_manifoldPtr);

	                                                        
	                                                      

	const btConvexShape* min0 = static_cast<const btConvexShape*>(body0Wrap->getCollisionShape());
	const btConvexShape* min1 = static_cast<const btConvexShape*>(body1Wrap->getCollisionShape());

	btVector3  normalOnB;
	btVector3  pointOnBWorld;

#ifdef USE_SEPDISTANCE_UTIL2
	if (dispatchInfo.m_useConvexConservativeDistanceUtil) {
		m_sepDistance.updateSeparatingDistance(body0->getWorldTransform(), body1->getWorldTransform());
	}

	if (!dispatchInfo.m_useConvexConservativeDistanceUtil || m_sepDistance.getConservativeSeparatingDistance() <= 0.f)
#endif                        

	{

		btGjkPairDetector::ClosestPointInput input;

		btVoronoiSimplexSolver simplexSolver;
		btGjkPairDetector	gjkPairDetector(min0, min1, &simplexSolver, m_pdSolver);
		                                         
		gjkPairDetector.setMinkowskiA(min0);
		gjkPairDetector.setMinkowskiB(min1);

#ifdef USE_SEPDISTANCE_UTIL2
		if (dispatchInfo.m_useConvexConservativeDistanceUtil) {
			input.m_maximumDistanceSquared = BT_LARGE_FLOAT;
		} else
#endif                        
		{
			                                             
			   
			                                                                                                                           
			        
			   
			input.m_maximumDistanceSquared = min0->getMargin() + min1->getMargin() + m_manifoldPtr->getContactBreakingThreshold();
			     

			input.m_maximumDistanceSquared *= input.m_maximumDistanceSquared;
		}

		input.m_transformA = body0Wrap->getWorldTransform();
		input.m_transformB = body1Wrap->getWorldTransform();

#ifdef USE_SEPDISTANCE_UTIL2
		btScalar sepDist = 0.f;
		if (dispatchInfo.m_useConvexConservativeDistanceUtil) {
			sepDist = gjkPairDetector.getCachedSeparatingDistance();
			if (sepDist > SIMD_EPSILON) {
				sepDist += dispatchInfo.m_convexConservativeDistanceThreshold;
				                                                        

			}
		}
#endif                        

		if (min0->isPolyhedral() && min1->isPolyhedral()) {


			struct btDummyResult : public btDiscreteCollisionDetectorInterface::Result
			{
				virtual void setShapeIdentifiersA(int partId0, int index0) {}
				virtual void setShapeIdentifiersB(int partId1, int index1) {}
				virtual void addContactPoint(const btVector3& normalOnBInWorld, const btVector3& pointInWorld, btScalar depth) {
				}
			};


			struct btWithoutMarginResult : public btDiscreteCollisionDetectorInterface::Result
			{
				btDiscreteCollisionDetectorInterface::Result* m_originalResult;
				btVector3	m_reportedNormalOnWorld;
				btScalar m_marginOnA;
				btScalar m_marginOnB;
				btScalar	m_reportedDistance;

				bool		m_foundResult;
				btWithoutMarginResult(btDiscreteCollisionDetectorInterface::Result* result, btScalar marginOnA, btScalar marginOnB)
					:m_originalResult(result),
					m_marginOnA(marginOnA),
					m_marginOnB(marginOnB),
					m_foundResult(false) {
				}

				virtual void setShapeIdentifiersA(int partId0, int index0) {}
				virtual void setShapeIdentifiersB(int partId1, int index1) {}
				virtual void addContactPoint(const btVector3& normalOnBInWorld, const btVector3& pointInWorldOrg, btScalar depthOrg) {
					m_reportedDistance = depthOrg;
					m_reportedNormalOnWorld = normalOnBInWorld;

					btVector3 adjustedPointB = pointInWorldOrg - normalOnBInWorld * m_marginOnB;
					m_reportedDistance = depthOrg + (m_marginOnA + m_marginOnB);
					if (m_reportedDistance < 0.f) {
						m_foundResult = true;
					}
					m_originalResult->addContactPoint(normalOnBInWorld, adjustedPointB, m_reportedDistance);
				}
			};


			btDummyResult dummy;

			                                                                                        

			btScalar min0Margin = min0->getShapeType() == BOX_SHAPE_PROXYTYPE ? 0.f : min0->getMargin();
			btScalar min1Margin = min1->getShapeType() == BOX_SHAPE_PROXYTYPE ? 0.f : min1->getMargin();

			btWithoutMarginResult	withoutMargin(resultOut, min0Margin, min1Margin);

			btPolyhedralConvexShape* polyhedronA = (btPolyhedralConvexShape*)min0;
			btPolyhedralConvexShape* polyhedronB = (btPolyhedralConvexShape*)min1;
			if (polyhedronA->getConvexPolyhedron() && polyhedronB->getConvexPolyhedron()) {

				btScalar threshold = m_manifoldPtr->getContactBreakingThreshold();

				btScalar minDist = -1e30f;
				btVector3 sepNormalWorldSpace;
				bool foundSepAxis = true;

				if (dispatchInfo.m_enableSatConvex) {
					foundSepAxis = btPolyhedralContactClipping::findSeparatingAxis(
						*polyhedronA->getConvexPolyhedron(), *polyhedronB->getConvexPolyhedron(),
						body0Wrap->getWorldTransform(),
						body1Wrap->getWorldTransform(),
						sepNormalWorldSpace, *resultOut);
				} else {
#ifdef ZERO_MARGIN
					gjkPairDetector.setIgnoreMargin(true);
					gjkPairDetector.getClosestPoints(input, *resultOut, dispatchInfo.m_debugDraw);
#else


					gjkPairDetector.getClosestPoints(input, withoutMargin);
					                                                                         
#endif              
				                                                                    
				                      
					{
						sepNormalWorldSpace = withoutMargin.m_reportedNormalOnWorld;                                                     
						                                                                   
						minDist = withoutMargin.m_reportedDistance;                                                                                    

#ifdef ZERO_MARGIN
						foundSepAxis = true;                                                    
#else
						foundSepAxis = withoutMargin.m_foundResult && minDist < 0;                                         
#endif
					}
				}
				if (foundSepAxis) {

					                                                                                                                            
					btDiscreteCollisionDetectorInterface::Result* resultOutDisc = resultOut;
					btPolyhedralContactClipping::clipHullAgainstHull(sepNormalWorldSpace, *polyhedronA->getConvexPolyhedron(), *polyhedronB->getConvexPolyhedron(),
						body0Wrap->getWorldTransform(),
						body1Wrap->getWorldTransform(), minDist - threshold, threshold, *resultOut);

				}
				if (m_ownManifold) {
					resultOut->refreshContactPoints();
				}
				return;

			} else {
				                                                                          
				if (polyhedronA->getConvexPolyhedron() && polyhedronB->getShapeType() == TRIANGLE_SHAPE_PROXYTYPE) {

					btVertexArray vertices;
					btTriangleShape* tri = (btTriangleShape*)polyhedronB;
					vertices.push_back(body1Wrap->getWorldTransform() * tri->m_vertices1[0]);
					vertices.push_back(body1Wrap->getWorldTransform() * tri->m_vertices1[1]);
					vertices.push_back(body1Wrap->getWorldTransform() * tri->m_vertices1[2]);

					                                      

					btScalar threshold = m_manifoldPtr->getContactBreakingThreshold();

					btVector3 sepNormalWorldSpace;
					btScalar minDist = -1e30f;
					btScalar maxDist = threshold;

					bool foundSepAxis = false;
					if (0) {
						polyhedronB->initializePolyhedralFeatures();
						foundSepAxis = btPolyhedralContactClipping::findSeparatingAxis(
							*polyhedronA->getConvexPolyhedron(), *polyhedronB->getConvexPolyhedron(),
							body0Wrap->getWorldTransform(),
							body1Wrap->getWorldTransform(),
							sepNormalWorldSpace, *resultOut);
						                                                                                                                              

				} else {
#ifdef ZERO_MARGIN
						gjkPairDetector.setIgnoreMargin(true);
						gjkPairDetector.getClosestPoints(input, *resultOut, dispatchInfo.m_debugDraw);
#else
						gjkPairDetector.getClosestPoints(input, dummy);
#endif             

						btScalar l2 = gjkPairDetector.getCachedSeparatingAxis().length2();
						if (l2 > SIMD_EPSILON) {
							sepNormalWorldSpace = gjkPairDetector.getCachedSeparatingAxis() * (1.f / l2);
							                                                          
							                      
							minDist = gjkPairDetector.getCachedSeparatingDistance() - min0->getMargin() - min1->getMargin();
							foundSepAxis = true;
						}
					}


					if (foundSepAxis) {
						btPolyhedralContactClipping::clipFaceAgainstHull(sepNormalWorldSpace, *polyhedronA->getConvexPolyhedron(),
							body0Wrap->getWorldTransform(), vertices, minDist - threshold, maxDist, *resultOut);
					}


					if (m_ownManifold) {
						resultOut->refreshContactPoints();
					}

					return;
			}

		}


		}

		gjkPairDetector.getClosestPoints(input, *resultOut);

		                                                                                                    

		                                                                                   
		if (m_numPerturbationIterations && resultOut->getPersistentManifold()->getNumContacts() < m_minimumPointsPerturbationThreshold) {

			int i;
			btVector3 v0, v1;
			btVector3 sepNormalWorldSpace;
			btScalar l2 = gjkPairDetector.getCachedSeparatingAxis().length2();

			if (l2 > SIMD_EPSILON) {
				sepNormalWorldSpace = gjkPairDetector.getCachedSeparatingAxis() * (1.f / l2);

				btPlaneSpace1(sepNormalWorldSpace, v0, v1);


				bool perturbeA = true;
				const btScalar angleLimit = 0.125f * SIMD_PI;
				btScalar perturbeAngle;
				btScalar radiusA = min0->getAngularMotionDisc();
				btScalar radiusB = min1->getAngularMotionDisc();
				if (radiusA < radiusB) {
					perturbeAngle = gContactBreakingThreshold / radiusA;
					perturbeA = true;
				} else {
					perturbeAngle = gContactBreakingThreshold / radiusB;
					perturbeA = false;
				}
				if (perturbeAngle > angleLimit)
					perturbeAngle = angleLimit;

				btTransform unPerturbedTransform;
				if (perturbeA) {
					unPerturbedTransform = input.m_transformA;
				} else {
					unPerturbedTransform = input.m_transformB;
				}

				for (i = 0; i < m_numPerturbationIterations; i++) {
					if (v0.length2() > SIMD_EPSILON) {
						btQuaternion perturbeRot(v0, perturbeAngle);
						btScalar iterationAngle = i * (SIMD_2_PI / btScalar(m_numPerturbationIterations));
						btQuaternion rotq(sepNormalWorldSpace, iterationAngle);


						if (perturbeA) {
							input.m_transformA.setBasis(btMatrix3x3(rotq.inverse() * perturbeRot * rotq) * body0Wrap->getWorldTransform().getBasis());
							input.m_transformB = body1Wrap->getWorldTransform();
#ifdef DEBUG_CONTACTS
							dispatchInfo.m_debugDraw->drawTransform(input.m_transformA, 10.0);
#endif                 
						} else {
							input.m_transformA = body0Wrap->getWorldTransform();
							input.m_transformB.setBasis(btMatrix3x3(rotq.inverse() * perturbeRot * rotq) * body1Wrap->getWorldTransform().getBasis());
#ifdef DEBUG_CONTACTS
							dispatchInfo.m_debugDraw->drawTransform(input.m_transformB, 10.0);
#endif
						}

						btPerturbedContactResult perturbedResultOut(resultOut, input.m_transformA, input.m_transformB, unPerturbedTransform, perturbeA);
						gjkPairDetector.getClosestPoints(input, perturbedResultOut);
					}
				}
				}
			}



#ifdef USE_SEPDISTANCE_UTIL2
		if (dispatchInfo.m_useConvexConservativeDistanceUtil && (sepDist > SIMD_EPSILON)) {
			m_sepDistance.initSeparatingDistance(gjkPairDetector.getCachedSeparatingAxis(), sepDist, body0->getWorldTransform(), body1->getWorldTransform());
		}
#endif                        


		}

	if (m_ownManifold) {
		resultOut->refreshContactPoints();
	}
}

bool disableCcd = false;
btScalar btConvexConvexAlgorithm::calculateTimeOfImpact(btCollisionObject* col0, btCollisionObject* col1, const btDispatcherInfo& dispatchInfo, btManifoldResult* resultOut)
{
	(void)resultOut;
	(void)dispatchInfo;
	                                                                                   

	                                                                              
	                          
	btScalar resultFraction = btScalar(1.);

	btScalar squareMot0 = (col0->getInterpolationWorldTransform().getOrigin() - col0->getWorldTransform().getOrigin()).length2();
	btScalar squareMot1 = (col1->getInterpolationWorldTransform().getOrigin() - col1->getWorldTransform().getOrigin()).length2();

	if (squareMot0 < col0->getCcdSquareMotionThreshold() &&
		squareMot1 < col1->getCcdSquareMotionThreshold())
		return resultFraction;

	if (disableCcd)
		return btScalar(1.);

	                                                                       
	                                                            
	                                                         
	                                                                                       
	                                                                                                                                           

	                                      
	{
		btConvexShape* convex0 = static_cast<btConvexShape*>(col0->getCollisionShape());

		btSphereShape sphere1(col1->getCcdSweptSphereRadius());                                                               
		btConvexCast::CastResult result;
		btVoronoiSimplexSolver voronoiSimplex;
		                                                          
		                                                       
		btGjkConvexCast ccd1(convex0, &sphere1, &voronoiSimplex);
		                                                             
		if (ccd1.calcTimeOfImpact(col0->getWorldTransform(), col0->getInterpolationWorldTransform(),
								  col1->getWorldTransform(), col1->getInterpolationWorldTransform(), result))
		{
			                                        

			if (col0->getHitFraction() > result.m_fraction)
				col0->setHitFraction(result.m_fraction);

			if (col1->getHitFraction() > result.m_fraction)
				col1->setHitFraction(result.m_fraction);

			if (resultFraction > result.m_fraction)
				resultFraction = result.m_fraction;
		}
	}

	                                        
	{
		btConvexShape* convex1 = static_cast<btConvexShape*>(col1->getCollisionShape());

		btSphereShape sphere0(col0->getCcdSweptSphereRadius());                                                               
		btConvexCast::CastResult result;
		btVoronoiSimplexSolver voronoiSimplex;
		                                                          
		                                                       
		btGjkConvexCast ccd1(&sphere0, convex1, &voronoiSimplex);
		                                                             
		if (ccd1.calcTimeOfImpact(col0->getWorldTransform(), col0->getInterpolationWorldTransform(),
								  col1->getWorldTransform(), col1->getInterpolationWorldTransform(), result))
		{
			                                        

			if (col0->getHitFraction() > result.m_fraction)
				col0->setHitFraction(result.m_fraction);

			if (col1->getHitFraction() > result.m_fraction)
				col1->setHitFraction(result.m_fraction);

			if (resultFraction > result.m_fraction)
				resultFraction = result.m_fraction;
		}
	}

	return resultFraction;
}
