#include "pch.h"
#include "cmScene.h"
#include "cmGameObject.h"

cmScene::cmScene()
{
	mObjectRepo.reserve(256);
	mUpdateList.reserve(256);
}

cmScene::~cmScene()
{
}

void cmScene::EnterSceneCore()
{
	EnterScene();
}

void cmScene::UpdateScene()
{
	for (cmGameObject* obj : mUpdateList)
	{
		if (obj->IsActive())
		{
			obj->Update();
		}
	}
}

void cmScene::LateUpdate()
{
	for (cmGameObject* obj : mUpdateList) 
	{
		if (obj->IsActive()) 
		{
			obj->LateUpdate();
		}
	}
}

void cmScene::PreRender()
{
	for (cmGameObject* obj : mUpdateList)
	{
		if (obj->IsActive())
		{
			obj->PreRender();
		}
	}
}

void cmScene::ExitSceneCore()
{
	ExitScene();

	// ��� ������Ʈ�� Active�� false�� �ٲ۵� �ı�
	for (cmGameObject* obj : mUpdateList)
	{
		obj->SetActive(false);
	}

	mObjectRepo.clear();
	mUpdateList.clear();

	// TODO : ���� ������ �Ѱܾ��ϴ� ��ü�� ���� ó��
}

cmGameObject* cmScene::CreateGameObject(bool isActive)
{
	std::unique_ptr<cmGameObject> obj = std::make_unique<cmGameObject>();
	cmGameObject* ptr = obj.get();
	mUpdateList.push_back(ptr);
	mObjectRepo[obj->GetObjectID()] = std::move(obj);
	if (isActive) { ptr->SetActive(true); };

	return ptr;
}

cmGameObject* cmScene::FindGameObjectByIDOrNull(const uint64& inObjID) const
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

void cmScene::RemoveGameObject(const uint64& inObjID)
{
	auto iter = mObjectRepo.find(inObjID);
	if (iter == mObjectRepo.end())
	{
		ASSERT(false, "Do not exist Game Object.");
		LOG_ERROR("Do not exist Game Object.");
		return;
	}

	// TODO : ����ȭ �ʿ�
	static const auto FindLambda = [&](cmGameObject* inObj) { return inObj->GetObjectID() == inObjID; };
	auto removeIter = std::remove_if(mUpdateList.begin(), mUpdateList.end(), FindLambda);
	mUpdateList.erase(removeIter, mUpdateList.end());

	mObjectRepo.erase(iter);
}
