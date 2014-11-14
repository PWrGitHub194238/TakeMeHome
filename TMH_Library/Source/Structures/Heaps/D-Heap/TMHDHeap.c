/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHDHeap.c
 * @author tomasz
 * @date 15 sie 2014
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

#include "../../../../Headers/Structures/Heaps/D-Heap/TMHDHeap.h"		/* TMHNode, TMHNodeIdx */

#include "../../../../Headers/Helpers/TMHAllocHelper.h"					/* memMalloc(), freeMem(), NULL */

#include "../../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHDHeap";

/*
 * Globals
 *
 */

/*
 * Private declarations
 *
 */
static void maxHeapify( TMHNode** nodeArray, TMHNodeIdx arraySize, TMHNodeIdx* nodeIdx, const TMHNodeIdx firstChildIdx, const TMHNodeIdx dHeapParam );

/*
 * Definitions
 *
 */

TMHDHeap* createTMHDHeapInstance( TMHNode** const inputArray, const TMHNodeIdx numberOfNodes, const TMHNodeIdx dHeapParam ) {
	TMHDHeap* newHeap = memMalloc(1,sizeof(TMHDHeap));

	newHeap->dHeapParam = dHeapParam;
	newHeap->arraySize = numberOfNodes+1;
	newHeap->nodeArray = inputArray;
	newHeap->heapSize = 0;

	return newHeap;
}

void destroyTMHDHeapInstance( TMHDHeap* const instance ) {
	TMHNode** nodeArray = instance->nodeArray;
	TMHNodeIdx nodeArraySize = instance->arraySize;
	for ( nodeArraySize--; nodeArraySize > 0; nodeArraySize-- ) {
		memFree(nodeArray[nodeArraySize]->toUpperStruct);
	}
	memFree(nodeArray[nodeArraySize]->toUpperStruct);
	memFree(instance);
}

void insertTMHDHeap( TMHDHeap* const instance, TMHNode* const newNode ) {
	TMHNodeIdx* nodeIdx = memCalloc(1,sizeof(TMHNodeIdx));
	*nodeIdx = newNode->nodeID;
	newNode->toUpperStruct = nodeIdx;
	instance->heapSize = instance->heapSize + 1;
	decreaseKeyTMHDHeap(instance,(TMHNodeIdx*)newNode->toUpperStruct,newNode->distanceLabel);
}

TMHNode* getMinimumTMHDHeap( TMHDHeap* const instance ) {
	return instance->nodeArray[1];
}

TMHNode* removeMinimumTMHDHeap( TMHDHeap* const instance ) {
	TMHNode* minNode;
	if ( instance->heapSize == 0 ) {
		warn(MODULE_NAME,warn_TMHDHeap_removeFromEmptyHeap);
		return NULL;
	} else {
		minNode = instance->nodeArray[1];
		instance->heapSize -= 1;
		maxHeapify(instance->nodeArray,instance->arraySize,(TMHNodeIdx*)minNode->toUpperStruct,instance->dHeapParam,instance->dHeapParam);
		return minNode;
	}
}

void decreaseKeyTMHDHeap( TMHDHeap* const instance, TMHNodeIdx* nodeIdx, const TMHNodeData newDistance ) {
	TMHNode* swap;
	TMHNodeIdx swapIdx;
	TMHNodeIdx dHeapParam = instance->dHeapParam;
	TMHNode** nodeArray = instance->nodeArray;
	TMHNodeIdx* parentIDx = (TMHNodeIdx*) nodeArray[(*nodeIdx)/dHeapParam]->toUpperStruct;

	while ( (*nodeIdx) > 1 && nodeArray[*parentIDx]->distanceLabel > newDistance ) {
		swapIdx = *parentIDx;
		swap = nodeArray[swapIdx];
		nodeArray[*parentIDx] = nodeArray[*nodeIdx];
		*parentIDx = *nodeIdx;
		nodeArray[*nodeIdx] = swap;
		*nodeIdx = swapIdx;
		parentIDx = (TMHNodeIdx*) nodeArray[(*nodeIdx)/dHeapParam]->toUpperStruct;
	}
}

static void maxHeapify( TMHNode** nodeArray, TMHNodeIdx arraySize, TMHNodeIdx* nodeIdx, const TMHNodeIdx firstChildIdx, const TMHNodeIdx dHeapParam ) {
	static TMHNode* swap;
	static TMHNodeIdx swapIdx;
	static TMHNodeIdx* minIdx;
	static TMHNodeIdx minId;
	static TMHNodeIdx j;
	static TMHNodeIdx childrenLastIdx;
	static TMHNodeIdx lastestIdx;

	minIdx = nodeIdx;
	minId = *minIdx;
	lastestIdx = firstChildIdx;
	childrenLastIdx = lastestIdx + dHeapParam;
	if ( childrenLastIdx >= arraySize ) {
		childrenLastIdx = dHeapParam - (childrenLastIdx-arraySize+1);
	}
	for ( j = 0; j < childrenLastIdx; j += 1 ) {
		if ( nodeArray[minId]->distanceLabel > nodeArray[lastestIdx]->distanceLabel ) {
			minId = lastestIdx;
		}
		lastestIdx += 1;
	}
	if ( minId != *nodeIdx ) {
		minIdx = (TMHNodeIdx*) nodeArray[minId]->toUpperStruct;
		swapIdx = *minIdx;
		swap = nodeArray[swapIdx];
		nodeArray[*minIdx] = nodeArray[*nodeIdx];
		*minIdx = *nodeIdx;
		nodeArray[*nodeIdx] = swap;
		*nodeIdx = swapIdx;
		maxHeapify(nodeArray,arraySize,minIdx,*minIdx*dHeapParam,dHeapParam);
	}
}
