#ifndef _TOP_H_
#define _TOP_H_

#include <systemc>

#include "device.hpp"
#include "host.hpp"
#include "ssd.hpp"

class Top : public sc_core::sc_module {
private:
	Device *device;
	Host *host;
	sc_core::sc_fifo<uint64_t> fifo[2];

public:
	Top(sc_core::sc_module_name name);
};

#endif
