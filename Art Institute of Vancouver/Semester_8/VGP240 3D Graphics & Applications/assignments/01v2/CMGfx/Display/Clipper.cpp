//=============================================================================
//Dependencies
//=============================================================================

//Precompiled Headers
#include "stdafx.h"

//General
#include "gl/gl.h"
#include "../Common/Common.h"
#include "../Common/MiniMath.h"
#include "Rasterizer.h"
#include "Clipper.h"

using std::vector;

//=============================================================================
//Statics
//=============================================================================

CClipper* CClipper::pInstance = nullptr;

//=============================================================================
//Class Definitions
//=============================================================================

//-----------------------------------------------------------------------------
//Constructor
//-----------------------------------------------------------------------------

CClipper::CClipper()
:	mViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)
,	mShowViewport(false)
{
}

//-----------------------------------------------------------------------------
// Copy Constructor
//-----------------------------------------------------------------------------

CClipper::CClipper(const CClipper&)
{
}

//-----------------------------------------------------------------------------
//Destructor
//-----------------------------------------------------------------------------

CClipper::~CClipper()
{
}

//-----------------------------------------------------------------------------
//Accessors
//-----------------------------------------------------------------------------

CClipper* CClipper::GetInstance()
{
	if(pInstance == nullptr)
	{
		pInstance == new CClipper();
	}
	return pInstance;
}

//-----------------------------------------------------------------------------
//Manipulators
//-----------------------------------------------------------------------------

void CClipper::SetViewport(int l, int t, int r, int b)
{
	mViewport.SetRect
	(
		(l < 0) ? 0 : l,
		(t < 0) ? 0 : t,
		(r > WINDOW_WIDTH) ? WINDOW_WIDTH : r,
		(b > WINDOW_HEIGHT) ? WINDOW_HEIGHT : b
	);
}

//-----------------------------------------------------------------------------
//Clipping Functions
//-----------------------------------------------------------------------------
	
void CClipper::DrawViewport()
{
	if(mShowViewport == true)
	{
		CRasterizer::Instance()->SetColor(1.0f, 1.0f, 1.0f);
		glBegin( GL_LINE_STRIP );
		glVertex2i(mViewport.left, mViewport.top - 1);
		glVertex2i(mViewport.left, mViewport.bottom);
		glVertex2i(mViewport.right + 1, mViewport.bottom);
		glVertex2i(mViewport.right + 1, mViewport.top - 1);
		glVertex2i(mViewport.left, mViewport.top - 1);
		glEnd();
	}
}

//-----------------------------------------------------------------------------

void CClipper::ResetViewport()
{
	mViewport.SetRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}

//-----------------------------------------------------------------------------

bool CClipper::ClipPoint(int x, int y)
{
	return
	(
		x > mViewport.left &&
		x < mViewport.right &&
		y > mViewport.top &&
		y < mViewport.bottom
	);
}

//-----------------------------------------------------------------------------

bool CClipper::ClipLine(CVertex2& v0, CVertex2& v1)
{
	// using Cohen-Sutherland line clipping
	// http://www.cs.helsinki.fi/group/goa/viewing/leikkaus/lineClip.html
	/* ***OUT CODES***
                1001  |  1000  |  1010      LEFT   = 1st bit
            ----------------------------    RIGHT  = 2nd bit
                0001  |  0000  |  0010      BOTTOM = 3rd bit
            ----------------------------    TOP    = 4th bit
                0101  |  0100  |  0110
	*/

	//Simplify viewport dimensions
	long &vpL = mViewport.left, &vpR = mViewport.right, &vpT = mViewport.top, &vpB = mViewport.bottom;

	//assign outcodes to each vertex
	const unsigned char OC_LEFT   = 1 << 0;
	const unsigned char OC_RIGHT  = 1 << 1;
	const unsigned char OC_BOTTOM = 1 << 2;
	const unsigned char OC_TOP    = 1 << 3;

	unsigned char code1 = 0, code2 = 0;
	{
		// left and right
		if      ( v0.point.x < vpL ) code1 |= OC_LEFT;
		else if ( v0.point.x > vpR ) code1 |= OC_RIGHT;
		if      ( v1.point.x < vpL ) code2 |= OC_LEFT;
		else if ( v1.point.x > vpR ) code2 |= OC_RIGHT;
		// bottom and top
		if      ( v0.point.y > vpB ) code1 |= OC_BOTTOM;
		else if ( v0.point.y < vpT ) code1 |= OC_TOP;
		if      ( v1.point.y > vpB ) code2 |= OC_BOTTOM;
		else if ( v1.point.y < vpT ) code2 |= OC_TOP;
	}

	// if bitwise OR yields 0000, trivially accept
	if((code1 | code2) == 0)
	{
		return true;
	}

	// if bitwise AND DOES NOT yield 0000, trivially reject
	if((code1 & code2) != 0)
	{
		return false;
	}


	//handle each bit of the outcode to clip endpoints to viewport
	//vars for LERP
	int dx, dy;
	float t;

	//handle vertex 1
	if(code1 & OC_LEFT)
	{
		dx = roundftoi(v1.point.x - v0.point.x);
		t = (mViewport.left - v0.point.x) / static_cast<float>(dx);
		v0 = Vertex2Lerp(v0, v1, t);
	}
	else if(code1 & OC_RIGHT)
	{
		dx = roundftoi(v1.point.x - v0.point.x);
		t = (mViewport.right - v0.point.x ) / static_cast<float>(dx);
		v0 = Vertex2Lerp(v0, v1, t);
	}
	else if(code1 & OC_BOTTOM)
	{
		dy = roundftoi(v1.point.y - v0.point.y);
		t = (mViewport.bottom - v0.point.y) / static_cast<float>(dy);
		v0 = Vertex2Lerp(v0, v1, t);
	}
	else if(code1 & OC_TOP)
	{
		dy = roundftoi(v1.point.y - v0.point.y);
		t = (mViewport.top - v0.point.y) / static_cast<float>(dy);
		v0 = Vertex2Lerp(v0, v1, t);
	}

	//Handle vertex 2
	if(code2 & OC_LEFT)
	{
		dx = roundftoi(v0.point.x - v1.point.x);
		t = (mViewport.left - v1.point.x ) / static_cast<float>(dx);
		v1 = Vertex2Lerp(v0, v1, t);
	}
	else if(code2 & OC_RIGHT)
	{
		dx = roundftoi(v0.point.x - v1.point.x);
		t = (mViewport.right - v1.point.x) / static_cast<float>(dx);
		v1 = Vertex2Lerp(v1, v0, t);
	}
	else if(code2 & OC_BOTTOM)
	{
		dy = roundftoi(v0.point.y - v1.point.y);
		t = (mViewport.bottom - v1.point.y ) / static_cast<float>(dy);
		v1 = Vertex2Lerp(v1, v0, t);
	}
	else if(code2 & OC_TOP)
	{
		dy = roundftoi(v0.point.y - v1.point.y);
		t = (mViewport.top - v1.point.y) / static_cast<float>(dy);
		v1 = Vertex2Lerp(v1, v0, t);
	}

	//Recursive call 
	return ClipLine(v0, v1);
}

//-----------------------------------------------------------------------------

void CClipper::ClipTriangle(std::vector< CVertex2 >& vBuffer, std::vector< CVertex2 >& newVertices, ClipPlane planeFlag)
{
	//using Sutherland-Hodgman clipping
	//http://en.wikipedia.org/wiki/Sutherland-Hodgeman

	unsigned int uiBufSize = vBuffer.size();
	CVertex2 v2 = vBuffer[uiBufSize - 1];

	//iterate through vertices to clip along chosen clip plane
	for(unsigned int i = 0; i < uiBufSize; ++i)
	{
		CVertex2 v1 = vBuffer[i];
		if(true == IsInClipBounds( planeFlag, v1 ))
		{
			if(IsInClipBounds(planeFlag, v2) == false)
			{
				newVertices.push_back(IntersectWithPlane(v2, v1, planeFlag));
			}
			newVertices.push_back(v1);
		}
		else if(IsInClipBounds(planeFlag, v2) == true)
		{
			newVertices.push_back(IntersectWithPlane(v1, v2, planeFlag));
		}

		v2 = v1;
	}
}

//-----------------------------------------------------------------------------
//Private Helper Functions
//-----------------------------------------------------------------------------

bool CClipper::IsInClipBounds(ClipPlane clipPlane, const CVertex2& v)
{
	switch(clipPlane)
	{
		case CP_LEFT:
		{
			return(v.point.x > mViewport.left);
		}
		break;

		case CP_BOTTOM:
		{
			return(v.point.y < mViewport.bottom);
		}
		break;
		
		case CP_RIGHT:
		{
			return(v.point.x < mViewport.right);
		}
		break;
		
		case CP_TOP:
		{
			return(v.point.y > mViewport.top);
		}
		break;
		
		default:
		break;
	}
	return false;
}

//-----------------------------------------------------------------------------

CVertex2 CClipper::IntersectWithPlane(const CVertex2& v0, const CVertex2& v1, ClipPlane planeFlag)
{
	float t = 0.0f;
	switch(planeFlag)
		{
		case CP_LEFT:
		{
			float dx = v1.point.x - v0.point.x;
			if(0 != dx)
			{
				t = (mViewport.left - v0.point.x) / dx;
			}
		}
		break;

		case CP_RIGHT:
		{
			float dx = v1.point.x - v0.point.x;
			if(0 != dx)
			{
				t = (mViewport.right - v0.point.x) / dx;
			}
		}
		break;

		case CP_BOTTOM:
		{
			float dy = v1.point.y - v0.point.y;
			if(0 != dy)
			{
				t = (mViewport.bottom - v0.point.y) / dy;
			}
		}
		break;

		case CP_TOP:
		{
			float dy = v1.point.y - v0.point.y;
			if(0 != dy)
			{
				t = (mViewport.top - v0.point.y) / dy;
			}
		}
		break;

		default:
		break;
	}
	
	return Vertex2Lerp(v0, v1, t);
}