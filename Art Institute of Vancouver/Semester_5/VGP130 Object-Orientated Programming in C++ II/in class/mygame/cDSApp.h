//====================================================================================================
//File:			cDSApp.h
//Created:		2012/07/26
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CDSAPP_H
#define CDSAPP_H

//====================================================================================================
//Includes
//====================================================================================================

// DirectX
#include <d3dx9math.h>

//SGE
#include "Core/Core.h"
#include "Graphics/Graphics.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

//SGE
class CFont;
class CSprite;
class CTexture;

//Daniel Schenker
class cDSCursor;
class cDSRoom;
class cDSRoomMainMenu;
class cDSRoomOptions;
class cDSRoomLevel1;
class cBitmap24bit;
class cDSBoard;

//====================================================================================================
//Enums
//====================================================================================================

enum Room
{
	kRoomMainMenu = 0,
	kRoomOptions = 1,
	kRoomLevelOne = 2
};

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSApp : public CApplication
{
public:
	//Constructors
	cDSApp();
	cDSApp(const int screenWidth, const int screenHeight);

	//Member Functions
protected:
	 //General
	virtual void OnInitialize(void);
	virtual void OnMainLoop(void);
	virtual void OnTerminate(void);
public:
	 //Getters
	D3DXVECTOR2 GetScreenSize() const;
	int GetScreenWidth() const;
	int GetScreenHeight() const;
	int GetRoomNumber() const;
	int GetPuzzleInUse() const;
	 //Setters
	void SetRoomNumber(const int roomNumber);
	void SetPuzzleInUse(int puzzleInUse);

	//Member Variables
public:
	 //Settings
	static const int msScreenWidth;
	static const int msScreenHeight;
	static float msDepthBackground;
	static float msDepthObject;
	static float msDepthButton;
	static float msDepthCursor;
protected:
	 //General
	int mRoomNumber;
	int mRows;
	int mColumns;
	 //Rooms
	cDSRoom* mpRoomMainMenu;
	cDSRoom* mpRoomOptions;
	cDSRoom* mpRoomLevel1;
	 //HUD
	  //Cursor
	cDSCursor* mpCursor;
	 //Objects
	int mPuzzleInUse;//0 = default, 1 = user
	int mPuzzleDimensionX;
	int mPuzzleDimensionY;
	 //Fonts
	CFont mDefaultFont;
	 //DEBUG
	#ifdef DSDEBUGMODE
		char mDebugBuff[512];
		CFont mFontDebug1;
		char debugBuff1[256];
		CFont mFontDebug2;
		char debugBuff2[256];
		CFont mFontDebug3;
		char debugBuff3[256];
	#endif //DSDEBUGMODE

	friend class cDSRoomOptions;
	friend class cDSRoomLevel1;
};

#endif //CDSAPP_H