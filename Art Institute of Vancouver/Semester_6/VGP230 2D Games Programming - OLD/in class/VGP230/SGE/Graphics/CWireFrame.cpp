//====================================================================================================
// Filename:	CWireFrame.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Graphics/CWireFrame.h"

#include "Core/CLog.h"
#include "Graphics/CDXGraphics.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CWireFrame::CWireFrame(void)
	: mpLineRenderer(NULL)
	, mColor(0xFFFFFFFF)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

CWireFrame::CWireFrame(const CWireFrame& rhs)
	: mpLineRenderer(NULL)
	, mColor(0xFFFFFFFF)
{
	// Copy vertex data
	const int kNumVertices = rhs.mVertices.size();
	for (int i = 0; i < kNumVertices; ++i)
	{
		mVertices.push_back(rhs.mVertices[i]);
	}

	// Copy color
	mColor = rhs.mColor;
}

//----------------------------------------------------------------------------------------------------

CWireFrame::~CWireFrame(void)
{
	// Release everything
	Destroy();
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::Create(void)
{
	// Release everything
	Destroy();

	// Create a new ID3DXLine interface for rendering
	D3DXCreateLine(CDXGraphics::Get()->D3DDevice(), &mpLineRenderer);
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::Destroy(void)
{
	// Release the font
	if (NULL != mpLineRenderer)
	{
		mpLineRenderer->Release();
		mpLineRenderer = NULL;
	}
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::Render(void)
{
	// Begin render
	mpLineRenderer->Begin();

	// Draw all the shapes
	const int kNumLines = mVertices.size() / 2;
	for (int i = 0; i < kNumLines; ++i)
	{
		const int index = i * 2;
		mpLineRenderer->Draw(&mVertices[index], 2, mColor);
	}

	// End render
	mpLineRenderer->End();
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::AddLine(float x0, float y0, float x1, float y1)
{
	mVertices.push_back(D3DXVECTOR2(x0, y0));
	mVertices.push_back(D3DXVECTOR2(x1, y1));
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::AddRect(float x, float y, float w, float h)
{
	mVertices.push_back(D3DXVECTOR2(x , y));
	mVertices.push_back(D3DXVECTOR2(x + w, y));
	mVertices.push_back(D3DXVECTOR2(x + w, y));
	mVertices.push_back(D3DXVECTOR2(x + w, y + h));
	mVertices.push_back(D3DXVECTOR2(x + w, y + h));
	mVertices.push_back(D3DXVECTOR2(x, y + h));
	mVertices.push_back(D3DXVECTOR2(x, y + h));
	mVertices.push_back(D3DXVECTOR2(x, y));
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::AddCircle(float x, float y, float r)
{
	// Add line to our list for rendering later
	const float angle = D3DX_PI / 8.0f;
	for (int i = 0; i < 16; ++i)
	{
		const float alpha(i * angle);
		const float beta((i + 1) * angle);

		mVertices.push_back(D3DXVECTOR2(r * sin(alpha) + x, r * cos(alpha) + y));
		mVertices.push_back(D3DXVECTOR2(r * sin(beta) + x, r * cos(beta) + y));
	}
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::Purge(void)
{
	mVertices.clear();
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::SetLineWidth(float fLineWidth)
{
	mpLineRenderer->SetWidth(fLineWidth);
}

//----------------------------------------------------------------------------------------------------

void CWireFrame::SetColor(DWORD rgb)
{
	mColor = 0xFF000000 | rgb;
}