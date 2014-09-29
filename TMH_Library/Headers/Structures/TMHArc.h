/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHArc.h
 * @author tomasz
 * @date 17 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHArc.h
 *
 *  Created on: 17 sie 2014
 *      Author: tomasz
 */

#ifndef TMHARC_H_
#define TMHARC_H_

/*
 * Includes
 *
 */

#include "TMHNode.h"/* TMHNode */
#include "../TMH.h"	/* TMHNodeData, TMHArcCost */

/*
 * Typedefs
 *
 */

/**
 * @brief Basic type for every arc within graph structure.
 *
 * @details Basic type for every arc within every graph structure that that will be passed
 * to any of the shortest-path algorithm that is implemented in this library.
 *
* It fully relies on the source node from which arc leads to the next one.
* Therefore it will not store any information about source node.
 */
typedef struct TMHArc {
	TMHArcCost distance; 	/*!< */
	struct TMHNode* successor; 	/*!< */
} TMHArc;


/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */


TMHArc* createTMHArcInstance( struct TMHNode* const successor, const TMHArcCost* const distance );
void destroyTMHArcInstance ( TMHArc* const arc );

#endif /* TMHARC_H_ */
