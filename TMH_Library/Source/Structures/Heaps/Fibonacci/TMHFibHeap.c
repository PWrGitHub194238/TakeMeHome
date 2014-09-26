/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHFibHeap.c
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

#include <math.h>														/* log()*/

#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibHeap.h"	/* TMHFibHeap, TMHFibNode, TMHNode, TMHNodeIdx */

#include "../../../../Headers/Helpers/TMHAllocHelper.h"					/* memMalloc(), memCalloc(), freeMem(), NULL */

#include "../../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHFibHeap";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static void consolidateTMHFibHeap ( TMHFibHeap* const instance );
static void cutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node, TMHFibNode* const parentNode );
static void cascadingCutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node );

/*
 * Definitions
 *
 */

TMHFibHeap* createSingleTMHFibHeapInstance( TMHFibNode* rootNode ) {
	TMHFibHeap* newHeap = memMalloc(1,sizeof(TMHFibHeap));
	newHeap->minNode = rootNode;
	newHeap->numberOfNodes = ((rootNode) ? 1 : 0);
	return newHeap;
}

TMHFibHeap* createTMHFibHeapInstance( TMHFibNode* rootNode ) {
	TMHFibHeap* newHeap = memMalloc(1,sizeof(TMHFibHeap));
	TMHFibNode* rootNodeHead;
	TMHNodeIdx numberOfNodes;
	if ( rootNode != NULL ) {
		newHeap->minNode = rootNode;
		rootNodeHead = rootNode->prev;		/*lepsze niż rN->next != rNH */
		while ( rootNode != rootNodeHead ) {
			numberOfNodes += 1;
			rootNode = rootNode->next;
		}
		newHeap->numberOfNodes = numberOfNodes + 1;
		return newHeap;
	} else {
		newHeap->minNode = NULL;
		newHeap->numberOfNodes = 0;
		return newHeap;
	}
}

void destroyTMHFibHeapInstance( TMHFibHeap* const instance ) {
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void insertSingleTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* nodeList ) {
	instance->minNode = concatTMHFibNode(instance->minNode,nodeList);
	instance->numberOfNodes += 1;
}

void insertTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* nodeList, const TMHNodeIdx* const listSize ) {
	TMHFibNode* nodeListHead;
	TMHNodeIdx numberOfNodes;
	if ( nodeList != NULL ) {
		if ( listSize == 0 ) {
			numberOfNodes = instance->numberOfNodes + 1;
			nodeListHead = nodeList->prev;
			while ( nodeList != nodeListHead ) {
				nodeList = nodeList->next;
				numberOfNodes += 1;
			}
		} else {
			numberOfNodes = *(listSize);
		}
		instance->minNode = concatTMHFibNode(instance->minNode,nodeList);
		instance->numberOfNodes = numberOfNodes;
	}
}


TMHFibNode* getMinimumTMHFibHeap( const TMHFibHeap* const instance ) {
	return instance->minNode;
}

TMHFibHeap* unionTMHFibHeap( TMHFibHeap* const heap1, const TMHFibHeap* const heap2 ) {
	heap1->minNode = concatTMHFibNode(heap1->minNode,heap2->minNode);
	heap1->numberOfNodes += heap2->numberOfNodes;
	return heap1;
}

TMHNode* removeMinimumTMHFibHeap( TMHFibHeap* const instance ) {
	TMHFibNode* z = instance->minNode;
	TMHNode* data = z->data;
	TMHFibNode* childList = z->childList;
	if ( z == NULL ) {
		warn(MODULE_NAME,warn_TMHFibHeap_removeFromEmptyHeap);
		return NULL;
	} else {
		if ( childList != NULL ) {
			instance->minNode = childList;	/* Jeśli na rootLiście 1 węzeł to usunięcie go tworzy z jego dzieci rootListę*/
			if ( z->next != z ) {
				/* nastepny node w rootLiscie z ostatnim dzieckiem z*/
				z->next->prev = childList->prev;
				childList->prev->next = z->next;
				/* poprzednik z wskazuje na 1 dziecko z*/
				z->prev->next = childList;
				childList->prev = z->prev;
				/* z jest "wypychany" przez swoja liste dzieci*/
			}
		} else {
			if ( z->next == z ) {	/* Jeśli na rootLiście 1 węzeł */
				instance->minNode = NULL;
				instance->numberOfNodes = 0;
				return data;
			}
			instance->minNode = z->next;
			z->next->prev = z->prev;	/* odpięcie z */
			z->prev->next = z->next;
		}
		destroyTMHFibNodeInstance(z,false);

		consolidateTMHFibHeap(instance);
		instance->numberOfNodes -= 1;
		return data;
	}
}

static void consolidateTMHFibHeap ( TMHFibHeap* const instance ) {
	TMHNodeIdx maxDegree = (TMHNodeIdx) (log(instance->numberOfNodes) * M_1_LOG_E_PHI);	/* multiply is faster that division*/
	TMHFibNode** auxiliaryArray = memCalloc(maxDegree,sizeof(TMHFibNode*));
	TMHFibNode* minNode = instance->minNode;
	TMHFibNode* tempNode = NULL;
	TMHFibNode* swapTmpAndChildNode = NULL;
	TMHFibNode* nextRootNode = NULL;
	/* Ostatnim nodem, który będziemy badać jest poprzednik "1" elementu na liście*/
	TMHFibNode* minNodeHead = minNode->prev;
	TMHNodeIdx degreeAndMin;
	while ( minNode != minNodeHead ) {
		degreeAndMin = minNode->degree;
		tempNode = auxiliaryArray[degreeAndMin];
		/* Następny elementdo badania na pewno nie będzie ruszany na rootLiście,
		 * bo jeszcze nie został dodany do auxiliaryArray, a jeśli został
		 * to znaczy, że sprawdzamy listę 2 raz, na co nie pozwoli minNodeHead*/
		nextRootNode = minNode->next;
		while ( tempNode != NULL ) {
			if (minNode->data->distanceLabel > tempNode->data->distanceLabel ) {
				swapTmpAndChildNode = minNode;
				minNode = tempNode;
				tempNode = swapTmpAndChildNode;
			}	/* nie zamieniamy degree, bo na pewno są takie same*/

			tempNode->parent = minNode;
			/* usunięcie tempNode z rootListy */
			tempNode->prev->next = tempNode->next;
			tempNode->next->prev = tempNode->prev;
			if ( degreeAndMin == 0 ) {	/* minNode->childList == NULL */
				minNode->childList = tempNode;
				tempNode->next = tempNode;
				tempNode->prev = tempNode;
			} else {
				swapTmpAndChildNode = minNode->childList;
				/* Dołączenie tempNode na początku dzieci minNode */
				tempNode->next = swapTmpAndChildNode;
				tempNode->prev = swapTmpAndChildNode->prev;
				/* Dowiązanie starego 1 nodea listy*/
				swapTmpAndChildNode->prev->next = tempNode;
				swapTmpAndChildNode->prev = tempNode;
			}

			auxiliaryArray[degreeAndMin++] = NULL;
			tempNode = auxiliaryArray[degreeAndMin];
		}
		auxiliaryArray[degreeAndMin] = minNode;
		minNode = nextRootNode;
	}

	/* Zatrzymaliśmy się na minNodeHead = minNode->prev - jedynym węźle, który na pewno nie został
	 * ruszony na rootLiście, a dawał nam najlepsze pojęcie o tym, gdzie jest koniec listy
	 * (jej początek, czyli następnik minNodeHead, mógł zostać już z rootListy usunięty).
	 * Aby przejść przez całą listę musimy wykonać ostatnią iterację po tym węźle.
	 * Robimy tzw. loop unrolling */

	degreeAndMin = minNode->degree;
	tempNode = auxiliaryArray[degreeAndMin];
	nextRootNode = minNode->next;
	while ( tempNode != NULL ) {
		if (minNode->data->distanceLabel > tempNode->data->distanceLabel ) {
			swapTmpAndChildNode = minNode;
			minNode = tempNode;
			tempNode = swapTmpAndChildNode;
		}

		tempNode->parent = minNode;
		tempNode->prev->next = tempNode->next;
		tempNode->next->prev = tempNode->prev;
		if ( degreeAndMin == 0 ) {
			minNode->childList = tempNode;
			tempNode->next = tempNode;
			tempNode->prev = tempNode;
		} else {
			swapTmpAndChildNode = minNode->childList;
			tempNode->next = swapTmpAndChildNode;
			tempNode->prev = swapTmpAndChildNode->prev;
			swapTmpAndChildNode->prev->next = tempNode;
			swapTmpAndChildNode->prev = tempNode;
		}

		auxiliaryArray[degreeAndMin++] = NULL;
		tempNode = auxiliaryArray[degreeAndMin];
	}

	/* Ustalamy nowe minimum na podstawie aktualnej rootListy.
	 * Domyślnie będzie to minNode
	 */
	minNode->parent = NULL;
	/* robota z removeMinimumTMHFibHeap - tutaj i tak już przeglądamy rootListę,
	 * czyli mamy "za darmo" iterowanie i ogranicznik. Czyli mamy 3p + 1 do m, więc tutaj to robić
	 * nam się opłaca, gdy 3p+1>m -> p>(m-1)/3. RootLista jest max długości \log_Phi(n)/
	 * Stopień node'a (ilość dzieci) to max. \log_Phi(n)/. Jako, że każdy węzeł na rootLiście ma
	 * inny stopień to dla ~2/3 z nich opłaca nam się wybrać opcję tutaj.
	*/
	nextRootNode = minNode->next;
	while ( nextRootNode != minNode ) {
		minNodeHead->parent = NULL;
		if ( nextRootNode->data->distanceLabel < minNode->data->distanceLabel ) {
			minNode = nextRootNode;
		}
		nextRootNode = nextRootNode->next;
	}
	instance->minNode = minNode;
}

void decreaseKeyTMHFibHeap( TMHFibHeap* const instance, TMHFibNode* const node, const TMHNodeIdx* newKey ) {
	TMHFibNode* parentNode;
	TMHNode* tmpData = node->data;
	TMHNode* minData = instance->minNode->data;
	if ( *newKey > tmpData->distanceLabel ) {
		return;
	}
	tmpData->distanceLabel = *newKey;
	parentNode = node->parent;
	if( tmpData->distanceLabel < minData->distanceLabel ) {
		minData->distanceLabel = tmpData->distanceLabel;
	}
	if ( parentNode != NULL && tmpData->distanceLabel < parentNode->data->distanceLabel ) {
		cutTMHFibHeap(instance->minNode,node,parentNode);
		cascadingCutTMHFibHeap(instance->minNode,parentNode);
	}
}

static void cutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node, TMHFibNode* const parentNode ) {
	/* Wyjęcie z listy dzieci*/
	node->next->prev = node->prev;
	node->prev->next = node->next;
	parentNode->degree -= 1;
	/* poprzednik <-> nowy - minNode*/
	minNode->prev->next = node;
	node->prev = minNode->prev;
	/* poprzednik <-> nowy <-> minNode*/
	minNode->prev = node;
	node->next = minNode;
	node->parent = NULL;
	node->mark = false;

}
static void cascadingCutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node ) {
	TMHFibNode* parentNode = node->parent;
	if ( parentNode != NULL ) {
		if ( node->mark == false ) {
			node->mark = true;
		} else {
			cutTMHFibHeap(minNode,node,parentNode);
			cascadingCutTMHFibHeap(minNode,parentNode);
		}
	}
}

TMHNode* deleteNodeTMHFibHeap( TMHFibHeap* const instance, TMHFibNode* const node ) {
	decreaseKeyTMHFibHeap(instance,node,0);
	return removeMinimumTMHFibHeap(instance);
}
