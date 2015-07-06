//----------------------------
// File:		grid.cpp
// Created:		2012/07/06
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "grid.h"
#include "cell.h"

cGrid::cGrid()
:	kSideLength(16)
,	piecesLeft(kSideLength * kSideLength)
{
	//Allocate memory for an array of cCell objects
	/*
	Note:	There is no direct way to initialize the contents of a dynamically allocated array.
			Consequently, if we are allocating an array of objects, there is no way to pass arguments to objects’ constructors.
			Therefore it is required that the objects that are stored in such an array have a no-argument constructor.
			Only after all of this can the contents of the objects be set.
	*/
	pGrid = new cCell[kSideLength * kSideLength];

	//For each row
	for(char i = 0; i < kSideLength; ++i)
	{
		//For each column
		for(int j = 0; j < kSideLength; ++j)
		{
			//Set the name of the rows and columns
			pGrid[(kSideLength * i) + j].row = 65 + i;//add 65 since ascii code 65 is 'A'
			pGrid[(kSideLength * i) + j].column = j;
		}
	}
}

cGrid::~cGrid()
{
	//Delete the grid and all of the cells contained
	delete[] pGrid;//Note: When dealing with an array of objects, the destructor for each of them is automatically called.

	pGrid = nullptr;
}

void cGrid::ClearGrid()
{
	for(int i = 0; i < kSideLength * kSideLength; ++i)
	{
		pGrid[i].isOccupied = false;
	}

	piecesLeft = 0;
}

void cGrid::FillGridSequencially()
{
	//Set the first 100 cells of the board to occupied
	for(int i = 0; i < piecesLeft; ++i)
	{
		pGrid[i].isOccupied = true;
	}
}

void cGrid::FillGridRandomly()
{
	if(piecesLeft != 0)
	{
		printf("ERROR: The board still has pieces on it. Clearing the board first. - cGridd::FillGridRandomly()\n");
		ClearGrid();
	}

	int cell = 0;

	while(piecesLeft < 100)
	{
		//Pick a random cell
		cell = rand() % (kSideLength * kSideLength);

		//If the cell is empty
		if(!pGrid[cell].isOccupied)
		{
			//Set the cell to occupied
			pGrid[cell].isOccupied = true;
			++piecesLeft;
		}
	}
}

void cGrid::PrintGrid()
{
	//Print two blank spaces to account for the vertical axis identifiers
	printf("   ");

	//Print the horizontal axis identifiers
	for(char hLabel = 0; hLabel < kSideLength; ++hLabel)
	{
		printf("%c", 65 + hLabel);//add 65 since ascii code 65 is 'A'
	}
	printf("\n");

	//Print the vertical axis identifiers
	for(int row = 0; row < kSideLength; ++row)
	{
		printf("%d ", row);
		//Print an extra space as a placeholder if the row is a single digit
		if(row < 10)
		{
			printf(" ", row);
		}

		//Print the grid data
		for(int column = 0; column < kSideLength; ++column)
		{
			if(pGrid[(kSideLength * row) + column].isOccupied)
			{
				printf("1");
			}
			else
			{
				printf("0");
			}
		}
		printf("\n");
	}
}

//If any 2 stones are next to each other
	//and if there is at least one stone left
		//and if all the stones are not in a straight line kSideLength long
			//there is a possible move available
void cGrid::MoveableStones()
{
	//Check for straight line of length kSideLength
		if(piecesLeft == kSideLength)
		{
			bool hole = false;//If a hole in the line exists

			//Find the first stone
				//Check the first row for a stone
				int checkRow = -1;
				for(int i = 0; i < kSideLength; ++i)
				{
					if(pGrid[i].isOccupied)
					{
						checkRow = i;
						break;
					}
				}
			//Check first row to see if a straight vertical line of stones exists
			if(checkRow > -1)
			{
				for(int i = 0; i < kSideLength; ++i)
				{
					//If a hole in the line exists
					if(!pGrid[checkRow + (i * kSideLength)].isOccupied)
					{
						hole = true;
					}
				}
				//A straight line exists
				if(!hole)
				{
					moveableStones = 0;
					immoveableStones == piecesLeft;
					return;
				}
			}

			//If no stones were found in the first row, check first column
			if(checkRow == -1)
			{
				//Find the first stone
					//Check the first column for a stone
					int checkColumn = -1;
					for(int i = 0; i < kSideLength; ++i)
					{
						if(pGrid[i * kSideLength].isOccupied)
						{
							checkColumn = i;
							break;
						}
					}
				//Check first column to see if a straight horizontal line of stones exists
				if(checkColumn > -1)
				{
					for(int i = 0; i < kSideLength; ++i)
					{
						//If a hole in the line exists
						if(!pGrid[checkColumn + i].isOccupied)
						{
							hole = true;
						}
					}
					//A straight line exists
					if(!hole)
					{
						moveableStones = 0;
						immoveableStones == piecesLeft;
						return;
					}
				}
			}
			//If we found a stone in the first row, but there was a hole in the line, simply continue with counting moveablePieces algorithm
		}

	//Iterate through entire grid once
	for(int i = 0; i < kSideLength * kSideLength; ++i)
	{
		//Check if a stone is in this cell
		if(pGrid[i].isOccupied)
		{
			//Check if stone is adjacent to a wall
				//First row
				if(pGrid->row == 65)
				{
					//First Column
					if(pGrid->column == 0)
					{
						//If the cell to the right is taken
						if(pGrid[i + 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell below is taken
						else if(pGrid[i + kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
					//Last Column
					else if(pGrid->column == kSideLength)
					{
						//If the cell to the left is taken
						if(pGrid[i - 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell below is taken
						else if(pGrid[i + kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}

					}
					//Middle 14 columns
					else
					{
						//If the cell to the right is taken
						if(pGrid[i + 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell to the left is taken
						else if(pGrid[i - 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell below is taken
						else if(pGrid[i + kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
				}
				//Last Row
				else if(pGrid->row == (65 + kSideLength))
				{
					//First Column
					if(pGrid->column == 0)
					{
						//If the cell to the right is taken
						if(pGrid[i + 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell above is taken
						else if(pGrid[i - kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
					//Last Column
					else if(pGrid->column == (kSideLength - 1))
					{
						//If the cell to the left is taken
						if(pGrid[i - 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell above is taken
						else if(pGrid[i - kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}

					}
					//Middle 14 columns
					else
					{
						//If the cell to the right is taken
						if(pGrid[i + 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell to the left is taken
						else if(pGrid[i - 1].isOccupied)
						{
							++moveableStones;
						}
						//If the cell above is taken
						else if(pGrid[i - kSideLength].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
				}
				//First column
				else if(pGrid->column == 0)
				{
					//Not first or last row as those have already been checked
					if(pGrid->row != 65 && pGrid->row != (65 + kSideLength))
					{
						//Check to the right for the middle rows
						//If the cell to the right is taken
						if(pGrid[i + 1].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
				}
				//Last Column
				else if(pGrid->column == (kSideLength - 1))
				{
					//Not first or last row as those have already been checked
					if(pGrid->row != 65 && pGrid->row != (65 + kSideLength))
					{
						//Check to the left for the middle rows
						//If the cell to the right is taken
						if(pGrid[i - 1].isOccupied)
						{
							++moveableStones;
						}
						else
						{
							++immoveableStones;
						}
					}
				}
			//end adjacent to wall check

			//Check cells not adjacent to walls
				//If the cell to the right is taken
				if(pGrid[i + 1].isOccupied)
				{
					++moveableStones;
				}
				//If the cell to the left is taken
				else if(pGrid[i - 1].isOccupied)
				{
					++moveableStones;
				}
				//If the cell below is taken
				else if(pGrid[i + kSideLength].isOccupied)
				{
					++moveableStones;
				}
				//If the cell above is taken
				else if(pGrid[i - kSideLength].isOccupied)
				{
					++moveableStones;
				}
				else
				{
					++immoveableStones;
				}
		}
	}
}

bool cGrid::ValidMoveAvailable()
{
	if(moveableStones > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void cGrid::MoveStone()
{
	//TODO
}

int cGrid::GetPiecesLeft()
{
	return piecesLeft;
}

int cGrid::GetMoveableStones()
{
	return moveableStones;
}

int cGrid::GetImmoveableStones()
{
	return immoveableStones;
}