/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHFibHeapBasic.c
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

#include "../../../../Headers/Helpers/TMHAllocHelper.h"					/* memMalloc(), memCalloc(), freeMem(), NULL */

#include "../../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */
#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibHeapBasic.h"
																		/* TMHFibHeap, TMHFibNode, TMHNode, TMHNodeIdx */


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHFibHeapBasic";

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static void destroyAuxiliaryArray( TMHFibNode** const auxiliaryArray, TMHNodeIdx maxDegree );
static void destroyTMHFibBHeap( TMHFibNode* rootListNode );
static TMHFibNode* concatenateTMHFibBHeap( TMHFibNode* Hmin, TMHFibNode* x );
static void consolidateTMHFibBHeap ( TMHFibHeap* const instance );
static void fibHeapLink(TMHFibHeap* const instance , TMHFibNode* y, TMHFibNode* x);
static void cascadingCutTMHFibBHeap( TMHFibHeap* H, TMHFibNode* y );
static void cutTMHFibBHeap( TMHFibHeap* H, TMHFibNode* x, TMHFibNode* y );

/*
 * Definitions
 *
 */

TMHFibHeap* createSingleTMHFibBHeapInstance( TMHFibNode* rootNode, const TMHNodeIdx maxNumberOfNodes ) {
	TMHFibHeap* newHeap = memMalloc(1,sizeof(TMHFibHeap));
	newHeap->minNode = rootNode;
	newHeap->numberOfNodes = (rootNode) ? 1 : 0;

	newHeap->maxDegree = (TMHNodeIdx) ( log(maxNumberOfNodes) * M_1_LOG_E_PHI);	/* floor(log_{Phi}(n)) = log_e(n)/log_e(Phi) = log_e(n) * 1/log_e(Phi) */
	newHeap->auxiliaryArray = memCalloc(newHeap->maxDegree,sizeof(TMHFibNode*));

	return newHeap;
}

/* Tworzy kopiec - główną listę złożoną z tylu nodów, do ilu ma dostęp z rootNode */
TMHFibHeap* createTMHFibBHeapInstance( TMHFibNode* rootNode, const TMHNodeIdx maxNumberOfNodes ) {
	TMHFibHeap* newHeap = memMalloc(1,sizeof(TMHFibHeap));
	TMHFibNode* rootNodeHead;
	TMHNodeIdx numberOfNodes = 0;

	newHeap->maxDegree = (TMHNodeIdx) ( log(maxNumberOfNodes) * M_1_LOG_E_PHI);	/* floor(log_{Phi}(n)) = log_e(n)/log_e(Phi) = log_e(n) * 1/log_e(Phi) */
	newHeap->auxiliaryArray = memCalloc(newHeap->maxDegree,sizeof(TMHFibNode*));

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

void destroyTMHFibBHeapInstance( TMHFibHeap* const instance ) {
	destroyAuxiliaryArray(instance->auxiliaryArray,instance->maxDegree);
	if (instance->minNode) {
		destroyTMHFibBHeap(instance->minNode);
	}

	memFree(instance);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

static void destroyAuxiliaryArray( TMHFibNode** const auxiliaryArray, TMHNodeIdx maxDegree ) {
	for ( maxDegree--; maxDegree > 0; maxDegree-- ) {
		memFree(auxiliaryArray[maxDegree]);
	}
	memFree(auxiliaryArray[maxDegree]);
	memFree(auxiliaryArray);
}

static void destroyTMHFibBHeap( TMHFibNode* rootListNode ) {
	TMHFibNode* listHead;
	TMHFibNode* temp;
	listHead = rootListNode;
	do {
		temp = rootListNode->next;
		if (temp->childList) {
			destroyTMHFibBHeap(temp->childList);
		}
		destroyTMHFibNodeInstance(rootListNode,false);
		rootListNode = temp;
	} while ( listHead != rootListNode );
}

void insertSingleTMHFibBHeap( TMHFibHeap* H, TMHFibNode* x ) {
	x->degree = 0;
	x->parent = NULL;
	x->childList = NULL;
	x->mark = false;
	if ( H->minNode == NULL ) {

		H->minNode = x;
		H->numberOfNodes = 1;
	/*	printf("%u Inserted to empty %u (dl: %u, d: %u)\n",H->numberOfNodes,x->data->nodeID,x->data->distanceLabel,x->degree);
			printFib(H->minNode,0);
			printf("\n-------------------------------------------------------\n");*/
	} else {
		H->minNode = concatenateTMHFibBHeap(H->minNode,x);
		H->numberOfNodes += 1;
		/*printf("%u Inserted %u (dl: %u, d: %u)\n",H->numberOfNodes,x->data->nodeID,x->data->distanceLabel,x->degree);
				printFib(H->minNode,0);
				printf("\n-------------------------------------------------------\n");*/

	}
}

static TMHFibNode* concatenateTMHFibBHeap( TMHFibNode* Hmin, TMHFibNode* x ) {
	if ( Hmin == NULL && x == NULL) {
		return NULL;
	} else if (Hmin == NULL ) {
		return x;
	} else if (x == NULL ) {
		return Hmin;
	} else {
		TMHFibNode* t1 = Hmin->prev;
		TMHFibNode* t2 = x->prev;
		TMHFibNode* h1 = Hmin;
		TMHFibNode* h2 = x;

		h1->prev = t2 ;
		t1->next = h2 ;
		h2->prev = t1 ;
		t2->next = h1 ;
		if ( h1->data->distanceLabel <= h2->data->distanceLabel ) {
			return h1;
		} else {
			return h2;
		}
	}
}

TMHNode* extractMinTMHFibBHeap( TMHFibHeap* H ) {
	TMHFibNode* z = H->minNode;
	if ( z != NULL ) {
		TMHFibNode* begin = z->childList;
		TMHFibNode* x = begin;

		if ( begin != NULL ) {
			do {
				x->parent = NULL;
				x = x->next;
			} while (x != begin);
			H->minNode = concatenateTMHFibBHeap(H->minNode,z->childList);
		}

		z->next->prev = z->prev;
		z->prev->next = z->next;

		if ( z == z->next ) {
			H->minNode = NULL;
		} else {
			H->minNode = z->next;
			consolidateTMHFibBHeap(H);
		}

		H->numberOfNodes -= 1;
	/*	printf("%u Extracted  %u (dl: %u, d: %u)\n",H->numberOfNodes,z->data->nodeID,z->data->distanceLabel,z->degree);
				printFib(H->minNode,0);
				printf("\n-------------------------------------------------------\n");*/
		return z->data;
	}
	/*printf("%u Extracted and empty  %u (dl: %u, d: %u)\n",H->numberOfNodes,z->data->nodeID,z->data->distanceLabel,z->degree);
					printFib(H->minNode,0);
					printf("\n-------------------------------------------------------\n");*/
	H->numberOfNodes = 0;
	return NULL;
}


TMHFibNode* getMinimumTMHFibBHeap( const TMHFibHeap* const instance ) {
	return instance->minNode;
}


static void consolidateTMHFibBHeap ( TMHFibHeap* const instance ) {
	TMHFibNode** A = instance->auxiliaryArray;
	for ( TMHNodeIdx i = 0; i < instance->maxDegree; i += 1 ) {
		A[i] = NULL;
	}

	TMHFibNode* temp,*x,*y,*w = instance->minNode;
	TMHNodeIdx d;
//	printf("\nPrzed konsolidacją:\n");
//	printFib(instance->minNode,0);
	TMHFibNode* end = w->prev;
	//printf("\nPoczątek w: %u:\n",end->data->nodeID);

	while (w != end) {
	//	scanf("%d",&i);
		x = w;
		d = x->degree;
	//	printFib(x,0);
	//	printf("\nNastępny: %u (%u):",x->data->nodeID,x->degree);
		w = x->next;	//zapamiętujemy teraz next'a, bo nie jest on na pewno jeszcze na A[] - nie zostanie przesunięty, a niżej to swap może nam popsuć.
		while ( A[d] != NULL) {
		//	printFib(x,0);


			y = A[d];
			if ( x->data->distanceLabel > y->data->distanceLabel ) {
				temp = x;
				x = y;
				y = temp;
			}
			fibHeapLink(instance,y,x);
			A[d] = NULL;
			d = d +1;
		//	printf("\n%u/%u\n",d,instance->maxDegree);

		}
		A[d] = x;
	//	printf("\nDodaj %u (%u) jako A[%u].",x->data->nodeID,x->degree,d);

	//	printf("\nNext: %u (dL %u d %u).",w->data->nodeID,w->data->distanceLabel,w->degree);

	}

	x = w;
	d = x->degree;

//	printFib(instance->minNode,0);
//	printf("\nNastępny o: %u (%u):",x->data->nodeID,x->degree);

	while ( A[d] != NULL) {
	//	printFib(x,0);

		y = A[d];
		if ( x->data->distanceLabel > y->data->distanceLabel ) {
			temp = x;
			x = y;
			y = temp;
		}
		fibHeapLink(instance,y,x);
		A[d] = NULL;
		d = d +1;

		//printf("\n%u/%u\n",d,instance->maxDegree);

	}
	A[d] = x;

//	printf("\nDodaj o %u (%u) jako A[%u].",x->data->nodeID,x->degree,d);


	instance->minNode = NULL;

	for ( TMHNodeIdx i = 0; i < instance->maxDegree; i += 1 ) {
		if ( A[i] != NULL ) {
			A[i]->next = A[i];
			A[i]->prev = A[i];
		//	printf("\nDRUKUJ A[%u]\n",i);

		//	printFib(A[i],0);
		//	printf("\nKONIEC DRUKUJ A[%u]\n",i);

			if (instance->minNode == NULL ) {
				instance->minNode = A[i];
			} else {
		//		instance->minNode = concatTMHFibNode(instance->minNode,A[i]);

					instance->minNode->prev->next = A[i];

			A[i]->prev = instance->minNode->prev;

							instance->minNode->prev = A[i];

A[i]->next = instance->minNode;

	instance->minNode = ((instance->minNode->data->distanceLabel <= A[i]->data->distanceLabel) ? instance->minNode : A[i]);


			}
		}
	}
		//printFib(instance->minNode,0);

}

/* y jako child x */
static void fibHeapLink(TMHFibHeap* const instance , TMHFibNode* y, TMHFibNode* x) {
	if ( y->next == y) {
		instance->minNode = NULL;
	} else {
		y->next->prev = y->prev;
		y->prev->next = y->next;
	}

	y->parent = x;

	if (x->childList) {

		x->childList->prev->next = y;
		y->prev = x->childList->prev;
		x->childList->prev = y;
		y->next = x->childList;

	} else {

		x->childList = y;
		y->next = y;
		y->prev = y;
	}
	x->degree += 1;
	y->mark = false;
}

void decreaseKeyTMHFibBHeap( TMHFibHeap* H, TMHFibNode* x, TMHNodeData k ) {
	TMHFibNode* y;
	x->data->distanceLabel = k;
	y = x->parent;
/*
	printf("%u Decreasing  %u (dl: %u, d: %u)\n",H->numberOfNodes,x->data->nodeID,x->data->distanceLabel,x->degree);
	printFib(H->minNode,0);
	printf("\n-------------------------------------------------------\n");
*/

	if ( y != NULL && x->data->distanceLabel < y->data->distanceLabel ) {
		cutTMHFibBHeap(H,x,y);
		cascadingCutTMHFibBHeap(H,y);
	}
	if ( x->data->distanceLabel < H->minNode->data->distanceLabel ) {
		H->minNode = x;
	}
}

/* y to parent x'a */
static void cutTMHFibBHeap( TMHFibHeap* H, TMHFibNode* x, TMHFibNode* y ) {
	x->next->prev = x->prev;
	x->prev->next = x->next;
	y->degree -= 1;

	if ( y->degree == 0 ) {
		y->childList = NULL;
	} else {
		if ( y->childList == x) {
			y->childList = x->next;
		}
	}
	H->minNode->prev->next = x;	// add x to H
			x->prev = H->minNode->prev;
			H->minNode->prev = x;
			x->next = H->minNode;

	//H->minNode = concatenate(H->minNode,x);
	x->parent = NULL;
	x->mark = false;
	/*printf("CUT  %u (dl: %u, d: %u)\n",x->data->nodeID,x->data->distanceLabel,x->degree);
	printFib(H->minNode,0);
	printf("\n-------------------------------------------------------\n");*/

}

static void cascadingCutTMHFibBHeap( TMHFibHeap* H, TMHFibNode* y ) {
	TMHFibNode* z = y->parent;
	if (z != NULL ) {
		if ( y->mark == false ) {
			y->mark = true;
		} else {
			cutTMHFibBHeap(H,y,z);
			cascadingCutTMHFibBHeap(H,z);
		}
	}
}

TMHNode* deleteNodeTMHFibBHeap( TMHFibHeap* const instance, TMHFibNode* const node ) {
	decreaseKeyTMHFibBHeap(instance,node,0);
	return extractMinTMHFibBHeap(instance);
}
