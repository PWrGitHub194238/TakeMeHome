/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHGraph.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHGraph.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHGRAPH_H_
#define TMHGRAPH_H_

/*
 * Includes
 *
 */

#include "../TMH.h"				/* TMHNodeIdx, TMHNodeData, TMHArcCost */
#include "TMHNode.h"			/* TMHNode */

/*
 * Typedefs
 *
 */

/**
 * @brief Basic type of graph structure.
 *
 * @details It holds only nodes as all arcs that leads from node <tt><b>i</b></tt>
 * to whatever node are stored in a data structure of that node <tt><b>i</b></tt>.
 *
 */
typedef struct TMHGraph {
	TMHNodeIdx numberOfNodes;
	TMHNodeIdx numberOfArcs;
	TMHArcCost maxArcCost;
	TMHNode** nodeArray;	/*!<  */
} TMHGraph;


/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHGraph* loadTMHGraphInstance ( const char* const filename );


/** Tworzy graf, tworzy numOfNodes nodów w tablicy.
 *
 * @param numOfNodes
 * @return
 */
TMHGraph* createTMHGraphInstance ( const TMHNodeIdx* const numOfNodes, const TMHNodeIdx* const numOfArcs );

/** Niszczy wszystkie węzły i graf na końcu
 *
 * @param graph
 */
void destroyTMHGraphInstance ( TMHGraph* const graph );

/** dokleja na początek listy węzła łuk
 *
 * @param graph
 * @param fromNodeID
 * @param toNodeID
 * @param distanceLabel
 */
void addArc ( TMHGraph* const graph, const TMHNodeIdx* const fromNodeID, const TMHNodeIdx* const toNodeID, const TMHArcCost* const distanceLabel );

#endif /* TMHGRAPH_H_ */
