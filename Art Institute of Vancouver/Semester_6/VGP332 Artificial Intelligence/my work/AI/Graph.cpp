//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------

#include "Graph.h"
#include "Node.h"

Graph::Graph()
	: mNodes(NULL)
	, mNumNodes(0)
{
}

Graph::~Graph()
{
	if(mNodes != NULL)
	{
		delete[] mNodes;
		mNodes = NULL;
	}
}

void Graph::Allocate(int numNodes)
{
	Purge();

	if(mNumNodes > 0)
	{
		mNodes = new Node[numNodes];
		mNumNodes = numNodes;
	}
}

void Graph::Purge()
{
	if(mNodes != NULL)
	{
		delete[] mNodes;
		mNodes = NULL;
	}
	mNumNodes = 0;
}

Node* Graph::GetNode(int index) const
{
	Node* node = NULL;
	if(index >= 0 && index < mNumNodes)
	{
		node = &mNodes[index];
	}
	return node;
}