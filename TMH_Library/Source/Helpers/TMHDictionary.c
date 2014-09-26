/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHDictionary.c
 * @author tomasz
 * @date 31 sie 2014
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

#include "../../Headers/Helpers/TMHDictionary.h"			/**/

/*
 * Constants
 *
 */

const char* dictionary_TMHAlgorithmAbbreviation[] = {"BFM","BFP","DKQ","DKB","DKM","DKA","DKD","DKF",
		"DKH","DKR","PAP","TQQ","THR","GR1","GR2"};
const char* dictionary_TMHAlgorithmFullName[] = {
		"Bellman-Ford-Moore",
		"Bellman-Ford-Moore (with Parent checking)",
		"Dijkstra's Naive Implementation",
		"Dijkstra's Buckets (Basic implementation)",
		"Dijkstra's Buckets (Overflow Bag)",
		"Dijkstra's Buckets (Approximate)",
		"Dijkstra's Buckets (Double buckets)",
		"Dijkstra's Heap (Fibonacci heap)",
		"Dijkstra's Heap (K-array)",
		"Dijkstra's Heap (R-Heap)",
		"Graph Growth (Pape)",
		"Graph Growth with Two Queues (Pallottino)",
		"Threshold Algorithm",
		"Topological Ordering (Basic implementation)",
		"Topological Ordering (Distance Updates)"};

const char* dictionary_TMHConfigAlgorithmModeShortcut[] = {"ss","p2p"};
const char* dictionary_TMHConfigAlgorithmMode[] = {"Single Source","Point To Point"};


/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */



/*
 * Definitions
 *
 */