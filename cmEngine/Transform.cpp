#include "EnginePch.h"
#include "Transform.h"

namespace cmEngine
{
	Transform Transform::sIdentity = { Vector3::Zero, EulerAngle::Zero, Vector3::One };

	Matrix Transform::GetWorldMatrix() const
	{
		return DirectX::XMMatrixAffineTransformation(
			scaling,
			Vector3::Zero,
			Quaternion::CreateFromYawPitchRoll(rotation),
			position
		);
	}
}
	
