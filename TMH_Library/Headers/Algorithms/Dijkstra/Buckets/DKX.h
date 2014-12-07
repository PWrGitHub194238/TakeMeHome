/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKX.h
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
 * DKX.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKX_H_
#define DKX_H_

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

typedef struct TMH_DKX {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKX;

/*
 * Externs
 *
 */

/*
 * Declarations
 *
 */


TMH_DKX* createTMHDKXInstance( TMHGraph* const graphData, TMHConfig* const configuration );

void destroyTMHDKXInstance ( TMH_DKX* const instance, bool withConfig );

void runDKX( TMH_DKX* const instance );

void runDKX_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKX_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

inline TMHNodeIdx* initBucketsSizeDKX( TMHArcCost numberOfBuckets ) __attribute__((always_inline));

inline TMHBucketRange** initBucketsRangeDKX( TMHArcCost numberOfBuckets, const TMHNodeIdx* const bucketsSizeArray )  __attribute__((always_inline));

//inline TMHBucketRange** initBucketsRangeDKX( TMHArcCost numberOfBuckets ) __attribute__((always_inline));

inline TMHNodeDLListWrapper** createBucketsDKX( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) __attribute__((always_inline));

inline TMHNodeIdx* initNodeBucketMapDKX( TMHNode** nodeArray, TMHNodeIdx numberOfNodes, const TMHArcCost numberOfBuckets )  __attribute__((always_inline));

/*
 * Inline definitions
 *
 */

/* [2^(k-1);2^(k)-1] k = {1..}
 *  [0;0][1;1][2;3][4;7][8;15]...*/
inline TMHNodeIdx* initBucketsSizeDKX( TMHArcCost numberOfBuckets ) {
	TMHNodeIdx* bucketsSizeArray = memMalloc(numberOfBuckets,sizeof(TMHNodeIdx*));
	TMHArcCost i;
	bucketsSizeArray[0] = 1;
	bucketsSizeArray[1] = 1;
	for ( i = 2; i < numberOfBuckets; i += 1 ) {
		bucketsSizeArray[i] = bucketsSizeArray[i-1]*2;
	}
	return bucketsSizeArray;
}

inline TMHBucketRange** initBucketsRangeDKX( TMHArcCost numberOfBuckets, const TMHNodeIdx* const bucketsSizeArray ) {
	TMHBucketRange** bucketsRangeArray = memMalloc(numberOfBuckets+1,sizeof(TMHBucketRange*));
	TMHArcCost i;
	bucketsRangeArray[0] = createBucketRangeInstance(0,1);

	for ( i = 1; i < numberOfBuckets; i += 1 ) {
		bucketsRangeArray[i] = createBucketRangeInstance(bucketsRangeArray[i-1]->end + 1,bucketsSizeArray[i]);
	}

	bucketsRangeArray[i] = createBucketRangeInstance(bucketsRangeArray[i-1]->end + 1,bucketsRangeArray[i-1]->end + 1);	//overflow

	return bucketsRangeArray;
}

/*inline TMHBucketRange** initBucketsRangeDKX( TMHArcCost numberOfBuckets ) {
	TMHBucketRange** bucketsRangeArray = memMalloc(numberOfBuckets,sizeof(TMHBucketRange*));
	TMHNodeData currentBound = pow(2,--numberOfBuckets);
	for ( numberOfBuckets; numberOfBuckets > 0; numberOfBuckets-- ) {
		bucketsRangeArray[numberOfBuckets]->end = currentBound - 1;
		currentBound >>= 1;
		bucketsRangeArray[numberOfBuckets]->begin = currentBound;
	}
	bucketsRangeArray[numberOfBuckets]->begin = 0;
	bucketsRangeArray[numberOfBuckets]->end = 0;

	return bucketsRangeArray;
}
*/

/**
 * tworzy buckety i wrzuca source node do kube�ka[0], gdzie indeksy to dystans. Tworzy te� overflow baga.
 */
inline TMHNodeDLListWrapper** createBucketsDKX( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(numberOfBuckets+1,sizeof(TMHNodeDLListWrapper*));
	bucketArray[numberOfBuckets] = createTMHNodeDLListInstance(); // overflow
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
inline TMHNodeIdx* initNodeBucketMapDKX( TMHNode** nodeArray, TMHNodeIdx numberOfNodes, const TMHArcCost numberOfBuckets ) {
	TMHNodeIdx* nodeBucketIDMap = memMalloc(numberOfNodes+1,sizeof(TMHNodeIdx*));
	TMHNodeData distanceLabel;
	for ( ; numberOfNodes > 0; numberOfNodes-- ) {
		distanceLabel = nodeArray[numberOfNodes]->distanceLabel;
		if ( distanceLabel == distanceLabelInfinity ) {
			nodeBucketIDMap[numberOfNodes] = numberOfBuckets;	// w overflow
		} else {
			nodeBucketIDMap[numberOfNodes] = (TMHNodeIdx) ((distanceLabel==0) ? 0 : floor(log2(distanceLabel)) + 1);
		}
	}
	return nodeBucketIDMap;
}

#endif /* DKX_H_ */
