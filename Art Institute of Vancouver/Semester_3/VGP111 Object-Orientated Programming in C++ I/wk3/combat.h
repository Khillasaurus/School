//----------------------------
// File:		combat.h
// Created:		2012/1/20
// Copyright:	Daniel Schenker
//----------------------------

#ifndef __cCombat_h
#define __cCombat_h

//forward declaration
class cUnit;

class cCombat
{
public:
cCombat();
cCombat( cUnit *pUnitA, cUnit *pUnitB );
~cCombat();

	void AddCombatants( cUnit* pFirstUnit, cUnit* pSecondUnit );
	void Announce();
	void Fight();
	void AttackEachOther();
	void Information();
	void SurvivorVictoryDance();

	cUnit *mpFirstUnit;
	cUnit *mpSecondUnit;
};

#endif // __cUnit_h