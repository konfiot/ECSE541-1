#include "systemc.h"
#include "sad.h"
#include "mem.h"

int sc_main(int argc, char* argv[]) {
	sc_signal<bool> ASig, BSig, FSig;
	sc_clock TestClk("TestClock", 10, SC_NS,0.5);

	if (argc < 2) {
		printf("Usage: sad memfile\n");
		return 1;
	}

	sad Sad1();
	mem Mem1(argv[1]);

	sad1.MEM(Mem1);

	sc_start();  // run forever

	return 0;

}
