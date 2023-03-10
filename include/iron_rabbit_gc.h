#ifndef __IRON_RABBIT_GC_H__
#define __IRON_RABBIT_GC_H__

#include "stddef.h"

// flag for GC information being printed to terminal
#ifndef VERBOSE
#define VERBOSE 1
#endif

typedef struct header
{
	size_t m_size;
	struct header *m_next;
} header_st;

void IR_info();
void *IR_malloc(size_t bytes_size);

#endif
