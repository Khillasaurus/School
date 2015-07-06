//=================================================================================================
// Edited by Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

#pragma once

//STL
#include <map>

//CMGfx
#include "CmdCommand.h"


//=================================================================================================
//Class Declarations
//=================================================================================================

class CScriptParser
{
public:
	//Constructors
	CScriptParser();
	//Deconstructors
	~CScriptParser();

	// List of commands to run
	typedef struct
	{
		CString keyword;
		CString params;
	}CommandLine;

	//Static Functions
	static void StringSplit( CStringList &result, CString &inputString, CString &splitter );

	//General Functions
	CCmdCommand* CommandLookup(CString &cmd);
	void ParseScript(CString &script);
	void ExecuteScript();

private:
	//Member Variables
	std::map<CString, CCmdCommand*> m_CommandDictionary;
	CList<CommandLine> m_CommandLines;
};
