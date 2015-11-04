#include "makejta.h"

/**
 * \c makejta module callback function.
 */
void makejta::calc()
{
  
  jumpaddress.write(PC4.range(31,27)+jta.read()<<2);

}
