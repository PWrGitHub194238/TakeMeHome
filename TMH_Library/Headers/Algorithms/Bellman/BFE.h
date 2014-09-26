/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file BFE.h
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
 * BFE.h http://siam.omnibooksonline.com/2012ANALCO/data/papers/005.pdf
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef BFE_H_
#define BFE_H_

/*
 * Includes
 *
 */

#include "../../Structures/TMHGraph.h"			/* TMHGraph */
#include "../../TMHConfig.h"					/* TMHConfig, TMHNodeIdx, bool */

/*
 * Typedefs
 *
 */

typedef struct TMH_BFE {
	TMHGraph* graphData;
	TMHConfig* configuration;
	bool* hasNodeChangeArray;
} TMH_BFE;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_BFE* createTMHBFEInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig );
void destroyTMHBFEInstance ( TMH_BFE* const instance );

void runBFE( TMH_BFE* const instance );

void runBFE_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runBFE_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

#endif /* BFE_H_ */
