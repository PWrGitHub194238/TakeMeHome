/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHIOHelper.c
 * @author tomasz
 * @date 17 sie 2014
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

#include "../../Headers/Helpers/TMHIOHelper.h"			/* TMHGraph, TMHConfig,
														createTMHGraphInstance(), addArc(),
														createTMHConfigInstance(), addSourceToRest(),
 	 	 	 	 	 	 	 	 	 	 	 	 	 	addPointToPoint()*/

#include <stdio.h>										/* FILE, NULL */
#include <string.h>										/* strcmp() */

#include "../../Headers/Helpers/TMHDictionary.h"		/* dictionary_TMHConfigAlgorithmModeShortcut */
#include "../../Headers/Helpers/TMHErrors.h"			/* err_TMHIOHelper_cannotOpenFile
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_startReadFile
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_problemDefinitionLineReaded
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_arcDefinitionLineReaded
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_auxiliaryProblemDefinitionLineReaded
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_auxiliarySSDefinitionLineReaded
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 info_TMHIOHelper_auxiliaryP2PDefinitionLineReaded
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 */
#include "../../Headers/TMH.h"							/* TMHNodeIdx, TMHNodeData
														*/
#include "../../Headers/TMHLogger.h"					/* void error( char*, char *__restrict, ... )
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 void info( char*, char *__restrict, ... )*/
#include "../../Headers/Helpers/TMHAllocHelper.h"		/* memAlloc(), memFree()*/



/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHIOHelper";

static const int C_LINE_ARGC = 0;
static const int P_LINE_ARGC = 2;
static const int A_LINE_ARGC = 3;
static const int S_LINE_ARGC = 1;
static const int Q_LINE_ARGC = 2;

/*
 * Globals
 *
 */



/*
 * Private declarations
 *
 */

static TMHGraph* getGraphData( FILE* const dataFile );

/*
 * Definitions
 *
 */

void* getGraphDataWrapper( TMHConfig* const config, const char* const filename ) {
	FILE* dataFile = NULL;
	TMHGraph* graphData = NULL;
	dataFile = fopen(filename,"r");
	if ( dataFile == NULL ) {
		error(MODULE_NAME,err_TMHIOHelper_cannotOpenFile,filename);
	} else {
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHIOHelper_startReadFile,filename);
		}
		switch(config->graphStruct) {
		case ADJACENCY_LIST:
			graphData = getGraphData(dataFile);
			break;
		}
		if (config->dumpConfig) {
			generateDumpConfig(config,graphData->numberOfNodes);
		}
	}
	return graphData;
}

static TMHGraph* getGraphData( FILE* const dataFile ) {
	TMHGraph* graph = NULL;
	TMHNodeIdx numberOfNodes;
	TMHNodeIdx numberOfArcs;
	TMHNodeIdx fromNodeID,toNodeID;
	TMHArcCost distanceLabel;
	TMHArcCost maxArcCost = 0;

	while ( !feof(dataFile) ) {
		switch (fgetc(dataFile)) {
		case 'c':
			if ( fscanf(dataFile, "%*[^\n]\n") != C_LINE_ARGC ) {
				fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
				return NULL;
			}
			break;
		case 'p':
			if ( fscanf(dataFile," %*[^ ] %u %u\n",&numberOfNodes,&numberOfArcs) == P_LINE_ARGC ) {
				if (isInfoLogEnabled()) {
					info(MODULE_NAME,info_TMHIOHelper_problemDefinitionLineReaded,
							"Shortest Path Problem",numberOfNodes,numberOfArcs);
				}
				graph = createTMHGraphInstance(&numberOfNodes,&numberOfArcs);
			} else {
				fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
				return NULL;
			}
			break;
		case 'a':
			if ( fscanf(dataFile," %u %u %u\n",&fromNodeID,&toNodeID,&distanceLabel) == A_LINE_ARGC ) {
				if (isInfoLogEnabled()) {
					info(MODULE_NAME,info_TMHIOHelper_arcDefinitionLineReaded,
							fromNodeID,distanceLabel,toNodeID);
				}
				maxArcCost = ( (maxArcCost < distanceLabel) ? distanceLabel : maxArcCost);
				addArc(graph->nodeArray[fromNodeID],graph->nodeArray[toNodeID],&distanceLabel);
			} else {
				fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
				return NULL;
			}
		}
	}
	graph->maxArcCost = maxArcCost;
	fclose(dataFile);
	return graph;
}

TMHConfig* getConfigData( const char* const filename, bool dumpConfig ) {
	TMHConfig* config = NULL;
	FILE* dataFile = NULL;
	char* algMode = NULL;

	TMHNodeIdx numberOfSources;
	TMHNodeIdx fromNodeID,toNodeID;

	dataFile = fopen(filename,"r");
	if ( dataFile == NULL ) {
		error(MODULE_NAME,err_TMHIOHelper_cannotOpenFile,filename);
	} else {
		if (isInfoLogEnabled()) {
			info(MODULE_NAME,info_TMHIOHelper_startReadFile,filename);
		}
		while ( !feof(dataFile) ) {
			switch (fgetc(dataFile)) {
			case 'c':
				if ( fscanf(dataFile, "%*[^\n]\n") != C_LINE_ARGC ) {
					fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
					return NULL;
				}
				break;
			case 'p':
				algMode = memMalloc(3,sizeof(char));
				if ( fscanf(dataFile," %*[^ ] %*[^ ] %s %u",algMode,&numberOfSources) == P_LINE_ARGC ) {
					if (isInfoLogEnabled()) {
						info(MODULE_NAME,info_TMHIOHelper_auxiliaryProblemDefinitionLineReaded,
								"Shortest Path Problem",algMode,numberOfSources);
					}
					if ( !strcmp(algMode,dictionary_TMHConfigAlgorithmModeShortcut[SINGLE_SOURCE]) ) {
						config = createTMHConfigInstance(dumpConfig,numberOfSources,SINGLE_SOURCE);
					} else if ( strcmp(algMode,dictionary_TMHConfigAlgorithmModeShortcut[POINT_TO_POINT]) ) {
						config = createTMHConfigInstance(dumpConfig,numberOfSources,POINT_TO_POINT);
					}
					memFree(algMode);
					if (dumpConfig) {
						fclose(dataFile);
						return config;
					}
				} else {
					fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
					return NULL;
				}
				break;
			case 's':
				if ( fscanf(dataFile," %u\n",&fromNodeID) == S_LINE_ARGC ) {
					if (isInfoLogEnabled()) {
						info(MODULE_NAME,info_TMHIOHelper_auxiliarySSDefinitionLineReaded,fromNodeID);
					}
					addSourceToRest(config,&fromNodeID,&numberOfSources);
				} else {
					fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
					return NULL;
				}
				break;
			case 'q':
				if ( fscanf(dataFile," %u %u\n",&fromNodeID,&toNodeID) == Q_LINE_ARGC ) {
					if (isInfoLogEnabled()) {
						info(MODULE_NAME,info_TMHIOHelper_auxiliaryP2PDefinitionLineReaded,
								fromNodeID,toNodeID);
					}
					addPointToPoint(config,&fromNodeID,&toNodeID,&numberOfSources);
				} else {
					fatal(MODULE_NAME,fatal_TMHIOHelper_errorReadingFile);
					return NULL;
				}
				break;
			}
		}
		fclose(dataFile);
	}
	return config;
}
