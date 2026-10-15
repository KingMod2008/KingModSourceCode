  
                                                             
  
                                                                     
                                                                       
                                                                 
                                                                
                                      
                                                              
  
#ifndef BT_RAYCASTVEHICLE_H
#define BT_RAYCASTVEHICLE_H

#include "../Dynamics/btRigidBody.h"
#include "../ConstraintSolver/btTypedConstraint.h"
#include "btVehicleRaycaster.h"
class btDynamicsWorld;
#include "../../LinearMath/btAlignedObjectArray.h"
#include "btWheelInfo.h"
#include "../Dynamics/btActionInterface.h"

class btDefaultVehicleRaycaster : public btVehicleRaycaster
{
public:
	btDynamicsWorld* m_dynamicsWorld;

	btDefaultVehicleRaycaster() {}

	btDefaultVehicleRaycaster(btDynamicsWorld* world)
		: m_dynamicsWorld(world)
	{
	}

	virtual void* castRay(const btVector3& from, const btVector3& to, const btCollisionObject* ignoreObj, btVehicleRaycasterResult& result);
};

#endif                       
