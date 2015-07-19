#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include <vector>

class CRasterizer
{
public:
	static CRasterizer* Instance();
protected:
	CRasterizer() {}
	CRasterizer(const CRasterizer&);
	CRasterizer& operator= (const CRasterizer&);
private:
	static CRasterizer* pinstance;

public:
	void Initialize() {}

	void SetColor( const float r, const float g, const float b );
	void DrawPoint( const int x, const int y );
	void DrawPoint( const float x, const float y );
	void DrawPoint( const float x, const float y, const float r, const float g, const float b );
	void DrawLine(const float x1, const float y1, const float x2, const float y2);
};

#endif // __RASTERIZER_H__
