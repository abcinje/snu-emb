#include "block_manager.hpp"
#include "device.hpp"
#include "ssd.hpp"

void Device::device_thread(void)
{
	BlockManager *block_manager = new BlockManager;

	while (true) {
		uint64_t lba = in->read();
		if (lba == MAGIC)
			block_manager->report();
		else
			block_manager->run(lba);
	}
}

Device::Device(sc_core::sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(Device);
	SC_THREAD(device_thread);
}
