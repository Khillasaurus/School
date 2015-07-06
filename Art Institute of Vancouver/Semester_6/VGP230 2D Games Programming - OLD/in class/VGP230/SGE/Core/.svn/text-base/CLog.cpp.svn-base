//====================================================================================================
// Filename:	CLog.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "CLog.h"

#include <cassert>
#include <cstdio>
#include <ctime>

//====================================================================================================
// Constants
//====================================================================================================

const char* c_LogMessageColour[ELogMessageType_MAX] =
{
	"#0000FF",  // ELogMessageType_MESSAGE,
	"#FFFF00",  // ELogMessageType_WARNING,
	"#FF0000"   // ELogMessageType_ERROR
};

//====================================================================================================
// Statics
//====================================================================================================

CLog* CLog::s_pInstance = NULL;

//====================================================================================================
// Class Definitions
//====================================================================================================

CLog* CLog::Get(void)
{
	// If we do not yet have an instance created
	if (NULL == s_pInstance)
	{
		// Create a new instance
		s_pInstance = new CLog;
	}

	return s_pInstance;
}

//----------------------------------------------------------------------------------------------------

CLog::CLog(void)
	: mpFilename(NULL)
	, mInitialized(false)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

void CLog::Initialize(const char* pFilename)
{
	// Open a file for writing
	FILE* pFile = NULL;
	fopen_s(&pFile, pFilename, "wt");

	// Check if we can open a file
	if (NULL == pFile)
	{
		MessageBoxA(NULL, "Error: Cannot open file for error log", "CLog", MB_OK | MB_ICONERROR);
		return;
	}

	// Write the header for our log file
	fprintf_s(pFile, "<HTML>\n<HEAD><TITLE>Application Log</TITLE></HEAD>\n<BODY BGCOLOR = \"#000000\">\n");

	// Get time and date
	char time[32];
	char date[32];
	_strtime_s(time, 32);
	_strdate_s(date, 32);

	// Write the time and date into the file
	fprintf_s(pFile, "<FONT COLOR = \"#FFFFFF\">Log Started at %s on %s</FONT><BR><BR>\n", time, date);
	fprintf_s(pFile, "</BODY></HTML>");

	// Close the file
	fclose(pFile);

	// Remember the file name for logging later
	mpFilename = const_cast<char*>(pFilename);

	// Set flag
	mInitialized = true;
}

//----------------------------------------------------------------------------------------------------

void CLog::Terminate(void)
{
	// Clear the file name
	mpFilename = NULL;

	// Set flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

void CLog::Write(ELogMessageType eLogMessageType, const char* pMessage, ...)
{
	va_list args;
	va_start(args, pMessage);
	Write(eLogMessageType, pMessage, args);
	va_end(args);
}

//----------------------------------------------------------------------------------------------------

void CLog::Write(ELogMessageType eLogMessageType, const char* pMessage, va_list args)
{
	// Make sure we have initialized first
	if (!mInitialized)
	{
		MessageBoxA(NULL, "Error: Log must be initialized first before writing any messages.", "CLog", MB_OK | MB_ICONERROR);
		return;
	}

	// Open a file for writing
	FILE* pFile = NULL;
	fopen_s(&pFile, mpFilename, "r+");

	// Check if we can open a file
	if (NULL == pFile)
	{
		MessageBoxA(NULL, "Error: Cannot open file for error log", "CLog", MB_OK | MB_ICONERROR);
		return;
	}

	// Move file cursor to before the end of file body
	fseek(pFile, -14, SEEK_END);

	// Get message
	char msg[1024];
	vsprintf_s(msg, 1024, pMessage, args);

	// Get time
	char time[32];
	_strtime_s(time, 32);

	// Write the message and time into the file
	const char* pColour = c_LogMessageColour[eLogMessageType];
	fprintf_s(pFile, "<FONT COLOR = \"%s\">%s&nbsp;&nbsp;&nbsp;&nbsp;%s</FONT><BR>\n", pColour, time, msg);
	fprintf_s(pFile, "</BODY></HTML>");

	// Close the file
	fclose(pFile);
}