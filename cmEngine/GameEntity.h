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

		void Awake();			/* ������Ʈ�� �ʱ�ȭ�� �� ȣ�� (�ʱ�ȭ �Լ�) */
		void Sleep();			/* ������Ʈ�� �ı��� �� ȣ�� (�޸𸮴� �������� ����) */

		void Update();			/* ���� ������Ʈ */
		void FinalUpdate();		/* Update ���� ���ŵ� ������ ���� ������Ʈ ���� ���� �� ���� */
		void PreRender();		/* ���������ΰ� ���õ� �۾��� ���� */

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

		// �̹� ���� ���
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