#ifndef FORWARDMOD_H      // esta correcto?
#define FORWARDMOD_H
#include <systemc.h>

SC_MODULE( forward )
{
  public: 
    sc_in< sc_uint<5> >  rs, rt, rd;
   // sc_in< sc_uint<5> >  AluOut;       wich alu signal is?
    sc_in< bool > MemRead_exe, MemRead_mem;
  //  sc_in< bool > MemRead;              nao sera apenas mem read?
  //  sc_in< bool>  control_signals       wich ones?      
        
  //  sc_out< bool >  enable_pc, ....;     o que sai?

    SC_CTOR(forward)
    {      
       // dont know what to put here
   }
  
   // void do_something();
};

#endif