#include <time.h>
#include <iostream>

struct Card
{
	char* face;
	char* suit;
	//unsigned int face : 4;
	//unsigned int suit : 2;
	//unsigned int colour : 1;

};

struct Deck
{
	Card cards[52];
};

void FillDeck(Deck* pDeck);
void Shuffle(Deck* pDeck);
void Deal(const Deck* pDeck);

int main()
{
	Deck myDeck;
	srand((unsigned)time(NULL));

	FillDeck(&myDeck);
	Shuffle(&myDeck);
	Deal(&myDeck);

	return 0;
}

void FillDeck(Deck* pDeck)
{
	char* face[] = {"Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King"};
	char* suit[] = {"Hearts","Diamonds","Clubs","Spades"};

	for (int i=0; i<52; ++i)
	{
		pDeck->cards[i].face = face[i%13];
		pDeck->cards[i].suit = suit[i/13];
	}
}

void Shuffle(Deck* pDeck)
{
	for (int i=0; i<52; ++i)
	{
		int j = rand()%52;
		Card temp = pDeck->cards[i];
		pDeck->cards[i] = pDeck->cards[j];
		pDeck->cards[j] = temp;
	}
}

void Deal(const Deck* pDeck)
{
	for (int i=0; i<52; ++i)
	{
		std::cout << pDeck->cards[i].face << " of " << pDeck->cards[i].suit << "\t\t";
		std::cout << pDeck->cards[i+1].face << " of " << pDeck->cards[i+1].suit << "\n";
	}
}