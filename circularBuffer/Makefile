MAJOR=1
MINOR=0
BUILD=$(shell cat version.build)
DEFINES=-DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -D BUILD=$(BUILD)

all:
	gcc main.c circularBuffer.c -o test $(DEFINES)
	echo $$(($(BUILD)+1)) > version.build

clean:
	rm test