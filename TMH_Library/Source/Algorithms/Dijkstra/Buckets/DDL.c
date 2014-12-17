/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DDL.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Approximate
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DDL.h"
															/* TMH_DDL, TMHGraph, TMHConfig, TMHNodeIdx, bool,
															destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		destroyTMHConfigurationInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		memFree() */

#include "../../../../Headers/Structures/TMHNodeDLList.h"	/* createTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	destroyTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	priorityPushTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	popLastTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	priorityRepinTMHNodeDLList() */
#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"	/* reinitializeTMHGraph() */

#include "../../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DDL */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DDL_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DDL";

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

TMH_DDL* createTMHDDLInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DDL* newInstance = memMalloc(1,sizeof(TMH_DDL));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDDLInstance ( TMH_DDL* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDDL( TMH_DDL* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDDL_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDDL_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DDL],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDDL_SingleSource(graph,source);
	}
}

void runDDL_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode ) {
	bool continueScanning = true;
	TMHArcCost i;
	TMHArcCost newIdx;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** bucketsArray;
	TMHNodeDLListWrapper* currentBucket;
	TMHArcCost maxCost = graph->maxArcCost;
	TMHArcCost numberOfBuckets = maxCost + 1;

	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;


	long long int k = 0;

	printf("\nNODE: %u", numberOfNodes);

	reinitializeTMHGraph(graph,sourceNode);
	bucketsArray = createBucketsDDL(numberOfBuckets,sourceNode);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DDL_createBuckets,numberOfBuckets);
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( continueScanning ) {
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_nextBucketScanLoop,numberOfBuckets);
		}
		continueScanning = false;
		for ( i = 0; i < numberOfBuckets; i += 1 ) {
			currentBucket = bucketsArray[i];
			if ( currentBucket->head->next == currentBucket->tail ) {	// is empty
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketEmpty,i);
				}
				continue;
			} else {
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucket,i,i+1,numberOfBuckets);
				}
				do {
					currentNode = popTMHNodeDLList(currentBucket->head);
					k+=1;
					if (isTraceLogEnabled()) {
						if ( currentNode->predecessor == NULL ) {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElementNoParent,currentNode->nodeID,currentNode->distanceLabel);
						} else {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElement,currentNode->nodeID,currentNode->distanceLabel,currentNode->predecessor->nodeID);
						}
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

							newIdx = newDistance % numberOfBuckets;

							if ( newIdx < i ) {
								continueScanning = true;
							}

							if (isTraceLogEnabled()) {
								if ( toNode->toUpperStruct == NULL ) {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newIdx);
								} else {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newIdx,((bucketsArray[toNode->distanceLabel%numberOfBuckets]->head->next->next->next)) ? "" : " Source bucket is now empty.");
								}
							}

							toNode->distanceLabel = newDistance;
							toNode->predecessor = currentNode;

							if ( toNode->toUpperStruct == NULL ) {
								pushTMHNodeDLList(bucketsArray[newIdx]->head,toNode);
							} else {
								repinTMHNodeDLList(bucketsArray[newIdx]->head,toNode);
							}
						}

						if (isTraceLogEnabled() && continueScanning ) {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_setRescan,toNode->nodeID,newDistance,newIdx);
						}

						adjacencyList = adjacencyList->nextElement;
					}
					if(isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketScanEnds,i);
					}
				} while ( currentBucket->head->next != currentBucket->tail );
			}
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyBucket,numberOfBuckets);
	}
	cleanUpBuckets(bucketsArray,numberOfBuckets);

	printf("\nNODE: %llu\n", k);
}
