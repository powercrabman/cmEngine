#pragma once

#include "cmScript.h"

class cmTransform;
class cmScript;
class cmIRenderable;

class cmGameObject
{
	struct ComponentData;
public:
	cmGameObject();
	virtual ~cmGameObject();

	void OnStart();			/* 오브젝트를 초기화할 때 호출 (초기화 함수) */
	void OnFinish();		/* 오브젝트가 파괴될 때 호출 (메모리는 해제하지 않음) */

	void Update();			/* 메인 업데이트 */
	void LateUpdate();		/* Update 에서 갱신된 내용을 통해 오브젝트 상태 보정 및 결정 */
	void PreRender();		/* 파이프라인과 관련된 작업을 수행 */

	cmTransform* GetTransform() const { return mTransform; }

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

		if constexpr (!std::is_base_of<cmScript, Ty>::value)
		{
			uint32 idx = (uint32)Ty::ComponentType;
			if (mCompRepo[idx])
			{
				ASSERT(false, "already exist component!");
				LOG_ERROR("already exist component!");
				return static_cast<Ty*>(mCompRepo[idx].get());
			}
		}

		std::unique_ptr<Ty> inst = std::make_unique<Ty>(std::forward<Args>(args)...);
		inst->SetOwner(this);
		Ty* retVal = inst.get();

		if constexpr (std::is_base_of<cmScript, Ty>::value)
		{
			inst->Initialize();
			mScripts.push_back(std::move(inst));
		}
		else
		{
			mCompRepo[(uint32)Ty::ComponentType] = std::move(inst);

			if constexpr (std::is_base_of<cmIRenderable, Ty>::value)
			{
				mRenderableList.push_back(std::make_pair(retVal, retVal));
			}
		}

		if (isActive) { retVal->SetActive(true); }
		return retVal;
	}

	template<typename Ty>
	Ty* FindComponentOrNull() const
	{
		static_assert(std::is_base_of<cmComponent, Ty>::value, "Ty must derived by cmComponent.");

		const std::unique_ptr<cmComponent>& retVal = mCompRepo[(uint32)Ty::ComponentType];

		if (retVal)
		{
			return static_cast<Ty*>(retVal.get());
		}
		else
		{
			ASSERT(false, "retVal is nullptr!");
			LOG_ERROR("retVal is nullptr!");
			return nullptr;
		}
	}

private:
	inline static uint64 sGameObjectCounter = 0;

	// TODO : 현재 구조는 마구잡이 식이라 나중에 고치기
	enum { COMPONENT_COUNT = (uint32)(eComponentType::Count) };
	std::array<std::unique_ptr<cmComponent>, COMPONENT_COUNT> mCompRepo = {};
	std::vector<std::unique_ptr<cmScript>> mScripts = {};
	std::vector<std::pair<cmComponent*, cmIRenderable*>> mRenderableList = {};

	cmTransform* mTransform = nullptr;

	std::string mName = "Undefined";

	uint64 mGameObjectID = 0;
	bool mActive = false;
};