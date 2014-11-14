/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHGraphRebuilder.c
 * @author tomasz
 * @date 28 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../Headers/Helpers/TMHGraphRebuilder.h"			/* GraphOrder, TMHGraph */

/*
 * Constants
 *
 */



/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static void addTopologicalStructureToAdjacencyListGraph( TMHGraph* const sourceGraph );

/*
 * Definitions
 *
 */

void rebuildAdjacencyListGraph( const GraphOrder graphOrder, TMHGraph* const sourceGraph ) {
	switch (graphOrder) {
		case TOPOLOGIC:
			addTopologicalStructureToAdjacencyListGraph(sourceGraph);
			break;
		default:
			break;
	}
}

TMHNode** copyArray( const TMHNode** const sourceArray, TMHNodeIdx numberOfNodes ) {
	TMHNode** copyArray = memMalloc(numberOfNodes+1,sizeof(TMHNode*));

	for ( ; numberOfNodes > 0; numberOfNodes-- ) {
		copyArray[numberOfNodes] = sourceArray[numberOfNodes];
	}
	copyArray[numberOfNodes] = sourceArray[numberOfNodes];
	return copyArray;
}

static void addTopologicalStructureToAdjacencyListGraph( TMHGraph* const sourceGraph ) {
	TMHNodeIdx numberOfNodes = sourceGraph->numberOfNodes;

}

