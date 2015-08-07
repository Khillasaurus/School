//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdFillMode : public CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdFillMode(void){}
	// Destructor
	~CCmdFillMode(void){}

	//General Methods
	virtual BOOL execute(CString& params);
};