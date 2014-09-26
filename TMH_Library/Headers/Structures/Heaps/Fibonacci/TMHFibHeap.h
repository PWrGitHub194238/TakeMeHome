/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHFibHeap.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHFibHeap.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHFIBHEAP_H_
#define TMHFIBHEAP_H_

/*
 * Includes
 *
 */

#include "TMHFibNode.h"				/* TMHFibNode, TMHNode */

#include "../../../TMH.h"			/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

#define M_1_LOG_E_PHI 2.07808692123502753760 /* 1/log((1 + √(5))/2) = 1/log_e(Phi)*/

/**
 * wska�nik na rootList = minimalny w�ze�
 * lista jest zamnki�ta, wi�c mo�emy sobie szansta� tym wska�nikiem
 */
typedef struct TMHFibHeap {
	TMHFibNode* minNode;
	TMHNodeIdx numberOfNodes;
} TMHFibHeap;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHFibHeap* createSingleTMHFibHeapInstance( TMHFibNode* rootNode );

/**
 * Tworzy nowy kopiec, ustawiajac minNode rootNode i ustawia liczbe wezlow w kopcu.
 * Ilosc - dlugosc listy rootNode.
 * rootNode - wezel robiacy jednoczesnie za element listy dwukierunkowej.
 * Jedyny sposob na jej konstrukcje to concatTMHFibDLList(), ktory zawsze zwraca wskaznik
 * na element listy spelniajacy warunki bycia minNode.
 */
TMHFibHeap* createTMHFibHeapInstance( TMHFibNode* rootNode );

void destroyTMHFibHeapInstance( TMHFibHeap* const instance );

void insertSingleTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* nodeList );

/**
 * Dodaje nody do kopca (do roor listy).
 * Jesli nodeList jest puste to nic nie rob. Wpp. polacz listy i ustaw minNode.
 * Takze zakladamy, ze i rootLista z instance i nodeList wskazuja na nody o wlasnosci minNode
 * Jesli listSize = 0 to sprawdz recznie
 */
void insertTMHFibHeapInstance( TMHFibHeap* const instance, TMHFibNode* nodeList, const TMHNodeIdx* const listSize );

/**
 * Zwraca minNode.
 */
TMHFibNode* getMinimumTMHFibHeap( const TMHFibHeap* const instance );

/**
 * insertTMHFibHeapInstance() i zwraca pierwszy kopiec - heap1
 */
TMHFibHeap* unionTMHFibHeap( TMHFibHeap* const heap1, const TMHFibHeap* const heap2 );

TMHNode* removeMinimumTMHFibHeap( TMHFibHeap* const instance );

void decreaseKeyTMHFibHeap( TMHFibHeap* const instance, TMHFibNode* const node, const TMHNodeIdx* newKey );

/** !!! Operujemy na unsigned - minimum to 0, wiec nie moze byc innych nodow z kosztem 0 ( co w arunkach drogowych raczej jest bez sensu, wiec jest ok)
 *
 * @param instance
 * @param node
 * @return
 */
TMHNode* deleteNodeTMHFibHeap( TMHFibHeap* const instance, TMHFibNode* const node );

#endif /* TMHFIBHEAP_H_ */
