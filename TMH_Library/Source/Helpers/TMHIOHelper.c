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

TMHGraph* getGraphData( const char* const filename ) {
	TMHGraph* graph = NULL;
	FILE* dataFile = NULL;
	TMHNodeIdx numberOfNodes;
	TMHNodeIdx numberOfArcs;
	TMHNodeIdx fromNodeID,toNodeID;
	TMHArcCost distanceLabel;
	TMHArcCost maxArcCost = 0;

	dataFile = fopen(filename,"r");
	if ( dataFile == NULL ) {
		error(MODULE_NAME,err_TMHIOHelper_cannotOpenFile,filename);
	} else {
		info(MODULE_NAME,info_TMHIOHelper_startReadFile,filename);
		while ( !feof(dataFile) ) {
			switch (fgetc(dataFile)) {
			case 'c':
				fscanf(dataFile, "%*[^\n]\n");
				break;
			case 'p':
				fscanf(dataFile," %*[^ ] %u %u\n",&numberOfNodes,&numberOfArcs);
				info(MODULE_NAME,info_TMHIOHelper_problemDefinitionLineReaded,
						"Shortest Path Problem",numberOfNodes,numberOfArcs);
				graph = createTMHGraphInstance(&numberOfNodes,&numberOfArcs);
				break;
			case 'a':
				fscanf(dataFile," %u %u %u\n",&fromNodeID,&toNodeID,&distanceLabel);
				info(MODULE_NAME,info_TMHIOHelper_arcDefinitionLineReaded,
						fromNodeID,distanceLabel,toNodeID);
				maxArcCost = ( (maxArcCost < distanceLabel) ? distanceLabel : maxArcCost);
				addArc(graph,&fromNodeID,&toNodeID,&distanceLabel);
			}
		}
		graph->maxArcCost = maxArcCost;
		fclose(dataFile);
	}
	return graph;
}

TMHConfig* getConfigData( const char* const filename ) {
	TMHConfig* config = NULL;
	FILE* dataFile = NULL;
	char* algMode = NULL;

	TMHNodeIdx numberOfSource;
	TMHNodeIdx fromNodeID,toNodeID;

	dataFile = fopen(filename,"r");
	if ( dataFile == NULL ) {
		error(MODULE_NAME,err_TMHIOHelper_cannotOpenFile,filename);
	} else {
		info(MODULE_NAME,info_TMHIOHelper_startReadFile,filename);
		while ( !feof(dataFile) ) {
			switch (fgetc(dataFile)) {
			case 'c':
				fscanf(dataFile, "%*[^\n]\n");
				break;
			case 'p':
				algMode = memMalloc(3,sizeof(char));
				fscanf(dataFile," %*[^ ] %*[^ ] %s %u",algMode,&numberOfSource);
				info(MODULE_NAME,info_TMHIOHelper_auxiliaryProblemDefinitionLineReaded,
						"Shortest Path Problem",algMode,numberOfSource);
				if ( !strcmp(algMode,dictionary_TMHConfigAlgorithmModeShortcut[SINGLE_SOURCE]) ) {
					config = createTMHConfigInstance(numberOfSource,SINGLE_SOURCE);
				} else if ( strcmp(algMode,dictionary_TMHConfigAlgorithmModeShortcut[POINT_TO_POINT]) ) {
					config = createTMHConfigInstance(numberOfSource,POINT_TO_POINT);
				}
				memFree(algMode);
				break;
			case 's':
				fscanf(dataFile," %u\n",&fromNodeID);
				info(MODULE_NAME,info_TMHIOHelper_auxiliarySSDefinitionLineReaded,fromNodeID);
				addSourceToRest(config,&fromNodeID,&numberOfSource);
				break;
			case 'q':
				fscanf(dataFile," %u %u\n",&fromNodeID,&toNodeID);
				info(MODULE_NAME,info_TMHIOHelper_auxiliaryP2PDefinitionLineReaded,
						fromNodeID,toNodeID);
				addPointToPoint(config,&fromNodeID,&toNodeID,&numberOfSource);
				break;
			}
		}
		fclose(dataFile);
	}
	return config;
}