/*
 * TMHErrors.h
 *
 *  Created on: 3 sie 2014
 *      Author: tomasz
 */

#ifndef TMHERRORS_H_
#define TMHERRORS_H_

/*
 * Includes
 */



/*
 * Typedefs
 */



/*
 * Declarations
 */


/* *****************************************************************************************************
 * TMHAllocHelper
 *
 */

/*	TRACE	*/

/*	DEBUG	*/
extern const char* debug_instanceDeletedSuccessfully;

/*	INFO	*/
extern const char* info_TMHAllocHelper_cannotFreeNull;

/*	WARN	*/

/*	ERROR	*/
extern const char* err_TMHAllocHelper_mallocFailure;
extern const char* err_TMHAllocHelper_callocFailure;

/*	FATAL	*/


/* *****************************************************************************************************
 * TMHLogger
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHLogger_timerAlreadyEnabled;
extern const char* info_TMHLogger_saveLogAlreadyEnabled;
extern const char* info_TMHLogger_timerNoNeedToDisable;

/*	WARN	*/
extern const char* warn_TMHLogger_enableLogWithOFF;

/*	ERROR	*/
extern const char* err_TMHLogger_allocErrorWithSaveLog;
extern const char* err_TMHLogger_allocErrorWithChangeSaveLog;

/*	FATAL	*/


/* *****************************************************************************************************
 * TMHIOHelper
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHIOHelper_startReadFile;
extern const char* info_TMHIOHelper_problemDefinitionLineReaded;
extern const char* info_TMHIOHelper_arcDefinitionLineReaded;
extern const char* info_TMHIOHelper_auxiliaryProblemDefinitionLineReaded;
extern const char* info_TMHIOHelper_auxiliarySSDefinitionLineReaded;
extern const char* info_TMHIOHelper_auxiliaryP2PDefinitionLineReaded;

/*	WARN	*/
/*	ERROR	*/
extern const char* err_TMHIOHelper_cannotOpenFile;

/*	FATAL	*/

extern const char* fatal_TMHIOHelper_errorReadingFile;

/* *****************************************************************************************************
 * TMHNodeSLList
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
extern const char* warn_TMHNodeSLList_removeFromEmptyList;
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
extern const char* warn_TMHNodeDLList_removeFromEmptyList;
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
extern const char* warning_TMHConfig_invalidMode;
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHAlgorithmHelper
 *
 */

/*	TRACE	*/
extern const char* trace_TMHAlgorithmHelper_reinitGraph;
extern const char* trace_TMHAlgorithmHelper_checkRelax;
extern const char* trace_TMHAlgorithmHelper_makeRelax;
extern const char* trace_TMHAlgorithmHelper_makeRelaxPredNULL;
extern const char* trace_TMHAlgorithmHelper_relaxLoop;
extern const char* trace_TMHAlgorithmHelper_nextForLoop;
extern const char* trace_TMHAlgorithmHelper_nextQueueLoop;
extern const char* trace_TMHAlgorithmHelper_nextBucketScanLoop;
extern const char* trace_TMHAlgorithmHelper_getInfinityFromQueue;
extern const char* trace_TMHAlgorithmHelper_popElementNoParent;
extern const char* trace_TMHAlgorithmHelper_popElement;
extern const char* trace_TMHAlgorithmHelper_noOutgoingEdges;
extern const char* trace_TMHAlgorithmHelper_createBucketWithRange;
extern const char* trace_TMHAlgorithmHelper_scanningBucket;
extern const char* trace_TMHAlgorithmHelper_scanningBucketWithRange;
extern const char* trace_TMHAlgorithmHelper_bucketEmpty;
extern const char* trace_TMHAlgorithmHelper_pushIntoBucket;
extern const char* trace_TMHAlgorithmHelper_repinBetweenBuckets;
extern const char* trace_TMHAlgorithmHelper_setRescan;
extern const char* trace_TMHAlgorithmHelper_bucketScanEnds;
extern const char* trace_TMHAlgorithmHelper_initTopologicalOrder;
extern const char* trace_TMHAlgorithmHelper_initBucketWithSource;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHAlgorithmHelper_SSSummaryBeforeExecution;
extern const char* info_TMHAlgorithmHelper_destroyBucket;
extern const char* info_TMHAlgorithmHelper_destroyStack;
extern const char* info_TMHAlgorithmHelper_destroyFibonacci;
extern const char* info_TMHAlgorithmHelper_destroyTopologicalOrderedArray;
extern const char* info_TMHAlgorithmHelper_destroyDHeap;

/*	WARN	*/
extern const char* warn_TMHAlgorithmHelper_negativeCycleInGraph;
extern const char* warn_TMHAlgorithmHelper_negativeCycleInGraphTopologicalOrder;

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * BFP
 *
 */

/*	TRACE	*/
extern const char* trace_BFP_skipNode;

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
extern const char* trace_DDL_createBuckets;

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
extern const char* info_DKA_parametrReaded;
extern const char* info_DKA_parametrSummary;
extern const char* info_DKA_parametrSummaryZeroRange;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKB
 *
 */

/*	TRACE	*/
extern const char* trace_DKB_createBuckets;

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
extern const char* trace_DKD_createHighLevelBucket;
extern const char* trace_DKD_createLowLevelBucket;
extern const char* trace_DKD_initBucketWithSource;
extern const char* trace_DKD_highLevelLoop;
extern const char* trace_DKD_highLevelBucketEmpty;
extern const char* trace_DKD_allNodesProcessedReturn;
extern const char* trace_DKD_scanningHighLevelBucket;
extern const char* trace_DKD_populateLowLevelBuckets;
extern const char* trace_DKD_lowLevelLoop;
extern const char* trace_DKD_lowLevelBucketEmpty;
extern const char* trace_DKD_scanningLowLevelBucket;
extern const char* trace_DKD_pushIntoLowLevelBucket;
extern const char* trace_DKD_pushIntoHighLevelBucket;
extern const char* trace_DKD_repinBetweenLowLevelBuckets;
extern const char* trace_DKD_repinToLowLevelBuckets;
extern const char* trace_DKD_noRepinBetweenHighLevelBucket;
extern const char* trace_DKD_repinBetweenHighLevelBucket;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_DKD_parametrReaded;
extern const char* info_DKD_destroyBuckets;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKM
 *
 */

/*	TRACE	*/
extern const char* trace_DKM_createBucket;
extern const char* trace_DKM_initBucketWithSource;
extern const char* trace_DKM_scanMainBuckets;
extern const char* trace_DKM_pushIntoOverflowBucket;
extern const char* trace_DKM_pushIntoMainBucket;
extern const char* trace_DKM_repinIgnored;
extern const char* trace_DKM_repinFromOverflow;
extern const char* trace_DKM_repinBetweenMainBuckets;
extern const char* trace_DKM_mainBucketsEmpty;
extern const char* trace_DKM_fillMainBucketsFromOverflow;
extern const char* trace_DKM_fillMainBucketsFromOverflowNoRepin;
extern const char* trace_DKM_overflowBagNotEmpty;
extern const char* trace_DKM_overflowBagIsEmpty;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_DKM_parametrReaded;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKX
 *
 */

/*	TRACE	*/
extern const char* trace_DKX_createOverflowBucket;
extern const char* trace_DKX_scanningOverflowBucket;
extern const char* trace_DKX_singleNodeInBucket;
extern const char* trace_DKX_multiplyNodesInBucketSingleRange;
extern const char* trace_DKX_uselessOverflowRepin;
extern const char* trace_DKX_uselessRepinBetweenBuckets;
extern const char* trace_DKX_mapNodeToBucket;
extern const char* trace_DKX_multiplyNodesInOverflow;
extern const char* trace_DKX_multiplyNodesInBucket;
extern const char* trace_DKX_newOverflowRange;
extern const char* trace_DKX_newBucketRange;
extern const char* trace_DKX_bucketRedistribution;
extern const char* trace_DKX_nodeRedistributionFromBucket;
extern const char* trace_DKX_uselessOverflowRepinRedistribution;
extern const char* trace_DKX_uselessBucketRepinRedistribution;
extern const char* trace_DKX_setRescan;

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
extern const char* trace_DKF_initQueueWithSource;
extern const char* trace_DKF_addMode;
extern const char* trace_DKF_decreaseKey;

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
extern const char* trace_DKR_initHeapWithSource;
extern const char* trace_DKR_addMode;
extern const char* trace_DKR_decreaseKey;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_DKR_parametrReaded;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKQ
 *
 */

/*	TRACE	*/
extern const char* trace_DKQ_initDLListWithSource;
extern const char* trace_DKQ_initSLListWithSource;

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
extern const char* trace_PAP_initQueueWithSource;

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
extern const char* trace_TQQ_initQueueWithSource;

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * THR
 *
 */

/*	TRACE	*/
extern const char* trace_THR_initQueueWithSource;
extern const char* trace_THR_insertBelowThresholdLevel;
extern const char* trace_THR_insertOutOfThresholdLevel;
extern const char* trace_THR_uselessBackgroundRepin;
extern const char* trace_THR_repinFromBackground;
extern const char* trace_THR_uselessMainRepin;
extern const char* trace_THR_updateThreshold;
extern const char* trace_THR_updateMainThresholdList;
extern const char* trace_THR_repinAfterThresholdUpdate;
extern const char* trace_THR_uselessRepinAfterThresholdUpdate;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_THR_parametrReaded;

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
extern const char* warn_TMHDHeap_removeFromEmptyHeap;

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
extern const char* warn_TMHFibHeap_removeFromEmptyHeap;

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeDoubleQueue
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHNodeDoubleQueue_alreadyInQueue;

/*	WARN	*/
extern const char* warn_TMHNodeDoubleQueue_removeFromEmptyQueue;

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
extern const char* warn_TMHNodeStack_removeFromEmptyStack;

/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * TMHNodeStackQueue
 *
 */

/*	TRACE	*/
/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHNodeStackQueue_alreadyInQueue;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

#endif /* TMHERRORS_H_ */
