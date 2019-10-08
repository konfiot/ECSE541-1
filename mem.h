#include <iostream>
#include <systemc.h>
#include "mem_if.h"
#include "define.h"

class simple_mem : public sc_module, public simple_mem_if
{
	private:
		unsigned int data[MEM_SIZE] = {0};

	public:
		// constructor
		simple_mem(sc_module_name nm, char* filename) : sc_module(nm) {
			unsigned int data, i = 0;

			std::ifstream memfile;
			memfile.open(filename);
			if (!memfile) {
				std::cerr << "Error opening file";
				exit(1);
			}

			while(memfile >> data) {
				this->Write(i, data);
			}
		}

		bool Read(unsigned int addr, unsigned int& data) {
			data = this->data[addr];
			return true; // TODO check bounds
		}

		bool Write(unsigned int addr, unsigned int data) {
			this->data[addr] = data;
			return true; // TODO check bounds
		}

};
