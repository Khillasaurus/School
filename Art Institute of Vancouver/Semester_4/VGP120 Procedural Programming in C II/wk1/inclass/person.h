//-----------------------------
// File:		person.h
// Created:		2012/04/05
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __PERSON_H
#define __PERSON_H

class cPerson
{
public:
	cPerson();
	~cPerson();
public:
	int mAge;
	float mHeight;
public:
	void Init();
	void DisplayData();
};

#endif //__PERSON_H