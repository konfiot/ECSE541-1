#include <systemc.h>

#ifndef __SIMPLE_MEM_IF_H__
#define __SIMPLE_MEM_IF_H__

class simple_mem_if : virtual public sc_interface
{
	public:
		virtual bool Write(unsigned int addr, unsigned int data) = 0;
		virtual bool Read(unsigned int addr, unsigned int& data) = 0;
};

#endif //__SIMPLE_MEM_IF_H__
