#include <systemc.h>
#include <iostream>
#include "mem.h"
#include "sad.h"

int sc_main(int argc, char* argv[]) {
	sc_clock TestClk("TestClock", 10, SC_NS,0.5);

	if (argc < 2) {
		printf("Usage: sad memfile\n");
		return 1;
	}
	mem Mem1("MEM1", argv[1]);
	sad Sad1("SAD1");

	Sad1.MEM(Mem1);

	std::cout << std::endl;
	sc_start();  // run forever

	return 0;
}
