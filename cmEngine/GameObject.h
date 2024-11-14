#pragma once
#include "Component.h"

namespace cmEngine
{
	class IPreRenderable;
	class IFinalUpdateable;
	class IUpdateable;
	class ISetupable;

	class GameObject
	{
		struct ComponentData;
	public:
		GameObject();
		virtual ~GameObject();

		void OnStart();			/* 오브젝트를 초기화할 때 호출 (초기화 함수) */
		void OnFinish();		/* 오브젝트가 파괴될 때 호출 (메모리는 해제하지 않음) */

		void Update();			/* 메인 업데이트 */
		void FinalUpdate();		/* Update 에서 갱신된 내용을 통해 오브젝트 상태 보정 및 결정 */
		void PreRender();		/* 파이프라인과 관련된 작업을 수행 */

		void	SetActive(bool inActive);
		bool	IsActive() const { return mActive; }
		uint64	GetObjectID() const { return mGameObjectID; }

		// Component
		template<typename Ty, typename ...Args>
		Ty* CreateComponent(Args ...args);

		template<typename Ty>
		Ty* FindComponentOrNull() const;

	private:
		// Component
		enum { COMPONENT_TYPE_COUNT = (uint32)eComponentType::Count };
		std::array<std::unique_ptr<Component>, COMPONENT_TYPE_COUNT>	mCompRepo;

		std::vector<std::pair<Component*, IUpdateable*>>				mUpdateableList;
		std::vector<std::pair<Component*, IFinalUpdateable*>>			mFinalUpdateableList;
		std::vector<std::pair<Component*, IPreRenderable*>>				mPreRenderableList;
		
		// Identity
		std::string mName = "Undefined";

		inline static uint64 sGameObjectCounter = 0;
		uint64 mGameObjectID = 0;

		bool mActive = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename Ty, typename ...Args>
	inline Ty* GameObject::CreateComponent(Args ...args)
	{
		static_assert(std::is_base_of<Component, Ty>::value, "Ty must derived by Component.");
		uint32 idx = static_cast<uint32>(Ty::ComponentType);

		// 이미 있을 경우
		if (mCompRepo[idx])
		{
			ASSERT(false, "This is a component type that already exists.");
			ENGINE_LOG_ERROR("This is a component type that already exists.");
			return static_cast<Ty*>(mCompRepo[idx].get());
		}
		else
		{
			mCompRepo[idx] = std::make_unique<Ty>(std::forward<Args>(args)...);
			Ty* ptr = static_cast<Ty*>(mCompRepo[idx].get());
			ptr->SetOwner(this);
		
			if constexpr (std::is_base_of<ISetupable, Ty>::value) { ptr->Setup(); }
			if constexpr (std::is_base_of<IUpdateable, Ty>::value) { mUpdateableList.emplace_back(ptr, ptr); }
			if constexpr (std::is_base_of<IFinalUpdateable, Ty>::value) { mFinalUpdateableList.emplace_back(ptr, ptr); }
			if constexpr (std::is_base_of<IPreRenderable, Ty>::value) { mPreRenderableList.emplace_back(ptr, ptr); }
		
			ptr->SetActive(true);
		
			return ptr;
		}
	}

	template<typename Ty>
	inline Ty* GameObject::FindComponentOrNull() const
	{
		static_assert(std::is_base_of<Component, Ty>::value, "Ty must derived by Component.");
		uint32 idx = (uint32)Ty::ComponentType;

		if (mCompRepo[idx])
		{
			return static_cast<Ty*>(mCompRepo[idx].get());
		}
		else
		{
			ASSERT(false, "retVal is nullptr!");
			ENGINE_LOG_ERROR("retVal is nullptr!");
			return nullptr;
		}
	}

	inline void GameObject::SetActive(bool inActive)
	{
		if (inActive == mActive)
		{
			ENGINE_LOG_WARN("GameObject state not changed!");
			return;
		}

		mActive = inActive;

		if (inActive) { OnStart(); }
		else { OnFinish(); }
	}
};