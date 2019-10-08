#include <systemc.h>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768

SC_MODULE(sad)
{
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

	SC_CTOR(nand2)
	{
		SC_METHOD(do_sad);
		sensitive << A << B;
	}
};
