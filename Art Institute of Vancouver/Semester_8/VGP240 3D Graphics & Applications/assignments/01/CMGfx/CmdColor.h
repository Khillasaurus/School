#pragma once
#include "CmdCommand.h"

class CCmdColor : public CCmdCommand
{
public:
	CCmdColor(void) {}
	~CCmdColor(void) {}

public:
	BOOL execute( CString &params );
};
