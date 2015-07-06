//=================================================================================================
// File:		Cursor.h
// Created:		2012/08/19
// Last Edited:	2012/10/12
// Copyright:	Daniel Schenker
// Description:	Cursor class that allows for determining which input device to use,
//				as well as adds animation to the cursor
//=================================================================================================

#ifndef INCLUDED_CURSOR_H
#define INCLUDED_CURSOR_H

//=================================================================================================
// Includes
//=================================================================================================

//DirectX
#include <d3dx9math.h>

// SGE
#include "Input/Input.h"
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//Daniel Schenker
#include "States.h"

//=================================================================================================
// Forward Declarations
//=================================================================================================

//// SGE
//class CSprite;
//class CTexture;

//=================================================================================================
// Class Declarations
//=================================================================================================

namespace CursorState
{
	enum eCursorState
	{
		kUp = 0,	//normal
		kDown = 1	//click
	};
}

//=================================================================================================
// Class Declarations
//=================================================================================================

class Cursor
{
public:
	// Constructors
	Cursor(D3DXVECTOR2 offset, const char* normalTexture, const char* clickTexture, float depth = StateDepth::Cursor, const bool inMenu = false);
	Cursor(int offsetX, int offsetY, const char* normalTexture, const char* clickTexture, float depth = StateDepth::Cursor, const bool inMenu = false);

	// Deconstructor
	~Cursor();

	// SGE Specific
	void Update(float deltaTime);
	void Render();

	//Accessors
	float GetDepth() const;
	bool GetInMenu() const;
	//Mutators
	void SetDepth(float depth);
	void SetInMenu(bool inMenu);

protected:
	//Sprites
	CSprite mSprite;

	// Textures
	CTexture mNormalTexture;
	CTexture mClickTexture;

	// Data
	int mOffsetX;//pixel offset from mOriginX where the user is actually pointing the mouse
	int mOffsetY;//pixel offset from mOriginY where the user is actually pointing the mouse
	float mDepth;
	int mLastX;//For use to check when controlling the cursor NOT through the mouse in a menu if the cursor can be switched back to following the mouse
	int mLastY;//For use to check when controlling the cursor NOT through the mouse in a menu if the cursor can be switched back to following the mouse

	//States
	bool mInMenu;
	int mLastState;
	int mCurState;
};

#endif //INCLUDED_CURSOR_H