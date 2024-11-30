#pragma once

namespace cmEngine
{
	enum class eCameraProjectionMode
	{
		Orthographic = 0,
		Perspective = 1,
	};
	JSON_SERIALIZE_ENUM(
		eCameraProjectionMode,
		ENUM_ENTRY(eCameraProjectionMode::Orthographic, "Orthographic"),
		ENUM_ENTRY(eCameraProjectionMode::Perspective,  "Perspective")
	);

	constexpr const char* ToString(const eCameraProjectionMode e)
	{
		switch (e)
		{
		case eCameraProjectionMode::Orthographic:	return "Orthographic";
		case eCameraProjectionMode::Perspective:	return "Perspective";
		default: return "Undefined";
		}
	}

	struct Camera
	{
		static Camera CreatePerspective(float inFov, float inNear, float inFar);
		static Camera CreateOrthographic(float inWidth, float inHeight, float inNear, float inFar);
		static Camera CreateOrthographicByRatio(float inHeight, float inNear, float inFar);

		Matrix GetViewMatrix(const Transform& inTrans) const;
		Matrix GetProjectionMatrix() const;
		Matrix GetViewProjMatrix(const Transform& inTrans) const;

		//===================================================

		eCameraProjectionMode mode	= eCameraProjectionMode::Orthographic;
		float	nearPlane			= 0.1f;
		float	farPlane			= 100.f;

		float	width				= 1.f;
		float	height				= 1.f;

		float	fov					= Math::PI_Q;

		SERIALIZABLE_COMPONENT_BODY(Camera, mode, nearPlane, farPlane, width, height, fov);
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
		cmr.width     = inHeight * GameWindow::Ref().GetAspectRatio();
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
			return DirectX::XMMatrixPerspectiveFovLH(fov, RENDERER.GetAspectRatio(), nearPlane, farPlane);
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


