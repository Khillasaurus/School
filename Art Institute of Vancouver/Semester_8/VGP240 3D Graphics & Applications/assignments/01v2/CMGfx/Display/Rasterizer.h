#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

//=============================================================================
//Forward Declarations
//=============================================================================

class CColor;
class CVertex2;

//=============================================================================
//Dependencies
//=============================================================================

#include <vector>

//=============================================================================
//Class Declarations
//=============================================================================

class CRasterizer
{
public:
	//Class Singleton
	static CRasterizer* Instance();
protected:
	//Singleton Duplication Prevention
	//TOIMPROVE: These do not prevent duplication in ALL cases, but the vast majority of them, all of which should fall under the scope of this project. Exeption example: Multithreading may allow for more than one of this class to be constructed.
	CRasterizer() {}
	CRasterizer(const CRasterizer&);
	CRasterizer& operator= (const CRasterizer&);
private:
	//Class Singleton Pointer
	static CRasterizer* pinstance;

public:
	//QUESTION: What does this do? I could not find an implementation anywhere.
	void Initialize() {}

	void SetColor		(const float r,  const float g, const float b);
	void SetColor		(const CColor& color);
	void DrawPoint		(const int	 x,  const int   y);
	void DrawPoint		(const float x,  const float y);
	void DrawPoint		(const float x,  const float y,  const float r,  const float g, const float b);
	void DrawLine		(const float x1, const float y1, const float x2, const float y2);
	void DrawLine		(const CVertex2& v0, const CVertex2& v1);
	void DrawTriangle	(const CVertex2& v0, const CVertex2& v1, const CVertex2& v2);

private:
	//Helper Functions
	void GetTriYVertices(CVertex2 vBuffer[], int iBufferSize);
};

#endif //#ifndef __RASTERIZER_H__