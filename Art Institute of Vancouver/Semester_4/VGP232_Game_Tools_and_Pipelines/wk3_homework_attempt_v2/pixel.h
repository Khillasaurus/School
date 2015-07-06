//-----------------------------
// File:		pixel.h
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __PIXEL_H
#define __PIXEL_H

class cPixel
{
public:
	cPixel();//Default to white
	cPixel(char grey);//Greyscale
	cPixel(char blue, char green, char red);//Colour

	char b;
	char g;
	char r;
};

#endif	//__PIXEL_H