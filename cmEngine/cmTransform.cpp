#include "pch.h"
#include "cmTransform.h"
#include "cmGraphicsResourceManager.h"

void cmTransform::PreRender()
{
	cmCBTransform t = {};
	t.World = GetWorld();

	auto* cb = Engine->GetRenderer()->GetGraphicsResourceManager()->FindConstantBuffer<cmCBTransform>();
	cb->UpdateBuffer(t);
}
