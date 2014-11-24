/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DLL.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Dial
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DLL.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DDL_H_
#define DDL_H_

/*
 * Includes
 *
 */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx, TMHNodeData */
#include "../../../Helpers/TMHAllocHelper.h"	/* memMalloc() */
#include "../../../Structures/TMHNodeDLList.h"	/**/

/*
 * Typedefs
 *
 */

typedef struct TMH_DDL {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DDL;

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
TMH_DDL* createTMHDDLInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDDLInstance ( TMH_DDL* const instance, bool withConfig );

void runDDL( TMH_DDL* const instance );

void runDDL_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDDL_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

inline TMHNodeDLListWrapper** createBucketsDDL( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) __attribute__((always_inline));

/*
 * Inline definitions
 *
 */

/**
 * tworzy buckety i wrzuca source node do kube�ka[0], gdzie indeksy to dystans. Tworzy te� overflow baga.
 */
inline TMHNodeDLListWrapper** createBucketsDDL( TMHArcCost numberOfBuckets, TMHNode* const sourceNode ) {
	TMHNodeDLListWrapper** bucketArray = memMalloc(numberOfBuckets,sizeof(TMHNodeDLListWrapper*));
	for ( numberOfBuckets--; numberOfBuckets > 0; numberOfBuckets-- ) {
		bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	}
	bucketArray[numberOfBuckets] = createTMHNodeDLListInstance();
	pushTMHNodeDLList(bucketArray[numberOfBuckets]->head,sourceNode);

	return bucketArray;
}


#endif /* DDL_H_ */
