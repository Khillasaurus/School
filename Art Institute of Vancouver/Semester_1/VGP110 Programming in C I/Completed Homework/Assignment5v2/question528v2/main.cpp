#include <stdio.h>

int main()
{

    int input;
    int reverse;

    int ones;
    int tens;
    int hundreds;
    int thousands;
    int tenThousands;
    int hundredThousands;
    int millions;

    printf("Please enter an integer and I will output the it in reverse.\n");
    scanf("%d",&input);

    ones = input%10;
    tens = (input/10)%10;
    hundreds = (input/100)%10;
    thousands = (input/1000)%10;
    tenThousands = (input/10000)%10;
    hundredThousands = (input/100000)%10;
    millions = (input/1000000)%10;

    reverse = (ones*1000000)+(tens*100000)+(hundreds*10000)+(thousands*1000)+(tenThousands*100)+(hundredThousands*10)+millions;

    printf("\nThe number you entered in reverse is: %d\n",reverse);

    return 0;
}
