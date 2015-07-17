#include <stdio.h>

int main()
{

    int pChoice; //Allows user to choose binary, octal or hexadecimal
    int numerator = 0;
    int remainder;
    int placeValue = 0;
    int ones = 0;
    int tens = 0;
    int hundreds = 0;
    int thousands = 0;
    int tenthousands = 0;
    int hundredthousands = 0;
    int millions = 0;
    int answer;

    printf("Enter 1 for Binary, 2 for Octal or 3 for Hexadecimal. I will then output the first 256 values of the type you chose.\n");
    scanf("%d" , &pChoice);

    if (pChoice ==  1)
    {
        for(int counter = 1; counter <= 256; counter++)
        {
            numerator = counter;
            while(numerator != 0)
            {
                placeValue++;
                remainder = numerator%2;
                if (placeValue == 1)
                {
                    ones = remainder;
                }
                else if (placeValue == 2)
                {
                    tens = remainder;
                }
                else if (placeValue == 3)
                {
                    hundreds = remainder;
                }
                else if (placeValue == 4)
                {
                    thousands = remainder;
                }
                else if (placeValue == 5)
                {
                    tenthousands = remainder;
                }
                else if (placeValue == 6)
                {
                    hundredthousands = remainder;
                }
                else if (placeValue == 7)
                {
                    millions = remainder;
                }
                numerator = numerator/2;
            }
        answer = ones + (tens*10) + (hundreds*100) + (thousands*1000) + (tenthousands*10000) + (hundredthousands*100000) + (millions*1000000);
        printf("Term number: %d\tNumerator: %d\tBinary Value: %d\n",counter,numerator,answer);
        }
    }



    return 0;
}
