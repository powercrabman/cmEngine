#include "pch.h"
#include "cmRenderComponent.h"

void cmRenderComponent::OnStart()
{
	Engine->GetRenderer()->RegistGameObject(GetOwner());
}

void cmRenderComponent::OnFinish()
{
	Engine->GetRenderer()->UnregistGameObject(GetOwner());
}
