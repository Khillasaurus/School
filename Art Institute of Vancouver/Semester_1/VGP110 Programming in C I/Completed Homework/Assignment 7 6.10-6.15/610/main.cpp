//Daniel Schenker
//Exercise 6.10
#include <stdio.h>

int wageCalculator(int x)
{

    int wage;

    wage = 200 + (x*0.09);

    return wage;

}




int main()
{

    //initialize variables
    int gross = 0;
    int input = 1;

    int table[9];

    //initialize elements of array table to 0
    for(int i = 0; i < 9; i++)
    {
        table[i] = 0;
    }

    while(input != 0)
    {
        printf("Please enter the gross sales of the week for the employee.\n");
        scanf("%d",&gross);

        if((wageCalculator(gross)>=200) && (wageCalculator(gross)<300))
        {
            table[0]++;
        }
        else if((wageCalculator(gross)>=300) && (wageCalculator(gross)<400))
        {
            table[1]++;
        }
        else if((wageCalculator(gross)>=400) && (wageCalculator(gross)<500))
        {
            table[2]++;
        }
        else if((wageCalculator(gross)>=500) && (wageCalculator(gross)<600))
        {
            table[3]++;
        }
        else if((wageCalculator(gross)>=600) && (wageCalculator(gross)<700))
        {
            table[4]++;
        }
        else if((wageCalculator(gross)>=700) && (wageCalculator(gross)<800))
        {
            table[5]++;
        }
        else if((wageCalculator(gross)>=800) && (wageCalculator(gross)<900))
        {
            table[6]++;
        }
        else if((wageCalculator(gross)>=900) && (wageCalculator(gross)<1000))
        {
            table[7]++;
        }
        else if(wageCalculator(gross)>=1000)
        {
            table[8]++;
        }

        printf("\tIf you would like to stop entering data and view results enter 0.\n");
        printf("\tIf you would like to continue enter 1.\n\t");
        scanf("%d",&input);
    }


    printf("The amount of people that earned inbetween (and including) $200-$299 this week are: %d",table[0]);
    printf("\n\nThe amount of people that earned inbetween (and including) $300-$399 this week are: %d",table[1]);
    printf("\n\nThe amount of people that earned inbetween (and including) $400-$499 this week are: %d",table[2]);
    printf("\n\nThe amount of people that earned inbetween (and including) $500-$599 this week are: %d",table[3]);
    printf("\n\nThe amount of people that earned inbetween (and including) $600-$699 this week are: %d",table[4]);
    printf("\n\nThe amount of people that earned inbetween (and including) $700-$799 this week are: %d",table[5]);
    printf("\n\nThe amount of people that earned inbetween (and including) $800-$899 this week are: %d",table[6]);
    printf("\n\nThe amount of people that earned inbetween (and including) $900-$999 this week are: %d",table[7]);
    printf("\n\nThe amount of people that earned over (and including) $1000 this week are: %d",table[8]);
    printf("\n");


    return 0;

}
