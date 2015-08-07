//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include "CmdDrawEnd.h"
#include "ScriptParser.h"
#include "../Display/PrimManager.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdDrawEnd::execute(CString& params)
{
	CPrimManager::GetInstance()->EndDraw();

	return TRUE;
}