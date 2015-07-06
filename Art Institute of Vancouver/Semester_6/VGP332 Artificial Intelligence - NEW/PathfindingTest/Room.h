//=================================================================================================
// File:		Room.h
// Created:		2012/09/05
// Last Edited:	2012/10/12
// Copyright:	Daniel Schenker
// Description	Abstract parent class that contains the basics of a room object.
//=================================================================================================

#ifndef INCLUDED_ROOM_H
#define INCLUDED_ROOM_H

//=================================================================================================
// Forward Declarations
//=================================================================================================

// SGE
class CSprite;
class CTexture;

//=================================================================================================
// Class Declarations
//=================================================================================================

class Room
{
public:
	//Constructors
	Room(const char* bgTexture);
	//Deconstructors
	virtual ~Room();

	// SGE Specific
	virtual void Render();

	// General
	virtual void RunPhysics() = 0;
	virtual int CheckRoomChange() = 0;

protected:
	//Graphics
	 //Background
	CSprite mBgSprite;
	CTexture mBgTexture;
};

#endif //INCLUDED_ROOM_H