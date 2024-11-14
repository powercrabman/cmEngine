#include "EnginePch.h"
#include "Transform.h"

namespace cmEngine
{
	void Transform::PreRender()
	{
		CBTransform t = {};
		t.World = GetWorld();

		ConstantBufferPool::FindConstantBuffer<CBTransform>()->UpdateBuffer(t);
	}
}
