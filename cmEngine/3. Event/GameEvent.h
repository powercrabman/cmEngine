#pragma once
namespace cmEngine
{
	//===================================================
	//			          Interface
	//===================================================

	enum class eEventType
	{
		AppShutdownEvent,

		WindowResizeEvent,
		WindowMoveEvent,
		WindowOnFocusEvent,
		WindowOffFocusEvent,

		Count
	};

#define GAMEEVENT_BODY(TypeName)\
		~TypeName() override{};\
		eEventType GetEventType() const override { return eEventType::TypeName; };\
		inline static eEventType sEventType = eEventType::TypeName

	struct GameEvent
	{
		virtual ~GameEvent()                       = default;
		virtual eEventType GetEventType() const    = 0;
	};

	//===================================================
	//			         Concrete
	//===================================================

	struct AppShutdownEvent : public GameEvent
	{
		GAMEEVENT_BODY(AppShutdownEvent);
	};

	struct WindowResizeEvent : public GameEvent
	{
		GAMEEVENT_BODY(WindowResizeEvent);

		uint32	windowWidth;
		uint32	windowHeight;
	};

	struct WindowMoveEvent : public GameEvent
	{
		GAMEEVENT_BODY(WindowMoveEvent);

		uint32	windowX;
		uint32	windowY;
	};

	struct WindowOnFocusEvent : public GameEvent
	{
		GAMEEVENT_BODY(WindowOnFocusEvent);
	};

	struct WindowOffFocusEvent : public GameEvent
	{
		GAMEEVENT_BODY(WindowOffFocusEvent);
	};
}

