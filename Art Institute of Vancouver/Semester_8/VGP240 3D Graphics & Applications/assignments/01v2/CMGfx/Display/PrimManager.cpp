//=============================================================================
//Dependencies
//=============================================================================

//Precompiled Headers
#include "stdafx.h"

//General
#include "PrimManager.h"
#include "StateManager.h"
#include "Rasterizer.h"
#include "Clipper.h"

//=============================================================================
//Statics
//=============================================================================

CPrimManager* CPrimManager::pInstance = nullptr;

//=============================================================================
//Class Definitions
//=============================================================================

//-----------------------------------------------------------------------------
//Vertex Functions
//-----------------------------------------------------------------------------

void CPrimManager::BeginDraw(Primitive type)
{
	//If we aren't already drawing something
	if(mDrawBegin == false)
	{
		//Set the type of primitive we would like to draw
		mPrimitive = type;
		//Clear the vertex buffer in order to hold new data
		mVertexBuffer.clear();
		//Set the drawing state flag to true
		mDrawBegin = true;
	}
}

//-----------------------------------------------------------------------------

void CPrimManager::AddVertex(const CVertex2& vertex)
{
	//TODO: Change this to an assert check, in order to throw an error when attempting to add vertices when not currently in a drawing mode, instead of simply ignoring the command.
	if(mDrawBegin == true)
	{
		mVertexBuffer.push_back(vertex);
	}
}

//-----------------------------------------------------------------------------

void CPrimManager::EndDraw()
{
	const unsigned int kNumVertices = mVertexBuffer.size();

	//Check to see if fill mode is type point. If so, treat all primitives as points, since drawing a point requires no filling.
	Primitive primitiveDesired = mPrimitive;
	if(CStateManager::GetInstance()->GetFillMode() == FillMode::kFillModePoint)
	{
		primitiveDesired = Primitive::kPrimitivePoint;
	}

	//Rasterize based on primitive type
	switch(primitiveDesired)
	{
		case Primitive::kPrimitivePoint:
		{
			//Draw all points
			for(unsigned int i = 0; i < kNumVertices; ++i)
			{
				CVertex2& v = mVertexBuffer.at(i);

				//if within viewport, clip
				if(CClipper::GetInstance()->ClipPoint(static_cast<int>(v.point.x + 0.5f), static_cast<int>(v.point.y + 0.5f)))
				{
					CRasterizer::Instance()->DrawPoint(v.point.x, v.point.y, v.color.r, v.color.g, v.color.b);
				}
			}
		}
		break;

		case Primitive::kPrimitiveLine:
		{
			//Check if there are enough points to form a line
			if(kNumVertices < 2)
			{
				//TODO: Throw error instead of simply ignoring raster script request
				break;
			}
			else
			{
				//Draw all lines
				//TOIMPROVE:	Make this more efficient. There is too much jumping around when querying the vertex buffer, so I feel like this could be made more efficiently.
				//				Possible solution: Use a pointer to the vertex buffer, and instead of using the at() function, simply iterate the pointer forward.
				for(unsigned i = 1; i < kNumVertices; i += 2)
				{
					CVertex2& v0 = mVertexBuffer.at(i - 1);
					CVertex2& v1 = mVertexBuffer.at(i);

					//Clip to viewport
					if(CClipper::GetInstance()->ClipLine(v0, v1))
					{
						CRasterizer::Instance()->DrawLine(v0, v1);
					}
				}
			}
		}

		case Primitive::kPrimitiveTriangle:
		{
			//Check if there are enough points to form a triangle
			if(kNumVertices < 3)
			{
				//TODO: Throw error instead of simply ignoring raster script request
				break;
			}
			else
			{
				//Draw all triangles
				//TOIMPROVE:	Make this more efficient. There is too much jumping around when querying the vertex buffer, so I feel like this could be made more efficiently.
				//				Possible solution: Use a pointer to the vertex buffer, and instead of using the at() function, simply iterate the pointer forward.
				for(unsigned i = 2; i < kNumVertices; i += 3)
				{
					CVertex2& v0 = mVertexBuffer.at(i - 2);
					CVertex2& v1 = mVertexBuffer.at(i - 1);
					CVertex2& v2 = mVertexBuffer.at(i);

					//Check for all same y coord
					if
					(
						v0.point.y == v1.point.y &&
						v0.point.y == v2.point.y
					)
					{
						continue;
					}

					//Clip only if in fill mode, will be deferred to other drawing modes otherwise
					if(CStateManager::GetInstance()->GetFillMode() == FillMode::kFillModeFill)
					{
						CRasterizer::Instance()->DrawTriangle(v0, v1, v2);
					}
					else
					{
						//perform clipping, may return a new poly with more than 3 vertices
						std::vector<CVertex2> vBuffer;
						std::vector<CVertex2> newVerts;
						vBuffer.push_back(v0);
						vBuffer.push_back(v1);
						vBuffer.push_back(v2);

						CClipper::GetInstance()->ClipTriangle(vBuffer, newVerts, CP_LEFT);

						if(0 == newVerts.size())
						{
							continue;
						}
						vBuffer.clear();
						
						CClipper::GetInstance()->ClipTriangle(newVerts, vBuffer, CP_BOTTOM);
						if(0 == vBuffer.size())
						{
							continue;
						}
						newVerts.clear();

						CClipper::GetInstance()->ClipTriangle(vBuffer, newVerts, CP_RIGHT);
						if(0 == newVerts.size())
						{
							continue;
						}
						vBuffer.clear();

						CClipper::GetInstance()->ClipTriangle(newVerts, vBuffer, CP_TOP);
						if(0 == vBuffer.size())
						{
							continue;
						}

						//split new poly into triangles and draw
						for(unsigned int i = 2; i < vBuffer.size(); ++i)
						{
							//rasterize the triangle given three vertices
							CRasterizer::Instance()->DrawTriangle(vBuffer.at(0), vBuffer.at(i - 1), vBuffer.at(i));
						}
					}
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
//Accessors
//-----------------------------------------------------------------------------

CPrimManager* CPrimManager::GetInstance()
{
	if(pInstance == nullptr)
	{
		pInstance = new CPrimManager();
	}

	return pInstance;
}