/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHDHeap.c
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../Headers/Structures/Buckets/TMHBucketRange.h"		/* TMHBucketRange */

#include "../../../Headers/Helpers/TMHAllocHelper.h"				/* memMalloc(), freeMem(), NULL */

#include "../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHBucketRange";

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

TMHBucketRange* createBucketRangeInstance( TMHNodeIdx begin, TMHNodeIdx size ) {
	TMHBucketRange* newBucketRange = memMalloc(1,sizeof(TMHBucketRange));
	newBucketRange->begin = begin;
	newBucketRange->size = size;
	newBucketRange->end = begin + size - 1;
	return newBucketRange;
}

void destroyTMHBucketRangeInstance( TMHBucketRange* const instance ) {
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}
