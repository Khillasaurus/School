//-----------------------------
// File:		aierror.cpp
// Created:		2012/04/02
// Copyright:	Daniel Schenker
//-----------------------------

#include "stdafx.h"
#include "core/aierror.h"
#include <Windows.h>
#include "stdio.h"

const int kMaxStringSize = 260;

bool AIDebug::AssertFunc(bool expression, const char *pExpr, const char *pDesc, int line, const char * pFile, bool* ignoreAlways)
{
	ignoreAlways = false;

	//if assert exp is true, DO NOT hit breakpoint
	if(expression)
	{
		 return false;
	}

	// TODO: impl dialog box
	// abort/retry/fail
	// display stack trace

	char szModName[kMaxStringSize];
	if(!GetModuleFileName(NULL , szModName, kMaxStringSize))
	{
		strcpy(szModName, "<unknown application>");
	}

	char buf[512];
	sprintf(buf,
		"Debug Assertion failed!\n\n"	\
		"Program : %s\n"				\
		"File : %s\n"					\
		"Line : %d\n"					\
		"Expression %s\n"				\
		"Msg: %s\n",
		szModName, pFile, line, pExpr, pDesc);

	//dbPrintf("%s(%d): [ ASSERT ] %s - %s", file, line, expression, description);

	int rc = MessageBox(NULL, buf, "Assert", MB_ABORTRETRYIGNORE | MB_ICONERROR);
	switch(rc)
	{
	case IDABORT:
		return true;	//< break into Assertion
	case IDRETRY:
		return false;	// ignore once
	case IDIGNORE:
		*ignoreAlways = true;
		return false;	// ignore forever
	}

	//ret val == "should assert" ... or "should hit breakpoint"
	return true;
}

// dbPrintf("hello %s", "world");
void AIDebug::DebugMessageV(const char *pFormat, ...)
{
	char buf[8192];
	va_list va;
	va_start(va, pFormat);
	int sz = vsprintf(buf, pFormat, va);
	va_end(va);
	strcat(buf, "\n");
	::OutputDebugString(buf);
	printf(buf);
}

// dbPrint("hello world");
void AIDebug::DebugMessageF(const char *pBuf)
{
	char szBuffer[8192];
	sprintf(szBuffer, "%s\n", pBuf);
	::OutputDebugString(szBuffer);

	// print to stdout as well
	printf(szBuffer);
}