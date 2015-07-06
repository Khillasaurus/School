//-----------------------------
// File:		object.h
// Created:		2012/04/21
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __OBJECT_H
#define __OBJECT_H

class cObject
{
public:
	cObject();
	cObject& operator ++();
	cObject& operator --();

	volatile Sint32 mVal;
};

#endif	//__OBJECT_H