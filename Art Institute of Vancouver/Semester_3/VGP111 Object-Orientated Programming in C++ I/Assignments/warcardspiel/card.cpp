//-----------------------------
// File:		card.cpp
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "card.h"

cCard::cCard()
{
}

cCard::cCard(int _mSuit, int _mValue)
:	mSuit(_mSuit)
,	mValue(_mValue)
{
}

cCard::~cCard()
{
}