#include <systemc.h>
#include <iostream>
#include "mem.h"
#include "sad.h"
#include "simple_mem.h"

int sc_main(int argc, char* argv[])
{
	char* init_mem_file;
	bool is_rtl = true;
	if (argc < 2)
	{
		printf("Error : no memory file\n");
		return 1;
	}
	else if (argc == 3) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
			case 's':
				is_rtl = false;
				break;
			case 'r':
				is_rtl = true;
				break;
			default:
				printf("Unknown switch detected: %s", argv[1]);
				return 1;
			}
			init_mem_file = argv[2];
		}
		else {
			printf("Unknown switch detected: %s", argv[1]);
			return 1;
		}
	}
	else if (argc > 3) {
		printf("Error : too many arguments passed\n");
		return 1;
	} else {
		init_mem_file = argv[1];
	}

	sad Sad1("SAD1");

	if (is_rtl) {
		cout << "Running RTL memory";

		// Instantiate memory
		mem Mem_RTL("MEM_RTL", init_mem_file);

		// Link memory
		Sad1.MEM(Mem_RTL);

		// Run simulation
		std::cout << std::endl;
		sc_start();
	}
	else {
		cout << "Running simple memory";
	
		// Instantiate memory
		simple_mem Mem_Simple("MEM_SMPL", init_mem_file);
	
		// Link memory
		Sad1.MEM(Mem_Simple);

		// Run simulation
		std::cout << std::endl;
		sc_start();
	}

	// Run simulation
//	std::cout << std::endl;
//	sc_start();

	return 0;
}
