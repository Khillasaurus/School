#ifndef INCLUDED_DEBUG_H
#define INCLUDED_DEBUG_H

//====================================================================================================
// Filename:	Debug.h
// Created by:	Peter Chan
// Description:	Header containing some useful debug rendering functions. A call to Debug::Initialize()
//			  must be made after the graphics system has been initialized to setup for debug
//			  rendering. During program termination, Debug::Terminate() must be called to clear all
//			  allocated resources.
//====================================================================================================

//====================================================================================================
// Namespace
//====================================================================================================

namespace Debug
{

//====================================================================================================
// Function Declarations
//====================================================================================================

// Functions to initialize/terminate the debug renderer
void Initialize(float fLineWidth = 1.0f);
void Terminate(void);

// Functions for adding new vertices for debug rendering
void AddScreenLine(float x0, float y0, float x1, float y1, DWORD rgb = 0xFFFFFF);
void AddScreenRect(float x, float y, float w, float h, DWORD rgb = 0xFFFFFF);
void AddScreenCircle(float x, float y, float r, DWORD rgb = 0xFFFFFF);
void AddScreenText(const char* text, float x, float y, DWORD rgb = 0xFFFFFF);

// Function to actually render all the geometry
void Render(void);

} // namespace Debug

#endif // #ifndef INCLUDED_DEBUG_H