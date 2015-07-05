//----------------------------
// File:		hero.h
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#ifndef __cHero_h
#define __cHero_h

#include "unit.h"

class cHero : public cUnit
{
public:
	enum
	{
		kHeroMaxHitPoints = 100,
		kHeroMaxDamage = 350
	};
public:
	cHero();
	~cHero();
public:	// cUnit
	virtual void IssueChallenge();
	virtual void DisplayStats();
	virtual bool Attack();
	virtual Uint32 DoDamage();
	virtual void TakeDamage( Uint32 damage );
	virtual void VictoryDance();
};



#endif // __cHero_h