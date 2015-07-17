#include "StdAfx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "MiniMath.h"
#include "Rasterizer.h"

CRasterizer* CRasterizer::pinstance = 0;// initialize pointer
CRasterizer* CRasterizer::Instance () 
{
	if (pinstance == 0)  // is it the first call?
	{  
		pinstance = new CRasterizer; // create sole instance
	}
	return pinstance; // address of sole instance
}

void CRasterizer::SetColor( const float r, const float g, const float b )
{
	// Set OpenGL color
	glColor3f( r, g, b );
}

void CRasterizer::DrawPoint( const int x, const int y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( x, y );
	glEnd();
}

void CRasterizer::DrawPoint( const float x, const float y )
{
	// Draw OpenGL pixel
	glBegin( GL_POINTS );
	glVertex2i( (int)(x + 0.5f), (int)(y + 0.5f) );
	glEnd();
}

void CRasterizer::DrawPoint( const float x, const float y, const float r, const float g, const float b )
{
	SetColor( r, g, b );
	DrawPoint( x, y );
}

