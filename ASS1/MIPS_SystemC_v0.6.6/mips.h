//mips.h

#ifndef MIPSMOD_H
#define MIPSMOD_H

/**
 *
 * MIPS module interface.
 */

#include <systemc.h>

#include "imem.h"
#include "decode.h"
#include "regfile.h"
#include "alu.h"
#include "dmem.h"
#include "control.h"
#include "hazard.h"

#include "mux.h"
#include "reg.h"
#include "ext.h"
#include "shiftl2.h"
#include "add.h"
#include "gates.h"

#include "regT.h"
#include "reg_if_id.h"
#include "reg_id_exe.h"
#include "reg_exe_mem.h"
#include "reg_mem_wb.h"

/**
 * MIPS module.
 * MIPS module is the main module of the MIPS simulator.
 * Instruction memory, register file, ALU, data memory, etc are instatiated
 * %and interconnected inside this module.
 *
 *   - input ports
 *   	- \c bool \c reset	- reset
 *   	- \c bool \c clk	- clock
 *
 * \image latex MIPS_datapathPipe3.eps "architecture of mips" width=15cm
 */

SC_MODULE(mips) {

   // Ports
   sc_in < bool > clk;
   sc_in < bool > reset;

   // Modules
   // IF 
   registo           *PCreg;     // PC register
   imem              *instmem;   // instruction memory
   add *add4;                    // adds 4 to PC
   mux< sc_uint<32> > *mPC;      // selects Next PC from PCbrach and PC + 4

   //ID
   decode            *dec1;      // decodes instruction
   regfile           *rfile;     // register file
   control           *ctrl;      // control
   mux< sc_uint<5> >  *mr;       // selects destination register
   ext *e1;                      // sign extends imm to 32 bits
   orgate *or_reset_idexe;
   hazard *hazard_unit;

   //EXE
   alu               *alu1;      // ALU
   mux< sc_uint<32> > *m1;       // selects 2nd ALU operand
   shiftl2 *sl2;                 // shift left 2 imm_ext
   add *addbr;                   // adds imm to PC + 4

   //MEM
   dmem              *datamem;   // data memory
   andgate *a1;                  // beq instruction and equal values

   //WB
   mux< sc_uint<32> > *m2;       // selects value to write in register (ALUout or MemOut)

   //pipeline registers
   reg_if_id_t       *reg_if_id;
   reg_id_exe_t      *reg_id_exe;
   reg_exe_mem_t     *reg_exe_mem;
   reg_mem_wb_t      *reg_mem_wb;

   // Signals
   
   // IF
   sc_signal < sc_uint<32> > PC,       // Program Counter
                             NPC,      // Next Program Counter
			     PC4;      // PC + 4
   sc_signal < sc_uint<32> > inst;     // current instruction
   sc_signal <bool> enable_pc;

   sc_signal <bool> enable_ifid;

   //ID
   sc_signal < sc_uint<32> > inst_id,  // current instruction ID phase
                             PC4_id;
      
   // instruction fields
   sc_signal < sc_uint<5> > rs, rt, rd;
   sc_signal < sc_uint<16> > imm;
   sc_signal < sc_uint<6> > opcode;
   sc_signal < sc_uint<5> > shamt;
   sc_signal < sc_uint<6> > funct;
   // register file signals
   sc_signal < sc_uint<5> > WriteReg;  // register to write

   sc_signal < sc_uint<32> > regdata1, // value of register rs
                             regdata2, // value of regiter rt
			     WriteVal; // value to write in register WriteReg

   sc_signal < sc_uint<32> > imm_ext;  // imm sign extended

   sc_signal < sc_uint<32> > rega_exe, // value of register rs EXE phase
                             regb_exe, // value of regiter rt EXE phase
                             regb_mem; // value of regiter rt MEM phase

   sc_signal <bool> reset_haz_idexe, reset_idexe;
   // control signals
   sc_signal <bool> MemRead, MemWrite, MemtoReg;
   sc_signal <bool> RegWrite, RegDst;
   sc_signal <bool> ALUSrc;
   sc_signal < sc_uint<3> > ALUOp;
   sc_signal <bool> Branch;

   // the following two signals are not used by the architecture
   // they are used only for visualization purposes
   sc_signal < sc_uint<32> > PC_id;      // PC of instruction in ID
   sc_signal < bool >        valid_id;   // true if there is an instruction in ID



   //ID2
   
   



   //EXE
   sc_signal < bool > Zero;            // ALU output is zero
   sc_signal < sc_uint<32> > imm_exe, PC4_exe;
   sc_signal < sc_uint<32> > addr_ext; // imm_ext shift left 2
   sc_signal < sc_uint<5> > WriteReg_exe;
   // ALU signals
   sc_signal < sc_uint<32> > ALUIn2,   // ALU second operand
                             ALUOut;   // ALU Output
   sc_signal <bool> MemRead_exe, MemWrite_exe, MemtoReg_exe;
   sc_signal <bool> RegWrite_exe;
   sc_signal <bool> ALUSrc_exe;
   sc_signal < sc_uint<3> > ALUOp_exe;
   sc_signal <bool> Branch_exe;
   
   // the following two signals are not used by the architecture
   // they are used only for visualization purposes
   sc_signal < sc_uint<32> > PC_exe;     // PC of instruction in ID
   sc_signal < bool > valid_exe;         // true if there is an instruction in ID

   //MEM
   sc_signal < sc_uint<32> > MemOut;   // data memory output
   sc_signal < sc_uint<32> > ALUOut_mem, BranchTarget_mem;   
   sc_signal < sc_uint<5> > WriteReg_mem;   
   sc_signal <bool> MemRead_mem, MemWrite_mem, MemtoReg_mem;
   sc_signal <bool> RegWrite_mem;
   sc_signal <bool> Branch_mem, Zero_mem;

   // the following two signals are not used by the architecture
   // they are used only for visualization purposes
   sc_signal < sc_uint<32> > PC_mem;   
   sc_signal < bool > valid_mem;

   //WB
   sc_signal < sc_uint<32> > MemOut_wb, ALUOut_wb;   
   sc_signal < sc_uint<5> > WriteReg_wb;   
   sc_signal <bool> MemtoReg_wb;
   sc_signal <bool> RegWrite_wb;

   // the following two signals are not used by the architecture
   // they are used only for visualization purposes
   sc_signal < sc_uint<32> > PC_wb;   
   sc_signal < bool > valid_wb;

   //nonpipelined signals
   sc_signal < sc_uint<32> > BranchTarget; // PC if branch
   sc_signal < bool > BranchTaken;       // execute branch
   sc_signal < sc_uint<32> > const4;   // contant 4
   sc_signal < bool > const1;          // contant 4

   SC_CTOR(mips) {
       buildArchitecture();
   }

   ~mips(void);

   void buildArchitecture();

   void buildIF();
   void buildID();
   void buildID2();
   void buildEXE();
   void buildMEM();
   void buildWB();
};

#endif
