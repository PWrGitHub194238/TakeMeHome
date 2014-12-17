/*
 * TMHErrors.c
 *
 *  Created on: 9 sie 2014
 *      Author: tomasz
 */

#include "../../Headers/Helpers/TMHErrors.h"


/* *****************************************************************************************************
 * TMHAllocHelper
 *
 */

/*	TRACE	*/

/*	DEBUG	*/
const char* debug_instanceDeletedSuccessfully = "%s instance has been destroyed successfully";

/*	INFO	*/
const char* info_TMHAllocHelper_cannotFreeNull = "Attempt to free NULL pointer. Skipped.";

/*	WARN	*/

/*	ERROR	*/
const char* err_TMHAllocHelper_mallocFailure = "Fail to allocate memory. %d elements of %d bytes cannot be allocated.";
const char* err_TMHAllocHelper_callocFailure = "Fail to allocate memory with zero-initialize. %d elements of %d bytes cannot be allocated.";

/*	FATAL	*/


/* *****************************************************************************************************
 * TMHLogger
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
const char* info_TMHLogger_timerAlreadyEnabled = "Logger is already set to capture events with time";
const char* info_TMHLogger_saveLogAlreadyEnabled = "Log-to-file writing is already enabled. Log file: '%s'.";
const char* info_TMHLogger_timerNoNeedToDisable = "";

/*	WARN	*/
const char* warn_TMHLogger_enableLogWithOFF = "Calling 'enableLog(DBG_LEVEL)' with 'OFF' as parameter has no effect. Set 'INFO' log level by default.";

/*	ERROR	*/
const char* err_TMHLogger_allocErrorWithSaveLog = "Fail to allocate memory. Log file '%s' cannot be created.";
const char* err_TMHLogger_allocErrorWithChangeSaveLog = "Fail to change log file due to memory allocation error. Log file '%s' cannot be created.";

/*	FATAL	*/


/* *****************************************************************************************************
 * TMHIOHelper
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
const char* info_TMHIOHelper_startReadFile = "Open data file: '%s'.";
const char* info_TMHIOHelper_problemDefinitionLineReaded = "Loading data for problem: '%s':\n\tNumber of nodes\t:\t%u\n\tNumber of arcs\t:\t%u";
const char* info_TMHIOHelper_arcDefinitionLineReaded = "Arc definition read:\n\t%u\t\t---(%u)--->\t\t%u";
const char* info_TMHIOHelper_auxiliaryProblemDefinitionLineReaded = "Loading auxiliary data for problem: '%s':\n\tTargeted algorithm mode\t\t:\t%s\n\tNumber of definitions to read\t:\t%u";
const char* info_TMHIOHelper_auxiliarySSDefinitionLineReaded = "Auxiliary definition added:\n\tFind all paths from node:\t%u";
const char* info_TMHIOHelper_auxiliaryP2PDefinitionLineReaded = "Auxiliary definition added:\n\tFind path between nodes:\t%u\t\t<--->\t\t%u";

/*	WARN	*/
/*	ERROR	*/
const char* err_TMHIOHelper_cannotOpenFile = "Cannot open file '%s'.";

/*	FATAL	*/

const char* fatal_TMHIOHelper_errorReadingFile = "Fatal error - something goes wrong during file reading.";

/* *****************************************************************************************************
 * TMHNodeSLList
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warn_TMHNodeSLList_removeFromEmptyList = "Attempt to remove element from already empty list.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeDLList
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warn_TMHNodeDLList_removeFromEmptyList = "Attempt to remove element from already empty list.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHConfig
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warning_TMHConfig_invalidMode = "Invalid mode for selected algorithm. See documentation for details.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHAlgorithmHelper
 *
 */

/*	TRACE	*/
const char* trace_TMHAlgorithmHelper_reinitGraph = "Initializing graph with %u nodes.\nSet node with ID: %u as a source node with distanceLabel = 0.";
const char* trace_TMHAlgorithmHelper_checkRelax = "Checking arc:\t%u\t---(%u)--->\t%u\n\tTarget's distance labels:\n\t\tOld\t:\t%u\n\t\tNew\t:\t%u";
const char* trace_TMHAlgorithmHelper_makeRelax = "Executing relaxation. Changing nodes' linkage from:\n\t%u (%u)\t---(%u)--->\t%u (%u)\nto:\n\t%u (%u)\t---(%u)--->\t%u (%u)";
const char* trace_TMHAlgorithmHelper_makeRelaxPredNULL = "Executing relaxation. Changing nodes' linkage from:\n\tNo parents found for node with ID: %u (%u)\nto:\n\t%u (%u)\t---(%u)--->\t%u (%u)";
const char* trace_TMHAlgorithmHelper_relaxLoop = "Scanning all arcs (loops remaining: %u).";
const char* trace_TMHAlgorithmHelper_nextForLoop = "Query for next element from queue (loops remaining: %u).";
const char* trace_TMHAlgorithmHelper_nextQueueLoop = "Query for next element from queue.";
const char* trace_TMHAlgorithmHelper_nextBucketScanLoop = "Rescanning %u buckets.";
const char* trace_TMHAlgorithmHelper_getInfinityFromQueue = "Queried node is inaccessible from source node with ID: %u. No other node is reachable from source.";
const char* trace_TMHAlgorithmHelper_popElementNoParent = "Queried node details:\n\tNode ID\t\t:\t%u\n\tDistance\t:\t%u\n\tParent's ID:\t:\tno parent";
const char* trace_TMHAlgorithmHelper_popElement = "Queried node details:\n\tNode ID\t\t:\t%u\n\tDistance\t:\t%u\n\tParent's ID:\t:\t%u";
const char* trace_TMHAlgorithmHelper_noOutgoingEdges = "Queried node with ID: %u has no outgoing arcs.";
const char* trace_TMHAlgorithmHelper_createBucketWithRange = "Bucket %u of total %u created:\n\tBucket's ID\t:\t%u\n\tRange\t\t:\t[%u\t;\t%u]";
const char* trace_TMHAlgorithmHelper_scanningBucket = "Scanning bucket with ID: %u (%u / %u)";
const char* trace_TMHAlgorithmHelper_scanningBucketWithRange = "Scanning bucket with ID: %u (%u / %u)\n\tScanning bucket's range:\t[%u\t;\t%u]";
const char* trace_TMHAlgorithmHelper_bucketEmpty = "Bucket with ID: %u is empty. Bucket skipped.";
const char* trace_TMHAlgorithmHelper_pushIntoBucket = "Push node with ID: %u (distance: %u) into bucket with ID: %u.";
const char* trace_TMHAlgorithmHelper_repinBetweenBuckets = "New distance label was set to node with ID: %u (new distance: %u). Node has been moved from source bucket to one with ID: %u.%s";
const char* trace_TMHAlgorithmHelper_setRescan = "Node with ID: %u (distance: %u) has been moved to bucket with ID: %u. New bucket scanning is required.";
const char* trace_TMHAlgorithmHelper_bucketScanEnds = "Bucket with ID: %u is empty.";
const char* trace_TMHAlgorithmHelper_initTopologicalOrder = "%u nodes has been sorted in a topological order.";
const char* trace_TMHAlgorithmHelper_initBucketWithSource = "Initialize bucket[0] with source node with ID: %u (distance: %u).";
/*	DEBUG	*/
/*	INFO	*/
const char* info_TMHAlgorithmHelper_SSSummaryBeforeExecution = "PreExecution summary:\n\tRunning algorithm\t:\t%s\n\tSelected mode\t\t:\t%s\n\tSource node's ID\t:\t%u";
const char* info_TMHAlgorithmHelper_destroyBucket = "Destroying temporary bucket structure (buckets to be destroyed: %u).";
const char* info_TMHAlgorithmHelper_destroyStack = "Destroying temporary stack structure";
const char* info_TMHAlgorithmHelper_destroyFibonacci = "Destroying temporary Fibonacci heap structure";
const char* info_TMHAlgorithmHelper_destroyTopologicalOrderedArray = "Destroying temporary helper array with topogicaly ordered nodes' IDs.";
const char* info_TMHAlgorithmHelper_destroyDHeap = "Destroying temporary D-Heap structure.";

/*	WARN	*/
const char* warn_TMHAlgorithmHelper_negativeCycleInGraph = "Negative cycle in graph has been found - returned results are useless!";
const char* warn_TMHAlgorithmHelper_negativeCycleInGraphTopologicalOrder = "Negative cycle in graph has been found - unable to generate topologically ordered graph.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * BFP
 *
 */

/*	TRACE	*/
const char* trace_BFP_skipNode = "No-source node with ID: %u has no parent therefor it's distance label is ∞. Relaxation of any of it's sucessors is pointless. Skipped.";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DDL
 *
 */

/*	TRACE	*/
const char* trace_DDL_createBuckets = "%u bucket have been created with range [k;k] for every bucket k.";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKA
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
const char* info_DKA_parametrReaded = "Approximation parameter was set to: %u.";
const char* info_DKA_parametrSummary = "Parameter summary:\n\tMax cost\t:\t%u\n\tBucket range\t:\t[k;k+%u]\n\t# Buckets\t:\t%u.";
const char* info_DKA_parametrSummaryZeroRange = "Parameter summary:\n\tMax cost\t:\t%u\n\tBucket range\t:\t[k;k]\n\t# Buckets\t:\t%u.";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKB
 *
 */

/*	TRACE	*/
const char* trace_DKB_createBuckets = "%u buckets was created.";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKD
 *
 */

/*	TRACE	*/
const char* trace_DKD_createHighLevelBucket = "High-level bucket %u of total %u created:\n\tRange\t:\t[%u\t;\t%u]";
const char* trace_DKD_createLowLevelBucket = "%u low-level buckets have been created.";
const char* trace_DKD_initBucketWithSource = "Initialize hight-level bucket[0] with source node with ID: %u (distance: %u).";
const char* trace_DKD_highLevelLoop = "Go to next high-level bucket with ID: %u (%u of total: %u)\n\tRange\t:\t[%u\t;\t%u]";
const char* trace_DKD_highLevelBucketEmpty = "High-level bucket with ID: %u is empty. Bucket skipped.";
const char* trace_DKD_scanningHighLevelBucket = "Scanning non-empty high-level bucket with ID: %u.";
const char* trace_DKD_populateLowLevelBuckets = "Move node with ID: %u (distance: %u) from high-level bucket with ID: %u to low-level bucket with ID: %u";
const char* trace_DKD_lowLevelLoop = "Scanning low-level bucket with ID: %u (%u of total: %u) populated from high-level bucket with ID: %u.";
const char* trace_DKD_lowLevelBucketEmpty = "Low-level bucket with ID: %u is empty. Bucket skipped.";
const char* trace_DKD_scanningLowLevelBucket = "Scanning non-empty low-level bucket with ID: %u.";
const char* trace_DKD_pushIntoLowLevelBucket = "Push node with ID: %u (distance: %u) into low-level bucket with ID: %u.";
const char* trace_DKD_pushIntoHighLevelBucket = "Push node with ID: %u (distance: %u) into high-level bucket with ID: %u.";
const char* trace_DKD_repinBetweenLowLevelBuckets = "New distance label was set to node with ID: %u (new distance: %u). Node has been moved from source low-level bucket with ID: %u to one with ID: %u.%s";
const char* trace_DKD_repinToLowLevelBuckets = "New distance label was set to node with ID: %u (new distance: %u). Node has been moved from source high-level bucket with ID: %u to low-level bucket with ID: %u.%s";
const char* trace_DKD_noRepinBetweenHighLevelBucket = "New distance label was set to node with ID: %u (new distance: %u) in high-level bucket with ID: %u.";
const char* trace_DKD_repinBetweenHighLevelBucket = "New distance label was set to node with ID: %u (new distance: %u). Node has been moved from source high-level bucket with ID: %u to one with ID: %u.%s";

/*	DEBUG	*/
/*	INFO	*/
const char* info_DKD_parametrReaded = "Bucket partition parameter was set to: %u.";
const char* info_DKD_destroyBuckets = "Destroying temporary bucket structure.\n\tHigh-level buckets\t:\t%u\n\tLow-level buckets\t:\t%u";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKM
 *
 */

/*	TRACE	*/
const char* trace_DKM_createBucket = "%u buckets was created. Last bucket (with ID: %u) is overflow bag.";
const char* trace_DKM_initBucketWithSource = "Initialize bucket[0] with source node with ID: %u (distance: %u).";
const char* trace_DKM_scanMainBuckets = "Begin scanning %u of main buckets:\n\tMain buckets' range\t:\t[%u:%u].";
const char* trace_DKM_pushIntoOverflowBucket = "Push node with ID: %u (distance: %u) into overflow bucket with ID: %u.";
const char* trace_DKM_pushIntoMainBucket = "Push node with ID: %u (distance: %u) into main bucket with ID: %u.";
const char* trace_DKM_repinIgnored = "Node with ID: %u will not be relocated from overflow bag with ID: %u regardless of it's distance label change (%u -> %u). Node is already in overflow bag.";
const char* trace_DKM_repinFromOverflow = "Distance label of node with ID: %u has been changed (%u -> %u) and it will be moved from overflow bag with ID: %u to bucket with ID: %u.%s";
const char* trace_DKM_repinBetweenMainBuckets = "New distance label was set to node with ID: %u  (distance: %u). Node has been moved from source bucket to one with ID: %u.%s";
const char* trace_DKM_mainBucketsEmpty = "All of %u main buckets are empty. New nodes from Overflow Bag will be taken.\n\tOld main buckets' range\t:\t[%u:%u]\n\tNew main backet's range\t:\t[%u:%u].";
const char* trace_DKM_fillMainBucketsFromOverflow = "Move node from Overflow Bag:\n\tNode ID\t\t:\t%u\n\tDistance\t:\t%u\n\tParent's ID:\t:\t%u\nto main bucket with ID: %u.";
const char* trace_DKM_fillMainBucketsFromOverflowNoRepin = "Node:\n\tNode ID\t\t:\t%u\n\tDistance\t:\t%u\n\tParent's ID:\t:\t%u\nis out of new ranges [%u:%u] and will be not removed from Overflow Bag.";
const char* trace_DKM_overflowBagNotEmpty = "Overflow bucket is not empty. Main buckets will be rescanned.";
const char* trace_DKM_overflowBagIsEmpty = "Overflow bucket is empty.";

/*	DEBUG	*/
/*	INFO	*/
const char* info_DKM_parametrReaded = "Number of buckets was set to: %u.";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKX
 *
 */

/*	TRACE	*/
const char* trace_DKX_createOverflowBucket = "Create overflow bucket:\n\tBucket's ID:\t:\t%u\n\tRange\t\t:\t[%u\t:\t∞].";
const char* trace_DKX_scanningOverflowBucket = "Scanning bucket with ID: %u (%u / %u)\n\tScanning bucket's range:\t[%u\t;\t∞]";
const char* trace_DKX_singleNodeInBucket = "Single node in bucket with ID: %u has been found.";
const char* trace_DKX_multiplyNodesInBucketSingleRange = "Multiply nodes in bucket with ID: %u has been found but bucket's range is already unitary: [%u\t;\t%u].";
const char* trace_DKX_uselessOverflowRepin = "Node with ID: %u\n\tNode's distance label\t:\t%u\n\tMap node to bucket\t:\t%u\n\tBucket's range\t\t:\t[%u\t;\t∞]\nis already in correct, overflow bucket and it will not be move.";
const char* trace_DKX_uselessRepinBetweenBuckets = "Node with ID: %u\n\tOld distance label\t:\t%u\n\tNew distance label\t:\t%u\n\tMap bucket\t\t:\t%u\n\tBucket's range\t\t:\t[%u\t;\t%u]\n is already in correct bucket and it will not be moved.";
const char* trace_DKX_mapNodeToBucket = "Map node with ID: %u\n\tNode's distance label\t:\t%u\n\tMap node to bucket\t:\t%u\n\tBucket's range\t\t:\t[%u\t;\t%u].";
const char* trace_DKX_multiplyNodesInOverflow = "Multiply nodes in overflow bucket: %u - redistributing buckets' ranges from bucket[0] to bucket[%u].";
const char* trace_DKX_multiplyNodesInBucket = "Multiply nodes in bucket: %u - redistributing buckets' ranges from bucket[0] to bucket[%u].";
const char* trace_DKX_newOverflowRange = "Overflow bucket's range with ID: %u has been changed:\n\t[%u\t;\t∞]\t->\t[%u\t;\t∞].";
const char* trace_DKX_newBucketRange = "Bucket's range with ID: %u has been changed:\n\t[%u\t;\t%u]\t->\t[%u\t;\t%u].";
const char* trace_DKX_bucketRedistribution = "Redistributing nodes from bucket with ID: %u";
const char* trace_DKX_nodeRedistributionFromBucket = "Redistribute node with ID: %u (distance %u) to bucket: %u.";
const char* trace_DKX_uselessOverflowRepinRedistribution = "Node with ID: %u\n\tNode's distance label\t:\t%u\n\tMap node to bucket\t:\t%u\n\tBucket's range\t\t:\t[%u\t;\t∞]\nis already in correct, overflow bucket and it will not be redistributed.";
const char* trace_DKX_uselessBucketRepinRedistribution = "Node with ID: %u\n\tNode's distance label\t:\t%u\n\tMap node to bucket\t:\t%u\n\tBucket's range\t\t:\t[%u\t;\t%u]\nis already in correct bucket and it will not be redistributed.";
const char* trace_DKX_setRescan = "Need to rescan buckets from bucket[0] after range redistribution.";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKF
 *
 */

/*	TRACE	*/
const char* trace_DKF_initQueueWithSource = "Initialize Fibonacci Heap with source node with ID: %u (distance: %u).";
const char* trace_DKF_addMode = "Insert new node with ID: %u (distance: %u) to Fibonacci Heap.";
const char* trace_DKF_decreaseKey = "Decrease key for node within Fibonacci Heap with ID: %u from %u to new distance: %u.";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKH
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKR
 *
 */

/*	TRACE	*/
const char* trace_DKR_initHeapWithSource = "Initialize R-Heap with source node with ID: %u (distance: %u). R-parameter: %u.";
const char* trace_DKR_addMode = "Insert new node with ID: %u (distance: %u) to R-Heap.";
const char* trace_DKR_decreaseKey = "Decrease key for node within R-Heap with ID: %u from %u to new distance: %u.";

/*	DEBUG	*/
/*	INFO	*/
const char* info_DKR_parametrReaded = "Heap width parameter was set to: %u.";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKQ
 *
 */

/*	TRACE	*/
const char* trace_DKQ_initDLListWithSource = "Initialize double-linked list with source node with ID: %u (distance: %u).";
const char* trace_DKQ_initSLListWithSource = "Initialize single-linked list with source node with ID: %u (distance: %u).";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * PAP
 *
 */

/*	TRACE	*/
const char* trace_PAP_initQueueWithSource = "Initialize stack with source node with ID: %u (distance: %u).";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TQQ
 *
 */

/*	TRACE	*/
const char* trace_TQQ_initQueueWithSource = "Initialize double queue with source node with ID: %u (distance: %u).";

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* ****************************************************************************************************
 * THR
 *
 */

/*	TRACE	*/
const char* trace_THR_initQueueWithSource = "Initialize threshold main queue with source node with ID: %u (distance: %u).";
const char* trace_THR_insertBelowThresholdLevel = "Inserting node with ID: %u (distance: %u) into main queue (current threshold level: %u)";
const char* trace_THR_insertOutOfThresholdLevel = "Inserting node with ID: %u (distance: %u) into background queue. New distance is not below current threshold level: %u";
const char* trace_THR_uselessBackgroundRepin = "Node with ID: %u:\n\tOld distance\t:\t%u\n\tNew distance\t:\t%u\nis still above given threshold level: %u and it will not be moved to main queue.";
const char* trace_THR_repinFromBackground = "Node with ID: %u:\n\tOld distance\t:\t%u\n\tNew distance\t:\t%u\nis is now below given threshold level: %u and it will be moved to main queue.";
const char* trace_THR_uselessMainRepin = "Node with ID: %u:\n\tOld distance\t:\t%u\n\tNew distance\t:\t%u\nis already below given threshold level: %u and it will not be moved.";
const char* trace_THR_updateThreshold = "Main queue is empty. Updating threshold level:\n\tOld value\t:\t%u\n\tNew value\t:\t%u";

/*	DEBUG	*/
/*	INFO	*/
const char* info_THR_parametrReaded = "Threshold parameter was set to: %u. Threshold level was set to: %u.";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHDHeap
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warn_TMHDHeap_removeFromEmptyHeap = "Attempt to remove element from already empty D-Heap heap.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHFibHeap
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warn_TMHFibHeap_removeFromEmptyHeap = "Attempt to remove element from already empty Fobonacci heap.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeDoubleQueue
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
const char* info_TMHNodeDoubleQueue_alreadyInQueue = "Node with ID: %u (distance: %u) is already in queue and will not be inserted.";

/*	WARN	*/
const char* warn_TMHNodeDoubleQueue_removeFromEmptyQueue = "Attempt to remove element from already empty queue.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeStack
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
const char* warn_TMHNodeStack_removeFromEmptyStack = "Attempt to remove element from already empty stack.";

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeStackQueue
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
const char* info_TMHNodeStackQueue_alreadyInQueue = "Node with ID: %u (distance: %u) is already in queue and will not be inserted.";

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/
