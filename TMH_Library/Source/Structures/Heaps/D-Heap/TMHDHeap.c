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

static const TMHNodeIdx ROOT_IDX = 1;

/*
 * Private declarations
 *
 */

static void maxHeapify( TMHNode** const nodeArray, TMHNodeIdx* const heapIDArray, const TMHNodeIdx heapSize, const TMHNodeIdx dHeapParam, TMHNodeIdx heapID );

/*
 * Definitions
 *
 */

TMHDHeap* createTMHDHeapInstance( TMHNode** const inputArray, const TMHNodeIdx numberOfNodes, const TMHNodeIdx dHeapParam ) {
	TMHDHeap* newHeap = memMalloc(1,sizeof(TMHDHeap));
	TMHNodeIdx noOfNodes = numberOfNodes+ROOT_IDX;
	TMHNodeIdx* heapIDArray = memMalloc(noOfNodes,sizeof(TMHNodeIdx));

	newHeap->dHeapParam = dHeapParam;
	newHeap->arraySize = noOfNodes;
	newHeap->nodeArray = inputArray;
	newHeap->heapIDArray = heapIDArray;
	newHeap->heapSize = 0;

	for ( noOfNodes--; noOfNodes > 0; noOfNodes-- ) {
		heapIDArray[noOfNodes] = noOfNodes;
	}

	return newHeap;
}

void destroyTMHDHeapInstance( TMHDHeap* const instance ) {
	memFree(instance->heapIDArray);
	memFree(instance);
}

/* toUS teraz jest indeksem węzłów w ich tablicy - ich id dłużej się nie pokrywa z kolejnością w tablicy*/
void insertTMHDHeap( TMHDHeap* const instance, TMHNode* const newNode ) {
	TMHNode* oldNode;
	TMHNodeIdx* heapIDArray = instance->heapIDArray;
	TMHNode** nodeArray = instance->nodeArray;
	instance->heapSize = instance->heapSize + 1;

	oldNode = nodeArray[instance->heapSize];	// wstawia węzeł na koniec kopca

	nodeArray[instance->heapSize] = newNode;
	nodeArray[heapIDArray[newNode->nodeID]] = oldNode;	// a stary wstawiany na stare miejsce nowego

	heapIDArray[oldNode->nodeID] = heapIDArray[newNode->nodeID];
	heapIDArray[newNode->nodeID] = instance->heapSize;

	decreaseKeyTMHDHeap(instance,instance->heapSize,newNode->distanceLabel);
}

TMHNode* getMinimumTMHDHeap( TMHDHeap* const instance ) {
	return instance->nodeArray[ROOT_IDX];
}

TMHNode* removeMinimumTMHDHeap( TMHDHeap* const instance ) {
	TMHNode* minNode;

	switch (instance->heapSize) {
		case 0:
			if(isWarnLogEnabled()) {
				warn(MODULE_NAME,warn_TMHDHeap_removeFromEmptyHeap);
			}
			return NULL;
		case 1:
			instance->heapSize -= 1;
			return instance->nodeArray[ROOT_IDX];
		default:
			minNode = instance->nodeArray[ROOT_IDX];

			instance->nodeArray[ROOT_IDX] = instance->nodeArray[instance->heapSize];	// wraz z przeniesieniem z końca na początek
			instance->heapIDArray[instance->nodeArray[ROOT_IDX]->nodeID] = ROOT_IDX;	// node, który został przeniesiony na początek ma id na początku

			instance->nodeArray[instance->heapSize] = minNode;
			instance->heapIDArray[minNode->nodeID] = instance->heapSize;

			instance->heapSize -= 1;

			if ( instance->heapSize > 1 ) {
				maxHeapify(instance->nodeArray,instance->heapIDArray,instance->heapSize,instance->dHeapParam,ROOT_IDX);
			}
			return minNode;
	}
}

void decreaseKeyTMHDHeap( TMHDHeap* const instance, TMHNodeIdx heapID, const TMHNodeData newDistance ) {
	TMHNodeIdx dHeapParam = instance->dHeapParam;
	TMHNode** nodeArray = instance->nodeArray;
	TMHNode* swap;
	TMHNodeIdx parentID;

	while ( heapID > ROOT_IDX ) {
		parentID = (TMHNodeIdx) (((heapID-ROOT_IDX)-1)/dHeapParam+ROOT_IDX);

		if ( nodeArray[parentID]->distanceLabel > newDistance ) {

			swap = instance->nodeArray[heapID];

			instance->nodeArray[heapID] = instance->nodeArray[parentID];		// parent dalej
			instance->heapIDArray[instance->nodeArray[heapID]->nodeID] = heapID;	// odpowiednio idx parenta

			instance->nodeArray[parentID] = swap;	// w miejsce parenta
			instance->heapIDArray[swap->nodeID] = parentID;


			heapID = parentID;
		} else {
			break;
		}
	}
}

static void maxHeapify( TMHNode** const nodeArray, TMHNodeIdx* const heapIDArray, const TMHNodeIdx heapSize, const TMHNodeIdx dHeapParam, TMHNodeIdx heapID ) {
	static TMHNode* swap;
	static TMHNodeIdx swapIdx;
	static TMHNodeIdx minId;
	static TMHNodeIdx firstChildIdx;
	static TMHNodeIdx lastChildIdx;

	minId = heapID;
	firstChildIdx = dHeapParam*(heapID-ROOT_IDX)+1+ROOT_IDX;
	lastChildIdx = firstChildIdx + dHeapParam - 1;

	if ( lastChildIdx > heapSize ) {
		lastChildIdx = heapSize;
	}

	for ( ; firstChildIdx <= lastChildIdx; firstChildIdx += 1 ) {
		if ( nodeArray[firstChildIdx]->distanceLabel < nodeArray[minId]->distanceLabel ) {
			minId = firstChildIdx;
		}
	}

	if ( minId != heapID ) {	// if not already minimum

		swap = nodeArray[heapID];
		swapIdx = heapIDArray[swap->nodeID];

		nodeArray[heapID] = nodeArray[minId];
		heapIDArray[swap->nodeID] = heapIDArray[nodeArray[minId]->nodeID];

		heapIDArray[nodeArray[minId]->nodeID] = swapIdx;
		nodeArray[minId] = swap;

		maxHeapify(nodeArray,heapIDArray,heapSize,dHeapParam,minId);
	}
}
