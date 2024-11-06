#include "pch.h"
#include "cmMeshRenderer.h"

void cmMeshRenderer::OnStart()
{
	Engine->GetRenderer()->RegisterMeshRenderer(this);
}

void cmMeshRenderer::OnFinish()
{
	Engine->GetRenderer()->UnregisterMeshRenderer(this);
}

