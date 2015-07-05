// file:	vgptypes.h
// created: 2011/10/14
//

#ifndef __cCharacter_H
#define __cCharacter_H

class cCharacter //same as struct but private
{
public:
	void Buff();

private:
	Uint32 strength;
	Uint32 dexterity;
	Uint32 intelligence;
};

#endif // __cCharacter_H