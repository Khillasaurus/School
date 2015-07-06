//=================================================================================================
// Filename:	Map.cpp
// Copyright:	Daniel Schenker
// Created:		2012/10/16
// Last Edited:	2012/11/06
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#include "Map.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constructor
//-------------------------------------------------------------------------------------------------

Map::Map()
: mColumns(0)
, mRows(0)
, mSelectedNum(-1)
, mSpriteCount(0)
, mSprites(NULL)
, mTiles(NULL)
, mTileSize(0)
///, mStartNum(-1)
///, mEndNum(-1)
{
	// Empty
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Map::~Map()
{
	// Empty
}

//-------------------------------------------------------------------------------------------------

void Map::Load(const char* pLevelFile, const char* pTexturePack)
{
	//Clean up before we start loading anything
	Unload();

	// Load level data
	if(!LoadLevel(pLevelFile))
	{
		Unload();
		return;
	}

	// Load texture pack
	if(!LoadTexturePack(pTexturePack))
	{
		Unload();
		return;
	}

	//Selected
	mSelectedSprite.Load("Tiles_02/Selected.png");

	// Debug
	#if DSDEBUGMODE == 1
	//Cache screen size
	const int kScreenWidth = IniFile_GetInt("WinWidth", 800);
	const int kScreenHeight = IniFile_GetInt("WinHeight", 600);
	// Mouse
	 // World
	  // X
	mFontMouseWorldX.Create(FontType::GARAMOND, 24, false, false);
	mFontMouseWorldX.SetColor(25, 155, 144);
	mFontMouseWorldX.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	  // Y
	mFontMouseWorldY.Create(FontType::GARAMOND, 24, false, false);
	mFontMouseWorldY.SetColor(25, 155, 144);
	mFontMouseWorldY.SetTextArea(0, 0, kScreenWidth, kScreenHeight);
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

void Map::Unload()
{
	// Release memory
	if(mTiles != NULL)
	{
		delete[] mTiles;
		mTiles = NULL;
	}
	if(mSprites != NULL)
	{
		delete[] mSprites;
		mSprites = NULL;
	}

	//Selected
	mSelectedSprite.Unload();

	// Reset params
	mColumns = 0;
	mRows = 0;
	mSelectedNum = -1;
	mSpriteCount = 0;
	mTileSize = 0;

	// Debug
	#if DSDEBUGMODE == 1
	// Mouse
	 // World
	  //X
	mFontMouseWorldX.Destroy();
	  //Y
	mFontMouseWorldY.Destroy();
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------

bool Map::Update(const SVector2& screenCoordinatesCursorPos, const SVector2& renderOffset, int type)
{
	bool modified = false;

	//Convert the cursor from screen coordinates to world coordinates
	SVector2 worldCoordinatesCursorPos = SVector2(-renderOffset.x, -renderOffset.y) + screenCoordinatesCursorPos;

	//Get the vector from the top left of the map to the cursor in world coordinates
	SVector2 offset = worldCoordinatesCursorPos - mTiles[0].GetPosition();

	// If the cursor is within the boundaries of the map
	if( offset.x >= 0.0f &&
		offset.y >= 0.0f &&
		offset.x < mColumns * mTileSize &&
		offset.y < mRows * mTileSize )
	{
		//Store which tile the cursor is on
		const int cursorColumn = offset.x / mTileSize;
		const int cursorRow = offset.y / mTileSize;
		mSelectedNum = (cursorRow * mColumns) + cursorColumn;

		//Move the selected sprite to the tile that the cursor is on
		mSelectedSprite.SetPosition(mTiles[mSelectedNum].GetPosition());

		//If the cursor is pressed, set the tile type accordingly
		if(Input_IsMousePressed(Mouse::LBUTTON))
		{
			modified = true;
			/*
			//If the type can be placed in multiple locations at once
			if(type > 1)
			{
				//Check if the tile is being placed on a singular placement tile
				if(mSelectedNum == mStartNum)
				{
					mStartNum = -1;
				}
				else if(mSelectedNum == mEndNum)
				{
					mEndNum = -1;
				}
				*/
				mTiles[mSelectedNum].SetType(type);
				/*
			}
			else
			{
				//For each type...
				if(type == 0)
				{
					//If the singular placement tile have been placed yet
					if(mStartNum >= 0)
					{
						//Set the old tile to the default tile type
						mTiles[mStartNum].SetType(2);
					}
					//Set the new tile type
					mTiles[mSelectedNum].SetType(0);
				}
				else if(type == 1)
				{
					//If the singular placement tile have been placed yet
					if(mEndNum >= 0)
					{
						//Set the old tile to the default tile type
						mTiles[mStartNum].SetType(2);
					}

					//Set the new tile type
					mTiles[mSelectedNum].SetType(1);
				}
			}
			*/
		}
	}
	else
	{
		//Set the tile that the cursor is on to none (invalid tile pos)
		mSelectedNum = -1;
	}


	// Debug
	#if DSDEBUGMODE == 1
	// Mouse
	 // World
	  //X
	//sprintf_s(mFontMouseWorldXTextBuff, "Mouse World X: %d", 0);
	sprintf_s(mFontMouseWorldXTextBuff, "Render Offset X: %f", renderOffset.x);
	  //Y
	//sprintf_s(mFontMouseWorldYTextBuff, "Mouse World Y: %d", 0);
	sprintf_s(mFontMouseWorldYTextBuff, "Render Offset Y: %f", renderOffset.y);
	#endif//#if DSDEBUGMODE == 1

	return modified;
}

//-------------------------------------------------------------------------------------------------

void Map::Render(const SVector2& offset)
{
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			const SVector2& pos = mTiles[index].GetPosition();
			const int type = mTiles[index].GetType();
			mSprites[type].SetPosition(pos + offset);
			mSprites[type].Render();
		}
	}

	//Selected
	if(mSelectedNum >= 0)
	{
		mSelectedSprite.SetPosition(mTiles[mSelectedNum].GetPosition());
		//mSelectedSprite.Render();
	}

	// Debug
	#if DSDEBUGMODE == 1
	// Mouse
	 // World
	  //X
	mFontMouseWorldX.PrintText(mFontMouseWorldXTextBuff, 0, 96);
	  //Y
	mFontMouseWorldY.PrintText(mFontMouseWorldYTextBuff, 0, 128);
	#endif//#if DSDEBUGMODE == 1
}

//-------------------------------------------------------------------------------------------------
// General
//-------------------------------------------------------------------------------------------------

SRect Map::GetBoudingBoxFromSegment(const SLineSegment& line) const
{
	// Validate the line segment
	if( line.from.x < 0.0f || line.from.x > GetWidth() ||
		line.from.y < 0.0f || line.from.y > GetHeight() ||
		line.to.x < 0.0f || line.to.x > GetWidth() ||
		line.to.y < 0.0f || line.to.y > GetHeight() )
	{
		// Line segment is out of bound!
		return SRect();
	}

	// Convert position to indices
	const int fromX = static_cast<int>(line.from.x) / mTileSize;
	const int fromY = static_cast<int>(line.from.y) / mTileSize;
	const int toX = static_cast<int>(line.to.x) / mTileSize;
	const int toY = static_cast<int>(line.to.y) / mTileSize;

	// Calculate tile count
	const int countX = toX - fromX + 1;
	const int countY = toY - fromY + 1;

	// Get region
	SRect region;
	for(int y = 0; y < countY; ++y)
	{
		for(int x = 0; x < countX; ++x)
		{
			const int index = (fromX + x) + ((fromY + y) * mColumns);
			if(!mTiles[index].IsWalkable())
			{
				region += mTiles[index].GetBoundingBox();
			}
		}
	}
	return region;
}

//-------------------------------------------------------------------------------------------------

bool Map::SaveLevel(const char* pLevelFile)
{
	if(mTiles != NULL)
	{
		FILE* pFile = NULL;
		fopen_s(&pFile, pLevelFile, "w");

		if(pFile != NULL)
		{
			// Write map dimensions
			fprintf_s(pFile, "%s %d\n", "Columns: ", mColumns);
			fprintf_s(pFile, "%s %d\n", "Rows: ", mRows);
			fprintf_s(pFile, "%s %d\n", "TileSize: ", mTileSize);

			int tileType = 0;

			// Write tile data
			for(int y = 0; y < mRows; ++y)
			{
				for(int x = 0; x < mColumns; ++x)
				{
					const int index = x + (y * mColumns);
					//fprintf_s(pFile, "%d", mTiles[index].GetType());
					tileType = mTiles[index].GetType();
					if(tileType < 10)
					{
						fprintf_s(pFile, " ");
					}
					fprintf_s(pFile, " %d", mTiles[index].GetType());
				}
				fprintf_s(pFile, "\n");
			}

			//Close file
			fclose(pFile);
			return true;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------------------------------

int Map::GetMapOriginWorldCoordinatesX() const
{
	return mTiles->GetPosition().x;
}

//-------------------------------------------------------------------------------------------------

int Map::GetMapOriginWorldCoordinatesY() const
{
	return mTiles->GetPosition().y;
}

//-------------------------------------------------------------------------------------------------

bool Map::LoadLevel(const char* pLevelFile)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pLevelFile, "r");

	// Read map dimensions
	fscanf_s(pFile, "%*s %d", &mColumns);
	fscanf_s(pFile, "%*s %d", &mRows);
	fscanf_s(pFile, "%*s %d", &mTileSize);

	// Create tile buffer
	mTiles = new Tile[mColumns * mRows];

	int tileType = 0;

	// Parse tile data
	fgetc(pFile);
	for(int y = 0; y < mRows; ++y)
	{
		for(int x = 0; x < mColumns; ++x)
		{
			const int index = x + (y * mColumns);
			mTiles[index].SetPosition(SVector2(static_cast<float>(x * mTileSize), static_cast<float>(y * mTileSize)));
			mTiles[index].SetSize(mTileSize);
			//mTiles[index].SetType(fgetc(pFile) - '0');
			fscanf_s(pFile, "%d", &tileType);
			mTiles[index].SetType(tileType);
			//mTiles[index].SetWalkable(); TODO
		}
		fgetc(pFile);
	}

	//Close file
	fclose(pFile);
	return true;
}

//-------------------------------------------------------------------------------------------------

bool Map::LoadTexturePack(const char* pTexturePack)
{
	FILE* pFile = NULL;
	fopen_s(&pFile, pTexturePack, "r");

	// Get number of textures
	fscanf_s(pFile, "%*s %d", &mSpriteCount);

	// Create sprite pool
	mSprites = new SGE_Sprite[mSpriteCount];

	// Load textures
	for(int i = 0; i < mSpriteCount; ++i)
	{
		char buffer[128];
		fscanf_s(pFile, "%s", buffer, 128);
		mSprites[i].Load(buffer);
	}

	//Close file
	fclose(pFile);
	return true;
}

//-------------------------------------------------------------------------------------------------