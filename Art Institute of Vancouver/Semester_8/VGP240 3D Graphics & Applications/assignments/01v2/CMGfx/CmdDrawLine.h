#pragma once
#include "CmdCommand.h"

class CCmdDrawLine : public CCmdCommand
{
public:
	CCmdDrawLine(void){}
	~CCmdDrawLine(void){}

public:
	virtual BOOL execute(CString &params);
};