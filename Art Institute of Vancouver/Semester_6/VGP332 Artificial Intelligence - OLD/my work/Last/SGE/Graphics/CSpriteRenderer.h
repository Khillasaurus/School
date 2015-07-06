#ifndef INCLUDED_SPRITERENDERER_H
#define INCLUDED_SPRITERENDERER_H

//====================================================================================================
// Filename:	CSpriteRenderer.h
// Created by:	Peter Chan
// Description:	Singleton class for a sprite renderer. Internally it makes use of the ID3DXSprite
//			  interface for rendering. The singleton can be accessed calling CSpriteRenderer::Get().
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <d3dx9.h>

//====================================================================================================
// Forward Declarations
//====================================================================================================

class CSprite;

//====================================================================================================
// Class Declarations
//====================================================================================================

class CSpriteRenderer
{
public:
	// Accessor function for singleton instance
	static CSpriteRenderer* Get(void);

	// Destructor
	virtual ~CSpriteRenderer(void);

	// Functions to startup and shutdown the sprite renderer
	void Initialize(void);
	void Terminate(void);

	// Functions for rendering
	void BeginRender(void);
	void EndRender(void);

	// Function to render the ID3DXSprite interface
	ID3DXSprite* D3DXSprite(void) const;

protected:
	// Protected constructor for singleton
	CSpriteRenderer(void);

private:
	// Members
	static CSpriteRenderer* s_pInstance;		// Static instance for singleton

	ID3DXSprite* mpD3DXSprite;				 // Pointer to D3DX sprite interface

	bool mInitialized;						 // Init flag
};

#endif // #ifndef INCLUDED_SPRITERENDERER_H