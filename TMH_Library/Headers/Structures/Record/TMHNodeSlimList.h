/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeSlimList.h
 * @author tomasz
 * @date 14 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNodeSlimList.h
 *
 *  Created on: 14 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHNODESLIMLIST_H_
#define TMHNODESLIMLIST_H_

/*
 * Includes
 *
 */

#include "TMHNodeSlim.h"			/* TMHNodeSlim */

/*
 * Typedefs
 *
 */

typedef struct TMHNodeSlimList {
	TMHNodeSlim* nodeInfo;
	struct TMHNodeSlimList* nextElement;
} TMHNodeSlimList;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeSlimList* createTMHNodeSlimListInstance( TMHNodeSlim* const newNodeInfo );
void destroyTMHNodeSlimListInstance ( TMHNodeSlimList* const instance );

/** Wstawia na początek listy i zwraca wskaźnik do nowego elementu
 *
 * @param slimListBegin
 * @param newNodeInfo
 * @return
 */
TMHNodeSlimList* pushTMHNodeSlimList ( TMHNodeSlimList* const slimListBegin, TMHNodeSlim* const newNodeInfo );

#endif /* TMHNODESLIMLIST_H_ */
