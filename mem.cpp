#include <systemc.h>
#include "define.h"
#include "mem.h"

bool mem::Read(unsigned int addr, unsigned int& data)
{
	ren_sig.write(sc_logic_1);
	addr_sig.write(static_cast<myDatType>(addr));
	while (ack_sig.read() == sc_logic_Z) {
		wait(10, SC_NS);
	}
	data = static_cast<unsigned int>(dataOut_sig.read());
	bool ack = ack_sig.read() == sc_logic_1;
	ren_sig.write(sc_logic_0);

	return ack;
}

bool mem::Write(unsigned int addr, unsigned int data)
{
	wen_sig.write(sc_logic_1);
	addr_sig.write(static_cast<myDatType>(addr));
	dataIn_sig.write(static_cast<myDatType>(data));
	while (ack_sig.read() == sc_logic_Z) {
		wait(10, SC_NS);
	}
	bool ack = ack_sig.read() == sc_logic_1;
	wen_sig.write(sc_logic_0);

	return ack;
}
mem::~mem() {
	delete mem_rtl;
	delete oscillator;
}

mem::mem(sc_module_name nm, char* filename) : sc_module(nm) {
	cout << "ENTERED mem constructor\n";

	// Module instance signal connections
	mem_rtl = new MEMORY_RTL("mem_rtl", filename);

	cout << "Initializing OSCILLATOR";

	oscillator = new OSCILLATOR("oscillator");

	cout << "ENTERED mem constructor\n";

	// RTL memory
	mem_rtl->clk(clk_sig);

	cout << "ARRIVING AT PROBLEM";
	mem_rtl->addr(addr_sig);
	mem_rtl->dataIn(dataIn_sig);
	mem_rtl->dataOut(dataOut_sig);
	mem_rtl->ren(ren_sig);
	cout << "PASSED AT PROBLEM";
	mem_rtl->wen(wen_sig);
	mem_rtl->ack(ack_sig);

	// Oscillator
	oscillator->os_clk(clk_sig);
}


