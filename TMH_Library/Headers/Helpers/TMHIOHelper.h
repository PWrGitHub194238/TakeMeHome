/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHIOHelper.h
 * @author tomasz
 * @date 17 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHIOHelper.h
 *
 *  Created on: 17 sie 2014
 *      Author: tomasz
 */

#ifndef TMHIOHELPER_H_
#define TMHIOHELPER_H_

/*
 * Includes
 *
 */

#include "../Structures/TMHGraph.h"			/* TMHGraph */
#include "../TMHConfig.h"					/* TMHConfig, GraphStructAbbreviation, bool */

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

void* getGraphDataWrapper( TMHConfig* const config, const char* const filename  );
TMHConfig* getConfigData( const char* const filename, bool dumpConfig );

#endif /* TMHIOHELPER_H_ */
