#include "forward.h"

/**
 * forwarding unit.
 */
void forward::forwarding()
{
		mux_alu1.write(0); 
		mux_alu2.write(0);
                mux_mem.write(0); 
		mux_dmem.write(0);

		if(rs.read() != 0 && rs.read() == WriteReg_mem.read() && RegWrite_mem.read() ) //Rtype dependencia dados de EXE para MEM (rs)
			mux_alu1.write(1); 
		
		if(rt.read() != 0 && rt.read() == WriteReg_mem.read() && RegWrite_mem.read() ) //Rtype dependencia dados de EXE para MEM (rt)
			mux_alu2.write(1); 

		if(rs.read() != 0 && rs.read() == WriteReg_wb.read() && RegWrite_wb.read() )   //Rtype de EXE para WB (rs)
			mux_alu1.write(2);
		
		if(rt.read() != 0 && rt.read() == WriteReg_wb.read() && RegWrite_wb.read() ) //Rtype de EXE para WB (rt) 
			mux_alu2.write(2);

		if(rt.read() != 0 && rt.read() == WriteReg_wb.read() && RegWrite_wb.read() && MemWrite_exe.read()) //store word + rtype  EXE para WB 
                        mux_mem.write(1); 
		
		if(MemToReg_wb.read() && MemWrite_mem.read() && rt_mem.read() != 0 && rt_mem.read() == WriteReg_wb.read()) //store word + load word MEM para WB 
			mux_dmem.write(1);					
			
		
}
