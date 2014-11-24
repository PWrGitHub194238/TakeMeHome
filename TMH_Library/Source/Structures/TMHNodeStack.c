/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeStack.c
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

#include "../../Headers/Structures/TMHNodeStack.h"	/* TMHNodeStack, TMHNode, destroyTMHNodeInstance() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* warn(), debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeStack";


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

TMHNodeStack* createTMHNodeStackInstance() {
	TMHNodeStack* stack = memMalloc(1,sizeof(TMHNodeStack));
	stack->data = NULL;
	stack->next = NULL;
	return stack;
}

void destroyTMHNodeStackInstance( TMHNodeStack* instance, bool withData ) {
	TMHNodeStack* temp;
	while ( instance != NULL ) {
		temp = instance->next;
		if (withData) {
			destroyTMHNodeInstance(instance->data);
		}
		if (instance->data != NULL) {
			instance->data->toUpperStruct = NULL;
		}
		memFree(instance);
		instance = temp;
	}
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

void pushTMHNodeStack( TMHNodeStack** const stack, TMHNode* newNode ) {
	TMHNodeStack* newNodeElement = memMalloc(1,sizeof(TMHNodeStack));
	newNodeElement->next = *stack;
	*stack = newNodeElement;
	newNodeElement->data = newNode;
	newNode->toUpperStruct = newNodeElement;
}

TMHNode* popTMHNodeStack( TMHNodeStack** const stack ) {
	TMHNodeStack* nextElement;
	TMHNode* returnedData;
	if ( (*stack)->next == NULL ) {
		warn(MODULE_NAME,warn_TMHNodeStack_removeFromEmptyStack);
		return NULL;
	}
	nextElement = (*stack)->next;
	returnedData = (*stack)->data;
	memFree((*stack));
	*stack = nextElement;
	return returnedData;
}
