#ifndef INCLUDED_ENGINE_INPUTTYPES_H
#define INCLUDED_ENGINE_INPUTTYPES_H

//====================================================================================================
// Filename:	InputTypes.h
// Created by:	Peter Chan
// Description:	Header containing a bunch on constants for inputs.
//====================================================================================================

//====================================================================================================
// Constants
//====================================================================================================

namespace Keys
{
	// Keyboard roll 1
	const u32 ESCAPE		= 0x01;
	const u32 F1			= 0x3B;
	const u32 F2			= 0x3C;
	const u32 F3			= 0x3D;
	const u32 F4			= 0x3E;
	const u32 F5			= 0x3F;
	const u32 F6			= 0x40;
	const u32 F7			= 0x41;
	const u32 F8			= 0x42;
	const u32 F9			= 0x43;
	const u32 F10			= 0x44;
	const u32 F11			= 0x57;
	const u32 F12			= 0x58;

	// Keyboard roll 2
	const u32 GRAVE			= 0x29;
	const u32 ONE			= 0x02;
	const u32 TWO			= 0x03;
	const u32 THREE			= 0x04;
	const u32 FOUR			= 0x05;
	const u32 FIVE			= 0x06;
	const u32 SIX			= 0x07;
	const u32 SEVEN			= 0x08;
	const u32 EIGHT			= 0x09;
	const u32 NINE			= 0x0A;
	const u32 ZERO			= 0x0B;
	const u32 MINUS			= 0x0C;
	const u32 EQUALS		= 0x0D;
	const u32 BACKSPACE		= 0x0E;

	// Keyboard roll 3
	const u32 TAB			= 0x0F;
	const u32 Q				= 0x10;
	const u32 W				= 0x11;
	const u32 E				= 0x12;
	const u32 R				= 0x13;
	const u32 T				= 0x14;
	const u32 Y				= 0x15;
	const u32 U				= 0x16;
	const u32 I				= 0x17;
	const u32 O				= 0x18;
	const u32 P				= 0x19;
	const u32 LBRACKET		= 0x1A;
	const u32 RBRACKET		= 0x1B;
	const u32 BACKSLASH		= 0x2B;

	// Keyboard roll 4
	const u32 A				= 0x1E;
	const u32 S				= 0x1F;
	const u32 D				= 0x20;
	const u32 F				= 0x21;
	const u32 G				= 0x22;
	const u32 H				= 0x23;
	const u32 J				= 0x24;
	const u32 K				= 0x25;
	const u32 L				= 0x26;
	const u32 SEMICOLON		= 0x27;
	const u32 APOSTROPHE	= 0x28;
	const u32 ENTER			= 0x1C;

	// Keyboard roll 5
	const u32 Z				= 0x2C;
	const u32 X				= 0x2D;
	const u32 C				= 0x2E;
	const u32 V				= 0x2F;
	const u32 B				= 0x30;
	const u32 N				= 0x31;
	const u32 M				= 0x32;
	const u32 COMMA			= 0x33;
	const u32 PERIOD		= 0x34;
	const u32 SLASH			= 0x35;

	// Lock keys
	const u32 CAPSLOCK		= 0x3A;
	const u32 NUMLOCK		= 0x45;
	const u32 SCROLLLOCK	= 0x46;

	// Numpad
	const u32 NUMPAD1		= 0x4F;
	const u32 NUMPAD2		= 0x50;
	const u32 NUMPAD3		= 0x51;
	const u32 NUMPAD4		= 0x4B;
	const u32 NUMPAD5		= 0x4C;
	const u32 NUMPAD6		= 0x4D;
	const u32 NUMPAD7		= 0x47;
	const u32 NUMPAD8		= 0x48;
	const u32 NUMPAD9		= 0x49;
	const u32 NUMPAD0		= 0x52;
	const u32 NUM_ADD		= 0x4E;
	const u32 NUM_SUB		= 0x4A;
	const u32 NUM_MUL		= 0x37;
	const u32 NUM_DIV		= 0xB5;
	const u32 NUM_ENTER		= 0x9C;
	const u32 NUM_DECIMAL	= 0x53;

	// Navigation keys
	const u32 INS			= 0xD2;
	const u32 DEL			= 0xD3;
	const u32 HOME			= 0xC7;
	const u32 END			= 0xCF;
	const u32 PGUP			= 0xC9;
	const u32 PGDN			= 0xD1;

	// Support keys
	const u32 LSHIFT		= 0x2A;
	const u32 RSHIFT		= 0x36;
	const u32 LCONTROL		= 0x1D;
	const u32 RCONTROL		= 0x9D;
	const u32 LALT			= 0x38;
	const u32 RALT			= 0xB8;
	const u32 LWIN			= 0xDB;
	const u32 RWIN			= 0xDC;
	const u32 SPACE			= 0x39;

	// Arrow keys
	const u32 UP			= 0xC8;
	const u32 DOWN			= 0xD0;
	const u32 LEFT			= 0xCB;
	const u32 RIGHT			= 0xCD;
}

//----------------------------------------------------------------------------------------------------

namespace Mouse
{
	const u32 LBUTTON		= 0;
	const u32 RBUTTON		= 1;
	const u32 MBUTTON		= 2;
}

//----------------------------------------------------------------------------------------------------

namespace GamePad
{
	const u32 BUTTON1		= 0;
	const u32 BUTTON2		= 1;
	const u32 BUTTON3		= 2;
	const u32 BUTTON4		= 3;
	const u32 BUTTON5		= 4;
	const u32 BUTTON6		= 5;
	const u32 BUTTON7		= 6;
	const u32 BUTTON8		= 7;
	const u32 BUTTON9		= 8;
	const u32 BUTTON10		= 9;
}

#endif // #ifndef INCLUDED_ENGINE_INPUTTYPES_H