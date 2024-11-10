#include "pch.h"
#include "cmKeyboardPoll.h"
#include "cmWindow.h"
#include "cmWindowsManager.h"

cmKeyboardPoll::cmKeyboardPoll()
{
}

cmKeyboardPoll::~cmKeyboardPoll()
{
}
void cmKeyboardPoll::Update()
{
	BYTE keyStates[256] = {};
	if (!GetKeyboardState(keyStates))
	{
		LOG_ERROR("Cannot Get Keyboard State");
		mKeyState.fill(eKeyState::Away);
		return;
	}

	const BYTE KEY_DOWN_MASK = 0x80;

	for (int i = 0; i < KEY_STATE_MAX; i++)
	{
		eKeyState& state = mKeyState[i];

		const bool isKeyDown = (keyStates[i] & KEY_DOWN_MASK) != 0;

		if (isKeyDown)
		{
			switch (state)
			{
			case eKeyState::Away:
			case eKeyState::Release:
				state = eKeyState::Pressed;
				break;
			case eKeyState::Pressed:
				state = eKeyState::Hold;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (state)
			{
			case eKeyState::Pressed:
			case eKeyState::Hold:
				state = eKeyState::Release;
				break;
			case eKeyState::Release:
				state = eKeyState::Away;
				break;
			default:
				break;
			}
		}
	}
}
