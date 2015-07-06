//-----------------------------
// File:		virtualpixel.h
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __VIRTUALPIXEL_H
#define __VIRTUALPIXEL_H

class cPixel
{
public:
	//Constructors
	cPixel();//White
	cPixel(unsigned char grey);//Greyscale
	cPixel(unsigned char blue, unsigned char green, unsigned char red);//Colour
	//Destructor
	~cPixel();

	unsigned char b;
	unsigned char g;
	unsigned char r;
};

#endif	//__VIRTUALPIXEL_H