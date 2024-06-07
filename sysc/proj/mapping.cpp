#include <cstring>
#include <cassert>

#include "mapping.hpp"

Mapping::Mapping(void)
{
	std::memset(l2p, 0xff, LBA_MAX * sizeof(uint64_t));
	std::memset(p2l, 0xff, NUM_PAGE * sizeof(uint64_t));
}

uint64_t Mapping::read_l2p(uint64_t lba)
{
	assert(lba >= 0 && lba < LBA_MAX);
	return l2p[lba];
}

void Mapping::write_l2p(uint64_t lba, uint64_t mun)
{
	assert(lba >= 0 && lba < LBA_MAX);
	l2p[lba] = mun;
}

uint64_t Mapping::read_p2l(uint64_t mun)
{
	assert(mun >= 0 && mun < NUM_PAGE);
	return p2l[mun];
}

void Mapping::write_p2l(uint64_t mun, uint64_t lba)
{
	assert(mun >= 0 && mun < NUM_PAGE);
	p2l[mun] = lba;
}

int Mapping::read_vc(int spblk_num)
{
	return vc[spblk_num];
}

void Mapping::dec_vc(int spblk_num)
{
	assert(vc[spblk_num] > 0);
	vc[spblk_num]--;
}

void Mapping::reset_vc(int spblk_num)
{
	vc[spblk_num] = PAGE_PER_BLOCK;
}
