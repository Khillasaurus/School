//-----------------------------
// File:		warcardspiel.cpp
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "card.h"
#include "player.h"
#include <algorithm>

//globals
const int kDeckSize = 52;

//function prototypes
bool WantsToPlay();
//cCard* CreateCards();
bool Initialize(deque<cCard*>&, deque<cCard*>&, deque<cCard*>&);
void ShuffleCards(deque<cCard*>&);
void DealCards(deque<cCard*>&, deque<cCard*>&, const int);
bool GameOver(deque<cCard*>&, deque<cCard*>&);
void PlayRound(cPlayer&, cPlayer&, cPlayer&, cPlayer&, cPlayer&);
void DescribeGameplay(const int, const int, const int);
void CalculateWinner(cPlayer&, cPlayer&);
bool FreeMemory(cPlayer&, cPlayer&, cPlayer&, cPlayer&, cPlayer&, cPlayer&);

int _tmain(int argc, _TCHAR* argv[])
{	
	bool runGame = true;

	while(runGame)
	{
		if(WantsToPlay())
		{
			cPlayer deck;
			cPlayer player1Hand;
			cPlayer player2Hand;
			cPlayer tableP1;
			cPlayer tableP2;
			cPlayer discardPile;

			//cCard* cardsListPtr = CreateCards();
			if(Initialize(deck.mList, player1Hand.mList, player2Hand.mList))
			{
				while(!GameOver(player1Hand.mList, player2Hand.mList))
				{
					PlayRound(player1Hand, player2Hand, tableP1, tableP2, discardPile);//game logic done here
				}
				CalculateWinner(player1Hand, player2Hand);
				if(!FreeMemory(deck, player1Hand, player2Hand, tableP1, tableP2, discardPile))
				{
					cout << "ERROR: Memory could not be freed." << endl;
					break;
				}
			}
			else
			{
				cout << "ERROR: Could not initialize game." << endl;
				break;
			}
		}
		else
		{
			runGame = false;
			cout << "See you next time!" << endl;
		}
	}

	return 0;
}

/*
cGame *pGame = new cChessGame();

if(pGame->Init())
{
	pGame->Run();
	pGame->Shutdown();
}

delete pGame;
*/



bool WantsToPlay()
{
	int wantsToPlay = -1;

	while(wantsToPlay < 0 || wantsToPlay > 1)
	{
		cout << "Do you want to play a card game of War?" << endl;
		cout << "Enter 1 for yes or 0 for no." << endl;
		cin >> wantsToPlay;
		if(wantsToPlay < 0 || wantsToPlay > 1)
		{
			cout << "You have entered an incorrect value." << endl;
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

/*
vector<cCard*> theDeck;

bool InitDeck( vector<cCard*> &theDeck )
{
	theDeck.reserve( kDeckSize );
	for(int i = 0; i < 1234; ++i)
	{
		(*deck).push_back( new cCard( suit, val ) );
	}
	return true;
}
*/

/*
cCard* CreateCards()
{
	cCard* cardsListPtr = new cCard[kDeckSize];
	for(int i = 0; i < kDeckSize; ++i)
	{
		cardsListPtr[i].mSuit = (kDeckSize-i-1) / 13;
		cardsListPtr[i].mValue = (kDeckSize-i-1) % 13;
	}
	
	return cardsListPtr;
}
*/

bool Initialize(deque<cCard*>& deck, deque<cCard*>& player1Hand, deque<cCard*>& player2Hand)
{
	//deck.reserve(kDeckSize);
	int suit;
	int value;

	for(int i = 0; i < kDeckSize; ++i)
	{
		suit = (kDeckSize-i-1) / 13;
		value = (kDeckSize-i-1) % 13;

		/*
		cCard *pCard;
		pCard = new cCard();
		pCard->mSuit = suit;
		pCard->mValue = value;

		deck.push_back( pCard )l;
		*/

		deck.push_back(new cCard(suit, value));
	}

	ShuffleCards(deck);

	DealCards(deck, player1Hand, kDeckSize/2);
	DealCards(deck, player2Hand, kDeckSize/2);
	
	if(deck.size() == 0)
	{
		if(player1Hand.size() == kDeckSize/2)
		{
			if(player2Hand.size() == kDeckSize/2)
			{
				return true;
			}
		}
	}

	return false;
}




void ShuffleCards(deque<cCard*>& cards)
{
	random_shuffle(cards.begin(), cards.end());
}




void DealCards(deque<cCard*>& deck, deque<cCard*>& hand, const int numCards)
{
	//for(int i = 0; i < kDeckSize; ++i)
	for(int i = 0; i < numCards; ++i)
	{
		if(deck.size())
		{
			//hand.push_back(deck.back());
			//deck.pop_back();

			hand.push_back(deck.front());
			deck.pop_front();

		}
		else
		{
			cout << "Attempting to deal cards from parameter one of function DealCards but parameter one has no cards." << endl;
			cout << "Dealing of cards will stop and game will continue to next step as if it was no cards were intended to be dealt." << endl;
			break;
		}
		
		//*hand.push_back(deck[(*deck).size()-1]);
		//deck.pop_back();
	}
}




bool GameOver(deque<cCard*>& player1Hand, deque<cCard*>& player2Hand)
{
	if(player1Hand.size() == 0 || player2Hand.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}




void PlayRound(cPlayer& player1Hand, cPlayer& player2Hand, cPlayer& tableP1, cPlayer& tableP2, cPlayer& discardPile)
{
	bool roundOver = false;
	int points = 0;
	int cardCounter = 0;

	while(!roundOver)
	{
		DealCards(player1Hand.mList, tableP1.mList, 1);
		DealCards(player2Hand.mList, tableP2.mList, 1);
		++points;
		DescribeGameplay((tableP1.mList[tableP1.mList.size()-1]->mSuit), (tableP1.mList[tableP1.mList.size()-1]->mValue), 1);
		DescribeGameplay((tableP2.mList[tableP2.mList.size()-1]->mSuit), (tableP2.mList[tableP2.mList.size()-1]->mValue), 2);

		if(tableP1.mList[cardCounter]->mValue > tableP2.mList[cardCounter]->mValue)
		{
			player1Hand.mScore += points;
			cout << "Player 1 earns " << points << " points!" << endl;
			cout << "Player 1's new score is: " << player1Hand.mScore << "." << endl << endl;
			roundOver = true;
		}
		else if(tableP1.mList[cardCounter]->mValue < tableP2.mList[cardCounter]->mValue)
		{
			player2Hand.mScore += points;
			cout << "Player 2 earns " << points << " points!" << endl;
			cout << "Player 2's new score is: " << player2Hand.mScore << "." << endl << endl;
			roundOver = true;
		}
		else//tie
		{
			cout << "It's a tie! WAR!" << endl << endl;
			if(player1Hand.mList.size() >= 3 && player2Hand.mList.size() >= 3)
			{
				DealCards(player1Hand.mList, tableP1.mList, 2);
				DealCards(player2Hand.mList, tableP2.mList, 2);
				points += 2;
				cardCounter += 3;
			}
			else if(player1Hand.mList.size() > 0 && player2Hand.mList.size() > 0)
			{
				if(player1Hand.mList.size() > player2Hand.mList.size())
				{
					points += player1Hand.mList.size();
					player1Hand.mScore += points;
					cout << "Player 1 earns " << points << " points!" << endl;
					cout << "Player 1's new score is: " << player1Hand.mScore << "." << endl << endl;
					DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
					DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
					roundOver = true;
					break;
				}
				else if(player1Hand.mList.size() < player2Hand.mList.size())
				{
					points += player2Hand.mList.size();
					player2Hand.mScore += points;
					cout << "Player 2 earns " << points << " points!" << endl;
					cout << "Player 2's new score is: " << player2Hand.mScore << "." << endl << endl;
					DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
					DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
					roundOver = true;
					break;
				}
				else//both players have an equal amount of cards left but it is less than 3 and greater than 0
				{
					cardCounter += player1Hand.mList.size();
					DealCards(player1Hand.mList, tableP1.mList, player1Hand.mList.size());
					DealCards(player2Hand.mList, tableP2.mList, player2Hand.mList.size());
					points += player1Hand.mList.size();
					if(tableP1.mList[cardCounter]->mValue > tableP2.mList[cardCounter]->mValue)
					{
						player1Hand.mScore += points;
						cout << "Player 1 earns " << points << " points!" << endl;
						cout << "Player 1's new score is: " << player1Hand.mScore << "." << endl << endl;
						DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
						DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
						roundOver = true;
						break;
					}
					else if(tableP1.mList[cardCounter]->mValue < tableP2.mList[cardCounter]->mValue)
					{
						player2Hand.mScore += points;
						cout << "Player 2 earns " << points << " points!" << endl;
						cout << "Player 2's new score is: " << player2Hand.mScore << "." << endl << endl;
						DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
						DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
						roundOver = true;
						break;
					}
					else//still tie on last card, no points awarded to either player for last card
					{
						cout << "Aww the last card was a tie. No points are awarded for this mini WAR!" << endl  << endl;
						DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
						DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
						roundOver = true;
						break;
					}
				}
			}
			else if(player1Hand.mList.size() > 0 && player2Hand.mList.size() == 0)//player 1 has cards and player 2 does not
			{
				points += player1Hand.mList.size();
				player1Hand.mScore += points;
				cout << "Player 1 earns " << points << " points!" << endl;
				cout << "Player 1's new score is: " << player1Hand.mScore << "." << endl << endl;
				DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
				DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
				roundOver = true;
				break;
			}
			else if(player1Hand.mList.size() == 0 && player2Hand.mList.size() > 0)//player 2 has cards and player 1 does not
			{
				points += player2Hand.mList.size();
				player2Hand.mScore += points;
				cout << "Player 2 earns " << points << " points!" << endl;
				cout << "Player 2's new score is: " << player2Hand.mScore << "." << endl << endl;
				DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
				DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
				roundOver = true;
				break;
			}
			else//both players do not have any cards left, no points awarded
			{
				cout << "Oh no! Both players ran out of cards! No points awarded for this mini WAR!" << endl << endl;
				DealCards(player1Hand.mList, discardPile.mList, player1Hand.mList.size());//to make garbage clean-up easier later
				DealCards(player2Hand.mList, discardPile.mList, player2Hand.mList.size());//to make garbage clean-up easier later
				roundOver = true;
				break;
			}
		}
	}
	DealCards(tableP1.mList, discardPile.mList, tableP1.mList.size());
	DealCards(tableP2.mList, discardPile.mList, tableP2.mList.size());
}




void DescribeGameplay(const int suit, const int value, const int playerNum)
{
	cout << "Player " << playerNum << " plays a(n) ";

	if(value <= 8)
	{
		cout << value+2;
	}
	else if(value == 9)
	{
		cout << "jack";
	}
	else if(value == 10)
	{
		cout << "queen";
	}
	else if(value == 11)
	{
		cout << "king";
	}
	else
	{
		cout << "ace";
	}

	cout << " of ";

	if(suit == 0)
	{
		cout << "hearts." << endl;
	}
	else if(suit == 1)
	{
		cout << "spades." << endl;
	}
	else if(suit == 2)
	{
		cout << "diamonds." << endl;
	}
	else
	{
		cout << "clubs." << endl;
	}
}




void CalculateWinner(cPlayer& player1Hand, cPlayer& player2Hand)
{
	cout << endl;
	cout << "Player 1 Score: " << player1Hand.mScore << endl;
	cout << "Player 2 Score: " << player2Hand.mScore << endl;
	if(player1Hand.mScore > player2Hand.mScore)
	{
		cout << "Congradulations! Player 1 wins!" << endl;
	}
	else if(player1Hand.mScore < player2Hand.mScore)
	{
		cout << "Congradulations! Player 2 wins!" << endl;
	}
	else//tie
	{
		cout << "Oh wow! It's a tie! Good game." << endl;
	}
	cout << endl;
}




bool FreeMemory(cPlayer& deck, cPlayer& player1Hand, cPlayer& player2Hand, cPlayer& tableP1, cPlayer& tableP2, cPlayer& discardPile)
{
	//delete cPlayer::deck;
	for(unsigned int i = 0; i < deck.mList.size(); ++i)
	{
		delete deck.mList[i];	
	}
	deck.mList.clear();
	for(unsigned int i = 0; i < player1Hand.mList.size(); ++i)
	{
		delete player1Hand.mList[i];	
	}
	player1Hand.mList.clear();
	for(unsigned int i = 0; i < player2Hand.mList.size(); ++i)
	{
		delete player2Hand.mList[i];	
	}
	player2Hand.mList.clear();
	for(unsigned int i = 0; i < tableP1.mList.size(); ++i)
	{
		delete tableP1.mList[i];	
	}
	tableP1.mList.clear();
	for(unsigned int i = 0; i < tableP2.mList.size(); ++i)
	{
		delete tableP2.mList[i];	
	}
	tableP2.mList.clear();
	for(unsigned int i = 0; i < discardPile.mList.size(); ++i)
	{
		delete discardPile.mList[i];	
	}
	discardPile.mList.clear();

	
	if(deck.mList.empty())
	{
		if(player1Hand.mList.empty())
		{
			if(player1Hand.mList.empty())
			{
				if(tableP1.mList.empty())
				{
					if(tableP2.mList.empty())
					{
						if(discardPile.mList.empty())
						{
							return true;
						}
						else
						{
							cout << "ERROR: discardPile could not be free'd from memory." << endl;
						}
					}
					else
					{
						cout << "ERROR: tableP2 could not be free'd from memory." << endl;
					}
				}
				else
				{
					cout << "ERROR: tableP1 could not be free'd from memory." << endl;
				}
			}
			else
			{
				cout << "ERROR: player2Hand could not be free'd from memory." << endl;
			}
		}
		else
		{
			cout << "ERROR: player1Hand could not be free'd from memory." << endl;
		}
	}
	else
	{
		cout << "ERROR: discardPile could not be free'd from memory." << endl;
	}
	return false;
}




	/*cout << "deck" << endl;
	for(int i = 0; i < (int)(*deck).size(); ++i)
	{
		cout << i << " Face = " << ((*deck)[i].mSuit) << endl;
		cout << i << " Value = " << ((*deck)[i].mValue) << endl;
	}
	cout << "player1" << endl;
	for(int i = 0; i < (int)(*player1).size(); ++i)
	{
		cout << i << " Face = " << ((*player1)[i].mSuit) << endl;
		cout << i << " value = " << ((*player1)[i].mValue) << endl;
	}
	cout << "player2" << endl;
	for(int i = 0; i < (int)(*player2).size(); ++i)
	{
		cout << i << " Face = " << ((*player2)[i].mSuit) << endl;
		cout << i << " value = " << ((*player2)[i].mValue) << endl;
	}*/




	//std::vector<int>::iterator vecIt;

	//cout << "index of for loop" << endl;
	//for(int i = 0; i < (int)deck.size(); ++i)
	//{
	//	cout << "value = " << (deck[i]/*index of is nano seconds faster than iterators so the time saved is almost useless*/) << endl;
	//}

	//cout << "iterator for loop, as well as shuffled" << endl;
	//for(vecIt = deck.begin(); vecIt !=deck.end(); ++vecIt)
	//{
	//	cout << "value = " << (*vecIt)/*iterator i was talking about in above inline comment*/ << endl;
	//}