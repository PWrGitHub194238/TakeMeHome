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
 * ze stosem
 *
 * @see http://www.Double.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../Headers/Algorithms/THR.h"				/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
														destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHConfigurationInstance(),*/

#include "../../Headers/Structures/TMHNodeDLList.h"		/* TMHNodeDLList, popTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	pushLastTMHNodeDLList()
 	 	 	 	 	 	 	 	 	 	 	 	 	 	repinTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHNodeDLListInstance() */

#include "../../Headers/Helpers/TMHAlgorithmHelper.h"	/* reinitializeTMHGraph() */
#include "../../Headers/Helpers/TMHAllocHelper.h"		/* memMalloc(), memFree() */

#include "../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 THR */
#include "../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../Headers/Helpers/TMHErrors.h"			/* debug_THR_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "THR";
static const TMHNodeData DEFAULT_PARAM = 5;
static const char* ASK_FOR_PARAM = "Interrupt!\nThreshold Algorithm requires additional parameter.\nLeaving input empty "
		"will set this parameter automatically (in THR implementation this parameter "
		"has an influence on final threshold level which can lead to different time consumption. "
		"See documentation for implementation details.).";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHNodeData getParameterOrDefaultTHR( const TMHNodeData constant );
static TMHNodeDLListWrapper* relocateAndUpdateTHR( TMHNodeDLListWrapper* const mainQueue, TMHNodeDLListWrapper* const outQueue, TMHNodeData* const threshold );

/*
 * Definitions
 *
 */

TMH_THR* createTMHTHRInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig, bool allowInterrupt ) {
	TMH_THR* newInstance = memMalloc(1,sizeof(TMH_THR));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( checkConfig ) {
		checkTMHConfig(configuration);
	}

	if ( allowInterrupt ) {
		printf("%s\n",ASK_FOR_PARAM);
		newInstance->thresholdParam = getParameterOrDefaultTHR(DEFAULT_PARAM);
		newInstance->threshold = computeThreshold(graphData,&(newInstance->thresholdParam));
	} else {
		newInstance->threshold = computeThreshold(graphData,&(DEFAULT_PARAM));
	}
	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_THR_parametrReaded,newInstance->thresholdParam,newInstance->threshold);
	}
	return newInstance;
}

void destroyTMHTHRInstance ( TMH_THR* const instance ) {
	destroyTMHGraphInstance(instance->graphData);
	destroyTMHConfigInstance(instance->configuration);
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runTHR( TMH_THR* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runTHR_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSource,&(instance->threshold));
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runTHR_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const threshold ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[THR],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runTHR_SingleSource(graph,source,*(threshold));
	}
}

void runTHR_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, TMHNodeData threshold  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHNodeDLListWrapper* mainQueue = createTMHNodeDLListInstance();
	TMHNodeDLListWrapper* outQueue = createTMHNodeDLListInstance();

	reinitializeTMHGraph(graph,sourceNode);
	pushTMHNodeDLList(mainQueue->head,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_THR_initQueueWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	do {
		while ( (currentNode = popTMHNodeDLList(mainQueue->head)) != NULL ) {
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_nextQueueLoop);
			}

			if (isTraceLogEnabled()) {
				if ( currentNode->predecessor == NULL ) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElementNoParent,currentNode->nodeID,currentNode->distanceLabel);
				} else {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElement,currentNode->nodeID,currentNode->distanceLabel,currentNode->predecessor->nodeID);
				}
			}

			adjacencyList = currentNode->successors;

			while ( adjacencyList != NULL ) {
				arc = adjacencyList->arc;
				toNode = graph->nodeArray[arc->successor];
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
						if ( newDistance < threshold ) {
							trace(MODULE_NAME,trace_THR_belowThresholdLevel,toNode->nodeID,toNode->distanceLabel);
						} else {
							trace(MODULE_NAME,trace_THR_outOfThresholdLevel,toNode->nodeID,toNode->distanceLabel);
						}
					}

					toNode->distanceLabel = newDistance;
					toNode->predecessor = currentNode;

					pushTMHNodeDLList(((newDistance < threshold) ? mainQueue->head : outQueue->head),toNode);

				}
				adjacencyList = adjacencyList->nextElement;
			}
		}
	} while ( (mainQueue = relocateAndUpdateTHR(mainQueue,outQueue,&threshold) ) != NULL );
}

static TMHNodeData getParameterOrDefaultTHR( const TMHNodeData constant ) {
	int j=0;
	int c;
	while ( (c = getc(stdin)) != '\n' ) {
		j = ((j<<3) + (j<<1)) + (c - 48);	/*10 = 3*2 + 2 */
	}
	if ( j == 0 ) {
		return constant;
	} else {
		return (TMHNodeData) j;
	}
}

static TMHNodeDLListWrapper* relocateAndUpdateTHR( TMHNodeDLListWrapper* const mainQueue, TMHNodeDLListWrapper* const outQueue, TMHNodeData* const threshold ) {
	TMHNodeDLList* list = outQueue->head->next;
	TMHNodeDLList* tail = outQueue->tail;
	TMHNodeData currentNodeDistance;
	TMHNodeData newThreshold = *(threshold);

	while ( list != tail ) {
		currentNodeDistance = list->data->distanceLabel;
		if ( newThreshold < currentNodeDistance ) {
			newThreshold = currentNodeDistance;
		}
		list = list->next;
	}

	list = outQueue->head->next;
	newThreshold += *(threshold);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_THR_updateThreshold,*(threshold),newThreshold);
	}

	while ( list != tail ) {
		currentNodeDistance = list->data->distanceLabel;
		if ( currentNodeDistance < newThreshold ) {
			repinTMHNodeDLList(mainQueue->head,list->data);
		}
		list = list->next;
	}

	*(threshold) = newThreshold;

	if (  mainQueue->head->next == mainQueue->tail ) {
		destroyTMHNodeDLListInstance(mainQueue,false);
		return NULL;
	} else {
		return mainQueue;
	}
}
