#include "Node.h"

Node::Node()
	: mID(kInvalidID)
	, mPosition(0.0f, 0.0f)
{
	memset(mpNeighbors, 0, sizeof(Node*) * kMaxNeighbors);
}