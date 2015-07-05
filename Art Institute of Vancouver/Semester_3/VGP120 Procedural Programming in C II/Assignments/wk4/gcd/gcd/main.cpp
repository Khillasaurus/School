#include <stdio.h>

//function prototypes
int FindGCD(const int, const int);

int main()
{
	int x = 0;
	int y = 0;

	printf("Please enter the two numbers that you would like to find the greatest common denominator of.\n");
	scanf("%d", &x);
	scanf("%d", &y);

	printf("The greatest common denominator of %d and %d is: %d\n", x, y, FindGCD(x, y));
}

int FindGCD(const int x, const int y)
{
	if((x % y) == 0)
	{
		return y;
	}
	else
	{
		return FindGCD(y, x % y);
	}
}