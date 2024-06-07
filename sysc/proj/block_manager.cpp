#include <cassert>
#include <cstring>
#include <iostream>

#include "block_manager.hpp"

BlockManager::BlockManager(void)
		: num_free(NUM_BLOCK), write_spblk(INVALID_SPBLK), write_page(PAGE_PER_BLOCK),
		  gc_spblk(INVALID_SPBLK), gc_page(PAGE_PER_BLOCK)
{
	std::memset(state, 0x0, NUM_BLOCK * sizeof(BlockState));
}

int BlockManager::alloc_spblk(void)
{
	for (int spblk_num = 0; spblk_num < NUM_BLOCK; spblk_num++)
		if (state[spblk_num] == BlockState::FREE) {
			num_free--;
			state[spblk_num] = BlockState::OPEN;
			mapping.reset_vc(spblk_num);
			return spblk_num;
		}

	std::cerr << "Stuck\n" << std::endl;
	while (true);
}

void BlockManager::write(uint64_t lba)
{
	/* Allocate a free block */
	if (write_spblk == INVALID_SPBLK) {
		write_spblk = alloc_spblk();
		write_page = 0;
	}

	/* Invalidate the page */
	uint64_t old_mun = mapping.read_l2p(lba);
	if (old_mun != INVALID_MUN) {
		uint64_t old_spblk_num = old_mun / PAGE_PER_BLOCK;
		mapping.dec_vc(old_spblk_num);
	}

	/* Update the mapping tables */
	uint64_t mun = write_spblk * PAGE_PER_BLOCK + write_page;
	mapping.write_l2p(lba, mun);
	mapping.write_p2l(mun, lba);
	write_page++;

	/* Close the block */
	if (write_page == PAGE_PER_BLOCK) {
		state[write_spblk] = BlockState::CLOSED;
		write_spblk = INVALID_SPBLK;
	}
}

int BlockManager::get_ratio(int num_free, int vc)
{
	assert(num_free < GC_THRESHOLD);

	int diff = GC_THRESHOLD - num_free;
	int gwrite_ratio = vc + GC_DIFF_WEIGHT * diff;
	if (gwrite_ratio > GC_RATIO_MAX)
		gwrite_ratio = GC_RATIO_MAX;

	return 1000 - gwrite_ratio;
}

int BlockManager::prepare_gc(void)
{
	assert(gc_spblk == INVALID_SPBLK);

	/* Pick the closed block with minimum vc */
	for (int spblk_num = 0; spblk_num < NUM_BLOCK; spblk_num++)
		if (state[spblk_num] == BlockState::CLOSED)
			if (gc_spblk == INVALID_SPBLK || mapping.read_vc(spblk_num) < mapping.read_vc(gc_spblk))
				gc_spblk = spblk_num;

	assert(gc_spblk != INVALID_SPBLK);
	gc_page = 0;
	return mapping.read_vc(gc_spblk);
}

bool BlockManager::do_gc(void)
{
	assert(gc_spblk >= 0 && gc_spblk < NUM_BLOCK);

	/* Finish */
	if (gc_page == PAGE_PER_BLOCK) {
		num_free++;
		state[gc_spblk] = BlockState::FREE;
		gc_spblk = INVALID_SPBLK;
		return false;
	}

	/* Check if the page is valid */
	uint64_t mun = gc_spblk * PAGE_PER_BLOCK + gc_page;
	uint64_t lba = mapping.read_p2l(mun);
	if (mun != mapping.read_l2p(lba)) {
		gc_page++;
		return false;
	}

	/* Request GC write */
	if (scheduler.schedule(WriteType::GC)) {
		write(lba);
		gc_page++;
	}

	return true;
}

void BlockManager::process_gc(void)
{
	while (true) {
		if (num_free >= GC_THRESHOLD) {
			scheduler.off();
			return;
		}

		if (gc_spblk == INVALID_SPBLK) {
			int vc = prepare_gc();
			int ratio = get_ratio(num_free, vc);
			scheduler.on(ratio);
		}

		if (do_gc())
			return;
	}
}

void BlockManager::run(uint64_t lba)
{
	while (true) {
		/* GC write */
		process_gc();

		/* Host write */
		if (scheduler.schedule(WriteType::HOST)) {
			write(lba);
			return;
		}
	}
}

void BlockManager::report(void)
{
	scheduler.report();
}
