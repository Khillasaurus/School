#include "stdafx.h"
#include "CmdVertex2.h"
#include "../Commands/ScriptParser.h"
#include "../Display/PrimManager.h"
#include "../Display/StateManager.h"

BOOL CCmdVertex2::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	// Need at least 2 params for x, y
	const int kNumParams = 2;
	if(paramStrList.GetCount() < kNumParams)
	{
		return FALSE;
	}

	float coords[kNumParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < kNumParams; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		coords[i] = (float)(wcstod(paramStr, NULL));
	}

	CVertex2 vertexCur;
	vertexCur.point.x = coords[0];
	vertexCur.point.y = coords[1];
	vertexCur.color = CStateManager::GetInstance()->GetColor();

	CPrimManager::GetInstance()->AddVertex(vertexCur);

	return TRUE;
}