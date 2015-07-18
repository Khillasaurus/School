#include "StdAfx.h"
#include "CmdColor.h"
#include "ScriptParser.h"
#include "Rasterizer.h"

BOOL CCmdColor::execute( CString &params )
{
	// Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit( paramStrList, params, CString( ' ' ) );

	// Need at least 3 params for r, g, b
	const int numParams = 3;
	if ( paramStrList.GetCount() < numParams )
	{
		return FALSE;
	}

	float channels[numParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < numParams; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		channels[i] = (float)wcstod(paramStr, NULL);
	}

	CRasterizer::Instance()->SetColor(channels[0], channels[1], channels[2]);

	return TRUE;
}
