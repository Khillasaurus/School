//----------------------------
// File:		combat.cpp
// Created:		2012/1/20
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "combat.h"
#include "unit.h"


cCombat::cCombat()
:	mpFirstUnit(NULL)
,	mpSecondUnit(NULL)
{
}
cCombat::cCombat( cUnit *pUnitA, cUnit *pUnitB )
:	mpFirstUnit(pUnitA)
,	mpSecondUnit(pUnitB)
{
}
cCombat::~cCombat()
{
	delete mpFirstUnit;
	delete mpSecondUnit;
}




void cCombat::AddCombatants( cUnit* pFirstUnit, cUnit* pSecondUnit )
{
	mpFirstUnit = pFirstUnit;
	mpSecondUnit = pSecondUnit;
}




void cCombat::Announce()
{
	mpFirstUnit->IssueChallenge();
	mpSecondUnit->IssueChallenge();
	std::cout << std::endl;
}




void cCombat::Fight()
{
	while( mpFirstUnit->IsAlive() && mpSecondUnit->IsAlive() )
	{
		cCombat::AttackEachOther();
	}
}




void cCombat::AttackEachOther()
{
	//TODO : determine who attacks first by initiative
	if( mpFirstUnit->Attack() )
	{
		mpSecondUnit->TakeDamage( mpFirstUnit->DoDamage() );
		mpSecondUnit->DisplayStats();
	}
	// if IsAlive || !IsAlive && HasPartingShotAbility()
	if( mpSecondUnit->Attack() )
	{
		mpFirstUnit->TakeDamage( mpSecondUnit->DoDamage() );
		mpFirstUnit->DisplayStats();
	}
}




void cCombat::Information()
{
	mpFirstUnit->DisplayStats();
	mpSecondUnit->DisplayStats();
	std::cout << std::endl;
}




void cCombat::SurvivorVictoryDance()
{
	if( mpFirstUnit->IsAlive() )
	{
		mpFirstUnit->VictoryDance();
	}
	else if( mpSecondUnit->IsAlive() )
	{
		mpSecondUnit->VictoryDance();
	}
	else
	{
		std::cout << "Both are dead. =(" << std::endl;
	}
}