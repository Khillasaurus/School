//====================================================================================================
// File:		cDSBoard.h
// Created:		2012/08/10
// Copyright:	Daniel Schenker
//====================================================================================================

#ifndef __CDSBOARD_H
#define __CDSBOARD_H

//====================================================================================================
// Includes
//====================================================================================================

#include <vector>
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

//Daniel Schenker
class cDSPiece;

//====================================================================================================
// Class Declarations
//====================================================================================================

class cDSBoard
{
public:
	//Constructors
	cDSBoard(const int posX, const int posY, const int width, const int height, const int tilesX, const int tilesY, int moveCounter = 0);
	~cDSBoard();

	//Member Functions
	 //General
	void LoadTileTextures(const char* pFileBaseName);
	void OverwriteTileTextures(const char* pFileBaseName);
	void UpdateTextures();
	bool MovePiece(const int pieceNum, bool increaseCounter = true);
	void ScramblePieces(const int moves);
	bool IsSolved();
	 //Getters
	bool GetPiecesPosScrambled() const;

public://should be protected with getters and setters, public for now
	//Member Variables
	const int mkPosX;				//horizontal offset in pixels of the top left origin of the board on the screen
	const int mkPosY;				//vertical offset in pixels of the top left origin of the board on the screen
	int mkWidth;					//board Width in pixels
	int mkHeight;					//board Height in pixels
	const int mkTilesX;				//number of tiles in the horizontal direction
	const int mkTilesY;				//number of tiles in the vertical direction
	bool mPiecesInitialPosSet;		//if the initial position of the pieces on the board have been set
	bool mPiecesPosScrambled;		//a flag to signal whether the puzzle has been scrambled at least once since creation
	bool mSolved;					//if the puzzle has been solved by the player
	int mMoveCounter;				//a counter for how many times a player uses the MovePiece command
	const int mkTilesTotal;			//total number of tiles on the board
	std::vector<cDSPiece*> mpTiles;	//list of piece on the board
	cDSPiece* mpEmptyTile;			//a fake piece for easy access for finding the empty tile on a board (if in another type of game more than one empty place is required, simply change this to a vector like the vector mpTiles)
};

#endif //__CDSBOARD_H