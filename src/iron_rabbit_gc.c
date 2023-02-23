#include "../include/iron_rabbit_gc.h"
#include "unistd.h"

#if VERBOSE==1
#include "stdio.h"
#endif

static header_st gptr_base;
static header_st *gptr_free = &gptr_base;
static header_st *gptr_used;

static void add_free_memory_block(header_st *ptr_blk)
{
	// verbose info
	#if VERBOSE==1

	printf("# Adding free memory block..\n");
	printf("\tStart at: %p\n", ptr_blk);
	printf("\tSize: %iu\n", ptr_blk->m_size);
	printf("\tFree at: %p\n", gptr_free);
	printf("\tSize: %iu\n", gptr_free->m_size);

	#endif

	header_st *ptr;

	/*
	* TODO: Explain
	* */
	for (ptr = gptr_free; (ptr_blk <= ptr || ptr->m_next <= ptr_blk); ptr = ptr->m_next)
	{
		/*
		* If pointer address is greater or equal to pointer next address
		* 	(i.e. ptr lies before next in memory) and,
		* 	block pointer is greater than pointer or,
		* 	block pointer is less than next pointer,
		* 		then break the loop
		* 	
		* */
		if (ptr >= ptr->m_next && (ptr_blk > ptr || ptr_blk < ptr->m_next))
			break;
	} // end loop
	
	// if block reaches next pointer,
	if (ptr_blk + ptr_blk->m_size == ptr->m_next)
	{
		// reserve additional for block
		ptr_blk->m_size += ptr->m_next->m_size;
		ptr_blk->m_next = ptr->m_next->m_next;
	}
	else // else, 
	{
		// set block next as pointer next
		ptr_blk->m_next = ptr->m_next;
	}

	// if pointer reaches block,
	if (ptr + ptr->m_size == ptr_blk)
	{
		// move pointer to after block
		ptr->m_size += ptr_blk->m_size;
		ptr->m_next = ptr_blk->m_next;
	}

	// set new global free pointer to pointer
	gptr_free = ptr;
	return;
}

static header_st *request_kernal_memory(unsigned int units)
{
	// verbose info
	#if VERBOSE == 1
	printf("Requesting %iu units of memory from kernal..\n", units);
	#endif

	void *ptr_void;
	header_st *ptr_blk;

	if (units > MIN_ALLOC_SIZE)
	{
		units = MIN_ALLOC_SIZE / sizeof(header_st);
	}

	// if sbrk fails (returns -1 void ptr),
	if ((ptr_void = sbrk(units * sizeof(header_st))) == (void *) -1)
	{
		// verbose info
		#if VERBOSE==1
		printf("\tRequest failed at sbrk()\n");
		#endif

		// return 0 (NULL)
		return 0;
	}

	// cast void pointer returned from sbrk to header_st pointer
	ptr_blk = (header_st *) ptr_void;
	// set size of block
	ptr_blk->m_size = units;
	// add block to free memory pool (updates gptr_free)
	add_free_memory_block(ptr_blk);

	// verbose info
	#if VERBOSE==1
	printf("\tSuccess!\n");
	printf("\tStart at: %p\n", ptr_blk);
	printf("\tSize: %iu\n", ptr_blk->m_size);
	#endif

	return gptr_free;
}
