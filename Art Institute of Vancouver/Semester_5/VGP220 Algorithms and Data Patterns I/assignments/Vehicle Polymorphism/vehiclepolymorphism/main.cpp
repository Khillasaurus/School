//====================================================================================================
//File:			main.cpp
//Created:		2012/09/09
//Copyright:	Daniel Schenker
//Description:	Defines the entry point for the console application.
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Run-Time Library
//#include <stdlib.h>

//Daniel Schenker
#include "cNode.h"
#include "cVehicle.h"
#include "cVehicleSedan.h"

//====================================================================================================
//Main
//====================================================================================================

int _tmain(int argc, _TCHAR* argv[])
{
	//Create list
	 //NODE 0
	cNode* pHead = new cNode;
	pHead->pVehicle = new cVehicleSedan();
	 //Usage pointers
	cNode* pLead = pHead;
	cNode* pFollow = pLead;
	cNode* pTraversal = pHead;

	 //NODE 1
	pLead = pHead;
	pFollow = pLead;
	if(!pLead->pNext)
	{
		pLead->pNext = new cNode;
		//update pLead to point to the new node (tail)
		pLead = pLead->pNext;
		pLead->pVehicle = new cVehicleSedan(1, "asd", "fgh", 2, 3, 4, true, false, 5);
		pLead->pPrev = pFollow;
	}

	//Move pLead to the end of the list
	pLead = pHead;
	while(pLead->pNext)
	{
		pLead = pLead->pNext;
	}
	//Add kN nodes
	const int kN = 3;
	for(int i = 0; i < kN; ++i)
	{
		if(!pLead->pNext)
		{
			pFollow = pLead;
			pLead->pNext = new cNode;
			//update pLead to point to the new node (tail)
			pLead = pLead->pNext;
			pLead->pVehicle = new cVehicleSedan();
			pLead->pPrev = pFollow;
		}
		else
		{
			printf("ERROR: pLead->pNext is already pointing to something.\n");
			break;
		}
	}

	//Insert a node
	//Move pLead to the correct position
	const int kPos = 5;
	pLead = pHead;
	for(int i = 0; i < kPos; ++i)
	{
		if(pLead->pNext)
		{
			pLead = pLead->pNext;
		}
		else
		{
			printf("ERROR: Cannot reach element %d. Returning the end of the list instead.\n", kPos);
			break;
		}
	}
	//if there is a node behind pLead
	if(pLead->pPrev)
	{
		//set pFollow to the node before pLead
		pFollow = pLead->pPrev;

		//if pLead is NOT pointing to the last node (tail)
		if(cNode::autoRefCount > kPos)
		{
			//Insert new node
			cNode* pInsert = new cNode();
			//Set node data
			pInsert->pVehicle = new cVehicleSedan(9, "9", "9", 9, 9, 9, false, true, 9);
			//Set node pointers
			pInsert->pNext = pLead;
			pInsert->pPrev = pFollow;
			pFollow->pNext = pInsert;
			pLead->pPrev = pInsert;
		}
		//else pLead is pointing to the last node (tail)
		else
		{
			//set pFollow to point to the tail
			pFollow = pLead;
			//add node to tail
			pLead->pNext = new cNode();
			//set pLead to point to the new tail
			pLead = pLead->pNext;
			//Set node data
			pLead->pVehicle = new cVehicleSedan(100, "100", "100", 100, 100, 100, false, false, 100);
			//Set node pointers
			pLead->pNext = NULL;
			pLead->pPrev = pFollow;
			pFollow->pNext = pLead;
		}
	}
	//else pLead is pointing to the first node (head)
	else
	{
		//Add node to head
		pFollow = new cNode();
		//Set node data
		pFollow->pVehicle = new cVehicleSedan(11, "11", "11", 11, 11, 11, true, true, 11);
		//Set node pointers
		if(pLead->pNext)
		{
			pFollow->pNext = pLead;
			pLead->pPrev = pFollow;
		}
		//the list does not exist other than the node we are currently adding to it
		else
		{
			pFollow->pNext = NULL;
		}
		//since a node has been added to the front, set the head pointer accordingly 
		pHead = pFollow;
	}

	printf("-===============================================================================-");
	//Print all data
	pTraversal = pHead;
	while(pTraversal->pNext)
	{
		pTraversal->pVehicle->ShowName();
		pTraversal->pVehicle->HowFast();
		pTraversal->pVehicle->NeedService();
		pTraversal->pVehicle->Horsepower();
		pTraversal->pVehicle->Show4WD();
		pTraversal->pVehicle->ShowWinch();
		pTraversal->pVehicle->ShowLoadToCarry();
		//move pTraversal forwards one node
		pTraversal = pTraversal->pNext;
		printf("\n");
	}
	pTraversal->pVehicle->ShowName();
	pTraversal->pVehicle->HowFast();
	pTraversal->pVehicle->NeedService();
	pTraversal->pVehicle->Horsepower();
	pTraversal->pVehicle->Show4WD();
	pTraversal->pVehicle->ShowWinch();
	pTraversal->pVehicle->ShowLoadToCarry();
	pTraversal = NULL;
	printf("\n");
	
	//Free all memory in the linked list
	pLead = pHead;
	pFollow = pLead;
	pHead = NULL;
	while(pLead->pNext)
	{
		pFollow = pLead;
		//move pLead forwards one node
		pLead = pLead->pNext;
		delete pFollow;
	}
	pFollow = NULL;
	delete pLead;
	pLead = NULL;

	return 0;
}
