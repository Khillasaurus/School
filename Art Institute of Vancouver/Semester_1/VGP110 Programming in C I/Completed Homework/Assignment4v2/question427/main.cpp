#include <stdio.h>
#include <math.h>

int main()
{

    int sideA;
    int sideB;
    int sideH = 0;
    int m = 1;
    int n = 1;

    while (n<500)
    {
        while(m<n)
        {
            sideA=(pow (n,2))-(pow (m,2));
            sideB=2*n*m;
            sideH=(pow (n,2))+(pow (m,2));
            if(sideH<500)
            {
                printf("If Side A = %d, Side B = %d and Side C = %d, a right angle triangle exists.\n",sideA,sideB,sideH);
            }
            m++;
        }
        n++;
    }

    return 0;

}
