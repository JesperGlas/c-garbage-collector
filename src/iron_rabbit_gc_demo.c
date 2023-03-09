#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "../include/iron_rabbit_gc.h"

int main()
{
	printf("Hello from demo!\n");

	IR_info();

	int *ptr1 = (int *) IR_malloc(sizeof(int));
	(*ptr1) = 5;
	printf("Returned ptr1: %p (%d)\n", (void *) ptr1, (*ptr1));
	IR_info();

	int *ptr2 = (int *) IR_malloc(sizeof(int));
	(*ptr2) = 10;
	printf("Returned ptr2: %p (%d)\n", (void *) ptr2, (*ptr2));
	IR_info();

	return 0;
}
