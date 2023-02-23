#include "stdio.h"
#include "../include/iron_rabbit_gc.h"

int main()
{
	printf("Hello from demo!\n");

	#if VERBOSE==1
	printf("Verbose..\n");
	#endif

	return 0;
}
