#pragma once

#include "cmComponent.h"
#include "cmScript.h"

class cmTransform;
class cmScript;

class cmGameObject
{
	struct ComponentData;
public:
	cmGameObject();
	virtual ~cmGameObject() = default;

	virtual void OnStart();			/* 오브젝트를 초기화할 때 호출 (초기화 함수) */
	virtual void OnFinish();		/* 오브젝트가 파괴될 때 호출 (메모리는 해제하지 않음) */

	virtual void Update();			/* 메인 업데이트 */
	virtual void LateUpdate();		/* Update 에서 갱신된 내용을 통해 오브젝트 상태 보정 및 결정 */

	void SetActive(bool inActive)
	{
		if (inActive == mActive)
		{
			LOG_WARN("GameObject state not changed!");
			return;
		}

		mActive = inActive;

		if (inActive) { OnStart(); }
		else { OnFinish(); }
	}

	bool IsActive() const { return mActive; }
	uint64 GetObjectID() const { return mGameObjectID; }

	template<typename Ty, typename ...Args>
	Ty* CreateComponent(bool isActive, Args ...args)
	{
		static_assert(std::is_base_of<cmComponent, Ty>::value, "Ty must derived by cmComponent.");

		auto iter = mCompRepo.find(TYPE_ID(Ty));
		if (iter != mCompRepo.end())
		{
			LOG_ERROR("Component of this type already exists.");
			return static_cast<Ty*>(iter->second.get()); 
		}

		std::unique_ptr<Ty> cmp = std::make_unique<Ty>(std::forward<Args>(args)...);
		cmp->SetOwner(this);
		if (isActive) { cmp->SetActive(true); }

		Ty* ptr = cmp.get();
		
		mCompRepo[TYPE_ID(Ty)] = std::move(cmp);

		if constexpr (std::is_base_of<cmScript, Ty>::value)
		{
			ptr->Initialize();
			mUpdateList.push_back(ptr);
		}

		return ptr;
	}

	template<typename Ty>
	Ty* FindComponentOrNull()
	{
		static_assert(std::is_base_of<cmComponent, Ty>::value, "Ty must derived by cmComponent.");

		auto iter = mCompRepo.find(TYPE_ID(Ty));

		if (iter == mCompRepo.end())
		{
			ASSERT(false, "Do not exist component");
			LOG_ERROR("Component does not exist.");
			return nullptr;
		}

		return static_cast<Ty*>(iter->second.get());
	}

private:
	inline static uint64 sGameObjectCounter = 0;

	// TODO : 현재 컴포넌트 생성만 존재하고, 제거는 존재하지 않음
	std::unordered_map<cmTypeID, std::unique_ptr<cmComponent>> mCompRepo;
	std::vector<cmScript*> mUpdateList;

	std::string mName = "Undefined";

	uint64 mGameObjectID = 0;
	bool mActive = false;
};