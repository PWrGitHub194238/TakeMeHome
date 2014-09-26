/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKB.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Basic Implementation
 * To znaczy z nC+1 kube�kami
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKB.h"	/* TMH_DKB, TMHGraph, TMHConfig, TMHNodeIdx, bool,
															destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		destroyTMHConfigurationInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		memFree() */

#include "../../../../Headers/Structures/TMHNodeDLList.h"	/* createTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	destroyTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	pushTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	isEmpty() */
#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"	/* reinitializeTMHGraph() */

#include "../../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKB */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKB_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKB";


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

TMH_DKB* createTMHDKBInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig ) {
	TMH_DKB* newInstance = memMalloc(1,sizeof(TMH_DKB));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( checkConfig ) {
		checkTMHConfig(configuration);
	}
	return newInstance;
}

void destroyTMHDKBInstance ( TMH_DKB* const instance ) {
	destroyTMHGraphInstance(instance->graphData);
	destroyTMHConfigInstance(instance->configuration);
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runDKB( TMH_DKB* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKB_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSource);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[DKB],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runDKB_SingleSource(graph,source);
	}
}

void runDKB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {
	TMHNodeData i;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** bucketsArray;
	TMHNodeDLList* currentBucket;
	TMHNodeData maxDistance = numberOfNodes * graph->maxArcCost + 1;

	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;


	reinitializeTMHGraph(graph,sourceNode);
	bucketsArray = createBucketsDKB(maxDistance,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKB_createBucket,maxDistance);
		trace(MODULE_NAME,trace_DKB_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	for ( i = 0; i < maxDistance; i += 1 ) {
		currentBucket = bucketsArray[i]->head;
		if ( currentBucket->next->next == NULL ) {	// is empty
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketEmpty,i);
			}
			continue;
		} else {
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucket,i,maxDistance);
			}
			do {

				currentNode = popTMHNodeDLList(currentBucket);

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
						if ( toNode->toUpperStruct == NULL ) {
							if (isTraceLogEnabled()) {
								trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newDistance);
							}
							pushTMHNodeDLList(bucketsArray[newDistance]->head,toNode);
						} else {
							if (isTraceLogEnabled()) {
								trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newDistance,((bucketsArray[toNode->distanceLabel]->head->next->next)) ? "" : " Source bucket is now empty.");
							}
							repinTMHNodeDLList(bucketsArray[newDistance]->head,toNode);
						}

						toNode->distanceLabel = newDistance;
						toNode->predecessor = currentNode;
					}
					adjacencyList = adjacencyList->nextElement;
				}
			} while ( currentBucket->next->next != NULL );
		}
	}

	info(MODULE_NAME,info_TMHAlgorithmHelper_destroyBucket,maxDistance);
	cleanUpBuckets(bucketsArray,maxDistance);

}
