#pragma once
#include "cmComponent.h"
#include "cmIRenderable.h"
#include "cmViewport.h"

class cmCamera : public cmComponent, public cmIRenderable
{
public:
	cmCamera() = default;
	virtual ~cmCamera() = default;

	void OnStart() override;
	void OnFinish() override;

	void Render() override;

Matrix GetView() const
{
	return DirectX::XMMatrixLookToLH(
		mPosition,
		DirectX::XMMatrixRotationRollPitchYawFromVector(mRotate).r[2],
		Vector3::Up
	);
}

	Matrix GetProjection() const
	{
		if (mMode == eProjectionMode::Perspective)
		{
			const cmViewport* vp = Engine->GetRenderer()->GetViewport();
			return DirectX::XMMatrixPerspectiveFovLH(mFOV, vp->AspectRatio(), mNear, mFar);
		}
		else
		{
			return DirectX::XMMatrixOrthographicLH(mWidth, mHeight, mNear, mFar);
		}
	}

	Matrix GetViewProjection() const
	{
		return GetView() * GetProjection();
	}

	void SetupPerspective(float inFov, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Perspective);
		SetFieldOfView(inFov);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	void SetupOrthographic(float inWidth, float inHeight, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Orthographic);
		SetCameraScreenSize(inWidth, inHeight);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	void SetupOrthographicMatchAspectRatio(float inHeight, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Orthographic);
		SetCameraScreenSizeMatchAspectRatio(inHeight);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	void SetFieldOfView(float inFOV) { mFOV = inFOV; }
	void SetProjectionMode(eProjectionMode inMode) { mMode = inMode; }
	void SetNearPlane(float inNear) { mNear = inNear; }
	void SetFarPlane(float inFar) { mFar = max(mNear + 0.01f, inFar); }

	float GetFieldOfView() const { return mFOV; }
	eProjectionMode GetProjectionMode() const { return mMode; }
	float GetNearPlane() const { return mNear; }
	float GetFarPlane() const { return mFar; }

	void SetPosition(const Vector3& inPosition) { mPosition = inPosition; }
	void AddPosition(const Vector3& inPosition) { mPosition += inPosition; }

	void SetPositionX(float inX) { mPosition.x = inX; }
	void AddPositionX(float inX) { mPosition.x += inX; }

	void SetPositionY(float inY) { mPosition.y = inY; }
	void AddPositionY(float inY) { mPosition.y += inY; }

	void SetPositionZ(float inZ) { mPosition.z = inZ; }
	void AddPositionZ(float inZ) { mPosition.z += inZ; }

	Vector3 GetPosition() const { return mPosition; }

	void SetRotation(const Vector3& inRotation) { mRotate = inRotation; }
	void AddRotation(const Vector3& inRotation) { mRotate += inRotation; }

	void SetRotationX(float inX) { mRotate.x = inX; }
	void AddRotationX(float inX) { mRotate.x += inX; }

	void SetRotationY(float inY) { mRotate.y = inY; }
	void AddRotationY(float inY) { mRotate.y += inY; }

	void SetRotationZ(float inZ) { mRotate.z = inZ; }
	void AddRotationZ(float inZ) { mRotate.z += inZ; }

	Vector3 GetRotation() const { return mRotate; }

	void SetCameraScreenSize(float inWidth, float inHeight)
	{
		mWidth = inWidth;
		mHeight = inHeight;
	}

	void SetCameraScreenSizeMatchAspectRatio(float inHeight)
	{
		float ratio = Engine->GetRenderer()->GetViewport()->AspectRatio();
		SetCameraScreenSize(inHeight * ratio, inHeight);
	}

	auto GetCameraScreenSize() const { return std::make_pair(mWidth, mHeight); }

	constexpr inline static eComponentType ComponentType = eComponentType::Camera;

private:
	eProjectionMode mMode = eProjectionMode::Orthographic;

	float mNear = 0.1f;
	float mFar = 100.f;

	Vector3 mPosition = Vector3::Zero;
	Vector3 mRotate = Vector3::Zero;

	// For Orthographic
	float mWidth = 1.f;
	float mHeight = 1.f;

	// For Perspective
	float mFOV = 45.f;
};

