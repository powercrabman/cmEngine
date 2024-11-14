#include "EnginePch.h"
#include "GameObject.h"
#include "Transform.h"
#include "IUpdateable.h"
#include "IPreRenderable.h"
#include "IFinalUpdateable.h"
#include "Component.h"

namespace cmEngine
{
	GameObject::GameObject()
	{
		mGameObjectID = sGameObjectCounter++;

		mUpdateableList.reserve(8);
		mFinalUpdateableList.reserve(8);
		mPreRenderableList.reserve(8);

		// default component
		CreateComponent<Transform>();
	}

	GameObject::~GameObject() {	}

	//Active ������ ������Ʈ�� ��� Start ��Ŵ
	void GameObject::OnStart()
	{
		for (const std::unique_ptr<Component>& cmp : mCompRepo)
		{
			if (cmp && cmp->IsActive())
			{
				cmp->OnStart();
			}
		}
	}

	//��� ������Ʈ�� Finish ��Ŵ
	void GameObject::OnFinish()
	{
		for (const std::unique_ptr<Component>& cmp : mCompRepo)
		{
			if (cmp && cmp->IsActive())
			{
				cmp->OnFinish();
			}
		}
	}

	void GameObject::Update()
	{
		for (auto& [cmp, updateable] : mUpdateableList)
		{
			if (cmp->IsActive())
			{
				updateable->Update();
			}
		}
	}

	void GameObject::FinalUpdate()
	{
		for (auto& [cmp, finalUpdateable] : mFinalUpdateableList)
		{
			if (cmp->IsActive())
			{
				finalUpdateable->FinalUpdate();
			}
		}
	}

	void GameObject::PreRender()
	{
		for (const auto& [cmp, preRenderable] : mPreRenderableList)
		{
			if (cmp->IsActive())
			{
				preRenderable->PreRender();
			}
		}
	}




}