#include "EnginePch.h"
#include "Scene.h"
#include "GameEntity.h"

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
		for (GameEntity* obj : mUpdateList)
		{
			if (obj->IsActive())
			{
				obj->Update();
			}
		}

		for (GameEntity* obj : mUpdateList)
		{
			if (obj->IsActive())
			{
				obj->FinalUpdate();
			}
		}

		for (GameEntity* obj : mUpdateList)
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
		for (GameEntity* obj : mUpdateList)
		{
			obj->SetActive(false);
		}

		mObjectRepo.clear();
		mUpdateList.clear();

		// TODO : ���� ������ �Ѱܾ��ϴ� ��ü�� ���� ó��
	}

	GameEntity* Scene::CreateGameEntity(bool isActive)
	{
		Scope<GameEntity> obj = MakeScope<GameEntity>();
		GameEntity* ptr = obj.get();
		mUpdateList.push_back(ptr);
		mObjectRepo[obj->GetObjectID()] = std::move(obj);
		if (isActive) { ptr->SetActive(true); };

		return ptr;
	}

	GameEntity* Scene::FindGameEntityOrNull(const uint64& inObjID) const
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

	void Scene::RemoveGameEntity(const uint64& inObjID)
	{
		auto iter = mObjectRepo.find(inObjID);
		if (iter == mObjectRepo.end())
		{
			ASSERT(false, "Do not exist Game Object.");
			LOG_ERROR("Do not exist Game Object.");
			return;
		}

		// TODO : ����ȭ �ʿ�
		static const auto FindLambda = [&](GameEntity* inObj) { return inObj->GetObjectID() == inObjID; };
		auto removeIter = std::remove_if(mUpdateList.begin(), mUpdateList.end(), FindLambda);
		mUpdateList.erase(removeIter, mUpdateList.end());

		mObjectRepo.erase(iter);
	}
}
