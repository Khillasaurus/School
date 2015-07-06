////=================================================================================================
//// File:		WinMain.cpp
//// Created:		2012/10/01
//// Last Edited:	2012/10/15
//// Copyright:	Daniel Schenker
//// Description:	Main entry point of application.
////=================================================================================================
//
////=================================================================================================
//// Includes
////=================================================================================================
//
//// SGE
//#include <SGE.h>
//using namespace SGE;
//
//#include <AI.h>
//
////=================================================================================================
//// Globals
////=================================================================================================
//
//Graph gGraph;
//const int gNumCols = 10;
//const int gNumRows = 10;
//
////=================================================================================================
//// Class Definitions
////=================================================================================================
//
//
//class WaklableFunctor : public Iwalkable
//{
//public:
//	// Implements IWalkable
//	virtual bool operator()(Node* pNode)
//	{
//		bool walkable = true;
//		int x = pNode->GetId() % gNumCols;
//		int y = pNode->GetId() / gNumRows;
//		if( x == 0 || x == gNumCols -1 ||
//			y == 0 || y == gNumRows - 1 )
//		{
//			walkable = false;
//		}
//		return walkable;
//	}
//};
//
//
//void SGE_Initialize()
//{
//	//Build a graph
//	gGraph.Allocate(gNumCols * gNumRows);
//	for(int y = 0; y < gNumRows; ++y)
//	{
//		for(int x = 0; x < gNumCols; ++x)
//		{
//			const int index = x + (y * gNumCols);
//			Node* pNode = gGraph.GetNode(index);
//			pNode->SetNeighbor(0, gGraph.GetNode((x - 1) + ((y - 1) * gNumCols)));
//			pNode->SetNeighbor(1, gGraph.GetNode((x    ) + ((y - 1) * gNumCols)));
//			pNode->SetNeighbor(2, gGraph.GetNode((x + 1) + ((y - 1) * gNumCols)));
//			pNode->SetNeighbor(3, gGraph.GetNode((x - 1) + ((y   1) * gNumCols)));
//			pNode->SetNeighbor(4, gGraph.GetNode((x + 1) + ((y   1) * gNumCols)));
//			pNode->SetNeighbor(5, gGraph.GetNode((x - 1) + ((y + 1) * gNumCols)));
//			pNode->SetNeighbor(6, gGraph.GetNode((x    ) + ((y + 1) * gNumCols)));
//			pNode->SetNeighbor(7, gGraph.GetNode((x + 1) + ((y + 1) * gNumCols)));
//
//			pNode->SetId(index);
//
//			pNode->GetPosition(SVector2(gHalfSize (x + gTileSize),gHalfSize + (y * gTileSize)));
//		}
//	}
//}
//
////-------------------------------------------------------------------------------------------------
//
//void SGE_Terminate()
//{
//	gGraph.Purge();
//}
//
////-------------------------------------------------------------------------------------------------
//
//bool SGE_Update(float deltaTime)
//{
//	if(Input_IsKeyPressed(Keys::SPACE))
//	{
//		int startX = RandomInt(1, gNumCols - 1);
//		int startY = RandomInt(1, gNumRows - 1);
//		int endX = RandomInt(1, gNumCols - 1);
//		int endY = RandomInt(1, gNumRows - 1);
//		if(startX != endX || startY != endY)
//		{
//			int start = startX + (startY * gNumCols);
//			int end = endX + (endY * gNumCols);
//			gGraph.SearchBFS(start, end, WalkableFunctor());
//		}
//	}
//	return Input_IsKeyPressed(SGE::Keys::ESCAPE);
//}
//
////-------------------------------------------------------------------------------------------------
//
//void SGE_Render()
//{
////	for(int y = 1; y < gNumRows - 1; ++y)
////	{
////		for(int x = 1; x < gNumcols - 1; ++x)
////		{
////			const int index = x + (Y * gNumCols);
////			Node* pNode = gGraph.GetNode(index);
////			for(int n = 0; n <  kMaxNeighbors; ++n)
////			{
////				Node* pNeighbor = pNode->GetNeighbor(n);
////				if(pNeighbor != NULL)
////				{
////					Graphics_DebugLine(pNode->GetPosition(), pNeighbor->GetPosition(), 0x00FFF);
////				}
////			}
////		}
////	}
//
//	const NodeList& ClosedList = gGraph.GetClosedList();
//	for(NodeList::const_iterator iter = closedList.begin(); 
//	iter != closedList.end()
//	++iter)
//	{
//		Node* pNode = (*Iter);
//		if(pNode != NULL && pNodeParent() != NULL)
//		{
//			Garphics_DebugLine(pNode->GetPosition(), pNode->GetParent()->GetPosition)-, 0xF400F3);
//		}
//	}
//}