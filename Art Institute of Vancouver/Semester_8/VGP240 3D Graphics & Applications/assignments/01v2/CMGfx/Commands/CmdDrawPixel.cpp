//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include "CmdDrawPixel.h"
#include "ScriptParser.h"
#include "../Display/Rasterizer.h"
#include "../Display/StateManager.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdDrawPixel::execute(CString& params)
{
	//Decode parameters
	CStringList paramStrList;
	CScriptParser::StringSplit(paramStrList, params, CString(' '));

	//Need at least 2 params for x, y
	const int kNumParams = 2;
	if(paramStrList.GetCount() < kNumParams)
	{
		return FALSE;
	}

	int coords[kNumParams];
	POSITION pos = paramStrList.GetHeadPosition();
	for(int i = 0; i < kNumParams; ++i)
	{
		CString paramStr = paramStrList.GetNext(pos);
		coords[i] = (int)(wcstod(paramStr, NULL) + 0.5f);
	}

	//Draw the pixel
	CRasterizer::Instance()->DrawPoint(coords[0], coords[1]);

	return TRUE;
}