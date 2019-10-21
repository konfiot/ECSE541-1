#include <systemc.h>
#include "define.h"
#include "simple_mem_if.h"
#include "mem.h"

#ifndef __SAD_H___
#define __SAD_H___

SC_MODULE(sad)
{
	sc_port<simple_mem_if> MEM;

	void do_sad(void);

	SC_CTOR(sad) {
		SC_THREAD(do_sad);
	}
};

void sad::do_sad()
{
	int i, v;
	unsigned int block;
	unsigned int sad;
	unsigned int a, b;

	// Every operation in the sad has a delay
	for (block=0; block<NUM_BLOCKS; block++)
	{
		sad = 0;
		wait(SAD_DELAY,SC_NS);
		for (i=0; i<BLOCK_SIZE; i++)
		{
			MEM->Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, a);
			MEM->Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, b);

			v = a - b;
			wait(SAD_DELAY,SC_NS);
			if( v < 0 ) v = -v;
			wait(SAD_DELAY,SC_NS);
			sad += v;
			wait(SAD_DELAY,SC_NS);
		}
		MEM->Write(SAD_OUTPUT_ADDR + block, sad);
		std::cout << sc_time_stamp() << " | block : "
			<< block << " | sad : " << sad << std::endl;
	}
	sc_stop();
}

#endif //__SAD_H___
