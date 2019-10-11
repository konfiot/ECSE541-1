#include <systemc.h>
#include "define.h"
#include "simple_mem_if.h"
#include "mem_rtl.h"
#include "oscillator.h"

#ifndef ___MEM_H___
#define ___MEM_H___

typedef sc_uint<32> myDatType;
typedef sc_signal<myDatType> mySignal;

class mem : public sc_module, public simple_mem_if
{
	private:
		// Module declarations
		MEMORY_RTL* mem_rtl;
		OSCILLATOR* oscillator;

		// Local signal declarations
		mySignal addr_sig;
		mySignal dataIn_sig;
		mySignal dataOut_sig;
		sc_signal<sc_logic> ren_sig;
		sc_signal<sc_logic> wen_sig;
		sc_signal<sc_logic> ack_sig;
		sc_signal<sc_logic> clk_sig;

	public:

		// constructor
		mem(sc_module_name nm, char* filename) : sc_module(nm)
		{
			// Module instance signal connections
			mem_rtl = new MEMORY_RTL("mem_rtl", filename);
			oscillator = new OSCILLATOR("oscillator");

			// RTL memory
			mem_rtl->clk(clk_sig);
			mem_rtl->addr(addr_sig);
			mem_rtl->dataIn(dataIn_sig);
			mem_rtl->dataOut(dataOut_sig);
			mem_rtl->ren(ren_sig);
			mem_rtl->wen(wen_sig);
			mem_rtl->ack(ack_sig);

			// Oscillator
			oscillator->os_clk(clk_sig);
		}

		bool Read(unsigned int addr, unsigned int& data);

		bool Write(unsigned int addr, unsigned int data);

		// destructor
		~mem()
		{
			delete mem_rtl;
			delete oscillator;
		}
};

#endif //___MEM_H___
