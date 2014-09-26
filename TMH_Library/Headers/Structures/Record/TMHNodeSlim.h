/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSlim.h
 * @author tomasz
 * @date 14 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNodeSlim.h
 *
 *  Created on: 14 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHNODESLIM_H_
#define TMHNODESLIM_H_

/*
 * Includes
 *
 */

#include "../../TMH.h"					/* TMHNodeIdx, TMHNodeData */
#include "../../Structures/TMHNode.h"	/* TMHNode */

/*
 * Typedefs
 *
 */

typedef struct TMHNodeSlim {
	TMHNodeIdx nodeID;
	TMHArcCost distanceLabel;
} TMHNodeSlim;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeSlim* createTMHNodeSlimInstance( const TMHNode* const node );
void destroyTMHNodeSlimInstance ( TMHNodeSlim* const instance );

#endif /* TMHNODESLIM_H_ */
