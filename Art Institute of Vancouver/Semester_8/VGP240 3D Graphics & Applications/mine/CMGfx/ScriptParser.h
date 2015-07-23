//=============================================================================
//Dependencies
//=============================================================================

#pragma once

#include <map>
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CScriptParser
{
public:
	//Default Methods
	// Constructors
	CScriptParser(void);
	// Destructor
	~CScriptParser(void);

	//List of commands to run
	typedef struct
	{
		CString keyword;
		CString params;
	} CommandLine;

	//Static Methods
	static void StringSplit(CStringList& result, CString& inputString, CString& splitter);

	//General Methods
	CCmdCommand* CommandLookup(CString& cmd);
	void ParseScript(CString& script);
	void ExecuteScript();

private:
	std::map<CString, CCmdCommand*> m_CommandDictionary;
	CList<CommandLine> m_CommandLines;
};