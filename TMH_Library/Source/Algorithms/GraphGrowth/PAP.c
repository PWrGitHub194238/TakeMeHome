/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file PAP.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Graph Growth -- Pape
 *
 * ze stosem
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../Headers/Algorithms/GraphGrowth/PAP.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
														destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHConfigurationInstance(),*/

#include "../../../Headers/Structures/TMHNodeStackQueue.h"/* TMHNodeStackQueue,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 createTMHNodeStackQueueInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 popTMHNodeStackQueue(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 pushTMHNodeStackQueue() */
#include "../../../Headers/Helpers/TMHAlgorithmHelper.h"/* reinitializeTMHGraph() */
#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */

#include "../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 PAP */
#include "../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../Headers/Helpers/TMHErrors.h"			/* debug_PAP_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "PAP";


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

TMH_PAP* createTMHPAPInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig ) {
	TMH_PAP* newInstance = memMalloc(1,sizeof(TMH_PAP));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( checkConfig ) {
		checkTMHConfig(configuration);
	}
	return newInstance;
}

void destroyTMHPAPInstance ( TMH_PAP* const instance ) {
	destroyTMHGraphInstance(instance->graphData);
	destroyTMHConfigInstance(instance->configuration);
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runPAP( TMH_PAP* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runPAP_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSource);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runPAP_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[PAP],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runPAP_SingleSource(graph,source);
	}
}

void runPAP_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	TMHNodeStackQueue* queue = createTMHNodeStackQueueInstance();

	reinitializeTMHGraph(graph,sourceNode);
	pushTMHNodeStackQueue(queue,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_PAP_initQueueWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( (currentNode = popTMHNodeStackQueue(queue)) != NULL ) {
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
				}

				pushTMHNodeStackQueue(queue,toNode);	/* nie priorytetowa, a potrzeba starej odleg³oœci*/

				toNode->distanceLabel = newDistance;
				toNode->predecessor = currentNode;
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}
}

