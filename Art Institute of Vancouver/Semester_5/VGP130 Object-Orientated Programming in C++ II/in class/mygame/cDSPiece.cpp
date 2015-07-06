//====================================================================================================
//File:			cDSMenuButton.cpp
//Created:		2012/08/18
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Daniel Schenker
#include "cDSPiece.h"
#include "cDSBoard.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

//Set the starting position of the piece equal to its correct position
cDSPiece::cDSPiece(const int pieceCorrectX, const int pieceCorrectY)
:	mPieceCorrectX(pieceCorrectX)
,	mPieceCorrectY(pieceCorrectY)
,	mPiecePosX(pieceCorrectX)
,	mPiecePosY(pieceCorrectY)
{
}

//----------------------------------------------------------------------------------------------------

cDSPiece::cDSPiece(const int pieceCorrectX, const int pieceCorrectY, const int piecePosX, const int piecePosY)
:	mPieceCorrectX(pieceCorrectX)
,	mPieceCorrectY(pieceCorrectY)
,	mPiecePosX(piecePosX)
,	mPiecePosY(piecePosY)
{
}

//----------------------------------------------------------------------------------------------------

cDSPiece::cDSPiece(const cDSPiece* piece)
:	mPieceCorrectX(piece->GetPieceCorrectX())
,	mPieceCorrectY(piece->GetPieceCorrectY())
,	mPiecePosX(piece->GetPiecePosX())
,	mPiecePosY(piece->GetPiecePosY())
{
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cDSPiece::~cDSPiece()
{
}

//----------------------------------------------------------------------------------------------------
//Overloaded Operators
//----------------------------------------------------------------------------------------------------

cDSPiece& cDSPiece::operator = (const cDSPiece& p)
{
	mPiecePosX = p.mPiecePosX;
	mPiecePosY = p.mPiecePosY;

	return (*this);
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

int cDSPiece::GetPieceCorrectX() const
{
	return mPieceCorrectX;
}

//----------------------------------------------------------------------------------------------------

int cDSPiece::GetPieceCorrectY() const
{
	return mPieceCorrectY;
}

//----------------------------------------------------------------------------------------------------

int cDSPiece::GetPiecePosX() const
{
	return mPiecePosX;
}

//----------------------------------------------------------------------------------------------------

int cDSPiece::GetPiecePosY() const
{
	return mPiecePosY;
}

//----------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------

void cDSPiece::SetPiecePos(const int piecePosX, const int piecePosY)
{
	mPiecePosX = piecePosX;
	mPiecePosY = piecePosY;
}