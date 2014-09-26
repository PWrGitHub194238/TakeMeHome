/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file BFM.h
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
 * BFM.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef BFM_H_
#define BFM_H_

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

typedef struct TMH_BFM {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_BFM;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_BFM* createTMHBFMInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig );
void destroyTMHBFMInstance ( TMH_BFM* const instance );

void runBFM( TMH_BFM* const instance );

void runBFM_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runBFM_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

#endif /* BFM_H_ */
