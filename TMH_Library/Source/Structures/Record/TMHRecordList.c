/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHRecordList.c
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

#include "../../../Headers/Structures/Record/TMHRecordList.h"	/*TMHRecord, destroyTMHRecordInstance() */

#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../../Headers/TMHLogger.h"				/* debug() */
#include "../../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHRecordList";

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

TMHRecordList* createTMHRecordListInstance( TMHRecord* const newRecord ) {
	return pushTMHRecordList(NULL,newRecord);
}

void destroyTMHRecordListInstance ( TMHRecordList* instance ) {
	TMHRecordList* temp = instance;
	while ( temp != NULL ) {
		instance = instance->nextElement;
		destroyTMHRecordInstance(temp->record);
		memFree(temp);
		temp = instance;
	}
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

TMHRecordList* pushTMHRecordList ( TMHRecordList* const slimListBegin, TMHRecord* const newRecord ) {
	TMHRecordList* newSlimListElement = memMalloc(1,sizeof(TMHRecordList));
	newSlimListElement->record = newRecord;
	newSlimListElement->nextElement = slimListBegin;
	return newSlimListElement;
}
