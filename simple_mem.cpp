#include "simple_mem.h"
#include "define.h"

bool simple_mem::Read(unsigned int addr, unsigned int& data)
{
	if (addr < MEM_SIZE)
	{
		data = this->data[addr];
		//std::cout << "Reading : " << data << " at address : " << addr << std::endl;
		return true;
	}

	return false;
}

bool simple_mem::Write(unsigned int addr, unsigned int data)
{
	if (addr < MEM_SIZE)
	{
		this->data[addr] = data;
		return true;
	}

	return false;
}
