/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSLList.c
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

#include "../../Headers/Structures/TMHNodeSLList.h"	/* TMHNodeSLList, TMHNode, destroyTMHNodeSLListInstance() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* warn(), debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeSLListWrapper";


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

TMHNodeSLListWrapper* createTMHNodeSLListInstance( ) {
	TMHNodeSLListWrapper* list = memMalloc(1,sizeof(TMHNodeSLListWrapper));
	TMHNodeSLList* head = memMalloc(1,sizeof(TMHNodeSLList));
	head->data = NULL;
	head->next = NULL;
	list->head = head;
	return list;
}

void destroyTMHNodeSLListInstance( TMHNodeSLListWrapper* instance, bool withData ) {
	TMHNodeSLList* temp;
	TMHNodeSLList* head = instance->head;
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

void pushTMHNodeSLList( TMHNodeSLList* const listHead, TMHNode* newNode ) {
	TMHNodeSLList* newNodeElement = memMalloc(1,sizeof(TMHNodeSLList));
	newNodeElement->next = listHead->next;
	listHead->next = newNodeElement;
	newNodeElement->data = newNode;
	newNode->toUpperStruct = newNodeElement;
}

TMHNode* popTMHNodeSLList( TMHNodeSLList* const listHead ) {
	TMHNodeSLList* returnedElement = listHead->next;
	TMHNode* returnedData;
	if ( returnedElement == NULL ) {
		if (isWarnLogEnabled()) {
			warn(MODULE_NAME,warn_TMHNodeSLList_removeFromEmptyList);
		}
		return NULL;
	}
	returnedData = returnedElement->data;
	listHead->next = returnedElement->next;
	memFree(returnedElement);
	returnedData->toUpperStruct = NULL;
	return returnedData;
}

TMHNode* popMinTMHNodeSLList( TMHNodeSLListWrapper* const list ) {
	TMHNodeSLList* listHead = list->head;
	TMHNodeSLList* nextElement = listHead->next;
	TMHNodeSLList* currentElement;
	TMHNodeSLList* returnedElement;
	TMHNode* returnedData;
	TMHNodeData minDistance = distanceLabelInfinity;
	if (nextElement == NULL ) {
		if (isWarnLogEnabled()) {
			warn(MODULE_NAME,warn_TMHNodeSLList_removeFromEmptyList);
		}
		return NULL;
	} else if ( nextElement->next == NULL ) {
		returnedData = nextElement->data;
		listHead->next = NULL;
		memFree(nextElement);
		return returnedData;
	}
	/* Pierwszy */
	if ( nextElement->data->distanceLabel < minDistance ) {
		currentElement = listHead;
		minDistance = nextElement->data->distanceLabel;
		returnedElement = nextElement;
	}
	do {
		if ( nextElement->next->data->distanceLabel < minDistance ) {
			currentElement = nextElement;
			nextElement = nextElement->next;
			minDistance = nextElement->data->distanceLabel;
			returnedElement = nextElement;
		} else {
			nextElement = nextElement->next;
		}
	} while( nextElement->next != NULL);

	returnedData = returnedElement->data;
	currentElement->next = returnedElement->next;
	memFree(returnedElement);
	returnedData->toUpperStruct = NULL;
	return returnedData;
}
