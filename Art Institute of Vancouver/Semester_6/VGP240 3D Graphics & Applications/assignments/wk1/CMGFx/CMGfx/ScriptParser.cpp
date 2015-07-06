//=================================================================================================
// Edited by Daniel Schenker
//=================================================================================================

//=================================================================================================
// Includes
//=================================================================================================

//Precompiled Headers
#include "stdafx.h"

//CMGfx
#include "ScriptParser.h"
#include "CmdColor.h"
#include "CmdDrawPixel.h"

//=================================================================================================
//Class Definitions
//=================================================================================================

//-------------------------------------------------------------------------------------------------
//Constuctors
//-------------------------------------------------------------------------------------------------

CScriptParser::CScriptParser(void)
{
	//Initialize dictionary
	 //Basic commands
	m_CommandDictionary.insert(std::make_pair("drawpixel", new CCmdDrawPixel));
	m_CommandDictionary.insert(std::make_pair("color", new CCmdColor));
}

//-------------------------------------------------------------------------------------------------
//Deconstructor
//-------------------------------------------------------------------------------------------------

CScriptParser::~CScriptParser(void)
{
	//Delete dictionary memory
	while(m_CommandDictionary.begin() != m_CommandDictionary.end())
	{
		delete m_CommandDictionary.begin()->second;
		m_CommandDictionary.erase(m_CommandDictionary.begin());
	}
}

//-------------------------------------------------------------------------------------------------
//General Functions
//-------------------------------------------------------------------------------------------------

//Split given input string into a string list, using given "splitString" as the separators
void CScriptParser::StringSplit(CStringList &result, CString &inputString, CString &splitter)
{
	int splitterLength = splitter.GetLength();
	CString choppedString = inputString;
	
	//Split string
	int splitPos = choppedString.Find(splitter);
	while(splitPos != -1)
	{
		CString word = choppedString.Left(splitPos);
		if (!word.IsEmpty())
		{
			result.AddTail(word);
		}
		choppedString = choppedString.Right(choppedString.GetLength() - splitPos - splitterLength);
		splitPos = choppedString.Find(splitter);
	}

	// Add last word
	if(!choppedString.IsEmpty())
	{
		result.AddTail(choppedString);
	}
}

//-------------------------------------------------------------------------------------------------

//Look up command in dictionary to return command object
CCmdCommand* CScriptParser::CommandLookup(CString &cmd)
{
	std::map<CString, CCmdCommand*>::const_iterator iter;
	iter = m_CommandDictionary.find(cmd.MakeLower());
	if(iter != m_CommandDictionary.end())
	{
		return iter->second;
	}
	else
	{
		return NULL;
	}
}

//-------------------------------------------------------------------------------------------------

// Parse script into commands and parameters
void CScriptParser::ParseScript(CString &script)
{
	//Strip off Windows return characters
	script.Remove('\r');

	//Separate script into separate lines in a list
	CStringList commandLineList;
	CScriptParser::StringSplit(commandLineList, script, CString('\n'));

	// For each command line, split out keyword and parameters
	POSITION pos;
	for(pos = commandLineList.GetHeadPosition(); pos != NULL;)
	{
		CommandLine command;

		CString line = commandLineList.GetNext(pos);
		int firstSpacePos = line.Find(' ');
		if(firstSpacePos != -1 && firstSpacePos != 0)
		{
			command.keyword = line.Left(firstSpacePos);
			command.params = line.Right(line.GetLength() - firstSpacePos - 1);
		}
		else
		{
			command.keyword = line;
			command.params.Empty();
		}
		m_CommandLines.AddTail(command);
	}

	// Debug
	/*
	for( pos = m_CommandLines.GetHeadPosition(); pos != NULL; )
	{
		CommandLine cmdLine = m_CommandLines.GetNext( pos );
		CString str = CString("keyword: \"") + cmdLine.keyword + CString("\"");
		str = str + CString("\nparams: \"") + cmdLine.params + CString("\"");
		AfxMessageBox(str);
	}
	*/
}

//-------------------------------------------------------------------------------------------------

void CScriptParser::ExecuteScript()
{
	// Execute script commands
	POSITION pos;
	for(pos = m_CommandLines.GetHeadPosition(); pos != NULL;)
	{
		CommandLine cmdLine = m_CommandLines.GetNext(pos);
		CCmdCommand* command = CommandLookup(cmdLine.keyword);
		if (command != NULL)
		{
			command->execute(cmdLine.params);
		}
	}
}
