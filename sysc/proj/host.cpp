#include <cassert>
#include <random>

#include "config.hpp"
#include "host.hpp"
#include "ssd.hpp"

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_int_distribution<uint64_t> distr(0, LBA_MAX - 1);

void Host::host_thread(void)
{
	if (IO_PATTERN == 0)
		for (unsigned long i = 0; i < (IO_SIZE_MB << 8); i++) {
			uint64_t lba = i % LBA_MAX;
			out->write(lba);
		}
	else if (IO_PATTERN == 1)
		for (unsigned long i = 0; i < (IO_SIZE_MB << 8); i++) {
			uint64_t lba = distr(gen);
			out->write(lba);
		}
	else
		assert(false);

	out->write(MAGIC);
}

Host::Host(sc_core::sc_module_name name) : sc_module(name)
{
	SC_HAS_PROCESS(Host);
	SC_THREAD(host_thread);
}
