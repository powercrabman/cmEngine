#pragma once

namespace cmEngine
{
	enum class eCameraProjectionMode
	{
		Perspective = 0,
		Orthographic = 1,
	};

	struct Camera
	{
		static Camera CreatePerspective(float inFov, float inNear, float inFar);
		static Camera CreateOrthographic(float inWidth, float inHeight, float inNear, float inFar);
		static Camera CreateOrthographicByRatio(float inHeight, float inNear, float inFar);

		Matrix GetViewMatrix(const Transform& inTrans) const;
		Matrix GetProjectionMatrix() const;
		Matrix GetViewProjMatrix(const Transform& inTrans) const;

		//===================================================

		eCameraProjectionMode mode = eCameraProjectionMode::Orthographic;

		float nearPlane = 0.1f;
		float farPlane  = 100.f;

		float width  = 1.f;
		float height = 1.f;

		float fov = Math::PI_Q;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline Camera Camera::CreatePerspective(float inFov, float inNear, float inFar)
	{
		Camera cmr    = {};
		cmr.mode      = eCameraProjectionMode::Perspective;
		cmr.fov       = inFov;
		cmr.nearPlane = inNear;
		cmr.farPlane  = inFov;
		return cmr;
	}

	inline Camera Camera::CreateOrthographic(float inWidth, float inHeight, float inNear, float inFar)
	{
		Camera cmr    = {};
		cmr.mode      = eCameraProjectionMode::Orthographic;
		cmr.width     = inWidth;
		cmr.height    = inHeight;
		cmr.nearPlane = inNear;
		cmr.farPlane  = inFar;
		return cmr;
	}

	inline Camera Camera::CreateOrthographicByRatio(float inHeight, float inNear, float inFar)
	{
		Camera cmr    = {};
		cmr.mode      = eCameraProjectionMode::Orthographic;
		cmr.width     = inHeight * Renderer::GetAspectRatio();
		cmr.height    = inHeight;
		cmr.nearPlane = inNear;
		cmr.farPlane  = inFar;
		return cmr;
	}

	inline Matrix Camera::GetViewMatrix(const Transform& inTrans) const
	{
		Matrix mat = DirectX::XMMatrixRotationRollPitchYawFromVector(inTrans.rotation);

		return DirectX::XMMatrixLookToLH(
			inTrans.position,
			mat.Backward(),
			mat.Up()
		);
	}

	inline Matrix Camera::GetProjectionMatrix() const
	{
		if (mode == eCameraProjectionMode::Perspective)
		{
			return DirectX::XMMatrixPerspectiveFovLH(fov, Renderer::GetAspectRatio(), nearPlane, farPlane);
		}
		else
		{
			return DirectX::XMMatrixOrthographicLH(width, height, nearPlane, farPlane);
		}
	}

	inline Matrix Camera::GetViewProjMatrix(const Transform& inTrans) const
	{
		return GetViewMatrix(inTrans) * GetProjectionMatrix();
	}
}


