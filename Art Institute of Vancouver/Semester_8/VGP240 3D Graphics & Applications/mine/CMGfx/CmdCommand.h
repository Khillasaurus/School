#pragma once

class CCmdCommand
{
public:
	CCmdCommand(void) {}
	virtual ~CCmdCommand(void) {}

public:
	// Function signature
    virtual BOOL execute(CString &) = 0;
};
