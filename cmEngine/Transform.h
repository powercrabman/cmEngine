#pragma once

namespace cmEngine
{
	struct Transform
	{
		[[nodiscard]] Matrix GetWorldMatrix() const;

		Vector3		position;
		EulerAngle	rotation;
		Vector3		scaling;

		static Transform sIdentity;
	};
}