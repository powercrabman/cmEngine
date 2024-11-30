#pragma once

namespace cmEngine
{
	// Component�� �ƴմϴ�.
	struct KeyEvent
	{
		std::string						eventName;
		eKeyCode						keyCode;
		eKeyState						keyState;
		std::function<void(GameEntity)> eventCallback;
	};

	// �̰� ������Ʈ�Դϴ�.
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