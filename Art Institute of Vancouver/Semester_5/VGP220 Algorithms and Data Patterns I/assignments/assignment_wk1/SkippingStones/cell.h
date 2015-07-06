//-----------------------------
// File:		cell.h
// Created:		2012/07/06
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __CELL_H
	#define __CELL_H

	class cCell
	{
	public:
		cCell();
		cCell(char row, int column, bool isOccupied = false);
		~cCell();
	public:
		char row;
		int column;
		bool isOccupied;
	};

#endif//__CELL_H

//I might have to implement a default constructor for cCell() and then create a function to fill in the data afterwords, because of the issue I'm having with the constructor for cGrid