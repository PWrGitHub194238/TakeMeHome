/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKQS.h
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
 * DKQS.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKQS_H_
#define DKQS_H_

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

typedef struct TMH_DKQS {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKQS;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKQS* createTMHDKQSInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDKQSInstance ( TMH_DKQS* const instance, bool withConfig );

void runDKQS( TMH_DKQS* const instance );

void runDKQS_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKQS_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* DKQS_H_ */
