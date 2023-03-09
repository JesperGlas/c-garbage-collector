#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "../include/iron_rabbit_gc.h"

int main()
{
	printf("Hello from demo!\n");

	IR_info();

	IR_malloc(5);
	IR_info();

	return 0;
}
