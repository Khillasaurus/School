#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{

    //initialize random seed:
    srand (time(NULL));

    int dice1;
    int dice2;
    int total;
    int list[]={0,0,0,0,0,0,0,0,0,0,0};

    printf("Welcome to the dice rolling program.\n");
    printf("In this program 2 die will be rolled 36,000 times. The total of each pair of die rolls will be calculated and displayed,\n");

    for(int i = 0; i < 35999; i++)
    {
        //generate random numbers from 1 to 6
        dice1 = rand() % 6 + 1;
        dice2 = rand() % 6 + 1;
        total = dice1 + dice2;

        //tally rolls
        if(total==2)
        {
            list[0]++;
        }
        else if(total==3)
        {
            list[1]++;
        }
        else if(total==4)
        {
            list[2]++;
        }
        else if(total==5)
        {
            list[3]++;
        }
        else if(total==6)
        {
            list[4]++;
        }
        else if(total==7)
        {
            list[5]++;
        }
        else if(total==8)
        {
            list[6]++;
        }
        else if(total==9)
        {
            list[7]++;
        }
        else if(total==10)
        {
            list[8]++;
        }
        else if(total==11)
        {
            list[9]++;
        }
        else if(total==12)
        {
            list[10]++;
        }
    }

    printf("Here are the result of how many times each total was rolled:\n");

    printf("Roll 2: %d\n",list[0]);
    printf("Roll 3: %d\n",list[1]);
    printf("Roll 4: %d\n",list[2]);
    printf("Roll 5: %d\n",list[3]);
    printf("Roll 6: %d\n",list[4]);
    printf("Roll 7: %d\n",list[5]);
    printf("Roll 8: %d\n",list[6]);
    printf("Roll 9: %d\n",list[7]);
    printf("Roll 10: %d\n",list[8]);
    printf("Roll 11: %d\n",list[9]);
    printf("Roll 12: %d\n",list[10]);


    return 0;

}
