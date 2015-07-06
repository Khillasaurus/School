//====================================================================================================
//File:			cSmartPointer.h
//Created:		2012/09/10
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CSMARTPOINTER_H
#define CSMARTPOINTER_H

//====================================================================================================
// Forward Declarations
//====================================================================================================

class cActualData;

//====================================================================================================
//Class Declarations
//====================================================================================================

class cSmartPointer
{
public:
	//Constructors
	cSmartPointer(char* sentence);
	//Deconstructors
	~cSmartPointer();

	//Member Functions
	 //General
	void PrintData() const;
	 //Getters
	 //Setters

	//Member Data
	 //General
	cActualData* pActualData;
};

#endif //CSMARTPOINTER_H