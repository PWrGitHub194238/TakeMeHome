/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file BFP.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Bellman-Ford-Moore
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../Headers/Algorithms/Bellman/BFP.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
														destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHConfigurationInstance(),*/

#include "../../../Headers/Helpers/TMHAlgorithmHelper.h"/* reinitializeTMHGraph() */
#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */

#include "../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 BFP */
#include "../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../Headers/Helpers/TMHErrors.h"			/* debug_BFP_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFP_reinitGraph,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFP_relaxLoop,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFP_checkRelax,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFP_makeRelax */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "BFP";


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

TMH_BFP* createTMHBFPInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig ) {
	TMH_BFP* newInstance = memMalloc(1,sizeof(TMH_BFP));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( checkConfig ) {
		checkTMHConfig(configuration);
	}
	return newInstance;
}
void destroyTMHBFPInstance ( TMH_BFP* const instance ) {
	destroyTMHGraphInstance(instance->graphData);
	destroyTMHConfigInstance(instance->configuration);
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runBFP( TMH_BFP* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runBFP_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSource);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runBFP_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[BFP],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runBFP_SingleSource(graph,source);
	}
}

void runBFP_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode = NULL;
	TMHNode* toNode = NULL;
	TMHArcList* adjacencyList = NULL;
	TMHArc* arc = NULL;
	TMHNodeIdx i;
	TMHNodeIdx j = numberOfNodes;
	TMHNodeData newDistance;
	bool hasChanged = false;

	reinitializeTMHGraph(graph,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
	}
	for ( numberOfNodes--; numberOfNodes > 0; numberOfNodes-- ) { /* |V| - 1  */
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_relaxLoop,numberOfNodes-1);
		}
		for ( i = 0; i < j; i++ ) {					/* dla takiej TMHGraph trzeba przeglądnąć wszystkie nody*/
			currentNode = graph->nodeArray[i];
			if (isTraceLogEnabled() && currentNode->predecessor == NULL) {
				trace(MODULE_NAME,trace_BFP_skipNode,currentNode->nodeID);
			}
			if ( currentNode->predecessor == NULL ) {	/* nie ma sensu sprawdzac nastepcow i ich mozliwosci relaksacji, skoro ich parent ma infinity
			 	 	 	 	 	 	 	 	 	 	 	 ( == nie ma parenta)*/
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
						toNode->distanceLabel = newDistance;
						toNode->predecessor = currentNode;
						hasChanged = true;
					}
					adjacencyList = adjacencyList->nextElement;
				}
			}
		}
		if (!hasChanged) break;
		hasChanged = false;
	}

	if ( checkForNegativeCirclesAfterRalax(graph) == false ) {
		warn(MODULE_NAME,warn_TMHAlgorithmHelper_negativeCycleInGraph);
	}
}
