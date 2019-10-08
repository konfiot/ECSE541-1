#include <systemc.h>
#include "define.h"

SC_MODULE(sad)
{
	sc_port<simple_mem_if> MEM;

	void do_sad()
	{
		int i, v;
		unsigned int block;
		unsigned int sad;
		unsigned int a, b;

		for (block=0; block<NUM_BLOCKS; block++) {
			sad = 0;
			for (i=0; i<BLOCK_SIZE; i++) {
				MEM.Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, &a);
				MEM.Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, &b);

				v = a - b;
				if( v < 0 ) v = -v;
				sad += v;
			}
			MEM.Write(SAD_OUTPUT_ADDR + block, sad);
		}
	}

	SC_CTOR(sad)
	{
		SC_METHOD(do_sad);
		sensitive << A << B;
	}
};
