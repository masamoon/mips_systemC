#ifndef MUX4ALUMOD_H
#define MUX4ALUMOD_H


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

template <class T> class mux4alu: public sc_module
{
public:
  sc_in< sc_uint<32> >  din0;
  sc_in< sc_uint<32> >  din1;        
  sc_in< sc_uint<32> >  din2;
  sc_in< sc_uint<32> >  din3;
  sc_in< bool > sel1;        
  sc_in< sc_uint<2> > sel2; 
  sc_out< T > dout;

  SC_CTOR(mux4alu)
     {      
      SC_METHOD(entry);
      sensitive << din0 << din1 << din2 << din3 << sel1 << sel2;
    }
  
  void entry();
};  


template <class T> void mux4alu<T>::entry()
{

    
  switch(sel2.read()){
	case 0:
		 if(sel1.read())
			dout.write(din1.read());
		else
			dout.write(din0.read()); 
		break;
  	case 1: dout.write(din2.read());
            break;
	case 2: dout.write(din3.read());
	    break; 
 }
  	       
}

#endif
