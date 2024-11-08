#pragma once

class cmGameObject;

class cmComponent
{
public:
	cmComponent();
	virtual ~cmComponent(); 

	virtual void OnStart()		abstract;	/* ������Ʈ�� Active �� �� �� �� ȣ���. */
	virtual void OnFinish()		abstract;	/* ������Ʈ�� �ı��ǰų� Inactive �� �� �� �� ȣ���. */

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
	// ������Ʈ ID
	inline static uint64 sComponentIDCounter = 0;
	uint64 mComponentID = 0;

	cmGameObject* mOwner = nullptr;

	bool mActive = false;
};

