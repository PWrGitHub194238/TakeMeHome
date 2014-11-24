/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHGraph.c
 * @author tomasz
 * @date 15 sie 2014
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

#include "../../Headers/Structures/TMHGraph.h"		/* TMHNodeIdx, TMHNodeData, TMHArcCost, TMHGraph, TMHNode */
#include "../../Headers/Structures/TMHArc.h"		/* createTMHArcInstance */
#include "../../Headers/Helpers/TMHIOHelper.h"		/* getGraphData() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */
#include "../../Headers/Structures/TMHNode.h"		/* createTMHNodeInstance(),
														destroyTMHNodeInstance() */
#include "../../Headers/TMHLogger.h"				/* debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHGraph";


/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

/*
 * Definitions
 *
 */

TMHGraph* createTMHGraphInstance ( const TMHNodeIdx* const numOfNodes, const TMHNodeIdx* const numOfArcs ) {
	TMHNodeIdx i = *(numOfNodes);
	TMHGraph* newGraph = memMalloc(1,sizeof(TMHGraph));
	newGraph->numberOfNodes = i;
	newGraph->numberOfArcs = *(numOfArcs);
	newGraph->nodeArray = memMalloc(i+1,sizeof(TMHNode*));
	for ( ; i > 0; i-- ) {
		newGraph->nodeArray[i] = createTMHNodeInstance(i);
	}
	newGraph->nodeArray[i] = NULL;
	return newGraph;
}

void destroyTMHGraphInstance ( TMHGraph* const graph ) {
	TMHNodeIdx numberOfNodes = graph->numberOfNodes;
	for ( ; numberOfNodes > 0; numberOfNodes-- ) {
		destroyTMHNodeInstance(graph->nodeArray[numberOfNodes]);
	}
	memFree(graph->nodeArray);
	memFree(graph);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void addArc ( TMHNode* const fromNode, TMHNode* const toNode, const TMHArcCost* const distanceLabel ) {
	fromNode->successors = pushTMHArcList(fromNode->successors,
			createTMHArcInstance(toNode,distanceLabel));
}
