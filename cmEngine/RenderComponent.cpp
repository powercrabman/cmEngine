#include "EnginePch.h"
#include "RenderComponent.h"

namespace cmEngine
{
	void RenderComponent::OnStart()
	{
		Renderer::RegisterRenderComponent(this);
	}

	void RenderComponent::OnFinish()
	{
		Renderer::UnregisterRenderComponent(this);
	}
}
