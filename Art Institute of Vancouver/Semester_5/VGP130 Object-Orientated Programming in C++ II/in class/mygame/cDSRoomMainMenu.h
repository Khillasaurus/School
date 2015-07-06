//====================================================================================================
//File:			cDSRoomMainMenu.h
//Created:		2012/09/05
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef DSGAME_CDSROOMMAINMENU_H
#define DSGAME_CDSROOMMAINMENU_H

//====================================================================================================
//Includes
//====================================================================================================

//Daniel Schenker
#include "cDSRoom.h"

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSRoomMainMenu : public cDSRoom
{
public:
	//Constructors
	cDSRoomMainMenu(const char* bgTexture);
	//Deconstructors
	virtual ~cDSRoomMainMenu();

	//Member Functions
	 //General
	virtual void RunPhysics();
	virtual int CheckRoomChange();
	virtual void Render();

protected:
	//Member Variables
	 //General
	 //Objects
	  //Buttons
	cDSMenuButton* mpButtonStart;
	cDSMenuButton* mpButtonOptions;
	 //Graphics
	  //Title
	CSprite mTitleSprite;
	CTexture mTitleTexture;
};

#endif //DSGAME_CDSROOMMAINMENU_H