//=============================================================================
//Dependencies
//=============================================================================

#include "StdAfx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "MiniMath.h"
#include "Rasterizer.h"

//=============================================================================
//Static Initialization
//=============================================================================

CRasterizer* CRasterizer::pinstance = 0;// initialize pointer

//=============================================================================
//Class Definitions
//=============================================================================

CRasterizer* CRasterizer::Instance()
{
	//if no instance of this class has already been created
	if(pinstance == 0)
	{
		//create sole instance (Singleton)
		pinstance = new CRasterizer;
	}
	return pinstance;
}

//-----------------------------------------------------------------------------

void CRasterizer::SetColor(const float r, const float g, const float b)
{
	//set OpenGL color
	glColor3f(r, g, b);
}

//-----------------------------------------------------------------------------

void CRasterizer::DrawPoint(const int x, const int y)
{
	//Draw OpenGL pixel
	glBegin(GL_POINTS);
		glVertex2i(x, y);
	glEnd();
}

//-----------------------------------------------------------------------------

void CRasterizer::DrawPoint(const float x, const float y)
{
	//Draw OpenGL pixel
	glBegin(GL_POINTS);
		glVertex2i(static_cast<int>(x + 0.5f), static_cast<int>(y + 0.5f));
	glEnd();
}

//-----------------------------------------------------------------------------

void CRasterizer::DrawPoint(const float x, const float y, const float r, const float g, const float b)
{
	SetColor(r, g, b);
	DrawPoint(x, y);
}

//-----------------------------------------------------------------------------

void CRasterizer::DrawLine(const float x1, const float y1, const float x2, const float y2)
{
	glBegin(GL_LINES);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);
	glEnd();
}