//-----------------------------
// File:		main.cpp
// Created:		2012/07/05
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include <string.h>

//Example Object
class cFireTruck
{
public:
	int litresOfWater;
	int wheels;
};

//Memory Manager
class cMemoryManager
{
public:
	cMemoryManager::cMemoryManager()
	:	sizeOfHeap(0)
	,	heapSet(false)
	{
		SetSizeOfHeap();
		AllocateHeap();
		InitDatabase();
		//Set our entire heap to empty
		memset(pHeap, 0, sizeOfHeap);
	}

	cMemoryManager::cMemoryManager(int heapSize)
	:	sizeOfHeap(heapSize)
	,	heapSet(false)
	{
		AllocateHeap();
		InitDatabase();
		//Set our entire heap to empty
		memset(pHeap, 0, sizeOfHeap);
	}

	~cMemoryManager()
	{
		delete[] pHeap;
		pHeap = nullptr;
	}
	
private:
	char* pHeap;
	int sizeOfHeap;
	bool heapSet;
	bool* pDatabase;

public:
	int GetSizeOfHeap()
	{
		return sizeOfHeap;
	}

	void ReleaseMemory(void* pObject)
	{
		//Create a temporary pointer to the beginning of the heap to iterate forward, without changing the original
		char* pTemp = pHeap;
		int offset = 0;

		//Edit database
			//Find the offset in bytes from the beginning of the heap to where the object is stored
			for(offset = 0; pTemp != pObject; ++offset)
			{
				++pTemp;
			}

			//Set the destoyed objects previously allocated memory in the database back to "available for use"
			for(int i = offset; i < (offset + sizeof(pObject)); ++i)
			{
				pDatabase[i] = false;
			}

		pObject = nullptr;
	}

	void PrintDatabase()
	{
		for(int i = 0; i < sizeOfHeap; ++i)
		{
			//If the byte is NOT in use
			if(pDatabase[i] == 0)
			{
				printf("0x%08x : 0\n", pHeap + i);
			}
			else
			{
				printf("0x%08x : 1\n", pHeap + i);
			}
		}
	}

private:
	void AllocateHeap()
	{
		//If the heap has NOT been set yet
		if(!heapSet)
		{
			if(sizeOfHeap <= 0)
			{
				SetSizeOfHeap();
			}
			pHeap = new char[sizeOfHeap];
		}
		else
		{
			printf("ERROR: The heap has already been allocated. Unable to reallocate. - cMemoryManager::AllocateHeap()\n");
		}
	}

	void* ReturnAddress(size_t objSize)
	{
		//Find a good location for the object in my heap
			char* pSavingLocation = pHeap;//location of the best found storage location
			int saveSize = sizeOfHeap;//smallest found size that is large enough to fit our object in
			int testAddress = 0;//offset from the beginning of the heap to the beginning of a potential storage location
			int testSize = 0;//counter used to determine the size of the current test storage location
			bool currentlyTesting = false;//Are we testing a potential storage location

			//Loop through the heap once to check for the most appropriate location to store our object
			for(int i = 0; i < sizeOfHeap; ++i)
			{
				//If the byte of the database is empty
				if(!pDatabase[i])
				{
					//If we are NOT already testing a location
					if(!currentlyTesting)
					{
						testAddress = i;
					}

					//Since we found an empty piece in our heap and we're not currently testing for a potential storage location, start testing
					currentlyTesting = true;

					//Increase the known size of the current free space in our heap
					++testSize;
				}
				else
				{
					currentlyTesting = false;

					//If we found a storage location that's the exact required size
					if(testSize == objSize)
					{
						saveSize = testSize;//Remember the size of the new best potential storage location for reference in future tests
						pSavingLocation = pHeap + (testAddress * sizeof(char));//Until a better storage location is found, this becomes our new best potential storage location

						break;//break out of our loop since we don't need to search any more
					}
					//Else if we found a location bigger than the size of our object but smaller than saveSize
					else if(testSize > objSize && testSize < saveSize)
					{
						saveSize = testSize;//Remember the size of the new best potential storage location for reference in future tests
						pSavingLocation = pHeap + (testAddress * sizeof(char));//Until a better storage location is found, this becomes our new best potential storage location
					}

					//Done last test, reset testSize counter for the next test
					testSize = 0;
				}
			}

		//Edit Database: Add data about the location and size of the object we are placing into our heap
		for(int i = 0; i < sizeOfHeap - testAddress; ++i)
		{
			//Set the byte in our heap to "in use"
			pDatabase[testAddress + i] = true;
		}

		//Return that address in my heap that the object will be stored at
		return (pSavingLocation);
	}

	void SetSizeOfHeap()
	{
		//If the heap has NOT been set yet
		if(!heapSet)
		{
			//If the heap doesn't exist or is an invalid value
			if(sizeOfHeap <= 0)
			{
				printf("How big would you like the heap to be?\n");
				scanf("%d", &sizeOfHeap);
			}
			//The heap size has already been set. Do not change it.
			else
			{
				printf("The size of the heap has already been set to %d bytes. Unable to change heap size.\n", sizeOfHeap);
			}
		}
		else
		{
			printf("ERROR: The heap has already been set. Unable to change. - cMemoryManager::SetSizeOfHeap()\n");
		}
	}

	bool* InitDatabase()
	{
		pDatabase = new bool[sizeOfHeap];

		//Set the entire database to empty
		for(int i = 0; i < sizeOfHeap; ++i)
		{
			pDatabase[i] = false;
		}

		return pDatabase;
	}

	//Set our overloaded placement new to be a friend function so that it can access cMemoryManager::ReturnAdress(objSize)
	friend void* operator new(size_t objSize, cMemoryManager* pMemoryManager);
};

//Overloaded placement new
void* operator new(size_t objSize, cMemoryManager* pMemoryManager)
{
	return pMemoryManager->ReturnAddress(objSize);
}


int _tmain(int argc, _TCHAR* argv[])
{
	//1) Allocate memory from the heap for my memory manager itself
		cMemoryManager* pMemoryManager = new cMemoryManager(1000);

	//2) Allocate all the memory I'll ever need for my game
		//pMemoryManager->sizeOfHeap = 1000;//Done in step 1
		//char* pHeap = new char[pMemoryManager->sizeOfHeap];//Done in step 1

	//3) Use the memory I've allocated for my game
	//A) When I need a new object in my game, allocate memory from my game memory
		//Allocate a cFireTruck object in my heap
		cFireTruck* pFireTruck = new(pMemoryManager) cFireTruck;

	//B) When I'm done using an object in my game and want to get rid of it, explicitly call the destructor, ~classnameofobject()
		//Deallocate a cFireTruck object in my heap
		pFireTruck->cFireTruck::~cFireTruck();

	//C) I use a release memory function to now give the now uneeded memory back to the game memory controlled by the memory manager
		pMemoryManager->ReleaseMemory(pFireTruck);
	
	//4) When I'm done playing my game, I free all the heap memory I ever used at once (this includes the memory manager as well as the memory for the game)
		delete pMemoryManager;

	return 0;
}

/*
My basic understanding of how a memory manager should work:
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