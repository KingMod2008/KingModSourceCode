  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btCollisionAlgorithm.h"
#include "../CollisionDispatch/btCollisionDispatcher.h"

btCollisionAlgorithm::btCollisionAlgorithm(const btCollisionAlgorithmConstructionInfo& ci)
{
	m_dispatcher = ci.m_dispatcher1;
}
