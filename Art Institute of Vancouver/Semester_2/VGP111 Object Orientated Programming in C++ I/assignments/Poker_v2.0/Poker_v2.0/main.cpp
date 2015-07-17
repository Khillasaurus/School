#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "hand.h"

void shuffle( int wDeck[][13] );
int deal( const int wDeck[][13], const char *wFace[], const char *wSuit[] );
void compare( int, int );

class card
{
public:

};

class hand
{
public:
	int points;
};

int main( void )
{
    // initialize suit array
    const char* suit[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};

    // initialize face array
    const char* face[13] = {"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};

    // initialize deck array
    int deck[4][13] = {0};

    srand(time(0)); // seed random-number generator

	hand player1;
	hand player2;

	shuffle(deck);
    player1.points = deal( deck, face, suit );
	for ( int i = 0; i < 4; ++i )
	{
		for ( int j = 0; j < 13; ++j )
		{
			deck[i][j] = 0;
		}
	}
	shuffle( deck );
    player2.points = deal( deck, face, suit );

	printf( "Player1 points: %d\n", player1.points );
	printf( "Player2 points: %d\n", player2.points );

	compare( player1.points, player2.points );

    return 0;

} // end main

// shuffle cards in deck
void shuffle( int wDeck[][13] )
{
    int row;    // row number
    int column; // column number
    int card;   // counter

    // for each of the 52 cards, choose slot of deck randomly
    for( card = 1; card <= 52; ++card )
    {
        // choose new random location until unoccupied slot found
        do
		{
			row = rand()%4;
			column = rand()%13;
		}while( wDeck[row][column] != 0 ); // end do...while

        // place card number in chosen slot of deck
        wDeck[row][column] = card;
    } // end for

} // end function shuffle

// deal cards in deck
int deal( const int wDeck[][13], const char* wFace[], const char* wSuit[] )
{
    int card;   // card counter
    int row;    // row counter
    int column; // column counter
    int amountOfEachSuit[4] = {0};
    int amountOfEachFaceValue[13] = {0};
    bool onePair = false;
    bool twoPairs = false;
    int j = 0;
    int points = 0;

    // deal a hand of 5 cards
    for ( card = 1; card <= 5; ++card )
    {
        // loop through rows of wDeck
        for ( row = 0; row <= 3; ++row )
        {
            // loop through columns of wDeck for current row
            for ( column = 0; column <= 12; column++ )
			{
	            // if slot contains current card, display card
				if ( wDeck[row][column] == card)
				{
					printf( "%5s of %-8s\n", wFace[column], wSuit[row] );
	                if( row == 0 )
		            {
						amountOfEachSuit[0]++;
					}
					else if( row == 1 )
					{
						amountOfEachSuit[1]++;
					}
					else if(row == 2)
					{
						amountOfEachSuit[2]++;
					}
					else if(row == 3)
					{
						amountOfEachSuit[3]++;
					}

					if(column == 0)
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
				} // end if
			} // end for
		} // end for
	} // end for

   // the following printf statements are for debugging purposes
    printf( "\nAmount of Hearts: \t%d\n", amountOfEachSuit[0] );
    printf( "Amount of Diamonds: \t%d\n", amountOfEachSuit[1] );
    printf( "Amount of Clubs: \t%d\n", amountOfEachSuit[2] );
    printf( "Amount of Spades: \t%d\n\n", amountOfEachSuit[3] );

    printf( "Amount of Aces: \t%d\n", amountOfEachFaceValue[0] );
    printf( "Amount of Twos: \t%d\n", amountOfEachFaceValue[1] );
    printf( "Amount of Threes: \t%d\n", amountOfEachFaceValue[2] );
    printf( "Amount of Fours: \t%d\n", amountOfEachFaceValue[3] );
    printf( "Amount of Fives: \t%d\n", amountOfEachFaceValue[4] );
    printf( "Amount of Sixes: \t%d\n", amountOfEachFaceValue[5] );
    printf( "Amount of Sevens: \t%d\n", amountOfEachFaceValue[6] );
    printf( "Amount of Eights: \t%d\n", amountOfEachFaceValue[7] );
    printf( "Amount of Nines: \t%d\n", amountOfEachFaceValue[8] );
    printf( "Amount of Tens: \t%d\n", amountOfEachFaceValue[9] );
    printf( "Amount of Jacks: \t%d\n", amountOfEachFaceValue[10] );
    printf( "Amount of Queens: \t%d\n", amountOfEachFaceValue[11] );
    printf( "Amount of Kings \t%d\n\n", amountOfEachFaceValue[12] );
    // end of debugging purposed printf statements

		//print special hand results
	//two pairs
    for ( int i = 0; i < 13; ++i )
    {
        if ( amountOfEachFaceValue[i] == 2 )
        {
            onePair = true;
            j = i + 1;
            while ( j < 13 )
            {
                if ( amountOfEachFaceValue[j] == 2 )
                {
                    twoPairs = true;
                }
                ++j;
            }
        }
    }
    if ( onePair == true && twoPairs == true )
    {
        printf( "This hand contains two pairs.\n" );
        points = 2;
    }
    else if ( onePair == true && twoPairs == false )
    {
        printf( "This hand contains a pair.\n" );
        points = 1;
    }

    //three of a kind
    for ( int i = 0; i < 13; ++i )
    {
        if ( amountOfEachFaceValue[i] == 3 )
        {
            printf( "This hand contains a three of a kind of %d's.\n",( i + 1 ) );
            points = 3;
        }
    }

    //four of a kind
    if ( onePair == true )
    {
        for ( int i = 0; i < 13; ++i )
        {
            if ( amountOfEachFaceValue[i] == 4 )
            {
                printf( "This hand contains a four of a kind of %d's.\n\n",( i + 1 ) );
                points = 4;
            }
        }
    }

    //flush
    for ( int i = 0; i < 4; ++i )
    {
        if ( amountOfEachSuit[i] == 5 )
        {
            printf( "This hand contains a flush.\n\n" );
            points = 5;
        }
    }

    //straight
    if ( onePair == false )
    {
        for ( int i = 0; i < 5; ++i )
        {
            if(amountOfEachFaceValue[i]==1 && amountOfEachFaceValue[i+1]==1 && amountOfEachFaceValue[i+2]==1 && amountOfEachFaceValue[i+3]==1 && amountOfEachFaceValue[i+4]==1)
            {
                printf( "This hand contains a straight.\n\n" );
                points = 6;
            }
        }
    }

    return points;

} // end function deal

void compare( int p1, int p2 )
{
	if ( p1 > p2 )
	{
		printf( "Player 1 beats Player 2!\n" );
	}
	else if ( p1 < p2 )
	{
		printf( "Player 2 beats Player 1!\n" );
	}
	else if ( p1 == p2 )
	{
		printf( "It's a tie!\n" );
	}

} // end function compare