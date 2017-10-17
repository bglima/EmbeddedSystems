#include<stdint.h>
#include<stdio.h>
#include "log.h"

sFirmwareVersion ver = {MAJOR, MINOR, BUILD};

int main(int argc, char *argv) {
	// Testing enabling and disabling log	
	LogGlobalOn();
	Log(SYS1, ALL, "Hello World with Log Enabled!");
	LogGlobalOff();
	Log(SYS1, ALL, "Hello World with Log Disabled!");
	Log(SYS1, ALL, "OMG!");
	Log(SYS1, ALL, "Nothing of this is being logged!");
	Log(SYS1, ALL, "And there is no IF/ELSE being used! :D");

	// Testing version logging
	// Next command won't work, since we didn't enabled Log
	Log(SYS1, ALL, "I'll try to print the version now...");
	LogVersion( &ver );
	// So, let's enable it
	LogGlobalOn();
	LogVersion( &ver );
	
	// Setting a new subsysLogLevel for SYS2
	LogSetOutputLevel( SYS2, WARNING );
	// Now, neither ALL or DEBUG logs will be showed to user within SYS2
	Log( SYS2, ALL, "Just a greeting from the programmer.");
	Log( SYS2, DEBUG, "Debugging everything around here.");
	// Now, let's try a WARNING or higher level message... These are going to appear
	Log( SYS2, WARNING, "Watchout! There are some deprecated uses.");
	Log( SYS2, ERROR, "Ops.. Something went wrong!\n");
	
	Log( SYS3, ALL, "Now let's set only ERROR messages for SYS3 from now on.");
	LogSetOutputLevel( SYS3, ERROR );
	Log( SYS3, ALL, "This will not be showed.");
	Log( SYS3, DEBUG, "Nor will it be.");
	Log( SYS3, WARNING, "Warnings are also hidden.");
	Log( SYS3, ERROR, "Ops. He is dead, Jim!");
	Log( SYS3, FATAL, "OMG! BLUE SCREEN OF DEATH!");
	
	return 0;
}
