//=================================================================================================
// File:		cDSCursor.cpp
// Created:		2012/08/19
// Last Edited:	2012/10/15
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Daniel Schenker
#include "Cursor.h"

//// SGE
//#include "Input/Input.h"
//#include "graphics/CSprite.h"
//#include "graphics/CTexture.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constuctors
//-------------------------------------------------------------------------------------------------

Cursor::Cursor(D3DXVECTOR2 offset, const char* normalTexture, const char* clickTexture, float depth, const bool inMenu)
:	mOffsetX(static_cast<int>(offset.x))
,	mOffsetY(static_cast<int>(offset.y))
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::Cursor)
,	mInMenu(inMenu)
{
	mNormalTexture.Load(normalTexture);
	mClickTexture.Load(clickTexture);
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

Cursor::Cursor(int offsetX, int offsetY, const char* normalTexture, const char* clickTexture, float depth, const bool inMenu)
:	mOffsetX(offsetX)
,	mOffsetY(offsetY)
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::Cursor)
,	mInMenu(inMenu)
{
	mNormalTexture.Load(normalTexture);
	mClickTexture.Load(clickTexture);
	mSprite.SetDepth(mDepth);
}

//-------------------------------------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------------------------------------

Cursor::~Cursor()
{
	mNormalTexture.Unload();
	mClickTexture.Unload();
}

//-------------------------------------------------------------------------------------------------
// SGE Specific
//-------------------------------------------------------------------------------------------------

void Cursor::Update(float deltaTime)
{
	//Position
	//if the user is not in a menu that can be controlled without the mouse
	if(!mInMenu)
	{
		mSprite.SetPosition(static_cast<float>(CDXInput::Get()->GetMouseScreenX() - mOffsetX), static_cast<float>(CDXInput::Get()->GetMouseScreenY() - mOffsetY));
	}

	//Texture
	 //Update the current state of the left mouse button variable
	//if the left mouse button is up
	if(!CDXInput::Get()->IsMouseDown(SGE::Mouse::LBUTTON))
	{
		mCurState = 0;
	}
	//else the left mouse button is down
	else
	{
		mCurState = 1;
	}

	//if the current state of the mouse is NOT equal to the last state
	if(mCurState != mLastState)
	{
		//update current state
		mLastState = mCurState;

		//Update the texture of the mouse
		mSprite.ClearTextures();
		//if the left mouse button is up
		if(mCurState == 0)
		{
			mSprite.AddTexture(&mNormalTexture);
		}
		//else the left mouse button is down
		else
		{
			mSprite.AddTexture(&mClickTexture);
		}
	}
}

//-------------------------------------------------------------------------------------------------

void Cursor::Render()
{
	mSprite.Render();
}

//-------------------------------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------------------------------

float Cursor::GetDepth() const
{
	return mDepth;
}

//----------------------------------------------------------------------------------------------------

bool Cursor::GetInMenu() const
{
	return mInMenu;
}

//-------------------------------------------------------------------------------------------------
// Mutators
//-------------------------------------------------------------------------------------------------

void Cursor::SetDepth(float depth)
{
	//if the depth is valid
	if(depth >= 0 && depth <= 1)
	{
		mDepth = depth;
		mSprite.SetDepth(mDepth);
	}
	//else throw error
	else
	{
		OutputDebugStringA("ERROR: The depth buffer must be between 0.0f and 1.0f. Leavig the depth as it was previously. - void cDSCursor::SetDepth(float depth)\n");
	}
}

//-------------------------------------------------------------------------------------------------

void Cursor::SetInMenu(bool inMenu)
{
	mInMenu = inMenu;
}