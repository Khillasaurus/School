#ifndef INCLUDED_AI_NODE_H
#define INCLUDED_AI_NODE_H

#include <SGE.h>
using namespace SGE;

class Node
{
public:
	static const int kMaxNeighbors = 8;
	static const int kInvalidID = -1;

	Node();
	
	Node* GetNeighbor(int index) const			{ return mpNeighbors[index]; };
	int GetID() const							{ return mID; };
	const SVector2& GetPosition() const			{ return mPosition; }

	void SetNeighbor(int index, Node* n)		{ mpNeighbors[index] = n; };
	void SetId(int id)							{ mID  = id; };


protected:
	Node* mpNeighbors[kMaxNeighbors];

	int mID;

	SVector2 mPosition;
};

#endif //INCLUDED_AI_NODE_H