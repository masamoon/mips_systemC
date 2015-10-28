
// sub.cpp

#include "sub.h"

/**
 * callback function of module \c add.
 */
void add::calc()
{
   res.write(op1.read()-op2.read());
}
