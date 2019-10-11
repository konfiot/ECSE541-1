#include <systemc.h>
#include "define.h"

class MEMORY_RTL: public sc_module
{
public:
  sc_in<sc_logic> clk;
  sc_in<sc_logic> ren, wen;
  sc_in<sc_uint<32>> addr;
  sc_in<sc_uint<32>> dataIn;
  sc_out<sc_uint<32>> dataOut;
  sc_out<sc_logic> ack;

  sc_uint<32> mem[MEM_SIZE];

  SC_HAS_PROCESS(MEMORY_RTL);

  void rtl();

  MEMORY_RTL(sc_module_name nm, char* filename) :
    sc_module(nm)
  {
    // Initialize memory
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
      mem[i] = (sc_uint<32>)(data);
      i++;
    }

    SC_METHOD(rtl);
    sensitive << clk.pos();
  }
};

void MEMORY_RTL::rtl()
{
  /*
    if ren : output data at addr on dataOut
    if wen : write data at addr
    if addr is valid : ack is
  */

  // Initialize output ports
  dataOut.write(0);
  ack.write(sc_logic_0);
  wait();

  // RW functions
  while (true)
  {
    // address valid
    sc_uint<32> addr_val = addr.read();
    if (addr_val < MEM_SIZE)
    {
      // Read mode
      if(ren.read() == sc_logic_1)
      {
        dataOut.write(mem[addr_val]);
      }
      // Write mode
      else if (wen.read() == sc_logic_1)
      {
        mem[addr_val] = dataIn.read();
      }
      ack.write(sc_logic_1);
    }
    // address invalid
    else
    {
      ack.write(sc_logic_0);
    }
    wait();
  }
}
