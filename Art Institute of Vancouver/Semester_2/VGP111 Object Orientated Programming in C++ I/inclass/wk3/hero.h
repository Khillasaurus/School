// file:	vgptypes.h
// created: 2011/10/14
//

#ifndef __cHero_H
#define __cHero_H

#include "character.h"

class cHero : public cCharacter	//almost always public, if not explain why to yourself so you don't get confused
{
public:
	void Yell()
	{
		cout << "RAAAAAGHHH" << endl;
	}
};

#endif // __cHero_H