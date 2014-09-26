/*
 * TMHAlllocHelper.c
 *
 *  Created on: 3 sie 2014
 *      Author: tomasz
 */

/*
 * Includes
 *
 */

#include "../../Headers/Helpers/TMHAllocHelper.h"

#include <stdlib.h>				/* free(void *__ptr), malloc(size_t __size) */

#include "../../Headers/TMHLogger.h"
#include "../../Headers/Helpers/TMHErrors.h"

/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHAllocHelper";

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

void memFree( void* object ) {
	if ( object == NULL ) {
		info(MODULE_NAME,info_TMHAllocHelper_cannotFreeNull);
	} else {
		free(object);
		object = NULL;
	}
}

void* memMalloc( const size_t elements, const size_t sizeofStructure ) {
	void* temp = malloc(elements*sizeofStructure);
	if ( temp == NULL ) {
		error(MODULE_NAME,err_TMHAllocHelper_mallocFailure,elements,sizeofStructure);
	}
	return temp;
}

void* memCalloc( const size_t elements, const size_t sizeofStructure ) {
	void* temp = calloc(elements,sizeofStructure);
	if ( temp == NULL ) {
		error(MODULE_NAME,err_TMHAllocHelper_callocFailure,elements,sizeofStructure);
	}
	return temp;
}
