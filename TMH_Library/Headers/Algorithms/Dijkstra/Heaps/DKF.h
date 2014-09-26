/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKF.h
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
 * DKF.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef DKF_H_
#define DKF_H_

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

typedef struct TMH_DKF {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_DKF;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_DKF* createTMHDKFInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig );
void destroyTMHDKFInstance ( TMH_DKF* const instance );

void runDKF( TMH_DKF* const instance );

void runDKF_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runDKF_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */


#endif /* DKF_H_ */
