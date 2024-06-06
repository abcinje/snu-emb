#include "device.hpp"
#include "ssd.hpp"

void Device::device_thread(void)
{
	while (true) {
		uint64_t lba = in->read();
		out->write(lba);
	}
}

Device::Device(sc_core::sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(Device);
	SC_THREAD(device_thread);
}
