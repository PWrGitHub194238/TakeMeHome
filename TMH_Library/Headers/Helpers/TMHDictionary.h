/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMHDictionary.h
 * @author tomasz
 * @date 31 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMHDictionary.h
 *
 *  Created on: 31 sie 2014
 *      Author: tomasz
 */

#ifndef TMHDICTIONARY_H_
#define TMHDICTIONARY_H_

/*
 * Includes
 *
 */


/*
 * Typedefs
 *
 */

typedef enum AlgorithmAbbreviation {
	BFM,
	BFP,
	DKQ,
	DKB,
	DKM,
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

/*
 * Externs
 *
 */

extern const char* dictionary_TMHAlgorithmAbbreviation[];
extern const char* dictionary_TMHAlgorithmFullName[];

extern const char* dictionary_TMHConfigAlgorithmModeShortcut[];
extern const char* dictionary_TMHConfigAlgorithmMode[];


/*
 * Declarations
 *
 */


#endif /* TMHDICTIONARY_H_ */
