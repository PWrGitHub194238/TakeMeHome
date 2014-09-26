/****************************************************************************
 * Copyright (C) 2014 by Tomasz Strzałka                                 	*
 *                                                                          *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/**
 * @file TMHLogger.c
 * @author Tomasz Strzałka
 * @date 10 Aug 2914
 * @brief
 *
 *
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

/*
 * Includes
 *
 */

#include "../Headers/TMHLogger.h"

#include <stddef.h>			/* NULL */
#include <stdlib.h>			/* atexit(void (*__func) (void)) */
#include <stdarg.h>			/* va_list, va_start(v,l), va_end(v)*/

#include "../Headers/Helpers/TMHAllocHelper.h"
#include "../Headers/Helpers/TMHErrors.h"


/*
 * Constants
 *
 */

static const char* MODULE_NAME = "TMHLogger";

static const unsigned short FORMATTED_TIME_SIZE = 10;


/*
 * Globals
 *
 */

Logger LOG = {OFF,false,NULL,NULL,NULL};

/*
 * Private declarations
 *
 */

/** @brief Non-public function.
 *
 * @details Prints log message described by @p _format along with @p arg argument list for the first one.
 * It prints log messages in two general forms, depending on configuration:
 * <ul>
 * 	<li>with time - can be enabled by calling @ref enableLog(DBG_LEVEL)  </li>
 * 	<li></li>
 * </ul>
 *
 * @param debug_level
 * @param src
 * @param __format
 * @param arg
 */
static void printLog(  const char* debug_level, const char* src, const char *__restrict __format, va_list arg );

/** @brief
 *
 * @details
 *
 * @param debug_level
 * @param src
 * @param __format
 * @param arg
 */
static void printLogWithoutTime( const char* debug_level, const char* src, const char *__restrict __format, va_list arg );

/** @brief
 *
 * @details
 *
 * @param debug_level
 * @param src
 * @param __format
 * @param arg
 */
static void printLogWithTime( const char* debug_level, const char* src, const char *__restrict __format, va_list arg );


static void disableSaveLog();

/*
 * Definitions
 *
 */

void disableLog() {
	LOG.DEBUGLEVEL = OFF;
}

void enableLog( DBG_LEVEL debugLevel, bool isOnlyOneLevel ) {
	LOG.ONLYLEVEL = isOnlyOneLevel;
	if ( debugLevel == OFF ) {
		LOG.DEBUGLEVEL = INFO;
		warn(MODULE_NAME,warn_TMHLogger_enableLogWithOFF);
	} else {
		LOG.DEBUGLEVEL = debugLevel;
	}
}

void enableTime() {
	if ( LOG.date == NULL ) {
		LOG.date = memMalloc(1,sizeof(time_t));
		LOG.formatedTime = memMalloc(FORMATTED_TIME_SIZE,sizeof(char));
	} else {
		info(MODULE_NAME,info_TMHLogger_timerAlreadyEnabled);
	}
}

void disableTime() {
	memFree(LOG.date);
	memFree(LOG.formatedTime);
}

void enableSaveLog( const char* logFileName, bool withTime ) {
	if ( LOG.logFile == NULL ) {
		LOG.logFile = fopen(logFileName,"a");
		if ( LOG.logFile == NULL ) {
			error(MODULE_NAME,err_TMHLogger_allocErrorWithSaveLog,logFileName);
		} else {
			if ( withTime == true ) {
				enableTime();
			}
			atexit(disableSaveLog);
		}
	} else {
		info(MODULE_NAME,info_TMHLogger_saveLogAlreadyEnabled,logFileName);
	}
}

static void disableSaveLog() {
	if ( LOG.logFile != NULL ) {
		if ( LOG.date != NULL ) {
			disableTime();
		}
		fclose(LOG.logFile);
	} else {
		info(MODULE_NAME,info_TMHLogger_timerNoNeedToDisable);
	}
}

void setLogFile( const char* logFileName ) {
	if ( LOG.logFile != NULL ) {
		fclose(LOG.logFile);
	}
	LOG.logFile = fopen(logFileName,"a");
	if ( LOG.logFile == NULL ) {
		error(MODULE_NAME,err_TMHLogger_allocErrorWithChangeSaveLog,logFileName);
	}
}

static void printLog( const char* debug_level, const char* src, const char *__restrict __format, va_list arg ) {
	if (LOG.formatedTime == NULL ) {
		printLogWithoutTime(debug_level,src,__format,arg);
	} else {
		printLogWithTime(debug_level,src,__format,arg);
	}
}

static void printLogWithoutTime( const char* debug_level, const char* src, const char *__restrict __format, va_list arg  ) {
	if (LOG.logFile) {
		fprintf(LOG.logFile,"\n%s | [%s] ",debug_level,src);
		vfprintf(LOG.logFile,__format,arg);
		fflush(LOG.logFile);
	} else {
		printf("\n%s | [%s] ",debug_level,src);
		vprintf(__format,arg);
	}
}

static void printLogWithTime( const char* debug_level, const char* src, const char *__restrict __format, va_list arg  ) {
	time(LOG.date);
	strftime( LOG.formatedTime, FORMATTED_TIME_SIZE, "%H:%M:%S", localtime(LOG.date));
	if (LOG.logFile) {
		fprintf(LOG.logFile,"\n%s | %s | [%s] ",LOG.formatedTime,debug_level,src);
		vfprintf(LOG.logFile,__format,arg);
		fflush(LOG.logFile);
	} else {
		printf("\n%s | %s | [%s] ",LOG.formatedTime,debug_level,src);
		vprintf(__format,arg);
	}
}

void trace( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("TRACE",src,__format,arg);
	va_end(arg);
}

void debug( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("DEBUG",src,__format,arg);
	va_end(arg);
}

void info( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("INFO",src,__format,arg);
	va_end(arg);
}

void warn( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("WARN",src,__format,arg);
	va_end(arg);
}

void error( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("ERROR",src,__format,arg);
	va_end(arg);
}

void fatal( const char* src, const char *__restrict __format, ... ) {
	va_list arg;
	va_start(arg, __format);
	printLog("FATAL",src,__format,arg);
	va_end(arg);
}

bool isTraceLogEnabled() {
	return ((LOG.ONLYLEVEL) ? LOG.DEBUGLEVEL == TRACE : LOG.DEBUGLEVEL >= TRACE);
}

bool isDebugLogEnabled() {
	return ((LOG.ONLYLEVEL) ? LOG.DEBUGLEVEL == DEBUG : LOG.DEBUGLEVEL >= DEBUG);
}

bool isInfoLogEnabled() {
	return ((LOG.ONLYLEVEL) ? LOG.DEBUGLEVEL == INFO : LOG.DEBUGLEVEL >= INFO);
}

bool isWarnLogEnabled() {
	return ((LOG.ONLYLEVEL) ? LOG.DEBUGLEVEL == WARN : LOG.DEBUGLEVEL >= WARN);
}
