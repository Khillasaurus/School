#ifndef INCLUDED_ENGINE_FONT_H
#define INCLUDED_ENGINE_FONT_H

//====================================================================================================
// Filename:	Font.h
// Created by:	Peter Chan
// Description:	Class for a 2D font.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace DirectX
{
	class SpriteFont;
}
class GraphicsSystem;
class SpriteRenderer;

//====================================================================================================
// Class Declarations
//====================================================================================================

class Font
{
public:
	Font();
	~Font();

	void Initialize(GraphicsSystem& gs, const wchar_t* pFilename);
	void Terminate();

	void Render(SpriteRenderer& renderer, const wchar_t* str, u32 x, u32 y);

private:
	NONCOPYABLE(Font);

	SpriteFont* mpSpriteFont;
};

#endif // #ifndef INCLUDED_ENGINE_FONT_H