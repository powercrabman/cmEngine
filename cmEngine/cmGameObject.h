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

	virtual void OnStart();			/* ������Ʈ�� �ʱ�ȭ�� �� ȣ�� (�ʱ�ȭ �Լ�) */
	virtual void OnFinish();		/* ������Ʈ�� �ı��� �� ȣ�� (�޸𸮴� �������� ����) */

	virtual void Update();			/* ���� ������Ʈ */
	virtual void LateUpdate();		/* Update ���� ���ŵ� ������ ���� ������Ʈ ���� ���� �� ���� */

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

	// TODO : ���� ������Ʈ ������ �����ϰ�, ���Ŵ� �������� ����
	std::unordered_map<cmTypeID, std::unique_ptr<cmComponent>> mCompRepo;
	std::vector<cmScript*> mUpdateList;

	std::string mName = "Undefined";

	uint64 mGameObjectID = 0;
	bool mActive = false;
};