//-----------------------------
// File:		question.h
// Created:		2012/3/14
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __QUESTION_H
#define __QUESTION_H

class cQuestion
{
public:
	cQuestion();
	cQuestion(Uint32, string, string, string, string, string, Uint32);
	~cQuestion();
private:
	Uint32 mQuestionNumber;
	string mQuestion;
	string mAnswer1;
	string mAnswer2;
	string mAnswer3;
	string mAnswer4;
	Uint32 mCorrectAnswer;
	Uint32 mUserAnswer;
public:
	//Setters
	void setQuestionNumber(Uint32);
	void setQuestion(string);
	void setAnswer1(string);
	void setAnswer2(string);
	void setAnswer3(string);
	void setAnswer4(string);
	void setCorrect(Uint32);
	void setUser(Uint32);
	//Getters
	string getQuestionNumber() const;
	string getQuestion() const;
	string getAnswer1() const;
	string getAnswer2() const;
	string getAnswer3() const;
	string getAnswer4() const;
	Uint32 getCorrect() const;
	Uint32 getUser() const;
};

#endif // __QUESTION_H