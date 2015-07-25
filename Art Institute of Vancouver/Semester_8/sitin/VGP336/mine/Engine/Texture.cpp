//====================================================================================================
// Filename:	Texture.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "Texture.h"

#include "GraphicsSystem.h"
#include <DDSTextureLoader.h>
#include <WICTextureLoader.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

Texture::Texture()
	: mpTexture(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------
Texture::~Texture()
{
	ASSERT(mpTexture == nullptr, "[Texture] Texture not released!");
}

//----------------------------------------------------------------------------------------------------

void Texture::Initialize(GraphicsSystem& gs, const wchar_t* pFilename)
{
	CreateDDSTextureFromFile(gs.GetDevice(), pFilename, nullptr, &mpTexture);
	if (mpTexture == nullptr)
	{
		CreateWICTextureFromFile(gs.GetDevice(), gs.GetContext(), pFilename, nullptr, &mpTexture);
	}
}

//----------------------------------------------------------------------------------------------------

void Texture::Terminate()
{
	SafeRelease(mpTexture);
}

//----------------------------------------------------------------------------------------------------

void Texture::BindVS(GraphicsSystem& gs, u32 index)
{
	gs.GetContext()->VSSetShaderResources(index, 1, &mpTexture);
}

//----------------------------------------------------------------------------------------------------

void Texture::BindPS(GraphicsSystem& gs, u32 index)
{
	gs.GetContext()->PSSetShaderResources(index, 1, &mpTexture);
}