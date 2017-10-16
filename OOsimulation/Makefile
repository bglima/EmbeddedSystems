MAJOR=0
MINOR=0
BUILD=$(shell cat version.build)
DEFINES=-DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -D BUILD=$(BUILD)

release:
	gcc main.c device.c -o runnable $(DEFINES)
	echo $$(($(BUILD)+1)) > version.build

clean:
	rm runnable