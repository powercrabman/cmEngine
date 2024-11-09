#include "pch.h"
#include "cmKeyboardPoll.h"
#include "cmWindow.h"
#include "cmWindowsManager.h"

cmKeyboard::cmKeyboard()
{
}

cmKeyboard::~cmKeyboard()
{
}

void cmKeyboard::Update()
{
	BYTE keyStates[256] = {};
	if (!GetKeyboardState(keyStates))
	{
		LOG_ERROR("Cannot Get Keyboard State");
		return;
	}

	for (int i = 0; i < KEY_STATE_MAX; i++)
	{
		eKeyState& state = mKeyState[i];

		if (Engine->GetWindowsManager()->GetMainWindow()->IsFocused())
		{
			if (keyStates[i] & 0x80)
			{
				if (state == eKeyState::Pressed) { state = eKeyState::Hold; }
				else if (state == eKeyState::Release || state == eKeyState::Away) { state = eKeyState::Pressed; }
			}
			else
			{
				if (state == eKeyState::Hold || state == eKeyState::Pressed) { state = eKeyState::Release; }
				else if (state == eKeyState::Release) { state = eKeyState::Away; }
			}
		}
		else
		{
			if (state == eKeyState::Hold || state == eKeyState::Pressed) { state = eKeyState::Release; }
			else if (state == eKeyState::Release) { state = eKeyState::Away; }
		}
	}
}
