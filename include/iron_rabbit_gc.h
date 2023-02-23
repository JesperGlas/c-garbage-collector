#ifndef __IRON_RABBIT_GC_H__
#define __IRON_RABBIT_GC_H__

// flag for GC information being printed to terminal
#ifndef VERBOSE
#define VERBOSE 1
#endif

// specifies the smallest alloc size allowed (page size)
#define MIN_ALLOC_SIZE 4096

/**
 * Struct for the header of our heaps memory blocks
 * */
typedef struct header {
	unsigned int m_size;
	struct header *m_next;
} header_st;

#endif
