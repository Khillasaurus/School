#ifndef INCLUDED_ENGINE_SPRITERENDERER_H
#define INCLUDED_ENGINE_SPRITERENDERER_H

//====================================================================================================
// Filename:	SpriteRenderer.h
// Created by:	Peter Chan
// Description:	Class for 2D sprite rendering.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace DirectX
{
	class SpriteBatch;
}
class GraphicsSystem;

//====================================================================================================
// Class Declarations
//====================================================================================================

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Initialize(GraphicsSystem& gs);
	void Terminate();

	void BeginRender();
	void EndRender();

	SpriteBatch* GetSpriteBatch() { return mpSpriteBatch; }

private:
	NONCOPYABLE(SpriteRenderer);

	friend class Font;

	SpriteBatch* mpSpriteBatch;
};

#endif // #ifndef INCLUDED_ENGINE_SPRITERENDERER_H