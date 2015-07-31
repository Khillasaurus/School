#include "StdAfx.h"
#include "CmdVertex2.h"
#include "../Commands/ScriptParser.h"
#include "../Display/Rasterizer.h"

BOOL CCmdVertex2::execute(CString &params)
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString( ' ' ));

	// Need at least 2 params for x, y
	const int numParams = 2;
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

	//TODO: Change this the following to store a vertex2
	//CRasterizer::Instance()->DrawPoint(coords[0], coords[1]);

	return TRUE;
}