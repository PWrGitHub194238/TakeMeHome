/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHDHeap.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHDHeap.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHDHEAP_H_
#define TMHDHEAP_H_

/*
 * Includes
 *
 */

#include "../../TMHNode.h"
#include "../../../TMH.h"			/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMHDHeap {
	TMHNodeIdx dHeapParam;
	TMHNodeIdx heapSize;
	TMHNodeIdx arraySize;
	TMHNode** nodeArray;
	TMHNodeIdx* heapIDArray;	// IDki dla kopca
} TMHDHeap;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHDHeap* createTMHDHeapInstance( TMHNode** const inputArray, const TMHNodeIdx numberOfNodes, const TMHNodeIdx dHeapParam );

void destroyTMHDHeapInstance( TMHDHeap* const instance );

void insertTMHDHeap( TMHDHeap* const instance, TMHNode* const newNode );

TMHNode* getMinimumTMHDHeap( TMHDHeap* const instance );

TMHNode* removeMinimumTMHDHeap( TMHDHeap* const instance );

void decreaseKeyTMHDHeap( TMHDHeap* const instance, TMHNodeIdx heapID, const TMHNodeData newDistance );

#endif /* TMHDHEAP_H_ */
