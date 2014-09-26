/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNode.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNode.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHNODE_H_
#define TMHNODE_H_

/*
 * Includes
 *
 */

#include "../Structures/TMHNode.h"

#include "../TMH.h"						/* TMHNodeData */
#include "../Structures/TMHArcList.h"	/* TMHArcList */


/*
 * Typedefs
 *
 */


/**
 * @brief Basic type for every node within graph structure.
 *
 * @details Basic type for every node within every graph structure that that will be passed
 * to any of the shortest-path algorithm that is implemented in this library.
 */
typedef struct TMHNode {
	TMHNodeIdx nodeID;
	TMHNodeData distanceLabel; 		/*!< distanceLabel (<b><tt>d(i)</tt></b>) stores an upper bound
									on the shortest path distance from <tt>source node</tt>
									to <tt>i< node</tt>. If there is no connection between these two nodes
									then <tt>d(i)</tt> is set to infinity.
									@see distanceLabelInfinity. */
	struct TMHNode* predecessor; 	/*!< predecessor (<b><tt>p(i)</tt></b>) stores the pointer to node
									that immediately precedes node <tt>i</tt> in a graph structure.*/
	TMHArcList* successors;			/*!< List of nodes to which current node
									directly leads to (node's neighbors).
									In fact it is only a list of arcs that leads to them.*/
	void* toUpperStruct;			/*!< To work properly, almost every SP algorithm
									have to use slightly different kind of data structure
									that involves basic node structure. This field is used
									to point to these structures so two-way linkage is maintain.*/
} TMHNode;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

/**
 *
 * @param graph
 * @param id
 * @return
 *
 * @throw
 */
TMHNode* createTMHNodeInstance( const TMHNodeIdx nodeID );
void destroyTMHNodeInstance ( TMHNode* const node );



#endif /* TMHNODE_H_ */
