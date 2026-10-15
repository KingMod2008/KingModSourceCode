  
                                                         
                                                                

                                                                           
                                                                                                  
                                                                      
                                                                               
                                      

                                                                                                                                                                                                                                                   
                                                                                                                         
                                                                          
  

#include "btQuantizedBvh.h"

#include "../../LinearMath/btAabbUtil2.h"
#include "../CollisionShapes/btStridingMeshInterface.h"

#define RAYAABB2

btQuantizedBvh::btQuantizedBvh() : m_bulletVersion(BT_BULLET_VERSION),
								   m_useQuantization(false),
								   m_subtreeHeaderCount(0)                      
{
	m_bvhAabbMin.setValue(-SIMD_INFINITY, -SIMD_INFINITY, -SIMD_INFINITY);
	m_bvhAabbMax.setValue(SIMD_INFINITY, SIMD_INFINITY, SIMD_INFINITY);
}

void btQuantizedBvh::buildInternal()
{
	                                                         
	m_useQuantization = true;
	int numLeafNodes = 0;

	if (m_useQuantization)
	{
		                                                  
		numLeafNodes = m_quantizedLeafNodes.size();

		m_quantizedContiguousNodes.resize(2 * numLeafNodes);
	}

	m_curNodeIndex = 0;

	buildTree(0, numLeafNodes);

	                                                                                              
	if (m_useQuantization && !m_SubtreeHeaders.size())
	{
		btBvhSubtreeInfo& subtree = m_SubtreeHeaders.expand();
		subtree.setAabbFromQuantizeNode(m_quantizedContiguousNodes[0]);
		subtree.m_rootNodeIndex = 0;
		subtree.m_subtreeSize = m_quantizedContiguousNodes[0].isLeafNode() ? 1 : m_quantizedContiguousNodes[0].getEscapeIndex();
	}

	                                  
	m_subtreeHeaderCount = m_SubtreeHeaders.size();

	                                                                     
	m_quantizedLeafNodes.clear();
	m_leafNodes.clear();
}

                                                                   
#ifdef DEBUG_PATCH_COLORS
btVector3 color[4] =
	{
		btVector3(1, 0, 0),
		btVector3(0, 1, 0),
		btVector3(0, 0, 1),
		btVector3(0, 1, 1)};
#endif                      

void btQuantizedBvh::setQuantizationValues(const btVector3& bvhAabbMin, const btVector3& bvhAabbMax, btScalar quantizationMargin)
{
	                                                                                      
	btVector3 clampValue(quantizationMargin, quantizationMargin, quantizationMargin);
	m_bvhAabbMin = bvhAabbMin - clampValue;
	m_bvhAabbMax = bvhAabbMax + clampValue;
	btVector3 aabbSize = m_bvhAabbMax - m_bvhAabbMin;
	m_bvhQuantization = btVector3(btScalar(65533.0), btScalar(65533.0), btScalar(65533.0)) / aabbSize;

	m_useQuantization = true;

	{
		unsigned short vecIn[3];
		btVector3 v;
		{
			quantize(vecIn, m_bvhAabbMin, false);
			v = unQuantize(vecIn);
			m_bvhAabbMin.setMin(v - clampValue);
		}
		aabbSize = m_bvhAabbMax - m_bvhAabbMin;
		m_bvhQuantization = btVector3(btScalar(65533.0), btScalar(65533.0), btScalar(65533.0)) / aabbSize;
		{
			quantize(vecIn, m_bvhAabbMax, true);
			v = unQuantize(vecIn);
			m_bvhAabbMax.setMax(v + clampValue);
		}
		aabbSize = m_bvhAabbMax - m_bvhAabbMin;
		m_bvhQuantization = btVector3(btScalar(65533.0), btScalar(65533.0), btScalar(65533.0)) / aabbSize;
	}
}

btQuantizedBvh::~btQuantizedBvh()
{
}

#ifdef DEBUG_TREE_BUILDING
int gStackDepth = 0;
int gMaxStackDepth = 0;
#endif                       

void btQuantizedBvh::buildTree(int startIndex, int endIndex)
{
#ifdef DEBUG_TREE_BUILDING
	gStackDepth++;
	if (gStackDepth > gMaxStackDepth)
		gMaxStackDepth = gStackDepth;
#endif                       

	int splitAxis, splitIndex, i;
	int numIndices = endIndex - startIndex;
	int curIndex = m_curNodeIndex;

	btAssert(numIndices > 0);

	if (numIndices == 1)
	{
#ifdef DEBUG_TREE_BUILDING
		gStackDepth--;
#endif                       

		assignInternalNodeFromLeafNode(m_curNodeIndex, startIndex);

		m_curNodeIndex++;
		return;
	}
	                                                                                                                              

	splitAxis = calcSplittingAxis(startIndex, endIndex);

	splitIndex = sortAndCalcSplittingIndex(startIndex, endIndex, splitAxis);

	int internalNodeIndex = m_curNodeIndex;

	                                                                                         
	                                                                                          
	setInternalNodeAabbMin(m_curNodeIndex, m_bvhAabbMax);                                                                                           
	setInternalNodeAabbMax(m_curNodeIndex, m_bvhAabbMin);                                                                                              

	for (i = startIndex; i < endIndex; i++)
	{
		mergeInternalNodeAabb(m_curNodeIndex, getAabbMin(i), getAabbMax(i));
	}

	m_curNodeIndex++;

	                              

	int leftChildNodexIndex = m_curNodeIndex;

	                       
	buildTree(startIndex, splitIndex);

	int rightChildNodexIndex = m_curNodeIndex;
	                        
	buildTree(splitIndex, endIndex);

#ifdef DEBUG_TREE_BUILDING
	gStackDepth--;
#endif                       

	int escapeIndex = m_curNodeIndex - curIndex;

	if (m_useQuantization)
	{
		                                                    
		const int sizeQuantizedNode = sizeof(btQuantizedBvhNode);
		const int treeSizeInBytes = escapeIndex * sizeQuantizedNode;
		if (treeSizeInBytes > MAX_SUBTREE_SIZE_IN_BYTES)
		{
			updateSubtreeHeaders(leftChildNodexIndex, rightChildNodexIndex);
		}
	}
	else
	{
	}

	setInternalNodeEscapeIndex(internalNodeIndex, escapeIndex);
}

void btQuantizedBvh::updateSubtreeHeaders(int leftChildNodexIndex, int rightChildNodexIndex)
{
	btAssert(m_useQuantization);

	btQuantizedBvhNode& leftChildNode = m_quantizedContiguousNodes[leftChildNodexIndex];
	int leftSubTreeSize = leftChildNode.isLeafNode() ? 1 : leftChildNode.getEscapeIndex();
	int leftSubTreeSizeInBytes = leftSubTreeSize * static_cast<int>(sizeof(btQuantizedBvhNode));

	btQuantizedBvhNode& rightChildNode = m_quantizedContiguousNodes[rightChildNodexIndex];
	int rightSubTreeSize = rightChildNode.isLeafNode() ? 1 : rightChildNode.getEscapeIndex();
	int rightSubTreeSizeInBytes = rightSubTreeSize * static_cast<int>(sizeof(btQuantizedBvhNode));

	if (leftSubTreeSizeInBytes <= MAX_SUBTREE_SIZE_IN_BYTES)
	{
		btBvhSubtreeInfo& subtree = m_SubtreeHeaders.expand();
		subtree.setAabbFromQuantizeNode(leftChildNode);
		subtree.m_rootNodeIndex = leftChildNodexIndex;
		subtree.m_subtreeSize = leftSubTreeSize;
	}

	if (rightSubTreeSizeInBytes <= MAX_SUBTREE_SIZE_IN_BYTES)
	{
		btBvhSubtreeInfo& subtree = m_SubtreeHeaders.expand();
		subtree.setAabbFromQuantizeNode(rightChildNode);
		subtree.m_rootNodeIndex = rightChildNodexIndex;
		subtree.m_subtreeSize = rightSubTreeSize;
	}

	                                  
	m_subtreeHeaderCount = m_SubtreeHeaders.size();
}

int btQuantizedBvh::sortAndCalcSplittingIndex(int startIndex, int endIndex, int splitAxis)
{
	int i;
	int splitIndex = startIndex;
	int numIndices = endIndex - startIndex;
	btScalar splitValue;

	btVector3 means(btScalar(0.), btScalar(0.), btScalar(0.));
	for (i = startIndex; i < endIndex; i++)
	{
		btVector3 center = btScalar(0.5) * (getAabbMax(i) + getAabbMin(i));
		means += center;
	}
	means *= (btScalar(1.) / (btScalar)numIndices);

	splitValue = means[splitAxis];

	                                                                                                              
	for (i = startIndex; i < endIndex; i++)
	{
		btVector3 center = btScalar(0.5) * (getAabbMax(i) + getAabbMin(i));
		if (center[splitAxis] > splitValue)
		{
			      
			swapLeafNodes(i, splitIndex);
			splitIndex++;
		}
	}

	                                                                                                            
	                                                                                 
	                                                     
	                                                                                

	                                                                         
	                          

	                          
	int rangeBalancedIndices = numIndices / 3;
	bool unbalanced = ((splitIndex <= (startIndex + rangeBalancedIndices)) || (splitIndex >= (endIndex - 1 - rangeBalancedIndices)));

	if (unbalanced)
	{
		splitIndex = startIndex + (numIndices >> 1);
	}

	bool unbal = (splitIndex == startIndex) || (splitIndex == (endIndex));
	(void)unbal;
	btAssert(!unbal);

	return splitIndex;
}

int btQuantizedBvh::calcSplittingAxis(int startIndex, int endIndex)
{
	int i;

	btVector3 means(btScalar(0.), btScalar(0.), btScalar(0.));
	btVector3 variance(btScalar(0.), btScalar(0.), btScalar(0.));
	int numIndices = endIndex - startIndex;

	for (i = startIndex; i < endIndex; i++)
	{
		btVector3 center = btScalar(0.5) * (getAabbMax(i) + getAabbMin(i));
		means += center;
	}
	means *= (btScalar(1.) / (btScalar)numIndices);

	for (i = startIndex; i < endIndex; i++)
	{
		btVector3 center = btScalar(0.5) * (getAabbMax(i) + getAabbMin(i));
		btVector3 diff2 = center - means;
		diff2 = diff2 * diff2;
		variance += diff2;
	}
	variance *= (btScalar(1.) / ((btScalar)numIndices - 1));

	return variance.maxAxis();
}

void btQuantizedBvh::reportAabbOverlappingNodex(btNodeOverlapCallback* nodeCallback, const btVector3& aabbMin, const btVector3& aabbMax) const
{
	                                                                               

	if (m_useQuantization)
	{
		                      
		unsigned short int quantizedQueryAabbMin[3];
		unsigned short int quantizedQueryAabbMax[3];
		quantizeWithClamp(quantizedQueryAabbMin, aabbMin, 0);
		quantizeWithClamp(quantizedQueryAabbMax, aabbMax, 1);

		walkStacklessQuantizedTreeCacheFriendly(nodeCallback, quantizedQueryAabbMin, quantizedQueryAabbMax);
	}
	else
	{
		walkStacklessTree(nodeCallback, aabbMin, aabbMax);
	}
}

void btQuantizedBvh::walkStacklessTree(btNodeOverlapCallback* nodeCallback, const btVector3& aabbMin, const btVector3& aabbMax) const
{
	btAssert(!m_useQuantization);

	const btOptimizedBvhNode* rootNode = &m_contiguousNodes[0];
	int escapeIndex, curIndex = 0;
	int walkIterations = 0;
	bool isLeafNode;
	                               
	unsigned aabbOverlap;

	while (curIndex < m_curNodeIndex)
	{
		                         
		btAssert(walkIterations < m_curNodeIndex);

		walkIterations++;
		aabbOverlap = TestAabbAgainstAabb2(aabbMin, aabbMax, rootNode->m_aabbMinOrg, rootNode->m_aabbMaxOrg);
		isLeafNode = rootNode->m_escapeIndex == -1;

		                               
		if (isLeafNode && (aabbOverlap != 0))
		{
			((MyNodeOverlapCallback*)nodeCallback)->processNode(rootNode->m_subPart, rootNode->m_triangleIndex);
		}

		                               
		if ((aabbOverlap != 0) || isLeafNode)
		{
			rootNode++;
			curIndex++;
		}
		else
		{
			escapeIndex = rootNode->m_escapeIndex;
			rootNode += escapeIndex;
			curIndex += escapeIndex;
		}
	}
}

void btQuantizedBvh::walkStacklessTreeAgainstRay(btNodeOverlapCallback* nodeCallback, const btVector3& raySource, const btVector3& rayTarget, const btVector3& aabbMin, const btVector3& aabbMax, int startNodeIndex, int endNodeIndex) const
{
	btAssert(!m_useQuantization);

	const btOptimizedBvhNode* rootNode = &m_contiguousNodes[0];
	int escapeIndex, curIndex = 0;
	int walkIterations = 0;
	bool isLeafNode;
	                               
	unsigned aabbOverlap = 0;
	unsigned rayBoxOverlap = 0;
	btScalar lambda_max = 1.0;

	                                    
	btVector3 rayAabbMin = raySource;
	btVector3 rayAabbMax = raySource;
	rayAabbMin.setMin(rayTarget);
	rayAabbMax.setMax(rayTarget);

	                                          
	rayAabbMin += aabbMin;
	rayAabbMax += aabbMax;

#ifdef RAYAABB2
	btVector3 rayDir = (rayTarget - raySource);
	rayDir.safeNormalize();                                                            
	lambda_max = rayDir.dot(rayTarget - raySource);
	                                                                   
	btVector3 rayDirectionInverse;
	rayDirectionInverse[0] = rayDir[0] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[0];
	rayDirectionInverse[1] = rayDir[1] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[1];
	rayDirectionInverse[2] = rayDir[2] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[2];
	unsigned int sign[3] = {rayDirectionInverse[0] < 0.0, rayDirectionInverse[1] < 0.0, rayDirectionInverse[2] < 0.0};
#endif

	btVector3 bounds[2];

	while (curIndex < m_curNodeIndex)
	{
		btScalar param = 1.0;
		                         
		btAssert(walkIterations < m_curNodeIndex);

		walkIterations++;

		bounds[0] = rootNode->m_aabbMinOrg;
		bounds[1] = rootNode->m_aabbMaxOrg;
		                          
		bounds[0] -= aabbMax;
		bounds[1] -= aabbMin;

		aabbOverlap = TestAabbAgainstAabb2(rayAabbMin, rayAabbMax, rootNode->m_aabbMinOrg, rootNode->m_aabbMaxOrg);
		                                                                 

#ifdef RAYAABB2
		                                                                                                
		                                                
		                                                                      
		rayBoxOverlap = aabbOverlap ? btRayAabb2(raySource, rayDirectionInverse, sign, bounds, param, 0.0f, lambda_max) : false;

#else
		btVector3 normal;
		rayBoxOverlap = btRayAabb(raySource, rayTarget, bounds[0], bounds[1], param, normal);
#endif

		isLeafNode = rootNode->m_escapeIndex == -1;

		                               
		if (isLeafNode && (rayBoxOverlap != 0))
		{
			((MyNodeOverlapCallback*)nodeCallback)->processNode(rootNode->m_subPart, rootNode->m_triangleIndex);
		}

		                               
		if ((rayBoxOverlap != 0) || isLeafNode)
		{
			rootNode++;
			curIndex++;
		}
		else
		{
			escapeIndex = rootNode->m_escapeIndex;
			rootNode += escapeIndex;
			curIndex += escapeIndex;
		}
	}
}

void btQuantizedBvh::walkStacklessTreeAgainstRayNoAABB(btNodeOverlapCallback* nodeCallback, const btVector3& raySource, const btVector3& rayTarget, int startNodeIndex, int endNodeIndex) const {
	btAssert(!m_useQuantization);

	const btOptimizedBvhNode* rootNode = &m_contiguousNodes[0];
	int escapeIndex, curIndex = 0;
	int walkIterations = 0;
	bool isLeafNode;
	                               
	unsigned aabbOverlap = 0;
	unsigned rayBoxOverlap = 0;
	btScalar lambda_max = 1.0;

	                                    
	btVector3 rayAabbMin = raySource;
	btVector3 rayAabbMax = raySource;
	rayAabbMin.setMin(rayTarget);
	rayAabbMax.setMax(rayTarget);

#ifdef RAYAABB2
	btVector3 rayDir = (rayTarget - raySource);
	rayDir.safeNormalize();                                                            
	lambda_max = rayDir.dot(rayTarget - raySource);
	                                                                   
	btVector3 rayDirectionInverse;
	rayDirectionInverse[0] = rayDir[0] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[0];
	rayDirectionInverse[1] = rayDir[1] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[1];
	rayDirectionInverse[2] = rayDir[2] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDir[2];
	unsigned int sign[3] = { rayDirectionInverse[0] < 0.0, rayDirectionInverse[1] < 0.0, rayDirectionInverse[2] < 0.0 };
#endif

	btVector3 bounds[2];

	while (curIndex < m_curNodeIndex) {
		btScalar param = 1.0;
		                         
		btAssert(walkIterations < m_curNodeIndex);

		walkIterations++;

		bounds[0] = rootNode->m_aabbMinOrg;
		bounds[1] = rootNode->m_aabbMaxOrg;

		aabbOverlap = TestAabbAgainstAabb2(rayAabbMin, rayAabbMax, rootNode->m_aabbMinOrg, rootNode->m_aabbMaxOrg);
		                                                                 

#ifdef RAYAABB2
		                                                                                                
		                                                
		                                                                      
		rayBoxOverlap = aabbOverlap ? btRayAabb2(raySource, rayDirectionInverse, sign, bounds, param, 0.0f, lambda_max) : false;

#else
		btVector3 normal;
		rayBoxOverlap = btRayAabb(raySource, rayTarget, bounds[0], bounds[1], param, normal);
#endif

		isLeafNode = rootNode->m_escapeIndex == -1;

		                               
		if (isLeafNode && (rayBoxOverlap != 0)) {
			((MyNodeOverlapCallback*)nodeCallback)->processNode(rootNode->m_subPart, rootNode->m_triangleIndex);
		}

		                               
		if ((rayBoxOverlap != 0) || isLeafNode) {
			rootNode++;
			curIndex++;
		} else {
			escapeIndex = rootNode->m_escapeIndex;
			rootNode += escapeIndex;
			curIndex += escapeIndex;
		}
	}
}

void btQuantizedBvh::walkStacklessQuantizedTreeAgainstRay(btNodeOverlapCallback* nodeCallback, const btVector3& raySource, const btVector3& rayTarget, const btVector3& aabbMin, const btVector3& aabbMax, int startNodeIndex, int endNodeIndex) const
{
	btAssert(m_useQuantization);

	int curIndex = startNodeIndex;
	int walkIterations = 0;
	int subTreeSize = endNodeIndex - startNodeIndex;
	(void)subTreeSize;

	const btQuantizedBvhNode* rootNode = &m_quantizedContiguousNodes[startNodeIndex];
	int escapeIndex;

	bool isLeafNode;
	                               
	unsigned boxBoxOverlap = 0;
	unsigned rayBoxOverlap = 0;

	btScalar lambda_max = 1.0;

#ifdef RAYAABB2
	btVector3 rayDirection = (rayTarget - raySource);
	rayDirection.safeNormalize();                                                            
	lambda_max = rayDirection.dot(rayTarget - raySource);
	                                                                   
	rayDirection[0] = rayDirection[0] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDirection[0];
	rayDirection[1] = rayDirection[1] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDirection[1];
	rayDirection[2] = rayDirection[2] == btScalar(0.0) ? btScalar(BT_LARGE_FLOAT) : btScalar(1.0) / rayDirection[2];
	unsigned int sign[3] = {rayDirection[0] < 0.0, rayDirection[1] < 0.0, rayDirection[2] < 0.0};
#endif

	                                    
	btVector3 rayAabbMin = raySource;
	btVector3 rayAabbMax = raySource;
	rayAabbMin.setMin(rayTarget);
	rayAabbMax.setMax(rayTarget);

	                                          
	rayAabbMin += aabbMin;
	rayAabbMax += aabbMax;

	unsigned short int quantizedQueryAabbMin[3];
	unsigned short int quantizedQueryAabbMax[3];
	quantizeWithClamp(quantizedQueryAabbMin, rayAabbMin, 0);
	quantizeWithClamp(quantizedQueryAabbMax, rayAabbMax, 1);

	while (curIndex < endNodeIndex)
	{
                                
#ifdef VISUALLY_ANALYZE_BVH
		                                                                        
		static int drawPatch = 0;
		                                          
		extern btIDebugDraw* debugDrawerPtr;
		if (curIndex == drawPatch)
		{
			btVector3 aabbMin, aabbMax;
			aabbMin = unQuantize(rootNode->m_quantizedAabbMin);
			aabbMax = unQuantize(rootNode->m_quantizedAabbMax);
			btVector3 color(1, 0, 0);
			debugDrawerPtr->drawAabb(aabbMin, aabbMax, color);
		}
#endif                        

		                         
		btAssert(walkIterations < subTreeSize);

		walkIterations++;
		                               
		                                                          
		btScalar param = 1.0;
		rayBoxOverlap = 0;
		boxBoxOverlap = testQuantizedAabbAgainstQuantizedAabb(quantizedQueryAabbMin, quantizedQueryAabbMax, rootNode->m_quantizedAabbMin, rootNode->m_quantizedAabbMax);
		isLeafNode = rootNode->isLeafNode();
		if (boxBoxOverlap)
		{
			btVector3 bounds[2];
			bounds[0] = unQuantize(rootNode->m_quantizedAabbMin);
			bounds[1] = unQuantize(rootNode->m_quantizedAabbMax);
			                          
			bounds[0] -= aabbMax;
			bounds[1] -= aabbMin;
			btVector3 normal;
#if 0
			bool ra2 = btRayAabb2 (raySource, rayDirection, sign, bounds, param, 0.0, lambda_max);
			bool ra = btRayAabb (raySource, rayTarget, bounds[0], bounds[1], param, normal);
			if (ra2 != ra)
			{
				printf("functions don't match\n");
			}
#endif
#ifdef RAYAABB2
			                                                                                                
			                                                
			                                                                      

			                           
			rayBoxOverlap = btRayAabb2(raySource, rayDirection, sign, bounds, param, 0.0f, lambda_max);

#else
			rayBoxOverlap = true;                                                                         
#endif
		}

		if (isLeafNode && rayBoxOverlap)
		{
			((MyNodeOverlapCallback*)nodeCallback)->processNode(rootNode->getPartId(), rootNode->getTriangleIndex());
		}

		                               
		if ((rayBoxOverlap != 0) || isLeafNode)
		{
			rootNode++;
			curIndex++;
		}
		else
		{
			escapeIndex = rootNode->getEscapeIndex();
			rootNode += escapeIndex;
			curIndex += escapeIndex;
		}
	}
}

                                                     
void btQuantizedBvh::walkStacklessQuantizedTreeCacheFriendly(btNodeOverlapCallback* nodeCallback, unsigned short int* quantizedQueryAabbMin, unsigned short int* quantizedQueryAabbMax) const
{
	btAssert(m_useQuantization);

	int i;

	for (i = 0; i < this->m_SubtreeHeaders.size(); i++)
	{
		const btBvhSubtreeInfo& subtree = m_SubtreeHeaders[i];

		                               
		unsigned overlap = testQuantizedAabbAgainstQuantizedAabb(quantizedQueryAabbMin, quantizedQueryAabbMax, subtree.m_quantizedAabbMin, subtree.m_quantizedAabbMax);
		if (overlap != 0)
		{
			walkStacklessQuantizedTree(nodeCallback, quantizedQueryAabbMin, quantizedQueryAabbMax,
									   subtree.m_rootNodeIndex,
									   subtree.m_rootNodeIndex + subtree.m_subtreeSize);
		}
	}
}

void btQuantizedBvh::walkStacklessQuantizedTree(btNodeOverlapCallback* nodeCallback, unsigned short int* quantizedQueryAabbMin, unsigned short int* quantizedQueryAabbMax, int startNodeIndex, int endNodeIndex) const {
	btAssert(m_useQuantization);

	int curIndex = startNodeIndex;
	int walkIterations = 0;
	int subTreeSize = endNodeIndex - startNodeIndex;
	(void)subTreeSize;

	const btQuantizedBvhNode* rootNode = &m_quantizedContiguousNodes[startNodeIndex];
	int escapeIndex;

	bool isLeafNode;
	                               
	unsigned aabbOverlap;

	while (curIndex < endNodeIndex) {
		                                
#ifdef VISUALLY_ANALYZE_BVH
		                                                                        
		static int drawPatch = 0;
		                                          
		extern btIDebugDraw* debugDrawerPtr;
		if (curIndex == drawPatch) {
			btVector3 aabbMin, aabbMax;
			aabbMin = unQuantize(rootNode->m_quantizedAabbMin);
			aabbMax = unQuantize(rootNode->m_quantizedAabbMax);
			btVector3 color(1, 0, 0);
			debugDrawerPtr->drawAabb(aabbMin, aabbMax, color);
		}
#endif                        

		                         
		btAssert(walkIterations < subTreeSize);

		walkIterations++;
		                               
		aabbOverlap = testQuantizedAabbAgainstQuantizedAabb(quantizedQueryAabbMin, quantizedQueryAabbMax, rootNode->m_quantizedAabbMin, rootNode->m_quantizedAabbMax);
		isLeafNode = rootNode->isLeafNode();

		if (isLeafNode && aabbOverlap) {
			((MyNodeOverlapCallback*)nodeCallback)->processNode(rootNode->getPartId(), rootNode->getTriangleIndex());
		}

		                               
		if ((aabbOverlap != 0) || isLeafNode) {
			rootNode++;
			curIndex++;
		} else {
			escapeIndex = rootNode->getEscapeIndex();
			rootNode += escapeIndex;
			curIndex += escapeIndex;
		}
	}
}

void btQuantizedBvh::reportRayOverlappingNodex(btNodeOverlapCallback* nodeCallback, const btVector3& raySource, const btVector3& rayTarget) const
{
	if (m_useQuantization) {
		walkStacklessQuantizedTreeAgainstRay(nodeCallback, raySource, rayTarget, btVector3(0, 0, 0), btVector3(0, 0, 0), 0, m_curNodeIndex);
	} else {
		walkStacklessTreeAgainstRayNoAABB(nodeCallback, raySource, rayTarget, 0, m_curNodeIndex);
	}
}

void btQuantizedBvh::reportBoxCastOverlappingNodex(btNodeOverlapCallback* nodeCallback, const btVector3& raySource, const btVector3& rayTarget, const btVector3& aabbMin, const btVector3& aabbMax) const
{
	                      

	if (m_useQuantization)
	{
		walkStacklessQuantizedTreeAgainstRay(nodeCallback, raySource, rayTarget, aabbMin, aabbMax, 0, m_curNodeIndex);
	}
	else
	{
		walkStacklessTreeAgainstRay(nodeCallback, raySource, rayTarget, aabbMin, aabbMax, 0, m_curNodeIndex);
	}
	  
  
                       
                                 
                                 
                             
                             
                      
                      
                                                             
  
   
}

void btQuantizedBvh::swapLeafNodes(int i, int splitIndex)
{
	if (m_useQuantization)
	{
		btQuantizedBvhNode tmp = m_quantizedLeafNodes[i];
		m_quantizedLeafNodes[i] = m_quantizedLeafNodes[splitIndex];
		m_quantizedLeafNodes[splitIndex] = tmp;
	}
	else
	{
		btOptimizedBvhNode tmp = m_leafNodes[i];
		m_leafNodes[i] = m_leafNodes[splitIndex];
		m_leafNodes[splitIndex] = tmp;
	}
}

void btQuantizedBvh::assignInternalNodeFromLeafNode(int internalNode, int leafNodeIndex)
{
	if (m_useQuantization)
	{
		m_quantizedContiguousNodes[internalNode] = m_quantizedLeafNodes[leafNodeIndex];
	}
	else
	{
		m_contiguousNodes[internalNode] = m_leafNodes[leafNodeIndex];
	}
}

              
#include <new>
#include "../CollisionShapes/btConcaveShape.h"

#if 0
             
static const unsigned BVH_ALIGNMENT = 16;
static const unsigned BVH_ALIGNMENT_MASK = BVH_ALIGNMENT-1;

static const unsigned BVH_ALIGNMENT_BLOCKS = 2;
#endif

void MyNodeOverlapCallback::processNode(int nodeSubPart, int nodeTriangleIndex) {
	m_numOverlap++;
	const unsigned char* vertexbase;
	int numverts;
	int stride;
	const unsigned char* indexbase;
	int indexstride;
	int numfaces;

	m_meshInterface->getLockedReadOnlyVertexIndexBase(
		&vertexbase,
		numverts,
		stride,
		&indexbase,
		indexstride,
		numfaces,
		nodeSubPart);

	unsigned int* gfxbase = (unsigned int*)(indexbase + nodeTriangleIndex * indexstride);

	const btVector3& meshScaling = m_meshInterface->getScaling();
	for (int j = 2; j >= 0; j--) {
		int graphicsindex = gfxbase[j];

#ifdef DEBUG_TRIANGLE_MESH
		printf("%d ,", graphicsindex);
#endif                       
		float* graphicsbase = (float*)(vertexbase + graphicsindex * stride);

		m_triangle[j] = btVector3(
			graphicsbase[0] * meshScaling.getX(),
			graphicsbase[1] * meshScaling.getY(),
			graphicsbase[2] * meshScaling.getZ());
#ifdef DEBUG_TRIANGLE_MESH
		printf("triangle vertices:%f,%f,%f\n", triangle[j].x(), triangle[j].y(), triangle[j].z());
#endif                       
	}

	m_callback->processTriangle(m_triangle, nodeSubPart, nodeTriangleIndex);
	m_meshInterface->unLockReadOnlyVertexBase(nodeSubPart);
}