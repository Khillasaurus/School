//----------------------------
// File:		main.cpp
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "monster.h"
#include "hero.h"
#include "combat.h"
#include <time.h>

//function prototypes----------------------------
void Introduction();
//-----------------------------------------------


int _tmain(int argc, _TCHAR* argv[])
{
	srand( (Uint32)time(NULL) );

	Introduction();

	cUnit* pMonster;
	cUnit* pHero;
	pMonster = new cMonster();
	pHero = new cHero();

	cCombat* pCombat = new cCombat( pMonster, pHero );
	if( pCombat )
	{
		pCombat->Announce();
		pCombat->Information();
		pCombat->Fight();
		pCombat->SurvivorVictoryDance();
		
		delete pCombat;
	}

	return 0;
}


void Introduction()
{
	std::cout << "As Bob is walking along in the forest, he hears something just off the path..." << std::endl;
	std::cout << std::endl;
}






//NOTES

// three features of c++
	// encapsulation
	// polymorphism
	// inheritance
