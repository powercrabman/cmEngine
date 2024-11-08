#include "pch.h"
#include "Demo.h"
#include "cmGUIRenderer.h"
#include "cmWindow.h"
#include "cmSceneManager.h"
#include "DummyScene.h"

void Demo::Initialize()
{
	auto* sm = Engine->GetSceneManager();
	sm->CreateScene<DummyScene>();
	sm->ChangeScene<DummyScene>();
}

void Demo::CleanUp()
{
}
