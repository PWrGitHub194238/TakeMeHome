/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file DKR.h
 * @author tomasz
 * @date 10 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * Dijkstra's Heap -- R--Heap
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * Includes
 *
 */

#include "../../../../Headers/Algorithms/Dijkstra/Heaps/DKR.h"	/* TMHGraph, TMHConfig, TMHNodeIdx, bool,
																destroyTMHGraphInstance(),
																destroyTMHConfigurationInstance(),*/

#include "../../../../Headers/Helpers/TMHAlgorithmHelper.h"		/* reinitializeTMHGraph() */
#include "../../../../Headers/Helpers/TMHAllocHelper.h"			/* memMalloc(), memFree() */

#include "../../../../Headers/Helpers/TMHDictionary.h"			/* dictionary_TMHConfigAlgorithmMode,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 dictionary_TMHAlgorithmFullName,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 DKR */
#include "../../../../Headers/TMHLogger.h"						/* info(), warn(), trace() */
#include "../../../../Headers/Helpers/TMHErrors.h"				/* debug_DKR_instanceDeletedSuccessfully,
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 trace_ */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "DKR";


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

TMH_DKR* createTMHDKRInstance( TMHGraph* const graphData, TMHConfig* const configuration ) {
	TMH_DKR* newInstance = memMalloc(1,sizeof(TMH_DKR));
	newInstance->graphData = graphData;
	newInstance->configuration = configuration;
	return newInstance;
}

void destroyTMHDKRInstance ( TMH_DKR* const instance, bool withConfig ) {
	destroyTMHGraphInstance(instance->graphData);
	if (withConfig) {
		destroyTMHConfigInstance(instance->configuration);
	}
	memFree(instance);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

void runDKR( TMH_DKR* const instance ) {
	switch (instance->configuration->mode) {
	case SINGLE_SOURCE:
		runDKR_SingleSourceWrapper(instance->graphData,instance->configuration->sourceNodeIdxArray,instance->configuration->numberOfSources);
		break;
	case POINT_TO_POINT:
		break;
	default:
		warn(MODULE_NAME,warning_TMHConfig_invalidMode,dictionary_TMHConfigAlgorithmMode[instance->configuration->mode]);
	}
}

void runDKR_SingleSourceWrapper ( TMHGraph* const graph, const TMHNodeIdx* const sourceNodeArray, const TMHNodeIdx sourceNodeArraySize ) {
	TMHNode* source = NULL;
	TMHNodeIdx i;
	for ( i = 0; i < sourceNodeArraySize; i++ ) {
		source = graph->nodeArray[sourceNodeArray[i]];
		info(MODULE_NAME,info_TMHAlgorithmHelper_SSSummaryBeforeExecution,
				dictionary_TMHAlgorithmFullName[DKR],
				dictionary_TMHConfigAlgorithmMode[SINGLE_SOURCE],
				source->nodeID);
		runDKR_SingleSource(graph,source);
	}
}

void runDKR_SingleSource ( TMHGraph* const graph, TMHNode* const sourceNode  ) {

}
