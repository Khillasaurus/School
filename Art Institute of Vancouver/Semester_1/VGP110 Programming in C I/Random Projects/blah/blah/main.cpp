/* Fig. 7.24: fig07_24.c
Card shuffling dealing program */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* prototypes */
void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]);

int main(void)
{
    /* initialize suit array */
    const char *suit[4]={"Hearts", "Diamonds", "Clubs", "Spades"};

    /* initialize face array */
    const char *face[13]={"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    /* initialize deck array */
    int deck[4][13]={0};

    srand(time(0)); /* seed random-number generator */

    shuffle(deck);
    deal(deck, face, suit);

    return 0; /* indicates successful termination */

} /* end main */

/* shuffle cards in deck */
void shuffle(int wDeck[][13])
{
    int row;    /* row number */
    int column; /* column number */
    int card;   /* counter */

    /* for each of the 52 cards, choose slot of deck randomly */
    for(card=1; card<=52; card++)
    {
        /* choose new random location until unoccupied slot found */
        do
        {
            row=rand()%4;
            column=rand()%13;
        }while(wDeck[row][column]!=0); /* end do...while */

        /* place card number in chosen slot of deck */
        wDeck[row][column]=card;
    } /* end for */

} /* end function shuffle */

/* deal cards in deck */
void deal(const int wDeck[][13], const char *wFace[], const char *wSuit[])
{
    int card;   /* card counter */
	int row;    /* row counter */
	int column; /* column counter */
	int handNumber=0;
	int suitArray[5]={0};
    int faceValueArray[5]={0};
    int similiarFaceValue=1;
    bool goodHand=false;
    bool pair=false;
    bool triple=false;
    bool quad=false;
    bool isFlush = true;

	/* deal a 5 card hand */
	for (card=1; card<=5; card++)
	{
        /* loop through rows of wDeck */
		for(row=0; row<=3; row++)
		{
            /* loop through columns of wDeck for current row */
			for(column=0; column<=12; column++)
			{
                /* if slot contains current card, display card */
				if(wDeck[row][column]==card)
				{
                    printf("%5s of %-8s\n", wFace[column], wSuit[row]);

                    suitArray[card-1]=row;
                    faceValueArray[card-1]=column;

                } /* end if */

            } /* end for */

        } /* end for */

    } /* end for */

    /* I'd like to make a function for the following part but for now I will leave it within this function for simplicity's sake */
    //determining if the hand contains a pair, three of a kind or four of a kind
    int i = 0; //counter
    int j = 1; //counter
    bool pairBeenMade = false;
    int firstPair = 0;
    int secondPair = 0;//not nessecary, just for debugging purposes
    while(i < 4)
    {
        while(j < 4)
        {
            if(faceValueArray[i]==faceValueArray[j])
            {
                similiarFaceValue++;
                if(pairBeenMade = false && similiarFaceValue==2)
                {
                    firstPair = faceValueArray[i];
                    pairBeenMade = true;
                }
                else if(similiarFaceValue==2 && pairBeenMade==true)
                {
                    if(faceValueArray[i]!=firstPair)
                    {
                        secondPair = faceValueArray[i];//not nessecary, just for debugging purposes
                        similiarFaceValue=1;
                        pair = true;
                    }
                }
                else if(similiarFaceValue==3 && pairBeenMade==true)
                {
                    if(faceValueArray[i]!=firstPair)
                    {
                        secondPair = faceValueArray[i];//not nessecary, just for debugging purposes
                        similiarFaceValue=1;
                        triple = true;
                    }
                }
            }
            j++;
        }
        i++;
        j = i+1;
    }

    printf("\n");
    //print special hand results
    if(similiarFaceValue==2 && pair==true)
    {
        printf("This hand contains two pairs.\n\n");
    }
    else if(similiarFaceValue==3 && pair==true)
    {
        printf("This hand contains a pair and a three of a kind.\n\n");
    }
    else if(similiarFaceValue==2 && triple==true)
    {
        printf("This hand contains a three of a kind and a pair.\n\n");
    }
    else if(similiarFaceValue==2)
    {
        printf("This hand contains a pair.\n\n");
    }
    else if(similiarFaceValue==3)
    {
        triple = true;
        printf("This hand contains a three of a kind.\n\n");
    }
    else if(similiarFaceValue==4)
    {
        quad = true;
        printf("This hand contains a four of a kind.\n\n");
    }
    else if(pair==false && triple==false && quad==false)
    {
        for(int m=1; m<4; m++)
        {
            if(suitArray[m]!=suitArray[0])
            {
                isFlush=false;
            }
        }
        if(isFlush==true)
        {
            printf("This hand conatains a flush.\n\n");
        }
    }

    //the following printf statements are for debugging purposes
    printf("%d\t", faceValueArray[0]+1);
    printf("%d\n", suitArray[0]+1);

    printf("%d\t", faceValueArray[1]+1);
    printf("%d\n", suitArray[1]+1);

    printf("%d\t", faceValueArray[2]+1);
    printf("%d\n", suitArray[2]+1);

    printf("%d\t", faceValueArray[3]+1);
    printf("%d\n", suitArray[3]+1);

    printf("%d\t", faceValueArray[4]+1);
    printf("%d\n", suitArray[4]+1);
    //end of debugging purposed printf statements

    printf("\nsimiliarFaceValue: %d\n", similiarFaceValue);
    printf("\nfirstPair: %d\n", firstPair);
    printf("\nsecondPair: %d\n", secondPair);


} /* end function deal */
