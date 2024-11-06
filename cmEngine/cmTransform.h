#pragma once
#include "cmComponent.h"

class cmTransform : public cmComponent
{
public:
	cmTransform() = default;
	virtual ~cmTransform() = default;

	void OnStart() override;
	void OnFinish() override;

	// Position
	void SetPosition(const Vector3& inPosition) { mPosition = inPosition; }
	void AddPosition(const Vector3& inPosition) { mPosition += inPosition; }

	void SetPositionX(float inX) { mPosition.x = inX; }
	void AddPositionX(float inX) { mPosition.x += inX; }

	void SetPositionY(float inY) { mPosition.y = inY; }
	void AddPositionY(float inY) { mPosition.y += inY; }

	void SetPositionZ(float inZ) { mPosition.z = inZ; }
	void AddPositionZ(float inZ) { mPosition.z += inZ; }

	Vector3 GetPosition() const { return mPosition; }

	// Rotation
	void SetRotation(const Vector3& inRotation) { mRotation = inRotation; }
	void AddRotation(const Vector3& inRotation) { mRotation += inRotation; }

	void SetRotationX(float inX) { mRotation.x = inX; }
	void AddRotationX(float inX) { mRotation.x += inX; }

	void SetRotationY(float inY) { mRotation.y = inY; }
	void AddRotationY(float inY) { mRotation.y += inY; }

	void SetRotationZ(float inZ) { mRotation.z = inZ; }
	void AddRotationZ(float inZ) { mRotation.z += inZ; }

	Vector3 GetRotation() const { return mRotation; }

	// Scale
	void SetScale(const Vector3& inScale) { mScale = inScale; }
	void AddScale(const Vector3& inScale) { mScale += inScale; }

	void SetScaleX(float inX) { mScale.x = inX; }
	void AddScaleX(float inX) { mScale.x += inX; }

	void SetScaleY(float inY) { mScale.y = inY; }
	void AddScaleY(float inY) { mScale.y += inY; }

	void SetScaleZ(float inZ) { mScale.z = inZ; }
	void AddScaleZ(float inZ) { mScale.z += inZ; }

	Vector3 GetScale() const { return mScale; }

	// Matrix
	Matrix GetWorldMatrix() const
	{
		Matrix result = Matrix::CreateFromYawPitchRoll(mRotation);

		// v S R T
		result._11 *= mScale.x;
		result._12 *= mScale.x;
		result._13 *= mScale.x;

		result._21 *= mScale.y;
		result._22 *= mScale.y;
		result._23 *= mScale.y;

		result._31 *= mScale.z;
		result._32 *= mScale.z;
		result._33 *= mScale.z;

		result._41 = mPosition.x;
		result._42 = mPosition.y;
		result._43 = mPosition.z;

		return result;
	}

private:
	Vector3 mPosition = Vector3::Zero;
	Vector3 mRotation = Vector3::Zero; // Pitch Yaw Roll
	Vector3 mScale = Vector3::One;
};