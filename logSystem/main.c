#include<stdint.h>
#include<stdio.h>
#include "log.h"

sFirmwareVersion ver = {MAJOR, MINOR, BUILD};

int main(int argc, char *argv) {
	// Testing enabling and disabling log	
	LogGlobalOn();
	Log(SYS1, MESSAGE, "Hello World with Log Enabled!");
	LogGlobalOff();
	Log(SYS1, MESSAGE, "Hello World with Log Disabled!");
	Log(SYS1, MESSAGE, "OMG!");
	Log(SYS1, MESSAGE, "Nothing of this is being logged!");
	Log(SYS1, MESSAGE, "And there is no IF/ELSE being used! :D");

	// Testing version logging
	// Next command won't work, since we didn't enabled Log
	LogVersion( &ver );
	// So, let's enable it
	LogGlobalOn();
	LogVersion( &ver );

	return 0;
}
