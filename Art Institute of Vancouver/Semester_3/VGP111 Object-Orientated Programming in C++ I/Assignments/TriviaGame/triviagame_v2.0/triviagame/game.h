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
//----------SPECIAL MEMBER FUNCTIONS----------
public:
	cGame();
	cGame(bool);
	~cGame();
//----------PRIVATE VARIABLES-----------------
private:
	bool mIsRunning;
	Uint32 mPlayerScore;
	///const Uint32 static mQuestionTotal;
	//Question and Answer Database
	deque<cQuestion*> mList;
	///deque<string> mQuestionList;
	///deque<string> mAnswer1List;
	///deque<string> mAnswer2List;
	///deque<string> mAnswer3List;
	///deque<string> mAnswer4List;
	///deque<Uint32> mCorrectAnswerList;
//----------PUBLIC STATIC VARIABLES-----------
public:
	const static Uint32 sQuestionTotal;
//----------PRIVATE FUNCTIONS-----------------
private:
	void InitQuestions();
	void Shuffle();
	bool IsCorrectString(Uint32, string);
	bool IsCorrectNumber(Uint32, Uint32);
	//Read From File (all info can be kept in one file if desired)
	//Would like to change this to templatized functions, as they are identical except for the return data type
	string readStringFromFile(const char [], const Uint32, const Uint32, const Uint32);
	Uint32 readNumberFromFile(const char [], const Uint32, const Uint32, const Uint32);
//----------PUBLIC FUNCTIONS------------------
public:
	void InitializeGame();
	bool QuizOnce(const Uint32);
	void ScoreScreen();
	//Setters
	void setGameState(bool);
	void setPlayerScore(Uint32);
	///void setQuestionCounter(Uint32);
	///void setQuestionList(string);
	///void setAnswer1List(string);
	///void setAnswer2List(string);
	///void setAnswer3List(string);
	///void setAnswer4List(string);
	///void setCorrectAnswerList(Uint32);
	//Getters
	bool getGameState() const;
	///Uint32 getQuestionTotal() const;
	Uint32 getPlayerScore() const;
	///Uint32 getQuestionCounter() const;
};

#endif // __GAME_H