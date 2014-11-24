/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file BFM.h
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

#include "../../../Headers/Algorithms/Bellman/BFM.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
														destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	destroyTMHConfigurationInstance(),*/

#include "../../../Headers/Helpers/TMHAlgorithmHelper.h"/* reinitializeTMHGraph() */
#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */

#include "../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 BFM */
#include "../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../Headers/Helpers/TMHErrors.h"			/* debug_BFM_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFM_reinitGraph,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFM_relaxLoop,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFM_checkRelax,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_BFM_makeRelax */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "BFM";


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

TMH_BFM* createTMHBFMInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_BFM* newInstance = memMalloc(1,sizeof(TMH_BFM));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}
void destroyTMHBFMInstance ( TMH_BFM* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runBFM( TMH_BFM* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runBFM_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runBFM_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[BFM],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runBFM_SingleSource(graph,source);
	}
}

void runBFM_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNode* currentNode = NULL;
	TMHNode* toNode = NULL;
	TMHArcList* adjacencyList = NULL;
	TMHArc* arc = NULL;
	TMHNodeIdx i;
	TMHNodeIdx j = numberOfNodes;
	TMHNodeData newDistance;

	reinitializeTMHGraph(graph,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
	}
	for ( numberOfNodes--; numberOfNodes > 0; numberOfNodes-- ) {	/* |V| - 1  */
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_relaxLoop,numberOfNodes-1);
		}
		for ( i = j; i > 0; i-- ) {					/* dla takiej TMHGraph trzeba przeglądnąć wszystkie nody*/
			currentNode = graph->nodeArray[i];
			adjacencyList = currentNode->successors;
			while ( adjacencyList != NULL ) {
				arc = adjacencyList->arc;
				toNode = arc->successor;
				if ( currentNode->distanceLabel == distanceLabelInfinity ) {
					newDistance = distanceLabelInfinity;
				} else {
					newDistance = currentNode->distanceLabel + arc->distance;
				}
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
				}
				adjacencyList = adjacencyList->nextElement;
			}
		}
	}

	if ( checkForNegativeCirclesAfterRalax(graph) == false ) {
		warn(MODULE_NAME,warn_TMHAlgorithmHelper_negativeCycleInGraph);
	}
}
