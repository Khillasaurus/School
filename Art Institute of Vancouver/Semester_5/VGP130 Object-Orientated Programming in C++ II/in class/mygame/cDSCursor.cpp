//====================================================================================================
//File:			cDSCursor.cpp
//Created:		2012/08/19
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

//Daniel Schenker
#include "cDSCursor.h"
#include "cDSApp.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSCursor::cDSCursor(D3DXVECTOR2 offset, const char* normalTexture, const char* clickTexture, float depth = 0.0f, const bool inMenu = false)
:	mOffsetX(offset.x)
,	mOffsetY(offset.y)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthCursor)
,	mInMenu(inMenu)
{
	mNormalTexture.Load(normalTexture);
	mClickTexture.Load(clickTexture);
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

cDSCursor::cDSCursor(int offsetX, int offsetY, const char* normalTexture, const char* clickTexture, float depth = 0.0f, const bool inMenu = false)
:	mOffsetX(offsetX)
,	mOffsetY(offsetY)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthCursor)
,	mInMenu(inMenu)
{
	mNormalTexture.Load(normalTexture);
	mClickTexture.Load(clickTexture);
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------

void cDSCursor::Update()
{
	//Position
	//if the user is not in a menu that can be controlled without the mouse
	if(!mInMenu)
	{
		mSprite.SetPositionX(static_cast<float>(CDXInput::Get()->GetMouseScreenX() - mOffsetX));
		mSprite.SetPositionY(static_cast<float>(CDXInput::Get()->GetMouseScreenY() - mOffsetY));
	}

	//Texture
	 //Update the current state of the left mouse button variable
	//if the left mouse button is up
	if(!CDXInput::Get()->IsMouseDown(0))
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

//----------------------------------------------------------------------------------------------------

void cDSCursor::Render()
{
	mSprite.Render();
}

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

float cDSCursor::GetDepth() const
{
	return mDepth;
}

//----------------------------------------------------------------------------------------------------

bool cDSCursor::GetInMenu() const
{
	return mInMenu;
}

//----------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------

void cDSCursor::SetDepth(float depth)
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
		OutputDebugString(TEXT("ERROR: The depth buffer must be between 0.0f and 1.0f. Leavig the depth as it was previously. - void cDSCursor::SetDepth(float depth)\n"));
	}
}

//----------------------------------------------------------------------------------------------------

void cDSCursor::SetInMenu(bool inMenu)
{
	mInMenu = inMenu;
}