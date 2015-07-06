////====================================================================================================
//// File:		App.h
//// Created:		2012/07/26
//// Last Edited:	2012/10/12
//// Copyright:	Daniel Schenker
//// Description:	Class used to hold application specifics,
////				allow for easy memory management
////				and encapsulate the functionality of header + cpp files for WinMain.
////====================================================================================================
//
//#ifndef INCLUDED_APP_H
//#define INCLUDED_APP_H
//
////====================================================================================================
//// Includes
////====================================================================================================
//
////DirectX
//#include <d3dx9math.h>
//
//// SGE
//#include "Core/Core.h"
//#include "Graphics/Graphics.h"
//
////====================================================================================================
//// Forward Declarations
////====================================================================================================
//
////SGE
//class CFont;
//class CSprite;
//class CTexture;
//
////Daniel Schenker
//class Cursor;
//class Room;
////class cRoomMainMenu;//!!!
////class cRoomOptions;//!!!
////class cRoomLevel1;//!!!
//
////====================================================================================================
//// Enums
////====================================================================================================
//
//namespace Room
//{
//	enum eRoom
//	{
//		kRoomMainMenu = 0,
//		kRoomOptions = 1,
//		kRoomLevelOne = 2
//	};
//}
//
////====================================================================================================
//// Class Declarations
////====================================================================================================
//
//class App
//{
//public:
//	//Constructors
//	App();
//	
//	//Deconstructor
//
//protected:
//	 //General
//	virtual void OnInitialize(void);
//	virtual void OnMainLoop(void);
//	virtual void OnTerminate(void);
//public:
//	 //Getters
//	D3DXVECTOR2 GetScreenSize() const;
//	int GetScreenWidth() const;
//	int GetScreenHeight() const;
//	int GetRoomNumber() const;
//	int GetPuzzleInUse() const;
//	 //Setters
//	void SetRoomNumber(const int roomNumber);
//	void SetPuzzleInUse(int puzzleInUse);
//
//	//Member Variables
//public:
//	 //Settings
//	static const int msScreenWidth;
//	static const int msScreenHeight;
//	static float msDepthBackground;
//	static float msDepthObject;
//	static float msDepthButton;
//	static float msDepthCursor;
//protected:
//	 //General
//	int mRoomNumber;
//	int mRows;
//	int mColumns;
//	 //Rooms
//	cDSRoom* mpRoomMainMenu;
//	cDSRoom* mpRoomOptions;
//	cDSRoom* mpRoomLevel1;
//	 //HUD
//	  //Cursor
//	cDSCursor* mpCursor;
//	 //Objects
//	int mPuzzleInUse;//0 = default, 1 = user
//	int mPuzzleDimensionX;
//	int mPuzzleDimensionY;
//	 //Fonts
//	CFont mDefaultFont;
//	 //DEBUG
//	#ifdef DSDEBUGMODE
//		char mDebugBuff[512];
//		CFont mFontDebug1;
//		char debugBuff1[256];
//		CFont mFontDebug2;
//		char debugBuff2[256];
//		CFont mFontDebug3;
//		char debugBuff3[256];
//	#endif //DSDEBUGMODE
//
//	friend class cDSRoomOptions;
//	friend class cDSRoomLevel1;
//};
//
//#endif //CDSAPP_H