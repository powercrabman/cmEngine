#pragma once

namespace cmEngine
{
	struct Transform
	{
		[[nodiscard]] Matrix GetWorldMatrix() const;

		Vector3		position = Vector3::Zero;
		EulerAngle	rotation = Vector3::Zero;
		Vector3		scaling  = Vector3::One;

		static Transform sIdentity;

		SERIALIZABLE_COMPONENT_BODY(Transform, position, rotation, scaling);
	};
}