#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void input(int amount, char list[][50])
{
	for(int i = 0; i < amount; i++)
	{
		scanf("%s",list[i]);	
	}
}

int main()
{

	int amountOfStrings = 0;
	char list[100][50];

	printf("How many strings?\t");
	scanf("%d",&amountOfStrings);

	while(amountOfStrings < 1 || amountOfStrings > 100)
	{
		printf("Number must be between 1 and 100 inclusive\t");
		scanf("%d",&amountOfStrings);
	}

	input(amountOfStrings, list);

	printf("\nStrings that begin with \"ai\" in reverse are:\n");

	for(int j = amountOfStrings; j >= 0; j--)
	{
		if(strncmp(list[j], "ai", 2)==0)
		{
			printf("%d: %s\n",j+1,list[j]);
		}
	}

	return 0;

}