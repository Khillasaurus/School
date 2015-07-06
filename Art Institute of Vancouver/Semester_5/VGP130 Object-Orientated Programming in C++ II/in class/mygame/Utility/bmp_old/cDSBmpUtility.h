//====================================================================================================
// File:		cDSBmpUtility.h
// Created:		2012/06/04	-	v1
// Version:		2012/08/16	-	v2
// Copyright:	Daniel Schenker
//====================================================================================================

#ifndef __CDSBMPUTILITY_H
#define __CDSBMPUTILITY_H

//====================================================================================================
// Includes
//====================================================================================================

#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "virtualpixel.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class cDSBmpUtility
{
public:
	//-Test-
	static void Test1CreateGridDefDef();
	static void Test2aCreateVirtualBMPDefDef();
	static void Test2bCreateVirtualBMPDefRan();
	static void Test2cCreateVirtualBMPRanRan();
	static void Test3ModifyPixel();
	static void Test4CreateBMPRandomly();
	static void Test5DisplayBMPData();
	static void Test6StoreBMPData();

	//-Usage-
	static void ChopBMP(const char*, const int, const int);

	//-BMP-
	static void CreateBMP(const char*, const int, cPixel*);
	static void GetBMPDimensions(FILE*, int&, int&);
	static void GetBMPDimensions(FILE*, long&, long&);
	static cPixel* ReadBMP(FILE*);
	static void PrintBMPFileHeaderData(FILE*);
	static void PrintBMPInfoHeaderData(FILE*);
	static void PrintBMPHeaderData(FILE*);
	static void PrintBMPImageData(FILE*);
	static void PrintBMPData(FILE* fpBMP);

	//-VIRTUAL PIXEL-
	 //CreateBMP
	static bool CreateVirtualBMP(cPixel*&, const int);
	static bool CreateVirtualBMP(cPixel*&, const int, const cPixel);
	static bool CreateVirtualBMP(cPixel*&, const int, const cPixel*);
	static bool CreateVirtualBMPRandomly(cPixel*&, const int);
	 //FillBMP
	static void FillVirtualBMP(cPixel*&, const int, const cPixel*);
	static void FillVirtualBMPRandomly(cPixel*&, const int);
	 //FillPixelNode
	static void FillVirtualPixelNode(cPixel*&, const cPixel, const int, const int, const int);
	static void FillVirtualPixelNode(cPixel*&, const cPixel* const, const int, const int, const int);
	static void FillVirtualPixelNodeRandomly(cPixel*&, const int, const int, const int);
	 //PrintBMP
	static void PrintVirtualBMPData(const cPixel*, const int);
	 //CleanUp
	static void CleanUpVirtualPixel(cPixel*&);
	static void CleanUpVirtualBMP(cPixel*&);

	//-INT-
	static bool CreateSquareGrid(int*&, const int);
	static bool CreateSquareGrid(int*&, const int, const int);
	static void FillSquareGrid(int*&, const int);
	static void FillSquareNode(int*&, const int, const int, const int, const int);
	static void PrintSquareGrid(const int*, const int);
	static void CleanUp(int*&);

	 //-UTILITY-
	static void EnsurePositive(int&);
};

#endif //__CDSBMPUTILITY_H