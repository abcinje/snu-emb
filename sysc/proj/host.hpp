#ifndef _HOST_H_
#define _HOST_H_

#include <systemc>

#include "ssd.hpp"

class Host : public sc_core::sc_module {
private:
	void host_thread(void);

public:
	sc_core::sc_fifo_in<uint64_t> in;
	sc_core::sc_fifo_out<uint64_t> out;

	Host(sc_core::sc_module_name name);
};

#endif
