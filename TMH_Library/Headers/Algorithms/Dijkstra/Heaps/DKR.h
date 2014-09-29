/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKR.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Heap -- R--Heap
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKR.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKR_H_
#define DKR_H_

/*
 * Includes
 *
 */

#include "../../../Structures/TMHGraph.h"		/* TMHGraph, TMHNode */
#include "../../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMH_DKR {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKR;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKR* createTMHDKRInstance( TMHGraph* const graphData, TMHConfig* configuration );
void destroyTMHDKRInstance ( TMH_DKR* const instance, bool withConfig );

void runDKR( TMH_DKR* const instance );

void runDKR_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKR_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* DKR_H_ */
