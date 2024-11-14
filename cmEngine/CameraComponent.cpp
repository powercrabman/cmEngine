#include "EnginePch.h"
#include "CameraComponent.h"

namespace cmEngine
{
	void CameraComponent::OnStart()
	{
	}

	void CameraComponent::OnFinish()
	{
	}

	void CameraComponent::PreRender()
	{
		CBCamera cmr = {};
		cmr.ViewProj = GetViewProjection();

		ConstantBufferPool::FindConstantBuffer<CBCamera>()->UpdateBuffer(cmr);
	}
}
