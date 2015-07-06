//====================================================================================================
// Filename:	Debug.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include <d3dx9.h>
#include <vector>

#include "Graphics/CDXGraphics.h"
#include "Utility/Debug.h"

//====================================================================================================
// Namespace
//====================================================================================================

namespace Debug
{

//====================================================================================================
// Structs
//====================================================================================================

struct SLine
{
	D3DXVECTOR2 from;
	D3DXVECTOR2 to;
	DWORD rgb;
	float size;

	SLine(void) :
		from(0.0f, 0.0f),
		to(0.0f, 0.0f),
		rgb(0xFFFFFF),
		size(1.0f)
	{ }

	SLine(const D3DXVECTOR2& _from,
		   const D3DXVECTOR2& _to,
		   DWORD _rgb,
		   float _size) :
		from(_from),
		to(_to),
		rgb(_rgb),
		size(_size)
	{ }
};

//====================================================================================================
// Statics
//====================================================================================================

static ID3DXLine* s_pLineRenderer = NULL;
static bool s_Initialized = false;

const int c_MaxNumLines = 10000;
static SLine s_LineList[c_MaxNumLines];

static int s_LineIndex = 0;

//====================================================================================================
// Function Definitions
//====================================================================================================

void Initialize(float fLineWidth)
{
	// Check if we have initialized
	if (s_Initialized)
	{
		return;
	}

	// Create a new ID3DXLine interface for rendering
	D3DXCreateLine(CDXGraphics::Get()->D3DDevice(), &s_pLineRenderer);

	// Set line width
	s_pLineRenderer->SetWidth(fLineWidth);

	// Set flag
	s_Initialized = true;
}

//----------------------------------------------------------------------------------------------------

void Terminate(void)
{
	// Check if we have terminated
	if (!s_Initialized)
	{
		return;
	}

	// Release everything
	if (NULL != s_pLineRenderer)
	{
		s_pLineRenderer->Release();
		s_pLineRenderer = NULL;
	}

	// Set flag
	s_Initialized = false;
}

//----------------------------------------------------------------------------------------------------

void AddScreenLine(float x0, float y0, float x1, float y1, DWORD rgb)
{
	// Check if we have initialized
	if (!s_Initialized)
	{
		return;
	}

	// Check if we have enough space
	if (s_LineIndex + 1>= c_MaxNumLines)
	{
		return;
	}

	// Add line to our list for rendering later
	s_LineList[s_LineIndex++] = SLine(D3DXVECTOR2(x0, y0), D3DXVECTOR2(x1, y1), rgb, 1.0f);
}

//----------------------------------------------------------------------------------------------------

void AddScreenRect(float x, float y, float w, float h, DWORD rgb)
{
	// Check if we have initialized
	if (!s_Initialized)
	{
		return;
	}

	// Check if we have enough space
	if (s_LineIndex + 4>= c_MaxNumLines)
	{
		return;
	}

	// Add line to our list for rendering later
	D3DXVECTOR2 A(x	, y	);
	D3DXVECTOR2 B(x + w, y	);
	D3DXVECTOR2 C(x + w, y + h);
	D3DXVECTOR2 D(x	, y + h);
	s_LineList[s_LineIndex++] = SLine(A, B, rgb, 1.0f);
	s_LineList[s_LineIndex++] = SLine(B, C, rgb, 1.0f);
	s_LineList[s_LineIndex++] = SLine(C, D, rgb, 1.0f);
	s_LineList[s_LineIndex++] = SLine(D, A, rgb, 1.0f);
}

//----------------------------------------------------------------------------------------------------

void AddScreenCircle(float x, float y, float r, DWORD rgb)
{
	// Check if we have initialized
	if (!s_Initialized)
	{
		return;
	}

	// Check if we have enough space
	if (s_LineIndex + 16>= c_MaxNumLines)
	{
		return;
	}

	// Add line to our list for rendering later
	const float angle = D3DX_PI / 8.0f;
	for (int i = 0; i < 16; ++i)
	{
		float alpha(i * angle);
		float beta((i + 1) * angle);

		D3DXVECTOR2 A(r * sin(alpha) + x, r * cos(alpha) + y);
		D3DXVECTOR2 B(r * sin(beta) + x, r * cos(beta) + y);

		s_LineList[s_LineIndex++] = SLine(A, B, rgb, 1.0f);
	}
}

//----------------------------------------------------------------------------------------------------

void Render(void)
{
	// Check if we have initialized
	if (!s_Initialized)
	{
		return;
	}

	// Begin render
	s_pLineRenderer->Begin();

	// Draw all the shapes
	for (int i = 0; i < s_LineIndex; ++i)
	{
		DWORD color = 0xFF000000 | s_LineList[i].rgb;
		s_pLineRenderer->Draw(&s_LineList[i].from, 2, color);
	}

	// End render
	s_pLineRenderer->End();

	// Reset index
	s_LineIndex = 0;
}

} // namespace Debug
