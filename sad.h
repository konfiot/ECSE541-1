#include <systemc.h>
#include "define.h"
#include "simple_mem_if.h"
#include "mem.h"

#ifndef __SAD_H___
#define __SAD_H___

class sad: public sc_module
{
	sc_port<simple_mem_if> MEM;

	void do_sad(void);

	sc_clock clk;

public :
	sad(sc_module_name nm, mem MEMORY) : sc_module(nm), MEM(MEMORY)
	{
		SC_METHOD(do_sad);
	}
};

void sad::do_sad()
{
	int i, v;
	unsigned int block;
	unsigned int sad;
	unsigned int a, b;

	for (block=0; block<NUM_BLOCKS; block++)
	{
		sad = 0;
		wait(10,SC_NS);
		for (i=0; i<BLOCK_SIZE; i++)
		{
			MEM->Read(INPUT1_ADDR+(block*BLOCK_SIZE)+i, a);
			MEM->Read(INPUT2_ADDR+(block*BLOCK_SIZE)+i, b);

			v = a - b;
			wait(10,SC_NS);
			if( v < 0 ) v = -v;
			wait(10,SC_NS);
			sad += v;
			wait(10,SC_NS);
		}
		MEM->Write(SAD_OUTPUT_ADDR + block, sad);
		std::cout << sc_time_stamp() << " | block : "
			<< block << " | sad : " << sad << std::endl;
	}
	sc_stop();
}

#endif //__SAD_H___
