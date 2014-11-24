/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeDLList.h
 * @author tomasz
 * @date 24 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNodeDLList.h
 *
 *  Created on: 24 sie 2014
 *      Author: tomasz
 */

#ifndef TMHNODEDLLIST_H_
#define TMHNODEDLLIST_H_

/*
 * Includes
 *
 */

#include <stdbool.h>			/* bool */

#include "TMHNode.h"			/* TMHNode */

/*
 * Typedefs
 *
 */

typedef struct TMHNodeDLList {
	TMHNode* data;
	struct TMHNodeDLList* next;
	struct TMHNodeDLList* prev;
} TMHNodeDLList;

typedef struct TMHNodeDLListWrapper {
	struct TMHNodeDLList* head;
	struct TMHNodeDLList* list;
	struct TMHNodeDLList* tail;
} TMHNodeDLListWrapper;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeDLListWrapper* createTMHNodeDLListInstance();
void destroyTMHNodeDLListInstance( TMHNodeDLListWrapper* instance, bool withData );

/**
 * Wrzuca za headerem nowy element + dopina wska�nik w w�le do jego wzbogaconej struktury
 */
void pushTMHNodeDLList( TMHNodeDLList* const nodeList, TMHNode* newNode );
void priorityPushTMHNodeDLList( TMHNodeDLList* const nodeList, TMHNode* newNode );
void pushLastTMHNodeDLList( TMHNodeDLList* const listTail, TMHNode* newNode );
TMHNode* popTMHNodeDLList( TMHNodeDLList* const listHead );
TMHNode* popLastTMHNodeDLList( TMHNodeDLList* const listTail );
void repinTMHNodeDLList( TMHNodeDLList* const destinylistHead, TMHNode* const relocatedNode );
void priorityRepinTMHNodeDLList( TMHNodeDLList* const destinylistHead, TMHNode* const relocatedNode );

TMHNode* popMinTMHNodeDLList( TMHNodeDLListWrapper* const list );

#endif /* TMHNODEDLLIST_H_ */
