#pragma once
#include "Component.h"

namespace cmEngine
{
	class IPreRenderable;
	class IFinalUpdateable;
	class IUpdateable;
	class ISetupable;

	class GameEntity
	{
		struct ComponentData;
	public:
		GameEntity();
		virtual ~GameEntity();

		void Awake();			/* 오브젝트를 초기화할 때 호출 (초기화 함수) */
		void Sleep();			/* 오브젝트가 파괴될 때 호출 (메모리는 해제하지 않음) */

		void Update();			/* 메인 업데이트 */
		void FinalUpdate();		/* Update 에서 갱신된 내용을 통해 오브젝트 상태 보정 및 결정 */
		void PreRender();		/* 파이프라인과 관련된 작업을 수행 */

		void Destory() { mValid = true; }

		void	SetActive(bool inActive);
		bool	IsActive() const { return mActive; }
		uint64	GetObjectID() const { return mGameEntityID; }

		// Component
		template<typename Ty, typename ...Args>
		Ty* CreateComponent(Args ...args);

		template<typename Ty>
		Ty* FindComponentOrNull() const;

		void SetName(std::string_view inName) { mName = inName; }

		const char* GetName() const { return mName.c_str(); }
		bool		IsValid() const { return mValid; }

	private:
		// Component
		enum { COMPONENT_COUNT_MAX = (uint32)eComponentType::Count };
		std::array<Scope<Component>, COMPONENT_COUNT_MAX>	mCompRepo;

		std::vector<std::pair<Component*, IUpdateable*>>				mUpdateableList;
		std::vector<std::pair<Component*, IFinalUpdateable*>>			mFinalUpdateableList;
		std::vector<std::pair<Component*, IPreRenderable*>>				mPreRenderableList;

		// Identity
		std::string mName = "GameEntity";

		inline static uint64 sGameEntityCounter = 0;
		uint64 mGameEntityID = 0;

		bool mActive = false;
		bool mValid = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	template<typename Ty, typename ...Args>
	inline Ty* GameEntity::CreateComponent(Args ...args)
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
			mCompRepo[idx] = MakeScope<Ty>(std::forward<Args>(args)...);
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
	inline Ty* GameEntity::FindComponentOrNull() const
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

	inline void GameEntity::SetActive(bool inActive)
	{
		if (inActive == mActive)
		{
			ENGINE_LOG_WARN("GameEntity state not changed!");
			return;
		}

		mActive = inActive;

		if (inActive) { Awake(); }
		else { Sleep(); }
	}
};