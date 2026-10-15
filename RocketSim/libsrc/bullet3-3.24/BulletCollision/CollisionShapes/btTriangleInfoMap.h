  
                                                         
                                                          

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#ifndef _BT_TRIANGLE_INFO_MAP_H
#define _BT_TRIANGLE_INFO_MAP_H

#include "../../LinearMath/btHashMap.h"

                             
#define TRI_INFO_V0V1_CONVEX 1
#define TRI_INFO_V1V2_CONVEX 2
#define TRI_INFO_V2V0_CONVEX 4

#define TRI_INFO_V0V1_SWAP_NORMALB 8
#define TRI_INFO_V1V2_SWAP_NORMALB 16
#define TRI_INFO_V2V0_SWAP_NORMALB 32

                                                                                                                         
                            
struct btTriangleInfo
{
	btTriangleInfo()
	{
		m_edgeV0V1Angle = SIMD_2_PI;
		m_edgeV1V2Angle = SIMD_2_PI;
		m_edgeV2V0Angle = SIMD_2_PI;
		m_flags = 0;
	}

	int m_flags;

	btScalar m_edgeV0V1Angle;
	btScalar m_edgeV1V2Angle;
	btScalar m_edgeV2V0Angle;
};

typedef btHashMap<btHashInt, btTriangleInfo> btInternalTriangleInfoMap;

                                                                                                                                                         
struct btTriangleInfoMap : public btInternalTriangleInfoMap
{
	btScalar m_convexEpsilon;                                                                                            
	btScalar m_planarEpsilon;                                                                           
	btScalar m_equalVertexThreshold;                                                                                                                                                   
	btScalar m_edgeDistanceThreshold;                                                                                                                                                                            
	btScalar m_maxEdgeAngleThreshold;                                                                                            
	btScalar m_zeroAreaThreshold;                                                                                                                        

	btTriangleInfoMap()
	{
		m_convexEpsilon = 0.00f;
		m_planarEpsilon = 0.0001f;
		m_equalVertexThreshold = btScalar(0.0001) * btScalar(0.0001);
		m_edgeDistanceThreshold = btScalar(0.1);
		m_zeroAreaThreshold = btScalar(0.0001) * btScalar(0.0001);
		m_maxEdgeAngleThreshold = SIMD_2_PI;
	}
	virtual ~btTriangleInfoMap() {}
};

#endif