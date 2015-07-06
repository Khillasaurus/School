//=================================================================================================
// File:		WinMain.cpp
// Created:		2012/10/01
// Last Edited:	2012/10/18
// Copyright:	Daniel Schenker
// Description:	Main entry point of application.
//=================================================================================================

#ifndef DSDEBUGMODE
#define DSDEBUGMODE 1
#endif //#ifndef DSDEBUGMODE

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include <SGE.h>
using namespace SGE;
#include "../SGE/Graphics/CFont.h"

// Daniel Schenker
#include "States.h"
#include "Cursor.h"
#include "Button.h"
#include <AI.h>

//=================================================================================================
// Globals
//=================================================================================================

//Cursor
Cursor* gpCursor = NULL;

// Waypoints
 // Start
SVector2 gWaypointStartPos;
SGE_Sprite gWaypointStartSprite;
 // End
SVector2 gWaypointEndPos;
SGE_Sprite gWaypointEndSprite;

// Tiles
const int gkTileWidth = 64;
const int gkTileHeight = 64;
const int gkTileCountHorizontal = /*8*/ StateScreen::kWinWidth / gkTileWidth;
const int gkTileCountVertical = /*8*/ StateScreen::kWinHeight / gkTileHeight;
const int gkTileCount = gkTileCountHorizontal * gkTileCountVertical;
Button** gpTiles = NULL;

//Graph
Graph gGraph;

//Debug
#if DSDEBUGMODE == 1
//Mouse
 //X
CFont gFontMouseX;
char gFontMouseXTextBuff[64];
 //Y
CFont gFontMouseY;
char gFontMouseYTextBuff[64];
//General
 //Debug 1
CFont gFontDebug1;
char gFontDebug1TextBuff[256];
 //Debug 2
CFont gFontDebug2;
char gFontDebug2TextBuff[256];
 //Debug 3
CFont gFontDebug3;
char gFontDebug3TextBuff[256];
#endif //#if DSDEBUGMODE == 1

//=================================================================================================
// Class Definitions
//=================================================================================================

class WalkableFunctor : public IWalkable
{
public:
	//Implements IWalkable
	virtual bool operator()(Node* pNode)
	{
		bool walkable = true;
		int x = pNode->GetID() % gkTileCountHorizontal;
		int y = pNode->GetID() / gkTileCountHorizontal;
		if( x == 0 || x == gkTileCountHorizontal -1 ||
			y == 0 || y == gkTileCountVertical - 1 ||
			(pNode->IsValid() == false) )
		{
			walkable = false;
		}
		return walkable;
	}
};

void SGE_Initialize()
{
	//Cursor
	if(gpCursor == NULL)
	{
		gpCursor = new Cursor(4, 4, "../Data/Textures/Cursor/cursorNormal.png", "../Data/Textures/Cursor/cursorClick.png", StateDepth::Cursor, false);
	}

	// Waypoints
	 // Start
	gWaypointStartPos = SVector2(0.0f, 0.0f);
	gWaypointStartSprite.SetPosition(gWaypointStartPos);
	gWaypointStartSprite.Load("Tiles/GreenUp.png");
	 // End
	gWaypointEndPos = SVector2(0.0f, 0.0f);
	gWaypointEndSprite.SetPosition(gWaypointEndPos);
	gWaypointEndSprite.Load("Tiles/BlueDarkUp.png");

	// Tiles
	//reserve the same space as the amount of tiles that will be on the screen
	gpTiles = new Button* [gkTileCount];

	// Create the tiles
	for(int y = 0; y < gkTileCountVertical; ++y)
	{
		for(int x = 0; x < gkTileCountHorizontal; ++x)
		{
			gpTiles[x + (y * gkTileCountHorizontal)] = new Button(x * gkTileWidth, y * gkTileHeight, gkTileWidth, gkTileHeight, "../Data/Textures/Tiles/RedUp.png", "../Data/Textures/Tiles/RedHover.png", "../Data/Textures/Tiles/RedDown.png", "../Data/Textures/Tiles/Click.png", 0, 2, false, StateDepth::HUD);
		}
	}

	//Build a graph
	int halfTileWidth = gkTileWidth / 2;
	int halfTileHeight = gkTileHeight / 2;
	gGraph.Allocate(gkTileCountHorizontal * gkTileCountVertical);
	for(int y = 0; y < gkTileCountVertical; ++y)
	{
		for(int x = 0; x < gkTileCountHorizontal; ++x)
		{
			const int index = x + (y * gkTileCountHorizontal);
			Node* pNode = gGraph.GetNode(index);
			pNode->SetNeighbor(0, gGraph.GetNode((x + 1) + ((y    ) * gkTileCountHorizontal)));
			pNode->SetNeighbor(1, gGraph.GetNode((x + 1) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(2, gGraph.GetNode((x    ) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(3, gGraph.GetNode((x - 1) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(4, gGraph.GetNode((x - 1) + ((y    ) * gkTileCountHorizontal)));

			pNode->SetNeighbor(5, gGraph.GetNode((x - 1) + ((y + 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(6, gGraph.GetNode((x    ) + ((y + 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(7, gGraph.GetNode((x + 1) + ((y + 1) * gkTileCountHorizontal)));
			/*
			pNode->SetNeighbor(0, gGraph.GetNode((x - 1) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(1, gGraph.GetNode((x    ) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(2, gGraph.GetNode((x + 1) + ((y - 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(3, gGraph.GetNode((x - 1) + ((y    ) * gkTileCountHorizontal)));
			pNode->SetNeighbor(4, gGraph.GetNode((x + 1) + ((y    ) * gkTileCountHorizontal)));
			pNode->SetNeighbor(5, gGraph.GetNode((x - 1) + ((y + 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(6, gGraph.GetNode((x    ) + ((y + 1) * gkTileCountHorizontal)));
			pNode->SetNeighbor(7, gGraph.GetNode((x + 1) + ((y + 1) * gkTileCountHorizontal)));
			*/

			pNode->SetId(index);

			pNode->SetPosition(SVector2(static_cast<float>(halfTileWidth + (x * gkTileWidth)), static_cast<float>(halfTileHeight + (y * gkTileHeight))));
		}
	}

	//Debug
	#if DSDEBUGMODE == 1
	 //Mouse
	  //X
	gFontMouseX.Create(FontType::GARAMOND, 24, false, false);
	gFontMouseX.SetColor(25, 155, 144);
	gFontMouseX.SetTextArea(0, 0, StateScreen::kWinWidth, StateScreen::kWinHeight);
	  //Y
	gFontMouseY.Create(FontType::GARAMOND, 24, false, false);
	gFontMouseY.SetColor(25, 155, 144);
	gFontMouseY.SetTextArea(0, 0, StateScreen::kWinWidth, StateScreen::kWinHeight);
	 //General
	  //Debug 1
	gFontDebug1.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug1.SetColor(150, 50, 100);
	gFontDebug1.SetTextArea(0, 0, StateScreen::kWinWidth, StateScreen::kWinHeight);
	gFontDebug1.SetFormat(FontFormat::RIGHT);
	  //Debug 2
	gFontDebug2.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug2.SetColor(150, 50, 100);
	gFontDebug2.SetTextArea(0, 0, StateScreen::kWinWidth, StateScreen::kWinHeight);
	gFontDebug2.SetFormat(FontFormat::RIGHT);
	  //Debug 3
	gFontDebug3.Create(FontType::GARAMOND, 24, false, false);
	gFontDebug3.SetColor(150, 50, 100);
	gFontDebug3.SetTextArea(0, 0, StateScreen::kWinWidth, StateScreen::kWinHeight);
	gFontDebug3.SetFormat(FontFormat::RIGHT);
	#endif //#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

void SGE_Terminate()
{
	// Cursor
	if(gpCursor != NULL)
	{
		delete gpCursor;
		gpCursor = NULL;
	}

	// Waypoints
	 //Start
	gWaypointStartSprite.Unload();
	 //End
	gWaypointEndSprite.Unload();

	// Tiles
	for(int i = 0; i < gkTileCount; ++i)
	{
		if(gpTiles[i])
		{
			delete gpTiles[i];
			gpTiles[i] = NULL;
		}
	}
	if(gpTiles != NULL)
	{
		delete gpTiles;
		gpTiles = NULL;
	}

	//Graph
	gGraph.Purge();

	// Debug
	#if DSDEBUGMODE == 1
	 // Mouse
	  //X
	gFontMouseX.Destroy();
	  //Y
	gFontMouseY.Destroy();
	 // General
	  //Debug1
	gFontDebug1.Destroy();
	  //Debug2
	gFontDebug2.Destroy();
	  //Debug3
	gFontDebug3.Destroy();
	#endif //#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

bool SGE_Update(float deltaTime)
{
	// Cursor
	if(gpCursor)
	{
		gpCursor->Update(deltaTime);
	}

	// Tiles
	// Cache mouse data
	int mouseX = CDXInput::Get()->GetMouseScreenX();
	int mouseY = CDXInput::Get()->GetMouseScreenY();
	int mouseTileX = mouseX / gkTileWidth;
	int mouseTileY = mouseY / gkTileHeight;
	bool leftMouseButtonPressed = CDXInput::Get()->IsMousePressed(SGE::Mouse::LBUTTON);
	bool rightMouseButtonPressed = CDXInput::Get()->IsMousePressed(SGE::Mouse::RBUTTON);
	bool spaceKeysButtonDown = CDXInput::Get()->IsKeyDown(SGE::Keys::SPACE);

	// Waypoints
	 // Start
	if(leftMouseButtonPressed)
	{
		gWaypointStartPos = SVector2(static_cast<float>(mouseTileX * gkTileWidth), static_cast<float>(mouseTileY * gkTileHeight));
		gWaypointStartSprite.SetPosition(gWaypointStartPos);
	}
	 // End
	if(rightMouseButtonPressed)
	{
		gWaypointEndPos = SVector2(static_cast<float>(mouseTileX * gkTileWidth), static_cast<float>(mouseTileY * gkTileHeight));
		gWaypointEndSprite.SetPosition(gWaypointEndPos);
	}

	//iterator through all tiles (unnecessary, only the tiles that have had the mouse move over them should be updated)
	for(int i = 0; i < gkTileCount; ++i)
	{
		int type = 0;
		if(spaceKeysButtonDown)
		{
			type = 1;
		}
		else
		{
			type = 0;
		}
		gpTiles[i]->Update(deltaTime, mouseX, mouseY, leftMouseButtonPressed, type, false);
		gpTiles[i]->Update(deltaTime, mouseX, mouseY, rightMouseButtonPressed, type, false);
	}

	/*
	// Update "valid" nodes
	for(int i = 0; i < gkTileCount; ++i)
	{
		if(gpTiles[i]->GetType() == 1)
		{
			gGraph.GetNode(i)->SetValid(false);
		}
	}
	*/

	// Graph

	if(Input_IsMousePressed(SGE::Mouse::LBUTTON) || Input_IsMousePressed(SGE::Mouse::RBUTTON))
	{
		//int startX = RandomInt(1, gNumCols - 1);
		//int startY = RandomInt(1, gNumRows - 1);
		//int endX = RandomInt(1, gNumCols - 1);
		//int endY = RandomInt(1, gNumRows - 1);
		//if(startX != endX || startY != endY)
		if(gWaypointStartPos.x != gWaypointEndPos.x || gWaypointStartPos.y != gWaypointEndPos.y)
		{
			int start = (gWaypointStartPos.x / gkTileWidth) + ((gWaypointStartPos.y /  gkTileHeight) * gkTileCountHorizontal);
			int end = (gWaypointEndPos.x / gkTileWidth) + ((gWaypointEndPos.y / gkTileHeight) * gkTileCountHorizontal);
			gGraph.SearchBFS(start, end, WalkableFunctor());
		}
	}

	// Debug
	#if DSDEBUGMODE == 1
	 // Mouse
	  //X
	sprintf_s(gFontMouseXTextBuff, "Mouse X: %d", CDXInput::Get()->GetMouseScreenX());
	  //Y
	sprintf_s(gFontMouseYTextBuff, "Mouse X: %d", CDXInput::Get()->GetMouseScreenX());
	 // General
	  //Debug1
	sprintf_s(gFontDebug1TextBuff, "gkTileCountHorizontal: %d", gkTileCountHorizontal);
	  //Debug2
	sprintf_s(gFontDebug2TextBuff, "gkTileCountVertical: %d", gkTileCountVertical);
	  //Debug3
	sprintf_s(gFontDebug3TextBuff, "gkTileCount: %d", gkTileCount);
	#endif //#if DSDEBUGMODE == 1

	return Input_IsKeyPressed(SGE::Keys::ESCAPE);
}

//-------------------------------------------------------------------------------------------------

void SGE_Render()
{
	// Tiles
	//iterate through all tiles
	for(int i = 0; i < gkTileCount; ++i)
	{
		gpTiles[i]->Render();
	}

	// Waypoints
	 //Start
	gWaypointStartSprite.Render();
	 //End
	gWaypointEndSprite.Render();

	//Cursor
	gpCursor->Render();

	// Graph: test paths
	const NodeList& closedList = gGraph.GetClosedList();
	for(NodeList::const_iterator iter = closedList.begin();
		iter != closedList.end();
		++iter)
	{
		Node* pNode = (*iter);
		if(pNode != NULL && pNode->GetParent() != NULL)
		{
			SVector2 startPoint(pNode->GetPosition());
			SVector2 endPoint(pNode->GetParent()->GetPosition());
			Graphics_DebugLine(startPoint, endPoint, 0x24D177);
		}
	}

	// Graph: result path
	const NodeList& path = gGraph.GetPath();
	for(NodeList::const_iterator iter = path.begin();
		iter != path.end();
		++iter)
	{
		Node* pNode = (*iter);
		if(pNode != NULL && pNode->GetParent() != NULL)
		{
			SVector2 startPoint(pNode->GetPosition());
			SVector2 endPoint(pNode->GetParent()->GetPosition());
			Graphics_DebugLine(startPoint, endPoint, 0x2401FD);
		}
	}

	//Debug
	#if DSDEBUGMODE == 1
	 //Mouse
	  //X
	gFontMouseX.PrintText(gFontMouseXTextBuff, 0, 32);
	  //Y
	gFontMouseY.PrintText(gFontMouseYTextBuff, 0, 64);
	 //General
	  //Debug1
	gFontDebug1.PrintText(gFontDebug1TextBuff, 0, 0);
	  //Debug2
	gFontDebug2.PrintText(gFontDebug2TextBuff, 0, 32);
	  //Debug1
	gFontDebug3.PrintText(gFontDebug3TextBuff, 0, 64);
	#endif //#if DSDEBUGMODE == 1
}