#include "EnginePch.h"
#include "Scene.h"
#include "GameEntity.h"
#include "RenderSystem.h"
#include "BehaviorSystem.h"
#include "InputControllerSystem.h"

namespace cmEngine
{
	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::EnterSceneCore()
	{
		// �⺻ ī�޶� ��ƼƼ ����
		mDefaultCameraEntity = CreateGameEntity();
		mDefaultCameraEntity.CreateComponent<Transform>(Transform::sIdentity);
		mDefaultCameraEntity.CreateComponent<Camera>(Camera::CreatePerspective(Math::DegToRad(45.f), 0.01f, 100.f));
		mDefaultCameraEntity.CreateComponent<Name>("Default Scene Camera");

		// �⺻ �ý��� ���
		AttachSystem(FlipbookUpdateSystem, eSystemLayer::Update);
		AttachSystem(BehaviorSystem, eSystemLayer::Update);
		AttachSystem(InputControllerSystem, eSystemLayer::Update);

		AttachSystem(FlipbookRenderSystem, eSystemLayer::Render);
		AttachSystem(SpriteRenderSystem, eSystemLayer::Render);
		AttachSystem(GeometryRenderSystem, eSystemLayer::Render);

		EnterScene();
	}

	void Scene::UpdateScene()
	{
		// Update Layer
		for (const auto& func : mSystemLayer[static_cast<uint32>(eSystemLayer::Update)]) { func(this); }
	}

	void Scene::RenderScene()
	{
		// Camera Update
		mCameraEntity = mCameraEntity.IsValid() ? mCameraEntity : mDefaultCameraEntity;
		auto [trans, cmr] = mRegistry.get<Transform, Camera>(mCameraEntity);
		Renderer::GetPipeline()->SetViewProj(cmr.GetViewProjMatrix(trans));

		// Render Layer
		for (const auto& func : mSystemLayer[static_cast<uint32>(eSystemLayer::Render)]) { func(this); }
	}

	void Scene::ExitSceneCore()
	{
		ExitScene();

		for (auto& layer : mSystemLayer)
		{
			layer.clear();
		}
	}

	GameEntity Scene::CloneGameEntity(GameEntity inGameEntity)
	{
		GameEntity copied = CreateGameEntity();

		auto storage_view = mRegistry.storage();
		for (auto [id, storage] : mRegistry.storage())
		{
			if (storage.contains(inGameEntity))
			{
				storage.push(copied, storage.value(inGameEntity));
			}
		}

		return copied;
	}

	GameEntity Scene::FindEntityByName(const Name& inName)
	{
		auto view = mRegistry.view<Name>();
		for (auto entity : view)
		{
			if (view.get<Name>(entity) == inName)
			{
				return GameEntity{ entity };
			}
		}

		return GameEntity::NullEntity;
	}


	GameEntity Scene::FindByID(uint32 inID) const
	{
		entt::entity entity = static_cast<entt::entity>(inID);
		if (mRegistry.valid(entity))
		{
			return GameEntity{ entity };
		}

		return GameEntity::NullEntity;
	}

	void Scene::SetMainCameraEntity(const GameEntity& inEntity)
	{
		if (inEntity.IsValid() && inEntity.HasComponents<Transform, Camera>())
		{
			mCameraEntity = inEntity;
		}
	}

	GameEntity Scene::GetMainCameraEntity() const
	{
		return mCameraEntity;
	}
}
