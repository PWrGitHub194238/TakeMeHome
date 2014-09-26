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
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

TMHFibNode* concatTMHFibNode( TMHFibNode* const nodeList1, TMHFibNode* const nodeList2 ) {
	TMHFibNode* nextElement;
	if (nodeList1 == NULL) {
			return nodeList2;
	} else if (nodeList2 == NULL) {
			return nodeList1;
	} else {
		nextElement= nodeList1->next;
		nodeList2->next = nextElement;
		nextElement->prev = nodeList2;
		nodeList2->prev = nodeList1;
		nodeList1->next = nodeList2;
		return ((nodeList1->data->distanceLabel <= nodeList2->data->distanceLabel ) ? nodeList1 : nodeList2 );
	}
}
