#ifndef MAKEJTA_H
#define MAKEJTA_H

/**
 * construct jump target address interface
 */

#include <systemc.h>

/**
 * construct jump target address  module.
 * construct jump target address  module adds two sc_uint<32> numbers without overflow or carry
 *   - input ports
 *   	   - \c sc_uint<32> \c o - first operand 
 *   	   - \c sc_uint<32> \c op2 - second operand
 *   - output ports
 *   	   - \c sc_uint<32> \c jumpaddress - result 
 *
 */

SC_MODULE(makejta) {
  
  sc_in< sc_uint<26> >  jta;
  sc_in< sc_uint<32> >  pc4;
  sc_out< sc_uint<32> > jumpaddress; 
    
  SC_CTOR(makejta)
     {      
      SC_METHOD(calc);
      sensitive << jta << pc4;
    }
  
  void calc();
};

#endif