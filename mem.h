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
		mem(sc_module_name nm, char* filename);

		bool Read(unsigned int addr, unsigned int& data);
		bool Write(unsigned int addr, unsigned int data);

		// destructor
		~mem();
};

#endif //___MEM_H___
