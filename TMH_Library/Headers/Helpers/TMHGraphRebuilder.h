/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHGraphRebuilder.h
 * @author tomasz
 * @date 28 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHGraphRebuilder.h
 *
 *  Created on: 28 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHGRAPHREBUILDER_H_
#define TMHGRAPHREBUILDER_H_

/*
 * Includes
 *
 */

#include "../TMHConfig.h"				/* GraphOrder */
#include "../Structures/TMHGraph.h"		/* TMHGraph */

/*
 * Typedefs
 *
 */



/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

void rebuildAdjacencyListGraph( const GraphOrder graphOrder, TMHGraph* const sourceGraph );
TMHNode** copyArray( const TMHNode** const sourceArray, TMHNodeIdx numberOfNodes );

#endif /* TMHGRAPHREBUILDER_H_ */
