//----------------------------
// File:		monster.cpp
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "monster.h"

cMonster::cMonster()
{
	mHitPoints = kMonsterHitPoints;
}
cMonster::~cMonster()
{
}
void cMonster::IssueChallenge()
{
	std::cout << "RAUAHRUruahGuGhhh" << std::endl;
}
void cMonster::DisplayStats()
{
	std::cout << "Slime's HP: " << cMonster::mHitPoints << std::endl;
	std::cout << std::endl;
}
bool cMonster::Attack()
{
	// monster attacks (%chance)
	Uint32 chance = rand() % 2;
	std::cout << "Slime uses gooball!" << std::endl;
	if( chance > 0 )
	{
		std::cout << "Bob is hit!" << std::endl;
		std::cout << std::endl;
		return true;
	}
	else
	{
		std::cout << "Slime misses." << std::endl;
		std::cout << std::endl;
		return false;
	}
}
Uint32 cMonster::DoDamage()
{
	// monster does damage (1-N)
	return ( (rand() % 40) + 10 );
}
void cMonster::TakeDamage( Uint32 damage )
{
	// monster deflects some damage due to natural defences
	cUnit::TakeDamage( damage );
}
void cMonster::VictoryDance()
{
	std::cout << "Splish Splash Splish Gloop" << std::endl;
	std::cout << "Slime leveled up! Slime is evolving..." << std::endl;
	std::cout << "Slime has evolved into Slime King!" << std::endl;
	std::cout << "Bob is dead. Poor Bob." << std::endl;
}