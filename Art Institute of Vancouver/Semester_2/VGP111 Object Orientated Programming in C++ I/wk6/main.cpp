#include <stdio.h>
#include <stdlib.h>
#include <time.h>


class cCard
{
public:
	int suit;
	int face;
};

class cGroupOfCards
{
public:
	vector<int> handCards;
	handCards.reserve( 5 );
	handCards.push_back( 5 );
};

class cDeck
{
public:
	vector<int> deckCards;
	deckCards.reserve( 52 );
	deckCards.push_back( 52 );
}

int _tmain(int argc, _TCHAR* argv[])
{
	cDeck deck;

	for( int i = 0; i < 52; ++i )
	{
		deck.deckCards[i] = 0;
	}

	cGroupOfCards handP1;
	cGroupOfCards handP2;

	return 0;
}