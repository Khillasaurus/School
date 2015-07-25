#ifndef INCLUDED_ENGINE_CAMERA_H
#define INCLUDED_ENGINE_CAMERA_H

//====================================================================================================
// Filename:	Camera.h
// Created by:	Peter Chan
// Description:	Class for a 3D camera.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "EngineMath.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class Camera
{
public:
	Camera();

	void Setup(f32 fov, f32 aspectRatio, f32 nearPlane, f32 farPlane);

	void SetPosition(const Math::Vector3& position);
	void SetDirection(const Math::Vector3& direction);
	void SetLookAt(const Math::Vector3& target);

	void Walk(f32 distance);
	void Strafe(f32 distance);
	void Rise(f32 distance);

	void Yaw(f32 degree);
	void Pitch(f32 degree);

	const Math::Vector3& GetPosition() const	{ return mPosition; }

	f32 GetFOV() const							{ return mFOV; }
	f32 GetAspectRatio() const					{ return mAspectRatio; }
	f32 GetNearPlane() const					{ return mNearPlane; }
	f32 GetFarPlane() const						{ return mFarPlane; }
	
	Math::Matrix GetViewMatrix() const;
	Math::Matrix GetProjectionMatrix() const;

private:
	void Renormalize();

	Math::Vector3 mPosition;
	Math::Vector3 mLook;
	Math::Vector3 mRight;

	f32 mFOV;
	f32 mAspectRatio;
	f32 mNearPlane;
	f32 mFarPlane;
};

#endif // #ifndef INCLUDED_ENGINE_CAMERA_H