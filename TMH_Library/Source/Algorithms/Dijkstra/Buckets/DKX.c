/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKX.h
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

#include <math.h>											/* min() */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKX.h"
															/* TMH_DKX, TMHGraph, TMHConfig, TMHNodeIdx, bool,
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
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKX */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKX_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKX";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static void cleanDKX( TMHBucketRange** bucketsRangeArray, TMHNodeIdx* bucketsSizeArray, TMHNodeIdx* nodeBucketIDMap, TMHArcCost numberOfBuckets );

/*
 * Definitions
 *
 */

TMH_DKX* createTMHDKXInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKX* newInstance = memMalloc(1,sizeof(TMH_DKX));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKXInstance ( TMH_DKX* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void runDKX( TMH_DKX* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKX_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKX_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
					dictionary_TMHAlgorithmFullName[DKX],
					dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
					source->nodeID);
		}
		runDKX_SingleSource(graph,source);
	}
}

void runDKX_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode ) {
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
	TMHArcCost numberOfBuckets = (TMHArcCost) ceil(log2(maxCost+1)) + 1;	// + extra overflow bag
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;
	TMHNodeData bucketLowerRange;
	TMHNodeData bucketMaxRange;
	bool update = false;

	long long int k = 0;

	printf("\nNODE: %u", numberOfNodes);

	reinitializeTMHGraph(graph,sourceNode);
	bucketsSizeArray = initBucketsSizeDKX(numberOfBuckets);
	bucketsRangeArray = initBucketsRangeDKX(numberOfBuckets,bucketsSizeArray);
	bucketsArray = createBucketsDKX(numberOfBuckets,sourceNode);
	nodeBucketIDMap = initNodeBucketMapDKX(graph->nodeArray,numberOfNodes,numberOfBuckets);

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		for ( newIdx = 0; newIdx < numberOfBuckets; newIdx += 1 ) {	//unused var
			trace(MODULE_NAME,trace_TMHAlgorithmHelper_createBucketWithRange,newIdx+1,numberOfBuckets,newIdx,bucketsRangeArray[newIdx]->begin, bucketsRangeArray[newIdx]->end);
		}
		trace(MODULE_NAME,trace_DKX_createOverflowBucket,newIdx,bucketsRangeArray[newIdx-1]->end+1);
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( i <= numberOfBuckets ) {
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
				if ( i == numberOfBuckets ) {
					trace(MODULE_NAME,trace_DKX_scanningOverflowBucket,i,i+1,numberOfBuckets,bucketsRangeArray[i-1]->end+1);
				} else {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucketWithRange,i,i+1,numberOfBuckets,bucketsRangeArray[i]->begin, bucketsRangeArray[i]->end);
				}
			}

			if ( i < numberOfBuckets && (i < 2 || bucketsRangeArray[i]->end - bucketsRangeArray[i]->begin == 0 || currentBucket->head->next->next == currentBucketTail) ) {	// jesli byl tylko jedne element lub range = [k;k] + z overflow bucketu nigdy nie będziemy brać bezpośrednio
				if ( isTraceLogEnabled() && currentBucket->head->next != currentBucketTail ) {
					if ( currentBucket->head->next->next == currentBucketTail ) {
						trace(MODULE_NAME,trace_DKX_singleNodeInBucket,i);
					} else {
						trace(MODULE_NAME,trace_DKX_multiplyNodesInBucketSingleRange,i,bucketsRangeArray[i]->begin,bucketsRangeArray[i]->end);
					}
				}

				while ( (currentNode = popTMHNodeDLList(currentBucket->head)) != NULL ) {
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

							newIdx = nodeBucketIDMap[toNode->nodeID];
							update = false;

						//	if ( newIdx == numberOfBuckets ) { //overflow
							if ( toNode->toUpperStruct == NULL ) {
								newIdx += 1;
								bucketsRangeArray[numberOfBuckets]->end = newDistance;	// do sprawdzania w forze - jeśli ma trafić do overflowu, a i tak na ->end nic nie jest oparte poza tym forem i do realokacji z overflow, gdzie inaczej sprawdzamy czy node ma zostać w overflow
								update = true;
							} else if ( newDistance < bucketsRangeArray[newIdx]->begin ) {	// jeśli nie jest w overflow
								update = true;
							} else {
								if (isTraceLogEnabled()) {
									if ( newIdx == numberOfBuckets ) {
										trace(MODULE_NAME,trace_DKX_uselessOverflowRepin,toNode->nodeID,toNode->distanceLabel,newDistance,nodeBucketIDMap[newIdx]+1);
									} else {
										trace(MODULE_NAME,trace_DKX_uselessRepinBetweenBuckets,toNode->nodeID,toNode->distanceLabel,newDistance,nodeBucketIDMap[toNode->nodeID],bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->begin,bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->end);
									}
								}
								toNode->distanceLabel = newDistance;
								toNode->predecessor = currentNode;
							}
						//	} else {
						//		newIdx += 1;	// zacznij pętlę od +1, ale wykonuj już od newIdx
						//		update = true;
						//	}

							if (update) {
								for ( ; (newIdx--) > 0; ) {	//szukamy nowego bucketu - ustaw +1, sprawdz warunek, zrób -1 i rób pętle. Tak możemy sprawdzić [k..0] zamiast [k..1]
									// już newIdx, nie newIdx+1 albo numberOfBuckets-1, a nie numberOfBuckets
									if ( bucketsRangeArray[newIdx]->begin <= newDistance && newDistance <= bucketsRangeArray[newIdx]->end ) {
										/*if ( nodeBucketIDMap[toNode->nodeID] == newIdx && toNode->toUpperStruct != NULL ) {	// nie przepinamy istniejącego, jeśli nie trzeba
											if (isTraceLogEnabled()) {
												trace(MODULE_NAME,trace_DKX_uselessRepinBetweenBuckets,toNode->nodeID,toNode->distanceLabel,newDistance,nodeBucketIDMap[toNode->nodeID],bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->begin,bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->end);
											}
											toNode->distanceLabel = newDistance;
											toNode->predecessor = currentNode;
										} else {*/
											nodeBucketIDMap[toNode->nodeID] = newIdx;
											if (isTraceLogEnabled()) {
												trace(MODULE_NAME,trace_DKX_mapNodeToBucket,toNode->nodeID,newDistance,nodeBucketIDMap[toNode->nodeID],bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->begin, bucketsRangeArray[nodeBucketIDMap[toNode->nodeID]]->end);
												if ( toNode->toUpperStruct == NULL ) {
													trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newIdx);
												} else {
													if ( nodeBucketIDMap[toNode->nodeID] == newIdx ) {
														trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newIdx,((bucketsArray[nodeBucketIDMap[toNode->nodeID]]->head->next->next)) ? "" : " Source bucket is now empty.");
													} else {
														trace(MODULE_NAME,trace_TMHAlgorithmHelper_repinBetweenBuckets,toNode->nodeID,newDistance,newIdx,((bucketsArray[nodeBucketIDMap[toNode->nodeID]]->head->next->next->next)) ? "" : " Source bucket is now empty.");	// jeszcze nie usunęliśmy
													}
												}
											}

											toNode->distanceLabel = newDistance;
											toNode->predecessor = currentNode;

											if ( toNode->toUpperStruct == NULL ) {
												pushTMHNodeDLList(bucketsArray[newIdx]->head,toNode);
											} else {
												repinTMHNodeDLList(bucketsArray[newIdx]->head,toNode);
											}
								//		}
										break;
									}
								}
							}
						}

						adjacencyList = adjacencyList->nextElement;
					}
				}

				if(isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketScanEnds,i);
				}

			} else {	// jesli po wyciagnieciu minimum nadal cos jest- bylo ich wiecej

				currentNode = popMinTMHNodeDLList(currentBucket);	// wyciagamy, bo i tak sie to przyda

				if (isTraceLogEnabled()) {
					if ( i == numberOfBuckets ) {
						trace(MODULE_NAME,trace_DKX_multiplyNodesInOverflow,i,i-1);
					} else {
						trace(MODULE_NAME,trace_DKX_multiplyNodesInBucket,i,i-1);
					}
				}

				bucketLowerRange = currentNode->distanceLabel;	// wyciągnęliśmy już minimum wcześniej

				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_DKX_newBucketRange,0,bucketsRangeArray[0]->begin,bucketsRangeArray[0]->end,bucketLowerRange,bucketLowerRange);
				}

				bucketsRangeArray[0]->begin = bucketLowerRange;
				bucketsRangeArray[0]->end = bucketLowerRange;

				if ( i == numberOfBuckets ) {	// if overflow
					for ( j = 1; j < i; j += 1 ) {
						if (isTraceLogEnabled()) {
							trace(MODULE_NAME,trace_DKX_newBucketRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[j]->end,(bucketsRangeArray[j-1]->end + 1),(bucketsRangeArray[j-1]->end + 1 + bucketsSizeArray[j] -1));
						}
						bucketsRangeArray[j]->begin = bucketsRangeArray[j-1]->end + 1;
						bucketsRangeArray[j]->end = bucketsRangeArray[j]->begin + (bucketsSizeArray[j] -1);
					}

					if (isTraceLogEnabled()) {
						trace(MODULE_NAME,trace_DKX_newOverflowRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[numberOfBuckets-1]->end + 1);
					}

					bucketsRangeArray[numberOfBuckets]->begin = bucketsRangeArray[numberOfBuckets-1]->end + 1;

				} else {	//przed overflowem

					bucketMaxRange = bucketsRangeArray[i]->end;

					for ( j = 1; j < i; j += 1 ) {
						if (isTraceLogEnabled()) {
							trace(MODULE_NAME,trace_DKX_newBucketRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[j]->end,((TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange)),((TMHNodeIdx) fmin(((TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange)) + (bucketsSizeArray[j] -1),bucketMaxRange)));
						}
						bucketsRangeArray[j]->begin = (TMHNodeIdx) fmin(bucketsRangeArray[j-1]->end + 1,bucketMaxRange);
						bucketsRangeArray[j]->end = (TMHNodeIdx) fmin(bucketsRangeArray[j]->begin + (bucketsSizeArray[j] -1),bucketMaxRange);
					}

					if (isTraceLogEnabled()) {
						if ( j == numberOfBuckets ) {
							trace(MODULE_NAME,trace_DKX_newOverflowRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[numberOfBuckets-1]->end + 1);
						} else {
							trace(MODULE_NAME,trace_DKX_newBucketRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[j]->end,bucketMaxRange + 1,bucketMaxRange + 1);
						}
					}

					bucketsRangeArray[j]->begin = bucketMaxRange; // +1
					bucketsRangeArray[j++]->end = bucketMaxRange; // +1;

					if ( j == numberOfBuckets ) {
						if (isTraceLogEnabled()) {
							trace(MODULE_NAME,trace_DKX_newOverflowRange,j,bucketsRangeArray[j]->begin,bucketsRangeArray[numberOfBuckets-1]->end + 1);
						}
						bucketsRangeArray[numberOfBuckets]->begin = bucketsRangeArray[numberOfBuckets-1]->end + 1;
					}
				}

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

					if ( newDistance < bucketsRangeArray[i]->begin ) {	// jeśli nie będzie już w overflow
						for ( newIdx = i - 1; newIdx > 0; newIdx -= 1 ) {	//szukamy nowego bucketu
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
					} else {
						currentBucketIt = currentBucketIt->next;
						if (isTraceLogEnabled()) {
							if ( i == numberOfBuckets ) {
								trace(MODULE_NAME,trace_DKX_uselessOverflowRepinRedistribution,currentNode->nodeID,currentNode->distanceLabel,nodeBucketIDMap[currentNode->nodeID],bucketsRangeArray[nodeBucketIDMap[currentNode->nodeID]]->begin);
							} else {
								trace(MODULE_NAME,trace_DKX_uselessBucketRepinRedistribution,currentNode->nodeID,currentNode->distanceLabel,nodeBucketIDMap[currentNode->nodeID],bucketsRangeArray[nodeBucketIDMap[currentNode->nodeID]]->begin,bucketsRangeArray[nodeBucketIDMap[currentNode->nodeID]]->end);
							}
						}
					}
				}

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
	cleanUpBuckets(bucketsArray,numberOfBuckets+1);
	cleanDKX(bucketsRangeArray,bucketsSizeArray,nodeBucketIDMap,numberOfBuckets);
	printf("\nNODE: %llu\n", k);

}

static void cleanDKX( TMHBucketRange** bucketsRangeArray, TMHNodeIdx* bucketsSizeArray, TMHNodeIdx* nodeBucketIDMap, TMHArcCost numberOfBuckets ) {
	for ( --numberOfBuckets; numberOfBuckets > 0; numberOfBuckets -= 1 ) {
		memFree(bucketsRangeArray[numberOfBuckets]);
	}
	memFree(bucketsRangeArray[numberOfBuckets]);
	memFree(bucketsRangeArray);
	memFree(bucketsSizeArray);
	memFree(nodeBucketIDMap);
}
