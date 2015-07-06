// q2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

class cArc
{
	char name;//name of the arc
	int* pNode;//pointer to node that the arc is pointing from
	int* pAhead;//pointer to node that the arc is pointing to
	cArc* pNext;//pointer to the next arc
}


int _tmain(int argc, _TCHAR* argv[])
{
	const int kNodes = 6;

	//array of nodes
	int mArray[kNodes] = {1, 2, 3, 4, 5, 6};

	//linked list of arcs
	cArc* pHead;
	//temp pointers to prevent losing the head of the linked list
	cArc* pLead = pHead;
	cArc* pFollow = pHead;

	//A (head arc)
	//allocate
	pHead = new cArc;
	//fill data
	pHead->name = 'A';
	pHead->pNode = &mArray[0];
	pHead->pAhead = &mArray[1];
	pHead->pNext = NULL;

	//B
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'B';
	pLead->pNode = &mArray[0];
	pHead->pAhead = &mArray[3];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;

	//C
	pFollow = pLead;
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'C';
	pLead->pNode = &mArray[1];
	pHead->pAhead = &mArray[2];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;

	//D
	pFollow = pLead;
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'D';
	pLead->pNode = &mArray[3];
	pHead->pAhead = &mArray[2];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;

	//E
	pFollow = pLead;
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'E';
	pLead->pNode = &mArray[5];
	pHead->pAhead = &mArray[3];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;

	//F
	pFollow = pLead;
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'F';
	pLead->pNode = &mArray[5];
	pHead->pAhead = &mArray[4];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;

	//G
	pFollow = pLead;
	//allocate
	pLead->pNext = new cArc;
	//move pLead forwards to the next arc
	pLead = pLead->pNext;
	//fill data
	pLead->name = 'G';
	pLead->pNode = &mArray[4];
	pHead->pAhead = &mArray[2];
	pLead->pNext = NULL;
	//set previous arc to point to this arc
	pFollow->pNext = pLead;


	//Free dynamically allocated memory

	for(int i = 0; i < kNodes + 1; ++i)
	{
		if(
	}

	return 0;
}

