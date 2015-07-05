//-----------------------------
// File:		game.h
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __GAME_H
#define __GAME_H

const Uint32 kAmountOfQuestions = 5;

//forward decl
class cQuestion;

class cGame
{
public:
	cGame();
	cGame(bool);
	~cGame();
private:
	bool mIsRunning;
	Uint32 mPlayerScore;
	Uint32 mQuestionCounter;
	//Question and Answer Database
	deque<cQuestion*> mList;
	deque<string> mQuestionList;
	deque<string> mAnswer1List;
	deque<string> mAnswer2List;
	deque<string> mAnswer3List;
	deque<string> mAnswer4List;
	deque<Uint32> mCorrectAnswerList;
private:
	void InitQuestions();
	void Shuffle();
	bool isCorrect(Uint32, Uint32);
public:
	//Setters
	void setGameState(bool);
	void setPlayerScore(Uint32);
	void setQuestionCounter(Uint32);
	void setQuestionList(string);
	void setAnswer1List(string);
	void setAnswer2List(string);
	void setAnswer3List(string);
	void setAnswer4List(string);
	void setCorrectAnswerList(Uint32);
	//Getters
	bool getGameState() const;
	Uint32 getPlayerScore() const;
	Uint32 getQuestionCounter() const;
};

#endif // __GAME_H