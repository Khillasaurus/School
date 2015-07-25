#ifndef INCLUDED_ENGINE_SIMPLEDRAW_H
#define INCLUDED_ENGINE_SIMPLEDRAW_H

//====================================================================================================
// Filename:	SimpleDraw.h
// Created by:	Peter Chan
// Description:	Header containing some useful rendering functions.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

namespace Math
{
	struct Vector2;
	struct Vector3;
}

struct Color;
class Camera;
class GraphicsSystem;

//====================================================================================================
// Function Declarations
//====================================================================================================

namespace SimpleDraw
{

// Functions to startup/shutdown simple draw
void Initialize(GraphicsSystem& gs, u32 maxVertices = 10000);
void Terminate();

// Functions for world space rendering
void AddLine(const Math::Vector3& v0, const Math::Vector3& v1, const Color& color);
void AddLine(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, const Color& color);
void AddAABB(const Math::Vector3& min, const Math::Vector3& max, const Color& color);
void AddAABB(const Math::Vector3& center, f32 extend, const Color& color);
void AddAABB(f32 minX, f32 minY, f32 minZ, f32 maxX, f32 maxY, f32 maxZ, const Color& color);
void AddSphere(const Math::Vector3& center, f32 radius, const Color& color, u32 slices = 8, u32 rings = 4);

// Functions for screen space rendering
void AddScreenLine(const Math::Vector2& v0, const Math::Vector2& v1, const Color& color);
void AddScreenLine(f32 x0, f32 y0, f32 x1, f32 y1, const Color& color);
void AddScreenRect(const Math::Vector2& min, const Math::Vector2& max, const Color& color);
void AddScreenRect(f32 x, f32 y, f32 w, f32 h, const Color& color);
void AddScreenCircle(const Math::Vector2& center, f32 r, const Color& color);
void AddScreenCircle(f32 x, f32 y, f32 r, const Color& color);

// Function to actually render all the geometry.
void Render(const Camera& camera);

} // namespace SimpleDraw

#endif // #ifndef INCLUDED_ENGINE_SIMPLEDRAW_H