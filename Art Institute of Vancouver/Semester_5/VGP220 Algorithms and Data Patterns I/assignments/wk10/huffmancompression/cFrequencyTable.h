//====================================================================================================
//File:			cFrequencyTable.h
//Created:		2012/09/07
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef CFREQUENCYTABLE_H
#define CFREQUENCYTABLE_H

//====================================================================================================
//Includes
//====================================================================================================

#include <queue>

//====================================================================================================
// Forward Declarations
//====================================================================================================

class cFrequencyElement;

//====================================================================================================
//Class Declarations
//====================================================================================================

template< class Type, class Container = vector<Type>, class Compare = less<typename Container::value_type> >
class cFrequencyTable
{
public:
	//Constructors
	cFrequencyTable();
	//Destructor
	~cFrequencyTable();

	//Member Functions
	 //General
	 //Getters
	 //Setters

protected:
	//Member Variables
	std::priority_queue<cFrequencyElement, std::vector<cFrequencyElement>,std::less<std::vector<cFrequencyElement>::value_type> > pData;
};

#endif //CFREQUENCYTABLE_H