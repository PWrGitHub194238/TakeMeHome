/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHFibNode.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHFibNode.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHFIBNODE_H_
#define TMHFIBNODE_H_

/*
 * Includes
 *
 */

#include <stdbool.h>			/* bool */

#include "../../TMHNode.h"		/* TMHNode */
#include "../../../TMH.h"		/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

/**
 *  Jako, ze kazdy node w strukturze ma linki do sasiadow, do ojca
 *  i do ktoregokolwiek noda z listy dzieci (lista zapetla sie)
 *  to nie ma sensu tworzyc osobnej struktury dla samej listy takich wezlow, tylko bez prev i next.
 */
typedef struct TMHFibNode {
	TMHNode* data;
	struct TMHFibNode* parent;
	struct TMHFibNode* childList;
	TMHNodeIdx degree;
	bool mark;
	struct TMHFibNode* prev;
	struct TMHFibNode* next;
} TMHFibNode;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHFibNode* createTMHFibNodeInstance( TMHNode* const node );

void destroyTMHFibNodeInstance( TMHFibNode* const instance, bool withData );

/**
 * laczy dwie listy nodow i zwraca wskaznik do tego, ktory spelnia wlasnosc minNode.
 * Kaskadowo kazda z list nodeList1 i nodeList2 wskazuje na taki element.
 */
TMHFibNode* concatTMHFibNode( TMHFibNode* const nodeList1, TMHFibNode* const nodeList2 );

#endif /* TMHFIBNODE_H_ */
