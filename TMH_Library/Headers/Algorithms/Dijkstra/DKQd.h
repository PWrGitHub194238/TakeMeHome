/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKQD.h
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
 * DKQD.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKQD_H_
#define DKQD_H_

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

typedef struct TMH_DKQD {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKQD;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKQD* createTMHDKQDInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHDKQDInstance ( TMH_DKQD* const instance, bool withConfig );

void runDKQD( TMH_DKQD* const instance );

void runDKQD_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKQD_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* DKQD_H_ */
