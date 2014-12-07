/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKXB.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Overflow Bag
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKXB.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKXB_H_
#define DKXB_H_

/*
 * Includes
 *
 */

#include "../../../TMHLogger.h"


#include <math.h>										/* log */

#include "../../../Structures/Buckets/TMHBucketRange.h"	/* TMHBucketRange */
#include "../../../Structures/TMHGraph.h"				/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"							/* TMHConfig, TMHNodeIdx, TMHNodeData */
#include "../../../Helpers/TMHAllocHelper.h"			/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"			/* TMHNodeDLListWrapper */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKXB {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKXB;

/*
 * Externs
 *
 */

/*
 * Declarations
 *
 */


TMH_DKXB* createTMHDKXBInstance( TMHGraph* const graphData, TMHConfig* const configuration );

void destroyTMHDKXBInstance ( TMH_DKXB* const instance, bool withConfig );

void runDKXB( TMH_DKXB* const instance );

void runDKXB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKXB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

inline TMHNodeIdx* initBucketsSizeDKXB( TMHArcCost numberOfBuckets ) __attribute__((always_inline));

inline TMHBucketRange** initBucketsRangeDKXB( TMHArcCost numberOfBuckets, const TMHNodeIdx* const bucketsSizeArray )  __attribute__((always_inline));

inline TMHNodeDLListWrapper** createBucketsDKXB( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) __attribute__((always_inline));

inline TMHNodeIdx* initNodeBucketMapDKXB( TMHNode** nodeArray, TMHNodeIdx numberOfNodes, const TMHArcCost numberOfBuckets )  __attribute__((always_inline));

/*
 * Inline definitions
 *
 */

/* [2^(k-1);2^(k)-1] k = {1..}
 *  [0;0][1;1][2;3][4;7][8;15]...*/
inline TMHNodeIdx* initBucketsSizeDKXB( TMHArcCost numberOfBuckets ) {
	TMHNodeIdx* bucketsSizeArray = memMalloc(numberOfBuckets,sizeof(TMHNodeIdx*));
	TMHArcCost i;
	bucketsSizeArray[0] = 1;
	bucketsSizeArray[1] = 1;
	for ( i = 2; i < numberOfBuckets; i += 1 ) {
		bucketsSizeArray[i] = bucketsSizeArray[i-1]*2;
	}
	return bucketsSizeArray;
}

inline TMHBucketRange** initBucketsRangeDKXB( TMHArcCost numberOfBuckets, const TMHNodeIdx* const bucketsSizeArray ) {
	TMHBucketRange** bucketsRangeArray = memMalloc(numberOfBuckets,sizeof(TMHBucketRange*));
	TMHArcCost i;
	bucketsRangeArray[0] = createBucketRangeInstance(0,1);

	for ( i = 1; i < numberOfBuckets; i += 1 ) {
		bucketsRangeArray[i] = createBucketRangeInstance(bucketsRangeArray[i-1]->end + 1,bucketsSizeArray[i]);
	}

	return bucketsRangeArray;
}

inline TMHNodeDLListWrapper** createBucketsDKXB( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(numberOfBuckets,sizeof(TMHNodeDLListWrapper*));
	for ( numberOfBuckets--; numberOfBuckets > 0; numberOfBuckets-- ) {
		bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	}
	bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(bucketArray[numberOfBuckets]->head,sourceNode);

	return bucketArray;
}

/* [2^(k-1);2^(k)-1] k = {1..}
 *  [0;0][1;1][2;3][4;7][8;15]...
 *  log2(i)*/
inline TMHNodeIdx* initNodeBucketMapDKXB( TMHNode** nodeArray, TMHNodeIdx numberOfNodes, const TMHArcCost numberOfBuckets ) {
	TMHNodeIdx* nodeBucketIDMap = memMalloc(numberOfNodes+1,sizeof(TMHNodeIdx*));
	TMHNodeData distanceLabel;
	for ( ; numberOfNodes > 0; numberOfNodes-- ) {
		distanceLabel = nodeArray[numberOfNodes]->distanceLabel;
		if ( distanceLabel == distanceLabelInfinity ) {
			nodeBucketIDMap[numberOfNodes] = numberOfBuckets - 1;
		} else {
			nodeBucketIDMap[numberOfNodes] = (TMHNodeIdx) ((distanceLabel==0) ? 0 : floor(log2(distanceLabel)) + 1);
		}
	}
	return nodeBucketIDMap;
}

#endif /* DKXB_H_ */
