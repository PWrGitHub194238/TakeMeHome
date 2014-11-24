/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeStackQueue.c
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

#include "../../Headers/Structures/TMHNodeStackQueue.h"	/* TMHNodeStack, TMHNodeDLList, TMHNode,
														createTMHNodeDLListInstance(),
														destroyTMHNodeInstance(),
														destroyTMHNodeDLListInstance(),
														pushLastTMHNodeDLList(),
														pushTMHNodeStack(),

														*/

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* warn() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHNodeStackQueue_alreadyInQueue*/

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeStackQueue";


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

TMHNodeStackQueue* createTMHNodeStackQueueInstance() {
	TMHNodeStackQueue* queue = memMalloc(1,sizeof(TMHNodeStackQueue));
	TMHNodeDLListWrapper* list = createTMHNodeDLListInstance();
	TMHNodeStack* stack = createTMHNodeStackInstance();
	queue->head = stack;
	queue->list = list;
	return queue;
}

void destroyTMHNodeStackQueueInstance( TMHNodeStackQueue* instance, bool withData ) {
	TMHNodeStack* temp;
	TMHNodeStack* stack = instance->head;
	while ( stack != NULL ) {
		temp = stack->next;
		if (withData) {
			destroyTMHNodeInstance(stack->data);
		}
		if (stack->data != NULL) {
			stack->data->toUpperStruct = NULL;
		}
		memFree(stack);
		stack = temp;
	}
	destroyTMHNodeDLListInstance(instance->list,withData);
	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void pushTMHNodeStackQueue( TMHNodeStackQueue* const queue, TMHNode* newNode ) {
	if ( newNode->toUpperStruct == NULL ) {
		if ( newNode->distanceLabel == distanceLabelInfinity ) {	/* wstawiany pierwszy raz */
			pushLastTMHNodeDLList(queue->list->tail,newNode);
		} else {
			pushTMHNodeStack(&(queue->head),newNode);
		}
	} else {
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHNodeStackQueue_alreadyInQueue,newNode->nodeID,newNode->distanceLabel);
		}
	}
}

TMHNode* popTMHNodeStackQueue( TMHNodeStackQueue* const queue ) {
	TMHNodeStack* returnedElement = queue->head;
	TMHNodeStack* temp;
	TMHNode* returnedData;
	if ( returnedElement->next == NULL ) {
		returnedData = popTMHNodeDLList(queue->list->head);
	} else {
		returnedData = returnedElement->data;
		temp = returnedElement->next;
		memFree(returnedElement);
		queue->head = temp;
	}
	return returnedData;
}


