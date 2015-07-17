#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define _ "[ ]"
#define X "[X]"
#define O "[O]"

void drawGrid(char grid[][3][3])
{
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			for (int c = 0; c < 3; c++)
			{
				printf("%c",grid[a][b][c]);
			}
			printf(" ");
		}
		printf("\n");
	}
	return;
}



int main()
{

	char grid[3][3][3]={'-'};
	int playerChoiceX;
	int playerChoiceY;
	int computerChoiceX;
	int computerChoiceY;
	int cRoll;
	int pRoll;
	bool playerFirst;

	//initialize random seed:
	srand ( time(NULL) );

	do
	{
		//generate random numbers
		cRoll = rand() % 6 + 1;
		pRoll = rand() % 6 + 1;
	}while (cRoll == pRoll);
	

	printf("Welcome to TicTacToe!\n");
	printf("To determine who goes first a die will be rolled.\n");
	printf("The computer rolled a %d.\n",cRoll);
	printf("You rolled a %d.\n",pRoll);

	if(cRoll>pRoll)
	{
		printf("The computer will go first.\n");
		playerFirst = false;
	}
	else if (pRoll>cRoll)
	{
		printf("You get to go first!\n");
		playerFirst = true;
	}

	drawGrid(grid);

	//scanf("%d",&playerChoiceX);


	return 0;
}