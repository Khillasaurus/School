//====================================================================================================
//File:			cActualData.h
//Created:		2012/09/10
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CACTUALDATA_H
#define CACTUALDATA_H

//====================================================================================================
//Class Declarations
//====================================================================================================

class cActualData
{
public:
	//Constructors
	cActualData(char* sentence);
	//Deconstructors
	~cActualData();

	//Member Functions
	 //General
	 //Getters
	 //Setters

	//Member Data
	 //General
	char mSentence[256];
};

#endif //CACTUALDATA_H