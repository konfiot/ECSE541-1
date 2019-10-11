#include <systemc.h>
#include "define.h"
#include "mem.h"

bool mem::Read(unsigned int addr, unsigned int& data)
{
	ren_sig.write(sc_logic_1);
	addr_sig.write(static_cast<myDatType>(addr));
	wait();
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
	wait();
	bool ack = ack_sig.read() == sc_logic_1;
	wen_sig.write(sc_logic_0);

	return ack;
}
mem::~mem() {
	delete mem_rtl;
	delete oscillator;
}

mem::mem(sc_module_name nm, char* filename) : sc_module(nm) {
	cout << "ENTERED mem constructor";

	// Module instance signal connections
	mem_rtl = new MEMORY_RTL("mem_rtl", filename);
	oscillator = new OSCILLATOR("oscillator");

	cout << "ENTERED mem constructor";

	// RTL memory
	mem_rtl->clk(clk_sig);
	mem_rtl->addr(addr_sig);
	mem_rtl->dataIn(dataIn_sig);
	mem_rtl->dataOut(dataOut_sig);
	cout << "ARRIVING AT PROBLEM";
	mem_rtl->ren(ren_sig);
	cout << "PASSED AT PROBLEM";
	mem_rtl->wen(wen_sig);
	mem_rtl->ack(ack_sig);

	// Oscillator
	oscillator->os_clk(clk_sig);
}


