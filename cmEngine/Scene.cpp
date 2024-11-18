#include "EnginePch.h"
#include "Scene.h"
#include "GameEntity.h"

namespace cmEngine
{
	Scene::Scene() {}
	Scene::~Scene() {}

	void Scene::EnterSceneCore()
	{
		// 기본 카메라 엔티티 생성
		mDefaultCameraEntity = CreateGameEntity();
		mDefaultCameraEntity.CreateComponent<Transform>(Transform::sIdentity);
		mDefaultCameraEntity.CreateComponent<Camera>(Camera::CreatePerspective(Math::DegToRad(45.f), 0.01f, 100.f));

		EnterScene();
	}

	void Scene::UpdateScene()
	{
		for (const auto& func : mSystemLayer[static_cast<uint32>(eSystemLayer::Update)])
		{
			func(this);
		}
	}

	void Scene::RenderScene()
	{
		// Camera Data Update
		UpdateCamera();

		for (const auto& func : mSystemLayer[static_cast<uint32>(eSystemLayer::Render)])
		{
			func(this);
		}
	}

	void Scene::ExitSceneCore()
	{
		ExitScene();
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
		else
		{
			return GameEntity::NullEntity;
		}
	}

	void Scene::SetCameraEntity(const GameEntity& inEntity)
	{
		if (inEntity.IsValid() && inEntity.HasComponents<Transform, Camera>())
		{
			mCameraEntity = inEntity;
		}
	}

	GameEntity Scene::GetCameraEntity() const
	{
		return mDefaultCameraEntity;
	}

	void Scene::UpdateCamera()
	{
		if (mCameraEntity.IsValid() == false)
		{
			mCameraEntity = mDefaultCameraEntity;
		}

		auto [trans, cmr] = mRegistry.get<Transform, Camera>(mCameraEntity);
		Renderer::GetPipeline()->SetViewProj(cmr.GetViewProjMatrix(trans));
	}
}
