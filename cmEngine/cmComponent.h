#pragma once

class cmGameObject;

class cmComponent
{
public:
	cmComponent();
	virtual ~cmComponent(); 

	virtual void OnStart()		abstract;	/* 컴포넌트가 Active 될 떄 한 번 호출됨. */
	virtual void OnFinish()		abstract;	/* 컴포넌트가 파괴되거나 Inactive 될 떄 한 번 호출됨. */

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

	uint64 GetComponentID() const { return mComponentID; }

	void SetOwner(cmGameObject* inOwner) { mOwner = inOwner; }
	cmGameObject* GetOwner() const { return mOwner; }

private:
	// 컴포넌트 ID
	inline static uint64 sComponentIDCounter = 0;
	uint64 mComponentID = 0;

	cmGameObject* mOwner = nullptr;

	bool mActive = false;
};

