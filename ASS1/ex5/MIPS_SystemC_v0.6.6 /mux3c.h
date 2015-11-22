#ifndef MUX3ALUMOD_H
#define MUX3ALUMOD_H


/**
 * Mux module.
 * Mux module models a generic 4:1 multiplexor of template type T. 
 * Implementation based on a template class.
 *
 *   - input ports
 *   	- \c T \c din0		- input 
 *   	- \c T \c din1		- input 
 *   	- \c bool \c sel		- select 
 *   - output ports
 *   	- \c T \c dout		- output
 */

template <class T> class mux3alu: public sc_module
{
public:
  sc_in< sc_uint<32> >  din0;
  sc_in< sc_uint<32> >  din1;        
  sc_in< sc_uint<32> >  din2;
  //sc_in< sc_uint<32> >  din3;
  sc_in< sc_uint<2> >  sel;        
  sc_out< T > dout;

  SC_CTOR(mux3alu)
     {      
      SC_METHOD(entry);
      sensitive << din0 << din1 << din2 << sel;
    }
  
  void entry();
};  


template <class T> void mux3alu<T>::entry()
{
  switch(sel.read()) {
    case 0: dout.write(din0.read());
            break;
    case 1: dout.write(din1.read());
            break;
    case 2: dout.write(din2.read());
            break;
    }
}

#endif
