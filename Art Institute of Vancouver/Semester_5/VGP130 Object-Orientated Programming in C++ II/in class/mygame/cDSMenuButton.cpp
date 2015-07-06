//====================================================================================================
//File:			cDSMenuButton.cpp
//Created:		2012/08/18
//Copyright:	Daniel Schenker
//====================================================================================================

//====================================================================================================
//Includes
//====================================================================================================

//Precompiled headers
#include "stdafx.h"

// SGE
//#include "graphics/CSprite.h"
//#include "graphics/CTexture.h"

//Daniel Schenker
#include "cDSMenuButton.h"
#include "cDSApp.h"

//====================================================================================================
//Class Definitions
//====================================================================================================

//----------------------------------------------------------------------------------------------------
//Constuctors
//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton()
:	mDepth(cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(false)
{
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(D3DXVECTOR2 origin, int width, int height, bool originCentered = false)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth(cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(int originX, int originY, int width, int height, bool originCentered = false)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth(cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(D3DXVECTOR2 origin, int width, int height, bool originCentered = false, float depth = cDSApp::msDepthButton)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(int originX, int originY, int width, int height, bool originCentered = false, float depth = cDSApp::msDepthButton)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth(cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(true)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);

	//Texture
	mUpTexture.Load(upTexture);
	mHoverTexture.Load(hoverTexture);
	mDownTexture.Load(downTexture);
	mClickTexture.Load(clickTexture);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth(cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(true)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);

	//Texture
	mUpTexture.Load(upTexture);
	mHoverTexture.Load(hoverTexture);
	mDownTexture.Load(downTexture);
	mClickTexture.Load(clickTexture);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false, float depth = cDSApp::msDepthButton)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(true)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);

	//Texture
	mUpTexture.Load(upTexture);
	mHoverTexture.Load(hoverTexture);
	mDownTexture.Load(downTexture);
	mClickTexture.Load(clickTexture);
}

//----------------------------------------------------------------------------------------------------

cDSMenuButton::cDSMenuButton(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false, float depth = cDSApp::msDepthButton)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthButton)
,	mBeenPressed(false)
,	mButtonState(ButtonState::kUp)
,	mTexturesLoaded(true)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= (0.5 * width);
		mOriginY -= (0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);

	//Texture
	mUpTexture.Load(upTexture);
	mHoverTexture.Load(hoverTexture);
	mDownTexture.Load(downTexture);
	mClickTexture.Load(clickTexture);
}

//----------------------------------------------------------------------------------------------------
//Deconstuctors
//----------------------------------------------------------------------------------------------------

cDSMenuButton::~cDSMenuButton()
{
	//Unload textures (existence of textures checked inside Unload() function)
	mUpTexture.Unload();
	mHoverTexture.Unload();
	mDownTexture.Unload();
	mClickTexture.Unload();
}

//----------------------------------------------------------------------------------------------------
//General Member Functions
//----------------------------------------------------------------------------------------------------

void cDSMenuButton::LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)
{
	//if no textures are already loaded
	if(!mTexturesLoaded)
	{
		//Load new textures
		mUpTexture.Load(upTexture);
		mHoverTexture.Load(hoverTexture);
		mDownTexture.Load(downTexture);
		mClickTexture.Load(clickTexture);

		//Set flag
		mTexturesLoaded = true;
	}
	//else throw error
	else
	{
		OutputDebugString(TEXT("ERROR: Attempting to load new textures without unloading old textures. Skipping loading of textures. - void cDSMenuButton::LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)\n"));
	}
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::UnloadTextures()
{
	//if textures are already loaded
	if(mTexturesLoaded)
	{
		//Unload old textures
		mUpTexture.Unload();
		mHoverTexture.Unload();
		mDownTexture.Unload();
		mClickTexture.Unload();

		//Set flag
		mTexturesLoaded = false;
	}
	//else throw error
	else
	{
		OutputDebugString(TEXT("ERROR: Attempting to unload textures but no textures are currently loaded. Skipping unloading of textures. - void cDSMenuButton::UnloadTextures()\n"));
	}
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)
{
	//Unload old textures
	mUpTexture.Unload();
	mHoverTexture.Unload();
	mDownTexture.Unload();
	mClickTexture.Unload();

	//Load new textures
	mUpTexture.Load(upTexture);
	mHoverTexture.Load(hoverTexture);
	mDownTexture.Load(downTexture);
	mClickTexture.Load(clickTexture);

	//Set flag
	mTexturesLoaded = true;
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::Update(const int cursorX, const int cursorY, const bool cursorPressed)
{
	//Physics
	//if the mouse is on top of the button
	if((cursorX >= mOriginX && cursorX <= (mOriginX + mWidth)) && (cursorY >= mOriginY && cursorY <= (mOriginY + mHeight)))
	{
		//check mouse left button state
		 //if the mouse left button is up
		if(!cursorPressed)
		{
			//if the button has been pressed earlier
			if(mBeenPressed)
			{
				mButtonState = kClick;
				mBeenPressed = false;
			}
			//else the mouse is moving onto the button
			else
			{
				mButtonState = kHover;
				mBeenPressed = false;
			}
		}
		 //else if the mouse left button is down
		else if(cursorPressed)
		{
			mButtonState = kDown;
			mBeenPressed = true;
		}
	}
	//else if the current texture is not the default up texture
	else if(mSprite.GetTexture() != &mUpTexture)
	{
		//Reset the texture back to the default up state
		mButtonState = kUp;
		mBeenPressed = false;
	}

	//Update Texture
	UpdateTexture();
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::UpdateTexture()
{
	mSprite.ClearTextures();

	if(mButtonState == kUp)
	{
		mSprite.AddTexture(&mUpTexture);
	}
	else if(mButtonState == kHover)
	{
		mSprite.AddTexture(&mHoverTexture);
	}
	else if(mButtonState == kDown)
	{
		mSprite.AddTexture(&mDownTexture);
	}
	else if(mButtonState == kClick)
	{
		mSprite.AddTexture(&mClickTexture);
	}
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::Render()
{
	mSprite.Render();
}

//----------------------------------------------------------------------------------------------------
//Getters
//----------------------------------------------------------------------------------------------------

D3DXVECTOR2 cDSMenuButton::GetOrigin() const
{
	//Convert origin data to the D3DXVECTOR2 format
	D3DXVECTOR2 origin(static_cast<float>(mOriginX), static_cast<float>(mOriginY));

	return origin;
}

//----------------------------------------------------------------------------------------------------

int cDSMenuButton::GetOriginX() const
{
	return mOriginX;
}

//----------------------------------------------------------------------------------------------------

int cDSMenuButton::GetOriginY() const
{
	return mOriginY;
}

//----------------------------------------------------------------------------------------------------

D3DXVECTOR2 cDSMenuButton::GetSize() const
{
	//Convert origin data to the D3DXVECTOR2 format
	D3DXVECTOR2 origin(static_cast<float>(mWidth), static_cast<float>(mHeight));

	return origin;
}

//----------------------------------------------------------------------------------------------------

int cDSMenuButton::GetWidth() const
{
	return mWidth;
}

//----------------------------------------------------------------------------------------------------

int cDSMenuButton::GetHeight() const
{
	return mHeight;
}

//----------------------------------------------------------------------------------------------------

bool cDSMenuButton::GetOriginCentered() const
{
	return mOriginCentered;
}

//----------------------------------------------------------------------------------------------------

float cDSMenuButton::GetDepth() const
{
	return mDepth;
}

//----------------------------------------------------------------------------------------------------

bool cDSMenuButton::GetBeenPressed() const
{
	return mBeenPressed;
}

//----------------------------------------------------------------------------------------------------

int cDSMenuButton::GetButtonState() const
{
	return mButtonState;
}

//----------------------------------------------------------------------------------------------------

bool cDSMenuButton::GetTexturesLoaded() const
{
	return mTexturesLoaded;
}

//----------------------------------------------------------------------------------------------------
//Setters
//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetOrigin(const D3DXVECTOR2 origin)
{
	//Collision Volume
	mOriginX = static_cast<int>(origin.x);
	mOriginY = static_cast<int>(origin.y);

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetOrigin(const int originX, const int originY)
{
	//Collision Volume
	mOriginX = originX;
	mOriginY = originY;

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetOriginX(const int originX)
{
	//Collision Volume
	mOriginX = originX;

	//Sprite
	mSprite.SetPositionX(static_cast<float>(mOriginX));
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetOriginY(const int originY)
{
	//Collision Volume
	mOriginY = mOriginY;

	//Sprite
	mSprite.SetPositionY(static_cast<float>(mOriginY));
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetSize(D3DXVECTOR2 size)
{
	mWidth = static_cast<int>(size.x);
	mHeight = static_cast<int>(size.y);
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetWidth(int width)
{
	mWidth = width;
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetHeight(int height)
{
	mHeight = height;
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetDepth(float depth)
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
		OutputDebugString(TEXT("ERROR: The depth buffer must be between 0.0f and 1.0f. Leaving the depth as it was previously. - void cDSCursor::SetDepth(float depth)\n"));
	}
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetBeenPressed(bool beenPressed)
{
	mBeenPressed = beenPressed;
}

//----------------------------------------------------------------------------------------------------

void cDSMenuButton::SetButtonState(int buttonState)
{
	mButtonState = buttonState;
}