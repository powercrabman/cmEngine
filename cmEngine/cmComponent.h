#pragma once

class cmGameObject;

class cmComponent
{
public:
	cmComponent() { mComponentID = sComponentIDCounter++; }; /* 자원 생성 */
	virtual ~cmComponent() = default; /* 자원 해제 */

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

////////////////////////////////
// 1. 내 프로그램에는 VertexShader와 PixelShader 구조체가 존재함
// 2. ConstantBuffer<T> 클래스도 존재함
// 3. VertexShader와 PixelShader 클래스가 멤버 변수로 사용할 컨스턴트 버퍼 리스트를 가지도록함
// 4. UpdateConstantBuffers(this) 를 통해서 상수버퍼를 업데이트 할 수 있다.
// 참고로 this는 Object이다.
// 상수버퍼마다 정보를 업데이트하는 방법이 제각각이기에..
////////////////////////////////
