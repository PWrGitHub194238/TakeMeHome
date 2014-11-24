/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSLList.h
 * @author tomasz
 * @date 24 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNodeSLList.h
 *
 *  Created on: 24 sie 2014
 *      Author: tomasz
 */

#ifndef TMHNODESLLIST_H_
#define TMHNODESLLIST_H_

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

typedef struct TMHNodeSLList {
	TMHNode* data;
	struct TMHNodeSLList* next;
} TMHNodeSLList;

typedef struct TMHNodeSLListWrapper {
	struct TMHNodeSLList* head;
} TMHNodeSLListWrapper;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeSLListWrapper* createTMHNodeSLListInstance();
void destroyTMHNodeSLListInstance( TMHNodeSLListWrapper* instance, bool withData );

/**
 * Wrzuca za headerem nowy element + dopina wska�nik w w�le do jego wzbogaconej struktury
 */
void pushTMHNodeSLList( TMHNodeSLList* const nodeList, TMHNode* newNode );
void pushLastTMHNodeSLList( TMHNodeSLList* const listTail, TMHNode* newNode );
TMHNode* popTMHNodeSLList( TMHNodeSLList* const listHead );
TMHNode* popLastTMHNodeSLList( TMHNodeSLList* const listTail );
void repinTMHNodeSLList( TMHNodeSLList* const destinyList, TMHNode* const relocatedNode );
TMHNode* popMinTMHNodeSLList( TMHNodeSLListWrapper* const list );

#endif /* TMHNODESLLIST_H_ */
