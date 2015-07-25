//====================================================================================================
// Filename:	SpriteRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SpriteRenderer.h"

#include "GraphicsSystem.h"
#include <SpriteBatch.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

SpriteRenderer::SpriteRenderer()
	: mpSpriteBatch(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::~SpriteRenderer()
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

//----------------------------------------------------------------------------------------------------

void SpriteRenderer::Initialize(GraphicsSystem& gs)
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	mpSpriteBatch = new SpriteBatch(gs.GetContext());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Terminate()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Already terminated.");
	SafeDelete(mpSpriteBatch);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::BeginRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->Begin();
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::EndRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->End();
}