/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKR.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Heap -- R--Heap
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include <math.h>												/* log(), pow() */

#include "../../../../Headers/Algorithms/Dijkstra/Heaps/DKR.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
																destroyTMHGraphInstance(),
																destroyTMHConfigurationInstance(),*/

#include "../../../../Headers/Structures/Heaps/D-Heap/TMHDHeap.h"/**/

#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"		/* reinitializeTMHGraph() */
#include "../../../../Headers/Helpers/TMHAllocHelper.h"			/* memMalloc(), memFree() */

#include "../../../../Headers/Helpers/TMHDictionary.h"			/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKR */
#include "../../../../Headers/TMHLogger.h"						/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"				/* debug_DKR_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKR";
static const char* ASK_FOR_WIDTH_OF_HEAP = "Interrupt!\nHeap-based implementation of "
		"Dijkstra's algorithm with D-Heap requires additional parameter.\nLeaving input empty "
		"will set this parameter to it's optimal value (in DKR implementation this parameter"
		"determinates how many children each node in heap structure will have) "
		"which can lead to either greater memory or time consumption. "
		"See documentation for implementation details.).";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHNodeData getParameterOrDefaultDKR( const TMHNodeIdx numberOfArcs, const TMHNodeIdx numberOfNodes );
static TMHNodeData findBestParameter( TMHNodeIdx const numberOfArcs, TMHNodeIdx const numberOfNodes );

/*
 * Definitions
 *
 */

TMH_DKR* createTMHDKRInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKR* newInstance = memMalloc(1,sizeof(TMH_DKR));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( configuration->allowInterrupt ) {
		printf("%s\n",ASK_FOR_WIDTH_OF_HEAP);
		newInstance->dHeapParameter = getParameterOrDefaultDKR(graphData->numberOfArcs,graphData->numberOfNodes);
	} else if ( configuration->defaultParameter == NULL ) {
		newInstance->dHeapParameter = findBestParameter(graphData->numberOfArcs,graphData->numberOfNodes);
	} else {
		newInstance->dHeapParameter = *(configuration->defaultParameter);
	}
	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_DKR_parametrReaded,newInstance->dHeapParameter);
	}

	return newInstance;
}

void destroyTMHDKRInstance ( TMH_DKR* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKR( TMH_DKR* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKR_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources,instance->dHeapParameter);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKR_SingleSourceWrapper( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeIdx dHeapParameter ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		printf("Source node: %d / %d\n",i+1,sourceNodeArraySize);

		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKR],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKR_SingleSource(graph,source,dHeapParameter);
	}
}

void runDKR_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeIdx dHeapParameter ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHDHeap* heap = createTMHDHeapInstance(graph->nodeArray,graph->numberOfNodes,dHeapParameter);

	reinitializeTMHGraph(graph,sourceNode);
	insertTMHDHeap(heap,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKR_initHeapWithSource,sourceNode->nodeID,sourceNode->distanceLabel,dHeapParameter);
	}

	while( (currentNode = removeMinimumTMHDHeap(heap)) != NULL ) {
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_nextQueueLoop);
			if ( currentNode->distanceLabel == distanceLabelInfinity ) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_getInfinityFromQueue,currentNode->nodeID);
			} else {
				if ( currentNode->predecessor == NULL ) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElementNoParent,currentNode->nodeID,currentNode->distanceLabel);
				} else {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElement,currentNode->nodeID,currentNode->distanceLabel,currentNode->predecessor->nodeID);
				}
			}
		}
		if ( currentNode->distanceLabel == distanceLabelInfinity ) {
			break;
		}
		adjacencyList = currentNode->successors;

		if( isTraceLogEnabled() &&  adjacencyList == NULL ) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_noOutgoingEdges,currentNode->nodeID);
		}

		while ( adjacencyList != NULL ) {
			arc = adjacencyList->arc;
			toNode = arc->successor;
			newDistance = currentNode->distanceLabel + arc->distance;

			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_checkRelax,currentNode->nodeID,arc->distance,toNode->nodeID,toNode->distanceLabel,newDistance);
			}
			if ( toNode->distanceLabel > newDistance ) {
				if (isTraceLogEnabled()) {
					if ( toNode->predecessor == NULL ) {
						trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelaxPredNULL,toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
					} else {
						trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,toNode->predecessor->nodeID,toNode->predecessor->distanceLabel,(toNode->distanceLabel-toNode->predecessor->distanceLabel),toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
					}
					if ( heap->heapIDArray[toNode->nodeID] > heap->heapSize ) {
						trace(MODULE_NAME,trace_DKR_addMode,toNode->nodeID,newDistance);
					} else {
						trace(MODULE_NAME,trace_DKR_decreaseKey,toNode->nodeID,toNode->distanceLabel,newDistance);
					}
				}
				toNode->distanceLabel = newDistance;
				toNode->predecessor = currentNode;

				if ( heap->heapIDArray[toNode->nodeID] > heap->heapSize ) {	// jeśli został wyrzucony poza kopiec poprzez inny element, a sam "po prostu tam był" i musiał dostać identyfikator. Jeśli tak było to traktuj go jako nowy węzeł
					insertTMHDHeap(heap,toNode);
				} else {
					decreaseKeyTMHDHeap(heap,heap->heapIDArray[toNode->nodeID],newDistance);
				}
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyDHeap);
	}
	destroyTMHDHeapInstance(heap);
}

static TMHNodeData getParameterOrDefaultDKR( const TMHNodeIdx numberOfArcs, const TMHNodeIdx numberOfNodes ) {
	int j=0;
	int c;
	while ( (c = getc(stdin)) != '\n' ) {
		j = ((j<<3) + (j<<1)) + (c - 48);	/*10 = 3*2 + 2 */
	}
	if ( j == 0 ) {
		return findBestParameter(numberOfArcs,numberOfNodes);
	} else {
		return (TMHNodeData) j;
	}
}

static TMHNodeData findBestParameter( TMHNodeIdx const numberOfArcs, TMHNodeIdx const numberOfNodes ) {
	TMHNodeData r = numberOfArcs / numberOfNodes;
	if (r < 2) {
		r = 2;
	}
	return r;
}
