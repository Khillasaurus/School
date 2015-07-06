//------------------------------------------
// File:		bitmap_terrain_generator.cpp
// Created:		2012/06/04
// Copyright:	Daniel Schenker
//------------------------------------------

#include "stdafx.h"
//#include <cstdlib>

//=---Function Prototypes---=
 //TEST
void Test1a();																			//DONE
void Test1b();																			//DONE
void Test1c();																			//DONE
void Test1d();																			//DONE
void Test2();																			//DONE
void Test3();																			//DONE
 //-BMP-																				//---
void MakeBMP(const char*, const int, cPixel*);											//WORKS
 //-PIXEL-																				//---
  //CreateBMP
bool CreateBMP(cPixel*&, const int);													//DONE
bool CreateBMP(cPixel*&, const int, const cPixel);										//DONE
bool CreateBMP(cPixel*&, const int, const cPixel*);										//DONE
bool CreateBMPRandomly(cPixel*&, const int);											//DONE
  //FillBMP
void FillBMP(cPixel*&, const int, const cPixel*);										//DONE
void FillBMPRandomly(cPixel*&, const int);												//DONE
  //FillPixelNode
void FillPixelNode(cPixel*&, const cPixel, const int, const int, const int);			//DONE
void FillPixelNode(cPixel*&, const cPixel* const, const int, const int, const int);		//DONE
void FillPixelNodeRandomly(cPixel*&, const int, const int, const int);					//DONE
  //PrintBMP
void PrintBMP(const cPixel*, const int);												//DONE
  //CleanUp
void CleanUpPixel(cPixel*&);															//DONE
void CleanUpBMP(cPixel*&);																//DONE
 //-INT-																				//---
bool CreateSquareGrid(int*&, const int);												//DONE
bool CreateSquareGrid(int*&, const int, const int);										//DONE
void FillSquareGrid(int*&, const int);													//DONE
void FillSquareNode(int*&, const int, const int, const int, const int);					//DONE
void PrintSquareGrid(const int*, const int);											//DONE
void CleanUp(int*&);																	//DONE
 //-UTILITY-																			//---
void EnsurePositive(int&);																//DONE

int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize Rand Seed
	srand((unsigned)time(NULL));

	Test3();

	return 0;
}

//Create a grid with a default initial value and default final value
void Test1a()
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
}

//Create a BMP with a default initial value and default final value
void Test1b()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;

	//Temporary Variables (Remove Later)
	cPixel* pPixelInitial = new cPixel(32);
	cPixel* pPixelFinal = new cPixel(128);
	
	if(CreateBMP(pBMP, kSideLength, pPixelInitial))
	{
		printf("The new BMP:\n");
		PrintBMP(pBMP, kSideLength);
		FillBMP(pBMP, kSideLength, pPixelFinal);
	}
	printf("The grid filled using my algorithm:\n");
	PrintBMP(pBMP, kSideLength);
	CleanUpBMP(pBMP);

	//Temporary (Remove Later)
	CleanUpPixel(pPixelInitial);
	CleanUpPixel(pPixelFinal);
}

//Create a BMP with a default initial value and random final value
void Test1c()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;

	//Temporary Variables (Remove Later)
	cPixel* pPixelInitial = new cPixel(32);
	
	if(CreateBMP(pBMP, kSideLength, pPixelInitial))
	{
		printf("The new BMP:\n");
		PrintBMP(pBMP, kSideLength);
		FillBMPRandomly(pBMP, kSideLength);
	}
	printf("The grid filled using my algorithm:\n");
	PrintBMP(pBMP, kSideLength);
	CleanUpBMP(pBMP);

	//Temporary (Remove Later)
	CleanUpPixel(pPixelInitial);
}

//Create a BMP with a random initial value and random final value
void Test1d()
{
	cPixel* pBMP = NULL;
	const int kSideLength = 4;
	
	if(CreateBMPRandomly(pBMP, kSideLength))
	{
		printf("The new BMP:\n");
		PrintBMP(pBMP, kSideLength);
		FillBMPRandomly(pBMP, kSideLength);
	}
	printf("The grid filled using my algorithm:\n");
	PrintBMP(pBMP, kSideLength);
	CleanUpBMP(pBMP);
}

//Access and modify the properties of a pixel object
void Test2()
{
	cPixel* pPixelWhite = new cPixel();
	cPixel* pPixelGreyscale = new cPixel(64);
	cPixel* pPixelColour = new cPixel(128, 128, 128);

	printf("White Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelWhite->b, pPixelWhite->g, pPixelWhite->r);
	printf("Greyscale Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelGreyscale->b, pPixelGreyscale->g, pPixelGreyscale->r);
	printf("Colour Pixel:\n");
	printf("B: %u, G: %u, R: %u\n", pPixelColour->b, pPixelColour->g, pPixelColour->r);

	delete pPixelWhite;
	pPixelWhite = NULL;
	delete pPixelGreyscale;
	pPixelGreyscale = NULL;
	delete pPixelColour;
	pPixelColour = NULL;
}

//Create a bmp with a random initial value and save it as a *.bmp file
void Test3()
{
	cPixel* pBMP = NULL;

	//Query bmp sideLength
	int sideLength = 0;
	printf("How long would you like the side length of the square bmp to be?\n");
	scanf("%d", &sideLength);
	EnsurePositive(sideLength);
	const int kSideLength = sideLength;
	
	//If a randomly generated bmp was created succesfully
	if(CreateBMPRandomly(pBMP, kSideLength))
	{
		//Query BMP file name
		char fileName[256] = "";
		char* pFileName = &fileName[0];
		printf("What would you like the file name of the bmp to be? (file extension not needed)\n");
		scanf("%s", pFileName);

		//Print the new bmp
		printf("The new bmp:\n");
		printf("Name: %s\tSide Length:%d\n", pFileName, kSideLength);
		PrintBMP(pBMP, kSideLength);
		printf("\n");

		//Use the virtual bmp to create a real bmp file
		MakeBMP(pFileName, kSideLength, pBMP);
	}
	CleanUpBMP(pBMP);
}

//Create a BMP file from specified virtual bmp data
void MakeBMP(const char* kFileName, const int kSideLength, cPixel* pBMPData)
{
	printf("Creating a BMP file from specified virtual bmp data. - MakeBMP(const char*, const int, const cPixel*)\n");

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

//Create a Square BMP with no default value
bool CreateBMP(cPixel*& pBMP, const int kSideLength)
{
	printf("Creating Square BMP with no default value. - CreateBMP(cPixel*&, const int)\n");

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

//Create a Square BMP with a default value
bool CreateBMP(cPixel*& pBMP, const int kSideLength, const cPixel kDefaultColour)
{
	printf("Creating Square BMP with a default value. - CreateBMP(cPixel*&, const int, const cPixel)\n");

	if(pBMP = new cPixel[kSideLength * kSideLength])
	{
		cPixel* pTemp = pBMP;
		for(int i = 0; i < kSideLength * kSideLength; ++i)
		{
			pTemp->b = kDefaultColour.b;
			pTemp->g = kDefaultColour.g;
			pTemp->r = kDefaultColour.r;
			++pTemp;

			//testing making part of bmp a different colour
			if(i > (kSideLength*2))
			{
				pTemp->b = 100;
				pTemp->g = 100;
				pTemp->r = 100;
			}
		}

		return true;
	}
	else
	{
		printf("ERROR: Could not allocate enough memory to create the BMP. - CreateBMP(cPixel*&, const int, const cPixel)\n");
		return false;
	}
}

//Create a Square BMP with a default value
bool CreateBMP(cPixel*& pBMP, const int kSideLength, const cPixel* kDefaultColour)
{
	printf("Creating Square BMP with a default value. - CreateBMP(cPixel*&, const int, const cPixel*)\n");

	if(pBMP = new cPixel[kSideLength * kSideLength])
	{
		cPixel* pTemp = pBMP;
		for(int i = 0; i < kSideLength * kSideLength; ++i)
		{
			pTemp->b = kDefaultColour->b;
			pTemp->g = kDefaultColour->g;
			pTemp->r = kDefaultColour->r;
			++pTemp;
		}

		return true;
	}
	else
	{
		printf("ERROR: Could not allocate enough memory to create the BMP. - CreateBMP(cPixel*&, const int, const cPixel*)\n");
		return false;
	}
}

//Create a Square BMP with random values
bool CreateBMPRandomly(cPixel*& pBMP, const int kSideLength)
{
	printf("Creating Square BMP with random values. - CreateBMPRandomly(cPixel*&, const int)\n");

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
		printf("ERROR: Could not allocate enough memory to create the BMP. - CreateBMP(cPixel*&, const int, const cPixel)\n");
		return false;
	}
}

//Fill a BMP with the properties of a specific pixel object
void FillBMP(cPixel*& pBMP, const int kSideLength, const cPixel* pFillPixel)
{
	printf("Filling BMP with the properties of a specific pixel object. - FillBMP(cPixel*&, const int, const cPixel*)\n");

	//x = current column of row being used
	int x = 0;
	//y = current row of row being used
	int y = 0;

	while(x < kSideLength && y < kSideLength)
	{
		//Fill corner
		if(x == y)
		{
			FillPixelNode(pBMP, pFillPixel, x, y, kSideLength);
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
			FillPixelNode(pBMP, pFillPixel, x, row, kSideLength);
		}
		++y;

		//Fill under side of square except corner
		//column = column currently being manipulated in the y row
		for(int column = 0; column < x; ++column)
		{
			FillPixelNode(pBMP, pFillPixel, column, y, kSideLength);
		}
	}
}

//Fill a BMP with random values
void FillBMPRandomly(cPixel*& pBMP, const int kSideLength)
{
	printf("Filling BMP with random values. - FillBMPRanodmly(cPixel*&, const int)\n");

	//x = current column of row being used
	int x = 0;
	//y = current row of row being used
	int y = 0;

	while(x < kSideLength && y < kSideLength)
	{
		//Fill corner
		if(x == y)
		{
			FillPixelNodeRandomly(pBMP, x, y, kSideLength);
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
			FillPixelNodeRandomly(pBMP, x, row, kSideLength);
		}
		++y;

		//Fill under side of square except corner
		//column = column currently being manipulated in the y row
		for(int column = 0; column < x; ++column)
		{
			FillPixelNodeRandomly(pBMP, column, y, kSideLength);
		}
	}
}

//Fill a pixel node in a square bmp using the properties of a pixel
void FillPixelNode(cPixel*& pPixel, const cPixel kFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a square bmp. - FillPixelNode(cPixel*&, const cPixel, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = kFillData.b;
	pPixel[kY * (kSideLength) + kX ].g = kFillData.g;
	pPixel[kY * (kSideLength) + kX ].r = kFillData.r;
}

//Fill a pixel node in a square bmp using the properties of a pixel
void FillPixelNode(cPixel*& pPixel, const cPixel* const pFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a square bmp. - FillPixelNode(cPixel*&, const cPixel* const, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = pFillData->b;
	pPixel[kY * (kSideLength) + kX ].g = pFillData->g;
	pPixel[kY * (kSideLength) + kX ].r = pFillData->r;
}

//Fill a pixel node in a square bmp randomly
void FillPixelNodeRandomly(cPixel*& pPixel, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a pixel node in a square bmp. - FillPixelNode(cPixel*&, const cPixel* const, const int, const int, const int)\n");
	pPixel[kY * (kSideLength) + kX ].b = rand() % 256;
	pPixel[kY * (kSideLength) + kX ].g = rand() % 256;
	pPixel[kY * (kSideLength) + kX ].r = rand() % 256;
}

void PrintBMP(const cPixel* pBMP, const int kSideLength)
{
	//system("CLS");
	printf("Printing a BMP. - PrintBMP(const cPixel*, const int)\n");

	for(int i = 1; i < (kSideLength * kSideLength) + 1; ++i)
	{
		printf("%u, %u, %u", pBMP->b, pBMP->g, pBMP->r);
		++pBMP;

		//If done printing a row, move onto next row
		if(i % kSideLength == 0)
		{
			printf("\n");
		}
		else
		{
			printf(" :\t");
		}
	}
	//DWORD dwMilliseconds = 100;
	//Sleep(dwMilliseconds);
}

void CleanUpPixel(cPixel*& pPixel)
{
	delete pPixel;
	pPixel = NULL;
}

void CleanUpBMP(cPixel*& pBMP)
{
	delete[] pBMP;
	pBMP = NULL;
}

bool CreateSquareGrid(int*& pGrid, const int kSideLength)
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
}

bool CreateSquareGrid(int*& pGrid, const int kSideLength, const int kDefaultValue)
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
}

void FillSquareGrid(int*& pGrid, const int kSideLength)
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
}

void FillSquareNode(int*& pGrid, const int kFillData, const int kX, const int kY, const int kSideLength)
{
	//printf("Filling a node in a square grid. - FillNode(int*&, const int, const int, const int, const int)\n");
	pGrid[kY * (kSideLength) + kX ] = kFillData;
}

void PrintSquareGrid(const int* pGrid, const int kSideLength)
{
	//system("CLS");
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
	//DWORD dwMilliseconds = 100;
	//Sleep(dwMilliseconds);
}

void CleanUp(int*& pGrid)
{
	delete[] pGrid;
	pGrid = NULL;
}

void EnsurePositive(int& choice)
{
	while(choice < 0)
	{
		printf("Invalid option. You must enter a positive value.\n");
		printf("Please choose again.\n");
		scanf("%d", choice);
	}
}