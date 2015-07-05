#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void fillBoard(int *);//fills board with 0's
void printBoard(int *);//prints out board to console
void movement(int &, int &, int, int &, int &, unsigned long long int &, int [], int [], int [][8]);//randomly moves the knight to an untravelled location on the board with it's maximum of 8 movement options

int main()
{

    int runThroughs[64];
    int board[8][8];
    int *boardPtr = &board[0][0];
    int horizontal[8];
    int vertical[8];
    int currentRow;//horizontal location of knight
    int currentColumn;//vertical location of knight
    int moveNumber = -1;//which movement pattern the knight will be taken with possible values 0-7 inclusive
    int moveSuccesful = 1;// 0 = succesful, 1 = not succesful, -1 = no possible moves
    int moveCounter = 1;//how many moves it takes until the knight gets stuck or succesfully touches every tile on the board
    unsigned long long int totalRunThroughs = 1;

    //initialize random seed
    srand (time(NULL));

    //defining values for movement calculation tables
    horizontal[0] = 2;
    horizontal[1] = 1;
    horizontal[2] = -1;
    horizontal[3] = -2;
    horizontal[4] = -2;
    horizontal[5] = -1;
    horizontal[6] = 1;
    horizontal[7] = 2;
    vertical[0] = -1;
    vertical[1] = -2;
    vertical[2] = -2;
    vertical[3] = -1;
    vertical[4] = 1;
    vertical[5] = 2;
    vertical[6] = 2;
    vertical[7] = 1;

    for (int m = 0; m < 64; ++m)//setting all values  in the runThroughs array to 0
    {
        runThroughs[m] = 0;
    }

    while(moveCounter != 64)//run until a perfect knight path is taken
    {
        moveNumber = -1;//which movement pattern the knight will be taken with possible values 0-7 inclusive
        moveSuccesful = 1;// 0 = succesful, 1 = not succesful, -1 = no possible moves
        moveCounter = 1;//how many moves it takes until the knight gets stuck or succesfully touches every tile on the board

        fillBoard(boardPtr);//fills board with 0's

        //randomize knight's starting position
        currentColumn = rand() % 8;
        currentRow = rand() % 8;
        //set knight's starting location on board to "travelled to" or "1"
        board[currentRow][currentColumn] = 1;

        while (moveSuccesful != -1 && moveCounter < 64)
        {
            movement(moveCounter, moveSuccesful, moveNumber, currentColumn, currentRow, totalRunThroughs, horizontal, vertical, board);

            if (moveSuccesful == -1 && moveCounter < 64)
            {
                printf("The knight managed to reach %d tiles on the board before it got stuck.\n", moveCounter);
                break;
            }
            else if(moveCounter == 64)
            {
                printf("The knight succesfully reach all 64 tiles on the board!\n");
                break;
            }
            moveSuccesful = 1;
        }

        printBoard(boardPtr);//prints out board to console
        ++runThroughs[moveCounter];
    }

    printf("\nThe knight reaches the following amount of tiles this many times:\n");
    for (int p = 0; p < 64; ++p)
    {
        printf("%d Tiles:\t%d\n", p+1, runThroughs[p]);
    }
    printf("\nIt took the knight %I64d Run Throughs to finally cover all 64 tiles.\n", totalRunThroughs);

   return 0;

}


void fillBoard(int *boardPtr)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            *boardPtr = 0;
            ++boardPtr;
        }
    }
}


void movement(int &moveCounter, int &moveSuccesful, int moveNumber, int &currentColumn, int &currentRow, unsigned long long int &totalRunThroughs,int horizontal[], int vertical[], int board[][8])
{
    //array used to determine if any moves are available at all or not
    int moveAvailable[8];

    //if no values in this array equal 0 then there are no avaiable moves
    for (int k = 0; k < 8; ++k)
    {
        moveAvailable[k] = 0;
    }

    while (moveSuccesful == 1)
    {
        moveNumber = rand() % 8;
        //checks to see if it has been determined that there are no avaiable moves at all
        if (moveAvailable[0] == 1 && moveAvailable[1] == 1 && moveAvailable[2] == 1 && moveAvailable[3] == 1 && moveAvailable[4] == 1 && moveAvailable[5] == 1 && moveAvailable[6] == 1 && moveAvailable[7] == 1)
        {
            moveSuccesful = -1;
            break;
        }
        //while moveNumber makes knight leave board get a new moveNumber
        while ( (currentRow + vertical[moveNumber] > 7) || (currentColumn + horizontal[moveNumber] > 7) || (currentRow + vertical[moveNumber] < 0) || (currentColumn + horizontal[moveNumber] < 0) )
        {
            moveAvailable[moveNumber] = 1;
            moveNumber = rand() % 8;
        }
        //makes sure that the knight has not been to this location before
        if (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]] == 1)
        {
            moveAvailable[moveNumber] = 1;
        }
        else//Knight moved to a new available tile
        {
            moveSuccesful = 0;
            ++moveCounter;
            ++totalRunThroughs;
        }
    }

    if (moveSuccesful == 0)
    {
        currentRow += vertical[moveNumber];
        currentColumn += horizontal[moveNumber];
        board[currentRow][currentColumn] = 1;
    }
}


void printBoard(int *boardPtr)
{
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            printf("%d", *boardPtr);
            ++boardPtr;
        }
        printf("\n");
    }
}
