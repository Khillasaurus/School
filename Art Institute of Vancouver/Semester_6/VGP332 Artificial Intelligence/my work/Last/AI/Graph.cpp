//=================================================================================================
// File:		Graph.cpp
// Created:		2012/10/01
// Last Edited:	2012/10/18
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Graph.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constuctors
//-------------------------------------------------------------------------------------------------

Graph::Graph()
	: mNodes(NULL)
	, mNumNodes(0)
	, mStart(Node::kInvalidID)
	, mEnd(Node::kInvalidID)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Graph::~Graph()
{
	Purge();
}

//-------------------------------------------------------------------------------------------------
// General
//-------------------------------------------------------------------------------------------------

void Graph::Allocate(int numNodes)
{
	Purge();

	if(mNumNodes == 0)
	{
		mNodes = new Node[numNodes];
		mNumNodes = numNodes;
	}
}

//-------------------------------------------------------------------------------------------------

void Graph::Purge()
{
	if(mNodes != NULL)
	{
		delete[] mNodes;
		mNodes = NULL;
	}
	mNumNodes = 0;
}

//-------------------------------------------------------------------------------------------------

void Graph::SearchBFS(int start, int end, IWalkable& IsWalkable)
{
	mStart = start;
	mEnd = end;

	// Reset
	for(int i = 0; i < mNumNodes; ++i)
	{
		mNodes[i].Reset();
	}
	mOpenList.clear();
	mClosedList.clear();

	// Put start node int the open list
	mOpenList.push_back(&mNodes[mStart]);
	mNodes[mStart].Open();

	// Loop until we are done
	bool found = false;
	while(!found & !mOpenList.empty())
	{
		Node* pNode = mOpenList.front();
		mOpenList.pop_front();

		// Check if this is the end node
		if(pNode == &mNodes[mEnd])
		{
			found = true;
		}
		else
		{
			for(int n = 0; n < Node::kMaxNeighbors; ++n)
			{
				Node* pNeighbor = pNode->GetNeighbor(n);
				if(pNeighbor != NULL && !pNeighbor->IsOpen() && IsWalkable(pNeighbor))
				{
					// Set parent
					pNeighbor->SetParent(pNode);

					// Add to open list
					mOpenList.push_back(pNeighbor);
					pNeighbor->Open();
				}
			}
		}

		// Add node to closed list
		mClosedList.push_back(pNode);
		pNode->Close();
	}

	// Check if we have a path
	if(found)
	{
		// Clear the old path
		mPath.clear();

		// Construct path from end to start
		Node* pNode = &mNodes[mEnd];
		while(pNode != NULL)
		{
			mPath.push_back(pNode);
			pNode = pNode->GetParent();
		}
	}
}

//-------------------------------------------------------------------------------------------------

void Graph::SearchDFS(int start, int end, IWalkable& IsWalkable)
{
	mStart = start;
	mEnd = end;

	// Reset
	for(int i = 0; i < mNumNodes; ++i)
	{
		mNodes[i].Reset();
	}
	mOpenList.clear();
	mClosedList.clear();

	// Put start node int the open list
	mOpenList.push_front(&mNodes[mStart]);
	mNodes[mStart].Open();

	// Loop until we are done
	bool found = false;
	while(!found & !mOpenList.empty())
	{
		Node* pNode = mOpenList.front();
		mOpenList.pop_front();

		// Check if this is the end node
		if(pNode == &mNodes[mEnd])
		{
			found = true;
		}
		else
		{
			for(int n = 0; n < Node::kMaxNeighbors; ++n)
			{
				Node* pNeighbor = pNode->GetNeighbor(n);
				if(pNeighbor != NULL && !pNeighbor->IsOpen() && IsWalkable(pNeighbor))
				{
					// Set parent
					pNeighbor->SetParent(pNode);

					// Add to open list
					mOpenList.push_front(pNeighbor);
					pNeighbor->Open();
				}
			}
		}

		// Add node to closed list
		mClosedList.push_front(pNode);
		pNode->Close();
	}

	// Check if we have a path
	if(found)
	{
		// Clear the old path
		mPath.clear();

		// Construct path from end to start
		Node* pNode = &mNodes[mEnd];
		while(pNode != NULL)
		{
			mPath.push_front(pNode);
			pNode = pNode->GetParent();
		}
	}
}

void Graph::SearchDijkstra(int start, int end, IWalkable& IsWalkable, ICost& GetG)
{
	mStart = start;
	mEnd = end;

	// Reset
	for(int i = 0; i < mNumNodes; ++i)
	{
		mNodes[i].Reset();
	}
	mOpenList.clear();
	mClosedList.clear();

	// Put start node int the open list
	mOpenList.push_back(&mNodes[mStart]);
	mNodes[mStart].Open();

	// Loop until we are done
	bool found = false;
	while(!found & !mOpenList.empty())
	{
		Node* pNode = mOpenList.front();
		mOpenList.pop_front();

		// Check if this is the end node
		if(pNode == &mNodes[mEnd])
		{
			found = true;
		}
		else
		{
			for(int n = 0; n < Node::kMaxNeighbors; ++n)
			{
				Node* pNeighbor = pNode->GetNeighbor(n);
				if(pNeighbor != NULL && !pNeighbor->IsClosed() && IsWalkable(pNeighbor))
				{
					float G = pNode->GetG() + GetG(pNode, pNeighbor);
					if(!pNeighbor->IsOpen())
					{
						// Set parent
						pNeighbor->SetParent(pNode);

						// Set cost
						pNeighbor->SetG(G);

						//Insert to open list
						InsertSortedByG(pNeighbor);
						pNeighbor->Open();
					}
					else if(pNeighbor->GetG() > G)
					{
						//Update parent
						pNeighbor->SetParent(pNode);

						//Update cosr
						pNeighbor->SetG(G);

						//Re-insert to open list
						mOpenList.remove(pNeighbor);
						InsertSortedByG(pNeighbor);
					}
				}
			}
		}

		// Add node to closed list
		mClosedList.push_front(pNode);
		pNode->Close();
	}

	// Check if we have a path
	if(found)
	{
		// Clear the old path
		mPath.clear();

		// Construct path from end to start
		Node* pNode = &mNodes[mEnd];
		while(pNode != NULL)
		{
			mPath.push_front(pNode);
			pNode = pNode->GetParent();
		}
	}
}

//-------------------------------------------------------------------------------------------------

Node* Graph::GetNode(int index) const
{
	Node* pNode = NULL;
	if(index >= 0 && index < mNumNodes)
	{
		pNode = &mNodes[index];
	}
	return pNode;
}

//-------------------------------------------------------------------------------------------------

void Graph::InsertSortedByG(Node* pNode)
{
	NodeList::iterator iter = mOpenList.begin();
	while(iter != mOpenList.end())
	{
		Node* node = *iter;
		if(node->GetG() > pNode->GetG())
		{
			break;
		}
		++iter;
	}
	mOpenList.insert(iter, pNode);
}

//-------------------------------------------------------------------------------------------------