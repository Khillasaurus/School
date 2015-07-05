//----------------------------
// File:		card.h
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//----------------------------

#ifndef __cCard_h
#define __cCard_h

class cCard
{
public:
	cCard();// default constructor
	~cCard();// destructor
protected:
	Sint32 mSuit;//0 hearts, 1 spades, 2 diamonds, 3 clubs
	Sint32 mValue;//ace = 1, 2-10, jack-king = 11-13
};


#endif // __cCard_h
