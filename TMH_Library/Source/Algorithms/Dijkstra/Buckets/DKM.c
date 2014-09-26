/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKM.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Buckets -- Overflow Bag
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Buckets/DKM.h"	/* TMH_DKM, TMHGraph, TMHConfig, TMHNodeIdx, bool,
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
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKM */
#include "../../../../Headers/TMHLogger.h"					/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"			/* debug_DKM_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKM";
static const char* ASK_FOR_NUMBER_OF_MAIN_BUCKET = "Interrupt!\nBucket-based implementation of "
		"Dijkstra's algorithm with Overflow Bag requires additional parameter.\nLeaving input empty "
		"will set this parameter to it's max allowed value (in DKM implementation this parameter"
		"partitions buckets' ranges - determining size of Overflow Bag and number of the rest of buckets (number of buckes "
		"will be equal to that parameter minus 1) which can lead to either greater memory or time consumption. "
		"See documentation for implementation details.).";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHNodeData getParameterOrDefaultDKM( const TMHNodeData* const constant );

/*
 * Definitions
 *
 */

TMH_DKM* createTMHDKMInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig, bool allowInterrupt ) {
	TMH_DKM* newInstance = memMalloc(1,sizeof(TMH_DKM));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;

	if ( checkConfig ) {
		checkTMHConfig(configuration);
	}
	if ( allowInterrupt ) {
		printf("%s\n",ASK_FOR_NUMBER_OF_MAIN_BUCKET);
		newInstance->numberOfMainBuckets = getParameterOrDefaultDKM(&(graphData->maxArcCost));
	} else {
		newInstance->numberOfMainBuckets = graphData->maxArcCost;
	}
	if (isInfoLogEnabled()) {
		info(MODULE_NAME,info_DKM_parametrReaded,newInstance->numberOfMainBuckets);
	}
	return newInstance;
}

void destroyTMHDKMInstance ( TMH_DKM* const instance ) {
	destroyTMHGraphInstance(instance->graphData);
	destroyTMHConfigInstance(instance->configuration);
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runDKM( TMH_DKM* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKM_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSource,&(instance->numberOfMainBuckets));
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKM_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize, const TMHNodeData* const numberOfMainBuckets ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[DKM],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runDKM_SingleSource(graph,source,*(numberOfMainBuckets));
	}
}

void runDKM_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode, const TMHNodeData numberOfBuckets ) {
	TMHNodeData i;
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	TMHNodeDLListWrapper** bucketsArray;
	TMHNodeDLList* currentBucket;
	TMHNodeDLList* overflowBag;
	TMHNodeData minimumBucketRange = 0;
	TMHNode* currentNode;
	TMHArcList* adjacencyList;
	TMHArc* arc;
	TMHNode* toNode;
	TMHNodeData newDistance;


	reinitializeTMHGraph(graph,sourceNode);
	bucketsArray = createBucketsDKM(numberOfBuckets,sourceNode);
	overflowBag = bucketsArray[numberOfBuckets]->head;		/* element numberOfBuckets + 1 */

	if (isTraceLogEnabled()) {
		trace(MODULE_NAME,trace_TMHAlgorithmHelper_reinitGraph,numberOfNodes,sourceNode->nodeID);
		trace(MODULE_NAME,trace_DKM_createBucket,numberOfBuckets,numberOfBuckets);
		trace(MODULE_NAME,trace_DKM_initBucketWithSource,sourceNode->nodeID,sourceNode->distanceLabel);
	}

	while ( overflowBag->next->next != NULL ) {	//dopoki jest cos w overflow bagu
		if (isTraceLogEnabled()) {
			trace(MODULE_NAME,trace_DKM_overflowBagNotEmpty);
		}
		for ( i = 0; i < numberOfBuckets; i += 1 ) {
			currentBucket = bucketsArray[i]->head;
			if ( currentBucket->next->next == NULL ) {	// is empty - zak�adamy, �e zawsze currentBucket wskazuje na headera
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_bucketEmpty,i);
				}
				continue;
			} else {
				if (isTraceLogEnabled()) {
					trace(MODULE_NAME,trace_TMHAlgorithmHelper_scanningBucket,i,numberOfBuckets);
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
								if ( toNode->toUpperStruct == NULL ) {
									trace(MODULE_NAME,trace_TMHAlgorithmHelper_pushIntoBucket,toNode->nodeID,newDistance,newDistance);
								} else {
									if ( toNode->distanceLabel >= numberOfBuckets ) {
										if ( newDistance - minimumBucketRange >= numberOfBuckets ) {
											trace(MODULE_NAME,trace_DKM_repinIgnored,toNode->nodeID,numberOfBuckets,toNode->distanceLabel,newDistance);
										} else {
											trace(MODULE_NAME,trace_DKM_repinFromOverflow,toNode->nodeID,toNode->distanceLabel,newDistance,numberOfBuckets,newDistance - minimumBucketRange,((bucketsArray[numberOfBuckets]->head->next->next)) ? "" : " Overflow bag is now empty.");
										}
									} else {
										if ( newDistance - minimumBucketRange >= numberOfBuckets ) {
											trace(MODULE_NAME,trace_DKM_repinToOverflow,toNode->nodeID,toNode->distanceLabel,newDistance,numberOfBuckets,((bucketsArray[toNode->distanceLabel]->head->next->next)) ? "" : " Source bucket is now empty.");
										} else {
											trace(MODULE_NAME,trace_DKM_repinBetweenMainBuckets,toNode->nodeID,toNode->distanceLabel,newDistance - minimumBucketRange,((bucketsArray[toNode->distanceLabel]->head->next->next)) ? "" : " Source bucket is now empty.");
										}
									}
								}
							}

							toNode->distanceLabel = newDistance;
							toNode->predecessor = currentNode;

							newDistance = newDistance - minimumBucketRange;

							if ( toNode->distanceLabel < numberOfBuckets || newDistance < numberOfBuckets ) {
								if ( toNode->toUpperStruct == NULL ) {
									pushTMHNodeDLList(bucketsArray[((newDistance<numberOfBuckets) ? newDistance : numberOfBuckets)]->head,toNode);
								} else {
									repinTMHNodeDLList(bucketsArray[((newDistance<numberOfBuckets) ? newDistance : numberOfBuckets)]->head,toNode);
								}
							}
						}
						adjacencyList = adjacencyList->nextElement;
					}
				} while ( currentBucket->next->next != NULL );
			}
		}
		currentBucket = overflowBag->next;
		minimumBucketRange = distanceLabelInfinity;

		while ( currentBucket->next != NULL ) {
			if ( minimumBucketRange > currentBucket->data->distanceLabel ) {
				minimumBucketRange = currentBucket->data->distanceLabel;
			}
			currentBucket = currentBucket->next;
		}
	}

	info(MODULE_NAME,info_TMHAlgorithmHelper_destroyBucket,numberOfBuckets+1);	/* + Overflow bag */
	cleanUpBuckets(bucketsArray,numberOfBuckets+1);
}

static TMHNodeData getParameterOrDefaultDKM( const TMHNodeData* const constant ) {
	int j=0;
	char c;
	while ( (c = getc(stdin)) != '\n' ) {
		j = ((j<<3) + (j<<1)) + (c - 48);	/*10 = 3*2 + 2 */
	}
	if ( j == 0 || (TMHNodeData) j > *(constant) ) {
		return *(constant);
	} else {
		return (TMHNodeData) j;
	}
}
