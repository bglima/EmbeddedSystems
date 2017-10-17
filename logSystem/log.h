#ifndef LOG_H
#define LOG_H

typedef enum { false, true } bool;
typedef enum { SYS1, SYS2, SYS3, EOS } eLogSubSystem;
typedef enum { ALL, DEBUG, WARNING, ERROR, FATAL, OFF, EOL } eLogLevel;

// Loglevel from each subsystem. Each starts with logLevel ALL
eLogLevel subsysLogLevel[EOS];
// Names for each subsystem
static char * subsysName[EOS] = {"SYS1", "SYS2", "SYS3"};
// Names for each logLevel
static char * levelName[EOL] = {"ALL", "DEBUG", "WARNING", "ERROR", "FATAL" };

typedef struct {
    uint8_t major;
    uint8_t minor;
    uint16_t build;
} sFirmwareVersion;

void (*logFunctionPointer)( eLogSubSystem, eLogLevel, char *);
void LogFuncOn (eLogSubSystem sys, eLogLevel level, char * msg); 
void LogFuncOff(eLogSubSystem sys, eLogLevel level, char * msg); 

void Log( eLogSubSystem sys, eLogLevel level, char * msg);
void LogSetOutputLevel( eLogSubSystem sys, eLogLevel level );
void LogGlobalOn(); 
void LogGlobalOff();
void LogVersion( sFirmwareVersion * v );


#endif
