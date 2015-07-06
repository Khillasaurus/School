//====================================================================================================
//File:			cFrequencyElement.h
//Created:		2012/09/07
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CFREQUENCYELEMENT_H
#define CFREQUENCYELEMENT_H

//====================================================================================================
//Includes
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

//====================================================================================================
//Class Declarations
//====================================================================================================

class cFrequencyElement
{
public:
	//Constructors
	cFrequencyElement();
	cFrequencyElement(char letter, int priority);
	//Destructor
	~cFrequencyElement();

	//Overloaded operators
	bool operator < (const cFrequencyElement& frequencyElement) const;
	bool operator > (const cFrequencyElement& frequencyElement) const;

	//Member Functions
	 //General
	 //Getters
	char GetLetter() const;
	int GetPriority() const;
	 //Setters
	void SetLetter(char letter);
	void SetPriority(int priority);

protected:
	//Member Variables
	char mLetter;
	int mPriority;
};

#endif //CFREQUENCYELEMENT_H