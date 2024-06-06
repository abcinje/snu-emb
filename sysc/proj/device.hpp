#ifndef _DEVICE_HPP_
#define _DEVICE_HPP_

#include <systemc>

#include "ssd.hpp"

class Device : public sc_core::sc_module {
private:
	void device_thread(void);

public:
	sc_core::sc_fifo_in<uint64_t> in;
	sc_core::sc_fifo_out<uint64_t> out;

	Device(sc_core::sc_module_name name);
};

#endif
