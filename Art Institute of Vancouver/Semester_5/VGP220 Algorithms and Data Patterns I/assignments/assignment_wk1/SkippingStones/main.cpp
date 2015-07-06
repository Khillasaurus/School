//-----------------------------
// File:		main.cpp
// Created:		2012/07/06
// Copyright:	Daniel Schenker
//-----------------------------

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//Note: The order of my algorithm to check the amount of moveable pieces left is 2.
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include "stdafx.h"
#include "grid.h"
#include "cell.h"

//Function Prototypes
bool PlayGame();

//Utility
bool UserAgrees();
void UnitTest1();

int _tmain(int argc, _TCHAR* argv[])
{
	srand((unsigned)time(NULL));

	while(PlayGame())
	{
		//Allocate the grid
		cGrid* pGrid = new cGrid;
		
		pGrid->ClearGrid();
		pGrid->FillGridRandomly();

		while(pGrid->ValidMoveAvailable())
		{
			pGrid->MoveStone();
			pGrid->PrintGrid();
		}
		
		printf("No more available moves.\n");
		if(pGrid->GetPiecesLeft() == 1)
		{
			printf("Final board state:\n");
			pGrid->PrintGrid();
			printf("You jumped all the stones! Congradulations!!! =)\n");
		}
		else
		{
			printf("Final board state:\n");
			pGrid->PrintGrid();
			printf("Oh no, there were %d pieces left. Nice try!!\n", pGrid->GetPiecesLeft());
		}

		//Deallocate the grid and set the corresponding pointer to nullptr
		delete pGrid;
		pGrid = nullptr;

		//Analogous to the system call, clear screen. system("CLS")
		//Instead call the new line feed command many times.
		//This is because system("CLS") is resource heavy and a security issue.
		for(int i = 0; i < 16; ++i)
		{
			printf("\n");
		}
	}

	return 0;
}

bool PlayGame()
{
	printf("Welcome to the game: Skipping Stones!\n");
	printf("Would you like to play a new game?\n");
	return UserAgrees();
}

bool UserAgrees()
{
	printf("Enter 1 for yes, 0 for no.\n");

	int choice = -1;
	while(choice < 0 || choice > 1)
	{
		scanf("%d", &choice);
		if(choice < 0 || choice > 1)
		{
			printf("Invalid option. Please choose again.\n");
		}
	}

	if(choice == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void UnitTest1()
{
	cGrid myBoard;
	printf("After Create: Pieces Left: %d\n", myBoard.GetPiecesLeft());
	myBoard.ClearGrid();
	printf("After Clear: Pieces Left: %d\n", myBoard.GetPiecesLeft());
	myBoard.FillGridRandomly();
	printf("After Fill Randomly: Pieces Left: %d\n", myBoard.GetPiecesLeft());
	myBoard.PrintGrid();
}

/*
NOTE: I am not physically moving pieces around the board.
Rather I am changing the states of specific cells(tiles) on the grid(board)
EX: move from here to there (if a safe move)
	means: here becomes empty, there becomes occupied
*/