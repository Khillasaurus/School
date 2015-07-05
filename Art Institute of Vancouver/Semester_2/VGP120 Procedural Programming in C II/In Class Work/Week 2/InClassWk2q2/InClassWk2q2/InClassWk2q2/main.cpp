#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Player{						//typedef struct Player{
	int money;						//	int money;
	int dice;						//	int dice;
};									//} player;
typedef struct Player player;		// this means the same thing as what's on the right but is more compact for aesthetics
typedef struct Player *playerPtr;	//following creates a pointer of type Player

//the following creates a pointer to a structure and can be referred to as playerPtr (same thing as 2 lines above)
*
typedef struct Player{
	int money;
	int dice;
}*playerPtr;
*/
//example: playerPtr pPtr;

void Initialize(playerPtr);
void DisplayPlayer(player, int);

int main()
{
	//initialize random seed:
	srand (time(NULL));

	int playerNum = 1;
	player p,q;

	playerPtr p1 = &p;
	playerPtr p2 = &q;

	Initialize(p1);
	Initialize(p2);
	DisplayPlayer(p, playerNum);
	++playerNum;
	DisplayPlayer(q, playerNum);

	return 0;
}

void Initialize(playerPtr pX)
{
	pX->money = rand() % 1000 + 1001;
	pX->dice = rand() % 2 + 1;
}

void DisplayPlayer(player pX, int playerNum)
{
	printf("p%d money: %d\tp%d dice: %d\n", playerNum, pX.money, playerNum, pX.dice);
}