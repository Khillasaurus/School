#include <stdio.h>

void update2Var(int *, int *);


int main()
{

	int a = 1; //non-const pointer to non-constant variable
	int b = 2; //constant pointer to non-constant variable
	const int c = 3; //non-constant pointer to constant variable
	const int d = 4; //constant pointer to constant variable

	printf("The starting value of a is: %d\n",a);
	printf("The starting value of b is: %d\n",b);
	printf("The starting value of c is: %d\n",c);
	printf("The starting value of d is: %d\n\n",d);

	update2Var(&a, &b);

	printf("The new value of a is: %d\n",a);
	printf("The new value of b is: %d\n",b);
	printf("The new value of c is: error\n");
	printf("The new value of d is: error\n\n");

	return 0;

}


void update2Var(int *aPtr, int *const bPtr)
{

	*aPtr = 5;
	*bPtr = 10;
		/* won't work
	*cPtr = 15;
	*dPtr = 20;
		*/

	return;

}
