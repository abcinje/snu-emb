#include <random>

#include "host.hpp"
#include "ssd.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<uint64_t> distr(0, LBA_MAX - 1);

void Host::host_thread(void)
{
	for (int i = 0; i < 1024; i++) {
		uint64_t lba = distr(gen);
		std::cout << lba << std::endl;

		out->write(lba);
		assert(in->read() == lba);
	}
}

Host::Host(sc_core::sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(Host);
	SC_THREAD(host_thread);
}
