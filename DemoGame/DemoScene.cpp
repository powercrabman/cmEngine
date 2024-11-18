#include "pch.h"
#include "DemoScene.h"
#include "SpriteRenderSystem.h"

void DemoScene::EnterScene()
{
	using namespace cmEngine;

	{
		Texture* tex = ResourceManager::CreateResource<Texture>("TestTexture");
		tex->Load(ResourceManager::GetClientResourcePath(L"test.png"));
		tex->Create();

		Sprite* sp = ResourceManager::CreateResource<Sprite>("TestSprite");
		sp->Create(SpriteData{
			.Texture  = tex,
			.Width    = 0,
			.Height   = 0,
			.PivotRow = 0,
			.PivotCol = 0
			});
	}

	{
		Texture* tex = ResourceManager::CreateResource<Texture>("TestFlipbookTexture");
		tex->Load(ResourceManager::GetClientResourcePath(L"Older_Walk.bmp"));
		tex->Create();

		Flipbook* fb = ResourceManager::CreateResource<Flipbook>("TestFlipbook");
		fb->Create(FlipbookData{
		.Texture       = tex,
		.Width         = 75,
		.Height        = 85,
		.PivotRow      = 0,
		.PivotCol      = 0,
		.FrameCount    = 12,
		.FrameDuration = 0.08f,
		.Loop          = true
			});
	}

	// Player
	{
		auto entity = CreateGameEntity();
		entity.CreateComponent<Transform>(Transform::sIdentity);
		entity.CreateComponent<SpriteRender>(SpriteRender{
		.sprite            = ResourceManager::FindResourceOrNull<Sprite>("TestSprite"),
		.shaders           = ResourceManager::FindResourceOrNull<ShaderSet>("TestShaders"),
		.rendererState     = RenderState{
		.samplerState      = eSamplerState::Point_Wrap,
		.depthStencilState = eDepthStencilState::Depth,
		.rasterizerState   = eRasterizerState::Default,
		.blendState        = eBlendState::Default
		}});
	}

	// Player 2
	{
		auto entity = CreateGameEntity();
		entity.CreateComponent<Transform>(Transform{ Vector3{0.5f,0.f,0.f}, EulerAngle::Zero, Vector3::One });
		entity.CreateComponent<FlipbookRender>(FlipbookRender{
			.flipbook      = ResourceManager::FindResourceOrNull<Flipbook>("TestFlipbook"),
			.shaders       = ResourceManager::FindResourceOrNull<ShaderSet>("TestShaders"),
			.rendererState = RenderState::DefaultState,
			.curFrame      = 0,
			.playbackSpeed = 1.f,
			.timeAcc       = 0.f,
			.finish        = false
			});
	}

	// Camera
	{
		auto entity = CreateGameEntity();
		entity.CreateComponent<Transform>(Transform{ Vector3{0.f,0.f,-1.f}, EulerAngle::Zero, Vector3::One });
		entity.CreateComponent<Camera>(Camera::CreatePerspective(45.f, 0.01f, 100.f));
		SetMainCameraEntity(entity);
	}
}

void DemoScene::ExitScene()
{
}
