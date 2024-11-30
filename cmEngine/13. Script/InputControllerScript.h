#pragma once

namespace cmEngine
{
	inline void InputControllerScript(Scene* inScene)
	{
		auto view = inScene->GetView<InputController>();

		for (auto entity : view)
		{
			InputController& ic = view.get<InputController>(entity);

			for (const KeyEvent& keyEvent : ic.keyEvents)
			{
				if (Input::IsKeyState(keyEvent.keyCode, keyEvent.keyState))
				{
					keyEvent.eventCallback({ inScene, entity });
				}
			}
		}
	}
}