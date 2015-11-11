#ifndef HAZARDMOD_H
#define HAZARDMOD_H

/**
 *
 * hazard module interface.
 */

#include <systemc.h>

/**
 * hazard module.
 * hazard module is the hazard detection unit.
 *
 *   - input ports
 *   	- \c sc_uint<5> \c rs	   - first register being read 
 *   	- \c sc_uint<5> \c rt	   - second register being read 
 *   	- \c sc_uint<5> \c WriteReg_exe	   - register to be written (EXE)
 *   	- \c sc_uint<5> \c WriteReg_mem	   - register to be written (MEM)
 *   	- \c bool \c RegWrite_exe	   - control signal of writing registers (EXE)
 *   	- \c bool \c RegWrite_mem	   - control signal of writing registers (MEM)
 *   - output ports
 *   	- \c bool \c enable_pc      - enables PC update
 *   	- \c bool \c enable_ifid    - enables IF/ID update
 *   	- \c bool \c reset_idexe    - resets IF/EXE
 */

SC_MODULE( hazard )
{
  public: 
    sc_in< sc_uint<5> >  rs, rs_id2;
    sc_in< sc_uint<5> >  rt, rt_id2; 
    sc_in< sc_uint<5> >  rd, rd_id2;        
    sc_in< sc_uint<5> >  WriteReg_exe, WriteReg_mem,WriteReg_wb; 
    sc_in< bool > MemRead_exe, MemRead_mem;
  //  sc_in< bool > MemRead;
    sc_in< bool> BranchTaken;        
    sc_in< bool >  RegWrite_exe, RegWrite_mem, RegWrite_wb;        
    sc_out< bool >  enable_exmem, reset_idid2, enable_regfile, reset_regfile, reset_exmem, reset_memwb; 
    sc_out< bool >  enable_pc, enable_ifid, enable_idexe, reset_haz_idexe, reset_haz_ifid, enable_idid2;        

    SC_CTOR(hazard)
    {      
        SC_METHOD(detect_hazard);
        sensitive << rs << rt 
		  << WriteReg_exe << RegWrite_exe
		  << WriteReg_mem << RegWrite_mem
          << rs_id2 << rt_id2 << WriteReg_wb 
          << RegWrite_wb 
          << MemRead_exe << MemRead_mem 
          << BranchTaken
          << rd << rd_id2;
   }
  
    void detect_hazard();
};

#endif
