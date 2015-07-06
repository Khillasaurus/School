// ------------------------------------------
// Filename:	wk6.cpp
// Created:		2012/02/10
// Copyright 2012 me
// ------------------------------------------

// wk1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stack>

//// abstract
//// interface
//// concrete
//
//class cIOStream;
//
//class cIFile
//{
//public: // cIFile
//	virtual bool Open() = 0;
//	virtual void* GetFileHandle() = 0;
//	virtual cIOStream *GetOStream() = 0;
//	virtual bool Close() = 0;
//	virtual bool Exists() = 0;
//	virtual bool Delete() = 0;
//	virtual Uint64 GetPos() = 0;
//	virtual void Seek(Uint64 _pos) = 0;
//};
//
//// ---
//#include "ifile.h"
//
//class cICompressedFile : public cIFile
//{
//public:
//	bool IsAWindowsFile(){ return true; }
//
//public: // cICompressedFile
//	virtual void SetMethod(int method) = 0;
//
//};
//
////---
//#include "icompressedfile.h"
//#include <Windows.h>
//class cWindowsFile : public cICompressedFile
//{
//	HANDLE mhFile;
//public:
//	bool IsAWindowsFile(){ return true; }
//
//public: // cICompressedFile
//	virtual void SetMethod(int method){}
//
//public: // cIFile
//	virtual cIOStream *GetOStream()
//	{
//		cIOStream *p = new cConcreteOStream;
//		//balbla
//		return 0;
//	}
//	//virtual bool Open() = 0;
//	//virtual bool Close(){ return false; }
//	//virtual bool Exists(){ return false; }
//	virtual bool Delete(){ return false; }
//	//virtual Uint64 GetPos(){ return 0; }
//	//virtual void Seek(Uint64 _pos){  }
//};
//
//class cFOOFile : public cWindowsFile
//{
//public: // cIFile
//	virtual bool Open() = 0;
//	virtual bool Close(){ return false; }
//	virtual bool Exists(){ return false; }
//	// impl by parent
//	//	virtual bool Delete(){ return false; }
//	virtual Uint64 GetPos(){ return 0; }
//	virtual void Seek(Uint64 _pos){  }
//};
	//cIFile *pFile = new cWindowsFile();
	//if( pFile->Open() )
	//{
	//}

// TOPIC:templates

//int Add(int a, int b)
//{
//	return a + b;
//}
//float Add(float a, float b)
//{
//	return a + b;
//}

//class cWidget
//{
//	cWidget operator+(const cWidget &rhs)
//	{
//	}
//};

float Add(float a, float b)
{
	return a + b;
}
int Add(int a, int b)
{
	return a + b;
}


template<typename T>
T Add(T a, T b)
{
	return a + b;
}

struct widget
{
	int data;

	widget *pPrev;
	widget *pNext;
};


//----- linkedlist.h
template <typename T>
class cLinkedList
{
public:
	T GetNext();

	T pPrev;
	T pNext;
};

//---

//#include "linkedlist.inl"

///---
// no includes
template <typename T>
T cLinkedList<T>::GetNext()
{
	return pNext;
}

class cwidget : cLinkedList<widget>
{
};


class object
{
public:
	bool isalive();
	bool  is;
};

//cpp
inline bool object::isalive()
{
	return is;
}



int _tmain(int argc, _TCHAR* argv[])
{
	object o;
	if( o.isalive() )
	{
	}

	//int x = Add(1,1);
	//float y = Add(1.0f,1.0f);

	//float z = Add((float)1,1.0f);

	float x = Add<float>(1.0f, 1.0f);
	int  y = Add<int>(1, 1);

	return 0;
}
