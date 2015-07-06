//-----------------------------
// File:		main.cpp
// Created:		2012/07/05
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include <string.h>

void* operator new(size_t objSize)
{
	return malloc(objSize);
}

//placement new
void* operator new(size_t objSize, void* pMemoryMgr)
{
	cPlacementNewManager* pMan = (cPlacementNewManager*)pMemoryMgr;//the c++ style of this is: cPlacementNewManager* pMan = reinterpret_cast<cPlacementNewManager*>(pMemoryMgr);
	return (pMemoryMgr->Alloc(objSize));
	//return malloc(objSize);
}

int _tmain(int argc, _TCHAR* argv[])
{
	// in the beginning... you have heap
	// if everything is heap based,
	// allocate memory manager from heap
	// allocate memory managed memory from heap -> store in memman

	cMemMan *pMemMan;
	pMemMan = new cMemMan();
	// use pMemMan ...
	delete pMemMan;

	cPlacementNewManager pnewman;
	char* pMemory = new char[1000];
	pnewman->mpHeap;
	int offsetoffreememory = 0;

	cThing* pThing1;
	pThing1 = new(pnewman) cThing();//the c style of this is: pThing1 = (cThing*)malloc(sizeof(cThing));
	offsetoffreememory += objSize;
	pThing1->x = 5;
	cThing* pThing2;
	pThing2 = new(pMemory) cThing();
	offsetoffreememory += objSize;

	pThing2->~cThing();
	pnewman.ReleaseObject(pThing2);//can also be written as: pnewman.Dealloc(pThing2);

	delete [] pMemory;

	return 0;
}

/*
My basic understanding:
	A memory manager allows for custom memory management
		The reason for this is because allocating memory from the heap is very expensive.
		If I allocate all the memory my game will ever need in the beginning of my program, I eliminate the inneficiency of allocating memory from the heap.
	The steps in which this is done:
		1) Allocate memory from the heap for my memory manager itself
		2) Allocate all the memory I'll ever need for my game
		3) Use the memory I've allocated for my game
			Step 3 Explained:
			A) When I need a new object in my game, allocate memory from my game memory
				Step 3A Explained:
				I use the overwritten opeartor new to say what object and the size of the object that I'm allocating
				This is done using the code:
					pObject = new(pMemoryManager) cObject();
						The reason I use pMemoryManager instead of pMemoryAllocatedForGame is so that the memory manager can itself can set the specific location in pMemoryAllocatedForGame and data about the newly stored data itself
							Remember: pObject = new(pMemoryManager) cObject(); actually passes 2 variables, but must be written with 1. They are: sizeof(cObject) as the first parameter and pMemoryManager as the destination(but since we're using pMemoryManager instead of pMemoryAllocatedForGame, this becomes the duty of the memory manager isntead of a destination)
			B) When I'm done using an object in my game and want to get rid of it, explicitly call the destructor, ~classnameofobject()
			C) I use a release memory function to now give the now uneeded memory back to the game memory controlled by the memory manager
		4) When I'm done playing my game, I free all the heap memory I ever used at once (this includes the memory manager as well as the memory for the game)
			This makes deallocating very efficient
*/