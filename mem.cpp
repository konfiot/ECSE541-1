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