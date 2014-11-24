/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHRecord.c
 * @author tomasz
 * @date 14 wrz 2014
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

#include "../../../Headers/Structures/Record/TMHRecord.h"	/* TMHRecord, TMHNodeIdx */

#include "../../../Headers/Helpers/TMHAllocHelper.h"		/* memMalloc(), memFree() */

#include "../../../Headers/TMHLogger.h"						/* debug() */
#include "../../../Headers/Helpers/TMHErrors.h"				/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHRecord";

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

TMHRecord* createTMHRecordInstance( const TMHNodeIdx sourceNodeID, const TMHNodeIdx targetNodeID, TMHNodeSlimList* const pathFromSource) {
	TMHRecord* newRecord = memMalloc(1,sizeof(TMHRecord));
	newRecord->sourceNodeID = sourceNodeID;
	newRecord->targetNodeID = targetNodeID;
	newRecord->pathFromSource = pathFromSource;
	return newRecord;
}

void destroyTMHRecordInstance ( TMHRecord* const instance ) {
	destroyTMHNodeSlimListInstance(instance->pathFromSource);
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}
