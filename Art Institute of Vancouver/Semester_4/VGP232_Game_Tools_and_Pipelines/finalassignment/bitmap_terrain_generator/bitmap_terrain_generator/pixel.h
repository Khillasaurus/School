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
	cPixel(unsigned char grey);//Greyscale
	cPixel(unsigned char blue, unsigned char green, unsigned char red);//Colour

	unsigned char b;
	unsigned char g;
	unsigned char r;
};

#endif	//__PIXEL_H