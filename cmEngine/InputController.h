#pragma once

namespace cmEngine
{
	// Component가 아닙니다.
	struct KeyEvent
	{
		std::string						eventName;
		eKeyCode						keyCode;
		eKeyState						keyState;
		std::function<void(GameEntity)> eventCallback;
	};

	// 이게 컴포넌트입니다.
	struct InputController
	{
		void Dattach(const std::string& inEventName)
		{
			std::erase_if(keyEvents, [&](const KeyEvent& inEvent) {
				return inEventName == inEvent.eventName;
				});
		}

		std::vector<KeyEvent> keyEvents;
	};
}