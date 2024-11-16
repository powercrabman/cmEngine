#pragma once
#include "Component.h"
#include "Viewport.h"
#include "Transform.h"

namespace cmEngine
{
	class CameraComponent
		: public		Component
	{
	public:
		COMPONENT_BODY(CameraComponent);

		CameraComponent(Transform* inOwnerTransform) { mTransform = inOwnerTransform; };
		virtual ~CameraComponent() = default;

		void OnStart() override;
		void OnFinish() override;

		void SetAsMainCamera() { mIsMainCamera = true; Renderer::RegisterCamera(this); }
		void UnSetMainCamera();

		Matrix GetView() const;
		Matrix GetProjection() const;
		Matrix GetViewProjection() const { return GetView() * GetProjection(); }

		void SetupPerspective(float inFov, float inNear, float inFar);
		void SetupOrthographic(float inWidth, float inHeight, float inNear, float inFar);
		void SetupOrthographicRatio(float inHeight, float inNear, float inFar);

		void SetFieldOfView(float inFOV) { mFOV = inFOV; }
		void SetProjectionMode(eProjectionMode inMode) { mMode = inMode; }
		void SetNearPlane(float inNear) { mNear = inNear; }
		void SetFarPlane(float inFar) { mFar = max(mNear + 0.01f, inFar); }

		float			GetFieldOfView() const { return mFOV; }
		eProjectionMode GetProjectionMode() const { return mMode; }
		float			GetNearPlane() const { return mNear; }
		float			GetFarPlane() const { return mFar; }

		void SetPosition(const Vector3& inPosition) { mTransform->SetPosition(inPosition); }
		void AddPosition(const Vector3& inPosition) { mTransform->AddPosition(inPosition); }

		void SetPositionX(float inX) { mTransform->SetPositionX(inX); }
		void AddPositionX(float inX) { mTransform->AddPositionX(inX); }

		void SetPositionY(float inY) { mTransform->SetPositionY(inY); }
		void AddPositionY(float inY) { mTransform->AddPositionY(inY); }

		void SetPositionZ(float inZ) { mTransform->SetPositionZ(inZ); }
		void AddPositionZ(float inZ) { mTransform->AddPositionZ(inZ); }

		Vector3 GetPosition() const { return mTransform->GetPosition(); }

		void SetRotation(const Vector3& inRotation) { mTransform->SetRotation(inRotation); }
		void AddRotation(const Vector3& inRotation) { mTransform->AddRotation(inRotation); }

		void SetRotationX(float inX) { mTransform->SetRotationX(inX); }
		void AddRotationX(float inX) { mTransform->AddRotationX(inX); }
		void SetRotationY(float inY) { mTransform->SetRotationY(inY); }
		void AddRotationY(float inY) { mTransform->AddRotationY(inY); }
		void SetRotationZ(float inZ) { mTransform->SetRotationZ(inZ); }
		void AddRotationZ(float inZ) { mTransform->AddRotationZ(inZ); }

		Vector3 GetRotation() const { return mTransform->GetRotation(); }

		void SetCameraResolution(float inWidth, float inHeight)
		{
			mWidth = inWidth;
			mHeight = inHeight;
		}

		void SetCameraResolutionRatio(float inHeight)
		{
			float ratio = Renderer::GetAspectRatio();
			SetCameraResolution(inHeight * ratio, inHeight);
		}

		auto GetCameraResolution() const { return std::make_pair(mWidth, mHeight); }

	private:
		eProjectionMode mMode = eProjectionMode::Orthographic;

		float mNear = 0.1f;
		float mFar = 100.f;

		Transform* mTransform = nullptr;

		// For Orthographic
		float mWidth = 1.f;
		float mHeight = 1.f;

		// For Perspective
		float mFOV = Math::PI_Q;

		bool mIsMainCamera = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline Matrix CameraComponent::GetView() const
	{
		Matrix mat = DirectX::XMMatrixRotationRollPitchYawFromVector(mTransform->GetRotation());

		return DirectX::XMMatrixLookToLH(
			GetPosition(),
			mat.Backward(),
			mat.Up()
		);
	}

	inline Matrix CameraComponent::GetProjection() const
	{
		if (mMode == eProjectionMode::Perspective)
		{
			return DirectX::XMMatrixPerspectiveFovLH(mFOV, Renderer::GetAspectRatio(), mNear, mFar);
		}
		else
		{
			return DirectX::XMMatrixOrthographicLH(mWidth, mHeight, mNear, mFar);
		}
	}

	inline void CameraComponent::SetupPerspective(float inFov, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Perspective);
		SetFieldOfView(inFov);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	inline void CameraComponent::SetupOrthographic(float inWidth, float inHeight, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Orthographic);
		SetCameraResolution(inWidth, inHeight);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	inline void CameraComponent::SetupOrthographicRatio(float inHeight, float inNear, float inFar)
	{
		SetProjectionMode(eProjectionMode::Orthographic);
		SetCameraResolutionRatio(inHeight);
		SetNearPlane(inNear);
		SetFarPlane(inFar);
	}

	inline void CameraComponent::UnSetMainCamera() {
		if (mIsMainCamera)
		{
			Renderer::UnregisterCamera(this);
			mIsMainCamera = false;
		}
	}
}