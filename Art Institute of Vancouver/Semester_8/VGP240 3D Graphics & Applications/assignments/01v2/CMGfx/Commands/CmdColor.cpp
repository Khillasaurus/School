//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include "CmdColor.h"
#include "ScriptParser.h"
#include "../Display/Rasterizer.h"
#include "../Display/StateManager.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdColor::execute(CString& params)
{
	//Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	//Need at least 3 params for r, g, b
	const int kNumParams = 3;
	if(paramStrList.GetCount() < kNumParams)
	{
		return FALSE;
	}

	float channels[kNumParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < kNumParams; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		channels[i] = (float)wcstod(paramStr, NULL);
	}

	CStateManager::GetInstance()->SetColor(CColor(channels[0], channels[1], channels[2]));

	return TRUE;
}