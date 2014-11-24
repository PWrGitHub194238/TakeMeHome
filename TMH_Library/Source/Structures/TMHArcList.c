/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHArcList.c
 * @author tomasz
 * @date 24 sie 2014
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

#include "../../Headers/Structures/TMHArcList.h"	/* TMHArcList, TMHArc, destroyTMHArcInstance() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHArcList";


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

TMHArcList* createTMHArcListInstance( struct TMHArc* const newArc ) {
	return pushTMHArcList(NULL,newArc);
}

void destroyTMHArcListInstance ( TMHArcList* instance ) {
	TMHArcList* temp = instance;
	while ( temp != NULL ) {
		instance = instance->nextElement;
		destroyTMHArcInstance(temp->arc);
		memFree(temp);
		temp = instance;
	}
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

TMHArcList* pushTMHArcList ( TMHArcList* const arcListBegin, struct TMHArc* const newArc ) {
	TMHArcList* newArcElement = memMalloc(1,sizeof(TMHArcList));
	newArcElement->arc = newArc;
	newArcElement->nextElement = arcListBegin;
	return newArcElement;
}
