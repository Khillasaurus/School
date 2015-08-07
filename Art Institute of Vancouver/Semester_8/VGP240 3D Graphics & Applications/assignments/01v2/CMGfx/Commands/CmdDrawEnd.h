//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdDrawEnd : public CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdDrawEnd(void){}
	// Destructor
	~CCmdDrawEnd(void){}

	//General Methods
	virtual BOOL execute(CString& params);
};