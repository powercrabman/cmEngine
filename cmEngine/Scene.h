#pragma once

namespace cmEngine
{
	class GameObject;

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

		GameObject* CreateGameObject(bool isActive);
		GameObject* FindGameObjectOrNull(const uint64& inObjID) const;
		void		RemoveGameObject(const uint64& inObjID);

		std::vector<GameObject*>::const_iterator GetGameObjectsConstBegin() const { return mUpdateList.cbegin(); }
		std::vector<GameObject*>::const_iterator GetGameObjectsConstEnd() const { return mUpdateList.cend(); }


		virtual constexpr const char* ToString() abstract;

	protected:
		virtual void EnterScene() abstract;
		virtual void ExitScene() abstract;

	private:
		std::unordered_map<uint64, std::unique_ptr<GameObject>> mObjectRepo;
		std::vector<GameObject*> mUpdateList;
	};
}

