#ifndef FORWARDMOD_H     
#define FORWARDMOD_H
#include <systemc.h>

SC_MODULE( forward )
{
  public: 
    sc_in< sc_uint<5> >  rs, rt;
    sc_in< bool > RegWrite_mem;
    sc_in< bool > RegWrite_wb;
    sc_in< sc_uint<5> > WriteReg_mem; 
    sc_in< sc_uint<5> > WriteReg_wb; 
    sc_in< bool > MemRead; 
    sc_out< sc_uint<2> > mux_alu1,mux_alu2;  
 

    
   // sc_in< sc_uint<5> >  AluOut;       wich alu signal is?
    //sc_in< bool > MemRead_exe, MemRead_mem;
  

  //  sc_in< bool > MemRead;              nao sera apenas mem read?
  //  sc_in< bool>  control_signals       wich ones?      
        
  //  sc_out< bool >  enable_pc, ....;     o que sai?

    SC_CTOR(forward)
    {      
       // dont know what to put here
      SC_METHOD(forwarding);
      sensitive << rs << rt << RegWrite_mem << RegWrite_wb << WriteReg_mem << WriteReg_wb << MemRead ; 


    }
  
   // void do_something();
   void forwarding(); 
};

#endif
