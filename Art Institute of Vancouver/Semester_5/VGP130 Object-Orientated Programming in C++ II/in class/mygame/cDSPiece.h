//====================================================================================================
//File:			cDSPiece.h
//Created:		2012/08/18
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef DSGAME_CDSPIECE_H
#define DSGAME_CDSPIECE_H

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSPiece : public cDSMenuButton
{
public:
	//Constructors
	cDSPiece(const int pieceCorrectX, const int pieceCorrectY);
	cDSPiece(const int pieceCorrectX, const int pieceCorrectY, const int piecePosX, const int piecePosY);
	cDSPiece(const cDSPiece* piece);
	//Deconstructors
	~cDSPiece();

	//Overloaded Operators
	cDSPiece& operator = (const cDSPiece& p);

	//Member Functions
	 //General
	 //Getters
	int GetPieceCorrectX() const;
	int GetPieceCorrectY() const;
	int GetPiecePosX() const;
	int GetPiecePosY() const;
	 //Setters
	void SetPiecePos(const int piecePosX, const int piecePosY);

protected:
	//Member Variables
	const int mPieceCorrectX;
	const int mPieceCorrectY;
	int mPiecePosX;
	int mPiecePosY;
};

#endif //DSGAME_CDSPIECE_H
