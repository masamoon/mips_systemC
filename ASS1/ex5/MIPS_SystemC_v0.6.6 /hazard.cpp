
#include "hazard.h"

/**
 * Callback for the hazrd detection of \c hazard module.
 */
void hazard::detect_hazard()
{
	//data hazards
	if( rt.read()!= 0 && rt.read()==WriteReg_exe.read() && jbr.read() != 0 //branch data dependency  
	    || rs.read()!= 0 && rs.read() == WriteReg_exe.read() && jbr.read()!= 0 // branch data dependency 
	    || rs.read()!= 0 && rs.read() == WriteReg_exe.read() && jbr.read()!= 0 && MemRead_exe.read() == true // branch data dependency with lw 
	    || rt.read()!= 0 && rt.read() == WriteReg_exe.read() && jbr.read()!= 0 && MemRead_exe.read() == true 
	    || rt.read()!= 0 && rt.read() == WriteReg_mem.read() && jbr.read()!= 0 && RegWrite_mem.read() == true && MemWrite.read() == false  //second bubble for lw branch dependency 
	    || rs.read()!= 0 && rs.read() == WriteReg_mem.read() && jbr.read()!= 0 && RegWrite_mem.read() == true && MemWrite.read() == false 
		//rs.read()!=0 && rs.read()==WriteReg_exe.read() && RegWrite_exe.read()==true
	    //|| rs.read()!=0 && rs.read()==WriteReg_mem.read() && RegWrite_mem.read()==true
	    //|| rs.read()!=0 && rs.read()==WriteReg_wb.read() && RegWrite_wb.read()==true
	       || rt.read()!=0 && rt.read()==WriteReg_exe.read() && RegWrite_exe.read()==true && MemRead_exe.read() == true && MemWrite.read() == false // no caso do lw  
	       || rs.read()!= 0 && rs.read() && WriteReg_exe.read() && RegWrite_exe.read()== true && MemRead_exe.read() == true && MemWrite.read() == false)	
	    //|| rt.read()!=0 && rt.read()==WriteReg_mem.read() && RegWrite_mem.read()==true && MemRead.read() == false)
            //|| rt.read()!=0 && rt.read()==WriteReg_wb.read() && RegWrite_wb.read()==true)
		{

		enable_pc.write(false);
		enable_ifid.write(false);
		enable_id1id2.write(false);
		enable_rfile.write(false);
		reset_ifid.write(false);
		reset_id1id2.write(false);
		reset_idexe.write(true);
		reset_exmem.write(false);
		reset_memwb.write(false);
		
	}
	else if(BranchTaken.read()){

		enable_pc.write(true);	
		enable_ifid.write(true);
		enable_id1id2.write(true);
		enable_rfile.write(true);
		reset_id1id2.write(false);
		reset_idexe.write(false);
		reset_ifid.write(true);
		reset_exmem.write(false);
		reset_memwb.write(false);
	}
	else {
        enable_pc.write(true);
		enable_ifid.write(true);
		enable_id1id2.write(true);
		enable_rfile.write(true);
		reset_idexe.write(false);
		reset_id1id2.write(false);
		reset_ifid.write(false);
		reset_exmem.write(false);
		reset_memwb.write(false);
	}
}

