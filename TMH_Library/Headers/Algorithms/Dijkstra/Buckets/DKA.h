/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKA.h
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
 * DKA.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKA_H_
#define DKA_H_

/*
 * Includes
 *
 */

#include <stdio.h>								/* stdin */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx, TMHNodeData */
#include "../../../Helpers/TMHAllocHelper.h"	/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"	/**/

/*
 * Typedefs
 *
 */

typedef struct TMH_DKA {
	TMHGraph* graphData;
	TMHConfig* configuration;
	TMHNodeData bucketsRangeMod;
} TMH_DKA;

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
TMH_DKA* createTMHDKAInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDKAInstance ( TMH_DKA* const instance, bool withConfig );

void runDKA( TMH_DKA* const instance );

void runDKA_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const bucketsRangeMod );

void runDKA_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData bucketsRangeMod );

inline TMHNodeDLListWrapper** createBucketsDKA( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) __attribute__((always_inline));

/*
 * Inline definitions
 *
 */

/**
 * tworzy buckety i wrzuca source node do kube�ka[0], gdzie indeksy to dystans. Tworzy te� overflow baga.
 */
inline TMHNodeDLListWrapper** createBucketsDKA( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(numberOfBuckets,sizeof(TMHNodeDLListWrapper*));
	for ( numberOfBuckets--; numberOfBuckets > 0; numberOfBuckets-- ) {
		bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	}
	bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(bucketArray[numberOfBuckets]->head,sourceNode);

	return bucketArray;
}


#endif /* DKA_H_ */
