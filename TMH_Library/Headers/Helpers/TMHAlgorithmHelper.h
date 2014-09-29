/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHAlgorithmHelper.h
 * @author tomasz
 * @date 6 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHAlgorithmHelper.h
 *
 *  Created on: 6 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHALGORITHMHELPER_H_
#define TMHALGORITHMHELPER_H_

/*
 * Includes
 *
 */

#include <stdbool.h>										/* bool */

#include "../../Headers/Structures/TMHGraph.h"				/* TMHGraph, TMHNode, TMHNodeData */

#include "../../Headers/Structures/TMHNodeDLList.h"			/* TMHNodeDLListWrapper */

#include "../../Headers/Helpers/TMHAllocHelper.h"			/* NULL */

/*
 * Typedefs
 *
 */



/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

inline void reinitializeTMHGraph( TMHGraph* const graph, TMHNode* const sourceNode ) __attribute__((always_inline));
inline bool checkForNegativeCirclesAfterRalax( TMHGraph* graph ) __attribute__((always_inline));
inline void cleanUpBuckets ( TMHNodeDLListWrapper** const bucketsArray, const TMHNodeData bucketsArraySize) __attribute__((always_inline));

/*
 * Inline definitions
 *
 */

inline void reinitializeTMHGraph( TMHGraph* const graph, TMHNode* const sourceNode ) {
	TMHNodeIdx n = graph->numberOfNodes;
	for ( ; n > 0; n-- ) {
		graph->nodeArray[n]->distanceLabel = distanceLabelInfinity;
		graph->nodeArray[n]->predecessor = NULL;
	}
	sourceNode->distanceLabel = 0;
}

inline bool checkForNegativeCirclesAfterRalax( TMHGraph* graph ) {
	TMHNode* node = NULL;
	TMHArcList* adjacencyList = NULL;
	TMHArc* arc = NULL;
	TMHNodeIdx i = graph->numberOfNodes;
	for ( i--; i > 0; i-- ) {
		node = graph->nodeArray[i];
		adjacencyList = node->successors;
		while ( adjacencyList != NULL ) {
			arc = adjacencyList->arc;
			if ( arc->successor->distanceLabel > node->distanceLabel + arc->distance ) {
				return false;
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}
	return true;
}

inline void cleanUpBuckets ( TMHNodeDLListWrapper** const bucketsArray, const TMHNodeData bucketsArraySize ) {
	TMHNodeData i;
	for ( i = 0; i < bucketsArraySize; i += 1 ) {
		destroyTMHNodeDLListInstance(bucketsArray[i],false);
	}
	memFree(bucketsArray);
}

#endif /* TMHALGORITHMHELPER_H_ */
