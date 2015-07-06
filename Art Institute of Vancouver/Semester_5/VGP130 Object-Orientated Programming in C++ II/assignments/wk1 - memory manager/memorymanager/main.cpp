//-----------------------------
// File:		main.cpp
// Created:		2012/07/05
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include <string.h>

/*
void* operator new(size_t objSize)
{
	return malloc(objSize);
}
*/

//Example Object
class cFireTruck
{
public:
	int a;
	int b;
};

//Memory Manager
class cMemoryManager
{
public:
	cMemoryManager::cMemoryManager(int heapSize)
	:	sizeOfHeap(heapSize)
	,	offset(0)
	{
		cMemoryManager::AllocateMemory();
	}
	~cMemoryManager()
	{
		delete[] pHeap;
		pHeap = nullptr;
	}
	
	char* pHeap;
	int sizeOfHeap;
	int offset;

	void AllocateMemory()
	{
		pHeap = new char[sizeOfHeap];
	}
	void* ReturnAddress(size_t objSize)
	{
		//Find a good location for the object in my heap
		//Edit Database

		offset += objSize;

		//Return that address in my heap that the object will be stored at
		return (pHeap + offset);
	}
	void ReleaseMemory(void* pObject)
	{
		//Edit database

		pObject = nullptr;
	}
};

//placement new
void* operator new(size_t objSize, cMemoryManager* pMemoryManager)
{
	return pMemoryManager->ReturnAddress(objSize);
}

/*
void* operator new(size_t sz, void* p)
{
	printf("Placement new invoked\n");
	return p;
}
*/

int _tmain(int argc, _TCHAR* argv[])
{
	//1) Allocate memory from the heap for my memory manager itself
		cMemoryManager* pMemoryManager = new cMemoryManager(1000);

	//2) Allocate all the memory I'll ever need for my game
		//pMemoryManager->sizeOfHeap = 1000;//Done in step 1
		printf("Size of my heap: %d\n", &pMemoryManager->sizeOfHeap);
		//char* pHeap = new char[pMemoryManager->sizeOfHeap];//Done in step 1
		printf("Address of my heap: 0x%08x\n", &pMemoryManager->pHeap);

	//3) Use the memory I've allocated for my game
	//A) When I need a new object in my game, allocate memory from my game memory
		//Allocate a cFireTruck object in my heap
		cFireTruck* pFireTruck = new(pMemoryManager) cFireTruck;
		printf("Address of my fire truck: 0x%08x\n", pFireTruck);

	//B) When I'm done using an object in my game and want to get rid of it, explicitly call the destructor, ~classnameofobject()
		//Deallocate a cFireTruck object in my heap
		pFireTruck->cFireTruck::~cFireTruck();
		printf("Pointer to fire truck should now be NULL: %p\n", pFireTruck);

	//C) I use a release memory function to now give the now uneeded memory back to the game memory controlled by the memory manager
		//TODO
	
	//4) When I'm done playing my game, I free all the heap memory I ever used at once (this includes the memory manager as well as the memory for the game)
		delete pMemoryManager;

		/*
		//=========================
		{
			pMemoryManager::BookKeepStats(cFireTruck);
			return pMemoryManager->MemoryManager::ReturnLocationInMemory(cFireTruck);
		}
		//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		//properly written
		//int* pSavingLocation = //firstAdressOfOurHeap;
		int saveSize = sizeOfOurHeap;
		for(int i = 0; i < sizeOfOurHeap; ++i)
		{
			if(pHeapDatabase[i] == false //false means empty)
			{
				//we find a location bigger than than our object but smaller than pSaveSize
				if(sizeOfThisLocation > sizeOfObject && sizeOfThisLocation < saveSize)
				{
					saveSize = sizeOfThisLocation;
					pSavingLocation = //ofThisLocation;
				}
			}
		}
		*/

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