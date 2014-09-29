/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHNodeStack.h
 * @author tomasz
 * @date 24 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHNodeStack.h
 *
 *  Created on: 24 sie 2014
 *      Author: tomasz
 */

#ifndef TMHNODESTACK_H_
#define TMHNODESTACK_H_

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

typedef struct TMHNodeStack {
	TMHNode* data;
	struct TMHNodeStack* next;
} TMHNodeStack;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHNodeStack* createTMHNodeStackInstance();
void destroyTMHNodeStackInstance( TMHNodeStack* instance, bool withData );

void pushTMHNodeStack( TMHNodeStack** const stack, TMHNode* newNode );
TMHNode* popTMHNodeStack( TMHNodeStack** const stack );

#endif /* TMHNODESTACK_H_ */
