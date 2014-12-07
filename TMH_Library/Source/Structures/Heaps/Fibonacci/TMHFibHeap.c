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

#include "../../../../Headers/Helpers/TMHAllocHelper.h"					/* memMalloc(), memCalloc(), freeMem(), NULL */

#include "../../../../Headers/TMHLogger.h"								/* debug() */
#include "../../../../Headers/Helpers/TMHErrors.h"						/* debug_instanceDeletedSuccessfully */
#include "../../../../Headers/Structures/Heaps/Fibonacci/TMHFibHeap.h"	/* TMHFibHeap, TMHFibNode, TMHNode, TMHNodeIdx */


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



static void consolidateTMHFibHeap2 ( TMHFibHeap* const instance );
static void fibHeapLink(TMHFibHeap* const instance , TMHFibNode* y, TMHFibNode* x);

static void destroyAuxiliaryArray( TMHFibNode** const auxiliaryArray, TMHNodeIdx maxDegree );
static void destroyTMHFibHeap( TMHFibNode* rootListNode );
static void consolidateTMHFibHeap ( TMHFibHeap* const instance );
static void cutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node, TMHFibNode* const parentNode );
static void cascadingCutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node );


/*
 * Definitions
 *
 */

TMHFibHeap* createSingleTMHFibHeapInstance( TMHFibNode* rootNode, const TMHNodeIdx maxNumberOfNodes ) {
	TMHFibHeap* newHeap = memMalloc(1,sizeof(TMHFibHeap));
	newHeap->minNode = rootNode;
	newHeap->numberOfNodes = (rootNode) ? 1 : 0;

	newHeap->maxDegree = (TMHNodeIdx) ( log(maxNumberOfNodes) * M_1_LOG_E_PHI);	/* floor(log_{Phi}(n)) = log_e(n)/log_e(Phi) = log_e(n) * 1/log_e(Phi) */
	newHeap->auxiliaryArray = memCalloc(newHeap->maxDegree,sizeof(TMHFibNode*));

	fatal(MODULE_NAME,"Create FibHeap with maxDegree: %u, rootNode with ID: %u (dL: %u, d: %u, m: %d)",newHeap->maxDegree,rootNode->data->nodeID,rootNode->data->distanceLabel,rootNode->degree,rootNode->mark);
	//printf("%u Init with + %u (dl: %u, d: %u)\n",newHeap->numberOfNodes,rootNode->data->nodeID,rootNode->data->distanceLabel,rootNode->degree);
	//printFib(newHeap->minNode,0);
	//printf("\n-------------------------------------------------------\n");

	return newHeap;
}

/* Tworzy kopiec - główną listę złożoną z tylu nodów, do ilu ma dostęp z rootNode */
TMHFibHeap* createTMHFibHeapInstance( TMHFibNode* rootNode, const TMHNodeIdx maxNumberOfNodes ) {
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

void destroyTMHFibHeapInstance( TMHFibHeap* const instance ) {
	destroyAuxiliaryArray(instance->auxiliaryArray,instance->maxDegree);
	if (instance->minNode) {
		destroyTMHFibHeap(instance->minNode);
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

static void destroyTMHFibHeap( TMHFibNode* rootListNode ) {
	TMHFibNode* listHead;
	TMHFibNode* temp;
	listHead = rootListNode;
	do {
		temp = rootListNode->next;
		if (temp->childList) {
			destroyTMHFibHeap(temp->childList);
		}
		destroyTMHFibNodeInstance(rootListNode,false);
		rootListNode = temp;
	} while ( listHead != rootListNode );
}

void insertSingleTMHFibHeapInstance2( TMHFibHeap* H, TMHFibNode* x ) {
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
		H->minNode = concatenate(H->minNode,x);
		H->numberOfNodes += 1;
		/*printf("%u Inserted %u (dl: %u, d: %u)\n",H->numberOfNodes,x->data->nodeID,x->data->distanceLabel,x->degree);
				printFib(H->minNode,0);
				printf("\n-------------------------------------------------------\n");*/

	}
}

TMHFibNode* concatenate( TMHFibNode* Hmin, TMHFibNode* x ) {
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

TMHNode* extractMin( TMHFibHeap* H ) {
	TMHFibNode* z = H->minNode;
	if ( z != NULL ) {
		TMHFibNode* begin = z->childList;
		TMHFibNode* x = begin;

		if ( begin != NULL ) {
			do {
				x->parent = NULL;
				x = x->next;
			} while (x != begin);
			H->minNode = concatenate(H->minNode,z->childList);
		}

		z->next->prev = z->prev;
		z->prev->next = z->next;

		if ( z == z->next ) {
			H->minNode = NULL;
		} else {
			H->minNode = z->next;
			consolidateTMHFibHeap2(H);
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

/* oba nie nulle*/
void insertSingleTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* singleNode ) {
	fatal(MODULE_NAME,"Insert 1 node with ID: %u (%u,%u,%d)",singleNode->data->nodeID,singleNode->data->distanceLabel,singleNode->degree,singleNode->mark);
	if (instance->minNode) {
		instance->minNode = concatTMHFibNode(instance->minNode,singleNode);
	} else {
		instance->minNode = singleNode;
	}
	instance->numberOfNodes += 1;
}

/* nie nulle */
void insertTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* nodeList, const TMHNodeIdx listSize ) {
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
			numberOfNodes = listSize;
		}
		instance->minNode = concatTMHFibNode(instance->minNode,nodeList);
		instance->numberOfNodes = numberOfNodes;
	}
}


TMHFibNode* getMinimumTMHFibHeap( const TMHFibHeap* const instance ) {
	return instance->minNode;
}

/* Dołącza 2 liste do pierwszej */
TMHFibHeap* unionTMHFibHeap( TMHFibHeap* const heap1, TMHFibHeap* const heap2 ) {
	if ( heap1->minNode == NULL && heap2->minNode == NULL ) {
		return NULL;
	} else if ( heap1->minNode == NULL ) {
		return heap2;
	} else if ( heap2->minNode == NULL ) {
		return heap1;
	} else {
		heap1->minNode = concatTMHFibNode(heap1->minNode,heap2->minNode);
		heap1->numberOfNodes += heap2->numberOfNodes;
		return heap1;
	}
}


TMHNode* removeMinimumTMHFibHeap( TMHFibHeap* const instance ) {
	printFib(instance->minNode,0);
	TMHFibNode* z = instance->minNode;
	TMHNode* data;
	TMHFibNode* childList;
	if ( z == NULL ) {
		warn(MODULE_NAME,warn_TMHFibHeap_removeFromEmptyHeap);
		return NULL;
	} else {
		data = z->data;
		error(MODULE_NAME,"Usuwanie z kolejki noda: %u (dL: %u, d: %u, m: %u)",data->nodeID,data->distanceLabel,z->degree,z->mark);
		childList = z->childList;
		if ( childList != NULL ) {
			error(MODULE_NAME,"Jako nowy min node ustaw pierwsze dziecko node'a: %u - %u (dL: %u, d: %u, m: %u)",data->nodeID,childList->data->nodeID,childList->data->distanceLabel,childList->degree,childList->mark);
			instance->minNode = childList;	/* Jeśli na rootLiście 1 węzeł to usunięcie go tworzy z jego dzieci rootListę*/
			if ( z->next != z ) {
				error(MODULE_NAME,"MinNode nie był jedyny na root liście. Wpięcie childListy w miejsce minNode.");
				/* nastepny node w rootLiscie z ostatnim dzieckiem z*/
				z->next->prev = childList->prev;
				childList->prev->next = z->next;
				/* poprzednik z wskazuje na 1 dziecko z*/
				z->prev->next = childList;
				childList->prev = z->prev;
				/* z jest "wypychany" przez swoja liste dzieci*/
			} else {	// TO DELETE
				error(MODULE_NAME,"MinNode był jedyny na root liście. Root listą jest teraz jego childList");

			}	// TO DELETE
		} else {
			error(MODULE_NAME,"MinNode nie ma dzieci");

			if ( z->next == z ) {	/* Jeśli na rootLiście 1 węzeł */
				error(MODULE_NAME,"I jest sam na rootLiście. -> puste drzewo");
				instance->minNode = NULL;
				instance->numberOfNodes = 0;
				destroyTMHFibNodeInstance(z,false);
				return data;
			}
			instance->minNode = z->next;
			z->next->prev = z->prev;	/* odpięcie z */
			z->prev->next = z->next;
			error(MODULE_NAME,"MinNode to teraz następik zwracanego minNode, odpięcie go od rootListy.");

		}
		destroyTMHFibNodeInstance(z,false);
		instance->numberOfNodes -= 1;

		consolidateTMHFibHeap2(instance);
		printFib(instance->minNode,0);
		return data;
	}
}

static void consolidateTMHFibHeap2 ( TMHFibHeap* const instance ) {
	int i;
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

//printf("NOOOOOOO\n");

					instance->minNode->prev->next = A[i];
		//			printf("WHY\n");

			A[i]->prev = instance->minNode->prev;
		//	printf("IT\n");

							instance->minNode->prev = A[i];

				//			printf("HAPPENDS\n");
A[i]->next = instance->minNode;
//printf("TO\n");

	instance->minNode = ((instance->minNode->data->distanceLabel <= A[i]->data->distanceLabel) ? instance->minNode : A[i]);
	//printf("ME\n");


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

	//	concatenate(y,x->childList);
	} else {

		x->childList = y;
		y->next = y;
		y->prev = y;
	}
	x->degree += 1;
	y->mark = false;
}

static void consolidateTMHFibHeap ( TMHFibHeap* const instance ) {
	/*TMHNodeIdx maxDegree = (TMHNodeIdx) (log(instance->numberOfNodes) * M_1_LOG_E_PHI);	 multiply is faster that division
	TMHFibNode** auxiliaryArray = memCalloc(maxDegree,sizeof(TMHFibNode*));*/	// Czy opłaca się allocować za każdym razem, czy raz z górnym ograniczeniem ?
	TMHFibNode** auxiliaryArray = instance->auxiliaryArray;
	TMHFibNode* minNode = instance->minNode;
	TMHFibNode* tempNode = NULL;
	TMHFibNode* swapTmpAndChildList = NULL;
	TMHFibNode* nextRootNode = NULL;
	/* Ostatnim nodem, który będziemy badać jest poprzednik "1" elementu na liście
	 * + mamy gwarancję, że nie zostanie on wywalony z listy nim do niego nie dojdziemy.
	 * Czemu działa - naszym celem jest stworzenie takiej root listy, której węzły będą miały parami różne stopnie -
	 * poprawiamy drzewo wtedy, kiedy na auxiliaryArray jest zaznaczony node o danym stopniu i jesteśmy w nodzie o tym samym stopniu.
	 * Od minNode idziemy w prawo - na prawo od minNode->prev (pomijając cykliczność) wszystkie nody są albo w tej tablicy (pierwsze powtórzzenie),
	 * albo jest stworzony z 2 powtórzeń drzewo o większym stopniu (i tak jest wstawiane do tej tablicy). Więc po prawej zostaną drzewa o różnuch stopniach, będące w tablicy.
	 * Zawracamy, dochodzimy do minNode->pred. Przeszliśmy "wszystkie" nody, a te, które wycieliśmy z rootListy, a do których nie zdążyliśmy dojść są albo na  auxiliaryArray
	 * albo już został podpięty jako dziecko. */
	TMHFibNode* minNodeHead = minNode->prev;
	TMHNodeIdx degree;

	error(MODULE_NAME,"Konsolidacja od nowego \"minimum\": %u (dL: %u, d: %u, m: %u). Stop pętli na poprzedniku: %u (dL: %u, d: %u, m: %u).",minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark,minNodeHead->data->nodeID,minNodeHead->data->distanceLabel,minNodeHead->degree,minNodeHead->mark);
	while ( minNode != minNodeHead ) {
		printFib(instance->minNode,0);

		degree = minNode->degree;
		tempNode = auxiliaryArray[degree];
		/* Następny elementdo badania na pewno nie będzie ruszany na rootLiście,
		 * bo jeszcze nie został dodany do auxiliaryArray, a jeśli został
		 * to znaczy, że sprawdzamy listę 2 raz, na co nie pozwoli minNodeHead*/
		nextRootNode = minNode->next;
		error(MODULE_NAME,"Badany: %u (dL: %u, d: %u, m: %u). Następny: %u (dL: %u, d: %u, m: %u).",minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark,nextRootNode->data->nodeID,nextRootNode->data->distanceLabel,nextRootNode->degree,nextRootNode->mark);

		if ( tempNode != NULL ) {	// TO REMOVE
			error(MODULE_NAME,"auxiliaryArray[%u]: %u (dL: %u, d: %u, m: %u).",degree,tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

		} else {
			error(MODULE_NAME,"auxiliaryArray[%u]: null.",degree);

		}	// TO REMOVE
		while ( tempNode != NULL ) {	//jeśli mamy już takie drzewo z danym stopniem to trzeba je połączyć w stopień +1
			if (minNode->data->distanceLabel > tempNode->data->distanceLabel ) {
				swapTmpAndChildList = minNode;
				minNode = tempNode;
				tempNode = swapTmpAndChildList;
			}	/* nie zamieniamy degree, bo na pewno są takie same*/
			error(MODULE_NAME,"Podpinamy jako dziecko: %u (dL: %u, d: %u, m: %u) do drzewa:  %u (dL: %u, d: %u, m: %u).",tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark,minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark);

			/* usunięcie tempNode z rootListy */
			tempNode->prev->next = tempNode->next;
			tempNode->next->prev = tempNode->prev;
			if ( degree == 0 ) {	/* minNode->childList == NULL  i temp tak samo*/
				error(MODULE_NAME,"Stopień = 0. Proste dopięcie.");
				tempNode->parent = minNode;	// minNode ma zawsze mniejszy dLabel
				minNode->childList = tempNode;
				tempNode->next = tempNode;
				tempNode->prev = tempNode;
			} else {	// link do parenta już jest - zwykłe dołączenie do listy
				error(MODULE_NAME,"Stopień = %u. Zwykłe złączenie list.",degree);

				tempNode->parent = NULL;

				swapTmpAndChildList = minNode->childList;

				tempNode->next = swapTmpAndChildList;
				tempNode->prev = swapTmpAndChildList->prev;
				swapTmpAndChildList->prev->next = tempNode;
				swapTmpAndChildList->prev = tempNode;
			}

			error(MODULE_NAME,"Zwiększony stopień: %u (dL: %u, d: %u, m: %u) z %u -> %u.",minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark,minNode->degree,minNode->degree+1);
			error(MODULE_NAME,"Czyszczenie markera: %u (dL: %u, d: %u, m: %u).",tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

			minNode->degree += 1;
			tempNode->mark = false;

			auxiliaryArray[degree++] = NULL;
			tempNode = auxiliaryArray[degree];
			error(MODULE_NAME,"Następny stopień = %u.",degree);
			if ( tempNode != NULL ) {	// TO REMOVE
				error(MODULE_NAME,"auxiliaryArray[%u]: %u (dL: %u, d: %u, m: %u).",degree,tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

			} else {
				error(MODULE_NAME,"auxiliaryArray[%u]: null.",degree);

			}	// TO REMOVE
		}
		auxiliaryArray[degree] = minNode;	// końcowy stopień

		error(MODULE_NAME,"Stworzono drzewo w auxiliaryArray[%u] o korzeniu %u (dL: %u, d: %u, m: %u).",degree,minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark);

		minNode = nextRootNode;
	}

	// minNode = oryginalne minNode->prev

	/* Zatrzymaliśmy się na minNodeHead = minNode->prev - jedynym węźle, który na pewno nie został
	 * ruszony na rootLiście, a dawał nam najlepsze pojęcie o tym, gdzie jest koniec listy
	 * (jej początek, czyli następnik minNodeHead, mógł zostać już z rootListy usunięty).
	 * Aby przejść przez całą listę musimy wykonać ostatnią iterację po tym węźle.
	 * Robimy tzw. loop unrolling */


	degree = minNode->degree;
	tempNode = auxiliaryArray[degree];
	printFib(instance->minNode,0);

	error(MODULE_NAME,"Badany ostatni: %u (dL: %u, d: %u, m: %u).",minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark);

	if ( tempNode != NULL ) {	// TO REMOVE
		error(MODULE_NAME,"auxiliaryArray[%u]: %u (dL: %u, d: %u, m: %u).",degree,tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

	} else {
		error(MODULE_NAME,"auxiliaryArray[%u]: null.",degree);

	}	// TO REMOVE

	while ( tempNode != NULL ) {	//jeśli mamy już takie drzewo z danym stopniem to trzeba je połączyć w stopień +1
		if (minNode->data->distanceLabel > tempNode->data->distanceLabel ) {
			swapTmpAndChildList = minNode;
			minNode = tempNode;
			tempNode = swapTmpAndChildList;
		}	/* nie zamieniamy degree, bo na pewno są takie same*/
		error(MODULE_NAME,"Podpinamy jako dziecko: %u (dL: %u, d: %u, m: %u) do drzewa:  %u (dL: %u, d: %u, m: %u).",tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark,minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark);

		/* usunięcie tempNode z rootListy */
		tempNode->prev->next = tempNode->next;
		tempNode->next->prev = tempNode->prev;
		if ( degree == 0 ) {	/* minNode->childList == NULL  i temp tak samo*/
			error(MODULE_NAME,"Stopień = 0. Proste dopięcie.");
			tempNode->parent = minNode;	// minNode ma zawsze mniejszy dLabel
			minNode->childList = tempNode;
			tempNode->next = tempNode;
			tempNode->prev = tempNode;
		} else {	// link do parenta już jest - zwykłe dołączenie do listy
			error(MODULE_NAME,"Stopień = %u. Zwykłe złączenie list.",degree);

			tempNode->parent = NULL;

			swapTmpAndChildList = minNode->childList;

			tempNode->next = swapTmpAndChildList;
			tempNode->prev = swapTmpAndChildList->prev;
			swapTmpAndChildList->prev->next = tempNode;
			swapTmpAndChildList->prev = tempNode;
		}

		error(MODULE_NAME,"Zwiększony stopień: %u (dL: %u, d: %u, m: %u) z %u -> %u.",minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark,minNode->degree,minNode->degree+1);
		error(MODULE_NAME,"Czyszczenie markera: %u (dL: %u, d: %u, m: %u).",tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

		minNode->degree += 1;
		tempNode->mark = false;

		auxiliaryArray[degree++] = NULL;
		tempNode = auxiliaryArray[degree];

		error(MODULE_NAME,"Następny stopień = %u.",degree);
		if ( tempNode != NULL ) {	// TO REMOVE
			error(MODULE_NAME,"auxiliaryArray[%u]: %u (dL: %u, d: %u, m: %u).",degree,tempNode->data->nodeID,tempNode->data->distanceLabel,tempNode->degree,tempNode->mark);

		} else {
			error(MODULE_NAME,"auxiliaryArray[%u]: null.",degree);

		}	// TO REMOVE
	}

	auxiliaryArray[degree] = NULL;	/* minNode powinien normalnie być przypisany do auxiliaryArray[degree], lecz sobie skracamy,
									jako że potem budujemy nową rootListę poprzez iterowanie nienullowych auxiliaryArray[] i je dołączając do minNode, które jest już jakimś
									auxiliaryArray[degree], tylko nieprzypisany*/

	error(MODULE_NAME,"Stworzono drzewo w auxiliaryArray[%u] %u (dL: %u, d: %u, m: %u).",degree,minNode->data->nodeID,minNode->data->distanceLabel,minNode->degree,minNode->mark);

	/* robota z removeMinimumTMHFibHeap - tutaj i tak już przeglądamy rootListę,
	 * czyli mamy "za darmo" iterowanie i ogranicznik. Czyli mamy 3p + 1 do m, więc tutaj to robić
	 * nam się opłaca, gdy 3p+1>m -> p>(m-1)/3. RootLista jest max długości \log_Phi(n)/
	 * Stopień node'a (ilość dzieci) to max. \log_Phi(n)/. Jako, że każdy węzeł na rootLiście ma
	 * inny stopień to dla ~2/3 z nich opłaca nam się wybrać opcję tutaj.
	*/

	// CHYBA JEDNAK PO auxiliaryArray - bo docelowo każdy node na root liście powinen mieć inny stopień - być jedynym o danym stopniu, więc będzie na auxiliaryArray
	// po starych nodach root listy nie możemy, bo kto wie, czy nie zostały zepchnięte do dzieci

	degree = instance->maxDegree;

	error(MODULE_NAME,"Odtwarzanie root listy...");

	for ( degree-- ; degree > 0; degree-- ) {
		nextRootNode = auxiliaryArray[degree];
		if (nextRootNode) {	//TOREMOVE
			error(MODULE_NAME,"auxiliaryArray[%u] %u (dL: %u, d: %u, m: %u).",degree,nextRootNode->data->nodeID,nextRootNode->data->distanceLabel,nextRootNode->degree,nextRootNode->mark);

		} else {
			error(MODULE_NAME,"auxiliaryArray[%u] = null",degree);

		}	// TO REMOVE
		if (nextRootNode) {
			auxiliaryArray[degree] = NULL;			/* czyścimy tutaj zamiast na początku - 1 petla mniej*/
			nextRootNode->parent = NULL;
			minNode = concatTMHFibNode(minNode,nextRootNode);
		}
	}

	nextRootNode = auxiliaryArray[0];
	if (nextRootNode) {	//TOREMOVE
		error(MODULE_NAME,"auxiliaryArray[%u] %u (dL: %u, d: %u, m: %u).",degree,nextRootNode->data->nodeID,nextRootNode->data->distanceLabel,nextRootNode->degree,nextRootNode->mark);

	} else {
		error(MODULE_NAME,"auxiliaryArray[%u] = null",degree);

	}	// TO REMOVE
	if (nextRootNode) {
		auxiliaryArray[0] = NULL;
		nextRootNode->parent = NULL;
		minNode = concatTMHFibNode(minNode,nextRootNode);
	}

	instance->minNode = minNode;
	printFib(instance->minNode,0);

}

void decreaseKey( TMHFibHeap* H, TMHFibNode* x, TMHNodeData k ) {
	TMHFibNode* y;
	x->data->distanceLabel = k;
	y = x->parent;
/*
	printf("%u Decreasing  %u (dl: %u, d: %u)\n",H->numberOfNodes,x->data->nodeID,x->data->distanceLabel,x->degree);
	printFib(H->minNode,0);
	printf("\n-------------------------------------------------------\n");
*/

	if ( y != NULL && x->data->distanceLabel < y->data->distanceLabel ) {
		CUT(H,x,y);
		cascCUT(H,y);
	}
	if ( x->data->distanceLabel < H->minNode->data->distanceLabel ) {
		H->minNode = x;
	}
}

/* y to parent x'a */
void CUT( TMHFibHeap* H, TMHFibNode* x, TMHFibNode* y ) {
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

void cascCUT( TMHFibHeap* H, TMHFibNode* y ) {
	TMHFibNode* z = y->parent;
	if (z != NULL ) {
		if ( y->mark == false ) {
			y->mark = true;
		} else {
			CUT(H,y,z);
			cascCUT(H,z);
		}
	}
}


void decreaseKeyTMHFibHeap( TMHFibHeap* const instance, TMHFibNode* const node, const TMHNodeIdx newKey ) {
	TMHFibNode* parentNode;
	TMHNode* tmpData = node->data;
	TMHNode* minData = instance->minNode->data;
	if ( newKey > tmpData->distanceLabel ) {
		return;
	}
	//tmpData->distanceLabel = newKey;	// Klucz jest zmniejszany w algorytmie, 2x nie trzeba
	parentNode = node->parent;
	if ( parentNode != NULL && tmpData->distanceLabel < parentNode->data->distanceLabel ) {
		cutTMHFibHeap(instance->minNode,node,parentNode);
		cascadingCutTMHFibHeap(instance->minNode,parentNode);
	}
	if( tmpData->distanceLabel < minData->distanceLabel ) {
		minData = tmpData;
	}
}

static void cutTMHFibHeap( TMHFibNode* const minNode, TMHFibNode* const node, TMHFibNode* const parentNode ) {
	/* Wyjęcie z listy dzieci*/
	node->next->prev = node->prev;
	node->prev->next = node->next;
	parentNode->degree -= 1;

	/* Dodanie do root listy */
	minNode->next->prev = node->prev;
	node->prev->next = minNode->next;
	minNode->next = node;
	node->prev = minNode;

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

void printFib( TMHFibNode* minNode, int lvl ) {
/*	static int a = 0;*/
	if ( minNode ) {
	//	a += 1;
	//	if ( a > 2000 ) exit(1);
		TMHFibNode* end = minNode;
		TMHFibNode* cur = minNode;
		do {
			printf("\n");
			for ( int i = 0; i < lvl; i += 1) {
				printf(" ");
			}
			printf("NID: %u DL: %u F<: %u F>: %u Fd: %u",cur->data->nodeID,cur->data->distanceLabel,cur->prev->data->nodeID,cur->next->data->nodeID,cur->degree);
			if (cur->parent) {
				printf(" F^: %u",cur->parent->data->nodeID);
			}
			if (cur->childList) {
				printf(" F_: %u",cur->childList->data->nodeID);
				printFib(cur->childList,lvl+1);
				printf("\nF_end: %u",cur->childList->data->nodeID);
			}
			cur = cur->next;
		} while ( cur != end );
	}
}
