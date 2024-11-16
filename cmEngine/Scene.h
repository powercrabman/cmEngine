#pragma once

namespace cmEngine
{
	class GameEntity;

#define SCENE_BODY(SceneClassName) \
	virtual const char*			ToString() override { return #SceneClassName; }; \

	class Scene
	{
	public:
		Scene();
		virtual ~Scene();

		void EnterSceneCore();
		void UpdateScene();
		void FinalUpdate();
		void PreRender();
		void ExitSceneCore();

		GameEntity* CreateGameEntity(bool isActive = true);
		GameEntity* FindGameEntityOrNull(const uint64& inObjID) const;
		void		RemoveGameEntity(const uint64& inObjID);

		std::vector<GameEntity*>::const_iterator GetGameEntitiesConstBegin() const { return mUpdateList.cbegin(); }
		std::vector<GameEntity*>::const_iterator GetGameEntitiesConstEnd() const { return mUpdateList.cend(); }

		const std::vector<GameEntity*>& GetGameEntities() const { return mUpdateList; }

		inline size_t GetEntityCount() { return mUpdateList.size(); }

		virtual constexpr const char* ToString() abstract;

	protected:
		virtual void EnterScene() abstract;
		virtual void ExitScene() abstract;

	private:
		std::unordered_map<uint64, Scope<GameEntity>> mObjectRepo;
		std::vector<GameEntity*> mUpdateList;
	};
}

