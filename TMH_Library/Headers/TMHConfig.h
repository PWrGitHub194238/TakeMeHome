/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHConfig.h
 * @author tomasz
 * @date 31 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHConfig.h
 *
 *  Created on: 31 sie 2014
 *      Author: tomasz
 */

#ifndef TMHCONFIG_H_
#define TMHCONFIG_H_

/*
 * Includes
 *
 */

#include <stdbool.h>			/* bool */

#include "TMH.h"				/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef enum GraphStructAbbreviation {
	ADJACENCY_LIST
} GraphStructAbbreviation;

typedef enum GraphOrder {
	NONE,
	TOPOLOGIC
} GraphOrder;

typedef enum AlgorithmAbbreviation {
	BFM,
	BFP,
	DKQd,
	DKQs,
	DKB,
	DKM,
	DDL,
	DKA,
	DKD,
	DKF,
	DKH,
	DKR,
	PAP,
	TQQ,
	THR,
	GR1,
	GR2
} AlgorithmAbbreviation;

typedef enum TMHConfigAlgorithmMode {
	SINGLE_SOURCE,
	POINT_TO_POINT
} TMHConfigAlgorithmMode;

typedef struct TMHConfig {
	GraphStructAbbreviation graphStruct;
	GraphOrder graphOrder;
	AlgorithmAbbreviation algorithm;
	TMHConfigAlgorithmMode mode;
	TMHNodeIdx numberOfSources;
	TMHNodeIdx numberOfTargets;
	TMHNodeIdx* sourceNodeIdxArray;
	TMHNodeIdx* targetNodeIdxArray;
	bool checkConfig;
	bool checkGraph;
	bool allowInterrupt;
	TMHNodeData* defaultParameter;
} TMHConfig;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

/** Tworzy konfigurację. 2 listy, jeżeli jest wybrany tryb pracy P2P.
 *
 * @param numberOfSources
 * @param algMode
 * @return
 */
TMHConfig* createTMHConfigInstance( const TMHNodeIdx numberOfSources, const TMHConfigAlgorithmMode algMode );

bool checkTMHConfig( const TMHConfig* const configuration );

void destroyTMHConfigInstance ( TMHConfig* const configuration );

void addSourceToRest( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, TMHNodeIdx* const numberOfSources );
void addPointToPoint( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, const TMHNodeIdx* const toNodeID, TMHNodeIdx* const numberOfSources );

#endif /* TMHCONFIG_H_ */
