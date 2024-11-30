#include "0. cmEngine/cmEngine.h"
#include "SceneManager.h"
#include "Scene.h"

namespace cmEngine
{
	void SceneManager::Update() const
	{
		if (mCurrentScene)
		{
			mCurrentScene->UpdateScene();
		}
	}
	void SceneManager::Render() const
	{
		if (mCurrentScene)
		{
			mCurrentScene->RenderScene();
		}
	}

	SceneManager::SceneManager()
	{
		EventDispatcher::Ref().AttachEventHandler<AppShutdownEvent>([](const AppShutdownEvent& e) { Destroy(); });
	}

	SceneManager::~SceneManager()
	{
		if (mCurrentScene)
		{
			mCurrentScene->ExitScene();
		}
		mSceneRepo.clear();
		mCurrentScene = nullptr;
	}

	Scene* SceneManager::CreateScene(std::string_view inSceneName)
	{
		auto [iter, ret] = mSceneRepo.emplace(inSceneName.data(), SceneNode{ .scene = Scope<Scene>(new Scene(inSceneName)), .listIdx = mSceneList.size() });
		mSceneList.emplace_back(iter->first.data());

		if (!ret)
		{
			ENGINE_LOG_ERROR("Scene name is duplicate");
			assert(false);
		}

		return iter->second.scene.get();
	}

	Scene* SceneManager::CreateOrReplaceScene(std::string_view inSceneName)
	{
		auto iter = mSceneRepo.find(inSceneName.data());

		if (iter != mSceneRepo.end())
		{
			ENGINE_LOG_INFO("Replacing existing scene with name: {}", inSceneName);

			if (mCurrentScene && inSceneName == mCurrentScene->GetName()) { mCurrentScene = nullptr; }
			iter->second.scene.reset(new Scene(inSceneName));
			return iter->second.scene.get();
		}
		else
		{
			ENGINE_LOG_INFO("Creating new scene with name: {}", inSceneName);
			return CreateScene(inSceneName);
		}
	}

	Scene* SceneManager::TryFindScene(std::string_view inSceneName)
	{
		auto iter = mSceneRepo.find(inSceneName.data());
		if (iter == mSceneRepo.end())
		{
			return nullptr;
		}
		else
		{
			return iter->second.scene.get();
		}
	}

	void SceneManager::ChangeScene(std::string_view inSceneName)
	{
		Scene* sc = TryFindScene(inSceneName);
		if (sc) { ChangeScene(sc); }
		else { assert(false); }
	}

	void SceneManager::ChangeScene(Scene* inScene)
	{
		if (mCurrentScene)
		{
			mCurrentScene->ExitScene();
		}

		mCurrentScene = inScene;
		mCurrentScene->EnterScene();
	}

	bool SceneManager::RemoveScene(std::string_view inSceneName)
	{
		return RemoveSceneEx(mSceneRepo.find(inSceneName.data()));
	}

	bool SceneManager::RemoveScene(Scene* inScene)
	{
		return RemoveSceneEx(mSceneRepo.find(inScene->GetName()));
	}

	bool SceneManager::RemoveSceneEx(SceneNodeIterator inIter)
	{
		if (inIter == mSceneRepo.end())
		{
			ENGINE_LOG_ERROR("Scene doesn't exist");
			return false;
		}

		// 만약 지우고자 하는 씬이 현재 씬과 동일하다면
		if (inIter->first == mCurrentScene->GetName())
		{
			mCurrentScene->ExitScene();
			mCurrentScene = nullptr;
		}

		// 삭제
		uint32 listIdx = inIter->second.listIdx;

		if (listIdx < mSceneList.size() - 1)
		{
			std::swap(mSceneList[listIdx], mSceneList.back());
			mSceneRepo[mSceneList[listIdx]].listIdx = listIdx;
		}

		mSceneList.pop_back();
		mSceneRepo.erase(inIter);

		return true;
	}
}
