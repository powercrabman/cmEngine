#pragma once

namespace cmEngine
{
	class GameEntity;

#define SCENE_BODY(SceneClassName) \
	virtual const char*			ToString() override { return #SceneClassName; }; \

	enum eSystemLayer
	{
		Update = 0,
		Render,
		//
		Count
	};

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void EnterSceneCore();
		void UpdateScene();
		void RenderScene();
		void ExitSceneCore();

		void AttachSystem(std::function<void(Scene*)> inCallback, eSystemLayer inLayer);
		void DattachSystem(std::function<void(Scene*)> inCallback, eSystemLayer inLayer);

		GameEntity	CreateGameEntity();
		GameEntity	CloneGameEntity(GameEntity inGameEntity);

		void		RemoveGameEntity(const GameEntity& inEntity) { mRegistry.destroy(inEntity); }

		GameEntity	FindEntityByName(const Name& inName);
		GameEntity	FindByID(uint32 inID) const;

		void		SetMainCameraEntity(const GameEntity& inEntity);
		GameEntity	GetMainCameraEntity() const;

		template <typename... ComponentTypes>
		auto GetView();

		template <typename... ComponentTypes>
		auto GetGroup();

		entt::registry& GetRegistry() { return mRegistry; }

		virtual constexpr const char* ToString() = 0;

	protected:
		virtual void EnterScene() = 0;
		virtual void ExitScene() = 0;

	private:
		entt::registry mRegistry = {};

		// System Layer
		using GameSystemCallback = std::function<void(Scene*)>;
		std::array<std::vector<GameSystemCallback>, static_cast<uint32>(eSystemLayer::Count)> mSystemLayer;

		// Camera
		GameEntity mDefaultCameraEntity = GameEntity::NullEntity;
		GameEntity mCameraEntity = GameEntity::NullEntity;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void Scene::AttachSystem(GameSystemCallback inCallback, eSystemLayer inLayer)
	{
		mSystemLayer[static_cast<uint32>(inLayer)].emplace_back(std::move(inCallback));
	}

	inline void Scene::DattachSystem(GameSystemCallback inCallback, eSystemLayer inLayer)
	{
		auto& callbackList = mSystemLayer[static_cast<uint32>(inLayer)];
		std::erase_if(callbackList, [inCallback](const GameSystemCallback& callback) {
			return callback.target<void(Scene*)>() == inCallback.target<void(Scene*)>();
			});
	}

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
		GameEntity entity = GameEntity{ mRegistry.create() };
		return entity;
	}
}

