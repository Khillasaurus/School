// file:	vgptypes.h
// created: 2011/10/14
//

#ifndef __cMonster_H
#define __cMonster_H

#include "character.h"

class cMonster : public cCharacter	//almost always public, if not explain why to yourself so you don't get confused
{
public:
	void Yell();
};

#endif // __cMonster_H