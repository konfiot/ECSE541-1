#include "systemc.h"
#include "mem_if.h"
#include "define.h"

class simple_mem : public sc_module, public simple_mem_if
{
	private:
		unsigned int data[MEM_SIZE];

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
