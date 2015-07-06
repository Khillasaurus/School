#ifndef INCLUDED_AI_GRAPH_H
#define INCLUDED_AI_GRAPH_H

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------

class Node;

class Graph
{
public:
	Graph();
	~Graph();

	void Allocate(int numNodes);
	void Purge();

	Node* GetNode(int index) const;
	int GetNumNodes() const						{ return mNumNodes; };

private:
	//no copy assign
	Graph(const Graph&);
	Graph operator=(const Graph&);

	Node* mNodes;
	int mNumNodes;

};

#endif //INCLUDED_AI_GRAPH_H