#ifndef INCLUDED_AI_GRAPH_H
#define INCLUDED_AI_GRAPH_H

//=================================================================================================
// File:		Graph.h
// Created:		2012/10/01
// Last Edited:	2012/11/07
// Copyright:	Daniel Schenker
// Description:	Graph.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Node.h"

//An interface is a list of public pure virtual functions
struct IWalkable
{
	virtual bool operator()(Node* pNode) = 0;
	//virtual bool operator()(Node* pNode, const int columns, const int rows) = 0;
};

struct ICost
{
	virtual float operator()(Node* pNodeA, Node* pNodeB) = 0;
};

class Graph
{
public:
	Graph();
	~Graph();

	void Allocate(int numNodes);
	void Purge();

	void SearchBFS(int start, int end, IWalkable& IsWalkable);
	void SearchDFS(int start, int end, IWalkable& IsWalkable);
	void SearchDijkstra(int start, int end, IWalkable& IsWalkable, ICost& GetG);

	Node* GetNode(int index) const;

	const NodeList& GetClosedList() const		{ return mClosedList; }
	const NodeList& GetPath() const				{ return mPath; }
	int GetNumNodes() const						{ return mNumNodes; };

private:
	//no copy assign
	Graph(const Graph&);
	Graph operator=(const Graph&);

	// Helper
	void InsertSortedByG(Node* pNode);

	NodeList mOpenList;
	NodeList mClosedList;
	NodeList mPath;

	Node* mNodes;

	int mNumNodes;
	int mStart;
	int mEnd;
};

#endif //INCLUDED_AI_GRAPH_H