  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef _BT_ACTION_INTERFACE_H
#define _BT_ACTION_INTERFACE_H

class btCollisionWorld;

#include "../../LinearMath/btScalar.h"
#include "btRigidBody.h"

                                                                                                          
class btActionInterface
{
protected:
	static btRigidBody& getFixedBody();

public:
	virtual ~btActionInterface()
	{
	}

	virtual void updateAction(btCollisionWorld* collisionWorld, btScalar deltaTimeStep) = 0;
};

#endif                          
