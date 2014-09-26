/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeDLList.c
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

#include "../../Headers/Structures/TMHNodeDLList.h"	/* TMHNodeDLList, TMHNode, destroyTMHNodeDLListInstance() */

#include "../../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree(), NULL */

#include "../../Headers/TMHLogger.h"				/* warn(), debug() */
#include "../../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHNodeDLListWrapper";


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

TMHNodeDLListWrapper* createTMHNodeDLListInstance( ) {
	TMHNodeDLListWrapper* list = memMalloc(1,sizeof(TMHNodeDLListWrapper));
	TMHNodeDLList* head = memMalloc(1,sizeof(TMHNodeDLList));
	TMHNodeDLList* tail = memMalloc(1,sizeof(TMHNodeDLList));
	head->prev = NULL;
	head->data = NULL;
	head->next = tail;
	tail->prev = head;
	tail->data = NULL;
	tail->next = NULL;
	list->head = head;
	list->tail = tail;
	return list;
}

void destroyTMHNodeDLListInstance( TMHNodeDLListWrapper* instance, bool withData ) {
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
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void pushTMHNodeDLList( TMHNodeDLList* const listHead, TMHNode* newNode ) {
	TMHNodeDLList* newNodeElement = memMalloc(1,sizeof(TMHNodeDLList));
	newNodeElement->prev = listHead;
	newNodeElement->next = listHead->next;
	listHead->next->prev = newNodeElement;
	listHead->next = newNodeElement;
	newNodeElement->data = newNode;
	newNode->toUpperStruct = newNodeElement;
}

void pushLastTMHNodeDLList( TMHNodeDLList* const listTail, TMHNode* newNode ) {
	TMHNodeDLList* newNodeElement = memMalloc(1,sizeof(TMHNodeDLList));
	newNodeElement->next = listTail;
	newNodeElement->prev = listTail->prev;
	listTail->prev->next = newNodeElement;
	listTail->prev = newNodeElement;
	newNodeElement->data = newNode;
	newNode->toUpperStruct = newNodeElement;
}

TMHNode* popTMHNodeDLList( TMHNodeDLList* const listHead ) {
	TMHNodeDLList* returnedElement = listHead->next;
	TMHNode* returnedData = returnedElement->data;
	if ( returnedElement->next == NULL ) {
		warn(MODULE_NAME,warn_TMHNodeDLList_removeFromEmptyList);
		return NULL;
	}
	listHead->next = returnedElement->next;
	returnedElement->next->prev = listHead;
	memFree(returnedElement);
	return returnedData;
}

TMHNode* popLastTMHNodeDLList( TMHNodeDLList* const listTail ) {
	TMHNodeDLList* returnedElement = listTail->prev;
		TMHNode* returnedData = returnedElement->data;
		if ( returnedElement->next == NULL ) {
			warn(MODULE_NAME,warn_TMHNodeDLList_removeFromEmptyList);
			return NULL;
		}
		listTail->prev = returnedElement->prev;
		returnedElement->prev->next = listTail;
		memFree(returnedElement);
		return returnedData;
}

void repinTMHNodeDLList( TMHNodeDLList* const destinyList, TMHNode* const relocatedNode ) {
	TMHNodeDLList* const sourceList = relocatedNode->toUpperStruct;
	relocatedNode->toUpperStruct = destinyList;
	/* Usuwamy z listy*/
	sourceList->prev->next = sourceList->next;
	sourceList->next->prev = sourceList->prev;
	/* wstawiamy za headerem listy docelowej*/
	sourceList->next = destinyList->next;
	sourceList->prev = destinyList;
	/* aktualizujemy dowiazania listy docelowej*/
	destinyList->next->prev = sourceList;
	destinyList->next = sourceList;
}
