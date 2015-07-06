//====================================================================================================
//File:			cDSRoomOptions.h
//Created:		2012/09/05
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef DSGAME_CDSROOMOPTIONS_H
#define DSGAME_CDSROOMOPTIONS_H

//====================================================================================================
//Includes
//====================================================================================================

//Daniel Schenker
#include "cDSRoom.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

//SGE
class CFont;

//Daniel Schenker
class cDSApp;
class cDSBoard;
class cDSPiece;
class cDSBitmap24bit;

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSRoomOptions : public cDSRoom
{
public:
	//Constructors
	cDSRoomOptions(const char* bgTexture, cDSApp* app);
	//Deconstructors
	virtual ~cDSRoomOptions();

	//Member Functions
	 //General
	virtual void RunPhysics();
	virtual int CheckRoomChange();
	virtual void Render();

protected:
	//Member Variables
	 //Objects
	  //Buttons
	cDSMenuButton* mpButtonBack;
	   //Puzzle
	    //Default
	     //image
	cDSMenuButton* mpButtonPuzzleDefaultImage;
	     //label
	cDSMenuButton* mpButtonPuzzleDefaultLabel;
	    //User
	     //image
	cDSMenuButton* mpButtonPuzzleUserImage;
	     //label
	cDSMenuButton* mpButtonPuzzleUserLabel;
	   //Choice Slider
	int mChoiceSliderDefaultX;
	int mChoiceSliderDefaultY;
	int mChoiceSliderUserX;
	int mChoiceSliderUserY;
	cDSMenuButton* mpButtonChoiceSlider;
	   //Arrows
	cDSMenuButton* mpButtonRowsArrowUp;
	cDSMenuButton* mpButtonRowsArrowDown;
	cDSMenuButton* mpButtonColumnsArrowUp;
	cDSMenuButton* mpButtonColumnsArrowDown;
	 //Graphics
	  //Title
	CSprite mTitleSprite;
	CTexture mTitleTexture;
	  //User puzzle instructions
	CSprite mInstructionsSprite;
	CTexture mInstructionsTexture;
	 //Fonts
	char mRowsBuff[16];
	CFont mFontRows;
	char mColumnsBuff[16];
	CFont mFontColumns;
	 //Other
	cDSApp* pApp;
};

#endif //DSGAME_CDSROOMOPTIONS_H