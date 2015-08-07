//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdVertex2 : public CCmdCommand
{
public:
	CCmdVertex2(void){}
	~CCmdVertex2(void){}

public:
	BOOL execute(CString &params);
};