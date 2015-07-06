//====================================================================================================
//File:			cDSMenuButton.h
//Created:		2012/08/18
//Copyright:	Daniel Schenker
//====================================================================================================

#ifndef DSGAME_CDSMENUBUTTON_H
#define DSGAME_CDSMENUBUTTON_H

//====================================================================================================
//Includes
//====================================================================================================

// DirectX
#include <d3dx9math.h>

//SGE
#include "graphics/CSprite.h"
#include "graphics/CTexture.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

// SGE
//class CSprite;
//class CTexture;

//====================================================================================================
//Enums
//====================================================================================================

//namespace ButtonStates
//{
//enum eButtonState
enum ButtonState
{
	kUp = 0,
	kHover = 1,
	kDown = 2,
	kClick = 3
};
//}

//====================================================================================================
//Class Declarations
//====================================================================================================

class cDSMenuButton
{
public:
	//Constructors
	cDSMenuButton();
	cDSMenuButton(D3DXVECTOR2 origin, int width, int height, bool originCentered);
	cDSMenuButton(int originX, int originY, int width, int height, bool originCentered);
	cDSMenuButton(D3DXVECTOR2 origin, int width, int height, bool originCentered, float depth);
	cDSMenuButton(int originX, int originY, int width, int height, bool originCentered, float depth);
	cDSMenuButton(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered);
	cDSMenuButton(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered);
	cDSMenuButton(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered, float depth);
	cDSMenuButton(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture, bool originCentered, float depth);
	//Deconstructors
	~cDSMenuButton();

	//Member Functions
	 //General
	void LoadTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture);
	void UnloadTextures();
	void OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* downTexture, const char* clickTexture);
	void Update(const int cursorX, const int cursorY, const bool cursorPressed);
	void UpdateTexture();
	void Render();
	 //Getters
	D3DXVECTOR2 GetOrigin() const;
	int GetOriginX() const;
	int GetOriginY() const;
	D3DXVECTOR2 GetSize() const;
	int GetWidth() const;
	int GetHeight() const;
	bool GetOriginCentered() const;
	float GetDepth() const;
	bool GetBeenPressed() const;
	int GetButtonState() const;
	bool GetTexturesLoaded() const;
	 //Setters
	void SetOrigin(const D3DXVECTOR2 origin);
	void SetOrigin(const int originX, const int originY);
	void SetOriginX(const int originX);
	void SetOriginY(const int originY);
	void SetSize(D3DXVECTOR2 size);
	void SetWidth(int width);
	void SetHeight(int height);
	void SetDepth(float depth);
	void SetBeenPressed(bool beenPressed);
	void SetButtonState(int buttonState);

	//Member Variables
public://public for now due to cDSBoard requiring more complete access to this. Eventually I would like to change this to having specific functions to change this
	 //Sprites
	CSprite mSprite;
	 //Textures
	CTexture mUpTexture;
	CTexture mHoverTexture;
	CTexture mDownTexture;
	CTexture mClickTexture;
protected:
	 //Data
	int mOriginX;
	int mOriginY;
	int mWidth;
	int mHeight;
	bool mOriginCentered;
	float mDepth;
	  //States
	bool mBeenPressed;
	int mButtonState;
	bool mTexturesLoaded;
};

#endif //DSGAME_CDSMENUBUTTON_H