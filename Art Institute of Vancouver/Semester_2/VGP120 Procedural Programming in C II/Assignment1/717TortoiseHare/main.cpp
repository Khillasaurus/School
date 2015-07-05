//STILL NEED TO IMPLEMENT OUCH!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//function prototypes
void tortoise(char [], char *, int, bool);
void hare(char [], char *, int, bool);
void fillTrack(char []);
void drawTrack(char [], char *, char *);

int main()
{
    char track[83];
    char *tortoisePtr = &track[0];
    char *harePtr = &track[0];
    int tortoiseMoveType = -1; //0 = Fast plod, 1 = Slip, 2 = Slow plod
    int hareMoveType = -1; //0 = Sleep, 1 = Bighop, 2 = Big slip, 3 = Smallhop, 4 = Small slip
    bool tortoiseFinish = false;
    bool hareFinish = false;

    /*
    Animal      Move Type       Percentage of the Time      Actual Move
    ---------------------------------------------------------------------
    Tortoise    Fast plod               50%             3 squares to the right
                Slip                    20%             6 squares to the left
                Slow plod               30%             1 square to the right

    Hare        Sleep                   20%             No move at all
                Bighop                  20%             9 squares to the right
                Big slip                10%             12 squares to theleft
                Smallhop                30%             1 square to the right
                Small slip              20%             2 squares to theleft
    */

    //initialize random seed
    srand (time(NULL));

    fillTrack(track);
    drawTrack(track, tortoisePtr, harePtr);

    while (tortoiseFinish == false || hareFinish == false)
    {
        tortoise(track, tortoisePtr, tortoiseMoveType, tortoiseFinish);
        hare(track, harePtr, hareMoveType, hareFinish);
        drawTrack(track, tortoisePtr, harePtr);
    }

    //Tortoise won
    if (tortoiseFinish == true && hareFinish == false)
    {
        printf("\nTORTOISE WINS!!! YAY!!!\n");
    }

    //Hare won
    else if(hareFinish == true && tortoiseFinish == false)
    {
        printf("\nHare wins. Yuch.\n");
    }
    else
    {
        printf("\nIt's a tie.\n");
    }

    return 0;
}


void fillTrack(char track[])
{
    for (int i = 0; i < 70; ++i)
    {
        track[i] = ' ';
    }
    for (int j = 70; j < 84; ++j)
    {
        track[j] = 'F';
    }
}


void tortoise(char track[], char *tortoisePtr, int tortoiseMoveType, bool tortoiseFinish)
{
    tortoiseMoveType = rand() % 3;

    *tortoisePtr = ' ';

    if (tortoiseMoveType == 0)
    {
        tortoisePtr += 3;
        *tortoisePtr = 'T';
    }
    else if (tortoiseMoveType == 1)
    {
        if((tortoisePtr-6)>=&track[0])
        {
            tortoisePtr -= 6;
            *tortoisePtr = 'T';
        }
    }
    else if (tortoiseMoveType == 2)
    {
        tortoisePtr ++;
        *tortoisePtr = 'T';
    }

    /*
    if (*tortoisePtr == 'F')
    {
        tortoiseFinish = true;
    }
    */

    *tortoisePtr = 'T';

    for (int i = 70; i < 76; ++i)
    {
        if (track[i] == 'T')
        {
            tortoiseFinish = true;
            break;
        }
    }
}


void hare(char track[], char *harePtr, int hareMoveType, bool hareFinish)
{
    hareMoveType = rand() % 5;

    *harePtr = ' ';

    if (hareMoveType == 0)
    {
        *harePtr = 'H';
    }
    else if (hareMoveType == 1)
    {
        harePtr += 9;
        *harePtr = 'H';
    }
    else if (hareMoveType == 2)
    {
        if((harePtr-12)>=&track[0])
        {
            harePtr -= 12;
            *harePtr = 'H';
        }
    }
    else if (hareMoveType == 3)
    {
        harePtr++;
        *harePtr = 'H';
    }
    else if (hareMoveType == 4)
    {
        if((harePtr-2)>=&track[0])
        {
            harePtr -= 2;
            *harePtr = 'H';
        }
    }

    /*
    if (*harePtr == 'F')
    {
        hareFinish = true;
    }
    */

    for (int i = 70; i < 81; ++i)
    {
        if (track[i] == 'H')
        {
            hareFinish = true;
            break;
        }
    }
}


void drawTrack(char track[], char *tortoisePtr, char *harePtr)
{
    for (int i = 0; i < 71; ++i)
    {
        printf("%c",track[i]);
    }
}
