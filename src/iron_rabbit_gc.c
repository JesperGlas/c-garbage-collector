#include "../include/iron_rabbit_gc.h"
#include "stddef.h"	// used for type size_t, ptrdiff_t (unsigned long %lu)
#include "stdbool.h"	// used for type bool (int)
#include "unistd.h"	// contains sbrk method
#include "stdio.h"	// used for printf method
#include "string.h"	// used for memcpy method

// global variables
bool g_active = false;
size_t g_pagesize;
void *g_start;
void *g_end;
size_t g_capacity;
header_st *g_used;
header_st *g_free;

void IR_init()
{
	// init heap
	g_pagesize = sysconf(_SC_PAGESIZE);
	g_start = (void *) sbrk(g_pagesize);
	g_end = (void *) sbrk(0);

	// init ptr to used memory
	g_used = g_start;
	g_used->m_size = 0;
	g_used->m_next = g_used + sizeof(header_st);

	// init ptr to free memory
	g_free = g_used->m_next;
	g_free->m_size = g_pagesize - 2*sizeof(header_st);
	g_free->m_next = (void *) NULL;

	// set heap as active
	g_active = true;
}

void IR_info()
{
	// make sure heap is initiated
	if (g_active == false)
	{
		printf("### HEAP INFO ###\n");
		printf("\tHeap is not initiated..\n");
		printf("### END ###\n");
		return;
	}

	// general heap info
	printf("### HEAP INFO ###\n");
	printf("\t%p [0]\tHeap start\n",
		(void *) g_start );
	printf("\t%p [%li]\tHeap end\n",
		(void *) g_end,
		g_end - g_start );
	
	// used memory info
	size_t i = 0;
	for (header_st *ptr = g_used; ptr != g_free; ptr = ptr->m_next, i++)
	{
		printf("\t%p [%li]\tUsed block %li (Size: %lu)\n",
			(void *) ptr,
			(ptrdiff_t) ((char *) ptr - (char *) g_start),
			i, ptr->m_size
		);
	} // end of used memory loop
	
	// free memory info
	i = 0;
	for (header_st *ptr = g_free; ptr != (void *) NULL; ptr = ptr->m_next, i++)
	{
		printf("\t%p [%li]\tFree block %li (Size: %lu)\n",
			(void *) ptr,
			(ptrdiff_t) ((char *) ptr - (char *) g_start),
			i, ptr->m_size
		);
	} // end of free memory loop
	
	printf("### END ###\n");
}

void *IR_malloc(size_t bytes_size)
{
	if (g_active == false)
		IR_init();

	// calculate new block size
	size_t block_size = sizeof(header_st) + bytes_size;
	printf("Block size: %lu\n", block_size);

	// assign current free block to variable
	header_st *ptr = g_free;

	// update free block address
	g_free += block_size;
	memcpy(g_free, ptr, sizeof(header_st));
	g_free->m_size -= block_size;

	// update new block
	ptr->m_size = bytes_size;
	ptr->m_next = g_free;

	// update used block
	g_used->m_next = ptr;

	return ptr + sizeof(header_st);
}
