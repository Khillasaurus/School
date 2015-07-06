//=================================================================================================
// File:		States.h
// Created:		2012/10/12
// Last Edited:	2012/10/12
// Copyright:	Daniel Schenker
// Description	Holds namespaces of enums and other types in order to prevent magic numbers.
//=================================================================================================

#ifndef INCLUDED_STATES_H
#define INCLUDED_STATES_H

//=================================================================================================
// Includes
//=================================================================================================

#include <SGE.h>
using namespace SGE;

//=================================================================================================
// Namespaces
//=================================================================================================

namespace StateButton
{
	static enum eStateButton
	{
		kUp = 0,
		kHover = 1,
		kDown = 2,
		kClick = 3
	};
}

namespace StateDepth
{
	static float Background = 1.0f;
	static float Object = 0.5f;
	static float HUD = 0.25f;
	static float Cursor = 0.0f;
}

namespace StateRoom
{
	static enum eRoom
	{
		kRoomMainMenu = 0,
		kRoomOptions = 1,
		kRoomLevelOne = 2
	};
}

namespace StateScreen
{
	static const int kWinWidth = IniFile_GetInt("WinWidth", 1280);
	static const int kWinHeight = IniFile_GetInt("WinHeight", 720);
}

namespace StateToggle
{
	static enum eStateToggle
	{
		kNoToggle = -1,
		kOff = 0,
		kOn = 1
	};
}

namespace StateType
{
	static enum eStateType
	{
		kRed = 0,
		kOrange = 1,
		kYellow = 2,
		kGreen = 3,
		kBlueLight = 4,
		kBlueDark = 5,
		kPurple = 6,
		kPink = 7
	};
}

#endif //INCLUDED_STATES_H