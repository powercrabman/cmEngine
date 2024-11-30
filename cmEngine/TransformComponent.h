#pragma once

namespace cmEngine
{
	struct TransformComponent
	{
		Vector3 mPosition = Vector3::Zero;
		Vector3 mRotation = Vector3::Zero; // Pitch Yaw Roll
		Vector3 mScale = Vector3::One;
	};
}