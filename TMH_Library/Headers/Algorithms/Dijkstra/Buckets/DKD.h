/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKD.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Double
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKD.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKD_H_
#define DKD_H_

/*
 * Includes
 *
 */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx, TMHNodeData */
#include "../../../Helpers/TMHAllocHelper.h"	/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"	/* TMHNodeDLListWrapper */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKD {
	TMHGraph* graphData;
	TMHConfig* configuration;
	TMHNodeData bucketsRangeMod;
} TMH_DKD;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKD* createTMHDKDInstance( TMHGraph* const graphData, TMHConfig* const configuration );

void destroyTMHDKDInstance ( TMH_DKD* const instance, bool withConfig );

void runDKD( TMH_DKD* const instance );

void runDKD_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const bucketsRangeMod );

void runDKD_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData bucketsRangeMod );

inline TMHNodeDLListWrapper** createHighLevelBucketsDKD( TMHNodeData numOfHLBuckets, TMHNode* const sourceNode ) __attribute__((always_inline));
inline TMHNodeDLListWrapper** createLowLevelBucketsDKD( TMHNodeData numOfLLBuckets ) __attribute__((always_inline));

	/*
 * Inline definitions
 *
 */

inline TMHNodeDLListWrapper** createHighLevelBucketsDKD( TMHNodeData numOfHLBuckets, TMHNode* const sourceNode ) {
	TMHNodeDLListWrapper** hight_level_bucketArray = memMalloc(numOfHLBuckets,sizeof(TMHNodeDLList*));

	for ( numOfHLBuckets--; numOfHLBuckets > 0; numOfHLBuckets-- ) {
		hight_level_bucketArray[numOfHLBuckets] = createTMHNodeDLListInstance();
	}
	hight_level_bucketArray[numOfHLBuckets] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(hight_level_bucketArray[numOfHLBuckets]->head,sourceNode);

	return hight_level_bucketArray;
}

inline TMHNodeDLListWrapper** createLowLevelBucketsDKD( TMHNodeData numOfLLBuckets ) {
	TMHNodeDLListWrapper** low_level_bucketArray = memMalloc(numOfLLBuckets,sizeof(TMHNodeDLList*));

	for ( numOfLLBuckets--; numOfLLBuckets > 0; numOfLLBuckets-- ) {
		low_level_bucketArray[numOfLLBuckets] = createTMHNodeDLListInstance();
	}
	low_level_bucketArray[numOfLLBuckets] = createTMHNodeDLListInstance();

	return low_level_bucketArray;
}

#endif /* DKD_H_ */
