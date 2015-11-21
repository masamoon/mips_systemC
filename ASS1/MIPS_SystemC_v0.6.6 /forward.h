#ifndef FORWARDMOD_H     
#define FORWARDMOD_H
#include <systemc.h>

SC_MODULE( forward )
{
  public: 
    sc_in< sc_uint<5> >  rs, rt,rt_mem,rs_id2, rt_id2;  
//4
    sc_in< bool > RegWrite_mem;
    sc_in< bool > RegWrite_wb;
    sc_in< sc_uint<5> > WriteReg_mem; 
    sc_in< sc_uint<5> > WriteReg_wb; 
    sc_in< bool > MemRead; 
    sc_in< bool > MemWrite_exe;
    sc_in< bool > MemWrite_mem; 
    sc_in< bool > MemWrite_wb; 
    sc_in< bool > MemToReg_wb; 
    sc_in< sc_uint<3> > jbr; 

    sc_out< sc_uint<2> > mux_alu1,mux_alu2,mux_comp1_sel, mux_comp2_sel; 
    sc_out< bool> mux_mem, mux_dmem; 
 

 

        

    SC_CTOR(forward)
    {      
      SC_METHOD(forwarding);
      sensitive << rs << rt << rt_mem <<  rs_id2 << rt_id2 << RegWrite_mem << RegWrite_wb << WriteReg_mem << WriteReg_wb << MemRead << MemWrite_exe << MemWrite_wb << MemWrite_mem << MemToReg_wb << jbr; 


    }
  
   void forwarding(); 
};

#endif
