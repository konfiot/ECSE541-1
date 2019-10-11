#include <iostream>
#include <systemc.h>
#include "simple_mem_if.h"
#include "define.h"

#ifndef __SIMPLE_MEM_H__
#define __SIMPLE_MEM_H__

class simple_mem : public sc_module, public simple_mem_if
{
	private:
		unsigned int data[MEM_SIZE] = {0};

	public:
		// constructor
		simple_mem(sc_module_name nm, char* filename) : sc_module(nm)
		{
			unsigned int data, i = 0;

			std::ifstream memfile;
			memfile.open(filename);
			if (!memfile)
			{
				std::cerr << "Error opening file\n";
				exit(1);
			}

			while(memfile >> data)
			{
				//std::cout << "Writing : " << data << " at address : " << i << std::endl;
				this->Write(i, data);
				i++;
			}
		}
};

#endif //__SIMPLE_MEM_H__
