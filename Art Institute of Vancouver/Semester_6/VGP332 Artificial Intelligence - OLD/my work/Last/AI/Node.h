#ifndef INCLUDED_AI_NODE_H
#define INCLUDED_AI_NODE_H

//=================================================================================================
// File:		Node.h
// Created:		2012/10/01
// Last Edited:	2012/10/18
// Copyright:	Daniel Schenker
// Description:	Node.h
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;

//STL
#include <list>

//=================================================================================================
// Class Definitions
//=================================================================================================

class Node
{
public:
	static const int kMaxNeighbors = 8;
	static const int kInvalidID = -1;

	Node();

	void Reset();
	
	Node* GetNeighbor(int index) const			{ return mpNeighbors[index]; };
	Node* GetParent() const						{ return mpParent; }
	int GetID() const							{ return mID; };
	const SVector2& GetPosition() const			{ return mPosition; }
	float GetF() const							{ return mG + mH; }
	float GetG() const							{ return mG; }
	float GetH() const							{ return mH; }
	bool IsOpen() const							{ return mOpen; }
	bool IsClosed() const						{ return mClosed; }
	bool IsValid() const						{ return mValid; }

	void SetNeighbor(int index, Node* n)		{ mpNeighbors[index] = n; };
	void SetParent(Node* p)						{ mpParent = p; }
	void SetId(int id)							{ mID  = id; };
	void SetPosition(const SVector2& pos)		{ mPosition = pos; }
	void SetG(float g)							{ mG = g; }
	void SetH(float h)							{ mH = h; }
	void Open()									{ mOpen = true; }
	void Close()								{ mClosed = true; }
	void SetValid(bool valid)					{ mValid = valid; }


protected:
	Node* mpNeighbors[kMaxNeighbors];
	Node* mpParent;

	int mID;

	SVector2 mPosition;

	float mG;//Cumulative cost
	float mH;//Heuristic cost

	bool mOpen;
	bool mClosed;
	bool mValid;
};

typedef std::list<Node*> NodeList;

#endif //#ifndef INCLUDED_AI_NODE_H