  
                                                             
  
                                                                     
                                                                       
                                                                 
                                                                
                                      
                                                              
  

#include "../../LinearMath/btVector3.h"
#include "btDefaultVehicleRaycaster.h"

#include "../ConstraintSolver/btJacobianEntry.h"
#include "../../LinearMath/btQuaternion.h"
#include "../Dynamics/btDynamicsWorld.h"
#include "btVehicleRaycaster.h"
#include "btWheelInfo.h"
#include "../../LinearMath/btMinMax.h"
#include "../ConstraintSolver/btContactConstraint.h"

#define ROLLING_INFLUENCE_FIX

btRigidBody& btActionInterface::getFixedBody()
{
	static btRigidBody s_fixed(0, 0, 0);
	s_fixed.setMassProps(btScalar(0.), btVector3(btScalar(0.), btScalar(0.), btScalar(0.)));
	return s_fixed;
}

void* btDefaultVehicleRaycaster::castRay(const btVector3& from, const btVector3& to, const btCollisionObject* ignoreObj, btVehicleRaycasterResult& result)
{
	                                     

	btCollisionWorld::ClosestRayResultCallback rayCallback(from, to, ignoreObj);
	rayCallback.m_collisionFilterGroup |= addedFilterMask;
	m_dynamicsWorld->rayTest(from, to, rayCallback);

	if (rayCallback.hasHit())
	{
		const btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);
		if (body && body->hasContactResponse())
		{
			result.m_hitPointInWorld = rayCallback.m_hitPointWorld;
			result.m_hitNormalInWorld = rayCallback.m_hitNormalWorld;
			result.m_hitNormalInWorld.normalize();
			result.m_distFraction = rayCallback.m_closestHitFraction;
			return (void*)body;
		}
	}
	return 0;
}
