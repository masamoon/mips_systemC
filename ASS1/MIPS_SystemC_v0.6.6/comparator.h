#ifndef COMPARATORMOD_H
#define COMPARATORMOD_H

/**
 * adder module interface
 */

#include <systemc.h>

/**
 * adder module.
 * adder module adds two sc_uint<32> numbers without overflow or carry
 *   - input ports
 *   	   - \c sc_uint<32> \c op1 - first operand 
 *   	   - \c sc_uint<32> \c op2 - second operand
 *   - output ports
 *   	   - \c sc_uint<32> \c res - result 
 *
 */

SC_MODULE(comparator) {
  
  
  sc_in< sc_uint<32> >  op1;
  sc_in< sc_uint<32> >  op2;
  sc_out < bool >  eq;
  sc_out < bool >  le;
  sc_out < bool >  gr;
  
  


  SC_CTOR(comparator)
     {      
      SC_METHOD(calc);
      sensitive << op1 << op2;
    }
  
  void calc();
};

#endif
