
#include "regfile.h"

/**
 * instantiates the 32 registers %and initializes values to 0.
 */
void regfile::init_regs()
{
    memory.clear();
    for(int i=0;i<32;i++) memory.push_back(0);
}

/**
 * Used for debugging.
 */
void regfile::dump()
{
    for(int i=0;i<16;i++) printf(" r%2d",i);
    printf("\n");
    for(int i=0;i<16;i++) printf("%4d",(int)memory[i]);
    printf("\n");
    for(int i=0;i<16;i++) printf(" r%2d",i+16);
    printf("\n");
    for(int i=0;i<16;i++) printf("%4d",(int)memory[i+16]);
    printf("\n");
}

/**
 * Callback for behaviour of \c regfile module.
 */
void regfile::regfile_access()
{
    if(reset.read() == true) {
	init_regs();
	data1.write(0);
	data2.write(0);
    }
    else {
	if(wr.read()) {
	    if(regwrite.read() < 32 && regwrite.read() > 0){
		memory[regwrite.read()] = datawr.read();
	    }
	}
	if(reg1.read() < 32) {
		data1.write(memory[reg1.read()]);
	}
	if(reg2.read() < 32) {
		data2.write(memory[reg2.read()]);
	}
    }
}
        
