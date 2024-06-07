#ifndef _BLOCK_MANAGER_HPP_
#define _BLOCK_MANAGER_HPP_

#include "mapping.hpp"
#include "scheduler.hpp"
#include "ssd.hpp"

#define INVALID_SPBLK (-1)

class BlockManager {
private:
	enum class BlockState {
		FREE,
		OPEN,
		CLOSED,
	};

	Mapping mapping;
	Scheduler scheduler;

	int num_free;
	BlockState state[NUM_BLOCK];

	int write_spblk;
	int write_page;
	int alloc_spblk(void);
	void write(uint64_t lba);

	int gc_spblk;
	int gc_page;
	int get_ratio(int num_free, int vc);
	int prepare_gc(void);
	bool do_gc(void);
	void process_gc(void);

public:
	BlockManager(void);

	void run(uint64_t lba);
	void report(void);
};

#endif
