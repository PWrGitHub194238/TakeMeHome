/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHArcList.h
 * @author tomasz
 * @date 24 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHArcList.h
 *
 *  Created on: 24 sie 2014
 *      Author: tomasz
 */

#ifndef TMHARCLIST_H_
#define TMHARCLIST_H_

/*
 * Includes
 *
 */

#include "TMHArc.h"			/* TMHArc */

/*
 * Typedefs
 *
 */

typedef struct TMHArcList {
	TMHArc*	arc;
	struct TMHArcList* nextElement;
} TMHArcList;


/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHArcList* createTMHArcListInstance( TMHArc* const newArc );
void destroyTMHArcListInstance ( TMHArcList* const instance );
TMHArcList* pushTMHArcList ( TMHArcList* const arcListBegin, TMHArc* const newArc );

#endif /* TMHARCLIST_H_ */
