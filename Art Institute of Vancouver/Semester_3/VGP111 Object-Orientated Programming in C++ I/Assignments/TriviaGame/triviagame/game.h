//-----------------------------
// File:		game.h
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __GAME_H
#define __GAME_H

const Uint32 kAmountOfQuestions = 9;

//Forward Declaration
class cQuestion;

class cGame
{
//----------SPECIAL MEMBER FUNCTIONS----------
public:
	cGame();
	cGame(bool);
	~cGame();
//----------PRIVATE VARIABLES-----------------
private:
	bool mIsRunning;
	Sint32 mPlayerScore;
	//Question and Answer Database
	deque<cQuestion*> mList;
//----------PUBLIC STATIC VARIABLES-----------
public:
	static const Uint32 sQuestionTotal;
//----------PRIVATE FUNCTIONS-----------------
private:
	void InitQuestions();
	void Shuffle();
	bool IsCorrectString(Uint32, string);
	bool IsCorrectNumber(Uint32, Uint32);
	//Read From File (all info can be kept in one file if desired)
	//Would like to change this to templated functions, as they are quite similiar except for the return data type
	string readStringFromFile(const char [], const Uint32, const Uint32, const Uint32);
	Uint32 readNumberFromFile(const char [], const Uint32, const Uint32, const Uint32);
//----------PUBLIC FUNCTIONS------------------
public:
	void InitializeGame();
	bool QuizOnce(const Uint32);
	void DisplayScore();
	void ScoreScreen();
	//Setters
	void setGameState(bool);
	void setPlayerScore(Sint32, bool, bool);
	//Getters
	bool getGameState() const;
	Sint32 getPlayerScore() const;
};

#endif // __GAME_H