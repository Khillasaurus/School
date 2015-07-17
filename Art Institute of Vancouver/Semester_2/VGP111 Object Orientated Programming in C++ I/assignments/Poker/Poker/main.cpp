/* Fig. 7.24: fig07_24.c
Card shuffling dealing program */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



/* prototypes */
void shuffle(int wDeck[][13], int &player);
//int deal(const int wDeck[][13], const char *wFace[], const char *wSuit[]);

class hand
{
public:	
	int currentTotal;
	int deal(deck, face, suit);
};

int main(void)
{
    int pointsP1 = 0;
    int pointsP2 = 0;
    int player = 1;

	hand player1;
	hand player2;
	pointsP1 = player1.deal();
	pointsP2 = player2.deal();

    /* initialize suit array */
    const char *suit[4]={"Hearts", "Diamonds", "Clubs", "Spades"};

    /* initialize face array */
    const char *face[13]={"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    /* initialize deck array */
    int deck[4][13]={0};

    srand(time(0)); /* seed random-number generator */

    shuffle(deck, player);
    //pointsP1 = deal(deck, face, suit);
    player = 2;
    //pointsP2 = deal(deck, face, suit);

    return 0; /* indicates successful termination */

} /* end main */

/* shuffle cards in deck */
void shuffle(int wDeck[][13], int &player)
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
            if(player==1)
            {
                row=rand()%4;
                column=rand()%13;
            }
            else
            {
                row=((rand()%4)*(rand()%873));//different random number
                column=((rand()%13)*(rand()%719));//different random number
            }
        }while(wDeck[row][column]!=0); /* end do...while */

        /* place card number in chosen slot of deck */
        wDeck[row][column]=card;
    } /* end for */

} /* end function shuffle */

/* deal cards in deck */
/* deal cards in deck */
int hand::deal(const int wDeck[][13], const char *wFace[], const char *wSuit[])
{
    int card;   /* card counter */
    int row;    /* row counter */
    int column; /* column counter */
    int amountOfEachSuit[4]={0};
    int amountOfEachFaceValue[13]={0};
    bool onePair = false;
    bool twoPairs = false;
    int j = 0;
    int points = 0;

    /* deal a hand of 5 cards */
    for ( card = 1; card <= 5; card++ )
    {
        /* loop through rows of wDeck */
        for ( row = 0; row <= 3; row++ )
        {
            /* loop through columns of wDeck for current row */
            for ( column = 0; column <= 12; column++) {

            /* if slot contains current card, display card */
            if ( wDeck[row][column] == card)
            {
                printf("%5s of %-8s\n", wFace[column], wSuit[row]);

                if(row==0)
                {
                amountOfEachSuit[0]++;
                }
                else if(row==1)
                {
                amountOfEachSuit[1]++;
                }
                else if(row==2)
                {
                amountOfEachSuit[2]++;
                }
                else if(row==3)
                {
                amountOfEachSuit[3]++;
                }

                if(column==0)
                {
                amountOfEachFaceValue[0]++;
                }
                else if(column==1)
                {
                amountOfEachFaceValue[1]++;
                }
                else if(column==2)
                {
                amountOfEachFaceValue[2]++;
                }
                else if(column==3)
                {
                amountOfEachFaceValue[3]++;
                }
                else if(column==4)
                {
                amountOfEachFaceValue[4]++;
                }
                else if(column==5)
                {
                amountOfEachFaceValue[5]++;
                }
                else if(column==6)
                {
                amountOfEachFaceValue[6]++;
                }
                else if(column==7)
                {
                amountOfEachFaceValue[7]++;
                }
                else if(column==8)
                {
                amountOfEachFaceValue[8]++;
                }
                else if(column==9)
                {
                amountOfEachFaceValue[9]++;
                }
                else if(column==10)
                {
                amountOfEachFaceValue[10]++;
                }
                else if(column==11)
                {
                amountOfEachFaceValue[11]++;
                }
                else if(column==12)
                {
                amountOfEachFaceValue[12]++;
                }
            } /* end if */

         } /* end for */

      } /* end for */

   } /* end for */

   //the following printf statements are for debugging purposes
    printf("\nAmount of Hearts: \t%d\n", amountOfEachSuit[0]);
    printf("Amount of Diamonds: \t%d\n", amountOfEachSuit[1]);
    printf("Amount of Clubs: \t%d\n", amountOfEachSuit[2]);
    printf("Amount of Spades: \t%d\n\n", amountOfEachSuit[3]);

    printf("Amount of Aces: \t%d\n", amountOfEachFaceValue[0]);
    printf("Amount of Twos: \t%d\n", amountOfEachFaceValue[1]);
    printf("Amount of Threes: \t%d\n", amountOfEachFaceValue[2]);
    printf("Amount of Fours: \t%d\n", amountOfEachFaceValue[3]);
    printf("Amount of Fives: \t%d\n", amountOfEachFaceValue[4]);
    printf("Amount of Sixes: \t%d\n", amountOfEachFaceValue[5]);
    printf("Amount of Sevens: \t%d\n", amountOfEachFaceValue[6]);
    printf("Amount of Eights: \t%d\n", amountOfEachFaceValue[7]);
    printf("Amount of Nines: \t%d\n", amountOfEachFaceValue[8]);
    printf("Amount of Tens: \t%d\n", amountOfEachFaceValue[9]);
    printf("Amount of Jacks: \t%d\n", amountOfEachFaceValue[10]);
    printf("Amount of Queens: \t%d\n", amountOfEachFaceValue[11]);
    printf("Amount of Kings \t%d\n\n", amountOfEachFaceValue[12]);
    //end of debugging purposed printf statements

        //print special hand results
    //two pairs
    for(int i = 0; i < 13; i++)
    {
        if(amountOfEachFaceValue[i]==2)
        {
            onePair = true;
            j=i+1;
            while(j < 13)
            {
                if(amountOfEachFaceValue[j]==2)
                {
                    twoPairs = true;
                }
                j++;
            }
        }
    }
    if(onePair ==true && twoPairs == true)
    {
        printf("This hand contains two pairs.\n");
        points = 2;
    }
    else if(onePair==true && twoPairs==false)
    {
        printf("This hand contains a pair.\n");
        points = 1;
    }

    //three of a kind
    for(int i = 0; i < 13; i++)
    {
        if(amountOfEachFaceValue[i]==3)
        {
            printf("This hand contains a three of a kind of %d's.\n",(i+1));
            points = 3;
        }
    }

    //four of a kind
    if(onePair==true)
    {
        for(int i = 0; i < 13; i++)
        {
            if(amountOfEachFaceValue[i]==4)
            {
                printf("This hand contains a four of a kind of %d's.\n\n",(i+1));
                points = 4;
            }
        }
    }

    //flush
    for(int i = 0; i < 4; i++)
    {
        if(amountOfEachSuit[i]==5)
        {
            printf("This hand contains a flush.\n\n");
            points = 5;
        }
    }

    //straight
    if(onePair==false)
    {
        for(int i = 0; i < 5; i++)
        {
            if(amountOfEachFaceValue[i]==1 && amountOfEachFaceValue[i+1]==1 && amountOfEachFaceValue[i+2]==1 && amountOfEachFaceValue[i+3]==1 && amountOfEachFaceValue[i+4]==1)
            {
                printf("This hand contains a straight.\n\n");
                points = 6;
            }
        }
    }

    return points;

} /* end function deal */

