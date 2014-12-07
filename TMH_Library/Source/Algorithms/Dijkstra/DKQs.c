/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKQs.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Naive Implementation
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../Headers/Algorithms/Dijkstra/DKQs.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
														destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHConfigurationInstance(),*/
#include "../../../Headers/Structures/TMHNodeSLList.h"	/* TMHNodeSLListWrapper,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 createTMHNodeSLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 pushTMHNodeSLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 popMinTMHNodeSLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 destroyTMHNodeSLListInstance()*/
#include "../../../Headers/Helpers/TMHAlgorithmHelper.h"/* reinitializeTMHGraph() */
#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */

#include "../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKQs */
#include "../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../Headers/Helpers/TMHErrors.h"			/* debug_DKQ_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKQs";


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

TMH_DKQS* createTMHDKQSInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKQS* newInstance = memMalloc(1,sizeof(TMH_DKQS));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKQSInstance ( TMH_DKQS* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKQS( TMH_DKQS* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKQS_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKQS_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKQs],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKQS_SingleSource(graph,source);
	}
}

void runDKQS_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHNodeSLListWrapper* list = createTMHNodeSLListInstance();

	reinitializeTMHGraph(graph,sourceNode);
	pushTMHNodeSLList(list->head,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKQ_initSLListWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( (currentNode = popMinTMHNodeSLList(list)) != NULL ) {
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
						if ( toNode->predecessor == currentNode ) {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,currentNode->nodeID,(toNode->distanceLabel-arc->distance),arc->distance,toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
						} else {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,toNode->predecessor->nodeID,toNode->predecessor->distanceLabel,(toNode->distanceLabel-toNode->predecessor->distanceLabel),toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
						}
					}
				}
				toNode->distanceLabel = newDistance;
				toNode->predecessor = currentNode;

				if ( toNode->toUpperStruct == NULL ) {
					pushTMHNodeSLList(list->head,toNode);
				}
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyStack);
	}
	destroyTMHNodeSLListInstance(list,false);
}

