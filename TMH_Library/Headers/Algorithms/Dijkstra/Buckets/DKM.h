/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKM.h
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
 * DKM.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKM_H_
#define DKM_H_

/*
 * Includes
 *
 */

#include <stdio.h>								/* stdin */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */
#include "../../../Helpers/TMHAllocHelper.h"	/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"	/* TMHNodeDLListWrapper */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKM {
	TMHGraph* graphData;
	TMHConfig* configuration;
	TMHNodeData numberOfMainBuckets;
} TMH_DKM;

/*
 * Externs
 *
 */


/*
 * Declarations
 *
 */

/**
 * allowInterrupt - gdy true to algorytm zapyta o parametr 'a'. Jesli nie to zostanie wybrana stala, wybrana doswiadczalnie.
 */
TMH_DKM* createTMHDKMInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig, bool allowInterrupt );
void destroyTMHDKMInstance ( TMH_DKM* const instance );

void runDKM( TMH_DKM* const instance );

void runDKM_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const numberOfMainBuckets );

void runDKM_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData numberOfBuckets );

inline TMHNodeDLListWrapper** createBucketsDKM( TMHNodeData numberOfMainBuckets, TMHNode* const sourceNode)  __attribute__((always_inline));
/*
 * Inline definitions
 *
 */

/**
 * tworzy buckety i wrzuca source node do kube�ka[0], gdzie indeksy to dystans. Tworzy te� overflow baga.
 */
inline TMHNodeDLListWrapper** createBucketsDKM( TMHNodeData numberOfMainBuckets, TMHNode* const sourceNode) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(numberOfMainBuckets+1,sizeof(TMHNodeDLList*));
	bucketArray[numberOfMainBuckets] = createTMHNodeDLListInstance();	//overflow bag
	for ( numberOfMainBuckets--; numberOfMainBuckets > 0; numberOfMainBuckets-- ) {
		bucketArray[numberOfMainBuckets] = createTMHNodeDLListInstance();
	}
	bucketArray[numberOfMainBuckets] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(bucketArray[numberOfMainBuckets]->head,sourceNode);

	return bucketArray;
}

#endif /* DKM_H_ */
