#ifndef INCLUDED_ENGINE_PIXELSHADER_H
#define INCLUDED_ENGINE_PIXELSHADER_H

//====================================================================================================
// Filename:	PixelShader.h
// Created by:	Peter Chan
// Description:	Class for a pixel shader.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;

//====================================================================================================
// Class Declarations
//====================================================================================================

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	void Initialize(GraphicsSystem& gs, const wchar_t* pFileName, const char* pEntryPoint, const char* pShaderModel);
	void Terminate();

	void Bind(GraphicsSystem& gs);

private:
	ID3D11PixelShader* mpPixelShader;
};

#endif // #ifndef INCLUDED_ENGINE_PIXELSHADER_H
