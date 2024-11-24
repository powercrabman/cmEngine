#include "pch.h"
#include "DemoScene.h"

void DemoScene::EnterScene()
{
	using namespace cmEngine;

	{
		Texture* tex = ResourceManager::CreateEmptyResource<Texture>("TestTexture");
		tex->LoadTextureImage(L"Resources\\test.png");

		Sprite* sp = ResourceManager::CreateEmptyResource<Sprite>("TestSprite");
		sp->Create(SpriteData{
			.texture  = tex,
			.width    = 0,
			.height   = 0,
			.pivotRow = 0,
			.pivotCol = 0
			});
	}

	{
		Texture* tex = ResourceManager::CreateEmptyResource<Texture>("TestFlipbookTexture");
		tex->LoadTextureImage(L"Resources\\Older_Walk_transparent.png");

		Flipbook* fb = ResourceManager::CreateEmptyResource<Flipbook>("TestFlipbook");
		fb->Create(FlipbookData{
		.texture       = tex,
		.width         = 75,
		.height        = 85,
		.pivotRow      = 0,
		.pivotCol      = 0,
		.frameCount    = 12,
		.frameDuration = 0.08f,
		.loop          = true});
	}

	// Player
	{
		auto entity = CreateGameEntity();
		entity.CreateComponent<Transform>(Transform{ Vector3{0.f,0.f,0.5f}, EulerAngle::Zero, Vector3::One });
		entity.CreateComponent<SpriteRender>(SpriteRender{
			.sprite = ResourceManager::TryFindResource<Sprite>("TestSprite")
			}
		);
		entity.CreateComponent<RenderProfile>(RenderProfile{
			.shaders           = ResourceManager::TryFindResource<ShaderSet>("TestShaders"),
			.rendererState     = RenderState{
			.samplerState      = eSamplerState::Point_Wrap,
			.depthStencilState = eDepthStencilState::Depth,
			.rasterizerState   = eRasterizerState::Default,
			.blendState        = eBlendState::Default
			}
		}
		);
	}

	// Player 2
	{
		auto entity = CreateGameEntity();
		entity.CreateComponent<Transform>(Transform{ Vector3{0.5f,0.f,0.f}, EulerAngle::Zero, Vector3::One });
		entity.CreateComponent<FlipbookRender>(FlipbookRender{
			.flipbook              = ResourceManager::TryFindResource<Flipbook>("TestFlipbook"),
			.curFrame              = 0,
			.playbackSpeed         = 1.f,
			.timeAcc               = 0.f,
			.finish                = false
			}
		);

		entity.CreateComponent<RenderProfile>(RenderProfile{
			.shaders = ResourceManager::TryFindResource<ShaderSet>("TestShaders"),
			.rendererState = RenderState{
			.samplerState = eSamplerState::Point_Wrap,
			.depthStencilState = eDepthStencilState::Depth,
			.rasterizerState = eRasterizerState::Default,
			.blendState = eBlendState::Default
			}
		});

		entity.CreateComponent<Name>("Player");
		auto& controller = entity.CreateComponent<InputController>();
		controller.keyEvents.emplace_back(
			"LeftMove",
			eKeyCode::Left,
			eKeyState::Hold,
			[] (GameEntity inGameEntity)
			{
				inGameEntity.FindComponent<Transform>().position.x += -1 * Timer::GetDeltaTime();
			}
		);

		controller.keyEvents.emplace_back(
			"RightMove",
			eKeyCode::Right,
			eKeyState::Hold,
			[](GameEntity inGameEntity)
			{
				inGameEntity.FindComponent<Transform>().position.x += 1 * Timer::GetDeltaTime();
			}
		);

		controller.keyEvents.emplace_back(
			"UpMove",
			eKeyCode::Up,
			eKeyState::Hold,
			[](GameEntity inGameEntity)
			{
				inGameEntity.FindComponent<Transform>().position.y += 1 * Timer::GetDeltaTime();
			}
		);

		controller.keyEvents.emplace_back(
			"DownMove",
			eKeyCode::Down,
			eKeyState::Hold,
			[](GameEntity inGameEntity)
			{
				inGameEntity.FindComponent<Transform>().position.y += -1 * Timer::GetDeltaTime();
			}
		);
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
