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
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
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

void priorityPushTMHNodeDLList( TMHNodeDLList* const listHead, TMHNode* newNode ) {
	TMHNodeDLList* newNodeElement = memMalloc(1,sizeof(TMHNodeDLList));
	TMHNodeDLList* targetElement = listHead->next;
	TMHNodeData newNodeLabel = newNode->distanceLabel;

	/* Przesuwamy w dół - data == null mają z założenia tylko header i tail*/
	while ( targetElement->data != NULL && targetElement->data->distanceLabel > newNodeLabel ) {
		targetElement = targetElement->next;
	}

	/* Wstawiamy przed wybranym*/
	newNodeElement->prev = targetElement->prev;
	newNodeElement->next = targetElement;
	targetElement->prev->next = newNodeElement;
	targetElement->prev = newNodeElement;

	newNodeElement->data = newNode;
	newNode->toUpperStruct = newNodeElement;
}

TMHNode* popTMHNodeDLList( TMHNodeDLList* const listHead ) {
	TMHNodeDLList* returnedElement = listHead->next;
	TMHNode* returnedData = returnedElement->data;
	if ( returnedElement->next == NULL ) {
		if (isWarnLogEnabled()) {
			warn(MODULE_NAME,warn_TMHNodeDLList_removeFromEmptyList);
		}
		return NULL;
	}
	listHead->next = returnedElement->next;
	returnedElement->next->prev = listHead;
	memFree(returnedElement);
	returnedData->toUpperStruct = NULL;
	return returnedData;
}

TMHNode* popLastTMHNodeDLList( TMHNodeDLList* const listTail ) {
	TMHNodeDLList* returnedElement = listTail->prev;
		TMHNode* returnedData;
		if ( returnedElement->prev == NULL ) {
			if (isWarnLogEnabled()) {
				warn(MODULE_NAME,warn_TMHNodeDLList_removeFromEmptyList);
			}
			return NULL;
		}
		returnedData = returnedElement->data;
		listTail->prev = returnedElement->prev;
		returnedElement->prev->next = listTail;
		memFree(returnedElement);
		returnedData->toUpperStruct = NULL;
		return returnedData;
}

void repinTMHNodeDLList( TMHNodeDLList* const destinyListHead, TMHNode* const relocatedNode ) {
	TMHNodeDLList* const sourceListElement = relocatedNode->toUpperStruct;

	/* Usuwamy z listy*/
	sourceListElement->prev->next = sourceListElement->next;
	sourceListElement->next->prev = sourceListElement->prev;
	/* podpinamy wskaźniki do listy docelowej*/
	sourceListElement->next = destinyListHead->next;
	sourceListElement->prev = destinyListHead;
	/* wstawiamy do listy docelowej*/
	destinyListHead->next->prev = sourceListElement;
	destinyListHead->next = sourceListElement;
}

/** Wrzuca na górę i spycha na dół, tak aby z najniższym labelem było na końcu */
void priorityRepinTMHNodeDLList( TMHNodeDLList* const destinyListHead, TMHNode* const relocatedNode ) {
	TMHNodeDLList* const sourceListElement = relocatedNode->toUpperStruct;
	TMHNodeData relocatedNodeLabel = relocatedNode->distanceLabel;
	TMHNodeDLList* destinyListElement;

	/* Usuwamy z listy*/
	sourceListElement->prev->next = sourceListElement->next;
	sourceListElement->next->prev = sourceListElement->prev;

	/* Pierwszy element po odpięciu z listy relokowanego (gdy był np. qw tej samej liście)*/
	destinyListElement = destinyListHead->next;

	/* Pzzesuwamy w dół*/
	while ( destinyListElement->data != NULL && destinyListElement->data->distanceLabel > relocatedNodeLabel ) {
		destinyListElement = destinyListElement->next;
	}

	/* Wstawiamy przed wybranym*/
	/* podpinamy wskaźniki do listy docelowej*/
	sourceListElement->prev = destinyListElement->prev;
	sourceListElement->next = destinyListElement;
	/* wstawiamy do listy docelowej*/
	destinyListElement->prev->next = sourceListElement;
	destinyListElement->prev = sourceListElement;
}

TMHNode* popMinTMHNodeDLList( TMHNodeDLListWrapper* const list ) {
	TMHNodeDLList* listHead = list->head;
	TMHNodeDLList* listTail = list->tail;
	TMHNodeDLList* nextElement = listHead->next;
	TMHNodeDLList* returnedElement = NULL;
	TMHNode* returnedData;
	TMHNodeData minDistance = distanceLabelInfinity;
	if (nextElement == listTail ) {
		if (isWarnLogEnabled()) {
			warn(MODULE_NAME,warn_TMHNodeDLList_removeFromEmptyList);
		}
		return NULL;
	}
	do {
		if ( nextElement->data->distanceLabel < minDistance ) {
			minDistance = nextElement->data->distanceLabel;
			returnedElement = nextElement;
		}
	} while((nextElement = nextElement->next) != listTail);

	returnedData = returnedElement->data;

	returnedElement->next->prev = returnedElement->prev;
	returnedElement->prev->next = returnedElement->next;
	memFree(returnedElement);
	returnedData->toUpperStruct = NULL;
	return returnedData;
}
