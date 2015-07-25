//=============================================================================
//Dependencies
//=============================================================================

#include "StdAfx.h"
#include "CmdDrawBegin.h"
#include "ScriptParser.h"
#include "Rasterizer.h"

//=============================================================================
//Class Definitions
//=============================================================================

BOOL CCmdDrawBegin::execute(CString& params)
{
	////Decode parameters
	//CStringList paramStrList;
	//CScriptParser::StringSplit(paramStrList, params, CString( ' ' ));

	//// Need at least 5 params for drawbegin, drawtype, x1, y1, drawend
	//const int kNumParams = paramStrList.GetCount();
	//if(kNumParams < 5)
	//{
	//	return FALSE;
	//}
	//else
	//{
	//	//Create array to store parameter information
	//	CString coords[kNumParams];

	//	//Iterate through string list and insert data into parameter info array named coords
	//	POSITION pos = paramStrList.GetHeadPosition();
	//	for(int i = 0; i < kNumParams; i++)
	//	{
	//		CString paramStr = paramStrList.GetNext(pos);
	//		//TODO: Add LIKELY macro here for the following if statement often being true)
	//		//Convert all vertex data CStrings into integers to be used as pixel coordinates
	//		if(coords[i] >= 2 && coords [i] < kNumParams)
	//		{
	//			coords[i] = (int)(wcstod(paramStr, NULL) + 0.5f);
	//		}
	//	}

	//	CRasterizer::Instance()->DrawLine(coords[0], coords[1], coords[2], coords[3]);

	//	return TRUE;
	//}

	return TRUE;
}

////Determine draw mode
//	//need 1 param for type
//	const int numParamsMode = 1;
//	if(paramStrList.GetCount() < numParamsMode)
//	{
//		return FALSE;
//	}
//
//	CString type[numParamsMode];
//	POSITION pos = paramStrList.GetHeadPosition();
//	for(int i = 0; i < numParamsMode; i++)
//	{
//		type[i] = paramStrList.GetNext(pos);
//	}
//	pos++;
//
//	//Draw mode
//	// Line
//	if(type[0] == "line")
//	{
//		//need at least 4 params to make a line (x1, y1, x2, y2)
//		const int numParams = 4;
//		if(paramStrList.GetCount() < numParamsMode)
//		{
//			return FALSE;
//		}
//
//		//Create a linked list of Vertex2 classes and insert begin and end point data until drawend is found.
//		//	if an odd number of vertices is given, ignore the last one.
//		//TODO: Linked list here
//		while(paramStrList.GetNext(pos) != "drawend")
//		{
//			CString coords[numParams];
//			POSITION pos = paramStrList.GetHeadPosition();
//			for(int i = 0; i < numParams; i++)
//			{
//				coords[i] = paramStrList.GetNext(pos);
//				coords[i] = (int)(wcstod(paramStrList, NULL) + 0.5f);
//			}
//		}
//		/*
//		for(int i = numParamsMode; i < vertex count; ++i)
//		{
//		}
//		*/
//	}
//
//CRasterizer::Instance()->DrawLine(coords[0]);