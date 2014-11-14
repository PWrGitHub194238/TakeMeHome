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

#include "../../Headers/Helpers/TMHIOHelper.h"				/* getGraphDataWrapper(), getConfigData(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 TMHConfig, GraphStructAbbreviation,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 AlgorithmAbbreviation, GraphOrder
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 */
#include "../../Headers/Helpers/TMHGraphRebuilder.h"

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

TMHConfig* createTMHConfig( const char* const configDataFilePath ) {
	return getConfigData(configDataFilePath);
}

void setGraphStruct( TMHConfig* config, const GraphStructAbbreviation graphStruct ) {
	config->graphStruct = graphStruct;
}

void setGraphOrder( TMHConfig* config, const GraphOrder graphOrder ) {
	config->graphOrder = graphOrder;
}

void setAlgorithm( TMHConfig* config, const AlgorithmAbbreviation algorithm ) {
	config->algorithm = algorithm;
}

void setCheckConfig( TMHConfig* config, const bool checkConfig ) {
	config->checkConfig = checkConfig;
}

void setAllowInterrupt( TMHConfig* config, const bool allowInterrupt ) {
	config->allowInterrupt = allowInterrupt;
}

void* createTMHAlgorithmInstance( TMHConfig* const config, const char* const graphDataFilePath ) {
	void* newGraph;

	if ( config->checkConfig ) {
		if ( checkTMHConfig(config) == false ) {
			return NULL;
		}
	}

	newGraph = getGraphDataWrapper(config->graphStruct,graphDataFilePath);

	switch (config->algorithm) {
	case BFM:
		return createTMHBFMInstance(newGraph, config);
	case BFP:
		return createTMHBFPInstance(newGraph, config);
	case DKQ:
		return createTMHDKQInstance(newGraph, config);
	case DKB:
		return createTMHDKBInstance(newGraph, config);
	case DKM:
		return createTMHDKMInstance(newGraph, config);
	case DKA:
		return createTMHDKAInstance(newGraph, config);
	case DKD:
		return createTMHDKDInstance(newGraph, config);
	case DKF:
		return createTMHDKFInstance(newGraph, config);
	case DKH:
	/*	return createTMHDKHInstance(newGraph, config);*/
	case DKR:
		return createTMHDKRInstance(newGraph, config);
	case PAP:
		return createTMHPAPInstance(newGraph, config);
	case TQQ:
		return createTMHTQQInstance(newGraph, config);
	case THR:
		return createTMHTHRInstance(newGraph, config);
	case GR1:
		return createTMHGR1Instance(newGraph, config);
	case GR2:
		return createTMHGR2Instance(newGraph, config);
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
		/*runDKH(instance);*/
		break;
	case DKR:
		runDKR(instance);
		break;
	case PAP:
		runPAP(instance);
		break;
	case TQQ:
		runTQQ(instance);
		break;
	case THR:
		runTHR(instance);
		break;
	case GR1:
		runGR1(instance);
		break;
	case GR2:
		runGR2(instance);
		break;
	}
}

void destroyTMHAlgorithmInstancje(const AlgorithmAbbreviation algorithm, void* instance, bool withConfig ) {
	switch (algorithm) {
	case BFM:
		destroyTMHBFMInstance(instance,withConfig);
		break;
	case BFP:
		destroyTMHBFPInstance(instance,withConfig);
		break;
	case DKQ:
		destroyTMHDKQInstance(instance,withConfig);
		break;
	case DKB:
		destroyTMHDKBInstance(instance,withConfig);
		break;
	case DKM:
		destroyTMHDKMInstance(instance,withConfig);
		break;
	case DKA:
		destroyTMHDKAInstance(instance,withConfig);
		break;
	case DKD:
		destroyTMHDKDInstance(instance,withConfig);
		break;
	case DKF:
		destroyTMHDKFInstance(instance,withConfig);
		break;
	case DKH:
	/*	destroyTMHDKHInstance(instance,withConfig);*/
		break;
	case DKR:
		destroyTMHDKRInstance(instance,withConfig);
		break;
	case PAP:
		destroyTMHPAPInstance(instance,withConfig);
		break;
	case TQQ:
		destroyTMHTQQInstance(instance,withConfig);
		break;
	case THR:
		destroyTMHTHRInstance(instance,withConfig);
		break;
	case GR1:
		destroyTMHGR1Instance(instance,withConfig);
		break;
	case GR2:
		destroyTMHGR2Instance(instance,withConfig);
		break;
	}
}

void rebuildGraph( const GraphStructAbbreviation graphStruct, const GraphOrder graphOrder, void* sourceGraph ) {
	switch ( graphStruct ) {
	case ADJACENCY_LIST:
		rebuildAdjacencyListGraph(graphOrder,sourceGraph);
		break;
	}
}
