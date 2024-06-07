#ifndef _SSD_HPP_
#define _SSD_HPP_

#define CAPACITY (1ul << 32)
#define SECTOR_SIZE (4096)
#define LBA_MAX (CAPACITY / SECTOR_SIZE)

#define PAGE_SIZE (4096)
#define PAGE_PER_BLOCK (256)
#define NUM_BLOCK (5243)
#define NUM_PAGE (PAGE_PER_BLOCK * NUM_BLOCK)

#define GC_THRESHOLD (97)
#define GC_DIFF_WEIGHT (10)
#define GC_RATIO_MAX (990)

#define MAGIC (0xdeadbeef)

#endif
