#pragma once

#include <map>
#include "CmdCommand.h"

class CScriptParser
{
public:
	CScriptParser(void);
	~CScriptParser(void);

public:
	// List of commands to run
	typedef struct
	{
		CString keyword;
		CString params;
	} CommandLine;

public:
	static void StringSplit( CStringList &result, CString &inputString, CString &splitter );

public:
	CCmdCommand *CommandLookup( CString &cmd );
	void ParseScript( CString &script );
	void ExecuteScript();

private:
	std::map<CString, CCmdCommand *> m_CommandDictionary;
	CList<CommandLine> m_CommandLines;
};
