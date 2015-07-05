//----------------------------
// File:		hero.cpp
// Created:		2012/1/13
// Copyright:	Daniel Schenker
//----------------------------

#include "stdafx.h"
#include "hero.h"

cHero::cHero()
{
	mHitPoints = kHeroMaxHitPoints;
}
cHero::~cHero()
{
}
void cHero::IssueChallenge()
{
	std::cout << "Avast! Tis now time for you Slime thing to uhm... DIE!!!" << std::endl;
}
void cHero::DisplayStats()
{
	std::cout << "Bob's HP: " << cHero::mHitPoints << std::endl;
	std::cout << std::endl;
}
bool cHero::Attack()
{
	Uint32 questionNumber = rand() % 3 + 1;
	Sint32 answer1 = 0;
	Sint32 answer2 = 0;
	Sint32 answer3 = 0;

	// hero attacks (answer question)
	//		ask question
	//		get input from player
	//		is answer correct
	//			yes == hit
	//			no == miss
	//		hero does damage (MAX)
	std::cout << "Answer the following riddle correctly and your warrior Bob will strike a mighty blow to the Slime!" << std::endl;
	std::cout << std::endl;
	switch( questionNumber )
	{
		case 1:
			std::cout << "Once upon a time there was an insurance salesman who was trying to sell insurance." << std::endl;
			std::cout << "He goes to a house and a woman answers." << std::endl;
			std::cout << "He starts taking to her about her family and asks if she has any kids, in hope that he can convince her to buy insurance from him." << std::endl;
			std::cout << "The woman replies: \"Yes I have three kids.\" and the insurance salesman asks: \"How old are they?\"" << std::endl;
			std::cout << "The woman responds: \"If you can guess the age of my children, I will buy your insurance.\"" << std::endl;
			
			std::cout << "The woman says: \"I have three children, the product of their ages is 36. If you add their ages together it is the number of the house next door.\"" << std::endl;
			std::cout << "So the salesman goes over, looks at the house next door's number, and comes back and says: \"I need one more clue.\"" << std::endl;
			std::cout << "The woman replies: \"My eldest daughter plays the piano.\"" << std::endl;

			std::cout << "How old are the children?" << std::endl;

			std::cout << "Please enter the ages of each child." << std::endl;
			std::cin >> answer1;
			std::cin >> answer2;
			std::cin >> answer3;

			if( answer1 == 9 || answer2 == 9 || answer3 == 9 )
			{
				if( (answer1 * answer2 * answer3) == 36 )
				{
					if( (answer1 + answer2 + answer3) == 13 )
					{
						std::cout << "Correct!" << std::endl;
						std::cout << std::endl;
						return true; // correct answer is 9, 2, 2
					}
					else
					{
						std::cout << "Sorry wrong answer. =(" << std::endl;
						std::cout << std::endl;
						return false;
					}
				}
				else
				{
					std::cout << "Sorry wrong answer. =(" << std::endl;
					std::cout << std::endl;
					return false;
				}
			}
			else
			{
				std::cout << "Sorry wrong answer. =(" << std::endl;
				std::cout << std::endl;
				return false;
			}
			break;

		case 2:
			std::cout << "You are on your way to visit your Grandma, who lives at the end of the valley." << std::endl;
			std::cout << "It's her birthday, and you want to give her the cakes you've made." << std::endl;
			std::cout << "Between your house and her house, you have to cross 7 bridges, and as it goes in the land of make believe, there is a troll under every bridge!" << std::endl;
			std::cout << "Each troll, quite rightly, insists that you pay a troll toll." << std::endl;
			std::cout << "Before you can cross their bridge, you have to give them half of the cakes you are carrying, but as they are kind trolls, they each give you back a single cake." << std::endl;
			std::cout << "How many cakes do you have to leave home with to make sure that you arrive at Grandma's with exactly 2 cakes?" << std::endl;
			
			std::cin >> answer1;
			if( answer1 == 2 )
			{
				std::cout << "Correct!" << std::endl;
				std::cout << std::endl;
				return true;
			}
			else
			{
				std::cout << "Sorry wrong answer. =(" << std::endl;
				std::cout << std::endl;
				return false;
			}
			break;

		case 3:
			std::cout << "Gretchen and Henry were looking to buy a house together, and finally found one with a beautifully landscaped yard, plenty of bedrooms, and a beautiful tree out front." << std::endl;
			std::cout << "They asked the owner how old the house was, and this was his reply:" << std::endl;
			std::cout << "\"I planted that tree when the house was built. It was 7 feet tall at the time. It has grown 3 feet each year, and at the end of this past full year, it was four times its original height.\"" << std::endl;
			std::cout << "\"But how old is the house?\" asked Henry." << std::endl;
			std::cout << "Gretchen said, \"Don\'t be so dense. He just told us.\"" << std::endl;
			std::cout << "How old is the house?" << std::endl;

			std::cin >> answer1;
			if( answer1 == 7 )
			{
				std::cout << "Correct!" << std::endl;
				std::cout << std::endl;
				return true;
			}
			else
			{
				std::cout << "Sorry wrong answer. =(" << std::endl;
				std::cout << std::endl;
				return false;
			}
			break;
	}
	std::cout << std::endl;
}
Uint32 cHero::DoDamage()
{
	// hero does damage (MAX)
	return kHeroMaxDamage;
}
void cHero::TakeDamage( Uint32 damage )
{
	// hero deflects some damage due to armour
	cUnit::TakeDamage( damage );
}
void cHero::VictoryDance()
{
	Uint8 learn;
	std::cout << "I can feel my power level rising... IT\'S OVER 9000!!!" << std::endl;
	std::cout << "Bob leveled up! Bob is trying to learn \"Fus Roh Dah\"!" << std::endl;
	std::cout << "Learn \"Fus Roh Dah\"?" << std::endl;
	std::cout << "Enter \'y\' for yes, \'n\' for no." << std::endl;
	std::cin >> learn;
	if( learn == 'Y' )
	{
		learn = 'y';
	}
	if( learn == 'y' )
	{
		std::cout << "While learning \"Fus Roh Dah\" Bob accidentaly blew up the planet. Bob is the new planet." << std::endl;
	}
	else
	{
		std::cout << "Lamesauce. Well bye now." << std::endl;
	}
}