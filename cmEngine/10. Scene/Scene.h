#pragma once
#include "ScriptStack.h"
#include "11. GameEntity/GameEntity.h"
#include "12. Component/Name.h"

namespace cmEngine
{
#define SCENE_BODY(SceneClassName) \
	virtual const char*			ToString() override { return #SceneClassName; }; \

	class Scene
	{
		friend class SceneManager;
	public:
		virtual ~Scene();

		// Core
		void EnterScene();
		void UpdateScene();
		void RenderScene();
		void ExitScene();

		// Game Entity
		GameEntity	CreateGameEntity();
		GameEntity	CreateGameEntityByID(uint32 inID);
		GameEntity	CloneGameEntity(GameEntity inGameEntity);
		void		RemoveGameEntity(const GameEntity& inEntity) { mRegistry.destroy(inEntity); }

		GameEntity	FindEntityByName(const Name& inName);
		GameEntity	FindEntityByID(uint32 inID);

		// Script Layer
		void AttachUpdateScript(const std::function<void(Scene*)>& inScript, eScriptUpdateLevel inLevel) { mScriptStack.AttachUpdateScript(inScript, inLevel); }
		void DattachUpdateScript(const std::function<void(Scene*)>& inScript, eScriptUpdateLevel inLevel) { mScriptStack.DattachUpdateScript(inScript, inLevel); }
		void AttachRenderScript(const std::function<void(Scene*)>& inScript, eScriptRenderLevel inLevel) { mScriptStack.AttachRenderScript(inScript, inLevel); }
		void DattachRenderScript(const std::function<void(Scene*)>& inScript, eScriptRenderLevel inLevel) { mScriptStack.DattachRenderScript(inScript, inLevel); }

		// View & Group
		template <typename... ComponentTypes>
		auto GetView();

		template <typename... ComponentTypes>
		auto GetGroup();

		// Camera
		void				SetSceneCamera(const GameEntity& inEntity);
		const GameEntity&	TryGetSceneCamera() const;

		// Registry
		entt::registry& GetRegistry() { return mRegistry; }

		// Name
		const char* GetName() const { return mSceneName.c_str(); }

	private:
		Scene(std::string_view inSceneName) : mSceneName(inSceneName) {}

		entt::registry	mRegistry    = {};
		std::string		mSceneName   = {};
		ScriptStack		mScriptStack = {};
		GameEntity		mSceneCamera = GameEntity::NullEntity;
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename ...ComponentTypes>
	inline auto cmEngine::Scene::GetView()
	{
		return mRegistry.view<ComponentTypes...>();
	}

	template<typename ...ComponentTypes>
	inline auto cmEngine::Scene::GetGroup()
	{
		return mRegistry.group<ComponentTypes...>();
	}

	inline GameEntity Scene::CreateGameEntity()
	{
		GameEntity entity = GameEntity{ this ,mRegistry.create() };
		return entity;
	}
}

