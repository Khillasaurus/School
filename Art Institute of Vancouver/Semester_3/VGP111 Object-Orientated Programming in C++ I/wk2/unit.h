//----------------------------
// File:		unit.h
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#ifndef __cUnit_h
#define __cUnit_h

class cUnit
{
public:
	virtual ~cUnit(){}
public:
	virtual void IssueChallenge() = 0;
	virtual void DisplayStats() = 0;
	virtual bool Attack() = 0;
	virtual Uint32 DoDamage() = 0;
	virtual void TakeDamage( Uint32 damage )
	{
		mHitPoints -= damage;
	}
	virtual bool IsAlive()
	{
		return( mHitPoints > 0 );
	}
	virtual void VictoryDance() = 0;

protected:
	Sint32 mHitPoints;
};

#endif // __cUnit_h