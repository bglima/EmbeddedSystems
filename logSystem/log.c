#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "log.h"

void LogGlobalOn() {
	logFunctionPointer = &LogFuncOn;
};

void LogGlobalOff() {
	logFunctionPointer = &LogFuncOff;
};

void LogFuncOn (eLogSubSystem sys, eLogLevel level, char * msg) {
	printf("Log: %s\n", msg);
}; 

void LogFuncOff(eLogSubSystem sys, eLogLevel level, char * msg) {
	// DO NOTHING!
}; 

void Log( eLogSubSystem sys, eLogLevel level, char * msg) {
	(*logFunctionPointer)(sys, level, msg);
};
