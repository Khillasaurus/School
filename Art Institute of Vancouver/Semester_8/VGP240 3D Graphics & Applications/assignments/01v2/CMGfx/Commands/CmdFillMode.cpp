//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include "CmdFillMode.h"
#include "ScriptParser.h"
#include "../Display/StateManager.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdFillMode::execute(CString& params)
{
	//Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	//Should be just 1 parameter
	const int kNumParams = 1;
	if(paramStrList.GetCount() < kNumParams)
	{
		return FALSE;
	}
	else
	{
		POSITION pos = paramStrList.GetHeadPosition();
		CString paramStr = paramStrList.GetNext(pos);

		//Check to see which param was specified
		FillMode modeCur = FillMode::kFillModeNone;
		CString validParams[FillMode::kFillModeLast + 1];
		validParams[FillMode::kFillModePoint] = "point";
		validParams[FillMode::kFillModeLine] = "line";
		validParams[FillMode::kFillModeFill] = "fill";

		//Compare parameter against valid fill modes
		for(int i = 0; i < FillMode::kFillModeLast + 1; ++i)
		{
			if(paramStr.CompareNoCase(validParams[i]) == 0)
			{
				modeCur = (FillMode)i;
				break;
			}
		}

		//Verify correct param and pass to state manager
		if(FillMode::kFillModeNone != modeCur)
		{
			CStateManager::GetInstance()->SetFillMode(modeCur);
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		return TRUE;
	}
}