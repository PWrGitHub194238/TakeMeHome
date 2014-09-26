/*
 * TMHAlllocHelper.h
 *
 *  Created on: 3 sie 2014
 *      Author: tomasz
 */

#ifndef TMHALLLOCHELPER_H_
#define TMHALLLOCHELPER_H_

#include <stddef.h>				/* size_t */

/**
 *
 * @param object
 *
 * @throws info_TMHAllocHelper_cannotFreeNull - when
 */
void memFree( void* object );

/**
 *
 * @param elements
 * @param sizeofStructure
 *
 * @throws err_TMHAllocHelper_mallocFailure -
 */
void* memMalloc( const size_t elements, const size_t sizeofStructure ) __attribute__((alloc_size(1,2)));

void* memCalloc( const size_t elements, const size_t sizeofStructure ) __attribute__((alloc_size(1,2)));

#endif /* TMHALLLOCHELPER_H_ */
