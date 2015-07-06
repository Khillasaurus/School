#ifndef INCLUDED_TEXTURE_H
#define INCLUDED_TEXTURE_H

//====================================================================================================
// Filename:	CTexture.h
// Created by:	Peter Chan
// Description:	Class for a Direct3D texture.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Resource/CResource.h"

#include <d3dx9.h>

//====================================================================================================
// Class Declarations
//====================================================================================================

class CTexture : public CResource
{
public:
	// Constructor
	CTexture(void);

	// Destructor
	virtual ~CTexture(void);

	//==================================================
	// CResource Implementation
	//==================================================
	// Function to load/unload a new texture
	virtual void Load(const char* pFilename);
	virtual void Unload(void);
	//==================================================

	// Function to get the Direct3D texture interface
	IDirect3DTexture9* GetTexture(void) const;

	// Functions for getting the texture dimensions
	int GetWidth(void) const;
	int GetHeight(void) const;

private:
	IDirect3DTexture9* mpTexture;  // Pointer to Direct3D texture interface

	int mWidth;
	int mHeight;
};

#endif // #ifndef INCLUDED_TEXTURE_H