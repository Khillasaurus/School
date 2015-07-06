//----------------------------------------------------------------------------------------------------
// File:		cDSPixel24bit.cpp
// Created:		2012/04/21
// Revision:	2012/08/24
// Copyright:	Daniel Schenker
//----------------------------------------------------------------------------------------------------

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Daniel Schenker
#include "cDSPixel24bit.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
// Constuctors
//----------------------------------------------------------------------------------------------------

//White
cPixel24bit::cPixel24bit()
:	mBlue(0)
,	mGreen(0)
,	mRed(0)
{
}

//----------------------------------------------------------------------------------------------------

//Greyscale
cPixel24bit::cPixel24bit(unsigned char intensity)
:	mBlue(intensity)
,	mGreen(intensity)
,	mRed(intensity)
{
}

//----------------------------------------------------------------------------------------------------

//Colour
cPixel24bit::cPixel24bit(unsigned char blue, unsigned char green, unsigned char red)
:	mBlue(blue)
,	mGreen(green)
,	mRed(red)
{
}

//----------------------------------------------------------------------------------------------------
// Overloaded Operators
//----------------------------------------------------------------------------------------------------

cPixel24bit& cPixel24bit::operator = (const cPixel24bit& p)
{
	mBlue = p.mBlue;
	mGreen = p.mGreen;
	mRed = p.mRed;

	return (*this);
}

//----------------------------------------------------------------------------------------------------

bool cPixel24bit::operator == (const cPixel24bit& p) const
{
	if((mBlue != p.mBlue) || (mGreen != p.mGreen) || (mRed != p.mRed))
	{
		return false;
	}
	else
	{
		return true;
	}
}

//----------------------------------------------------------------------------------------------------

bool cPixel24bit::operator != (const cPixel24bit& p) const
{
	if((mBlue != p.mBlue) || (mGreen != p.mGreen) || (mRed != p.mRed))
	{
		return true;
	}
	else
	{
		return false;
	}
}

//----------------------------------------------------------------------------------------------------

void cPixel24bit::SetPixelData(const unsigned char blue, const unsigned char green, const unsigned char red)
{
	mBlue = blue;
	mGreen = green;
	mRed = red;
}