/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHAlgorithmHelper.c
 * @author tomasz
 * @date 6 wrz 2014
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

#include "../../Headers/Helpers/TMHAlgorithmHelper.h"		/* TMHGraph, TMHNode, AlgorithmAbbreviation,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 bool, NULL */

#include "../../Headers/TMHLogger.h"						/* warn() */
#include "../../Headers/Helpers/TMHErrors.h"				/* warn_TMHAlgorithmHelper_negativeCycleInGraphTopologicalOrder */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHAlgorithmHelper";

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

TMHNodeIdx* getTopologicalOrder( TMHNode** nodeArray, const TMHNodeIdx nodeArraySize ) {
	TMHNodeIdx i;
	TMHArcList* adjacencyList;
	TMHNode* currentNode;
	TMHNodeIdx toNodeID;
	TMHNodeIdx orderCounter = 1;
	TMHNodeDLListWrapper* nodeList = createTMHNodeDLListInstance();
	TMHNodeIdx* successorCountArray = memCalloc(nodeArraySize+1,sizeof(TMHNodeIdx));
	TMHNodeIdx* topologicalIndexOrder = memMalloc(nodeArraySize+1,sizeof(TMHNodeIdx));

	i = nodeArraySize;

	for ( ; i > 0; i-- ) {	/*  branie kazdego node'a i dodawanie jego nastepnikom liczby lukow wejsciowych */
		adjacencyList = nodeArray[i]->successors;
		while ( adjacencyList != NULL ) {
			successorCountArray[adjacencyList->arc->successor->nodeID] += 1;
			adjacencyList = adjacencyList->nextElement;
		}
	}

	i = nodeArraySize;

	for ( ; i > 0; i-- ) {	/* wrzucanie na liste nodow, ktore sa startowe, bez lukow wchodzacych */
		if ( successorCountArray[i] == 0 ) {
			pushLastTMHNodeDLList(nodeList->tail,nodeArray[i]);
		}
	}

	i = nodeArraySize;

	while ( (currentNode = popTMHNodeDLList(nodeList->head)) != NULL ) {
		adjacencyList = currentNode->successors;
		while ( adjacencyList != NULL ) {
			toNodeID = adjacencyList->arc->successor->nodeID;
			successorCountArray[toNodeID] -= 1; /* Jesli odwiedzono lukiem node to "usun" prowadzacy do niego luk */
			if ( successorCountArray[toNodeID] == 0 ) {	/* Jesli do luku nie prowadzi juz wezel to ustaw w jakiej kolejnosci zostal wyzerowany z lukow */
				successorCountArray[toNodeID] = orderCounter;
				orderCounter += 1;
				pushLastTMHNodeDLList(nodeList->tail,nodeArray[toNodeID]);
			}
			adjacencyList = adjacencyList->nextElement;
		}
	}

	i = nodeArraySize;

	for ( ; i > 0; i-- ) {
		if ( successorCountArray[i] > 0 ) {
			warn(MODULE_NAME,warn_TMHAlgorithmHelper_negativeCycleInGraphTopologicalOrder);
			return NULL;
		}
	}

	i = nodeArraySize;

	for ( ; i > 0; i-- ) {
		topologicalIndexOrder[successorCountArray[i]] = i;	/* indeksy sCA: nodeID; wartosci: kolejnosc odwiedzen*/
	}

	topologicalIndexOrder[i] = 0;

	return topologicalIndexOrder;
}
