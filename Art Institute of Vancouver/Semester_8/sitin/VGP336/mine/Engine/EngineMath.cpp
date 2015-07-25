//====================================================================================================
// Filename:	EngineMath.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "EngineMath.h"

namespace Math
{

//====================================================================================================
// Constants
//====================================================================================================

const f32 kPi			= 3.14159265358979f;
const f32 kTwoPi		= 6.28318530717958f;
const f32 kPiByTwo		= 1.57079632679489f;
const f32 kRootTwo		= 1.41421356237309f;
const f32 kRootThree	= 1.73205080756887f;
const f32 kDegToRad		= kPi / 180.0f;
const f32 kRadToDeg		= 180.0f / kPi;

//====================================================================================================
// Function Definitions
//====================================================================================================

Quaternion Quaternion::RotationAxis(const Vector3& axis, f32 rad)
{
	const f32 c = cos(rad * 0.5f);
	const f32 s = sin(rad * 0.5f);
	const Math::Vector3 a = Math::Normalize(axis);
	return Quaternion(a.x * s, a.y * s, a.z * s, c);
}

//----------------------------------------------------------------------------------------------------

Matrix Matrix::RotationAxis(const Vector3& axis, f32 rad)
{
	const Vector3 u = Normalize(axis);
	const f32 x = u.x;
	const f32 y = u.y;
	const f32 z = u.z;
	const f32 s = sin(rad);
	const f32 c = cos(rad);

	return Matrix
	(
		c + (x * x * (1.0f - c)),
		x * y * (1.0f - c) + z * s,
		x * z * (1.0f - c) - y * s,
		0.0f,

		x * y * (1.0f - c) - z * s,
		c + (y * y * (1.0f - c)),
		y * z * (1.0f - c) + x * s,
		0.0f,

		x * z * (1.0f - c) + y * s,
		y * z * (1.0f - c) - x * s,
		c + (z * z * (1.0f - c)),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
}

//----------------------------------------------------------------------------------------------------

Matrix Matrix::RotationQuaternion(const Quaternion& q)
{
	return Matrix
	(
		1.0f - (2.0f * q.y * q.y) - (2.0f * q.z * q.z),
		(2.0f * q.x * q.y) + (2.0f * q.z * q.w),
		(2.0f * q.x * q.z) - (2.0f * q.y * q.w),
		0.0f,

		(2.0f * q.x * q.y) - (2.0f * q.z * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.z * q.z),
		(2.0f * q.y * q.z) + (2.0f * q.x * q.w),
		0.0f,

		(2.0f * q.x * q.z) + (2.0f * q.y * q.w),
		(2.0f * q.y * q.z) - (2.0f * q.x * q.w),
		1.0f - (2.0f * q.x * q.x) - (2.0f * q.y * q.y),
		0.0f,

		0.0f,
		0.0f,
		0.0f,
		1.0f
	);
}

//----------------------------------------------------------------------------------------------------

Quaternion Slerp(Quaternion q0, Quaternion q1, f32 t)
{
	// Find the dot product
	f32 dot = (q0.x * q1.x) + (q0.y * q1.y) + (q0.z * q1.z) + (q0.w * q1.w);

	// Determine the direction of the rotation.
	if (dot < 0.0f)
	{
		dot = -dot;
		q1.x = -q1.x;
		q1.y = -q1.y;
		q1.z = -q1.z;
		q1.w = -q1.w;
	}
	else if (dot > 0.999f)
	{
		return Normalize(Lerp(q0, q1, t));
	}

	f32 theta = acosf(dot);
	f32 sintheta = sinf(theta);
	f32 scale0 = sinf(theta * (1.0f - t)) / sintheta;
	f32 scale1 = sinf(theta * t) / sintheta;

	// Perform the slerp
	return Quaternion
	(
		(q0.x * scale0) + (q1.x * scale1),
		(q0.y * scale0) + (q1.y * scale1),
		(q0.z * scale0) + (q1.z * scale1),
		(q0.w * scale0) + (q1.w * scale1)
	);
}

//----------------------------------------------------------------------------------------------------

bool Intersect(const Ray& ray, const Plane& plane, f32& distance)
{
	const f32 orgDotN = Dot(ray.org, plane.n);
	const f32 dirDotN = Dot(ray.dir, plane.n);

	// Check if ray is parallel to the plane
	if (IsZero(dirDotN))
	{
		if (IsZero(orgDotN - plane.d))
		{
			distance = 0.0f;
			return true;
		}
		else
		{
			return false;
		}
	}

	// Compute distance
	distance = (plane.d - orgDotN) / dirDotN;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Intersect(const Ray& ray, const AABB& aabb, f32& distEntry, f32& distExit)
{
	// https://truesculpt.googlecode.com/hg-history/Release%25200.8/Doc/ray_box_intersect.pdf

	// Returns true if ray intersects bounding box
	// Sets d1 to entry distance, d2 to exit distance (along ray.dir)

	Vector3 boxMin = aabb.center - aabb.extend;
	Vector3 boxMax = aabb.center + aabb.extend;
	f32 tmin, tmax, tymin, tymax, tzmin, tzmax;

	f32 divx = 1.0f / ray.dir.x;
	f32 divy = 1.0f / ray.dir.y;
	f32 divz = 1.0f / ray.dir.z;

	if (divx >= 0.0f)
	{
		tmin = (boxMin.x - ray.org.x) * divx;
		tmax = (boxMax.x - ray.org.x) * divx;
	}
	else
	{
		tmin = (boxMax.x - ray.org.x) * divx;
		tmax = (boxMin.x - ray.org.x) * divx;
	}
	if (divy >= 0.0f)
	{
		tymin = (boxMin.y - ray.org.y) * divy;
		tymax = (boxMax.y - ray.org.y) * divy;
	}
	else
	{
		tymin = (boxMax.y - ray.org.y) * divy;
		tymax = (boxMin.y - ray.org.y) * divy;
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		return false;
	}

	if (tymin > tmin)
	{
		tmin = tymin;
	}

	if (tymax < tmax)
	{
		tmax = tymax;
	}

	if (divz >= 0.0f)
	{
		tzmin = (boxMin.z - ray.org.z) * divz;
		tzmax = (boxMax.z - ray.org.z) * divz;
	}
	else
	{
		tzmin = (boxMax.z - ray.org.z) * divz;
		tzmax = (boxMin.z - ray.org.z) * divz;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		return false;
	}

	if (tzmin > tmin)
	{
		tmin = tzmin;
	}

	if (tzmax < tmax)
	{
		tmax = tzmax;
	}

	distEntry = tmin;
	distExit = tmax;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Intersect(const Ray& ray, const OBB& obb, f32& distEntry, f32& distExit)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix matTrans = Matrix::Translation(obb.center.x, obb.center.y, obb.center.z);
	Matrix matRot = Matrix::RotationQuaternion(obb.rot);
	Matrix matWorld = matRot * matTrans;
	Matrix matWorldInv = Inverse(matWorld);

	// Transform the ray into the OBB's local space
	Vector3 org = TransformCoord(ray.org, matWorldInv);
	Vector3 dir = TransformNormal(ray.dir, matWorldInv);

	AABB aabb(Vector3::Zero(), obb.extend);
	return Intersect(Ray(org, dir), aabb, distEntry, distExit);
}

//----------------------------------------------------------------------------------------------------

bool Intersect(const Vector3& point, const AABB& aabb)
{
	const Vector3 test = point + aabb.center;
	if (abs(test.x) > aabb.extend.x) return false;
	if (abs(test.y) > aabb.extend.y) return false;
	if (abs(test.z) > aabb.extend.z) return false;
	return true;
}

//----------------------------------------------------------------------------------------------------

bool Intersect(const Vector3& point, const OBB& obb)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix matTrans = Matrix::Translation(obb.center.x, obb.center.y, obb.center.z);
	Matrix matRot = Matrix::RotationQuaternion(obb.rot);
	Matrix matWorld = matRot * matTrans;
	Matrix matWorldInv = Inverse(matWorld);

	// Transform the point into the OBB's local space
	Vector3 localPoint = TransformCoord(point, matWorldInv);
	AABB aabb(Vector3::Zero(), obb.extend);

	// Test against local AABB
	return Intersect(localPoint, aabb);
}

//----------------------------------------------------------------------------------------------------

void GetCorners(const OBB& obb, std::vector<Vector3>& corners)
{
	// Compute the local-to-world matrices
	Matrix matTrans = Matrix::Translation(obb.center.x, obb.center.y, obb.center.z);
	Matrix matRot = Matrix::RotationQuaternion(obb.rot);
	Matrix matWorld = matRot * matTrans;

	// Create a local AABB
	corners.clear();
	corners.push_back(Vector3(-obb.extend.x, -obb.extend.y, -obb.extend.z));
	corners.push_back(Vector3(-obb.extend.x, -obb.extend.y,  obb.extend.z));
	corners.push_back(Vector3( obb.extend.x, -obb.extend.y,  obb.extend.z));
	corners.push_back(Vector3( obb.extend.x, -obb.extend.y, -obb.extend.z));
	corners.push_back(Vector3(-obb.extend.x,  obb.extend.y, -obb.extend.z));
	corners.push_back(Vector3(-obb.extend.x,  obb.extend.y,  obb.extend.z));
	corners.push_back(Vector3( obb.extend.x,  obb.extend.y,  obb.extend.z));
	corners.push_back(Vector3( obb.extend.x,  obb.extend.y, -obb.extend.z));

	// Transform AABB into world space to form the OBB
	const u32 kNumCorners = corners.size();
	for (u32 i = 0; i < kNumCorners; ++i)
	{
		corners[i] = TransformCoord(corners[i], matWorld);
	}
}

//----------------------------------------------------------------------------------------------------

bool GetContactPoint(const Ray& ray, const OBB& obb, Vector3& point, Vector3& normal)
{
	// Compute the local-to-world/world-to-local matrices
	Matrix matTrans = Matrix::Translation(obb.center.x, obb.center.y, obb.center.z);
	Matrix matRot = Matrix::RotationQuaternion(obb.rot);
	Matrix matWorld = matRot * matTrans;
	Matrix matWorldInv = Inverse(matWorld);

	// Transform the ray into the OBB's local space
	Vector3 org = TransformCoord(ray.org, matWorldInv);
	Vector3 dir = TransformNormal(ray.dir, matWorldInv);
	Ray localRay(org, dir);

	Plane planes[] =
	{
		Plane( 0.0f,  0.0f, -1.0f, obb.extend.z),
		Plane( 0.0f,  0.0f,  1.0f, obb.extend.z),
		Plane( 0.0f, -1.0f,  0.0f, obb.extend.y),
		Plane( 0.0f,  1.0f,  0.0f, obb.extend.y),
		Plane(-1.0f,  0.0f,  0.0f, obb.extend.x),
		Plane( 1.0f,  0.0f,  0.0f, obb.extend.x)
	};

	u32 numIntersections = 0;
	for (u32 i = 0; i < 6; ++i)
	{
		const f32 d = Dot(org, planes[i].n);
		if (d > planes[i].d)
		{
			f32 distance = 0.0f;
			if (Intersect(localRay, planes[i], distance) && distance >= 0.0f)
			{
				Vector3 pt = org + (dir * distance);
				if (abs(pt.x) <= obb.extend.x + 0.01f &&
					abs(pt.y) <= obb.extend.y + 0.01f &&
					abs(pt.z) <= obb.extend.z + 0.01f)
				{
					point = pt;
					normal = planes[i].n;
					++numIntersections;
				}
			}
		}
	}

	if (numIntersections == 0)
	{
		return false;
	}

	point = TransformCoord(point, matWorld);
	normal = TransformNormal(normal, matWorld);
	return true;
}

} // namespace Math