//-----------------------------
// File:		player.h
// Created:		2012/2/10
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __PLAYER_H
#define __PLAYER_H

//forward decl
class cCard;

class cPlayer
{
public:
	cPlayer();
	~cPlayer();
public:
	int mScore;
	deque<cCard*> mList;
public:
	void Init();
};

#endif // __PLAYER_H