#include "StdAfx.h"
#include "CmdDrawLine.h"
#include "ScriptParser.h"
#include "../Display/Rasterizer.h"

BOOL CCmdDrawLine::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString( ' ' ));

	// Need at least 4 params for x1, y1, x2, y2
	const int numParams = 4;
	if(paramStrList.GetCount() < numParams)
	{
		return FALSE;
	}

	int coords[numParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < numParams; i++)
	{
		CString paramStr = paramStrList.GetNext(pos);
		coords[i] = (int)(wcstod(paramStr, NULL) + 0.5f);
	}

	CRasterizer::Instance()->DrawLine(coords[0], coords[1], coords[2], coords[3]);

	return TRUE;
}