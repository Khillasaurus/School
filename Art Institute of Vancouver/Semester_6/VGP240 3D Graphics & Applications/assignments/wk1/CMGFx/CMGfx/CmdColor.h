//=================================================================================================
// File:			CmdColor.h
// Created:			2012/10/03
// Last Modified:	2012/10/03
// Copyright:		Daniel Schenker
// Description:		Command script to set the color of a pixel.
//=================================================================================================

#ifndef CMGFX_CMDCOLOR_H
#define CMGFX_CMDCOLOR_H

//=================================================================================================
// Includes
//=================================================================================================

//CMGfx
#include "CmdCommand.h"

//=================================================================================================
//Class Declarations
//=================================================================================================

class CCmdColor : public CCmdCommand
{
public:
	//Constructors
	CCmdColor();
	//Deconstructors
	~CCmdColor();

	//General Functions
	BOOL execute(CString &params);
};

#endif //CMGFX_CMDCOLOR_H