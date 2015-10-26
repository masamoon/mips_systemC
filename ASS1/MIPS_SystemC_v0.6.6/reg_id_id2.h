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

	sc_in  < sc_uint<32> > imm_id, PC4_id;
	sc_out < sc_uint<32> > imm_id2, PC4_id2;

	sc_in < sc_uint<6> > opcode_id;
	sc_out < sc_uint<6> > opcode_id2;

	sc_in <sc_uint<6>> funct_id;
	sc_out <sc_uint<6>> funct_id2; 


	regT < sc_uint<32> > *PC;      // only for visualization purposes
	regT < bool > *valid;          // only for visualization purposes

	SC_CTOR(reg_id_id2_t) {

		opcode = new regT< sc_uint<6>> ("opcode");
		opcode-> din(opcode_id);
		opcode-> din(opcode_id2);
		opcode->clk(clk);
		opcode->enable(enable);
		opcode->reset(reset);

		PC4 = new regT < sc_uint<32> >("PC4");
		PC4->din(PC4_id);
		PC4->dout(PC4_exe);
		PC4->clk(clk);
		PC4->enable(enable);
		PC4->reset(reset);

		imm = new regT < sc_uint<32> >("imm");
		imm->din(imm_id);
		imm->dout(imm_id2);
		imm->clk(clk);
		imm->enable(enable);
		imm->reset(reset);

		PC = new regT < sc_uint<32> >("PC");
		PC->din(PC_id);
		PC->dout(PC_exe);
		PC->clk(clk);
		PC->enable(enable);
		PC->reset(reset);

		funct = new regT<sc_uint<6>>("funct");
		funct ->din(funct_id);
		funct ->dout(funct_id2); 
		funct -> clk(clk);
		funct ->enable(enable);
		funct ->reset(reset);

	}
};

#endif
