/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMH_API.c
 * @author tomasz
 * @date 7 wrz 2014
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

#include "../../Headers/API/TMH_API.h"						/* bool */

#include <stddef.h>											/* NULL */

#include "../../Headers/Helpers/TMHIOHelper.h"				/* getGraphData(), getConfigData() */

#include "../../Headers/Algorithms/THR.h"					/* THR */
#include "../../Headers/Algorithms/Bellman/BFM.h"			/* THR */
#include "../../Headers/Algorithms/Bellman/BFP.h"			/* THR */
#include "../../Headers/Algorithms/Dijkstra/DKQ.h"			/* THR */
#include "../../Headers/Algorithms/Dijkstra/Buckets/DKA.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Buckets/DKB.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Buckets/DKD.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Buckets/DKM.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Heaps/DKF.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Heaps/DKH.h"	/* THR */
#include "../../Headers/Algorithms/Dijkstra/Heaps/DKR.h"	/* DKR */
#include "../../Headers/Algorithms/GraphGrowth/PAP.h"		/* PAP */
#include "../../Headers/Algorithms/GraphGrowth/TQQ.h"		/* TQQ */
#include "../../Headers/Algorithms/Topological/GR1.h"		/* GR1 */
#include "../../Headers/Algorithms/Topological/GR2.h"		/* GR2 */

/*
 * Constants
 *
 */

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

void* createTMHAlgorithmInstance(const AlgorithmAbbreviation algorithm,
		const char* const graphDataFilePath,
		const char* const configDataFilePath, bool checkConfig, bool allowInterrupt ) {
	TMHGraph* newGraph = getGraphData(graphDataFilePath);
	TMHConfig* config = getConfigData(configDataFilePath);
	switch (algorithm) {
	case BFM:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case BFP:
		return createTMHBFPInstance(newGraph, config, checkConfig);
	case DKQ:
		return createTMHDKQInstance(newGraph, config, checkConfig);
	case DKB:
		return createTMHDKBInstance(newGraph, config, checkConfig);
	case DKM:
		return createTMHDKMInstance(newGraph, config, checkConfig, allowInterrupt);
	case DKA:
		return createTMHDKAInstance(newGraph, config, checkConfig, allowInterrupt);
	case DKD:
		return createTMHDKDInstance(newGraph, config, checkConfig, allowInterrupt);
	case DKF:
		return createTMHDKFInstance(newGraph, config, checkConfig);
	case DKH:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case DKR:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case PAP:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case TQQ:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case THR:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case GR1:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	case GR2:
		return createTMHBFMInstance(newGraph, config, checkConfig);
	default:
		return NULL;
	}
}

void runTMHAlgorithm(const AlgorithmAbbreviation algorithm, void* instance) {
	switch (algorithm) {
	case BFM:
		runBFM(instance);
		break;
	case BFP:
		runBFP(instance);
		break;
	case DKQ:
		runDKQ(instance);
		break;
	case DKB:
		runDKB(instance);
		break;
	case DKM:
		runDKM(instance);
		break;
	case DKA:
		runDKA(instance);
		break;
	case DKD:
		runDKD(instance);
		break;
	case DKF:
		runDKF(instance);
		break;
	case DKH:
		break;
	case DKR:
		break;
	case PAP:
		break;
	case TQQ:
		break;
	case THR:
		break;
	case GR1:
		break;
	case GR2:
		break;
	}
}
