//----------------------------------------------------------------------------------------------------
// File:		cDSPixel24bit.h
// Created:		2012/04/21
// Revision:	2012/08/24
// Copyright:	Daniel Schenker
//----------------------------------------------------------------------------------------------------

#ifndef CDSPIXEL24BIT_H
#define CDSPIXEL24BIT_H

//====================================================================================================
//Class Declarations
//====================================================================================================

class cPixel24bit
{
public:
	//Constructors
	cPixel24bit();//White
	cPixel24bit(unsigned char grey);//Greyscale
	cPixel24bit(unsigned char blue, unsigned char green, unsigned char red);//Colour

public:
	//Overloaded Operators
	cPixel24bit& operator = (const cPixel24bit& p);
	bool operator == (const cPixel24bit& p) const;
	bool operator != (const cPixel24bit& p) const;

public:
	//Member Functions
	 //General
	void SetPixelData(const unsigned char blue, const unsigned char green, const unsigned char red);

public:
	//Member Variables
	unsigned char mBlue;
	unsigned char mGreen;
	unsigned char mRed;
};

#endif	//CDSPIXEL24BIT_H