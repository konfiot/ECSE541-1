#include <systemc.h>
#include "define.h"

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

SC_MODULE(OSCILLATOR)
{
  sc_out<sc_logic> os_clk;

  void func()
  {
    while(true)
    {
	  os_clk.write(sc_logic_0);
      wait(5, SC_NS);
	  os_clk.write(sc_logic_1);
      wait(5, SC_NS);
    }
  }

  SC_CTOR(OSCILLATOR)
  {
	  SC_THREAD(func);
  }
  
};
#endif //__OSCILLATOR_H__
