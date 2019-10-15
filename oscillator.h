#include <systemc.h>
#include "define.h"

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

SC_MODULE(OSCILLATOR)
{
  sc_out<sc_logic> os_clk;
  double clock_period_2 = CLOCK_PERIOD / 2;

  void func()
  {
    while(true)
    {
	     os_clk.write(sc_logic_0);
       wait(clock_period_2, SC_NS);
	     os_clk.write(sc_logic_1);
       wait(clock_period_2, SC_NS);
    }
  }

  SC_CTOR(OSCILLATOR)
  {
	  SC_THREAD(func);
  }

};
#endif //__OSCILLATOR_H__
