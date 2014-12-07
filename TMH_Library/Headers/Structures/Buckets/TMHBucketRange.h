/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHBucketRange.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHFibNode.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMHBUCKETRANGE_H_
#define TMHBUCKETRANGE_H_

/*
 * Includes
 *
 */

#include "../../TMH.h"		/* TMHNodeIdx */

/*
 * Typedefs
 *
 */

typedef struct TMHBucketRange {
	TMHNodeIdx begin;
	TMHNodeIdx size;
	TMHNodeIdx end;

} TMHBucketRange;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHBucketRange* createBucketRangeInstance( TMHNodeIdx begin, TMHNodeIdx size );

void destroyTMHBucketRangeInstance( TMHBucketRange* const instance );

#endif /* TMHBUCKETRANGE_H_ */
