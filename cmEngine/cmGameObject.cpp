#include "pch.h"
#include "cmGameObject.h"
#include "cmScript.h"
#include "cmTransform.h"
#include "cmIUpdateable.h"
#include "cmIPreRenderable.h"
#include "cmIFinalUpdateable.h"

inline cmGameObject::cmGameObject()
{
	mGameObjectID = sGameObjectCounter++;

	mUpdateableList.reserve(8);
	mFinalUpdateableList.reserve(8);
	mPreRenderableList.reserve(8);

	mTransform = CreateComponent<cmTransform>(true);
}

cmGameObject::~cmGameObject()
{
}

//Active ������ ������Ʈ�� ��� Start ��Ŵ
void cmGameObject::OnStart()
{
	for (const std::unique_ptr<cmComponent>& cmp : mCompRepo)
	{
		if (cmp && cmp->IsActive())
		{
			cmp->OnStart();
		}
	}
}

//��� ������Ʈ�� Finish ��Ŵ
void cmGameObject::OnFinish()
{
	for (const std::unique_ptr<cmComponent>& cmp : mCompRepo)
	{
		if (cmp && cmp->IsActive())
		{
			cmp->OnFinish();
		}
	}
}

void cmGameObject::Update()
{
	for (auto& [cmp, updateable] : mUpdateableList)
	{
		if (cmp->IsActive())
		{
			updateable->Update();
		}
	}
}

void cmGameObject::FinalUpdate()
{
	for (auto& [cmp, finalUpdateable] : mFinalUpdateableList)
	{
		if (cmp->IsActive())
		{
			finalUpdateable->FinalUpdate();
		}
	}
}

void cmGameObject::PreRender()
{
	for (const auto& [cmp, preRenderable] : mPreRenderableList)
	{
		if (cmp->IsActive())
		{
			preRenderable->PreRender();
		}
	}
}

