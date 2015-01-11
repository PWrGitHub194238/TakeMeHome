/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKXb.c
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Radix Heap with nC buckets
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include <math.h>											/* min() */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKXb.h"
															/* TMH_DKXB, TMHGraph, TMHConfig, TMHNodeIdx, bool,
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
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKXB */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKXB_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKXb";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static void cleanDKXB( TMHBucketRange** bucketsRangeArray, TMHNodeIdx* bucketsSizeArray, TMHNodeIdx* nodeBucketIDMap, TMHArcCost numberOfBuckets );

/*
 * Definitions
 *
 */

TMH_DKXB* createTMHDKXBInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKXB* newInstance = memMalloc(1,sizeof(TMH_DKXB));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKXBInstance ( TMH_DKXB* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKXB( TMH_DKXB* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKXB_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKXB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKXb],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKXB_SingleSource(graph,source);
	}
}

void runDKXB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode ) {
	TMHArcCost i = 0;
	TMHArcCost j;
	TMHArcCost newIdx;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** bucketsArray;
	TMHBucketRange** bucketsRangeArray;
	TMHNodeIdx* bucketsSizeArray;
	TMHNodeIdx* nodeBucketIDMap;
	TMHNodeDLListWrapper* currentBucket;
	TMHNodeDLList* currentBucketIt;
	TMHNodeDLList* currentBucketTail;
	TMHArcCost maxCost = graph->maxArcCost;
	TMHArcCost numberOfBuckets = (TMHArcCost) floor(log2(numberOfNodes)+log2(maxCost)) + 2;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;
	TMHNodeData bucketLowerRange;
	TMHNodeData bucketMaxRange;

	long long int k = 0;

	printf("\nNODE: %u", numberOfNodes);

	reinitializeTMHGraph(graph,sourceNode);
	bucketsSizeArray = initBucketsSizeDKXB(numberOfBuckets);
	bucketsRangeArray = initBucketsRangeDKXB(numberOfBuckets,bucketsSizeArray);
	bucketsArray = createBucketsDKXB(numberOfBuckets,sourceNode);
	nodeBucketIDMap = initNodeBucketMapDKXB(graph->nodeArray,numberOfNodes,numberOfBuckets);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		for ( newIdx = 0; newIdx < numberOfBuckets; newIdx += 1 ) {	//unused var
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_createBucketWithRange,newIdx+1,numberOfBuckets,newIdx,bucketsRangeArray[newIdx]->begin, bucketsRangeArray[newIdx]->end);
		}
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( i < numberOfBuckets ) {
		currentBucket = bucketsArray[i];
		currentBucketTail = currentBucket->tail;
		if ( currentBucket->head->next == currentBucketTail ) {	// is empty
			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketEmpty,i);
			}
			i += 1;
			continue;
		} else {

			if (isTraceLogEnabled()) {
				trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucketWithRange,i,i+1,numberOfBuckets,bucketsRangeArray[i]->begin, bucketsRangeArray[i]->end);
			}

			if ( i >= 2 )  {
				currentNode = popMinTMHNodeDLList(currentBucket);	// wyciagamy, bo i tak sie to przyda
			} else {
				currentNode = popTMHNodeDLList(currentBucket->head);	// 0 i 11 mają zasięg [k;k][k+1;k+1]
			}

			if ( currentBucket->head->next == currentBucketTail || i < 2 ) {	// jesli byl tylko jedne element lub range = [k;k]

				do {
					k+=1;
					if (isTraceLogEnabled()) {
						if ( currentNode->predecessor == NULL ) {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElementNoParent,currentNode->nodeID,currentNode->distanceLabel);
						} else {
							trace(MODULE_NAME,trace_TMHAlgorithmHelper_popElement,currentNode->nodeID,currentNode->distanceLabel,currentNode->predecessor->nodeID);
						}
					}

					adjacencyList = currentNode->successors;

					if(isTraceLogEnabled() && adjacencyList == NULL ) {
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

							for ( newIdx = nodeBucketIDMap[toNode->nodeID]; newIdx > 0; newIdx -= 1 ) {	//szukamy nowego bucketu
								if ( bucketsRangeArray[newIdx]->begin <= newDistance && newDistance <= bucketsRangeArray[newIdx]->end ) {

									nodeBucketIDMap[toNode->nodeID] = newIdx;
									break;
								}
							}

							// lub newIdx = 0

							if (isTraceLogEnabled()) {
								trace(MODULE_NAME,trace_DKX_mapNodeToBucket,toNode->nodeID,newDistance,nodeBucketIDMap[toNode->nodeID],bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->begin, bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->end);
								if ( toNode->toUpperStruct == NULL ) {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newIdx);
								} else {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newIdx,((bucketsArray[nodeBucketIDMap[toNode->nodeID]]->head->next->next->next)) ? "" : " Source bucket is now empty.");
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

						adjacencyList = adjacencyList->nextElement;
					}
				} while ( (currentNode = popTMHNodeDLList(currentBucket->head)) != NULL );

				if(isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketScanEnds,i);
				}

			} else {	// jesli po wyciagnieciu minimum nadal cos jest- bylo ich wiecej

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_multiplyNodesInBucket,i,i);
				}

				bucketLowerRange = currentNode->distanceLabel;	// wyciągnęliśmy już minimum wcześniej
				bucketMaxRange = bucketsRangeArray[i]->end;

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_newBucketRange,0,bucketsRangeArray[0]->begin,bucketsRangeArray[0]->end,bucketLowerRange,bucketLowerRange);
				}

				bucketsRangeArray[0]->begin = bucketLowerRange;
				bucketsRangeArray[0]->end = bucketLowerRange;


				for ( j = 1; j < i; j += 1 ) {
					if (isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_DKX_newBucketRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[j]->end,((TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange)),((TMHNodeIdx) fmin(((TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange)) + (bucketsSizeArray[j] -1),bucketMaxRange)));
					}
					bucketsRangeArray[j]->begin = (TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange);
					bucketsRangeArray[j]->end = (TMHNodeIdx) fmin(bucketsRangeArray[j]->begin + (bucketsSizeArray[j] -1),bucketMaxRange);
				}

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_newBucketRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[j]->end,bucketMaxRange + 1,bucketMaxRange + 1);
				}

				bucketsRangeArray[j]->begin = bucketMaxRange;
				bucketsRangeArray[j]->end = bucketMaxRange;

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_bucketRedistribution,i);
				}

				pushTMHNodeDLList(bucketsArray[0]->head,currentNode);

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_nodeRedistributionFromBucket,currentNode->nodeID,currentNode->distanceLabel,0);
				}

				currentBucketIt = currentBucket->head->next;
				while ( currentBucketIt != currentBucketTail ) {
					currentNode = currentBucketIt->data;
					newDistance = currentNode->distanceLabel;
					for ( newIdx = i; newIdx > 0; newIdx -= 1 ) {	//szukamy nowego bucketu
						if ( bucketsRangeArray[newIdx]->begin <= newDistance && newDistance <= bucketsRangeArray[newIdx]->end ) {
							nodeBucketIDMap[currentNode->nodeID] = newIdx;
							break;
						}
					}

					if (isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_DKX_nodeRedistributionFromBucket,currentNode->nodeID,currentNode->distanceLabel,newIdx);
					}

					currentBucketIt = currentBucketIt->next;
					repinTMHNodeDLList(bucketsArray[newIdx]->head,currentNode);
				};

				if (isTraceLogEnabled() ) {
					trace(MODULE_NAME,trace_DKX_setRescan,numberOfBuckets);
				}
				i = 0;
				continue;
			}
		}
		i += 1;
	}	// next while loop

	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_TMHAlgorithmHelper_destroyBucket,numberOfBuckets);
	}
	cleanUpBuckets(bucketsArray,numberOfBuckets);
	cleanDKXB(bucketsRangeArray,bucketsSizeArray,nodeBucketIDMap,numberOfBuckets);
	printf("\nNODE: %llu\n", k);
}

static void cleanDKXB( TMHBucketRange** bucketsRangeArray, TMHNodeIdx* bucketsSizeArray, TMHNodeIdx* nodeBucketIDMap, TMHArcCost numberOfBuckets ) {
	for ( --numberOfBuckets; numberOfBuckets > 0; numberOfBuckets -= 1 ) {
		memFree(bucketsRangeArray[numberOfBuckets]);
	}
	memFree(bucketsRangeArray[numberOfBuckets]);
	memFree(bucketsRangeArray);
	memFree(bucketsSizeArray);
	memFree(nodeBucketIDMap);
}
