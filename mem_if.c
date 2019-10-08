#include "systemc.h"
#include "mem_if.h"
#include "define.h"

#define max(a,b) ((a) &gt; (b) ? (a) : (b))
#define max3(a,b,c) (max((a), max((b),(c))))

class simple_mem : public sc_module, public simple_mem_if
{
	private:
		unsigned int data[NUM_BLOCKS*BLOCK_SIZE+ max3(SAD_OUTPUT_ADDR, INPUT1_ADDR, INPUT2_ADDR)];

	public:
		// constructor
		simple_mem(sc_module_name nm) : sc_module(nm), top(0) {}

		simple_mem::Read(unsigned int addr, unsigned int& data) {
			data = this.data[addr];
			return true; // TODO check bounds
		}

		simple_mem::Write(unsigned int addr, unsigned int data) {
			this.data[addr] = data;
			return true; // TODO check bounds
		}

};
