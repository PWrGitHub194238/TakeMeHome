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
 * Dijkstra's Heap -- Fibonacci basic impl
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Heaps/DKFb.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
																destroyTMHGraphInstance(),
																destroyTMHConfigurationInstance(),*/
#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibHeapBasic.h"
																/* TMHFibHeap,
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
#include "../../../../Headers/Helpers/TMHErrors.h"				/* debug_DKF_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKFb";


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

TMH_DKFB* createTMHDKFBInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKFB* newInstance = memMalloc(1,sizeof(TMH_DKFB));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKFBInstance ( TMH_DKFB* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKFB( TMH_DKFB* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKFB_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKFB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKF],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKFB_SingleSource(graph,source);
	}
}

void runDKFB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHFibHeap* heap;


	long long int k = 0;

	printf("\nNODE: %u", numberOfNodes);



	reinitializeTMHGraph(graph,sourceNode);

	heap = createSingleTMHFibBHeapInstance(
			createTMHFibNodeInstance(sourceNode),
			numberOfNodes);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKF_initQueueWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( (currentNode = extractMinTMHFibBHeap(heap)) != NULL ) {
		k+=1;
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
						if ( toNode->predecessor == currentNode ) {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,currentNode->nodeID,(toNode->distanceLabel-arc->distance),arc->distance,toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
						} else {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,toNode->predecessor->nodeID,toNode->predecessor->distanceLabel,(toNode->distanceLabel-toNode->predecessor->distanceLabel),toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
						}
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
					insertSingleTMHFibBHeap(heap,
							createTMHFibNodeInstance(toNode));
				} else {
					decreaseKeyTMHFibBHeap(heap,(TMHFibNode*)toNode->toUpperStruct,newDistance);
				}
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyFibonacci);
	}
	destroyTMHFibBHeapInstance(heap);


	printf("\nNODE: %llu\n", k);

}
