/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKA.h
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

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKA.h"	/* TMH_DKA, TMHGraph, TMHConfig, TMHNodeIdx, bool,
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
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKA */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKA_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKA";
static const char* ASK_FOR_NUMBER_OF_MAIN_BUCKET = "Interrupt!\nBucket-based implementation of "
		"Dijkstra's algorithm with Approximate buckets requires additional parameter.\nLeaving input empty "
		"will set this parameter to it's optimized value (in DKA implementation this parameter"
		"partitions buckets' ranges - determining number of buckets (number of buckets "
		"will be equal to maximal arc cost divided by that parameter plus 1) which can lead "
		"to either greater memory or time consumption. See documentation for implementation details.).";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHNodeData getParameterOrDefaultDKA( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost );

static TMHNodeData findBestParameter( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost );

static long long int worstCaseTimeKDA( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost, const TMHNodeData param );


/*
 * Definitions
 *
 */

TMH_DKA* createTMHDKAInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKA* newInstance = memMalloc(1,sizeof(TMH_DKA));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( configuration->allowInterrupt ) {
		printf("%s\n",ASK_FOR_NUMBER_OF_MAIN_BUCKET);
		newInstance->bucketsRangeMod = getParameterOrDefaultDKA(&(graphData->numberOfArcs),&(graphData->numberOfNodes),&(graphData->maxArcCost));
	} else if ( configuration->defaultParameter == NULL ) {
		newInstance->bucketsRangeMod = findBestParameter(&(graphData->numberOfArcs),&(graphData->numberOfNodes),&(graphData->maxArcCost));
	} else {
		newInstance->bucketsRangeMod = *(configuration->defaultParameter);
	}
	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_DKA_parametrReaded,newInstance->bucketsRangeMod);
	}
	return newInstance;
}

void destroyTMHDKAInstance ( TMH_DKA* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKA( TMH_DKA* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKA_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources,&(instance->bucketsRangeMod));
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKA_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const bucketsRangeMod ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		printf("Source node: %d / %d\n",i+1,sourceNodeArraySize);
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKA],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKA_SingleSource(graph,source,*bucketsRangeMod);
	}
}

void runDKA_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData bucketsRangeMod ) {
	bool continueScanning = true;
	TMHArcCost i;
	TMHArcCost newIdx;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** bucketsArray;
	TMHNodeDLListWrapper* currentBucket;
	TMHArcCost maxCost = graph->maxArcCost;
	TMHArcCost numberOfBuckets = maxCost/bucketsRangeMod + 1;

	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;

	reinitializeTMHGraph(graph,sourceNode);
	bucketsArray = createBucketsDKA(numberOfBuckets,sourceNode);

	if (isInfoLogEnabled()) {
		if ( bucketsRangeMod > 1 ) {
			info(MODULE_NAME,info_DKA_parametrSummary,maxCost,bucketsRangeMod-1,numberOfBuckets);
		} else {
			info(MODULE_NAME,info_DKA_parametrSummaryZeroRange,maxCost,numberOfBuckets);
		}
	}
	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		for ( i = 1; i <= numberOfBuckets; i += 1 ) {
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_createBucketWithRange,i,numberOfBuckets,i-1,(i-1)*bucketsRangeMod, i*bucketsRangeMod-1);
		}
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
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucketWithRange,i,i+1,numberOfBuckets,i*bucketsRangeMod, (i+1)*bucketsRangeMod-1);
				}
				do {
					currentNode = popLastTMHNodeDLList(currentBucket->tail);	/* fifo - wrzucamy od strony headera, wyci�gamy z taila */
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

							newIdx = newDistance/bucketsRangeMod;
							if ( newIdx >= numberOfBuckets ) {
								newIdx = newIdx % numberOfBuckets;
								continueScanning = true;
							}
							if (isTraceLogEnabled()) {
								if ( toNode->toUpperStruct == NULL ) {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newIdx);
								} else {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newIdx,((bucketsArray[(toNode->distanceLabel/bucketsRangeMod)%numberOfBuckets]->head->next->next->next)) ? "" : " Source bucket is now empty.");
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

				} while ( currentBucket->head->next != currentBucket->tail );

				if(isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketScanEnds,i);
				}
			}
		}
	}

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyBucket,numberOfBuckets);
	}
	cleanUpBuckets(bucketsArray,numberOfBuckets);
}

static TMHNodeData getParameterOrDefaultDKA( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost ) {
	int j=0;
	int c;
	while ( (c = getc(stdin)) != '\n' ) {
		j = ((j<<3) + (j<<1)) + (c - 48);	/*10 = 3*2 + 2 */
	}
	if ( j == 0 ) {
		return findBestParameter(numberOfArcs,numberOfNodes,maxArcCost);
	} else {
		return (TMHNodeData) j;
	}
}

/**
 * takes O(nI+mD+nE) time where I, D, E is the time for insert, decrease-key, extract-min
 * @param numberOfArcs
 * @param numberOfNodes
 * @param maxArcCost
 * @return
 */
static TMHNodeData findBestParameter( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost ) {
	long long int i = worstCaseTimeKDA(numberOfArcs,numberOfNodes,maxArcCost,1);
	TMHNodeData j = 2;
	if ( i >= 0 ) {
		return 1;
	} else {
		do {
			i = worstCaseTimeKDA(numberOfArcs,numberOfNodes,maxArcCost,j++);
		} while ( i < 0 );
		return j;
	}
}

static long long int worstCaseTimeKDA( const TMHNodeIdx* const numberOfArcs, const TMHNodeIdx* const numberOfNodes, const TMHArcCost* const maxArcCost, const TMHNodeData param ) {
	return -(((*maxArcCost)*(*numberOfNodes)))/(param*param) + (*numberOfArcs) + (*numberOfNodes);
}
