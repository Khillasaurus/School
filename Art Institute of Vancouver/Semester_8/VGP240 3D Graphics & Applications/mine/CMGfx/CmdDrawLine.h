#pragma once
#include "CmdCommand.h"

class CCmdDrawLine : public CCmdCommand
{
public:
	CCmdDrawLine(void){}
	~CCmdDrawLine(void){}

public:
	BOOL execute(CString &params);
};