/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHConfig.c
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

#include "../Headers/TMHConfig.h"				/* TMHNodeIdx, TMHNodeData, TMHGraph, TMHNode, bool */
#include "../Headers/Helpers/TMHIOHelper.h"		/* getGraphData() */

#include "../Headers/Helpers/TMHAllocHelper.h"	/* memMalloc(), memFree() */

#include "../Headers/TMHLogger.h"				/* debug() */
#include "../Headers/Helpers/TMHErrors.h"		/* debug_instanceDeletedSuccessfully */

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHConfig";


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

TMHConfig* loadTMHConfigInstance ( const char* const filename ) {
	return getConfigData(filename);
}

TMHConfig* createTMHConfigInstance( const TMHNodeIdx numberOfSource, const TMHConfigAlgorithmMode algMode ) {
	TMHConfig* newConfig = memMalloc(1,sizeof(TMHConfig));
	newConfig->numberOfSource = numberOfSource;
	newConfig->mode = algMode;

	newConfig->sourceNodeIdxArray = memMalloc(numberOfSource,sizeof(TMHNodeIdx));

	if ( algMode == POINT_TO_POINT ) {
		newConfig->targetNodeIdxArray = memMalloc(numberOfSource,sizeof(TMHNodeIdx));
	}
	return newConfig;
}

void destroyTMHConfigInstance ( TMHConfig* const config ) {
	memFree(config->sourceNodeIdxArray);
	if ( config->mode == POINT_TO_POINT ) {
		memFree(config->targetNodeIdxArray);
	}
	memFree(config);
	debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
}

bool checkTMHConfig( const TMHConfig* const configuration ) {
	bool resoult = true;
	resoult &= (configuration != NULL);
	return resoult;
}

void addSourceToRest( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, TMHNodeIdx* const numberOfSource ) {
	config->sourceNodeIdxArray[--(*(numberOfSource))] = *(fromNodeID);
}

void addPointToPoint( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, const TMHNodeIdx* const toNodeID, TMHNodeIdx* const numberOfSource ) {
	config->sourceNodeIdxArray[--(*(numberOfSource))] = *(fromNodeID);
	config->targetNodeIdxArray[*(numberOfSource)] = *(toNodeID);
}
