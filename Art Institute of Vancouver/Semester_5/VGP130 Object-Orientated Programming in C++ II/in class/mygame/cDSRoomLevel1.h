//====================================================================================================
//File:			cDSRoomLevel1.h
//Created:		2012/09/06
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef DSGAME_CDSROOMLEVEL1_H
#define DSGAME_CDSROOMLEVEL1_H

//====================================================================================================
//Includes
//====================================================================================================

//Daniel Schenker
#include "cDSRoom.h"
#include "cDSBitmap24bit.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

//SGE
class CFont;

//Daniel Schenker
class cDSApp;
class cDSBoard;
class cDSPiece;

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSRoomLevel1 : public cDSRoom
{
public:
	//Constructors
	cDSRoomLevel1(const char* bgTexture, const int puzzleInUse = 0, const int rows = 3, const int columns = 4);
	//Deconstructors
	virtual ~cDSRoomLevel1();

	//Member Functions
	 //General
	virtual void RunPhysics();
	virtual int CheckRoomChange();
	virtual void Render();
protected:
	void NewBoard();
	bool CreatePuzzlePieces(const char* bitmapName, const char* outputBaseName = NULL, const int directory = 0);

protected:
	//Member Variables
	 //General
	bool mPuzzleDefaultInitialized;
	bool mPuzzleUserInitialized;
	const int mPuzzleInUse;//0 = default, 1 = user
	const int mRows;
	const int mColumns;
	 //Tools
	cBitmap24bit* mpBitmapFull;
	 //Objects
	  //Puzzle
	cDSBoard* mpBoard;
	  //Buttons
	cDSMenuButton* mpButtonBack;
	cDSMenuButton* mpButtonScramble;
	 //Graphics
	  //Congratulations
	CSprite mCongratulationsSprite;
	CTexture mCongratulationsTexture;
	 //Fonts
	char mStatsBuff[512];
	CFont mFontStats;

	#ifdef DSDEBUGMODE
		char scoreTextBuff[64];
	#endif //DSDEBUGMODE
};

#endif //DSGAME_CDSROOMLEVEL1_H