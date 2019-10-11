#include <systemc.h>
#include "define.h"
#include "mem_if.h"
#include "mem_rtl.h"

typedef sc_signal<sc_uint<32>> mySignal;

class mem : public sc_module, public simple_mem_if
{
	private:
		// Module declarations
		MEMORY_RTL* mem_rtl;

		// Local signal declarations
		mySignal addr_sig;
		mySignal dataIn_sig;
		mySignal dataOut_sig;
		sc_signal<sc_logic> ren_sig;
		sc_signal<sc_logic> wen_sig;
		sc_signal<sc_logic> ack_sig;

		sc_clock clk_sig;

	public:
		// constructor
		mem(sc_module_name nm, char* filename) :
			sc_module(nm), clk_sig("clk_sig",10,SC_NS)
		{
			// Module instance signal connections
			mem_rtl = new MEMORY_RTL("mem_rtl",filename);
			mem_rtl->clk(clk_sig);
			mem_rtl->addr(addr_sig);
			mem_rtl->dataIn(dataIn_sig);
			mem_rtl->dataOut(dataOut_sig);
			mem_rtl->ren(ren_sig);
			mem_rtl->wen(wen_sig);
			mem_rtl->ack(ack_sig);
		}

		// destructor
		~mem()
		{
			delete mem_rtl;
		}
};

// Interface RW
bool mem::Read(unsigned int addr, unsigned int& data)
{
	ren_sig.write(1);
	addr_sig.write(dynamic_cast<mySignal>(addr));
	wait();
	data = dynamic_cast<unsigned int>(dataOut.read());
	bool ack = dynamic_cast<bool>(ack.read());
	ren_sig.write(0);

	return ack;
}

bool mem::Write(unsigned int addr, unsigned int data)
{
	wen_sig.write(1);
	addr_sig.write(dynamic_cast<mySignal>(addr));
	dataIn_sig.write(dynamic_cast<mySignal>(data));
	wait();
	bool ack = dynamic_cast<unsigned int>(ack.read());
	ren_sig.write(0);

	return ack;
}
