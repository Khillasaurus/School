//=================================================================================================
// File:		Button.cpp
// Created:		2012/08/18
// Last Edited:	2012/10/18
// Copyright:	Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

// SGE
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//Daniel Schenker
#include "Button.h"

//=================================================================================================
// Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
// Constuctors
//-------------------------------------------------------------------------------------------------

/*
Button::Button()
:	mType(0)
,	mDepth(StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
}

//-------------------------------------------------------------------------------------------------

Button::Button(D3DXVECTOR2 origin, int width, int height, bool originCentered = false)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth(StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//-------------------------------------------------------------------------------------------------

Button::Button(int originX, int originY, int width, int height, bool originCentered = false)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth(StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//-------------------------------------------------------------------------------------------------

Button::Button(D3DXVECTOR2 origin, int width, int height, bool originCentered = false, float depth = StateDepth::HUD)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//-------------------------------------------------------------------------------------------------

Button::Button(int originX, int originY, int width, int height, bool originCentered = false, float depth = StateDepth::HUD)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);
}

//-------------------------------------------------------------------------------------------------

Button::Button(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth(StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(true)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
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

//-------------------------------------------------------------------------------------------------

Button::Button(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth(StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(true)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
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

//-------------------------------------------------------------------------------------------------

Button::Button(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered = false, float depth = StateDepth::HUD)
:	mOriginX(static_cast<int>(origin.x))
,	mOriginY(static_cast<int>(origin.y))
,	mWidth(width)
,	mHeight(height)
,	mType(0)
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(true)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
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
*/

//-------------------------------------------------------------------------------------------------

Button::Button(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, int type, const int typeTotal, bool originCentered, float depth)
:	mOriginX(originX)
,	mOriginY(originY)
,	mWidth(width)
,	mHeight(height)
,	mType((type > 0) ? type : 0)//the type must be represented by a positive id
,	mTypeTotal((typeTotal > type) ? typeTotal : (type + 1))//mTypeTotal must be at least 1 greater than the current type
,	mOriginCentered(originCentered)
,	mDepth((depth >= 0 && depth <= 1) ? depth : StateDepth::HUD)
,	mBeenPressed(false)
,	mButtonState(StateButton::kUp)
,	mTexturesLoaded(false)
,	mToggle(false)
{
	//Collision Volume
	//if the origin is centered, set the origin to the top left, to allow for uniform mathematical calculations
	if(mOriginCentered)
	{
		mOriginX -= static_cast<int>(0.5 * width);
		mOriginY -= static_cast<int>(0.5 * height);
		mOriginCentered = false;
	}

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
	mSprite.SetDepth(mDepth);

	//Texture
	LoadTextures(upTexture, hoverTexture, downTexture, clickTexture, mType);
}

//-------------------------------------------------------------------------------------------------
//Deconstuctors
//-------------------------------------------------------------------------------------------------

Button::~Button()
{
	//Unload textures (existence of textures checked inside Unload() function)
	mUpTexture.Unload();
	mHoverTexture.Unload();
	mDownTexture.Unload();
	mClickTexture.Unload();
}

//-------------------------------------------------------------------------------------------------
// SGE Specific
//-------------------------------------------------------------------------------------------------

void Button::Load(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)
{
	LoadTextures(upTexture, hoverTexture, downTexture, clickTexture);
}

//-------------------------------------------------------------------------------------------------

void Button::Unload()
{
	UnloadTextures();
}

//-------------------------------------------------------------------------------------------------

//type:		Refers to input type, which is stored into the button and can be accessed through a
//			public getter, but has no meaning internal to the button class, as it relies on the
//			implementation of the user of the button class.
//
//toggle:	Refers to whether the button is state based or event based.
void Button::Update(float deltaTime, const int cursorX, const int cursorY, const bool cursorPressed, const int type, const bool toggle)
{
	// Update type
	if(type == 1)
	{
		mType = 1;
	}
	else
	{
		mType = 0;
		//if toggle mode was previously on, but is now turned off
		if(!toggle && mToggle != StateToggle::kNoToggle)
		{
			mButtonState = StateButton::kUp;

			//Update Texture
			UpdateTexture();
		}
		//Physics
		//if the mouse is on top of the button
		if((cursorX >= mOriginX && cursorX < (mOriginX + mWidth)) && (cursorY >= mOriginY && cursorY < (mOriginY + mHeight)))
		{
			//check mouse left button state
			 //if the mouse left button is up
			if(!cursorPressed)
			{
				//if the button has been pressed earlier
				if(mBeenPressed)
				{
					//if toggle mode is off
					if(!toggle)
					{
						mButtonState = StateButton::kClick;
						mBeenPressed = false;
					}
				}
				//else the mouse is moving onto the button
				else
				{
					//if toggle mode is off
					if(!toggle)
					{
						mButtonState = StateButton::kHover;
					}
					mBeenPressed = false;
				}
			}
			 //else if the mouse left button is down
			else if(cursorPressed)
			{
				//if toggle mode is off
				if(!toggle)
				{
					mButtonState = StateButton::kDown;
					mBeenPressed = true;
				}
				else
				{
					//Toggle between the up and click state
					//if the button is off or restarting toggle control
					if(mToggle < StateToggle::kOn)
					{
						mButtonState = StateButton::kClick;
						mToggle = StateToggle::kOn;
					}
					//else turn the button off
					else
					{
						mButtonState = StateButton::kUp;
						mToggle = StateToggle::kOff;
					}
				}

			}

			//Update Texture
			UpdateTexture();
		}
		//else if the current texture is not the default up texture
		else if(mSprite.GetTexture() != &mUpTexture)
		{
			//if toggle mode is off
			if(!toggle)
			{
				//Reset the texture back to the default up state
				mButtonState = StateButton::kUp;
				mBeenPressed = false;
			}
			else
			{
				if(mToggle == StateToggle::kOn)
				{
					mButtonState = StateButton::kClick;
				}
				else
				{
					mButtonState = StateButton::kUp;
				}
			}

			//Update Texture
			UpdateTexture();
		}
	}
}

//-------------------------------------------------------------------------------------------------

void Button::Render()
{
	mSprite.Render();
}

//-------------------------------------------------------------------------------------------------
// General
//-------------------------------------------------------------------------------------------------

void Button::LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, const int type)
{
	//if no textures are already loaded
	if(!mTexturesLoaded)
	{
		if(type == 0)
		{
			//Load new textures
			mUpTexture.Load(upTexture);
			mHoverTexture.Load(hoverTexture);
			mDownTexture.Load(downTexture);
			mClickTexture.Load(clickTexture);

			//Set flag
			mTexturesLoaded = true;
		}
	}
	//else throw error
	else
	{
		OutputDebugStringA("ERROR: Attempting to load new textures without unloading old textures. Skipping loading of textures. - void cDSMenuButton::LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)\n");
	}
}

//-------------------------------------------------------------------------------------------------

void Button::UnloadTextures()
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

//-------------------------------------------------------------------------------------------------

void Button::OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture)
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

//-------------------------------------------------------------------------------------------------

void Button::UpdateTexture()
{
	mSprite.ClearTextures();

	if(mButtonState == StateButton::kUp)
	{
		mSprite.AddTexture(&mUpTexture);
	}
	else if(mButtonState == StateButton::kHover)
	{
		mSprite.AddTexture(&mHoverTexture);
	}
	else if(mButtonState == StateButton::kDown)
	{
		mSprite.AddTexture(&mDownTexture);
	}
	else if(mButtonState == StateButton::kClick)
	{
		mSprite.AddTexture(&mClickTexture);
	}
}

//-------------------------------------------------------------------------------------------------
// Accessors
//-------------------------------------------------------------------------------------------------

D3DXVECTOR2 Button::GetOrigin() const
{
	//Convert origin data to the D3DXVECTOR2 format
	D3DXVECTOR2 origin(static_cast<float>(mOriginX), static_cast<float>(mOriginY));

	return origin;
}

//-------------------------------------------------------------------------------------------------

int Button::GetOriginX() const
{
	return mOriginX;
}

//-------------------------------------------------------------------------------------------------

int Button::GetOriginY() const
{
	return mOriginY;
}

//-------------------------------------------------------------------------------------------------

D3DXVECTOR2 Button::GetSize() const
{
	//Convert origin data to the D3DXVECTOR2 format
	D3DXVECTOR2 origin(static_cast<float>(mWidth), static_cast<float>(mHeight));

	return origin;
}

//-------------------------------------------------------------------------------------------------

int Button::GetWidth() const
{
	return mWidth;
}

//-------------------------------------------------------------------------------------------------

int Button::GetHeight() const
{
	return mHeight;
}

//-------------------------------------------------------------------------------------------------

int Button::GetType() const
{
	return mType;
}

//-------------------------------------------------------------------------------------------------

int Button::GetTypeTotal() const
{
	return mTypeTotal;
}

//-------------------------------------------------------------------------------------------------

bool Button::GetOriginCentered() const
{
	return mOriginCentered;
}

//-------------------------------------------------------------------------------------------------

float Button::GetDepth() const
{
	return mDepth;
}

//-------------------------------------------------------------------------------------------------

bool Button::GetBeenPressed() const
{
	return mBeenPressed;
}

//-------------------------------------------------------------------------------------------------

int Button::GetButtonState() const
{
	return mButtonState;
}

//-------------------------------------------------------------------------------------------------

bool Button::GetTexturesLoaded() const
{
	return mTexturesLoaded;
}

//-------------------------------------------------------------------------------------------------
// Mutators
//-------------------------------------------------------------------------------------------------

void Button::SetOrigin(const D3DXVECTOR2 origin)
{
	//Collision Volume
	mOriginX = static_cast<int>(origin.x);
	mOriginY = static_cast<int>(origin.y);

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
}

//-------------------------------------------------------------------------------------------------

void Button::SetOrigin(const int originX, const int originY)
{
	//Collision Volume
	mOriginX = originX;
	mOriginY = originY;

	//Sprite
	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
}

//-------------------------------------------------------------------------------------------------

//Commented out because SetPositionX does not exist in SGE\Graphics\CSprite
/*
void Button::SetOriginX(const int originX)
{
	//Collision Volume
	mOriginX = originX;

	//Sprite
	mSprite.SetPositionX(static_cast<float>(mOriginX));
}
*/

//-------------------------------------------------------------------------------------------------

//Commented out because SetPositionX does not exist in SGE\Graphics\CSprite
/*
void Button::SetOriginY(const int originY)
{
	//Collision Volume
	mOriginY = mOriginY;

	//Sprite
	mSprite.SetPositionY(static_cast<float>(mOriginY));
}
*/

//-------------------------------------------------------------------------------------------------

void Button::SetSize(D3DXVECTOR2 size)
{
	mWidth = static_cast<int>(size.x);
	mHeight = static_cast<int>(size.y);
}

//-------------------------------------------------------------------------------------------------

void Button::SetWidth(int width)
{
	mWidth = width;
}

//-------------------------------------------------------------------------------------------------

void Button::SetHeight(int height)
{
	mHeight = height;
}

//-------------------------------------------------------------------------------------------------

int Button::SetType(int type)
{
	if(type < mTypeTotal)
	{
		mType = type;
	}
	return mType;
}

//-------------------------------------------------------------------------------------------------

void Button::SetDepth(float depth)
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

//-------------------------------------------------------------------------------------------------

void Button::SetBeenPressed(bool beenPressed)
{
	mBeenPressed = beenPressed;
}

//-------------------------------------------------------------------------------------------------

void Button::SetButtonState(int buttonState)
{
	mButtonState = buttonState;
}