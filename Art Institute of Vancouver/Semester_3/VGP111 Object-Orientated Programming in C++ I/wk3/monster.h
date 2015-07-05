//----------------------------
// File:		monster.h
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#ifndef __cMonster_h
#define __cMonster_h

#include "unit.h"

class cMonster : public cUnit
{
public:
	enum
	{
		kMonsterHitPoints = 1000
	};
public:
	// upon declaration
	//	eg:	cMonster slime;
	cMonster();										// default constructor

	// upon declaration
	//	eg:	cMonster slimeB( slime );
	//cMonster( const cMonster &rhs );				// copy constructor

	// upon destruction or exit of scope
	// eg:	{
	//			cMonster slime;
	//		} // at exit of scope, slime.~cMonster();
	//			// slime is gone
	virtual ~cMonster();									// destructor

	// eg: slimeb = slime;
	// inefficient eg: cMonster slimec = cMonster();
	//cMonster &operator = ( const cMOnster &rhs );	//assignment operator

public: // cUnit
	virtual void IssueChallenge();
	virtual void DisplayStats();
	virtual bool Attack();
	virtual Uint32 DoDamage();
	virtual void TakeDamage( Uint32 damage );
	virtual void VictoryDance();
};


#endif // __cMonster_h
