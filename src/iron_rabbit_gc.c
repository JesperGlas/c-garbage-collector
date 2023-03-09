#include "../include/iron_rabbit_gc.h"
#include "stdlib.h"
#include "stddef.h"
#include "stdbool.h"
#include "assert.h"
#include <unistd.h>

#if VERBOSE==1
#include "stdio.h"
#endif

bool g_heap_init = false;
size_t g_pagesize;
header_st *g_heap;
header_st *g_free;
header_st *g_used;

void IR_init()
{
	// set global variable for page size
	g_pagesize = sysconf(_SC_PAGESIZE);

	// initialize heap
	g_heap = malloc(g_pagesize);
	g_heap->m_size = g_pagesize - sizeof(header_st);
	g_heap->m_next = (void *) NULL;

	// initialize free ptr
	g_free = g_heap + sizeof(header_st);
	g_free->m_size = g_pagesize - 2 * sizeof(header_st);
	g_free->m_next = (void *) NULL;

	// initalize used ptr
	g_used = (void *) NULL;

	// set heap as active
	g_heap_init = true;
}

void IR_info()
{
	printf("### HEAP INFO ###\n");
	
	// check if heap is initalized
	if (g_heap_init == false)
	{
		printf("\tHeap is not initialized!\n");
		return;
	}

	// heap info
	printf("\tCurrent size: %lu\n", g_heap->m_size);
	printf("\t%p [0] Heap start\n", g_heap);
	printf("\t%p [%lu] Free\n", g_free, g_free - g_heap);
}

void *IR_malloc(size_t bytes_size)
{
	IR_init();

	return (void *) NULL;
}
