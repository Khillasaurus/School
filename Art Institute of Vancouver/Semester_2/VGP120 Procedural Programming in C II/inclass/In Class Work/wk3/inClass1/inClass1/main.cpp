#include <stdio.h>

int main()
{
	int num;
	int storage;//retains original value of num

	fprintf(stdout, "Enter an integer: " );
	fscanf(stdin, "%d", &num );
	storage = num;

	printf( "\nnum: %d\n", num );
	num = num << 1;
	printf( "\nnum bitwise shifted left: %d\n", num );

	num = storage;
	num = num >> 1;
	printf( "\nnum bitwise shifted right: %d\n", num );
	
	num = storage;
	num = ~num + 1;
	printf( "\nnum negated: %d\n", num );

	return 0;
}
