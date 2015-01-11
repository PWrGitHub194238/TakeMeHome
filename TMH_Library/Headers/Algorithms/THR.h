/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file THR.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Threshold Algorithm
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * THR.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef THR_H_
#define THR_H_

/*
 * Includes
 *
 */

#include <stddef.h>							/* NULL */

#include "../Structures/TMHGraph.h"			/* TMHGraph, TMHNode */
#include "../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMH_THR {
	TMHGraph* graphData;
	TMHConfig* configuration;
	TMHNodeData thresholdParam;
	TMHNodeData threshold;
} TMH_THR;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_THR* createTMHTHRInstance( TMHGraph* const graphData, TMHConfig* configuration );

void destroyTMHTHRInstance( TMH_THR* const instance, bool withConfig );

void runTHR( TMH_THR* const instance );

void runTHR_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData threshold );

void runTHR_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, TMHNodeData threshold  );

inline TMHNodeData computeThreshold( const TMHGraph* const graphData, const TMHNodeData thresholdParam ) __attribute__((always_inline));
/*
 * Inline definitions
 *
 */

inline TMHNodeData computeThreshold( const TMHGraph* const graphData, const TMHNodeData thresholdParam ) {
	TMHNodeIdx numberOfNodes = graphData->numberOfNodes;
	TMHNode* currentNode = NULL;
	TMHArcList* adjacencyList = NULL;
	TMHNodeIdx i;
	TMHNodeData averageArcCost = 0;
	double minDense = thresholdParam;
	double dense;

	for ( i = 1; i <= numberOfNodes; i++ ) {					/* dla takiej TMHGraph trzeba przeglądnąć wszystkie nody*/
		currentNode = graphData->nodeArray[i];
		adjacencyList = currentNode->successors;
		while ( adjacencyList != NULL ) {
			averageArcCost += adjacencyList->arc->distance;
			adjacencyList = adjacencyList->nextElement;
		}
	}
	averageArcCost = averageArcCost / graphData->numberOfArcs;

	dense = (graphData->numberOfArcs*1.0) / graphData->numberOfNodes;

	if ( dense < minDense ) {
		dense = minDense;
	}
	return averageArcCost * (TMHNodeData) (thresholdParam / dense);
}

#endif /* THR_H_ */
