#include "makejta.h"

/**
 * \c makejta module callback function.
 */
void makejta::calc()
{
  sc_uint<32> programcounter;
  programcounter = pc4.read(); 

  jumpaddress.write(programcounter.range(31,27)+jta.read()<<2);

}
