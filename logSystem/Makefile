MAJOR=0
MINOR=0
BUILD=$(shell cat version.build)
DEFINES=-DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -D BUILD=$(BUILD)

release:
	gcc main.c log.c -o runnable $(DEFINES)
	@echo $$(($(BUILD)+1)) > version.build

run:
	gcc main.c log.c -o runnable $(DEFINES)
	@echo $$(($(BUILD)+1)) > version.build
	@echo ''
	@./runnable
	
clean:
	rm runnable
