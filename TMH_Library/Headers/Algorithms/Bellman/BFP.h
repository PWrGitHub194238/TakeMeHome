/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file BFP.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Bellman-Ford-Moore
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * BFP.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef BFP_H_
#define BFP_H_

/*
 * Includes
 *
 */

#include "../../Structures/TMHGraph.h"			/* TMHGraph */
#include "../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMH_BFP {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_BFP;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_BFP* createTMHBFPInstance( TMHGraph* const graphData, TMHConfig* const configuration );
void destroyTMHBFPInstance ( TMH_BFP* const instance, bool withConfig );

void runBFP( TMH_BFP* const instance );

void runBFP_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runBFP_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

#endif /* BFP_H_ */
