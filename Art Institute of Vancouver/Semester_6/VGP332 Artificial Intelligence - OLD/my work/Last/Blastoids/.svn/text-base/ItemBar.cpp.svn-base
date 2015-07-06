//=================================================================================================
// Filename:	ItemBar.cpp
// Copyright:	Daniel Schenker
// Created:		2012/11/04
// Last Edited:	2012/11/07
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "ItemBar.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------------------------------------

ItemBar::ItemBar(GameContext& gc)
: mpTileTypes(NULL)
, mSpriteCount(0)
, mLastMouseWheelState(Input_GetMouseMoveZ())
, mSelectedNum(0)
, mOffset(0.0f, 0.0f)
{
}

//-------------------------------------------------------------------------------------------------
// //Destructor
//-------------------------------------------------------------------------------------------------

ItemBar::~ItemBar()
{
	delete[] mpTileTypes;
	mpTileTypes = NULL;
}

//-------------------------------------------------------------------------------------------------
// SGE Specific
//-------------------------------------------------------------------------------------------------

bool ItemBar::Load(const char* pTilesFile)
{
	//Clean up before we start loading anything
	Unload();

	//Selected
	mSelectedSprite.Load("Tiles_02/SelectedIcon.png");

	FILE* pFile = NULL;
	fopen_s(&pFile, pTilesFile, "r");

	// Get number of textures
	fscanf_s(pFile, "%*s %d", &mSpriteCount);

	// Create sprite pool
	//mTileTypes.reserve(mSpriteCount);
	mpTileTypes = new SGE_Sprite[mSpriteCount];

	// Load textures
	for(int i = 0; i < mSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		//mTileTypes.push_back(SGE_Sprite());
		//mTileTypes[i].Load(buffer);
		mpTileTypes[i].Load(buffer);

		// Set position of tile icons
		 //Get spacing for tiles to be rendered
		//mTileWidth = mTileTypes[0].GetWidth();
		const int tileWidth = mpTileTypes[0].GetWidth();
		//mTileTypes[i].SetPosition(mOffset.x + (i * tileWidth), mOffset.y);
		mpTileTypes[i].SetPosition(mOffset.x + (i * tileWidth), mOffset.y);
	}

	//Close file
	fclose(pFile);

	return true;
}

//-------------------------------------------------------------------------------------------------

void ItemBar::Unload()
{
	//mTileTypes.clear();

	//Selected
	mSelectedSprite.Unload();

	for(int i = 0; i < mSpriteCount; ++i)
	{
		mpTileTypes[i].Unload();
	}
	delete[] mpTileTypes;
	mpTileTypes = NULL;
}

//-------------------------------------------------------------------------------------------------

void ItemBar::Update()
{
	//Store the current state of the mouse wheel
	int newWheelState = Input_GetMouseMoveZ();

	//If for every click the mouse wheel has been scrolled up
	if(newWheelState > mLastMouseWheelState)
	{
		if(mSelectedNum < mSpriteCount - 1)
		{
			++mSelectedNum;
		}
		else
		{
			mSelectedNum = 0;
		}
	}
	//If for every click the mouse wheel has been scrolled down
	else if(newWheelState < mLastMouseWheelState)
	{
		if(mSelectedNum == 0)
		{
			mSelectedNum = mSpriteCount - 1;
		}
		else
		{
			--mSelectedNum;
		}
	}

	//Update selected sprite icon position
	mSelectedSprite.SetPosition(static_cast<float>(mpTileTypes[0].GetWidth() * mSelectedNum), 0.0f);

	/*
	if(Input_IsKeyPressed(Keys::ONE))
	{
		SetSelected(0);
	}
	else if(Input_IsKeyPressed(Keys::TWO))
	{
		SetSelected(1);
	}
	else if(Input_IsKeyPressed(Keys::THREE))
	{
		SetSelected(2);
	}
	else if(Input_IsKeyPressed(Keys::FOUR))
	{
		SetSelected(3);
	}
	else if(Input_IsKeyPressed(Keys::FIVE))
	{
		SetSelected(4);
	}
	else if(Input_IsKeyPressed(Keys::SIX))
	{
		SetSelected(5);
	}
	else if(Input_IsKeyPressed(Keys::SEVEN))
	{
		SetSelected(6);
	}
	else if(Input_IsKeyPressed(Keys::EIGHT))
	{
		SetSelected(7);
	}
	*/
}

//-------------------------------------------------------------------------------------------------

/*
void ItemBar::Update(int itemInUse)
{
	//TODO
}
*/

//-------------------------------------------------------------------------------------------------

void ItemBar::Render()
{
	// Tile icons
	for(int i = 0; i < mSpriteCount; ++i)
	{
		//mTileTypes[i].Render();
		mpTileTypes[i].Render();
	}

	//Selected
	mSelectedSprite.Render();
}

//-------------------------------------------------------------------------------------------------
// Mutators
//-------------------------------------------------------------------------------------------------

void ItemBar::SetSelected(unsigned int selected)
{
	//if((selected > 0) && (selected < mTileTypes.size()))
	if((selected >= 0) && (selected < mSpriteCount))
	{
		mSelectedNum = selected;
		mSelectedSprite.SetPosition(static_cast<float>(mpTileTypes[0].GetWidth() * mSelectedNum), 0.0f);
	}
}