#include "pch.h"
#include "cmTransform.h"
#include "cmGraphicsResourceManager.h"

void cmTransform::Render()
{
	cmCBTransform t = {};
	t.World = GetWorld();

	auto* cb = Engine->GetRenderer()->GetGraphicsResourceManager()->FindConstantBufferOrNull<cmCBTransform>();
	cb->UpdateBuffer(t);
}
