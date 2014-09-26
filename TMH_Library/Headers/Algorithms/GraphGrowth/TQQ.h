/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TQQ.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Graph Growth -- TQQe
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TQQ.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef TQQ_H_
#define TQQ_H_

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

typedef struct TMH_TQQ {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_TQQ;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_TQQ* createTMHTQQInstance( TMHGraph* const graphData, TMHConfig* configuration, bool checkConfig );
void destroyTMHTQQInstance ( TMH_TQQ* const instance );

void runTQQ( TMH_TQQ* const instance );

void runTQQ_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runTQQ_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* TQQ_H_ */
