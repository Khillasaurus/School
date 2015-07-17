#include <stdio.h>

int main()
{

	float *fPtr;
	bool *bPtr;
	unsigned long *ulPtr;

	float x = 3.50;
	bool y = false;
	unsigned long z =1234567890;

	fPtr = &x;
	bPtr = &y;
	ulPtr = &z;

	printf("This pointer is pointing to a value inside float x which is equal to: %.2f\n",*fPtr);
	printf("This pointer is pointing to a value inside bool y which is equal to: %d\n",*bPtr);
	printf("This pointer is pointing to a value inside unsigned long z which is equal to: %u\n\n",*ulPtr);

	printf("The address of fPtr is: %d\n",&fPtr);
	printf("The address of bPtr is %d\n",&bPtr);
	printf("The address of ulPtr is %d\n\n",&ulPtr);

	*fPtr += 5;
	*bPtr += 5;
	*ulPtr += 5;

	printf("This pointer is pointing to a value inside float x which is equal to: %2f\n",*fPtr);
	printf("This pointer is pointing to a value inside bool y which is equal to: %d\n",*bPtr);
	printf("This pointer is pointing to a value inside unsigned long z which is equal to: %u\n\n",*ulPtr);	
	
	fPtr += 5;
	bPtr += 5;
	ulPtr += 5;

	printf("The new address the pointer fPtr is pointing to is: %p\n",fPtr);
	printf("The new address the pointer bPtr is pointing to is: %p\n",bPtr);
	printf("The new address the pointer ulPtr is pointing to is: %p\n\n",ulPtr);


	return 0;

}