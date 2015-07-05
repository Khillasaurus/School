#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

//globals
const int kDeckSize = 52;
const int kHandSize = 10;

struct cCard
{
	int suit;//1 hearts, 2 spades, 3 diamonds, 4 clubs
	int value;//ace = 1, 2-10, jack-king = 11-13
	struct cCard* next;
	struct cCard* previous;
};

typedef struct cCard _c;
typedef struct cCard* cPtr;

struct cHand
{
	int cardCount;
	int bookCount;
	cPtr list;
};

typedef struct cHand _h;
typedef struct cHand* hPtr;

//function prototypes
bool WantsToPlay();
bool Initialize(hPtr&, hPtr&, hPtr&, hPtr&, hPtr&);
cPtr CreateNodes(const int);
void ShuffleCards(cPtr);
cPtr Search(const cPtr, const int);
void TakeFromMiddleAndAddToEnd(cPtr head, const int pos);
cPtr RemoveN(const cPtr, const int);
cPtr AddEnd(const cPtr, const cPtr);
int Length(const cPtr);
void DealCards(cPtr&, cPtr&, const int);
bool GameOver(const hPtr, const hPtr, const hPtr, const hPtr, const hPtr);
void PlayRound();
void CalculateWinner();
bool FreeMemory();

int main()
{
	//initialize random seed
	srand((unsigned)time(NULL));

	bool runGame = true;

	while(runGame)
	{
		if(WantsToPlay())
		{
			hPtr deck = (hPtr)malloc(sizeof(_h));
			hPtr player1Hand = (hPtr)malloc(sizeof(_h));
			hPtr player2Hand = (hPtr)malloc(sizeof(_h));
			hPtr player3Hand = (hPtr)malloc(sizeof(_h));
			hPtr player4Hand = (hPtr)malloc(sizeof(_h));
			if(Initialize(deck, player1Hand, player2Hand, player3Hand, player4Hand))
			{
				while(!GameOver(deck, player1Hand, player2Hand, player3Hand, player4Hand))
				{
					PlayRound();
				}
				CalculateWinner();

				if(!FreeMemory())
				{
					printf("ERROR: Memory could not be freed.\n");
					break;
				}
			}
			else
			{
				printf("ERROR: Could not initialize game.\n");
				break;
			}
		}
		else
		{
			runGame = false;
			printf("See you next time!\n");
		}
	}

	return 0;
}




bool WantsToPlay()
{
	int wantsToPlay = -1;

	while(wantsToPlay < 0 || wantsToPlay > 1)
	{
		printf("Do you want to play a card game of Fish?\n");
		printf("Enter 1 for yes or 0 for no.\n");
		scanf("%d", &wantsToPlay);
		if(wantsToPlay < 0 || wantsToPlay > 1)
		{
			printf("You have entered an incorrect value.\n");
		}
	}
	if(wantsToPlay == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}




bool Initialize(hPtr& deck, hPtr& player1Hand, hPtr& player2Hand, hPtr& player3Hand, hPtr& player4Hand)
{
	deck->list = CreateNodes(kDeckSize);

	player1Hand->list = (cPtr)malloc(sizeof(_c));
	player1Hand->list->suit = -1;//if Length() is called and it returns 1, this can be used to test if it's 1 actual node, or just the initial allocated node with garbage values
	player1Hand->list->next = NULL;
	player2Hand->list = (cPtr)malloc(sizeof(_c));
	player2Hand->list->suit = -1;//same as above
	player2Hand->list->next = NULL;
	player3Hand->list = (cPtr)malloc(sizeof(_c));
	player3Hand->list->suit = -1;//same as above
	player3Hand->list->next = NULL;
	player4Hand->list = (cPtr)malloc(sizeof(_c));
	player4Hand->list->suit = -1;//same as above
	player4Hand->list->next = NULL;

	ShuffleCards(deck->list);

	DealCards(deck->list, player1Hand->list, kHandSize);
	DealCards(deck->list, player2Hand->list, kHandSize);
	DealCards(deck->list, player3Hand->list, kHandSize);
	DealCards(deck->list, player4Hand->list, kHandSize);

	if(Length(deck->list) == kDeckSize - (4 * kHandSize))
	{
		if(Length(player1Hand->list) == kHandSize)
		{
			if(Length(player2Hand->list) == kHandSize)
			{
				if(Length(player3Hand->list) == kHandSize)
				{
					if(Length(player4Hand->list) == kHandSize)
					{
						return true;
					}
				}
			}
		}
	}

	return false;
}




cPtr CreateNodes(const int amountOfNodes)
{
	cPtr head;
	cPtr tail;

	tail = head = (cPtr)malloc(sizeof(_c));
	head->suit = 4;//clubs
	head->value = 13;//king
	head->next = NULL;

	for(int i = 1; i < amountOfNodes; ++i)
	{
		tail->next = (cPtr)malloc(sizeof(_c));
		tail = tail->next;
		tail->next = NULL;
		tail->suit = ((kDeckSize-i-1) / 13) + 1;
		tail->value = ((kDeckSize-i-1) % 13) + 1;
	}
	return head;
}




////for some reason this function doesn't remove cards when shuffling, rather it adds a copy of the randomly selected card to shuffle to the end of the deck list (top of the deck if cards are facing down)
//void ShuffleCards(const cPtr head)
//{
//	cPtr start = head;
//	cPtr temp;
//	cPtr hold = (cPtr)malloc(sizeof(_c));
//	int shuffles = 1000;//1 shuffle equals taking a card randomly from the deck and placing it at the end
//	int randomNumber;
//
//	for(int i = 0; i < shuffles; ++i)
//	{
//		randomNumber = rand() % kDeckSize;
//		temp = Search(start, randomNumber);
//		hold->suit = temp->suit;
//		hold->value = temp->value;
//		start = RemoveN(head, randomNumber);
//		start = AddEnd(head, hold);
//	}
//}
//for some reason this function doesn't remove cards when shuffling, rather it adds a copy of the randomly selected card to shuffle to the end of the deck list (top of the deck if cards are facing down)
void ShuffleCards(const cPtr head)
{
	cPtr start = head;
	cPtr temp;
	cPtr hold = (cPtr)malloc(sizeof(_c));
	int shuffles = 1000;//1 shuffle equals taking a card randomly from the deck and placing it at the end
	int randomNumber;

	for(int i = 0; i < shuffles; ++i)
	{
		randomNumber = rand() % kDeckSize;
		temp = Search(start, randomNumber);
		hold->suit = temp->suit;
		hold->value = temp->value;
		TakeFromMiddleAndAddToEnd(start, const int randomNumber);
		//start = RemoveN(head, randomNumber);
		//start = AddEnd(head, hold);
	}
}




//when this is -2 or smaller, an error should be returned
//if -1 is used, sets pointer to end of list
//if a specific positive number is used, sets pointer to that element of list
cPtr Search(const cPtr head, const int nodePos)
{
	cPtr temp = head;
	int safetyCounter = 1;//boundary checking for list search
	if(nodePos < -1)
	{
		printf("ERROR: Invalid posisition passed in to 2nd parameter of Search function. Terminating program.\n");
		std::terminate();
	}
	else if(nodePos == -1)
	{
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
	}
	else
	{
		for(int i = 0; i < nodePos; ++i)
		{
			if(temp->next != NULL)
			{
				temp = temp->next;
				++safetyCounter;
			}
			else
			{
				printf("ERROR: Attempting to access memory outside boundary of list. Returning last element of list instead which is at position %d\n", safetyCounter);
				temp = head;
				for(int j = 0; j < safetyCounter; ++j)
				{
					temp = temp->next;
				}
			}
		}
	}
    return temp;
}


//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void TakeFromMiddleAndAddToEnd(cPtr head, const int pos)
{
	cPtr temp = head;
	cPtr hold;
	int listLength = Length(temp);

	temp = Search(temp, pos - 1);
	hold = temp->next;
	hold->next = NULL;
	temp = temp->next->next;
	Search(temp, -1);
	temp->next = hold;
}
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

cPtr RemoveN(const cPtr head, const int pos)
{
	cPtr temp = head;
	cPtr head2;
	cPtr tail2;
	int listLength = 0;
	int counter = 1;

	listLength = Length(temp);

	tail2 = head2 = (cPtr)malloc(sizeof(_c));
	tail2->suit = temp->suit;
	tail2->value = temp->value;
	tail2->next = NULL;
	
	while(counter < pos)
	{
		temp = temp->next;
		tail2->next = (cPtr)malloc(sizeof(_c));
		tail2 = tail2->next;
		tail2->next = NULL;
		tail2->suit = temp->suit;
		tail2->value = temp->value;
		++counter;
	}
	temp = temp->next;

	while(counter < listLength-1)//-1 because one node of temp has been skipped on purpose
	{
		temp = temp->next;
		tail2->next = (cPtr)malloc(sizeof(_c));
		tail2 = tail2->next;
		tail2->suit = temp->suit;
		tail2->value = temp->value;
		++counter;
	}

	return head2;
}




cPtr AddEnd(const cPtr head, const cPtr hold)
{
	cPtr temp = head;

	if(Length(temp) < 1)
	{
		printf("ERROR: Length of list being added to < 1. Returning head of list instead without added node.\n");
		return head;
	}
	else if(Length(temp) > 1)
	{
		temp = Search(temp, -1);
		temp->next = (cPtr)malloc(sizeof(_c));
		temp = temp->next;
		temp->next = NULL;
	}
	else if(Length(temp) == 1 && temp->suit != -1)
	{
		temp->next = (cPtr)malloc(sizeof(_c));
		temp = temp->next;
		temp->next = NULL;
	}
	temp->suit = hold->suit;
	temp->value = hold->value;
	temp->next = NULL;

	return head;
}




int Length(const cPtr head)
{
	cPtr temp = head;
	int numOfElements = 1;
	
	while(temp->next != NULL)
	{
		temp = temp->next;
		++numOfElements;
	}

	return numOfElements;
}




//passing by reference since multiple returns at ocne is not possible
void DealCards(cPtr& deckList, cPtr& handList, const int passingAmount)
{
	int deckSize = Length(deckList);
	cPtr hold;

	for(int i = 0; i < passingAmount; ++i)
	{
		if(deckSize > 0)
		{
			hold = Search(deckList, -1);//-1 refers to last element of list, which is the top of the deck
			deckList = RemoveN(deckList, -1);
			handList = AddEnd(handList, hold);
		}
		else
		{
			printf("ERROR: Attmepting to access cards that do not exist in parameter 1 of DealCards.\n");
		}
	}
}




bool GameOver(const hPtr deck, const hPtr player1Hand, const hPtr player2Hand, const hPtr player3Hand, const hPtr player4Hand)
{
	hPtr deckTemp = deck;
	hPtr player1HandTemp = player1Hand;
	hPtr player2HandTemp = player2Hand;
	hPtr player3HandTemp = player3Hand;
	hPtr player4HandTemp = player4Hand;
	
	int deckSize = Length(deckTemp->list);
	int player1HandSize = Length(player1HandTemp->list);
	int player2HandSize = Length(player2HandTemp->list);
	int player3HandSize = Length(player3HandTemp->list);
	int player4HandSize = Length(player4HandTemp->list);

	if(deckSize == 0 || player1HandSize == 0 || player2HandSize == 0 || player3HandSize == 0 || player4HandSize == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}




void PlayRound()
{
}




void CalculateWinner()
{

}




bool FreeMemory()
{
	return true;//temporary
}	