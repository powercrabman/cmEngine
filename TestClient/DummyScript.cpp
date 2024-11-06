#include "pch.h"
#include "DummyScript.h"
#include "cmGameObject.h"
#include "cmMeshRenderer.h"
#include "cmMesh.h"

void DummyScript::Initialize()
{
	mesh = GetOwner()->CreateComponent<cmMeshRenderer>(true);
	mesh->SetMesh(Engine->GetResourceManager()->FindResourceOrNull<cmMesh>("SimpleMesh"));
}

void DummyScript::OnStart()
{
}

void DummyScript::OnFinish()
{
}

void DummyScript::Update()
{
}

void DummyScript::FinalUpdate()
{
}

