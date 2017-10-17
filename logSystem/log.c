#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

/*
 * Function: LogGlobalOn
 * ----------------------------
 *   Enables all the logging functions.
 *
 *   returns: nothing
 */
void LogGlobalOn() {
	logFunctionPointer = &LogFuncOn;
};

/*
 * Function: LogGlobalOff
 * ----------------------------
 *   Disables all the logging functions.
 *
 *   returns: nothing
 */
void LogGlobalOff() {
	logFunctionPointer = &LogFuncOff;
};

/*
 * Function: LogFuncOn
 * ----------------------------
 *   Executes when Log is called and LogGlobalOn was called last.
 *   Logs if 
 *
 *   sys: Subsystem which Log refers to
 *   level: Level of importance of current log. Needs to be LEQ than subsysLogLevel
 *   msg: Content message that is to be logged
 *
 *   returns: nothing
 */
void LogFuncOn (eLogSubSystem sys, eLogLevel level, char * msg) {
	if ( level >= subsysLogLevel[ sys ] )
		printf("%s->%s: %s\n", subsysName[sys], levelName[level], msg);
}; 

/*
 * Function: LogFuncOff
 * ----------------------------
 *   Executes when Log is called and LogGlobalOff was called last.
 *
 *   sys: Subsystem which Log refers to
 *   level: Level of importance of current log
 *   msg: Content message that is to be logged
 *
 *   returns: nothing
 */
void LogFuncOff(eLogSubSystem sys, eLogLevel level, char * msg) {
	// DO NOTHING!
}; 


/*
 * Function: Log
 * ----------------------------
 *   Interface that will be called by user. It abstracts wether or not Log is enabled.
 *
 *   sys: Subsystem which Log refers to
 *   level: Level of importance of current log
 *   msg: Content message that is to be logged
 *
 *   returns: nothing
 */
void Log( eLogSubSystem sys, eLogLevel level, char * msg) {
	(*logFunctionPointer)(sys, level, msg);
};


/*
 * Function: LogVersion
 * ----------------------------
 *   Logs the version passed as parameter
 *
 *   v: Version that will be logged if LogGlobalOn was last called.
 *
 *   returns: nothing
 */
void LogVersion( sFirmwareVersion * v ) {
	char buffer[200];
	uint8_t len;
	len = sprintf(buffer, "Version %u.%u.%u; All rights reserved.\n", v->major, v->minor, v->build);
	Log(SYS1, ALL, buffer);	
};

/*
 * Function: LogSetOutputLevel
 * ----------------------------
 *   A log request of level p in a logger with level q is enabled if p >=  q.
 *   For standard levels, we have ALL < DEBUG < WARN < ERROR < FATAL < OFF.
 * 
 *
 *   v: Version that will be logged if LogGlobalOn was last called.
 *
 *   returns: nothing
 */
 void LogSetOutputLevel( eLogSubSystem sys, eLogLevel level ) {
	 subsysLogLevel[ sys ] = level;
 };
