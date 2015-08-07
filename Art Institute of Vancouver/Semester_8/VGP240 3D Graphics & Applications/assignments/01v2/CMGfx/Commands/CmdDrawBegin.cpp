//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include "CmdDrawBegin.h"
#include "ScriptParser.h"
#include "../Display/PrimManager.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdDrawBegin::execute(CString& params)
{
	//Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	//Should be just 1 paramater (namely the word for what we are going to draw)
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
		Primitive primitiveCur = Primitive::kPrimitiveNone;
		CString validParams[Primitive::kPrimitiveLast + 1];
		validParams[Primitive::kPrimitivePoint] = "point";
		validParams[Primitive::kPrimitiveLine] = "line";
		validParams[Primitive::kPrimitiveTriangle] = "triangle";

		//Compare parameter against valid primitive types
		for(int i = 0; i < Primitive::kPrimitiveLast + 1; ++i)
		{
			if(paramStr.CompareNoCase(validParams[i]) == 0)
			{
				primitiveCur = (Primitive)i;
				break;
			}
		}

		//Verify correct param and pass to state manager
		if(Primitive::kPrimitiveNone != primitiveCur)
		{
			CPrimManager::GetInstance()->BeginDraw(primitiveCur);
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}