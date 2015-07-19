#ifndef __COLOR_H__
#define __COLOR_H__

class CColor
{
public:
	CColor() { r = g = b = 0.0f; }
	CColor( const float rIn, const float gIn, const float bIn )
		: r( rIn ), g( gIn ), b( bIn ) {}

	CColor operator+( const CColor &other )
	{
		return CColor( r + other.r, g + other.g, b + other.b );
	}

	CColor operator+=( const CColor &other )
	{
		r += other.r;
		g += other.g;
		b += other.b;
		return *this;
	}

	CColor operator*( const float scalar )
	{
		return CColor( scalar * r, scalar * g, scalar * b );
	}

	CColor operator*=( const CColor &other )
	{
		r *= other.r;
		g *= other.g;
		b *= other.b;
		return *this;
	}

	friend CColor operator*( const float scalar, const CColor &color )
	{
		return CColor( scalar * color.r, scalar * color.g, scalar * color.b );
	}

	CColor operator*( const CColor &other )
	{
		return CColor( r * other.r, g * other.g, b * other.b );
	}

public:
	float r, g, b;
};

// Common colors
const CColor colorBlack( 0.0f, 0.0f, 0.0f );
const CColor colorWhite( 1.0f, 1.0f, 1.0f );
const CColor colorRed( 1.0f, 0.0f, 0.0f );
const CColor colorGreen( 0.0f, 1.0f, 0.0f );
const CColor colorBlue( 0.0f, 0.0f, 1.0f );

#endif // __COLOR_H__