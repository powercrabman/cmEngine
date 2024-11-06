#include "pch.h"
#include "cmGameObject.h"
#include "cmScript.h"
#include "cmTransform.h"

inline cmGameObject::cmGameObject()
{
	mGameObjectID = sGameObjectCounter++;
	mUpdateList.reserve(16);
	mCompRepo.reserve(32);

	CreateComponent<cmTransform>(true);
}

//Active ������ ������Ʈ�� ��� Start ��Ŵ
void cmGameObject::OnStart()
{
	for (cmScript* cmp : mUpdateList)
	{
		if (cmp->IsActive())
		{
			cmp->OnStart();
		}
	}
}

//��� ������Ʈ�� Finish ��Ŵ
void cmGameObject::OnFinish()
{
	for (cmScript* cmp : mUpdateList)
	{
		cmp->OnFinish();
	}
}

void cmGameObject::Update()
{
	for (cmScript* cmp : mUpdateList)
	{
		if (cmp->IsActive())
		{
			cmp->Update();
		}
	}
}

void cmGameObject::LateUpdate()
{
	for (cmScript* cmp : mUpdateList)
	{
		if (cmp->IsActive())
		{
			cmp->LateUpdate();
		}
	}
}

