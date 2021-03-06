/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKD.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Double
 *
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include <math.h>											/* ceil(), pow() */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKD.h"	/* TMH_DKD, TMHGraph, TMHConfig, TMHNodeIdx, bool,
															destroyTMHGraphInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		destroyTMHConfigurationInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 		memFree() */

#include "../../../../Headers/Structures/TMHNodeDLList.h"	/* createTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	destroyTMHNodeDLListInstance(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	pushTMHNodeDLList(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	  	isEmpty() */
#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"	/* reinitializeTMHGraph(), cleanUpBuckets() */

#include "../../../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKD */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKD_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKD";
static const char* ASK_FOR_NUMBER_OF_MAIN_BUCKET = "Interrupt!\nBucket-based implementation of "
		"Dijkstra's algorithm with Double Buckets requires additional parameter.\nLeaving input empty "
		"will set this parameter to it's optimal value (in DKD implementation this parameter"
		"partitions high-buckets' ranges and number of low-buckets) which can lead to either greater memory or time consumption. "
		"See documentation for implementation details.).";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHNodeData getParameterOrDefaultDKD( const TMHNodeData constant );

/*
 * Definitions
 *
 */

TMH_DKD* createTMHDKDInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKD* newInstance = memMalloc(1,sizeof(TMH_DKD));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( configuration->allowInterrupt ) {
		printf("%s\n",ASK_FOR_NUMBER_OF_MAIN_BUCKET);
		newInstance->bucketsRangeMod = getParameterOrDefaultDKD((TMHNodeData) pow(graphData->maxArcCost,0.5));
	} else if ( configuration->defaultParameter == NULL ) {
		newInstance->bucketsRangeMod = (TMHNodeData) pow(graphData->maxArcCost,0.5);
	} else {
		newInstance->bucketsRangeMod = *(configuration->defaultParameter);
	}
	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_DKD_parametrReaded,newInstance->bucketsRangeMod);
	}
	return newInstance;
}

void destroyTMHDKDInstance ( TMH_DKD* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKD( TMH_DKD* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKD_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources,&(instance->bucketsRangeMod));
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKD_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const bucketsRangeMod ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		printf("Source node: %d / %d\n",i+1,sourceNodeArraySize);

		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKD],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKD_SingleSource(graph,source,(*bucketsRangeMod));
	}
}

void runDKD_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData bucketsRangeMod ) {
	TMHNodeData i,j,mapToLowLevelIdx = 0;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** highLevelBucketsArray;
	TMHNodeDLListWrapper** lowLevelBucketsArray;
	TMHNodeData highLevelBucketCount = ((numberOfNodes * graph->maxArcCost) / bucketsRangeMod) + 1;
	TMHNodeDLList* currentHighLevelBucket;
	TMHNodeDLList* currentLowLevelBucket;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;

	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;
	TMHNodeData oldLowLevelDistance;
	TMHNodeData newLowLevelDistance;

	TMHNodeData nodeProcessedCounter = 0;

	reinitializeTMHGraph(graph,sourceNode);
	highLevelBucketsArray = createHighLevelBucketsDKD(highLevelBucketCount,sourceNode);	/* Lepiej dla algorytmu będzie jak zaczniemy od zera*/
	lowLevelBucketsArray = createLowLevelBucketsDKD(bucketsRangeMod);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		for ( i = 0; i < highLevelBucketCount; i += 1 ) {
			trace(MODULE_NAME,trace_DKD_createHighLevelBucket,i+1,highLevelBucketCount,i*bucketsRangeMod,(i+1)*bucketsRangeMod-1);
		}
		trace(MODULE_NAME,trace_DKD_createLowLevelBucket,bucketsRangeMod);
		trace(MODULE_NAME,trace_DKD_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	for ( i = 0; i < highLevelBucketCount; i += 1 ) {
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_DKD_highLevelLoop,i,i+1,highLevelBucketCount,i*bucketsRangeMod,(i+1)*bucketsRangeMod-1);
		}
		currentHighLevelBucket = highLevelBucketsArray[i]->head->next;
		if ( currentHighLevelBucket->next == NULL ) {	// is empty
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_DKD_highLevelBucketEmpty,i);
			}
			if ( nodeProcessedCounter == numberOfNodes ) {
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKD_allNodesProcessedReturn);
					info(MODULE_NAME,info_DKD_destroyBuckets,highLevelBucketCount,bucketsRangeMod);
				}
				cleanUpBuckets(highLevelBucketsArray,highLevelBucketCount);
				cleanUpBuckets(lowLevelBucketsArray,bucketsRangeMod);
				return;
			}
			mapToLowLevelIdx += bucketsRangeMod;
			continue;
		} else {
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_DKD_scanningHighLevelBucket,i);
			}

			do {	// nie jest pusty
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKD_populateLowLevelBuckets,currentHighLevelBucket->data->nodeID,currentHighLevelBucket->data->distanceLabel,i,currentHighLevelBucket->data->distanceLabel-mapToLowLevelIdx);
				}
				currentLowLevelBucket = currentHighLevelBucket;
				currentHighLevelBucket = currentHighLevelBucket->next;
				repinTMHNodeDLList(lowLevelBucketsArray[currentLowLevelBucket->data->distanceLabel - mapToLowLevelIdx]->head,currentLowLevelBucket->data);
			} while ( currentHighLevelBucket->next != NULL );

			for ( j = 0; j < bucketsRangeMod; j++ ) {
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKD_lowLevelLoop,j,j+1,bucketsRangeMod,i);
				}
				currentLowLevelBucket = lowLevelBucketsArray[j]->head;
				if ( currentLowLevelBucket->next->next == NULL ) {	// is empty
					if (isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_DKD_lowLevelBucketEmpty,j);
					}
					continue;
				} else {
					if (isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_DKD_scanningLowLevelBucket,j);
					}
					do {

						currentNode = popTMHNodeDLList(currentLowLevelBucket);
						nodeProcessedCounter += 1;
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
										trace(MODULE_NAME,trace_TMHAlgorithmHelper_makeRelax,toNode->predecessor->nodeID,toNode->predecessor->distanceLabel,(toNode->distanceLabel-toNode->predecessor->distanceLabel),toNode->nodeID,toNode->distanceLabel,currentNode->nodeID,currentNode->distanceLabel,arc->distance,toNode->nodeID,newDistance);
									}
								}

								oldLowLevelDistance = toNode->distanceLabel - mapToLowLevelIdx;
								newLowLevelDistance = newDistance - mapToLowLevelIdx;

								if ( toNode->toUpperStruct == NULL ) {
									if ( newLowLevelDistance < bucketsRangeMod ) {	/* -> low */
										if (isTraceLogEnabled()) {
											trace(MODULE_NAME,trace_DKD_pushIntoLowLevelBucket,toNode->nodeID,newDistance,newLowLevelDistance);
										}
										pushTMHNodeDLList(lowLevelBucketsArray[newLowLevelDistance]->head,toNode);
									} else {	/* -> high */
										if (isTraceLogEnabled()) {
											trace(MODULE_NAME,trace_DKD_pushIntoHighLevelBucket,toNode->nodeID,newDistance,newDistance/bucketsRangeMod);
										}
										pushTMHNodeDLList(highLevelBucketsArray[newDistance/bucketsRangeMod]->head,toNode);
									}
								} else {
									if ( oldLowLevelDistance < bucketsRangeMod ) {	/* new < old < bRM => low -> low*/
										if (isTraceLogEnabled()) {
											trace(MODULE_NAME,trace_DKD_repinBetweenLowLevelBuckets,toNode->nodeID,newDistance,oldLowLevelDistance,newLowLevelDistance,((lowLevelBucketsArray[oldLowLevelDistance]->head->next->next->next)) ? "" : " Source low-level bucket is now empty.");
										}
										repinTMHNodeDLList(lowLevelBucketsArray[newLowLevelDistance]->head,toNode);
									} else {
										if ( newLowLevelDistance < bucketsRangeMod ) {	/* high -> low */
											if (isTraceLogEnabled()) {
												trace(MODULE_NAME,trace_DKD_repinToLowLevelBuckets,toNode->nodeID,newDistance,toNode->distanceLabel/bucketsRangeMod,newLowLevelDistance,((highLevelBucketsArray[toNode->distanceLabel/bucketsRangeMod]->head->next->next->next)) ? "" : " Source high-level bucket is now empty.");
											}
											repinTMHNodeDLList(lowLevelBucketsArray[newLowLevelDistance]->head,toNode);
										} else if ( toNode->distanceLabel/bucketsRangeMod == newDistance/bucketsRangeMod ) {	/* high -> high, jeśli ma sens */
											if (isTraceLogEnabled()) {
												trace(MODULE_NAME,trace_DKD_noRepinBetweenHighLevelBucket,toNode->nodeID,newDistance,newDistance/bucketsRangeMod);
											}
										} else {
											if (isTraceLogEnabled()) {
												trace(MODULE_NAME,trace_DKD_repinBetweenHighLevelBucket,toNode->nodeID,newDistance,toNode->distanceLabel/bucketsRangeMod,newDistance/bucketsRangeMod,((highLevelBucketsArray[toNode->distanceLabel/bucketsRangeMod]->head->next->next->next)) ? "" : " Source high-level bucket is now empty.");
											}
											repinTMHNodeDLList(highLevelBucketsArray[newDistance/bucketsRangeMod]->head,toNode);
										}
									}
								}

								toNode->distanceLabel = newDistance;
								toNode->predecessor = currentNode;
							}
							adjacencyList = adjacencyList->nextElement;
						}
					} while ( currentLowLevelBucket->next->next != NULL );
				}
			}
			mapToLowLevelIdx += bucketsRangeMod;
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_DKD_destroyBuckets,highLevelBucketCount,bucketsRangeMod);
	}
	cleanUpBuckets(highLevelBucketsArray,highLevelBucketCount);
	cleanUpBuckets(lowLevelBucketsArray,bucketsRangeMod);
}

static TMHNodeData getParameterOrDefaultDKD( const TMHNodeData constant ) {
	int j=0;
	char c;
	while ( (c = getc(stdin)) != '\n' ) {
		j = ((j<<3) + (j<<1)) + (c - 48);	/*10 = 3*2 + 2 */
	}
	if ( j == 0 || (TMHNodeData) j > constant ) {
		return constant;
	} else {
		return (TMHNodeData) j;
	}
}
