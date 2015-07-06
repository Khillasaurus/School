//=================================================================================================
// File:		Button.h
// Created:		2012/08/18
// Last Edited:	2012/10/18
// Copyright:	Daniel Schenker
// Description:	Button class with 4 states: Up, Hover, Down, Click.
//				Can be set to event or toggle mode.
//				Can house other data such as type.
//=================================================================================================

#ifndef INCLUDED_BUTTON_H
#define INCLUDED_BUTTON_H

//=================================================================================================
// Includes
//=================================================================================================

// DirectX
#include <d3dx9math.h>

//=================================================================================================
// Forward Declarations
//=================================================================================================

// SGE
class CSprite;
class CTexture;

//STL
//#include <list>

//Daniel Schenker
#include "States.h"

//=================================================================================================
// Class Declarations
//=================================================================================================

class Button
{
public:
	// Constructors
	/*
	Button();
	Button(D3DXVECTOR2 origin, int width, int height, bool originCentered);
	Button(int originX, int originY, int width, int height, bool originCentered);
	Button(D3DXVECTOR2 origin, int width, int height, bool originCentered, float depth);
	Button(int originX, int originY, int width, int height, bool originCentered, float depth);
	Button(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered);
	Button(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered);
	Button(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered, float depth);
	*/
	Button(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, int type = 0, const int typeTotal = 1, bool originCentered = false, float depth = StateDepth::HUD);
	
	//Deconstructors
	~Button();

	// SGE Specific
	void Load(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture);
	void Unload();
	void Update(float deltaTime, const int cursorX, const int cursorY, const bool cursorPressed, const int type = 0, const bool toggle = false);
	void Render();
	
	// General
	void LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, const int type = 0);
	void UnloadTextures();
	void OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture);
	void UpdateTexture();
	
	// Accessors
	D3DXVECTOR2 GetOrigin() const;
	int GetOriginX() const;
	int GetOriginY() const;
	D3DXVECTOR2 GetSize() const;
	int GetWidth() const;
	int GetHeight() const;
	int GetType() const;
	int GetTypeTotal() const;
	bool GetOriginCentered() const;
	float GetDepth() const;
	bool GetBeenPressed() const;
	int GetButtonState() const;
	bool GetTexturesLoaded() const;
	
	// Mutators
	void SetOrigin(const D3DXVECTOR2 origin);
	void SetOrigin(const int originX, const int originY);
	//void SetOriginX(const int originX);//Commented out because SetPositionX does not exist in SGE\Graphics\CSprite
	//void SetOriginY(const int originY);//Commented out because SetPositionX does not exist in SGE\Graphics\CSprite
	void SetSize(D3DXVECTOR2 size);
	void SetWidth(int width);
	void SetHeight(int height);
	int SetType(int type);//Returns mType so that the function caller knows if the type was changed or not.
	void SetDepth(float depth);
	void SetBeenPressed(bool beenPressed);
	void SetButtonState(int buttonState);

protected:
	//Sprites
	CSprite mSprite;

	// Textures
	CTexture mUpTexture;
	CTexture mHoverTexture;
	CTexture mDownTexture;
	CTexture mClickTexture;

	// Data
	int mOriginX;
	int mOriginY;
	int mWidth;
	int mHeight;
	int mType;
	const int mTypeTotal;
	bool mOriginCentered;
	float mDepth;
	
	// States
	bool mBeenPressed;
	int mButtonState;
	bool mTexturesLoaded;
	int mToggle;
};

#endif //INCLUDED_BUTTON_H