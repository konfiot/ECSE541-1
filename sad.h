#include <systemc.h>

#define NUM_BLOCKS 64
#define BLOCK_SIZE 64
#define INPUT1_ADDR 0
#define INPUT2_ADDR 16384
#define SAD_OUTPUT_ADDR 32768

SC_MODULE(sad)
{
	sc_in<unsigned int> A, B;
	sc_out<unsigned int> F;

	void do_sad()
	{
		F.write( !(A.read() && B.read()) );
	}

	SC_CTOR(nand2)
	{
		SC_METHOD(do_sad);
		sensitive << A << B;
	}
};
