#ifndef INCLUDED_ENGINE_INPUTEVENT_H
#define INCLUDED_ENGINE_INPUTEVENT_H

//====================================================================================================
// Filename:	InputEvent.h
// Created by:	Peter Chan
// Description:	Struct for an input event.
//====================================================================================================

//====================================================================================================
// Structs
//====================================================================================================

struct InputEvent
{
	enum Type
	{
		Character,
		KeyUp,
		KeyDown,
		MouseUp,
		MouseDown,
		MouseMove
	};

	Type type;
	u32 value;
	s32 x;
	s32 y;
};

#endif // #ifndef INCLUDED_ENGINE_INPUTEVENT_H