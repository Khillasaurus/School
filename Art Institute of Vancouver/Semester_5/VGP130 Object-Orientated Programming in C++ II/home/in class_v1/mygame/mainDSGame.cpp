//====================================================================================================
// File:		mainDSGame.cpp
// Created:		2012/07/26
// Copyright:	Daniel Schenker
// Description:	Defines the entry point for the application.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "stdafx.h"
#include <windows.h>
#include <string.h>
#include <SGE.h>
#include "core/core.h"
#include "cDSApp.h"

//====================================================================================================
// Main
//====================================================================================================

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	cDSApp app;
	app.Initialize("test", hInstance, 800, 600);
	app.Run();
	app.Terminate();

	return 0;
}