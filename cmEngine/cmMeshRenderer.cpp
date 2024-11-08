#include "pch.h"
#include "cmMeshRenderer.h"

void cmMeshRenderer::OnStart()
{
	Engine->GetRenderer()->RegistGameObject(GetOwner());
}

void cmMeshRenderer::OnFinish()
{
	Engine->GetRenderer()->UnregistGameObject(GetOwner());
}

