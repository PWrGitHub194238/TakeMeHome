/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeDoubleQueue.h
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

#ifndef TMHNODEDOUBLEQUEUE_H_
#define TMHNODEDOUBLEQUEUE_H_

/*
 * Includes
 *
 */

#include <stdbool.h>			/* bool */

#include "TMHNodeDLList.h"		/* TMHNodeDLList, TMHNode */

/*
 * Typedefs
 *
 */

typedef struct TMHNodeDoubleQueue {
	struct TMHNodeDLList* head;
	struct TMHNodeDLList* tailLeft;
	struct TMHNodeDLList* tailRight;
} TMHNodeDoubleQueue;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeDoubleQueue* createTMHNodeDoubleQueueInstance();
void destroyTMHNodeDoubleQueueInstance( TMHNodeDoubleQueue* instance, bool withData );
void pushLastTMHNodeDoubleQueue( TMHNodeDoubleQueue* const queue, TMHNode* newNode );
TMHNode* popTMHNodeDoubleQueue( TMHNodeDoubleQueue* const queue );

#endif /* TMHNODEDOUBLEQUEUE_H_ */
