//====================================================================================================
//File:			cDSCursor.h
//Created:		2012/08/19
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef __CDSCURSOR_H
#define __CDSCURSOR_H

//====================================================================================================
//Includes
//====================================================================================================

// DirectX
#include <d3dx9math.h>
// SGE
#include "Input/Input.h"
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSCursor
{
public:
	//Constructors
	cDSCursor(D3DXVECTOR2 offset, const char* normalTexture, const char* clickTexture, float depth, const bool inMenu);
	cDSCursor(int offsetX, int offsetY, const char* normalTexture, const char* clickTexture, float depth, const bool inMenu);

	//Member Functions
	 //General
	void Update();
	void Render();
	 //Getters
	float GetDepth() const;
	bool GetInMenu() const;
	 //Setters
	void SetDepth(float depth);
	void SetInMenu(bool inMenu);

protected:
	//Member Variables
	 //Sprites
	CSprite mSprite;
	 //Textures
	CTexture mNormalTexture;
	CTexture mClickTexture;
	 //Data
	int mOffsetX;//pixel offset from mOriginX where the user is actually pointing the mouse
	int mOffsetY;//pixel offset from mOriginY where the user is actually pointing the mouse
	float mDepth;
	int mLastX;//For use to check when controlling the cursor NOT through the mouse in a menu if the cursor can be switched back to following the mouse
	int mLastY;//For use to check when controlling the cursor NOT through the mouse in a menu if the cursor can be switched back to following the mouse
	 //States
	bool mInMenu;
	int mLastState;//0 = up (normal), 1 = down (click)
	int mCurState;//0 = up (normal), 1 = down (click)
};

#endif //__CDSCURSOR_H