#include "pch.h"
#include "DemoScene.h"

void DemoScene::EnterScene()
{
	using namespace cmEngine;

	// Demo object
	{
		cmEngine::GameEntity* obj = CreateGameEntity();
		cmEngine::GeometryRenderer* geo = obj->CreateComponent<cmEngine::GeometryRenderer>();
		geo->SetQuadGeometry(cmEngine::Colors::Blue);
		geo->SetShaders(ResourceManager::FindResourceOrNull<ShaderSet>("DemoShaderSet"));
	}

	// Demo Camera
	{
		cmEngine::GameEntity* obj = CreateGameEntity();
		cmEngine::CameraComponent* cmr = obj->CreateComponent<cmEngine::CameraComponent>(obj->FindComponentOrNull<Transform>());
		cmr->SetupOrthographicRatio(1.666f, 0.01, 100.f);
		cmr->SetPosition({ 0.f,0.f,-3.f });
		cmr->SetAsMainCamera();
	}
}

void DemoScene::ExitScene()
{
}
