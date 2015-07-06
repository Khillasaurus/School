//====================================================================================================
//File:			mainDSGame.cpp
//Created:		2012/07/26
//Copyright:	Daniel Schenker
//Description:	Defines the entry point for the application.
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

#include "stdafx.h"
#include <string.h>
#include <SGE.h>
#include "core/core.h"
#include "cDSApp.h"

//====================================================================================================
//Main
//====================================================================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	//cDSApp app(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	cDSApp app;
	app.Initialize("Super Slider!", hInstance, app.GetScreenWidth(), app.GetScreenHeight());
	app.Run();
	app.Terminate();

	return 0;
}