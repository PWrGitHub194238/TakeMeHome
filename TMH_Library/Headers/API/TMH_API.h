/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMH_API.h
 * @author tomasz
 * @date 7 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMH_API.h
 *
 *  Created on: 7 wrz 2014
 *      Author: tomasz
 */

#ifndef TMH_API_H_
#define TMH_API_H_

/*
 * Includes
 *
 */

#include <stdbool.h>										/* bool */

#include "../../Headers/Helpers/TMHDictionary.h"			/* AlgorithmAbbreviation */
#include "../../Headers/TMHConfig.h"						/* TMHConfig */
/*
 * Typedefs
 *
 */



/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */


TMHConfig* createTMHConfig( const char* const configDataFilePath, bool dumpConfig );

void setGraphStruct( TMHConfig* config, const GraphStructAbbreviation graphStruct );
void setGraphOrder( TMHConfig* config, const GraphOrder graphOrder );
void setAlgorithm( TMHConfig* config, const AlgorithmAbbreviation algorithm );
void setCheckConfig( TMHConfig* config, const bool checkConfig );

/**
 *
 * @param config
 * @param allowInterrupt
 * @param defaultParam jeśli null i ai = true to liczy sam default
 */
void setAllowInterrupt( TMHConfig* config, const bool allowInterrupt, TMHNodeData* const defaultParam );

void* createTMHAlgorithmInstance( TMHConfig* const config, const char* const graphDataFilePath );
void runTMHAlgorithm(const AlgorithmAbbreviation algorithm, void* instance);

void destroyTMHAlgorithmInstancje(const AlgorithmAbbreviation algorithm, void* instance, bool withConfig );

void rebuildGraph( const GraphStructAbbreviation graphStruct, const GraphOrder graphOrder, void* sourceGraph );
#endif /* TMH_API_H_ */
