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

void IR_init()
{
	// set global variable for page size
	g_pagesize = sysconf(_SC_PAGESIZE);

	// initialize heap
	g_heap = malloc(g_pagesize);
	g_heap->m_size = g_pagesize - sizeof(header_st);
	g_heap->m_next = g_heap + sizeof(header_st);

	// initialize free ptr
	g_free = g_heap->m_next;
	g_free->m_size = g_heap->m_size;
	g_free->m_next = (void *) NULL;

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
	printf("\t%p [0] Heap start\n", (void *) g_heap);

	// print all free blocks
	size_t i = 0;
	for (header_st *ptr = g_free; ptr != (void *) NULL; ptr = ptr->m_next, i++)
	{
		printf(	"\t%p [%lu] Free block %lu (Size %lu)\n",
			(void *) ptr,
			ptr - g_heap,
			i,
			ptr->m_size
		);
	}

	// print all used blocks
	i = 0;
	for (header_st *ptr = g_heap->m_next; ptr != g_free; ptr = ptr->m_next)
	{
		printf(	"\t%p [%lu] Used block %lu (Size %lu)\n",
			(void *) ptr,
			ptr - g_heap,
			i,
			ptr->m_size
		);
	}
}

void *IR_malloc(size_t bytes_size)
{
	// init heap on first call to IR_malloc
	if (g_heap_init == false)
		IR_init();

	size_t chunk_size = sizeof(header_st) + bytes_size;

	// save old free header
	header_st *ptr = g_free;

	// update free ptr and header
	g_free += chunk_size;
	g_free->m_size = ptr->m_size - chunk_size;
	g_free->m_next = (void *) NULL;

	// update ptr header
	ptr->m_size = chunk_size;
	ptr->m_next = g_free;

	return ptr + sizeof(header_st);
}
