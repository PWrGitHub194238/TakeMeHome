/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNode.c
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

#include "../../Headers/Structures/TMHNode.h"

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */
#include "../../Headers/Structures/TMHArcList.h"	/*destroyTMHArcListInstance() */
#include "../../Headers/TMHLogger.h"				/* debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNode";


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

TMHNode* createTMHNodeInstance( const TMHNodeIdx nodeID ) {
	TMHNode* newNode = memMalloc(1,sizeof(TMHNode));
	newNode->nodeID = nodeID;
	newNode->distanceLabel = distanceLabelInfinity;
	newNode->predecessor = NULL;
	newNode->successors = NULL;
	newNode->toUpperStruct = NULL;
	return newNode;
}

void destroyTMHNodeInstance ( TMHNode* const node ) {
	destroyTMHArcListInstance(node->successors);
	memFree(node);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}
