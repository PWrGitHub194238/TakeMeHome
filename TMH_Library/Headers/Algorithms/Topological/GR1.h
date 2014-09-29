/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file GR1.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Topological Ordering -- Basic
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * GR1.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef GR1_H_
#define GR1_H_

/*
 * Includes
 *
 */

#include "../../Structures/TMHGraph.h"			/* TMHGraph, TMHNode */
#include "../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMH_GR1 {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_GR1;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_GR1* createTMHGR1Instance( TMHGraph* const graphData, TMHConfig* configuration );
void destroyTMHGR1Instance ( TMH_GR1* const instance, bool withConfig );

void runGR1( TMH_GR1* const instance );

void runGR1_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runGR1_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* GR1_H_ */
