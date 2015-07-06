//-----------------------------
// File:		pixel.cpp
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"

//Default to white
cPixel::cPixel()
: b(255)
, g(255)
, r(255)
{
}

//Greyscale
cPixel::cPixel(unsigned char grey)
: b(grey)
, g(grey)
, r(grey)
{
}

//Colour
cPixel::cPixel(unsigned char blue, unsigned char green, unsigned char red)
: b(blue)
, g(green)
, r(red)
{
}