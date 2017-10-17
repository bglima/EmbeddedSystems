MAJOR=0
MINOR=0
BUILD=$(shell cat Version.build)
DEFINES=-DMAJOR=$(MAJOR) -DMINOR=$(MINOR) -D BUILD=$(BUILD)

release:
	gcc main.c device.c -o runnable $(DEFINES)
	@echo $$(($(BUILD)+1)) > Version.build

run:
	gcc main.c device.c -o runnable $(DEFINES)
	@echo $$(($(BUILD)+1)) > Version.build
	@echo ''
	@./runnable*
	
clean:
	rm runnable*