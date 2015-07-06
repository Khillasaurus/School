//====================================================================================================
//File:			cVehicleSedan.h
//Created:		2012/09/09
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CVEHICLESEDAN_H
#define CVEHICLESEDAN_H

//====================================================================================================
//Includes
//====================================================================================================

//Daniel Schenker
#include "cVehicle.h"

//====================================================================================================
//Class Declarations
//====================================================================================================

class cVehicleSedan : public cVehicle
{
public:
	//Constructors
	cVehicleSedan();
	cVehicleSedan(int vin, char* make, char* model, int maxSpeed, int serviceKM, int horsepower, bool is4WD, bool winch, int loadtoCarry);
	//Deconstructors
	virtual ~cVehicleSedan();

	//Overloaded Operators

	//Member Functions
	 //General
	virtual void ShowName();
	virtual void HowFast();
	virtual void NeedService();
	virtual void Horsepower();
	virtual void Show4WD();
	virtual void ShowWinch();
	virtual void ShowLoadToCarry();

protected:
	//Member Variables
	int mVIN;
	char* mMake;
	char* mModel;
	int mMaxSpeed;
	int mServiceKM;
	int mHorsepower;
	bool m4WD;
	bool mWinch;
	int mLoadToCarry;
};

#endif //CVEHICLESEDAN_H