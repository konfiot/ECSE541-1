#include <systemc.h>

class simple_mem_if : virtual public sc_interface
{
	public:
		virtual bool Write(unsigned int addr, unsigned int data) = 0;
		virtual bool Read(unsigned int addr, unsigned int& data) = 0;
};

