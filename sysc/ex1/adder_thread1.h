#include "systemc.h"

SC_MODULE(adder_thread1) {
  sc_in<int> A, B;
  sc_out<int> C;
  sc_in<bool> clk;

  void do_adder(){
    while(1) {
      C = A+B;
      wait();
    }
  }

  SC_CTOR(adder_thread1){
    SC_THREAD(do_adder);
    sensitive << clk.pos();
  }
};
