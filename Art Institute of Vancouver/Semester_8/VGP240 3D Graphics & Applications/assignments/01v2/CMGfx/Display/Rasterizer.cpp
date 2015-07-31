//=============================================================================
//Dependencies
//=============================================================================

#include "stdafx.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "../Common/MiniMath.h"
#include "Rasterizer.h"
#include "StateManager.h"
#include "../Common/Color.h"
#include "../Common/Vertex2.h"

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

void CRasterizer::SetColor(const CColor& color)
{
	//set OpenGL color
	glColor3f(color.r, color.g, color.b);
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

//-----------------------------------------------------------------------------

//This DrawLine functions utilyzes Bresenham's algorithm
void CRasterizer::DrawLine(const CVertex2& v0, const CVertex2& v1)
{
	//TOIMPROVE: Add a likely compiler hint so that the branch guess directs to the else at first.
	//Check if the two vertices share the same coordinates
	if(v0.point.x == v1.point.x && v0.point.y == v1.point.y)
	{
		DrawPoint(v0.point.x, v0.point.y, v0.color.r, v0.color.g, v0.color.b);
		return;
	}
	else
	{
		//Process for different fill modes
		switch(CStateManager::GetInstance()->GetFillMode())
		{
			case FillMode::kFillModeLine:
			case FillMode::kFillModeFill:
			{
				//Simplify equations
				CColor colorCur = v0.color;
				int x0 = roundftoi(v0.point.x);
				int y0 = roundftoi(v0.point.y);
				int x1 = roundftoi(v1.point.x);
				int y1 = roundftoi(v1.point.y);

				int dx = (x1 - x0);
				int dy = (y1 - y0);

				//Protect against division by zero later on
				//TODO: Instead of simply returning, throw an error using assert
				if(dx == 0 && dy == 0)
				{
					return;
				}
				else
				{
					float dr = v1.color.r - v0.color.r;
					float dg = v1.color.g - v0.color.g;
					float db = v1.color.b - v0.color.b;
					int xStep = 0;
					int yStep = 0;
					float rStep = 0;
					float gStep = 0;
					float bStep = 0;

					//Check for negative d values
					// dx
					if(dx < 0)
					{
						dx = -dx;
						xStep = -1;
					}
					else
					{
						xStep = 1;
					}
					// dy
					if(dy < 0)
					{
						dy = -dy;
						yStep = -1;
					}
					else
					{
						yStep = 1;
					}

					//Calculate the step values for rgb
					if(dx > dy)
					{
						rStep = dr / dx;
						gStep = dg / dx;
						bStep = db / dx;
					}
					else
					{
						rStep = dr / dy;
						gStep = dg / dy;
						bStep = db / dy;
					}

					dy <<= 1; //dy is now 2* dy
					dx <<= 1; //dx is now 2* dx

					DrawPoint((float)x0, (float)y0, colorCur.r, colorCur.g, colorCur.b);
					if(dx > dy)
					{
						int fraction = dy - (dx >> 1);//same as 2*dy - dx;
						while(x0 != - x1)
						{
							if(fraction >= 0)
							{
								y0 += yStep;
								fraction -= dx;//same as fraction -=2*dx
							}
							x0 += xStep;
							fraction += dy;//same as fraction += 2*dy
							colorCur.r += rStep;
							colorCur.g += gStep;
							colorCur.b += bStep;
							DrawPoint((float)x0, (float)y0, colorCur.r, colorCur.g, colorCur.b);
						}
					}
					else
					{
						int fraction = dx - (dy >> 1);
						while(y0 != y1)
						{
							if(fraction >= 0)
							{
								x0 += xStep;
								fraction -= dy;
							}
							y0 += yStep;
							fraction += dx;
							colorCur.r += rStep;
							colorCur.g += gStep;
							colorCur.b += bStep;
							DrawPoint((float)x0, (float)y0, colorCur.r, colorCur.g, colorCur.b);
						}
					}
				}
			}
				break;
			default:
				break;
		}
	}
}