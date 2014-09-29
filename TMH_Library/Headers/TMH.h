/****************************************************************************
 * Copyright (C) 2014 by 				                                 	*
 *                                                                          *
 ****************************************************************************/

/**
 * @file TMH.h
 * @author tomasz
 * @date 15 sie 2014
 * @brief Brief description goes here.
 *
 * @details Detailed description goes here.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/
 */

/*
 * TMH.h
 *
 *  Created on: 15 sie 2014
 *      Author: tomasz
 */

#ifndef TMH_H_
#define TMH_H_

/*
 * Includes
 *
 */


/*
 * Typedefs
 *
 */

/**
 *  @brief Defines a type of nodes' id parameter.
 *
 *  @details It is a global typedef that defines the <b><tt>id</tt></b> parameter
 *  of every node in entire graph structure that will be passed to any of the shortest path algorithm
 *  that is implemented in this library. It limits a number of nodes that can be hold in that structure.
 *	<b><tt>Id</tt></b> have to be unique for every node.
 *
 * Supported types are only non-floating point types:
 * <ul>
 * 	<li>
 * 		unsigned char <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned short int <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned int <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned long int <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned long long int <sup>1</sup>
 * 	</li>
 * </ul>
 *
 * <sup>1</sup> - the actual value depends on the particular system and library implementation,
 * 				but shall reflect the limits of these types in the target platform.
 *
 * @see limits.h
 */
typedef unsigned int TMHNodeIdx;

/**
 *  @brief Defines a type of nodes' distance parameter.
 *
 *  @details It is a global typedef that defines <tt><b>d(i)</b></tt> (distance label) parameter
 *  of every node in entire graph structure that will be passed to any of the shortest-path algorithm
 *  that is implemented in this library.
 *
 * Supported types are only non-floating point types:
 * <ul>
 * 	<li>
 * 		unsigned char <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned short int <sup>1,2</sup>
 * 	</li>
 * 	<li>
 * 		unsigned int <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned long int <sup>1</sup>
 * 	</li>
 * 	<li>
 * 		unsigned long long int <sup>1</sup>
 * 	</li>
 * </ul>
 *
 * <sup>1</sup> - the actual value depends on the particular system and library implementation,
 * 				but shall reflect the limits of these types in the target platform.
 * <sup>2</sup> - using of that type of data instead of <tt><b>unsigned int</b></tt> will cost some performance lose but saves memory.
 *
 * Any change of that typedef have to be followed by changing <tt><b>@ref distanceLabelInfinity</b></tt> field
 * due to avoid conversion or overflow error. It should be changed to a proper X_MAX value
 * from <tt>limits.h</tt> header where <tt>X</tt> corresponds to selected type.
 *
 * @see limits.h
 * @see distanceLabelInfinity
 */
typedef unsigned int TMHNodeData;

typedef unsigned int TMHArcCost;

/*
 * Externs
 *
 */

extern const TMHNodeIdx maxNumberOfSource;

/**
 *  @brief Defines a type of nodes' distance max value
 *  which correspond to typedef definition of @ref TMHNodeData.
 *
 *  @details It is a global field that defines <tt><b>d(i)</b></tt> (distance label) max value
 *  of every node in entire graph structure that will be passed to any of the shortest-path algorithm
 *  that is implemented in this library. To prevent conversion errors or overflows
 *  it have to be suitable to chosen type of @ref TMHNodeData as it is presents down below:
 *
 * Supported types are only non-floating point types:
 * <ul>
 * 	<li>
 * 		unsigned char (\f$ 0 - 255 \f$) <sup>1</sup> @see UCHAR_MAX
 * 	</li>
 * 	<li>
 * 		unsigned short int (\f$ 0 - 65535 \f$) <sup>1,2</sup> @see USHRT_MAX
 * 	</li>
 * 	<li>
 * 		unsigned int (\f$ 0 - 65535 \f$) <sup>1</sup> @see UINT_MAX
 * 	</li>
 * 	<li>
 * 		unsigned long int (\f$ 0 - 4294967295 \f$) <sup>1</sup> @see ULONG_MAX
 * 	</li>
 * 	<li>
 * 		unsigned long long int (\f$ 0 - 18446744073709551615 \f$) @see ULLONG_MAX
 * 	</li>
 * </ul>
 *
 * <sup>1</sup> - the actual value depends on the particular system and library implementation,
 * 				but shall reflect the limits of these types in the target platform.
 *
 * <sup>2</sup> - using of that type of data instead of <b>unsigned int</b> will cost some performance lose but saves memory.
 *
 * Any change of that filed have to be followed by changing @ref TMHNodeData type definition
 * due to avoid conversion or overflow error.
 *
 */
extern const TMHNodeData distanceLabelInfinity;

/*
 * Declarations
 *
 */


#endif /* TMH_H_ */
