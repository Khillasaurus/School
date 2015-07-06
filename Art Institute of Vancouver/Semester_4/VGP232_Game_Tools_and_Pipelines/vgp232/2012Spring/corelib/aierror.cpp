
#include "stdafx.h"
#include "core/aierror.h"
#include <Windows.h>


namespace AIDebug
{

	// dbPrint( "hello world" );
	void DebugMsgF( const char *pBuf)
	{
		//char szBuffer[8192];
		//sprintf(szBuffer, "%s\n",pBuf);
		//::OutputDebugString(szBuffer);
		// print to stdout as well
		//printf(szBuffer);

		::OutputDebugString(pBuf);
		printf(pBuf);
	}


	bool AssertFunc( bool expression, const char *pExpr, const char *pDesc, int line, const char *pFile, bool *ignoreAlways )
	{
		*ignoreAlways = false;

		// if assert exp is true, DO NOT hit breakpoint
		if( expression )
		{
			return false;
		}

		// dialog box
		// abort/retry/fail
		// TODO: display stack trace

		char szModName[ 260 ];
		if ( !GetModuleFileName( NULL , szModName , 250 ) )
		{
			strcpy( szModName , "<unknown application>");
		}

		char buf[1024];
		sprintf(buf, 
			"Debug Assertion Failed!\n\n"  \
			"Program : %s\n"               \
			"File : %s\n"                  \
			"Line : %d\n"                  \
			"Expression : %s\n"            \
			"Msg: %s\n",
			szModName, pFile, line, pExpr, pDesc);

		//AIDebug::DebugMessageF( buf );
		AIDebug::DebugMsgF(buf);
		//dbPrintf("%s(%d): [ ASSERT ] %s - %s", file, line, expression, description);

		{
			int rc = MessageBox(NULL, buf, "Assert", MB_ABORTRETRYIGNORE | MB_ICONERROR );
			switch(rc)
			{
			case IDABORT:
				return true;
			case IDRETRY:
				return false;	// aka DO NOT BREAK
			case IDIGNORE:
				*ignoreAlways = true;
				return false;   // aka DO NOT BREAK NOW,, and forever
			}
		}
		// ret val == "should assert" ,.. or "should hit breakpoint"
		return true;
	}

	// dbPrintf("hello %s", "world" );
	void DebugMessageV( const char *pFormat, ... )
	{
		char buf[8192];
		va_list va;
		va_start(va, pFormat);
		int sz = vsprintf(buf, pFormat, va);
		va_end(va);
		strcat(buf,"\n");
		::OutputDebugString( buf );
		printf(buf);
	}


}