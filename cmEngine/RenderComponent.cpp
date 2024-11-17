#include "EnginePch.h"
#include "RenderComponent.h"

namespace cmEngine
{
	void RenderComponent::Awake()
	{
		Renderer::RegisterRenderComponent(this);
	}

	void RenderComponent::Sleep()
	{
		Renderer::UnregisterRenderComponent(this);
	}
}
