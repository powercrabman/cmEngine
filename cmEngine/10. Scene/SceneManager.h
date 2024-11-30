#pragma once
#include "10. Scene/Scene.h"

namespace cmEngine
{
	class SceneManager
	{
		SINGLETON(SceneManager);
		struct SceneNode;
		using SceneNodeIterator = std::unordered_map<std::string, SceneNode>::iterator;
	public:
		Scene*	CreateScene(std::string_view inSceneName);
		Scene*	CreateOrReplaceScene(std::string_view inSceneName);
		Scene*	TryFindScene(std::string_view inSceneName);

		bool	IsExistScene(std::string_view inSceneName) const {return mSceneRepo.contains(inSceneName.data());}

		bool	RemoveScene(std::string_view inSceneName);
		bool	RemoveScene(Scene* inScene);

		void	ChangeScene(std::string_view inSceneName);
		void	ChangeScene(Scene* inScene);

		Scene*	TryGetCurrentScene() const { return mCurrentScene; }

		std::vector<const char *>::const_iterator	GetSceneCBegin() const { return mSceneList.cbegin(); }
		std::vector<const char *>::const_iterator	GetSceneCEnd() const { return mSceneList.cend(); }
		std::vector<const char *>::iterator			GetSceneBegin() { return mSceneList.begin(); }
		std::vector<const char *>::iterator			GetSceneEnd() { return mSceneList.end(); }
		auto										GetSceneNameList() { return std::make_pair(mSceneList.data(), mSceneList.size()); }

	private:
		SceneManager();
		~SceneManager();

		void	Update() const;
		void	Render() const;
		bool	RemoveSceneEx(SceneNodeIterator inIter);

		struct SceneNode
		{
			Scope<Scene> scene;
			size_t listIdx = 0;
		};
		std::unordered_map<std::string, SceneNode>		mSceneRepo    = {};
		std::vector<const char*>						mSceneList    = {};
		Scene*											mCurrentScene = nullptr;
	};
}
