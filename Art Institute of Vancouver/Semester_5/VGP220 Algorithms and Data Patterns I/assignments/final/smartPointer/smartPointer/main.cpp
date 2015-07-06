//====================================================================================================
//File:			main.cpp
//Created:		2012/09/10
//Copyright:	Daniel Schenker
//Description:	Defines the entry point for the console application.
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Run-Time Library
//#include <stdlib.h>

//Daniel Schenker
#include "cSmartPointer.h"
#include "cActualData.h"

//====================================================================================================
//Main
//====================================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	cSmartPointer* pSmartPointer = new cSmartPointer("Hello World!");

	pSmartPointer->PrintData();

	delete pSmartPointer;
	pSmartPointer = NULL;

	return 0;
}
