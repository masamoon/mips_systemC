// comparator.cpp

#include "comparator.h"

/**
 * callback function of module \c comparator.
 */
void comparator::calc()
{
	if(op1.read() > op2.read())
		gr.write(true);
	else
		gr.write(false);
   	
   	if(op1.read() == op2.read())
   		eq.write(true);
   	else
   		eq.write(false);

   	if(op1.read() < op2.read())
   		le.write(true);
   	else
   		le.write(false);
}
