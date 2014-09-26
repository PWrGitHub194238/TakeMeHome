/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKB.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Basic Implementation
 * To znaczy z nC+1 kube�kami
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKB.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKB_H_
#define DKB_H_

/*
 * Includes
 *
 */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */
#include "../../../Helpers/TMHAllocHelper.h"	/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"	/* TMHNodeDLListWrapper */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKB {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKB;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKB* createTMHDKBInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig );

void destroyTMHDKBInstance ( TMH_DKB* const instance );

void runDKB( TMH_DKB* const instance );

void runDKB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

inline TMHNodeDLListWrapper** createBucketsDKB( TMHNodeData maxDistance, TMHNode* const sourceNode) __attribute__((always_inline));
/*
 * Inline definitions
 *
 */

/**
 * tworzy buckety i wrzuca source node do kube�ka[0], gdzie indeksy to dystans
 */
inline TMHNodeDLListWrapper** createBucketsDKB( TMHNodeData maxDistance, TMHNode* const sourceNode) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(maxDistance,sizeof(TMHNodeDLList*));
	for ( maxDistance--; maxDistance > 0; maxDistance-- ) {
		bucketArray[maxDistance] = createTMHNodeDLListInstance();
	}
	bucketArray[maxDistance] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(bucketArray[maxDistance]->head,sourceNode);

	return bucketArray;
}

#endif /* DKB_H_ */
