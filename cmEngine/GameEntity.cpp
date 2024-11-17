#include "EnginePch.h"
#include "GameEntity.h"
#include "Transform.h"
#include "IUpdateable.h"
#include "IPreRenderable.h"
#include "IFinalUpdateable.h"
#include "Component.h"

namespace cmEngine
{
	GameEntity::GameEntity()
	{
		mGameEntityID = sGameEntityCounter++;

		mUpdateableList.reserve(8);
		mFinalUpdateableList.reserve(8);
		mPreRenderableList.reserve(8);

		mValid = true;

		// default component
		CreateComponent<Transform>();
	}

	GameEntity::~GameEntity() { Sleep(); }

	//Active ������ ������Ʈ�� ��� Start ��Ŵ
	void GameEntity::Awake()
	{
		for (const Scope<Component>& cmp : mCompRepo)
		{
			if (cmp && cmp->IsActive())
			{
				cmp->Awake();
			}
		}
	}

	//��� ������Ʈ�� Finish ��Ŵ
	void GameEntity::Sleep()
	{
		for (const Scope<Component>& cmp : mCompRepo)
		{
			if (cmp && cmp->IsActive())
			{
				cmp->Sleep();
			}
		}
	}

	void GameEntity::Update()
	{
		for (auto& [cmp, updateable] : mUpdateableList)
		{
			if (cmp->IsActive())
			{
				updateable->Update();
			}
		}
	}

	void GameEntity::FinalUpdate()
	{
		for (auto& [cmp, finalUpdateable] : mFinalUpdateableList)
		{
			if (cmp->IsActive())
			{
				finalUpdateable->FinalUpdate();
			}
		}
	}

	void GameEntity::PreRender()
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