#include "../include/iron_rabbit_gc.h"
#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"

int main()
{
	IR_info();

	int *ptr1 = IR_malloc(sizeof(int));
	*ptr1 = 10;
	IR_info();

	char *ptr2 = IR_malloc(6 * sizeof(char));
	strcpy(ptr2, "Hello");
	IR_info();

	long *ptr3 = IR_malloc(sizeof(long));
	*ptr3 = 256;
	IR_info();

	strcpy(ptr2, "Hello world!");
	
	printf("Returned values:\n");
	printf("%p (%d)\n", ptr1, *ptr1);
	printf("%p (%s)\n", ptr2, ptr2);
	printf("%p (%li)\n", ptr3, *ptr3);

	return 0;
}
