//=================================================================================================
// File:			CmdColor.cpp
// Created:			2012/10/03
// Last Modified:	2012/10/03
// Copyright:		Daniel Schenker
// Description:		Command script to set the color of a pixel.
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Precompiled Headers
#include "stdafx.h"

//CMGfx
#include "CmdColor.h"
#include "CmdDrawPixel.h"
#include "ScriptParser.h"
#include "Rasterizer.h"

//=================================================================================================
//Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//Constuctors
//-------------------------------------------------------------------------------------------------

CCmdColor::CCmdColor() : CCmdCommand()
{
}

//-------------------------------------------------------------------------------------------------
//Deconstructor
//-------------------------------------------------------------------------------------------------

CCmdColor::~CCmdColor()
{
}

//-------------------------------------------------------------------------------------------------
//General Functions
//-------------------------------------------------------------------------------------------------

BOOL CCmdColor::execute(CString &params)
{
	//Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	//Need 3 params for R, G and B
	const int numParams = 3;
	if(paramStrList.GetCount() != numParams)
	{
		return false;
	}

	float colorValue[numParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < numParams; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		colorValue[i] = (float)(wcstod(paramStr, NULL));

		//Clamp values to be in color range
		if(colorValue[i] < 0.0f)
		{
			colorValue[i] = 0.0f;
		}
		else if(colorValue[i] > 1.0f)
		{
			colorValue[i] = 1.0f;
		}
	}

	//Note: Internally this calls the openGL function: glColor3f()
	CRasterizer::Instance()->SetColor(colorValue[0], colorValue[1], colorValue[2]);

	return true;
}
