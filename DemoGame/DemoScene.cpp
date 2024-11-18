#include "pch.h"
#include "DemoScene.h"

void DemoScene::EnterScene()
{
	using namespace cmEngine;

	Texture* tex = ResourceManager::CreateResource<Texture>("TextTexture");
	tex->Load(ResourceManager::GetClientResourcePath(L"test.png"));
	tex->Create();

	Sprite* sp = ResourceManager::CreateResource<Sprite>("TestSprite");
	sp->Create(SpriteData{
		.Texture = tex,
		.Width = 0,
		.Height = 0,
		.PivotRow = 0,
		.PivotCol = 0
		});

	auto entity = CreateGameEntity();
	entity.CreateComponent<Transform>(Transform::sIdentity);
	entity.CreateComponent<SpriteRender>(SpriteRender{
	.sprite = sp,
	.shaders = ResourceManager::FindResourceOrNull<ShaderSet>("TestShader"),
	.rendererState = RenderState::DefaultState
	});
}

void DemoScene::ExitScene()
{
}
