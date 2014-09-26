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

void* createTMHAlgorithmInstance( const AlgorithmAbbreviation algorithm, const char* const graphDataFilePath,  const char* const configDataFilePath, bool checkConfig, bool allowInterrupt );
void runTMHAlgorithm ( const AlgorithmAbbreviation algorithm, void* instance );

#endif /* TMH_API_H_ */
