//-----------------------------
// File:		card.h
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __CARD_H
#define __CARD_H

class cCard
{
public:
	cCard();
	cCard(int mSuit, int mValue);
	~cCard();
public:
	int mSuit;//0 hearts, 1 spades, 2 diamonds, 3 clubs
	int mValue;// 2-10 = 0-8, jack-king = 9-11, ace = 12,
};

#endif // __CARD_H