// comparator.cpp

#include "comparator.h"

/**
 * callback function of module \c comparator.
 */
void comparator::calc()
{
	if(op1.read() == op2.read())
		res.write(true);
	else
		res.write(false);
   
}
