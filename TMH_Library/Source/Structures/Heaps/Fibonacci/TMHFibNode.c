/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHFibNode.c
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

#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibNode.h"	/* TMHFibNode, TMHNode, bool
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 destroyTMHNodeInstance() */

#include "../../../../Headers/Helpers/TMHAllocHelper.h"					/* memMalloc(), freeMem(), NULL */

#include "../../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHFibNode";


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

TMHFibNode* createTMHFibNodeInstance( TMHNode* const node ) {
	TMHFibNode* newNode = memMalloc(1,sizeof(TMHFibNode));
	newNode->childList = NULL;
	newNode->data = node;
	newNode->degree = 0;
	newNode->mark = false;
	newNode->parent = NULL;
	newNode->next = newNode;
	newNode->prev = newNode;
	node->toUpperStruct = newNode;
	return newNode;
}

void destroyTMHFibNodeInstance( TMHFibNode* const instance, bool withData ) {
	if (withData) {
		destroyTMHNodeInstance(instance->data);
	}
	if (instance->data) {
		instance->data->toUpperStruct = NULL;
	}
	error(MODULE_NAME,"Zdeallocotwanie node: %u (dL: %u, d: %u, m: %u).",instance->data->nodeID,instance->data->distanceLabel,instance->degree,instance->mark);

	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

/* Łączy dwie root listy i zwraca minimalny node z min. nodów 2 root list - łapanie, czy któraś lub czy obie są puste trzeba robić wyżej*/
TMHFibNode* concatTMHFibNode( TMHFibNode* const nodeList1, TMHFibNode* const nodeList2 ) {
	nodeList1->next->prev = nodeList2->prev;
	nodeList2->prev->next = nodeList1->next;
	nodeList1->next = nodeList2;
	nodeList2->prev = nodeList1;
	error(MODULE_NAME,"[concatTMHFibNode] połączono l1 (min: %u) z l2 (min: %u)",nodeList1->data->distanceLabel,nodeList2->data->distanceLabel);
	return ((nodeList1->data->distanceLabel <= nodeList2->data->distanceLabel ) ? nodeList1 : nodeList2 );
}
