/**
 * @file TMHLogger.h
 * @author Tomasz Strzałka
 * @date 10 Aug 2914
 * @brief
 *
 *
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#ifndef TMHLOGGER_H_
#define TMHLOGGER_H_

/*
 * Includes
 */

#include <stdbool.h>		/* bool */
#include <stdio.h>			/* FILE */
#include <time.h>			/* time_t */

/*
 * Typedefs
 */

/**
 *	\brief Określa poziom szczrgółowości wypisywanych komunikatów w trakcie działania programu.
 *
 *	\details Jeżeli obsługa dziennika zdarzeń nie została wyłączona (zobacz \ref disableLog()),
 *			poprzez wybór odpowiedniego poziomu monitorowania zachowań programu
 *			można regulować ilość informacji, wypisywanych na linię poleceń w trakcie działania programu.
 */
typedef enum DBG_LEVEL {
	OFF,   /*!< całkowicie wyłącza wypisywanie komunikatów w trakcie działanie programu.
			*/
	FATAL,/*!< zastosowanie tego poziomu pozwala na ignorowanie wszystkich komunikatów
			poza tymi, których wystąpienie oznacza krytyczny błąd aplikacji, powodując jej zamknięcie.
			*/
	ERROR,/*!< użyty, wyświetla informacje o błędach w trakcie wykonywania programu.
			 */
	WARN, /*!< zastosowanie tego poziomu pozwala na selektywne wyświetlanie informacji
			zawierających wyłącznie ostrzeżenia o potencjalnie niechcianym zachowaniu się programu.
			*/
	INFO, /*!< użyty, wyświetla podstawowe informacje o przebiegu algorytmów,
			wykorzystywanych przez aplikację.
			*/
	DEBUG,/*!< użyty, wyświetla większość istotnych komunikatów - podobnie jak \ref TRACE -
			odnoszących się do funkcjonowania aplikacji.
			*/
	TRACE,/*!< użyty, wyświetla większość istotnych komunikatów
			odnoszących się do funkcjonowania aplikacji, łącznie z informacjami na temat alokacji pamięci.
			*/
	ALL  /*!< użyty, wyświetla wszystkie możliwe komunikaty,
			pozwalając na najbardziej szczegółową analizę działania programu.
	 	 	*/
} DBG_LEVEL;

typedef struct Logger {
	DBG_LEVEL DEBUGLEVEL;
	bool ONLYLEVEL;
	time_t* date;
	char* formatedTime;
	FILE* logFile;
} Logger;

/*
 * Declarations
 */

/**
 *
 */
void disableLog();

/**
 *
 * @param debugLevel
 */
void enableLog( DBG_LEVEL debugLevel, bool isOnlyOneLevel );

/**
 *
 */
void enableTime();

/**
 *
 */
void disableTime();

/**
 *
 * @param logFileName
 * @param withTime - determinates log format for opened file:
 * 	<ul>
 * 		<li>true - sets log format to HH:MM:SS | DBG_LVL | [SRC_FILE] LOG</li>
 * 		<li>false - sets log format to DBG_LVL | [SRC_FILE] LOG</li>
 * 	</ul>
 */
void enableSaveLog( const char* logFileName, bool withTime );

/**
 *
 * @param logFileName
 */
void setLogFile( const char* logFileName );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void trace( const char* src, const char *__restrict __format, ... );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void debug( const char* src, const char *__restrict __format, ... );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void info( const char* src, const char *__restrict __format, ... );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void warn( const char* src, const char *__restrict __format, ... );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void error( const char* src, const char *__restrict __format, ... );

/** @brief
 *
 * @details
 *
 * @param src
 * @param __format
 */
void fatal( const char* src, const char *__restrict __format, ... );

bool isTraceLogEnabled();

bool isDebugLogEnabled();

bool isInfoLogEnabled();

bool isWarnLogEnabled();

#endif /* TMHLOGGER_H_ */
