/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKFB.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Heap -- Fibonacci
 *
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKFB.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKFB_H_
#define DKFB_H_

/*
 * Includes
 *
 */

#include "../../../Structures/TMHGraph.h"	/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"				/* TMHConfig, TMHNodeIdx, bool */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKFB {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKFB;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKFB* createTMHDKFBInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDKFBInstance ( TMH_DKFB* const instance, bool withConfig );

void runDKFB( TMH_DKFB* const instance );

void runDKFB_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKFB_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */


#endif /* DKFB_H_ */
