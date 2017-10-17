#include<stdint.h>
#include<stdio.h>
#include "log.h"

sFirmwareVersion ver = {MAJOR, MINOR, BUILD};

int main(int argc, char *argv) {
	LogGlobalOn();
	Log(SYS1, MESSAGE, "Hello World with Log Enabled!");
	LogGlobalOff();
	Log(SYS1, MESSAGE, "Hello World with Log Disabled!");
	Log(SYS1, MESSAGE, "OMG!");
	Log(SYS1, MESSAGE, "Nothing of this is being written!");
	return 0;
}
