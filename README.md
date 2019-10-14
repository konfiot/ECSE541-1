# ECSE541-1
First assignment of ECSE541

GLOSSARY:

- define.h : contains the device and test becnh properties
- main.cpp : file that will run the test on both simple and rtl memories
- mem.h : simple_meme_if wrapper for the RTL memory implementation (Assignment pasrt 2)
- mem.cpp : implements the logc for the methonds in the mem class (Assignment pasrt 2)
- mem_rtl.h : implements thet RTL verion of the memory (Assignment pasrt 2)
- mem_init.txt : memory initialization file
- sad.h : implements the sum of absolute differences for both rtl and simple memory
- simple_mem_if.h : memory interface
- simple_mem.h : implemnts the memory with out time delays
- simple_mem.cpp: has the logic for the methods in the simple_mem class

COMPILING:

Use the makefile included to compile and run the tests

ADDITIONAL OPTIONS:

Switching between the rtl and simple memory is pretty simple. 2 switches are accepted by the program: "-r" to run rtl memory and "-s" to run simple memory. By default, the program will always run the rtl version. The switch must be placed in between the program call and the memory file location. Example:

    main -s mem_init.txt

Memory properties can be customized in the define.h file. Once modified, the code would need to be recompiled.


