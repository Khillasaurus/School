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

//Not being used, but being kept for reference sake
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

//Not being used, but being kept for reference sake
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

//-----------------------------------------------------------------------------

//This DrawLine functions utilyzes ___ algorithm
void CRasterizer::DrawTriangle(const CVertex2& v0, const CVertex2& v1, const CVertex2& v2)
{
	//TOIMPROVE: Add a likely compiler hint so that the branch guess directs to the last else at first.
	//Determine if the vertices form a dot, line or triangle

	//if v0 == v1
	if
	(
		v0.point.x == v1.point.x &&
		v0.point.y == v1.point.y
	)
	{
		//if v0 == v2
		if
		(
			v0.point.x == v2.point.x &&
			v0.point.y == v2.point.y
		)
		//all vertices are the same and therefore form a dot
		{
			DrawPoint(v0.point.x, v0.point.y, v0.color.r, v0.color.g, v0.color.b);
			return;
		}
		//else v0 == v1 != v2, therefore the vertices form a line
		else
		{
			DrawLine(v0, v2);
			return;
		}
	}
	//else if v0 == v2
	else if
	(
		v0.point.x == v2.point.x &&
		v0.point.y == v2.point.y
	)
	//v0 == v2 != v1, therefore the vertices form a line
	{
		DrawLine(v0, v1);
		return;
	}
	//else if v1 == v2
	else if
	(
		v1.point.x == v2.point.x &&
		v1.point.y == v2.point.y
	)
	//v0 != v1 == v2, therefore the vertices form a line
	{
		DrawLine(v0, v1);
		return;
	}
	//else all 3 vertices are unique
	else
	{
		//TODO: Degenerate triangle checks
		//area(A, B, C) = 0.5 * ((B - A).cross(C - A)).length();
		//degenerate(A, B, C, minarea) = ((B - A).cross(C - A)).lengthSquared() < (4.0f * minarea * minarea);

		//Process for different fill modes
		switch(CStateManager::GetInstance()->GetFillMode())
		{
			case FillMode::kFillModeLine:
			{
				//Treat triangle as 3 line draws
				DrawLine(v0, v1);
				DrawLine(v0, v2);
				DrawLine(v1, v2);
				return;
			}
			case FillMode::kFillModeFill:
			{
				//Order vertices from top to bottom
				CVertex2 yOrder[3] = { v0, v1, v2 };
				CVertex2 temp;
				if(yOrder[1].point.y < yOrder[0].point.y)
				{
					temp = yOrder[0];
					yOrder[0] = yOrder[1];
					yOrder[1] = temp;
				}
				if(yOrder[2].point.y < yOrder[1].point.y)
				{
					temp = yOrder[1];
					yOrder[1] = yOrder[2];
					yOrder[2] = temp;
				}
				if(yOrder[1].point.y < yOrder[0].point.y)
				{
					temp = yOrder[0];
					yOrder[0] = yOrder[1];
					yOrder[1] = temp;
				}

				//If there is no flat line along y
				if(v0.point.y != v1.point.y && v0.point.y != v2.point.y && v1.point.y != v2.point.y)
				{
					//Find vertex to split triangle into two
					float t = (yOrder[1].point.y - yOrder[0].point.y) / (yOrder[2].point.y - yOrder[0].point.y);
					CVertex2 splitVertex = Vertex2Lerp(yOrder[0], yOrder[2], t);

					//Draw the split triangle as two smaller individual triangles
					DrawTriangle(yOrder[0], splitVertex, yOrder[1]);
					DrawTriangle(yOrder[1], splitVertex, yOrder[2]);
				}
				else
				{
					//Triangle y limits
					int yTop;
					int yBot;
					yTop = static_cast<int>(yOrder[0].point.y);
					yBot = static_cast<int>(yOrder[2].point.y);

					//Scan Line Related
					int yLines = yBot - yTop + 1;
					CVertex2* leftVertices = new CVertex2[yLines];
					CVertex2* rightVertices = new CVertex2[yLines];

					/*
					Determine which two points from the horizontal line and set
					will be either 1st and 2nd or 2nd and 3rd from the already sorted points list.
					topleft, topright, bottomleft, bottomright
					*/
					if(yOrder[0].point.y == yOrder[1].point.y)
					{
						if(yOrder[0].point.x < yOrder[1].point.x)
						{
							leftVertices[0] = yOrder[0];
							rightVertices[0] = yOrder[1];
						}
						else
						{
							leftVertices[0] = yOrder[1];
							rightVertices[0] = yOrder[0];
						}
						leftVertices[yLines - 1] = yOrder[2];
						rightVertices[yLines - 1] = yOrder[2];
					}
					else
					{
						if(yOrder[1].point.x < yOrder[2].point.x)
						{
							leftVertices[yLines - 1] = yOrder[1];
							rightVertices[yLines - 1] = yOrder[2];
						}
						else
						{
							leftVertices[yLines - 1] = yOrder[2];
							rightVertices[yLines - 1] = yOrder[1];
						}
						leftVertices[0] = yOrder[0];
						rightVertices[0] = yOrder[0];
					}

					//Fill vertex arrays with y vertices
					GetTriYVertices(leftVertices, yLines);
					GetTriYVertices(rightVertices, yLines);

					//init
					int xSteps = 0;
					float rStepX = 0.0f;
					float gStepX = 0.0f;
					float bStepX = 0.0f;
					CColor midColor;

					//iterate through the scan lines
					for(int i = 0; i < yLines; ++i)
					{
						//get color increments
						xSteps = static_cast<int>(rightVertices[i].point.x - leftVertices[i].point.x + 0.5f);
						if(xSteps > 0)
						{
							rStepX = (rightVertices[i].color.r - leftVertices[i].color.r) / xSteps;
							gStepX = (rightVertices[i].color.g - leftVertices[i].color.g) / xSteps;
							bStepX = (rightVertices[i].color.b - leftVertices[i].color.b) / xSteps;
						}

						//iterate through x pixels and draw with interpolated color
						midColor = leftVertices[i].color;
						//account for proper rounding casting floats to ints
						for
						(
							int x = static_cast<int>(leftVertices[i].point.x + 0.5f);
							x <= static_cast<int>(rightVertices[i].point.x + 0.5f);
							++x
						)
						{
							if(leftVertices[i].point.x == rightVertices[i].point.x)
							{
								break;
							}
							//draw the pixel
							SetColor(midColor);
							DrawPoint(static_cast<float>(x), leftVertices[i].point.y);

							//increment the scan line's color interpolation
							midColor.r += rStepX;
							midColor.g += gStepX;
							midColor.b += bStepX;
						}
					}

					//Clean up memory
					delete[] leftVertices;
					delete[] rightVertices;
				}
			}
			break;
			default:
				break;
		}
	}
}

//-----------------------------------------------------------------------------

//todo: change this function to take in a memoryleak safe pointer instead of passing an array by reference, or simply pass in a better type such as an STL vector
void CRasterizer::GetTriYVertices(CVertex2 vBuffer[], const int kBufferSize)
{
	//To simplify equations
	CVertex2* pVFirst = &vBuffer[0];
	CVertex2* pVLast = &vBuffer[kBufferSize - 1];
	CColor colorCur = pVFirst->color;

	int x1 = static_cast<int>(pVFirst->point.x +0.5f);
	int y1 = static_cast<int>(pVFirst->point.y +0.5f);
	int x2 = static_cast<int>(pVLast->point.x +0.5f);
	int y2 = static_cast<int>(pVLast->point.y +0.5f);

	int dx = x2 - x1;
	int dy = y2 - y1;

	//Protect against division by zero later on
	//TODO: Change this to proper error checking instead of simply retuning with no work done
	if(dx == 0 && dy == 0)
	{
		return;
	}

	float dr = pVLast->color.r - pVFirst->color.r;
	float dg = pVLast->color.g - pVFirst->color.g;
	float db = pVLast->color.b - pVFirst->color.b;
	int xStep = 0;
	int yStep = 0;
	float rStep = 0;
	float gStep = 0;
	float bStep = 0;

	//Check for negative d values
	if(dx < 0)
	{
		dx = -dx;
		xStep = -1;
	}
	else
	{
		xStep = 1;
	}
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
	int greater = 0;
	if(dx > dy)
	{
		greater = dx;
	}
	else
	{
		greater = dy;
	}
	rStep = dr / greater;
	gStep = dg / greater;
	bStep = db / greater;

	dx <<= 1;//dx is now 2*dx
	dy <<= 1;//dy is now 2*dy

	int indexCur = 0;
	int yCur = y1;
	if(dx > dy)
	{
		int fraction = dy - (dx >> 1);////same as 2*dy - dx
		while(x1 != x2)
		{
			if(fraction >= 0)
			{
				y1 += yStep;
				fraction -= dx;//same as fraction -= 2*dx
			}
			x1 += xStep;
			fraction += dy;//same as fraction += 2*dy
			colorCur.r += rStep;
			colorCur.g += gStep;
			colorCur.b += bStep;
			if(y1 != yCur)
			{
				yCur = y1;
				if(kBufferSize == ++indexCur)
				{
					break;
				}
				vBuffer[indexCur].point.x = x1;
				vBuffer[indexCur].point.y = y1;
				vBuffer[indexCur].color = colorCur;
			}
		}
	}
	else
	{
		int fraction = dx - (dy >> 1);
		while(y1 != y2)
		{
			if(fraction >= 0)
			{
				x1 += xStep;
				fraction -= dy;
			}
			y1 += yStep;
			fraction += dx;
			colorCur.r += rStep;
			colorCur.g += gStep;
			colorCur.b += bStep;
			if(y1 != yCur)
			{
				yCur = y1;
				if(kBufferSize == ++indexCur)
				{
					break;
				}
				vBuffer[indexCur].point.x = x1;
				vBuffer[indexCur].point.y = y1;
				vBuffer[indexCur].color = colorCur;
			}
		}
	}
}