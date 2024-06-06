#ifndef _SSD_H_
#define _SSD_H_

#include <cstdint>

#define CAPACITY (1UL << 32)
#define SECTOR_SIZE (4096)
#define LBA_MAX (CAPACITY / SECTOR_SIZE)

#define PAGE_SIZE (4096)
#define PAGE_PER_BLOCK (256)
#define NUM_BLOCK (4383)

#define NUM_PAGE (PAGE_PER_BLOCK * NUM_BLOCK)

#endif
