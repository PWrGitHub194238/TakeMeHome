/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHArc.c
 * @author tomasz
 * @date 17 sie 2014
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

#include "../../Headers/Structures/TMHArc.h"		/* TMHArc, TMHNodeIdx, TMHArcCost */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), freeMem(), NULL */

#include "../../Headers/TMHLogger.h"				/* debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHArc";


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

TMHArc* createTMHArcInstance( struct TMHNode* const successor, const TMHArcCost* const distance ) {
	TMHArc* newArc = memMalloc(1,sizeof(TMHArc));
	newArc->distance = *(distance);
	newArc->successor = successor;
	return newArc;
}

void destroyTMHArcInstance ( TMHArc* const arc ) {
	memFree(arc);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}
