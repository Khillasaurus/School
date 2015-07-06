//----------------------------------------------------------------------------------------------------
// File:		cDSBitmap24bit.cpp
// Created:		2012/08/24
// Revision:	2012/08/25
// Copyright:	Daniel Schenker
//----------------------------------------------------------------------------------------------------

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Daniel Schenker
#include "cDSBitmap24bit.h"
#include "cDSPixel24bit.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cBitmap24bit::cBitmap24bit()
:	mWidth(0)
,	mHeight(0)
{
	mpData = NULL;//mpData = nullptr; is only avaible in VS2010 and newer
}

//----------------------------------------------------------------------------------------------------

cBitmap24bit::cBitmap24bit(const int width, const int height)
:	mWidth(width)
,	mHeight(height)
{
	mpData = new cPixel24bit[mWidth * mHeight];
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cBitmap24bit::~cBitmap24bit()
{
	delete[] mpData;
	mpData = NULL;//mpData = nullptr; is only avaible in VS2010 and newer
}

//----------------------------------------------------------------------------------------------------
//Overloaded Operators
//----------------------------------------------------------------------------------------------------

cBitmap24bit& cBitmap24bit::operator = (const cBitmap24bit& b)
{
	//use the area shared by both, with both images expanding up and to the right from a shared bottom left origin
	//TODO

	return (*this);
}

//----------------------------------------------------------------------------------------------------

bool cBitmap24bit::operator == (const cBitmap24bit& b) const
{
	//if the sizes of the bitmaps are not equal
	if((mWidth != b.mWidth) || (mHeight != b.mHeight))
	{
		return false;
	}
	else
	{
		//compare every pixel in each bitmap until a difference is found
		for(int i = 0; i < (mWidth * mHeight); ++i)
		{
			if((mpData[i].mBlue != b.mpData[i].mBlue) || (mpData[i].mGreen != b.mpData[i].mGreen) || (mpData[i].mRed != b.mpData[i].mRed))
			{
				return false;
			}
		}
	}

	//since the bitmaps are identical return true
	return true;
}

//----------------------------------------------------------------------------------------------------

bool cBitmap24bit::operator != (const cBitmap24bit& b) const
{
	//if the sizes of the bitmaps are not equal
	if((mWidth != b.mWidth) || (mHeight != b.mHeight))
	{
		return true;
	}
	else
	{
		//compare every pixel in each bitmap until a difference is found
		for(int i = 0; i < (mWidth * mHeight); ++i)
		{
			if((mpData[i].mBlue != b.mpData[i].mBlue) || (mpData[i].mGreen != b.mpData[i].mGreen) || (mpData[i].mRed != b.mpData[i].mRed))
			{
				return true;
			}
		}
	}

	//since the bitmaps are identical return false
	return false;
}

//----------------------------------------------------------------------------------------------------
//General Functions
//----------------------------------------------------------------------------------------------------

//store physical bitmap file header, info header and image data
bool cBitmap24bit::Input(const char* fileName)
{
	unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
	unsigned int kBihSize = sizeof(BITMAPINFOHEADER);

	FILE* fpBitmap = fopen(fileName, "rb");
	if(fpBitmap)
	{
		//Store BITMAPFILEHEADER data
		if(fread(&mBfh, 1, kBfhSize, fpBitmap) == kBfhSize)
		{
			//Store BITMAPINFOHEADER data
			if(fread(&mBih, 1, kBihSize, fpBitmap) == kBihSize)
			{
				//update virtual bitmap size data
				mWidth = mBih.biWidth;
				mHeight = mBih.biHeight;

				//Store image data into virtual bmp
				//seek to beginning of bmp image data (likely redundant)
				fseek(fpBitmap, mBfh.bfOffBits, SEEK_SET);
				int padding = -1;
				//if the image data pointer is in use
				if(mpData)
				{
					//free the memory
					delete[] mpData;
					mpData = NULL;//mpData = nullptr; is only avaible in VS2010 and newer
					//Overwrite the old data
				}
				//allocate memory for the image data
				mpData = new cPixel24bit[mBih.biWidth * mBih.biHeight];
				//read one row at a time, since padding to a multiple of 4 bytes is added to the end of each row
				for(int i = 0; i < mBih.biHeight; ++i)
				{
					//Since mBih.biWidth does NOT include the padding, we must calculate it ourselves
					if(mBih.biWidth % 4 == 0)
					{
						padding = 0;
					}
					else if(mBih.biWidth % 4 == 1)
					{
						padding = 1;
					}
					else if(mBih.biWidth % 4 == 2)
					{
						padding = 2;
					}
					else if(mBih.biWidth % 4 == 3)
					{
						padding = 3;
					}
					for(int j = 0; j < mBih.biWidth; ++j)
					{
						//read in a row of bitmap data and store it into the virtual bitmap
						fread(&mpData[(i * mBih.biWidth) + j].mBlue, 1, 1, fpBitmap);
						fread(&mpData[(i * mBih.biWidth) + j].mGreen, 1, 1, fpBitmap);
						fread(&mpData[(i * mBih.biWidth) + j].mRed, 1, 1, fpBitmap);
					}
					//move to file pointer forward towards the next line, so that we don't read in the padding
					fseek(fpBitmap, padding, SEEK_CUR);
				}
			}
			else
			{
				printf("ERROR: BITMAPINFOHEADER unsuccessfully read from file. - void cBitmap24bit::Input(const char* fileName)\n");
			}
		}
		else
		{
			printf("ERROR: BITMAPFILEHEADER unsuccessfully read from file. - void cBitmap24bit::Input(const char* fileName)\n");
		}
		fclose(fpBitmap);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - void cBitmap24bit::Input(const char* fileName)\n", fileName);
		return false;
	}

	return true;
}

//----------------------------------------------------------------------------------------------------

//store physical bitmap file header and info header
void cBitmap24bit::InputHeader(const char* fileName)
{
	unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
	unsigned int kBihSize = sizeof(BITMAPINFOHEADER);

	FILE* fpBitmap = fopen(fileName, "rb");
	if(fpBitmap)
	{
		//Store BITMAPFILEHEADER data
		if(fread(&mBfh, 1, kBfhSize, fpBitmap) == kBfhSize)
		{
			//Store BITMAPINFOHEADER data
			if(fread(&mBih, 1, kBihSize, fpBitmap) == kBihSize)
			{
				//update virtual bitmap size data
				mWidth = mBih.biWidth;
				mHeight = mBih.biHeight;
			}
			else
			{
				printf("ERROR: BITMAPINFOHEADER unsuccessfully read from file. - void cBitmap24bit::InputHeader(const char* fileName)\n");
			}
		}
		else
		{
			printf("ERROR: BITMAPFILEHEADER unsuccessfully read from file. - void cBitmap24bit::InputHeader(const char* fileName)\n");
		}
		fclose(fpBitmap);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - void cBitmap24bit::InputHeader(const char* fileName)\n", fileName);
	}
}

//----------------------------------------------------------------------------------------------------

//store physical bitmap file header
void cBitmap24bit::InputFileHeader(const char* fileName)
{
	unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);

	FILE* fpBitmap = fopen(fileName, "rb");
	if(fpBitmap)
	{
		//Store BITMAPFILEHEADER data
		if(!fread(&mBfh, 1, kBfhSize, fpBitmap) == kBfhSize)
		{
			printf("ERROR: BITMAPFILEHEADER unsuccessfully read from file. - void cBitmap24bit::InputFileHeader(const char* fileName)\n");
		}
		fclose(fpBitmap);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - void cBitmap24bit::InputFileHeader(const char* fileName)\n", fileName);
	}
}

//----------------------------------------------------------------------------------------------------

//store physical bitmap info header
void cBitmap24bit::InputInfoHeader(const char* fileName)
{
	unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
	unsigned int kBihSize = sizeof(BITMAPINFOHEADER);

	FILE* fpBitmap = fopen(fileName, "rb");
	if(fpBitmap)
	{
		fseek(fpBitmap, kBfhSize, SEEK_CUR);
		//Store BITMAPINFOHEADER data
		if(fread(&mBih, 1, kBihSize, fpBitmap) == kBihSize)
		{
			//update virtual bitmap size data
			mWidth = mBih.biWidth;
			mHeight = mBih.biHeight;
		}
		else
		{
			printf("ERROR: BITMAPINFOHEADER unsuccessfully read from file. - void cBitmap24bit::InputInfoHeader(const char* fileName)\n");
		}
		fclose(fpBitmap);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - void cBitmap24bit::InputInfoHeader(const char* fileName)\n", fileName);
	}
}

//----------------------------------------------------------------------------------------------------

//store physical bitmap image data
void cBitmap24bit::InputImageData(const char* fileName)
{
	unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
	unsigned int kBihSize = sizeof(BITMAPINFOHEADER);

	FILE* fpBitmap = fopen(fileName, "rb");
	if(fpBitmap)
	{
		//Store BITMAPFILEHEADER data
		BITMAPFILEHEADER tempBfh;
		if(fread(&tempBfh, 1, kBfhSize, fpBitmap) == kBfhSize)
		{
			//Store BITMAPINFOHEADER data
			BITMAPINFOHEADER tempBih;
			if(fread(&tempBih, 1, kBihSize, fpBitmap) == kBihSize)
			{
				//update virtual bitmap size data
				mWidth = mBih.biWidth;
				mHeight = mBih.biHeight;

				//Store image data into virtual bmp
				//seek to beginning of bmp image data (likely redundant)
				fseek(fpBitmap, tempBfh.bfOffBits, SEEK_SET);
				int padding = -1;
				//if the image data pointer is in use
				if(mpData)
				{
					//free the memory
					delete[] mpData;
					mpData = NULL;//mpData = nullptr; is only avaible in VS2010 and newer
					//Overwrite the old data
				}
				//allocate memory for the image data
				mpData = new cPixel24bit[mBih.biWidth * mBih.biHeight];
				mWidth = mBih.biWidth;
				mHeight = mBih.biHeight;
				//read one row at a time, since padding to a multiple of 4 bytes is added to the end of each row
				for(int i = 0; i < mBih.biHeight; ++i)
				{
					//Since mBih.biWidth does NOT include the padding, we must calculate it ourselves
					if(mBih.biWidth % 4 == 0)
					{
						padding = 0;
					}
					else if(mBih.biWidth % 4 == 1)
					{
						padding = 1;
					}
					else if(mBih.biWidth % 4 == 2)
					{
						padding = 2;
					}
					else if(mBih.biWidth % 4 == 3)
					{
						padding = 3;
					}
					for(int j = 0; j < mBih.biWidth; ++j)
					{
						//read in a row of bitmap data and store it into the virtual bitmap
						fread(&mpData[(i * mBih.biWidth) + j].mBlue, 1, 1, fpBitmap);
						fread(&mpData[(i * mBih.biWidth) + j].mGreen, 1, 1, fpBitmap);
						fread(&mpData[(i * mBih.biWidth) + j].mRed, 1, 1, fpBitmap);
					}
					//move to file pointer forward towards the next line, so that we don't read in the padding
					fseek(fpBitmap, padding, SEEK_CUR);
				}
			}
			else
			{
				printf("ERROR: BITMAPINFOHEADER unsuccessfully read from file. - bool cBitmap24bit::InputImageData(const char* fileName)\n");
			}
		}
		else
		{
			printf("ERROR: BITMAPFILEHEADER unsuccessfully read from file. - bool cBitmap24bit::InputImageData(const char* fileName)\n");
		}
		fclose(fpBitmap);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - bool cBitmap24bit::InputImageData(const char* fileName)\n", fileName);
	}
}

//----------------------------------------------------------------------------------------------------

//store specific section of phsyical bitmap image data
void cBitmap24bit::InputPartialImageData(const char* fileName, const int minX, const int minY, const int maxX, const int maxY)
{
	//TODO
}

//----------------------------------------------------------------------------------------------------

//write physical bitmap from virtual bitmap data
void cBitmap24bit::Output(const char* fileName)
{
	FILE* f_out;//file pointer

	//Open file
	f_out = fopen(fileName, "wb");
	//if the file was opened succesfully
	if(f_out)
	{
		//cache data
		const unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
		const unsigned int kBihSize = sizeof(BITMAPINFOHEADER);
		
		//Define bitmap file header data for writing to file
		//specifies the file type. The file is a bmp if this is equal to 0x4D42
		mBfh.bfType = (0x4D42);
		//bitmap file size in bytes =
			//  size of bitmap file header:						sizeof(BITMAPFILEHEADER)
			//+ size of bitmap info header:						sizeof(BITMAPINFOHEADER)
			//+ size of bitmap image data including padding:	((width * 3) + (width % 4)) * height
		mBfh.bfSize = kBfhSize + kBihSize + (((mWidth * 3) + (mWidth % 4)) * mHeight);
		mBfh.bfReserved1 = 0;//Must be 0
		mBfh.bfReserved2 = 0;//Must be 0
		mBfh.bfOffBits = kBfhSize + kBihSize;//Offset in bytes from the beginning of the file to the bitmap image data

		//Write bitmap file header
		if(fwrite(&mBfh, 1, kBfhSize, f_out) == kBfhSize)
		{
			//Define bitmap info header data for writing to file
			//the size of the this header in bytes (bitmap info header)
			mBih.biSize = kBihSize;
			//the width of the bitmap image data NOT including padding
			mBih.biWidth = mWidth;
			//the height of the bitmap image data
			mBih.biHeight = mHeight;
			//number of colour planes, must be 1
			mBih.biPlanes = 1;
			//number of bits per pixel
			mBih.biBitCount = 24;
			//compression type BI_RGB is no compression which is most common)
			mBih.biCompression = BI_RGB;
			//bitmap image data size in bytes NOT including padding
			mBih.biSizeImage = mWidth * mHeight;
			//pixels per meter in x axis
				//3780 per meter is about 96 pixels per inch)
				//Since the 1980s, the Microsoft Windows operating system has set the default display "DPI" to 96 PPI
			mBih.biXPelsPerMeter = 3780;
			//pixels per meter in y axis
				//3780 per meter is about 96 pixels per inch)
				//Since the 1980s, the Microsoft Windows operating system has set the default display "DPI" to 96 PPI
			mBih.biYPelsPerMeter = 3780;
			//number of colours used by the bitmap
				//0 to default to 2n
			mBih.biClrUsed = 0;
			//number of colours that are important
				//0 when every color is important
			mBih.biClrImportant = 0;

			//Write bitmap info header
			if(fwrite(&mBih, 1, kBihSize, f_out) == kBihSize) 
			{
				//Write Bitmap data
				int padding = -1;
				const unsigned char kPaddingSymbol = '0';
				const unsigned char* const pkPaddingSymbol = & kPaddingSymbol;
				//if the image data pointer contains data
				if(mpData)
				{
					//Since mWidth does NOT include the padding, we must calculate it ourselves
					if(mWidth % 4 == 0)
					{
						padding = 0;
					}
					else if(mWidth % 4 == 1)
					{
						padding = 1;
					}
					else if(mWidth % 4 == 2)
					{
						padding = 2;
					}
					else if(mWidth % 4 == 3)
					{
						padding = 3;
					}
					//write one row at a time, since padding to a multiple of 4 bytes is added to the end of each row
					for(int i = 0; i < mHeight; ++i)
					{
						for(int j = 0; j < mWidth; ++j)
						{
							//write in a row of bitmap image data NOT including the padding
							if(fwrite(&mpData[(i * mWidth) + j].mBlue, 1, 1, f_out) != 1)
							{
								printf("ERROR: Failure of writing blue component of pixel %d in a physical bitmap. - void cBitmap24bit::Output(const char* fileName)\n", ((i * mWidth) + j));
							}
							if(fwrite(&mpData[(i * mWidth) + j].mGreen, 1, 1, f_out) != 1)
							{
								printf("ERROR: Failure of writing green component of pixel %d in a physical bitmap. - void cBitmap24bit::Output(const char* fileName)\n", ((i * mWidth) + j));
							}
							if(fwrite(&mpData[(i * mWidth) + j].mRed, 1, 1, f_out) != 1)
							{
								printf("ERROR: Failure of writing red component of pixel %d in a physical bitmap. - void cBitmap24bit::Output(const char* fileName)\n", ((i * mWidth) + j));
							}
						}
						//write 0's as padding
						if(fwrite(&pkPaddingSymbol, 1, padding, f_out) != padding)
						{
							printf("ERROR: Incorrect amount of padding written to physical bitmap. - void cBitmap24bit::Output(const char* fileName)\n");
						}
					}
				}
				else
				{
					printf("ERROR: mpData does not contain data. - bool cBitmap24bit::Output(const char* fileName)\n");
				}
			}
			else
			{
				printf("ERROR: Could not write bitmap info header. - bool cBitmap24bit::Output(const char* fileName)\n");
			}
		}
		else
		{
			printf("ERROR: Could not write bitmap file header. - bool cBitmap24bit::Output(const char* fileName)\n");
		}
		fclose(f_out);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to write in binary mode - bool cBitmap24bit::Output(const char* fileName)\n", fileName);
	}
}

//----------------------------------------------------------------------------------------------------

//write physical bitmap from specific section (inclusive coordinates) of virtual bitmap data
bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)
{
	//Ensure that the specified boundaries make a proper box
	if(bottomLeftX >= topRightX)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: A proper box cannot be formed due to bottomLeftX >= topRightX. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}
	else if(bottomLeftY >= topRightY)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: A proper box cannot be formed due to bottomLeftY >= topRightY. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}

	//Ensure that specified boundaries are compatible
	if(bottomLeftX < 0)
	{
		bottomLeftX = 0;
	}
	else if(bottomLeftX >= mWidth)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: bottomLeftX >= the width of the virtual bitmap data. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}
	if(bottomLeftY < 0)
	{
		bottomLeftY = 0;
	}
	else if(bottomLeftY >= mHeight)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: bottomLeftY >= the height of the virtual bitmap data. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}
	if(topRightX > mWidth)
	{
		topRightX = mWidth;
	}
	else if(topRightX <= 0)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: topRightX is <= 0. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}
	if(topRightY > mHeight)
	{
		topRightY = mHeight;
	}
	else if(topRightY <= 0)
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: topRightY is <= 0. - bool OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
		return false;
	}

	FILE* f_out;//file pointer

	//Open file
	f_out = fopen(fileName, "wb");
	//if the file was opened succesfully
	if(f_out)
	{
		//cache data
		const unsigned int kBfhSize = sizeof(BITMAPFILEHEADER);
		const unsigned int kBihSize = sizeof(BITMAPINFOHEADER);
		const unsigned int kWidth = topRightX - bottomLeftX + 1;//Plus one as coordinates are inclusive
		const unsigned int kHeight = topRightY - bottomLeftY + 1;//Plus one as coordinates are inclusive
		
		//Define bitmap file header data for writing to file
		//specifies the file type. The file is a bmp if this is equal to 0x4D42
		mBfh.bfType = (0x4D42);
		//bitmap file size in bytes =
			//  size of bitmap file header:						sizeof(BITMAPFILEHEADER)
			//+ size of bitmap info header:						sizeof(BITMAPINFOHEADER)
			//+ size of bitmap image data including padding:	((width * 3) + (width % 4)) * height
		mBfh.bfSize = kBfhSize + kBihSize + (((kWidth * 3) + (kWidth % 4)) * kHeight);
		mBfh.bfReserved1 = 0;//Must be 0
		mBfh.bfReserved2 = 0;//Must be 0
		mBfh.bfOffBits = kBfhSize + kBihSize;//Offset in bytes from the beginning of the file to the bitmap image data

		//Write bitmap file header
		if(fwrite(&mBfh, 1, kBfhSize, f_out) == kBfhSize)
		{
			//Define bitmap info header data for writing to file
			//the size of the this header in bytes (bitmap info header)
			mBih.biSize = kBihSize;
			//the width of the bitmap image data NOT including padding
			mBih.biWidth = kWidth;
			//the height of the bitmap image data
			mBih.biHeight = kHeight;
			//number of colour planes, must be 1
			mBih.biPlanes = 1;
			//number of bits per pixel
			mBih.biBitCount = 24;
			//compression type BI_RGB is no compression which is most common)
			mBih.biCompression = BI_RGB;
			//bitmap image data size in bytes NOT including padding
			mBih.biSizeImage = kWidth * kHeight;
			//pixels per meter in x axis
				//3780 per meter is about 96 pixels per inch)
				//Since the 1980s, the Microsoft Windows operating system has set the default display "DPI" to 96 PPI
			mBih.biXPelsPerMeter = 3780;
			//pixels per meter in y axis
				//3780 per meter is about 96 pixels per inch)
				//Since the 1980s, the Microsoft Windows operating system has set the default display "DPI" to 96 PPI
			mBih.biYPelsPerMeter = 3780;
			//number of colours used by the bitmap
				//0 to default to 2n
			mBih.biClrUsed = 0;
			//number of colours that are important
				//0 when every color is important
			mBih.biClrImportant = 0;

			//Write bitmap info header
			if(fwrite(&mBih, 1, kBihSize, f_out) == kBihSize) 
			{
				//Write Bitmap data
				int padding = -1;
				const unsigned char kPaddingSymbol = '0';
				const unsigned char* const pkPaddingSymbol = & kPaddingSymbol;
				//if the image data pointer contains data
				if(mpData)
				{
					//Since mWidth does NOT include the padding, we must calculate it ourselves
					if(kWidth % 4 == 0)
					{
						padding = 0;
					}
					else if(kWidth % 4 == 1)
					{
						padding = 1;
					}
					else if(kWidth % 4 == 2)
					{
						padding = 2;
					}
					else if(kWidth % 4 == 3)
					{
						padding = 3;
					}
					//row written flags
					bool startedWriting = false;
					bool finishedWriting = false;
					//write one row at a time, since padding to a multiple of 4 bytes is added to the end of each row
					for(int i = 0; i < mHeight; ++i)
					{
						for(int j = 0; j < mWidth; ++j)
						{
							//write in a row of bitmap image data NOT including the padding
							if(i >= bottomLeftY && i <= topRightY)
							{
								if(j >= bottomLeftX && j <= topRightX)
								{
									if(fwrite(&mpData[(i * mWidth) + j].mBlue, 1, 1, f_out) != 1)
									{
										#ifdef DSDEBUGMODE
											sprintf_s(mDebugBuff, "ERROR: Failure of writing blue component of pixel %d in a physical bitmap. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n", ((i * mWidth) + j));
											OutputDebugStringA(mDebugBuff);
										#endif //DSDEBUGMODE
									}
									if(fwrite(&mpData[(i * mWidth) + j].mGreen, 1, 1, f_out) != 1)
									{
										#ifdef DSDEBUGMODE
											sprintf_s(mDebugBuff, "ERROR: Failure of writing green component of pixel %d in a physical bitmap. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n", ((i * mWidth) + j));
											OutputDebugStringA(mDebugBuff);
										#endif //DSDEBUGMODE
									}
									if(fwrite(&mpData[(i * mWidth) + j].mRed, 1, 1, f_out) != 1)
									{
										#ifdef DSDEBUGMODE
											sprintf_s(mDebugBuff, "ERROR: Failure of writing red component of pixel %d in a physical bitmap. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n", ((i * mWidth) + j));
											OutputDebugStringA(mDebugBuff);
										#endif //DSDEBUGMODE
									}
									startedWriting = true;
								}
								if(startedWriting && (j == (mWidth - 1)))
								{
									finishedWriting = true;
								}
							}
						}
						if(finishedWriting)
						{
							//write 0's as padding
							if(fwrite(&pkPaddingSymbol, 1, padding, f_out) == padding)
							{
								//reset flags for next row
								startedWriting = false;
								finishedWriting = false;
							}
							else
							{
								#ifdef DSDEBUGMODE
									sprintf_s(mDebugBuff, "ERROR: Incorrect amount of padding written to physical bitmap. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
									OutputDebugStringA(mDebugBuff);
								#endif //DSDEBUGMODE
							}
						}
					}
				}
				else
				{
					#ifdef DSDEBUGMODE
						sprintf_s(mDebugBuff, "ERROR: mpData does not contain data. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
						OutputDebugStringA(mDebugBuff);
					#endif //DSDEBUGMODE
				}
			}
			else
			{
				#ifdef DSDEBUGMODE
					sprintf_s(mDebugBuff, "ERROR: Could not write bitmap info header. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
					OutputDebugStringA(mDebugBuff);
				#endif //DSDEBUGMODE
			}
		}
		else
		{
			#ifdef DSDEBUGMODE
				sprintf_s(mDebugBuff, "ERROR: Could not write bitmap file header. - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n");
				OutputDebugStringA(mDebugBuff);
			#endif //DSDEBUGMODE
		}
		fclose(f_out);
	}
	else
	{
		#ifdef DSDEBUGMODE
			sprintf_s(mDebugBuff, "ERROR: Could not open file \"%s\" to write in binary mode - bool cBitmap24bit::OutputPartial(const char* fileName, int bottomLeftX, int bottomLeftY, int topRightX, int topRightY)\n", fileName);
			OutputDebugStringA(mDebugBuff);
		#endif //DSDEBUGMODE
	}

	return true;
}

//----------------------------------------------------------------------------------------------------

//print virtual bitmap file header, info header and image data
void cBitmap24bit::PrintVirtual() const
{
	//Bitmap file header
	printf("BITMAPFILEHEADER\n");
	printf("bfType: 0x%x\n", mBfh.bfType);
	printf("bfSize: %d\n", mBfh.bfSize);
	printf("bfReserved1: %d\n", mBfh.bfReserved1);
	printf("bfReserved2: %d\n", mBfh.bfReserved2);
	printf("bfOffBits: %d\n", mBfh.bfOffBits);

	printf("\n");

	//Bitmap info header
	printf("BITMAPINFOHEADER\n");
	printf("biSize: %d\n", mBih.biSize);
	printf("biWidth: %d\n", mBih.biWidth);
	printf("biHeight: %d\n", mBih.biHeight);
	printf("biPlanes: %d\n", mBih.biPlanes);
	printf("biBitCount: %d\n", mBih.biBitCount);
	printf("biCompression: %d\n", mBih.biCompression);
	printf("biSizeImage: %d\n", mBih.biSizeImage);
	printf("biXPelsPerMeter: %d\n", mBih.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", mBih.biYPelsPerMeter);
	printf("biClrUsed: %d\n", mBih.biClrUsed);
	printf("biClrImportant: %d\n", mBih.biClrImportant);

	printf("\n");

	//Bitmap image data
	const int kSz = mBih.biWidth * mBih.biHeight;
	//temporary pointer to bitmap to prevent mpBitmap from moving
	cPixel24bit* pTemp = mpData;
	//format for printing bitmap image data
	printf("Pxl# = BU  : GN  : RD\n");
	//loop through virtual bitmap image data
	for(int pixelCount = 0; pixelCount < kSz; ++pixelCount)
	{
		if(pTemp)
		{
			printf("%-5d= ", pixelCount);
			printf("%-3u : ", pTemp->mBlue);
			printf("%-3u : ", pTemp->mGreen);
			printf("%-3u\n", pTemp->mRed);
			++pTemp;
		}
		else
		{
			printf("ERROR: Incomplete bitmap data stored into cBitmap24bit object. - void cBitmap24bit::PrintVirtual() const\n");
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------

//print virtual bitmap file header and info header
void cBitmap24bit::PrintVirtualHeader() const
{
	//Bitmap file header
	printf("BITMAPFILEHEADER\n");
	printf("bfType: 0x%x\n", mBfh.bfType);
	printf("bfSize: %d\n", mBfh.bfSize);
	printf("bfReserved1: %d\n", mBfh.bfReserved1);
	printf("bfReserved2: %d\n", mBfh.bfReserved2);
	printf("bfOffBits: %d\n", mBfh.bfOffBits);

	printf("\n");

	//Bitmap info header
	printf("BITMAPINFOHEADER\n");
	printf("biSize: %d\n", mBih.biSize);
	printf("biWidth: %d\n", mBih.biWidth);
	printf("biHeight: %d\n", mBih.biHeight);
	printf("biPlanes: %d\n", mBih.biPlanes);
	printf("biBitCount: %d\n", mBih.biBitCount);
	printf("biCompression: %d\n", mBih.biCompression);
	printf("biSizeImage: %d\n", mBih.biSizeImage);
	printf("biXPelsPerMeter: %d\n", mBih.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", mBih.biYPelsPerMeter);
	printf("biClrUsed: %d\n", mBih.biClrUsed);
	printf("biClrImportant: %d\n", mBih.biClrImportant);
}

//----------------------------------------------------------------------------------------------------

//print virtual bitmap file header
void cBitmap24bit::PrintVirtualFileHeader() const
{
	//Bitmap file header
	printf("BITMAPFILEHEADER\n");
	printf("bfType: 0x%x\n", mBfh.bfType);
	printf("bfSize: %d\n", mBfh.bfSize);
	printf("bfReserved1: %d\n", mBfh.bfReserved1);
	printf("bfReserved2: %d\n", mBfh.bfReserved2);
	printf("bfOffBits: %d\n", mBfh.bfOffBits);
}

//----------------------------------------------------------------------------------------------------

//print virtual bitmap info header
void cBitmap24bit::PrintVirtualInfoHeader() const
{
	//Bitmap info header
	printf("BITMAPINFOHEADER\n");
	printf("biSize: %d\n", mBih.biSize);
	printf("biWidth: %d\n", mBih.biWidth);
	printf("biHeight: %d\n", mBih.biHeight);
	printf("biPlanes: %d\n", mBih.biPlanes);
	printf("biBitCount: %d\n", mBih.biBitCount);
	printf("biCompression: %d\n", mBih.biCompression);
	printf("biSizeImage: %d\n", mBih.biSizeImage);
	printf("biXPelsPerMeter: %d\n", mBih.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", mBih.biYPelsPerMeter);
	printf("biClrUsed: %d\n", mBih.biClrUsed);
	printf("biClrImportant: %d\n", mBih.biClrImportant);
}

//----------------------------------------------------------------------------------------------------

//print virtual bitmap image data
void cBitmap24bit::PrintVirtualImageData()
{
	//Bitmap image data
	const int kSz = mBih.biWidth * mBih.biHeight;
	//temporary pointer to bitmap to prevent mpBitmap from moving
	cPixel24bit* pTemp = mpData;
	//format for printing bitmap image data
	printf("Pxl# = BU  : GN  : RD\n");
	//loop through virtual bitmap image data
	for(int pixelCount = 0; pixelCount < kSz; ++pixelCount)
	{
		if(pTemp)
		{
			printf("%-5d= ", pixelCount);
			printf("%-3u : ", pTemp->mBlue);
			printf("%-3u : ", pTemp->mGreen);
			printf("%-3u\n", pTemp->mRed);
			++pTemp;
		}
		else
		{
			printf("ERROR: Incomplete bitmap data stored into cBitmap24bit object. - void cBitmap24bit::PrintVirtualImageData()\n");
			break;
		}
	}
}

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

int cBitmap24bit::GetWidth() const
{
	return mWidth;
}

//----------------------------------------------------------------------------------------------------

int cBitmap24bit::GetHeight() const
{
	return mHeight;
}