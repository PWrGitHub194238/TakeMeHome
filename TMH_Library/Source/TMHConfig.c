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

#include "../Headers/TMHConfig.h"				/* TMHNodeIdx, TMHNodeData, TMHGraph, TMHNode, bool,
 	 	 	 	 	 	 	 	 	 	 	 	 maxNumberOfSource */
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

static bool checkTMHConficPreConditions( const TMHConfig* const configuration );
static bool checkGraphStruct( const TMHConfig* const configuration );
static bool checkGraphOrder( const TMHConfig* const configuration );
static bool checkAlgorithm( const TMHConfig* const configuration );
static bool checkMode( const TMHConfig* const configuration );
static bool checknumberOfSources( const TMHConfig* const configuration );
static bool checkSourceNodeIdxArray( const TMHNodeIdx numberOfNodes, TMHNodeIdx numberOfSourcess, const TMHNodeIdx* const sourceNodeIdxArray );
static bool checkTargetNodeIdxArray( const TMHNodeIdx numberOfNodes, TMHNodeIdx numberOfTargets, const TMHNodeIdx* const targetNodeIdxArray );

/*
 * Definitions
 *
 */

TMHConfig* createTMHConfigInstance( const bool dumpConfig, const TMHNodeIdx numberOfSources, const TMHConfigAlgorithmMode algMode ) {
	TMHConfig* newConfig = memMalloc(1,sizeof(TMHConfig));
	newConfig->graphStruct = ADJACENCY_LIST;
	newConfig->graphOrder = NONE;
	newConfig->algorithm = BFM;

	newConfig->mode = algMode;
	newConfig->numberOfSources = numberOfSources;

	newConfig->dumpConfig = dumpConfig;

	if (!dumpConfig) {
		newConfig->sourceNodeIdxArray = memMalloc(numberOfSources,sizeof(TMHNodeIdx));

		if ( algMode == POINT_TO_POINT ) {
			newConfig->targetNodeIdxArray = memMalloc(numberOfSources,sizeof(TMHNodeIdx));
		} else {
			newConfig->targetNodeIdxArray = NULL;
		}

		newConfig->checkConfig = true;
	} else {
		newConfig->sourceNodeIdxArray = NULL;
		newConfig->targetNodeIdxArray = NULL;
		newConfig->checkConfig = false;
	}
	newConfig->allowInterrupt = false;

	return newConfig;
}

void destroyTMHConfigInstance ( TMHConfig* const config ) {
	memFree(config->sourceNodeIdxArray);
	if ( config->mode == POINT_TO_POINT ) {
		memFree(config->targetNodeIdxArray);
	}
	memFree(config);
	if (isDebugLogEnabled()) {
		debug(MODULE_NAME,debug_instanceDeletedSuccessfully,MODULE_NAME);
	}
}

bool checkTMHConfig( const TMHConfig* const configuration ) {
	return (configuration != NULL ) && checkTMHConficPreConditions(configuration);
}

static bool checkTMHConficPreConditions( const TMHConfig* const configuration ) {
	bool resoult = true;
	resoult &= checkGraphStruct(configuration);
	resoult &= checkGraphOrder(configuration);
	resoult &= checkAlgorithm(configuration);
	resoult &= checkMode(configuration);
	resoult &= checknumberOfSources(configuration);
	return resoult;
}

bool checkTMHConficPostConditions( const TMHNodeIdx numberOfNodes, const TMHConfig* const configuration ) {
	bool resoult = true;
	resoult &= checkSourceNodeIdxArray(numberOfNodes,configuration->numberOfSources,configuration->sourceNodeIdxArray);
	resoult &= checkTargetNodeIdxArray(numberOfNodes,configuration->numberOfTargets,configuration->targetNodeIdxArray);
	return resoult;
}

static bool checkGraphStruct( const TMHConfig* const configuration ) {
	return configuration->graphStruct <= ADJACENCY_LIST;
}

static bool checkGraphOrder( const TMHConfig* const configuration ) {
	return configuration->graphOrder <= TOPOLOGIC;
}

static bool checkAlgorithm( const TMHConfig* const configuration ) {
	return configuration->algorithm <= GR2;
}

static bool checkMode( const TMHConfig* const configuration ) {
	return configuration->mode <= POINT_TO_POINT;
}

static bool checknumberOfSources( const TMHConfig* const configuration ) {
	return configuration->numberOfSources <= maxNumberOfSource;
}

static bool checkSourceNodeIdxArray( const TMHNodeIdx numberOfNodes, TMHNodeIdx numberOfSources, const TMHNodeIdx* const sourceNodeIdxArray ) {
	for ( numberOfSources--; numberOfSources >0; numberOfSources-- ) {
		if ( sourceNodeIdxArray[numberOfSources] > numberOfNodes ) {
			return false;
		}
	}
	if ( sourceNodeIdxArray[numberOfSources] > numberOfNodes ) {
		return false;
	}
	return true;
}

static bool checkTargetNodeIdxArray( TMHNodeIdx numberOfNodes, TMHNodeIdx numberOfTargets, const TMHNodeIdx* const targetNodeIdxArray ) {
	for ( numberOfTargets--; numberOfTargets > 0; numberOfTargets-- ) {
		if ( targetNodeIdxArray[numberOfTargets] > numberOfNodes ) {
			return false;
		}
	}
	if ( targetNodeIdxArray[numberOfTargets] > numberOfNodes ) {
		return false;
	}
	return true;
}

void addSourceToRest( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, TMHNodeIdx* const numberOfSources ) {
	config->sourceNodeIdxArray[--(*(numberOfSources))] = *(fromNodeID);
}

void addPointToPoint( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, const TMHNodeIdx* const toNodeID, TMHNodeIdx* const numberOfSources ) {
	config->sourceNodeIdxArray[--(*(numberOfSources))] = *(fromNodeID);
	config->targetNodeIdxArray[*(numberOfSources)] = *(toNodeID);
}

void generateDumpConfig( TMHConfig* const config, TMHNodeIdx numberOfNodes ) {
	if ( config->mode == SINGLE_SOURCE ) {
		config->numberOfSources = numberOfNodes;
		config->sourceNodeIdxArray = memMalloc(numberOfNodes,sizeof(TMHNodeIdx));
		for ( ; numberOfNodes > 0; numberOfNodes-- ) {
			config->sourceNodeIdxArray[numberOfNodes-1] = numberOfNodes;
		}
	}
}
