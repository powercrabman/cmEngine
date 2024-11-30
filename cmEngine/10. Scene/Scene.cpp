#include "0. cmEngine/cmEngine.h"
#include "Scene.h"
#include "13. Script/RenderScript.h"
#include "13. Script/UserScript.h"
#include "13. Script/InputControllerScript.h"
#include "6. Renderer/Core/Renderer.h"

namespace cmEngine
{
	Scene::~Scene() {}

	void Scene::EnterScene()
	{
		// 기본 스크립트 등록
		AttachUpdateScript(FlipbookUpdateSystem, eScriptUpdateLevel::Update);
		AttachUpdateScript(UserScript, eScriptUpdateLevel::Update);
		AttachUpdateScript(InputControllerScript, eScriptUpdateLevel::Update);

		AttachRenderScript(FlipbookRenderScript, eScriptRenderLevel::Render);
		AttachRenderScript(SpriteRenderScript, eScriptRenderLevel::Render);
		AttachRenderScript(GeometryRenderScript, eScriptRenderLevel::Render);
	}

	void Scene::UpdateScene()
	{
		// Update Script
		mScriptStack.OnUpdateScript(this);
	}

	void Scene::RenderScene()
	{
		// Camera Update
		if (mSceneCamera.IsValid())
		{
			auto [trans, cmr] = mRegistry.get<Transform, Camera>(mSceneCamera);
			Renderer::Ref().GetPipeline()->SetViewProj(cmr.GetViewProjMatrix(trans));
		}
		else
		{
			Renderer::Ref().GetPipeline()->SetViewProj(Matrix::Identity);
		}
		
		// Render Script
		mScriptStack.OnRenderScript(this);
	}

	void Scene::ExitScene()
	{
		mScriptStack.Clear();
	}

	GameEntity Scene::CreateGameEntityByID(uint32 inID)
	{
		entt::entity entity{ inID };

		if (!mRegistry.valid(entity))
		{
			return GameEntity(this, mRegistry.create(entity));
		}
		else
		{
			return GameEntity(this, entity);
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
				return GameEntity{ this, entity };
			}
		}

		return GameEntity::NullEntity;
	}

	GameEntity Scene::FindEntityByID(uint32 inID) 
	{
		entt::entity entity = static_cast<entt::entity>(inID);
		if (mRegistry.valid(entity))
		{
			return GameEntity{ this,  entity };
		}

		return GameEntity::NullEntity;
	}

	void Scene::SetSceneCamera(const GameEntity& inEntity)
	{
		if (inEntity.IsValid() && inEntity.HasComponents<Transform, Camera>())
		{
			mSceneCamera = inEntity;
		}
	}

	const GameEntity& Scene::TryGetSceneCamera() const
	{
		return mSceneCamera;
	}
}
