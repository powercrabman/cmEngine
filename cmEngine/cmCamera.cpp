#include "pch.h"
#include "cmCamera.h"
#include "cmGraphicsResourceManager.h"

void cmCamera::OnStart()
{
}

void cmCamera::OnFinish()
{
}

void cmCamera::Render()
{
	cmCBCamera cmr = {};
	cmr.ViewProj = GetViewProjection();

	auto* cb = Engine->GetRenderer()->GetGraphicsResourceManager()->FindConstantBufferOrNull<cmCBCamera>();
	cb->UpdateBuffer(cmr);
}
