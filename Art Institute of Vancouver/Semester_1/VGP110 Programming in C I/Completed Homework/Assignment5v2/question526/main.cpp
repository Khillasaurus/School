#include <stdio.h>
#include <math.h>


void perfect(int p)
{
    int pNum;

    pNum = ((pow(2,(p-1)))*((pow(2,p))-1));

    printf("%d, ",pNum);
}




int main()
{

    int prime[] = { 2, 3, 5};

    int pNum;

    printf("The perfect numbers between 1 and 1000 are:\n");

    for(int counter = 0; counter < 3; counter++)
    {
        perfect(prime[counter]);
    }


    return 0;
}
