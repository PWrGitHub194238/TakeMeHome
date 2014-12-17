/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeDoubleQueue.c
 * @author tomasz
 * @date 24 sie 2014
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

#include "../../Headers/Structures/TMHNodeDoubleQueue.h"	/* TMHNodeDLList, TMHNode,
															destroyTMHNodeDoubleQueueInstance() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* warn(), debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeDoubleQueue";


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

TMHNodeDoubleQueue* createTMHNodeDoubleQueueInstance() {
	TMHNodeDoubleQueue* queue = memMalloc(1,sizeof(TMHNodeDoubleQueue));
	TMHNodeDLList* head = memMalloc(1,sizeof(TMHNodeDLList));
	TMHNodeDLList* tailLeft = memMalloc(1,sizeof(TMHNodeDLList));
	TMHNodeDLList* tailRight = memMalloc(1,sizeof(TMHNodeDLList));
	head->prev = NULL;
	head->data = NULL;
	head->next = tailLeft;
	tailLeft->prev = head;
	tailLeft->data = NULL;
	tailLeft->next = tailRight;
	tailRight->prev = tailLeft;
	tailRight->data = NULL;
	tailRight->next = NULL;

	queue->head = head;
	queue->tailLeft = tailLeft;
	queue->tailRight = tailRight;
	return queue;
}

void destroyTMHNodeDoubleQueueInstance( TMHNodeDoubleQueue* instance, bool withData ) {
	TMHNodeDLList* temp;
	TMHNodeDLList* head = instance->head;
	while ( head != NULL ) {
		temp = head->next;
		if (withData) {
			destroyTMHNodeInstance(head->data);
		}
		if (head->data != NULL) {
			head->data->toUpperStruct = NULL;
		}
		memFree(head);
		head = temp;
	}
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void pushLastTMHNodeDoubleQueue( TMHNodeDoubleQueue* const queue, TMHNode* newNode ) {
	TMHNodeDLList* newNodeElement;
	TMHNodeDLList* tail;
	if ( newNode->toUpperStruct == NULL ) {
		newNodeElement = memMalloc(1,sizeof(TMHNodeDLList));
		tail = ((newNode->distanceLabel == distanceLabelInfinity) ? queue->tailRight : queue->tailLeft);
		tail->prev->next = newNodeElement;
		newNodeElement->prev = tail->prev;
		tail->prev = newNodeElement;
		newNodeElement->next = tail;

		newNodeElement->data = newNode;
		newNode->toUpperStruct = newNodeElement;
	} else {
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHNodeDoubleQueue_alreadyInQueue,newNode->nodeID,newNode->distanceLabel);
		}
	}
}

TMHNode* popTMHNodeDoubleQueue( TMHNodeDoubleQueue* const queue ) {
	TMHNodeDLList* returnedElement = queue->head->next;
	TMHNode* returnedData;
	if ( returnedElement->next == queue->tailRight ) {	// na po headerze tylko LT (next) i RT (next->next)
		if (isWarnLogEnabled()) {
			warn(MODULE_NAME,warn_TMHNodeDoubleQueue_removeFromEmptyQueue);
		}
		return NULL;
	}
	returnedData = returnedElement->data;

	returnedElement->next->prev = returnedElement->prev;
	returnedElement->prev->next = returnedElement->next;
	memFree(returnedElement);
	return returnedData;
}
