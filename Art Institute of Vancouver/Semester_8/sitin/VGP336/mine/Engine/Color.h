#ifndef INCLUDED_ENGINE_COLOR_H
#define INCLUDED_ENGINE_COLOR_H

//====================================================================================================
// Filename:	Color.h
// Created bg:	Peter chan
// Description:	Struct for a color.
//====================================================================================================

//====================================================================================================
// Structs
//====================================================================================================

struct Color
{
	f32 r, g, b, a;

	Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f) {}
	Color(f32 r, f32 g, f32 b, f32 a) : r(r), g(g), b(b), a(a) {}
	
	static Color Red();
	static Color Green();
	static Color Blue();
	static Color Yellow();
	static Color Cyan();
	static Color Magenta();
	static Color Black();
	static Color White();
};


//====================================================================================================
// Inline Definitions
//====================================================================================================

inline Color Color::Red()		{ return Color(1.0f, 0.0f, 0.0f, 1.0f); }
inline Color Color::Green()		{ return Color(0.0f, 1.0f, 0.0f, 1.0f); }
inline Color Color::Blue()		{ return Color(0.0f, 0.0f, 1.0f, 1.0f); }
inline Color Color::Yellow()	{ return Color(1.0f, 1.0f, 0.0f, 1.0f); }
inline Color Color::Cyan()		{ return Color(0.0f, 1.0f, 1.0f, 1.0f); }
inline Color Color::Magenta()	{ return Color(1.0f, 0.0f, 1.0f, 1.0f); }
inline Color Color::Black()		{ return Color(0.0f, 0.0f, 0.0f, 1.0f); }
inline Color Color::White()		{ return Color(1.0f, 1.0f, 1.0f, 1.0f); }

#endif // #ifndef INCLUDED_ENGINE_COLOR_H