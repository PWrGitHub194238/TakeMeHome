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

typedef enum TMHConfigAlgorithmMode {
	SINGLE_SOURCE,
	POINT_TO_POINT
} TMHConfigAlgorithmMode;

typedef struct TMHConfig {
	TMHNodeIdx numberOfSource;
	TMHNodeIdx* sourceNodeIdxArray;
	TMHNodeIdx* targetNodeIdxArray;
	TMHConfigAlgorithmMode mode;
} TMHConfig;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHConfig* loadTMHConfigInstance( const char* const filename );

/** Tworzy konfigurację. 2 listy, jeżeli jest wybrany tryb pracy P2P.
 *
 * @param numberOfSource
 * @param algMode
 * @return
 */
TMHConfig* createTMHConfigInstance( const TMHNodeIdx numberOfSource, const TMHConfigAlgorithmMode algMode );

bool checkTMHConfig( const TMHConfig* const configuration );

void destroyTMHConfigInstance ( TMHConfig* const configuration );

void addSourceToRest( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, TMHNodeIdx* const numberOfSource );
void addPointToPoint( TMHConfig* const config, const TMHNodeIdx* const fromNodeID, const TMHNodeIdx* const toNodeID, TMHNodeIdx* const numberOfSource );

#endif /* TMHCONFIG_H_ */
