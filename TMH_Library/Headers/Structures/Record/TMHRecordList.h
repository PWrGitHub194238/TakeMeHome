/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHRecordList.h
 * @author tomasz
 * @date 14 wrz 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHRecordList.h
 *
 *  Created on: 14 wrz 2014
 *      Author: tomasz
 */

#ifndef TMHRecordLIST_H_
#define TMHRecordLIST_H_

/*
 * Includes
 *
 */

#include "TMHRecord.h"			/* TMHRecord */

/*
 * Typedefs
 *
 */

typedef struct TMHRecordList {
	TMHRecord* record;
	struct TMHRecordList* nextElement;
} TMHRecordList;

/*
 * Externs
 *
 */



/*
 * Declarations
 *
 */

TMHRecordList* createTMHRecordListInstance( TMHRecord* const newRecord );
void destroyTMHRecordListInstance ( TMHRecordList* const instance );

/** Wstawia na początek listy i zwraca wskaźnik do nowego elementu
*/
TMHRecordList* pushTMHRecordList ( TMHRecordList* const recordListBegin, TMHRecord* const newRecord );

#endif /* TMHRecordLIST_H_ */
