#include <systemc.h>
#include "define.h"
#include "mem.h"

bool mem::Read(unsigned int addr, unsigned int& data)
{
	// Waiting for memory bus to be free
	while (ack_sig.read() != sc_logic_Z)
	{
		wait(CLOCK_PERIOD, SC_NS);
	}

	ren_sig.write(sc_logic_1);
	wen_sig.write(sc_logic_0);
	addr_sig.write(static_cast<myDatType>(addr));

	// Waiting for acknowledge
	while (ack_sig.read() == sc_logic_Z)
	{
		wait(CLOCK_PERIOD, SC_NS);
	}

	data = static_cast<unsigned int>(dataOut_sig.read());
	//std::cout << "Memory wrapper got data " << data << std::endl;
	bool ack = ack_sig.read() == sc_logic_1;
	ren_sig.write(sc_logic_0);

	return ack;
}

bool mem::Write(unsigned int addr, unsigned int data)
{
	// Waiting for memory bus to be free
	while (ack_sig.read() != sc_logic_Z)
	{
		wait(CLOCK_PERIOD, SC_NS);
	}

	wen_sig.write(sc_logic_1);
	ren_sig.write(sc_logic_0);
	addr_sig.write(static_cast<myDatType>(addr));
	dataIn_sig.write(static_cast<myDatType>(data));

	while (ack_sig.read() == sc_logic_Z)
	{
		wait(CLOCK_PERIOD, SC_NS);
	}

	bool ack = ack_sig.read() == sc_logic_1;
	wen_sig.write(sc_logic_0);

	return ack;
}
mem::~mem()
{
	delete mem_rtl;
	delete oscillator;
}

mem::mem(sc_module_name nm, char* filename) : sc_module(nm)
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

	// Initialize signals
	ren_sig.write(sc_logic_0);
	wen_sig.write(sc_logic_0);
	ack_sig.write(sc_logic_Z);

	// Oscillator
	oscillator->os_clk(clk_sig);
}
