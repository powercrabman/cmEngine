#include "EnginePch.h"
#include "Scene.h"
#include "GameObject.h"

namespace cmEngine
{
	Scene::Scene()
	{
		mObjectRepo.reserve(256);
		mUpdateList.reserve(256);
	}

	Scene::~Scene()
	{
	}

	void Scene::EnterSceneCore()
	{
		EnterScene();
	}

	void Scene::UpdateScene()
	{
		for (GameObject* obj : mUpdateList)
		{
			if (obj->IsActive())
			{
				obj->Update();
			}
		}
	}

	void Scene::FinalUpdate()
	{
		for (GameObject* obj : mUpdateList)
		{
			if (obj->IsActive())
			{
				obj->FinalUpdate();
			}
		}
	}

	void Scene::PreRender()
	{
		for (GameObject* obj : mUpdateList)
		{
			if (obj->IsActive())
			{
				obj->PreRender();
			}
		}
	}

	void Scene::ExitSceneCore()
	{
		ExitScene();

		// 모든 오브젝트의 Active를 false로 바꾼뒤 파괴
		for (GameObject* obj : mUpdateList)
		{
			obj->SetActive(false);
		}

		mObjectRepo.clear();
		mUpdateList.clear();

		// TODO : 다음 씬으로 넘겨야하는 객체는 따로 처리
	}

	GameObject* Scene::CreateGameObject(bool isActive)
	{
		std::unique_ptr<GameObject> obj = std::make_unique<GameObject>();
		GameObject* ptr = obj.get();
		mUpdateList.push_back(ptr);
		mObjectRepo[obj->GetObjectID()] = std::move(obj);
		if (isActive) { ptr->SetActive(true); };

		return ptr;
	}

	GameObject* Scene::FindGameObjectOrNull(const uint64& inObjID) const
	{
		auto iter = mObjectRepo.find(inObjID);
		if (iter == mObjectRepo.end())
		{
			ASSERT(false, "Do not exist Game Object.");
			LOG_ERROR("Do not exist Game Object.");
			return nullptr;
		}
		return iter->second.get();
	}

	void Scene::RemoveGameObject(const uint64& inObjID)
	{
		auto iter = mObjectRepo.find(inObjID);
		if (iter == mObjectRepo.end())
		{
			ASSERT(false, "Do not exist Game Object.");
			LOG_ERROR("Do not exist Game Object.");
			return;
		}

		// TODO : 최적화 필요
		static const auto FindLambda = [&](GameObject* inObj) { return inObj->GetObjectID() == inObjID; };
		auto removeIter = std::remove_if(mUpdateList.begin(), mUpdateList.end(), FindLambda);
		mUpdateList.erase(removeIter, mUpdateList.end());

		mObjectRepo.erase(iter);
	}
}
