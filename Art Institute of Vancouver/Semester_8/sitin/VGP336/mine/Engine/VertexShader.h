#ifndef INCLUDED_ENGINE_VERTEXSHADER_H
#define INCLUDED_ENGINE_VERTEXSHADER_H

//====================================================================================================
// Filename:	VertexShader.h
// Created by:	Peter Chan
// Description:	Class for a vertex shader.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class GraphicsSystem;

//====================================================================================================
// Class Declarations
//====================================================================================================

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	void Initialize(GraphicsSystem& gs, const wchar_t* pFileName, const char* pEntryPoint, const char* pShaderModel, u32 vertexFormat);
	void Terminate();

	void Bind(GraphicsSystem& gs);

private:
	ID3D11VertexShader* mpVertexShader;
	ID3D11InputLayout* mpVertexLayout;
};

#endif // #ifndef INCLUDED_ENGINE_VERTEXSHADER_H
