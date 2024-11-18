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

		void AttachSystem(void(*inCallback)(Scene*), eSystemLayer inLayer);
		void DattachSystem(void(*inCallback)(Scene*), eSystemLayer inLayer);

		GameEntity	CreateGameEntity() { return GameEntity{ mRegistry.create() }; }
		void		RemoveGameEntity(const GameEntity& inEntity) { mRegistry.destroy(inEntity); }

		GameEntity	FindEntityByName(const Name& inName);
		GameEntity	FindByID(uint32 inID) const;

		void		SetCameraEntity(const GameEntity& inEntity);
		GameEntity	GetCameraEntity() const;

		void UpdateCamera();

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
		using  GameSystemCallback = void(*)(Scene*);
		std::array<std::vector<GameSystemCallback>, static_cast<uint32>(eSystemLayer::Count)> mSystemLayer;

		// Camera
		GameEntity mDefaultCameraEntity = GameEntity::NullEntity;
		GameEntity mCameraEntity        = GameEntity::NullEntity;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void cmEngine::Scene::AttachSystem(void(*inCallback)(Scene*), eSystemLayer inLayer)
	{
		mSystemLayer[static_cast<uint32>(inLayer)].emplace_back(inCallback);
	}

	inline void cmEngine::Scene::DattachSystem(void(*inCallback)(Scene*), eSystemLayer inLayer)
	{
		auto& callbackList = mSystemLayer[static_cast<uint32>(inLayer)];
		std::erase_if(callbackList,
		              [inCallback](const GameSystemCallback& callback) {
			              return callback == inCallback;
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
}

