#include <systemc.h>
#include <iostream>
#include "mem.h"
#include "sad.h"

int sc_main(int argc, char* argv[])
{
	if (argc < 2)
	{
		printf("Error : no memory file\n");
		return 1;
	}

	// Instantiate modules
	mem Mem1("MEM1", argv[1]);
	sad Sad1("SAD1");

	// Link memory
	Sad1.MEM(Mem1);

	// Run simulation
	std::cout << std::endl;
	sc_start();

	return 0;
}
