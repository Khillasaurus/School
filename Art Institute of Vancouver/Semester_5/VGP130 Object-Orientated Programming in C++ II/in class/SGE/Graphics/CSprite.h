#ifndef INCLUDED_SPRITE_H
#define INCLUDED_SPRITE_H

//====================================================================================================
// Filename:	CSprite.h
// Created by:	Peter Chan
// Description:	Class for a 2D sprite. It contains an array of textures and provides functionalities
//				for transformations and animations.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <d3dx9.h>
#include <vector>

//====================================================================================================
// Forward Declarations
//====================================================================================================

class CTexture;

//====================================================================================================
// Class Declarations
//====================================================================================================

class CSprite
{
public:
	// Constructor
	CSprite(void);

	// Destructor
	virtual ~CSprite(void);

	// Function to update the sprite
	virtual void Update(float fSeconds);

	// Function to render the sprite
	virtual void Render(void);

	// Functions for managing textures used by the sprite
	void AddTexture(CTexture* pTexture);
	const CTexture* GetTexture(void) const;
	void ClearTextures(void);

	// Function to get sprite dimension
	void GetDimension(int& iWidth, int& iHeight) const;
	D3DXVECTOR2 GetDimension() const;//DS
	float GetDimensionX() const;//DS
	float GetDimensionY() const;//DS

	// Function to set color
	void SetColor(int iRed, int iGreen, int iBlue, int iAlpha);
	void SetColor(int argb);

	// Functions to get sprite attributes
	void GetPosition(float& fPosX, float& fPosY) const;
	D3DXVECTOR2 GetPosition() const;//DS
	float GetPositionX() const;//DS
	float GetPositionY() const;//DS
	void GetScale(float& fScaleX, float& fScaleY) const;
	D3DXVECTOR2 GetScale() const;//DS
	float GetScaleX() const;//DS
	float GetScaleY() const;//DS
	float GetRotation(void) const;
	float GetDepth(void) const;
	bool IsScaleAboutCenter(void) const;
	bool GetFlipH(void) const;
	bool GetFlipV(void) const;

	// Functions to set sprite attributes
	void SetPosition(float fPosX, float fPosY);
	void SetPosition(D3DXVECTOR2 position);//DS
	void SetPositionX(float fPosX);//DS
	void SetPositionY(float fPosY);//DS
	void SetScale(float fScaleX, float fScaleY);
	void SetScale(D3DXVECTOR2 scale);//DS
	void SetScaleX(float fScaleX);//DS
	void SetScaleY(float fScaleY);//DS
	void SetRotation(float fRotation);
	void SetDepth(float fDepth);
	void SetScaleAboutCenter(bool bScaleAboutCenter);
	void SetFlipH(bool bFlip);
	void SetFlipV(bool bFlip);

	// Functions for controlling animation playback
	void Play(bool bLoopOnce = false);
	void Stop(void);
	void Step(void);
	void Reset(void);

	// Function that returns true if the animation is done
	bool IsFinished(void) const;

	// Functions to get multi sprite attributes
	float GetAnimationSpeed(void) const;
	int GetCurrentFrame(void) const;

	// Functions to set multi sprite attributes
	void SetAnimationSpeed(float fSpeed);
	void SetCurrentFrame(int iFrame);

protected:
	// Members
	std::vector<CTexture*> mpTextures;

	D3DXCOLOR mColor;

	D3DXVECTOR2 mPosition;
	D3DXVECTOR2 mScale;

	float mRotation;
	float mDepth;

	bool mScaleAboutCenter;
	bool mFlipH;
	bool mFlipV;

	float mAnimationSpeed;		// Frames per second
	float mAnimationTime;		// Time since start of animation
	int mCurrentFrame;			// Current animation frame

	bool mPlay;					// True when playing
	bool mLoopOnce;				// True if we only want to loop once
};

#endif // #ifndef INCLUDED_SPRITE_H