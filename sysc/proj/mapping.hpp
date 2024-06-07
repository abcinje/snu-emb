#ifndef _MAPPING_HPP_
#define _MAPPING_HPP_

#include <cstdint>

#include "ssd.hpp"

#define INVALID_LBA (0xfffffffffffffffful)
#define INVALID_MUN (0xfffffffffffffffful)

class Mapping {
private:
	uint64_t l2p[LBA_MAX];
	uint64_t p2l[NUM_PAGE];
	int vc[NUM_BLOCK];

public:
	Mapping(void);

	uint64_t read_l2p(uint64_t lba);
	void write_l2p(uint64_t lba, uint64_t mun);

	uint64_t read_p2l(uint64_t mun);
	void write_p2l(uint64_t mun, uint64_t lba);

	int read_vc(int spblk_num);
	void dec_vc(int spblk_num);
	void reset_vc(int spblk_num);
};

#endif
