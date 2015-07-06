//----------------------------------------------------------------------------------------------------
// File:		cDSBitmap24bit.h
// Created:		2012/08/24
// Revision:	2012/08/25
// Copyright:	Daniel Schenker
//----------------------------------------------------------------------------------------------------

#ifndef CDSBITMAP24BIT_H
#define CDSBITMAP24BIT_H

//====================================================================================================
// Forward Declarations
//====================================================================================================

//Daniel Schenker
class cPixel24bit;

//====================================================================================================
//Class Declarations
//====================================================================================================

class cBitmap24bit
{
public:
	//Constructors
	cBitmap24bit();
	cBitmap24bit(const int width, const int height);
	//Destructor
	~cBitmap24bit();

public:
	//Overloaded Operators
	cBitmap24bit& operator = (const cBitmap24bit& b);
	bool operator == (const cBitmap24bit& b) const;
	bool operator != (const cBitmap24bit& b) const;

public:
	//Member Functions
	 //General
	  //Input
	//store physical bitmap file header, info header and image data
	bool Input(const char* fileName);
	//store physical bitmap file header and info header
	void InputHeader(const char* fileName);
	//store physical bitmap file header
	void InputFileHeader(const char* fileName);
	//store physical bitmap info header
	void InputInfoHeader(const char* fileName);
	//store physical bitmap image data
	void InputImageData(const char* fileName);
	//store specific section of phsyical bitmap image data
	void InputPartialImageData(const char* fileName, const int minX, const int minY, const int maxX, const int maxY);
	  //Output
	//write physical bitmap from virtual bitmap data
	void Output(const char* fileName);
	//write physical bitmap from specific section of virtual bitmap data
	bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY);
	  //Print
	//print virtual bitmap file header, info header and image data
	void PrintVirtual() const;
	//print virtual bitmap file header and info header
	void PrintVirtualHeader() const;
	//print virtual bitmap file header
	void PrintVirtualFileHeader() const;
	//print virtual bitmap info header
	void PrintVirtualInfoHeader() const;
	//print virtual bitmap image data
	void PrintVirtualImageData();
	 //Getters
	int GetWidth() const;
	int GetHeight() const;

protected:
	//Member Variables
	BITMAPFILEHEADER mBfh;	//Bitmap File Header
	BITMAPINFOHEADER mBih;	//Bitmap Info Header
	cPixel24bit* mpData;	//Pointer to the beginning of the bitmap
	int mWidth;				//Width of the bitmap in pixels
	int mHeight;			//Height of the bitmap in pixels
	#ifdef DSDEBUGMODE
		char mDebugBuff[512];
	#endif //DSDEBUGMODE

};

#endif	//CDSBITMAP24BIT_H

/*
TODO:
invert colours
how many colours in this bitmap
rotate
scale
crop/resize
flip
shade
tint
convert to greyscale
find least/greatest intensity (my version of intensity is the sum of the rgb)
calculate average intensity
*/