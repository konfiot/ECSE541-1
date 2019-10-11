SYSTEMC_ARCH=linux64
SYSTEMC=/usr/local/systemc-2.3.3
#SYSTEMC_ARCH=linux
LIB_DIRS=$(SYSTEMC)/lib-$(SYSTEMC_ARCH)

# Include directories
INCLUDE_DIRS = -I. -I$(SYSTEMC)/include

# header files used, for dependency checking
HEADERS = define.h simple_mem_if.h mem.h mem_rtl.h sad.h oscillator.h simple_mem.h

# source files used, for depedency checking
SOURCES = main.cpp simple_mem.cpp mem.cpp

DEPENDENCIES = \
	Makefile \
	$(HEADERS) \
	$(SOURCES)

LIBS = -lsystemc -lstdc++ -lm

TESTS = main

all: $(TESTS)
	./$(TESTS) mem_init.txt

$(TESTS): $(DEPENDENCIES)
	g++ -g -o $@ $(SOURCES) $(INCLUDE_DIRS) -L. -L$(LIB_DIRS) $(LIBS) -Wl,-rpath=$(LIB_DIRS)

clean:
	rm -f $(TESTS)
