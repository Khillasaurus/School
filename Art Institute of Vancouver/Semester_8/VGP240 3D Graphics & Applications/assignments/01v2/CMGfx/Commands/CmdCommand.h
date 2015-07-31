#pragma once

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdCommand(void) {}
	// Destructor
	virtual ~CCmdCommand(void) {}

	//Function signature
	virtual BOOL execute(CString& params) = 0;
};
