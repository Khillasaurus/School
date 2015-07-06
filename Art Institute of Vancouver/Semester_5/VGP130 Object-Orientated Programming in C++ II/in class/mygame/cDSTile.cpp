////====================================================================================================
////File:			cDSTile.cpp
////Created:		2012/08/20
////Copyright:	Daniel Schenker
////====================================================================================================
//
////====================================================================================================
////Includes
////====================================================================================================
//
////Precompiled headers
#include "stdafx.h"
//
//// SGE
//#include "graphics/CSprite.h"
//#include "graphics/CTexture.h"
//
////Daniel Schenker
//#include "cDSTile.h"
//#include "cDSApp.h"
//
////====================================================================================================
////Class Definitions
////====================================================================================================
//
////----------------------------------------------------------------------------------------------------
////Constuctors
////----------------------------------------------------------------------------------------------------
//
//cDSTile::cDSTile()
//{
//}
//
////----------------------------------------------------------------------------------------------------
//
//cDSTile::cDSTile(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* clickTexture, int currentTileX, int currentTileY, int correctTileX, int correctTileY, float depth = cDSApp::msDepthObject)
//:	mOriginX(static_cast<int>(origin.x))
//,	mOriginY(static_cast<int>(origin.y))
//,	mWidth(width)
//,	mHeight(height)
//,	mCurrentTileX(currentTileX)
//,	mCurrentTileY(currentTileY)
//,	mCorrectTileX(correctTileX)
//,	mCorrectTileY(correctTileY)
//,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthObject)
//,	mButtonState(0)
//,	mTexturesLoaded(true)
//{
//	//Sprite
//	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
//	mSprite.SetDepth(mDepth);
//
//	//Texture
//	mUpTexture.Load(upTexture);
//	mHoverTexture.Load(hoverTexture);
//	mClickTexture.Load(clickTexture);
//}
//
////----------------------------------------------------------------------------------------------------
//
//cDSTile::cDSTile(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* clickTexture, int currentTileX, int currentTileY, int correctTileX, int correctTileY, float depth = cDSApp::msDepthObject)
//:	mOriginX(static_cast<int>(originX))
//,	mOriginY(static_cast<int>(originY))
//,	mWidth(width)
//,	mHeight(height)
//,	mDepth((depth >= 0 && depth <= 1) ? depth : cDSApp::msDepthObject)
//,	mButtonState(0)
//,	mTexturesLoaded(true)
//{
//	//Sprite
//	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
//	mSprite.SetDepth(mDepth);
//
//	//Texture
//	mUpTexture.Load(upTexture);
//	mHoverTexture.Load(hoverTexture);
//	mClickTexture.Load(clickTexture);
//}
//
////----------------------------------------------------------------------------------------------------
////Deconstuctors
////----------------------------------------------------------------------------------------------------
//
//cDSTile::~cDSTile()
//{
//}
//
////----------------------------------------------------------------------------------------------------
////General Member Functions
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::LoadTextures(const char* upTexture, const char* hoverTexture, const char* clickTexture)
//{
//	//if no textures are already loaded
//	if(!mTexturesLoaded)
//	{
//		//Load new textures
//		mUpTexture.Load(upTexture);
//		mHoverTexture.Load(hoverTexture);
//		mClickTexture.Load(clickTexture);
//
//		//Set flag
//		mTexturesLoaded = true;
//	}
//	//else throw error
//	else
//	{
//		OutputDebugString(TEXT("ERROR: Attempting to load new textures without unloading old textures. Skipping loading of textures. - void cDSTile::LoadTextures(const char* upTexture, const char* hoverTexture, const char* clickTexture)\n"));
//	}
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* clickTexture)
//{
//	//Unload old textures
//	mUpTexture.Unload();
//	mHoverTexture.Unload();
//	mClickTexture.Unload();
//
//	//Load new textures
//	mUpTexture.Load(upTexture);
//	mHoverTexture.Load(hoverTexture);
//	mClickTexture.Load(clickTexture);
//
//	//Set flag
//	mTexturesLoaded = true;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::Update(const int cursorX, const int cursorY, const bool cursorPressed)
//{
//	//Physics
//	//if the mouse is on top of the button
//	if((cursorX >= mOriginX && cursorX <= (mOriginX + mWidth)) && (cursorY >= mOriginY && cursorY <= (mOriginY + mHeight)))
//	{
//		//check mouse left button state
//		 //if the mouse left button is up
//		if(!cursorPressed)
//		{
//			mButtonState = kHover;
//		}
//		 //else the mouse left button is down
//		else
//		{
//			mButtonState = kClick;
//		}
//	}
//	//else if the current texture is not the default up texture
//	else if(mSprite.GetTexture() != &mUpTexture)
//	{
//		//Reset the texture back to the default up state
//		mButtonState = kUp;
//	}
//
//	//Update Texture
//	UpdateTexture();
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::UpdateTexture()
//{
//	mSprite.ClearTextures();
//
//	if(mButtonState == kUp)
//	{
//		mSprite.AddTexture(&mUpTexture);
//	}
//	else if(mButtonState == kHover)
//	{
//		mSprite.AddTexture(&mHoverTexture);
//	}
//	else if(mButtonState == kClick)
//	{
//		mSprite.AddTexture(&mClickTexture);
//	}
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::Render()
//{
//	mSprite.Render();
//}
//
////----------------------------------------------------------------------------------------------------
////Getters
////----------------------------------------------------------------------------------------------------
//
//D3DXVECTOR2 cDSTile::GetOrigin() const
//{
//	//Convert origin data to the D3DXVECTOR2 format
//	D3DXVECTOR2 origin(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
//
//	return origin;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetOriginX() const
//{
//	return mOriginX;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetOriginY() const
//{
//	return mOriginY;
//}
//
////----------------------------------------------------------------------------------------------------
//
//D3DXVECTOR2 cDSTile::GetSize() const
//{
//	//Convert origin data to the D3DXVECTOR2 format
//	D3DXVECTOR2 origin(static_cast<float>(mWidth), static_cast<float>(mHeight));
//
//	return origin;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetWidth() const
//{
//	return mWidth;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetHeight() const
//{
//	return mHeight;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetCurrentTileX() const
//{
//	return mCurrentTileX;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetCurrentTileY() const
//{
//	return mCurrentTileY;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetCorrectTileX() const
//{
//	return mCorrectTileX;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetCorrectTileY() const
//{
//	return mCorrectTileY;
//}
//
////----------------------------------------------------------------------------------------------------
//
//float cDSTile::GetDepth() const
//{
//	return mDepth;
//}
//
////----------------------------------------------------------------------------------------------------
//
//int cDSTile::GetButtonState() const
//{
//	return mButtonState;
//}
//
////----------------------------------------------------------------------------------------------------
//
//bool cDSTile::GetTexturesLoaded() const
//{
//	return mTexturesLoaded;
//}
//
////----------------------------------------------------------------------------------------------------
////Setters
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetOrigin(D3DXVECTOR2 origin)
//{
//	//Collision Volume
//	mOriginX = static_cast<int>(origin.x);
//	mOriginY = static_cast<int>(origin.y);
//
//	//Sprite
//	mSprite.SetPosition(static_cast<float>(mOriginX), static_cast<float>(mOriginY));
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetOriginX(int originX)
//{
//	//Collision Volume
//	mOriginX = originX;
//
//	//Sprite
//	mSprite.SetPositionX(static_cast<float>(mOriginX));
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetOriginY(int originY)
//{
//	//Collision Volume
//	mOriginY = mOriginY;
//
//	//Sprite
//	mSprite.SetPositionY(static_cast<float>(mOriginY));
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetSize(D3DXVECTOR2 size)
//{
//	mWidth = static_cast<int>(size.x);
//	mHeight = static_cast<int>(size.y);
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetWidth(int width)
//{
//	mWidth = width;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetHeight(int height)
//{
//	mHeight = height;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetCurrentTileX(int currentTileX)
//{
//	mCurrentTileX = currentTileX;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetCurrentTileY(int currentTileY)
//{
//	mCurrentTileY = currentTileY;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetCorrectTileX(int correctTileX)
//{
//	mCorrectTileX = correctTileX;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetCorrectTileY(int correctTileY)
//{
//	mCorrectTileY = correctTileY;
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetDepth(float depth)
//{
//	//if the depth is valid
//	if(depth >= 0 && depth <= 1)
//	{
//		mDepth = depth;
//		mSprite.SetDepth(mDepth);
//	}
//	//else throw error
//	else
//	{
//		OutputDebugString(TEXT("ERROR: The depth buffer must be between 0.0f and 1.0f. Leavig the depth as it was previously. - void cDSTile::SetDepth(float depth)\n"));
//	}
//}
//
////----------------------------------------------------------------------------------------------------
//
//void cDSTile::SetButtonState(int buttonState)
//{
//	mButtonState = buttonState;
//}