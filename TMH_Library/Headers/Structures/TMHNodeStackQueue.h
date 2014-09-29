/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeStackQueue.h
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

#ifndef TMHNODESTACKQUEUE_H_
#define TMHNODESTACKQUEUE_H_

/*
 * Includes
 *
 */

#include <stdbool.h>			/* bool */

#include "TMHNodeStack.h"		/* TMHNodeStack */
#include "TMHNodeDLList.h"		/* TMHNodeDLListWrapper, TMHNode */

/*
 * Typedefs
 *
 */

typedef struct TMHNodeStackQueue {
	struct TMHNodeStack* head;
	struct TMHNodeDLListWrapper* list;
} TMHNodeStackQueue;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeStackQueue* createTMHNodeStackQueueInstance();
void destroyTMHNodeStackQueueInstance( TMHNodeStackQueue* instance, bool withData );
void pushTMHNodeStackQueue( TMHNodeStackQueue* const queue, TMHNode* newNode );
TMHNode* popTMHNodeStackQueue( TMHNodeStackQueue* const queue );

#endif /* TMHNODESTACKQUEUE_H_ */
