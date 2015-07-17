#include <stdio.h>

int main()
{
	int num;
	int storage;//retains original value of num

	fprintf(stdout, "Enter an integer: " );
	fscanf(stdin, "%d", &num );
	storage = num;

	num = storage;
	num = num >> 4;
	printf( "\nnum bitwise shifted right: %d\n", num );

	return 0;
}
