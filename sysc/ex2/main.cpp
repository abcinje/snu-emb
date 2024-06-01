#include "systemc.h"

SC_MODULE (generator) {
  sc_out<short> sig;
  sc_out<short> buf;
  
  void do_it(void){
    wait(5, SC_NS);
    sig.write(5); buf.write(5); wait(10, SC_NS);
    sig.write(6); buf.write(6); wait(10, SC_NS);
    sig.write(6); buf.write(6); wait(10, SC_NS);
    sig.write(7); buf.write(7); wait(10, SC_NS);
    sig.write(7); buf.write(7); wait(10, SC_NS);

  }

  SC_CTOR(generator){
    SC_THREAD(do_it);
  }
};


SC_MODULE(receiver){
  sc_in<short> iport;

  void do_it(void){
    cout<<sc_time_stamp() <<":"<<name() <<" got " <<iport.read() <<endl;
  }

  SC_CTOR(receiver){
    SC_METHOD(do_it);
    sensitive <<iport;
    dont_initialize();
  }
};



int sc_main(int argc, char *argv[]){
  sc_signal<short> sig;
  sc_buffer<short> buf;

  generator GEN("GEN");
  GEN.sig(sig); GEN.buf(buf);

  receiver REV_SIG("REV_SIG");
  REV_SIG.iport(sig);
  receiver REV_BUF("REV_BUF");
  REV_BUF.iport(buf);

  sc_trace_file *tf = sc_create_vcd_trace_file("wave");
  sc_trace(tf, sig, "sig"); sc_trace(tf, buf, "buf");

  sc_start();
  sc_close_vcd_trace_file(tf);
  return(0);
}
