#include <stdio.h>

int main()
{

    int numbers[20];
    int storage = -100;


    for(int i = 0; i < 20; i++)
    {
        numbers[i] = 0;
    }

    printf("Please enter 20 integers between 10 and 100 (inclusive) seperated by comas.\n");
    for(int j = 0; j < 20; j++)
    {
        scanf("%d",&numbers[j]);
        if(storage == numbers[j])
        {
            printf("\tDuplicate: %d\n",numbers[j]);
        }
        storage = numbers[j];
    }


	return 0;

}
