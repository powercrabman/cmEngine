#include "pch.h"
#include "cmGameObject.h"
#include "cmScript.h"
#include "cmTransform.h"
#include "cmIRenderable.h"

inline cmGameObject::cmGameObject()
{
	mGameObjectID = sGameObjectCounter++;

	mScripts.reserve(16);
	mRenderableList.reserve(16);

	mTransform = CreateComponent<cmTransform>(true);
}

cmGameObject::~cmGameObject()
{
}

//Active 상태인 컴포넌트를 모두 Start 시킴
void cmGameObject::OnStart()
{
	for (const std::unique_ptr<cmScript>& cmp : mScripts)
	{
		if (cmp->IsActive())
		{
			cmp->OnStart();
		}
	}
}

//모든 컴포넌트를 Finish 시킴
void cmGameObject::OnFinish()
{
	for (const std::unique_ptr<cmScript>& cmp : mScripts)
	{
		if (cmp->IsActive())
		{
			cmp->OnFinish();
		}
	}
}

void cmGameObject::Update()
{
	for (const std::unique_ptr<cmScript>& cmp : mScripts)
	{
		if (cmp->IsActive())
		{
			cmp->Update();
		}
	}
}

void cmGameObject::LateUpdate()
{
	for (const std::unique_ptr<cmScript>& cmp : mScripts)
	{
		if (cmp->IsActive())
		{
			cmp->LateUpdate();
		}
	}
}

void cmGameObject::PreRender()
{
	for (const auto& [cmp, renderable] : mRenderableList)
	{
		if (cmp->IsActive())
		{
			renderable->Render();
		}
	}
}

