/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKQ.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Naive Implementation
 * czyli z tablic� jako kolejka
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * DKQ.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKQ_H_
#define DKQ_H_

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

typedef struct TMH_DKQ {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKQ;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKQ* createTMHDKQInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDKQInstance ( TMH_DKQ* const instance, bool withConfig );

void runDKQ( TMH_DKQ* const instance );

void runDKQ_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKQ_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* DKQ_H_ */
