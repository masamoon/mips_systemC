
#include "hazard.h"


void hazard::detect_hazard()
{
	
	if(    rs.read()!=0 && rs.read()==WriteReg_exe.read() && RegWrite_exe.read()==true
	    || rs.read()!=0 && rs.read()==WriteReg_mem.read() && RegWrite_mem.read()==true
	    || rs_id2.read()!=0 && rs_id2.read()==WriteReg_exe.read() && RegWrite_exe.read()==true
	    || rs_id2.read()!=0 && rs_id2.read()==WriteReg_mem.read() && RegWrite_mem.read()==true
	    

	    || rt.read()!=0 && rt.read()==WriteReg_exe.read() && RegWrite_exe.read()==true && MemRead.read() == false
	    || rt.read()!=0 && rt.read()==WriteReg_mem.read() && RegWrite_mem.read()==true && MemRead.read() == false
        || rt_id2.read()!=0 && rt_id2.read()==WriteReg_exe.read() && RegWrite_exe.read()==true && MemRead.read() == false
	    || rt_id2.read()!=0 && rt_id2.read()==WriteReg_mem.read() && RegWrite_mem.read()==true && MemRead.read() == false) {

		enable_pc.write(false);
            
                enable_ifid.write(false);
                             
                enable_regfile.write(false);
                                
                enable_idid2.write(false);
                
                reset_idexe.write(true);
                
                                
                printf("hazard\n");
	} else {
	    
	    enable_pc.write(true);
		enable_ifid.write(true);
		reset_idexe.write(false);
		enable_pc.write(true);
            
        enable_ifid.write(true);
        reset_ifid.write(false);
                
        enable_idid2.write(true);
        reset_idid2.write(false);
                
        enable_regfile.write(true);
        reset_regfile.write(false);
                
        enable_idexe.write(true);
        reset_idexe.write(false);
                
        enable_exmem.write(true);
        //reset_exmem.write(false);

        printf("no hazard\n");
	}
	if( BranchTaken.read() ) {
                enable_pc.write(true);
            
                enable_ifid.write(true);
                reset_ifid.write(true);
                
                reset_idexe.write(true);
                
                //reset_exmem.write(true);
                
                printf("taken\n");
        }
}


