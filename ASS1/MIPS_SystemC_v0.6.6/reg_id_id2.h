#ifndef REG_ID_ID2_H
#define REG_ID_ID2_H

/**
 *
 * reg_id_id2_t module interface.
 */

#include <systemc.h>

#include "regT.h"

/**
 * reg_id_id2_t module.
 * reg_id_id2_t module is the ID/EXE pipeline register. 
 */

SC_MODULE(reg_id_id2_t) {

	// Ports
	
	sc_in  < bool > clk;
	sc_in  < bool > reset;
	sc_in  < bool > enable;

	sc_in  < sc_uint<32> > PC4_id, PC_id;
	sc_out < sc_uint<32> > PC4_id2, PC_id2; 
	sc_in  < sc_uint<16> > imm_id;
	sc_out < sc_uint<16> > imm_id2;
	sc_in < sc_uint<5> > rs; 
	sc_in < sc_uint<5> > rt; 
	sc_in < sc_uint<5> > rd;

	sc_out < sc_uint<5> > rs_id2; 
	sc_out < sc_uint<5> > rt_id2; 
	sc_out < sc_uint<5> > rd_id2; 


	sc_in < bool > valid_id;
	sc_out < bool > valid_id2; 

	sc_in < sc_uint<6> > opcode_id;
	sc_out < sc_uint<6> > opcode_id2;

	sc_in < sc_uint<6> >  funct_id;
	sc_out < sc_uint<6> > funct_id2; 

	sc_in < bool > branch_id; 
	sc_out < bool > branch_id2; 

	regT < sc_uint<32> > *PC4;
	regT < sc_uint<16> > *imm;
	
	regT < sc_uint<6> > *funct;
	regT < sc_uint<6> > *opcode;
	//regT < sc_uint<3> > *ALUOp;

	regT < bool > *branch; 

	regT < sc_uint<32> > *PC;      // only for visualization purposes
	regT < bool > *valid;          // only for visualization purposes

	SC_CTOR(reg_id_id2_t) {


		branch = new regT< bool > ("branch");
		branch ->din(branch_id);
		branch ->dout(branch_id2);
		branch ->clk(clk);
		branch ->enable(enable);
		branch ->reset(reset);



     
		opcode = new regT< sc_uint<6> > ("opcode");
	    opcode->din(opcode_id);
		opcode->dout(opcode_id2);
		opcode->clk(clk);
		opcode->enable(enable);
		opcode->reset(reset);

#if 1
		PC4 = new regT < sc_uint<32> >("PC4");
		PC4->din(PC4_id);
		PC4->dout(PC4_id2);
		PC4->clk(clk);
		PC4->enable(enable);
		PC4->reset(reset);
     
		imm = new regT < sc_uint<16> >("imm");
	    imm->din(imm_id);
		imm->dout(imm_id2);
		imm->clk(clk);
		imm->enable(enable);
		imm->reset(reset);

	
		funct = new regT< sc_uint<6> >("funct");
		funct ->din(funct_id);
		funct ->dout(funct_id2); 
		funct -> clk(clk);
		funct ->enable(enable);
		funct ->reset(reset);

	//só para visualização 
		PC = new regT < sc_uint<32> >("PC");
		PC->din(PC_id);
		PC->dout(PC_id2);
		PC->clk(clk);
		PC->enable(enable);
		PC->reset(reset);


		valid = new regT < bool >("valid");
		valid->din(valid_id);
		valid->dout(valid_id2);
		valid->clk(clk);
		valid->enable(enable);
		valid->reset(reset);
	#endif

	}
};

#endif
