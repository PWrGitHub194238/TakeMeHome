/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file GR2.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Topological Ordering -- Distance Updates
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * GR2.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef GR2_H_
#define GR2_H_

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

typedef struct TMH_GR2 {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_GR2;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_GR2* createTMHGR2Instance( TMHGraph* const graphData, TMHConfig* configuration );
void destroyTMHGR2Instance ( TMH_GR2* const instance, bool withConfig );

void runGR2( TMH_GR2* const instance );

void runGR2_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runGR2_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* GR2_H_ */
