#include "top.hpp"

Top::Top(sc_core::sc_module_name name) : sc_module(name)
{
	device = new Device("device");
	host = new Host("host");

	host->out(fifo[0]);
	device->in(fifo[0]);

	device->out(fifo[1]);
	host->in(fifo[1]);
}
