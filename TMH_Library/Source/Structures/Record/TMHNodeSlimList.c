/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSlimList.c
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

#include "../../../Headers/Structures/Record/TMHNodeSlimList.h"	/*TMHNodeSlim, destroyTMHNodeSlimInstance() */

#include "../../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../../Headers/TMHLogger.h"				/* debug() */
#include "../../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeSlimList";

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

TMHNodeSlimList* createTMHNodeSlimListInstance( TMHNodeSlim* const newNodeInfo ) {
	return pushTMHNodeSlimList(NULL,newNodeInfo);
}

void destroyTMHNodeSlimListInstance ( TMHNodeSlimList* instance ) {
	TMHNodeSlimList* temp = instance;
	while ( temp != NULL ) {
		instance = instance->nextElement;
		destroyTMHNodeSlimInstance(temp->nodeInfo);
		memFree(temp);
		temp = instance;
	}
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

TMHNodeSlimList* pushTMHNodeSlimList ( TMHNodeSlimList* const slimListBegin, TMHNodeSlim* const newNodeInfo ) {
	TMHNodeSlimList* newSlimListElement = memMalloc(1,sizeof(TMHNodeSlimList));
	newSlimListElement->nodeInfo = newNodeInfo;
	newSlimListElement->nextElement = slimListBegin;
	return newSlimListElement;
}
