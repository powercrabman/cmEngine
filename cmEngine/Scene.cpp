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

		// ��� ������Ʈ�� Active�� false�� �ٲ۵� �ı�
		for (GameObject* obj : mUpdateList)
		{
			obj->SetActive(false);
		}

		mObjectRepo.clear();
		mUpdateList.clear();

		// TODO : ���� ������ �Ѱܾ��ϴ� ��ü�� ���� ó��
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

		// TODO : ����ȭ �ʿ�
		static const auto FindLambda = [&](GameObject* inObj) { return inObj->GetObjectID() == inObjID; };
		auto removeIter = std::remove_if(mUpdateList.begin(), mUpdateList.end(), FindLambda);
		mUpdateList.erase(removeIter, mUpdateList.end());

		mObjectRepo.erase(iter);
	}
}
