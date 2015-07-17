#include <stdio.h>

void floorFill(int floor[50][50])
{

    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            floor[i][j]=0;
        }
    }

}




void floorDraw(int floor[50][50])
{

    int rowCounter = 0;

    for(int i = 0; i < 50; i++)
    {
        for(int j = 0; j < 50; j++)
        {
            if(rowCounter==50)
            {
                printf("\n");
                rowCounter = 0;
            }
            rowCounter++;
            printf("%d",floor[i][j]);
        }
    }

}




bool turtleControl(int &command, int &turtleXPos, int &turtleYPos, int &turtleDirection, bool &penUp, bool &draw)
{

    int spaces;
    bool cont = true;

    while(cont)
    {
        printf("Please enter a choice from the following list:\n");
        printf("1: Raise pen.\n");
        printf("2: Lower pen.\n");
        printf("3: Turn right.\n");
        printf("4: Turn left.\n");
        printf("5: Move forward.\n");
        printf("6: Draw the floor (grid).\n");
        printf("7: Get the turtle's stats.\n");
        printf("9: End the program.\n");

        scanf("%d",&command);
        while(command<1 || command>9)
        {
            printf("You have entered an incorrect option. Please choose a new option from the list.\n");
        }

        if(command==1)
        {
            penUp = true;
        }
        else if(command==2)
        {
            penUp = false;
        }
        else if(command==3)
        {
            if(turtleDirection==4)
            {
                turtleDirection = 1;
            }
            else
            {
                turtleDirection++;
            }
        }
        else if(command==4)
        {
            if(turtleDirection==1)
            {
                turtleDirection = 4;
            }
            else
            {
                turtleDirection--;
            }
        }
        else if(command==5)
        {
            printf("How many spaces would you like to move forward?\n");
            scanf("%d",&spaces);
        }
        else if(command==6)
        {
            //draw = true;
			floorDraw(floor);
        }
        else if(command==7)
        {
            //get info about turtle
        }
        else if(command==9)
        {
            cont = false;
        }
    }

    return draw;

}



int main()
{

    int floor[50][50];
    int turtleXPos = 0;
    int turtleYPos = 2;
    int turtleDirection = 2;    /*  North:  1
                                    East:   2
                                    South:  3
                                    West:   4  */
    bool penUp = true;
    int command = 0;
    bool draw = false;

    printf("The turtle starts in the top left corner of a 50x50 grid facing east.\n");

    floorFill(floor);

    while(command!=9)
    {
        turtleControl(command, turtleXPos,turtleYPos, turtleDirection, penUp, draw);
        /*if(draw==true)
        {
            floorDraw(floor);
        }*/
    }

    return 0;

}
