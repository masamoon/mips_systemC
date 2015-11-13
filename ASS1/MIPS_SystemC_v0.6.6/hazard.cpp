
#include "hazard.h"


void hazard::detect_hazard()
{
	
	if( rs.read()!=0 && rs.read()==WriteReg_exe.read() && RegWrite_exe.read()==true
	    || rs.read()!=0 && rs.read()==WriteReg_mem.read() && RegWrite_mem.read()==true
	    || rs.read()!=0 && rs.read()==WriteReg_wb.read() && RegWrite_wb.read()==true
	    || rt.read()!=0 && rt.read()==WriteReg_exe.read() && RegWrite_exe.read()==true && MemRead_exe.read() == true // no caso do lw  
	    || rt.read()!=0 && rt.read()==WriteReg_mem.read() && RegWrite_mem.read()==true && MemRead_mem.read() == true
	    || rt.read()!=0 && rt.read()==WriteReg_wb.read() && RegWrite_wb.read()==true){

				
            
                enable_pc.write(false);
				enable_ifid.write(false);
				enable_idid2.write(false);
			//	enable_regfile.write(false);	
				reset_haz_ifid.write(false);
				reset_idid2.write(false);
				reset_haz_idexe.write(true);
				reset_exmem.write(false);
				reset_memwb.write(false);

                
                                
                printf("hazard\n");
	}else if ( BranchTaken.read() ) {
                enable_pc.write(true);
            	enable_idid2.write(true);
			//	enable_regfile.write(true);
                enable_ifid.write(true);
                reset_idid2.write(false);
				reset_haz_idexe.write(false);
				reset_haz_ifid.write(true);
				reset_exmem.write(false);
				reset_memwb.write(false);
                
                //reset_exmem.write(true);
                
                printf("taken\n");
	    
	    
	}
	else{
        enable_pc.write(true);
		enable_ifid.write(true);
		enable_idid2.write(true);
	//	enable_regfile.write(true);
		reset_haz_idexe.write(false);
		reset_idid2.write(false);
		reset_haz_ifid.write(false);
		reset_exmem.write(false);
		reset_memwb.write(false);

        printf("no hazard\n");
        }
}


