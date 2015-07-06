//====================================================================================================
//File:			cDSApp.cpp
//Created:		2012/07/26
//Copyright:	Daniel Schenker
//Description:	Defines the entry point for the console application.
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

#include "stdafx.h"

//====================================================================================================
//Main
//====================================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	//buffer to store data to be compressed
	char dataBuff[256] = "Hello, how are you?";

	//frequency table
	//std::priority_queue<freqElement> freqTable (dataBuff, dataBuff + strlen(dataBuff));

	return 0;
}

	/*
	//Free dynamically allocated memory
	if(pDataOriginal)
	{
		delete pDataOriginal;
		pDataOriginal = NULL;//Switch NULL for nullptr when using visual studio 2010 or newer
	}
	*/
