#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void display(int seats[])
{

    for(int i = 0; i < 10; i++)
    {
        if(i==0)
        {
            printf("First Class:\t%d",seats[i]);
        }
        else if(i==5)
        {
            printf("\nEconomy:\t%d",seats[i]);
        }
        else if(i==9)
        {
            printf("%d\n\n",seats[i]);
        }
        else
        {
            printf("%d",seats[i]);
        }
    }

}




void seating(int seats[], int seatingClass)
{

    bool seatedProperly = false;
    int seatNumber;

    while(seatedProperly==false)
    {
        //generate secret number from 0 to 4
        seatNumber = rand() % 5;
        if(seatingClass==2)
        {
            seatNumber += 5;
        }

        if(seats[seatNumber]==0)
        {
            seats[seatNumber]=1;
            seatedProperly=true;
        }
        else
        {
            seatNumber = rand() % 5;
        }
    }


}



int main()
{

    //initialize random seed:
    srand (time(NULL));


    int seatingClass = -1;
    int seats[]={0,0,0,0,0,0,0,0,0,0};
    int firstClassFilled = 0;
    int economyClassFilled = 0;
    int switchClass;

    while(seatingClass!=0)
    {
        printf("Please enter a 1 for \"first class\".\n");
        printf("Please enter a 2 for \"economy\".\n");
        printf("Please enter a 0 to quit.\n");
        scanf("%d",&seatingClass);


        if(seatingClass==0)
        {
            break;
        }

        if(seatingClass==1)
        {
            firstClassFilled++;
            if(firstClassFilled>5)
            {
                printf("First class is full. Would you like to sit in the economy class?\n");
                printf("Enter a 1 for yes or a 0 for no.\n");
                scanf("%d",&switchClass);
                if(switchClass==0)
                {
                    printf("Next Flight leaves in 3 hours.\n");
                    break;
                }
                else
                {
                    seatingClass = 2;
                }
            }
        }

        if(seatingClass==2)
        {
            economyClassFilled++;
            if(economyClassFilled>5 && firstClassFilled<5)
            {
                printf("Economy class is full. Would you like to sit in the first class?\n");
                printf("Enter a 1 for yes or a 0 for no.\n");
                scanf("%d",&switchClass);
                if(switchClass==0)
                {
                    printf("Next Flight leaves in 3 hours.\n");
                    break;
                }
                else
                {
                    seatingClass = 1;
                    firstClassFilled++;
                }
            }
            if(firstClassFilled>5 && economyClassFilled>5)
            {
                printf("Next Flight leaves in 3 hours.\n");
                break;
            }
        }

        seating(seats, seatingClass);
        display(seats);
    }

    return 0;

}
