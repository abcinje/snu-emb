#include "adder_method.h"
#include "adder_thread1.h"
#include "adder_thread2.h"
#include "adder_thread3.h"
#include "adder_cthread.h"
#include "stimulus.h"

int sc_main(int argc, char *argv[]){
  sc_core::sc_report_handler::set_actions( "/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING );
  sc_signal<int> A, B, R_M, R_T1, R_T2, R_T3, R_C;
  sc_set_time_resolution(1, SC_NS);
  sc_set_default_time_unit(1, SC_NS);
  sc_clock clock("clock", 20, SC_NS, 0.5, 15, SC_NS);

  adder_method AD_M("adder_method");
  AD_M(A,B,R_M);
  adder_thread1 AD_T1("adder_thread");
  AD_T1(A,B,R_T1, clock);
  adder_thread2 AD_T2("adder_thread2");
  AD_T2(A,B,R_T2);
  adder_thread3 AD_T3("adder_thread3");
  AD_T3(A,B,R_T3, clock);
  adder_cthread AD_C("adder_cthread");
  AD_C(A,B,R_C,clock);
  stimulus STIM("stimulus");
  STIM(A,B, clock);

  sc_trace_file * tf = sc_create_vcd_trace_file("wave");
  sc_trace(tf, clock, "clock");
  sc_trace(tf, A, "A");
  sc_trace(tf, B, "B");
  sc_trace(tf, R_M, "R_M");
  sc_trace(tf, R_T1, "R_T1");
  sc_trace(tf, R_T2, "R_T2");
  sc_trace(tf, R_T3, "R_T3");
  sc_trace(tf, R_C, "R_C");
  sc_start(80, SC_NS);
  return 0;
}

