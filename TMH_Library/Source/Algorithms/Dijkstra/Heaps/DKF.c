/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKF.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Heap -- Fibonacci
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Heaps/DKF.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
																destroyTMHGraphInstance(),
																destroyTMHConfigurationInstance(),*/

#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibHeap.h"/* TMHFibHeap,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 createSingleTMHFibHeapInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 removeMinimumTMHFibHeap(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 insertSingleTMHFibHeapInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 decreaseKeyTMHFibHeap(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 createTMHFibNodeInstance()*/
#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"		/* reinitializeTMHGraph() */
#include "../../../../Headers/Helpers/TMHAllocHelper.h"			/* memMalloc(), memFree() */

#include "../../../../Headers/Helpers/TMHDictionary.h"			/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKF */
#include "../../../../Headers/TMHLogger.h"						/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"				/* debug_DKF_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKF";


/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */



/*
 * Definitions
 *
 */

TMH_DKF* createTMHDKFInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKF* newInstance = memMalloc(1,sizeof(TMH_DKF));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKFInstance ( TMH_DKF* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runDKF( TMH_DKF* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKF_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKF_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[DKF],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runDKF_SingleSource(graph,source);
	}
}

void runDKF_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHFibHeap* heap;

	reinitializeTMHGraph(graph,sourceNode);
	heap = createSingleTMHFibHeapInstance(
			createTMHFibNodeInstance(sourceNode),
			&numberOfNodes);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKF_initQueueWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( (currentNode = removeMinimumTMHFibHeap(heap)) != NULL ) {
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_nextQueueLoop);
		}

		if (isTraceLogEnabled()) {
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
					if ( toNode->toUpperStruct == NULL ) {
						trace(MODULE_NAME,trace_DKF_addMode,toNode->nodeID,newDistance);
					} else {
						trace(MODULE_NAME,trace_DKF_decreaseKey,toNode->nodeID,toNode->distanceLabel,newDistance);
					}
				}

				toNode->distanceLabel = newDistance;
				toNode->predecessor = currentNode;

				if ( toNode->toUpperStruct == NULL ) {
					insertSingleTMHFibHeapInstance(heap,
							createTMHFibNodeInstance(toNode));
				} else {
					decreaseKeyTMHFibHeap(heap,toNode->toUpperStruct,&newDistance);
				}
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}

	info(MODULE_NAME,info_TMHAlgorithmHelper_destroyFibonacci);
	destroyTMHFibHeapInstance(heap);
}
