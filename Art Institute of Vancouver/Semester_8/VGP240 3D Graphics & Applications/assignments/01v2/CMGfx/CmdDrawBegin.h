//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdDrawBegin : public CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdDrawBegin(void){}
	// Destructor
	~CCmdDrawBegin(void){}

	//General Methods
	virtual BOOL execute(CString& params);
};