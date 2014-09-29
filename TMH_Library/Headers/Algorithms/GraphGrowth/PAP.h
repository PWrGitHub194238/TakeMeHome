/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file PAP.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Graph Growth -- Pape
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * PAP.h
 *
 *  Created on: 10 sie 2014
 *      Author: tomasz
 */

#ifndef PAP_H_
#define PAP_H_

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

typedef struct TMH_PAP {
	TMHGraph* graphData;
	TMHConfig* configuration;
} TMH_PAP;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMH_PAP* createTMHPAPInstance( TMHGraph* const graphData, TMHConfig* configuration );
void destroyTMHPAPInstance ( TMH_PAP* const instance, bool withConfig );

void runPAP( TMH_PAP* const instance );

void runPAP_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize );

void runPAP_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode );

/*
 * Inline definitions
 *
 */

#endif /* PAP_H_ */
