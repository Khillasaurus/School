//-----------------------------
// File:		grid.h
// Created:		2012/07/06
// Copyright:	Daniel Schenker
//-----------------------------

//Forward decl
class cCell;

#ifndef __GRID_H
	#define __GRID_H

	class cGrid
	{
		public:
			cGrid();
			~cGrid();

			void ClearGrid();
			void FillGridSequencially();
			void FillGridRandomly();
			void PrintGrid();
			void MoveableStones();
			bool ValidMoveAvailable();
			void MoveStone();

			//Getters
			int GetPiecesLeft();
			int GetMoveableStones();
			int GetImmoveableStones();

		public:
			cCell* pGrid;
		private:
			const int kSideLength;
			int piecesLeft;
			int moveableStones;
			int immoveableStones;
	};

#endif//__GRID_H