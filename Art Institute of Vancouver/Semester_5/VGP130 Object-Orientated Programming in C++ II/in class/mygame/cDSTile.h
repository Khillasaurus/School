////====================================================================================================
////File:			cDSTile.h
////Created:		2012/08/20
////Copyright:	Daniel Schenker
////====================================================================================================
//
//#ifndef DSGAME_CDSTILE_H
//#define DSGAME_CDSTILE_H
//
////====================================================================================================
////Includes
////====================================================================================================
//
//// DirectX
//#include <d3dx9math.h>
//
////====================================================================================================
//// Forward Declarations
////====================================================================================================
//
//// SGE
//class CSprite;
//class CTexture;
//
////====================================================================================================
////Enums
////====================================================================================================
//
//enum ButtonState
//{
//	kUp = 0,
//	kHover = 1,
//	kClick = 3
//};
//
////====================================================================================================
////Class Declarations
////====================================================================================================
//
//class cDSTile
//{
//public:
//	//Constructors
//	cDSTile();
//	cDSTile(D3DXVECTOR2 origin, int width, int height, const char* upTexture, const char* hoverTexture, const char* clickTexture, int currentTileX, int currentTileY, int correctTileX, int correctTileY, float depth);
//	cDSTile(int originX, int originY, int width, int height, const char* upTexture, const char* hoverTexture, const char* clickTexture, int currentTileX, int currentTileY, int correctTileX, int correctTileY, float depth);
//	//Deconstructors 
//	~cDSTile();
//
//	//Member Functions
//	 //General
//	void LoadTextures(const char* upTexture, const char* hoverTexture, const char* clickTexture);
//	void OverwriteTextures(const char* upTexture, const char* hoverTexture, const char* clickTexture);
//	void Update(const int cursorX, const int cursorY, const bool cursorPressed);
//	void UpdateTexture();
//	bool hasEmptyNeighbour();
//	void MoveCell();
//
//	void Render();
//	 //Getters
//	D3DXVECTOR2 GetOrigin() const;
//	int GetOriginX() const;
//	int GetOriginY() const;
//	D3DXVECTOR2 GetSize() const;
//	int GetWidth() const;
//	int GetHeight() const;
//	int GetCurrentTileX() const;
//	int GetCurrentTileY() const;
//	int GetCorrectTileX() const;
//	int GetCorrectTileY() const;
//	float GetDepth() const;
//	int GetButtonState() const;
//	bool GetTexturesLoaded() const;
//	bool GetCorrectPosition() const;
//	 //Setters
//	void SetOrigin(D3DXVECTOR2 origin);
//	void SetOriginX(int originX);
//	void SetOriginY(int originY);
//	void SetSize(D3DXVECTOR2 size);
//	void SetWidth(int width);
//	void SetHeight(int height);
//	void SetCurrentTileX(int currentTileX);
//	void SetCurrentTileY(int currentTileY);
//	void SetCorrectTileX(int correctTileX);
//	void SetCorrectTileY(int correctTileY);
//	void SetDepth(float depth);
//	void SetButtonState(int buttonState);
//
//protected:
//	//Member Variables
//	 //Sprites
//	CSprite mSprite;
//	 //Textures
//	CTexture mUpTexture;
//	CTexture mHoverTexture;
//	CTexture mClickTexture;
//	 //Data
//	int mOriginX;
//	int mOriginY;
//	int mWidth;
//	int mHeight;
//	int mCurrentTileX;
//	int mCurrentTileY;
//	int mCorrectTileX;
//	int mCorrectTileY;
//	float mDepth;
//	  //States
//	int mButtonState;
//	bool mTexturesLoaded;
//	bool mCorrectPosition;
//};
//
//#endif //DSGAME_CDSTILE_H