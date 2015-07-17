#include <stdio.h>

void bNumber(int num)
{
   int binary;

   binary = num%2;
   num /= 2;

   if (num != 0)
   {
       bNumber(num);
   }

   printf("%d",binary);

   return;
}




int main()
{

    int counter;
    int num;

    printf("Decimal:\tBinary:\t\tOctagonal:\tHexidecimal:\n");

    for (counter = 1; counter <=256; counter ++)
    {
        printf("%d\t\t",counter);
        bNumber(counter);
        printf("\t\t%o",counter);
        printf("\t\t%x",counter);
        printf("\n");
    }
}
