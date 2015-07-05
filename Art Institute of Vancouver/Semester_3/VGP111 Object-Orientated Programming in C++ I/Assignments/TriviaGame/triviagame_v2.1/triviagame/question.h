//-----------------------------
// File:		question.h
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __QUESTION_H
#define __QUESTION_H

class cQuestion
{
//----------SPECIAL MEMBER FUNCTIONS----------
public:
	cQuestion();
	cQuestion(string, string, string, string, string, Uint32);
	~cQuestion();
//----------PRIVATE VARIABLES-----------------
private:
	string mQuestion;
	string mAnswer1;
	string mAnswer2;
	string mAnswer3;
	string mAnswer4;
	Uint32 mCorrectAnswer;
	string mUserStringAnswer;
	Uint32 mUserNumberAnswer;
//----------PUBLIC FUNCTIONS------------------
public:
	//Setters
	void setQuestion(string);
	void setAnswer1(string);
	void setAnswer2(string);
	void setAnswer3(string);
	void setAnswer4(string);
	void setCorrect(Uint32);
	void setUserString(string);
	void setUserNumber(Uint32);
	//Getters
	string getQuestion() const;
	string getAnswer1() const;
	string getAnswer2() const;
	string getAnswer3() const;
	string getAnswer4() const;
	Uint32 getCorrect() const;
	string getUserString() const;
	Uint32 getUserNumber() const;
};

#endif // __QUESTION_H