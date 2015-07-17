#include <stdio.h>

void fillArray(bool isPrime[1000], int &i)
{

    for(i = 0; i<1000; i++)
    {
        isPrime[i]=1;
    }

    return;

}



void drawArray(bool isPrime[1000])
{

    for(int m = 1; m<=1000; m++)
    {
        printf("%d: %d\n",m,isPrime[m]);
    }

    return;

}



int main()
{

    bool isPrime[1000];
    int i = 0;
    fillArray(isPrime, i);

    for(int j = 1; j<1000; j++)
    {
        for(int k = 1; k<j; k++)
        {
            if(isPrime[j]%k==0)
            {
                isPrime[i]=0;
                k=1001;
            }
        }
    }

    drawArray(isPrime);

    return 0;

}
