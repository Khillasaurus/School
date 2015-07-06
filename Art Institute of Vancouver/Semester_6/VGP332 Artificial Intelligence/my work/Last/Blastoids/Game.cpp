//=================================================================================================
// Filename:	Game.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/23
// Last Edited:	2012/11/09
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// Daniel Schenker
#include "Game.h"
#include "GameStates.h"

//=================================================================================================
// Globals
//=================================================================================================

int gColumns = -1;
int gRows = -1;

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Functors
//-------------------------------------------------------------------------------------------------

class WalkableFunctor : public IWalkable
{
public:
	//Implements IWalkable
	virtual bool operator()(Node* pNode)
	{
		bool walkable = true;
		int x = pNode->GetID() % gColumns;
		int y = pNode->GetID() / gColumns;
		if( x == 0 || x == gColumns -1 ||
			y == 0 || y == gRows - 1 ||
			(pNode->IsValid() == false) )
		{
			walkable = false;
		}
		return walkable;
	}
};

class CostFunctor : public ICost
{
public:
	CostFunctor(Tile* pTiles)
	: mpTiles(pTiles)
	{}

	Tile* mpTiles;

	//Implements IWalkable
	virtual float operator()(Node* pNodeA, Node* pNodeB)
	{
		float cost =  0.0f;

		int mTypeA = (mpTiles[pNodeA->GetID()].GetType());
		int mTypeB = (mpTiles[pNodeB->GetID()].GetType());

		if(mTypeA == 0)
		{
			if(mTypeB == 0)
			{
				cost = 1.0f;
			}
			else if(mTypeB == 1)
			{
				cost = 2.0f;
			}
			else
			{
				cost = 500.0f;
			}
		}
		else if(mTypeA == 1)
		{
			if(mTypeB == 0)
			{
				cost = 2.0f;
			}
			else if(mTypeB == 1)
			{
				cost = 1.0f;
			}
			else
			{
				cost = 500.0f;
			}
		}
		else
		{
			cost = 1000.0f;
		}
		return cost;
	}
};

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

Game::Game(GameContext& gc)
: BaseState(gc)
, mSearchType(Search::kBFS)
, mAILastMouseWheelState(Input_GetMouseMoveZ())
, mWaypointStartPos(0.0f, 0.0f)
, mWaypointEndPos(0.0f, 0.0f)
, mCurrentMode(Mode::kStandard)
, mRenderOffset(0.0f, 0.0f)
, mDefaultScrollRate(16)
, mScrollRate(mDefaultScrollRate)
, mItemBar(gc)
, mMapModified(false)
{
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Game::~Game()
{
}

//-------------------------------------------------------------------------------------------------
// Implements BaseState
//-------------------------------------------------------------------------------------------------

void Game::Load()
{
	//Cursor
	mCursor.Load("PeterChan/sword.png");

	// Character
	mCharacter.Load();
	mCharacter.SetPosition(SVector2(100.0f, 100.0f));

	//Item Bar
	mItemBar.Load("texturepacktileicons.txt");

	// Map
	if(mGameContext.GetLevel() == 0)
	{
		mMap.Load("level_space_01.txt", "texturepack_space.txt");
	}
	else
	{
		mMap.Load("level_space_01.txt", "texturepack_space.txt");
	}

	gColumns = mMap.GetColumns();
	gRows = mMap.GetRows();

	//AI
	AIInitialize();
}

//-------------------------------------------------------------------------------------------------

void Game::Unload()
{
	//Cursor
	mCursor.Unload();

	//Character
	mCharacter.Unload();

	//Map
	mMap.Unload();

	//AI
	AITerminate();
}

//-------------------------------------------------------------------------------------------------

int Game::Update(float deltaTime)
{
	//Update current mode
	if(Input_IsKeyPressed(Keys::F1))
	{
		mCurrentMode = Mode::kStandard;
	}
	else if(Input_IsKeyPressed(Keys::F2))
	{
		mCurrentMode = Mode::kSearchControl;
	}
	else if(Input_IsKeyPressed(Keys::F3))
	{
		mCurrentMode = Mode::kMapEditor;
	}

	//Cursor
	mCursor.Update(deltaTime);

	// Update based on what the current mode is
	if(mCurrentMode == Mode::kStandard)
	{
		//Character
		mCharacter.Update(deltaTime, mMap);
	}
	else if(mCurrentMode == Mode::kSearchControl)
	{
		if(AIUpdate())
		{
			AISearch(mSearchType);
		}
	}
	else if(mCurrentMode == Mode::kMapEditor)
	{
		mMapModified = mMap.Update(SVector2(static_cast<float>(Input_GetMouseScreenX()), static_cast<float>(Input_GetMouseScreenY())), mRenderOffset, mItemBar.GetSelected());

		//If the map has been modified
		if(mMapModified)
		{
			//Update the graph
			AIUpdateGraph();

			//Update the path
			AISearch(mSearchType);
		}

		if(Input_IsKeyPressed(Keys::S))//change to a button that appears only when in the map editor mode instead of only being able to press a magic keyboard button, but keep the magic button functionality as a hotkey
		{
			mMap.SaveLevel("leveltest.txt");
		}

		mItemBar.Update();
	}

	// GameState
	GameState::Type nextState = GameState::Invalid;
	if(Input_IsKeyPressed(Keys::ESCAPE))
	{
		nextState = GameState::Frontend;
	}
	return nextState;
}

//-------------------------------------------------------------------------------------------------

void Game::Render()
{
	//Cache data
	const int kScreenWidth = IniFile_GetInt("WinWidth", 1280);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 720);
	const int kMapWidth = mMap.GetWidth();
	const int kMapHeight = mMap.GetHeight();

	if(mCurrentMode == Mode::kStandard)
	{
		const SVector2 kTarget = mCharacter.GetPosition();

		mRenderOffset.x = (kScreenWidth * 0.5f) - kTarget.x;
		mRenderOffset.x = Clamp(mRenderOffset.x, (float)kScreenWidth - kMapWidth, 0.0f);
		mRenderOffset.y = (kScreenHeight * 0.5f) - kTarget.y;
		mRenderOffset.y = Clamp(mRenderOffset.y, (float)kScreenHeight - kMapHeight, 0.0f);
	}
	else
	{
		// Offset
		if(Input_GetMouseScreenX() < (static_cast<float>(kScreenWidth) * 0.1f))
		{
			mRenderOffset = SVector2(mRenderOffset.x + mScrollRate, mRenderOffset.y);
		}
		else if(Input_GetMouseScreenX() > (static_cast<float>(kScreenWidth) * 0.9f))
		{
			mRenderOffset = SVector2(mRenderOffset.x - mScrollRate, mRenderOffset.y);
		}
		if(Input_GetMouseScreenY() < (static_cast<float>(kScreenHeight) * 0.1f))
		{
			mRenderOffset = SVector2(mRenderOffset.x, mRenderOffset.y + mScrollRate);
		}
		else if(Input_GetMouseScreenY() > (static_cast<float>(kScreenHeight) * 0.9f))
		{
			mRenderOffset = SVector2(mRenderOffset.x, mRenderOffset.y - mScrollRate);
		}
	}

	//Map
	mMap.Render(mRenderOffset);

	//Character
	//mCharacter.Render(mRenderOffset);

	AIRender(mRenderOffset);

	// Render based on what the current mode is
	if(mCurrentMode == Mode::kMapEditor)
	{
		//Item Bar
		mItemBar.Render();
	}

	//Cursor
	mCursor.Render();
}

//-------------------------------------------------------------------------------------------------

void Game::AIInitialize()
{
	// Waypoints
	 // Start
	mWaypointStartSprite.Load("Tiles_02/S.png");
	 // End
	mWaypointEndSprite.Load("Tiles_02/E.png");

	//Build a graph
	 //Cache frequently used values
	const int kTileWidth = mMap.GetTileSize();
	const int kTileHeight = mMap.GetTileSize();
	const int kHalfTileWidth = kTileWidth * 0.5;
	const int kHalfTileHeight = kTileHeight * 0.5;
	const int kColumnCount = mMap.GetColumns();
	const int kRowCount = mMap.GetRows();

	mGraph.Allocate(kColumnCount * kRowCount);
	for(int y = 0; y < kRowCount; ++y)
	{
		for(int x = 0; x < kColumnCount; ++x)
		{
			const int index = x + (y * kColumnCount);
			Node* pNode = mGraph.GetNode(index);
			pNode->SetNeighbor(0, mGraph.GetNode((x + 1) + ((y    ) * kColumnCount)));
			pNode->SetNeighbor(1, mGraph.GetNode((x + 1) + ((y - 1) * kColumnCount)));
			pNode->SetNeighbor(2, mGraph.GetNode((x    ) + ((y - 1) * kColumnCount)));
			pNode->SetNeighbor(3, mGraph.GetNode((x - 1) + ((y - 1) * kColumnCount)));
			pNode->SetNeighbor(4, mGraph.GetNode((x - 1) + ((y    ) * kColumnCount)));
			pNode->SetNeighbor(5, mGraph.GetNode((x - 1) + ((y + 1) * kColumnCount)));
			pNode->SetNeighbor(6, mGraph.GetNode((x    ) + ((y + 1) * kColumnCount)));
			pNode->SetNeighbor(7, mGraph.GetNode((x + 1) + ((y + 1) * kColumnCount)));

			pNode->SetId(index);
			if(mMap.GetTiles()[index].GetType() > 1)
			{
				pNode->SetValid(false);
			}

			pNode->SetPosition(SVector2(static_cast<float>(kHalfTileWidth + (x * kTileWidth)), static_cast<float>(kHalfTileHeight + (y * kTileHeight))));
		}
	}
}

//-------------------------------------------------------------------------------------------------

void Game::AITerminate()
{
	// Waypoints
	 //Start
	mWaypointStartSprite.Unload();
	 //End
	mWaypointEndSprite.Unload();

	//Graph
	mGraph.Purge();
}

//-------------------------------------------------------------------------------------------------

bool Game::AIUpdate()
{
	bool shouldSearchAgain = false;

	//Store the current state of the mouse wheel
	int newWheelState = Input_GetMouseMoveZ();

	//If for every click the mouse wheel has been scrolled up
	if(newWheelState > mAILastMouseWheelState)
	{
		if(mSearchType < Search::kMax - 1)
		{
			mSearchType = (Search::eSearchType)(mSearchType + 1);
		}
		else
		{
			mSearchType = (Search::eSearchType)0;
		}
		shouldSearchAgain = true;
	}
	//Else if for every click the mouse wheel has been scrolled down
	else if(newWheelState < mAILastMouseWheelState)
	{
		if(mSearchType > Search::kInvalid + 1)
		{
			mSearchType = (Search::eSearchType)(mSearchType - 1);
		}
		else
		{
			mSearchType = (Search::eSearchType)((int)(Search::kMax) - 1);
		}
		shouldSearchAgain = true;
	}

	// Waypoints
	 //Cache frequently used values
	const int kTileWidth = mMap.GetTileSize();
	const int kTileHeight = mMap.GetTileSize();
	const int kHalfTileWidth = kTileWidth * 0.5;
	const int kHalfTileHeight = kTileHeight * 0.5;
	const int kColumnCount = mMap.GetColumns();
	const int kRowCount = mMap.GetRows();
	
	//Convert the cursor from screen coordinates to world coordinates
	SVector2 worldCoordinatesCursorPos = SVector2(-mRenderOffset.x, -mRenderOffset.y) + SVector2(Input_GetMouseScreenX(), Input_GetMouseScreenY());
	
	//Get the vector from the top left of the map to the cursor in world coordinates
	SVector2 mOriginWorldCoordinates(mMap.GetMapOriginWorldCoordinatesX(), mMap.GetMapOriginWorldCoordinatesY());
	SVector2 offset = worldCoordinatesCursorPos - mOriginWorldCoordinates;

	//Store which tile the cursor is on
	const int cursorColumn = offset.x / kTileWidth;
	const int cursorRow = offset.y / kTileHeight;

	// If the cursor is within the boundaries of the map
	if( offset.x >= 0.0f &&
		offset.y >= 0.0f &&
		offset.x < kColumnCount * kTileWidth &&
		offset.y < kRowCount * kTileHeight )
	{
		 // Start
		if(Input_IsMousePressed(Mouse::LBUTTON))
		{
			mWaypointStartPos = SVector2(static_cast<float>(mOriginWorldCoordinates.x + (cursorColumn * kTileWidth)), static_cast<float>(mOriginWorldCoordinates.y + (cursorRow * kTileHeight)));
			mWaypointStartSprite.SetPosition(mWaypointStartPos);
		}
		 // End
		if(Input_IsMousePressed(Mouse::RBUTTON))
		{
			mWaypointEndPos = SVector2(static_cast<float>(mOriginWorldCoordinates.x + (cursorColumn * kTileWidth)), static_cast<float>(mOriginWorldCoordinates.y + (cursorRow * kTileHeight)));
			mWaypointEndSprite.SetPosition(mWaypointEndPos);
		}

		// Graph
		if(Input_IsMousePressed(Mouse::LBUTTON) || Input_IsMousePressed(Mouse::RBUTTON))
		{
			//int startX = RandomInt(1, gNumCols - 1);
			//int startY = RandomInt(1, gNumRows - 1);
			//int endX = RandomInt(1, gNumCols - 1);
			//int endY = RandomInt(1, gNumRows - 1);
			//if(startX != endX || startY != endY)
			if(mWaypointStartPos.x != mWaypointEndPos.x || mWaypointStartPos.y != mWaypointEndPos.y)
			{
				int start = (mWaypointStartPos.x / kTileWidth) + ((mWaypointStartPos.y /  kTileHeight) * kColumnCount);
				int end = (mWaypointEndPos.x / kTileWidth) + ((mWaypointEndPos.y / kTileHeight) * kColumnCount);
				AISearch(mSearchType);
			}
		}
	}
	return shouldSearchAgain;
}

//-------------------------------------------------------------------------------------------------

void Game::AIUpdateGraph()
{
	// Cache frequently used values
	const int kTileWidth = mMap.GetTileSize();
	const int kTileHeight = mMap.GetTileSize();
	const int kHalfTileWidth = kTileWidth * 0.5;
	const int kHalfTileHeight = kTileHeight * 0.5;
	const int kColumnCount = mMap.GetColumns();
	const int kRowCount = mMap.GetRows();

	for(int y = 0; y < kRowCount; ++y)
	{
		for(int x = 0; x < kColumnCount; ++x)
		{
			const int index = x + (y * kColumnCount);
			Node* pNode = mGraph.GetNode(index);

			if(mMap.GetTiles()[index].GetType() < 2)
			{
				pNode->SetValid(true);
			}
			else
			{
				pNode->SetValid(false);
			}

			pNode->SetPosition(SVector2(static_cast<float>(kHalfTileWidth + (x * kTileWidth)), static_cast<float>(kHalfTileHeight + (y * kTileHeight))));
		}
	}

	mMapModified = false;
}

//-------------------------------------------------------------------------------------------------

void Game::AISearch(Search::eSearchType searchType)
{
	const int kTileWidth = mMap.GetTileSize();
	const int kTileHeight = mMap.GetTileSize();
	const int kColumnCount = mMap.GetColumns();
	const int kRowCount = mMap.GetRows();

	const int start = (mWaypointStartPos.x / kTileWidth) + ((mWaypointStartPos.y /  kTileHeight) * kColumnCount);
	const int end = (mWaypointEndPos.x / kTileWidth) + ((mWaypointEndPos.y / kTileHeight) * kColumnCount);

	if(searchType == Search::kBFS)
	{
		mGraph.SearchBFS(start, end, WalkableFunctor());
	}
	else if(searchType == Search::kDFS)
	{
		mGraph.SearchDFS(start, end, WalkableFunctor());
	}
	else if(searchType == Search::kDijkstra)
	{
		mGraph.SearchDijkstra(start, end, WalkableFunctor(), CostFunctor(const_cast<Tile*>(mMap.GetTiles())));
	}
}

//-------------------------------------------------------------------------------------------------

void Game::AIRender(const SVector2& offset)
{
	// Waypoints
	 //Start
	mWaypointStartSprite.SetPosition(mWaypointStartPos.x + offset.x, mWaypointStartPos.y + offset.y);
	mWaypointStartSprite.Render();
	 //End
	mWaypointEndSprite.SetPosition(mWaypointEndPos.x + offset.x, mWaypointEndPos.y + offset.y);
	mWaypointEndSprite.Render();

	// Graph: test paths
	const NodeList& closedList = mGraph.GetClosedList();
	for(NodeList::const_iterator iter = closedList.begin();
		iter != closedList.end();
		++iter)
	{
		Node* pNode = (*iter);
		if(pNode != NULL && pNode->GetParent() != NULL)
		{
			SVector2 startPoint(pNode->GetPosition());
			SVector2 endPoint(pNode->GetParent()->GetPosition());
			Graphics_DebugLine(startPoint + mRenderOffset, endPoint + mRenderOffset, 0x24D177);
		}
	}

	// Graph: result path
	const NodeList& path = mGraph.GetPath();
	for(NodeList::const_iterator iter = path.begin();
		iter != path.end();
		++iter)
	{
		Node* pNode = (*iter);
		if(pNode != NULL && pNode->GetParent() != NULL)
		{
			SVector2 startPoint(pNode->GetPosition());
			SVector2 endPoint(pNode->GetParent()->GetPosition());
			Graphics_DebugLine(startPoint + mRenderOffset, endPoint + mRenderOffset, 0x2401FD);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// Mutators
//-------------------------------------------------------------------------------------------------

void Game::SetWaypointStartPos(const SVector2& pos)
{
	//Not a guaranteed safety check, but it does eliminate some invalid values immediately
	if( pos.x >= 0 &&
		pos.x < mGraph.GetNumNodes() &&
		pos.y >= 0 &&
		pos.y < mGraph.GetNumNodes() )
	{
		mWaypointStartPos = pos;
	}
}

//-------------------------------------------------------------------------------------------------

void Game::SetWaypointEndPos(const SVector2& pos)
{
	//Not a guaranteed safety check, but it does eliminate some invalid values immediately
	if( pos.x >= 0 &&
		pos.x < mGraph.GetNumNodes() &&
		pos.y >= 0 &&
		pos.y < mGraph.GetNumNodes() )
	{
		mWaypointEndPos = pos;
	}
}