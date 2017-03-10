# NEVER NAME the EXECUTABLE: c, cc, h, etc.
EXECUTABLE=255
CC=gcc -m64
C_ENDING=c
DEFINES=
MAINS=main
MAINS_G=main test
DEBUGLEVEL=5
DEBUGLEVEL_G=9001
CFLAGS_COMMON=-std=c11 $(DEFINES:%=-D%)
LDFLAGS=
# source c/cc files with headers:
HEADED=balanced255 math255 allocate255 print255 unsafe255 comparisons255
# source cc files without headers:
NON_HEADED=
# also add any other remaining headers to this guy:
REMAINING_HEADERS=config255

# hopefully no need to modify past this point
CFLAGS=$(CFLAGS_COMMON) -DDEBUG=$(DEBUGLEVEL)
CFLAGS_G=$(CFLAGS_COMMON) -O0 -g -DDEBUG=$(DEBUGLEVEL_G)
HEADERS=$(HEADED:%=%.h) $(REMAINING_HEADERS:%=%.h)
SYS := $(shell $(CC) -dumpmachine)
BUILD_DIR=build/$(SYS)
BUILD_DIR_G=build/g$(SYS)
OBJECTS=$(NON_HEADED:%=$(BUILD_DIR)/%.o) $(HEADED:%=$(BUILD_DIR)/%.o)
OBJECTS_G=$(NON_HEADED:%=$(BUILD_DIR_G)/%.o) $(HEADED:%=$(BUILD_DIR_G)/%.o)
C_FILES=$(HEADED:%=%.$(C_ENDING)) $(NON_HEADED:%=%.$(C_ENDING))

.PHONY: clean, debug, clean-g, clean-docs, all, test

all: $(MAINS:%=%.$(EXECUTABLE)) test.g$(EXECUTABLE)

.PRECIOUS: $(OBJECTS) $(MAINS:%=$(BUILD_DIR)/%.o) $(OBJECTS_G) $(MAINS_G:%=$(BUILD_DIR_G)/%.o)

%.$(EXECUTABLE): $(BUILD_DIR) $(OBJECTS) $(BUILD_DIR)/%.o
	$(CC) $(OBJECTS) $(@:%.$(EXECUTABLE)=$(BUILD_DIR)/%.o) -o $@.$(SYS) $(LDFLAGS) 
	rm -f $@
	ln -s $@.$(SYS) $@

%.g$(EXECUTABLE): $(BUILD_DIR_G) $(OBJECTS_G) $(BUILD_DIR_G)/%.o
	$(CC) $(OBJECTS_G) $(@:%.g$(EXECUTABLE)=$(BUILD_DIR_G)/%.o) -o $@.$(SYS) $(LDFLAGS) 
	rm -f $@
	ln -s $@.$(SYS) $@

config.h: Makefile

$(BUILD_DIR):
	mkdir -p build
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR_G):
	mkdir -p build
	mkdir -p $(BUILD_DIR_G)

$(BUILD_DIR)/%.o: %.$(C_ENDING) $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(BUILD_DIR_G)/%.o: %.$(C_ENDING) $(HEADERS)
	$(CC) -c $(CFLAGS_G) -o $@ $<

clean-g:
	rm -fr build/g$(SYS)
	rm -f *.g$(EXECUTABLE)
	rm -f *.g$(EXECUTABLE).$(SYS)

clean: clean-g clean-docs
	rm -fr build/$(SYS)
	rm -f *.$(EXECUTABLE)
	rm -f *.$(EXECUTABLE).$(SYS)
	rmdir build ||:

clean-docs:
	rm -rf docs

docs: Doxyfile $(C_FILES) $(HEADERS)
	mkdir -p docs
	doxygen Doxyfile

debug: $(MAINS_G:%=%.g$(EXECUTABLE))

test: test.g$(EXECUTABLE)
	./test.g$(EXECUTABLE)

# DO NOT DELETE
