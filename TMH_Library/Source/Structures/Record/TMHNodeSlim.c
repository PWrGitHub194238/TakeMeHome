/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSlim.c
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

#include "../../../Headers/Structures/Record/TMHNodeSlim.h"	/* TMHNodeSlim, TMHNodeIdx, TMHNodeData*/

#include "../../../Headers/Helpers/TMHAllocHelper.h"		/* memMalloc(), memFree(), NULL */

#include "../../../Headers/TMHLogger.h"						/* debug() */
#include "../../../Headers/Helpers/TMHErrors.h"				/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeSlim";

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

TMHNodeSlim* createTMHNodeSlimInstance( const TMHNode* const node ) {
	TMHNodeSlim* newNode = memMalloc(1,sizeof(TMHNodeSlim));
	newNode->nodeID = node->nodeID;
	newNode->distanceLabel = node->distanceLabel;
	return newNode;
}

void destroyTMHNodeSlimInstance ( TMHNodeSlim* const instance ) {
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}
