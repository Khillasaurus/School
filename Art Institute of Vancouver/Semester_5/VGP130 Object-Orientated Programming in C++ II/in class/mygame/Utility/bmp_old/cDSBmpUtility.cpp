//====================================================================================================
// File:		cDSBmpUtility.cpp
// Created:		2012/06/04	-	v1
// Version:		2012/08/16	-	v2
// Copyright:	Daniel Schenker
// Description:	Defines the entry point for the application.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "stdafx.h"
#include "cDSBmpUtility.h"
#include <cmath>

//====================================================================================================
// Class Definitions
//====================================================================================================

//Create a grid with a default initial value and default final value
void cDSBmpUtility::Test1CreateGridDefDef()
{
	int* pGrid = NULL;
	const int kSideLength = 16;
	
	if(CreateSquareGrid(pGrid, kSideLength, 0))
	{
		printf("The new grid:\n");
		PrintSquareGrid(pGrid, kSideLength);
		FillSquareGrid(pGrid, kSideLength);
	}
	printf("The grid filled using my algorithm:\n");
	PrintSquareGrid(pGrid, kSideLength);
	CleanUp(pGrid);

	printf("\n");
}

//Create a virtual bmp with a default initial value and default final value
void cDSBmpUtility::Test2aCreateVirtualBMPDefDef()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;

	cPixel* pPixelInitial = new cPixel(32);
	cPixel* pPixelFinal = new cPixel(128);
	
	if(CreateVirtualBMP(pBMP, kSideLength, pPixelInitial))
	{
		printf("The new BMP:\n");
		PrintVirtualBMPData(pBMP, kSideLength);
		FillVirtualBMP(pBMP, kSideLength, pPixelFinal);
	}
	printf("The grid filled using my algorithm:\n");
	PrintVirtualBMPData(pBMP, kSideLength);
	CleanUpVirtualBMP(pBMP);

	CleanUpVirtualPixel(pPixelInitial);
	CleanUpVirtualPixel(pPixelFinal);

	printf("\n");
}

//Create a virtual bmp with a default initial value and random final value
void cDSBmpUtility::Test2bCreateVirtualBMPDefRan()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;

	cPixel* pPixelInitial = new cPixel(32);
	
	if(CreateVirtualBMP(pBMP, kSideLength, pPixelInitial))
	{
		printf("The new BMP:\n");
		PrintVirtualBMPData(pBMP, kSideLength);
		FillVirtualBMPRandomly(pBMP, kSideLength);
	}
	printf("The grid filled using my algorithm:\n");
	PrintVirtualBMPData(pBMP, kSideLength);
	CleanUpVirtualBMP(pBMP);

	CleanUpVirtualPixel(pPixelInitial);

	printf("\n");
}

//Create a virtual bmp with a random initial value and random final value
void cDSBmpUtility::Test2cCreateVirtualBMPRanRan()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;
	
	if(CreateVirtualBMPRandomly(pBMP, kSideLength))
	{
		printf("The new BMP:\n");
		PrintVirtualBMPData(pBMP, kSideLength);
		FillVirtualBMPRandomly(pBMP, kSideLength);
	}
	printf("The grid filled using my algorithm:\n");
	PrintVirtualBMPData(pBMP, kSideLength);
	CleanUpVirtualBMP(pBMP);

	printf("\n");
}

//Access and modify the properties of a pixel object
void cDSBmpUtility::Test3ModifyPixel()
{
	cPixel* pPixelWhite = new cPixel;
	cPixel* pPixelGreyscale = new cPixel(64);
	cPixel* pPixelColour = new cPixel(128, 128, 128);

	printf("White Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelWhite->b, pPixelWhite->g, pPixelWhite->r);
	printf("Greyscale Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelGreyscale->b, pPixelGreyscale->g, pPixelGreyscale->r);
	printf("Colour Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelColour->b, pPixelColour->g, pPixelColour->r);

	CleanUpVirtualPixel(pPixelWhite);
	CleanUpVirtualPixel(pPixelGreyscale);
	CleanUpVirtualPixel(pPixelColour);

	printf("\n");
}

//Create a randomly generated virtual bmp and save it as a bmp file
void cDSBmpUtility::Test4CreateBMPRandomly()
{
	cPixel* pBMP = NULL;

	//Query bmp sideLength
	int sideLength = 0;
	printf("How long would you like the side length of the square bmp to be?\n");
	scanf("%d", &sideLength);
	EnsurePositive(sideLength);
	const int kSideLength = sideLength;
	
	//If a randomly generated bmp was created succesfully
	if(CreateVirtualBMPRandomly(pBMP, kSideLength))
	{
		//Query BMP file name
		char fileName[256] = "";
		char* pFileName = &fileName[0];
		printf("What would you like the file name of the bmp to be? (Not including file extension \".bmp\")\n");
		scanf("%s", pFileName);

		//Print the new bmp
		printf("The new bmp:\n");
		printf("Name: %s\tSide Length:%d\n", pFileName, kSideLength);
		PrintVirtualBMPData(pBMP, kSideLength);
		printf("\n");

		//Use the virtual bmp to create a real bmp file
		CreateBMP(pFileName, kSideLength, pBMP);
	}
	CleanUpVirtualBMP(pBMP);

	printf("\n");
}

//Display the data of a pre-existing bmp file one piece at a time
void cDSBmpUtility::Test5DisplayBMPData()
{
	//Query BMP file name
	char fileName[256] = "";
	printf("What is the name of the bmp file that you would like to view that data of? (Not including file extension \".bmp\")\n");
	scanf("%s", fileName);
	strcat(fileName, ".bmp");
	printf("\n");

	FILE* fpBMP = fopen(fileName, "rb");
	printf("Opening file \"%s\" to read in binary mode\n", fileName);
	if(fpBMP)
	{
		printf("File \"%s\" opened succesfully\n", fileName);

		PrintBMPData(fpBMP);
		fclose(fpBMP);
	}
	else
	{
		printf("ERROR: Could not open file \"%S\" to read in binary mode - Test5DisplayBMPData()\n");
	}

	printf("\n");
}

//Store the data of a pre-existing bmp file into a virtual bmp and display both the bmp and virtual bmp data as a comparison
void cDSBmpUtility::Test6StoreBMPData()
{
	//Query BMP file name
	char fileName[256] = "";
	printf("What is the name of the bmp file that you would like to store the data of? (Not including file extension \".bmp\")\n");
	scanf("%s", fileName);
	strcat(fileName, ".bmp");
	printf("\n");

	FILE* fpBMP = fopen(fileName, "rb");
	printf("Opening file \"%s\" to read in binary mode\n", fileName);
	if(fpBMP)
	{
		printf("File \"%s\" opened succesfully\n", fileName);

		printf("Storing bmp data into a virtual bmp\n");
		cPixel* pBMP = ReadBMP(fpBMP);
		printf("Virtual bmp has successfully been created from the bmp file\n");

		printf("Comparing the virtual bmp data to the original bmp data:\n");

		long width = 0;
		long height = 0;

		GetBMPDimensions(fpBMP, width, height);

		if(width == height)
		{
			printf("Virtual Bmp Data:\n");
			PrintVirtualBMPData(pBMP, width);
		}
		else
		{
			printf("ERROR: Bmp width does not equal height. - Test6StoreBMPData()\n");
			printf("Skipping printing of virtual bmp data\n");
		}
		printf("\n");
		printf("Original Bmp Data:\n");
		PrintBMPData(fpBMP);

		CleanUpVirtualBMP(pBMP);
		fclose(fpBMP);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - Test6StoreBMPData()\n", fileName);
	}

	printf("\n");
}

//-----------------------------------------------------------------------------

//Load a bmp and create multiple smaller bmps that combine to make up the original bmp
void cDSBmpUtility::ChopBMP(const char* pFileName, const int tilesX, const int tilesY)
{
	if(tilesX <= 0)
	{
		printf("ERROR: tilesX must be greater than 0. Returning. - cDSBmpUtility::ChopBMP(const char* pFileName, const int tilesX, const int tilesY)");
		return;
	}
	if(tilesY <= 0)
	{
		printf("ERROR: tilesY must be greater than 0. Returning. - cDSBmpUtility::ChopBMP(const char* pFileName, const int tilesX, const int tilesY)");
		return;
	}

	FILE* fpBMP = fopen(pFileName, "rb");
	printf("Opening file \"%s\" to read in binary mode\n", pFileName);
	if(fpBMP)
	{
		printf("File \"%s\" opened succesfully\n", pFileName);

		printf("Storing bmp data into a virtual bmp\n");
		cPixel* pBMP = ReadBMP(fpBMP);
		printf("Virtual bmp has successfully been created from the bmp file\n");

		int bmpWidth = 0;
		int bmpHeight = 0;

		GetBMPDimensions(fpBMP, bmpWidth, bmpHeight);

		// Close the file pointer to the physical bmp
		fclose(fpBMP);

		float tileWidth = floor((float)bmpWidth / (float)tilesX);
		float tileHeight = floor((float)bmpHeight / (float)tilesY);

		CleanUpVirtualBMP(pBMP);
	}
	else
	{
		printf("ERROR: Could not open file \"%s\" to read in binary mode - ChopBMP()\n", pFileName);
	}

	printf("\n");
}

//-----------------------------------------------------------------------------

//Create a BMP file from specified virtual bmp data
void cDSBmpUtility::CreateBMP(const char* kFileName, const int kSideLength, cPixel* pBMPData)
{
	printf("Creating a BMP file from specified virtual bmp data. - CreateBMP(const char*, const int, const cPixel*)\n");

	FILE * f_out;//file pointer
	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;

	//BMP file name
	char fileName[260] = "";
	strcpy(fileName, kFileName);
	strcat(fileName, ".bmp");

	//Open file
	f_out = fopen(fileName, "wb");
	printf("Opening file \"%s\" to write in binary mode\n", fileName);
	if(f_out)
	{
		printf("File \"%s\" opened succesfully\n", fileName);
		bfh.bfType = (0x4D42);//Specifies the file type. The file is a bmp if this is equal to 0x4D42
		bfh.bfSize = kSideLength * kSideLength;//Bitmap file size in bytes
		bfh.bfReserved1 = 0;//Must be 0
		bfh.bfReserved2 = 0;//Must be 0
		bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);//Offset in bytes from the bitmapfileheader to the bitmap bits

		//Write BMP file header
		printf("Writing BMP file header\n");
		if(fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), f_out) == sizeof(BITMAPFILEHEADER))
		{
			printf("Done writing BMP file header\n");

			bih.biSize = sizeof(BITMAPINFOHEADER);//Number of bytes required by the struct
			bih.biWidth = kSideLength;
			bih.biHeight = kSideLength;
			bih.biPlanes = 1;//Number of colour planes, must be 1
			bih.biBitCount = 24;//Number of bit per pixel
			bih.biCompression = BI_RGB;//Compression type
			bih.biSizeImage = kSideLength * kSideLength;//Image size in bytes
			bih.biXPelsPerMeter = 96;//Pixels per meter in x axis
			bih.biYPelsPerMeter = 96;//Pixels per meter in y axis
			bih.biClrUsed = 0;//Number of colours used by the bitmap
			bih.biClrImportant = 0;//Number of colours that are important

			//Write BMP info header
			printf("Writing BMP info header\n");
			if(fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), f_out) == sizeof(BITMAPINFOHEADER)) 
			{
				printf("Done writing BMP info header\n");

				//Write BMP data
				printf("Writing BMP data\n");

				for(int i = 0; i < (kSideLength * kSideLength); ++i)
				{
					fwrite(&pBMPData[i].b, 1, 1, f_out);
					fwrite(&pBMPData[i].g, 1, 1, f_out);
					fwrite(&pBMPData[i].r, 1, 1, f_out);
				}
				printf("Done writing BMP data.\n");
			}
			else
			{
				printf("ERROR: Could not write BMP info header!\n");
			}
		}
		else
		{
			printf("ERROR: Could not write BMP file header!\n");
		}
		fclose(f_out);
	}
}

void cDSBmpUtility::GetBMPDimensions(FILE* fpBMP, int& width, int& height)
{
	printf("Determing dimensions of bmp - GetBMPDimensions(FILE* fpBmp, int&, int&)\n");

	BITMAPINFOHEADER bih;
	unsigned int kBfhSize = 14;
	unsigned int kBihSize = 40;
	BITMAPINFOHEADER* pBih = &bih;

	//Seek to beginning of bmp info header data
	fseek(fpBMP, kBfhSize, SEEK_SET);

	//Store BITMAPINFOHEADER data
	fread(pBih, kBihSize, 1, fpBMP);

	width = bih.biWidth;
	height = bih.biHeight;

	printf("Bmp width: %ld\n", width);
	printf("Bmp height: %ld\n", height);

	printf("\n");
}

void cDSBmpUtility::GetBMPDimensions(FILE* fpBMP, long& width, long& height)
{
	printf("Determing dimensions of bmp - GetBMPDimensions(FILE* fpBMP long& width, long& height)\n");

	BITMAPINFOHEADER bih;
	unsigned int kBfhSize = 14;
	unsigned int kBihSize = 40;
	BITMAPINFOHEADER* pBih = &bih;

	//Seek to beginning of bmp info header data
	fseek(fpBMP, kBfhSize, SEEK_SET);

	//Store BITMAPINFOHEADER data
	fread(pBih, kBihSize, 1, fpBMP);

	width = bih.biWidth;
	height = bih.biHeight;

	printf("Bmp width: %ld\n", width);
	printf("Bmp height: %ld\n", height);

	printf("\n");
}

//Store the data of a bmp as a virtual bmp
cPixel* cDSBmpUtility::ReadBMP(FILE* fpBMP)
{
	printf("Storing bmp Data into a virtual bmp. - ReadBMP(FILE*)\n");

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned int kBfhSize = 14;
	unsigned int kBihSize = 40;
	BITMAPFILEHEADER* pBfh = &bfh;
	BITMAPINFOHEADER* pBih = &bih;

	//Store BITMAPFILEHEADER data
	fread(pBfh, kBfhSize, 1, fpBMP);
	//Store BITMAPINFOHEADER data
	fread(pBih, kBihSize, 1, fpBMP);

	//If not pointing at bmp image data
	if(bfh.bfOffBits != (kBfhSize + kBihSize))
	{
		//Seek to beginning of bmp image data
		fseek(fpBMP, bfh.bfOffBits, SEEK_SET);
	}

	if(bih.biWidth != bih.biHeight)
	{
		printf("ERROR: Bmp width does not equal bmp height. Will attempt to proceed regardless. - ReadBMP(FILE*)\n");
	}

	cPixel* pBMP = NULL;
	if(CreateVirtualBMP(pBMP, bih.biWidth))
	{
		//Store image data into virtual bmp
		fread(pBMP, sizeof(cPixel), (bih.biWidth * bih.biHeight), fpBMP);
	}

	printf("\n");

	return pBMP;
}

void cDSBmpUtility::PrintBMPFileHeaderData(FILE* fpBMP)
{
	printf("Printing bmp file header data. - PrintBMPFileHeaderData(FILE*)\n");

	BITMAPFILEHEADER bfh;
	unsigned int kBfhSize = 14;
	BITMAPFILEHEADER* pBfh = &bfh;

	//Seek to beginning of bmp file header data
	fseek(fpBMP, 0, SEEK_SET);

	//Store BITMAPFILEHEADER data
	fread(pBfh, kBfhSize, 1, fpBMP);

	//print BITMAPFILEHEADER data
	printf("BITMAPFILEHEADER\n");
	printf("bfType: 0x%x\n", bfh.bfType);
	printf("bfSize: %d\n", bfh.bfSize);
	printf("bfReserved1: %d\n", bfh.bfReserved1);
	printf("bfReserved2: %d\n", bfh.bfReserved2);
	printf("bfOffBits: %d\n", bfh.bfOffBits);

	printf("\n");
}

void cDSBmpUtility::PrintBMPInfoHeaderData(FILE* fpBMP)
{
	printf("Printing bmp info header data. - PrintBMPInfoHeaderData(FILE*)\n");

	BITMAPINFOHEADER bih;
	unsigned int kBfhSize = 14;
	unsigned int kBihSize = 40;
	BITMAPINFOHEADER* pBih = &bih;

	//Seek to beginning of bmp info header data
	fseek(fpBMP, kBfhSize, SEEK_SET);

	//Store BITMAPINFOHEADER data
	fread(pBih, kBihSize, 1, fpBMP);

	//print BITMAPINFOHEADER data
	printf("BITMAPINFOHEADER\n");
	printf("biSize: %d\n", bih.biSize);
	printf("biWidth: %d\n", bih.biWidth);
	printf("biHeight: %d\n", bih.biHeight);
	printf("biPlanes: %d\n", bih.biPlanes);
	printf("biBitCount: %d\n", bih.biBitCount);
	printf("biCompression: %d\n", bih.biCompression);
	printf("biSizeImage: %d\n", bih.biSizeImage);
	printf("biXPelsPerMeter: %d\n", bih.biXPelsPerMeter);
	printf("biYPelsPerMeter: %d\n", bih.biYPelsPerMeter);
	printf("biClrUsed: %d\n", bih.biClrUsed);
	printf("biClrImportant: %d\n", bih.biClrImportant);

	printf("\n");
}

void cDSBmpUtility::PrintBMPHeaderData(FILE* fpBMP)
{
	PrintBMPFileHeaderData(fpBMP);
	PrintBMPInfoHeaderData(fpBMP);
}

void cDSBmpUtility::PrintBMPImageData(FILE* fpBMP)
{
	printf("Printing bmp image data. - PrintBMPImageData(FILE*)\n");

	BITMAPFILEHEADER bfh;
	BITMAPINFOHEADER bih;
	unsigned int kBfhSize = 14;
	unsigned int kBihSize = 40;
	BITMAPFILEHEADER* pBfh = &bfh;
	BITMAPINFOHEADER* pBih = &bih;

	//Seek to beginning of bmp data
	fseek(fpBMP, 0, SEEK_SET);

	//Store BITMAPFILEHEADER data
	fread(pBfh, kBfhSize, 1, fpBMP);
	//Store BITMAPINFOHEADER data
	fread(pBih, kBihSize, 1, fpBMP);

	printf("\n");

	printf("Printing bmp pixel data using the format:\n");
	printf("Pxl# = BU  : GN  : RD\n");

	//If not pointing at bmp image data
	if(bfh.bfOffBits != (kBfhSize + kBihSize))
	{
		//Seek to beginning of bmp image data
		fseek(fpBMP, bfh.bfOffBits, SEEK_SET);
	}

	for(int pixelCount = 0; pixelCount < bih.biSizeImage; ++pixelCount)
	{
		//For some reason the following line prints RGB instead of BGR
		//printf("%-5d= %-3u : %-3u : %-3u\n", pixelCount, fgetc(fpBMP), fgetc(fpBMP), fgetc(fpBMP));

		printf("%-5d= ", pixelCount);
		printf("%-3u : ", fgetc(fpBMP));
		printf("%-3u : ", fgetc(fpBMP));
		printf("%-3u\n", fgetc(fpBMP));
	}

	printf("\n");
}

//Print the data of a bmp
void cDSBmpUtility::PrintBMPData(FILE* fpBMP)
{
	printf("Printing bmp data. - PrintBMPData(FILE*)\n");

	PrintBMPHeaderData(fpBMP);
	PrintBMPImageData(fpBMP);

	printf("\n");
}

//-----------------------------------------------------------------------------

//Create a Square BMP with no default value
bool cDSBmpUtility::CreateVirtualBMP(cPixel*& pBMP, const int kSideLength)
{
	printf("Creating Virtual Square BMP with no default value. - CreateVirtualBMP(cPixel*&, const int)\n");

	if(!pBMP)
	{
		if(pBMP = new cPixel[kSideLength * kSideLength])
		{
			return true;
		}
		else
		{
			printf("ERROR: Could not allocate enough memory to create the grid. - CreateSquareGrid(cPixel*&, const int)\n");
			return false;
		}
	}
	else
	{
		printf("ERROR: pBMP is already pointing to something. - CreateVirtualBMP(cPixel*&, const int)\n");
	}

	printf("\n");
}

//Create a Square BMP with a default value
bool cDSBmpUtility::CreateVirtualBMP(cPixel*& pBMP, const int kSideLength, const cPixel kDefaultColour)
{
	printf("Creating Virtual Square BMP with a default value. - CreateVirtualBMP(cPixel*&, const int, const cPixel)\n");

	if(!pBMP)
	{
		if(pBMP = new cPixel[kSideLength * kSideLength])
		{
			cPixel* pTemp = pBMP;
			for(int i = 0; i < kSideLength * kSideLength; ++i)
			{
				pTemp->b = kDefaultColour.b;
				pTemp->g = kDefaultColour.g;
				pTemp->r = kDefaultColour.r;
				++pTemp;
			}

			return true;
		}
		else
		{
			printf("ERROR: Could not allocate enough memory to create the BMP. - CreateVirtualBMP(cPixel*&, const int, const cPixel)\n");
			return false;
		}
	}
	else
	{
		printf("ERROR: pBMP is already pointing to something. - CreateVirtualBMP(cPixel*&, const int, const cPixel)\n");
	}

	printf("\n");
}

//Create a Square BMP with a default value
bool cDSBmpUtility::CreateVirtualBMP(cPixel*& pBMP, const int kSideLength, const cPixel* pDefaultColour)
{
	printf("Creating Virtual Square BMP with a default value. - CreateVirtualBMP(cPixel*&, const int, const cPixel*)\n");

	if(!pBMP)
	{
		if(pBMP = new cPixel[kSideLength * kSideLength])
		{
			cPixel* pTemp = pBMP;
			for(int i = 0; i < kSideLength * kSideLength; ++i)
			{
				pTemp->b = pDefaultColour->b;
				pTemp->g = pDefaultColour->g;
				pTemp->r = pDefaultColour->r;
				++pTemp;
			}

			return true;
		}
		else
		{
			printf("ERROR: Could not allocate enough memory to create the BMP. - CreateVirtualBMP(cPixel*&, const int, const cPixel*)\n");
			return false;
		}
	}
	else
	{
		printf("ERROR: pBMP is already pointing to something. - CreateVirtualBMP(cPixel*&, const int, const cPixel*)\n");
	}

	printf("\n");
}

//Create a Square BMP with random values
bool cDSBmpUtility::CreateVirtualBMPRandomly(cPixel*& pBMP, const int kSideLength)
{
	printf("Creating Virtual Square BMP with random values. - CreateVirtualBMPRandomly(cPixel*&, const int)\n");

	if(!pBMP)
	{
		if(pBMP = new cPixel[kSideLength * kSideLength])
		{
			cPixel* pTemp = pBMP;

			for(int i = 0; i < kSideLength * kSideLength; ++i)
			{
				pTemp->b = rand() % 256;
				pTemp->g = rand() % 256;
				pTemp->r = rand() % 256;
				++pTemp;
			}

			return true;
		}
		else
		{
			printf("ERROR: Could not allocate enough memory to create the BMP. - CreateVirtualBMPRandomly(cPixel*&, const cPixel)\n");
			return false;
		}
	}
	else
	{
		printf("ERROR: pBMP is already pointing to something. - CreateVirtualBMPRandomly(cPixel*&, const int)\n");
	}

	printf("\n");
}

//Fill a BMP with the properties of a specific pixel object
void cDSBmpUtility::FillVirtualBMP(cPixel*& pBMP, const int kSideLength, const cPixel* pFillPixel)
{
	printf("Filling Virtual BMP with the properties of a specific pixel object. - FillVirtualBMP(cPixel*&, const int, const cPixel*)\n");

	//x = current column of row being used
	int x = 0;
	//y = current row of row being used
	int y = 0;

	while(x < kSideLength && y < kSideLength)
	{
		//Fill corner
		if(x == y)
		{
			FillVirtualPixelNode(pBMP, pFillPixel, x, y, kSideLength);
			++x;
		}

		//Early out after manipulating last node (bottom right corner)
		if(x >= kSideLength)
		{
			break;
		}
		//Fill right side of square except corner
		//row = row currently being manipulated in the x column
		for(int row = 0; row <= y; ++row)
		{
			FillVirtualPixelNode(pBMP, pFillPixel, x, row, kSideLength);
		}
		++y;

		//Fill under side of square except corner
		//column = column currently being manipulated in the y row
		for(int column = 0; column < x; ++column)
		{
			FillVirtualPixelNode(pBMP, pFillPixel, column, y, kSideLength);
		}
	}

	printf("\n");
}

//Fill a BMP with random values
void cDSBmpUtility::FillVirtualBMPRandomly(cPixel*& pBMP, const int kSideLength)
{
	printf("Filling Virtual BMP with random values. - FillVirtualBMPRandomly(cPixel*&, const int)\n");

	//x = current column of row being used
	int x = 0;
	//y = current row of row being used
	int y = 0;

	while(x < kSideLength && y < kSideLength)
	{
		//Fill corner
		if(x == y)
		{
			FillVirtualPixelNodeRandomly(pBMP, x, y, kSideLength);
			++x;
		}

		//Early out after manipulating last node (bottom right corner)
		if(x >= kSideLength)
		{
			break;
		}
		//Fill right side of square except corner
		//row = row currently being manipulated in the x column
		for(int row = 0; row <= y; ++row)
		{
			FillVirtualPixelNodeRandomly(pBMP, x, row, kSideLength);
		}
		++y;

		//Fill under side of square except corner
		//column = column currently being manipulated in the y row
		for(int column = 0; column < x; ++column)
		{
			FillVirtualPixelNodeRandomly(pBMP, column, y, kSideLength);
		}
	}

	printf("\n");
}

//Fill a pixel node in a square bmp using the properties of a pixel
void cDSBmpUtility::FillVirtualPixelNode(cPixel*& pPixel, const cPixel kFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a virtual square bmp. - FillVirtualPixelNode(cPixel*&, const cPixel, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = kFillData.b;
	pPixel[kY * (kSideLength) + kX ].g = kFillData.g;
	pPixel[kY * (kSideLength) + kX ].r = kFillData.r;
}

//Fill a pixel node in a square bmp using the properties of a pixel
void cDSBmpUtility::FillVirtualPixelNode(cPixel*& pPixel, const cPixel* const pFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a virtual square bmp. - FillVirtualPixelNode(cPixel*&, const cPixel* const, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = pFillData->b;
	pPixel[kY * (kSideLength) + kX ].g = pFillData->g;
	pPixel[kY * (kSideLength) + kX ].r = pFillData->r;
}

//Fill a pixel node in a square bmp randomly
void cDSBmpUtility::FillVirtualPixelNodeRandomly(cPixel*& pPixel, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a virtual square bmp. - FillVirtualPixelNodeRandomly(cPixel*&, const cPixel* const, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = rand() % 256;
	pPixel[kY * (kSideLength) + kX ].g = rand() % 256;
	pPixel[kY * (kSideLength) + kX ].r = rand() % 256;
}

void cDSBmpUtility::PrintVirtualBMPData(const cPixel* pBMP, const int kSideLength)
{
	printf("Printing Virtual BMP Data. - PrintVirtualBMPData(const cPixel*, const int)\n");

	printf("Printing virtual bmp pixel data using the format:\n");
	printf("Pxl# = BU  : GN  : RD\n");

	for(int pixelCount = 0; pixelCount < (kSideLength * kSideLength); ++pixelCount)
	{
		printf("%-5d= %-3u : %-3u : %-3u\n", pixelCount, pBMP->b, pBMP->g, pBMP->r);
		++pBMP;
	}

	printf("\n");
}

void cDSBmpUtility::CleanUpVirtualPixel(cPixel*& pPixel)
{
	delete pPixel;
	pPixel = NULL;
}

void cDSBmpUtility::CleanUpVirtualBMP(cPixel*& pBMP)
{
	delete[] pBMP;
	pBMP = NULL;
}

//-----------------------------------------------------------------------------

bool cDSBmpUtility::CreateSquareGrid(int*& pGrid, const int kSideLength)
{
	printf("Creating Square Grid with no default value. - CreateSquareGrid(int*&, const int)\n");

	if(pGrid = new int[kSideLength * kSideLength])
	{
		return true;
	}
	else
	{
		printf("ERROR: Could not allocate enough memory to create the grid. - CreateSquareGrid(int*&, const int)\n");
		return false;
	}

	printf("\n");
}

bool cDSBmpUtility::CreateSquareGrid(int*& pGrid, const int kSideLength, const int kDefaultValue)
{
	printf("Creating Square Grid with a default value. - CreateSquareGrid(int*&, const int, const int)\n");

	if(pGrid = new int[kSideLength * kSideLength])
	{
		int* pTemp = pGrid;
		for(int i = 0; i < kSideLength * kSideLength; ++i)
		{
			*pTemp = kDefaultValue;
			++pTemp;
		}

		return true;
	}
	else
	{
		printf("ERROR: Could not allocate enough memory to create the grid. - CreateSquareGrid(int*&, const int, const int)\n");
		return false;
	}

	printf("\n");
}

void cDSBmpUtility::FillSquareGrid(int*& pGrid, const int kSideLength)
{
	printf("Filling square grid. - FillSquareGrid(int*&, const int)\n");

	//x = current column of row being used
	int x = 0;
	//y = current row of row being used
	int y = 0;

	while(x < kSideLength && y < kSideLength)
	{
		//Fill corner
		if(x == y)
		{
			FillSquareNode(pGrid, 1, x, y, kSideLength);
			++x;
		}

		//Early out after manipulating last node (bottom right corner)
		if(x >= kSideLength)
		{
			break;
		}
		//Fill right side of square except corner
		//row = row currently being manipulated in the x column
		for(int row = 0; row <= y; ++row)
		{
			FillSquareNode(pGrid, 1, x, row, kSideLength);
		}
		++y;

		//Fill under side of square except corner
		//column = column currently being manipulated in the y row
		for(int column = 0; column < x; ++column)
		{
			FillSquareNode(pGrid, 1, column, y, kSideLength);
		}
	}

	printf("\n");
}

void cDSBmpUtility::FillSquareNode(int*& pGrid, const int kFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a node in a square grid. - FillNode(int*&, const int, const int, const int, const int)\n");
	pGrid[kY * (kSideLength) + kX ] = kFillData;
}

void cDSBmpUtility::PrintSquareGrid(const int* pGrid, const int kSideLength)
{
	printf("Printing a square grid. - PrintSquareGrid(const int*, const int)\n");

	for(int i = 1; i < (kSideLength * kSideLength) + 1; ++i)
	{
		printf("%d", *pGrid);
		++pGrid;

		//If done printing a row, move onto next row
		if(i % kSideLength == 0)
		{
			printf("\n");
		}
	}

	printf("\n");
}

void cDSBmpUtility::CleanUp(int*& pGrid)
{
	delete[] pGrid;
	pGrid = NULL;
}

//-----------------------------------------------------------------------------

void cDSBmpUtility::EnsurePositive(int& choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
}