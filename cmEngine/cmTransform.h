#pragma once
#include "cmComponent.h"
#include "cmIPreRenderable.h"

class cmTransform 
	: public cmComponent
	, IMPLEMENTS cmIPreRenderable
{
public:
	cmTransform() = default;
	virtual ~cmTransform() = default;

	void OnStart() override {}
	void OnFinish() override {}
	void PreRender() override;

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

	void SetRotationX(float inDegree) { mRotation.x = inDegree; }
	void AddRotationX(float inDegree) { mRotation.x += inDegree; }

	void SetRotationY(float inDegree) { mRotation.y = inDegree; }
	void AddRotationY(float inDegree) { mRotation.y += inDegree; }

	void SetRotationZ(float inDegree) { mRotation.z = inDegree; }
	void AddRotationZ(float inDegree) { mRotation.z += inDegree; }

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
	Matrix GetWorld() const
	{
		return DirectX::XMMatrixAffineTransformation(
			mScale,
			Vector3::Zero,
			Quaternion::CreateFromYawPitchRoll(mRotation),
			mPosition
		);
	}

	constexpr inline static eComponentType ComponentType = eComponentType::Transform;

private:
	Vector3 mPosition = Vector3::Zero;
	Vector3 mRotation = Vector3::Zero; // Pitch Yaw Roll
	Vector3 mScale = Vector3::One;
};