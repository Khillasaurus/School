//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdColor : public CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdColor(void) {}
	// Destructor
	~CCmdColor(void) {}

	//General Methods
	virtual BOOL execute(CString& params);
};
