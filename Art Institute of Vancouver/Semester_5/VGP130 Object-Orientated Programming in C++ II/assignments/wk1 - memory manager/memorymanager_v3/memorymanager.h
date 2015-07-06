//-----------------------------
// File:		grid.h
// Created:		2012/07/11
// Copyright:	Daniel Schenker
//-----------------------------

#ifndef __MEMORYMANAGER_H
	#define __MEMORYMANAGER_H

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

#endif//__MEMORYMANAGER_H