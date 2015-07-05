//----------------------------
// File:		main.cpp
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "monster.h"
#include "hero.h"
#include <time.h>


int _tmain(int argc, _TCHAR* argv[])
{
	srand( (Uint32)time(NULL) );

	std::cout << "As Bob is walking along in the forest, he hears something just off the path..." << std::endl;
	std::cout << std::endl;

	// a monster
	cMonster slime;
	// a hero
	cHero bob;

	slime.IssueChallenge();
	bob.IssueChallenge();
	std::cout << std::endl;

	slime.DisplayStats();
	bob.DisplayStats();

	while( slime.IsAlive() && bob.IsAlive() )
	{
		if( slime.Attack() )
		{
			bob.TakeDamage( slime.DoDamage() );
			bob.DisplayStats();
		}
		if( bob.Attack() )
		{
			slime.TakeDamage( bob.DoDamage() );
			slime.DisplayStats();
		}
	}

	// survivor named the victor!
	if( slime.IsAlive() )
	{
		slime.VictoryDance();
	}
	else if( bob.IsAlive() )
	{
		bob.VictoryDance();
	}
	else
	{
		std::cout << "Both are dead. =(" << std::endl;
	}

	return 0;
}






//NOTES

// three features of c++
	// encapsulation
	// polymorphism
	// inheritance
