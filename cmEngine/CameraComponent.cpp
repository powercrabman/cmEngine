#include "EnginePch.h"
#include "CameraComponent.h"

namespace cmEngine
{
	void CameraComponent::Awake()
	{
	}

	void CameraComponent::Sleep()
	{
		Renderer::UnregisterCamera(this);
	}
}
