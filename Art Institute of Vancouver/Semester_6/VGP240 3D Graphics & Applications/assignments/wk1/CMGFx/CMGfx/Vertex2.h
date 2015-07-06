#ifndef __VERTEX2_H__
#define __VERTEX2_H__

#include "Color.h"
#include "Vector2.h"

struct CVertex2
{
	CColor color;
	CVector2 point;
};

inline void Vertex2Round( CVertex2 &v )
{
	v.point.x = (float)(int)(v.point.x + 0.5f);
	v.point.y = (float)(int)(v.point.y + 0.5f);
}

inline CVertex2 Vertex2Lerp( const CVertex2 &v1, const CVertex2 &v2, const float t )
{
	CVertex2 result;
	result.point.x = v1.point.x + t * (v2.point.x - v1.point.x);
	result.point.y = v1.point.y + t * (v2.point.y - v1.point.y);
	result.color.r = v1.color.r + t * (v2.color.r - v1.color.r);
	result.color.g = v1.color.g + t * (v2.color.g - v1.color.g);
	result.color.b = v1.color.b + t * (v2.color.b - v1.color.b);
	return result;
}

#endif // __VERTEX_H__