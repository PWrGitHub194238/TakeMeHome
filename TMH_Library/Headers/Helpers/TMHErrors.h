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
extern const char* trace_TMHAlgorithmHelper_scanningBucket;
extern const char* trace_TMHAlgorithmHelper_bucketEmpty;
extern const char* trace_TMHAlgorithmHelper_pushIntoBucket;
extern const char* trace_TMHAlgorithmHelper_repinBetweenBuckets;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_TMHAlgorithmHelper_SSSummaryBeforeExecution;
extern const char* info_TMHAlgorithmHelper_destroyBucket;

/*	WARN	*/
extern const char* warn_TMHAlgorithmHelper_negativeCycleInGraph;

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
 * DKA
 *
 */

/*	TRACE	*/
extern const char* trace_DKA_createBucket;
extern const char* trace_DKA_initBucketWithSource;
extern const char* trace_DKA_setRescan;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_DKA_parametrReaded;

/*	WARN	*/
/*	ERROR	*/
/*	FATAL	*/

/* *****************************************************************************************************
 * DKB
 *
 */

/*	TRACE	*/
extern const char* trace_DKB_createBucket;
extern const char* trace_DKB_initBucketWithSource;

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
extern const char* trace_DKD_scanningHighLevelBucket;
extern const char* trace_DKD_populateLowLevelBuckets;
extern const char* trace_DKD_lowLevelLoop;
extern const char* trace_DKD_lowLevelBucketEmpty;
extern const char* trace_DKD_scanningLowLevelBucket;
extern const char* trace_DKD_pushIntoLowLevelBucket;
extern const char* trace_DKD_repinBetweenLowLevelBuckets;
extern const char* trace_DKD_pushIntoHighLevelBucket;
extern const char* trace_DKD_repinIntoHighLevelBucket;

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
extern const char* trace_DKM_overflowBagNotEmpty;
extern const char* trace_DKM_repinIgnored;
extern const char* trace_DKM_repinFromOverflow;
extern const char* trace_DKM_repinToOverflow;
extern const char* trace_DKM_repinBetweenMainBuckets;

/*	DEBUG	*/
/*	INFO	*/
extern const char* info_DKM_parametrReaded;

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
 * DKQ
 *
 */

/*	TRACE	*/
extern const char* trace_DKQ_initQStackWithSource;

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
const char* trace_PAP_initQueueWithSource;

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
const char* trace_TQQ_initQueueWithSource;

/*	DEBUG	*/
/*	INFO	*/
/*	WARN	*/
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