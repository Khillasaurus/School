//=============================================================================
//Dependencies
//=============================================================================

//Precompiled Headers
#include "stdafx.h"

//General
#include "StateManager.h"
#include "Rasterizer.h"

//=============================================================================
//Statics
//=============================================================================

CStateManager* CStateManager::pInstance = nullptr;

//=============================================================================
//Class Definitions
//=============================================================================

//-----------------------------------------------------------------------------
//Accessors
//-----------------------------------------------------------------------------

CStateManager* CStateManager::GetInstance()
{
	if(pInstance == nullptr)
	{
		pInstance = new CStateManager();
	}

	return pInstance;
}

//-----------------------------------------------------------------------------

const CColor& CStateManager::GetColor() const
{
	return mColor;
}

//-----------------------------------------------------------------------------

FillMode CStateManager::GetFillMode() const
{
	return mFillMode;
}

//-----------------------------------------------------------------------------
//Manipulators
//-----------------------------------------------------------------------------

void CStateManager::SetColor(const CColor& color)
{
	mColor = color;
	CRasterizer::Instance()->SetColor(color);
}

//-----------------------------------------------------------------------------

void CStateManager::SetFillMode(FillMode mode)
{
	mFillMode = mode;
}