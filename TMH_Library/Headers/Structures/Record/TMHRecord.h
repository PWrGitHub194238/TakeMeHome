/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHRecord.h
 * @author tomasz
 * @date 14 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHRecord.h
 *
 *  Created on: 14 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHRECORD_H_
#define TMHRECORD_H_

/*
 * Includes
 *
 */

#include "TMHNodeSlimList.h"			/* TMHNodeSlimList */
#include "../../TMH.h"					/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMHRecord {
	TMHNodeIdx sourceNodeID;
	TMHNodeIdx targetNodeID;
	TMHNodeSlimList* pathFromSource;
} TMHRecord;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHRecord* createTMHRecordInstance( const TMHNodeIdx sourceNodeID, const TMHNodeIdx targetNodeID, TMHNodeSlimList* const pathFromSource);
void destroyTMHRecordInstance ( TMHRecord* const instance );

#endif /* TMHRECORD_H_ */
