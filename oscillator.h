#include <systemc.h>
#include "define.h"

#ifndef __OSCILLATOR_H__
#define __OSCILLATOR_H__

{
  sc_out<sc_logic> clk;

  void func()
  {
    while(true)
    {
      clk.write(sc_logic_0);
      wait(5, SC_NS);
      clk.write(sc_logic_1);
      wait(5, SC_NS);
    }
  }

  OSCILLATOR(sc_module_name nm) :
    sc_module(nm)
  {
    SC_METHOD(func);
  }
};
#endif //__OSCILLATOR_H__
