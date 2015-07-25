#ifndef INCLUDED_ENGINE_TEXTURE_H
#define INCLUDED_ENGINE_TEXTURE_H

//====================================================================================================
// Filename:	Texture.h
// Created by:	Peter Chan
// Description:	Class for a texture resource.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Resource.h"

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture();
	
	void Initialize(GraphicsSystem& gs, const wchar_t* pFilename);
	void Terminate();
	
	void BindVS(GraphicsSystem& gs, u32 index);
	void BindPS(GraphicsSystem& gs, u32 index);

private:
	ID3D11ShaderResourceView* mpTexture;
};

#endif // #ifndef INCLUDED_ENGINE_TEXTURE_H