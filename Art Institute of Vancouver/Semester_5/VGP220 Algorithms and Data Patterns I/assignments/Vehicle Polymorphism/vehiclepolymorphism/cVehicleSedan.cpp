//====================================================================================================
//File:			cVehicleSedan.cpp
//Created:		2012/09/09
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Daniel Schenker
#include "cVehicle.h"
#include "cVehicleSedan.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cVehicleSedan::cVehicleSedan()
:	mVIN(0)
,	mMake("")
,	mModel("")
,	mMaxSpeed(0)
,	mServiceKM(0)
,	mHorsepower(0)
,	m4WD(false)
,	mWinch(false)
,	mLoadToCarry(0)
{
}

//----------------------------------------------------------------------------------------------------

cVehicleSedan::cVehicleSedan(int vin, char* make, char* model, int maxSpeed, int serviceKM, int horsepower, bool is4WD, bool winch, int loadToCarry)
:	mVIN(vin)
,	mMake(make)
,	mModel(model)
,	mMaxSpeed(maxSpeed)
,	mServiceKM(serviceKM)
,	mHorsepower(horsepower)
,	m4WD(is4WD)
,	mWinch(winch)
,	mLoadToCarry(loadToCarry)
{
}

//----------------------------------------------------------------------------------------------------
//Deconstructor
//----------------------------------------------------------------------------------------------------

cVehicleSedan::~cVehicleSedan()
{
}

//----------------------------------------------------------------------------------------------------
//Member Functions - General
//----------------------------------------------------------------------------------------------------

void cVehicleSedan::ShowName()
{
	printf("ShowName:\n   Make - %s\n   Model - %s\n   VIN - %d\n", mMake, mModel, mVIN);
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::HowFast()
{
	printf("The sedan can go %dkm/h\n", mMaxSpeed);
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::NeedService()
{
	printf("The sedan will need service at %dkm.\n", mServiceKM);
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::Horsepower()
{
	printf("The sedan's horsepower is %d.\n", mHorsepower);
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::Show4WD()
{
	if(m4WD)
	{
		printf("The sedan has 4 wheel drive.\n");
	}
	else
	{
		printf("The sedan does not have 4 wheel drive.\n");
	}
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::ShowWinch()
{
	if(mWinch)
	{
		printf("The sedan has a winch.\n");
	}
	else
	{
		printf("The sedan does not have a winch.\n");
	}
}

//----------------------------------------------------------------------------------------------------

void cVehicleSedan::ShowLoadToCarry()
{
	printf("The sedan can carry %dkg.\n", mLoadToCarry);
}