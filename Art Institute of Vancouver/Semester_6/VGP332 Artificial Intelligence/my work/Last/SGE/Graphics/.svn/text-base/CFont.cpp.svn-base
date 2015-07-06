//====================================================================================================
// Filename:	CFont.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CFont.h"

#include "Core/CLog.h"
#include "Graphics/CDXGraphics.h"
#include "Graphics/CSpriteRenderer.h"

//====================================================================================================
// Class Definitions
//====================================================================================================

CFont::CFont(void)
	: mpFont(NULL)
	, mColor(0xFFFFFFFF)
	, mFormat(DT_LEFT | DT_TOP | DT_NOCLIP)
{
	// Set a default text area
	SetRect(&mTextArea, 0, 0, 1000, 1000);
}

//----------------------------------------------------------------------------------------------------

CFont::~CFont(void)
{
	// Release everything
	Destroy();
}

//----------------------------------------------------------------------------------------------------

void CFont::Create(const char* pFontType, int iSize, bool bBold, bool bItalic)
{
	HRESULT hr = D3DXCreateFontA
	(
		CDXGraphics::Get()->D3DDevice(),	// Direct3D device
		iSize,								// Font height
		0,									// Font width (0 = default based on height)
		(bBold) ? 800 : 500,				// Weight (0 - 1000)
		1,									// MipMap level
		bItalic,							// Use italic?
		DEFAULT_CHARSET,					// Character set
		OUT_DEFAULT_PRECIS,					// Output precision
		DEFAULT_QUALITY,					// Quality
		DEFAULT_PITCH | FF_DONTCARE,		// Pitch and font family
		pFontType,
		&mpFont
	);

	if (FAILED(hr))
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Font] Failed to create Direct3D font.");
		return;
	}
}

//----------------------------------------------------------------------------------------------------

void CFont::Destroy(void)
{
	// Release the font
	if (NULL != mpFont)
	{
		mpFont->Release();
		mpFont = NULL;
	}
}

//----------------------------------------------------------------------------------------------------

void CFont::SetColor(int iRed, int iGreen, int iBlue)
{
	// Set color
	mColor = D3DCOLOR_RGBA(iRed, iGreen, iBlue, 255);
}

//----------------------------------------------------------------------------------------------------

void CFont::SetTextArea(int iPosX, int iPosY, int iWidth, int iHeight)
{
	// Validate parameters
	if (iPosX <0)
	{
		iPosX = 0;
	}
	if (iPosY <0)
	{
		iPosY = 0;
	}
	if (iWidth <1)
	{
		iWidth = 1;
	}
	if (iHeight <1)
	{
		iHeight = 1;
	}

	// Set the text area
	SetRect(&mTextArea, iPosX, iPosY, iPosX + iWidth, iPosY + iHeight);
}

//----------------------------------------------------------------------------------------------------

void CFont::SetFormat(int iFormat)
{
	// Clear old format
	mFormat = 0;

	// Check for horizontal alignment
	if (iFormat & FontFormat::LEFT)
	{
		mFormat |= DT_LEFT;
	}
	else if (iFormat & FontFormat::CENTER)
	{
		mFormat |= DT_CENTER;
	}
	else if (iFormat & FontFormat::RIGHT)
	{
		mFormat |= DT_RIGHT;
	}

	// Check for vertical alignment
	if (iFormat & FontFormat::TOP)
	{
		mFormat |= DT_TOP;
	}
	else if (iFormat & FontFormat::MIDDLE)
	{
		mFormat |= DT_VCENTER;
	}
	else if (iFormat & FontFormat::BOTTOM)
	{
		mFormat |= DT_BOTTOM;
	}

	// Check if single- or multi-line
	if (iFormat & FontFormat::SINGLE)
	{
		mFormat |= DT_SINGLELINE;
	}
	else if (iFormat & FontFormat::MULTI)
	{
		mFormat |= DT_WORDBREAK;
	}

	// Always turn no-clip on
	mFormat |= DT_NOCLIP;
}

//----------------------------------------------------------------------------------------------------

void CFont::PrintText(const char* pText, int iPosX, int iPosY)
{
	if (NULL == mpFont)
	{
		// Write to log
		CLog::Get()->Write(ELogMessageType_WARNING, "[Font] Cannot draw text without a font.");
		return;
	}

	RECT rect = mTextArea;
	rect.left += iPosX;
	rect.right += iPosX;
	rect.top += iPosY;
	rect.bottom += iPosY;

	// Reset transform
	D3DXMATRIX matIdentity;
	D3DXMatrixIdentity(&matIdentity);
	CSpriteRenderer::Get()->D3DXSprite()->SetTransform(&matIdentity);

	// Render the string
	mpFont->DrawTextA
	(
		CSpriteRenderer::Get()->D3DXSprite(),	// Sprite object for batching and optimization
		pText,									// String to draw
		-1,										// Character count (-1 = auto detect if null terminated)
		&rect,									// Render area
		mFormat,								// Format
		mColor									// Color
	);
}