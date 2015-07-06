//-----------------------------
// File:		pixel.cpp
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "pixel.h"

//Default to white
cPixel::cPixel()
: b(255)
, g(255)
, r(255)
{
}

//Greyscale
cPixel::cPixel(char grey)
: b(grey)
, g(grey)
, r(grey)
{
}

//Colour
cPixel::cPixel(char blue, char green, char red)
: b(blue)
, g(green)
, r(red)
{
}