#pragma once

namespace cmEngine
{
	class EventDispatcher
	{
		SINGLETON(EventDispatcher);
	public:
		template <typename EventType>
		void	EventDispatch(const EventType& inEvent)
		{
			const auto& list = mEventHandlerRepo[static_cast<uint32_t>(EventType::sEventType)];
			if constexpr (std::is_same_v<EventType, AppShutdownEvent>)
			{
				for (auto iter = list.rbegin(); iter != list.rend(); ++iter)
				{
					(*iter)(inEvent);
				}
			}
			else
			{
				for (const auto& func : list)
				{
					func(inEvent);
				}
			}
		}

		template <typename EventType>
		void	AttachEventHandler(const std::function<void(const EventType&)>& inCallback)
		{
			mEventHandlerRepo[static_cast<uint32_t>(EventType::sEventType)].emplace_back(
				[=](const GameEvent& event)
				{
					inCallback(static_cast<const EventType&>(event));
				}
			);
		}

	private:
		EventDispatcher() = default;
		~EventDispatcher() = default;

		using CallbackBase = std::function<void(const GameEvent&)>;
		std::array<std::vector<CallbackBase>, static_cast<uint32_t>(eEventType::Count)> mEventHandlerRepo = {};
	};
}