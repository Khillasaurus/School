//=============================================================================
//Dependencies
//=============================================================================

#pragma once
#include "CmdCommand.h"

//=============================================================================
//Class Declarations
//=============================================================================

class CCmdDrawPixel : public CCmdCommand
{
public:
	//Default Methods
	// Constructors
	CCmdDrawPixel(void){}
	// Destructor
	~CCmdDrawPixel(void){}

	//General Methods
	virtual BOOL execute(CString& params);
};