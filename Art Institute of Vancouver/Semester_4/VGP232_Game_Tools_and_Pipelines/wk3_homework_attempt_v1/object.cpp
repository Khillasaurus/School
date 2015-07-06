//-----------------------------
// File:		object.cpp
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "object.h"

cObject::cObject()
:mVal(0)
{
}
//pre
cObject& cObject::operator ++()
{
	++mVal;// = (static_cast<Sint32>(InterlockedIncrement(reinterpret_cast<long volatile*>(&mVal))));
	return (*this);
}
//pre
cObject& cObject::operator --()
{
	--mVal;// = (static_cast<Sint32>(InterlockedDecrement(reinterpret_cast<long volatile*>(&mVal))));
	return (*this);
}