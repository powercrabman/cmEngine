#pragma once

class GameObject;

namespace cmEngine
{

#define COMPONENT_BODY(ComponentClassName) \
	virtual const char* ToString() override { return #ComponentClassName; } \
	inline static eComponentType ComponentType = eComponentType::ComponentClassName

	enum class eComponentType
	{
		Transform = 0,
		CameraComponent,
		GuiComponent,

		/* RendererComponent */
		FlipbookRenderer,
		SpriteRenderer,
		GeometryRenderer,

		Script,

		Count
	};

	class Component
	{
	public:
		Component();
		virtual ~Component();

		virtual void OnStart()		abstract;	/* ������Ʈ�� Active �� �� �� �� ȣ���. */
		virtual void OnFinish()		abstract;	/* ������Ʈ�� �ı��ǰų� Inactive �� �� �� �� ȣ���. */

		void		SetActive(bool inActive);
		bool		IsActive() const { return mActive; }

		uint64		GetComponentID() const { return mComponentID; }

		void		SetOwner(GameObject* inOwner) { mOwner = inOwner; }
		GameObject* GetOwner() const { return mOwner; }

		virtual const char* ToString() abstract;

	private:
		// ������Ʈ ID
		inline static uint64 sComponentIDCounter = 0;
		uint64 mComponentID = 0;

		GameObject* mOwner = nullptr;

		bool mActive = false;
	};

	//===================================================
	//                      Inline
	//===================================================

	inline void Component::SetActive(bool inActive)
	{
		if (inActive == mActive)
		{
			ENGINE_LOG_TRACE("GameObject state not changed!");
			return;
		}

		mActive = inActive;

		if (inActive) { OnStart(); }
		else { OnFinish(); }
	}
}

